# Prose Auditor (2026-04-13)

## Scope

Third-round prose audit. Two rounds of major edits in one week. Focus on whether transitions still work after restructure and second-round fixes, whether abstract/intro/conclusion are still consistent with the body, and whether new prose introduced in §5.3, §5.5, §6.1, §6.3 reads cleanly.

## Summary

Writing quality remains high. The 2026-04-12 restructure's narrative arc ("one principle, three instances, two realizations") is preserved through the 2026-04-13 fixes. Abstract and conclusion still match the body. Most carry-forward minor issues from 2026-04-12 are not addressed but they are minor.

The new prose in the second-round fixes is mostly clean. The §6.3 paragraph mapping the typed-chain bound onto cipher TMs has a logical-content problem (flagged by logic-checker LC-NEW-1), but its prose is fine. The new §5.3 entropy-form theorem statement is concise and well-written.

## Confirmed-clean (post-fix)

### Abstract and Introduction

Abstract (lines 37-63): unchanged from 2026-04-12. Closing sentence (lines 57-62) is still a long compound sentence covering both realizations and the experimental task. Acceptable but on the edge of run-on. Carry-forward of m12.

Introduction contributions list (lines 95-124): matches the body.
- Contribution 1 (sum-type impossibility) refers to Thm `thm:sum-impossibility`. Confirmed in §4.3.
- Contribution 2 (orbit closure and confidentiality bound) refers to §5. Confirmed.
- Contribution 3 (cipher program realizations) refers to §6. Confirmed.

Closing paragraph (lines 126-133) preempts ORAM/FHE/garbled circuits. Clean.

### Related Work (§2)

Five paragraphs: IFC, FE, SSE, QIF, related concepts. Each is one paragraph, well-grounded, with the right citations. The QIF paragraph is new in 2026-04-12; it positions the entropy-form bound in the QIF tradition and is appropriate. Clean.

### Conclusion

Conclusion (lines 1469-1502): three paragraphs, matching contributions 1-3 plus an experimental summary. Clean.

## New prose introduced in second-round fixes

### §5.3 Confidentiality Bound (entropy form)

Lines 661-732. Replaces the prior candidate-set detour. The lead-in paragraph (lines 661-666) frames the bound as connecting orbit reachability to information-theoretic confidentiality. The theorem statement is one line; the proof is three lines. Two remarks (lines 715-732) acknowledge looseness and extreme cases.

**Prose-level**: clean. The flow from orbit-closure definition to confidentiality bound is direct.

**Logic-level note**: see logic-checker. The notational confusion between V_F as set vs. scalar is a content issue, not a prose issue.

### §5.5 Typed Composition Chains

Lines 835-928. Definition 5.4 (typed chain), Proposition 5.5 (orbit bound), Example 5.4 (depth-limited Boolean search), and a closing paragraph stating the design principle.

**Prose-level**: well-written. The reader is led from the active-probing risk (Remark 5.4) to the typed-chain mitigation. The two special cases (single-value start, unary chain) are clearly labeled.

**Carry-forward minor**: the closing line "compile-time (construction-time) decision with no runtime cost: the untrusted machine simply does not have cipher maps for deeper levels" still gives the impression that there is no storage cost. The prior review's m15 was about this; it is not addressed.

### §6.1 Cipher Turing Machines

Lines 950-1030. Definition 6.1 rewritten to use joint encoding `C(Q x Gamma)` per cell with cleartext direction.

**Prose-level**: cleaner than the 2026-04-12 version. The phrasing "by swapping the state component of the neighbouring cell with the current cell via a second cipher map for the shift operation" (lines 978-981) is dense. A reader has to parse "second cipher map for the shift operation" without elaboration. This sentence carries a lot of weight without analysis (logic-checker flagged the missing space analysis).

**Suggestion**: split the head-shift mechanism into a paragraph of its own with a brief description of how the shift cipher map works. This would resolve both the prose density and the missing logical analysis.

### §6.3 Cut-Point Structure (revised and expanded)

Lines 1110-1183. Now includes Definition 6.3 (cut point), four paragraphs of mapping/leakage/typed-chain analysis, and Example 6.1 (regex matching).

**Prose-level**: section is more substantive than in 2026-04-12. The paragraph structure (cut-point definition, mapping the realizations, what leaks above, what the typed-chain bound says, regex example) is a reasonable progression.

**Carry-forward issue**: section is now about 75 lines, up from 15 in 2026-04-12. Better balanced.

**Logic-level notes**: the typed-chain mapping paragraph (lines 1151-1165) and the regex example (lines 1167-1183) have content issues flagged by logic-checker. The prose itself is fine; the underlying claims are problematic.

## Carry-forward minor prose issues from 2026-04-12 not addressed

### m1. delta vs delta_T notation collision

Line 237 (delta = TV distance) vs line 966 (delta_T = TM transition). Still present.
**Suggestion**: rename TM transition to tau_T or sigma_T.

### m2. C(X) notation formal definition

The notation `C(X)` is introduced informally at line 283 ("We write C(X) for the type of cipher values encoding elements of X"). This is now in §4 introduction rather than Preliminaries. Acceptable but a Preliminaries definition would be cleaner.

### m4. Pairing operation (cipher TM)

Resolved by joint encoding `C(Q x Gamma)`. Closed.

### m5. "Zero errors on full domain" framing

Line 1377: "All three produce zero errors on the full domain". Still definitional rather than empirical. Suggested fix: prepend "as expected from the PHF construction".

### m7. Granularity table unnumbered

Lines 1366-1376. Still uses `\begin{center}\begin{tabular}` instead of `\begin{table}`. Should be promoted to a numbered table with caption and label.

### m12. Abstract closing sentence run-on

Lines 57-62. Single sentence covers both realizations, parenthetical for cipher TM, and experimental task. On the edge.

### m13. "Most fundamental algebraic structure" value judgement

Line 1191: "specializes the sum-type trade-off to the most fundamental algebraic structure". Still present. Suggested replacement: "to a minimal non-trivial sum-type instance".

### m14. "Shannon-optimal allocation" citation

Line 1221 now cites `shannon1948mathematical`. Closed.

### m15. "Compile-time decision with no runtime cost" misleading

Line 926-928. Still suggests no storage cost; should clarify that k cipher maps are stored.

### m16. Remark 5.3 / Example 5.1 duplication

The 2026-04-12 review noted that Remark 5.3 duplicates Example 5.1. The current §5.4 has Example 5.1 (Boolean operations) and Remark 5.4 (active probing). They cover overlapping content but the framing differs. Acceptable as-is.

### m17. Conclusion's "apply to any cipher map construction" overstated

Line 1478: "These results apply to any cipher map construction, not just specific implementations." Still overstated. Should constrain to constructions satisfying representation uniformity and composability.

## New minor observations

### PA-NEW-1. Section 6.3 paragraph headers

The four paragraphs in §6.3 use `\paragraph{}` for Mapping, What leaks, What the typed-chain bound says. The "Both realizations implement the same abstract move" lead sentence is on its own line before Definition 6.3. The flow is: lead -> definition -> three paragraph-headed analyses -> example. This is unusual. Most papers either lead with a definition or with prose, not both.

**Suggestion**: either fold the lead sentence into the section's intro and lead with Definition 6.3, or expand the lead into a proper introductory paragraph before Definition 6.3.

### PA-NEW-2. Regex example reads as a proof of cipher-TM superiority

Lines 1167-1183. The example concludes "Cipher TM is preferable for long strings; expression-tree decomposition is preferable when ell is small and string length must be hidden." This presents the choice as a clear win for cipher TM in most cases. As logic-checker notes, the example fabricates the exponential cost for the expression tree by choosing a strawman decomposition.

**Suggestion**: revise the example so the trade-off is genuinely balanced, or remove the example and present the cut-point placement question as an open problem.

## Strengths preserved

- Introduction is well-positioned and direct.
- Related Work has the right structure (one paragraph per relevant subfield).
- Theorem and proposition statements are concise.
- The "two realizations" framing is preserved through the fixes.
- Conclusion summarizes accurately and does not oversell.

## Verdict

Prose quality is high. The 2026-04-13 fixes mostly preserved the writing quality. Two new prose issues (PA-NEW-1 §6.3 lead sentence, PA-NEW-2 regex example framing) are minor. The carry-forward minor issues from 2026-04-12 (notation collision, run-on abstract closing, granularity table unnumbered, value judgement, "no runtime cost" wording, conclusion overstatement) are mostly still open.

The biggest prose-level concern is not in the manuscript itself but in §6.3 Example 6.1, where the prose is fine but the underlying claim is wrong. That is logic-checker's domain.
