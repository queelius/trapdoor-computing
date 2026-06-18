# Design: Part II (The Cipher Map Abstraction), the keystone

**Author:** Alexander Towell
**Date:** 2026-06-17
**Status:** Design (pre-implementation)
**Parent spec:** `docs/superpowers/specs/2026-06-10-master-design.md`
**Scope:** Section-level outline for chapters 3-5 (Part II, ~30-34 pp). Authoritative for the ch3-5 implementation plans. This is the KEYSTONE part; everything after it builds on these definitions.

## 1. Purpose

Part II turns the informal paradigm of Part I into a precise object. By the end of chapter 5 the reader has the cipher map as a formal tuple, the four properties as numbered definitions with their parameters, the one theorem that makes composition predictable, and the abstract construction (the acceptance predicate) that the concrete constructions of Part V will instantiate. This is where the book's notation and its canonical definitions are set, so correctness here is load-bearing for every later part.

Inherits from the master spec: research-monograph voice (established by Part I, continue it); **technical-part density** (this part runs to its natural ~30 pp, not the tight Part I budget); proof SKETCHES plus pointers as the default; no exercises; chapter-end Notes and Provenance; the spine (`../../formalism/cipher-map-formalism.md`) is the authority on every shared definition.

## 2. Settled decisions (this spec)

Two choices fixed in the 2026-06-17 design Q&A:

- **(Concreteness) A toy running example.** One tiny cipher map, an encrypted **watchlist-membership** map ("is this name on a short list?", universe `{alice, bob, carol, dave}`, set `S = {alice, carol}`), is introduced in chapter 3 and returns in each chapter as the properties and the construction accrue. It grounds the abstraction without pre-empting Part V's real constructions (HashSet, codec). It is deliberately a membership map `f : X -> {0,1}`, the simplest non-trivial latent function, and it connects back to the search/membership framing of Part I.
- **(Proof depth) Prove the short ones, point for the rest.** The composition theorem and the space-accuracy duality get full, short proofs in the book; the tight space lower bound gets a proof sketch plus a pointer to the cipher-maps paper. Everything else is stated with intuition and a citation. This keeps the keystone self-contained on its load-bearing results while avoiding wholesale reproduction of the paper (a self-overlap risk, since cipher-maps targets PoPETs).

## 3. Cross-cutting commitments (all three chapters)

### 3.1 Running threads (per the master threads table)

| Thread | Action in Part II |
|---|---|
| Trusted/untrusted lens | **Formalized** in Ch 3.1 (planted informally in Ch 1.1) |
| Totality as privacy | **Introduced formally** in Ch 3.3 / Ch 4.1 (teased in Ch 1.2) |
| Measurable-not-negligible | **Re-entered** in Ch 4.2 as the parameter delta (planted in Ch 1.3) |
| Composition predictability | **Introduced** in Ch 4.4 (the composition theorem) |
| The Bernoulli connection | **Introduced** in Ch 4.3 (eta from the Bernoulli error model -> Appendix A) |

The four-cannots prose preview of Ch 1.2 is **paid off** here: each cannot was promised against a named property, and Ch 4 supplies the numbered definitions. Ch 4 should cross-reference Ch 1.2 explicitly so the reader feels the promise kept.

### 3.2 Notation, formally introduced

Part II is where `notation.sty` earns its keep. Introduce, at first formal use and matched to spine section 8: `\fhat`, `\ghat` (cipher-map approximations); `\enc`, `\dec`; `\B` (so `\B^n`); `\TV`; `\cipher{X}` (the cipher type, Ch 3.4); the parameter tuple `(\eta, \varepsilon, \mu, \delta)` in **spine-canonical order** (cross-paper item C-6, do not reorder). A consolidated notation reference is Appendix B; Part II is where the symbols are defined, not just listed.

### 3.3 The canonical definitions live here

Ch 3 (the tuple) and Ch 4 (the four properties) are the book's definitions of record for these objects. They must match the spine, and where the standalone papers differ, the book follows the spine and the divergence is logged to back-port. This is the chapter set that makes the cross-paper QA payoff real.

## 4. Chapter 3: Cipher Maps (~10 pp)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 3.1 | The trusted and untrusted machines | ~2 | spine sec 1.1; cipher-maps sec 3 | Formalize `T` (holds `\enc`, `\dec`, secret `s`) and `U` (holds `\fhat`); the latent function `f : X -> Y`; introduce the watchlist toy. Plants nothing new; formalizes the Ch 1 trusted/untrusted thread. |
| 3.2 | The cipher map tuple | ~3 | cipher-maps sec 3 (Def); spine sec 1.1 | Numbered Definition: a cipher map is `(\fhat, \enc, \dec, s)` with `\fhat : \B^n -> \B^n` total, `\enc : X x \{0..K(x)-1\} -> \B^n`, `\dec : \B^n -> Y u \{\bot\}`. The toy map instantiated against the definition. Notation introduced here. |
| 3.3 | Totality and the populated support | ~3 | spine sec 1.2; cipher-maps sec 5 | Totality as the structural fact (every `\B^n` string answers); the noise-decode probability `\varepsilon` (a random string decodes valid with prob `\varepsilon`); `\mathrm{im}(\enc)` the populated support, the object delta will be measured against. The filler-indistinguishability consequence (totality-as-privacy thread). |
| 3.4 | The cipher type `C(X)` | ~1.5 | cipher-maps sec 3; spine | The functorial view in one stroke: a cipher map is a morphism, `\cipher{X}` the cipher type over `X`. Kept brief; it sets up Part III (footnote to `part:algebra`). |
| 3.5 | Notes and Provenance | ~0.5 | fresh | cipher-maps sec 3, spine sec 1-2; note that the formal tuple is the book's definition of record. |

## 5. Chapter 4: The Four Properties (~12 pp)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 4.1 | Totality | ~2 | spine Property 1; cipher-maps sec 4 | Numbered Definition (Property 1). Every input produces output; `\varepsilon` revisited; the filler/real indistinguishability stated as the consequence. Toy: filler names. Pays off Ch 1.2 cannot-distinguish-filler. |
| 4.2 | Representation uniformity (`\delta`) | ~3 | spine Property 2; cipher-maps sec 4 | Numbered Definition (Property 2), **IMAGE-RELATIVE**: `\delta = \TV(Q, U_{\mathrm{im}})`, `H^* = \log_2|\mathrm{im}(\enc)|`, NOT ambient `\B^n` (LANDMINE / harvest BP-1). Multiple encodings `K(x)`; frequency flattening; this is the parameter the measurable-not-negligible thread becomes. Pays off Ch 1.2 cannot-determine-domain. **This section defines `\delta` for the whole book.** |
| 4.3 | Correctness (`\eta`) | ~2 | spine Property 3; cipher-maps sec 4 | Numbered Definition (Property 3). The error budget; `\eta` as the Bernoulli error rate (introduce the Bernoulli-connection thread, footnote to `Appendix A`); `\eta` as deniability (callback to Ch 1.2 cannot-be-sure-correct). |
| 4.4 | Composability and the composition theorem | ~3 | spine Property 4 / sec 3; cipher-maps sec 7 | Numbered Definition (Property 4). The composition theorem `\eta_{\mathrm{total}} \le 1 - \prod_i (1 - \eta_i)`, **INEQUALITY form** (LANDMINE: not equality, because an error in one stage can mask an error in another). **Full short proof** (per the proof-depth decision). Introduces the composition-predictability thread. |
| 4.5 | The parameter tuple `(\eta, \varepsilon, \mu, \delta)` | ~1.5 | spine sec 1.4 | The decomposition: each property's parameter; `\mu = H(Y)` the value-encoding cost. Spine-canonical order (C-6). |
| 4.6 | Notes and Provenance | ~0.5 | fresh | cipher-maps sec 4, spine sec 3; record the inequality-not-equality point and the image-relative `\delta` as the book's canonical forms. |

## 6. Chapter 5: Constructions in the Abstract (~10 pp)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 5.1 | Two strategies: batch and online | ~2 | cipher-maps sec 6; spine sec 1.2 | Batch (seed search, build the table once) vs online (algebraic). The toy watchlist as a batch construction. Concrete realizations deferred to `part:constructions` (footnote). |
| 5.2 | The acceptance predicate | ~3 | cipher-maps sec 6.2; spine | The abstract unification: `A(y) \subseteq \B^n` the tokens that decode to `y`; the family `\{A(y)\}` partitions the populated hash space; Shannon-optimal allocation `|A(y)| \propto \Pr[f(X)=y]`. Toy: `A(\text{yes})/A(\text{no})` for the watchlist. This is the device that makes HashSet, frequency-smoothing, and encrypted search one construction (forward to `part:constructions`). |
| 5.3 | The space-accuracy duality | ~3 | cipher-maps sec 6 (Thm 6.1) | bits/element `= -\log_2 \varepsilon + \mu`, with `\mu = H(Y)`: `-\log_2\varepsilon` is the cost of hiding signal in noise, `\mu` the cost of encoding values. **Full short derivation.** The tight information-theoretic lower bound stated with a **proof sketch + pointer** to cipher-maps. |
| 5.4 | Notes and Provenance | ~1 | fresh | cipher-maps sec 6, spine sec 1.2 + 2; the space bound and the acceptance-predicate framing are candidates to back-port to cipher-maps if the book's statement is cleaner (harvest). |

## 7. Forward / backward reference map

- **Backward (real `\cref`, Part I labels exist):** Ch 3.1 formalizes `\cref{sec:oblivious-service}`'s trusted/untrusted model; Ch 4 pays off `\cref{sec:untrusted-sees}`'s four cannots; Ch 4.2 makes precise the entropy-ratio tease of `\cref{sec:measured-not-negligible}`.
- **Forward (footnote, part labels only):** the algebra and types `part:algebra`; the confidentiality measures where `\delta` becomes the entropy ratio `part:confidentiality`; the concrete constructions that instantiate the acceptance predicate `part:constructions`; the Bernoulli primer (Appendix A).
- **Within Part II:** ch3 -> ch4 -> ch5 cross-refs to ch/sec/thm labels are fine once drafted.

## 8. Page budget

Ch 3 ~10, Ch 4 ~12, Ch 5 ~10, total ~32 pp, within the ~30-34 pp natural budget for the keystone. Ch 4 is the densest (the four definitions plus the composition proof); if it runs long the parameter-tuple section 4.5 can compress, not the definitions.

## 9. Harvest (the cross-paper payoff, Part II is rich)

Part II consolidates the cipher-maps paper (the PoPETs target), so **extraction is N/A**, but the back-port harvest is the point:

- **BP-1 (image-relative delta).** Ch 4.2 is the chapter that defines `\delta`. Writing it image-relative forces the corrected definition into cipher-maps Property 2 and the spine (cross-paper item C-11). Log to `HARVEST.md` when drafted; this is the single highest-value back-port in the book.
- **BP-4 (NEW): composition `\le` vs `=`.** The cipher-maps R3 review flagged an equality/inequality inconsistency (Thm uses `\le`, a corollary and the discussion used `=`). Ch 4.4 states the clean `\le` form with proof; this is the canonical statement to back-port to cipher-maps wherever it still says `=`. Log to `HARVEST.md` and cross-ref the cipher-maps review.
- **Cleaner-statement candidates:** the four properties as a clean numbered set and the acceptance-predicate unification; if the book's phrasing is sharper than the paper's, note it for the next cipher-maps revision.
- **Drafting discipline:** verify every cipher-maps section/theorem number against the paper's `.aux` before citing it (the companion was renumbered); re-read sources at draft time (a parallel session may have moved them).

## 10. Risks (part-specific)

1. **The image-relative `\delta` landmine (4.2).** The single most important definition to get right; it is the book's canonical `\delta`. (Highest attention.)
2. **Composition stated as equality.** Must be `\le` (4.4); errors can mask. Landmine.
3. **Self-overlap with cipher-maps under PoPETs.** The proof-depth decision (short proofs only for elementary results) mitigates; do not reproduce the paper's full proofs. The composition proof is standard/elementary, low double-publication risk; the space lower bound stays a sketch + pointer.
4. **Stale companion numbers.** cipher-maps was renumbered; verify against `.aux`.
5. **Parameter-tuple order drift** `(\eta, \varepsilon, \mu, \delta)`; use the spine order (C-6).

## 11. Out of scope (Part II)

The concrete constructions' full treatment (Part V); the confidentiality measures and the Fannes bridge (Part IV); the algebra and type theory (Part III); the full Bernoulli model (Appendix A); the active-adversary / orbit-closure scale (Part III/IV).

## 12. Success criteria

- The four properties are defined consistently with the spine, with `\delta` image-relative.
- The composition theorem is stated in inequality form with a clean short proof.
- The watchlist toy threads through all three chapters and makes the abstraction tangible.
- The book's notation is established here for every later part.
- `make` builds Part II clean (0 undefined refs, landmines intact).
- `HARVEST.md` logs BP-1 and BP-4 (the back-ports drafting forced).

## 13. Next step

`/bookwright:plan ch03` (Cipher Maps), then ch04, then ch05. Draft carefully: this is the keystone. After Part II, the master sequencing pulls Part IV forward if the Entropy Ratio paper work wants the cross-check; otherwise Part III.
