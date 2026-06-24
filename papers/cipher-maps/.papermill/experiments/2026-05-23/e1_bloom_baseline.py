#!/usr/bin/env python3
"""E1: Bloom-filter baseline at matched FPR.

Question: at matched per-document false-positive rate (p_T = epsilon),
how does cipher set space cost compare to an optimal Bloom filter?

Setup: per-document membership test on the 20 Newsgroups corpus.
Sweep over corpus size m and target FPR epsilon. For each cell, build
both a cipher set (PHF backed via phobic, slot-tagged with cipher
Boolean True/False/Noise region) and an optimal Bloom filter (k hash
functions, m_bits chosen for target epsilon). Measure space three ways
(theoretical info bound, practical theoretical, serialized bytes) and
verify empirical FPR with held-out queries.

This script is self-contained: it depends only on phobic (PHF
backend), scikit-learn (20NG corpus), and Python stdlib. The cipher
set construction is hand-rolled here rather than going through the
trapdoor_maps library to keep the script portable across library API
changes.

Run from cipher-maps paper directory:

    python -m .papermill.experiments.2026-05-23.e1_bloom_baseline \\
        --out .papermill/experiments/2026-05-23/e1

Or directly:

    python .papermill/experiments/2026-05-23/e1_bloom_baseline.py \\
        --out .papermill/experiments/2026-05-23/e1
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import math
import os
import random
import re
import sys
import time
from collections.abc import Iterable
from dataclasses import dataclass, asdict
from pathlib import Path


_TOKEN_RE = re.compile(r"[a-zA-Z]+")


def tokenize(doc: str) -> set[str]:
    return {tok.lower() for tok in _TOKEN_RE.findall(doc)}


def load_corpus(limit: int | None = None) -> list[set[str]]:
    """Load 20 Newsgroups training split as a list of token sets."""
    from sklearn.datasets import fetch_20newsgroups

    data = fetch_20newsgroups(
        subset="train",
        remove=("headers", "footers", "quotes"),
    )
    docs = [tokenize(d) for d in data.data]
    docs = [d for d in docs if len(d) > 0]
    if limit is not None:
        docs = docs[:limit]
    return docs


# ----------------------------------------------------------------------
# Bloom filter (hand-rolled, optimal k for given epsilon and n)
# ----------------------------------------------------------------------


class BloomFilter:
    """Optimal Bloom filter for n elements at target false-positive rate epsilon.

    Uses SHA-256 truncated to compute k independent hash functions via
    double hashing. Size m_bits chosen as ceil(-n * ln(eps) / (ln 2)^2).
    Number of hash functions k chosen as ceil((m / n) * ln 2).
    """

    def __init__(self, n: int, eps: float) -> None:
        if n <= 0 or not (0 < eps < 1):
            raise ValueError(f"invalid bloom params: n={n}, eps={eps}")
        self.n = n
        self.eps = eps
        ln2 = math.log(2.0)
        self.m_bits = max(1, math.ceil(-n * math.log(eps) / (ln2 * ln2)))
        self.k = max(1, round((self.m_bits / n) * ln2))
        self.bits = bytearray((self.m_bits + 7) // 8)

    def _hashes(self, key: bytes) -> Iterable[int]:
        h = hashlib.sha256(key).digest()
        # Split into two 64-bit halves for double-hashing scheme of Kirsch and Mitzenmacher
        h1 = int.from_bytes(h[:8], "big")
        h2 = int.from_bytes(h[8:16], "big")
        for i in range(self.k):
            yield (h1 + i * h2) % self.m_bits

    def add(self, key: bytes) -> None:
        for idx in self._hashes(key):
            self.bits[idx >> 3] |= 1 << (idx & 7)

    def contains(self, key: bytes) -> bool:
        for idx in self._hashes(key):
            if not (self.bits[idx >> 3] >> (idx & 7)) & 1:
                return False
        return True

    def bits_per_element_theoretical(self) -> float:
        """Optimal Bloom: 1.44 * log2(1/eps) bits per element."""
        return 1.4427 * math.log2(1.0 / self.eps)

    def bits_per_element_actual(self) -> float:
        """Built Bloom: actual m_bits / n."""
        return self.m_bits / self.n

    def serialized_bytes(self) -> int:
        """Bits array plus a small header (n, m_bits, k as varints)."""
        return len(self.bits) + 16


# ----------------------------------------------------------------------
# Cipher set: PHF + slot storage with cipher Boolean partition
# ----------------------------------------------------------------------


@dataclass
class CipherSetSpec:
    """Cipher set parameters.

    n_bits is the slot fingerprint width.  Target FPR is 1 / 2^n_bits.
    """
    n_bits: int
    target_fpr: float


def make_cipher_spec(eps: float) -> CipherSetSpec:
    """Choose slot fingerprint width so target FPR <= eps.

    n_bits chosen as ceil(log_2(1/eps)); this gives FPR = 1/2^n_bits.
    """
    n_bits = max(1, math.ceil(math.log2(1.0 / eps)))
    return CipherSetSpec(n_bits=n_bits, target_fpr=2.0 ** (-n_bits))


def _fingerprint(key: bytes, n_bits: int, salt: int) -> int:
    """Deterministic n_bits fingerprint of key, salted to decorrelate from PHF hashes.

    SHA-256 truncated to n_bits, salted with the cipher set's seed.
    """
    h = hashlib.sha256(salt.to_bytes(8, "big") + key).digest()
    mask = (1 << n_bits) - 1
    return int.from_bytes(h[:8], "big") & mask


class CipherSet:
    """PHF-backed cipher set membership test (perfect hash filter construction).

    For each member m, store the fingerprint h(m) at slot PHF(m).
    For non-member slot positions, store a random n_bits fingerprint.
    Membership test for query q: compute h(q) and slot[PHF(q)]; member iff equal.

    The fingerprint salt is independent of the PHF seed (so a query that
    collides with a member's PHF position rarely also collides on
    fingerprint).  FPR = 1 / 2^n_bits asymptotically.
    """

    def __init__(self, members: Iterable[str], spec: CipherSetSpec, seed: int = 0) -> None:
        self.spec = spec
        self.members = list(members)
        self.n = len(self.members)
        self.rng = random.Random(seed)
        self.fp_salt = self.rng.randrange(2**63)
        self._build_phf()
        self._fill_slots()

    def _build_phf(self) -> None:
        try:
            import phobic
        except ImportError:
            raise RuntimeError(
                "E1 requires phobic. Install with: pip install phobic"
            )
        keys = [m.encode("utf-8") for m in self.members]
        last_err: Exception | None = None
        for lf in (0.95, 0.90, 0.80, 0.70, 0.50):
            try:
                self.phf = phobic.build(
                    keys, load_factor=lf, seed=self.rng.randrange(2**32)
                )
                break
            except RuntimeError as e:
                last_err = e
                continue
        else:
            raise RuntimeError(f"PHF build failed at all load factors: {last_err}")
        self.n_slots = self.phf.range_size
        self.phf_bits_per_key = self.phf.bits_per_key

    def _fill_slots(self) -> None:
        n_bits = self.spec.n_bits
        slot_width_bytes = (n_bits + 7) // 8
        self.slot_width_bytes = slot_width_bytes
        self.slots = bytearray(self.n_slots * slot_width_bytes)

        # Members: store their fingerprint at PHF position
        member_positions: set[int] = set()
        keys_bytes = [m.encode("utf-8") for m in self.members]
        positions = self.phf.lookup(keys_bytes)
        for key, pos in zip(keys_bytes, positions, strict=True):
            member_positions.add(pos)
            fp = _fingerprint(key, n_bits, self.fp_salt)
            self._write_slot(pos, fp)
        # Non-member slots: fill with random n_bits value
        slot_max = 1 << n_bits
        for pos in range(self.n_slots):
            if pos in member_positions:
                continue
            self._write_slot(pos, self.rng.randrange(slot_max))

    def _write_slot(self, pos: int, value: int) -> None:
        off = pos * self.slot_width_bytes
        for i in range(self.slot_width_bytes):
            self.slots[off + i] = (value >> (8 * (self.slot_width_bytes - 1 - i))) & 0xFF

    def _read_slot(self, pos: int) -> int:
        off = pos * self.slot_width_bytes
        v = 0
        for i in range(self.slot_width_bytes):
            v = (v << 8) | self.slots[off + i]
        return v

    def contains(self, key: str) -> bool:
        """Membership test: fingerprint of query matches stored slot value."""
        kb = key.encode("utf-8")
        pos = self.phf.lookup([kb])[0]
        stored = self._read_slot(pos)
        expected = _fingerprint(kb, self.spec.n_bits, self.fp_salt)
        return stored == expected

    def bits_per_element_practical(self) -> float:
        """Practical: PHF bits/key + n_bits per element (slot fingerprint storage)."""
        return self.phf_bits_per_key + self.spec.n_bits

    def bits_per_element_theoretical(self) -> float:
        """Theoretical lower bound: PHF bits/key + log_2(1/FPR) = PHF bits + n_bits.

        For a perfect hash filter, theoretical and practical coincide;
        the only slack is in the PHF bits/key constant (RecSplit gives
        ~1.8 bits/key asymptotically, plus a per-bucket constant).
        """
        return self.phf_bits_per_key + self.spec.n_bits

    def serialized_bytes(self) -> int:
        """Slot array + PHF backing structure (theoretical)."""
        return len(self.slots) + math.ceil(self.phf_bits_per_key * self.n / 8) + 32


# ----------------------------------------------------------------------
# Experiment driver
# ----------------------------------------------------------------------


@dataclass
class CellResult:
    m: int
    eps: float
    n_docs: int
    mean_vocab_size: float
    bloom_bits_per_elem_theoretical: float
    bloom_bits_per_elem_actual: float
    bloom_serialized_bits_per_elem: float
    bloom_empirical_fpr: float
    cipher_bits_per_elem_theoretical: float
    cipher_bits_per_elem_practical: float
    cipher_serialized_bits_per_elem: float
    cipher_empirical_fpr: float
    ratio_practical: float  # cipher_practical / bloom_actual
    ratio_theoretical: float  # cipher_theoretical / bloom_theoretical
    ratio_serialized: float  # cipher_serialized / bloom_serialized
    cipher_n_bits: int


def held_out_queries(docs: list[set[str]], n_queries: int, rng: random.Random) -> list[str]:
    """Generate query strings unlikely to be in any document vocabulary."""
    out = []
    for _ in range(n_queries):
        s = "".join(rng.choices("abcdefghijklmnopqrstuvwxyz", k=12))
        out.append(s)
    return out


def evaluate_fpr(test_fn, queries: list[str]) -> float:
    """Fraction of queries that test_fn predicts positive."""
    n = len(queries)
    pos = sum(1 for q in queries if test_fn(q))
    return pos / n if n > 0 else 0.0


def run_cell(docs: list[set[str]], eps: float, n_queries: int, seed: int) -> CellResult:
    """Build cipher set and Bloom filter per doc, average across docs."""
    rng = random.Random(seed)
    spec = make_cipher_spec(eps)
    queries = held_out_queries(docs, n_queries, rng)

    bloom_bits_actual = 0.0
    bloom_bits_serial = 0.0
    bloom_fpr = 0.0
    cipher_bits_practical = 0.0
    cipher_bits_serial = 0.0
    cipher_fpr = 0.0
    n_with_vocab = 0
    sum_vocab = 0

    for i, vocab in enumerate(docs):
        n_vocab = len(vocab)
        if n_vocab == 0:
            continue
        sum_vocab += n_vocab
        n_with_vocab += 1

        # Bloom
        bloom = BloomFilter(n=n_vocab, eps=eps)
        for tok in vocab:
            bloom.add(tok.encode("utf-8"))
        bloom_bits_actual += bloom.bits_per_element_actual()
        bloom_bits_serial += 8 * bloom.serialized_bytes() / n_vocab
        # filter queries to those not in vocab to test FPR
        fp_queries = [q for q in queries if q not in vocab]
        if fp_queries:
            bloom_fpr += evaluate_fpr(lambda q: bloom.contains(q.encode("utf-8")), fp_queries)

        # Cipher set
        try:
            cs = CipherSet(vocab, spec, seed=rng.randrange(2**32))
        except RuntimeError as e:
            print(f"cipher set build failed (doc {i}, vocab={n_vocab}): {e}", file=sys.stderr)
            raise
        cipher_bits_practical += cs.bits_per_element_practical()
        cipher_bits_serial += 8 * cs.serialized_bytes() / n_vocab
        if fp_queries:
            cipher_fpr += evaluate_fpr(cs.contains, fp_queries)

    n_with_vocab = max(1, n_with_vocab)
    bloom_bits_actual /= n_with_vocab
    bloom_bits_serial /= n_with_vocab
    bloom_fpr /= n_with_vocab
    cipher_bits_practical /= n_with_vocab
    cipher_bits_serial /= n_with_vocab
    cipher_fpr /= n_with_vocab
    mean_vocab = sum_vocab / n_with_vocab

    bloom_bits_theoretical = 1.4427 * math.log2(1.0 / eps)
    # Cipher set (PHF filter) theoretical: PHF asymptotic bits/key + n_bits fingerprint
    # phobic RecSplit asymptotic is ~1.8 bits/key; n_bits = ceil(log_2(1/eps))
    cipher_bits_theoretical = 1.8 + spec.n_bits

    return CellResult(
        m=len(docs),
        eps=eps,
        n_docs=n_with_vocab,
        mean_vocab_size=mean_vocab,
        bloom_bits_per_elem_theoretical=bloom_bits_theoretical,
        bloom_bits_per_elem_actual=bloom_bits_actual,
        bloom_serialized_bits_per_elem=bloom_bits_serial,
        bloom_empirical_fpr=bloom_fpr,
        cipher_bits_per_elem_theoretical=cipher_bits_theoretical,
        cipher_bits_per_elem_practical=cipher_bits_practical,
        cipher_serialized_bits_per_elem=cipher_bits_serial,
        cipher_empirical_fpr=cipher_fpr,
        ratio_practical=cipher_bits_practical / bloom_bits_actual,
        ratio_theoretical=cipher_bits_theoretical / bloom_bits_theoretical,
        ratio_serialized=cipher_bits_serial / bloom_bits_serial,
        cipher_n_bits=spec.n_bits,
    )


def write_csv(rows: list[CellResult], path: Path) -> None:
    if not rows:
        return
    fieldnames = list(asdict(rows[0]).keys())
    with path.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow(asdict(r))


def write_summary(rows: list[CellResult], path: Path) -> None:
    lines = [
        "# E1 Bloom-filter baseline at matched FPR",
        "",
        f"Run: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        "",
        "## Headline numbers",
        "",
        "| m    | eps  | mean vocab | Bloom bits/elem | Cipher bits/elem | Ratio (cipher/bloom) | Bloom FPR | Cipher FPR |",
        "|------|------|------------|-----------------|------------------|----------------------|-----------|------------|",
    ]
    for r in rows:
        lines.append(
            f"| {r.m:>4} | {r.eps:.2f} | {r.mean_vocab_size:>10.1f} | "
            f"{r.bloom_bits_per_elem_actual:>15.2f} | {r.cipher_bits_per_elem_practical:>16.2f} | "
            f"{r.ratio_practical:>20.2f} | {r.bloom_empirical_fpr:>9.4f} | {r.cipher_empirical_fpr:>10.4f} |"
        )
    lines += [
        "",
        "## Headline finding",
        "",
        f"Across all cells, mean practical-bits ratio (cipher/bloom): "
        f"{sum(r.ratio_practical for r in rows) / max(1, len(rows)):.2f}",
        f"Mean theoretical-bits ratio: "
        f"{sum(r.ratio_theoretical for r in rows) / max(1, len(rows)):.2f}",
        f"Mean serialized-bits ratio: "
        f"{sum(r.ratio_serialized for r in rows) / max(1, len(rows)):.2f}",
        "",
        "## Inclusion decision (per design.md)",
        "",
        "- Strong include (ratio <= 2.5): claim 'space-comparable to Bloom with totality plus frequency-hiding plus composition as additional capabilities'",
        "- Honest include (ratio 2.5 to 5): claim 'modest space overhead for trapdoor capabilities; theoretical lower bound competitive with Bloom'",
        "- Discuss-only (ratio > 5): note in section 10.5 future-work that implementation overhead is significant",
    ]
    path.write_text("\n".join(lines) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, required=True, help="Output directory")
    parser.add_argument("--m-values", nargs="*", type=int, default=[1000, 5000, 18266])
    parser.add_argument("--eps-values", nargs="*", type=float, default=[0.01, 0.05, 0.10])
    parser.add_argument("--n-queries", type=int, default=5000)
    parser.add_argument("--seed", type=int, default=42)
    args = parser.parse_args()

    args.out.mkdir(parents=True, exist_ok=True)

    print("loading 20 Newsgroups...", file=sys.stderr)
    docs_full = load_corpus()
    print(f"loaded {len(docs_full)} documents", file=sys.stderr)

    rows: list[CellResult] = []
    for m in args.m_values:
        docs = docs_full[:m]
        for eps in args.eps_values:
            t0 = time.time()
            print(f"cell m={m}, eps={eps}...", file=sys.stderr, flush=True)
            result = run_cell(
                docs=docs,
                eps=eps,
                n_queries=args.n_queries,
                seed=args.seed + m + int(eps * 1000),
            )
            dt = time.time() - t0
            print(
                f"  ratio_practical={result.ratio_practical:.2f} "
                f"bloom_fpr={result.bloom_empirical_fpr:.4f} "
                f"cipher_fpr={result.cipher_empirical_fpr:.4f} "
                f"({dt:.1f}s)",
                file=sys.stderr,
            )
            rows.append(result)

    write_csv(rows, args.out / "results.csv")
    write_summary(rows, args.out / "summary.md")
    print(f"wrote {args.out / 'results.csv'} and {args.out / 'summary.md'}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
