# Experiment Design: Realized Compositional Leakage Attack

Date: 2026-06-03
Status: RUN 2026-06-03, added as §6.7. H1 confirmed (c=0.32 vs §6.6 0.31, slope -0.50); eta-floor finding added. H3 noise dropped (modeling-ambiguous; Thm 4.1 noise dilution already in §6.6 S2).
Owner theorem(s): Thm 5.1 (upper), Thm 5.2 (lower), Thm 4.1 (noise defense)

## The gap this closes

The paper's empirical coverage is otherwise comprehensive:

| Claim | Anchor |
|---|---|
| Functional correctness | §6.1 Boolean search precision/recall |
| FPR compounding + noise floor | §6.2 |
| Granularity cost spectrum | §6.3 |
| Homophonic flattening | §6.4 (20NG) |
| Compositional/noise RATES | §6.6 Monte Carlo (synthetic i.i.d. draws) |
| Compression measurement | §6.5 |
| Finite-sample delta | §5.4 |

The one thing untested: an **actual attack on the actual construction**.
§6.6 validates the `Theta(sqrt(|Y1||Y2|/N))` rate, but it draws
i.i.d. pairs from a *known* joint `P`. It never builds real cipher
maps, never has the untrusted machine evaluate them on shared cipher
values, and never recovers `P` it was not handed. A TCC/CSF/QIF
reviewer will ask: does the PHF-backed construction (hashing,
acceptance predicates, finite `n`) actually leak the joint at the
predicted rate, or does its structure change the constant or the
exponent? This experiment answers that, and adds the adversarial
dimension the paper currently lacks.

## Hypotheses

- **H1 (primary, attack achievability on the real construction).** An
  adversary observing `N` shared-cipher-value evaluations
  `(fhat_1(c_i), fhat_2(c_i))` on cipher maps *built by the
  cipher-maps library* recovers the latent joint `P` on `Y1 x Y2` at
  `E[TV(Phat, P)] = c * sqrt(|Y1||Y2|/N)`, with slope in `N` near
  `-1/2` and constant `c` matching the synthetic §6.6 value (~0.31)
  up to finite-`n` corrections.
- **H2 (MI preservation, Thm 5.1 part 2).** The observed-pair mutual
  information equals the latent-pair MI within estimation error:
  `|Ihat(fhat_1(C); fhat_2(C)) - I(f_1(X); f_2(X))| / I < 0.10` at the
  largest `N`.
- **H3 (noise defense works on the real construction, Thm 4.1).**
  Injecting `R` filler queries per `N` real degrades the adversary's
  effective sample size, inflating `TV` by `~1/rho`
  (since Fisher info falls by `rho^2`, effective `N -> rho^2 N`, and
  `TV ~ sqrt(m/(rho^2 N)) = (1/rho) sqrt(m/N)`).

## Variables

| Role | Variable | Levels |
|---|---|---|
| IV | `N` (observations) | geometric grid 256 .. 32768 |
| IV | `rho` (noise level) | 1.0 (no noise), 0.5, 0.1 |
| IV | latent joint `P` | low / medium / high MI (controlled coupling) |
| IV | `n` (cipher-value bits) | 16 (main), 8 (finite-`n` stress) |
| DV | `TV(Phat, P)` | continuous |
| DV | `Ihat` (estimated MI, bits) | continuous |
| DV | attack wall-clock | seconds |
| Control | seeds | R = 30 per cell |
| Control | acceptance-predicate allocation | fixed (Shannon-optimal) |
| Control | corpus / domain | fixed across conditions |

## Methodology

1. **Latent pair.** Two realizations, run both:
   (a) *Synthetic-on-real-construction*: a controllable joint `P` on
   `Y1 x Y2` (the §6.6 coupling), with `X` a domain of `|X|` keys
   labeled by `(f_1(x), f_2(x)) ~ P`. Isolates the construction effect
   from corpus messiness.
   (b) *Real-corpus*: on 20 Newsgroups, `f_1(doc) = coarse topic`
   (e.g. 8 grouped categories), `f_2(doc) = 1[doc contains "god"]`
   (Bool); genuinely correlated (religion groups), MI is measurable.
2. **Build.** Construct `fhat_1, fhat_2` with the cipher-maps library
   (PHF backend, `n` bits, Shannon-optimal acceptance predicates).
3. **Observe.** Trusted machine encodes inputs `x_i -> c_i = enc(x_i)`;
   untrusted records `(fhat_1(c_i), fhat_2(c_i))` for `i = 1..N`.
   For `rho < 1`, interleave `R = N(1-rho)/rho` filler `c ~ U(B^n)`
   (each stream element real w.p. `rho`, matching Thm 4.1's model).
4. **Attack.** Plug-in empirical `Phat` over `Y1 x Y2` from the
   decoded observed pairs; compute `TV(Phat, P)` and `Ihat`.
5. **Sweep** `N x rho x P x n`; `R = 30` seeds; mean +/- 95% CI.
6. **Fit** `log E[TV]` on `log N` (restricted to `N >= 4m` so the
   plug-in is out of the small-sample floor); compare slope and
   constant to §6.6.

## Success criteria

- **H1 PASS** iff fitted `N`-slope in `[-0.55, -0.45]` for the
  no-noise (`rho=1`) condition at `n=16`, AND constant `c` within a
  factor 2 of 0.31 (finite-`n` may inflate, not deflate).
- **H2 PASS** iff `|Ihat - I_true|/I_true < 0.10` at the largest `N`.
- **H3 PASS** iff `TV(rho=0.5)/TV(rho=1.0)` is within `[1.7, 2.3]`
  (predicted `1/rho = 2`) and `TV(rho=0.1)/TV(rho=1.0)` within
  `[7, 13]` (predicted 10), at matched `N`.
- **Negative-result value.** If `c` at `n=8` is materially larger than
  at `n=16`, that quantifies the finite-`n` (birthday) penalty and is
  itself a reportable finding (the construction leaks *more* than the
  abstract model at small `n`, tightening the defender's `n` budget).

## Sample-size planning

- §6.6 showed `R=40` synthetic seeds give clean slopes; real-build
  cost is higher (PHF construction per map), so `R=30`, cap `m` at 64
  (`|Y1|=8, |Y2|=8`) and `N` at 32768.
- For the fit to resolve `-1/2`, need the largest-`N` `TV` above the
  per-cell CI half-width. At `m=64, N=32768`: `TV ~ 0.31*sqrt(64/32768)
  = 0.0137`; with `R=30`, CI half-width `~ 0.4*TV/sqrt(30) ~ 0.001`,
  i.e. `< 10%` of the mean. Adequate.
- Build cost: PHF build is `O(|X|)`; `|X| ~ 5000`, two maps, 30 seeds,
  ~5 grid points => low single-digit minutes total.

## Threats to validity

- **Finite-`n` collisions.** At `n=8` the cipher space is 256;
  birthday collisions inflate the marginal `delta` and can perturb the
  joint estimate. Mitigation: `n=16` for the headline run, `n=8` only
  as the stress condition (and reported as such).
- **Plug-in small-sample bias.** `TV(Phat, P)` is positively biased at
  `N < m`; restrict the power-law fit to `N >= 4m`.
- **Decode errors (eta).** With `eta > 0` some observed pairs are
  wrong; this adds noise to `Phat` that does not vanish with `N`.
  Run the main condition at `eta = 0` (exact PHF) to isolate the
  leakage rate, then one `eta = 0.05` condition to show robustness.
- **MI estimation bias.** Plug-in MI is upward-biased at finite `N`;
  use the Miller-Madow correction (or report the bias-corrected
  estimate) for H2.

## Relationship to §6.6

§6.6 (just added) is the *abstract-model* validation: the estimator
rate on i.i.d. draws. This experiment is the *construction-level*
validation: the same attack on cipher maps the library actually
builds. Together they would close the loop from theorem to abstract
estimator to deployed construction. If run and H1-H3 pass, this
becomes §6.7 "Realized Attack on the Construction"; if the constant
inflates at small `n`, that is a finding worth a sentence in §9
(practical depth / `n` budget).

## Decision

This experiment is genuinely valuable for a security venue (it is the
paper's only adversarial, construction-level test). But the paper is
already mature (26pp, six review rounds) and §6.6 already validates the
rate. Whether to implement and run it (adding §6.7) versus keeping this
design on file is a scope call for the author. Implementation requires
the cipher-maps library's build/encode/evaluate API
(`~/github/trapdoor-computing/src/cipher-maps/`), which the existing
`examples/` and `experiments/` scripts already exercise, so the lift
is moderate (est. half a day including the figure).
