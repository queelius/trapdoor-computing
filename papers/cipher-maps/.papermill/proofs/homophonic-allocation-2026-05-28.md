# Proof verification: Homophonic allocation (Proposition 4.x)

Date: 2026-05-28
Skill: papermill:proof, Candidate A (homophonic prescription optimality)

## What was proven and added to the paper

Proposition (Homophonic allocation), inserted in cipher_maps.tex after
the Definition 4.2 prose, before the "Marginal uniformity only" remark.

**Exact identity** (the valuable result):
For injective enc with N = sum_x K(x) cipher values in the image and
A(x) = K(x)/N the normalized allocation,

    TV(Q, Uniform(im enc)) = (1/2) sum_x |D(x) - K(x)/N| = TV(D, A).

Representation uniformity is *exactly* how well the integer allocation
K/N approximates the query distribution D. Verified to machine
precision in homophonic_tv_check.py / homophonic_tv_structured.py.

**Provable sufficient bound** (Simmons allocation K(x) = ceil(c D(x))):

    TV(Q, Uniform(im enc)) <= R/N < |X|/N,  R = sum_x r(x), r(x) in [0,1)

vanishing as budget c grows. Triangle-inequality proof. Held in all
200,000 adversarial trials (max ratio to |X|/N was 0.734 < 1).

## IMPORTANT FINDING: the |X|/(2N) constant is FALSE for naive ceil allocation

The parent CLAUDE.md (Core Principle 7), the cipher-maps library
README (cited as "Thm 6.2"), and the maxconf design notes all assert

    delta <= |X| / (2 * sum K(x))   [i.e., TV <= |X|/(2N)]

For K(x) = ceil(c D(x)), this is VIOLATED. Adversarial search over
200,000 random distributions (homophonic_tv_check.py):

- 885 violations out of 200,000 trials
- max ratio TV / (|X|/(2N)) = 1.468
- worst case: n=5, c=2, TV=0.6116, bound |X|/(2N)=0.4167

Structured example that violates it at every budget:
heavy-tail D = (0.9, 0.0111 x 9):

    c       sumK    TV         |X|/(2N)    violated?
    10      18      0.400000   0.277778    yes
    100     108     0.066667   0.046296    yes
    1000    1008    0.007143   0.004960    yes
    10000   10008   0.000719   0.000500    yes

Mechanism: when D is concentrated and the budget is small relative to
the skew, ceil rounding forces the allocation toward uniform while D
stays near a point mass, so TV is large. The factor-2-tighter bound
fails precisely in the regime where multiplicity is too coarse to
track a skewed D.

### What this means

The exact identity TV = TV(D, K/N) is correct and is what cipher-maps
now states. The |X|/(2N) constant must NOT be cited in cipher-maps
for the naive ceil allocation. Three possibilities for the ecosystem:

1. maxconf's Theorem proves |X|/(2N) under an additional hypothesis
   the naive model omits (e.g., large-budget regime where every
   K(x) >= some threshold so ceil rounding is non-binding; or a
   water-filling / largest-remainder allocation rather than
   independent per-element ceil). If so, cite it WITH that hypothesis.
2. maxconf uses a different normalization (e.g., bound on TV to
   Uniform over a fixed 2^n space, not the image; or floor instead
   of ceil; or K(x) = round(c D(x))). Re-derive under the actual
   maxconf statement.
3. The |X|/(2N) constant in maxconf is simply wrong and should be
   corrected to |X|/N (or R/N), propagating to the parent CLAUDE.md
   Principle 7, the library README "Thm 6.2", and the entropy-ratio
   chain e >= 1 - delta - h_2(delta)/n wherever delta = |X|/(2N) is
   substituted.

ACTION REQUIRED (user / maxconf-side): determine which of (1)-(3)
holds by checking the actual maxconf Theorem statement and proof.
cipher-maps is safe either way: it states the exact identity and the
provable |X|/N, and defers "tighter constants under additional budget
hypotheses" to maxconf without committing to a specific value.

## Verification scripts

- homophonic_tv_check.py: 200k-trial adversarial search; reports
  violations and max ratio for |X|/(2N).
- homophonic_tv_structured.py: structured sweep (uniform, zipf-8,
  zipf-32, heavy-tail) x (c in 10,100,1000,10000); prints exact TV,
  both candidate bounds, and pass/fail per cell.

Both stdlib-only Python; run directly.
