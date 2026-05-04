# Thesis Refinement: Sharpening to Information-Theoretic Optimality

Date: 2026-05-04
Paper state: 25 pages, zero warnings, 6 theorems, 4 tables, 3 figures.

## What changed

Promoted the compositional-leakage contribution from a "rate result"
to an "information-theoretically optimal rate" framing throughout the
paper. The change reflects Theorem 5.2 (Le Cam minimax lower bound),
which was added on 2026-04-30 (commit 08b38e3) but had not been fully
reflected in the paper's framing language or in the recorded thesis.

## Why it's defensible

Theorem 5.1 establishes that the empirical-distribution plug-in
estimator achieves rate O(|Y_1||Y_2|/xi^2) for joint recovery.
Theorem 5.2 establishes via Le Cam's two-point method on a packing of
perturbed-uniform distributions that no estimator can achieve a faster
rate. Together they give the **sharp rate**
Theta(|Y_1||Y_2|/xi^2), with matching asymptotic dependence on N,
|Y_i|, and xi between upper and lower bounds (absolute constants on
each side may differ by a factor, which is standard for minimax
results).

This is standard minimax usage: "minimax-optimal rate" or
"information-theoretically optimal rate" describes a result where the
asymptotic rate matches between upper and lower bounds, even when
absolute constants differ.

Reviewers respond more strongly to impossibility-flavored framing than
to capability-flavored framing. The paper's contribution is now
phrased as "the adversary's task is provably as hard as it gets, and
the defender's marginal-scale tools cannot help", which is a
fundamental-limit claim that maps cleanly onto the literature's
expectation for such results.

## Important precision preserved

The framing carefully distinguishes:

- **No per-cipher-map parameter changes the rate.** Tuning delta,
  K(x), epsilon, or encoding choice does not affect the
  Theta(|Y_1||Y_2|/xi^2) rate at the compositional scale.
- **System-level interventions DO reduce effective adversary
  advantage.** Reducing observations N (caps the parametric rate),
  joint encoding via Prop 4.3 (replaces |Y_1|*|Y_2| with |Y|^k for
  merged cipher maps), noise injection (dilutes effective sample
  size).

The impossibility is therefore with respect to per-cipher-map
parameters only. The paper avoids the over-reach "no construction can
stop it" because noise injection is an effective system-level
mitigation that the paper's own Sec 6.5 case study uses (rho=0.5
boosts entropy ratio from 0.87 to 0.98).

## Updates landed

### Abstract
The compositional sentence now reads:

> recover the latent joint distribution at the
> *information-theoretically optimal* rate Theta(|Y_1||Y_2|/xi^2)
> (matching upper bound from plug-in estimation, matching lower bound
> via Le Cam's two-point method). The compositional channel is
> therefore not merely exploitable but unavoidable for any choice of
> per-cipher-map parameters; reducing delta is necessary but not
> sufficient, and only system-level interventions ... reduce the
> adversary's effective advantage.

### Sec 1 framing paragraph (Compositional scale.)
Now leads with: "the paper's main result is that this is not enough,
and in a strong sense" and cites the optimal rate via both theorems.
The "no per-cipher-map parameter changes the rate" claim is explicit.

### Sec 1 contributions list (item 1)
Renamed from "Compositional leakage theorem (main result)" to
"Compositional leakage at the optimal rate (main result)". Lists both
Thms 5.1 and 5.2; the per-parameter-vs-system-level distinction is
explicit.

### Sec 2 Related Work
The novelty enumeration in the QIF paragraph now reads "(i) the
compositional leakage result establishing the
information-theoretically optimal rate Theta(|Y_1||Y_2|/xi^2) via
matching upper and lower bounds".

### Sec 8 Conclusion
Now refers to the "compositional leakage pair" rather than the
singular theorem, with explicit Le Cam citation.

## What did NOT change

- The mathematical content of the theorems and proofs.
- The two-scale conceptual frame from 2026-04-29 (still the spine of
  the paper).
- The contribution-ordering decision from 2026-04-29 (compositional
  leakage first, Fannes bridge second).
- The Sec 9 practical-depth discussion from 2026-05-03.
- Any of the experimental results.

## Build verification

PDF builds clean at 25 pages, zero warnings. All citations and
references resolve.

## Next actions (open)

1. /papermill:venue to pick a target. The impossibility framing is
   well-suited to TCC, CSF, or QIF workshop. Less well-suited to
   USENIX Security (which prefers attacks/systems framings).
2. Optional: cross-paper sync of Pinsker/K(x) errors in
   ../cipher-maps/ companion paper. Last verified 2026-04-12.
3. Optional: resume papers/adaptive-trapdoor/ once
   PHFCipherMap.retune_k() is implemented in the cipher-maps library.
