# Methodology Auditor Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Round 7 delta focus: §10.6 (Codec Security: Direct Membership-Inference
Study). Verify experimental design, statistical rigor, reproducibility,
and consistency with the formal claims.

## MAJOR FINDINGS

### METH-1: §10.6 single-run results lack replication and variance characterization

**Location**: §10.6 line 2483, "All numbers below are single-run (no
replicates)."

**Quoted text**:
> "Train and test sets are 5000 each at balanced class prior; AUC is
> Mann-Whitney $U$ with tie correction. All numbers below are
> single-run (no replicates)."

**Problem**: Five tables and three quantitative claims (24/25 in CI,
mean Bayes gap -0.0004, 42× TV reduction) are based on single runs.
The use of Wilson 95% CI on per-cell empirical proportions (each cell
has n=5000) gives one source of variance; but variance across
independent randomizations of the codec construction or the test
sample is not captured. The "24/25 in CI" statistic is informative but
limited.

**Suggestion**: For the headline claims (Le Cam tightness, 42× TV
reduction, coincidence-oracle accuracy), run at least 3 replicates
with different random seeds and report mean ± std across replicates.
This is roughly 10× the current compute (~100 seconds based on the
RESULTS_14 elapsed=10.3s scale) and would substantively strengthen
the reproducibility claims. Even one replicate would help triangulate
the "24/25 inside CI" finding.

### METH-2: No baseline comparison to Bloom filters at matched FPR for the codec sweep

**Location**: §10.6 entire subsection.

**Problem**: The Le Cam tightness study compares attacker accuracy
across five acceptance predicates, but does not include a Bloom-filter
baseline. The novelty claim ("Bloom filters become cipher maps with
$K(x) = 1$, Property 2 degenerate, etc.") would be strengthened by a
direct comparison cell showing where Bloom sits on the (TV, L) Pareto
frontier. This is the same METH-N4 item from R6 minor backlog.

**Suggestion**: Add a "Bloom" row to Table `tab:le-cam-tight` at
matched $\varepsilon$ (false-positive rate), showing the TV gap that
Bloom achieves (likely worse than Huffman, since Bloom does not shape
the acceptance partition). Even a one-cell comparison would close the
"how does this compare to the baseline" reviewer question.

### METH-3: §10.6 (TV, L) Pareto frontier 14 configurations are not enumerated

**Location**: §10.6 line 2524-2527, "Across 14 configurations covering
$|Y| \in \{4, 6, 8\}$, $n \in \{4, 6\}$, and four $p_y$ shapes
(uniform, Zipf, two-mode, heavy-tail)".

**Problem**: 14 configurations under $|Y| \in \{4,6,8\} \times n \in
\{4,6\} \times \text{4 shapes}$ would be $3 \times 2 \times 4 = 24$
full combinations, not 14. The 14 likely reflects feasibility filtering
(e.g., some $(|Y|, n)$ combinations have insufficient codeword budget
for some shapes), but the filtering criterion is not stated, and the
14 are not enumerated. Without the configuration list, the
"7 of 14 Huffman is not TV-optimal" finding cannot be replicated.

**Suggestion**: Supplementary table listing the 14 configurations and
per-cell TV gap (Huffman vs TV-min). Could be in an appendix.

### METH-4: §10.3 20 Newsgroups benchmarks remain single-run (carry-over)

**Location**: §10.3 line 2333-2335, "Numbers below are wall-clock from
the published library benchmarks in the examples/ subdirectory; a
single run per cell, no cross-replicate aggregation."

**Problem**: Carry-over from R6 (METH-2). 20 Newsgroups benchmarks are
single-run. Throughput, precision, recall numbers all lack variance
characterization.

**Suggestion**: For at least the headline numbers (713 docs/sec full
corpus, 0.39 precision, 12 FPs at 3-term AND), run 3 replicates and
report mean ± std. Even one replicate triangulates the single-run
numbers.

### METH-5: §10.6 attacker class comparison "ties" needs sample-size justification

**Location**: §10.6 line 2486-2492.

**Quoted text**:
> "Train and test sets are 5000 each at balanced class prior;... All
> three attackers achieve the same accuracy to within 0.014 sampling
> noise"

**Problem**: 0.014 is approximately the 95% CI half-width for n=5000
at balanced prior. The "tie" claim is therefore "the three attackers
agree to within statistical resolution at this sample size". With
larger n, the attackers might or might not separate. The claim should
be sharpened to "indistinguishable at n=5000" rather than implying
they are equivalent in some structural sense.

**Suggestion**: Reword to "the three attackers are statistically
indistinguishable at n=5000 (95% Wilson CI half-width 0.014); at the
codomain size $|Y|=8$ used here, the feature space saturates and all
three reduce to per-value majority vote." Add: "Larger codomains
would re-separate the classes; see future work."

## MINOR FINDINGS

### METH-MIN-1: §10.6 Setup paragraph compresses many details into one paragraph

The Setup paragraph (lines 2469-2484) covers build set, codomain,
distribution, cipher value space, six predicates, three attackers,
train/test sizes, evaluation metric, and replication policy. This is
information-dense to the point of unreadability. Break into 3-4
subparagraphs.

### METH-MIN-2: §10.6 codec naming is inconsistent

"Dense($\alpha_y = 1/|Y|$)", "Padded variants", "Huffman from $p_y$ at
$n = 4$", "AntiHuffman from $p_y$". The Dense codec is parameterized
by an arithmetic constraint, the Padded codecs by a default-value
choice, the Huffman by data plus cipher-value-space size. Naming
convention is inconsistent. Suggested fix: name each codec by its
underlying allocation principle (Uniform vs Huffman vs Anti-Huffman)
and parameterize each by $(|Y|, n, \text{padding})$.

### METH-MIN-3: §10.6 "Padded (default = $y_7$)" appears only in table, not in setup

The Setup paragraph mentions "two Padded variants with default values
$y_0$ and $y_7$" but Table `tab:le-cam-tight` only shows "Padded
(default = $y_7$)". The $y_0$ variant is missing. Likely an oversight
or the variant was dropped from this table. Confirm and document.

### METH-MIN-4: §10.6 randomized encoding numbers "at $n = 5$ ... 0.543" needs the codec

Line 2581-2582: "At $n = 4$ with the Huffman partition: canonical
encoding gives pattern-coincidence accuracy 1.000 at $t = 4$, while
randomized encoding reduces it to 0.699. At $n = 5$, the reduction is
to 0.543." The $n=5$ codec is presumably also Huffman, but the
sentence reads ambiguously. Confirm.

### METH-MIN-5: §10.6 Key-feature attacker characterization is thin

Table `tab:scope-keys` reports key-feature attacker accuracy of 0.997
on modular keys. What does the attacker actually compute? "An
empirical study of three key-universe configurations" doesn't specify
the attacker's algorithm. Add one sentence describing the key-feature
attacker (e.g., "logistic regression on the bit representation of the
encoded query c").

### METH-MIN-6: §10.6 Pareto frontier claim "Huffman is always on the Pareto frontier (14/14)" needs a precise definition

A point $(L, \text{TV})$ is on the Pareto frontier if no other
feasible point dominates it (lower or equal L AND lower or equal TV,
strictly lower in at least one). The "Huffman is on the frontier" claim
needs the enumeration of feasible points to be verified. With integer
codeword lengths and Kraft constraint, the feasible set is finite. The
14/14 claim is plausible but needs the explicit Pareto check, not just
the comparison to TV-min.

### METH-MIN-7: §10.3 (carry-over) test query distribution still single-uniform

Line 2330: "Query distribution: uniform over the corpus vocabulary."
R5 METH-3 flagged this. Still uniform. For an encrypted-search
workload, query distributions are typically Zipfian or skewed by user
intent. The uniform-query result is the "strawman best case" for the
construction. Acknowledge this explicitly.

## SUGGESTIONS

### METH-SUG-1: Add a §10.7 "Reproducibility and Limitations"

Consolidate all the reproducibility caveats (single-run, no Bloom
baseline, uniform query distribution, missing variance,
saturation-assumption limits) into one subsection at the end of §10.
This is cleaner than scattering them across paragraphs.

### METH-SUG-2: Move detailed setup tables to an appendix

§10.6 has 4 tables in close succession. Moving 2 of them (e.g.,
`tab:scope-keys` and the codec enumeration) to an appendix would
reduce density in the main text without losing information.

### METH-SUG-3: Run the codec sweep at a larger $|Y|$ to test scaling

The current sweep uses $|Y| = 8$. Doubling to $|Y| = 16$ or $32$
would test whether the Le Cam tightness holds at larger codomain
sizes (which is where the attacker classes might separate, per
METH-5).

## Summary

- Critical: 0
- Major: 5 (METH-1 single-run, METH-2 no Bloom baseline, METH-3
  unenumerated configs, METH-4 §10.3 single-run carry-over, METH-5
  "tie" needs sample-size justification)
- Minor: 7
- Suggestions: 3
