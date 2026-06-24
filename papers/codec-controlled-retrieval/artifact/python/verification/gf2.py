"""Minimal GF(2)^M toolkit + the {1,2,3,3} codec, shared by both verifications."""
from fractions import Fraction
from itertools import combinations

M = 4
# canonical left-aligned codewords (top bits set, low bits zero), M-bit ints, bit M-1 = MSB
CODE = {'A': (1, 0b0000), 'B': (2, 0b1000), 'C': (3, 0b1100), 'D': (3, 0b1110)}
ORDER = ['A', 'B', 'C', 'D']  # by length ascending for prefix-free decode

def mask_top(l):
    if l >= M:
        return (1 << M) - 1
    return (((1 << M) - 1) >> (M - l)) << (M - l)

def decode(x):
    for v in ORDER:               # shortest prefix wins (prefix-free)
        l, cw = CODE[v]
        if (x & mask_top(l)) == (cw & mask_top(l)):
            return v
    return None

def gf2_basis(vecs):
    piv = {}
    for b in vecs:
        for p in sorted(piv, reverse=True):
            if (b >> p) & 1:
                b ^= piv[p]
        if b:
            piv[b.bit_length() - 1] = b
    return [piv[p] for p in sorted(piv, reverse=True)]

def gf2_span(basis):
    out = [0]
    for b in basis:
        out += [x ^ b for x in out]
    return out

def gf2_rank(vecs):
    return len(gf2_basis(vecs))

def gf2_in_span(v, basis):
    for b in basis:
        if v == 0:
            break
        p = b.bit_length() - 1
        if (v >> p) & 1:
            v ^= b
    return v == 0

def class_hits_and_W(stored):
    """(hits dict over A,B,C,D ; |W|) by enumerating W = span(stored) and decoding."""
    span = gf2_span(gf2_basis(list(stored)))
    hits = {v: 0 for v in ORDER}
    for x in span:
        hits[decode(x)] += 1
    return hits, len(span)

def law(stored):
    hits, W = class_hits_and_W(stored)
    return tuple(Fraction(hits[v], W) for v in ORDER)

def all_subspaces():
    """All distinct subspaces of GF(2)^M, as frozensets of points."""
    univ = list(range(1 << M))
    seen = set()
    subs = []
    for k in range(0, M + 1):
        for combo in combinations(univ, k):
            s = frozenset(gf2_span(gf2_basis(list(combo))))
            if s not in seen:
                seen.add(s)
                subs.append(s)
    return subs
