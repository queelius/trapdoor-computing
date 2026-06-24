# Design: Part V (Constructions)

**Author:** Alexander Towell
**Date:** 2026-06-18
**Status:** Design (pre-implementation)
**Parent spec:** `docs/superpowers/specs/2026-06-10-master-design.md`
**Scope:** Section-level outline for chapters 11-13 (Part V, ~36 pp budget; expect ~15-18 pp at the established density). Authoritative for the ch11-13 implementation plans.

## 1. Purpose

Parts II-IV are abstract: the cipher map, its properties, its algebra, its confidentiality, all specified without committing to how a cipher map is actually built. Part V builds them. It presents three construction families, each realizing the acceptance predicate of \Cref{sec:acceptance} a different way, and shows that the abstract knobs (`eta`, `delta`, the frequency-hiding of \Cref{ch:marginal-scale}, the defenses of \Cref{sec:defenses}) become concrete engineering choices with measured costs. By the end the reader can point to running code, not just theorems: a hash-based batch construction, a GF(2)-linear retrieval structure, and the closure machinery that turns cipher maps into data structures, rekeying, and whole programs.

Inherits from the master spec: research-monograph voice; technical-part density with figures + worked examples; chapter-end Notes and Provenance; the spine is the authority on shared definitions.

## 2. Settled decisions (this spec)

- **Proof depth varies by source status.** Ch 11 (cipher-maps §6, consolidated into the book in Part II) realizes the construction concretely and cites Part II for the abstraction; the space/FPR results are stated, not re-proved. Ch 12 (`codec-controlled-retrieval`, a live ACM TOPS submission) SUMMARIZES, state the construction and the threshold/frequency-hiding theorems with intuition and a pointer, do NOT reproduce proofs (same posture as Part IV's Entropy Ratio summary). Ch 13 folds three drafts (`cipher-rekeying`, `cipher-closures`, `cipher-program-construction`) more fully, but keeps to the conceptual results (the closure abstraction, the code-data duality, the infectious-ciphering and control-flow points), with pointers for the formal naturality / cost theorems.
- **The watchlist toy is realized, then retired.** The membership map that threaded Parts II-IV gets its concrete construction in Ch 11 (a HashSet over the four names) and a GF(2) realization in Ch 12, closing the loop from abstraction to running code. Ch 13's material is structural and uses small program/data-structure examples instead.
- **The library is real.** Ch 11 references the actual `trapdoor_maps` Python library (`src/cipher-maps/`) that backs the experimental claims of the cipher-maps and Entropy Ratio papers; the chapter points to it as the canonical implementation, not pseudocode.

## 3. Cross-cutting commitments

### 3.1 Running threads

| Thread | Action in Part V |
|---|---|
| The acceptance predicate | **Realized** three ways: PHF seed search (Ch 11), GF(2) span (Ch 12), closure dispatch (Ch 13) |
| Space-accuracy duality | Ch 11: the `-log2(eps)+H(Y)` bound achieved by the Bernoulli hash construction |
| Frequency-hiding (Ch 9 levers) | Ch 12: a STRUCTURAL alternative to homophonic multiplicity, at zero per-query cost |
| Coincidence oracle (Ch 10 C2) | Ch 12: the opposite-pull, concentrated codec defends C2, flat defends FreqDist; a tunable frontier |
| Sum-type impossibility (Ch 7) | Ch 13: control flow IS untrusted dispatch on a sum; the conditional must leak the test or evaluate both branches |
| Orbit closure (Ch 8) | Ch 13: designed-orbit data structures leak LENGTH through the orbit |
| Values-are-maps / cipher exponential (Ch 3, 7) | Ch 13: the code-data duality, the cipher closure as universal carrier |

### 3.2 Two construction strategies, made concrete

\Cref{sec:strategies} split constructions into batch (seed search) and online (algebraic). Part V populates both: Ch 11 is the canonical batch construction (PHF seed search); Ch 12 is a linear-algebraic construction whose frequency-hiding is structural, not searched; Ch 13's closures are online (read off a hash structure). The part is where that abstract dichotomy becomes three real engineering paths.

## 4. Chapter 11: Hash-Based Constructions (~12 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 11.1 | The perfect-hash backend | ~3 | cipher-maps §6; src/cipher-maps | The PHF as the realization of `f-hat`: a minimal perfect hash maps in-domain keys to codeword slots; the seed search of \Cref{sec:strategies} made concrete. The `trapdoor_maps` library named as the canonical implementation. |
| 11.2 | HashSet and the entropy map | ~3 | cipher-maps §6 | The two instantiations: HashSet (membership, `eta=0`, the acceptance partition with one region) and the entropy map (`eta`-tunable, value regions sized to the output distribution, `mu=H(Y)`). The watchlist realized as a HashSet over the four names. |
| 11.3 | Correctness and space, realized | ~3 | cipher-maps §6; bernoulli base | `eta` IS the Bernoulli false-negative rate; the realized space hits the `-log2(eps)+H(Y)` duality of \Cref{prop:space-duality}; the seed-search cost / FPR trade. Cite Part II for the abstract bound, show the concrete numbers. |
| 11.4 | Notes and Provenance | ~1 | fresh | cipher-maps §6 owner; the library is the implementation of record. |

## 5. Chapter 12: GF(2)-Linear Retrieval (~12 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 12.1 | Retrieval without a membership gate | ~2 | codec-controlled-retrieval §1-2 | Ribbon / XOR / Bloomier retrieval returns a value for EVERY key: the member's value, and "junk" for non-members. The linear-retrieval view: a query is a GF(2)-linear combination of solution rows. Connects to \Cref{def:totality} (totality, now linear-algebraic). |
| 12.2 | Junk is designable | ~3 | codec-controlled-retrieval §3 (`thm:support`) | The headline: the non-member output is uniform on the GF(2) span `W` of the stored codewords, so a PUBLIC value codec fixes its distribution, independent of how often each value was stored. SUMMARIZE + pointer. |
| 12.3 | The rank threshold | ~3 | codec-controlled-retrieval (`thm:control`, `thm:cogirth`) | Full codec control iff the codewords are transversal to the codec's class partition, `rank(proj|_W) = log2 K`: a STEP in an integer rank, no graded middle. The matroid cogirth `d*` as the erasure-robustness budget. Statement + intuition + pointer. |
| 12.4 | Frequency-hiding at zero per-query cost | ~3 | codec-controlled-retrieval (FreqDist game) | The structural confidentiality payoff: in the idealized model the non-member law is independent of stored frequencies, so the FreqDist adversary has advantage exactly zero; in the real construction within TV `delta(p0)+delta(p1)`, a small scale-independent redundancy term. A STRUCTURAL alternative to Ch 9's homophonic multiplicity, paid once at build, not per query. The coincidence-oracle opposite-pull (Ch 10 C2): concentrated vs flat, the tunable frontier. |
| 12.5 | Notes and Provenance | ~1 | fresh | codec paper (TOPS) owner; SUMMARIZE. The header-only C++23 implementation and the at-scale empirical checks. |

## 6. Chapter 13: Rekeying, Closures, and Programs (~12 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 13.1 | The cipher closure | ~2 | cipher-closures §3 | The unifying abstraction: a procedure that captures a secret and exposes an operation interface. Cipher values, cipher maps, and cipher data structures are all special cases (the SICP closures-as-data-structures lens). |
| 13.2 | Code is data, data is code | ~3 | cipher-closures §4-7 | The duality: a cipher data structure (pair, list, map) is ONE cipher map, its interface folded into a query tag (the dispatch pattern, "data is code"); a cipher map is a point of the cipher exponential `cipher{A->B}` ("code is data"). Designed orbits (sequential structure via hash chains) and their length leakage (callback \Cref{thm:orbit-bound}). |
| 13.3 | Rekeying | ~3 | cipher-rekeying §3-5 | Rotating the captured secret without plaintext: rekeying maps a cipher value under one secret to one under another, preserving the latent value. The rekeying functor is itself a cipher map (the untrusted machine applies it); naturality (rekeying commutes with operations). Statement + pointer for the cost theorem. |
| 13.4 | Programs as cipher-map compositions | ~3 | cipher-program-construction §3-4 | Realizing a program as a composition of cipher maps: ciphering is INFECTIOUS (a cut is upward-closed; one cut can cipher a whole single-rooted program); control flow IS untrusted dispatch on a sum type (callback \Cref{thm:sum-impossibility}): a conditional must either expose which branch ran (cheap, leaks the test) or hide it (expensive, evaluate both branches). |
| 13.5 | Notes and Provenance | ~1 | fresh | Three papers (rekeying, closures, program-construction); the cipher closure unifies them. |

## 7. Forward / backward reference map

- **Backward (real `\cref`):** Ch 11 realizes `sec:acceptance`, `sec:strategies`, `prop:space-duality`, `def:correctness`; Ch 12.1 builds on `def:totality`; Ch 12.4 contrasts Ch 9's `tab:levers` and recalls Ch 10's coincidence oracle; Ch 13.2 recalls `thm:orbit-bound` and `rem:values-are-maps`/`sec:cipher-type`; Ch 13.4 recalls `thm:sum-impossibility` and `thm:composition`.
- **Forward (footnote, part labels):** open problems `part:frontiers`.
- **External pointers (owners):** `\cite{towell2026cipher}` (Ch 11), `\cite{towell2026codec}` (Ch 12), the rekeying/closures/program papers (Ch 13, add bibkeys).
- **Within Part V:** ch11 -> ch12 -> ch13.

## 8. Page budget

Ch 11 ~12, Ch 12 ~12, Ch 13 ~12 (master ~36). At density expect ~5-6 pp/chapter, ~16-18 pp total. Ch 12 (codec) and Ch 13 (three-paper fold) get the most care; Ch 11 leans on Part II for the abstraction and stays concrete.

## 9. Harvest

- **Cross-cut (genuine):** the GF(2)-codec frequency-hiding (Ch 12) is a *structural* alternative to homophonic multiplicity (Ch 9), trading per-query cost for a one-time build and a rank condition; the two together are a clean "two ways to hide frequency" statement worth surfacing across the codec and Entropy Ratio papers. And the cipher closure (Ch 13.1) is a candidate unifying abstraction to promote into the spine (it subsumes cipher values, maps, data structures, and the secret).
- **Back-port candidates:** the code-data duality (Ch 13.2) as a clean statement; the infectious-ciphering / control-flow-is-sum-dispatch observation (Ch 13.4) ties `cipher-program-construction` directly to `thm:sum-impossibility`, a cross-paper link worth noting in both.
- **New bibkeys needed:** `towell2026codec`, `towell2026rekeying`, `towell2026closures`, `towell2026programs` (verify exact keys against each paper's `.bib`).

## 10. Risks (part-specific)

1. **Self-overlap with the codec TOPS submission (Ch 12).** SUMMARIZE; state the threshold and frequency-hiding theorems, do not reproduce the rank/cogirth proofs.
2. **Ch 13 breadth.** Three papers in one chapter; keep to the unifying spine (the cipher closure) and the three load-bearing observations (duality, rekeying-as-natural-transformation, control-flow-is-sum-dispatch); resist drafting each paper in full.
3. **Overlap with Ch 5.** Ch 11 realizes what Ch 5 abstracted; cite Ch 5, do not re-derive the acceptance predicate or the space duality, show the concrete construction.
4. **Codec frequency-hiding vs Ch 9 conflation.** They are different mechanisms (structural span vs homophonic multiplicity); state the contrast, do not equate.

## 11. Out of scope (Part V)

The full codec rank/cogirth proofs (cited, TOPS paper); the full rekeying cost and program-rewriting theory (cited, in the three Ch-13 papers); the open problems (Part VI); a tutorial on perfect hashing (cited to the Bernoulli / cipher-maps base).

## 12. Success criteria

- Three construction families realized: PHF batch (Ch 11), GF(2)-linear (Ch 12), closures (Ch 13).
- The codec's non-member-output-on-span-W and the rank threshold stated correctly, with frequency-hiding at zero per-query cost contrasted against Ch 9's per-query homophonic lever.
- Ch 13 unified by the cipher closure; control flow tied back to `thm:sum-impossibility`; designed-orbit length leakage tied to `thm:orbit-bound`.
- The watchlist toy realized concretely (HashSet, Ch 11) and closes the abstraction-to-code loop.
- `make` builds Part V clean; bibkeys added; `HARVEST.md` Part V filled.

## 13. Next step

Draft ch11 -> ch12 -> ch13 from this spec. After Part V, only Part VI (Frontiers) remains, the open-problems close, seeded by the 2026-06-09 ecosystem survey and EC-2.
