# Methodology Auditor, Round 6 (2026-05-02)

Checked the experimental and reproducibility content of section 10
("Implementation and Evaluation"), now landed as a top-level section
per the R6 §10 promotion (METH-1 fix).

## Round 5 Findings, Round 6 Status

### METH-1 (was critical, now mostly resolved)

**R5 issue**: section 10 promotion did not land in the manuscript.

**R6 verification**: section 10 "Implementation and Evaluation" exists at
line 1784 with five subsections:
- 10.1 Reference Implementation (line 1797).
- 10.2 Application: Encrypted Search (line 1814).
- 10.3 20 Newsgroups: Boolean Search Validation (line 1853).
- 10.4 Deniability via the Correctness Parameter (line 1917).
- 10.5 Further Empirical Investigations (line 1946).

The 20 Newsgroups subsection has the requested paragraph structure:
Setup, Construction, Single-term queries, Multi-term Boolean queries,
Reproducibility. The deniability subsection contains Proposition 9.4
(now numbered 10.4.1) Bayesian deniability, moved from the old §9.4.

**Resolved on the structural promotion**. **Not resolved on the
experimental rigor** (see METH-N1 through METH-N5 below).

### METH-2 (was major, partially addressed)

**R5 issue**: No confidence intervals on experimental numbers.

**R6 status**: section 10.3 line 1878-1879 acknowledges:
"a single run per cell, no cross-replicate aggregation."
Section 10.3 line 1909-1915 ("Reproducibility") repeats:
"The numbers reported here are from one run; variance characterization
across replicates and against Bloom-filter and SSE baselines at matched
operating points is work in progress."

This is honest but does not solve the underlying problem. PoPETs
reviewers expect at least 10 replicates per cell with reported variance.
A "work in progress" disclaimer without numbers will be a major review
target. Severity: **major** (carry-over).

### METH-3 (was major, addressed)

**R5 issue**: Query distribution unstated.

**R6 verification**: Line 1874 now says:
"Query distribution: uniform over the corpus vocabulary."

**Resolved**, though "uniform" is the strawman; real adversary models
typically use the empirical query distribution or a Zipf approximation.
A reviewer interested in worst-case leakage will ask about
non-uniform query distributions. Severity: **resolved** (with note for
later: METH-N3 below).

### METH-4 (was major, addressed)

**R5 issue**: Library uncited.

**R6 verification**: Line 1789 footnote: `\url{https://github.com/queelius/cipher-maps}`.
Also line 1804 footnote: `\url{https://pypi.org/project/phobic/}`.
**Resolved**, though anonymization will need to strip both before submission.

### METH-5 (was minor, addressed)

**R5 issue**: 5%/90%/5% partition choice unjustified.

**R6 verification**: Line 1869-1873 now justifies:
"The partition reflects the empirical sparsity of keyword presence in
the corpus (mean per-document presence rate $\approx 0.05$ for moderate-
frequency terms); matching $p_T$ to the operational rate places the
construction in the regime where Property 2 ($\delta$-bounded) is most
useful."

**Resolved**. The justification is a soft-pedal of the design choice
to match the empirical sparsity, which is reasonable and now stated.

## New Findings Introduced by R6 (or Discovered on Closer Read)

### METH-N1 (new, major): Construction time inconsistency

Line 1883-1885: "At 5,000 documents, construction completes in 5.9
seconds (843 documents per second). The full 18,266-document index
builds in 25.6 seconds."

Compute: 5000/5.9 = 847 docs/sec at 5K documents.
18266/25.6 = 713 docs/sec at full corpus.

The state file says "700 documents per second" for the published library
benchmarks. The R6 narrative also says "700 documents per second
on the 20 Newsgroups corpus." Cipher-maps section 6.4 (line 1190) says
"700 documents per second on the 20 Newsgroups corpus".

Three different numbers in the manuscript and the state file:
- Section 6.4 line 1190: 700 docs/sec.
- Section 10.3 line 1883: 843 docs/sec (at 5K), implicit 713 at 18K.
- 25.6 sec for 18,266 documents implies 713 docs/sec.

Either the per-document time scales up with corpus size (PHF construction
is super-linear?), or the numbers are inconsistent. **Recommend**
either (a) report the same number consistently, or (b) report both
and note the scaling: "construction time scales approximately linearly
in document count, ranging from 843 docs/sec at 5K to 713 docs/sec at
18K." Severity: **major**.

### METH-N2 (new, major): Single-term FP count vs corpus size

Line 1890-1895: "expected per-document false positives $5000 \cdot p_T = 250$
over $\approx 4{,}840$ true non-matches".

Computing: 5000 documents, $p_T = 0.05$, gives 250 expected FPs per
*query* (not per document). The "per-document" wording is wrong; the
correct phrasing is "per query, false positives = 5000 * 0.05 = 250
documents flagged as containing the queried term but not actually
containing it."

Line 1898: "from 248 single-term to 12 for 3-term AND" appears to be
from the same 5K-document subset (248 ≈ 250). For 3-term AND:
$p_T^3 = 0.05^3 = 1.25 \times 10^{-4}$, times 5000 documents = 0.625
expected FPs. The reported "12 false positives" is far more than
$0.625$, suggesting either:
(a) the single-term and 3-term numbers come from different document
counts (e.g., 3-term over 18K corpus = 18266 * 1.25e-4 = 2.3 FPs ≠ 12),
(b) the queries are not independent (correlated terms inflate FPs),
(c) the cipher Boolean composition does not produce $p_T^k$ FPs
because of the noise injection in the cipher Boolean implementation.

This is a **major** numerical/methodological issue: the single-term to
multi-term FP reduction is the headline empirical result, but the math
doesn't add up under the stated assumptions. Either the experimental
setup has details not captured by the simple $p_T^k$ model, or the
numbers come from non-comparable runs. **Recommend** either:
(a) recompute and report consistently, with explicit corpus size for
each cell, or
(b) reproduce the experiment under a fixed protocol and report the
output.

Severity: **major**.

### METH-N3 (new, minor): "Uniform over the corpus vocabulary"

Real attackers don't query uniformly; they query high-information terms
(rare words, named entities). Uniform is a fair strawman benchmark but
the paper should either:
(a) acknowledge uniform as a baseline, with a note that adversarial
distributions are explored in maxconf, or
(b) report at least one non-uniform distribution (e.g., Zipf with
$s = 1$, or empirical query log).

Severity: **minor** (already noted in METH-3 resolution).

### METH-N4 (new, minor): No baseline comparison

Line 1909-1915: "Bloom-filter baseline at matched FPR for the
20 Newsgroups workload, relating cipher set space cost to a
non-trapdoor baseline at equivalent operating points" is in the
"work in progress" list.

PoPETs reviewers will ask "what is the overhead of the trapdoor relative
to a non-trapdoor baseline?" Without a Bloom-filter strawman at matched
FPR, the empirical claim "cipher maps work in practice" is unmoored
from a comparison anchor. **Recommend** even a single-cell comparison:
"At single-term query, cipher set has FPR 0.05 vs Bloom filter at FPR
0.05 with same memory budget achieving X." Severity: **minor**
(structurally important but fixable in a few hours).

### METH-N5 (new, minor): "Variance characterization ... is work in progress"

Same paragraph (line 1909-1915) lists three other "work in progress"
items: bloom-filter baseline, construction-time scaling beyond 10^5,
and empirical entropy ratio measurement.

Honest disclosure is good, but "work in progress" in a submission
draft is risky. PoPETs reviewers may interpret this as "the experimental
section is incomplete." Either:
(a) trim section 10.5 to a one-paragraph "Limitations" pointer that
forwards to maxconf for the missing experiments, or
(b) do the bloom-filter cell + 3 replicates per cell before submission
(a few hours of work).

Severity: **minor** (presentation-level, but matters for venue).

### METH-N6 (new, suggestion): Reproducibility claim

Line 1909-1915 says "a single command reproduces the table above."
Which table? section 10.3 has no LaTeX `\begin{table}` environment; the
numbers are in prose. **Recommend** either:
(a) add a proper table summarizing the queries × FPs/recall numbers,
or
(b) reword to "reproduces the numbers above" rather than "the table."

Severity: **suggestion**.

### METH-N7 (new, minor): Hardware spec is too thin

Line 1875: "single-thread CPython 3.12, commodity x86_64 desktop."

PoPETs reproducibility checklist asks for: CPU model, RAM, OS, Python
version, library versions (cipher-maps version, phobic version, numpy,
etc.), random seed. Currently only Python version and rough hardware
class. **Recommend** a 3-line table with: CPU model, RAM size, OS,
cipher-maps commit hash, phobic version, random seed. Severity: **minor**.

### METH-N8 (new, suggestion): The "843 docs/sec" headline number

The section 10.3 narrative leads with construction throughput (843
docs/sec) before query latency. PoPETs reviewers care more about query
latency under real workloads (microseconds per query) than construction
throughput. **Recommend** restructure the §10.3 Construction paragraph
to lead with: "Per-query latency: ~X microseconds (single hash
evaluation per cipher map). Construction throughput: 843 docs/sec at
5K, 713 docs/sec at 18K." This puts the operationally meaningful
number first. Severity: **suggestion**.

## Summary

- 0 critical (R5 critical METH-1 §10 promotion is structurally resolved).
- 2 major (METH-N1 construction time inconsistency, METH-N2 multi-term FP count math doesn't check out).
- 1 carry-over major (METH-2 no CIs / single-run aggregation).
- 4 minor (METH-N3 uniform query distribution, METH-N4 no baseline,
  METH-N5 work-in-progress framing, METH-N7 thin hardware spec).
- 2 suggestions (METH-N6 table vs prose, METH-N8 lead with latency).

Net assessment of section 10: structurally promoted (the §10 was the
big METH-1 ask, and that's done), but the experimental content has
arithmetic inconsistencies (METH-N1, METH-N2) that didn't exist before
the promotion (because the old §9.4 paragraphs were briefer). The
promotion exposed the numbers to closer scrutiny and they don't all
add up. This is the trade-off of giving experimental claims more
real estate.

The overall recommendation for METH track is to fix METH-N1 and METH-N2
arithmetic before submission (a few hours), then the remaining minors
can be handled in a polish pass.
