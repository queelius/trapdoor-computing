# Multi-Agent Review Report, Round 9 (2026-06-02)

**Date**: 2026-06-02
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Manuscript**: paper/cipher_maps.tex (2861 lines, 39 pages PDF)
**Target venue**: PoPETs 2027
**Recommendation**: **minor-revision** (conditional on MAJ-1 sister-paper
Zenodo DOIs; one new same-day editorial fix, LOG-MAJ-1, also required)

## Summary

**Overall assessment**: The homophonic-allocation arc this round is
mathematically sound and self-contained. The new Proposition prop:homophonic
states a correct exact total-variation identity and a correct,
hypothesis-free bound (TV < |X|/N), with a clean proof that depends on
nothing external; removing the false maxconf deferral was the right call.
The K(x) proportional to D(x) direction is correct at every site, D and K
are defined before first use, and the d_TV-inline and codec-inventory edits
introduced no regressions. The two R8 majors (codec inventory, E4 H1
wording) are cleanly closed.

The aggressive direction/parameter sweep the user requested surfaced **one
new major finding** of the exact family the user has been catching by hand:
the multi-instance value distribution is labeled Zipf s = 1 at two sites,
but the paper's own headline numbers (max alpha = 0.5, attacker accuracy
0.984, 132x defense ratio) require s = 1.2, which is what the source
experiment actually uses. A literal Huffman code on Zipf(s=1) gives
max alpha = 0.25 and does not reproduce the illustration. This is a
one-character mislabel at each of two sites; the numbers are all correct
and validated against the experiment CSV. It slipped past R8 because that
round checked the ratio against the formula but did not reconstruct the
Huffman code from the stated skew.

Everything else is carry-over (sister-paper preprints, template/page-count/
anonymization, a few notation slips and citation adds). No data
fabrication; no soundness gap in any proof.

**Strengths**:
1. The new Proposition prop:homophonic is correct, self-contained, and
   strengthens the paper by removing a load-bearing deferral
   (logic-checker, novelty-assessor). Verified numerically across 6 configs.
2. The K(x) prescription direction is correct at all five sites; D and K
   are introduced before first use (logic-checker).
3. R8 MAJ-2 (codec inventory) and MAJ-3 (E4 H1 wording) are both cleanly
   closed (logic-checker, methodology-auditor).
4. All proof-bearing results re-verified: homophonic identity + Simmons
   bound, composition formula, AND-gate table, lower bound, space
   optimality, coincidence-oracle, cor:t-geometry direction, Bayesian
   deniability, Fannes-Audenaert direction. All PASS (logic-checker).
5. E1/E3/E4 empirical numbers reproduce from the published CSVs
   (methodology-auditor).
6. Build is production-clean: 0 undefined refs, 0 bibtex warnings, 4 minor
   overfulls (max 14.3pt); R7 critical 118.9pt stays closed
   (format-validator).
7. Novelty position is sound and slightly improved; the framework
   contribution is genuinely new (novelty-assessor, literature scouts).

**Weaknesses**:
1. NEW: Zipf skew mislabeled s=1; should be s=1.2 at two sites. The
   headline 132x illustration does not reproduce from s=1 (logic-checker
   LOG-MAJ-1, methodology-auditor METH-MAJ-1).
2. Four "Manuscript in preparation" citations remain; one (towell2026maxconf)
   is load-bearing for Proposition 5.1 (citation-verifier, novelty-assessor).
3. NEW minor: E1 table caption claims m up to 18266; experiment ran on the
   11,004-doc training split (methodology-auditor METH-MIN-1).
4. NEW minor: kappa(y) undefined (lines 2098-2101); n-vs-M bit-width
   notation unreconciled in section 10.6 (logic-checker, prose-auditor).
5. Article class, 39-page count, non-anonymized author block all block
   submission (format-validator).

**Finding counts**: Critical: 0 | Major: 2 | Minor: 9 | Suggestions: 6.

(Major = LOG-MAJ-1 / METH-MAJ-1 [the same s=1.2 finding, cross-listed] plus
MAJ-1 sister-paper preprints. Format majors FMT-MAJ-1/2/3 are
submission-logistics carry-overs the user already plans to handle; counted
in the per-domain notes, not double-counted in the headline.)

## Critical Issues

**None.**

R7 CRIT-1 (coincidence-oracle direction inversion) stays closed: verified
numerically that uniform maximizes attacker accuracy (worst defense) and
concentrated/Huffman minimizes it (best defense), at t in {2,3,5}. K(x)
prescription direction stays closed at all sites.

## Major Issues

### LOG-MAJ-1 / METH-MAJ-1 (NEW): Zipf skew mislabeled s=1; should be s=1.2

- **Source**: logic-checker (LOG-MAJ-1), methodology-auditor (METH-MAJ-1).
- **Location**: line 1934 (section 8.3 "Numerical illustration") and
  line 2609 (section 10.6 Setup).
- **Quoted text** (line 1934-1936): "For |Y| = 8 with a Zipf p_y (skew
  parameter s = 1), the Shannon-optimal Huffman partition gives
  max_y alpha(y) approx 0.5 (the dominant value claims half the
  codespace)." And (line 2609): "latent value distribution p_y Zipf with
  skew s = 1."
- **Problem**: The stated parameter s=1 is inconsistent with the paper's
  own numbers and with the source experiment. A literal Huffman code on
  Zipf(s=1) over |Y|=8 gives the dominant value a length-2 codeword
  (max alpha = 0.25), not 0.5, and t=5 attacker accuracy approx 0.999,
  not 0.984, so the "132x" ratio collapses. The source experiment
  (14_coincidence_oracle.py line 77) uses 1/(i+1)^1.2, i.e. s=1.2, which
  gives p[0]=0.4286, Huffman lengths [1,3,3,4,4,4,5,5], max alpha=0.5,
  sum alpha^5=0.0313, accuracy 0.9843. These match the paper exactly, and
  the E3 results.csv max_q column = 0.5 for Huffman(M=4,p_f). The numbers
  are correct and validated; only the skew label is wrong.
- **Suggestion**: Change "s = 1" to "s = 1.2" at lines 1934 and 2609.
  Zero risk to the numbers. One-character edit at each site. (Optionally
  note the dominant value receives a length-1 codeword under this skew.)
- **Cross-verified**: YES, three independent ways. (1) Independent Huffman
  construction on both s=1 and s=1.2; (2) source experiment file
  f_distribution() using exponent 1.2; (3) E3 results.csv max_q = 0.5 and
  predicted accuracy 0.98436 at t=5. All three agree the distribution is
  s=1.2. The orchestrator confirmed the exact manuscript quote.

### MAJ-1: Sister-paper preprints load-bearing (carry-over R6/R7/R8)

- **Source**: citation-verifier (CITE-MAJ-1), novelty-assessor (NOV-MAJ-1).
- **Location**: references.bib lines 45-50, 190-209 (four "Manuscript in
  preparation" entries); 14+ citation sites.
- **Quoted text**: bernoulli-types, towell2026algebraic, towell2026maxconf,
  towell2026rekeying all carry "Manuscript in preparation".
- **Problem**: Three theorem-level forward references must resolve at
  submission or a PoPETs reviewer flags them as unverifiable. The most
  load-bearing: Proposition 5.1's proof defers its Fannes-Audenaert
  derivation to maxconf Theorem 4.1 part 3; the cipher-maps paper states
  the bound but not its proof. Exposure is slightly reduced this round
  because the new homophonic proposition is self-contained (the
  representation-uniformity story no longer needs maxconf), but
  Proposition 5.1 still does.
- **Suggestion**: Post all four to Zenodo with DOIs (user's stated MAJ-1
  task). Add doi fields. Estimated 1-2 days. Closes the major.
- **Cross-verified**: YES. R6 verified the cite targets are correct
  (maxconf Thm 4.1 has 3 parts, part 3 is Fannes-Audenaert; rekeying
  section 7 has Theorem 7.1). The availability, not the target, is the
  problem.

## Minor Issues

### LOG-MIN-1 / PROSE-MIN-1: kappa(y) undefined
- **Location**: lines 2098-2101. "space cost only when kappa(y) > 1 ...
  Dense partition ... has kappa(y) = 1 for all y."
- **Problem**: kappa(y) appears nowhere else; the multiplicity symbol is
  K(x)/K(y). Undefined.
- **Suggestion**: Replace kappa(y) with K(y). One-line fix.

### LOG-MIN-3 / PROSE-MIN-2: n vs M bit-width unreconciled
- **Location**: Le Cam study uses n (lines 2612-2614); E3/E4 use M
  (lines 2618-2620, 2748-2781). Line 2005 writes class size 2^{n-l};
  line 2748 writes 2^{M-l_y} for the same quantity.
- **Suggestion**: Standardize on n, or note M = n in the section 10.6 Setup.

### LOG-MIN-2: Proposition 8.2 saturation hypothesis informal (carry-over)
- **Location**: lines 1999-2006. The "saturates" condition is the
  bijectivity the proof needs but is stated inline, not as a named
  definition. Proof is correct given saturation; precision issue only.
- **Suggestion**: Promote to a one-line Definition (Encoder saturation).

### METH-MIN-1 (NEW): E1 table caption claims m up to 18266; experiment ran on 11,004
- **Location**: line 2471, "For m in {1000, 5000, 18266} documents".
- **Problem**: e1/summary.md states "training split, 11,004 documents";
  CSV m values are {1000, 5000, 11004}. The full 18,266-doc corpus is used
  for section 10.3 throughput but the Bloom baseline (E1) ran on 11,004.
  Table values are robust (near-constant across m), so reported ratios are
  correct; only the stated largest m is wrong.
- **Suggestion**: Change "18266" to "11004" at line 2471, or rerun E1 on
  the full corpus.

### METH-MIN-2: Le Cam tightness table single-run (carry-over, now flagged)
The Le Cam tightness table is single-run while same-section E3/E4 are
replicated. Now honestly flagged ("Le Cam results are single-run").
3 replicates recommended; non-blocking.

### METH-MIN-3: Key-universe scope table single-run (carry-over)
tab:scope-keys is single-run. Qualitative claim robust; specific
accuracies single-run. Non-blocking.

### METH-MIN-4: 14 Pareto configs not enumerated in a CSV (carry-over)
The (TV, L) frontier claims 14/14 on frontier without a published
enumeration. The 42x headline is checkable by hand and correct; the full
sweep is not reproducible from an artifact.

### CITE-MIN-1: Huffman 1952 missing (carry-over)
The paper centers Huffman codes but never cites Huffman 1952. Conspicuous,
and the s=1.2 finding this round is precisely about Huffman-code behavior,
reinforcing the need. Strong recommend.

### PROSE-MIN-3/4/5 + FMT-MIN-1/2/3/4: presentation carry-overs
Section 8.3 subsubsection style; section 10.6 paragraph density;
integration comment markers in source; cleveref underused (4 \Cref vs 116
\ref); stale title date; bare tabular not in table env. All cosmetic
carry-overs.

## Suggestions

1. **LOG-SUG-1 / PROSE-SUG-1**: Direction/parameter-summary table codifying,
   per prescription, "which direction is better defense" plus "which
   distribution parameter gives which max alpha." Would have caught the
   s=1.2 mislabel at edit time. Now FOUR direction/parameter errors have
   appeared over the revision cycle; this defense is overdue.
2. **NOV-MIN-1 / PROSE-SUG-2**: Split the section 1 framework-contribution
   paragraph into "what is not new" and "what is new" (the disclaim and the
   results-enumeration currently undercut each other).
3. **CITE-MIN-2/3**: Add Cover-Thomas 2006 (Kraft inequality) and a
   multi-instance lineage cite (Kellaris 2016).
4. **METH-SUG-2**: Add Xor/Ribbon filter rows to the E1 Bloom baseline to
   land the overhead story against the current frontier, not the 1970
   baseline.
5. **METH-SUG-3 / PROSE-MIN-4**: Consolidated experiments table at the top
   of section 10.6.
6. **FMT-SUG-1**: Notation/glossary table near section 3 (would have
   surfaced the kappa/n-M slips).

## Detailed Notes by Domain

### Logic and Proofs
Centerpiece verified: Proposition prop:homophonic is correct (exact
identity and Simmons bound confirmed numerically across 6 configs), fully
self-contained (no maxconf, no unproven general-n result), and correctly
targets within-image uniformity with a clean prose bridge to the full-space
delta. K(x) direction correct at all sites with D, K defined before use. No
regressions from the d_TV/deferral/codec-inventory edits. 16
theorems/propositions re-verified, all PASS. One NEW major: the Zipf skew
mislabel (s=1 written, s=1.2 required). Two minor notation slips
(kappa(y), n-vs-M).

### Novelty and Contribution
Sound and slightly improved. The homophonic proposition removes a
load-bearing deferral, making the representation-uniformity story
self-standing. Framework contribution genuinely new; no fatal prior-art
overlap. Remaining risks: the maxconf deferral for Proposition 5.1 (MAJ-1)
and the section 1 disclaim/enumeration tension.

### Methodology
E1/E3/E4 reproduce from published CSVs. Two new reproducibility gaps, both
"stated parameter does not match artifact" rather than fabrication: the
s=1.2 mislabel (METH-MAJ-1) and the E1 m=11004 vs claimed 18266
(METH-MIN-1). Carry-over single-run limitations (Le Cam table,
key-universe table) honestly flagged.

### Writing and Presentation
Recently edited prose (Definition 4.2, the Proposition, the
within-image/full-space remark, the section 10.6 Setup) reads cleanly.
Notation slips (kappa, n-vs-M) and structural carry-overs (subsubsection
style, paragraph density, integration markers) remain. None blocks
submission.

### Citations and References
34 keys, 34 entries, 0 orphans, 0 bibtex warnings. The removed deferral
sentence correctly removed an unneeded maxconf citation. Blocker: four
"Manuscript in preparation" entries (MAJ-1). Strongest adds: Huffman 1952,
Cover-Thomas 2006, Kellaris 2016.

### Formatting and Production
Build production-clean, 39 pages, max overfull 14.3pt. Submission blockers
are the standing trio: article class (not PoPETs template), page count over
target, non-anonymized author block. All carry-overs the user plans to
handle pre-submission.

## Literature Context Summary
Cipher maps sit at a stable four-way intersection (approximate membership,
frequency-hiding encryption, SSE/leakage-abuse, QIF). The QIF positioning
is defensible and standard. No prior-art threat to novelty. The
most-likely-noticed missing citations remain Huffman 1952 and Cover-Thomas
2006 given the paper's heavy Huffman/Kraft content. Xor/Ribbon filters are
the modern below-Bloom baselines worth adding to E1. None blocks acceptance.

## R8 Closure Summary

| R8 finding | This round status |
|---|---|
| MAJ-1 sister-paper preprints | Still open (carry-over MAJ-1); exposure reduced (homophonic prop now self-contained) |
| MAJ-2 codec inventory mismatch | CLOSED (commit 9b60c2b verified; per-sweep enumeration in Setup) |
| MAJ-3 E4 H1 "within 0.01" wording | CLOSED (commit 9b60c2b verified; now "within 0.02, 13 of 15 within 0.01") |
| MAJ-4 article class | Still open (FMT-MAJ-1) |
| MAJ-5 page count (38, now 39) | Still open (FMT-MAJ-2) |
| MAJ-6 anonymization | Still open (FMT-MAJ-3) |
| LOG-MAJ-1 Q support gap | Addressed: the homophonic prop + within-image/full-space remark now make the support story explicit |
| LOG-MAJ-3 Thm 8.1 homo/hetero | Still open (precision; Thm 8.1 covers heterogeneous via alpha_i, homogeneous as special case) |
| LOG-MAJ-4 Prop 8.2 saturation/bijectivity | Still open (LOG-MIN-2) |
| Direction-of-prescription discipline | Reinforced; one NEW parameter mislabel found (s=1.2), of the same family |

New this round: LOG-MAJ-1/METH-MAJ-1 (s=1.2 skew mislabel), METH-MIN-1
(E1 m mismatch), LOG-MIN-1 (kappa undefined), LOG-MIN-3 (n-vs-M).

## Honest PoPETs Survivability

The paper is technically sound and the framework contribution is sharp. The
homophonic-allocation arc this round is exactly the kind of rigorous,
self-contained result that strengthens a submission: a correct exact TV
identity, a bulletproof hypothesis-free bound, and the honest removal of an
unverifiable deferral. Every proof re-verifies. The R8 majors are closed.

What blocks "ready":
- MAJ-1 (sister-paper Zenodo DOIs): blocking, 1-2 days. The user's stated
  task. Closes the last hard external dependency (Proposition 5.1).
- LOG-MAJ-1/METH-MAJ-1 (s=1.2 mislabel): blocking but trivial, a
  one-character edit at two sites. Must be fixed: a careful reviewer
  reproducing the headline multi-instance illustration from the stated s=1
  will get max alpha=0.25 and conclude the numbers are wrong, when only the
  label is wrong. This is the highest-value 5-minute fix in the paper.
- FMT-MAJ-1/2/3 (template + page trim + anonymization): blocking, 1-2 days
  editorial, already planned.
- The minors (E1 m, kappa, n-vs-M, Huffman 1952 cite) are 1-2 hours total.

Total to "ready": ~1-2 weeks if work parallelizes; the technical content is
done. There is no substantive technical work remaining: no proof needs
fixing, no experiment needs rerunning (the artifacts are correct), no claim
is unsupported once the s=1.2 and m=11004 labels are corrected.

Direct answer to the user's question: **Yes, this paper is
submission-ready once (a) the Zenodo DOIs are minted and (b) the s=1.2
skew label is corrected at the two flagged sites.** Those two items plus
the planned template/anonymization editorial pass are all that stand
between the current draft and a clean PoPETs submission. The remaining
findings are camera-ready polish. Confidence: high.

## Direction / Parameter Audit (this round)

The user flagged a recurring pattern: three direction/constant errors
caught by the user, not the review team, across prior rounds. This round's
sweep was aggressive and found a fourth, of the constant/parameter family:

- Every `\propto` relation (15 sites): correct. K(x) propto D(x),
  alpha(y) propto p_y, w_y propto p_y all verified.
- Every min/max/favor/prefer/dominate/best/worst (30+ sites): correct.
  cor:t-geometry direction (uniform = worst defense, concentrated = best)
  verified numerically.
- Every inequality direction (composition `<=`, Fannes-Audenaert lower
  bound, Le Cam upper bound, Simmons bound): correct.
- NEW catch: the Zipf skew parameter s=1 (lines 1934, 2609) is mislabeled;
  the numbers require s=1.2. This is not a direction error but a
  parameter/constant mislabel of the same family. It evaded R8 because the
  ratio was checked against the formula without reconstructing the Huffman
  code from the stated skew.

Recommendation (LOG-SUG-1, now urgent): a direction/parameter-summary table
pairing each distribution with its resulting max alpha and each
prescription with its better-defense direction. With four such errors over
the cycle, this discipline should be codified in the manuscript so the next
one is visible at edit time.

## Review Metadata

- Specialists run: literature-context (scouts merged; subagent dispatch
  unavailable, orchestrator-direct), logic-checker, methodology-auditor,
  novelty-assessor, prose-auditor, citation-verifier, format-validator.
- Mode: orchestrator-direct (Task tool unavailable this session, as in
  R6/R7/R8). All specialist analyses performed by the orchestrator with
  direct manuscript reads and independent numerical verification.
- Cross-verifications performed: 9 (homophonic identity + Simmons bound
  numerically; K(x) direction across 5 sites; cor:t-geometry direction
  numerically; AND-gate table by enumeration; Bayesian deniability boundary
  cases; Fannes-Audenaert direction; s=1.2 skew via independent Huffman
  build + source file + E3 CSV; composition formula across 5 sites; E1/E3/E4
  numbers against CSVs).
- Disagreements between specialists: 0.
- Build: clean (39 pages, 0 undefined refs, 0 bibtex warnings, 4 overfulls
  max 14.3pt).
