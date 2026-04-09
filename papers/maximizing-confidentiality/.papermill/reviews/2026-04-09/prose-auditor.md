# Prose Auditor Report

**Paper**: "Quantitative Confidentiality for Cipher Maps"
**Date**: 2026-04-09

---

## Overall Assessment

The writing is generally clear, direct, and well-structured. The paper follows the author's stated preference for plain English over notation. The narrative arc (measure -> levers -> composition -> measurement -> experiments) is logical and easy to follow. The main weaknesses are: (1) the paper lacks a Related Work section, which is expected at theory venues; (2) the Preliminaries section re-derives standard definitions unnecessarily; (3) some informal arguments would benefit from tighter language.

**Confidence**: HIGH

---

## Findings

### MAJOR: No Related Work section

**Location**: Between Section 1 (Introduction) and Section 2 (Preliminaries).

**Problem**: The paper has no Related Work section. For a theory venue like IEEE Trans. Information Theory or Designs, Codes and Cryptography, this is expected. The Introduction mentions what the paper does NOT do (no ORAM, FHE, simulation-based security) but does not discuss what others HAVE done in quantifying leakage. The QIF literature, SSE leakage quantification work, and entropy-based security measures are all relevant and should be discussed.

The "What this paper does not do" paragraph (lines 143-148) partially serves this purpose but is framed negatively (what we exclude) rather than positively (how our approach relates to existing work).

**Suggestion**: Add a Related Work section (1 page) after the Introduction that covers: (1) SSE leakage quantification (Cash et al. 2015, Grubbs et al. 2018, and the SoK by Fuller et al. 2017), (2) Quantitative Information Flow (Smith 2009, Alvim et al. 2020), (3) entropy-based security measures (Dodis & Smith 2005, Cachin 1997), and (4) leakage mitigation techniques (Bost & Fouque 2017, Demertzis et al. 2020). Position the cipher map approach relative to each.

### MINOR: Preliminaries re-derives standard IT definitions

**Location**: Section 2, lines 229-244.

**Quoted text**: "Shannon entropy $H(X) = -\sum_x p(x) \log_2 p(x)$ measures the average surprise (in bits) of a random variable; higher entropy means less predictable. Conditional entropy $H(X \mid Y)$ is the remaining uncertainty..."

**Problem**: At a theory venue, the audience knows Shannon entropy, conditional entropy, mutual information, and KL divergence. Defining these from scratch uses ~15 lines that could be spent on more substantive content. The CLAUDE.md instruction says "Don't define standard concepts (entropy, conditional entropy, TV distance) from scratch."

**Suggestion**: Replace the information-theoretic notation paragraph with a single sentence: "We use standard information-theoretic notation from Cover \& Thomas~\cite{cover2006elements}; $H$, $H(\cdot|\cdot)$, $I(\cdot;\cdot)$, and $D_{\mathrm{KL}}$ denote Shannon entropy, conditional entropy, mutual information, and KL divergence, all in bits." This saves 12 lines.

### MINOR: Notation conflict between $Q$ as distribution and $Q$ as cipher value

**Location**: Section 2, line 242 vs. throughout.

**Quoted text**: "We use $D$ for the distribution of queries over the domain $X$, and $Q$ for the induced distribution over cipher values."

**Problem**: The standard use of $Q$ in information theory is as the second argument in $D_{\mathrm{KL}}(P \| Q)$, i.e., a reference distribution. The paper uses $Q$ for the cipher value distribution (the "true" distribution being measured) and $U$ for the reference (uniform). This is not wrong but creates a moment of confusion when reading $D_{\mathrm{KL}}(Q \| U)$ because $Q$ and $U$ are in the "expected" positions for an information-theoretic audience ($Q$ looks like the reference).

**Suggestion**: Consider renaming the cipher value distribution to $P_C$ or $\Pi$ to avoid the notation clash. Alternatively, add a sentence noting the convention.

### MINOR: "Convergence under deep composition" paragraphs are informal

**Location**: Section 5.1, lines 637-659.

**Quoted text**: "Long AND chains converge toward False (or noise). [...] Dually, long OR chains converge toward True (or noise). [...] In both cases, noise acts as an attractor..."

**Problem**: These three paragraphs make qualitative arguments about convergence without formal statements. The language ("noise acts as an attractor," "drowning the signal") is evocative but imprecise for a theory paper. What exactly converges? The output distribution? The FPR? The entropy? "Noise acts as an attractor" is a metaphor, not a mathematical statement.

**Suggestion**: Either formalize these observations as a corollary (e.g., "Corollary: For a chain of $k$ independent AND operations with base FPR $p_T$, the probability of a True output converges to 0 as $k \to \infty$") or label them as remarks/observations rather than leaving them as unmarked prose between formal results.

### MINOR: Abstract is well-written but dense

**Location**: Abstract, lines 46-65.

**Problem**: The abstract packs in the entropy ratio definition, three levers, four parameters, composition analysis, compression estimation, and experimental validation in 19 lines. Each item gets about 1.5 lines. For a reader unfamiliar with cipher maps, the abstract may be overwhelming. The opening sentence ("A cipher map is a total function on bit strings...") does good work establishing the concept, but the subsequent enumeration of contributions is very compressed.

**Suggestion**: Consider splitting the abstract into two parts: (1) context and problem (what is a cipher map, why confidentiality matters), (2) contributions (what this paper does). This would improve readability without increasing length.

### SUGGESTION: Section headers could be more informative

Current: "Three Levers for Improving Confidentiality" (Section 4).
Better: "Three Levers: Noise, Multiplicity, and Granularity" -- tells the reader what's coming.

Current: "Compositional Confidentiality" (Section 5).
Better: "Confidentiality Under Composition" -- active voice.

### SUGGESTION: The Discussion section is strong

The Discussion (Section 7) is one of the paper's best sections. The open questions are genuine and well-framed (adaptive K(x), tight composition bounds, beyond Boolean search). The Limitations subsection is honest and specific. This is good practice and should be preserved through revisions.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 1 | No Related Work section |
| Minor | 4 | Standard IT definitions, $Q$ notation clash, informal convergence arguments, dense abstract |
| Suggestion | 2 | Section headers, preserve Discussion |
