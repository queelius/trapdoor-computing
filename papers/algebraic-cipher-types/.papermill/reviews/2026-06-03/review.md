# Coherence Review (post-surgery)

**Date**: 2026-06-03
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Scope**: Targeted coherence pass after the 2026-06-03 removal of section 6 "Realizing Cipher Programs" (365 lines: expression-tree decomposition, propagation rule, the tikz figure, branching analysis, cut-point structure) to companion paper `towell2026cipherprog`, plus the new section 6.4 "Partial Filtering". Not a full editorial round; prior-round findings (proofs of Thm 4.2, Thm 5.3, Prop 5.5) are out of scope.

**Recommendation**: **minor-revision**

The surgery is clean. The slimmed paper reads as a complete, self-contained arc; the algebra (sections 4 and 5) plus a concrete instantiation (section 6) fully justifies the title, and the empirical contribution is proportionate. I found **no critical issues, no dangling prose forward-references to the deleted section 6 realization, and no orphan cross-references** (confirmed mechanically and by reading). The new section 6.4 is analytically sound and well-integrated. Three minor issues are worth tightening before submission; only one (M1) is a genuine technical gap in the new subsection, and it is a one-sentence fix.

If the author prefers, M1 through M3 are all addressable in a single short editing pass and none blocks the "content-complete" status the paper already held.

---

## Verdict on the six review questions

| # | Question | Verdict |
|---|----------|---------|
| 1 | Does the arc still close? (5 to 6 bridge; abstract/intro/conclusion vs body) | **Yes.** Clean. |
| 2 | Dangling prose forward-references to deleted section 6 | **None found.** Clean. |
| 3 | Is section 6.4 Partial Filtering sound and well-integrated? | **Mostly yes**, one technical gap (M1) plus one integration nit (m2). |
| 4 | Does the section 3 construction-cite leave section 6 constructions unsupported? | **No.** Holds up. |
| 5 | Does `rem:oblivious-elim` still read coherently; does the section 7 companion item land? | **Yes.** Both clean. |
| 6 | Anything now over- or under-claimed? Does the title still hold? | **Title holds.** One small over-reach (m3, abstract "the same machinery"). |

---

## Summary

**Overall Assessment**: The scope-narrowing achieved exactly what it set out to do. Removing whole-program realization left the cipher-TYPES story intact and, if anything, more focused: section 4 (algebra), section 5 (orbit closure plus typed chains), section 6 (cipher Boolean instantiation plus evaluation plus partial filtering). The intro contribution list, abstract, and conclusion were all updated consistently with the body. The one new piece of content (section 6.4) is a genuine and welcome addition that ties the orbit bound to an operational privacy lever, but it has one unstated assumption that should be made explicit.

**Strengths**:
1. The section 5 to section 6 transition needs no bridge to the deleted material: section 5 ends on "the type system controls the orbit" (a construction-time discipline), and section 6 opens by specializing the *sum-type* trade-off to Bool. The link is to the section 4 and 5 type theory, not to the excised realization machinery. (coherence)
2. Abstract, intro contribution #3 ("Instantiation and evaluation"), and the conclusion all describe exactly what the body now delivers: cipher Booleans, 20 Newsgroups search, the AND-chain FPR divergence, and partial filtering. No residue of "expression-tree / @cipher_node / cut-point" framing survives in any of the three. (coherence)
3. `rem:oblivious-elim` (section 4) was *de-coupled* from section 6 correctly: it now points only to `rem:trusted-matching` (section 4) and `ex:branching-orbit` (section 5), both of which still exist. It reads as a self-contained type-level remark. (logic)
4. Section 6.4 is honestly analytical. It makes no fabricated empirical claims, explicitly defers padding ("a separate mechanism we do not pursue here"), and ties precision approximately 1/m back to the *measured* precision axis of Table 1 rather than inventing new numbers. (methodology)
5. The section 7 Discussion open-question #4 ("Realizing whole programs") and the conclusion's companion-pointer paragraph both land cleanly and now carry the cut-point / control-flow / propagation vocabulary that was removed from the body. The deleted ideas are correctly *forwarded*, not orphaned. (coherence)

**Weaknesses**:
1. (Minor, M1) Section 6.4's "one bit per bag" / fire-vs-idle observability is asserted but rests on an unstated premise: the gate's cipher *output* must be decodable by the trusted machine to know which bag to fetch from, yet the *untrusted* machine is said to "learn which bags fire." The mechanism by which the untrusted machine acts on a fire/idle that is itself a cipher value is left implicit, and the noise region (Prop `prop:noise-unreliability`) is ignored in the precision/recall claim.
2. (Minor, m2) Section 6.4 says partial filtering uses "Hand composition" and is built "exactly as the cipher Boolean operations of section 6"; but the OR-chain it relies on is precisely the construction whose FPR *diverges* by 12,160x at k=5 (Table 2). The recall-preservation claim ("every relevant document's bag fires") is correct, but the interaction with the AND/OR noise floor deserves one sentence so section 6.4 does not read as ignoring section 6.3's headline finding.
3. (Minor, m3) The abstract says the cipher Boolean machinery supports partial filtering with "the same machinery"; strictly, partial filtering adds a *new* gate cipher map and a bag partition on top of the Boolean search. Minor over-compression, easily reworded.

**Finding Counts**: Critical: 0 | Major: 0 | Minor: 3 | Suggestions: 2

---

## Minor Issues

### M1. Section 6.4: fire/idle observability and the noise region are under-specified (source: logic-checker / methodology-auditor)

- **Location**: Section 6.4 Partial Filtering, lines 1463 to 1495 (the `gate` definition and the two paragraphs after it).
- **Quoted text**:
  > "Construct a single \emph{gate} cipher map $\widehat{\mathrm{gate}} : \cipher{\mathrm{Bool}}^{\,m} \to \cipher{\{\text{fire}, \text{idle}\}}$ ... When the gate fires, the untrusted machine returns the bag's $m$ handles ... The untrusted machine therefore learns only \emph{which bags} contain a match, one bit per bag ... the adversary's per-bag observation ranges over a two-element set (fired or idle), so it gains at most one bit per bag ..."
- **Problem**: Two coupled gaps.
  1. **Observability mechanism.** The gate's codomain is written as a *cipher* type `C({fire, idle})`, i.e., an opaque bit string the untrusted machine cannot decode (by Def `def:machines`, U "cannot decode"). But the very next sentence has the untrusted machine *act* on the outcome ("when the gate fires, the untrusted machine returns the bag's m handles") and the paragraph concludes the untrusted machine "learns ... one bit per bag." There is a real design choice hidden here that the paper does not state. Either (a) the gate output is *cleartext* fire/idle (a 1-bit plaintext signal the untrusted machine branches on, which is fine, and is exactly the "tag in the clear" component-wise reading, but then the codomain should not be written as the cipher type `C({...})`), or (b) the gate output stays ciphered and the *trusted* machine pulls fired bags (in which case the untrusted machine does NOT learn which bags fire, and the "one bit per bag" leakage statement is describing the trusted-side view, not the adversary's). As written, the paper wants both readings at once. The orbit-bound argument ("ranges over a two-element set ... at most one bit") is correct *only* under reading (a); under (b) the per-bag leakage to the adversary is approximately 0, which is a stronger and arguably more interesting claim.
  2. **Noise region.** The gate is "an m-ary cipher OR ... realized ... exactly as the cipher Boolean operations of section 6." By Prop `prop:noise-unreliability`, if any `b_i` is in the noise region N the OR output is noise, landing fire/idle by the allocation ratios independent of the true disjunction. So "every relevant document's bag fires" (line 1495) is true only up to the same noise-driven recall loss that section 6.3 reports for OR chains (recall 0.959, not 1.000, in Table 1). The recall-preservation claim should be qualified the same way the OR row of Table 1 is.
- **Suggestion**: One or two sentences. (i) State which reading is intended. The natural and strongest choice is operational: the *fire/idle decision* is cleartext on the untrusted side (so it can fetch), but it is a coarse bag-level bit by construction. Then either write the codomain as plaintext `{fire, idle}` or add a clause "the fire/idle verdict is exposed in the clear (a deliberate component-wise tag), unlike the per-document verdicts which remain ciphered." That makes the "one bit per bag" leakage statement and the orbit bound exact. (ii) Add: "as with the OR queries of section 6.3, a noise value at any bag member can flip the gate, so recall is preserved only up to the cipher-OR noise floor (Table 1)." This also resolves m2.
- **Cross-verified**: Yes. I checked the gate codomain (`C({fire,idle})`, line 1466) against Def `def:machines` (U cannot decode, line 286) and against Prop `prop:noise-unreliability` (lines 1218 to 1241). The tension is real, not a misreading. This is a *clarity/precision* gap, not a soundness error: under the intended-and-natural reading the construction works and the bounds are correct; the paper just under-specifies which reading it means.

### m2. Section 6.4 should acknowledge section 6.3's AND/OR noise floor (source: methodology-auditor)

- **Location**: Section 6.4, lines 1474 to 1476 and 1491 to 1495.
- **Quoted text**:
  > "realized over the input domain $(T\cup F)^m$ exactly as the cipher Boolean operations of \Cref{sec:cipher-bool} (an $m$-ary cipher OR; or a chain of binary ORs ...)" ... "recall is preserved (every relevant document's bag fires)."
- **Problem**: The gate is built from the same cipher-OR machinery whose empirical behavior section 6.3 just characterized (OR chains track theory, but recall in Table 1 for OR is 0.959, not perfect, because of noise). Reading section 6.4 right after section 6.3, the unqualified "recall is preserved" reads as if section 6.3's noise caveat does not apply, which is slightly inconsistent. (The OR side is the *good* case for FPR, ratios 0.90 to 1.02, so the analytic story is fine; this is only about the recall floor.)
- **Suggestion**: Folded into M1(ii). A single clause tying recall preservation to the OR noise floor of Table 1 makes section 6.4 sit flush against section 6.3 instead of reading as bolted on. (Note: the integration is otherwise good; section 6.4 explicitly reuses `tab:boolean-search`'s precision axis at line 1496, which is the right hook.)
- **Cross-verified**: Yes. Table 1 OR recall = 0.959 plus/minus 0.010 (line 1325), section 6.4 claims recall preserved (line 1495). Both true under their own framing (analytic ideal vs measured); one sentence reconciles them.

### m3. Abstract slightly over-compresses "the same machinery" (source: prose-auditor / novelty-assessor)

- **Location**: Abstract, lines 62 to 66; mirrored in intro contribution #3, lines 137 to 140.
- **Quoted text** (abstract):
  > "We instantiate the algebra in a cipher Boolean type and evaluate it on a 20~Newsgroups Boolean search task, and show how the same machinery supports partial filtering, returning a superset of the relevant documents while hiding which are actually relevant ..."
- **Problem**: Partial filtering is not literally "the same machinery"; it adds a new `gate` cipher map and a bag partition. The intro is more careful ("The same construction supports..."), but even there it elides that a gate plus bagging is layered on top. This is minor over-claim by compression, not a false statement (the gate *is* built from the same cipher-OR primitive).
- **Suggestion**: "...and show how the same cipher-Boolean primitives compose into a *bag-gated* filter that returns a superset...". One word ("bag-gated") signals the added structure and removes the over-compression.
- **Cross-verified**: Yes. Not load-bearing; purely a framing nicety.

---

## Suggestions (optional)

1. **Bibliography and preamble hygiene (carry-over of M6).** `fredman1984storing` is defined in `references.bib` but never `\cite`d in `main.tex` (the PHF backing it supports is mentioned in prose at line 1281 and in the section 6.1 noise allocation, but the citation was apparently dropped in an earlier edit). Either cite it where PHF construction is invoked (e.g., line 1234 "backed by a PHF" or line 1281) or remove the entry. This is the only bib defect; the other 21 entries are all cited. Separately, `\usepackage{tikz}` and `\usetikzlibrary{fit}` (preamble lines 7 to 8) are now **unused** because the only figure (`fig:cipher-tree`) was deleted with section 6; they can be removed for cleanliness. Both items are mechanical, not surgery-coherence defects.

2. **One forward-pointer for section 6.4 to companion.** Section 6.4's "Bags may be padded with decoy handles ... a separate mechanism we do not pursue here" (line 1500) is a natural hook to the companion paper if padding/whole-program assembly lives there; a one-clause `\cite{towell2026cipherprog}` pointer would tie the deferred mechanism to where it gets treated, consistent with how section 7 open-question #4 and the conclusion already forward the realization story. Optional.

---

## Detailed Notes by Domain

### Coherence / Arc closure (the core question)

**Section 5 to section 6 bridge: intact.** Section 5 (`sec:typed-chains`) closes on a *type-system* principle: "the type system controls the orbit ... a compile-time decision with no runtime cost" (lines 1158 to 1164). Section 6 opens (lines 1172 to 1174): "The cipher Boolean type ... specializes the sum-type trade-off to the most fundamental algebraic structure and provides the concrete instantiation we evaluate." The bridge is section 4 (sum types) plus section 5 (orbit/typed chains) to section 6 (Bool as the canonical sum). No reference to expression trees, cut points, or realization is needed or present. The deleted section 6 realization was *never* the bridge between orbit-closure and cipher Booleans; it was a parallel third leg. Removing it left the section 5 to section 6 seam untouched.

**Abstract vs body: consistent.** Abstract claims (algebra of constructors; products leak correlations; sums force impossibility; cipher exponential = cipher map abstraction; uniform `H(X|view) >= H(X) - log2|orbit|`; typed-composition budget; cipher Boolean instantiation; 20 Newsgroups; partial filtering trading precision for confidentiality). Every one is delivered in the body (sections 4.2, 4.3, 4.4 Prop `prop:exponential-identity`, 5.3 Thm `thm:confidentiality-bound`, 5.4 Prop `prop:typed-orbit`, 6.1 to 6.3, 6.4). No abstract claim is now unsupported by the slimmed body.

**Intro contribution list vs body: consistent.** Contribution #3 was changed to "Instantiation and evaluation (section 6)" and now reads (lines 131 to 140): cipher Boolean with AND/OR/NOT plus 20 Newsgroups plus FPR compounding (OR tracks, AND diverges) plus partial filtering. This is exactly sections 6.1 to 6.4. Contributions #1 (algebra) and #2 (uniform bound plus typed chains) are unchanged and still correctly cite into sections 4 and 5. The intro's "This is not ORAM/FHE/garbled circuits" framing (lines 143 to 150) is unaffected.

**Conclusion vs body: consistent.** The conclusion (lines 1594 to 1636) summarizes only what remains: the algebra, the uniform bound, the typed-composition budget, then the practical side (cipher Boolean search, AND-chain FPR divergence, granularity spectrum). The realization paragraph was correctly reframed (lines 1608 to 1615) to "these results are about cipher *types* ... assembling many cipher maps into a general program ... is a distinct problem ... companion paper." No conclusion sentence claims a realization/compiler contribution.

**Dangling forward-references: none.** Grep for the danger vocabulary (`expression tree`, `cut point`, `@cipher_node`, `propagat*`, `short circuit`, `cipher TM`, `control flow`, `whole program`, `automatic tracing/rewriting`, `we realize`, `as we show in Section 6`) returns hits ONLY at: (i) section 7 open-question #4 (lines 1581 to 1586) and (ii) the conclusion companion paragraph (lines 1611 to 1615), both of which *correctly* forward this vocabulary to the companion paper, and (iii) benign uses of "realized/realization" in section 4.4 Prop `prop:exponential-tradeoff` (line 692) and section 6.4 (line 1474) meaning "implemented as a cipher map," which is the standard usage throughout and predates the surgery. No prose presupposes a realization section still exists in *this* paper.

**Cross-references: all resolve.** Every `\Cref`/`\ref` target has a matching `\label` (verified by set difference). The "unreferenced labels" set is benign (section/example/remark labels that simply are not cited, which is normal). Build clean at 20pp, 0 undefined, 0 overfull (confirmed from `main.log`).

### Logic and Proofs

**`rem:oblivious-elim` (section 4, lines 595 to 624): coherent post-surgery.** This remark *used* to set up the section 6 realization (it was the type-level companion to the program-level "no oblivious short-circuit" prop that moved to the companion). After surgery it points only to `rem:trusted-matching` (line 608, section 4, present) and `ex:branching-orbit` (line 619, section 5, present). It reads as a self-contained statement about cipher-sum elimination: fused eliminator `h-hat` over the joint encoding, or evaluate-both-branches plus cipher-mux. Neither dependency is dangling. The remark no longer promises a program-level consequence; it is purely about the type-level eliminator. Coherent.

**Thm `thm:sum-impossibility`'s reach (check 5): correctly scoped.** The theorem statement (lines 472 to 488) and proof (490 to 568) are self-contained at the type level (dispatch vs. tag-hiding). The program-level "no oblivious short-circuit" consequence is gone from the body and correctly forwarded to the companion (section 7 #4, conclusion). The proof's inline note (lines 521 to 524), "the result ... can be produced as a cipher value with the tag hidden (by a fused eliminator, or by evaluating both branches), but neither route forms s," references `rem:oblivious-elim`, which is intact. No part of the impossibility proof depends on deleted section 6 material. (The proof itself was hardened 2026-05-04 and is out of scope; I confirm the surgery did not touch it.)

**Section 6.4 orbit-bound claim (check 3b): correct, modulo M1.** The claim "ranges over a two-element set (fired or idle), so ... at most one bit per bag" is a correct instantiation of Thm `thm:confidentiality-bound` (orbit <= 2 implies leakage <= log2 2 = 1 bit) **provided** the fire/idle verdict is what the adversary observes (reading (a) in M1). The arithmetic is right. The only issue is which view the bit accrues to (M1.1).

**Section 6.4 precision approximately 1/m (check 3c): correct.** "If the |R| relevant documents fall in distinct bags, partial filtering returns up to m|R| documents of which |R| are relevant, so precision falls to approximately 1/m." The arithmetic is right (|R| relevant / m|R| returned = 1/m), and "up to" correctly handles the case where relevant docs share a bag (fewer bags fire, precision higher). Recall preservation is correct in the noiseless ideal; needs the noise caveat (M1.2/m2).

### Methodology

**Section 3 construction-cite (check 4): holds up.** Section 3 (lines 305 to 313) cites the batch/PHF construction from `towell2026cipher` section 6 and explicitly scopes out whole-program assembly to the companion. The section 6 cipher-Boolean and partial-filtering constructions read as "applying the cited construction to specific functions," exactly the fine line the brief asked me to check. Section 6.1 Def `def:cipher-bool` builds the cipher Boolean as a partition of B^n (the cited construction specialized to Y = {True, False}); section 6.4's gate is "an m-ary cipher OR ... realized exactly as the cipher Boolean operations of section 6." Neither owes the reader a construction the paper deleted. The granularity experiment (section 6.3, `tab:granularity`) was correctly reworded to drop annotation/tracing language and is tied to Prop `prop:product-tradeoff` (line 1442), not to any realization machinery.

**Section 6.4 makes no fabricated empirical claims (check 3e): confirmed.** Section 6.4 is purely analytical. Its only numeric hooks are the *already-measured* precision axis of Table 1 (line 1496) and the structural 1/m precision relation (analytic). No new table, no new measured quantity, no implied experiment. The padding mechanism is explicitly deferred ("we do not pursue here", line 1501). This is exactly the honesty the brief required.

**Empirical contribution proportionate to claims (check 6): yes.** The empirical surface is now Boolean search (Table 1), FPR compounding (Table 2), granularity (Table 3), and analytic partial filtering (section 6.4). This matches contribution #3 ("Instantiation and evaluation") and is appropriately modest: the paper does not claim a deployed system or a security proof, only that the algebra instantiates and that the AND-chain divergence is a real, quantified, surprising phenomenon. Proportionate.

### Writing and Presentation

**Title still justified (check 6): yes.** "Algebraic Cipher Types" is carried entirely by section 4 (the constructor algebra: void/unit/product/sum/exponential with Table `tab:algebra-summary`) and section 5 (the uniform bound plus typed-composition that make it a *calculus*). The realization was never what justified the title; its removal is invisible to the title's promise. Section 6 is the instantiation that the title's "types" implies one would want to see.

**Two argument modes preserved.** Per the paper's own convention (CLAUDE.md): sections 3 to 5 are theory, section 6 is concrete instantiation/evaluation. The surgery removed the former section 6 "realization" middle mode entirely, leaving a cleaner two-mode structure (theory to instantiation). Section 6.4 stays in the instantiation mode (it is a construction over the cipher Boolean, with analytic privacy/precision), so it does not violate the mode separation.

### Citations and References

- 21 of 22 bib entries cited; `fredman1984storing` is defined but uncited (Suggestion 1). Not a surgery artifact.
- `towell2026cipherprog` (the companion) is correctly added and cited twice (section 7 #4 line 1586, conclusion line 1615). Its bib entry (references.bib lines 15 to 20) is present with a descriptive title matching the deleted content ("Cut-Point Decomposition and Control-Flow Obliviousness"). Good.
- The `towell2026cipher` bib note (references.bib line 5) flags that cross-reference numbers follow the 2026-05 revision and may shift, appropriate given the unposted foundation; not in scope to re-verify (done in the 2026-05-04 cross-paper round).

### Formatting and Production

- Build clean: 20 pages, 0 warnings, 0 undefined references, 0 overfull/underfull boxes (from `main.log`).
- M7 (article doc class, venue-gated) and M9 (three unposted @misc self-cites, now four with the companion) remain open external blockers, unchanged by the surgery and explicitly out of scope.
- The `\usepackage{tikz}` plus `\usetikzlibrary{fit}` (lines 7 to 8) are now **unused** because the only figure (`fig:cipher-tree`) was deleted with section 6. Harmless, but they can be removed for cleanliness (folded into Suggestion 1). Not a defect.

---

## Literature Context Summary

No new literature grounding was performed for this targeted pass (the related-work positioning against ORAM/FHE/garbled circuits, SSE leakage attacks, IFC, FE, and QIF was settled in prior rounds and is unaffected by the surgery). The Related Work section (section 2) makes no reference to the deleted realization material, so it required no reconciliation.

---

## Review Metadata

- Mode: focused coherence pass (area-chair direct review; specialist lenses applied inline, prose/arc, logic/soundness, methodology/empirics, rather than as separate agent threads, appropriate for a single-surgery scope check).
- Verification performed: full manuscript re-read (lines 1 to 1654); mechanical label/reference set-difference (all refs resolve); danger-vocabulary grep (no dangling forward-refs); section 6.4 construction traced against Def `def:machines`, Prop `prop:noise-unreliability`, Thm `thm:confidentiality-bound`, and Table 1; bib citation coverage cross-check; build-log inspection.
- Cross-verifications performed: 3 (M1 fire/idle reading vs. machine model; m2 recall vs. Table 1 OR row; abstract/intro/conclusion triangulation against body).
- Disagreements noted: 0.
- Hallucination check: all quoted manuscript text verified against the actual file at the cited line numbers.

### Bottom line

The surgery left the paper coherent. There are no gaps that block submission and nothing that undermines the title or the contribution list. The single substantive item (M1) is a precision gap in the new section 6.4: state which side sees the fire/idle bit, and qualify recall with the OR noise floor, fixable in two sentences. m2 and m3 fold into the same edit or are one-word changes. Recommend **minor-revision**, closable in one short pass.
