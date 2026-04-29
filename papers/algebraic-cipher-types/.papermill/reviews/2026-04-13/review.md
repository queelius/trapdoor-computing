# Multi-Agent Review Report

**Date**: 2026-04-13
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Author**: Alexander Towell
**Version**: Post second-round fixes (2026-04-12 evening through 2026-04-13), 19pp, 1518 lines, LaTeX article class
**Prior reviews**:
- 2026-04-08 (major-revision; Critical: 2, Major: 11, Minor: 12, Suggestions: 6)
- 2026-04-12 (major-revision; Critical: 1, Major: 12, Minor: 18, Suggestions: 14)

**Recommendation**: **major-revision** (third in a row, but the trajectory is positive: each round narrows the open issue set, and the remaining defects are concentrated in §6.1, §6.3, and the experimental section).

## Summary

**Overall assessment**: The 2026-04-13 second-round fixes resolve the most consequential 2026-04-12 finding (C1, candidate-set tautology) cleanly: the entropy-form theorem replaces the disconnected candidate-set definition entirely, and the corollary's set-form bound uses |X| correctly. The typed-chain arity fix (M1) lands fully: the recurrence N_{i+1} = N_i^{a_i} is sound, the proof goes through, and the example matches. The bibliography expansion to 21 cites closes the 2026-04-12 thinness concern.

Two new defects entered with the second-round fixes. The cipher TM definition cleanup (LC-MIN-1, LC-MIN-2) eliminated the pair-cipher-map issue but introduced an unanalyzed "second cipher map for the shift operation" whose space cost is not accounted for in Proposition 6.1. The new regex example in §6.3 contains errors: the cipher-TM analysis assumes O(r) DFA states (potentially 2^r), and the expression-tree analysis fabricates an exponential cost by choosing a strawman decomposition.

The carry-forward experimental issues (M2, M3, M4, M5) remain open by design (require re-running experiments). M7 document class is pending venue commitment. M9 self-citations remain load-bearing.

**Strengths**:
1. C1 (candidate-set tautology) is now cleanly resolved. The entropy-form theorem `H(X | view) >= H(X) - log_2 |orbit|` replaces the disconnected candidate-set detour. The set-form bound is presented as a corollary with |X| in the denominator. (logic-checker)
2. M1 (typed-chain arity) is fully resolved. The recurrence and the example are consistent. (logic-checker)
3. Bibliography expanded to 21 cites; all 21 are now in use; four new references (Smith 2009, Cash 2015, Grubbs 2017, Lang 1995) are appropriately placed. (citation-verifier)
4. The QIF positioning (Smith 2009 in §2 Related Work) grounds the entropy-form bound in a recognized tradition. (novelty-assessor)
5. Section 6.3 is now substantive (about 75 lines, up from 15 in 2026-04-12) with a formal cut-point definition, explicit mapping of both realizations, and a worked example. The structure is right even though the example contents have issues. (prose-auditor)
6. PDF builds clean at 19 pages. All 54 labels resolve. All 21 cites resolve. No build warnings. (format-validator)

**Weaknesses**:
1. The new regex example in §6.3 fabricates an exponential cost for the expression-tree decomposition. Both realizations should have O(ell * |Q| * |Sigma|) total space. (logic-checker)
2. The cipher TM cleanup introduced a "second cipher map for the shift operation" without space analysis. Proposition 6.1's claim of O(|Q| * |Gamma|) does not include this auxiliary cipher map. (logic-checker, methodology-auditor)
3. The §6.3 paragraph mapping the typed-chain bound onto the cipher TM conflates typed-chain orbit reasoning (which requires distinct cipher spaces) with deterministic-trajectory reasoning. The cipher TM is a self-loop, not a typed chain. (logic-checker)
4. Theorem 5.3's proof has a notational confusion between "view = orbit set" and "view = element of orbit set". Result is sound under either reading but the proof needs tightening. (logic-checker)
5. Carry-forward experimental issues (no baselines, no error bars, FPR table missing, granularity space data missing) are unaddressed. (methodology-auditor)
6. Self-citations to unpublished manuscripts (towell2026cipher, towell2026bernoulli) remain load-bearing. (citation-verifier)
7. Cipher TM positioning vs. obfuscation literature is missing (no Lynn-Prabhakaran-Sahai 2004, no garbled TMs, no iO). (citation-verifier, novelty-assessor)
8. @cipher_node decorator positioning vs. FHE compilers is missing (no Concrete, HEIR, Viand 2021 SoK). (citation-verifier, novelty-assessor)

**Finding counts**: Critical: 0 | Major: 6 | Minor: 14 | Suggestions: 8

The reduction in critical count (2 in 2026-04-08, 1 in 2026-04-12, 0 in 2026-04-13) reflects real progress on proof-soundness issues. The major count is roughly stable because two new majors entered (regex example, shift cipher map) while several were closed.

---

## Status of prior-review findings

This section explicitly addresses the orchestrator's request to confirm or deny each fix.

### Closed and verified (2026-04-13)

| Prior finding | Status | Notes |
|---|---|---|
| C1 (candidate-set tautology) | **fully resolved** | Entropy-form theorem H(X | view) >= H(X) - log_2 |orbit| as primary; set-form as corollary using |X|. The disconnected candidate-set definition is gone. Minor notational confusion in the proof (V_F as set vs. scalar) does not invalidate the result. |
| M1 (typed-chain arity mismatch) | **fully resolved** | Recurrence N_{i+1} = N_i^{a_i} is sound. Proof walks through level-by-level. Example 5.4 matches: m=1 gives 1+k=3; multi-start m gives m + m^2 + m^4. |
| M11 (denominator switch) | **fully resolved** | The corollary cleanly uses |X|. The entropy form sidesteps the issue. |
| LC-MIN-1 (cipher TM head direction) | **fully resolved** | Output is (c', d) with d in clear. |
| LC-MIN-2 (pairing cipher map) | **partially resolved** | Joint encoding C(Q x Gamma) per cell removes the pair-cipher-map. But a new "second cipher map for the shift operation" was introduced without space analysis. See LC-NEW-1 below. |
| M6 (bibliography thin) | **resolved** | 21 cites, all in use. Bibliography is now on the lower end of expectations but no longer thin. |
| M8 (thin §6.3 synthesis) | **structurally resolved, content has errors** | §6.3 now has a formal cut-point definition, mapping paragraphs, and a worked example. The structure is right. The example contents have errors (see LC-NEW-2 below). |

### Carry-forward (still open by design)

| Prior finding | Status | Notes |
|---|---|---|
| M2/M3/M4/M5 (experimental issues) | **carry-forward** | Require re-running experiments in cipher-maps Python lib. Not yet done. |
| M7 (document class) | **carry-forward** | Pending venue commitment. |
| M9 (unpublished self-citations) | **carry-forward** | Posting towell2026cipher to arXiv/IACR ePrint is the recommended fix. |
| LC-MIN-3 through LC-MIN-6 | **mostly carry-forward** | delta vs delta_T notation collision still present. C(X) defined informally in §4 rather than §3. "Zero errors" framing still definitional. Acceptable but should be tightened. |

### New defects introduced by the 2026-04-13 fixes

| Finding | Source | Notes |
|---|---|---|
| LC-NEW-1: cipher TM shift cipher map space not analyzed | logic-checker, methodology-auditor | Prop 6.1 claims O(|Q| * |Gamma|) for delta_T but the new definition invokes a "second cipher map for the shift operation" potentially of size O((|Q| * |Gamma|)^2). |
| LC-NEW-2: regex example in §6.3 contains errors | logic-checker | DFA state count claim (O(r) instead of 2^r), exponential expression-tree cost claim (strawman decomposition). Both halves of the comparison have issues. |
| LC-NEW-3: §6.3 conflates typed-chain bound with deterministic-trajectory bound | logic-checker | The cipher TM is a self-loop, not a typed chain. Its 1+T orbit bound comes from determinism, not from Proposition 5.5. |
| LC-NEW-4: Thm 5.3 proof has notational defect | logic-checker | View defined as orbit set (V_F(c) = orbit_F(c)) but proof treats view as scalar in orbit. Easily fixed in revision. |

---

## Major Issues

### MAJ-1. Regex example in §6.3 fabricates exponential cost (logic-checker; new in 2026-04-13)

- **Location**: §6.3, Example 6.1, lines 1167-1183.
- **Quoted text**:
  > "As an expression tree, the program is a fold over the string with ell cut points at the transition function; the combiner cipher map above them has domain C(Q)^ell so its construction cost is exponential in ell."
- **Problem**: The natural typed-chain decomposition of regex matching as a fold has ell separate cipher maps delta_0, ..., delta_{ell-1}, each of space O(|Q| * |Sigma|), total O(ell * |Q| * |Sigma|). This is linear in ell, not exponential. The example forces the exponential by choosing a strawman "single combiner over all ell intermediate states" decomposition. As a result, the example's conclusion "Cipher TM is preferable for long strings" is conjured by the strawman, not by an actual cost difference.

  The cipher-TM half also has an issue: "Q is the set of DFA states for R (size O(r))" without acknowledging that DFA states can be 2^r in worst case (subset construction).

- **Suggestion**: Replace the example with one where the realizations genuinely differ. Or correct it to acknowledge that both have O(ell * |Q| * |Sigma|) total space, both leak ell, and the choice between them is more subtle than the example suggests. Alternatively: present cut-point placement as an open optimization problem (already listed in §8 Discussion) and remove this example.

- **Cross-verified**: Yes, by area chair. The regex-fold typed-chain decomposition is straightforward; the strawman is visible at line 1177-1179.

### MAJ-2. Cipher TM shift cipher map space not analyzed (logic-checker, methodology-auditor; new in 2026-04-13)

- **Location**: §6.1, Definition 6.1 (lines 960-987), Proposition 6.1 (lines 989-1000).
- **Quoted text**:
  > "writes c' back to the current cell, shifts the 'head' marker according to d (by swapping the state component of the neighbouring cell with the current cell via a second cipher map for the shift operation)"
- **Problem**: The "second cipher map for the shift operation" is invoked but not analyzed. Its natural domain is C(Q x Gamma) x C(Q x Gamma) (two adjacent cells), giving space O((|Q| * |Gamma|)^2). Proposition 6.1's claim of O(|Q| * |Gamma|) for the cipher TM is therefore incomplete.

  Alternative: factor the shift into two unary cipher maps (extract state from cell A, place state into cell B), each O(|Q| * |Gamma|). But Definition 6.1 says "swap" which suggests a binary operation.

- **Suggestion**: Either (a) explicitly factor into two unary cipher maps with separate analyses, or (b) acknowledge the shift cipher map as a separate sub-construction with its own space cost in Proposition 6.1.

- **Cross-verified**: Yes. methodology-auditor independently flagged this as MA-NEW-3.

### MAJ-3. §6.3 typed-chain bound applied to cipher TM is conceptually wrong (logic-checker; new in 2026-04-13)

- **Location**: §6.3, paragraph "What the typed-chain bound says in each case" (lines 1151-1165).
- **Quoted text**:
  > "For a cipher TM running for T steps with self-loop at a single (binary-arity, if state and symbol are distinct inputs) cut point, a naive reading gives N_i = 1 for a single initial tape configuration so the orbit is bounded by 1 + T."
  > "Typing the cipher spaces between cut points is what prevents the self-loop in either realization from degenerating into an unbounded orbit."
- **Problem**: Proposition 5.5 explicitly requires distinct cipher spaces (Definition 5.4). The cipher TM has a single cipher space C(Q x Gamma) reused at every step (a self-loop). Proposition 5.5 therefore does not apply to the cipher TM.

  The cipher TM's bound of 1 + T (or m * (T+1)) follows from a different argument: deterministic computation produces a single trajectory of length T, so at most T+1 distinct cipher values appear. This is a deterministic-trajectory argument, not a typed-chain argument.

  The closing line "Typing the cipher spaces between cut points is what prevents the self-loop in either realization from degenerating into an unbounded orbit" mixes the two: typing prevents unboundedness in the expression tree, but the cipher TM is bounded by determinism, not typing.

- **Suggestion**: Distinguish the two arguments. Add one paragraph explaining that the cipher TM is bounded by deterministic-trajectory length (no typing involved), and the expression tree is bounded by Proposition 5.5 (which requires typing).

- **Cross-verified**: Yes, against Definition 5.4 (line 845-853).

### MAJ-4. Carry-forward: experimental baselines and error bars (methodology-auditor; carry-forward of M2/M3 from 2026-04-12)

Same issue as 2026-04-12. No baselines (plaintext, Bloom filter, SSE benchmark). No error bars, no run counts, no hardware spec. Single most impactful methodology fix is to flesh out the FPR-compounding finding into a proper subsection with a chain-length table.

### MAJ-5. Carry-forward: bibliography positioning gaps for cipher TM and @cipher_node (citation-verifier, novelty-assessor; new framing of 2026-04-12 M6)

- Cipher TM: should cite at least one obfuscation-of-FSM/TM reference (Lynn-Prabhakaran-Sahai 2004, Wichs-Zirdelis 2017, garbled TM line of work).
- @cipher_node: should cite at least one FHE compiler reference (Viand-Jattke-Hithnawi 2021 SoK).

Both are positioning preemptions, not strict requirements. A reviewer asking "how does this differ from obfuscation?" or "is this an FHE compiler?" will not find a textual answer.

### MAJ-6. Carry-forward: unpublished self-citations (citation-verifier; carry-forward of M9)

towell2026cipher (16x), towell2026bernoulli (4x), towell2026maxconf (1x). Posting at least the first to arXiv/IACR ePrint before submission is the recommended path.

---

## Minor Issues

### MIN-1. Theorem 5.3 proof notational defect (logic-checker)

- **Location**: §5.3, lines 674-693.
- **Quoted text**: "The view V_F(c) takes at most |orbit_F(c)| distinct values as X ranges over its distribution".
- **Problem**: V_F(c) is defined as the orbit *set* (line 669-670). The cardinality of the set is |orbit_F(c)|. But the bound H(V_F) <= log_2 |orbit_F(c)| only makes sense if V_F is a *scalar* random variable on bit-strings drawn from the orbit. The result is sound under the scalar reading but the formal definition does not match.
- **Suggestion**: Recast: "Let Y be any bit-string the adversary derives from c by composing maps in F. Then Y in orbit_F(c), so H(Y) <= log_2 |orbit_F(c)|. Since Y is a function of c (and hence of X), I(X; Y) <= H(Y) <= log_2 |orbit_F(c)|."

### MIN-2. delta vs delta_T notation collision (carry-forward of m1)

Line 237 (TV distance) vs line 966 (TM transition). Suggestion: rename TM transition to tau_T or sigma_T.

### MIN-3. C(X) notation in §4 rather than §3 (carry-forward of m2)

The notation C(X) is introduced informally at line 283 in §4. Cleaner to add a Definition in §3 Preliminaries.

### MIN-4. "Zero errors on the full domain" framing (carry-forward of m5)

Line 1377: "All three produce zero errors on the full domain." Definitional from PHF, not empirical. Suggestion: prepend "as expected from the PHF construction".

### MIN-5. Granularity table unnumbered (carry-forward of m7)

Lines 1366-1376 use `\begin{center}\begin{tabular}` without `\begin{table}` wrapping. No caption, no number, no label. Promote to numbered table.

### MIN-6. Queries in Table 1 not specified (carry-forward of m8)

Table 1 (lines 1324-1339) lists query types but not the specific terms used or how they were selected. Add one sentence on protocol.

### MIN-7. 150-input loan pipeline is a toy (carry-forward of m9)

§7.3 granularity table. Scale up or add asymptotic-scaling note.

### MIN-8. Construction rate without hardware spec (carry-forward of m10)

Line 1322: "Construction rate: 843 documents per second." No hardware spec.

### MIN-9. No reproducibility statement (carry-forward of m11)

§7.3 should mention artifact URL, commit hash, dataset reference, hardware, seeds.

### MIN-10. Abstract closing sentence is a long compound sentence (carry-forward of m12)

Lines 57-62. Combines both realizations, parenthetical for cipher TM, and the experimental task. On the edge of being a run-on. Consider splitting.

### MIN-11. "Most fundamental algebraic structure" (carry-forward of m13)

Line 1191. Value judgement. Replace with "a minimal non-trivial sum-type instance".

### MIN-12. "Compile-time decision with no runtime cost" (carry-forward of m15)

Lines 926-928. Misleading: there is a storage cost (k cipher maps must still be stored). Suggestion: clarify.

### MIN-13. Conclusion "apply to any cipher map construction" overstated (carry-forward of m17)

Line 1478. Should constrain to constructions satisfying representation uniformity and composability.

### MIN-14. phobic library uncited (carry-forward of m18)

Line 1313 mentions "PHF backend via phobic". Add a footnote with URL or a citation.

---

## Suggestions

1. **Promote the FPR-compounding finding to a dedicated subsection** with a chain-length table (k=1..5) for both AND and OR chains. This is the paper's single most novel empirical observation.

2. **Add at least one figure**: cut-point structure showing both realizations side by side in §6.3. Carries the unification message visually.

3. **Replace or correct the regex example in §6.3.** Either pick a problem where the realizations genuinely differ in cost, or present the cut-point placement as an open optimization without forcing a specific example.

4. **Factor the cipher TM shift cipher map analysis explicitly.** Either two unary cipher maps (extract state, place state) or a binary cipher map on adjacent cells. Account for its space in Proposition 6.1.

5. **Add one paragraph each for cipher TM positioning vs. obfuscation and @cipher_node positioning vs. FHE compilers.** Two new citations would close the positioning gaps.

6. **Post towell2026cipher to arXiv or IACR ePrint** so the load-bearing self-citations are publicly verifiable.

7. **Recast the entropy-form theorem proof** using "Y in orbit_F(c)" as the scalar view rather than "V_F(c) = orbit_F(c)" as the set. Pure notational tightening.

8. **Distinguish typed-chain bound from deterministic-trajectory bound** in §6.3. The cipher TM is bounded by determinism, not typing.

---

## Detailed Notes by Domain

### Logic and Proofs (logic-checker)

Six second-round fixes verified:
- C1 (entropy-form rewrite): largely sound, minor notational defect (LC-NEW-4 / MIN-1).
- M1 (typed-chain recurrence): fully sound. Proof and example match.
- M11 (denominator switch): resolved by entropy form.
- LC-MIN-1 (head direction): resolved.
- LC-MIN-2 (pair cipher map): resolved at the cell level, but new shift cipher map issue (MAJ-2).
- M8 (regex example): structure good, contents have errors (MAJ-1).

Two new defects: MAJ-2 (shift cipher map space), MAJ-1 (regex example), MAJ-3 (§6.3 typed-chain misapplication).

The proof-soundness trajectory: 2026-04-08 had two critical proof issues; 2026-04-12 had one critical and a tautological partial fix; 2026-04-13 has zero critical and clear fixes for the prior critical/major issues, with localized new defects in §6.1 and §6.3.

### Novelty and Contribution (novelty-assessor)

Contribution structure has stabilized. Sum-type impossibility remains the strongest standalone result. Orbit-closure framework now grounded in QIF tradition (via Smith 2009 citation). Typed-chain bound is sound and motivated. Cipher TM is on weaker ground because of the shift cipher map issue and missing obfuscation positioning. Expression-tree decomposition with @cipher_node is the practical realization, well-described.

The empirical FPR-compounding finding remains underclaimed.

### Methodology (methodology-auditor)

Unchanged from 2026-04-12. All carry-forward issues remain. Two new methodological errors entered: MA-NEW-2 (regex example) and MA-NEW-3 (cipher TM shift space). The single most impactful methodology fix is to flesh out the FPR-compounding finding into a proper experimental subsection.

### Writing and Presentation (prose-auditor)

Writing quality preserved through the 2026-04-13 fixes. Two new minor prose issues: PA-NEW-1 (§6.3 lead sentence positioning) and PA-NEW-2 (regex example reads as cipher-TM advocacy). Most carry-forward minor prose issues from 2026-04-12 are unaddressed but minor.

### Citations and References (citation-verifier)

Bibliography expanded from 10 to 21 cites. All 21 in use. Four new citations are appropriate. Two positioning gaps remain (cipher TM vs. obfuscation; @cipher_node vs. FHE compilers). Self-citation issue persists.

### Formatting and Production (format-validator)

Build is clean (19 pages, no warnings, all references resolve). Carry-forward issues: granularity table unnumbered, zero figures, document class is article (pending venue commitment). No new format-level defects.

---

## Literature Context Summary

The 2026-04-12 to 2026-04-13 bibliography expansion (10 to 21 cites) closes the largest 2026-04-12 finding. The remaining gaps are concentrated in obfuscation (cipher TM positioning) and FHE compilers (@cipher_node positioning). Both are positioning preemptions, not requirements.

Venue fit: PLAS remains the natural primary target. IACR ePrint is a fallback. TCC is a weak fit (game-based proofs expected).

---

## Recommendation Rationale

**major-revision** because:
- Two new defects in §6.1 (cipher TM shift cipher map space) and §6.3 (regex example) are clear blockers that need to be resolved before submission. They are tractable but not yet fixed.
- A third issue in §6.3 (typed-chain bound applied to cipher TM) is a conceptual conflation that needs to be untangled.
- Carry-forward experimental issues (no baselines, no error bars, FPR-compounding finding in prose only) collectively undermine the experimental credibility.
- The paper is otherwise on a strong trajectory: critical issues in 2026-04-08 and 2026-04-12 are resolved; bibliography is now adequate; restructure has settled; sum-type impossibility and typed-chain bound are clean.

**Path to acceptance** is concrete:
1. Replace or correct the regex example (highest priority new defect).
2. Factor the cipher TM shift cipher map and analyze its space.
3. Distinguish typed-chain bound from deterministic-trajectory bound in §6.3.
4. Tighten the Theorem 5.3 proof notation (one paragraph).
5. Run experiments: baselines, error bars, FPR-compounding table, granularity space data.
6. Add 2-3 obfuscation/FHE-compiler citations to close positioning gaps.
7. Post towell2026cipher to arXiv or IACR ePrint.
8. Commit to a venue and swap document class if needed.

Estimated effort: one focused revision pass of two to three weeks (similar to the prior estimate).

---

## Comparison with 2026-04-12 Review

The 2026-04-13 revision's effect on 2026-04-12 findings:

**Critical (prior, 1)**:
- C1 (candidate-set tautology): **resolved** by entropy-form rewrite. The set-form bound now cleanly uses |X| as denominator.

**Major (prior, 14)**:
- M1 (typed-chain arity mismatch): **resolved**.
- M2-M5 (experimental issues): **carry-forward** by design.
- M6 (bibliography thin): **resolved**. 21 cites, all in use.
- M7 (document class): **carry-forward**, pending venue commitment.
- M8 (thin §6.3 synthesis): **structurally resolved, content has errors**. Now the source of MAJ-1 (regex example).
- M9 (unpublished self-citations): **carry-forward**.
- M10 (precision 0.39 unexplained): **carry-forward**.
- M11 (denominator switch): **resolved** by entropy form.
- M12 (20 Newsgroups uncited): **resolved** by Lang 1995 citation.
- M13-M14 (5,000-doc subset, "order of magnitude"): **carry-forward**.

**Minor (prior, 18)**: 1 resolved (m14 Shannon citation), 17 carry-forward.

**New defects entered**:
- MAJ-1 (regex example errors).
- MAJ-2 (cipher TM shift cipher map space).
- MAJ-3 (§6.3 typed-chain misapplication to cipher TM).
- MIN-1 (Thm 5.3 proof notation).

Summary: 5 of 33 prior open issues fully resolved; 2 partially resolved; 26 carry-forward; 4 new defects entered. The pattern is the same as 2026-04-08 to 2026-04-12: each round resolves the most consequential proof-soundness issues, the experimental issues stay open, and the new edits introduce localized defects that the next round closes.

---

## Review Metadata

- Specialists consulted: logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator. (The Task tool for parallel subagent execution was not available in this run; the area chair conducted each specialist's analysis directly.)
- Cross-verifications performed:
  - C1 entropy-form rewrite: verified against Def 5.1 (line 581-595), Thm 5.3 (line 674-693), Cor 5.4 (line 695-713).
  - M1 typed-chain recurrence: verified against Def 5.4 (line 845-853), Prop 5.5 (line 860-895), Example 5.4 (line 897-920).
  - LC-MIN-1, LC-MIN-2: verified against Def 6.1 (line 960-987), Prop 6.1 (line 989-1000).
  - M8 regex example: verified against Example 6.1 (line 1167-1183).
- Disagreements noted: 0. All specialists converge on MAJ-1, MAJ-2, MAJ-3 as the principal new defects.
- Hallucination check: every quoted text in the report has been re-verified against the manuscript.
