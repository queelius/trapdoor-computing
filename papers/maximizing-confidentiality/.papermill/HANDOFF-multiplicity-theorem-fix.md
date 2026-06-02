# HANDOFF: fix Theorem 5.x (constant is WRONG for n >= 3, and proof)

Written 2026-05-30, revised twice; THIS version (2026-06-02, final) is
authoritative. Earlier revisions flip-flopped; see "provenance" at the
bottom. Resume in a fresh maximizing-confidentiality session.

## TL;DR

Theorem 5.x ("Representation uniformity via multiplicity", main.tex
line 654) is WRONG as stated for |X| >= 3. It claims
TV(Q, U_im) <= |X|/(2 sum K); the correct tight bound is
TV < (|X|-1)/(sum K) = (|X|-1)/N. The stated constant is too small by
a factor approaching 2 (the violation ratio is 2(|X|-1)/|X|, which is
1 at |X|=2 and grows to 2). Both the constant and the proof need
fixing, and downstream e-numbers must be recomputed.

## Hand-verified counterexample (n=3)

D = (0.0101, 0.0101, 0.9798), c = 100.
- min D = 0.0101, 1/min D = 99.01, so c >= 1/min D: hypothesis HOLDS.
- cD = (1.01, 1.01, 97.98); K = ceil(cD) = (2, 2, 98); N = 102.
- TV = (1/2)( 2*|0.0101 - 2/102| + |0.9798 - 98/102| ) = 0.019016.
- maxconf claim |X|/(2N) = 3/204 = 0.014706.
- TV / claim = 1.293 > 1.  VIOLATION.
Reproduced exactly by
../cipher-maps/.papermill/proofs/homophonic_counterexample_n3.py
(deterministic; also checks n=2..8, violation ratios 1.00, 1.33, 1.50,
1.60, 1.66, 1.71, 1.75 -> 2).

n=2 is the exceptional case where |X|/(2N) holds (ratio -> 1). It does
NOT generalize; an earlier handoff revision wrongly extrapolated from
n=2.

## Correct theorem and proof (drop-in)

Exact identity (cipher-maps prop:homophonic):
    TV(Q, U_im) = (1/2) sum_x |D(x) - K(x)/N|.
Deviations r(x) - R D(x) (with r(x) = K(x) - cD(x), R = sum r,
N = c + R) sum to zero, so with P = {x : r(x) > R D(x)}:
    TV = (1/N) sum_{x in P} (r(x) - R D(x)).
P is a PROPER subset (deviations summing to zero cannot all be
positive), so |P| <= |X| - 1, and using R D(x) >= 0, r(x) < 1:
    TV <= (1/N) sum_{x in P} r(x) < |P|/N <= (|X|-1)/N.
No hypothesis on c is required. Tight: the n>=3 construction above
approaches (|X|-1)/N (script ratios 0.998-0.999).

Suggested statement:
    Theorem. For K(x) = ceil(c D(x)) with N = sum_x K(x), under
    injective enc, TV(Q, U_im) < (|X|-1)/N, vanishing as c -> infinity.
    The constant |X|-1 is tight.

The hypothesis c >= 1/min D can be DROPPED (the bound holds without it).

## Required fixes (all needed)

1. [ ] Theorem 5.x statement: |X|/(2 sum K) -> (|X|-1)/(sum K), and
       |X|/(2c) -> (|X|-1)/c (since N >= c). Drop the c >= 1/min D
       hypothesis or keep it as harmless.
2. [ ] Replace the proof with the exact-identity + proper-subset
       argument above. (The old proof bounded discrepancy against 1/c
       instead of 1/N and asserted |X|/(2M) without summing; both are
       fixed by the new proof.)
3. [ ] Recompute downstream e-numbers. delta roughly DOUBLES for a
       given budget (|X|/(2N) -> (|X|-1)/N is up to 2x larger), so
       e >= 1 - delta - h2(delta)/n weakens. Affected: the Zipf
       worked example (main.tex ~line 707) and any e-values in the
       abstract, intro, and experiments that were computed from the
       old delta. This is a REAL change, not cosmetic.
4. [ ] Propagate the corrected delta bound to:
       - parent ~/github/trapdoor-computing/CLAUDE.md Principle 7
         ("delta = |X|/(2 sum K)" -> "delta < (|X|-1)/(sum K)")
       - the cipher-maps library README / docs if it cites "Thm 6.2".
5. [ ] papermill:proof verification on the corrected theorem.

## Already done (cipher-maps side; do NOT redo)

- cipher-maps Proposition prop:homophonic now states the correct,
  tight TV < (|X|-1)/N with the proper-subset proof (committed this
  session). It is hypothesis-free and strictly stronger than the
  |X|/N it replaced.
- Full diagnosis + counterexample + script:
  ../cipher-maps/.papermill/proofs/homophonic-allocation-2026-05-28.md
  ../cipher-maps/.papermill/proofs/homophonic_counterexample_n3.py

## Severity: moderate (constant + downstream numbers)

NOT a framework change: the Fannes bridge e >= 1 - delta - h2(delta)/n
is unchanged, and K(x) propto D(x) is still right. But the achievable-
delta numbers are off by up to 2x, so any quantitative confidentiality
claim derived from Theorem 5.x must be restated. Must be fixed before
submission.

## Provenance (why this revision is trustworthy)

This question flip-flopped across a session with an unreliable tool-
output channel: (a) flaky-numerics "case 3, off by 2x" (retracted,
numbers were garbled); (b) "case 1, constant fine" (wrong, extrapolated
from the n=2 special case); (c) THIS: case 3, confirmed by a concrete
hand-checked n=3 counterexample, an elementary proof of the
replacement bound, and a deterministic script, all agreeing to 4
significant figures. Trust (c): it does not depend on any random
search or any single tool output.
