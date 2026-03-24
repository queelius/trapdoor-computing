# Thesis Refinement: Composable Oblivious Algebraic Data Types

**Date**: 2026-03-19
**Paper**: `papers/algebraic_cipher_types/`
**Stage**: Early notebook (2019-2022), pre-trapdoor reframing
**Prior review**: `.papermill/reviews/review-2026-03-19.md`
**Prior thesis**: `.papermill/thesis-analysis.md`

---

## 1. Core Insight This Paper Uniquely Captures

The unique contribution is the **confidentiality-side algebraic type theory for cipher types**: how each algebraic type constructor (void, unit, sum, product, exponential) interacts with the trapdoor construction, and the fundamental trade-offs that arise.

No other paper in the ecosystem addresses this:

- **cipher-maps** defines cipher maps (the exponential type) but does not treat void, unit, sum, or product cipher types at all. It has no algebraic type theory.
- **bernoulli_data_type/algebraic_types** treats algebraic types but only on the *error/accuracy* axis (how errors propagate through type constructors). It says nothing about confidentiality.
- **trapdoor-boolean-algebra** is a special case (the Boolean cipher type) with no general type theory.

The gap: nobody has formalized the confidentiality consequences of type constructors for cipher types. This paper's notebook contains the raw material for that formalization.

### What makes this non-obvious

The sum-type trade-off (`OT(X+Y)` hides the branch but breaks composability with `OT(X)`/`OT(Y)` functions; `OT(X)+OT(Y)` preserves composability but reveals the branch) is a *structural* result about cipher types. It is not an artifact of a particular construction; it follows from the information-theoretic requirements of pattern matching on tagged unions. This is the kind of result that constrains all implementations and deserves a formal proof.

---

## 2. Standalone Paper vs. Absorption into cipher-maps

**Recommendation: Standalone paper, but with a different scope and framing.**

### Arguments for standalone

1. **Orthogonal axis.** cipher-maps is about the *exponential type* (functions). Algebraic cipher types is about the full type algebra (void, unit, sum, product, exponential). These are complementary, not redundant.

2. **Different audience.** cipher-maps targets readers who want to understand cipher map construction. Algebraic cipher types targets readers who want to understand how to build compound cipher systems from simple ones -- a design-level concern.

3. **Sufficient depth.** The sum-type trade-off, product-type correlation hiding, orbit/closure analysis, and cipher TM together constitute enough material for a standalone paper.

### Arguments for absorption

1. cipher-maps already cites the "three construction layers" from this paper. Absorbing the algebraic type theory would make it a more complete reference.

2. The algebraic material is still mostly informal. Starting a new paper from scratch may be easier than trying to wrestle the notebook into shape.

### Verdict

**Start a new paper** titled something like "Algebraic Cipher Types: Type Constructors and Confidentiality for Trapdoor Computing." Do *not* revise this notebook. Instead, write the new paper fresh, using the cipher-map formalism as the foundation and mining this notebook for ideas. The notebook stays as a historical artifact.

---

## 3. Idea-to-Publication Map

Each high-value idea from the review, mapped to where it should live:

| Idea | Home | Status | Notes |
|------|------|--------|-------|
| **Three-monad pipeline** (restrict -> partial -> embed -> noise -> cipher) | cipher-maps, Section 1.2 | Already absorbed | The formalism already credits "algebraic cipher types, 2019" and presents the three construction layers. Add a citation in the final paper; no further work needed. |
| **Sum-type confidentiality/composability trade-off** | New algebraic cipher types paper | Needs formalization | The core novel result. Prove it: (a) `OT(X+Y)` requires `|OT(X+Y)| >= |OT(X)| + |OT(Y)|` representations and hides the tag; (b) pattern-matching on `OT(X+Y)` to extract `OT(X)` or `OT(Y)` requires the trapdoor; (c) `OT(X)+OT(Y)` is composable but reveals the tag bit. This should be a theorem with information-theoretic proof. |
| **Orbit/closure leak analysis** | New algebraic cipher types paper, or a short standalone note | Needs formalization | The principle: given a computational basis F, the orbit closure of any known cipher value under F bounds the adversary's knowledge. The examples (and(x,not(x))=false, successor cascades, division-based reconstruction) are compelling. Needs: (a) formal definition of orbit closure for cipher types; (b) a monotonicity theorem (more operations => larger orbit closure => less confidentiality); (c) quantitative bound: confidentiality <= 1 - |orbit closure| / |cipher values|. Could be a section in the new paper or a separate note. |
| **Cipher Turing machine** | New algebraic cipher types paper, Section on computational alternatives | Needs development | The key insight -- space complexity can be divorced from domain cardinality -- deserves a proposition. The observation about multiple transition-function versions indexed by cipher tags is worth stating precisely. This is the computational counterpart to the cipher map: where cipher maps are lookup tables with space O(|domain|), cipher TMs are programs with space O(|program|). |
| **Obfuscation hierarchy** (value -> function -> type -> pair -> full black box) | New algebraic cipher types paper, introductory framework | Informal taxonomy, keep informal | Good for framing the problem space. The set-membership example is an excellent pedagogical device. Does not need a formal proof; it is a taxonomy, not a theorem. |
| **Regularity and non-regularity of cipher types** | New algebraic cipher types paper, brief remark | Observation, keep informal | The connection to Stepanov's EoP is distinctive. State it as a remark: cipher types are inherently non-regular (no general equality, no default construction) because regularity leaks information. |
| **Bernoulli FPR model, binomial theorems** | bernoulli_data_type papers | Already absorbed | Do not duplicate. Reference from bernoulli_data_type/algebraic_types. |
| **Cardinality estimation via space complexity** | Tangential; cite from cipher-maps if relevant | Already noted in formalism | The PHF cardinality estimator example is a specific case of Kerckhoffs-aware space analysis. Mention in passing, do not develop. |
| **k-ary predicate model** | bernoulli_data_type | Already absorbed | The approximate k-ary predicate model is essentially the Bernoulli error model applied to relations. Already covered in bernoulli_data_type. |
| **Encrypted Boolean Search application** | encrypted-search paper (separate repo) | Application-specific | Does not belong in the algebraic cipher types paper. |

---

## 4. Proposed Thesis (if this becomes a standalone paper)

### Title
**Algebraic Cipher Types: Type Constructors and Confidentiality for Trapdoor Computing**

### Thesis Statement
Cipher types -- opaque representations of values behind a cryptographic trapdoor -- form an algebra over the standard type constructors (void, unit, sum, product, exponential), but each constructor introduces a specific trade-off between confidentiality and composability. We characterize these trade-offs:

1. **Sum types** force a choice between hiding the tag (confidentiality) and supporting pattern matching (composability). This trade-off is structural: no construction can avoid it.
2. **Product types** force a choice between hiding correlations between components and supporting projection functions.
3. **Exponential types** (cipher maps) are the primary construction mechanism; their space complexity is the fundamental resource.
4. The **orbit closure** of a computational basis bounds the adversary's knowledge: given operations F on cipher type OT(T), the fraction of cipher values deducible from any known value via F determines the residual confidentiality.

These results are independent of the specific cipher map construction (batch or online) and apply to any system satisfying the four cipher map properties.

### Paper Outline (proposed)

1. **Introduction and problem statement.** Computing on hidden values; the trusted/untrusted model; what algebraic types buy you.
2. **Preliminaries.** Cipher map definition and four properties (cite cipher-maps). Bernoulli error model (cite bernoulli_data_type).
3. **Cipher type constructors.**
   - 3.1 Void and Unit (brief; structural completeness)
   - 3.2 Sum types and the confidentiality/composability trade-off (main theorem)
   - 3.3 Product types and correlation hiding
   - 3.4 Exponential types: cipher maps as the function space
4. **Information leak analysis.**
   - 4.1 Orbits and orbit closure under a computational basis
   - 4.2 Monotonicity: more operations => more leakage
   - 4.3 Examples: Boolean algebra, integer arithmetic, comparison
5. **Computational alternatives.**
   - 5.1 Cipher Turing machine: space complexity divorced from domain cardinality
   - 5.2 Multiple implementations indexed by cipher tags
   - 5.3 Trade-off: cipher map (space) vs. cipher TM (time + pattern leakage)
6. **Obfuscation hierarchy.** Taxonomy from value obfuscation to steganographic hiding.

---

## 5. What To Do Next

1. **Do not revise this notebook.** It is a historical artifact.
2. **Start writing Section 3.2** (sum-type trade-off) as a standalone theorem with proof. This is the most formalization-ready claim and the core contribution.
3. **Formalize orbit closure** (Section 4.1-4.2). Define it precisely, prove monotonicity, give quantitative bounds.
4. **After those two sections exist**, evaluate whether there is enough for a paper or whether they should fold into cipher-maps as an appendix or companion section.
5. The Bernoulli error-propagation content is already in bernoulli_data_type/algebraic_types. Do not re-derive; cite.
