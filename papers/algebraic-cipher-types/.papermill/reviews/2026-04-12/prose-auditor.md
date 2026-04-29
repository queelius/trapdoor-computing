# Prose Auditor Report

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp)
**Date**: 2026-04-12
**Scope**: Writing quality, narrative arc, notation consistency, cross-reference hygiene.

## Summary

The restructure substantially improved the narrative. The prior review's M3 (Discussion overload, 40% of paper body) is clearly addressed: Section 8 Discussion is now slim (relationship paragraphs + open questions only), and the experimental/definitional material that bloated it has been promoted into proper sections. Related Work (Section 2) and Conclusion (Section 9) exist. The "one principle, three instances, two realizations" thesis mostly comes through, though Section 6.3 (the synthesis subsection) is thin and earns the framing only in part.

Remaining prose issues are more granular than before: a few sentence-level awkwardnesses, one notation overload that was flagged last time and remains (delta vs delta_T), inconsistent framing in Section 6.1, and some introductory material that could be tightened. No critical prose issues.

The overall prose quality is high: clear, direct, precise, with effective examples. The introduction remains exemplary, and Related Work is short but focused. The paper reads like a serious theoretical contribution with minor rough edges rather than a first draft.

---

## Major Issues

### PR-MAJ-1. Section 6.3 "earns" the cut-point synthesis only in part

**Location**: Section 6.3, lines 1045 to 1064.

**Problem**: Section 6.3 (the synthesis between cipher TM and expression-tree decomposition) is the pivotal subsection for the "one principle, two realizations" framing. It is currently about 15 lines and contains:
- A claim that both realizations share a cut-point pattern (1 sentence).
- A contrast between their leakage profiles (1 sentence).
- A claim that the typed-chain bound applies to both (1 sentence).

The text is compressed, and the unification is more asserted than demonstrated. A reviewer will ask: what exactly is the "cut point"? Is it a formal construct or a metaphor? The text leans toward metaphor.

**Suggestion**: Strengthen Section 6.3 to at least 30 lines with:
(a) A formal definition of "cut point" as a node in a computation graph where a subtree is replaced by a cipher map, accompanied by a small figure or diagram (the paper currently has zero figures).
(b) A worked example showing the same computation realized both ways (e.g., regular-expression matching: as a cipher TM iterating a transition cipher map; as an expression tree of per-character cipher maps).
(c) An explicit statement of the orbit bound applied to each realization: "For cipher TM, the orbit is bounded by 1 + T(|x|) where T is the plaintext TM runtime. For expression trees of depth d, the orbit is bounded by 1 + d."

Even one of (a), (b), (c) would turn the synthesis from metaphor into substance.

### PR-MAJ-2. Notation overload: delta (TV distance) vs. delta_T (transition function)

**Location**: Section 3 (delta as representation uniformity parameter, lines 204 to 206) vs. Section 6.1 (delta_T as TM transition function, lines 911 and following).

**Problem**: This was m2 in the prior review and remains unresolved. Throughout the paper, delta is the representation uniformity parameter (TV distance from uniform). In Section 6.1, delta_T refers to the transition function of a Turing machine. The notation is locally distinguishable but a hurried reader could conflate them, and the collision is gratuitous.

**Suggestion**: Rename the transition function. Standard alternatives:
- tau_T (transition)
- sigma_T (state transition)
- trans_T

This is a three-character find-and-replace. The fix is trivial and has no downside.

### PR-MAJ-3. Introduction of C(X) notation is still not a formal definition (carry-forward of M7)

**Location**: Section 4 (first use, line 252): "We write C(X) for the type of cipher values encoding elements of X."

**Problem**: This was M7 in the prior review. C(X) is the paper's central notation. It appears embedded in prose rather than as a numbered Definition. A PLAS reviewer or a reader skimming definitions will miss it. The fix is small and was explicitly suggested in the prior review.

**Suggestion**: Add Definition 3.3 to Section 3 (Preliminaries):
> **Definition 3.3** (Cipher type). Let X be a finite type. The cipher type C(X) is the set of valid cipher values for X:
>   C(X) := { enc(x, k) : x in X, 0 <= k < K(x) } subset of B^n.
> In general, |C(X)| <= 2^n, with equality in the limit of representation uniformity delta = 0.

This places the notation where it belongs (before its first use), gives it a label for reference, and formalizes the "valid cipher value" notion that appears implicitly throughout.

---

## Minor Issues

### PR-MIN-1. Abstract's closing sentence is a run-on

**Location**: Abstract, lines 57 to 62.

**Quoted text**:
> We then present two realizations of cipher programs, an expression-tree decomposition with cipher-map cut points (the practical path, exposed via a @cipher_node decorator) and a cipher Turing machine (space O(|Q| * |Gamma|), leaks head movement), and evaluate the cipher Boolean algebra specialization on a 20 Newsgroups Boolean search task.

**Problem**: This is a single sentence of 50+ words with nested parentheticals. The "(the practical path, exposed via a @cipher_node decorator)" is a double parenthetical, and the entire sentence has two "and"s that create mild parsing ambiguity.

**Suggestion**: Split into two sentences:
> "We realize cipher programs two ways: expression-tree decomposition with cipher-map cut points (the practical path, via a @cipher_node decorator), and a cipher Turing machine (space O(|Q| * |Gamma|), with head-movement leakage). We evaluate the cipher Boolean algebra specialization on a 20 Newsgroups Boolean search task."

### PR-MIN-2. "the most fundamental algebraic structure" is a value judgement

**Location**: Section 7, first line, line 1072: "The cipher Boolean type C(Bool) specializes the sum-type trade-off to the most fundamental algebraic structure."

**Problem**: "Most fundamental" is a subjective claim. Booleans are convenient and widely applicable, but "most fundamental" depends on one's foundational lens. A PL audience might say sums and products are more fundamental; a crypto audience might say finite fields are.

**Suggestion**: "The cipher Boolean type C(Bool) is a minimal non-trivial sum-type instance and provides the concrete instantiation we evaluate on a real corpus."

### PR-MIN-3. "Shannon-optimal allocation" cited in-line without unpacking

**Location**: Section 7.1, Remark 7.1 (line 1101): "|R_y|/2^n proportional to Pr[Y = y] (Shannon-optimal allocation)."

**Problem**: "Shannon-optimal" is unexplained. The reader is expected to know that this matches a source-coding argument. A one-line gloss would help non-information-theorist readers.

**Suggestion**: "|R_y|/2^n proportional to Pr[Y = y] (Shannon-optimal: regions sized in proportion to value probability, matching the information content of decoding)."

### PR-MIN-4. "The encoding granularity principle" paragraph reads like a bullet list

**Location**: Section 8, "The encoding granularity principle" paragraph (lines 1290 to 1299).

**Quoted text**:
> The product and sum trade-offs in Sections 4.2 and 4.3 are instances of a single principle developed in [9, Sec. 9]: coarser encoding granularity (encoding more values as a single unit) yields better confidentiality but fewer operations available to the untrusted machine. The entanglement parameter p [9, Sec. 9.3] controls the spectrum: p = 1 (component-wise) gives maximum functionality and minimum confidentiality; p = k (whole-state) gives maximum confidentiality and minimum functionality.

**Problem**: The paragraph is information-dense but flat. The first sentence states the principle; the second describes the parameter; no synthesis. A reader comes away with a reference to an external paper rather than a settled understanding.

**Suggestion**: Either (a) add a half-sentence synthesis at the end: "...This paper's sum-type impossibility and product trade-off correspond to endpoints of this spectrum: the impossibility is the p = k limit for sums, the correlation leakage is the p = 1 limit for products." Or (b) cut this paragraph and integrate its content into Section 4.4 (where exponential types already gesture at the same principle).

### PR-MIN-5. "Compile-time (construction-time) decision with no runtime cost" is slightly misleading

**Location**: Section 5.5, lines 872 to 874: "This is a compile-time (construction-time) decision with no runtime cost: the untrusted machine simply does not have cipher maps for deeper levels."

**Problem**: "No runtime cost" is true only in a narrow sense. The runtime cost of typed chains is actually *incurred* at construction time: the trusted machine must build k distinct cipher maps (one per level). And the untrusted machine must hold all k maps. The total space grows linearly with k. Saying "no runtime cost" obscures the cost that is really there.

**Suggestion**: "This is a construction-time decision. The runtime cost for the untrusted machine is the additional space required to hold k distinct cipher maps, linear in chain depth; runtime evaluation cost per query is unchanged."

### PR-MIN-6. "the typed-chain bound constrains identically" is slightly awkward

**Location**: Section 6.3, last sentence, lines 1062 to 1064: "The typed-chain bound of Proposition 5.4 applies to both: typing the cipher spaces between cut points limits the adversary's orbit depth regardless of the realization."

**Problem**: "Constrains identically" appears in the Conclusion (line 1367): "Both are instances of a single cut-point pattern that the typed-chain bound constrains identically." This phrasing is ambiguous: are the bounds numerically identical, or is the mechanism the same? Given the LC-MAJ-1 issue (typed-chain bound may not apply cleanly to arity > 1 operations), a claim of "identical" constraint is premature.

**Suggestion**: Replace "constrains identically" with something more guarded: "the typed-chain bound of Proposition 5.4 applies to both, with chain depth playing the role of TM steps in one case and expression-tree depth in the other."

### PR-MIN-7. Remark 5.3 (active probing) duplicates Section 5.4 Example 5.1

**Location**: Section 5.4 Example 5.1 (lines 705 to 733) vs. Section 5.4 Remark 5.3 (lines 785 to 798).

**Problem**: Example 5.1 (Boolean operations) walks through AND/NOT probing. Remark 5.3 (Active probing) then gives an abstract version of the same idea: "Given cipher AND and a cipher value c, the adversary computes AND(c, c), AND(c, c') for other values c', and checks structural consistency." The content substantially overlaps; the reader gets the same story twice.

**Suggestion**: Either (a) fold Remark 5.3's content into Example 5.1 (so the example makes the abstract point itself), or (b) cut Example 5.1's second paragraph (starting "This comparison reveals information...") and keep Remark 5.3 for the abstract statement. The current arrangement has the example foreshadowing a point the remark then restates.

### PR-MIN-8. Conclusion's "These results apply to any cipher map construction" is absolute

**Location**: Section 9, line 1358: "These results apply to any cipher map construction, not just specific implementations."

**Problem**: This is an overclaim. The orbit-closure bound (Theorem 5.3) assumes representation uniformity delta approximately 0. The sum-type impossibility (Theorem 4.2) assumes non-empty types and explicit priors. Not every cipher map construction satisfies these assumptions uniformly. A more guarded claim would read better.

**Suggestion**: "These results are construction-agnostic: they hold for any cipher map construction that satisfies representation uniformity (delta close to 0) and the composability property of [9]."

### PR-MIN-9. "We have shown" at the start of the conclusion is slightly overreaching

**Location**: Section 9, line 1350: "We have shown that algebraic type constructors create unavoidable confidentiality costs in trapdoor computing."

**Problem**: "Unavoidable" is strong. The paper shows that certain costs are unavoidable *given the framework assumptions* (untrusted pattern matching on cipher values) but one could avoid them by, e.g., doing pattern matching on the trusted side (Remark 4.2) or by accepting game-based rather than information-theoretic security (any FHE scheme). A reader familiar with FHE will push back on "unavoidable."

**Suggestion**: "We have shown that algebraic type constructors impose specific, quantifiable confidentiality costs for cipher values manipulated by an untrusted machine, and that these costs are unavoidable within the trapdoor-computing framework (totality + representation uniformity + information-theoretic parameterization)."

---

## Suggestions

### PR-SUG-1. Add a figure to Section 5 or Section 6.3

The paper has zero figures and is 17 pages long in a theoretical area where figures help. Two natural figures:

1. **Orbit-closure diagram** (Section 5.1 or 5.4): small state-transition graph with cipher values as nodes, cipher maps as labeled edges, starting from c and growing. Would make the orbit concept immediately concrete.

2. **Cut-point diagram** (Section 6.3): expression tree with some nodes marked as cipher nodes (shaded); separate panel showing TM transition function as a single cut point. Would make the "cut-point unification" visually obvious.

Either figure would do work currently carried entirely by prose.

### PR-SUG-2. Section headers read more cleanly as noun phrases

Currently:
- Section 4: "Cipher Type Constructors" (noun, good)
- Section 5: "Orbit Closure and Information Leakage" (noun, good)
- Section 6: "Realizing Cipher Programs" (verb phrase, OK)
- Section 7: "Cipher Boolean Algebra and Evaluation" (noun, good)

"Realizing" is the odd one out. Consider:
- "Cipher Program Realizations"
- "Two Realizations of Cipher Programs"

Minor, but the uniform noun-phrase convention would read slightly better.

### PR-SUG-3. Related Work could cite more recent work

Related Work (Section 2) has three paragraphs citing Sabelfeld-Myers 2003, Boneh-Sahai-Waters 2011, Curtmola et al. 2006, and Naveed et al. 2015. All are 10+ years old; the most recent is 2015. PLAS readers expect engagement with current work (2020 to 2025). Useful additions:
- Grubbs et al. on SSE leakage attacks (post-2015).
- More recent PPE/SSE work (Kellaris et al., Cash et al.).
- Modern FHE compilers (HEIR, EVA, Concrete).
- Language-based security work post-2015 (e.g., Viaene et al., Hritcu et al., WebAssembly security).

This also helps the M2 thin-bibliography problem.

### PR-SUG-4. State the thesis in one sentence at the top of the Introduction

The thesis (from state.md, refined 2026-04-12) is: "Every algebraic operation the untrusted machine can perform on cipher values enlarges their orbit closure and reduces confidentiality; typing the cipher spaces converts this into a design-time budget."

The Introduction currently develops this over three paragraphs (lines 71 to 94). Consider adding a one-sentence summary statement at the end of the first or second paragraph, along the lines of: "In this paper we show that each algebraic operation the untrusted machine can perform enlarges the orbit of a cipher value and, by an information-theoretic bound, reduces its confidentiality; a typed-composition discipline converts this cost into a design-time budget."

This pre-positions the reader and matches the thesis formally stated in state.md.

---

## Cross-cutting Observations

- **Restructure effect on prose quality**: Substantially positive. The Discussion is no longer a dumping ground; sections have a clear job. Related Work and Conclusion exist. The overall narrative is improved.
- **Writing quality**: High. Sentences are direct, precise, and appropriately rigorous. Examples are well chosen. The most common issue is mild over-claiming in summary sentences (PR-MIN-8, PR-MIN-9) rather than fundamental clarity problems.
- **Notation**: Mostly consistent. One remaining overload (PR-MAJ-2). One missing formal definition (PR-MAJ-3).
- **Figures**: Zero. At 17 pages of theoretical writing, two figures would materially help.
- **Prior-review status**:
  - M3 (Discussion overload), **fixed** by restructure.
  - M7 (C(X) informal), **not addressed** (PR-MAJ-3).
  - M10 (no Related Work), **fixed** by restructure.
  - M12 (no Conclusion), **fixed** by restructure.
  - m2 (delta vs delta_T overload), **not addressed** (PR-MAJ-2).
  - m9 (cipher value vs cipher map conflation), **no regression**: the paper still has the "we use interchangeably" remark at line 226 to 228, which is acceptable but could be a proper definition (PR-MAJ-3 would subsume this).
  - m11 (functorial metadata), see NV-MIN-3.
