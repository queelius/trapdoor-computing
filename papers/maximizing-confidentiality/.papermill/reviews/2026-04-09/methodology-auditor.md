# Methodology Auditor Report

**Paper**: "Quantitative Confidentiality for Cipher Maps"
**Date**: 2026-04-09

---

## Overall Assessment

The paper combines theoretical development with experimental validation. The theoretical methodology is information-theoretic and largely sound in structure. The experimental methodology has significant gaps: small scale, no statistical reporting, no baselines, and limited reproducibility information.

**Confidence**: HIGH

---

## Findings

### MAJOR: Experimental scale is too small for the claims

**Location**: Section 6 (Experimental Results), Tables 1-4, lines 838-958.

**Problem**: The experiments use:
- 5,000 documents (Table 1) from a corpus of 18,266
- 150 inputs (Table 3: 30 applicants x 5 loan amounts)
- No stated number of trials, no confidence intervals, no standard deviations

For a paper targeting IEEE Trans. Information Theory or Designs, Codes and Cryptography, the experimental section needs either (a) larger-scale experiments with statistical rigor, or (b) a clear statement that the experiments are illustrative examples validating theoretical predictions, not comprehensive empirical studies.

The FPR compounding experiment (Table 2) shows 0.000 for AND chains at k=3,4,5, which suggests the sample size is too small to observe the predicted theoretical values ($0.05^3 \approx 10^{-4}$, requiring ~10,000+ trials to observe even one event with $p_T = 0.05$, $k=3$). The "Ratio" column shows "---" for these entries, confirming the measurement floor was hit. This is not a validation failure but should be acknowledged.

**Suggestion**: (1) Report sample sizes and number of trials. (2) For the FPR experiment, either increase the trial count or explicitly state the measurement resolution. (3) Add confidence intervals to the FPR and precision/recall numbers.

### MAJOR: No baselines or comparative evaluation

**Location**: Section 6, all experiments.

**Problem**: All experiments validate the cipher map framework against its own predictions. There is no comparison with:
- Other encrypted search systems (SSE schemes with known leakage profiles)
- Alternative confidentiality measures (min-entropy, guessing entropy)
- Standard benchmarks (Enron corpus, synthetic data with controlled distributions)

For a systems-oriented venue this would be fatal. For a theory venue, internal consistency validation is acceptable, but the paper should explicitly acknowledge the absence of external baselines and explain why internal validation suffices.

**Suggestion**: Add a paragraph in Section 6 or Discussion (Section 7) explaining that the experiments validate theoretical predictions (internal consistency) rather than comparing against alternative systems. Acknowledge that comparative evaluation against SSE schemes with known leakage would strengthen the empirical contribution.

### MAJOR: Case study methodology unclear

**Location**: Section 6.4 (Case Study), Table 4, lines 933-957.

**Quoted text**: "We demonstrate the three levers on a system with vocabulary $m = 10{,}000$ and Zipf-distributed queries."

**Problem**: Table 4 shows entropy ratio values (0.59, 0.77, 0.72, 0.85) but does not explain how these were computed. Were they computed analytically from the formulas in Sections 3-4? Or were they measured empirically? If analytical, they validate the formulas, not the system. If empirical, what experimental setup was used?

The "Baseline" entry $e = 0.59$ matches the calculation in Example 4.1 ($H(D) \approx 7.83$, $H^* \approx 13.29$, $e \approx 0.59$), suggesting these are analytical values, not measurements. If so, calling this an "experiment" is misleading.

**Suggestion**: Clarify whether Table 4 values are analytical or empirical. If analytical, relabel Section 6.4 as "Worked Example" rather than a case study within the experimental section.

### MINOR: Reproducibility gaps

**Location**: Section 6, line 843.

**Quoted text**: "We validate the theoretical predictions using the cipher-maps Python library."

**Problem**: No version number, commit hash, or release tag for the library. No hardware/timing information. No link to specific experimental scripts. For reproducibility, the paper should provide enough information to re-run the experiments.

**Suggestion**: Add a footnote or subsection with: library version/commit, Python version, hardware (if timing matters), and pointer to the experimental scripts within the repository.

### MINOR: Encoding granularity experiment design

**Location**: Section 6.3, Table 3, lines 905-931.

**Problem**: The experiment uses a toy example (loan approval pipeline, 30 applicants x 5 amounts = 150 inputs, 7 functions). While illustrative, the pipeline structure is not described: what are the 7 functions? What are their types? The "Bits/elem" column shows 33.5, 64.2, 112.9 for root/intermediate/leaf, which demonstrates the cost spectrum. But without knowing the pipeline structure, the reader cannot verify whether 33.5 bits/element is reasonable for a 7-function pipeline.

**Suggestion**: Describe the 7-function pipeline briefly (e.g., "income check, credit score, DTI ratio, ...") and state the output type sizes so the reader can verify the space calculations.

### SUGGESTION: State the threat model explicitly

The paper assumes the untrusted machine is honest-but-curious (it evaluates cipher maps faithfully but tries to learn from observations). This is implied but never stated. For a security-adjacent paper, the threat model should be explicit: what does the adversary observe? What can it compute? What is it trying to learn?

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 3 | Small-scale experiments without statistics, no baselines, case study methodology unclear |
| Minor | 2 | Reproducibility gaps, encoding granularity experiment under-described |
| Suggestion | 1 | Explicit threat model |
