# HANDOFF: fix the PROOF of Theorem 5.x (constant is fine)

Written 2026-05-30, revised 2026-06-02 after an analytic derivation.
Resume in a fresh maximizing-confidentiality session with this paper's
CLAUDE.md loaded.

## TL;DR (revised)

Theorem 5.x ("Representation uniformity via multiplicity", main.tex
line 654) has the RIGHT constant but a WRONG proof. The stated bound
TV(Q, U_im) <= |X|/(2 sum K) is (almost certainly) correct under the
hypothesis c >= 1/min D. The proof, however, is broken and must be
replaced. An earlier alarm ("constant off by 2x, case 3") was based on
unreliable numerics and is FULLY RETRACTED; hand analysis flips the
verdict to "constant correct" (case 1).

## Why the constant is fine (analytic, trustworthy)

Exact identity (proved + committed in cipher-maps as prop:homophonic):
    TV(Q, U_im) = (1/2) sum_x |D(x) - K(x)/N|,
    K(x)=ceil(cD(x)), r(x)=K(x)-cD(x) in [0,1), R=sum r, N=c+R.

Result A: the hypothesis forces c >= n.
    min_x D(x) <= 1/n (min <= mean), so 1/min D >= n, so c >= n.
    At c = n: D is forced uniform, every r(x)=0, TV=0.
    The hypothesis is really "budget >= n" and pins TV=0 at c=n.

Result B: positive-part form.
    sum_x r(x) = R = sum_x R D(x), so signed deviations cancel:
    TV = (1/N) sum_{x: r(x) > R D(x)} (r(x) - R D(x)).

Result C: n=2 at the boundary c = 1/p, exact.
    With 1/p = m + phi (m = floor(1/p) >= 2), TV/(|X|/(2N)) =
    (1-phi)/(m+phi) <= 1/m <= 1/2. The bound holds with a factor of 2
    to spare.

Structural exploration of the two-group worst-case family tops out
near 3 - 2*sqrt(2) ~ 0.17, well under |X|/(2N) at the relevant scale.
So |X|/(2N) is sound; no constant change needed.

## What is actually broken: the proof (must fix)

main.tex ~lines 668-674. The proof bounds the per-cipher discrepancy
of Q(v) = D(x)/K(x) against 1/c, but TV is measured against
U_im = 1/M (M = sum K = N), and 1/c != 1/M since M in [c, c+|X|]. It
then asserts "aggregating gives |X|/(2M)" without completing the sum.
The constant happens to be right; the derivation does not establish it.

## Required fix

1. [ ] Replace the proof with the exact-identity derivation (Results
       A + B above). The remaining step is to prove
       sup TV <= |X|/(2N) for GENERAL n under c >= 1/min D. The n=2
       case (Result C) is done; general n is a finite optimization,
       made tractable by Result A (c >= n) and Result B (positive-part
       form). This is the one genuine piece of math left. If the
       general bound turns out to be a slightly different clean
       constant, adjust the statement accordingly, but n=2 and the
       exploration both point at |X|/(2N) surviving.
2. [ ] Keep the hypothesis c >= 1/min D (it is load-bearing: Result A
       shows it is what makes any tight constant possible; without it
       only the looser |X|/N holds).
3. [ ] Numeric cross-check is fine to GUIDE the general-n proof but
       must be reproduced in a stable environment before being trusted
       (the originating session's tool output was intermittently
       unreliable; it produced four mutually inconsistent search
       results for the same quantity, all now disregarded in favor of
       the hand analysis).

## Likely-no-op propagation (only if the constant changes)

If the general-n proof confirms |X|/(2N) (expected), NOTHING
downstream changes: the entropy-ratio numbers, the Zipf example, the
parent CLAUDE.md Principle 7 ("delta = |X|/(2 sum K)"), and the
cipher-maps library README all stay as-is. Only revisit them if the
general-n analysis yields a different constant than |X|/(2N).

## Already done (cipher-maps side; do NOT redo)

- cipher-maps Proposition prop:homophonic: exact identity + the
  rigorous hypothesis-free bound TV < |X|/N. Correct, committed.
- cipher-maps removed an earlier false deferral sentence (commit
  c9e830b) and never published any unverified tightness claim.
- Full diagnosis, the retracted numerics, and Results A/B/C:
  ../cipher-maps/.papermill/proofs/homophonic-allocation-2026-05-28.md

## Severity: low

The framework is unaffected. The Fannes bridge
e >= 1 - delta - h2(delta)/n is unchanged, K(x) propto D(x) is the
right prescription, and the headline confidentiality numbers stand.
This is a proof-rewrite (one bounded optimization for general n), not
a result change. Must still be fixed before submission because a
PoPETs-style reviewer will catch the gap between the asserted constant
and the proof's own per-term bounds.
