# Multi-Agent Review Report, Round 8 (2026-05-27)

**Date**: 2026-05-27
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Manuscript**: paper/cipher_maps.tex (2794 lines, 38 pages PDF)
**Target venue**: PoPETs 2027
**Recommendation**: **minor-revision** (conditional on MAJ-6 closure
via sister-paper preprint posting)

## Summary

**Overall assessment**: This round verifies a clean closure of the
R7 critical (CRIT-1 inversion direction) and a clean correction of
the K(x) prescription direction caught by the user just before this
review. The three new empirical results (E1 Bloom baseline, E3
replicated codec-security, E4 randomized-encoding K sweep) are
integrated honestly; the underlying numbers match the published CSVs;
substantive claims hold. No new critical issues. Six major issues
identified: four are R6/R7 carry-over (sister-paper preprints,
article class, page count, anonymization), two are introduced by the
new content (codec inventory mismatch in section 10.6, E4 H1 wording
overstates by missing two M=5 cells). With MAJ-6 closed via Zenodo
DOIs, the paper is plausibly minor-revision territory at PoPETs.

**Strengths**:
1. Framework contribution (four-property cipher map abstraction +
   acceptance predicate) is genuinely new (novelty-assessor).
2. The (TV, L) Pareto frontier with 42x TV reduction is a sharp,
   non-controversial finding (novelty-assessor, methodology-auditor).
3. The R7 CRIT-1 fix landed cleanly across all five flagged sites
   (logic-checker).
4. Today's K(x) prescription direction fix is consistent across all
   four sites; the new Related Work paragraph and Definition 4.2
   rewrite are coherent (logic-checker, prose-auditor).
5. E1 Bloom baseline is methodologically honest (single-run flagged,
   theoretical asymptote computed) (methodology-auditor).
6. E3 replicated codec-security study is well-designed (10 reps x
   100K trials) and 23/25 cells within Wilson 95% CI is a tight
   match (methodology-auditor).
7. Build is clean: 4 minor overfulls (max 14pt), R7 critical 118.9pt
   overfull closed (format-validator).

**Weaknesses**:
1. Four "Manuscript in preparation" citations remain (one is highly
   load-bearing for Proposition 5.1). Blocker for clean PoPETs
   submission (citation-verifier, novelty-assessor).
2. Codec inventory mismatch between section 10.6 Le Cam tightness
   table and E3 multi-instance table; reader cannot reconcile
   without the underlying CSVs (methodology-auditor).
3. The E4 H1 "within 0.01 in all 15 cells" claim is overstated; two
   M=5 cells exceed the bound (mean gap claim 0.004 is correct)
   (methodology-auditor).
4. Section 1 framework-contribution paragraph mixes a disclaim about
   construction novelty with an enumeration of new results, weakening
   the disclaim (novelty-assessor, prose-auditor).
5. Article class (not PoPETs template) and 38-page count both block
   submission (format-validator).
6. Direction-of-prescription pattern: three errors caught by user
   over the revision cycle. A direction-summary table at section 5.2
   would codify discipline (logic-checker recommendation).

**Finding counts**: Critical: 0 | Major: 6 | Minor: 28 |
Suggestions: 12.

## Critical issues

**None.**

R7 CRIT-1 (t-dependent allocation direction inversion) is closed:
verified all five flagged sites in cipher_maps.tex now use the
correct direction. K(x) prescription direction fix (today's commit)
verified at all four flagged sites; new Related Work paragraph and
Definition 4.2 rewrite are coherent.

## Major issues

### MAJ-1: Sister-paper preprints load-bearing (carry-over R6/R7 MAJ-6)
**Source**: citation-verifier (CITE-MAJ-1), novelty-assessor (NOV-MAJ-1)
**Location**: 4 bibentries; 14+ citation sites in manuscript.

**Quoted text** (from references.bib lines 45 to 49, 190 to 208):
- bernoulli-types: "Manuscript in preparation. See [URL]"
- towell2026algebraic: "Manuscript in preparation"
- towell2026maxconf: "Manuscript in preparation"
- towell2026rekeying: "Manuscript in preparation"

**Problem**: Three specific theorem-level forward references must
resolve at submission time, or PoPETs reviewers will flag them as
unverifiable:
- Theorem 4.1, part 3 of towell2026maxconf (Prop 5.1 proof)
- Section 4 of towell2026maxconf (entropy ratio definition)
- Sections 5 to 6 of towell2026maxconf (function-value leakage
  translation)
- Theorem 7.1 of towell2026rekeying (chain confidentiality bound)

**Suggestion**: Post all four to Zenodo with DOIs before submission
(stated user intent). Estimated 1 to 2 days. Closes the major fully.

**Cross-verified**: Logic-checker confirmed Prop 5.1 currently
depends on towell2026maxconf for the Fannes-Audenaert derivation;
the cipher-maps paper only states the bound, not its proof. Without
the preprint, the proof of Prop 5.1 is incomplete.

### MAJ-2: Codec inventory mismatch in section 10.6
**Source**: methodology-auditor (METH-MAJ-1)
**Location**: lines 2550 to 2596 (Le Cam tightness table) vs E3
empirical sweep at lines 2640 to 2653.

**Quoted text** (section 10.6 Setup, lines 2554 to 2559):
"Six acceptance predicates compared: Dense(alpha_y = 1/|Y|), two
Padded variants with default values y_0 and y_7, Huffman from p_y
at n = 4 and n = 5, and AntiHuffman from p_y at n = 5"

**Problem**: The Le Cam tightness table (lines 2575 to 2596) uses
this 5-codec set (Huffman n=5, Huffman n=4, Dense n=4, Padded
default y_7, AntiHuffman n=5). The E3 replicated sweep
underwriting the "23 of 25" claim uses a different codec set:
Dense(M=3), Dense(M=4), Padded(M=4,v0), Huffman(M=4,p_f),
AntiHuffman(M=4). No Huffman M=5, no Padded default y_7, no
AntiHuffman M=5.

A reader who tries to reproduce will be confused.

**Suggestion**: Either (a) add a Setup-level note that the Le Cam
tightness table and E3 multi-instance table use different focused
subsets of the nominal 6-codec inventory, or (b) rerun the Le Cam
tightness table on the E3 codec set so both tables share their
inventory. Option (b) is cleaner; option (a) is 30 minutes editorial.

**Cross-verified**: Verified codec name mismatch against
e3/summary.md per-cell table. The two tables genuinely use different
codec sets.

### MAJ-3: E4 H1 "within 0.01" claim overstates
**Source**: methodology-auditor (METH-MAJ-2)
**Location**: lines 2688 to 2691.

**Quoted text**:
"Empirical values match the closed form sum_v p_f(v) * 2^(-(M-l_v)(t-1))
of Remark 8.x to within 0.01 in all 15 Huffman cells (mean absolute
gap 0.004)."

**Problem**: Verified against e4/summary.md per-cell table. Two
cells exceed 0.01: Huffman(M=5) random t=2 at 0.0104, and
Huffman(M=5) random t=3 at 0.0163. The mean-gap claim (0.004) is
correct; the "within 0.01 in all 15" wording is too tight.

**Suggestion**: Change to "within 0.02 in all 15 Huffman cells (13 of
15 within 0.01, two M=5 cells at t in {2, 3} with gaps 0.010 and
0.016 respectively; mean absolute gap 0.004)."

**Cross-verified**: Direct enumeration of all 15 Huffman cells in
e4 results confirms gap values: M=4 gaps 0.0089/0.0075/0.0066;
M=5 gaps 0.0104/0.0163/0.0000; M=6 gaps 0.0044/0.0022/0.0016;
M=7 gaps 0.0005/0.0009/0.0001; M=8 gaps 0.0028/0.0003/0.0000.
Mean = 0.0042.

### MAJ-4: Article class not PoPETs template (carry-over R5 to R7)
**Source**: format-validator (FMT-MAJ-1)
**Location**: line 1, `\documentclass[11pt]{article}`.

**Problem**: PoPETs requires their own template (two-column,
ACM-derived). Article class with 1-inch margins gives 38 pages;
PoPETs target is 18 to 20 pages in their template (corresponding to
~ 22 to 28 pages article class).

**Suggestion**: Port to PoPETs 2027 template (4 to 8 hours).
Coupled with MAJ-5 (page trim) before submission.

### MAJ-5: Page count 38 vs PoPETs target (carry-over R7 MAJ-19)
**Source**: format-validator (FMT-MAJ-2)
**Location**: PDF page count 38 (up from R7's 36 due to E1/E3/E4
integrations).

**Problem**: After PoPETs template port, expected page count ~ 26
to 30 pages, which exceeds the 18 to 20 target. Need 8 to 10 page
trim.

**Suggestion**: Page-trim candidates: section 9.1 (Bernoulli
relationship, compress), section 9.4 (bounded composition, move to
appendix), section 10.4 (deniability, appendix), section 10.5
(future investigations, compress to paragraph), section 6.3
(Algorithm 1, appendix).

### MAJ-6: Anonymization for double-blind review (upgraded from R7 minor)
**Source**: format-validator (FMT-MAJ-3)
**Location**: lines 47 to 49 (title page), 2269 (cipher-maps URL),
2786 to 2789 (acknowledgments).

**Problem**: PoPETs uses double-blind review. Current author block,
identifying URL, and acknowledgments paragraph reveal the author's
identity.

**Suggestion**: Anonymize for submission. Standard form:
`\author{Anonymous Submission}`, replace
`https://github.com/queelius/cipher-maps` with `https://[anonymous]`,
rewrite acknowledgments. Companion citations (towell2026*) cite as
"anonymous companion work" or move to camera-ready. Estimated 1 to 2
hours.

## Minor issues (selected; full list in specialist reports)

**Logic and proofs**

- **LOG-MAJ-1** (logic-checker): Definition 4.2 Q distribution
  support gap. Q is supported on Im(enc); TV(Q, Uniform(B^n)) bound
  is vacuous unless filler dilutes the stream. Resolution: add a
  remark clarifying the role of filler. Not a new finding (R5/R6
  partially addressed) but the support issue is upstream of the
  normalization issue.
- **LOG-MAJ-3** (logic-checker): Theorem 8.1 homogeneous vs
  heterogeneous instance hypothesis not explicitly stated.
- **LOG-MAJ-4** (logic-checker): Proposition 8.2 saturation hypothesis
  needs bijectivity (carry-over R7 MAJ-2). Recommended: add
  Definition (Encoder saturation) per prose-auditor PROSE-MIN-5.

**Methodology**

- **METH-MAJ-3** (methodology-auditor): 14 Pareto-frontier
  configurations not enumerated in a CSV (carry-over R7 MAJ-9).
- **METH-MAJ-4** (methodology-auditor): Le Cam tightness table
  single-run while same-paragraph E3 result is 10-replicate
  (carry-over R7 MAJ-7).
- **METH-MAJ-5** (methodology-auditor): Threat-model scope table
  single-run (carry-over R7 MAJ-11).
- **METH-MAJ-6** (methodology-auditor): E1 worst-cell flag missing
  (eps=0.10 cells at ratio 5.8 exceed design's 5 threshold; paper
  doesn't flag).

**Prose**

- **PROSE-MAJ-1** (prose-auditor): Section 8.3 subsubsection style
  (3 unnumbered `\subsubsection*` mixed with numbered subsubsection
  elsewhere; carry-over R7 MAJ-13).
- **PROSE-MAJ-2** (prose-auditor): Section 10.6 paragraph density
  (7 paragraphs without intervening structure; carry-over R7 MAJ-14).
- **PROSE-MAJ-3** (prose-auditor, novelty-assessor): Section 1
  framework-contribution paragraph mixes disclaim with new-results
  enumeration. Recommended: split per NOV-MAJ-2.

**Citations**

- **CITE-MAJ-2** (citation-verifier): Huffman 1952 missing
  (carry-over R7 CITE-2).
- **CITE-MAJ-3** (citation-verifier): Cover-Thomas 2006 missing
  (Kraft inequality reference).
- **CITE-MAJ-4** (citation-verifier): Patel-Persiano-Yeo-Yung 2019
  volume-hiding STE missing (carry-over R6/R7).

**Format**

- **FMT-MIN-1 to 7** (format-validator): cleveref consistency, table
  environments, title page date, integration comment markers,
  URL formatting (cosmetic, R7 carry-over).

## Suggestions

1. **LOG-SUG-1** (logic-checker): Direction-summary table at section
   5.2 codifying direction conventions. Defensive against the
   user-flagged direction-error pattern. Cross-reference:
   prose-auditor PROSE-SUG-1.
2. **NOV-MAJ-2** (novelty-assessor): Split section 1 framework-
   contribution paragraph into (A) disclaim + (B) new-results. See
   novelty-assessor for suggested text.
3. **METH-SUG-1** (methodology-auditor): Consolidated experiments
   table at top of section 10.6.
4. **METH-SUG-2** (methodology-auditor): Publish Le Cam tightness +
   Pareto frontier + threat-model scope scripts to experiments dir.
5. **METH-SUG-3** (methodology-auditor): E1 against Xor/Ribbon
   baselines (current frontier vs 1970 Bloom).
6. **METH-SUG-4** (methodology-auditor): E4 add t=5 cell to align
   with section 8.3 numerical example.
7. **PROSE-SUG-2** (prose-auditor): "How to read this paper" guide
   paragraph in section 1 (R7 carry-over).
8. **PROSE-SUG-3** (prose-auditor): Promote randomized encoding to
   section 8.4 standalone (R7 carry-over).
9. **CITE-SUG-1** (citation-verifier): "Concurrent and prior work in
   multi-instance composition" subsection in section 2 (R7
   carry-over).
10. **CITE-SUG-2** (citation-verifier): Issa-Wagner-Kamath 2020
    (operational leakage Pareto) at section 10.6.
11. **FMT-SUG-1** (format-validator): Notation table near section 3
    (R7 carry-over).
12. **FMT-SUG-2** (format-validator): Algorithm 1 to appendix for
    page trim (R7 carry-over).

## Detailed notes by domain

### Logic and proofs

R7 CRIT-1 (t-dependent allocation direction) closed cleanly. Verified
all five flagged sites use correct direction: uniform maximizes
attacker accuracy (worst defense), concentrated minimizes (best
defense). Numerical example (Huffman defends 132x better at t=5)
arithmetically verified: at |Y|=8, t=5, Huffman max alpha=0.5 gives
attacker accuracy 0.984 (error rate 0.016); uniform gives 0.9999
(error rate 1.2e-4). Ratio 133, paper says 132. PASS.

K(x) prescription direction fix verified at all four flagged sites
(lines 323, 457, 521, 644). New Related Work paragraph cleanly
introduces D(x) and K(x) with forward references; Definition 4.2
rewrite defines D explicitly as the query distribution; post-prose
gives correct operational reading (D(x)/K(x) constant). PASS.

16 theorems / propositions / corollaries verified: all PASS
mechanically. LOG-MAJ-1 (Q distribution support gap) is a clarity
issue, not a soundness gap. LOG-MAJ-3 (Theorem 8.1 hetero vs homo)
is a precision improvement. LOG-MAJ-4 (Prop 8.2 saturation needs
bijectivity) is an R7 carry-over still requiring tightening.

### Novelty and contribution

Five-pronged novelty claim verified against manuscript and literature
context. The framework contribution is genuinely new (no prior work
unifies the four properties). The (TV, L) Pareto frontier is
surprising and underwritten. The multi-instance composition theorem
is incremental over Naveed et al / Kellaris et al but the closed-form
coincidence-oracle accuracy is specific to cipher maps.

Main weaknesses: (1) section 1 framework-contribution paragraph mixes
disclaim with results-enumeration (recommend split); (2) load-bearing
deferral to four unpublished sister papers (MAJ-1).

### Methodology

E1 Bloom baseline, E3 replicated codec-security, E4 randomized-
encoding K sweep all verified against CSVs. E1: 9 cells, all numbers
match, methodology honest. E3: 23/25 cells in Wilson 95% CI as
claimed; mean gap 4e-4 confirmed. E4: H1 (monotone decrease), H2
(invariance), H3 (Dense saturation) all PASS; but "within 0.01"
wording at line 2690 overstates (METH-MAJ-3).

Codec inventory mismatch (METH-MAJ-1) between Le Cam table and E3
table is the most concrete methodology issue introduced this round.

### Writing and presentation

Today's Related Work + Definition 4.2 rewrites read coherently.
Section 8.3 subsubsection style remains inconsistent (PROSE-MAJ-1).
Section 10.6 paragraph density still high (PROSE-MAJ-2). Section 1
framework paragraph still mixes claims (PROSE-MAJ-3).

The "coincidence oracle" term is introduced informally in section
8.3; could be promoted to a Definition environment.

### Citations and references

38 bibentries, all cited, no orphans. 4 Manuscript-in-prep entries
(MAJ-1). Strong missing adds: Huffman 1952, Cover-Thomas 2006,
Patel-Persiano-Yeo-Yung 2019, Kellaris-Kollios-Nissim-O'Neill 2016
(new this round), Alvim 2020, Köpf-Smith 2010.

### Formatting and production

Build clean. 4 minor overfulls (max 14pt at section 10.3
reproducibility URL). R7 critical 118.9pt overfull closed via
commit e8bbfd3.

Article class + 38-page count + author block all block submission
(MAJ-4 + MAJ-5 + MAJ-6).

## Literature context summary

Cipher maps sit at a four-way intersection (approximate membership,
frequency-hiding encryption, SSE/leakage-abuse, QIF). The paper
correctly positions itself in this space. Direct comparison points
that are not currently in the bibliography: Patel-Persiano-Yeo-Yung
2019 (closest STE work), Kellaris-Kollios-Nissim-O'Neill 2016
(closest multi-snapshot attack), Alvim 2020 (modern QIF textbook),
Huffman 1952 (the paper centers Huffman codes), Cover-Thomas 2006
(Kraft inequality background). Adding these six citations would
strengthen the paper's positioning materially.

The Xor filter (Graf-Lemire 2020) and Ribbon filter (Dillinger-
Walzer 2021) are the modern below-Bloom approximate-membership
constructions; adding these as additional rows in the E1 Bloom
baseline table (10.3) would land the practical-overhead story
against the current frontier rather than the 1970 baseline.

## R7 closure summary

| R7 finding | This round status |
|---|---|
| CRIT-1 inversion direction | CLOSED (commit 3b77c04 verified) |
| K(x) prescription direction (caught by user pre-R8) | CLOSED (commit 41210a8 verified) |
| MAJ-1 Theorem 8.1 verbal-def-vs-proof tuple | Partially closed; residual ambiguity (PROSE-MIN-4) |
| MAJ-2 Prop 8.2 saturation vs bijectivity | Still open (LOG-MAJ-4) |
| MAJ-3 Prop 8.2 homogeneous-instances formula | Still open (LOG-MAJ-3) |
| MAJ-4 Huffman saturation encoder gloss | Still open (PROSE-MIN-5) |
| MAJ-5 sister-paper preprints | Still open (MAJ-1) |
| MAJ-6 article class | Still open (MAJ-4) |
| MAJ-7 section 10.6 single-run | Partially closed (E3, E4 replicated; Le Cam tightness still single-run) |
| MAJ-8 no Bloom baseline | CLOSED (E1) |
| MAJ-9 14 Pareto configs unenumerated | Still open (METH-MAJ-3) |
| MAJ-10 section 10.3 single-run | Partially closed (single-run still, but Bloom-baseline cross-check added) |
| MAJ-11 attacker-tie sample-size | Still open (METH-MAJ-5) |
| MAJ-12 abstract inverts wording | CLOSED (commit 3b77c04) |
| MAJ-13 section 8.3 subsubsection style | Still open (PROSE-MAJ-1) |
| MAJ-14 section 10.6 paragraph density | Still open (PROSE-MAJ-2) |
| MAJ-15 abstract Pareto sentence | Still open (PROSE-MIN-1) |
| MAJ-16 Huffman 1952 missing | Still open (CITE-MAJ-2) |
| MAJ-17 bernoulli-types URL stale | CLOSED (verified HTTP 200) |
| MAJ-18 118.9pt overfull | CLOSED (commit e8bbfd3 verified, max overfull now 14pt) |
| MAJ-19 36 pages | Still open (now 38 pages, MAJ-5) |

R7 closure rate: 5 fully closed + 3 partially closed + 11 still
open. Net progress: 8 fewer R7 findings carrying forward.

## Honest PoPETs survivability

The paper is technically sound and the framework contribution is
sharp. Three R6/R7-era critical findings have been correctly
identified and fixed (composition formula `<=`, coincidence-oracle
direction, K(x) prescription direction). The R8 new content (E1, E3,
E4) integrates honestly. The mismatches identified this round
(codec inventory, H1 wording overstating) are precision-of-wording
issues, not data fabrication.

What blocks "ready" status:
- MAJ-1 (sister-paper preprints): blocking. Closes with 1 to 2 days
  of Zenodo posting.
- MAJ-4 + MAJ-5 + MAJ-6 (template port + page trim + anonymization):
  blocking. Closes with 1 to 2 days editorial.
- MAJ-2 + MAJ-3 (codec inventory mismatch + H1 wording): editorial,
  4 to 8 hours.
- LOG-MAJ-1 / LOG-MAJ-3 / LOG-MAJ-4 (logic precision): each 1 to 2
  hours editorial.

Total to "ready": ~ 1 to 2 weeks if work parallelizes; ~ 2 to 3
weeks sequential.

Confidence: moderate-high that this paper, with MAJ-1 closed and the
identified majors addressed, is ready for PoPETs submission.

## Direction-of-prescription audit summary

The user has caught three direction errors over the revision cycle.
This round's logic-checker performed an explicit direction-of-
prescription audit:

- `\propto` patterns (lines 255, 323, 457, 521, 644, 1044, 1050,
  1054, 1062, 1070, 1173, 1355, 1395, 1396, 2625): all directions
  verified correct.
- `minimize/maximize` prescriptions (lines 785, 1014, 1056, 1069,
  1857, 1858, 1869, 1871, 2772, 2773): all directions verified
  correct (the cor:t-geometry direction was the recent fix, now
  cleanly stated).
- `prefer/favor/dominate/best for/worst for` (lines 83, 742, 1833,
  1873, 1889, 1893, 2667, 2775): all directions consistent with
  formulas.
- Proposition 8.2 "Increasing |A_i(y)| via larger multiplicity K(x)
  cuts the in-domain coincidence probability" (line 1961): correct.
  Larger |A(y)| → smaller 1/|A(y)| product → lower attacker success
  on members → better defense.

No additional direction errors detected this round. The
direction-of-prescription discipline is now consistent throughout.

The defensive recommendation (LOG-SUG-1 / PROSE-SUG-1): add an
explicit direction-summary table at section 5.2 codifying the
direction conventions for each parameter and each prescription. This
would make any future direction error visible at edit time rather
than at user-catch time.

## Review metadata

- Specialists run: literature-context (scouts merged), logic-checker,
  novelty-assessor, methodology-auditor, prose-auditor,
  citation-verifier, format-validator.
- Mode: orchestrator-direct (subagent dispatch unavailable in this
  session). All specialist reads performed by orchestrator.
- Cross-verifications performed: 6 (K(x) sites across 4 places,
  R7 CRIT-1 across 5 sites, E1/E3/E4 numbers against CSVs, codec
  inventory between two tables in section 10.6, H1 cell counts in E4,
  direction-of-prescription audit across 15+ `\propto` and 20+
  min/max/favor sites).
- Disagreements noted: 0 between specialists.
- Time: full review session, all specialist reports produced.
