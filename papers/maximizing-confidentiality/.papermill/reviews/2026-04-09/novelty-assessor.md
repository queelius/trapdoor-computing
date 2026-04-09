# Novelty Assessor Report

**Paper**: "Quantitative Confidentiality for Cipher Maps"
**Date**: 2026-04-09

---

## Overall Assessment

The paper's primary contribution is applying information-theoretic confidentiality measurement to the specific cipher map framework. The encoding granularity spectrum and its connection to orbit closure are genuinely novel. However, the paper's central measure (entropy ratio) is a rediscovery of normalized Shannon leakage from the Quantitative Information Flow (QIF) literature, and the individual techniques (noise injection, homophonic substitution) are well-known. The paper does not engage with QIF, which is a significant gap for a theory venue.

**Confidence**: HIGH

---

## Findings

### MAJOR: Entropy ratio is a known measure in QIF literature

**Location**: Section 3.2, Definition 3.3 (Entropy ratio), lines 289-296.

**Quoted text**: "The entropy ratio of a cipher map system is $e = H/H^* \in [0, 1]$."

**Problem**: The entropy ratio $e = H/H^*$ is a normalized version of Shannon entropy, equivalent to $1 - L/H^*$ where $L = H^* - H$ is the Shannon leakage. This is a standard measure in the Quantitative Information Flow (QIF) literature, studied extensively by Smith (2009, FoSSaCS), Alvim et al. (2012, CSF), and the comprehensive monograph by Alvim et al. (2020, Springer). The paper presents this as if it were a novel contribution without acknowledging the existing body of work.

The QIF literature has also extensively debated the choice of Shannon entropy vs. min-entropy vs. guessing entropy as leakage measures. Shannon entropy (used here) averages over all outcomes and can miss worst-case vulnerabilities. Min-entropy captures the most vulnerable element. The paper's Discussion section (Section 7) acknowledges the averaging limitation (point 1: "The entropy ratio is an average measure; it does not bound the leakage of any specific query") but does not connect this to the established debate in QIF.

**Suggestion**: Add a Related Work section or expand the Introduction to explicitly connect the entropy ratio to Shannon leakage in QIF. Acknowledge that the measure itself is not new; the novelty is applying it to cipher map systems with the specific parameter decomposition (Theorem 3.1). Justify the choice of Shannon entropy over min-entropy for this setting (e.g., because cipher maps have many elements and the adversary faces a distribution estimation problem, not a single-element guessing problem).

### MAJOR: Individual techniques are well-known

**Location**: Section 4 (Three Levers), all subsections.

**Problem**:
- **Noise injection** (Section 4.1): Adding dummy queries to hide real ones is a standard technique in SSE. Bost & Fouque (2017, CCS) propose exactly this with formal security analysis. The paper's information-theoretic analysis of noise injection is a valid contribution but should acknowledge the technique's prior existence in SSE.
- **Multiple representations** (Section 4.2): This is classical homophonic substitution (Simmons 1979, cited). The paper acknowledges this but the theorem (Theorem 4.2) is primarily a formalization of the well-known idea that assigning representations proportional to 1/frequency equalizes output frequencies.
- **Compression-based entropy estimation** (Section 5.1): Using compression as entropy estimation is textbook (Shannon source coding theorem). The paper correctly attributes this to Shannon but presents it as a contribution (Proposition 5.1) when it is a direct application.

**What IS novel**: The packaging of these three techniques as "levers" parameterized by the cipher map framework, with explicit cost/benefit trade-offs in terms of $(\eta, \varepsilon, \delta, \mu)$. The unified treatment is a legitimate contribution even if the individual techniques are known.

**Suggestion**: Restructure the contribution claims. Instead of claiming the techniques as contributions, claim the unified framework that connects them to cipher map parameters. The contribution is the parameter decomposition, not the techniques themselves.

### MINOR: Encoding granularity is the strongest novel contribution but is under-developed

**Location**: Section 4.3 (Encoding Granularity), lines 500-572.

**Problem**: The encoding granularity spectrum (root/intermediate/leaf) and its connection to orbit closure confidentiality bounds is the paper's most original contribution. No prior work frames the correlation-hiding/functionality trade-off as a formal spectrum parameterized by an entanglement parameter $p$. However, this section is relatively brief (about 1.5 pages) compared to the noise injection and multiplicity sections (which formalize well-known ideas). The paper's strongest novelty claim gets the least development.

**Suggestion**: Expand Section 4.3 with a theorem that formally connects the entanglement parameter $p$ to the entropy ratio $e$. Currently, the granularity section relies on citing the companion papers rather than developing its own result. A theorem of the form "for entanglement parameter $p$, the mutual information leaked to the adversary is bounded by..." would make the contribution self-contained and strengthen the paper's strongest novelty claim.

### MINOR: FPR compounding is standard probability

**Location**: Section 5.1 (Error Compounding), Theorem 5.1, lines 603-613.

**Problem**: The FPR compounding formulas ($p_T^k$ for AND, $1-(1-p_T)^k$ for OR) are elementary probability (independence of events). The paper cites this from the companion paper [towell2026cipher]. The novelty is the *interpretation* in terms of confidentiality (AND reduces noise, OR increases it), not the formulas themselves. The paper handles this well in the discussion paragraphs following the theorem, but should be careful not to overclaim.

### SUGGESTION: Clarify the paper's contribution hierarchy

The paper lists four contributions in the Introduction. A clearer hierarchy would be:
1. **Primary**: The parameter decomposition -- connecting entropy ratio to $(\eta, \varepsilon, \delta, \mu)$ (Theorem 3.1, novel in this framework)
2. **Primary**: Encoding granularity spectrum and orbit closure connection (Section 4.3, genuinely novel)
3. **Secondary**: Unified three-lever framework with cost/benefit analysis (Section 4, packaging of known techniques)
4. **Secondary**: Compositional confidentiality analysis (Section 5, novel application of standard tools)
5. **Tertiary**: Experimental validation (Section 6, confirmatory)

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 2 | Entropy ratio is known in QIF (unacknowledged), individual techniques are standard |
| Minor | 2 | Encoding granularity under-developed, FPR compounding is standard |
| Suggestion | 1 | Restructure contribution hierarchy |
