# Design: Part III (Algebra and Types)

**Author:** Alexander Towell
**Date:** 2026-06-18
**Status:** Design (pre-implementation)
**Parent spec:** `docs/superpowers/specs/2026-06-10-master-design.md`
**Scope:** Section-level outline for chapters 6-8 (Part III, ~34 pp budget; expect ~15-18 pp at the established density). Authoritative for the ch6-8 implementation plans.

## 1. Purpose

Part II fixed the cipher map and its four properties. Part III asks what *algebra* those objects support: which type constructors survive the passage through the trapdoor, what a cipher map can and cannot compute, and how much an adversary who can *operate* on cipher values (not just observe them) can learn. It is the bridge from the single-map view (Parts II, IV-marginal) to the active, compositional view (Part IV-compositional). Three chapters: the Boolean algebra and its exact/approximate asymmetry; the type constructors and the sum-type impossibility; and orbit closure, the first active-adversary measure.

Inherits from the master spec: research-monograph voice; technical-part density (runs to natural length, with figures + worked examples per the 2026-06-18 calibration); proof SKETCHES plus pointers as default, full short proofs for the load-bearing elementary results; no exercises; chapter-end Notes and Provenance; the spine is the authority on shared definitions.

## 2. Settled decisions (this spec)

- **The watchlist toy continues, and grows a second operand.** Part II's membership map returns; Part III needs Boolean *combination*, so a second small set is introduced (a second watchlist, or a "VIP list") so AND/OR/NOT have something to act on. The toy stays a membership/Boolean example so it threads from Part II without a new domain.
- **Proof depth.** Full short proofs for: the Boolean asymmetry (NOT is approximate, via pigeonhole) and the orbit-closure confidentiality bound (it is an elementary counting/entropy argument). Proof SKETCH + pointer for: the sum-type impossibility theorem (the structural heart of the algebraic-cipher-types paper; state it, give the intuition and the obstruction, point to the paper for the full proof) and the orbit monotonicity theorem. This keeps the keystone-style self-containment on the elementary results without reproducing the paper's hardest proof.
- **Source posture.** Part III consolidates the `algebraic-cipher-types` paper plus `foundations/trapdoor-boolean-algebra.md`. Like Part II, extraction is N/A (the paper exists); the harvest is back-port (cleaner statements) and one genuine cross-cut (the Boolean asymmetry as a constraint the whole book inherits).

## 3. Cross-cutting commitments

### 3.1 Running threads (per the master threads table)

| Thread | Action in Part III |
|---|---|
| Composition predictability | **Returns** in Ch 6 (Boolean chains accrue error through the Ch 4 composition theorem) |
| Boolean asymmetry (AND/OR exact, NOT approximate) | **Introduced** in Ch 6; used in Ch 7; a structural constraint flagged for the whole book |
| Measurable-not-negligible | Ch 8: the active-adversary residual entropy `H(X | view)`, a second measurable quantity beside `\delta` |
| Encoding granularity / entanglement | **Introduced** in Ch 7 (joint vs component-wise encoding, the entanglement parameter `p`); pays off the Ch 4.2 "delta bounds only the marginal" limitation |
| The compositional confidentiality scale | **Previewed** in Ch 8 (orbit closure is the active/compositional scale; full treatment in `part:confidentiality`) |

Ch 4.2 left an explicit promise: `\delta` bounds only the marginal distribution, joint correlations leak. Ch 7's encoding-granularity section is where that promise is paid; cross-reference `def:uniformity` and its honest-limitation note explicitly.

### 3.2 The two-scale boundary (do not conflate)

Part III straddles the marginal/compositional boundary that `book/CLAUDE.md` and spine §4A insist on. Ch 6-7 are mostly marginal/structural (the algebra of single maps and their types). Ch 8 (orbit closure) is the FIRST compositional/active measure: it answers "what can an adversary who applies operations to cipher values learn?", governed by `H(X|view)`, NOT by `\delta`. Ch 8 must say plainly that `\delta` does not control this scale, and forward to `part:confidentiality` for the rest (coincidence oracle, joint recovery).

### 3.3 Notation

Continue `notation.sty`. Part III adds: `\cipher{X}` used in earnest (cipher type constructors); `\orbitF` (orbit closure, spine §8); the Boolean operators on cipher values; the entanglement parameter `p`. New symbols go in `notation.sty`, never inline.

## 4. Chapter 6: Boolean Algebra over Trapdoor Values (~12 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 6.1 | Sets as bit images | ~2 | trapdoor-boolean-algebra.md; alg-cipher-types §"Cipher Boolean" | The online construction: a set `A` becomes a bit image `F(A)` (OR of element hashes); membership as a bit test. The K=1 deterministic trapdoor-set baseline (folded from the retired boolean-algebra paper). Connects to Ch 5's online strategy. |
| 6.2 | AND and OR are exact | ~2 | trapdoor-boolean-algebra.md; spine §3.4 | Union is exact (`F(A\cup B)=F(A)\,|\,F(B)`); intersection is one-sided (spurious bits from cross-element collisions, never missing bits). Worked toy: two small sets. |
| 6.3 | NOT is approximate (the asymmetry) | ~3 | spine §3.4 (lines 463-471); trapdoor-boolean-algebra.md WITH its erratum | **LANDMINE.** NOT cannot be exact: by pigeonhole, for a universe `> 2^n`, `F(A^c)` tends to `1^n`, while `~F(A)` does not. NOT is a BETTER approximation for SMALL `|A|`, WORSE for large, the OPPOSITE of the blog erratum. Full short proof (pigeonhole). The error depends on `|A|/2^n`. This is the structural constraint the whole book inherits. |
| 6.4 | The equality channel | ~2 | alg-cipher-types; spine | What the deterministic K=1 construction leaks: representational equality reveals value equality (the plaintext-Boolean / equality-channel regime). The cost of determinism; why K>1 (Ch 4.2) buys it back. |
| 6.5 | Boolean chains and error | ~2 | spine §3.4-3.5; Ch 4 | AND/OR chains accrue error only through the Ch 4 composition theorem (`\le`, callback to `thm:composition`); NOT adds structural error. Circuits heavy in NOT degrade faster. The composition-predictability thread, Boolean-flavored. |
| 6.6 | Notes and Provenance | ~0.5 | fresh | trapdoor-boolean-algebra.md (with erratum), spine §3.4; the K=1 baseline's provenance (retired boolean-algebra paper, folded). |

LANDMINE note: 6.3 carries the corrected NOT direction; the foundations file has the inverted erratum flagged inline. Verify against spine §3.4 lines 317-319 (the errata note) before drafting.

## 5. Chapter 7: Algebraic Cipher Types (~12 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 7.1 | Cipher types as a type algebra | ~2 | alg-cipher-types §3 (Cipher Type Constructors), §"Void and Unit" | `\cipher{X}` revisited (Ch 3.4); the program: which constructors of the type algebra (void, unit, product, sum, exponential) lift through the trapdoor. The summary table as the spine of the chapter. |
| 7.2 | Product types pass | ~3 | alg-cipher-types §"Product Types" | `\cipher{X\times Y}` is well-behaved: a product encodes cleanly, projections work. Worked toy. This is the easy, positive case, the foil for sum types. |
| 7.3 | The sum-type impossibility | ~3 | alg-cipher-types §"Sum Types", Thm (sum-type impossibility) | **The structural heart.** A faithful, total `\cipher{X+Y}` with both injections and a case analysis cannot exist in general: the obstruction (totality forces every token to decode, so the tag cannot be hidden AND recovered). State precisely; give the obstruction intuition; proof SKETCH + pointer to the paper. Contrast with 7.2. |
| 7.4 | Encoding granularity and entanglement | ~3 | alg-cipher-types; spine §4 (granularity) | Pays off Ch 4.2's marginal-only limitation. Joint vs component-wise encoding; the entanglement parameter `p` (p=1 marginal uniformity / leaks correlations; p=k joint, space `O(|Y|^k)`). The granularity trade-off (Core Principle 5). Worked: encoding a pair jointly vs separately. |
| 7.5 | Notes and Provenance | ~1 | fresh | alg-cipher-types §3, §8; the type-algebra summary as a candidate back-port / shared figure. |

## 6. Chapter 8: Orbit Closure and the Active Adversary (~10 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 8.1 | The active adversary | ~2 | alg-cipher-types §"Orbit Closure"; spine §4A | The shift: not just observing tokens, but APPLYING operations (the Boolean ops of Ch 6) and watching coincidences. Why `\delta` (a marginal measure) does not bound this. Sets up the compositional scale. |
| 8.2 | Orbit closure | ~2 | alg-cipher-types Def (orbit closure), Thm (monotonicity) | `\orbitF(c)`: the set of values a token could encode, consistent with all observed operation-outcomes. Monotonicity (more operations, smaller orbit): state, proof SKETCH. |
| 8.3 | The residual-entropy bound | ~3 | alg-cipher-types Thm (confidentiality bound, entropy form); spine §4A | **LANDMINE.** `H(X \mid \text{view}) \ge H(X) - \log_2|\orbitF(c)|`, the orbit set-form denominator is `|X|`, NOT `2^n`. Full short proof (it is an elementary entropy/counting bound). Worked toy: how operations shrink the orbit and the residual entropy. |
| 8.4 | Typed composition chains | ~2 | alg-cipher-types §"Typed Composition Chains" | Chaining typed cipher maps; how the orbit propagates through a chain; the preview of `part:confidentiality`'s compositional rate (the joint-recovery `\Theta(|Y_1||Y_2|/\xi^2)`, Assouad not Le Cam, stated as a forward pointer only). |
| 8.5 | Notes and Provenance | ~1 | fresh | alg-cipher-types §"Orbit Closure", spine §4A; the orbit denominator `|X|` correction as a landmine record; the two-scale boundary. |

## 7. Forward / backward reference map

- **Backward (real `\cref`):** Ch 6.1 builds on Ch 5's online strategy (`sec:strategies`); Ch 6.5 calls back `thm:composition`; Ch 7.1 revisits `sec:cipher-type` (`\cipher{X}`) and `rem:values-are-maps`; Ch 7.4 pays off `def:uniformity`'s marginal-only note; Ch 8.1 contrasts with `def:uniformity` (`\delta` is marginal).
- **Forward (footnote, part labels only):** the full compositional confidentiality theory `part:confidentiality`; the concrete Boolean construction `part:constructions`; the frontiers `part:frontiers`.
- **Within Part III:** ch6 -> ch7 -> ch8 cross-refs once drafted.

## 8. Page budget

Ch 6 ~12, Ch 7 ~12, Ch 8 ~10 (master budget ~34). At the established density expect ~5-6 pp/chapter, ~15-18 pp total; the rich elements (Boolean-asymmetry figure, sum-type contrast figure, orbit-shrink worked example) are the priority over raw page count. Ch 6 and Ch 8 carry the landmines and get the most care.

## 9. Harvest (back-port + one cross-cut)

- **Cross-cut (genuine):** the Boolean asymmetry (AND/OR exact, NOT approximate, the `|A|/2^n` error) is a constraint EVERY system on this framework inherits (master thread). Worth one canonical statement the papers cite, candidate to promote into the spine §3.4 as the reference treatment.
- **Back-port candidates:** the type-algebra summary table (7.1) and the sum-type impossibility as a clean numbered statement; if sharper than `algebraic-cipher-types`, note for its next revision. The orbit residual-entropy bound (8.3) with the `|X|` denominator stated unambiguously, a guard against the `2^n` reversion.
- **Landmine guard:** 6.3 (NOT direction) and 8.3 (orbit denominator `|X|`) are the two reversion risks; both get full proofs so the correct form is locked in the book.

## 10. Risks (part-specific)

1. **NOT-direction reversion (6.3).** The foundations file has the inverted erratum; draft from spine §3.4 lines 317-319, not the blog text. (Highest attention with 8.3.)
2. **Orbit denominator `|X|` vs `2^n` (8.3).** The book/CLAUDE.md landmine; full proof locks it.
3. **Sum-type impossibility overreach.** State the theorem with its exact hypotheses; do not over-claim (it is impossibility *in general*, under totality + faithfulness; specific restricted sum encodings exist). Sketch + pointer, do not reprove.
4. **Two-scale conflation (Ch 8).** Orbit closure is the ACTIVE/compositional scale; say plainly `\delta` does not bound it. Spine §4A is the authority.
5. **Self-overlap with algebraic-cipher-types (its own venue).** Proof-depth decision mitigates: sketch the hard theorem (sum-type), prove only the elementary ones (NOT asymmetry, orbit bound).

## 11. Out of scope (Part III)

The full compositional confidentiality theory (coincidence oracle, joint-recovery rate, Assouad lower bound), which is `part:confidentiality`; the concrete Boolean construction's implementation and experiments, which is `part:constructions`; the marginal entropy-ratio bound, which is `part:confidentiality`.

## 12. Success criteria

- AND/OR exact, NOT approximate with the correct direction (better for small `|A|`), proved by pigeonhole.
- The sum-type impossibility stated precisely with its hypotheses; product types shown to pass, as the contrast.
- The orbit-closure residual-entropy bound with denominator `|X|` (not `2^n`), proved.
- Ch 7.4 pays off Ch 4.2's marginal-only limitation (encoding granularity / entanglement).
- Ch 8 keeps the marginal/compositional scales distinct and forwards the rest to `part:confidentiality`.
- `make` builds Part III clean (0 undefined refs, landmines intact).
- `HARVEST.md` Part III section filled.

## 13. Next step

`/bookwright:plan ch06` (or draft directly from this spec, as Part II's ch3-5 were). Draft order ch6 -> ch7 -> ch8. After Part III, the master sequencing goes to Part IV (Confidentiality), which consolidates the Entropy Ratio paper and pays off Ch 8's compositional preview.
