# Methodology Auditor Report

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp)
**Date**: 2026-04-12
**Scope**: Experimental design, statistical rigor, reproducibility, methodological soundness.

## Summary

The paper is predominantly theoretical; the methodological footprint is Section 7.3 (one subsection, ~30 lines) plus Table 1 and one unnumbered subtable. The prior review flagged experimental baselines, error bars, and missing data (M4, M5, M6). None of these have been addressed in the restructure. The experimental presentation is the weakest part of the paper and, for a PLAS submission, is below conference-grade standard.

Three core issues persist from the prior review:
- M4: no baselines (plaintext search, Bloom filter, or SSE), no error bars, no statement of whether results are from single or averaged runs.
- M5: the FPR compounding finding (genuinely interesting) is reported in prose only.
- M6: the encoding granularity table has space data for 1 of 3 levels.

Two new issues surfaced:
- The 5,000-document subset is chosen without justification (the full corpus has 18,266). This is a sampling decision that affects precision/recall estimates.
- The construction-time and evaluation-time measurements are single-trial point estimates; wall-clock numbers without hardware specification are not reproducible.

---

## Major Issues

### MT-MAJ-1. No baselines in Table 1 (carry-forward of M4)

**Location**: Section 7.3, Table 1 (lines 1204 to 1219).

**Problem**: Table 1 shows precision/recall/FP/time for cipher Boolean search but has no comparison point. A reader cannot tell whether the reported numbers are good, bad, or typical for Boolean encrypted search.

Baselines a reviewer will expect:
1. **Plaintext Boolean search** (expected P=R=1.0): shows what recall should look like when not degraded by noise.
2. **Bloom filter equivalent** (same p_T=0.05 false-positive rate, no noise region): separates the contribution of the noise region from the contribution of the hash-based partition.
3. **Some SSE baseline or benchmark number** for the 20 Newsgroups corpus: e.g., precision/recall of a secure-index keyword search scheme (Cash et al. 2013, Kamara et al. on encrypted text search).

Without (1), the 0.39 precision and 1.00 recall cannot be contextualized. Without (2), the contribution of the noise region is not isolated. Without (3), the PLAS reviewer cannot position the work against existing encrypted-search benchmarks.

**Suggestion**: Add at minimum (1) and (2) as columns. A full three-way comparison (plaintext / Bloom / cipher-map) turns Table 1 from a point estimate into a contribution-isolating comparison.

### MT-MAJ-2. No error bars or run counts (carry-forward of M4)

**Location**: Section 7.3, Table 1 (lines 1204 to 1219); unnumbered granularity table (lines 1247 to 1256).

**Problem**: The paper does not state:
- Whether each row is a single run, an average, or something else.
- How many runs were performed.
- What the variance or standard deviation of precision, recall, FP count, or time is.

For precision values in the range 0.26 to 0.39, the standard deviation could be anywhere from <0.01 (if the corpus is large and the randomization is over seed) to >0.10 (if it's over query selection). The reader has no way to know.

Wall-clock timing is similarly unreliable without (a) hardware specification, (b) warm-up/steady-state handling, and (c) variance estimates. A report of "0.10s" versus "0.60s" could easily shift 2x run to run on a typical developer laptop.

**Suggestion**: Minimum viable improvement:
- Run 5+ seeds, report mean +/- SD for precision, recall, and time.
- State the hardware: "All measurements on [CPU model], single-threaded, Python 3.x, cipher-maps commit [hash]."
- State what varies: "The seed controls the PHF seed search; queries and document splits are fixed."
- For FP counts (integer-valued), reporting the range (min to max) across seeds is appropriate.

### MT-MAJ-3. FPR compounding reported only in prose (carry-forward of M5)

**Location**: Section 7.3, "FPR compounding vs. Bernoulli model" paragraph (lines 1228 to 1242).

**Problem**: The single most interesting experimental finding (that cipher-map AND composition violates the Bernoulli independence assumption) is described in words with no data. "An order of magnitude at k=3" is not quantified. The reader cannot:
- Verify the claim.
- Assess the magnitude (an order of magnitude could be 5x or 30x, both round to "an order").
- Determine at what k the divergence emerges (>2 is vague).
- Compare the OR chain (said to match theory) to the AND chain (said to diverge).

**Suggestion**: Add Table 2:

| k | Predicted FPR (p_T^k) | Empirical OR FPR | Empirical AND FPR | AND ratio |
|---|-----------------------|------------------|-------------------|-----------|
| 1 | 0.05 | 0.045 | 0.050 | 1.0 |
| 2 | 0.0025 | ... | ... | ... |
| 3 | 1.25e-4 | ... | ... | ~10x |
| 4 | 6.25e-6 | ... | ... | ... |
| 5 | 3.13e-7 | ... | ... | ... |

Or, alternatively, a log-scale figure plotting predicted vs. empirical for both operations.

### MT-MAJ-4. Space column missing for 2 of 3 granularity levels (carry-forward of M6)

**Location**: Section 7.3, unnumbered granularity table (lines 1247 to 1256).

**Problem**: The granularity table has "---" in the space column for intermediate and leaf annotations. Since the whole point of the encoding granularity spectrum is space versus confidentiality, missing space data undermines the comparison. The reader is told only that root annotation uses 694 bytes; they cannot determine whether intermediate and leaf use 7 KB, 70 KB, or 700 KB.

**Suggestion**: Measure and fill the space column. Use JSON serialization or a safe binary format to measure on-disk size. Alternatively, provide an analytic estimate: "Intermediate annotation produces 3 cipher maps of size approximately |domain_i| * log_2 |codomain_i| bytes; the total is X bytes at the 150-input domain size." If space data cannot be obtained, drop the column entirely and state that space is left to future comparison.

### MT-MAJ-5. The 5,000-document subset is unmotivated

**Location**: Section 7.3 (lines 1192 to 1202).

**Problem**: The corpus has 18,266 documents (stated at line 1194). The experiments use 5,000 (line 1200). The paper does not state:
- How the 5,000 were selected (random, first-N, topic-balanced?).
- Why not use the full corpus.
- Whether the 5,000 are the same across all queries in Table 1, or whether they vary.

If the subset is arbitrary, a reviewer will ask "do the results hold on the full 18,266?" If it is topic-balanced, that should be stated. If it's a performance limitation, that should be stated and motivate future work on scalability.

**Suggestion**: One sentence: "We use a random sample of 5,000 documents (fixed across queries, selected by [seed/criterion]) for evaluation; construction over the full 18,266 corpus is reported in [future work / appendix]."

### MT-MAJ-6. 150-input loan approval domain is a toy (carry-forward of m7)

**Location**: Section 7.3, granularity table (lines 1244 to 1262).

**Problem**: A 7-function loan approval pipeline with 150 inputs is tiny. The root cipher map is 694 bytes; this is smaller than a single Ethernet frame. It cannot demonstrate scaling behavior, and the "650x faster" comparison is therefore anecdotal rather than generalizable.

**Suggestion**: Either (a) run at a larger scale (e.g., 10^4 or 10^5 inputs, where PHF construction vs. seed search differ more meaningfully); (b) add a note about asymptotic scaling: "Space grows as O(|X|) for root annotation, O(sum |X_i|) for leaf annotation; the 150-input case is a proof-of-concept, not a scalability benchmark"; or (c) drop the comparison and focus on functional equivalence (zero errors, correctness of the pipeline).

### MT-MAJ-7. Precision of 0.39 is unexplained (carry-forward of m4)

**Location**: Section 7.3, Table 1, first row (Single term).

**Problem**: Precision of 0.39 for a single-term query means 61% of returned documents are false positives. To a reader expecting plaintext-style precision, this looks alarming. The paper does not explain that this is expected for a Bloom-like filter with p_T=0.05.

The expected precision for a single-term query is approximately:
  P = (true positives) / (true positives + false positives) = TP / (TP + p_T * (N - TP))
where N is the corpus size and TP is the true-set size. For TP small relative to N (e.g., TP=100, N=5000, p_T=0.05), P = 100 / (100 + 0.05 * 4900) = 100 / 345 ~= 0.29, consistent with 0.39.

**Suggestion**: Add a sentence explaining the expected precision given p_T and the query set size. Alternatively, normalize: report precision at various p_T values (0.01, 0.05, 0.10) to show the space/confidentiality trade-off empirically.

---

## Minor Issues

### MT-MIN-1. "Construction rate: 843 documents per second" lacks hardware spec

**Location**: Section 7.3, line 1202.

**Problem**: Without hardware specification, 843/s could mean anything from "ran on Raspberry Pi" to "ran on 128-core server." Commercial SSE systems typically report 10^4 to 10^5 per second; a reviewer comparing will want hardware details.

**Suggestion**: "Construction rate: 843 documents per second on [hardware spec], single-threaded."

### MT-MIN-2. No reproducibility statement or artifact pointer

**Location**: Section 7.3 and paper-level.

**Problem**: The paper mentions "reference implementation (cipher-maps, Python with PHF backend via phobic)" but does not give a version/commit, URL, or reproducibility package. Current PLAS submissions typically require or strongly encourage an artifact.

**Suggestion**: Add a reproducibility paragraph at end of Section 7.3 or in Conclusion:
> "Code and experiment scripts are available at https://github.com/queelius/cipher-maps (commit [X]). Experiments use the 20 Newsgroups dataset [cite Lang 1995] downloaded via scikit-learn."

### MT-MIN-3. "843 documents per second" versus times in Table 1: consistency

**Location**: Section 7.3 line 1202 ("843 docs/sec" = construction rate) vs. Table 1 time column ("0.10s to 0.60s" for queries).

**Problem**: The 843/sec is construction rate; the times in Table 1 are query times. Without clarification, a reader might conflate them. For 5000 documents at 843/sec, construction takes ~6 seconds; this context helps place the query times (which are for searching the prebuilt index).

**Suggestion**: State clearly: "Construction took 5000 / 843 = 5.9 seconds; the query times in Table 1 are for search over the prebuilt cipher-map index."

### MT-MIN-4. Queries in Table 1 are not specified

**Location**: Section 7.3, Table 1.

**Problem**: What words are in the queries? Is "Single term" the average over all single-term queries? Over a specific one? Is "2-term AND" the conjunction of two frequent words, or random words, or disjoint categories? The reproducibility and interpretation depend critically on the query selection.

**Suggestion**: Either (a) list the queries (e.g., "Single term: 'computer'; 2-term AND: 'computer' AND 'hardware'; 3-term AND: 'computer' AND 'hardware' AND 'sale'"); or (b) state the averaging protocol: "Each row is the average over 10 queries randomly sampled from the 1000 most common terms, with 5 seeds per query."

### MT-MIN-5. Recall of 0.88 for OR AND NOT: worth closer analysis

**Location**: Section 7.3, Table 1, last row.

**Problem**: OR AND NOT reaches 0.88 recall, 12% below OR alone. The text attributes this to "noise propagation" in NOT. This deserves a bit more analysis:
- How often does NOT on a cipher Boolean value produce noise?
- Is 12% consistent with p_N = 0.05 (two cascaded noise passes = 0.0975)?
- If not, what's going on?

This is related to the FPR compounding finding and may share a root cause.

**Suggestion**: Expand the paragraph after Table 1 to quantify noise propagation. For a 12% recall drop, the noise contribution at each stage should be traceable. A short error analysis (2 to 3 sentences) would turn "noise propagation" from a hand-wave into a data-supported claim.

---

## Suggestions

### MT-SUG-1. Extend experiments to demonstrate the theoretical claims

The theoretical results (orbit bound, typed-chain bound) are never validated empirically. Options:
- For orbit closure: measure the orbit size of a cipher Boolean under AND/NOT for n = 4, 5, 6, 7, 8 bits. Plot versus 2^n. Does it grow as predicted?
- For typed-chain bound: show that a 2-level typed Boolean system's adversary view is strictly smaller than an untyped system's view for the same computation.

Even a single small experiment validating the orbit bound would strengthen the link between theory and practice.

### MT-SUG-2. Add a confidentiality-cost experiment matching the granularity table

The granularity table shows space and intermediate count. It should also show the theoretical confidentiality bound:

| Level | Build time | Space | Intermediates | Conf bound |
|-------|------------|-------|---------------|-----------|
| Root (1 cipher map) | 0.009s | 694 B | 0 | 1 - 1/|X| |
| Intermediate (3 groups) | 6.8s | ~X B | 3 | 1 - 3/|X| |
| Leaf (7 nodes) | 5.9s | ~Y B | 7 | 1 - 7/|X| |

This turns the granularity table into a direct illustration of the orbit-closure bound, connecting theory to experiment in one place.

### MT-SUG-3. Consider a small-scale deliberate-attack experiment

The paper's threat model is "passive adversary observes cipher values and can evaluate cipher maps." An explicit attack experiment would strengthen claims:
- Given cipher values and cipher AND/OR/NOT, can an untrusted party partition them into T / F / N classes using active probing (as per Remark 5.3)?
- How many probes (orbit expansions) does it take to achieve, e.g., 80% classification accuracy?

This would both validate the orbit-closure risk model and give practical guidance on when typed-chain discipline is strictly necessary.

---

## Cross-cutting Observations

- **Theoretical/experimental balance**: The paper is 85% theory, 15% experiment. The experimental portion is currently below bar for PLAS; strengthening it via the fixes above would bring it to bar.
- **Reproducibility**: No commit hash, no hardware, no protocol. All three are correctable with short edits.
- **Integration between theory and experiment**: The experiments demonstrate that cipher Boolean search works; they do not demonstrate the theoretical contributions (orbit bound, typed chains). MT-SUG-1 and MT-SUG-2 would fix this and make the experimental section earn its place.
- **Prior-review status**:
  - M4 (baselines, error bars), **not addressed** (MT-MAJ-1, MT-MAJ-2).
  - M5 (FPR compounding in prose only), **not addressed** (MT-MAJ-3).
  - M6 (space data missing), **not addressed** (MT-MAJ-4).
  - m4 (0.39 precision unexplained), **not addressed** (MT-MAJ-7).
  - m5 (granularity table unnumbered), **not addressed**: the table is still unnumbered in the restructured version.
  - m6 (zero errors is expected), **not addressed**, see LC-MIN-5.
  - m7 (150-input toy), **not addressed** (MT-MAJ-6).
  - m10 (20 Newsgroups citation), **not addressed**: the dataset is still unreferenced.
