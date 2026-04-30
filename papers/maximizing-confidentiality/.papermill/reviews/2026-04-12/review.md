# Multi-Agent Review Report

**Date**: 2026-04-12
**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing" by Alexander Towell
**Recommendation**: major-revision

## Summary

**Overall Assessment**: The 2026-04-12 revision lands a strong
framing/positioning improvement: the QIF concession is honest, the
Related Work section is substantive, the "two constructions plus an
inherited third" frame is clean in the Introduction, and the
compositional leakage theorem is correctly promoted to headline. The
prior round's critical findings (Thm 3.1 algebraic error with extra
$H^*$ factor; Thm 3.1 part 3 statement-proof mismatch; undefined
`\cipher` command) are resolved.

However, the revision introduced or surfaced two new critical
mathematical errors in the headline contributions: (1) the Pinsker
bridge proof applies Pinsker's inequality in the wrong direction (the
$e \geq 1 - 2\delta^2/n$ bound does not follow from $d_{TV}(Q,U) \leq
\delta$; the correct bound via Fannes is linear in $\delta$, not
quadratic); and (2) the multiplicity construction $K(x) \propto
1/D(x)$ is backwards (the correct classical homophonic prescription is
$K(x) \propto D(x)$; the paper's version makes cipher value
distributions *more* non-uniform, not less). Both errors propagate:
the Pinsker bound appears in the abstract, introduction, contributions
list, and Theorem 3.1; the multiplicity error appears in Theorem 4.2,
Example 5, Table 4, and the introduction bullet list.

The experimental section retains all of the prior round's methodology
gaps (no CIs, no trial counts, no reproducibility pointers,
analytical values presented as experimental) and adds a new numerical
inconsistency: Example 5 / Table 4 "Zipf distribution $D \propto 1/i$,
$m = 10000$, $e \approx 0.59$" does not match the actual Zipf $s=1$
entropy (which gives $e \approx 0.72$); the claimed numbers correspond
to Zipf exponent approximately 1.2, not 1.0.

Finally, Simmons 1979 (homophonic substitution) is claimed to be cited
per the refined thesis, and is in references.bib, but is not `\cite`d
anywhere in main.tex.

**Strengths**:
1. Two-plus-inherited framing is clean and reviewer-defensible in §1
   and the contributions list (source: novelty-assessor, prose-auditor)
2. Related Work section (new §2) is honest, engaging QIF (Smith,
   Alvim) and SSE leakage (Bost/Fouque, Demertzis) (source:
   citation-verifier, prose-auditor)
3. §5 reorder putting correlation leakage first (Thm 5.1 promoted from
   Prop 5.2) is narratively correct (source: prose-auditor)
4. Prior round's critical algebraic error (extra $H^*$ in Eq. 2) is
   fixed (source: logic-checker)
5. Prior round's undefined `\cipher` command is fixed (source:
   format-validator)
6. Paper builds cleanly at 16 pages; fits all candidate venues
   (source: format-validator)

**Weaknesses**:
1. Pinsker bridge proof applies Pinsker in wrong direction; $e \geq
   1 - 2\delta^2/n$ does not follow (source: logic-checker)
2. Multiplicity construction $K(x) \propto 1/D(x)$ is backwards;
   correct direction is $K(x) \propto D(x)$ (source: logic-checker)
3. Example 5 / Table 4 Zipf entropy numbers do not match stated
   distribution (source: methodology-auditor)
4. Simmons 1979 promised in the thesis refinement, not cited (source:
   citation-verifier)
5. Thm 4.1 Fisher information $\rho^2$ claim missing
   distribution-dependent constant (source: logic-checker)
6. Experimental methodology gaps from prior round unresolved: no CIs,
   no reproducibility info, case study values are analytical not
   empirical (source: methodology-auditor)
7. Thm 5.1 sampling model unspecified; "preserves all correlations"
   imprecise (source: logic-checker)
8. Abstract and conclusion still say "three levers" contradicting the
   Introduction's two-plus-inherited framing (source: prose-auditor)

**Finding Counts**: Critical: 2 | Major: 12 | Minor: 13 | Suggestions: 3

---

## Critical Issues

### C1. Pinsker's inequality applied in the wrong direction (source: logic-checker, cross-verified by area chair)
- **Location**: Section 3.3, Theorem 3.1 part (3), proof at lines 421 to 428. Also abstract line 52 to 66, introduction line 97 to 100, contributions #1 line 141 to 146.
- **Quoted text**: "by Pinsker's inequality (which bounds KL divergence from below by squared TV distance), $\TV(Q, U) \leq \sqrt{D_{\mathrm{KL}}(Q \| U) / 2}$. Since $\TV(Q, U) \leq \delta$, we have $D_{\mathrm{KL}}(Q \| U) \leq 2\delta^2$."
- **Problem**: Pinsker gives $D_{KL} \geq 2 d_{TV}^2$ (nats), equivalently $d_{TV} \leq \sqrt{D_{KL}/2}$. This is an upper bound on $d_{TV}$ given $D_{KL}$. The paper concludes the reverse direction: "$d_{TV} \leq \delta$ implies $D_{KL} \leq 2\delta^2$." That implication does not follow from Pinsker. Counterexample: $Q = (1-\delta)U + \delta \cdot \mathbf{1}_{c_0}$ has $d_{TV}(Q, U) = \Theta(\delta)$ but $D_{KL}(Q \| U) = \Theta(\delta \cdot n)$, not $O(\delta^2)$.
- **Suggestion**: Replace the Pinsker step with a Fannes-type inequality: for $d_{TV}(Q, U) \leq \delta \leq 1/2$ on a support of size $2^n$, $|H(Q) - H(U)| \leq \delta \log_2(2^n - 1) + h_2(\delta)$, giving $e \geq 1 - \delta - h_2(\delta)/n$ (linear in $\delta$, not quadratic). Update the abstract, introduction, and contributions list accordingly. This is the paper's headline contribution; it must be mathematically sound.
- **Cross-verified**: Area chair independently verified by direct computation: for $\delta = 0.05, n = 64$, paper's bound gives $e \geq 0.9999$; correct Fannes bound gives $e \geq 0.945$. The gap (5 percentage points of leakage) is material.

### C2. Multiplicity construction $K(x) \propto 1/D(x)$ is backwards (source: logic-checker, cross-verified by methodology-auditor)
- **Location**: Introduction line 113; Section 4.2 lines 524 to 525; Theorem 4.2 proof at lines 538 to 551; Example 5 at lines 562 to 572; Table 4 row 2.
- **Quoted text (§4.2)**: "Assigning $K(x) \propto 1/D(x)$ equalizes the cipher value frequencies, achieving $\delta \approx 0$."
- **Problem**: Under random oracle (no collisions), the cipher value distribution is $Q(v) = D(x)/K(x)$ for the unique $(x, k)$ mapping to $v$. For $Q$ to be uniform, $D(x)/K(x)$ must be constant across $x$, i.e., $K(x) \propto D(x)$, not $K(x) \propto 1/D(x)$. Classical homophonic substitution (Simmons 1979) has it right: heavier elements get MORE representations, so that the per-cipher mass is equalized. The paper's prescription (heavier gets fewer) *concentrates* mass in few cipher cells and makes the distribution *more* skewed. Worked example: $D(a) = 0.9, D(b) = 0.1$. Paper's $K(a) = 1, K(b) = 9$ gives cipher distribution (0.9, 0.011, 0.011, ...). Correct $K(a) = 9, K(b) = 1$ gives uniform (0.1, 0.1, 0.1, ...). The error also appears in the Theorem 4.2 proof, where "$D(x)/K(x) \approx c$ for all $x$" is a plain algebra mistake: $D(x)/(c/D(x)) = D(x)^2/c$, not $c$.
- **Suggestion**: Replace every "$K(x) \propto 1/D(x)$" with "$K(x) \propto D(x)$" in main.tex. Rewrite the Theorem 4.2 proof with the correct construction. Update Example 5 and Table 4 with correctly-computed homophonic entropies. Note: the same error appears in the cipher-maps companion paper (`cipher_maps.tex` lines 187, 338); that paper is outside the current review scope but should be corrected for consistency.
- **Cross-verified**: Area chair independently verified by numerical simulation. For Zipf $s=1$, $m=10000$ with correctly-directed multiplicity on top 100, $e$ reaches approximately 0.93, not 0.77. The paper's backwards construction does accidentally improve $e$ slightly (to approximately 0.80 by spreading mass to more cipher values), but through a different mechanism than flattening.

---

## Major Issues

### M1. Case study Zipf entropy numbers are internally inconsistent (source: methodology-auditor)
- **Location**: Section 4.2 Example 5 lines 562 to 572; Section 7.4 Table 4 row 1 (Baseline).
- **Quoted text**: "A vocabulary of $m = 10{,}000$ words with Zipf distribution $D(x_i) \propto 1/i$ has entropy $H(D) \approx 7.83$ bits, compared to $H^* = \log_2 10{,}000 \approx 13.29$ bits, giving $e \approx 0.59$."
- **Problem**: Zipf with $s = 1$ on $m = 10000$ has $H(D) = 9.53$ bits, giving $e = 0.72$, not 0.59. The claimed 7.83 bits corresponds to Zipf exponent approximately 1.2. The paper's stated "$\propto 1/i$" (exponent 1) does not produce the claimed numbers. The 518-trapdoor number also does not reconcile with standard interpretations of $b = 100$ and $K(x_i) = i$.
- **Suggestion**: Either specify the correct Zipf exponent (e.g., $s = 1.2$) or correct the entropy to match $s = 1$. Propagate the correction through Table 4.

### M2. Thm 4.1 Fisher information $\rho^2$ claim missing distribution-dependent constant (source: logic-checker)
- **Location**: Section 4.1, Theorem 4.1 part (3), proof at lines 496 to 509.
- **Problem**: For mixture $P_{\text{mix}} = \rho P_\theta + (1-\rho) U$, $I^{\text{mix}}(\theta) = \rho^2 \cdot C(P_\theta, U)$ where $C$ is a distribution-dependent constant that can be $\gg 1$ when $P_\theta$ is skewed. The "$\rho^2$" scaling is correct as an asymptotic exponent in $\rho \to 0$, but the leading constant is not universal.
- **Suggestion**: State the theorem as $I^{\text{mix}}(\theta) \leq C(D) \cdot \rho^2 \cdot I^{\text{pure}}(\theta)$ with $C(D)$ depending on $\max_c D(c)/U(c)$, or provide the full mixture Fisher formula.

### M3. Theorem 5.1 sampling model unspecified (sources: logic-checker, methodology-auditor)
- **Location**: Section 5.1, Theorem 5.1 part (3), lines 691 to 694.
- **Problem**: The "$N = O(|Y_1|\cdot|Y_2|/\xi^2)$" rate is correct for i.i.d. samples from the true joint over $Y_1 \times Y_2$. In cipher maps, the adversary observes $(\fhat_1(c_i), \fhat_2(c_i))$ for various $c_i$. For the rate to apply, $c_i$ must be sampled so the pair follows the latent joint. The paper does not specify the sampling distribution ($c$ uniform on $\B^n$ includes out-of-domain; $c$ uniform on $\text{Im}(\enc)$ restricts to in-domain). These give different rates.
- **Suggestion**: Specify the sampling model explicitly. Distinguish "shared $c$ with many evaluations" from "many distinct $c_i$ observed across deployment."

### M4. Theorem 5.1 part (2) "preserves all correlations" is imprecise (source: logic-checker, carry-over from 2026-04-09 m4)
- **Location**: Section 5.1, Theorem 5.1 part (2), lines 689 to 690.
- **Problem**: "Preserves all correlations" has no mathematical definition. The correct statement is that mutual information is preserved: $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X^\ast); f_2(X^\ast))$ where $X^\ast$ is distributed per the relevant pushforward.
- **Suggestion**: Replace with explicit mutual-information preservation statement (prior review made same suggestion; fix not landed).

### M5. Theorem 5.1 part (4) reduces to a trivial fact (source: logic-checker)
- **Location**: Section 5.1, Theorem 5.1 part (4), lines 695 to 698.
- **Problem**: "Non-uniform input gives non-uniform output" for a deterministic function is trivially true. Without a specific rate of non-uniformity propagation, part (4) adds no quantitative content.
- **Suggestion**: Downgrade to a remark, or replace with a quantitative bound linking $I(f_1, f_2)$ to the minimum achievable $\delta_3$.

### M6. Simmons 1979 cited in thesis refinement but not in text (source: citation-verifier)
- **Location**: `simmons1979symmetric` in references.bib; no `\cite` in main.tex.
- **Problem**: The refined thesis (2026-04-12) states "homophonic cites Simmons." Simmons is the classical reference for homophonic substitution; §4.2 opening and Example 5 are natural citation points.
- **Suggestion**: Add `\cite{simmons1979symmetric}` at line 524 (§4.2 opening) and/or line 562 (Example 5).

### M7. Bost and Fouque 2017 venue may be incorrect (source: citation-verifier)
- **Location**: references.bib entry `bost2017thwarting` lines 290 to 296.
- **Problem**: The bib lists CCS 2017 pages 1901 to 1915, but the Bost-Fouque "Thwarting leakage abuse attacks" paper is best known as IACR ePrint 2017/617, not a CCS paper. The cited page range appears to match a different CCS 2017 paper (Bost, Minaud, Ohrimenko).
- **Suggestion**: Verify primary record. If ePrint-only, use `@misc` with note "IACR ePrint 2017/617."

### M8. Abstract and conclusion contradict refined two-plus-inherited framing (source: prose-auditor)
- **Location**: Abstract lines 56 to 58; Conclusion lines 1150 to 1158.
- **Problem**: §1 Introduction and the contributions list correctly say "two constructions we analyze plus a third we inherit"; the abstract and conclusion still say "three levers... and prove how each affects." A reviewer skimming abstract and conclusion will see inconsistency.
- **Suggestion**: Update abstract and conclusion to reflect the two-plus-inherited framing. Trivial fix.

### M9. Experimental methodology gaps unresolved (sources: methodology-auditor, carry-over from 2026-04-09)
- **Location**: Section 7, Tables 1 to 4.
- **Problem**: No sample sizes, no CIs, no trial counts, no reproducibility info. Table 4 "Case Study" values are analytical (computed from formulas), not empirical, but labeled as an experiment. Table 2 AND chain empirical = 0.000 hits the measurement floor without quantifying it.
- **Suggestion**: Add trial counts and CIs. Relabel §7.3 and §7.4 as "Worked Examples" if analytical. Add a reproducibility footnote with commit hash and script link.

### M10. Pinsker bridge is a single-line invocation, not a theorem-level contribution (source: novelty-assessor)
- **Location**: Abstract, Introduction contributions #1, Theorem 3.1.
- **Problem**: Even if the direction error is fixed, the $\delta \to e$ translation is a textbook invocation of Fannes (or Pinsker in the other direction). Claiming it as the top contribution may not clear the novelty bar for a theory venue. The *framing* is valuable; the *theorem* is modest.
- **Suggestion**: Either prove a non-trivial consequence (tightness, composition behavior, achievability under specific constructions), or reframe as "a formal translation enabling the design-space analysis in §4, §5" rather than "the headline contribution."

### M11. Thm 5.1 sample complexity is standard plug-in estimator rate (source: novelty-assessor)
- **Location**: Section 5.1, Theorem 5.1 part (3).
- **Problem**: The "$|Y_1||Y_2|/\xi^2$" rate is standard empirical-distribution-estimation rate. The *insight* (shared-$c$ does not hide the joint) is valuable as framing; the *quantitative bound* has no novel probability content.
- **Suggestion**: Add a matching lower bound (Le Cam / Fano) showing no estimator does better, to lift the result from a statistical rate to an information-theoretic impossibility.

### M12. QIF Related Work paragraph does not address Shannon vs min-entropy (source: prose-auditor, novelty-assessor)
- **Location**: Section 2 lines 184 to 203.
- **Problem**: The paragraph concedes the measure to QIF (good) but does not engage with the canonical Shannon-vs-min-entropy debate that Smith 2009 explicitly pushes. A QIF reviewer's first question: "why Shannon, not min-entropy?"
- **Suggestion**: Add a second QIF paragraph or a Discussion remark: cipher-map systems face a distribution-estimation adversary, not a single-query guessing adversary; Shannon is the appropriate measure for that model; min-entropy is appropriate when a single high-probability query dominates.

---

## Minor Issues

### m1. Q notation overloaded (source: prose-auditor, carry-over from 2026-04-09 m3)
- **Location**: Throughout, especially §3 to §4.
- **Problem**: $Q$ is used for the cipher value distribution but IT convention reserves $Q$ for the reference distribution in $D_{KL}(P \| Q)$. Writing $D_{KL}(Q \| U)$ inverts the mental parsing.
- **Suggestion**: Rename to $P_C$ or $\Pi$.

### m2. §5 opening paragraph buries the narrative hook (source: prose-auditor)
- **Location**: Section 5 opening, lines 655 to 666.
- **Suggestion**: Lead with "marginal $\delta$ is necessary but not sufficient" rather than the two-effect breakdown.

### m3. §5.1 ordering: "Why this matters" should precede the theorem (source: prose-auditor)
- **Location**: Section 5.1, lines 679 to 728.
- **Suggestion**: Lead with the operational takeaway, then theorem, then proof.

### m4. Prelim re-derives standard IT definitions (source: prose-auditor, carry-over from 2026-04-09 m2)
- **Location**: Section 3 lines 301 to 316.
- **Suggestion**: Replace with one sentence pointing to Cover and Thomas 2006.

### m5. §5.2 "Active probing" subsection is informal (source: prose-auditor)
- **Location**: Lines 830 to 865.
- **Suggestion**: Formalize or trim.

### m6. Compression estimator proof is too terse (source: logic-checker)
- **Location**: Section 6.1, lines 893 to 899.
- **Suggestion**: Cite Ziv 1978 / Wyner-Ziv 1989 for the specific bias bound, or weaken to asymptotic.

### m7. Limitations section could add tightness remark (source: prose-auditor)
- **Location**: Section 7 Limitations.
- **Suggestion**: Add fifth bullet on the looseness of the $\delta \to e$ bound.

### m8. Implicit threat model (source: methodology-auditor, carry-over from 2026-04-09 suggestion 4)
- **Location**: §3 and §5.1.
- **Suggestion**: Add explicit threat-model paragraph.

### m9. Compression estimator has no empirical anchor (source: methodology-auditor)
- **Suggestion**: Add a small validation experiment on known-entropy synthetic streams.

### m10. Hyperref bookmark warning at line 519 (source: format-validator)
- **Location**: `\subsection{Multiple Representations ($K > 1$)}`
- **Suggestion**: Use `\texorpdfstring` or remove math from title.

### m11. Paper has zero figures (source: format-validator)
- **Suggestion**: Consider adding a schematic of the trusted/untrusted model.

### m12. 21 uncited bibliography entries (source: citation-verifier)
- **Observation**: Bibliographic hygiene; not visible in compiled PDF.

### m13. `grubbs2018pump` bib entry has wrong venue (source: citation-verifier, carry-over from 2026-04-09 m6)
- **Problem**: Should be HotOS 2017, not "Proceedings of the ACM on Management of Data."

---

## Suggestions

1. **Add cheap min-entropy remark in §7 Discussion** (source:
   novelty-assessor): preempts the canonical QIF reviewer question.
2. **Add entropy-gap column to Table 4** (source:
   methodology-auditor): bits-leaked-per-query is more operational
   than ratios.
3. **Position Thm 5.1 against SSE joint-leakage literature**
   (source: literature-context): cite Kellaris et al. 2016 and Oya
   and Kerschbaum 2021 in §2; one sentence in §5 or §2 about what is
   quantitatively new vs conceptually established.

---

## Detailed Notes by Domain

### Logic and Proofs
The paper has 4 theorems and 1 proposition carrying the technical
contribution. Two theorems (Thm 3.1 part 3, the Pinsker bridge; and
Thm 4.2, the multiplicity construction) have critical mathematical
errors. Thm 4.1 (noise dilution) has a Fisher-info scaling claim that
is correct in direction but missing a distribution-dependent constant.
Thm 5.1 (compositional leakage) is directionally correct but
under-specified in its sampling model and has imprecise language in
part (2); part (4) is trivial. Prop 6.1 (compression estimator) has a
proof that asserts bias direction without a rigorous reduction. The
prior round's critical algebraic errors (extra $H^*$ factor;
statement-proof mismatch in Thm 3.1) are cleanly fixed; the fix
introduced the new Pinsker-direction error.

### Novelty and Contribution
The refined thesis (2026-04-12) is honestly framed: QIF concession is
explicit, granularity is explicitly inherited, FPR compounding is
explicitly inherited. The two retained novelty claims (Pinsker bridge
and compositional leakage) are both present but thin: the Pinsker
bridge is a single-line textbook invocation (and currently incorrect);
the compositional leakage rate is standard plug-in estimator bound.
The *framing* novelty (marginal uniformity is insufficient under
shared variables, parameterized by cipher-map four-tuple) is the real
contribution; the theorem-statements could better reflect that. The
engineering packaging (cost-attached toolkit for $\delta$-reduction)
is the paper's most genuinely useful contribution but is currently
under-claimed.

### Methodology
Theoretical methodology is sound in choice of tools (information
theory, mixture analysis, plug-in estimators) but fails in two
theorem-level instances (Thm 3.1 pt 3 direction; Thm 4.2 construction
direction). Experimental methodology unchanged from prior round: no
statistical rigor, no baselines, reproducibility unclear. New issue:
the case-study numerical example does not match the stated Zipf
distribution. The three "experiments" (Boolean search, FPR compounding,
encoding granularity) are adequate for a theory paper *if labeled as
validation of theoretical predictions*, which the paper does not
explicitly do.

### Writing and Presentation
The 2026-04-12 revision made three substantive prose improvements: the
Introduction framing is now two-plus-inherited (clean); §2 Related
Work is a real addition engaging QIF and SSE; §5 opens with
correlation leakage (the novel contribution). Residual issues:
abstract and conclusion still use the old "three levers" framing
(trivially fixable); §5.1 ordering could better lead with the
operational takeaway; several 2026-04-09 minor items (Q notation,
imprecise "preserves all correlations," informal §5.2 paragraphs) were
not addressed.

### Citations and References
Three of the four highest-priority 2026-04-09 missing references are
now cited: Smith 2009, Alvim 2020, Demertzis 2020, Bost and Fouque
2017 (venue needs verification). Simmons 1979 promised in the thesis
refinement is not actually cited. Oya and Kerschbaum 2021
(search-pattern leakage) remains a gap and is directly relevant to
Thm 5.1's motivation. Twenty-one .bib entries are uncited (cosmetic).
One .bib entry has wrong venue (`grubbs2018pump`).

### Formatting and Production
Paper builds cleanly at 16 pages. Prior critical format issue
(undefined `\cipher`) resolved. All labels and refs resolve. Fits all
candidate venues (TCC, CSF, QIF workshop, USENIX). Two cosmetic
warnings (hyperref bookmark; zero figures).

## Literature Context Summary

The paper's conceptual positioning is correct: it targets the
intersection of QIF (information-theoretic leakage measurement) and
trapdoor-style constructions (cipher maps). The QIF engagement is
substantive; the SSE engagement is partial (Bost/Fouque and Demertzis
cited but Kellaris et al. 2016, Oya and Kerschbaum 2021, Fuller et al.
2017 SoK, Grubbs et al. 2017 HotOS are missing). The specific
cipher-map framing remains distinctive; no 2024 to 2026 work (to the
area chair's knowledge) proposes an equivalent Pinsker-style bridge in
a cryptographic setting. The 20 Newsgroups benchmark remains
non-standard for encrypted search and would benefit from a one-sentence
justification.

## Review Metadata
- Agents used: area chair (this review), logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator. Literature scouts (broad, targeted) could not be launched in this environment; their findings are synthesized from the 2026-04-09 scout output and area chair direct verification against the manuscript.
- Cross-verifications performed: 3 (Pinsker direction: logic-checker + area chair independent calculation; $K(x)$ direction: logic-checker + area chair numerical simulation; Zipf entropy: methodology-auditor + area chair independent calculation).
- Disagreements noted: 0.

---

## Recommendation rationale

Two critical mathematical errors in headline contributions
(Pinsker-direction in Thm 3.1 pt 3; $K(x)$ inversion in Thm 4.2)
together invalidate the main quantitative claims of Sections 3 and 4.
Both are *fixable in revision*: swap Pinsker for Fannes; invert the
$K(x)$ formula. The errors are mechanical, not conceptual. The paper's
conceptual framework (entropy ratio as measure, $\delta$ as operational
handle, two-plus-inherited construction toolkit, compositional leakage
from shared variables) is sound, the QIF positioning is honest, and
the Related Work engagement is substantive. The experimental
methodology gaps and citation gaps are also fixable at moderate cost.

The correct classification is **major-revision**: the critical findings
are in headline material, but the overall architecture of the paper
does not need restructuring. With the two critical fixes, the several
major methodology fixes, and the half-dozen minor tightenings, this
becomes a reasonable submission to a theory venue. Without the fixes,
the paper's main quantitative claims do not hold.
