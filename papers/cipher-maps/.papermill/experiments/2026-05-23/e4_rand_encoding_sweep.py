#!/usr/bin/env python3
"""E4: randomized-encoding defense validation across K(x) sweep.

Wraps bernoulli Experiment 15 (randomized encoding) with:
- M_bits sweep for Huffman codec ({4, 5, 6, 7, 8}) which implicitly
  varies K(x) via codespace class size 2^(M - l_v) per value
- Dense codec at saturating M (boundary case H3: K(x) cannot grow)
- Both canonical and random encoding modes for direct comparison
- t in {2, 3, 4}
- 5 replicates per cell

Three sub-hypotheses verified:
- H1 (pattern-coincidence under randomized): member coincidence
  decays as ~1/K(x)^(t-1) on average, within sampling error
- H2 (decode-coincidence under randomized): unchanged from
  canonical (invariant under K)
- H3 (Dense saturation): no defense benefit when K(x) cannot
  increase (codespace already saturated)

Run from cipher-maps paper root:

    python3 .papermill/experiments/2026-05-23/e4_rand_encoding_sweep.py \\
        --out .papermill/experiments/2026-05-23/e4 \\
        --n-replicates 5
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import math
import random
import sys
import time
from dataclasses import dataclass, asdict
from pathlib import Path

BERNOULLI_SRC = Path.home() / "github/bernoulli/src/bernoulli/src"
BERNOULLI_EXP = Path.home() / "github/bernoulli/src/bernoulli/experiments"
sys.path.insert(0, str(BERNOULLI_SRC))


def _load_exp15():
    spec = importlib.util.spec_from_file_location(
        "exp15", str(BERNOULLI_EXP / "15_randomized_encoding.py")
    )
    if spec is None or spec.loader is None:
        raise RuntimeError("could not load Experiment 15")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["exp15"] = mod
    spec.loader.exec_module(mod)
    return mod


exp15 = _load_exp15()


# Sweep configuration.
# Each entry is (codec_label, m_bits) and the codec will be built from f_distribution.
# Huffman variants cover the K(x) sweep via M_bits (class size = 2^(M - l_v)).
# Dense(M=3) saturates at K(x) = 1 (boundary H3).
HUFFMAN_M_BITS = [4, 5, 6, 7, 8]
DENSE_CONFIGS = [("Dense(M=3)", 3)]
T_VALUES = [2, 3, 4]
ENCODINGS = ["canonical", "random"]


@dataclass
class ReplicatedCell:
    codec_label: str
    encoding: str
    t: int
    m_bits: int
    n_replicates: int
    # decode-coincidence (public codec): TPR, FPR
    decode_tpr_mean: float
    decode_tpr_std: float
    decode_fpr_mean: float
    decode_fpr_std: float
    # pattern-coincidence (private codec): TPR, FPR
    pattern_tpr_mean: float
    pattern_tpr_std: float
    pattern_fpr_mean: float
    pattern_fpr_std: float
    # Predictions
    pred_decode_tpr: float
    pred_decode_fpr: float
    pred_pattern_tpr: float
    pred_pattern_fpr: float
    # Gaps (empirical mean - prediction)
    gap_decode_tpr: float
    gap_decode_fpr: float
    gap_pattern_tpr: float
    gap_pattern_fpr: float


def make_codec(label: str, m_bits: int, p_f) -> object:
    if label.startswith("Huffman"):
        return exp15.PrefixCodec.from_frequencies(p_f, m_bits=m_bits)
    if label.startswith("Dense"):
        return exp15.DenseCodec(exp15.VALUES, m_bits=m_bits)
    raise ValueError(f"unknown codec {label!r}")


def run_cell_replicated(
    codec_label: str,
    m_bits: int,
    encoding: str,
    t: int,
    p_f,
    n_keys: int,
    n_universe_extra: int,
    n_member_eval: int,
    n_nonmember_eval: int,
    n_replicates: int,
    base_seed: int,
) -> ReplicatedCell:
    codec = make_codec(codec_label, m_bits, p_f)
    decode_tprs = []
    decode_fprs = []
    pattern_tprs = []
    pattern_fprs = []
    pred_decode_tpr = pred_decode_fpr = pred_pattern_tpr = pred_pattern_fpr = 0.0

    for rep in range(n_replicates):
        cell_rng = random.Random(base_seed + rep)
        cell = exp15.evaluate_one(
            codec=codec,
            codec_label=codec_label,
            p_f=p_f,
            encoding=encoding,
            t=t,
            n_keys=n_keys,
            n_universe_extra=n_universe_extra,
            n_member_eval=n_member_eval,
            n_nonmember_eval=n_nonmember_eval,
            m_bits=m_bits,
            rng=cell_rng,
        )
        decode_tprs.append(cell.emp_decode_tpr)
        decode_fprs.append(cell.emp_decode_fpr)
        pattern_tprs.append(cell.emp_pattern_tpr)
        pattern_fprs.append(cell.emp_pattern_fpr)
        # Predictions are deterministic given codec, encoding, t
        pred_decode_tpr = cell.pred_decode_tpr
        pred_decode_fpr = cell.pred_decode_fpr
        pred_pattern_tpr = cell.pred_pattern_tpr
        pred_pattern_fpr = cell.pred_pattern_fpr

    def stats(xs):
        m = sum(xs) / len(xs)
        v = sum((x - m) ** 2 for x in xs) / max(1, len(xs) - 1) if len(xs) > 1 else 0.0
        return m, math.sqrt(v)

    dtpr_m, dtpr_s = stats(decode_tprs)
    dfpr_m, dfpr_s = stats(decode_fprs)
    ptpr_m, ptpr_s = stats(pattern_tprs)
    pfpr_m, pfpr_s = stats(pattern_fprs)

    return ReplicatedCell(
        codec_label=codec_label,
        encoding=encoding,
        t=t,
        m_bits=m_bits,
        n_replicates=n_replicates,
        decode_tpr_mean=dtpr_m,
        decode_tpr_std=dtpr_s,
        decode_fpr_mean=dfpr_m,
        decode_fpr_std=dfpr_s,
        pattern_tpr_mean=ptpr_m,
        pattern_tpr_std=ptpr_s,
        pattern_fpr_mean=pfpr_m,
        pattern_fpr_std=pfpr_s,
        pred_decode_tpr=pred_decode_tpr,
        pred_decode_fpr=pred_decode_fpr,
        pred_pattern_tpr=pred_pattern_tpr,
        pred_pattern_fpr=pred_pattern_fpr,
        gap_decode_tpr=dtpr_m - pred_decode_tpr,
        gap_decode_fpr=dfpr_m - pred_decode_fpr,
        gap_pattern_tpr=ptpr_m - pred_pattern_tpr,
        gap_pattern_fpr=pfpr_m - pred_pattern_fpr,
    )


def write_csv(rows: list[ReplicatedCell], path: Path) -> None:
    if not rows:
        return
    fieldnames = list(asdict(rows[0]).keys())
    with path.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow(asdict(r))


def write_summary(rows: list[ReplicatedCell], path: Path) -> None:
    # Verify sub-hypotheses
    # H1: under randomized encoding, pattern TPR decreases as K (M_bits) grows
    h1_evidence: list[str] = []
    huffman_random = sorted(
        [r for r in rows if r.codec_label.startswith("Huffman") and r.encoding == "random"],
        key=lambda r: (r.t, r.m_bits),
    )
    for t in T_VALUES:
        tprs = [(r.m_bits, r.pattern_tpr_mean) for r in huffman_random if r.t == t]
        tprs.sort()
        if len(tprs) >= 2:
            monotone = all(tprs[i][1] >= tprs[i + 1][1] for i in range(len(tprs) - 1))
            h1_evidence.append(
                f"  t={t}: Huffman pattern TPR vs M_bits = "
                f"{', '.join(f'{m}->{p:.4f}' for m, p in tprs)} "
                f"(monotone decreasing: {monotone})"
            )

    # H2: decode TPR/FPR for randomized matches canonical at same (codec, t)
    h2_evidence: list[str] = []
    by_key: dict = {}
    for r in rows:
        key = (r.codec_label, r.m_bits, r.t)
        by_key.setdefault(key, {})[r.encoding] = r
    h2_decode_gaps: list[float] = []
    for key, pair in by_key.items():
        if "canonical" in pair and "random" in pair:
            gap_tpr = abs(pair["canonical"].decode_tpr_mean - pair["random"].decode_tpr_mean)
            gap_fpr = abs(pair["canonical"].decode_fpr_mean - pair["random"].decode_fpr_mean)
            h2_decode_gaps.append(max(gap_tpr, gap_fpr))
    h2_max_gap = max(h2_decode_gaps) if h2_decode_gaps else 0.0
    h2_pass = h2_max_gap < 0.05  # sampling-noise scale at n=2000

    # H3: Dense canonical vs random pattern TPR (should be ~equal, no defense)
    h3_evidence: list[str] = []
    dense_pairs = [
        (key, pair) for key, pair in by_key.items()
        if key[0].startswith("Dense") and "canonical" in pair and "random" in pair
    ]
    h3_max_gap = 0.0
    for key, pair in dense_pairs:
        gap = abs(pair["canonical"].pattern_tpr_mean - pair["random"].pattern_tpr_mean)
        h3_evidence.append(
            f"  Dense {key[0]} M={key[1]} t={key[2]}: "
            f"canonical pattern_tpr={pair['canonical'].pattern_tpr_mean:.4f}, "
            f"random pattern_tpr={pair['random'].pattern_tpr_mean:.4f}, gap={gap:.4f}"
        )
        h3_max_gap = max(h3_max_gap, gap)
    h3_pass = h3_max_gap < 0.05

    lines = [
        "# E4 Randomized-encoding defense validation (K sweep)",
        "",
        f"Run: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        f"Replicates per cell: {rows[0].n_replicates if rows else 'N/A'}",
        f"Total cells: {len(rows)}",
        "",
        "## Sub-hypothesis verification",
        "",
        "### H1: under randomized encoding, pattern-coincidence TPR decreases with K",
        "",
    ]
    lines.extend(h1_evidence)
    lines += [
        "",
        "### H2: decode-coincidence accuracy is invariant under K",
        "",
        f"Max gap between canonical and random decode rates across all (codec, M, t) cells: {h2_max_gap:.4f}",
        f"H2 verdict (gap < 0.05 within sampling noise): {'PASS' if h2_pass else 'FAIL'}",
        "",
        "### H3: Dense saturation (K=1 forced)",
        "",
    ]
    lines.extend(h3_evidence)
    lines += [
        "",
        f"Max canonical-vs-random pattern TPR gap on Dense: {h3_max_gap:.4f}",
        f"H3 verdict (gap < 0.05): {'PASS' if h3_pass else 'FAIL'}",
        "",
        "## Per-cell results (pattern-coincidence focus)",
        "",
        "| codec | M | enc | t | pattern TPR mean (std) | pattern FPR mean (std) | pred TPR | pred FPR |",
        "|---|--:|---|--:|---|---|--:|--:|",
    ]
    for r in sorted(rows, key=lambda x: (x.codec_label, x.m_bits, x.encoding, x.t)):
        lines.append(
            f"| {r.codec_label} | {r.m_bits} | {r.encoding} | {r.t} | "
            f"{r.pattern_tpr_mean:.4f} ({r.pattern_tpr_std:.4f}) | "
            f"{r.pattern_fpr_mean:.4f} ({r.pattern_fpr_std:.4f}) | "
            f"{r.pred_pattern_tpr:.4f} | {r.pred_pattern_fpr:.4f} |"
        )
    lines += [
        "",
        "## Inclusion decision (per design.md)",
        "",
        f"- H1 monotone decrease in K: see per-t evidence above",
        f"- H2 PASS: {h2_pass}",
        f"- H3 PASS: {h3_pass}",
        "",
        "Strong include if H1 + H2 + H3 all hold: new section 10.7 'Randomized-Encoding Defense at Scale' with two figures",
        "Partial include if H1 holds but H2 or H3 fails: H1 part with caveat",
        "Cut and re-investigate if H1 fails: revisit Proposition 8.2",
    ]
    path.write_text("\n".join(lines) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--n-replicates", type=int, default=5)
    parser.add_argument("--n-keys", type=int, default=1000)
    parser.add_argument("--n-universe-extra", type=int, default=4000)
    parser.add_argument("--n-member-eval", type=int, default=2000)
    parser.add_argument("--n-nonmember-eval", type=int, default=2000)
    parser.add_argument("--seed", type=int, default=2026)
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=True)

    p_f = exp15.f_distribution()

    configs: list[tuple[str, int]] = []
    for m_bits in HUFFMAN_M_BITS:
        configs.append((f"Huffman(M={m_bits})", m_bits))
    configs.extend(DENSE_CONFIGS)

    rows: list[ReplicatedCell] = []
    for codec_label, m_bits in configs:
        for encoding in ENCODINGS:
            for t in T_VALUES:
                t0 = time.time()
                print(
                    f"cell {codec_label} enc={encoding} t={t}...",
                    file=sys.stderr,
                    flush=True,
                )
                cell = run_cell_replicated(
                    codec_label=codec_label,
                    m_bits=m_bits,
                    encoding=encoding,
                    t=t,
                    p_f=p_f,
                    n_keys=args.n_keys,
                    n_universe_extra=args.n_universe_extra,
                    n_member_eval=args.n_member_eval,
                    n_nonmember_eval=args.n_nonmember_eval,
                    n_replicates=args.n_replicates,
                    base_seed=args.seed + hash((codec_label, encoding, t)) % (1 << 20),
                )
                dt = time.time() - t0
                print(
                    f"  pattern_tpr={cell.pattern_tpr_mean:.4f} "
                    f"pattern_fpr={cell.pattern_fpr_mean:.4f} "
                    f"decode_tpr={cell.decode_tpr_mean:.4f} ({dt:.1f}s)",
                    file=sys.stderr,
                )
                rows.append(cell)

    write_csv(rows, args.out / "results.csv")
    write_summary(rows, args.out / "summary.md")
    print(f"wrote {args.out}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
