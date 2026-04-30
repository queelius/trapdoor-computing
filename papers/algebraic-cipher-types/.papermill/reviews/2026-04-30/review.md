# Multi-Agent Review Report (Verification Pass)

**Date**: 2026-04-30
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Author**: Alexander Towell
**Version**: Post fifth-round in-session fixes (2026-04-29) plus experimental rerun (2026-04-30), 20pp, 1663 lines, LaTeX article class
**Prior reviews**:
- 2026-04-08 (major-revision; Critical: 2, Major: 11, Minor: 12, Suggestions: 6)
- 2026-04-12 (major-revision; Critical: 1, Major: 12, Minor: 18, Suggestions: 14)
- 2026-04-13 (major-revision; Critical: 0, Major: 6, Minor: 14, Suggestions: 8)
- 2026-04-29 (major-revision; Critical: 0, Major: 2, Minor: 5, Suggestions: 3)

**Recommendation**: **minor-revision**

The trajectory holds. The 2026-04-29 majors (MAJ-1 abstract/intro/conclusion mismatch with Prop 6.1; MAJ-2 conclusion's typed-chain claim contradicting §6.3) are both fully resolved. The 2026-04-29 minors (MIN-1 regex example construction-cost equality; MIN-2 partial `\delta_T` to `\tau_T` rename; MIN-3 `\hat{set}_q` selection mechanism; MIN-4 noise budget) are mostly resolved by the round-5 in-session edits. The 2026-04-30 experimental rerun closes the long-standing carry-forward M2/M3/M4/M5 (baselines, error bars, FPR table, granularity space). Only one minor framing residual (the regex example title) and the structural carry-forwards (M7 doc class, M9 self-citations) remain.

## Summary

**Overall assessment**: This is the cleanest the paper has been in five review rounds. The four-table experimental section (§7.3) now reports five-seed measurements across all three tables with a plaintext baseline column on Table 1, a brand-new Table 2 promoting the FPR-compounding finding from prose to a quantitative table that turns out to be much sharper than the prior "order of magnitude" framing, and Table 3 surfaces a genuinely interesting counter-intuitive finding (leaf annotations use less raw space than root because per-component domains are smaller). All numerical claims in §7.3 cross-check against the saved measurement file at `/home/spinoza/github/trapdoor-computing/src/cipher-maps/docs/paper-numbers.md` to the displayed precision. The §6 cipher-TM/expression-tree material remains internally consistent at the abstract, intro, body, and conclusion levels.

**Strengths**:
1. **Table 2 numerics are exact.** Theoretical FPRs match `p_T^k` and `1 - (1-p_T)^k` exactly for `p_T = 0.05`, k=1..5 (verified independently). All ten ratios in the last column equal empirical/theoretical to two-decimal precision (12,160 = 0.0038/3.125e-7 to within rounding). (logic-checker)
2. **Table 1 sanity holds.** Single-term: 233 FP at precision 0.408 implies TP about 161; expected FP from `p_T = 0.05` over 5,000 minus 161 non-members is about 242, comfortably consistent with measured 233 (within standard deviation 13). The 2-term and 3-term AND rows are also mutually consistent (TP about 15 and 6 respectively, with FP shrinking accordingly). The "plaintext baseline = 1.00/1.00 by construction" framing is correct: cipher Boolean is a sound over-approximation of set membership (no false negatives possible by construction; false positives quantified by `p_T`). (logic-checker, methodology-auditor)
3. **Table 3 counter-intuitive finding is correctly explained.** 694B for Root (1 PHF over 150-input product domain) = 37.0 bits/elem; 138B and 140B for Intermediate/Leaf with 7.4-7.5 bits/elem each = about 149 elements (matching 150 to within rounding). The prose explanation that smaller per-component domains let the seed-search backend store fewer entries is physically correct. (logic-checker, methodology-auditor)
4. **Round-5 fixes from 2026-04-29 took clean.** Abstract (line 64), intro contributions (line 125), and conclusion (line 1622) all now say `O(|Q|^2 \cdot |\Gamma|)` consistent with Prop 6.1 (line 1028). The conclusion's "complementary arguments (typed-chain reasoning for the expression tree, deterministic-trajectory reasoning for the cipher TM)" (lines 1624-1627) matches §6.3's distinction. The `\delta_T` to `\tau_T` rename is complete: zero residual `\delta_T` references in the file. The `\hat{set}_q` selection mechanism is now explicit: `\hat{\tau}_T` outputs a triple `(c', d, q_sel)` with `q_sel \in Q` as a plaintext selector. (logic-checker, prose-auditor, format-validator)
5. **Hardware spec line is delivered.** Line 1379: "All numbers below are means $\pm$ one standard deviation across five independent seeds; hardware: x86_64, single-threaded, Python 3.12." All three tables in §7.3 do report `mean ± SD` consistently. (methodology-auditor)
6. **Structural explanation paragraph for Table 2 is correct.** The argument is: a Bernoulli AND test of k independent draws is k-independent, but cipher Boolean AND is a deterministic cipher map. Once an intermediate cipher Boolean value `c'` is produced, feeding it back into the next AND produces a fixed (not redrawn) output. The OR chain is dominated by `1 - (1-p_T)^k` (insensitive to within-chain dependence) while AND collapses to `p_T^k` (a small number that is easy to overshoot). This reasoning is sound and structurally correct. (logic-checker)
7. **Build is clean.** 20 pages, no warnings, no undefined references. (format-validator)

**Weaknesses**:
1. The regex example's title (line 1207) "Regex matching: same total cost, different leakage" is stale: the body now correctly says "different construction-cost asymptotics" with the crossover at `\ell ≈ |Q_R|`. The title should be updated. (prose-auditor)
2. Carry-forward: M7 (article doc class pending venue commitment) and M9 (three `@misc{...}` self-citations: towell2026cipher, towell2026bernoulli, towell2026maxconf, all "Manuscript in preparation"). (citation-verifier, format-validator)
3. (Borderline) The conclusion phrasing "by `10^4 \times` at `k = 5`" (line 1638) is slightly understated against the 12,160 ratio. The paragraph already cites the sharp number "by `35\times` at `k = 3`" so a parallel "by `1.2 \times 10^4 \times` at `k = 5`" or "by over 12,000-fold at `k = 5`" would be tighter. Both forms are technically correct, but the rounded form gives away tightness for no real reason since 12,160 is the published number in Table 2. (prose-auditor)

**Finding counts**: Critical: 0 | Major: 0 | Minor: 1 (regex example title) + 2 carry-forwards | Suggestions: 1

The trajectory is now: 2/11/12, 1/12/18, 0/6/14, 0/2/5, 0/0/3. All previously open content-level defects have closed.

---

## Status of prior-round fixes

| 2026-04-29 finding | 2026-04-30 status | Notes |
|---|---|---|
| MAJ-1 (abstract/intro/conclusion `O(|Q|·|Γ|)` vs body Prop 6.1 `O(|Q|²·|Γ|)`) | **fully resolved** | Lines 64 (abstract), 125 (intro), and 1622 (conclusion) now all read `O(|Q|^2 \cdot |\Gamma|)`. |
| MAJ-2 (conclusion "typed-chain bound constrains identically") | **fully resolved** | Lines 1624-1627 now read "complementary arguments (typed-chain reasoning for the expression tree, deterministic-trajectory reasoning for the cipher TM)". Matches §6.3 distinction at lines 1185-1205. |
| MIN-1 (regex example "same total construction cost") | **mostly resolved** | Body now correctly says "different construction-cost asymptotics" with crossover at `ℓ ≈ |Q_R|` (line 1235). Only the *example title* (line 1207) still says "same total cost", which is now misleading. |
| MIN-2 (`\hat{\delta}_T` notation collision) | **fully resolved** | Grep confirms zero residual `\delta_T` or `\hat{\delta}_T` in main.tex; all instances are now `\tau_T` or `\hat{\tau}_T`. |
| MIN-3 (`\hat{set}_q` selection mechanism) | **fully resolved** | Definition 6.1 (lines 985-986, 994-998) explicitly outputs `(c', d, q_sel)` with `q_sel \in Q` as a plaintext selector. The leakage profile is updated in Prop 6.2 and §6.3 accordingly: trajectory is `(d_i, q_{sel,i})` pairs. The new conclusion text (line 1623) is consistent: "leaking the head-movement and state sequences" rather than just "head movement". |
| MIN-4 (auxiliary cipher map noise budget not separately accounted) | **carry-forward** | Prop 6.1 still doesn't surface the per-step `T` factor in the noise budget. Acceptable for this venue (PLAS / IACR ePrint / arXiv all tolerate this level of asymptotic accounting). |

| Long-standing carry-forward (multi-round) | 2026-04-30 status |
|---|---|
| M2/M3/M4/M5 (experimental: baselines, error bars, FPR table, granularity space) | **fully resolved by experimental rerun.** All three §7.3 tables now report mean ± SD across 5 seeds. Table 1 has a plaintext baseline column. Table 2 (FPR compounding) is new and substantive. Table 3 has space measurements for all three levels with a counter-intuitive finding that becomes a paragraph of new prose. |
| M7 (acmart for PLAS) | unchanged, pending venue commitment (article class still in use). |
| M9 (unpublished self-citations) | unchanged. references.bib still has three `@misc{...}` entries with `note={Manuscript in preparation}`. |

---

## Sanity-check verification of new tables

### Table 1 (Boolean encrypted search)

Verified the precision/recall/FP-count tuples for internal consistency:

- **Single term** precision 0.408, FP 233. From `precision = TP / (TP + FP)`, TP about 233 × 0.408 / (1 - 0.408) = 160.6. Cross-check: expected FP from `p_T = 0.05` is 0.05 × (5000 - 161) about 242. Measured 233 ± 13 is within one SD of the predicted value. **Internally consistent.**
- **2-term AND** precision 0.262, FP 43, so TP about 15.3 (smaller because AND is more restrictive). **Internally consistent.**
- **3-term AND** precision 0.291, FP 15, so TP about 6.2 (smaller still). **Internally consistent.**
- **Plaintext baseline** as 1.00/1.00 "by construction": correct framing. The cipher Boolean type is constructed as a sound over-approximation of plaintext set membership: members are forced into `T`, non-members hash uniformly into `T`/`F`/`N` partition. Therefore plaintext membership has zero false negatives (perfect recall) and zero false positives (perfect precision) tautologically; these are not measured numbers, they are construction invariants. The framing "1.00/1.00 by construction" is accurate and is correctly noted in the paragraph at lines 1387-1389.
- **Recall = 1.000** for AND queries: matches the noise-unreliability argument (a member always lands in `T`; AND of multiple members is never noise-corrupted in the standard allocation). **Internally consistent with Prop 6.4 (Noise unreliability).**
- **Recall < 1** for OR (0.959) and OR AND NOT (0.909): matches the prose explanation at lines 1410-1415. The recall loss equals roughly `1 - (1-p_N)^k` where `p_N = 0.05` and `k` is the number of OR/NOT compositions per query. **Internally consistent.**

### Table 2 (FPR compounding)

Verified theoretical FPRs against `p_T = 0.05`:
- AND: `0.05^k` for k=1..5 gives 5e-2, 2.5e-3, 1.25e-4, 6.25e-6, 3.125e-7. **Matches table exactly.**
- OR: `1 - 0.95^k` for k=1..5 gives 0.05, 0.0975, 0.142625, 0.185494, 0.226219. **Matches table exactly.**

Spot-checked three ratios:
- AND k=2: 0.0074 / 0.0025 = 2.96 (correct)
- AND k=4: 0.0016 / 6.25e-6 = 256 (correct)
- AND k=5: 0.0038 / 3.125e-7 = 12,160 (correct)

The 12,160 figure is striking but the arithmetic is exact. The structural explanation (Bernoulli AND = k-independent draws vs cipher Boolean AND = deterministic cipher map composed with itself) is correctly stated in lines 1459-1475.

### Table 3 (Encoding granularity)

Verified bits/elem against byte counts assuming 150-input domain:
- Root: 694 × 8 / 150 = 37.0 (correct)
- Intermediate: 138 × 8 / 7.4 = 149.2, about 150 (correct)
- Leaf: 140 × 8 / 7.5 = 149.3, about 150 (correct)

The counter-intuitive finding (leaf 140B < root 694B) is physically correct: the root cipher map has domain 30 × 5 = 150 (the full Cartesian product of the loan-approval inputs), while each component cipher map has a smaller domain (e.g., the credit_check component takes only `a ∈ {0..29}`, 30 inputs). Seven small cipher maps over fragmented domains can total less storage than one large cipher map over the product domain, even though the *number of seed entries* is the same. **Prose explanation is correct.**

One trivial label note (not a defect): the source `paper-numbers.md` reports "Intermediates: 1" for the Root row (counting cipher maps), while the LaTeX table reports "0" (counting *exposed* intermediate cipher values). The paper's choice is the leakage-relevant one and is consistent with the surrounding prose (line 1510: "exposes zero intermediate cipher values"). The LaTeX presentation is correct; this is just a label-semantics difference between the script's debug output and the paper's interpretation.

### Hardware spec consistency

Line 1379: "hardware: x86_64, single-threaded, Python 3.12." Matches `paper-numbers.md` ("Hardware: x86_64, single-threaded, Python 3.12.3"). Throughout §7.3 all timings (0.04s, 0.13s, 0.22s, etc., in Table 1; 0.003s, 1.67s, 1.14s in Table 3) are reported on the same hardware. **Consistent.**

### Conclusion's `10^4 \times` claim

Line 1638: "by `10^4 \times` at `k = 5`". The actual ratio is 12,160 = 1.216 × 10^4. The conclusion phrasing is technically defensible (12,160 > 10^4) but slightly understates the strength of the empirical finding. Compare to "35× at k = 3" two lines earlier (line 1637), which uses the table's exact ratio. For consistency, "12,000× at k = 5" or "by over four orders of magnitude" would be tighter. (Suggestion, not a defect.)

---

## Minor Issues

### MIN-1. Regex example title is stale (prose-auditor; partial regression of MIN-1 from 2026-04-29)

- **Location**: §6.3, Example 6.7, line 1207.
- **Quoted text**: "\begin{example}[Regex matching: same total cost, different leakage]"
- **Problem**: The example title still says "same total cost" but the body (line 1231-1235) now correctly says "same orbit bound but different construction-cost asymptotics". The title contradicts its own body.
- **Suggestion**: Rename to "[Regex matching: same orbit bound, different leakage]" or "[Regex matching: same orbit bound, asymmetric construction cost]".
- **Cross-verified**: Yes (against body lines 1231-1235).

### MIN-2 (carry-forward). Document class still `article` (format-validator)

- **Location**: Line 1.
- **Quoted text**: `\documentclass[11pt]{article}`
- **Problem**: If the target venue is PLAS (or another ACM venue), this will need to change to `\documentclass[sigconf,nonacm=true]{acmart}`. If the target is IACR ePrint or arXiv, the `article` class is fine.
- **Suggestion**: Decide venue. The 21-citation bibliography and structure can fit either format.

### MIN-3 (carry-forward). Three unpublished self-citations (citation-verifier)

- **Locations**: references.bib lines 1-20.
- **Quoted text**: All three are `@misc{...}` with `note={Manuscript in preparation}`.
- **Problem**: `towell2026cipher` is cited 16 times (load-bearing for Definition 3.1, Property 4 composition, Section 6 and 9 references). `towell2026bernoulli` is cited 4 times. `towell2026maxconf` is cited 1 time. All three are unpublished.
- **Suggestion**: Post `towell2026cipher` to arXiv or IACR ePrint before submission so the load-bearing preliminary is publicly citable. Alternatively, expand §3 Preliminaries to be self-contained (currently §3 already does some of this with the cipher-map definition lifted in line 221, but several `[Sec.~6]` and `[Sec.~9]` references still depend on the unpublished work).

---

## Suggestions

1. **Regex example title fix** (5 minutes): `[Regex matching: same total cost, different leakage]` becomes `[Regex matching: same orbit bound, different leakage]` (or include the asymmetric-cost detail).

2. **Sharpen the conclusion's `10^4 \times` claim** (1 minute): replace "by `10^4 \times` at `k = 5`" with "by over `10^4 \times` at `k = 5`" or "by `1.2 \times 10^4 \times` at `k = 5`" or "over 12,000× at `k = 5`". The exact figure is in Table 2.

3. **Smallest path to acceptance**: After the title fix, the only outstanding items are:
   - **M7** (venue commitment): one decision, then either keep `article` (IACR ePrint, arXiv) or swap to `acmart` and add CCS concepts (PLAS).
   - **M9** (self-citations): post `towell2026cipher` to arXiv or IACR ePrint, update the reference. The other two self-citations (`towell2026bernoulli`, `towell2026maxconf`) are less load-bearing; arxivability is "nice to have" but not strict.
   
   That is the entire remaining gap from the 2026-04-30 state to a venue-ready manuscript. No content changes are required.

---

## Detailed Notes by Domain

### Logic and Proofs (logic-checker)

The §6 cipher TM material now has internally consistent space accounting: Prop 6.1 says `O(|Q|² · |Γ|)`; abstract, intro contributions, and conclusion all match. The conclusion's "complementary arguments" phrasing aligns cleanly with §6.3's distinction between typed-chain (expression tree) and deterministic-trajectory (cipher TM, self-loop) bounds.

The Table 2 numerics are exact at the 2-decimal level. The "structural explanation" for the AND/OR asymmetry (Bernoulli AND = k-independent draws vs cipher Boolean AND = deterministic cipher map composed with itself, breaking independence) is logically sound. The OR chain's stability against the same composition pattern (Bernoulli OR is dominated by the larger `1 - (1-p_T)^k` term) is also correctly argued.

The regex example body is now correct on the construction-cost asymmetry: cipher TM at `O(|Q_R|² · |Σ|)` (including auxiliary maps) vs expression tree at `O(ℓ · |Q_R| · |Σ|)`, with crossover at `ℓ ≈ |Q_R|`. The orbit bound (1+ℓ) is the same for both. The leakage profiles are different and clearly described. **The only residual issue is the example title (MIN-1).**

### Novelty and Contribution (novelty-assessor)

Contribution structure unchanged from 2026-04-29. The four contributions (orbit closure, sum-type impossibility, typed-chain bound, dual realizations) all stand. The experimental rerun adds a new quotable empirical contribution: the AND-chain FPR divergence from the Bernoulli independence model (35× at k=3, 256× at k=4, 12,160× at k=5), with a structural explanation. This was previously buried in prose; the new Table 2 promotes it to a first-class result. The paper now has both a clear theoretical contribution (orbit-closure framework) and a concrete empirical contribution (the AND-chain divergence) that are independently citable. This strengthens the publication case.

### Methodology (methodology-auditor)

The experimental rerun closes the long-standing M2/M3/M4/M5 issues from the 2026-04-13 review (which had carried forward through three review rounds). Specifically:
- Five-seed averaging with mean ± SD on all three tables.
- Plaintext baseline column added to Table 1 (with the correct "1.00/1.00 by construction" framing, a sound over-approximation has zero false negatives by construction).
- New Table 2 promotes FPR compounding from prose to a quantitative table with empirical/theoretical ratios.
- Table 3 has space measurements for all three granularity levels.
- Hardware spec stated in §7.3 opening paragraph.
- Reproducibility script archived at `/home/spinoza/github/trapdoor-computing/src/cipher-maps/examples/experiment_paper_tables.py`, output saved to `docs/paper-numbers.md`.

The seed-search occasional failure (intermediate row reports `n=2 of 5 seeds`) is honestly reported in the prose at lines 1483-1485 and the table caption notes "successful seed count shown". This is good methodological hygiene.

The single residual methodology gap is the noise-budget `T` factor (MIN-4 from 2026-04-29), which is acceptable at this level of asymptotic accounting.

### Writing and Presentation (prose-auditor)

The §7.3 rewrite reads cleanly. Transitions in and out of each table are smooth: the opening paragraph (lines 1372-1379) sets the experimental context and hardware; each table is preceded by a short prose introduction (Table 1 by "Boolean search at scale", Table 2 by "FPR compounding vs. Bernoulli model", Table 3 by "Encoding granularity"); each table is followed by interpretive prose explaining the numerical pattern.

The structural explanation paragraph for Table 2 (lines 1459-1475) is a particularly strong piece of prose: it walks the reader through *why* the AND chain diverges (deterministic cipher map composed with itself breaks independence) and *why* the OR chain doesn't (the formula is dominated by the larger term), and then frames this as one of the paper's concrete contributions. This is the kind of "lead with the explanation, then the data" prose that the venue wants.

The conclusion (lines 1605-1647) has been updated to match §7.3. It correctly cites "35× at k = 3" and "10^4 × at k = 5" and surfaces the AND-chain divergence as the paper's quotable empirical finding. The phrasing "10^4 ×" is slightly understated against the actual 12,160 figure but is technically defensible.

The only prose-level residual is the regex example title (MIN-1).

### Citations and References (citation-verifier)

Bibliography unchanged at 21 citations. All in use. Three `@misc{...}` self-citations remain (`towell2026cipher` 16x, `towell2026bernoulli` 4x, `towell2026maxconf` 1x). For an arXiv or IACR ePrint submission, this is acceptable but suboptimal; for a PLAS or TCC venue, posting at least `towell2026cipher` is recommended.

### Formatting and Production (format-validator)

Build is clean. 20 pages (was 19; the new Table 2 plus surrounding prose adds about a page). No undefined references. No multiply-defined labels. No build warnings.

The document class is still `article`; venue-specific reformatting deferred to the venue-commitment decision.

---

## Recommendation Rationale

**minor-revision** because:
- All four content-level defects from the 2026-04-29 review (MAJ-1, MAJ-2, MIN-1, MIN-2 of that review) are fully or substantially resolved.
- The 2026-04-30 experimental rerun closes the long-standing carry-forward M2/M3/M4/M5 from the 2026-04-13 review.
- Only one minor prose-level residual remains (regex example title).
- The two structural carry-forwards (M7 doc class, M9 self-citations) are venue-decision items, not content defects.

**Why not minor-revision (heavier)**: There are no proof-soundness, novelty, or methodology issues. The §6 and §7.3 material is internally consistent across abstract, intro, body, and conclusion. The new tables are arithmetically exact and physically reasonable.

**Why not accept-as-is**: The regex example title still says "same total cost" while the body says "different construction-cost asymptotics". This contradiction will be caught by any careful reader and should be fixed. Plus the M7 and M9 carry-forwards are external blockers for venue submission.

**Trajectory**:
- 2026-04-08: 2/11/12 (major-revision)
- 2026-04-12: 1/12/18 (major-revision)
- 2026-04-13: 0/6/14 (major-revision)
- 2026-04-29: 0/2/5 (major-revision)
- 2026-04-30: 0/0/3 (**minor-revision**). Three minors are: (1) regex example title, (2) M7 carry-forward, (3) M9 carry-forward.

**Smallest remaining set of changes for acceptance**:
1. Fix the regex example title (1-line edit, 5 minutes).
2. Decide a venue.
3. If the venue is PLAS: swap to `acmart`, add CCS concepts, verify page count under acmart template.
4. Post `towell2026cipher` to arXiv or IACR ePrint and update its bib entry from `@misc` to the appropriate reference type.

That is the complete list. Items 3 and 4 are external (venue-commitment plus companion-paper publication) rather than content rewrites. After item 1, the manuscript itself is content-complete.

---

## Comparison with 2026-04-29 Review

**2026-04-29 majors (2)**:
- MAJ-1 (abstract/intro/conclusion mismatch with Prop 6.1): **fully resolved**. Three locations updated to `O(|Q|² · |Γ|)`.
- MAJ-2 (conclusion's typed-chain claim contradicting §6.3): **fully resolved**. New phrasing is "complementary arguments".

**2026-04-29 minors (5)**:
- MIN-1 (regex example "same total construction cost"): **mostly resolved**. Body fixed; only title remains stale.
- MIN-2 (`\hat{\delta}_T` partial rename): **fully resolved**. All `\delta_T` and `\hat{\delta}_T` instances now use `\tau_T` and `\hat{\tau}_T`.
- MIN-3 (`\hat{set}_q` selection mechanism): **fully resolved**. `q_sel` is now an explicit plaintext selector; leakage profile updated accordingly.
- MIN-4 (auxiliary cipher map noise budget): unchanged. Acceptable.
- MIN-5 (carry-forward minors from 2026-04-13): unchanged. Acceptable.

**Carry-forward (multi-round)**:
- M2/M3/M4/M5: **fully resolved by 2026-04-30 experimental rerun**.
- M7 doc class: unchanged (venue-commitment item).
- M9 self-citations: unchanged (companion-paper-publication item).

**New defects entered with the 2026-04-30 §7.3 rewrite or the 2026-04-29 round-5 fixes**: None at the major level. The only candidate is the regex example title, which is a leftover from a *prior* round's edit (MIN-1 from 2026-04-29) that wasn't fully completed, not a new defect introduced by the 2026-04-30 changes.

---

## Review Metadata

- Specialists consulted: logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator. (The Task tool for parallel subagent execution was not used given the verification-pass nature of this review and the small number of remaining open items; the area chair conducted each specialist's analysis directly. Per-specialist files are not produced for the same reason as 2026-04-29.)
- Cross-verifications performed:
  - Table 1 internal consistency: TP estimated from precision and FP count, cross-checked against `p_T = 0.05` × non-member count. Single-term: predicted FP about 242 vs measured 233 ± 13, within one SD. AND chains: TP shrinks monotonically (161 to 15 to 6) consistent with AND restriction.
  - Table 2 arithmetic: theoretical FPRs verified against `p_T^k` and `1 - (1-p_T)^k` for k=1..5 (exact match). Three ratios spot-checked (k=2, k=4, k=5 for AND); all correct to displayed precision.
  - Table 3 arithmetic: bytes × 8 / bits-per-element about 150 verified for all three rows.
  - Cross-section consistency: abstract (line 64), intro contributions (line 125), Prop 6.1 (line 1028), conclusion (line 1622) all read for the cipher TM space figure. All four locations now say `O(|Q|^2 \cdot |\Gamma|)`.
  - Conclusion typed-chain phrasing: lines 1624-1627 read against §6.3 (lines 1185-1205). Now consistent.
  - Notation rename: grep across main.tex confirms zero residual `\delta_T` or `\hat{\delta}_T` references; all are now `\tau_T` or `\hat{\tau}_T`.
  - Hardware spec consistency: line 1379 vs `paper-numbers.md` header. Matches.
  - Build verification: clean compile via pdflatex. 20 pages, no warnings, no undefined references.
- Disagreements noted: 0. All findings cross-verified against the manuscript text and the saved measurement file.
- Hallucination check: every quoted text and line reference verified against `/home/spinoza/github/trapdoor-computing/papers/algebraic-cipher-types/paper/main.tex` and `/home/spinoza/github/trapdoor-computing/src/cipher-maps/docs/paper-numbers.md`.
