"""ITEM 1: complete characterization of the realizable non-member-mass set."""
from fractions import Fraction
from itertools import product
from gf2 import CODE, ORDER, M, mask_top, all_subspaces

def q_of_subspace(S):
    S = list(S)
    n = len(S)
    out = {}
    for v in ORDER:
        l, cw = CODE[v]
        m = mask_top(l)
        c = sum(1 for x in S if (x & m) == (cw & m))
        out[v] = Fraction(c, n)
    return tuple(out[v] for v in ORDER)

subs = all_subspaces()
print(f"subspaces of GF(2)^{M}: {len(subs)}  (Galois number G_2(4)=67 expected)")
R = sorted(set(q_of_subspace(S) for S in subs), key=lambda q: tuple(float(x) for x in q))
print(f"realizable laws |R| = {len(R)}")

def share(v):
    return Fraction(1, 1 << CODE[v][0])

def equal_within_length(q):     # C, D both length 3
    return q[2] == q[3]
def mass_ge_share(q):           # hit => mass >= codespace share 2^-l
    return all(q[i] == 0 or q[i] >= share(ORDER[i]) for i in range(4))
def ladder(q):                  # among hit classes, shorter >= longer
    hit = [(CODE[ORDER[i]][0], q[i]) for i in range(4) if q[i] > 0]
    return all(q1 >= q2 for (l1, q1) in hit for (l2, q2) in hit if l1 <= l2)
def is_prob(q):
    return sum(q) == 1

print("\nclean NECESSARY conditions, checked over ALL realizable q in R:")
print(f"  sum to 1:                 {all(is_prob(q) for q in R)}")
print(f"  equal-mass-within-length: {all(equal_within_length(q) for q in R)}")
print(f"  mass >= codespace share:  {all(mass_ge_share(q) for q in R)}")
print(f"  ladder (shorter>=longer): {all(ladder(q) for q in R)}")
print(f"  q[A] values seen:         {sorted(set(str(q[0]) for q in R))}  (A always hit, in {{1,1/2}})")

# Ladder NECESSARY but NOT SUFFICIENT: a ladder-respecting q outside R.
bad = (Fraction(1,2), Fraction(0), Fraction(1,4), Fraction(1,8))  # C != D
print(f"\nladder-respecting test vector {tuple(str(x) for x in bad)}: "
      f"ladder={ladder(bad)} sum1={is_prob(bad)} equal_len={equal_within_length(bad)} in R? {bad in set(R)}")

# Are the CLEAN conditions (sum1 + equal-len + mass-share + ladder) SUFFICIENT?
massvals = [Fraction(0), Fraction(1,8), Fraction(1,4), Fraction(1,2), Fraction(1,1)]
cand = []
for qa in [Fraction(1,1), Fraction(1,2)]:
    for qb in massvals:
        for qc in massvals:
            q = (qa, qb, qc, qc)   # force equal-within-length for C,D
            if is_prob(q) and mass_ge_share(q) and ladder(q):
                cand.append(q)
cand = sorted(set(cand), key=lambda q: tuple(float(x) for x in q))
Rset = set(R)
clean_but_unreal = [q for q in cand if q not in Rset]
print(f"\ncandidates satisfying ALL clean conditions: {len(cand)}")
print(f"  ...of which REALIZABLE: {sum(1 for q in cand if q in Rset)}")
print(f"  ...clean but NON-realizable: {len(clean_but_unreal)}")
for q in clean_but_unreal:
    print(f"      {tuple(str(x) for x in q)}  <- clean conditions hold yet unreachable")
print(f"\n=> clean conditions SUFFICIENT for this codec? {len(clean_but_unreal) == 0}")

print("\nfull realizable set R:")
for q in R:
    print("   ", tuple(str(x) for x in q))
