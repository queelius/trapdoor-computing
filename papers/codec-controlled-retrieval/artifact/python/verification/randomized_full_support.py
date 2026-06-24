"""Verification for the corrected randomized-encoding boundary (thm:randenc).

The skewed randomized-encoding invariance is FALSE in general. Two boundary
claims are checked here in exact rational arithmetic:

  (A) FULL SUPPORT is sufficient (for a complete / Kraft-tight codec): every
      within-class redraw of a full-support store reproduces the designed Kraft
      law q(v) = 2^-len(v). Proven in the note by sibling contraction; checked
      here exhaustively across several complete codes.

  (B) SATURATION is NOT sufficient: a store can have every per-length projection
      pi_l(W) full (saturated) without full support, yet have redraws that change
      the law. Witness: codec {2,2,2,3,3}, store {B,C,E}.

This is the second correction in this lemma's history: the original claim
(skewed invariance in general) was refuted by {A,A,B}; an intermediate patch
(saturation sufficient) is refuted here by {B,C,E}. Both share one blind spot:
the verification behind each sampled only the regime where the claim happens to
hold (full support, which is saturated). Full support is the defensible boundary.
"""
from fractions import Fraction
from itertools import product


def mask(l, M):
    return (((1 << M) - 1) >> (M - l)) << (M - l) if l < M else (1 << M) - 1


def basis(vs):
    piv = {}
    for b in vs:
        for p in sorted(piv, reverse=True):
            if (b >> p) & 1:
                b ^= piv[p]
        if b:
            piv[b.bit_length() - 1] = b
    return [piv[p] for p in sorted(piv, reverse=True)]


def span(B):
    out = [0]
    for b in B:
        out += [x ^ b for x in out]
    return out


def gf2_rank(vs):
    return len(basis(list(vs)))


def assign_canonical(lengths, M):
    """Canonical left-aligned prefix-free assignment (sort by length, assign
    consecutive integers, shift to the top bits). Returns idx -> (len, pattern)."""
    order = sorted(range(len(lengths)), key=lambda i: (lengths[i], i))
    code, nxt, last = {}, 0, 0
    for idx in order:
        l = lengths[idx]
        if last and l > last:
            nxt <<= (l - last)
        code[idx] = (l, nxt << (M - l))
        nxt += 1
        last = l
    return code


def law(code, stored, M):
    order = sorted(code, key=lambda v: code[v][0])  # shortest prefix wins
    def decode(x):
        for v in order:
            l, cw = code[v]
            if (x & mask(l, M)) == (cw & mask(l, M)):
                return v
        return None
    sp = span(basis(list(stored)))
    h = {v: 0 for v in code}
    for x in sp:
        h[decode(x)] += 1
    return tuple(Fraction(h[v], len(sp)) for v in sorted(code))


def members(code, v, M):
    l, cw = code[v]
    return [cw | i for i in range(1 << (M - l))]


def proj_rank(code, stored, l, M):
    return gf2_rank([b & mask(l, M) for b in basis(list(stored))])


def saturated(code, stored, M):
    return all(proj_rank(code, stored, code[v][0], M) == code[v][0]
               for v in {vv: 0 for vv in code})


# ===== (A) FULL SUPPORT is sufficient (complete codes). =====
print("(A) FULL-SUPPORT sufficiency, exhaustive over complete (Kraft-tight) codes:")
complete_codes = [
    ([1, 2, 3, 3], 4),
    ([1, 2, 3, 4, 4], 4),
    ([2, 2, 2, 2], 2),
    ([1, 2, 2], 2),
    ([3, 3, 3, 3, 3, 3, 3, 3], 3),
    ([1, 3, 3, 3, 3], 3),
    ([2, 2, 3, 3, 3, 3], 4),
    ([2, 2, 2, 3, 3], 4),
]
all_ok = True
for lengths, M in complete_codes:
    kraft = sum(Fraction(1, 1 << l) for l in lengths)
    assert kraft == 1, f"{lengths} not Kraft-tight ({kraft})"
    code = assign_canonical(lengths, M)
    stored = list(range(len(lengths)))
    designed = tuple(Fraction(1, 1 << code[v][0]) for v in sorted(code))
    opts = [members(code, v, M) for v in stored]
    total = 1
    for o in opts:
        total *= len(o)
    bad = sum(1 for draw in product(*opts)
              if law(code, list(draw), M) != designed)
    print(f"   lengths={lengths} M={M}: {total} draws, designed-law-invariant, "
          f"breaking={bad}")
    all_ok &= (bad == 0)
assert all_ok, "full-support sufficiency FAILED"
print("   => full support is sufficient on every complete code tested.")

# ===== (B) SATURATION is NOT sufficient. =====
print("\n(B) SATURATION refutation, codec {2,2,2,3,3}, store {B,C,E}:")
M = 4
code = assign_canonical([2, 2, 2, 3, 3], M)   # A,B,C len2 ; D,E len3
names = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E"}
store = [1, 2, 4]                              # B, C, E (A, D unstored)
canon = [code[v][1] for v in store]
q0 = law(code, canon, M)
print("   canonical patterns:", {names[v]: f"{code[v][1]:04b}" for v in store})
print("   saturated?", saturated(code, canon, M),
      " full support?", len(store) == 5)
print("   canonical law:", tuple(str(x) for x in q0))
laws = {}
for b, c, e in product(members(code, 1, M), members(code, 2, M), members(code, 4, M)):
    laws.setdefault(law(code, [b, c, e], M), 0)
    laws[law(code, [b, c, e], M)] += 1
total = sum(laws.values())
breaking = total - laws.get(q0, 0)
print(f"   distinct laws over all {total} draws: {len(laws)}; breaking: {breaking}")
qb = law(code, [code[1][1], 0b1010, code[4][1]], M)  # C -> 1010
print("   draw C->1010 gives:", tuple(str(x) for x in qb),
      "(D collapses)" if qb != q0 else "")
assert saturated(code, canon, M) and breaking > 0, "saturation refutation FAILED"
print("   => saturated yet not invariant: SATURATION IS NOT SUFFICIENT.")

print("\nPASS: full support sufficient (complete codes); saturation not sufficient.")
