# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Scope of this file

This is a single-paper directory inside the `trapdoor-computing` monorepo. Paradigm-level guidance (cipher maps, four properties, the "this is not ORAM/FHE/simulation-based" rule, the Bernoulli relationship, the formalism source-of-truth) lives in `../../CLAUDE.md` and is auto-loaded; do not restate it here. This file covers what is specific to this paper.

## Build

```bash
cd paper && make             # pdflatex + bibtex + pdflatex x2 (no latexmk)
cd paper && make clean       # aux files only; keeps PDF
cd paper && make cleanall    # also removes main.pdf
```

The Makefile has no `quick` target. For an iterative single-pass build, run `pdflatex main` directly. The build is fast (under 5s), but bib changes require `bibtex main` between `pdflatex` runs to refresh `.bbl`.

After editing, sanity-check the build with:
```bash
grep -iE "warning|undefined|multiply" paper/main.log | grep -v "^Package:"
```
A clean build emits no lines matching that pattern. Page count and undefined-reference status are the cheapest signals that nothing structural broke.

## Layout

```
paper/
  main.tex         # monolithic LaTeX, ~1460 lines, all sections in one file
  references.bib   # bibliography; every entry should be cited (review M6)
  Makefile         # build recipe
  main.pdf         # checked in, kept current
.papermill/
  state.md         # thesis, novelty, review history, next actions (source of truth)
  reviews/<date>/  # multi-agent review reports (review.md plus per-specialist files)
```

There is no figures directory, no separate sections, no test suite, no source code. The paper draws its empirical results from the `cipher-maps` Python library at `~/github/cipher-maps/`. That library is where re-running experiments happens, not here.

## Paper-specific conventions

- **Thesis and structure live in `.papermill/state.md`.** Update it as work progresses, not just at milestones. The `review_history` block records each multi-agent review and what was addressed; the `Next Actions` section is the working to-do list. When refining the claim, preserve the previous claim under `previous_claim` with refinement notes.
- **Labels are stable contracts.** Theorems, propositions, definitions, and section labels (e.g. `thm:sum-impossibility`, `prop:typed-orbit`, `sec:cipher-bool`, `def:cipher-node`) are referenced from prose throughout the paper and from review reports. Restructuring should preserve label names even when sections are renamed; a label rename means hunting every `\Cref` and `\ref` site.
- **The paper has two distinct argument modes.** Sections 3 to 5 are theory (preliminaries, type-constructor trade-offs, orbit-closure framework). Section 6 is realization (cipher TM and expression-tree decomposition with cut-point synthesis). Section 7 is concrete instantiation and evaluation (cipher Boolean algebra). Edits should respect those modes: don't mix realization details into the orbit-closure section, don't mix experimental specifics into the theory.
- **Unicode em-dash characters are blocked by a global session hook on every file write.** Use colons, commas, periods, or parentheses instead. Inside `paper/main.tex` the LaTeX triple-hyphen `---` is fine and renders as an em-dash; the hook only blocks the literal Unicode U+2014 character.

## Recent work and current state

- **2026-04-12 restructure** reorganized the paper around "one principle with three instances plus two realizations" (the prior framing was "three independent results"). Cipher TM was demoted from a full headline section to a brief subsection of §6 Realizing Cipher Programs, with expression-tree decomposition (the practical `@cipher_node` realization) elevated alongside it.
- **2026-04-12 second-round fixes** (post-review): the §5.3 confidentiality bound was rewritten in entropy form (`H(X | view) >= H(X) - log2 |orbit|`) as the primary theorem, with the set-form bound as a corollary; the typed-chain proposition was generalized to arbitrary arity with the recurrence `N_{i+1} = N_i^{a_i}`; cipher TM definition cleaned to store `(state, symbol)` as one cipher value per cell; §6.3 cut-point synthesis fleshed out with a formal definition and a regex-matching worked example; bibliography expanded from 10 to 21 cites.
- **Open from the 2026-04-12 review**: M2/M3/M4/M5 (experimental baselines, error bars, FPR-vs-chain-length Table 2, granularity space measurements; these require re-running the Boolean search in `~/github/cipher-maps/`); M7 (document class swap to `acmart` sigconf if PLAS committed); M9 (post `towell2026cipher` and `towell2026bernoulli` publicly, or expand §3 Preliminaries to be self-contained).

## Companion repositories and where to look for things

- **`../cipher-maps/paper/`**: foundation paper (cipher map abstraction, four properties, batch construction). Most theorems in this paper cite into `[cite:towell2026cipher]`. If the foundation paper changes a definition or numbering, this paper's preliminaries (§3) are the first thing to reconcile.
- **`~/github/cipher-maps/`**: Python implementation backing the Section 7 experiments (PHF-backed cipher maps, the cipher Boolean type with AND/OR/NOT, `@cipher_node` decorator, 20 Newsgroups benchmark). All empirical numbers in §7.3 trace back to commits in that repo.
- **`~/github/bernoulli/papers/bernoulli_data_type/`**: companion paper on the accuracy side (Kronecker factorization of confusion matrices, error propagation through type constructors). Cited as `[cite:towell2026bernoulli]`.
- **`../../.archive/algebraic_cipher_types-legacy/`**: the 2019 to 2022 C++ notebook this paper was extracted from. Source of original ideas (cipher Booleans, cipher unions, cipher TM). Archived 2026-04-29; see its `ARCHIVED.md` for provenance and the idea-map. Do not edit; do not build. Companion living roadmap is `../../FUTURE-RESEARCH.md`.
- **`../maximizing-confidentiality/`**: sibling paper using the entropy-ratio framework. Cited as `[cite:towell2026maxconf]`.
