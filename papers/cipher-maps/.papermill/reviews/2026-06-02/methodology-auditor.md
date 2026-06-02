# Methodology Auditor Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Scope**: experimental design, statistical rigor, reproducibility of the
empirical claims in section 10 (E1 Bloom baseline, E3 replicated
codec-security, E4 randomized-encoding K sweep, Le Cam tightness, Pareto
frontier, key-universe scope), plus the section 8.3 numerical illustration.

All numbers below were checked against the published CSVs and summaries in
.papermill/experiments/2026-05-23/ and the source experiment in the
bernoulli repo.

---

## Summary

The empirical core is honest and, with two exceptions, reproduces from the
published artifacts. E3 (10 replicates x 100K trials) and E4 (5 replicates)
are well-designed; E1 (Bloom baseline) is methodologically careful and
flags its single-run nature. The Le Cam tightness result is clean.

Two reproducibility gaps surfaced this round, both of the "stated parameter
does not match the artifact" family rather than data fabrication:

- **METH-MAJ-1 (NEW, cross-listed with logic LOG-MAJ-1)**: the section 8.3
  and section 10.6 distribution is labeled Zipf s = 1 but the experiment
  and the numbers require s = 1.2. The headline "132x" illustration does
  not reproduce from s = 1.
- **METH-MIN-1 (NEW)**: the E1 Bloom-baseline table caption claims
  m up to 18266, but the experiment ran on the 11,004-document training
  split (per e1/summary.md). Table values are robust to this (numbers are
  near-constant across m), but the stated largest m is wrong.

The carry-over single-run limitations (Le Cam tightness table,
section 10.3, key-universe scope table) persist but are honestly flagged.

**Counts**: Critical 0 | Major 1 | Minor 4 | Suggestions 3.

---

## Empirical claims verified against artifacts (PASS)

### E1, Bloom baseline (section 10.3, Table tab:bloom-baseline)

Source: e1/results.csv (9 cells: m in {1000, 5000, 11004} x
eps in {0.01, 0.05, 0.10}).

| eps | Paper ratio | CSV ratio_practical (per m) | Verdict |
|---|---|---|---|
| 0.01 | 3.20 | 3.18 / 3.22 / 3.19 | PASS (avg ~3.20) |
| 0.05 | 4.59 | 4.57 / 4.62 / 4.58 | PASS |
| 0.10 | 5.76 | 5.73 / 5.80 / 5.74 | PASS |

Bloom bits/elem (9.60, 6.25, 4.81) match bloom_bits_per_elem_theoretical.
Cipher bits/elem (30.7, 28.7, 27.7) match cipher_bits_per_elem_practical.
Cipher empirical FPR (0.0078, 0.0312, 0.0625) matches CSV. The theoretical
ratio-1.07 claim is supported by the asymptotic-PHF reasoning. The honest
flag "single run per cell" is present (line 2521). PASS on values.

### E3, replicated coincidence-oracle sweep (section 10.6)

Source: e3/results.csv (5 codecs x t in {1..5}, 10 reps x 100K trials).

- "23 of 25 cells with prediction inside Wilson 95% CI": confirmed. The
  two outside-CI cells are Dense(M=3) t=4 (gap -2e-4) and Huffman(M=4,p_f)
  t=5 (gap -1.4e-3), exactly as the paper states (lines 2709-2713). Both
  prediction_in_ci = False in the CSV; all others True.
- Mean absolute gap 4e-4, max 1.7e-3: matches.
- Numerical example at t=5: Huffman(M=4,p_f) predicted accuracy 0.98436
  (CSV), Dense(M=3) predicted 0.99988 (CSV). Error-rate ratio
  (1-0.98436)/(1-0.99988) = 0.01564/0.00012 = 130 (paper says ~132,
  using empirical 0.016/0.00012 = 133). PASS.

### E4, randomized-encoding K sweep (section 10.6)

Source: e4/summary.md.

- H1 monotone decay: t=4 Huffman pattern TPR 0.4156 -> 0.1058 -> 0.0116
  -> 0.0018 -> 0.0002 for M=4..8. Matches line 2750-2751 exactly.
- H1 closed-form match "within 0.02 (13 of 15 within 0.01; two M=5 cells
  at 0.010, 0.016; mean 0.004)": matches summary; R8 MAJ-3 fix verified.
- H2 invariance (PASS, gap < 0.05): matches.
- H3 Dense saturation (canonical = random = 1.0 at all t): matches.
- 230x reduction M=4 to M=7 (0.4156 -> 0.0018): matches line 2780.
- t=2/t=4 anchor numbers (1.000 canonical -> 0.699 random at n=4, 0.543 at
  n=5) at lines 2084-2085: consistent with the e4 table family.
PASS.

### Le Cam tightness (section 10.6, Table tab:le-cam-tight)

The TV / Le Cam UB / best-attacker triples (Huffman n=5: 0.096/0.548/0.542;
... AntiHuffman n=5: 0.616/0.808/0.811) are internally consistent
(UB = 1/2 + TV/2 holds for each row). Mean Bayes gap -0.0004
(statistically zero), three attacker classes tie. Clean result. Single-run
(honestly flagged); see METH-MIN-2.

---

## MAJOR FINDING

### METH-MAJ-1 (NEW, cross-listed with LOG-MAJ-1): section 8.3 / 10.6 distribution labeled s=1 but is s=1.2

**Severity**: Major (reproducibility of the headline multi-instance
illustration).

The section 8.3 numerical illustration (lines 1934-1937) and the
section 10.6 Setup (line 2609) both state the value distribution is
Zipf with skew s = 1. But:

- A literal Huffman code on Zipf(s=1) over |Y|=8 gives the dominant value
  a length-2 codeword (max alpha = 0.25), NOT the length-1 codeword
  (max alpha = 0.5) the paper claims. The resulting t=5 attacker accuracy
  would be ~0.999, not the stated 0.984, and the "132x" ratio collapses.
- The source experiment (14_coincidence_oracle.py line 77) uses
  1/(i+1)^1.2, i.e. s = 1.2, which gives p[0] = 0.4286, Huffman lengths
  [1,3,3,4,4,4,5,5], max alpha = 0.5, sum alpha^5 = 0.0313, accuracy
  0.9843. These match the paper's numbers and the E3 CSV max_q = 0.5.

So the numbers are correct and validated; only the stated skew is wrong.
A reviewer reproducing from s=1 cannot get the paper's figures. This is
the same class of parameter mislabel the user has caught repeatedly.

**Suggestion**: s = 1 -> s = 1.2 at lines 1934 and 2609. Zero risk to the
numbers. One-character edit at each site.

**Cross-verification**: independent Huffman build on both skews + source
file inspection (exponent 1.2) + E3 CSV max_q column (0.5 for
Huffman(M=4,p_f)). Triple-confirmed.

---

## MINOR FINDINGS

### METH-MIN-1 (NEW): E1 table caption claims m up to 18266; experiment ran on 11,004

**Location**: line 2471, "For m in {1000, 5000, 18266} documents".
**Artifact**: e1/summary.md states "20 Newsgroups training split, 11,004
documents after filtering empties." The CSV's distinct m values are
{1000, 5000, 11004}.

**Problem**: The full corpus (18,266 docs) is used for the throughput
numbers in section 10.3 and the cipher-set construction, but the
**Bloom-baseline** experiment (E1) ran on the 11,004-doc training split.
The table caption mislabels the largest m as 18266. The averaged table
values are robust (e1 confirms differences across m are within 0.04
bits/elem), so the reported ratios are correct, but the stated largest m
does not match the artifact.

**Suggestion**: Change "18266" to "11004" in the E1 sentence at line 2471
(and the parenthetical "11004 / 18266 document subsets" in e1/summary's
note should be reconciled too). Alternatively rerun E1 on the full corpus.
The editorial fix is 5 minutes; the rerun is optional.

### METH-MIN-2: Le Cam tightness table single-run (carry-over R7 MAJ-7 / R8 METH-MAJ-4)

The Le Cam tightness table (tab:le-cam-tight) is single-run while the
same-section E3 and E4 results are replicated. The paper now flags this
explicitly ("Le Cam results are single-run", line 2627), which is an
improvement over R7. Still worth 3 replicates for the headline value-side
result. Non-blocking given the honest flag.

### METH-MIN-3: key-universe scope table single-run (carry-over R7 MAJ-11 / R8 METH-MAJ-5)

Table tab:scope-keys (three key-universe configs) is single-run. The
qualitative claim (structured keys break the value-side bound) is robust
to sampling noise, but the specific accuracies (0.997, 0.990) are
single-run. Non-blocking.

### METH-MIN-4: 14 Pareto-frontier configs not enumerated in a CSV (carry-over R7 MAJ-9 / R8 METH-MAJ-3)

The (TV, L) Pareto frontier claims "14 of 14 on frontier, 7 of 14
TV-optimal" but the 14 configs are not enumerated in a published table or
CSV. The 42x headline (heavy-tail p_y = (0.9, 0.0143, ...), TV 0.40 ->
0.0094 at 17% L overhead) is checkable by hand and is correct, but the
full sweep is not reproducible from an artifact. Recommend publishing the
enumeration. Non-blocking.

---

## SUGGESTIONS

### METH-SUG-1: Publish the Le Cam / Pareto / key-universe scripts
The E1/E3/E4 scripts are published; the Le Cam tightness, Pareto frontier,
and key-universe scope experiments should be too, for parity. (carry-over)

### METH-SUG-2: Add Xor/Ribbon filter rows to the E1 baseline
Comparing per-document overhead to the 1970 Bloom filter understates the
modern frontier. Xor (Graf-Lemire 2020) and Ribbon (Dillinger-Walzer 2021)
are the current below-Bloom constructions. (carry-over R8 METH-SUG-3)

### METH-SUG-3: Consolidated experiments table at the top of section 10.6
Seven paragraphs of distinct sub-experiments (Le Cam, Pareto, E3, E4,
key-universe) would read better with a one-row-per-experiment summary
table (codec set, |S|, n/M, replicates, headline result). (carry-over
R8 METH-SUG-1, also prose PROSE-MAJ-2)

---

## Reproducibility posture

The paper is in good shape on reproducibility relative to its own claims.
E1/E3/E4 reproduce from published artifacts. The two new gaps
(METH-MAJ-1 s=1.2, METH-MIN-1 m=11004) are label/parameter mismatches
where the artifact is correct and the manuscript text is wrong, both
fixable in minutes. No fabricated data; no claim is unsupported by an
artifact once the labels are corrected.
