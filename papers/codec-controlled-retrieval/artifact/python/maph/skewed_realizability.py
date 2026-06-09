#!/usr/bin/env python3
"""T4b: skewed codecs are graded, and the realizable non-member mass set.

Context
-------
The note docs/codec_controlled_retrieval.md proves T4 (the sharp codec-control
threshold) for BALANCED linear codecs: a single homophone subspace C describes
the whole class partition, so every class is a coset of the same C, and the
subspace-meets-coset lemma forces the non-member mass to be 0 or one common
value 1/K' on every hit class (two-valued, "sharp"). For a SKEWED codec
(variable codeword lengths, as in a genuine Huffman code) the classes are cosets
of DIFFERENT within-class subspaces, so that lemma does not apply uniformly.
Whether a genuinely GRADED regime (distinct positive masses on distinct hit
classes) can occur was left open. This script settles it by exhaustively
enumerating EVERY GF(2) subspace of GF(2)^M.

What it confirms (exhaustively, exact rationals)
------------------------------------------------
1. GRADED EXISTS. For a skewed codec there is a subspace W meeting distinct hit
   classes in DISTINCT POSITIVE proportions. Explicit witness printed: the skew
   {1,2,3,3} codec on M=4 with W = span of all four stored codewords gives
   q = (1/2, 1/4, 1/8, 1/8).
2. BALANCED STAYS SHARP. For a balanced codec, over ALL subspaces W, the hit
   classes always share one common positive mass (at most one distinct positive
   value); never graded.
3. THE FLAG FORMULA. With C_l = span of the bottom (M - l) standard basis
   vectors (a complete flag {0} = C_M < C_{M-1} < ... < C_1, dim C_l = M - l),
       q(v) = h_v * 2^( dim(W cap C_{len(v)}) - dim W ),
   h_v = [ aligned(v) in W + C_{len(v)} ] (hit indicator). Verified equal to
   brute-force intersection counts for ALL W. Because the C_l are nested,
   dim(W cap C_l) is monotone non-increasing in l, so among hit classes the
   masses are a NON-INCREASING ladder in code length.
4. FULL-SPAN PUNCHLINE. W = GF(2)^M gives q(v) = 2^(-len(v)) exactly, the codec's
   designed Kraft / codespace-share law.
5. UNIFORM UNREACHABLE. The closest reachable q to a uniform target over the skew
   codec has strictly positive total variation (1/4 for skew4), so a uniform
   non-member law over a skewed codec is provably unreachable by any W; the
   designed 2^(-len) law is reachable.

Subspace counts are checked against the Galois numbers (total subspaces of
GF(2)^M): 67 at M=4 and 2825 at M=6.

This is a research script (not part of the C++ build). The same facts are gated
in tests/v3/test_skewed_realizability.cpp, tag [skewed][realizability], which
reuses the real maph::prefix_codec via include/maph/codecs/prefix_codec.hpp.

Run
---
    python3 analysis/skewed_realizability.py

Pure Python (no numpy). Deterministic; exits non-zero if any claim fails, so it
doubles as a regression check.
"""

from __future__ import annotations

import sys
from fractions import Fraction
from itertools import combinations


# --------------------------------------------------------------------------
# GF(2)^M linear algebra over python ints. Bit i is the (1 << i) bit.
# --------------------------------------------------------------------------

def gf2_basis(vectors):
    """Reduced basis (list of ints) for the span of `vectors`, keyed by pivot."""
    basis_by_pivot = {}
    for v in vectors:
        b = v
        while b:
            piv = b.bit_length() - 1
            if piv in basis_by_pivot:
                b ^= basis_by_pivot[piv]
            else:
                break
        if b:
            basis_by_pivot[b.bit_length() - 1] = b
    return [basis_by_pivot[p] for p in sorted(basis_by_pivot, reverse=True)]


def gf2_rank(vectors):
    return len(gf2_basis(vectors))


def gf2_span(basis):
    """All 2^len(basis) XOR combinations of `basis`."""
    out = [0]
    for b in basis:
        out += [x ^ b for x in out]
    return out


def intersection_dim(W_basis, C_basis):
    """dim(W cap C) via the rank identity dim W + dim C - dim(W + C)."""
    return len(W_basis) + len(C_basis) - gf2_rank(list(W_basis) + list(C_basis))


def all_subspaces(M):
    """Yield every linear subspace of GF(2)^M as a frozenset of its points.

    Enumerated by reduced row echelon form (RREF), which is in bijection with
    subspaces. Pivots are chosen high-bit-first; for each non-pivot column to the
    right of a pivot row's pivot, the entry is a free GF(2) choice.
    """
    positions = list(range(M - 1, -1, -1))  # high bit to low bit
    yield frozenset([0])  # the zero subspace
    seen = {frozenset([0])}
    for k in range(1, M + 1):
        for pivots in combinations(positions, k):  # already high->low
            pivots = list(pivots)
            nonpivot = [p for p in positions if p not in set(pivots)]
            free_slots = [(i, c) for i, piv in enumerate(pivots)
                          for c in nonpivot if c < piv]
            nfree = len(free_slots)
            for mask in range(1 << nfree):
                rows = [1 << piv for piv in pivots]
                for bidx, (i, c) in enumerate(free_slots):
                    if mask & (1 << bidx):
                        rows[i] |= (1 << c)
                pts = frozenset(gf2_span(rows))
                if pts not in seen:
                    seen.add(pts)
                    yield pts


# --------------------------------------------------------------------------
# prefix_codec canonical assignment + class geometry (mirrors prefix_codec.hpp).
# --------------------------------------------------------------------------

def canonical_codewords(codes, M):
    """codes: list of (value, length). Returns entries with left-aligned codewords.

    Mirrors maph::prefix_codec::validate_and_assign: sort by (length, value),
    assign consecutive integers, shift left when the length grows, left-align by
    `code << (M - l)`.
    """
    kraft = sum(Fraction(1, 1 << l) for (_, l) in codes)
    assert kraft <= 1, f"Kraft violated: {kraft}"
    for (_, l) in codes:
        assert 1 <= l <= M
    out = []
    next_code = 0
    last_length = 0
    for (v, l) in sorted(codes, key=lambda vl: (vl[1], vl[0])):
        if last_length != 0 and l > last_length:
            next_code <<= (l - last_length)
        aligned = next_code << (M - l)
        out.append({"value": v, "length": l, "aligned": aligned})
        next_code += 1
        last_length = l
    return out


def within_class_subspace(length, M):
    """C_l = bottom (M - l) standard basis vectors (the within-class directions)."""
    return [1 << i for i in range(M - length)]


def class_points(aligned, length, M):
    """All points of class(v) = coset aligned + C_l."""
    return frozenset(aligned ^ x for x in gf2_span(within_class_subspace(length, M)))


# --------------------------------------------------------------------------
# The analyses.
# --------------------------------------------------------------------------

def analyze(tag, codes, M, expect_graded):
    """Enumerate ALL subspaces; verify graded-status, the flag formula, the ladder."""
    entries = canonical_codewords(codes, M)
    members = [e["value"] for e in entries]
    cps = {e["value"]: class_points(e["aligned"], e["length"], M) for e in entries}
    cbasis = {e["value"]: within_class_subspace(e["length"], M) for e in entries}
    aligned = {e["value"]: e["aligned"] for e in entries}
    length = {e["value"]: e["length"] for e in entries}

    n_sub = 0
    max_distinct_positive = 0
    formula_ok = True
    ladder_ok = True
    full_share_ok = True
    graded_witness = None

    for Wpts in all_subspaces(M):
        n_sub += 1
        W_basis = gf2_basis(list(Wpts))
        dimW = len(W_basis)
        q = {}
        for v in members:
            brute = len(cps[v] & Wpts)
            q[v] = Fraction(brute, len(Wpts))
            # Flag formula: q(v) = h_v * 2^(dim(W cap C_l) - dim W).
            hit = aligned[v] in set(gf2_span(gf2_basis(list(Wpts) + cbasis[v])))
            d = intersection_dim(W_basis, cbasis[v])
            pred = Fraction(1 << d, 1 << dimW) if hit else Fraction(0)
            if q[v] != pred:
                formula_ok = False
        # Non-increasing ladder among hit classes: len smaller => mass >= .
        hits = [v for v in members if q[v] > 0]
        for v in hits:
            for w in hits:
                if length[v] <= length[w] and not (q[v] >= q[w]):
                    ladder_ok = False
        positives = sorted({q[v] for v in members if q[v] > 0})
        max_distinct_positive = max(max_distinct_positive, len(positives))
        # Record the smallest-dim graded witness for printing.
        if len(positives) >= 2 and graded_witness is None and dimW == len(members) - 1:
            graded_witness = (W_basis, dict(q))

    # Full-space punchline: q(v) = 2^(-len(v)).
    full = frozenset(range(1 << M))
    for v in members:
        if Fraction(len(cps[v] & full), len(full)) != Fraction(1, 1 << length[v]):
            full_share_ok = False

    graded = max_distinct_positive >= 2
    print(f"\n=== {tag}  M={M}  codes={codes} ===")
    print(f"  subspaces enumerated: {n_sub}")
    print(f"  max distinct positive masses over all W: {max_distinct_positive}")
    print(f"  GRADED (some W has >= 2 distinct positive masses)? "
          f"{'YES' if graded else 'NO (sharp)'}  (expected: "
          f"{'GRADED' if expect_graded else 'SHARP'})")
    print(f"  flag formula q = h*2^(d-dimW) matches brute for ALL W? "
          f"{'YES' if formula_ok else 'NO'}")
    print(f"  non-increasing ladder in code length for ALL W? "
          f"{'YES' if ladder_ok else 'NO'}")
    print(f"  full-space W gives q(v) = 2^(-len)? {'YES' if full_share_ok else 'NO'}")

    ok = (graded == expect_graded) and formula_ok and ladder_ok and full_share_ok
    return ok, graded_witness, members, length, cps


def print_witness(tag, witness, members, length, cps, M):
    if witness is None:
        return
    W_basis, q = witness
    Wpts = sorted(gf2_span(W_basis))
    fmt = lambda x: format(x, "0" + str(M) + "b")
    print(f"  --- graded witness for {tag} ---")
    print(f"  dim W = {len(W_basis)}, |W| = {len(Wpts)}")
    print(f"  W basis: {[fmt(b) for b in W_basis]}")
    print(f"  W points: {[fmt(x) for x in Wpts]}")
    for v in members:
        print(f"    q(v={v}) [len {length[v]}, |class|={len(cps[v])}] = {q[v]}")


def min_tv_to_target(codes, M, target):
    """Closest reachable q (min total variation) over spans of MEMBER codewords."""
    entries = canonical_codewords(codes, M)
    members = [e["value"] for e in entries]
    cps = {e["value"]: class_points(e["aligned"], e["length"], M) for e in entries}
    vecs = [e["aligned"] for e in entries]
    best = None
    for r in range(0, len(vecs) + 1):
        for combo in combinations(range(len(vecs)), r):
            Wpts = frozenset(gf2_span(gf2_basis([vecs[i] for i in combo])))
            q = {v: Fraction(len(cps[v] & Wpts), len(Wpts)) for v in members}
            tv = sum(abs(q[v] - target[v]) for v in members) / 2
            cost = len(combo)
            if best is None or (tv, cost) < (best[0], best[1]):
                best = (tv, cost, q)
    return members, best


def main():
    all_ok = True

    # Galois subspace-count cross-check + the four headline cases.
    cases = [
        ("skew4_1233", [(0, 1), (1, 2), (2, 3), (3, 3)], 4, True),
        ("bal4_2222",  [(0, 2), (1, 2), (2, 2), (3, 2)], 4, False),
        ("skew6_huff", [(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 6)], 6, True),
        ("bal6_3s",    [(i, 3) for i in range(8)], 6, False),
    ]
    galois = {4: 67, 6: 2825}

    witnesses = []
    for tag, codes, M, expect_graded in cases:
        ok, witness, members, length, cps = analyze(tag, codes, M, expect_graded)
        # Subspace count must equal the Galois number for this M.
        n_sub = sum(1 for _ in all_subspaces(M))
        if n_sub != galois[M]:
            print(f"  !! subspace count {n_sub} != Galois {galois[M]} for M={M}")
            ok = False
        else:
            print(f"  subspace count == Galois number {galois[M]} for M={M}: YES")
        all_ok = all_ok and ok
        if witness is not None:
            witnesses.append((tag, witness, members, length, cps, M))

    print("\n================ GRADED WITNESSES ================")
    for tag, witness, members, length, cps, M in witnesses:
        print_witness(tag, witness, members, length, cps, M)

    print("\n================ REALIZABILITY OF TARGETS (skew4) ================")
    skew = [(0, 1), (1, 2), (2, 3), (3, 3)]
    # Designed Kraft / codespace-share target = 2^(-len) per member.
    designed = {e["value"]: Fraction(1, 1 << e["length"])
                for e in canonical_codewords(skew, 4)}
    members, (tv_d, cost_d, q_d) = min_tv_to_target(skew, 4, designed)
    print(f"  designed 2^(-len) target {[str(designed[v]) for v in members]}:")
    print(f"    closest reachable q = {[str(q_d[v]) for v in members]}  "
          f"min-TV = {tv_d}  via {cost_d} seed codeword(s)")
    designed_reachable = (tv_d == 0)
    print(f"    designed target reachable exactly? {'YES' if designed_reachable else 'NO'}")

    uniform = {v: Fraction(1, len(members)) for v in members}
    _, (tv_u, cost_u, q_u) = min_tv_to_target(skew, 4, uniform)
    print(f"  uniform target {[str(uniform[v]) for v in members]}:")
    print(f"    closest reachable q = {[str(q_u[v]) for v in members]}  "
          f"min-TV = {tv_u}  via {cost_u} seed codeword(s)")
    uniform_unreachable = (tv_u > 0)
    print(f"    uniform target reachable exactly? {'YES' if not uniform_unreachable else 'NO'}"
          f"  (min-TV strictly positive => UNREACHABLE)")

    all_ok = all_ok and designed_reachable and uniform_unreachable and (tv_u == Fraction(1, 4))

    print("\n================ SUMMARY ================")
    print(f"  all claims hold: {'YES' if all_ok else 'NO'}")
    if not all_ok:
        print("  FAILURE: a claim did not hold (see above).")
        return 1
    print("  T4b settled: skewed codecs are graded; realizable masses are a "
          "non-increasing ladder in code length; uniform is unreachable; the "
          "designed 2^(-len) law is reachable and equals full-span control.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
