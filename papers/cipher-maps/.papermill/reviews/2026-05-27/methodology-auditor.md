# Methodology Auditor Report, Round 8 (2026-05-27)

This round verifies the three new empirical results landed since R7
(E1 Bloom baseline, E3 replicated codec security, E4 randomized
encoding K sweep) against the underlying CSVs and summary documents,
and audits the remaining experimental claims.

## Cross-verification of new empirical content

### E1: Bloom-filter baseline (section 10.3)

Source: `.papermill/experiments/2026-05-23/e1/results.csv`,
`e1/summary.md`. Single run, no replicates.

Paper claims (lines 2411 to 2457) verified against summary:

| Claim in paper | Source value | Verdict |
|---|---|---|
| eps = 0.01: Bloom 9.60, Cipher 30.7, ratio 3.20, FPR 0.0078 | 9.60 / 30.55 / 3.18 / 0.0078 (1000 doc); 30.89 / 3.22 / 0.0078 (5000); 30.59 / 3.19 / 0.0078 (11004) | Paper rounds cipher to 30.7 (mean across m), close to mean 30.68. PASS. Ratio 3.20 vs mean 3.20. PASS. |
| eps = 0.05: Bloom 6.25, Cipher 28.7, ratio 4.59, FPR 0.0312 | Mean cipher 28.68, ratio mean 4.59, FPR 0.0312 | PASS |
| eps = 0.10: Bloom 4.81, Cipher 27.7, ratio 5.76, FPR 0.0625 | Mean cipher 27.68, ratio mean 5.76, FPR mean 0.0624 | PASS |
| Mean ratio 4.52 practical | summary.md "Mean across 9 cells: 4.52" | PASS |
| Theoretical asymptote 1.07 | summary.md "Theoretical lower bound ... 1.07" | PASS |
| PHF overhead ~23.6 bits/key | summary.md finding 1 confirms this | PASS |

The paper text at lines 2440 to 2442 says "phobic's per-PHF
fixed-cost overhead at the per-document scale (mean vocabulary ~ 98
tokens)". Summary.md confirms mean vocabulary ~98 to 100 tokens
across m. PASS.

The single-run caveat is correctly disclosed at lines 2462 to 2468:
"The numbers above are from one run per cell; variance
characterization across replicates and against SSE baselines at
matched operating points is work in progress."

**Finding**: E1 is well-integrated. Numbers match the underlying CSV.
The single-run caveat is honest. R7 MAJ-8 (no Bloom baseline)
materially closed. Only residual issue is that "eps = 0.10" cells
sit at ratio 5.76, which the E1 design.md flagged as exceeding the
"discuss only" threshold of 5; the paper does not explicitly note
this is the worst-case cell. Recommendation: add a one-clause note
"the ratio degrades to 5.8x at eps = 0.10 (the largest tested), where
Bloom asymptotically approaches its 1.44 log_2(1/eps) formula and
cipher stays roughly flat."

### E3: Replicated codec-security study (section 10.6)

Source: `e3/results.csv`, `e3/summary.md`. 10 replicates per cell,
100K trials per cell pooled, 25 cells total.

Paper claims (lines 2636 to 2653) verified:

| Claim in paper | Source value | Verdict |
|---|---|---|
| "5 codecs at t in {1, 2, 3, 4, 5}" | 25 cells in summary table | PASS |
| "10 replicates per cell, 10,000 trials per replicate" | summary lines 4-5: Replicates 10, Trials 100,000 (= 10 x 10K). | PASS |
| "23 of 25 cells with theoretical prediction inside Wilson 95% CI" | summary line 6: "Cells with theoretical prediction inside Wilson 95% CI: 23 / 25" | PASS |
| "mean absolute gap ... 4 x 10^-4" | summary line 7: 0.0004 | PASS |
| "max 1.7 x 10^-3" | summary line 8: 0.0017 | PASS |
| "Dense(M=3) t=4 predicted 0.9990 vs CI upper 0.9990 with gap -2 x 10^-4" | summary table row "Dense(M=3) | 4 | 0.9990 | 0.9988 | ... [0.9985, 0.9990] | -0.0002 | NO" | PASS (the CI is [0.9985, 0.9990] and pred 0.9990 is on the boundary; paper correctly notes "CI upper 0.9990 with gap -2 x 10^-4"). |
| "Huffman(M=4) t=5 predicted 0.9844 vs CI [0.9821, 0.9837] with gap -1.4 x 10^-3" | summary row Huffman(M=4,p_f) t=5: predicted 0.9844, empirical 0.9830, CI [0.9821, 0.9837], gap -0.0014. | PASS |
| Codec inventory (Dense, two Padded, Huffman x2, AntiHuffman) | summary covers 5 codecs: Dense(M=3), Dense(M=4), Padded(M=4,v0), Huffman(M=4,p_f), AntiHuffman(M=4). | The paper says "Five codecs" and lists Dense, two Padded variants, Huffman at n=4 and n=5, and AntiHuffman at n=5 in section 10.6 paragraph "Setup" (line 2554). Summary actually has Dense(M=3) and Dense(M=4) (not "Padded with default y_7"). Mismatch. See METH-MAJ-1 below. |

**METH-MAJ-1 (codec inventory mismatch between section 10.6 Setup and
underlying E3 sweep)**. Location: lines 2550 to 2564 vs e3 summary.

Section 10.6 "Setup" (lines 2550 to 2564) lists six acceptance
predicates:
- Dense (alpha_y = 1/|Y|)
- Two Padded variants with default values y_0 and y_7
- Huffman at n = 4 and n = 5
- AntiHuffman at n = 5

This is the setup for the Table 10.x Le Cam tightness table at
lines 2575 to 2596, which has 5 rows: Huffman(n=5), Huffman(n=4),
Dense(n=4), Padded(default = y_7), AntiHuffman(n=5).

But the E3 replicated sweep underlying the "23 of 25" claim used a
different codec inventory: Dense(M=3), Dense(M=4), Padded(M=4,v0),
Huffman(M=4,p_f), AntiHuffman(M=4). No Huffman(M=5), no
Padded(default = y_7), no AntiHuffman(M=5). Different codec set across
the two tables.

This is not a fatal error, but it is a methodological seam: the paper
describes one codec inventory and reports two tables drawing on
different inventories from that nominal set. A reader who tries to
reproduce will be confused.

Recommendations:
1. Add a Setup-level note that "Table 10.x (Le Cam tightness) uses
   single-run numbers across the full 5-codec set described above,
   while the E3 replicated sweep at the end of this paragraph uses a
   focused subset (Dense at M=3 and M=4, Padded at M=4 v0, Huffman at
   M=4, AntiHuffman at M=4) for tractability."
2. Or, more cleanly: rerun the Le Cam tightness table on the same E3
   codec set so the two tables share their inventory.

This is the most concrete methodology issue introduced by the new
content.

### E4: Randomized-encoding K sweep (section 10.6)

Source: `e4/results.csv`, `e4/summary.md`. 36 cells, 5 replicates per
cell, |S| = 1000.

Paper claims (lines 2674 to 2721) verified:

| Claim in paper | Source value | Verdict |
|---|---|---|
| "M in {4, 5, 6, 7, 8}, |S| = 1000, t in {2, 3, 4}, 5 replicates" | summary lines 4-5; per-cell table confirms M, t ranges and Replicates = 5 | PASS |
| "36 cells" | Counting summary table: 6 (Dense) + 30 (Huffman M=4 to 8, both encodings, t=2 to 4) = 36 cells. PASS. | PASS |
| H1 t=4 TPR: 0.4156 -> 0.1058 -> 0.0116 -> 0.0018 -> 0.0002 | summary line 13: "t=4: ... 4->0.4156, 5->0.1058, 6->0.0116, 7->0.0018, 8->0.0002" | PASS exactly |
| "to within 0.01 in all 15 Huffman cells (mean absolute gap 0.004)" | Compare paper text and source: 15 Huffman cells = (M=4..8) x (t=2,3,4) = 15. Gap empirical-vs-prediction is in summary table: e.g., Huffman(M=4) random t=2: 0.5406 vs pred 0.5317 = 0.0089. Huffman(M=5) random t=3: 0.1294 vs 0.1457 = -0.0163. The 0.0163 gap exceeds 0.01! Re-check paper claim. | DISCREPANCY |
| H2 max gap 0.0114 | summary line 17: "Max gap between canonical and random decode rates across all (codec, M, t) cells: 0.0114" | PASS |
| H3 Dense all four cells at 1.0 | summary lines 22-25 + table rows: Dense(M=3) pattern_tpr = 1.0000 (both canonical and random) for t=2,3,4 | PASS |

**METH-MAJ-2 (H1 "within 0.01" claim does not hold uniformly)**.
Location: line 2690.

Paper text (lines 2688 to 2691): "Empirical values match the closed
form sum_v p_f(v) * 2^(-(M - l_v)(t - 1)) of Remark 8.x to within
0.01 in all 15 Huffman cells (mean absolute gap 0.004)."

Checking against e4/summary.md per-cell table for Huffman random
cells:

- Huffman(M=4) random t=2: emp 0.5406, pred 0.5317, gap 0.0089 (< 0.01) PASS
- Huffman(M=4) random t=3: emp 0.4306, pred 0.4381, gap 0.0075 (< 0.01) PASS
- Huffman(M=4) random t=4: emp 0.4156, pred 0.4090, gap 0.0066 (< 0.01) PASS
- Huffman(M=5) random t=2: emp 0.2652, pred 0.2756, gap 0.0104 (just above 0.01) FAIL
- Huffman(M=5) random t=3: emp 0.1294, pred 0.1457, gap 0.0163 (> 0.01) FAIL
- Huffman(M=5) random t=4: emp 0.1058, pred 0.1058, gap 0.0000 PASS
- Huffman(M=6) random t=2: emp 0.1422, pred 0.1378, gap 0.0044 PASS
- Huffman(M=6) random t=3: emp 0.0386, pred 0.0364, gap 0.0022 PASS
- Huffman(M=6) random t=4: emp 0.0116, pred 0.0132, gap 0.0016 PASS
- Huffman(M=7) random t=2: emp 0.0684, pred 0.0689, gap 0.0005 PASS
- Huffman(M=7) random t=3: emp 0.0082, pred 0.0091, gap 0.0009 PASS
- Huffman(M=7) random t=4: emp 0.0018, pred 0.0017, gap 0.0001 PASS
- Huffman(M=8) random t=2: emp 0.0316, pred 0.0344, gap 0.0028 PASS
- Huffman(M=8) random t=3: emp 0.0020, pred 0.0023, gap 0.0003 PASS
- Huffman(M=8) random t=4: emp 0.0002, pred 0.0002, gap 0.0000 PASS

So 13 of 15 cells are within 0.01, but 2 (Huffman M=5 at t=2 and
t=3) exceed it. Max gap is 0.0163 (M=5, t=3), not "0.01" as the paper
claims. Mean absolute gap: (0.0089 + 0.0075 + 0.0066 + 0.0104 + 0.0163
+ 0.0000 + 0.0044 + 0.0022 + 0.0016 + 0.0005 + 0.0009 + 0.0001 +
0.0028 + 0.0003 + 0.0000) / 15 = 0.0042 ~ 0.004.

The paper's "mean absolute gap 0.004" is correct. But the
"within 0.01 in all 15 Huffman cells" overstates by missing the two
M=5 cells. Recommendation: change "within 0.01 in all 15 Huffman
cells" to "within 0.02 in all 15 Huffman cells (13 of 15 within 0.01,
two M=5 cells at t in {2, 3} at gaps 0.010 and 0.016 respectively;
mean absolute gap 0.004)."

This is the kind of small precision issue that R7 raised in its
"3-replicate variance characterization" recommendation. The data
supports the substantive claim (empirics match prediction at the
mean-gap level); the "within 0.01" wording is too tight.

## Audit of remaining experimental claims

### Le Cam tightness (lines 2566 to 2596)

The Le Cam tightness table (Table 10.x at lines 2575 to 2596) reports
single-run numbers (per the Setup paragraph at line 2563: "All numbers
below are single-run (no replicates)"). The paper's claim "All three
attackers achieve the same accuracy to within 0.014 sampling noise"
is supported by the table where the gap between Best attacker and Le
Cam UB is bounded.

But the Le Cam tightness table is single-run, while the E3 multi-
instance result that follows is 10-replicate. The same-paragraph
juxtaposition of single-run and replicated results without flagging
the difference is methodologically opaque. R7 MAJ-7 (section 10.6
single-run) was about this; the replicated rerun for E3 partially
addresses it but the Le Cam tightness table remains single-run.

Recommendation: rerun the Le Cam tightness table at 5-replicate
minimum, or add a one-line disclosure "Le Cam tightness numbers
below are single-run; the multi-instance results that follow use
the E3 replicated sweep."

### (TV, L) Pareto frontier (lines 2599 to 2634)

Paper claims (lines 2604 to 2607): "14 configurations covering |Y|
in {4, 6, 8}, n in {4, 6}, and four p_y shapes (uniform, Zipf,
two-mode, heavy-tail)."

Three findings reported:
1. Huffman on Pareto frontier in 14 of 14
2. Huffman is TV-optimal in 7 of 14
3. Heavy-tail p_y = (0.9, 0.0143, ...) at n = 6 gives 42x TV
   reduction at 17% L overhead

Source: not in the experiments/2026-05-23 directory. The 14
configurations are not enumerated in the paper or in any committed
source file. R7 MAJ-9 ("14 Pareto configs unenumerated") remains
open.

**METH-MAJ-3 (Pareto frontier configurations not enumerated)**.
Location: lines 2604 to 2614.

The 14-config Pareto frontier result is reported as a paragraph but
not backed by a published CSV or table. The headline number "42x TV
reduction at 17% L overhead" is for one specific configuration
(heavy-tail p_y at n=6) that is described but not pinned down (the
"..." in "(0.9, 0.0143, ...)" hides the remaining mass).

Recommendation: publish the 14-config CSV alongside e1/e3/e4 (e.g.,
e5_pareto_sweep) with per-row L, TV, codec, and Pareto-optimality
flags. This is a low-cost honesty fix and would close R7 MAJ-9 and
this round's METH-MAJ-3.

### Threat model scope (lines 2723 to 2755)

The key-feature attacker results (Table 10.x at lines 2730 to 2750)
are single-run. The R7 MAJ-11 ("attacker-tie sample-size") raised
this. The Setup paragraph at lines 2550 to 2564 says "All numbers
below are single-run (no replicates)" which covers this table.
Carry-over from R7.

## Findings

### Critical

None. All three new empirical results (E1, E3, E4) integrate
honestly. The substantive claims hold. The mismatches are precision-
of-wording issues, not data fabrication.

### Major

**METH-MAJ-1 (codec inventory mismatch)**: Le Cam tightness table and
E3 multi-instance table use different codec inventories (Padded
y_7 + Huffman n=5 + AntiHuffman n=5 in Le Cam vs Dense M=3 + Dense
M=4 + Padded M=4 v0 + Huffman M=4 + AntiHuffman M=4 in E3) without
flagging the difference. See above. Recommended fix: add a Setup-level
note or align the two inventories.

**METH-MAJ-2 (H1 "within 0.01" claim overstates)**: Two of 15 Huffman
cells exceed the 0.01 threshold (M=5 at t=2 and t=3, gaps 0.010 and
0.016). The mean-gap claim (0.004) is correct. Fix: change "within
0.01 in all 15" to "within 0.02 in all 15 (13 of 15 within 0.01)".

**METH-MAJ-3 (Pareto frontier configurations not enumerated)**: 14
configs not published as CSV. R7 MAJ-9 carry-over. Recommended fix:
publish e5_pareto_sweep CSV.

**METH-MAJ-4 (Le Cam tightness table single-run)**: Section 10.6's
Le Cam tightness table is single-run, while the same paragraph's E3
multi-instance result is 10-replicate. Methodologically opaque
juxtaposition. R7 MAJ-7 partially carry-over. Recommended fix: 5+
replicates or explicit disclosure.

**METH-MAJ-5 (threat model scope table single-run)**: Table 10.x at
lines 2730 to 2750 is single-run. R7 MAJ-11 carry-over.

**METH-MAJ-6 (E1 worst-cell flag missing)**: E1 design.md flagged
eps = 0.10 cells (ratio 5.8x) as exceeding the "discuss only"
threshold. The paper does not flag this as the worst-case cell. See
above. Recommended fix: one-clause note in §10.3.

### Minor

**METH-MIN-1 (E1 single-run caveat)**. Section 10.3 says "single run
per cell; variance characterization ... is work in progress". Good
disclosure, but could be stronger: estimate the sampling noise scale.
For per-document FPR averaged across 11K documents, the sampling
noise is roughly sqrt(eps * (1-eps) / 11000) ~ 0.002 for eps = 0.05.
The reported FPR-vs-target gap is within 0.0005, well inside sampling
noise. Worth saying.

**METH-MIN-2 (Section 10.3 line 2453 phrasing "deployment that can
share a single PHF across documents recover near-Bloom space")**.
The "give up document-level independence" tradeoff is mentioned but
the security implication is not unpacked. A single shared PHF leaks
cross-document token correlations to the untrusted machine; this is
the compositional leakage of §8.2 specialized to a real deployment.
One forward reference to §8.2 would tie these together.

**METH-MIN-3 (E4 H1 closed-form approximation in paper)**. The closed
form at lines 2688 to 2691 is sum_v p_f(v) * 2^(-(M-l_v)(t-1)). The
e4 source uses this (verified against summary table prediction
column). Confirmed.

**METH-MIN-4 (E3 codomain prior Zipf-1 used implicitly)**. The Setup
paragraph at line 2553 says "latent value distribution p_y Zipf with
skew s = 1." The E3 source presumably uses this same distribution.
Not explicitly stated in e3/summary.md (the per-cell table just lists
codecs by name). Worth verifying that the codec-name "Huffman(M=4,
p_f)" in summary uses the same Zipf-1 p_y as section 10.6 setup
states. The paper's claim that "Huffman" means "Huffman from p_y" is
unambiguous in context but a reader could ask for explicit p_y in the
results table caption.

**METH-MIN-5 (cell |Y| = 8 vs n = 4 vs n = 5)**. The Setup paragraph
mixes |Y| (codomain size) and n (cipher value space dimension). E3
sweep uses M = 3, M = 4 (cipher value space dimensions, equivalent
to n). Are M and n always equal in these experiments? Yes, both
refer to bits in the cipher value codespace. Worth one
sentence aligning notation: "We use M as a synonym for n (bits of
cipher value space) in the empirical tables to match the underlying
experiment code."

**METH-MIN-6 (Section 10.6 sample size disclosure)**. Line 2562
states "Train and test sets are 5000 each at balanced class prior;
AUC is Mann-Whitney U with tie correction." Good. But the E3 paragraph
(lines 2640 to 2641) says "10,000 trials per replicate" without
clarifying whether trials are member queries, filler queries, or
balanced. Worth a one-sentence note.

**METH-MIN-7 (reproducibility paragraph misses E5/Pareto)**.
Section 10.3 reproducibility paragraph (lines 2459 to 2468) cites
e1_bloom_baseline.py but does not cite the experiment files for the
Le Cam tightness table or the Pareto frontier. R7 carry-over: section
10.6 has no separate reproducibility paragraph at all.

### Suggestions

**METH-SUG-1 (consolidate experiments section)**. Section 10.6 has
five distinct paragraphs (Setup, Le Cam tightness, Pareto, multi-
instance, randomized encoding K sweep, threat model scope, Summary)
spanning ~120 lines. A consolidated experiments table at the top of
the section would help orientation:

| Experiment | Replicates | Cells | Underlying file |
|---|---|---|---|
| Le Cam tightness | 1 | 5 | (not committed; single-run) |
| (TV, L) Pareto | 1 (analytical) | 14 | (not committed) |
| Multi-instance E3 | 10 | 25 | e3_codec_replicated.py |
| Randomized encoding E4 | 5 | 36 | e4_rand_encoding_sweep.py |
| Threat model scope | 1 | 3 | (not committed; single-run) |

This makes the methodological seams (single-run vs replicated,
committed vs not) visible at one glance.

**METH-SUG-2 (publish remaining experiment scripts)**. Committed:
e1, e3, e4. Uncommitted: Le Cam tightness, Pareto frontier, threat
model scope. Publishing these to the same experiments directory would
close R7's reproducibility carry-over fully.

**METH-SUG-3 (e1 against Xor/Ribbon baselines)**. The Bloom-baseline
result is informative but Bloom is no longer the modern SOTA for
approximate membership. Xor filters (Graf-Lemire 2020) and Ribbon
filters (Dillinger-Walzer 2021) achieve below-Bloom space at similar
construction cost. Adding these as additional rows in Table 10.x at
lines 2419 to 2438 would land the practical-overhead story against
the current frontier rather than 1970-era baseline. Lower priority
than METH-MAJ-1 to 3.

**METH-SUG-4 (e4 t > 4 cells)**. E4 sweeps t in {2, 3, 4}. The
paper's headline figure 132x defense is at t = 5 (in section 8.3
numerical example). Adding t = 5 to E4 would let the same source
underwrite both the §8.3 numerical illustration and the §10.6
empirical claim. Currently §8.3 says "for |Y| = 8 ... at t = 5" and
§10.6 §8.3 numerical follow-on at line 2655 says "at t = 5" but no
underlying E4 t=5 cell exists. The §10.6 t=5 claim must therefore
be coming from another source (E3 perhaps, which does sweep t=1 to
5). Worth verifying.

Cross-check: E3 results at Huffman(M=4) t=5: predicted 0.9844,
empirical 0.9830. Paper §10.6 (lines 2657 to 2659) says "Shannon-
optimal Huffman partition produces attacker accuracy approximately
0.984", matches Huffman(M=4) t=5 = 0.9830. So the §10.6 132x defense
claim at t=5 comes from E3 (which is 10-rep, 100K trial), not E4
(which is 5-rep). E4 supports only the H1/H2/H3 randomized-encoding
claims. This is fine but the paper text could clarify which empirical
result underwrites which claim.
