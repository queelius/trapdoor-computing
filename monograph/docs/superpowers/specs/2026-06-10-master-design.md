# Design: Trapdoor Computing (master spec)

**Author:** Alexander Towell
**Date:** 2026-06-10
**Status:** Master design (pre-implementation)
**Scope:** Book-level design for the monograph "Trapdoor Computing: Computing on Opaque Encodings." Authoritative for the per-Part design specs and the per-chapter implementation plans.

## 1. Thesis / through-line

Trapdoor computing is computing on values whose meaning is hidden behind a one-way trapdoor. A trusted machine holds the encoder and decoder; an untrusted machine sees only total functions on opaque bit strings flowing through opaque lookup tables. The book's through-line: this single abstraction (the **cipher map**) unifies a family of constructions, its confidentiality is **measurable** (quantitative information flow) rather than **negligible** (cryptographic reductions), its composition is **predictable**, and its privacy comes from **one-way hashing plus uniform representation**, not from hiding access patterns.

The book consolidates the trapdoor-computing paper family into one coherent development and closes with a research-agenda frontier that launches the next program ("consolidate, then pivot").

## 2. Audience and prerequisites

Researchers and graduate students in security, cryptography, and information theory. Assumed background: graduate probability; basic information theory (entropy, conditional entropy, mutual information, total-variation distance) used but not re-derived; familiarity with hashing and Bloom filters is helpful. Quantitative information flow and the Bernoulli error model are introduced as needed (the Bernoulli foundation via the Appendix A primer).

## 3. Format, tone, depth

Research monograph, single authorial voice, intuition-first but rigorous. Theorems are stated precisely with **proof sketches plus pointers**; full proofs of the headline results live in the standalone papers and are cited (concise-synthesis depth, target ~150-220 pp). No exercises. Each chapter closes with a **Notes and Provenance** section (citations, authentic-source pointers, and any open sub-questions), the research-monograph analog of bibliographic notes.

**Density calibration (2026-06-17, after drafting ch1-2).** Motivation chapters run tight: Part I came in at ~4.5 pp (ch1) and ~3 pp (ch2), ~8-10 pp for the part, and reads complete. The technical parts (II-V) run to their natural, richer length (theorem- and construction-driven). Book target recalibrated to ~150 pp body. The per-chapter page budgets in section 4 are over-estimates for Part I and remain upper guides for the technical parts.

## 4. Structure (parts, chapters, page budgets)

Six parts, fourteen chapters, three appendices. Body ~174 pp; with front matter and appendices ~198 pp.

### Part I: The Paradigm (~24 pp)
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 1 | Computing on Opaque Encodings | ~12 | foundations/, spine sec 1 | The motivating vision (a search engine that cannot read your queries or your results); the trusted/untrusted machine model; the central question (how much does the untrusted machine learn?); measurable-not-negligible. |
| 2 | What Trapdoor Computing Is Not | ~10 | foundations/, cipher-maps sec 1 | Position against ORAM, FHE, garbled circuits, SSE/PPE. The privacy source is one-way hash + uniform representation, NOT access-pattern hiding. Sets the provenance guardrail for the whole book. |

### Part II: The Cipher Map Abstraction (~34 pp) -- KEYSTONE
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 3 | Cipher Maps | ~12 | cipher-maps sec 3, spine sec 2 | The tuple (f-hat, enc, dec, s); the latent function and its trapdoor approximation; totality; the trusted/untrusted machine model formalized. |
| 4 | The Four Properties | ~12 | cipher-maps sec 4, spine sec 3 | Totality, representation uniformity delta, correctness eta, composability; the parameter tuple (eta, epsilon, mu, delta); the composition theorem eta_total = 1 - prod(1 - eta_i). |
| 5 | Constructions in the Abstract | ~10 | cipher-maps sec 6, spine sec 3 | Batch vs online strategies; the acceptance predicate; the space-accuracy duality bits/element = -log2(epsilon) + mu; the information-theoretic lower bound. |

### Part III: Algebra and Types (~34 pp)
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 6 | Boolean Algebra over Trapdoor Values | ~12 | algebraic-cipher-types, foundations/trapdoor-boolean-algebra.md | AND/OR exact at the bit level, NOT approximate (the Boolean asymmetry via pigeonhole); the equality channel; the K=1 deterministic trapdoor-set baseline. |
| 7 | Algebraic Cipher Types | ~12 | algebraic-cipher-types | Product and sum types; the sum-type impossibility theorem; type constructors over trapdoor computing; encoding granularity / the entanglement parameter. |
| 8 | Orbit Closure and the Active Adversary | ~10 | algebraic-cipher-types, spine sec 4A | Orbit-closure residual entropy H(X|view) >= H(X) - log2|orbit| (set-form denominator |X|); typed composition chains; preview of the compositional confidentiality scale. |

### Part IV: Confidentiality (~28 pp)
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 9 | The Marginal Scale | ~14 | maximizing-confidentiality (SUMMARIZE), spine sec 4A | The entropy ratio e = H/H*; the Fannes-Audenaert bound e >= 1 - delta - h2(delta)/n (linear, not Pinsker); the three delta-reduction levers with costs (noise injection / Fisher dilution rho^2; multiplicity K propto D, homophonic; joint-encoding granularity). |
| 10 | The Compositional Scale | ~14 | maximizing-confidentiality (SUMMARIZE), spine sec 4A | The joint-recovery rate Theta(|Y1||Y2|/xi^2) with matching bounds (Assouad, not Le Cam); mutual-information preservation; the two scales do not reduce; delta necessary-not-sufficient; system-level defenses. SUMMARIZE, point to the standalone CSF paper for full proofs. |

### Part V: Constructions (~36 pp)
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 11 | Hash-Based Constructions | ~12 | cipher-maps sec 6, src/cipher-maps | The PHF backend; the batch construction realized; the trapdoor_maps library; HashSet and entropy-map instantiations; correctness/FPR from the Bernoulli base. |
| 12 | GF(2)-Linear Retrieval | ~12 | codec-controlled-retrieval | The codec/ribbon construction; non-member output uniform on the span W; the GF(2)-rank threshold; structural frequency-hiding at zero per-query cost. |
| 13 | Rekeying, Closures, and Programs | ~12 | cipher-rekeying, cipher-closures, cipher-program-construction | Cipher rekeying via closures; cipher data structures and the code-data duality; realizing programs as cipher-map compositions. |

### Part VI: Frontiers (~18 pp)
| Ch | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 14 | Open Problems and the Next Program | ~18 | .papermill/prior-art/2026-06-09-ecosystem-survey.md | A structured research agenda from the survey: the salient open directions organized into a roadmap; what the next original-research program looks like; the pivot. Roadmap, NOT new results. |

### Appendices
- **A. A Bernoulli Error-Theory Primer (~10 pp).** The minimal FPR/FNR, confusion matrices, and the composition theorem the book uses; cites the Bernoulli papers for the rest. (Chosen handling for the Bernoulli foundation.)
- **B. Notation Reference (~3 pp).** Consolidated from `notation.sty` and spine sec 8.
- **C. Deferred Proofs (as needed).** Full proofs for results where the book, not a standalone paper, is the better home.

## 5. Running threads

Seven threads, introduced early and returned to at named points so each feels carried:

| Thread | Introduced | Returns | Closes |
|---|---|---|---|
| Trusted/untrusted lens (who holds enc/dec) | Ch 1 | Ch 3 (formal), Ch 9-10 | Ch 13 |
| Measurable-not-negligible (QIF, not reductions) | Ch 1 | Ch 4 (delta), Ch 9 | Ch 10 |
| Two-scale confidentiality (marginal / compositional) | Ch 8 (preview) | Ch 9 (marginal), Ch 10 (compositional) | Ch 14 |
| Composition predictability (eta_total = 1 - prod(1-eta_i)) | Ch 4 | Ch 6 (Boolean), Ch 11 (constructions) | Ch 13 |
| Totality as privacy | Ch 3 | Ch 10 (it creates the compositional channel) | Ch 12 |
| Boolean asymmetry (AND/OR exact, NOT approximate) | Ch 6 | Ch 7, Ch 13 | Ch 14 (a structural constraint on all systems) |
| The Bernoulli connection (error theory underneath) | Ch 4 | Ch 11 | Appendix A |

## 6. Citation policy and provenance

- The monograph is the **synthesis**; full proofs of the headline theorems live in the standalone papers (cipher-maps, algebraic-cipher-types, codec-controlled-retrieval, the Entropy Ratio at CSF) and are cited, with proof sketches in the book.
- Self-citations to the framework papers; external citations to the foundations (Shannon; QIF, Smith and Alvim et al.; Fannes-Audenaert; homophonic, Simmons / Gunther / Jendal-Kuhn-Massey; the Bernoulli papers).
- **Provenance is the authority rule:** the spine `../../formalism/cipher-map-formalism.md` governs every shared definition. When the book and the spine disagree, the spine wins. Authentic sources are `foundations/`; see `ECOSYSTEM-TRIAGE.md` for the AUTHENTIC / CLAUDE-EXPANDED / DRIFTED classification.
- Citations and authentic-source pointers live in each chapter's Notes and Provenance section.

## 7. Repository layout

Per `book/CLAUDE.md` and `bookwright.config.yaml`. `book/` holds the LaTeX (master, preamble, `notation.sty`, the six parts, chapters, appendices); `notebooks/` is unused under the minimal-notebook decision; `docs/superpowers/specs/` (this file and the per-Part specs) and `docs/superpowers/plans/` (per-chapter implementation plans). Source papers are read in place under `../papers/`, `../formalism/`, `../foundations/`.

## 8. Notebook and figures discipline (minimal)

No paired per-chapter notebooks. Figures and tables are **pre-generated from the existing `trapdoor_maps` library** (`../../src/cipher-maps/`) and reused; the reproducing script is named in the relevant Notes and Provenance section. `notebook_stack` is set to `none` (the notebook-author agent is not dispatched). This keeps the book a synthesis of already-validated empirics rather than a re-execution harness.

## 9. Exercises convention

None. This is a research monograph, not a textbook. The pedagogical load that a textbook carries in exercises is carried here by the chapter-end Notes and Provenance sections and by the Part VI open-problems agenda.

## 10. Sequencing and build plan

- **Part II is the keystone** (the abstraction everything else builds on): design and draft it carefully.
- Dependency order is forward, I -> II -> III -> IV -> V -> VI; Appendix A (Bernoulli primer) must exist before Parts IV and V reference it.
- Recommended draft order: **Part I first** (to lock voice and the running threads), then **II** (keystone), then III, then IV (summarize Entropy Ratio), then V, then VI (roadmap), then appendices. (Part I is short and sets tone; doing it first de-risks the voice for the auditors.)
- Per-Part design specs come next, one per part, each authoritative for its chapter plans. Then per-chapter implementation plans, then drafting.

## 11. Risks

1. **ORAM / crypto-formalism drift.** The standing provenance landmine. Mitigation: the spine-authority rule, the guardrail chapter (Ch 2), and the constraint section in `book/CLAUDE.md`; the math-auditor and a provenance check on every chapter.
2. **The four mathematical landmines reverting** (Fannes-not-Pinsker; K propto D; orbit denominator |X|; Assouad-not-Le-Cam). Listed in `book/CLAUDE.md` and `bookwright.config.yaml`; verify on every relevant chapter.
3. **Double-publication / self-overlap, especially Entropy Ratio (under CSF).** The book must SUMMARIZE and point, not reproduce verbatim. Part IV in particular paraphrases and cites; it does not lift the CSF paper's proofs. Flag for the spec-auditor.
4. **Redundancy across folded papers** (cipher-maps and algebraic both touch cipher types; codec and cipher-maps both construct). The book must dedupe into one development; resolved at per-Part design.
5. **Concurrent edits to source papers by a parallel session.** The fold reads sources that may shift; re-read sources at draft time, do not cache stale.
6. **Scope creep in Part VI** (roadmap, not new results). Hold the line; new contributions belong in future papers.

## 12. Out of scope

- New original results (future papers; Part VI is a roadmap only).
- Full development of the Bernoulli model (Appendix A primer only).
- Library / implementation documentation (the `trapdoor_maps` library has its own).
- Full proofs of headline theorems already published elsewhere (cited, sketched).
- The Entropy Ratio's full compositional proofs (in the CSF paper).
- Extended application case studies beyond illustrative examples.

## 13. Success criteria

- `make` builds clean: no undefined references, no LaTeX warnings, landmines intact, no ORAM/crypto drift.
- ~150-220 pp body at proof-sketch depth with correct pointers to the standalone papers.
- The seven running threads are visibly carried across parts.
- Each part's argument flows; the folded papers are deduped into one coherent development.
- A reader finishes Part VI with a concrete picture of the next research program.
- Every shared definition matches the spine.

## 14. Next step

`/bookwright:design part1` to produce the per-Part design spec for The Paradigm (chapters 1-2, section tables, page budgets, reference map), then `/bookwright:plan ch01`. Per the sequencing above, Part I is drafted first to lock voice and threads, with Part II (the keystone) immediately after.
