# Multi-Agent Review, Round 2 (Fable): "The Entropy Ratio"

**Date:** 2026-06-11
**Commits reviewed:** canonical at 59db449 content (HEAD 768977e); CSF port at venue/csf/ (768977e)
**Round-1 context:** 2026-06-10 round (5 Opus specialists) returned clean MINOR-REVISION.
**This round:** 5 specialists on the model-sensitive dimensions. THREE completed
(hostile 3-persona CSF referee on the built submission PDF; format/compliance
validator on the port; editorial seam auditor on the port). TWO died on the
account's monthly spend limit (deep proof verifier; numerical recomputation
auditor); the orchestrator (Fable, max effort) independently verified every
critical claim below by hand derivation and exact Python recomputation, so the
load-bearing findings are NOT single-agent claims.

---

## Verdict: MAJOR-REVISION (overturns round 1). Do not submit as-is.

Round 1 verified scoping, citations, and prose. Round 2 went after the proofs
and the rendered submission, and found one genuine correctness error in a
headline-supporting theorem, several missing hypotheses, a definitional defect
in the central parameter, and a submission-blocking anonymization breach in the
venue port. Every item is fixable; the headline compositional result (Thm 5.2)
survives line-by-line verification by two independent checks. Referee
simulation scored the CURRENT draft P(accept at CSF) ~15%; the same simulation
says the honest core "would plausibly clear the bar" once the claims are
reconciled to what is proved.

---

## Findings (severity / verified-by)

### C1. CRITICAL (verified by orchestrator: counterexample + exact numerics).
**Thm 4.1 part (1): the mixture-entropy formula is false as an equality.**
The proof (lines 699-707) computes H(B) + H(C|B) = H(C, B), the joint entropy
of the observation WITH the latent real/filler indicator B, and calls it the
per-element observed entropy. The observed entropy is H(C) = H(rho*D +
(1-rho)*U) = H(C,B) - H(B|C), strictly smaller whenever supports overlap.
Counterexample: D = U, rho = 1/2 gives the formula value n + 1 bits on a
2^n-point alphabet (impossible).
**Exact contamination of the case study (Table 4, abstract, intro,
conclusion):** recomputation reproduces the published numbers to four decimals
under the wrong formula and corrects them as follows (Zipf m = 10^4, rho = 2/3,
effective-alphabet normalizer):
- baseline 0.7174 ("0.72", unaffected)
- homophonic 0.8668 ("0.87", unaffected; sum K = 10,482 = 1.048x space)
- noise-only: paper-formula 0.8807 = published "0.88"; CORRECT 0.8408 (~0.84)
- combined: paper-formula 0.9800 = published "0.98"; CORRECT 0.9350 (~0.94)
The honest headline is "72% to 94% at 1.05x space and 1.5x bandwidth."
**Fix:** restate part (1) as the exact object H_mix = H(rho*D + (1-rho)*U) with
two-sided bounds (concavity gives >= rho*H(D) + (1-rho)*H(U); chain rule gives
<= the same + h_2(rho), equality iff supports disjoint); recompute Table 4 and
every restatement (abstract L87-90 region, intro, conclusion L2126-2128); check
whether the Fig. 5 predicted-line uses the formula (S2 script) at fix time.

### C2. MAJOR (verified by orchestrator: derivation + numerics).
**Thm 4.1 part (3): statement TRUE, proof as written INVALID.** The proof
lower-bounds the denominator by P_mix >= (1-rho)U, which only yields
I_mix <= rho^2 C(D) I_pure / (1-rho); the stated bound omits 1/(1-rho). The
upper bound on P_mix at lines 719-721 is vestigial (used nowhere). The
statement is nonetheless correct via the pointwise inequality
P_theta(c) <= C(D) * P_mix(c), since C(D)*P_mix >= rho*C(D)*P_theta +
(1-rho)*max_c P_theta >= P_theta (using C(D) >= 1). Numerics confirm the
stated bound holds and the (1-rho) version is strictly looser.
**Fix:** one-paragraph proof repair (pointwise bound), delete the vestigial
lines, resolve the D-vs-P_theta definitional seam in C(D).

### C3. MAJOR (verified by argument; flagged independently by referee
personas 2 and 3). **Thm 4.1 part (3) regime honesty + filterable filler.**
C(D) = 2^n max_c D(c) is astronomical in the paper's own sparse-vocabulary
regime (K = 1, |X| << 2^n): the rho^2 bound is then vacuous and the true
dilution is rho, not rho^2 (uniform ambient filler never collides with the
support; the adversary filters by repetition, since real values repeat and
64-bit uniform filler is singleton almost surely). The proof's closing caveat
admits this; the contribution list, abstract, and section 7E restatements drop
the condition. The advertised operating point (R/N = 0.5) sits outside the
protective regime the paper's own Fig. 2 exhibits (rho <= 10^-2).
**Fix:** move the bounded-ratio condition into the theorem statement; add a
remark on repetition-filtering and the in-image-filler variant (filler uniform
on the image, which the trusted machine can sample, restores the mixture
analysis on a common support and interacts with C1's corrected formula); align
the prose restatements.

### C4. MAJOR (verified by orchestrator: counterexample admissible in the
paper's own construction). **Thm 5.1 part (2): MI-preservation equality needs
a missing hypothesis.** With acceptance-predicate output cells (|A(y)| > 1)
and representatives chosen deterministically from c, both outputs are
functions of the same C: taking f_1, f_2 constant gives latent MI = 0 while
I(fhat_1(C); fhat_2(C)) ~ H(C). The correct general statement is the
inequality I(fhat_1(C); fhat_2(C)) >= I(f_1(X); f_2(X)) (the direction the
attack story needs), with equality under canonical outputs (K_out = 1, or
representative choice conditionally independent of the partner map given the
latent pair). Part (3) additionally presumes the adversary estimates on the
LATENT alphabet; with output multiplicity the observed alphabet inflates and
the dimension factor grows accordingly (coarsening is a TV contraction, so a
known partition recovers the latent rate; an unknown partition raises the
constant, not the N-exponent). The realized attack (sec. 6.7) is the
K_out = 1 case, so the empirics anchor the hypothesized version.
**Fix:** add the canonical-output hypothesis to part (2) (equality) and state
the general inequality; state the adversary-alphabet assumption in part (3);
re-scope the "no per-cipher-map parameter, delta included, lowers this rate"
claim as a corollary that quantifies exactly over input-side parameters and
notes the output-multiplicity caveat (it scales the dimension factor linearly,
never the N^{-1/2} exponent, and aggregation recovers the latent rate when the
partition is known or learnable).

### C5. MAJOR (verified by orchestrator against the text). **Property 2 /
delta is defined on the wrong probability space.** Lines 402-407 define delta
as TV to uniform on ambient B^n; any sparse-image construction (all of the
paper's own) has TV ~ 1 - |Im|/2^n ~ 1, so the property as written is
unsatisfiable, while the paper's operational delta-hat (the finite-sample
appendix prices N = Omega(|Im|/delta_0^2)) lives on the image. Thm 3.1 part
(3)'s ambient Fannes bound inherits the mismatch; Remark "two normalizers"
partially mitigates but does not resolve it.
**Fix:** define representation uniformity relative to uniform-on-image (the
seed-conditional support), restate Thm 3.1(3) with d = |Im| and normalizer
log2|Im| (same algebra), keep the ambient statement as the ROM/computational
layer remark. Log as cross-paper item C-11 in
formalism/cross-paper-consistency.md: the same ambient definition is inherited
from towell2026cipher and appears in the spine.

### C6. MAJOR (verified by orchestrator against Table 3 and sec. 6.2).
**Conclusion contradicts the paper's own results.** Lines 2122-2128: "FPR
compounds as p_T^k for AND chains" (the body's central empirical finding is
the ~4e-3 noise floor for k >= 3, reframed as a defender's budget); "33.5
bits/element (root) to 112.9 bits/element (leaf)" (stale: Table 3 has 37.0
root and 7.4-7.5 per map; neither 33.5 nor 112.9 appears anywhere); "72% to
98%" (changes per C1). The abstract's "confirms the theoretical predictions
for FPR compounding" needs "for OR chains; AND chains saturate at a
construction floor".

### C7. CRITICAL for submission (port; found independently by two agents).
**Anonymization breach in venue/csf:** \url{https://github.com/queelius/cipher-maps}
at port line 1168 renders in the PDF (the handle identifies the author and
links the "Anonymous" companion citations). The earlier pdftotext check
missed it because xurl line-breaks the URL across the 2-column layout and the
grep was line-based; NOTES.md's "zero identifying strings" claim is wrong.
**Fix:** anonymized artifact link or "repository withheld for review"; correct
NOTES.md; sweep with line-joined pdftotext (tr -d '\n') henceforth.

### C8. MAJOR (port). **Five rendering overflows:** tab:fpr (49pt), tab:boolean
(40pt), tab:case-study (33pt) lack \resizebox (the earlier check only flagged
boxes > 50pt); two display-math chains in the Assouad proof overflow (port
lines 1062, 1083; split with aligned).

### C9. MINOR cluster (port seams; seam auditor M1-M4 + m1-m5). Section-VI
preamble says "we treat both in this section" two lines before deferring one
facet to Appendix B; Appendix C opens with a dangling "the estimators above";
(p_T, p_F, p_N) are used in sec. 7A before any body definition (definition
moved to Appendix B; add two orienting sentences); contribution 1 points at
sec:composition for FPR compounding that now lives in Appendix B; five
one-line pointer/expansion patches (intro measurement pointer, discussion
Prop pointer, appendix-figure tags, FPR expansion in abstract, Appendix A
orienting sentence).

### C10. NOTES (low). Thm 3.1 part (2) states <= where the proof derives =;
the finite-sample appendix attributes the multinomial L1 rate to
Glivenko-Cantelli (cite the multinomial result instead); Example "homophonic"
does not satisfy Thm 4.2's own hypothesis c >= 1/min_x D(x) (label it a
heuristic partial allocation); Table 3 intermediate row is n = 2 of 5 seeds
(report both values or add a survivorship caveat); add one sentence to Thm 5.2
acknowledging the multinomial TV minimax rate is classical and the new content
is the cipher-map reduction plus the validated constants.

---

## What was verified SOUND (positive findings)

- **Thm 5.2 (Assouad lower bound): correct line by line**, verified twice
  independently (referee persona 2; orchestrator pre-read). Packing validity,
  pairwise TV (2*eps/m)*d_H, Hellinger (4/m)(1 - sqrt(1-eps^2)) <= 4eps^2/m,
  affinity chain with the x <= 1/2 condition, eps = sqrt(m/16N) with the
  N >= m/16 admissibility caveat, final constant e^{-1/2}/16 ~ 0.0379 >= 0.03.
- Thm 3.1 part (3) Fannes application: correct as algebra (the space issue is
  C5, not the inequality); delta <= 1/2 condition stated; linear-not-Pinsker
  intact. K(x) ~ D(x) intact everywhere. Assouad-not-Le-Cam intact.
- Reproducibility plumbing praised by all three completed agents.
- The two-scale frame and the headline rate-plus-irreducibility story SURVIVE
  the fixes; what changes is hypotheses, regime conditions, and the case-study
  numbers (94, not 98).

## Referee simulation (cold, on the built PDF)

QIF theorist: borderline. Statistician: weak reject. Applied cryptographer:
weak reject (and flagged the anonymity breach). Consolidated P(accept) ~15%
AS-IS; single most damaging weakness = Thm 4.1 (parts 1 and 3 jointly
underwrite the two most quotable claims); single best fix = the
claims-to-theorems reconciliation now planned. Full three-persona reviews in
the agent transcript (referee task output).

## Fix plan (ordered)

1. Canonical surgery (C1-C6, C10): restate Thm 4.1(1) two-sided + repair
   4.1(3) proof + regime condition + filler remark; hypothesis + scoping for
   Thm 5.1(2)/(3) + irreducibility corollary; image-based delta definition +
   Thm 3.1(3) restatement; Table 4 recompute (0.72 / 0.87 / 0.84 / 0.94) and
   all restatements (abstract, intro, conclusion); conclusion stale numbers;
   notes cluster. Add the new landmine to the paper CLAUDE.md (mixture
   entropy is H(C), not H(C,B)) and C-11 to cross-paper-consistency.md.
2. Rebuild canonical; verify all landmines; re-run the affected analytic
   table script if any.
3. Re-derive the CSF port per venue/csf/NOTES.md re-application workflow;
   apply port-only fixes (C7 URL, C8 resizeboxes + display splits, C9 seams);
   line-joined anonymization sweep; rebuild.
4. Update .papermill/state.md, pubs record note, and this report's status.

## Venue impact

None on the chosen path. CSF 2027 cycle 1 (projected ~Jul 24, 2026 from the
CSF 2026 pattern Jul 24 / Oct 9 / Jan 29; CFP not yet posted) absorbs a 1-2
day fix round; fallback PoPETs 2027 Issue 2 (Aug 31, 2026 FIRM; notification
Nov 1) unchanged. The fix round is required for EITHER venue.

## Process notes

- Two agents died mid-run on the account monthly spend limit (deep proof
  verifier at ~80 tokens, numerics auditor at ~271). Their briefs were covered
  by orchestrator hand-verification (Thm 4.1 both parts, Thm 5.2, case-study
  exact recompute) plus referee persona 2. Residual unswept: full numeric
  audit of Tables 1-3, the 20NG homophonic figures, and finite-sample example
  values (LOW risk; re-run after the limit is raised if desired).
- Round-1's "C(D) notational seam: cosmetic" call is superseded by C2 (it is
  a real proof gap); round-1's landmine checks remain valid.
