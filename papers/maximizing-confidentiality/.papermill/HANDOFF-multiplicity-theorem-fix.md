# HANDOFF: re-verify Theorem 5.x (Representation uniformity via multiplicity)

Written 2026-05-30 from a cipher-maps session (papermill:proof on the
cipher-maps homophonic-allocation proposition). Resume in a FRESH
maximizing-confidentiality session with a clean environment (the
originating session had unreliable tool output; see the retraction
note below). Load this paper's CLAUDE.md too.

## TL;DR

Theorem 5.x ("Representation uniformity via multiplicity", main.tex
line 654) has (a) a genuine, environment-independent GAP IN THE PROOF
that must be fixed, and (b) an OPEN question about whether its stated
constant |X|/(2 sum K) is exactly right. Do NOT blindly change the
constant; re-derive it analytically first.

## (a) The proof gap (certain, fix this)

maxconf proof, main.tex ~lines 668-674. It bounds the per-cipher
discrepancy of Q(v) = D(x)/K(x) against 1/c, then asserts
"aggregating gives TV <= |X|/(2M)". Problems:

1. TV is measured against U_im (mass 1/M per image value, M = sum K),
   not against 1/c. Since M in [c, c+|X|], 1/c != 1/M. The proof
   bounds discrepancy from the wrong reference point.
2. The "aggregating gives |X|/(2M)" step is asserted, not derived; the
   per-term bounds shown do not visibly sum to that constant.

Replace with the exact-identity skeleton (proved and committed in the
cipher-maps companion as Proposition prop:homophonic):

    TV(Q, U_im) = (1/2) sum_x | D(x) - K(x)/N |  =  TV(D, K/N),
    N = sum_x K(x).

For K(x) = ceil(c D(x)): K(x) = c D(x) + r(x), r in [0,1), N = c + R,
R = sum r < |X|, K(x)/N - D(x) = (r(x) - R D(x))/N, hence

    TV = (1/2N) sum_x |r(x) - R D(x)|  <=  R/N  <  |X|/N.

This rigorously gives |X|/N with NO hypothesis on c. That much is
certain and provable by hand.

## (b) The open question: is the tighter |X|/(2N) actually valid?

maxconf claims TV <= |X|/(2 sum K) under the hypothesis
c >= 1/min_x D(x). Whether this tighter constant (a factor of 2 below
the rigorous |X|/N) holds is NOT resolved.

RETRACTION: the originating cipher-maps session first concluded
"maxconf is wrong by 2x (case 3)" based on an adversarial search.
That conclusion was withdrawn: the session's environment produced
three mutually inconsistent numeric runs for the same question
(violation rates of ~0.003%, ~44%, and ~5%; worst ratios of 1.17,
2.0, and 1.22). The "44% / 2x" figure was a transcription error and
must be ignored. The cleanest run (stratified by the hypothesis
multiplier) suggested |X|/(2N) is violated only MILDLY -- a few
percent of cases, by at most ~1.22x, concentrated at n=2 and at the
hypothesis boundary c = 1/min D -- which would make maxconf's bound
"almost right" (correct up to a small constant or a small-n
correction), not catastrophically wrong. But no run was independently
reproduced, so treat ALL of it as unverified.

## REQUIRED FIRST STEP (analytic, not numeric)

Using the exact identity, the tight constant is the solution of

    maximize  (1/2N) sum_x |r(x) - R D(x)|

over distributions D on X (|X| = n) and the induced
r(x) = ceil(c D(x)) - c D(x) in [0,1), R = sum r, N = c + R, subject
to c >= 1/min_x D(x). This is a clean finite optimization. Derive the
exact sup. Then:

- if sup = |X|/(2N): maxconf's constant is correct; keep it, but still
  fix the proof per (a). cipher-maps may optionally cite the tighter
  constant (it currently states only the rigorous |X|/N).
- if sup = k |X|/N for some k in (1/2, 1]: correct maxconf's stated
  constant to k |X|/N (the n=2 worst cases in the numeric run hint the
  true constant may carry a small-n factor), fix the proof, and
  propagate (below).

Do this analytically. Do not rely on the originating session's
numeric scripts (they are in
../cipher-maps/.papermill/proofs/homophonic_tv_*.py but their outputs
were not reproducible in that session).

## Propagation checklist (only after the constant is settled)

1. [ ] Theorem 5.x statement: set the constant to the analytically
       derived tight value.
2. [ ] Theorem 5.x proof: replace with the exact-identity proof.
3. [ ] If the constant changed: Example 5.x (Zipf homophonic,
       main.tex ~line 707) and any entropy-ratio numbers that
       substitute this delta -- recompute the e values (abstract,
       intro, example). A constant change of up to 2x roughly halves
       the achievable e-gain claims; re-state them.
4. [ ] Parent ~/github/trapdoor-computing/CLAUDE.md Principle 7
       ("delta = |X| / (2 * sum K(x))"): update to the settled value.
5. [ ] cipher-maps library README ("Thm 6.2"): same.
6. [ ] papermill:proof verification on the corrected Theorem 5.x.

## Already done (cipher-maps side; do NOT redo)

- cipher-maps Proposition prop:homophonic states the exact identity
  and the rigorous |X|/N bound. Correct and committed.
- cipher-maps removed an earlier false deferral sentence (it had
  claimed "tighter constants are developed in the companion
  entropy-ratio work") AND a briefly-added unverified "|X|/N is tight"
  claim. The paper now states only the proven content.
- Full diagnosis + retraction:
  ../cipher-maps/.papermill/proofs/homophonic-allocation-2026-05-28.md

## Severity

If maxconf's |X|/(2N) turns out merely "almost right" (mild small-n /
boundary violations), this is a minor wording/constant tweak plus a
proof rewrite, not a structural problem: the Fannes bridge
e >= 1 - delta - h2(delta)/n is unchanged and K(x) propto D(x)
remains the right prescription. If it is off by a full factor of 2,
the achievable-confidentiality numbers weaken by that factor. Either
way it must be settled before submission because the constant appears
in the theorem statement and the worked example.
