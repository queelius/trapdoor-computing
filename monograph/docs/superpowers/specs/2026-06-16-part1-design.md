# Design: Part I (The Paradigm) of the Trapdoor Computing monograph

**Author:** Alexander Towell
**Date:** 2026-06-16
**Status:** Design (pre-implementation)
**Parent spec:** `docs/superpowers/specs/2026-06-10-master-design.md`
**Scope:** Section-level outline for chapters 1-2 (Part I, ~22-24 pp). Authoritative for the chapter plans that draft them.

## 1. Purpose

Part I makes the case for the paradigm before any formalism arrives. By the end of chapter 2 a reader knows what trapdoor computing is (computing on opaque encodings, with confidentiality that is measured rather than assumed negligible), what it is *not* (ORAM, FHE, garbled circuits, leaky searchable encryption), and where its privacy actually comes from (one-way hashing plus uniform representation, not access-pattern hiding). No cipher map tuple, no theorem: those land in Part II. Part I's job is the vision, the central question, and the provenance guardrail.

Inherits from the master spec: researcher / graduate audience; concise research-monograph voice, intuition-first; no exercises; chapter-end Notes and Provenance; minimal notebooks; the spine (`../../formalism/cipher-map-formalism.md`) is the authority on every shared definition; the corrected (round-2) confidentiality framing (image-relative delta, `H* = log2|im(enc)|`) is canonical, NOT the older ambient-`B^n` form that the foundations blog and earlier paper drafts carry.

## 2. Settled decisions (this spec)

Three choices fixed in the 2026-06-16 design Q&A:

- **(Ch 1 opening) Concrete scenario first.** Open on the "oblivious service" (a search engine that cannot read your queries or its own answers), then generalize to the paradigm and the central question. This sets the voice and doubles as the hook for the extracted position paper.
- **(Ch 2 treatment) Crisp positioning plus a comparison table.** A short paragraph per alternative and a one-screen table (what each hides / its cost / how it differs), kept to ~10 pp. The chapter is the provenance guardrail; it must be fair to the alternatives, never "ours is strictly better."
- **(Posture) Lift-ready.** Part I is written to be liftable as a standalone position/overview paper (the program's missing "paradigm paper"). Body stays self-contained; forward-references into later parts go in footnotes, not in the running argument. Accept a little redundancy in the book in exchange for a clean lift.

## 3. Cross-cutting commitments (both chapters)

### 3.1 Running threads introduced here

Two of the master spec's seven threads start in Part I and must be planted cleanly so later parts can call back:

| Thread | Planted | First callback (out of Part I) |
|---|---|---|
| Trusted/untrusted lens (who holds enc/dec) | Ch 1.1 (informal) | Ch 3 (formalized) |
| Measurable-not-negligible (QIF, not reductions) | Ch 1.3 | Ch 4 (delta), Ch 9 |

Totality-as-privacy is *teased* in Ch 1.2 (the untrusted machine cannot tell real from filler) but formally introduced in Ch 3; the two-scale confidentiality thread is only named, not developed, until Ch 8-10. Part I plants, it does not pay off.

### 3.2 Notation discipline

Part I is prose-first and uses almost no symbols. The few it needs (`enc`, `dec`, the trusted/untrusted machines `T`/`U`, an informal "delta-close to uniform") come from `notation.sty` and are introduced in a light sidebar at first use, not in a formal table. No `\B^n`-heavy displays; those belong to Part II. Any symbol used must match the spine section 8 table.

### 3.3 No theorems, no proofs

Part I states no theorem environments. The "four properties" appear in Ch 1 as a named prose list (a preview), not as a numbered definition; the numbered Definition lives in Part II. This keeps Part I liftable and keeps the formal load where the master spec put it.

### 3.4 Provenance is the whole point of Ch 2

Chapter 2 is the book's no-ORAM-drift guardrail. Its existence plus the spine-authority rule is what protects every later chapter from sliding into access-pattern-indistinguishability language. The chapter should read as the canonical "what this is not" statement that the *papers* can cite back to (today that statement is scattered across cipher-maps sec 1 and the spine).

## 4. Chapter 1: Computing on Opaque Encodings (~12 pp)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 1.1 | The oblivious service | ~3 | fresh; foundations/ framing | Open on the scenario: a search engine that cannot read queries or answers. Introduce the trusted/untrusted split informally (who holds the decoder). The image of opaque bits through opaque lookup tables. Name the object at the end: the *cipher map*. Plants the trusted/untrusted thread. |
| 1.2 | What the untrusted machine sees | ~3 | spine sec 1; cipher-maps sec 5 | The central question: how much does the untrusted machine learn? Totality as the first privacy mechanism (every input yields output; filler is indistinguishable from real). The four things the untrusted machine cannot do: decode, distinguish real from filler, determine the domain, tell a correct result from noise. Must match the spine's list exactly. |
| 1.3 | Measured, not negligible | ~3 | spine; QIF (Smith 2009, Alvim et al. 2020) | The stance that separates this from cryptography-as-usual: confidentiality is a *quantity* you measure (an entropy ratio, teased), not an asymptotic negligible-advantage claim. Contrast the two security idioms honestly. Plants the measurable-not-negligible thread. Use the corrected image-relative framing when teasing the entropy ratio. |
| 1.4 | The shape of the book | ~2 | master spec sec 1 | The through-line in one place: one abstraction unifies a family of constructions; confidentiality lives at two scales; composition is predictable; privacy is hash plus uniformity. A short roadmap of the six parts. Forward-pointers in footnotes only (lift-ready). |
| 1.5 | Notes and Provenance | ~1 | fresh | The authentic 2023-2024 `foundations/` sources (bernoulli-model, trapdoor-boolean-algebra with its erratum, entropy-maps, noisy-gates); QIF citations; the note that this is a synthesis whose formal development and full proofs live in later parts and the standalone papers. |

### Chapter 1 harvest notes

- **Extraction.** Sections 1.1-1.4 are the spine of the standalone position paper. Write them so 1.1-1.3 stand without 1.4's roadmap (the paper version drops the book roadmap and adds a one-paragraph contributions list).
- **Consistency to reconcile while drafting.** (a) The `foundations/` blog framing predates the round-2 confidentiality corrections; the 1.3 entropy-ratio tease must use image-relative delta, not the old ambient `B^n` form (cross-paper item C-11). (b) The 1.2 "four cannots" list must be verified verbatim against spine sec 1 and cipher-maps sec 5, do not paraphrase loosely. Flag any divergence to back-port.

## 5. Chapter 2: What Trapdoor Computing Is Not (~10 pp)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 2.1 | Where the privacy comes from | ~2 | spine; cipher-maps sec 1 | The positive claim, stated sharply, that frames every contrast: privacy comes from one-way hashing and uniform representation, not from hiding access patterns and not from a hardness reduction. The guardrail thesis. |
| 2.2 | Not ORAM | ~1.5 | Goldreich-Ostrovsky; Path ORAM | ORAM hides the *access pattern*; trapdoor computing does not (the untrusted machine sees which tables are touched). It hides *meaning*. Different threat model, not a weaker ORAM. |
| 2.3 | Not FHE, not garbled circuits | ~2 | Gentry 2009; Yao | FHE computes *exactly* on ciphertexts at large cost; cipher maps *approximate* (measurably, with correctness eta) on a *static, reusable* total function. Garbled circuits are one-shot and per-gate; cipher maps are reusable lookup tables. Be fair: these solve different problems. |
| 2.4 | Not (just) searchable or property-preserving encryption | ~2 | Song-Wagner-Perrig; Curtmola et al.; Naveed/Islam/Cash; Lacharite-Paterson | SSE/PPE leak through index structure and preserved relations (the leakage-abuse line). Here, leakage is the *measured* entropy ratio, and frequency hiding is *structural* (uniform representation), the same lever as frequency-smoothing encryption but realized as a property of a total function, not an online protocol. |
| 2.5 | The comparison, and the guardrail | ~1.5 | synthesis | The one-screen table (approach / what it hides / cost / how trapdoor computing differs). Then the explicit guardrail: this book imports no ORAM, differential-privacy, simulation-based, or game-based definitions; the spine is the authority. This is the "do not drift" anchor the rest of the book leans on. |
| 2.6 | Notes and Provenance | ~1 | fresh | Citations for every alternative above; the `ECOSYSTEM-TRIAGE.md` pointer (AUTHENTIC / CLAUDE-EXPANDED / DRIFTED); the note that prior sessions drifted toward ORAM-style indistinguishability and that this chapter is the correction. |

### Chapter 2 harvest notes

- **Extraction.** The comparison table and 2.1's privacy-source claim are the strongest single artifact for the position paper; they are also the canonical "what this is not" the papers should cite back to (consider promoting the table into the spine as a shared figure).
- **Consistency / fairness risk.** Do NOT echo the speculative "FHE leaks side channels" line from old notes; keep every contrast about threat-model *difference*, not about an alternative being worse. The 2.4 frequency-hiding contrast must use `K(x) propto D(x)` (never the inverted `1/D(x)` that the authentic `trapdoor-boolean-algebra.md` carries with an erratum).

## 6. Forward / backward reference map

- **Backward:** none; Part I opens the book.
- **Forward (footnote pointers only, per the lift-ready posture):** cipher map tuple and the formal four properties -> Part II (Ch 3-4); the entropy ratio and the two scales -> Part IV (Ch 9-10); the static reusable construction -> Part V; the Bernoulli error model under correctness -> Appendix A.
- **Threads out:** trusted/untrusted (planted 1.1) and measurable-not-negligible (planted 1.3) are both first re-entered in Part II / Part IV per the master threads table.

## 7. Page budget

Ch 1 ~12 pp (3+3+3+2+1), Ch 2 ~10 pp (2+1.5+2+2+1.5+1). Part I body ~22 pp, within the master's ~24 pp allowance. If Ch 2 runs long, the table absorbs material that would otherwise be prose (the table is load-bearing, not decorative).

## 8. Sequencing for the chapter plans

1. `/bookwright:plan ch01` first: it sets the voice, so the quality-auditor reads it before anything else in the book. Re-read `foundations/` and spine sec 1 at plan time for the exact trusted/untrusted model and the four-cannots list.
2. `/bookwright:plan ch02` next: re-read cipher-maps sec 1 and the spine's "what this is not"; pull the external comparison citations from the Entropy Ratio `references.bib` where they already exist (lacharite2018frequency, cash2015leakage, naveed2015inference, islam2012access) and add ORAM/FHE/garbled keys.

## 9. Open action items

- Verify the 1.2 "four cannots" verbatim against the spine before drafting (consistency).
- Confirm the 1.3 entropy-ratio tease uses image-relative `H* = log2|im(enc)|` (C-11), not ambient `n`.
- Draft the Ch 2 comparison-table rows against a current source for each alternative; do not misstate ORAM/FHE costs.
- Open a `harvest.md` log for Part I (extraction candidate + back-port findings) so the cross-paper consistency work the user wants is captured as drafting proceeds, not lost.

## 10. Risks (part-specific)

1. **Unfair contrasts in Ch 2.** Overclaiming against ORAM/FHE reads as a strawman and undercuts the guardrail. Keep contrasts about threat-model difference. (High attention.)
2. **Old-framing leakage.** The authentic `foundations/` blog carries the pre-correction confidentiality form and the inverted homophonic erratum; either could seep into Ch 1.3 / Ch 2.4. Reconcile against the spine. (This is exactly the cross-paper value of drafting the book.)
3. **Lift-ready redundancy creeping into the body** rather than footnotes. Forward-pointers go in footnotes; the running text stays clean.
4. **Voice miss.** Part I sets the book's voice; if the opening is flat the auditor will flag it. The concrete-scenario opening is chosen precisely to de-risk this.

## 11. Out of scope (Part I)

The cipher map tuple and any numbered definition (Part II); any theorem or proof (Part II onward); the actual constructions (Part V); the formal QIF measures and the Fannes bridge (Part IV); the Bernoulli error model beyond a one-line mention (Appendix A).

## 12. Success criteria

- The voice is locked: the quality-auditor approves the Ch 1 opening as the book's tone.
- The two threads (trusted/untrusted, measurable-not-negligible) are planted and named.
- Ch 2 is a fair, citable "what it is not" with the comparison table and the explicit guardrail; no ORAM/crypto-formalism drift; the spine-authority rule is stated.
- Part I reads self-contained (a reader who stops after Ch 2 has the paradigm), confirming the lift-ready posture.
- `make` builds Part I clean; the harvest log records at least the extraction candidate and any back-port findings.

## 13. Next step

`/bookwright:plan ch01` (Computing on Opaque Encodings), then `/bookwright:plan ch02`, then draft. Part I is the voice-setting pass; Part II (the keystone) follows, with Part IV pulled forward in the interleave if the Entropy Ratio paper work wants the cross-check.
