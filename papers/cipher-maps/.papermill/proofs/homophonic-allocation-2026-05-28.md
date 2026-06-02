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

## SUPERSEDING ANALYTIC RESULT (2026-06-02) -- lean flips to case (1)

Did the derivation by hand (no numerics; the retracted runs above are
moot). Two clean, checkable results:

### Result A: the hypothesis c >= 1/min D forces c >= n.

min_x D(x) <= (1/n) sum D(x) = 1/n (min <= mean), so 1/min D >= n,
hence c >= 1/min D >= n. At equality c = n: min D >= 1/n with mean
1/n forces D uniform, so every cD(x) = 1, r(x) = 0, R = 0, TV = 0.
The hypothesis is really "budget >= n", and it pins TV = 0 at the
boundary. (Neither paper noted this.)

### Result B: collapse to positive part.

Since sum_x r(x) = R = sum_x R D(x), signed deviations cancel:
    TV = (1/N) sum_{x : r(x) > R D(x)} (r(x) - R D(x)).

### Result C: n = 2 at the budget boundary, exact.

X = {1,2}, D = (p, 1-p), p <= 1/2, c = 1/p. Then cp = 1 so r1 = 0;
with 1/p = m + phi (m = floor(1/p) >= 2, phi = frac), both deviations
equal (1-phi)/(m+phi), giving
    TV / (|X|/(2N)) = (1-phi)/(m+phi) <= 1/m <= 1/2 < 1.
So maxconf's |X|/(2N) HOLDS for n=2, with a factor of 2 to spare.

### Conclusion: CASE (1), not case (3).

The earlier "worst ratio -> 2.0, maxconf wrong" was flaky-channel
numerics and is RETRACTED in full. Hand analysis says the opposite:
n=2 ratio <= 1/2, no violation. maxconf's CONSTANT |X|/(2N) is almost
certainly correct (rigorous for n=2; strongly indicated for general n
by the c >= n structure; structural exploration of the two-group
worst-case family tops out near 3 - 2*sqrt(2) ~ 0.17, well under
|X|/(2N) at the relevant scale).

maxconf's PROOF is still wrong and must be replaced (it bounds the
per-cipher discrepancy against 1/c, but TV is against 1/N = 1/M, and
it asserts the |X|/(2M) constant without completing the sum). The
exact-identity derivation (Result B plus the c >= n reduction) is the
clean replacement.

### Remaining (clean session, tractable):

Prove sup TV <= |X|/(2N) for GENERAL n under c >= 1/min D. The n=2
case is done; general n is a finite optimization made tractable by
Result A (c >= n) and Result B (positive-part form). Numeric
cross-check is fine to GUIDE it but must be reproduced in a stable
environment before being trusted.

### cipher-maps paper impact: none required.

cipher-maps states only the hypothesis-free |X|/N (rigorous,
unchanged) and no longer defers to maxconf for a tighter constant
(false-deferral sentence removed in commit c9e830b). If/when the
general-n |X|/(2N) result is proven, cipher-maps MAY optionally cite
the tighter constant, but is correct as-is.
