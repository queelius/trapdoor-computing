"""Verification for the corrected FreqDist real bound (thm:freqdist-real).

Two exact facts behind the 2026-06-09 correction:

  (1) Le Cam equality. In the Adv = |2 Pr[b' = b] - 1| convention, the optimal
      test on ONE observation distinguishing laws P, Q has advantage EXACTLY
      TV(P, Q): Pr[correct] = (1/2) sum_x max(P(x), Q(x)) = 1/2 + TV/2. So the
      per-observation bound is Adv <= TV <= delta(p0) + delta(p1) with NO factor
      of 2 (the earlier 2(...) form double-counted the convention factor).

  (2) Per-observation scoping is necessary. For two FIXED distinct laws at TV
      distance d > 0, the optimal advantage over n i.i.d. observations grows
      toward 1 (likelihood-ratio test); "the two laws are within d" does NOT cap
      the many-query advantage. What protects the many-query regime in the paper
      is NOT this TV bound but the frequency-blindness of the per-build
      deviation: by T3 the law carries no multiplicity term, and E2 measures the
      cross-profile distance at the same-profile rebuild floor, so estimating
      the realized law surfaces no profile signal. That many-query statement is
      measured ([characterize]), not proven; the proven content is (1).

Fact (1) is checked in exact rational arithmetic; fact (2) by a likelihood-ratio
Monte Carlo at the E2 scale (TV = 0.006, the rich/rich corrected bound).
"""
import math
import random
from fractions import Fraction as F

# Two laws within delta ~ 0.003 of a common center, separated by d = 0.006:
# the corrected rich/rich FreqDist scale.
law0 = [F(1, 2) + F(3, 1000), F(1, 4) - F(3, 1000), F(1, 8), F(1, 8)]
law1 = [F(1, 2) - F(3, 1000), F(1, 4) + F(3, 1000), F(1, 8), F(1, 8)]
assert sum(law0) == 1 and sum(law1) == 1

TV = sum(abs(a - b) for a, b in zip(law0, law1)) / 2
print("TV(law0, law1) =", TV, "=", float(TV))

# (1) Le Cam equality, exact: optimal single-observation Adv == TV.
p_correct = sum(max(a, b) for a, b in zip(law0, law1)) / 2
adv_one = abs(2 * p_correct - 1)
print("optimal single-observation Adv =", adv_one)
assert adv_one == TV, "per-observation advantage must equal TV exactly (no factor of 2)"
print("  == TV exactly: the corrected constant is tight, no factor of 2.")

# (2) Amplification: the optimal n-observation advantage grows with n.
random.seed(7)
l0 = [float(x) for x in law0]
l1 = [float(x) for x in law1]


def llr(law, n):
    xs = random.choices(range(4), weights=law, k=n)
    return sum(math.log(l0[x] / l1[x]) for x in xs)


M = 20000
prev = float(TV)
print("n-observation optimal-test advantage (Monte Carlo, M = %d):" % M)
for n in [50, 200, 1000]:
    s0 = [llr(l0, n) for _ in range(M)]
    s1 = [llr(l1, n) for _ in range(M)]
    pc = (sum(1 for v in s0 if v > 0) + sum(1 for v in s1 if v <= 0)) / (2 * M)
    adv_n = abs(2 * pc - 1)
    print(f"  n = {n:5d}: Adv ~= {adv_n:.3f}")
    assert adv_n > prev, "advantage must grow with n for fixed distinct laws"
    prev = adv_n

print("PASS: per-observation Adv == TV exactly; many-query Adv grows toward 1,")
print("so the bound is correctly scoped per observation.")
