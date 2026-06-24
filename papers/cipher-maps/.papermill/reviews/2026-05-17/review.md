# Multi-Agent Review Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Target venue**: PoPETs 2027
**Recommendation**: major-revision (regression from R6 due to CRIT-1; the
new multi-instance content surfaced a load-bearing direction-of-inequality
error in the central new contribution)

## Summary

**Overall Assessment**: Round 7 introduces ambitious new content (the
multi-instance composition theorem in §8.3 and the codec-security
empirical study in §10.6) backed by a thesis v3 framework-first
restructure. The formal proofs are mostly sound, but the central new
finding (the "inversion" of single-instance Shannon recommendation at
$t \geq 2$) is structurally inverted: the formula and empirical numbers
are correct, but the defender-vs-attacker direction is reversed. Huffman
allocation provides better multi-instance defense than uniform, not
worse. This propagates through the abstract, intro, Corollary 8.x,
and §10.6 summary. The paper is otherwise in good shape, with R6's
seven majors substantively addressed, but this single critical issue
requires nontrivial revision to the v3 thesis before the paper survives
PoPETs review.

**Strengths**:
1. Framework contribution and three-literature unification are
   well-defined and well-positioned (novelty-assessor NOV-1, NOV-5)
2. Le Cam tightness empirical validation is clean and useful
   (methodology-auditor, novelty-assessor NOV-4)
3. (TV, L) Pareto frontier finding with 42x TV reduction is a sharp,
   non-controversial empirical contribution (novelty-assessor NOV-2)
4. R6 majors substantively addressed: entropy ratio definition
   unified, Theorem 6.2 Step 2 separated storage/search costs,
   throughput numbers consistent, framework framing added to §1
   (logic-checker, methodology-auditor verification)
5. Randomized-encoding defense is genuinely novel and clean
   (novelty-assessor NOV-3 partial)
6. Threat model decomposition (§5 value-side, §8.3 multi-instance,
   §9.6 key-side) is consistent and well-motivated (logic-checker,
   prose-auditor)
7. Build is clean (no undefined refs, no multiply-defined labels)
   (format-validator)

**Weaknesses**:
1. CRIT-1: Direction of multi-instance recommendation inverted
   (logic-checker, novelty-assessor, prose-auditor)
2. Five major issues across logic, methodology, citations
3. Sister-paper preprint posting still pending (carry-over from R5/R6)
4. Page count grew to 36 (PoPETs target is 18-20 in their template,
   roughly 25-28 in article-class)
5. §10.6 single-run results lack variance characterization
6. Several proof technicalities in Proposition 8.2 (saturation vs
   bijectivity, heterogeneous instance formula)

**Finding Counts**: Critical: 1 | Major: 19 | Minor: 49 | Suggestions: 17

## Critical Issues

### CRIT-1: Direction of t-dependent allocation recommendation is inverted (source: logic-checker, cross-verified)

- **Location**: Abstract line 80-83, Corollary 8.x at lines 1846-1858,
  §10.6 paragraph "Multi-instance leakage and the coincidence oracle"
  at lines 2555-2573, Summary item (iv) at lines 2640-2643
- **Quoted text (abstract)**:
  > "characterizes multi-instance leakage and inverts the
  > single-instance Shannon recommendation at $t \geq 2$."
- **Quoted text (Corollary 8.x)**:
  > "$t \geq 2$ shared-$f$ optimum: $\alpha(y) = \varepsilon/|Y|$
  > (uniform allocation) minimizes coincidence-oracle leakage"
- **Quoted text (§10.6)**:
  > "At $t = 5$, the uniform Dense partition achieves accuracy
  > $\approx 0.9999$ while the Shannon-optimal Huffman partition
  > achieves $\approx 0.984$; the uniform allocation defends $\approx
  > 16\times$ better at large $t$ in this configuration."
- **Problem**: The formula (Theorem 8.1) and empirical numbers are
  both correct, but the interpretation is reversed. Coincidence-oracle
  accuracy = $1 - \tfrac{1}{2}\sum_y \alpha(y)^t$ is the *attacker's
  classification accuracy*. Higher accuracy means the attacker is more
  successful, i.e. worse for the defender. By Jensen, convexity of
  $x^t$ at fixed $\sum_y \alpha(y) = \varepsilon$:
  - Uniform: $\sum_y \alpha(y)^t = \varepsilon^t / |Y|^{t-1}$, MINIMUM
    of $\sum$, so MAXIMUM accuracy, WORST defense.
  - Skewed Huffman: $\sum_y \alpha(y)^t \approx (\max_y \alpha)^t$,
    LARGER $\sum$, so SMALLER accuracy, BETTER defense.

  Verified numerically: at $|Y|=8, t=5$:
  - Uniform: attacker accuracy = 0.99988 (error 0.00012)
  - Huffman: attacker accuracy = 0.98387 (error 0.01613)
  - Huffman provides $\approx 132\times$ higher attacker error rate
    (better defense), not $16\times$ less, and not in the uniform
    direction.

  The Huffman codec wins at every $t$ in the experiment (single-instance
  TV-min AND multi-instance coincidence-cover), so there is no
  "inversion".

  The paper inherits this inversion from the bernoulli experiment
  writeup `RESULTS_14.md`, which makes the same misreading in its
  "Defense implications" section. The formula derivation and
  empirical numbers are both correct; only the defender-vs-attacker
  reading is reversed.

- **Suggestion**: Pick one of two paths.

  Path A (recommended): preserve the formula, fix the interpretation.
  Rewrite abstract, Corollary 8.x, §10.6 paragraph, and Summary item
  (iv) to say Huffman (or any skewed allocation with larger $\max_y
  \alpha(y)$) provides BOTH single-instance frequency hiding (small
  TV) AND multi-instance coincidence cover (slow attacker accuracy
  growth). The thesis loses the "inversion" framing but recovers a
  true finding: the dominant value in Huffman provides a
  high-probability decoy lane for filler queries.

  Path B: redefine the attacker to make a genuine inversion exist.
  E.g., consider a distinguish-which-value attacker that exploits
  the distribution of the common coincidence value. This would
  inversely favor uniform (less info in the common value), giving the
  inversion the abstract claims. Requires new formal analysis.

  Either path requires substantive revision of the v3 thesis.

- **Cross-verified**: Yes. Verified against bernoulli experiment file
  (`RESULTS_14.md`), Python source (`14_coincidence_oracle.py`, where
  `accuracy_empirical = correct / n_total` is unambiguously
  classification accuracy), the Theorem 8.1 proof (which correctly
  derives accuracy = $1 - \tfrac{1}{2} \sum_y \alpha(y)^t$), and
  direct numerical computation. Cross-verified against methodology
  audit: experimental setup is sound, the formula matches empirical
  results, only the conclusion is reversed.

## Major Issues

### MAJ-1: Theorem 8.1 verbal definition uses single c, proof uses tuple (source: logic-checker)

- **Location**: Lines 1738-1740 (verbal definition) vs lines 1770-1798
  (proof)
- **Quoted (verbal)**: "predicts in-domain iff $\dec_1(\fhat_1(c)) =
  \cdots = \dec_t(\fhat_t(c))$"
- **Quoted (proof)**: "publishes one cipher value per instance, $c_i =
  \enc_i(x, 0)$"
- **Problem**: Verbal definition uses a single $c$; proof correctly
  uses a tuple $(c_1, \ldots, c_t)$ where each $c_i$ is from instance
  $i$'s own encoder. These are different attack models.
- **Suggestion**: Rewrite verbal definition to use the tuple-probe
  notation matching the proof and Definition 8.x (pattern/decode
  attackers).
- **Cross-verified**: Yes, prose-auditor reads the verbal definition
  the same way.

### MAJ-2: Proposition 8.2 member-case proof needs bijectivity, not just saturation (source: logic-checker)

- **Location**: Lines 1918-1926 (statement), 1950-1961 (proof)
- **Quoted text**: "assume the construction \emph{saturates} each
  acceptance region: every bit string in $A_i(y)$ is reachable as
  $\fhat_i(c)$..."
- **Problem**: Saturation only ensures reachability; the proof needs
  uniformity of the induced distribution on $A_i(y)$ when $k$ is
  drawn uniformly. This requires bijectivity of $k \mapsto
  \fhat_i(\enc_i(x, k))$, with $K(x) = |A_i(y)|$.
- **Suggestion**: Replace "saturates" with "uniform-saturating"
  (bijection). Cite the Huffman example with the explicit construction.

### MAJ-3: Proposition 8.2 formula assumes homogeneous instances (source: logic-checker)

- **Location**: Line 1929-1932
- **Quoted**: "$\Pr[\text{predict in} \mid \text{member}, f(x) = y] =
  \prod_{i=2}^{t} 1/|A_i(y)|$"
- **Problem**: Formula is correct only when all $A_i(y)$ coincide
  (homogeneous instances). For heterogeneous $A_i(y)$, the formula
  involves $|\bigcap_i A_i(y)|$.
- **Suggestion**: Restrict statement to homogeneous instances OR
  clarify that $A_i(y)$ refers to codec-level acceptance set (same
  across instances).

### MAJ-4: Huffman saturation example glosses over encoder mechanism (source: logic-checker)

- **Location**: Line 1923-1924
- **Quoted**: "Huffman codespace classes where $K(x)$ equals the
  codespace class size $2^{n - \ell_{f(x)}}$"
- **Problem**: Says $K(x) = |A_i(y)|$ but does not show how the
  encoder maps distinct $k$ values to distinct patterns in $A(y)$.
- **Suggestion**: Add a construction note for the Huffman case.

### MAJ-5: Sister-paper preprints still pending (source: citation-verifier, carry-over from R5/R6)

- **Location**: References.bib entries `towell2026maxconf`,
  `towell2026rekeying`
- **Problem**: Two load-bearing citations remain at "Manuscript in
  preparation". The Proposition 5.1 confidentiality bound cites
  [Theorem 4.1, part 3] in towell2026maxconf; the bounded-composition
  discussion at §9.5 cites [Thm. 7.1] in towell2026rekeying.
  PoPETs reviewers will not accept these.
- **Suggestion**: Post arXiv preprints with DOIs before submission.

### MAJ-6: Article class still in use, not PoPETs template (source: format-validator, carry-over)

- **Location**: cipher_maps.tex line 1
- **Quoted**: `\documentclass[11pt]{article}`
- **Problem**: PoPETs requires their LaTeX template. Current build is
  36 pages.
- **Suggestion**: Port to PoPETs template; estimated trim to ~22-25
  pages.

### MAJ-7: §10.6 single-run results lack replication and variance (source: methodology-auditor)

- **Location**: §10.6 line 2483
- **Quoted**: "All numbers below are single-run (no replicates)."
- **Problem**: Five tables and three quantitative claims (24/25 in CI,
  mean Bayes gap -0.0004, 42x TV reduction) lack cross-replicate
  variance.
- **Suggestion**: Run 3 replicates with different random seeds; report
  mean and std.

### MAJ-8: No Bloom-filter baseline at matched FPR for codec sweep (source: methodology-auditor, carry-over R6 METH-N4)

- **Location**: §10.6 entire subsection
- **Problem**: The novelty claim "Bloom filters become cipher maps
  with $K(x) = 1$, etc." would be supported by a direct comparison
  cell.
- **Suggestion**: Add a Bloom row to Table `tab:le-cam-tight` at
  matched $\varepsilon$.

### MAJ-9: §10.6 14 Pareto-frontier configurations not enumerated (source: methodology-auditor)

- **Location**: §10.6 line 2524-2527
- **Problem**: "14 configurations" is stated but not listed.
  Reproducibility requires the enumeration.
- **Suggestion**: Supplementary table listing the 14 configurations
  and per-cell TV gaps.

### MAJ-10: §10.3 20 Newsgroups benchmarks still single-run (source: methodology-auditor, carry-over R6)

- **Location**: §10.3 line 2333-2335
- **Problem**: Headline benchmarks (713 docs/sec, 0.39 precision, 12
  3-term AND FPs) lack variance characterization.
- **Suggestion**: 3 replicates; report mean and std.

### MAJ-11: §10.6 attacker-class "tie" needs sample-size justification (source: methodology-auditor)

- **Location**: §10.6 line 2486-2492
- **Problem**: "All three attackers achieve the same accuracy to
  within 0.014 sampling noise"; 0.014 is approximately the Wilson CI
  half-width at n=5000. The tie may not generalize to larger n.
- **Suggestion**: Reword to "indistinguishable at n=5000".

### MAJ-12: PROSE-1 abstract "inverts" claim is misleading (source: prose-auditor)

- **Location**: Abstract lines 80-83
- **Problem**: Prose embodiment of CRIT-1. Independent of the
  technical issue, the abstract creates an expectation the paper does
  not deliver on.
- **Suggestion**: After CRIT-1 fix, rewrite to match corrected
  interpretation.

### MAJ-13: §8.3 subsubsection style breaks paper convention (source: prose-auditor)

- **Location**: Lines 1729, 1837, 1878
- **Problem**: §8.3 uses three `\subsubsection*{...}` while rest of
  paper uses numbered subsections or paragraph headings.
- **Suggestion**: Replace with paragraph headings or numbered
  subsubsections.

### MAJ-14: §10.6 paragraph headings duplicate the formal-result structure (source: prose-auditor)

- **Location**: Lines 2485, 2518, 2555, 2575, 2590, 2625
- **Problem**: §10.6 reads as one-paragraph-per-claim recap; narrative
  arc is weak.
- **Suggestion**: Add a structure-setting sentence at start of §10.6.

### MAJ-15: Abstract sentence on (TV, L) Pareto frontier is awkward (source: prose-auditor)

- **Location**: Abstract lines 72-77
- **Problem**: 49-word sentence with three semicolon-joined clauses.
- **Suggestion**: Split into three sentences.

### MAJ-16: Huffman 1952 missing from bibliography (source: citation-verifier)

- **Location**: §10.6 Pareto frontier discussion
- **Problem**: Paper centers Huffman codes vs TV-optimal allocations;
  Huffman 1952 is standard reference.
- **Suggestion**: Add `huffman1952method` to bib; cite at §6.6 first
  Huffman mention.

### MAJ-17: `bernoulli-types` URL stale (source: citation-verifier)

- **Location**: bib entry line 49
- **Problem**: URL points to `github.com/queelius/bernoulli_sets`
  which is now part of the bernoulli monorepo at
  `github.com/queelius/bernoulli`.
- **Suggestion**: Update URL or split into specific sub-paper refs.

### MAJ-18: 118.9pt overfull hbox at Definition 8.x (source: format-validator)

- **Location**: Lines 1905-1910
- **Problem**: Long description-list label combined with long math
  expression overflows margin by ~1.6 inches; visible in PDF.
- **Suggestion**: Move math to display style or shorten via
  composition notation $\dec_i \circ \fhat_i$.

### MAJ-19: 36 pages exceeds PoPETs target by 8-10 pages (source: format-validator)

- **Location**: Whole paper
- **Problem**: Page count grew from 28 (R6) to 36 (R7) due to §8.3 +
  §10.6 additions.
- **Suggestion**: After PoPETs template port plus §9.1, §9.4, §10.4
  trim, target ~18-20 pages.

## Minor Issues

(49 total across all specialists; listed by source for brevity)

### Logic-checker minors
- MIN-1: Theorem 8.1 "members" case canonical-K(x)=1 link could be
  tighter
- MIN-2: General-prior crossover analysis is correct
- MIN-3: §10.6 Le Cam table doesn't show per-attacker columns
- MIN-4: §10.6 (TV, L) Pareto 14 configurations not listed (also
  MAJ-9)
- MIN-5: §10.3 noise-floor formula derivation deferred to manuscript
  in prep
- MIN-6: Pareto frontier mechanism explanation dense
- MIN-7: Member coincidence under Huffman remark could be sharper

### Methodology-auditor minors
- METH-MIN-1: §10.6 Setup paragraph too dense
- METH-MIN-2: §10.6 codec naming inconsistent
- METH-MIN-3: Padded(default=y_0) variant missing from table
- METH-MIN-4: $n=5$ codec in randomized encoding paragraph ambiguous
- METH-MIN-5: Key-feature attacker characterization thin
- METH-MIN-6: Pareto frontier "always on frontier" claim needs explicit
  definition
- METH-MIN-7: §10.3 uniform query distribution (carry-over)

### Prose-auditor minors
- PROSE-MIN-1: §8.3 "deployment pattern arises" list could be bullets
- PROSE-MIN-2: §8.3 prose-to-theorem transition abrupt
- PROSE-MIN-3: "coincidence-oracle" terminology repetitive
- PROSE-MIN-4: $\sim$ vs "approximately" inconsistent
- PROSE-MIN-5: §10.6 "Marginal output distribution" sentence dense
- PROSE-MIN-6: §9.6 "Out of scope" header italic vs bold
- PROSE-MIN-7: §1 Bernoulli paragraph stands alone awkwardly
- PROSE-MIN-8: Abstract "We formalize" sentence is longest in paper
- PROSE-MIN-9: "Bernoulli axiom" vs "Bernoulli framework" differs
- PROSE-MIN-10: §10.6 "sampling noise at 0.003" phrasing informal

### Citation-verifier minors
- CITE-MIN-1: §6.4 RecSplit cite added (R6 closed)
- CITE-MIN-2: Cover-Thomas not cited for Kraft inequality
- CITE-MIN-3: QIF multi-instance literature not cited
- CITE-MIN-4: Patel-Persiano-Yeo-Yung 2019 missing (carry-over)
- CITE-MIN-5: Köpf-Smith 2010 min-entropy missing
- CITE-MIN-6: Pouliot-Wright 2016 missing (carry-over)
- CITE-MIN-7: `towell2026algebraic` cited once for load-bearing claim
- CITE-MIN-8: DOI fields absent throughout bib (carry-over)
- CITE-MIN-9: Le Cam page number not given
- CITE-MIN-10: `towell2026codec` URL not stable archive
- CITE-MIN-11: Kerschbaum bib hygiene
- CITE-MIN-12: Kamara-Moataz bib title redundant

### Format-validator minors
- FMT-MIN-1: No underfull warnings (clean)
- FMT-MIN-2: Theorem numbering consistent
- FMT-MIN-3: `\Cref` vs `\ref` mixed (carry-over R6 FMT-N2)
- FMT-MIN-4: §5.2 enumerate style consistent
- FMT-MIN-5: §6.4 / §6.6.1 tables not in `\begin{table}` env
  (carry-over R6 FMT-N4, FMT-N5)
- FMT-MIN-6: bibtex clean
- FMT-MIN-7: Author block not anonymized for double-blind
- FMT-MIN-8: hyperref options fine
- FMT-MIN-9: §9 to §10 ordering correct
- FMT-MIN-10: Title page date stale ("March 2026")

## Suggestions

### Logic-checker
- SUG-1: Threat-model summary table (also FMT-SUG-1 cross-ref)
- SUG-2: Reproducibility appendix
- SUG-3: After CRIT-1, lead with (TV, L) Pareto frontier as headline

### Methodology-auditor
- METH-SUG-1: §10.7 Reproducibility and Limitations subsection
- METH-SUG-2: Move detailed setup tables to appendix
- METH-SUG-3: Codec sweep at larger $|Y|$

### Prose-auditor
- PROSE-SUG-1: Sweep §10.6 Summary for direction-of-claim errors
  after CRIT-1 fix
- PROSE-SUG-2: "How to read this paper" guide paragraph in §1
- PROSE-SUG-3: Promote randomized encoding to §8.4

### Citation-verifier
- CITE-SUG-1: "Concurrent and prior work in multi-instance composition"
  subsection
- CITE-SUG-2: Warner 1965 cite added (R6 closed)
- CITE-SUG-3: Split `bernoulli-types` into specific sub-paper refs

### Format-validator
- FMT-SUG-1: Glossary or notation table near §3
- FMT-SUG-2: Algorithm 1 to appendix
- FMT-SUG-3: §8.3 subsubsections under `\paragraph` headings

## Detailed Notes by Domain

### Logic and Proofs

The Round 7 additions (Theorem 8.1, Proposition 8.2, Corollary 8.x,
Definition 8.x, Remark on Huffman member coincidence) are mostly
sound. Theorem 8.1's proof is correct (verified the member case, the
filler-independence calculation, and the balanced-prior combination).
Proposition 8.2's proof has two technical gaps (saturation vs
bijectivity in MAJ-2, and homogeneous-vs-heterogeneous in MAJ-3) but
the core calculations are correct under the natural reading
(homogeneous instances with codec-level acceptance sets shared across
instances).

The critical issue (CRIT-1) is not a proof error but an interpretation
error: the formula is right, the empirical numbers are right, but the
"defender prefers smaller $\max_y \alpha$" conclusion is the reverse
of what the formula implies. The cipher-maps paper inherits this from
the bernoulli experiment writeup.

Other R6 logic issues (entropy ratio definition unified, Theorem 6.2
Step 2 separated storage/search costs, composition equality vs
inequality consistent) are addressed.

### Novelty and Contribution

The framework contribution (NOV-1) and three-literature unification
(NOV-5) are the strongest pillars and are uncontested. The empirical
Le Cam tightness (NOV-4) is solid. The (TV, L) Pareto frontier (NOV-2)
is a sharp empirical finding.

The multi-instance composition theorem (NOV-3) is the most ambitious
new claim, structurally compromised by CRIT-1. After the inversion
framing is dropped, what remains (the closed-form coincidence formula,
the randomized-encoding defense, the threat-model distinction) is
still novel but less striking. The thesis can be salvaged with NOV-2
and NOV-3-residual doing the headline narrative work.

### Methodology

Round 7 added the §10.6 codec-security empirical study. Setup is
careful (random seeds documented, train/test split balanced, Wilson
CIs reported). The 24/25-in-CI statistic is meaningful but limited.
Five major methodology gaps: single-run (METH-1), no Bloom baseline
(METH-2), 14 configurations not enumerated (METH-3), §10.3 single-run
carry-over (METH-4), attacker-class "tie" sample-size caveat (METH-5).

§10.3 retains R6's resolved CRIT-1 (noise-floor explanation for 3-term
AND FP arithmetic) and addresses the throughput inconsistency (713
docs/sec consistent across §6.4 and §10.3).

### Writing and Presentation

PROSE-1 (abstract "inverts" framing) is the headline writing issue,
embodying CRIT-1. PROSE-2 (§8.3 subsubsection style break), PROSE-3
(§10.6 paragraph-per-claim density), and PROSE-4 (abstract Pareto
sentence) are major editorial items. Ten minor prose issues across
the paper.

The R6 prose-residual items (register seam, definition env wrapping,
intro/section structure) are addressed. New issues are concentrated
in the Round 7 deltas (§8.3, §10.6, abstract).

### Citations and References

Bibliography has 33 entries, all properly cited. Round 7 activated
`towell2026algebraic` (now used at §10.3) and added `towell2026codec`
(used at §10.6). Two load-bearing "Manuscript in preparation" entries
remain: `towell2026maxconf` and `towell2026rekeying` (MAJ-5,
carry-over).

Missing citations: Huffman 1952 (MAJ-16), Patel-Persiano-Yeo-Yung
2019, Köpf-Smith 2010, Pouliot-Wright 2016, Cover-Thomas 2006, QIF
multi-instance work.

### Formatting and Production

Build is clean. 36 pages, 5 overfull hboxes (one severe at 118.9pt
in Definition 8.x). PoPETs template port still pending. Page count
exceeds PoPETs target by 8-10 pages; trim plan available.

## Literature Context Summary

The R5/R6 literature context is updated with three R7-relevant gaps:
(1) Huffman 1952 missing despite Huffman being central to §10.6,
(2) QIF multi-instance literature (Geng-Smith) not cited despite
§8.3's multi-instance contribution, (3) Cover-Thomas missing for
Kraft inequality background. No new direct competitors to the cipher
maps abstraction surfaced. The framework remains a synthesis across
three previously-disconnected literatures.

## Honest PoPETs survivability assessment

**Without CRIT-1 fixed**: NOT survivable. The abstract makes a
central claim (the inversion) that the formula contradicts. A
careful PoPETs reviewer will catch this. Recommendation: major
revision.

**With CRIT-1 fixed (Path A: keep formula, fix interpretation)**:
Plausibly survivable to minor revision in 1-2 reviewing cycles. The
v3 thesis bullet 3 needs to be revised (the "inversion" framing
dropped), the abstract reworked, Corollary 8.x and §10.6 paragraph
rewritten, the Summary item (iv) corrected. Total editorial effort:
~4-6 hours, plus the v3 thesis restructure (~half day). The remaining
majors (5 carry-overs and ~13 R7-new) are all addressable in 1-2
weeks if sister-paper preprints post in parallel.

**With CRIT-1 fixed and sister-paper preprints posted**: Minor
revision territory. The paper has solid technical content, a
well-defined framework, and credible empirical evidence (Le Cam
tightness, 42x TV reduction, 24/25 in CI). The remaining work is
production polish (PoPETs template, page trim, anonymization,
Huffman cite, replicate runs for §10.6 headline numbers).

## What's left for final polish before submission

In order of priority:

1. **CRIT-1 fix** (4-6 hours editorial plus v3 thesis rework): rewrite
   abstract, Corollary 8.x, §10.6 paragraph, Summary item (iv), and
   state.md thesis to drop "inversion" framing. Lead with "Huffman
   wins at every $t$" and the randomized-encoding defense.

2. **R7 major fixes** (4-8 hours): MAJ-1 (Theorem 8.1 verbal
   definition), MAJ-2 (Proposition 8.2 bijectivity), MAJ-3 (homogeneous
   instances clarification), MAJ-4 (Huffman saturation construction),
   MAJ-7 (3-replicate runs for §10.6), MAJ-8 (Bloom baseline), MAJ-12
   (abstract rewrite), MAJ-13 (§8.3 subsubsection style), MAJ-14
   (§10.6 structure sentence), MAJ-18 (118pt overfull fix).

3. **Sister-paper preprint posting** (1-2 days; closes MAJ-5):
   `towell2026maxconf`, `towell2026rekeying`. Lower priority but
   helpful: `towell2026algebraic`, `bernoulli-types` (rename and split).

4. **R6 minor backlog cleanup** (2-3 days): Le Cam normalization
   (logic MIN), Cref/ref unification (FMT-MIN-3), table env
   wrapping (FMT-MIN-5), CITE-MIN-2 (Cover-Thomas), CITE-MIN-3 (QIF
   multi-instance), CITE-MIN-4 (Patel-Persiano-Yeo-Yung), CITE-MIN-5
   (Köpf-Smith), CITE-MIN-6 (Pouliot-Wright), CITE-MIN-8 (DOIs),
   CITE-MIN-9 (Le Cam page), PROSE-MIN-1 to PROSE-MIN-10.

5. **Pre-submission cleanup** (1-2 hours): PoPETs template port
   (FMT-MIN; closes MAJ-6, MAJ-19 partly), anonymize for double-blind
   (FMT-MIN-7), date update (FMT-MIN-10), page trim per
   format-validator FMT-3.

## Review Metadata

- Agents: orchestrator-only (subagent dispatch unavailable, consistent
  with R5/R6); produced 6 specialist reports plus literature context
  plus this unified review
- Cross-verifications performed: 3 (CRIT-1 cross-checked against
  formula, empirical numbers, and source experiment; Theorem 8.1 proof
  cross-checked against verbal definition and Definition 8.x;
  Proposition 8.2 saturation assumption cross-checked against the
  Huffman example)
- Disagreements noted: 0 (CRIT-1 is consistently identified by
  logic-checker as a logic-direction issue, prose-auditor as a
  prose-framing issue, novelty-assessor as a novelty-claim issue;
  all three converge on the same root cause)
