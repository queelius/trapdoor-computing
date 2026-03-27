# Prose Auditor Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The writing is generally clear, well-organized, and appropriately technical. The paper reads well as a self-contained theory paper. The notation is consistent throughout. The honest limitations sections are unusually candid and strengthen the paper. There are some areas where prose could be tightened or structure improved.

## Findings

### F1. Section ordering puts trust model after constructions (Major, High confidence)
**Location**: Sections 5-6 vs. Section 6 (Trust Model)
**Problem**: The constructions (Section 5: HashSet, entropy map, trapdoor Boolean algebra) reference the trust model implicitly -- they discuss what the "untrusted machine" sees, what the "trusted machine" holds, etc. But the trust model is only formalized in Section 6. A reader encountering "the untrusted machine sees only opaque bit strings" in Section 5 has no formal definition of what "untrusted machine" means until Section 6.
**Suggestion**: Move the trust model (Section 6) to before the constructions (current Section 5), or immediately after the four properties (Section 4). The natural order is: abstraction -> properties -> trust model -> constructions -> singular hash map -> composition. This matches the formalism document's ordering.

### F2. Abstract mentions "three orthogonal construction layers" without payoff (Minor, High confidence)
**Location**: Abstract, lines 49-51
**Quoted text**: "show how they arise from three orthogonal construction layers (undefined injection, noise closure, multiple representations)"
**Problem**: The abstract promises that the paper will "show how" the four properties arise from three construction layers. The paper does describe these layers (Section 3.3), but as "conceptual scaffolding" that is explicitly not formalized. The abstract creates an expectation of a formal layer decomposition that the paper does not deliver. "Three orthogonal construction layers" sounds like a formal algebraic contribution.
**Suggestion**: Soften the abstract: "motivate them through three conceptual construction layers" or "trace their origin to three independent design choices."

### F3. "Bernoulli error model" paragraph in introduction assumes familiarity (Minor, Medium confidence)
**Location**: Section 1, lines 91-99
**Quoted text**: "Two axioms (element-wise independence and conditional independence of block error rates) reduce the error model from exponential complexity to two parameters per element."
**Problem**: This paragraph introduces the Bernoulli model with technical detail (two axioms, exponential complexity reduction) that a reader unfamiliar with the companion paper cannot evaluate. The paragraph cites [bernoulli-types] which is an unpublished working paper. A reader cannot verify these claims.
**Suggestion**: Either (a) reduce to a single sentence ("The Bernoulli model provides the error accounting framework; see [bernoulli-types] for details") or (b) include a brief self-contained description of the two axioms within this paper, sufficient for a reader to understand the composition theorem.

### F4. Notation: $h$ introduced in multiple places (Minor, High confidence)
**Location**: Lines 455-456 (HashSet), 621 (trapdoor Boolean algebra)
**Problem**: The hash function $h : \{0,1\}^* \to \{0,1\}^n$ is introduced in the HashSet construction ("where $h : \{0,1\}^* \to \{0,1\}^n$ is a cryptographic hash modeled as a random oracle") and again in the trapdoor Boolean algebra ("where $|$ denotes bitwise OR and $h : X^* \to \{0,1\}^n$ is a cryptographic hash"). The domain differs ($\{0,1\}^*$ vs. $X^*$). This should be unified.
**Suggestion**: Define $h$ once in a notation/preliminaries section with domain $\{0,1\}^*$ and note that elements of $X^*$ are encoded as bit strings before hashing.

### F5. \date{\today} left as dynamic date (Minor, High confidence)
**Location**: Line 40
**Problem**: The date will change every time the paper is compiled. For a submission, this should be a fixed date.
**Suggestion**: Replace with a fixed date.

### F6. Acknowledgments section is thin (Minor, Low confidence)
**Location**: Lines 1408-1411
**Quoted text**: "The constructions in this paper draw on the author's earlier work on the Bernoulli data type library and the trapdoor Boolean algebra."
**Problem**: This reads more like a provenance statement than an acknowledgment. It does not acknowledge any reviewers, colleagues, or funding sources.
**Suggestion**: Either expand with appropriate acknowledgments or remove the section if there are none.

### F7. Construction comparison table (Table 2) lacks delta column (Minor, Medium confidence)
**Location**: Table 2 (lines 733-755)
**Problem**: The table compares the three constructions across totality, rep. uniformity, correctness, epsilon, mu, and space. But it does not include a $\delta$ column, despite $\delta$ being one of the four main parameters. The HashSet has $\delta = $ N/A, the entropy map has $\delta$ = achievable, and the trapdoor Boolean algebra has $\delta$ = marginal only. These are stated in the text but not in the comparison table.
**Suggestion**: Add a $\delta$ row to Table 2.

### F8. "What This Framework Is Not" section repeats introduction (Suggestion)
**Location**: Section 10.4, lines 1390-1404 vs. Section 1, lines 101-110
**Problem**: The "What this is not" paragraph in the introduction (ORAM, FHE, garbled circuits) is repeated almost verbatim in Section 10.4. The repetition adds page count without new information.
**Suggestion**: Keep the brief version in the introduction and remove or significantly condense Section 10.4. Alternatively, the Section 10.4 version could add deeper analysis not present in the introduction.

### F9. No figures in a 20-page paper (Minor, High confidence)
**Problem**: The paper has zero figures despite being 20 pages and describing visual concepts (the trusted/untrusted machine model, the composition chain, the construction layers). The `img/` directory contains `fig_shmap.tex` and `fig_shs.tex` but these are not included.
**Suggestion**: Include at least one diagram showing the trusted/untrusted machine model protocol flow and one showing the construction layers. These would significantly aid reader comprehension.

## Narrative Assessment

The paper has a clear narrative arc: introduce the problem (outsourcing computation to untrusted parties), define the central object (cipher map), characterize it (four properties), instantiate it (three constructions), prove key results (composition theorem, space bounds), and discuss limitations and extensions. The narrative is honest about what the framework does and does not provide, which is a strength.

The writing is technically precise with few ambiguities. The main structural issue is section ordering (trust model should precede constructions). The main prose issue is the duplication between introduction and Section 10.4.

**Overall writing quality**: Good. Above average for a theory paper. Clear notation, consistent terminology, honest limitations.
