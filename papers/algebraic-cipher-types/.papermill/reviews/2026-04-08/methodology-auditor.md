# Methodology Auditor Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Auditor**: methodology-auditor

## Summary

The paper contains experimental results in Section 6 (Discussion): a Boolean search evaluation, FPR compounding analysis, and an encoding granularity comparison. The experimental methodology is thin -- the results serve as proof-of-concept demonstrations rather than rigorous evaluations. For a workshop paper, this is borderline acceptable, but several gaps should be addressed.

---

## 1. Boolean Search Experiments (Table 1)

### Setup
- 20 Newsgroups corpus (18,266 documents, 58,903 unique words)
- Evaluation on 5,000 documents
- n = 8 bits, |T| = 13, |F| = 230
- p_T = 0.05 (false positive rate)
- Construction rate: 843 documents/second

### Issues

**Major: No baseline or comparison.** The table shows precision and recall for Boolean cipher search but does not compare against:
- Plaintext Boolean search (expected precision 1.0, recall 1.0)
- Alternative encrypted search schemes (SSE, ORAM-based)
- A simple Bloom filter approach

Without a baseline, the reader cannot assess whether p=0.39 precision for a single term is acceptable, expected, or poor.
**Severity**: Major. **Confidence**: High.

**Major: No error bars or confidence intervals.** The precision and recall values are point estimates. With 5,000 documents and stochastic cipher map construction (seed search), there is inherent variance. Are these from a single run? Multiple runs? What is the standard deviation?
**Severity**: Major. **Confidence**: High.

**Minor: Why 5,000 of 18,266 documents?** The corpus has 18,266 documents but only 5,000 are used for evaluation. Is this a random sample? The first 5,000? All from one newsgroup? The selection criterion affects the results.
**Severity**: Minor. **Confidence**: Medium.

**Minor: Query selection not described.** "Representative Boolean queries" -- which terms? How were they chosen? A reproducible experiment would specify the exact queries.
**Severity**: Minor. **Confidence**: High.

**Minor: 843 docs/sec throughput.** This number is stated without context. Is this fast or slow? What hardware? Is this construction time or query time? For a workshop paper, a brief hardware description (CPU, RAM) would suffice.
**Severity**: Minor. **Confidence**: Medium.

**Suggestion: The OR recall of 0.97 and OR AND NOT recall of 0.88 need explanation.** The paper attributes this to noise propagation, which is plausible, but the specific mechanism (noise values causing documents to drop from results) should be quantified: what fraction of the recall loss is due to noise vs. FPR compounding?

---

## 2. FPR Compounding Analysis

### Setup
The paper reports that the Bernoulli model predicts FPR_AND,k = p_T^k for k independent AND operations, and that empirically:
- OR chains match theory (ratio ~0.9 across chain lengths 1-5)
- AND chains diverge at depth > 2: empirical FPR exceeds p_T^k by an order of magnitude at k=3

### Issues

**Major: No data table or graph.** This is the most interesting experimental finding in the paper -- the independence assumption breaks for cipher map composition -- but it is presented only in prose. A table showing predicted vs. empirical FPR for chain lengths 1-5, for both AND and OR, would be far more convincing.
**Severity**: Major. **Confidence**: High.

**Major: "Order of magnitude" is imprecise.** What are the actual numbers? If p_T = 0.05, then p_T^3 = 0.000125. An "order of magnitude" higher would be ~0.00125. Is the empirical value 0.001? 0.01? The difference matters for practical implications.
**Severity**: Major. **Confidence**: High.

**Minor: Attribution of the divergence.** The explanation (cipher Boolean AND is a deterministic cipher map, so feeding its output into another AND is not an independent draw) is plausible and important. But the paper should distinguish between two effects: (a) the cipher map is deterministic for a given seed, and (b) the output distribution after one AND is not uniform over T union F (it is biased toward F). Effect (b) alone could explain the divergence without invoking (a).
**Severity**: Minor. **Confidence**: Medium.

---

## 3. Encoding Granularity Comparison

### Setup
- 7-function loan approval pipeline
- 150 inputs
- Three granularity levels: root (1 cipher map), intermediate (3 groups), leaf (7 nodes)

### Issues

**Major: Missing space data.** The table shows "---" for the space column at intermediate and leaf levels. This is the most interesting dimension of the comparison (the space/confidentiality trade-off). Why is this data missing?
**Severity**: Major. **Confidence**: High.

**Minor: 150 inputs is very small.** A loan approval pipeline with 150 inputs is a toy example. The domain is small enough that the root-level cipher map (which stores the entire function) is trivially small (694 bytes). The comparison is not informative about scaling behavior.
**Severity**: Minor. **Confidence**: High.

**Minor: "Zero errors on full domain" is expected.** For a PHF-backed construction with seed search, zero errors on the construction domain is guaranteed by construction (the seed is chosen to produce zero errors). This should be stated as expected, not as a result.
**Severity**: Minor. **Confidence**: High.

**Suggestion**: The 650x speed difference (root vs. leaf) is striking but explained by the different backends (PHF vs. seed search). This comparison conflates the granularity trade-off with the construction algorithm trade-off. A fair comparison would use the same construction method at each level.

---

## 4. Reproducibility

**Major: Missing implementation details.** The paper mentions "cipher-maps, Python with PHF backend via phobic" but provides no:
- Repository URL or version
- Python version
- phobic library version
- Hardware specification
- Random seed or method for reproducibility

For a workshop paper, at minimum a URL to the implementation should be provided.
**Severity**: Major. **Confidence**: High.

**Minor: 20 Newsgroups not formally cited.** The 20 Newsgroups dataset (Mitchell, 1997 / Lang, 1995) should be cited with a standard reference. It is mentioned by name but not referenced.
**Severity**: Minor. **Confidence**: High.

---

## 5. Statistical Rigor

The experiments are presented as demonstrations, not as statistically rigorous evaluations. For a workshop paper, this is partially acceptable, but:

- Claims about FPR compounding should include confidence intervals or at least multiple random seeds
- The Boolean search table should indicate whether results are from single or averaged runs
- The "order of magnitude" divergence claim needs quantification

**Overall methodology severity**: The experiments are sufficient as proof-of-concept for a workshop paper, but not for a full conference paper. The FPR compounding finding is the most interesting and most underserved by the current presentation.
