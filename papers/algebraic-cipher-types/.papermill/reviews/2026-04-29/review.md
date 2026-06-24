# Multi-Agent Review Report (Verification Pass)

**Date**: 2026-04-29
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Author**: Alexander Towell
**Version**: Post fourth-round in-session fixes (2026-04-29), 19pp, 1568 lines, LaTeX article class
**Prior reviews**:
- 2026-04-08 (major-revision; Critical: 2, Major: 11, Minor: 12, Suggestions: 6)
- 2026-04-12 (major-revision; Critical: 1, Major: 12, Minor: 18, Suggestions: 14)
- 2026-04-13 (major-revision; Critical: 0, Major: 6, Minor: 14, Suggestions: 8)

**Recommendation**: **major-revision**

The recommendation is heavier than the user's expected "minor-revision" because four genuinely new defects entered with the round-4 fixes, three of which are in propositional/abstract content rather than prose. They are easy to fix (10-20 minutes) but they are real propagation failures from the §6 edits to the abstract, intro, and conclusion. The trajectory remains positive, but the round-4 fixes are not yet clean.

## Summary

**Overall assessment**: The three flagged majors from 2026-04-13 (MAJ-1 regex example, MAJ-2 cipher TM shift cipher map, MAJ-3 typed-chain misapplication) and the three flagged minors (LC-MIN-3 notation, LC-MIN-4 cipher type definition, LC-MIN-6 zero-errors framing) are mostly resolved at the body level. §6.1 now factors the shift into auxiliary cipher maps and gives a self-consistent space bound. §6.3 cleanly distinguishes the typed-chain bound from the deterministic-trajectory bound. §3 has a formal Definition 3.3 of cipher type. §7.3 correctly qualifies the "zero errors" claim.

But four new defects entered:
1. The MAJ-2 fix updated Prop 6.1 to `O(|Q|² · |Γ|)` but did not propagate to the abstract (line 60), introduction (line 120), or conclusion (line 1534), all of which still claim `O(|Q| · |Γ|)`. Three locations now contradict the body proposition.
2. The MAJ-3 fix correctly distinguishes the two bound arguments in §6.3 but the conclusion (line 1536-1537) still says "Both are instances of a single cut-point pattern that the typed-chain bound constrains identically." This contradicts §6.3's distinction.
3. The MAJ-1 fix removed the strawman exponential cost claim from the regex example, but the new closing line "The two realizations have the same total construction cost (up to a constant factor)" (line 1222-1223) is also wrong: the example itself shows cipher TM at `O(|Q_R|·|Σ|)` and expression tree at `O(ℓ·|Q_R|·|Σ|)`, which differ by a factor of `ℓ`.
4. The LC-MIN-3 fix renamed only the *plaintext* transition function from `\delta_T` to `\tau_T`, but left the cipher version as `\hat{\delta}_T` (lines 977, 987, 1017, 1039, 1207, 1213, 1214). The visual notation collision with TV-distance `\delta` at lines 237 ff. is not fully resolved.

Carry-forward issues from prior rounds (M2/M3/M4/M5 experimental, M7 doc class, M9 self-citations) remain open as expected.

**Strengths**:
1. The MAJ-3 fix in §6.3 (lines 1178-1198) is conceptually sharp. The expression-tree case invokes Prop 5.5 with bound `\sum_i N_i`. The cipher-TM case is explicitly called out as not satisfying typed-chain hypothesis (single cipher space, self-loop) and bounded by deterministic-trajectory. The closing prose frames cut-point structure as a syntactic abstraction over decompositions, not a single confidentiality theorem. (logic-checker)
2. The MAJ-2 fix factors the shift into named auxiliary cipher maps `\hat{clear}` and `\hat{set}_q` (line 991-1001). Body Proposition 6.1 (line 1009-1027) now self-consistently accounts for all three families with total `O(|Q|² · |Γ|)`. (logic-checker)
3. The new Definition 3.3 (cipher type, line 271-284) sits cleanly between Def 3.2 (machines) and §4. The §3 flow now reads: Def 3.1 (cipher map) → four properties → Bernoulli paragraph → cipher value note → Def 3.2 (machines) → Def 3.3 (cipher type) → §4. No redundancy with Def 3.1. The §4 inline introduction has been removed. (prose-auditor)
4. The LC-MIN-6 fix at lines 1424-1427 reads cleanly: "As expected from the PHF construction ... each cipher map is built over its declared input set, so on-domain inputs are exact lookups by construction." Honest framing of a definitional sanity check. (methodology-auditor)
5. PDF builds clean at 19 pages. All references resolve. No build warnings. No undefined or multiply-defined labels. (format-validator)
6. Round-4 fixes did not regress any prior-round resolutions. C1 (entropy form), M1 (typed-chain arity), M11 (denominator), LC-MIN-1/LC-MIN-2 cleanups all stand. (cross-cut)

**Weaknesses**:
1. Cipher TM space claim mismatch: abstract (line 60), intro contributions (line 120), and conclusion (line 1534) all say `O(|Q|·|Γ|)`; Prop 6.1 (line 1021) says `O(|Q|²·|Γ|)`. Three locations to update for consistency. (logic-checker)
2. Conclusion line 1536-1537 still asserts that the typed-chain bound constrains both realizations identically; this directly contradicts the MAJ-3 fix in §6.3. (logic-checker)
3. The new regex example (lines 1200-1230) eliminates the prior strawman but introduces a new inaccuracy: it claims "same total construction cost (up to a constant factor)" while showing one realization at `O(|Q_R|·|Σ|)` and the other at `O(ℓ·|Q_R|·|Σ|)`. (logic-checker)
4. LC-MIN-3 fix is partial. The plaintext function was renamed `\delta_T → \tau_T`, but the cipher version `\hat{\delta}_T` still uses `\delta`. The notation collision with representation-uniformity `\delta` is therefore visually preserved in §6.1 and §6.3. (prose-auditor)
5. Cipher TM `\hat{set}_q` selection mechanism is under-specified. The construction text says "parameterized by the new state q extracted from c'" but does not specify how the untrusted machine selects the right `\hat{set}_q` instance without decoding c'. (logic-checker, methodology-auditor)
6. Carry-forward: M2/M3/M4/M5 experimental issues (no baselines, no error bars, FPR table missing, granularity space data missing). (methodology-auditor)
7. Carry-forward: M7 document class pending venue commitment, M9 unpublished self-citations. (citation-verifier, format-validator)

**Finding counts**: Critical: 0 | Major: 2 | Minor: 5 | Suggestions: 3

The two majors are the abstract/intro/conclusion mismatch with Prop 6.1 (one bundle: items 1+2 above) and the regex-example construction-cost equality claim (item 3). Both are tractable in a single editing pass.

---

## Status of prior-round fixes

| 2026-04-13 finding | 2026-04-29 status | Notes |
|---|---|---|
| MAJ-1 (regex example fabricates exponential cost) | **partial** | Strawman exponential claim is gone; new claim of "same total cost (up to a constant factor)" is also wrong. |
| MAJ-2 (cipher TM shift cipher map space unanalyzed) | **resolved** | Two unary cipher maps `\hat{clear}` and `\hat{set}_q` introduced; Prop 6.1 self-consistently sums to `O(|Q|² · |Γ|)`. |
| MAJ-3 (§6.3 typed-chain misapplied to cipher TM) | **fully resolved** | "What bounds the orbit in each case" paragraph distinguishes typed-chain (expression tree) from deterministic-trajectory (cipher TM). |
| LC-MIN-3 (delta_T notation collision) | **partial** | Plaintext renamed to `\tau_T`; cipher version `\hat{\delta}_T` still uses `\delta`. |
| LC-MIN-4 (informal C(X) introduction) | **fully resolved** | Definition 3.3 added in §3 Preliminaries; informal §4 introduction removed. |
| LC-MIN-6 ("zero errors" framing) | **fully resolved** | Lines 1424-1427 read as expected. |

| Prior carry-forward | 2026-04-29 status |
|---|---|
| M2/M3/M4/M5 (experimental: baselines, error bars, FPR table, granularity space) | unchanged, remain open by design |
| M7 (acmart for PLAS) | unchanged, pending venue commitment |
| M9 (unpublished self-citations) | unchanged |

---

## Major Issues

### MAJ-1. Cipher TM space mismatch across abstract/intro/conclusion vs. Prop 6.1 (logic-checker, format-validator; new in 2026-04-29)

- **Locations**:
  - Line 60 (abstract): "(space $O(|Q| \cdot |\Gamma|)$, leaks head movement)"
  - Line 120 (intro contributions): "with space $O(|Q| \cdot |\Gamma|)$ at the cost of leaking head movement"
  - Line 1021 (Prop 6.1): "Total space is $O(|Q|^2 \cdot |\Gamma| \cdot |\{L,R,S\}|) = O(|Q|^2 \cdot |\Gamma|)$"
  - Line 1023 (Prop 6.1 follow-up): "When $|X| \gg |Q|^2 \cdot |\Gamma|$, this is a qualitative improvement"
  - Line 1534 (conclusion): "a cipher Turing machine gives space $O(|Q| \cdot |\Gamma|)$"
- **Problem**: The MAJ-2 fix correctly updated Prop 6.1's body to account for the auxiliary cipher maps (`\hat{clear}`, `|Q| \cdot 3` instances of `\hat{set}_q`) yielding `O(|Q|^2 \cdot |\Gamma|)`. But the abstract, intro contributions, and conclusion all still report the prior `O(|Q| \cdot |\Gamma|)` figure (the size of the primary `\hat{\delta}_T` map alone). A reviewer reading the abstract will see a different headline number than the body.
- **Suggestion**: Update lines 60, 120, and 1534 to `O(|Q|^2 \cdot |\Gamma|)`. The qualitative claim ("space is independent of input domain |X|") is unchanged; only the polynomial in the state set updates.
- **Cross-verified**: Yes (area chair, against Prop 6.1 line 1021 and the |Q|·3 instance count at line 1019).

### MAJ-2. Conclusion claim about typed-chain bound contradicts §6.3 distinction (logic-checker; new in 2026-04-29)

- **Location**: Conclusion, lines 1536-1537.
- **Quoted text**:
  > "Both are instances of a single cut-point pattern that the typed-chain bound constrains identically."
- **Problem**: The MAJ-3 fix in §6.3 (lines 1185-1198) explicitly says the cipher TM does *not* satisfy the typed-chain hypothesis (it reuses a single cipher space, self-loop, not a chain) and is bounded by a separate deterministic-trajectory argument. The conclusion's "constrains identically" claim contradicts this. The two bounds coexist as different arguments, not as one bound applied uniformly.
- **Suggestion**: Reword as "Both are instances of a single cut-point pattern, with the orbit bounded by typed-chain reasoning (expression tree) or by deterministic-trajectory reasoning (cipher TM); both turn the cut-point structure into a finite, design-time orbit budget." Or shorter: "Both are instances of a single cut-point pattern; their orbits are bounded by complementary arguments (typed-chain for the expression tree, deterministic-trajectory for the cipher TM)."
- **Cross-verified**: Yes, against §6.3 paragraph "What bounds the orbit in each case" (lines 1178-1198).

---

## Minor Issues

### MIN-1. Regex example claims equal total cost while showing different costs (logic-checker; new in 2026-04-29; partial regression of MAJ-1)

- **Location**: §6.3, Example 6.7 (lines 1200-1230).
- **Quoted text**: "The two realizations have the same total construction cost (up to a constant factor) and the same orbit bound" (lines 1222-1223).
- **Problem**: The example body itself says cipher TM has "single cipher map of space $O(|Q_R| \cdot |\Sigma|)$" (line 1207-1208) and expression tree has "total $O(\ell \cdot |Q_R| \cdot |\Sigma|)$" (line 1216). These differ by a factor of `\ell`, which is not a constant. The "same total construction cost" claim is internally inconsistent with the same example's space accounting.
  - When the cipher TM's auxiliary `\hat{clear}` and `\hat{set}_q` maps are included (per Prop 6.1), total cipher-TM space is `O(|Q_R|^2 \cdot |\Sigma|)`, while the expression tree is `O(\ell \cdot |Q_R| \cdot |\Sigma|)`. These are equal when `\ell ≈ |Q_R|`, but in general the cipher TM wins for large `\ell` and the tree wins for large `|Q_R|`.
  - Note that the prior MAJ-1 finding (strawman exponential cost) is genuinely fixed: the new typed-chain decomposition is the natural one and gives polynomial total cost. The remaining issue is one of imprecise framing rather than fabricated cost.
- **Suggestion**: Either (a) rewrite the closing as "The two realizations have similar asymptotic cost (within polynomial factors) and the same orbit bound; the comparison turns on the relationship between `\ell` and `|Q_R|`", or (b) accept the cost asymmetry and reframe as "For long strings (`\ell \gg |Q_R|`), the cipher TM is more compact; for exponential DFAs (`|Q_R| \gg \ell`), the expression tree is more compact; the choice between them is more leakage-driven than space-driven within their shared regime", or (c) drop the "same total construction cost" subclaim entirely and let the leakage-profile distinction stand on its own.
- **Cross-verified**: Yes, against the example's own space arithmetic.

### MIN-2. Notation collision `\hat{\delta}_T` vs. `\delta` (TV-distance) (prose-auditor; partial regression of LC-MIN-3)

- **Location**: §6.1, lines 977, 987, 1017, 1039; §6.3, lines 1207, 1213, 1214.
- **Quoted text**: "a cipher map $\hat{\delta}_T$ for the transition function $\tau_T$" (line 977-979).
- **Problem**: The fix renamed the *plaintext* TM transition function `\delta_T → \tau_T`, but kept the *cipher* version as `\hat{\delta}_T`. So `\delta` still appears in §6.1 and §6.3 as the body of `\hat{\delta}_T`. The visual collision with the representation-uniformity parameter `\delta` (used heavily in §3-§4, lines 237, 353, 365, 376, 386, 426, 442-505, etc.) is therefore preserved in §6.
- **Suggestion**: Rename `\hat{\delta}_T → \hat{\tau}_T` (and `\hat{\delta}_i → \hat{\tau}_i` in the regex example) to complete the rename.
- **Cross-verified**: Yes, by grep across main.tex.

### MIN-3. Cipher TM `\hat{set}_q` selection mechanism is under-specified (logic-checker, methodology-auditor)

- **Location**: §6.1, Definition 6.1, lines 991-1001.
- **Quoted text**: "$\hat{\mathrm{set}}_q : \cipher{Q \times \Gamma} \to \cipher{Q \times \Gamma}$ (parameterized by the new state $q$ extracted from $c'$) places the head into the neighbouring cell at offset $d$. We treat the shift as a choice over a small finite family of unary cipher maps, one per $(q, d)$ pair".
- **Problem**: The text says `q` is "extracted from `c'`", but the untrusted machine cannot decode `c'` (no trapdoor). It is therefore unclear how the untrusted machine selects which `\hat{\mathrm{set}}_q` instance to apply. Three options:
  1. The untrusted machine extracts `q` (defeats confidentiality of the state sequence).
  2. The untrusted machine evaluates all `|Q|·3` instances and somehow combines (per-step cost becomes `O(|Q|)` not `O(1)`).
  3. The cipher map `\hat{\delta}_T` outputs an additional plaintext selector indicating which `\hat{\mathrm{set}}_q` to apply (this would need to be specified, and would leak `q` in plaintext per step, which is roughly equivalent to leaking the state sequence).
- **Suggestion**: Specify the selection mechanism explicitly. The most defensible reading is option 3: the cipher TM transition output is `(c', d, q_selector)` where `q_selector \in Q` is a plaintext selector that the untrusted machine uses to pick the right `\hat{\mathrm{set}}_q`. This formalizes the leakage explicitly. The leakage profile then becomes (head-movement sequence, state sequence) rather than just head-movement, which is a stronger leakage than was previously claimed but does not invalidate the construction. The proposition would still give the same `O(|Q|^2 \cdot |\Gamma|)` space bound.
- **Cross-verified**: Yes, against the four-properties cipher map definition (no decoding by untrusted machine).

### MIN-4. Auxiliary cipher map noise budget not separately accounted (logic-checker)

- **Location**: §6.1, Proposition 6.1.
- **Problem**: Per step, three cipher maps are applied (`\hat{\delta}_T`, `\hat{clear}`, one `\hat{set}_q`). By Composability (Property 4 of §3), composed correctness is `1 - (1-η_1)(1-η_2)(1-η_3) ≈ η_1 + η_2 + η_3` for small `η_i`. After `T` steps, total error rate is roughly `3T · η_avg`. To achieve a target `η_total`, each cipher map needs `η_i ≤ η_total / (3T)`, so the per-entry noise budget `-log_2 ε` grows as `\log_2(3T) - \log_2(η_total)`. Prop 6.1 does not surface this dependency on `T`. The per-entry storage is mentioned generically but the `T` factor is implicit.
- **Suggestion**: Either explicitly state that the per-entry noise budget grows as `\log_2 T` for an `η`-bounded `T`-step cipher TM, or note that this is absorbed into the `O(\cdot)` bound. A one-line clarification suffices.

### MIN-5. Carry-forward minors from 2026-04-13 (citation-verifier, methodology-auditor, prose-auditor)

The 2026-04-13 review's MIN-1 through MIN-14 are mostly carry-forward. Specific items relevant to current text:
- MIN-1 (Theorem 5.3 proof notational defect): unchanged, minor.
- MIN-5 through MIN-9 (granularity table unnumbered, queries protocol, 150-input scale, hardware spec, reproducibility statement): all unchanged.
- MIN-10 through MIN-14 (writing nits, conclusion overstatement, phobic uncited): unchanged.

These carry-forward unchanged and continue to be acceptable for the venue spread (PLAS, IACR ePrint, arXiv).

---

## Suggestions

1. **Single editing pass to fix MAJ-1, MAJ-2, MIN-1, MIN-2.** All four are surface-level edits (4 line changes for MAJ-1, 1 for MAJ-2, 1 for MIN-1's closing line, 7 for MIN-2's notation rename). Estimate 15-30 minutes.

2. **Add a short construction footnote for `\hat{set}_q` selection (MIN-3).** Either resolve to "untrusted machine receives a plaintext selector and the leakage profile is (movements, states)" or to "untrusted machine evaluates all `|Q|` instances per step at `O(|Q|)` per-step cost". Either is defensible, but the choice should be made.

3. **Carry-forward path to acceptance** is unchanged from the 2026-04-13 review:
   - Run experiments with baselines, error bars, FPR-compounding table, granularity space data (M2/M3/M4/M5).
   - Commit to a venue and swap document class if PLAS (M7).
   - Post `towell2026cipher` to arXiv or IACR ePrint to externalize the load-bearing self-citation (M9).

---

## Detailed Notes by Domain

### Logic and Proofs (logic-checker)

The MAJ-3 §6.3 fix is the strongest of the round-4 fixes. The "What bounds the orbit in each case" paragraph (lines 1178-1198) cleanly distinguishes typed-chain reasoning from deterministic-trajectory reasoning, with sharp prose explaining why both bounds coexist (the cut-point structure is a syntactic abstraction over decompositions, not a single confidentiality theorem). The closing sentence is well-calibrated.

The MAJ-2 fix is solid at the body level: Prop 6.1 names three cipher map families, sums their counts (`1 + 1 + |Q| \cdot 3`), and reports `O(|Q|^2 \cdot |\Gamma|)` consistently with the per-map domain `|Q \cdot \Gamma|`. The arithmetic is internally correct.

But Prop 6.1's body update did not propagate to abstract/intro/conclusion (MAJ-1 of this review). And the §6.3 fix did not propagate to the conclusion (MAJ-2 of this review). These are the two new majors entered with the round-4 fixes.

The new regex example resolves the strawman exponential issue but introduces a "same total construction cost" claim that contradicts its own arithmetic (MIN-1). Less serious than the prior strawman (the example is no longer fabricating an asymptotic difference) but still imprecise.

The cipher TM `\hat{set}_q` selection mechanism (MIN-3) is a deeper construction-detail issue that surfaces from the MAJ-2 factoring. The construction is operationally implementable but the leakage profile may need to be revised: it is not "head-movement only" if the state selector is plaintext.

### Novelty and Contribution (novelty-assessor)

Contribution structure unchanged. Sum-type impossibility, orbit-closure framework, typed-chain bound, and dual realizations all stand. The round-4 fixes do not affect the novelty story; they affect the integrity of the cipher-TM realization's space and leakage claims. None of the fixes touch the algebraic-types core.

### Methodology (methodology-auditor)

Carry-forward issues (M2/M3/M4/M5) remain unchanged. The single most impactful remaining methodology fix is to flesh out the FPR-compounding finding into a proper experimental subsection with a chain-length table.

The cipher TM `\hat{set}_q` selection mechanism (MIN-3) is a methodological gap in the construction description.

### Writing and Presentation (prose-auditor)

The §3 flow with Definition 3.3 added is clean. The §6.3 prose is much stronger than the 2026-04-13 version (the typed-chain-vs-trajectory distinction reads cleanly). The §7.3 LC-MIN-6 fix reads well.

Two prose-level issues persist: the partial `\delta_T → \tau_T` rename (MIN-2) and the regex example's "same total construction cost" claim (MIN-1).

The conclusion (line 1530-1552) has not been updated since the §6 edits; it should be revised to match (MAJ-1, MAJ-2 of this review).

### Citations and References (citation-verifier)

Bibliography unchanged. 21 citations, all in use. Two positioning gaps from prior rounds (cipher TM vs. obfuscation; @cipher_node vs. FHE compilers) remain. Self-citation issue (towell2026cipher 16x, towell2026bernoulli 4x, towell2026maxconf 1x) persists.

### Formatting and Production (format-validator)

Build is clean. 19 pages. No undefined references, no multiply-defined labels, no warnings. Document class still `article`, pending venue commitment.

---

## Recommendation Rationale

**major-revision** because:
- Two new majors (MAJ-1 abstract/intro/conclusion mismatch with Prop 6.1; MAJ-2 conclusion's typed-chain claim contradicts §6.3) are real defects that affect what a reviewer reading the abstract will see.
- These are tractable: a single editing pass of 15-30 minutes resolves both, plus MIN-1 (regex example imprecision) and MIN-2 (partial notation rename).
- Carry-forward issues (M2/M3/M4/M5 experimental, M7 doc class, M9 self-citations) remain open by design.

**Why not minor-revision**: The user's expected recommendation was minor-revision contingent on "no new defects entered". Four new defects entered, two at the abstract/conclusion level. These are propagation failures from §6 edits, not new ideas, but they do create internal inconsistencies that a reviewer will catch.

**Why not major-revision (heavier)**: The defects are localized, surface-level, and easy to fix. There are no proof-soundness issues, no novelty issues, no methodology issues beyond carry-forward. The §6 body edits are technically correct.

**Path to next round (15-30 minutes of editing)**:
1. Update line 60 (abstract): `O(|Q| \cdot |\Gamma|)` → `O(|Q|^2 \cdot |\Gamma|)`.
2. Update line 120 (intro contributions): same.
3. Update line 1534 (conclusion): same.
4. Update lines 1536-1537 (conclusion): replace "typed-chain bound constrains identically" with "complementary bounds (typed-chain for the expression tree, deterministic-trajectory for the cipher TM)".
5. Update line 1222-1223 (regex example): drop or rephrase "same total construction cost".
6. Rename `\hat{\delta}_T → \hat{\tau}_T` and `\hat{\delta}_i → \hat{\tau}_i` (7 occurrences).
7. Optional: add 1-line clarification for `\hat{set}_q` selection mechanism.

After this pass, recommendation should be **minor-revision** with carry-forward experimental issues as the only remaining blocker.

---

## Comparison with 2026-04-13 Review

The 2026-04-13 to 2026-04-29 revision's effect on prior findings:

**Major (prior, 6)**:
- MAJ-1 (regex example exponential cost): **partial**. Strawman is gone; new framing has its own (lesser) issue.
- MAJ-2 (cipher TM shift cipher map space): **resolved**.
- MAJ-3 (typed-chain misapplication): **fully resolved** in §6.3, but conclusion still has the old claim (new MAJ-2 of this review).
- MAJ-4 (experimental baselines/error bars): **carry-forward**.
- MAJ-5 (positioning vs obfuscation/FHE compilers): **carry-forward**.
- MAJ-6 (unpublished self-citations): **carry-forward**.

**Minor (prior, 14)**:
- MIN-1 (Theorem 5.3 proof notation): unchanged.
- MIN-2 (`\delta_T` notation): **partial**. Plaintext renamed; cipher version unchanged.
- MIN-3 (C(X) informal in §4): **resolved** (Definition 3.3 added).
- MIN-4 ("zero errors" framing): **resolved**.
- MIN-5 through MIN-14: unchanged.

**New defects entered**:
- (this review's MAJ-1) Abstract/intro/conclusion claim `O(|Q| \cdot |\Gamma|)` while Prop 6.1 says `O(|Q|^2 \cdot |\Gamma|)`.
- (this review's MAJ-2) Conclusion claims typed-chain bound constrains both realizations identically; contradicts §6.3.
- (this review's MIN-1) Regex example claims "same total construction cost" while showing differing costs.
- (this review's MIN-3) `\hat{set}_q` selection mechanism under-specified (surfaces from MAJ-2 factoring).

Summary: 3 of 6 prior majors fully resolved, 1 partial; 2 of 6 minors fully resolved, 1 partial; 4 new defects entered (2 majors, 2 minors).

This round's pattern matches the prior pattern: fixes resolve the targeted issues at the local site but have not been propagated to other parts of the paper that reference the same content. The fix-then-propagate discipline would close this gap.

---

## Review Metadata

- Specialists consulted: logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator. (The Task tool for parallel subagent execution was not used given the verification-pass nature of this review; the area chair conducted each specialist's analysis directly. Per-specialist files would be redundant for confirm-fixed items and are not produced.)
- Cross-verifications performed:
  - MAJ-3 verification: §6.3 (lines 1178-1198) read against Def 5.4 (line 858-866), Prop 5.5 (line 873-895). Bound arguments correctly distinguished.
  - MAJ-2 verification: Prop 6.1 arithmetic re-checked. Three families of cipher maps: `\hat{\delta}_T` (1 instance, `O(|Q| \cdot |\Gamma|)`), `\hat{clear}` (1 instance, `O(|Q| \cdot |\Gamma|)`), `\hat{set}_q` (`|Q| \cdot 3` instances, each `O(|Q| \cdot |\Gamma|)`). Total: `O(|Q|^2 \cdot |\Gamma|)`. Self-consistent.
  - LC-MIN-4 verification: Definition 3.3 placement (line 271-284) read in context. Sits between Def 3.2 (machines) and §4. No redundancy with Def 3.1.
  - Build verification: clean compile via `pdflatex / bibtex / pdflatex / pdflatex`. 19-page output, no warnings, no undefined references.
  - Cross-section consistency check: abstract, intro contributions, body propositions, and conclusion all read for the cipher TM space figure. Three locations (abstract, intro, conclusion) say `O(|Q| \cdot |\Gamma|)`, contradicting body Prop 6.1.
- Disagreements noted: 0. All findings cross-verified against the manuscript text.
- Hallucination check: every quoted text and line reference verified against /home/spinoza/github/trapdoor-computing/papers/algebraic-cipher-types/paper/main.tex.
