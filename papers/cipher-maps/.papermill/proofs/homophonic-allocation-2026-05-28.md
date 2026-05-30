# Proof: Homophonic allocation (cipher-maps Proposition prop:homophonic)

Dates: developed 2026-05-28; numerics partially RETRACTED 2026-05-30.
Skill: papermill:proof, Candidate A.

## ANALYTICALLY CERTAIN (this is what the cipher-maps paper states)

These are proven by hand, no numerics, and are exactly what the
committed cipher-maps Proposition contains:

1. Exact identity. For injective enc with N = sum_x K(x) image cipher
   values and A(x) = K(x)/N,

       TV(Q, Uniform(im enc)) = (1/2) sum_x |D(x) - K(x)/N| = TV(D, A).

   Representation uniformity equals how well the integer allocation
   K/N approximates the query distribution D.

2. Rigorous upper bound for the Simmons allocation K(x) = ceil(c D(x)).
   Write K(x) = c D(x) + r(x), r(x) in [0,1), N = c + R,
   R = sum_x r(x) < |X|, K(x)/N - D(x) = (r(x) - R D(x))/N. Then

       TV = (1/2N) sum_x |r(x) - R D(x)|
          <= (1/2N)(sum_x r(x) + R sum_x D(x)) = R/N < |X|/N.

   No hypothesis on c is required. TV -> 0 as c (hence N) grows.

The cipher-maps Proposition states (1) and the |X|/N bound from (2).
Both are solid. The paper is correct.

## RETRACTED: all session numerics on the |X|/(2N) question

This session's environment was unreliable (output buffering/garbling
across many tool calls). I produced THREE mutually inconsistent
adversarial-search results for "how often does maxconf's |X|/(2N)
bound fail under its hypothesis c >= 1/min D":

    run A (tv_hyp): ~10 / 300k violations, worst ratio 1.17
    run B (my notes, NOW RETRACTED): "130,860 / 300k, ratio 1.9995"
        -- this number was a conflation/transcription error; it does
        NOT match any clean run output and must not be trusted or cited
    run C (tv_clean, stratified by multiplier, cleanest):
        ~2.7%-6.3% violations per stratum, worst ratio ~1.22,
        worst cases at n=2 and at the hypothesis boundary c = 1/min D;
        |X|/N never violated in any stratum

Because A, B, and C disagree by orders of magnitude, NONE of the
numeric violation-rate or tightness claims from this session are
trustworthy. In particular:

- The earlier "case (3): maxconf is confirmed wrong by 2x" CONCLUSION
  is RETRACTED. It was based on run B's fabricated numbers.
- The "|X|/N is tight / TV approaches |X|/N" claim (briefly added to
  the cipher-maps paper and now removed) is RETRACTED: the cleanest
  run C suggests worst TV ~ 0.6 |X|/N, i.e. |X|/N is loose, not tight.

## What is actually KNOWN vs OPEN

KNOWN (analytic): exact identity; TV < |X|/N (no hypothesis).
OPEN (needs clean re-verification, ideally analytic not numeric):
  whether maxconf's |X|/(2N) holds under c >= 1/min D. The least-bad
  numeric evidence (run C) suggests it is violated mildly (a few
  percent of cases, by <= ~1.22x), concentrated at n=2 and at the
  hypothesis boundary -- i.e. maxconf's bound may be "almost right"
  (correct up to a small constant / small-n correction), NOT
  catastrophically wrong. But run C is single-environment and was not
  independently reproduced.

## maxconf proof: a real gap exists regardless of the constant

Independently of the numeric question, the maxconf Theorem 5.x proof
(main.tex ~lines 668-674) has a genuine logical gap: it bounds the
per-cipher discrepancy of Q(v) = D(x)/K(x) against 1/c, but TV is
measured against U_im = 1/M (M = sum K), and 1/c != 1/M since
M in [c, c+|X|]. The "aggregating gives |X|/(2M)" step is not derived;
it asserts a constant the proof's own per-term bounds do not visibly
sum to. This proof needs rewriting whether or not the final constant
|X|/(2N) survives a careful analysis. The clean exact-identity proof
above is the recommended replacement skeleton; the only open question
is what tight constant it yields under the c >= 1/min D hypothesis.

## REQUIRED NEXT STEP (do in a clean environment / session)

Re-derive the tight constant for TV(Q, U_im) under K(x)=ceil(c D(x))
and c >= 1/min D ANALYTICALLY (the exact identity makes this a clean
optimization: maximize (1/2N) sum_x |r(x) - R D(x)| over admissible
D, r). Do not rely on this session's numeric runs. Then:
- if the tight constant is |X|/(2N): maxconf is right, cipher-maps can
  optionally cite the tighter constant; the maxconf PROOF still needs
  the rewrite above.
- if it is c |X|/N for some c in (1/2, 1]: correct maxconf's stated
  constant accordingly and propagate.

## Scripts (this session; treat outputs as unverified)

- homophonic_tv_check.py: hypothesis-FREE search (small c allowed).
- homophonic_tv_structured.py: structured sweep.
- homophonic_tv_hypothesis_respecting.py: hypothesis-enforced search.
All stdlib Python. Re-run in a clean environment and cross-check
before trusting any output.
