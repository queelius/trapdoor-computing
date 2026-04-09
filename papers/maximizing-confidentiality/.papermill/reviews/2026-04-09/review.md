# Multi-Agent Review Report

**Date**: 2026-04-09
**Paper**: "Quantitative Confidentiality for Cipher Maps" by Alexander Towell
**Recommendation**: major-revision

## Summary

**Overall Assessment**: The paper develops a quantitative confidentiality theory for cipher map systems using the entropy ratio e = H/H* as the central measure, identifies three levers for improving confidentiality, and validates predictions experimentally. The architecture is sound and the encoding granularity analysis is genuinely novel. However, the paper has a critical mathematical error in its central theorem, does not engage with the Quantitative Information Flow (QIF) literature (which has studied the same class of measures extensively), and the experimental section lacks statistical rigor. These issues are all fixable in a revision.

**Strengths**:
1. Clear narrative arc from measure to levers to composition to measurement -- well-organized for a theory audience (prose-auditor)
2. The encoding granularity spectrum (Section 4.3) and its connection to orbit closure are genuinely novel contributions with no direct prior work (novelty-assessor)
3. Honest limitations section (Section 7) that identifies real weaknesses including the averaging nature of Shannon entropy (prose-auditor)
4. The trusted/untrusted model and the "what this paper does not do" framing effectively scope the contribution (novelty-assessor)
5. Experimental results, though thin, successfully confirm the FPR compounding and granularity cost predictions (methodology-auditor)
6. Compact (13 pages) -- a major improvement over the prior 43-page version (format-validator)

**Weaknesses**:
1. Theorem 3.1 equation (2) has an algebraic error: extra H* factor makes the identity trivially wrong (logic-checker)
2. Theorem 3.1 part (3) statement does not match its proof -- two different bounds (logic-checker)
3. No engagement with the QIF literature -- the entropy ratio is a known measure in that field (novelty-assessor, citation-verifier)
4. No Related Work section, which is expected at theory venues (prose-auditor)
5. Experimental section lacks statistical reporting (confidence intervals, sample sizes, trial counts) (methodology-auditor)
6. Undefined LaTeX command \cipher causes compilation errors at three locations (format-validator)

**Finding Counts**: Critical: 1 | Major: 7 | Minor: 9 | Suggestions: 5

---

## Critical Issues

### C1. Theorem 3.1 equation has an algebraic error (source: logic-checker)
- **Location**: Section 3.3, Theorem 3.1, equation (2), line 324. Also appears in Preliminaries, lines 240-241.
- **Quoted text**: `H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) \cdot H^* = H^*(1 - \delta')`
- **Problem**: The identity $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) \cdot H^*$ is incorrect. The correct identity is $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U)$ (without the multiplicative $H^*$ on the KL divergence term). This can be verified directly: for $U$ uniform on $2^n$ elements, $D_{\mathrm{KL}}(Q \| U) = \sum_c Q(c) \log_2(Q(c) \cdot 2^n) = n - H(Q)$, giving $H(Q) = n - D_{\mathrm{KL}}(Q \| U) = H^* - D_{\mathrm{KL}}(Q \| U)$. The erroneous extra $H^*$ factor is a systematic error appearing in both the Preliminaries notation section (line 240) and the theorem statement (line 324). The second form $H^*(1 - \delta')$ is correct if $\delta' = D_{\mathrm{KL}}(Q \| U) / H^*$, but the explicit first equality is wrong.
- **Suggestion**: Fix to $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) = H^*(1 - D_{\mathrm{KL}}(Q \| U)/n)$ in both locations.
- **Cross-verified**: Yes, by methodology-auditor and area chair. Algebraically confirmed by direct computation of $D_{\mathrm{KL}}(Q \| U)$ for uniform $U$.

### C1a. Theorem 3.1 part (3) -- statement/proof mismatch (source: logic-checker)
- **Location**: Section 3.3, Theorem 3.1, part (3), line 335 (statement) vs. lines 350-356 (proof).
- **Quoted text (statement)**: `$e \geq 1 - \delta \cdot \log_2(2^n / \delta)$ for small $\delta$, via Pinsker's inequality`
- **Quoted text (proof)**: `$e \geq 1 - 2\delta^2/n$`
- **Problem**: The proof correctly applies Pinsker's inequality and derives the bound $e \geq 1 - 2\delta^2/n$. But the theorem statement claims $e \geq 1 - \delta \cdot \log_2(2^n / \delta)$, which is a different (weaker) bound and does not follow from the proof. The statement appears to be a vestige of a different derivation path.
- **Suggestion**: Replace the theorem statement with the bound actually derived: $e \geq 1 - 2\delta^2/n$.
- **Cross-verified**: Yes, by methodology-auditor. The proof's derivation chain is correct; only the statement is wrong.

---

## Major Issues

### M1. No engagement with Quantitative Information Flow (QIF) literature (sources: novelty-assessor, citation-verifier)
- **Location**: Throughout, but especially Introduction (lines 69-148) and Section 3.2 (lines 287-309).
- **Problem**: The entropy ratio $e = H/H^*$ is a normalized version of Shannon leakage, a well-studied measure in the QIF literature. Smith (2009, FoSSaCS) defines min-entropy leakage; Alvim et al. (2020, Springer) provide a comprehensive monograph on QIF. The paper presents the entropy ratio as if it were a novel contribution without acknowledging this body of work. A reviewer at IEEE Trans. Information Theory or Designs, Codes and Cryptography will immediately recognize the connection and question the novelty claim.
- **Suggestion**: (1) Add a Related Work section citing Smith (2009), Alvim et al. (2020), and Braun et al. (2009). (2) Reframe contribution 1 as "applying QIF to the cipher map framework with a specific parameter decomposition," not as inventing the measure itself. (3) Justify the choice of Shannon entropy over min-entropy for this setting -- the paper's Discussion already notes that Shannon entropy is an average measure (Limitation 1), but should connect this to the established Shannon-vs-min-entropy debate in QIF.
- **Cross-verified**: Yes, by prose-auditor, who confirms this is primarily a framing/positioning issue rather than a fundamental contribution problem.

### M2. No Related Work section (source: prose-auditor)
- **Location**: Between Section 1 and Section 2.
- **Problem**: Theory venues expect a Related Work section. The paper's "What this paper does not do" paragraph (lines 143-148) excludes ORAM/FHE/simulation-based approaches but does not discuss what others HAVE done. Missing coverage: QIF (Smith 2009, Alvim et al.), SSE leakage quantification (Cash et al. 2015, Fuller et al. 2017 SoK), leakage mitigation (Bost & Fouque 2017, Demertzis et al. 2020 SEAL), and entropy-based security (Dodis & Smith 2005, Bellare, Boldyreva, O'Neill 2007).
- **Suggestion**: Add a 1-page Related Work section after the Introduction covering these four areas and positioning the cipher map approach relative to each.

### M3. Noise dilution theorem assumes K(x) = 1 without stating it (source: logic-checker)
- **Location**: Section 4.1, Theorem 4.1, equation (3), line 399.
- **Quoted text**: `$H_{\mathrm{mix}} = H_b(\rho) + \rho \cdot H(D) + (1 - \rho) \cdot n$`
- **Problem**: The term $\rho \cdot H(D)$ uses the entropy of the query distribution $D$, which equals the entropy of real cipher values only when $K(x) = 1$ (injective encoding). With $K(x) > 1$ (multiple representations, from Section 4.2), the entropy of a real cipher value is $H(Q_{\text{real}}) \geq H(D)$ because the encoding choice adds randomness. Since Section 4.2 (multiplicity) follows Section 4.1 (noise), the implicit assumption is that noise injection is analyzed before multiplicity is introduced. But the theorem does not state this assumption.
- **Suggestion**: Add the assumption "with $K(x) = 1$" to Theorem 4.1, or replace $H(D)$ with $H(Q_{\text{real}})$ and note that $H(Q_{\text{real}}) = H(D)$ when $K(x) = 1$.
- **Cross-verified**: Yes, by methodology-auditor. Confirmed that the interaction between levers is not addressed.

### M4. Fisher information claim lacks rigorous derivation (source: logic-checker)
- **Location**: Section 4.1, Theorem 4.1, part (3), lines 422-433.
- **Quoted text**: `giving Fisher information reduced by a factor of $\rho^2$ relative to observing $D$ directly`
- **Problem**: For a general mixture model $P_{\text{mix}}(c) = \rho \cdot D(c) + (1-\rho) \cdot U(c)$, the Fisher information reduction is not simply $\rho^2$ -- it depends on the ratio $D(c)/P_{\text{mix}}(c)$ integrated over $c$. The $\rho^2$ factor is an approximation valid when $\rho \ll 1$ (so $P_{\text{mix}} \approx U$), but this condition is not stated.
- **Suggestion**: Either (a) provide the full Fisher information calculation, or (b) state the $\rho^2$ factor as an approximation valid for $\rho \ll 1$ with a reference to the Fisher information of mixture models.

### M5. Experimental section lacks statistical rigor (source: methodology-auditor)
- **Location**: Section 6, Tables 1-4, lines 838-958.
- **Problem**: (a) No sample sizes or trial counts reported. (b) No confidence intervals or standard deviations. (c) FPR compounding table (Table 2) shows 0.000 for AND chains at k >= 3, hitting the measurement floor without acknowledging this. (d) Case study (Table 4) values appear to be analytical calculations, not measurements, but are presented in the "Experimental Results" section.
- **Suggestion**: (1) Report sample sizes and number of trials for each experiment. (2) Add confidence intervals to Tables 1-2. (3) Acknowledge the measurement floor in the FPR experiment. (4) Relabel Section 6.4 as "Worked Example" if the values are analytical, or describe the measurement methodology if empirical.

### M6. Missing SSE leakage mitigation references (source: citation-verifier)
- **Location**: Section 4 (Three Levers) and bibliography.
- **Problem**: The noise injection lever (Section 4.1) has a direct parallel in Bost & Fouque (2017, CCS), who propose dummy queries for SSE with formal game-based security analysis. The tunable leakage-functionality trade-off has been studied by Demertzis et al. (2020, USENIX Security, SEAL). Neither is cited.
- **Suggestion**: Cite both in the Related Work section and distinguish the information-theoretic analysis (this paper) from the simulation-based analysis (Bost & Fouque).

### M7. Definition 3.2 lists vestigial constraints never used (source: area chair, self-verification)
- **Location**: Section 3.1, Definition 3.2, lines 271-278.
- **Quoted text**: `system constraints: domain size $|X|$, vocabulary size $|Y|$, query arrival rate $\lambda$, mean query size $\mu_q$, number of agents $k$, and the cipher map parameters $(\eta, \varepsilon, \delta)$`
- **Problem**: The constraints $\lambda$ (arrival rate), $\mu_q$ (mean query size), and $k$ (number of agents) appear only in this definition and nowhere else in the paper. They are vestigial from the old 43-page paper, which included queueing theory analysis. The actual theorems work with single-query entropy or i.i.d. sequences.
- **Suggestion**: Remove $\lambda$, $\mu_q$, and $k$ from Definition 3.2, or add a remark explaining they are included for generality but the current paper analyzes the i.i.d. case.

---

## Minor Issues

### m1. Undefined LaTeX command \cipher (source: format-validator)
- **Location**: Lines 589, 691, 735.
- **Problem**: `\cipher` is used at three locations but never defined in the preamble. The build log confirms `! Undefined control sequence` errors. The PDF renders these locations with garbled output.
- **Suggestion**: Add `\newcommand{\cipher}[1]{\widehat{#1}}` to the preamble (or the appropriate notation convention).

### m2. Preliminaries re-derives standard IT definitions (source: prose-auditor)
- **Location**: Section 2, lines 229-244.
- **Problem**: At a theory venue, the audience knows Shannon entropy, conditional entropy, mutual information, and KL divergence. The 15-line paragraph defining these is unnecessary.
- **Suggestion**: Replace with a single sentence referencing Cover & Thomas (2006).

### m3. Notation conflict: Q used for both cipher distribution and IT convention (source: prose-auditor)
- **Location**: Line 242 and throughout.
- **Problem**: $Q$ typically denotes a reference distribution in IT (as in $D_{\mathrm{KL}}(P \| Q)$). Here it denotes the cipher value distribution, creating momentary confusion in expressions like $D_{\mathrm{KL}}(Q \| U)$.
- **Suggestion**: Consider renaming to $P_C$ or $\Pi$.

### m4. "Preserves all correlations" is imprecise (source: logic-checker)
- **Location**: Proposition 5.1, line 715.
- **Problem**: What is preserved is mutual information (invariant under bijection), not Pearson correlation (which depends on numerical values).
- **Suggestion**: Replace with "preserves mutual information: $I(\hat{f}_1(C); \hat{f}_2(C)) = I(f_1(X); f_2(X))$."

### m5. Informal convergence arguments in Section 5.1 (source: prose-auditor)
- **Location**: Lines 637-659 ("Convergence under deep composition").
- **Problem**: Three paragraphs of qualitative arguments ("noise acts as an attractor," "drowning the signal") without formal statements. Imprecise for a theory paper.
- **Suggestion**: Formalize as a corollary or label as remarks/observations.

### m6. grubbs2018pump bibliographic entry incomplete (source: citation-verifier)
- **Location**: references.bib, entry grubbs2018pump.
- **Problem**: Missing volume, pages, DOI. Venue name may be incorrect.
- **Suggestion**: Update to full citation with correct conference name and metadata.

### m7. Unused bibliography entries (source: citation-verifier)
- **Location**: references.bib, entries sayood2017introduction and mackay2003information.
- **Problem**: These entries do not appear in any `\cite{}` command in the manuscript.
- **Suggestion**: Either add citations where they support claims or remove from bibliography.

### m8. Encoding granularity experiment under-described (source: methodology-auditor)
- **Location**: Section 6.3, Table 3, lines 905-931.
- **Problem**: The 7-function loan approval pipeline is not described: what are the functions, what are their types/output sizes?
- **Suggestion**: Add a brief description of the pipeline structure so readers can verify the space calculations.

### m9. No reproducibility information (source: methodology-auditor)
- **Location**: Section 6, line 843.
- **Problem**: No library version, commit hash, Python version, or pointer to experimental scripts.
- **Suggestion**: Add a footnote with reproducibility details.

---

## Suggestions

1. **Restructure contribution claims** (novelty-assessor): The paper's strongest novel contributions are (a) the parameter decomposition connecting entropy ratio to cipher map parameters, and (b) the encoding granularity spectrum. The individual techniques (noise, multiplicity, compression estimation) are well-known. Reframe contributions accordingly: the unified framework and the granularity theory are primary; the individual technique analyses are secondary.

2. **Expand encoding granularity section** (novelty-assessor): Section 4.3 is the paper's most original contribution but gets less development (~1.5 pages) than the noise injection section (~1 page for a well-known technique). A theorem formally connecting entanglement parameter $p$ to the entropy ratio $e$ would make this contribution self-contained.

3. **Make assumptions explicit** (logic-checker): The paper has implicit assumptions (random oracle model, independent evaluations, K(x) = 1 vs. > 1, i.i.d. queries) that interact across sections. A consolidated assumption block at the beginning of Section 3 would clarify the logical dependencies.

4. **Add explicit threat model** (methodology-auditor): The honest-but-curious adversary model is implied but never stated. For a security-adjacent paper, state: what the adversary observes, what it can compute, and what it tries to learn.

5. **Justify 20 Newsgroups** (literature context): 20 Newsgroups is a text classification benchmark, not a standard encrypted search benchmark (Enron email corpus is standard). The paper should briefly justify why 20 Newsgroups suffices for validating the theoretical predictions.

---

## Detailed Notes by Domain

### Logic and Proofs
The paper contains 4 theorems, 2 propositions, and several informal arguments. The central theorem (Theorem 3.1) has an algebraic error in its main equation and a statement/proof mismatch in part (3) -- both fixable. The noise dilution theorem (Theorem 4.1) is correct under an unstated assumption (K(x) = 1) and has an under-derived Fisher information claim. The FPR compounding theorem (Theorem 5.1) is correct (elementary probability, cited from companion paper). The multiplicity theorem (Theorem 4.2) is correct. The proofs are sketch-level throughout -- acceptable for a theory venue if the statements are correct, which they currently are not in two cases.

### Novelty and Contribution
The entropy ratio is a rediscovery of normalized Shannon leakage from QIF. The individual techniques (noise injection, homophonic substitution, compression estimation) are well-known. The genuinely novel contributions are: (1) the parameter decomposition connecting the entropy ratio to the four cipher map parameters, (2) the encoding granularity spectrum with the entanglement parameter $p$, and (3) the orbit closure connection for dynamic confidentiality. These are sufficient for a theory paper if properly framed.

### Methodology
Theoretical methodology is information-theoretic and largely sound except for the equation errors noted above. Experimental methodology is weak: small scale, no statistics, no baselines, and one "experiment" that appears to be an analytical calculation. For a theory venue, experiments are supplementary and the theoretical contribution carries the paper, but the experimental section should either be strengthened (add statistics) or scaled back (relabel as "illustrative examples").

### Writing and Presentation
Generally clear and well-structured. The paper follows the cipher maps notation consistently. The main structural gap is the missing Related Work section. The Discussion section is strong and honest. Some informal arguments in Section 5 need tightening. The abstract is dense but informative. The paper length (13 pages) is appropriate for the content.

### Citations and References
The bibliography has 25 entries, of which 3 are unpublished companion papers. The critical gap is the QIF literature (Smith 2009, Alvim et al. 2020), which must be cited and discussed at a theory venue. The SSE leakage mitigation literature (Bost & Fouque 2017, Demertzis et al. 2020) should also be cited. One entry (grubbs2018pump) has incomplete metadata. Two entries appear unused in the text.

### Formatting and Production
The paper uses generic article class formatting, appropriate for a draft. The `\cipher` command is undefined, causing compilation errors at three locations. Tables are clean but column alignment is inconsistent. Venue-specific formatting will be needed before submission.

---

## Literature Context Summary

The paper draws on three distinct bodies of work: (1) Searchable Symmetric Encryption (SSE), which uses simulation-based leakage definitions; (2) Quantitative Information Flow (QIF), which uses information-theoretic leakage measures; and (3) the author's own cipher map framework. The paper's approach is closest to QIF but does not cite or discuss it. The encoding granularity spectrum has no direct prior art. The individual leakage mitigation techniques (noise injection, frequency flattening) have been studied in SSE (Bost & Fouque 2017, Demertzis et al. 2020). The benchmark choice (20 Newsgroups) is non-standard for encrypted search (Enron corpus is standard). The paper's main vulnerability at a theory venue is the missing QIF connection; its main strength is the encoding granularity formalization and the cipher map parameter decomposition.

---

## Review Metadata
- Agents used: literature-scout-broad, literature-scout-targeted, logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator
- Cross-verifications performed: 5 (Theorem 3.1 equation x2, Theorem 4.1 assumption, QIF framing, experimental methodology)
- Disagreements noted: 1 (Theorem 4.1 K(x) assumption severity: logic-checker rated MAJOR, cross-verification downgraded to major-with-clarification since the section ordering implies K(x)=1 baseline, but the assumption must still be stated)
