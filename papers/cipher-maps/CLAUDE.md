# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

The core cipher maps paper: "Cipher Maps: Total Functions as Trapdoor Approximations." Single-author (Alexander Towell), LaTeX, currently in revision targeting **PoPETs 2027**. Created by merging two earlier papers (`algebraic_cipher_types` + `cipher_maps`); originals archived in `archive/`.

This directory is a git subtree of the `trapdoor-computing` monorepo (remote name: `cipher-maps`). Edit in place; push back with `git subtree push --prefix=papers/cipher-maps cipher-maps main`.

See the parent `CLAUDE.md` at `../../CLAUDE.md` for the conceptual framework, key concepts, core principles, and provenance rules. **Do not duplicate that content here, and do not re-derive the trapdoor formalism. Prior sessions drifted toward ORAM-style definitions, which is wrong.**

## Thesis

A cipher map is a total, trapdoored function on bit strings, characterized by four measurable properties: **totality** (the untrusted machine sees only a total function and cannot tell real inputs from noise), **representation uniformity** (δ), **correctness** (η), and **composability** (`η_total ≤ 1 − Π(1 − η_i)`). Totality is the foundational privacy mechanism, and security is *measurable rather than negligible* (QIF). Within this abstraction, the batch construction's design freedom collapses to a single **acceptance predicate**, whose allocation traces a (TV, length) leakage/size frontier: the space-optimal (Shannon) corner reaches the bound `-log₂(ε) + H(Y)` bits/element, while a *distinct* TV-optimal corner minimizes leakage (the two are not one simultaneous optimum). The δ-to-leakage confidentiality bound is proved self-contained (Fannes-Audenaert continuity plus the tight homophonic bound `TV < (|X|−1)/N`); the unification of Bloom filters, frequency-hiding encryption, and encrypted search follows from the abstraction rather than being the headline.

Full refined thesis and novelty claims live in `.papermill/state.md`.

## Build

```bash
make          # full build (pdflatex x3 + bibtex), copies PDF to repo root
make clean    # remove aux files
make cleanall # remove aux + PDFs
make watch    # rebuild on file changes (requires inotifywait)
```

Source is `paper/cipher_maps.tex` (~1460 lines) with `paper/references.bib` (~18 entries). The root `Makefile` delegates to `paper/` and copies the final PDF up; `paper/Makefile` can also be used directly (also has an `html` target via `tex2html`).

## Paper Structure

9 sections plus front-matter. Theorem numbering is `[section].[index]` (e.g., Theorem 6.2 lives in §6).

| § | Section | Content |
|---|---------|---------|
| 1 | Introduction | Setup, "what this is not" (vs ORAM/FHE/garbled circuits) |
| 2 | Related Work | PPE/SSE/SHE comparison; **needs leakage-abuse attacks + honey encryption** |
| 3 | The Cipher Map Abstraction | Preliminaries (ROM), tuple definition, batch vs online strategies, construction layers |
| 4 | Four Properties | Totality, Representation Uniformity (δ), Correctness (η), Composability; parameter decomposition |
| 5 | The Trusted/Untrusted Machine Model | Formal machine model, Definition 5.2 (informal security claims) |
| 6 | The Batch Construction | Info-theoretic lower bound, **acceptance predicates** (the unification), Algorithm 1, space optimality (Thm 6.2), construction time/bucketing, instantiations (HashSet, Entropy Map, Trapdoor Boolean Algebra) |
| 7 | Composition | AND-gate warm-up, general theorem (Thm 7.1, inequality form), chains, error by gate type |
| 8 | Representation Uniformity and Encoding Granularity | Joint vs component-wise encoding, entanglement parameter, compositional leakage |
| 9 | Discussion | Bernoulli relationship, algebraic structure, online construction, encrypted search application, open questions, "What This Framework Is Not" |

TikZ figures live in `paper/img/` (`fig_shmap.tex`, `fig_shs.tex`).

## Current State (as of Round 3 review, 2026-03-28)

**Recommendation: major-revision.** 0 critical, 6 major, 11 minor, 4 suggestions. Latest review at `.papermill/reviews/2026-03-28/review.md`; per-specialist reports in the same directory.

The 6 majors blocking PoPETs acceptance:

- **M1**: No formal security definition. Definition 5.2 makes claims without a security game.
- **M2**: No experimental evaluation. Even a Python prototype with timing would help; minimum is a "Concrete Instantiation" subsection comparing to Bloom/SSE baselines.
- **M3**: Missing leakage-abuse attack literature (Naveed/Islam/Cash) and honey encryption (Juels & Ristenpart 2014).
- **M4**: Composition formula equality/inequality inconsistency persists. Theorem 7.1 uses `≤`; Theorem 4.1, Corollary 7.1, and Discussion still use `=`.
- **M5**: Space optimality (Thm 6.2) conflates information-theoretic capacity with physical storage when `η > 0`.
- **M6**: ROM dependency pervasive but standard-model implications never discussed.

Earlier rounds (2026-03-19, 2026-03-26) are summarized in `.papermill/state.md`; full reports under `.papermill/reviews/`.

## Key Files

- `paper/cipher_maps.tex`: main source
- `paper/references.bib`: bibliography
- `paper/cipher_maps_original.tex`: pre-trapdoor-reframing snapshot for diffing
- `DESIGN-trapdoor-reframing.md`: approved design doc for the trapdoor paradigm shift (largely implemented)
- `.papermill/state.md`: project state, thesis, review history, venue candidates, related papers
- `.papermill/reviews/2026-03-28/`: most recent multi-agent review (8 specialists)
- `.papermill/proofs/proof-verification-2026-03-19.md`: proof-by-proof verification log
- `archive/`: original `algebraic_cipher_types` and `cipher_maps` papers (zipped) prior to merge

## Companion Repos

Relationships are spelled out in `.papermill/state.md` under `related_papers`. Three live in this monorepo:

- `../boolean-algebra-over-trapdoor-sets/`: online construction instantiated here
- `../algebraic-cipher-types/`: algebraic/functorial framing
- `../maximizing-confidentiality/`: entropy-ratio confidentiality measure (uses cipher maps)

Foundational error theory lives in `~/github/bernoulli/papers/` (`bernoulli_sets`, `bernoulli-hash-function`, `bernoulli_maps`). The Python implementation backing the experimental claims is `~/github/cipher-maps/` (PHF backend, `CipherBoolType`, `CipherSpace` chains).
