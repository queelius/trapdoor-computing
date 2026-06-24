# Methodology Auditor (2026-04-13)

## Scope

Review of experimental design, statistical rigor, and reproducibility. The 2026-04-12 review's M2/M3/M4/M5 (baselines, error bars, FPR table, granularity space data) were carry-forward at that point and remain uncorrected per the orchestrator's brief. The state notes confirm these require re-running experiments in the cipher-maps Python library, which has not yet been done.

## Summary

The experimental section is the weakest part of the paper and was not materially improved by the 2026-04-13 second-round fixes. All prior carry-forward issues remain open. The most consequential one is the FPR-compounding finding (the paper's only genuinely novel empirical observation) reported in prose without supporting data.

## Carry-forward findings (still open from 2026-04-12)

### MA-CF-1. No experimental baselines in Table 1 (carry-forward of M2/prior M4)

- **Location**: §7.3, Table 1 (lines 1324-1339).
- **Status**: not addressed.
- **Issue**: Reader cannot tell whether 0.39 precision is good, typical, or poor for Boolean encrypted search without a baseline. Natural baselines: plaintext search, Bloom filter at p=0.05, an SSE benchmark on 20 Newsgroups (Cash et al. 2013 or similar).
- **Suggestion**: Add plaintext and Bloom-filter columns. Three-way comparison isolates what the cipher-map construction contributes beyond a Bloom-like filter. Without this, the table is uninformative.

### MA-CF-2. No error bars or run counts (carry-forward of M3/prior M4)

- **Location**: §7.3, Table 1 and granularity table.
- **Status**: not addressed.
- **Issue**: Single-run numbers, no variance, no SD, no hardware spec. Reproducibility undermined.
- **Suggestion**: 5+ seeds, mean +/- SD for precision/recall/time. Hardware line.

### MA-CF-3. FPR compounding finding in prose only (carry-forward of M4/prior M5)

- **Location**: §7.3, "FPR compounding vs. Bernoulli model" paragraph (lines 1348-1361).
- **Status**: not addressed.
- **Issue**: The single most surprising empirical finding (Bernoulli independence breaks for cipher-map AND chains at depth > 2) is a paragraph of prose. "An order of magnitude at k=3" is not quantified. No OR-chain data table. No chain-length progression.
- **Suggestion**: Add Table 2 with: predicted FPR (p_T^k), empirical OR FPR, empirical AND FPR, ratio, for k = 1 to 5. Or a log-scale figure. This is the paper's strongest novel empirical observation; promoting it to a table is the single most impactful methodology fix.

### MA-CF-4. Space column missing for 2 of 3 granularity levels (carry-forward of M5/prior M6)

- **Location**: §7.3, granularity table (lines 1366-1376).
- **Status**: not addressed.
- **Issue**: Space is the central axis of the encoding-granularity trade-off. Two of three rows have "---" in the space column.
- **Suggestion**: Measure on-disk size of the cipher maps via a serialization format, or provide analytic estimates.

### MA-CF-5. 5,000-document subset is unmotivated (carry-forward of M13)

- **Location**: §7.3, lines 1314-1322.
- **Status**: not addressed.
- **Issue**: Corpus has 18,266; experiments use 5,000. No selection criterion.
- **Suggestion**: One sentence on subsetting rationale.

### MA-CF-6. "Order of magnitude" not quantified (carry-forward of M14)

- **Location**: §7.3, line 1354-1355.
- **Status**: not addressed.
- **Issue**: "An order of magnitude at k=3" should be the actual ratio.
- **Suggestion**: "Empirical FPR at k=3 is approximately X, versus predicted 1.25e-4, factor-of-Y."

### MA-CF-7. 150-input loan pipeline is a toy (carry-forward of m9)

- **Location**: §7.3, granularity table.
- **Status**: not addressed.
- **Issue**: 150 inputs is small; results may not extrapolate.
- **Suggestion**: Scale up or asymptotic-scaling note.

### MA-CF-8. Construction rate without hardware spec (carry-forward of m10)

- **Location**: §7.3, line 1322.
- **Status**: not addressed.

### MA-CF-9. No reproducibility statement (carry-forward of m11)

- **Location**: §7.3.
- **Status**: not addressed.
- **Suggestion**: URL, commit hash, dataset reference, hardware, seeds.

### MA-CF-10. phobic library uncited (carry-forward of m18)

- **Location**: §7.3, line 1313.
- **Status**: not addressed.

## New methodology observations (2026-04-13)

### MA-NEW-1. Sanity-check arithmetic in §7.3

- **Location**: lines 1314-1316.
- **Issue**: With `n=8`, `|T|=13`, `|F|=230`, the implied `|N| = 256 - 13 - 230 = 13`. Check: `p_T = 13/256 ~= 0.0508`, `p_F = 230/256 ~= 0.898`, `p_N = 13/256 ~= 0.0508`. The text earlier states `p_T = 0.05, p_F = 0.90, p_N = 0.05`. Consistent within rounding.
- `(13+230)^2 = 243^2 = 59,049`. Correct.
- **Status**: arithmetic is consistent. No issue.

### MA-NEW-2. Construction-time vs. evaluation-time confusion in regex example

- **Location**: §6.3, Example 6.1, lines 1167-1183.
- **Issue**: The example claims the expression-tree decomposition for regex matching has "construction cost exponential in ell". This is a methodological error: it conflates a strawman decomposition (one combiner cipher map over all ell intermediate states) with the natural typed-chain decomposition (ell separate cipher maps in a chain, total cost linear in ell). The empirical question of how cut-point placement affects construction cost is real but the example does not demonstrate it.
- **Suggestion**: Replace the example with one where the two realizations genuinely differ in cost. Or correct the analysis: both realizations have `O(ell * |Q| * |Sigma|)` total space for regex matching; both leak `ell`. The example is supposed to motivate cut-point placement as an optimization; as written, it does the opposite.

### MA-NEW-3. Cipher TM space claim does not include shift cipher map

- **Location**: §6.1, Proposition 6.1, lines 989-1000.
- **Issue**: The proposition claims `O(|Q| x |Gamma|)` space for `delta_T` but the new definition (line 978-981) invokes "a second cipher map for the shift operation". This second cipher map is not analyzed. If it operates on adjacent cell pairs jointly, its space is `O((|Q| x |Gamma|)^2)`, which dominates `delta_T`.
- **Suggestion**: Either (a) factor the shift into two unary cipher maps and add them to the space analysis, or (b) acknowledge the shift as a separate cipher map and account for its space cost in the proposition. Currently the cipher TM's total space is not actually `O(|Q| x |Gamma|)`.

## Strengths (preserved from prior review)

- The cipher Boolean experiments cover real (not synthetic) data: 18,266 documents from 20 Newsgroups.
- The construction rate (843 doc/sec) is a useful concrete number.
- The encoding-granularity comparison includes three different granularity levels (root, intermediate, leaf), which is the right experimental design even if the data points are incomplete.
- The FPR compounding observation, although in prose, is genuinely surprising and worth following up.

## Verdict

Methodology has not changed since 2026-04-12. All prior carry-forward issues remain open. Two new methodological errors entered with the second-round fixes (MA-NEW-2 regex example, MA-NEW-3 cipher TM shift space).

The most impactful single revision the paper could undergo is to flesh out the FPR-compounding finding (MA-CF-3) into a proper experimental contribution. As it stands, the experimental section is supportive but does not stand on its own.
