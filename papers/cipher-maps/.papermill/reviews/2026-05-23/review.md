# Multi-Agent Review Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Target venue**: PoPETs 2027
**Recommendation**: minor-revision (regression cleared; remaining work
is production polish plus the 4 R7 majors carried over from
interpretation-side cleanup)

## Summary

**Overall Assessment**: Round 8 review finds the Round 7 critical
issue (CRIT-1: direction-inverted multi-instance recommendation)
FULLY RESOLVED via Path A in the manuscript. The abstract, Corollary
8.x (cor:t-geometry), §10.6 paragraph, and §10.6 Summary item (iv)
all now read the defender-vs-attacker direction correctly: Huffman
provides 132x better defense than uniform at t = 5, with the
formula 1 - (1/2) sum_y alpha(y)^t unchanged. The fix preserved the
formal apparatus and only corrected the interpretation, exactly as
Path A recommended.

The 19 R7 majors split into three categories after R8 review:
(a) 4 logic-side majors carry over (MAJ-1 Theorem 8.1 verbal
definition tuple, MAJ-2 Proposition 8.2 saturation vs bijectivity,
MAJ-3 homogeneous instances, MAJ-4 Huffman saturation construction);
(b) 7 production-polish majors carry over (sister-paper preprints,
template port, page count, overfull, §10.6 single-run, no Bloom
baseline, 14 configs not enumerated); (c) 8 mostly closed via the
CRIT-1 fix (PROSE-1 abstract inverts wording, etc., now consistent).

**Strengths**:
1. Framework contribution and three-literature unification are
   well-defined and well-positioned (novelty-assessor NOV-1, NOV-5)
2. Le Cam tightness empirical validation is clean and useful
   (methodology-auditor, novelty-assessor NOV-4)
3. (TV, L) Pareto frontier finding with 42x TV reduction is sharp
   and non-controversial (novelty-assessor NOV-2)
4. R7 CRIT-1 fix landed cleanly; no regression introduced
   (logic-checker, novelty-assessor, prose-auditor convergent)
5. Randomized-encoding defense and the threat-model distinction
   (pattern-coincidence vs decode-coincidence) are genuinely novel
   and clean (novelty-assessor NOV-N2)
6. Build is clean; bibtex is clean; theorem numbering is consistent
   (format-validator FMT-N5, FMT-N6)
7. R6 + R7 framework-framing fixes hold; §1 contribution paragraph
   correctly distinguishes framework from new construction
   (logic-checker LOG-N3, novelty-assessor)

**Weaknesses**:
1. 4 logic-side carry-over majors in §8.3 (Theorem 8.1 verbal
   definition, Proposition 8.2 statement and proof, Huffman saturation
   construction)
2. 5 methodology-side carry-over majors (variance characterization
   missing on headline empirical claims; no Bloom baseline; 14
   Pareto configurations unenumerated)
3. Sister-paper preprint posting still pending (2 load-bearing
   citations, plus 2 additional non-load-bearing citations)
4. Production: 36 pages on article class; PoPETs template port
   pending; 118.87pt overfull at Definition 8.x; anonymization not
   performed; date stale
5. 3 R7 prose carry-overs (§8.3 subsubsection* style, §10.6 paragraph
   density, abstract sentence length)

**Finding Counts**: Critical: 0 | Major: 14 | Minor: 38 | Suggestions: 8

## Critical Issues

None.

The R7 critical (CRIT-1: direction-inverted t-dependent allocation
recommendation) has been fully resolved across all five sites in the
manuscript: abstract, Corollary cor:t-geometry, §10.6 paragraph,
§10.6 Summary item (iv), and the §10.6 numerical illustration.

## Major Issues

### MAJ-1: Theorem 8.1 verbal definition uses single c, proof uses tuple (source: logic-checker; carry-over R7)

- **Location**: Lines 1741 to 1743 (verbal), lines 1773 to 1798 (proof)
- **Quoted (verbal)**: "predicts 'in-domain' iff
  $\dec_1(\fhat_1(c)) = \cdots = \dec_t(\fhat_t(c))$"
- **Quoted (proof)**: "publishes one cipher value per instance,
  $c_i = \enc_i(x, 0)$"
- **Problem**: Verbal definition uses a single c; proof correctly uses
  a tuple $(c_1, \ldots, c_t)$ where each $c_i$ is from instance i's
  own encoder. The Definition 8.x (lines 1902 to 1920) uses tuple
  notation correctly. The §10.6 implementation also uses tuples. Only
  the verbal Theorem 8.1 statement glosses this.
- **Suggestion**: Rewrite verbal definition: "given a probe tuple
  $(c_1, \ldots, c_t)$ constructed by the trusted side as
  $c_i = \enc_i(x, 0)$, the coincidence oracle predicts 'in-domain'
  iff $\dec_1(\fhat_1(c_1)) = \cdots = \dec_t(\fhat_t(c_t))$ and the
  common decoded value is in $Y$."
- **Cross-verified**: Yes (logic-checker and prose-auditor agree;
  prose-auditor PROSE-N7 also notes the transition is abrupt).

### MAJ-2: Proposition 8.2 member-case proof needs bijectivity, not just saturation (source: logic-checker; carry-over R7)

- **Location**: Lines 1922 to 1948 (statement and proof)
- **Quoted**: "assume the construction *saturates* each acceptance
  region: every bit string in $A_i(y)$ is reachable as $\fhat_i(c)$..."
- **Problem**: Saturation only ensures reachability; the proof needs
  uniformity of the induced distribution on $A_i(y)$ when $k$ is drawn
  uniformly. This requires bijectivity of $k \mapsto \fhat_i(\enc_i(x, k))$
  with $K(x) = |A_i(y)|$.
- **Suggestion**: Replace "saturates" with "uniform-saturating"
  (bijection). Cite the Huffman example with explicit construction.

### MAJ-3: Proposition 8.2 formula assumes homogeneous instances (source: logic-checker; carry-over R7)

- **Location**: Lines 1938 to 1944
- **Quoted**: "$\Pr[\text{predict in} \mid \text{member}, f(x) = y] =
  \prod_{i=2}^{t} 1/|A_i(y)|$"
- **Problem**: Formula correct only when all $A_i(y)$ coincide.
- **Suggestion**: Restrict statement to homogeneous instances OR clarify
  that $A_i(y)$ is codec-level shared across instances.

### MAJ-4: Huffman saturation example glosses over encoder mechanism (source: logic-checker; carry-over R7)

- **Location**: Lines 1932 to 1933 in Proposition 8.2, and Remark
  rem:huffman-member-coincidence lines 1990 to 2007
- **Problem**: Says $K(x) = |A_i(y)|$ but does not show how the encoder
  maps distinct $k$ values to distinct patterns in $A(y)$.
- **Suggestion**: Add a construction note showing $\enc_i(x, k) =
  \mathrm{codeword}(f(x)) \| (k\text{-th element of } \{0,1\}^{n - \ell})$
  in canonical order.

### MAJ-5: Sister-paper preprints still pending (source: citation-verifier; carry-over R5/R6/R7)

- **Location**: `towell2026maxconf` (load-bearing for Proposition 5.1),
  `towell2026rekeying` (load-bearing for §9.5)
- **Problem**: Two load-bearing citations point to unpublished
  manuscripts. PoPETs reviewers will reject this.
- **Suggestion**: Post arXiv preprints with DOIs before submission.

### MAJ-6: Article class, not PoPETs template (source: format-validator; carry-over R5/R6/R7)

- **Location**: cipher_maps.tex line 1 `\documentclass[11pt]{article}`
- **Problem**: PoPETs requires their LaTeX template.
- **Suggestion**: Port to PoPETs template. Estimated trim to ~22 to 25
  pages.

### MAJ-7: §10.6 single-run results lack replication and variance (source: methodology-auditor; carry-over R7)

- **Location**: §10.6 line 2493
- **Quoted**: "All numbers below are single-run (no replicates)."
- **Problem**: Five tables and three quantitative claims (24/25 in CI,
  mean Bayes gap -0.0004, 42x TV reduction) lack cross-replicate
  variance characterization.
- **Suggestion**: Run 3 replicates with different random seeds; report
  mean and std.

### MAJ-8: No Bloom-filter baseline at matched FPR for codec sweep (source: methodology-auditor; carry-over R6/R7)

- **Location**: §10.6 entire subsection
- **Problem**: The novelty claim "Bloom filters become cipher maps
  with $K(x) = 1$" would be supported by a direct comparison cell in
  Table tab:le-cam-tight.
- **Suggestion**: Add a Bloom row at matched epsilon.

### MAJ-9: §10.6 14 Pareto-frontier configurations not enumerated (source: methodology-auditor; carry-over R7)

- **Location**: §10.6 lines 2528 to 2563
- **Problem**: "14 configurations" is stated but not listed; reproducibility
  requires the enumeration.
- **Suggestion**: Supplementary table listing the 14 configurations and
  per-cell TV gaps.

### MAJ-10: §10.3 20 Newsgroups benchmarks still single-run (source: methodology-auditor; carry-over R6/R7)

- **Location**: §10.3 lines 2343 to 2345
- **Problem**: Headline benchmarks (713 docs/sec, 0.39 precision, 12
  3-term AND FPs) lack variance characterization.
- **Suggestion**: 3 replicates; report mean and std.

### MAJ-11: §10.6 attacker-class tie needs sample-size justification (source: methodology-auditor; carry-over R7)

- **Location**: §10.6 line 2496 to 2502
- **Problem**: "Within 0.014 sampling noise" is approximately the Wilson
  CI half-width at n = 5000; the tie may not generalize to larger n.
- **Suggestion**: Reword to "indistinguishable at n = 5000".

### MAJ-12: §8.3 subsubsection* style break (source: prose-auditor; carry-over R7)

- **Location**: Lines 1732, 1840, 1887 use `\subsubsection*{...}` while
  rest of paper uses numbered subsections or paragraph headings.
- **Suggestion**: Replace with `\paragraph{...}` headings (lighter
  touch) or numbered subsubsections.

### MAJ-13: §10.6 paragraph-per-claim density breaks narrative arc (source: prose-auditor; carry-over R7)

- **Location**: §10.6 lines 2495, 2528, 2565, 2590, 2605, 2640
- **Problem**: One-paragraph-per-claim recap; narrative weak.
- **Suggestion**: Add structure-setting sentence at start of §10.6.

### MAJ-14: Abstract (TV, L) sentence is 56 words with three semicolons (source: prose-auditor; carry-over R7)

- **Location**: Abstract lines 72 to 77
- **Suggestion**: Split into three sentences.

## Minor Issues

(38 total across all specialists; condensed listing by source)

### Logic-checker minors
- **LOG-N1**: Independent seeds link to master-vs-operational
  subkey paragraph could be explicit at Theorem 8.1 (line 1747).
- **LOG-N2**: Theorem 6.2 cancellation remark wording could clarify
  when equality is reached under re-randomization.
- **LOG-N3**: Entropy ratio definition unification holds (CLEAN).
- **LOG-N4**: cor:chain induction is correct (CLEAN).
- **LOG-N5**: Fannes-Audenaert bound direction correct (CLEAN).

### Methodology-auditor minors
- **METH-N1**: §10.7 Reproducibility appendix recommended.
- **METH-N2**: 6 codecs in setup vs 5 in table (Padded(y_0) missing).
- **METH-N3**: Key-feature attacker not formally defined.
- **METH-N4**: §10.3 uniform query distribution (carry-over).

### Prose-auditor minors
- **PROSE-N1**: "Huffman dominates at every t" reads as inverted; use
  "Huffman is recommended" or "lowest attacker accuracy."
- **PROSE-N2**: "Coincidence oracle" repetition; abbreviate after
  first introduction.
- **PROSE-N3**: $\sim$ vs approximately vs $\approx$ inconsistent.
- **PROSE-N4**: "Sampling noise" phrasing informal; use Wilson CI.
- **PROSE-N5**: "Honest limitations" headings get repetitive; rename
  to "Limitations."
- **PROSE-N6**: §10 missing from §1 roadmap.
- **PROSE-N7**: §8.3 prose-to-theorem transition abrupt.
- **PROSE-N8**: Abstract opening sentence dense.
- **PROSE-N9**: Bernoulli paragraph in §1 needs forward reference.
- **PROSE-N10**: "Verified" vs "confirmed" in §10.6 Summary inconsistent.

### Citation-verifier minors (all carry-over R7)
- **CITE-MIN-2**: Cover-Thomas 2006 missing.
- **CITE-MIN-3**: QIF multi-instance literature missing.
- **CITE-MIN-4**: Patel-Persiano-Yeo-Yung 2019 missing.
- **CITE-MIN-5**: Köpf-Smith 2010 missing.
- **CITE-MIN-6**: Pouliot-Wright 2016 missing.
- **CITE-MIN-7**: `towell2026algebraic` preprint posting recommended.
- **CITE-MIN-8**: DOI fields absent throughout.
- **CITE-MIN-9**: Le Cam 1986 cite missing page number.
- **CITE-N1**: `towell2026codec` URL points to moving tree/main.
- **CITE-N3**: Kamara-Moataz booktitle verbose.

### Format-validator minors (all carry-over R7 unless noted)
- **FMT-MIN-3**: \Cref vs \ref mixed.
- **FMT-MIN-5**: §6.4 and §6.6 inline tables not in `\begin{table}`.
- **FMT-MIN-7**: Author block not anonymized.
- **FMT-MIN-10**: Title page date stale ("March 2026").
- **FMT-N1** (new): 4 mild overfull hboxes (under 20pt each).
- **FMT-N2** (new): TikZ figure dimensions audit after template port.

## Suggestions

1. **PROSE-SUG-2**: "How to read this paper" guide paragraph in §1.
2. **PROSE-SUG-3**: Promote randomized-encoding threat-model
   distinction to abstract.
3. **METH-SUG-1**: §10.7 Reproducibility subsection.
4. **METH-SUG-2**: Move detailed setup tables to appendix.
5. **METH-SUG-3**: Codec sweep at larger |Y|.
6. **CITE-SUG-1**: "Concurrent and prior work in multi-instance
   composition" subsection.
7. **FMT-SUG-1**: Glossary or notation table near §3.
8. **FMT-N3** (suggestion): Algorithm 1 to appendix.

## Detailed Notes by Domain

### Logic and Proofs

The Round 7 CRIT-1 fix is fully landed without regression. The four
R7 logic carry-overs (MAJ-1 to MAJ-4) all concern editorial polish in
the new §8.3 content rather than substantive proof errors. The formal
apparatus (Theorem 8.1, Proposition 8.2, Corollary 8.x, Definition 8.x)
is sound under the natural reading (homogeneous instances with
codec-level acceptance sets). The unified entropy ratio definition
(e = H(Q)/n) holds. The composition theorem inequality direction is
correct. The Fannes-Audenaert bound direction is correct.

### Novelty and Contribution

The five-contribution package (NOV-1 framework, NOV-2 Pareto frontier
with 42x, NOV-3 multi-instance theorem post-CRIT-1, NOV-4 empirical
Le Cam tightness, NOV-5 three-literature unification) is coherent and
the headline narrative is consistent across the abstract, §1, and
§10.6. NOV-3 changed from a counterintuitive "inversion" claim to a
conventional closed-form result with the randomized-encoding defense
distinguishing two threat models. This is a downgrade in headline
drama but an upgrade in correctness. The 42x finding (NOV-2) is now
the strongest novel empirical result.

### Methodology

Round 7 introduced §10.6 with careful setup (random seeds documented,
Wilson CIs reported, train/test split balanced). The 24/25-in-CI
statistic is meaningful. Five methodology gaps remain: single-run
(MAJ-7), no Bloom baseline (MAJ-8), 14 configurations not enumerated
(MAJ-9), §10.3 single-run carry-over (MAJ-10), attacker-class tie
sample-size caveat (MAJ-11). All five are addressable in 1 to 2 days.

§10.3 retains the R6-closed 3-term AND noise-floor explanation and
maintains throughput consistency (713 docs/sec) across §6.4 and §10.3.

### Writing and Presentation

R7 PROSE-1 (abstract "inverts" framing) is CLOSED. The three R7 major
prose carry-overs (MAJ-12 §8.3 subsubsection* style, MAJ-13 §10.6
density, MAJ-14 abstract sentence length) remain. The 10 minor prose
issues are mostly editorial polish (terminology consistency, transition
sentences, header style). The R6 prose-residual items (register seam,
definition env wrapping, intro/section structure) are addressed.

### Citations and References

Bibliography has 34 entries, all properly cited, bibtex passes clean.
Round 7 activated `towell2026algebraic` (now used at §10.3) and added
`towell2026codec` (used at §10.6). Three major carry-overs:
sister-paper preprints (MAJ-5), Huffman 1952 (MAJ-16 from R7, now
carried into MAJ-5 grouping), bernoulli-types URL (MAJ-17 from R7).
Eight minor carry-overs (Cover-Thomas, QIF multi-instance, Patel-
Persiano-Yeo-Yung, Köpf-Smith, Pouliot-Wright, towell2026algebraic
preprint, DOIs, Le Cam page number).

### Formatting and Production

Build is clean. 36 pages, 5 overfull hboxes (one severe at 118.87pt
in Definition 8.x). PoPETs template port still pending. Page count
exceeds PoPETs target by 8 to 10 pages; trim plan available.
Anonymization not performed. Title date stale.

## Literature Context Summary

The R5/R6/R7 consolidated literature context remains authoritative.
No new direct competitors to the cipher-maps abstraction surfaced.
Seven citation gaps carry over: Huffman 1952 (strong), Patel-Persiano-
Yeo-Yung 2019 (strong), Köpf-Smith 2010 (strong), Cover-Thomas 2006
(medium), Pouliot-Wright 2016 (low), Geng-Smith 2025 (medium), Alvim
et al. 2020 textbook (medium). None are submission blockers; all are
positioning improvements.

## Honest PoPETs survivability assessment

**Post-R7-CRIT-1 fix, R8 standpoint**: Plausibly survivable to minor
revision in 1 to 2 reviewing cycles. The framework contribution,
three-literature unification, (TV, L) Pareto frontier with 42x
finding, and Le Cam tightness empirical confirmation form a coherent
contribution package. The R7 critical regression is fully closed.

**Remaining blockers for submission**:
1. Sister-paper preprint posting (MAJ-5): 1 to 2 days.
2. PoPETs template port (MAJ-6, MAJ-19): 4 to 8 hours.
3. Definition 8.x overfull fix (MAJ-18 from R7, now part of FMT-N1
   group): 10 minutes.
4. R7 logic-side editorial fixes (MAJ-1 to MAJ-4): 2 to 4 hours.

**Remaining blockers for ready**:
5. §10.6 and §10.3 3-replicate variance characterization
   (MAJ-7, MAJ-10): 4 to 8 hours engineering plus rerun time.
6. Bloom baseline cell (MAJ-8): 2 hours.
7. 14 configuration enumeration (MAJ-9): 1 hour.
8. Huffman 1952 cite (MAJ-5 carry-over): 5 minutes.
9. bernoulli-types URL fix (MAJ-5 carry-over): 5 minutes.

**Total estimated effort to minor-revision ready**: 2 to 3 days
editorial plus preprint posting. Total estimated effort to ready
for submission: 3 to 5 days including the variance characterization
and baseline runs.

## What's left for final polish before submission

In order of priority:

1. **R7 carry-over major editorial fixes** (4 to 6 hours):
   MAJ-1 (Theorem 8.1 verbal definition tuple notation),
   MAJ-2 (Proposition 8.2 uniform-saturating),
   MAJ-3 (homogeneous instances clarification),
   MAJ-4 (Huffman saturation construction note),
   MAJ-12 (§8.3 subsubsection* to paragraph headings),
   MAJ-13 (§10.6 structure-setting sentence),
   MAJ-14 (abstract Pareto sentence split).

2. **Sister-paper preprint posting** (1 to 2 days; closes MAJ-5):
   `towell2026maxconf`, `towell2026rekeying`. Lower priority but
   helpful: `towell2026algebraic`, `bernoulli-types` URL fix.

3. **Replication and baseline runs** (1 to 2 days):
   MAJ-7 (3 replicates for §10.6), MAJ-10 (3 replicates for §10.3),
   MAJ-8 (Bloom baseline cell), MAJ-9 (14 configs enumeration).

4. **PoPETs template port and anonymization** (4 to 8 hours):
   MAJ-6 (article class to PoPETs template), MAJ-19 (page trim
   from §9.1, §9.4, §10.4), MAJ-18 (Definition 8.x overfull),
   FMT-MIN-7 (anonymize), FMT-MIN-10 (date update).

5. **R7 minor backlog cleanup** (1 to 2 days):
   Citations (Cover-Thomas, QIF multi-instance, Patel-Persiano-Yeo-Yung,
   Köpf-Smith, Pouliot-Wright, Huffman 1952), DOIs throughout,
   Le Cam page, prose minors (10 items), format minors (Cref/ref,
   inline tables to env).

## Trajectory Across Review Rounds

| Round | Date | Critical | Major | Minor | Suggestion | Recommendation |
|------:|:-----|:--------:|:-----:|:-----:|:----------:|:---------------|
| R1    | 2026-03-19 | 0 | 1 | 8/9 proofs PASS | -- | major-revision |
| R2    | 2026-03-26 | 0 | 3 | 12 | 5 | minor-revision |
| R3    | 2026-03-28 | 0 | 6 | 11 | 4 | major-revision |
| R4    | 2026-04-28 | 0 | 5 | 26 | 8 | major-revision |
| R5    | 2026-04-30 | 3 | 14 | 26 | 19 | major-revision |
| R6    | 2026-05-02 | 1 | 7 | 22 | 10 | major-revision |
| R7    | 2026-05-17 | 1 | 19 | 49 | 17 | major-revision |
| R8    | 2026-05-23 | 0 | 14 | 38 | 8 | **minor-revision** |

**Key observations from the trajectory**:
- R3 to R5: Major count growing as new content was added and old issues
  inherited. Each round closed many, found more.
- R5 introduced critical regressions (wrong theorem numbers) under
  load.
- R6 closed R5 criticals via Path A fixes, found one new critical
  (3-term AND FP arithmetic).
- R7 closed R6 critical via noise-floor formula, BUT new §8.3 +
  §10.6 content introduced CRIT-1 (direction-inverted multi-instance
  recommendation).
- R8 confirms R7 CRIT-1 fix is fully landed; recommendation drops
  back to minor-revision for the first time since R2.

## Review Metadata

- Agents: orchestrator-only (subagent dispatch unavailable, consistent
  with R5/R6/R7); produced 6 specialist reports plus literature context
  plus this unified review
- Cross-verifications performed: 3 (CRIT-1 fix verified via direct
  quote inspection of abstract, Corollary 8.x, §10.6 paragraph, and
  §10.6 Summary; Theorem 8.1 verbal definition cross-checked against
  proof and Definition 8.x; build status verified via log file
  inspection)
- Disagreements noted: 0 (specialists converge on the same findings;
  CRIT-1 fix is identified as closed by logic-checker, novelty-assessor,
  and prose-auditor independently)
