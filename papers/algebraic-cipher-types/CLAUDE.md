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
  main.tex         # monolithic LaTeX, ~1530 lines, all sections in one file
  references.bib   # bibliography; every entry must be cited (review M6)
  Makefile         # build recipe
  main.pdf         # checked in, kept current
.papermill/
  state.md         # thesis, novelty, review history, next actions (source of truth)
  reviews/<date>/  # multi-agent review reports (review.md plus per-specialist files)
```

There is no figures directory, no separate sections, no test suite, no source code. The paper draws its empirical results from the `cipher-maps` Python library at `../../src/cipher-maps/` (a sibling git repo inside the trapdoor-computing monorepo). That library is where re-running experiments happens, not here. The handshake is via `src/cipher-maps/PAPER-INTEGRATION.md` and `src/cipher-maps/docs/paper-numbers.md`: the library writes measured numbers to that markdown file, this paper ingests them.

## Paper-specific conventions

- **Thesis and structure live in `.papermill/state.md`.** Update it as work progresses, not just at milestones. The `review_history` block records each multi-agent review and what was addressed; the `Next Actions` section is the working to-do list. When refining the claim, preserve the previous claim under `previous_claim` with refinement notes.
- **Labels are stable contracts.** Theorems, propositions, definitions, and section labels (e.g. `thm:sum-impossibility`, `prop:typed-orbit`, `sec:cipher-bool`, `def:cipher-node`) are referenced from prose throughout the paper and from review reports. Restructuring should preserve label names even when sections are renamed; a label rename means hunting every `\Cref` and `\ref` site.
- **The paper has two distinct argument modes.** Sections 3 to 5 are theory (preliminaries, type-constructor trade-offs, orbit-closure framework). Section 6 is realization (expression-tree decomposition with cut-point synthesis). Section 7 is concrete instantiation and evaluation (cipher Boolean algebra). Edits should respect those modes: don't mix realization details into the orbit-closure section, don't mix experimental specifics into the theory.
- **Unicode em-dash characters are blocked by a global session hook on every file write.** Use colons, commas, periods, or parentheses instead. Inside `paper/main.tex` the LaTeX triple-hyphen `---` is fine and renders as an em-dash; the hook only blocks the literal Unicode U+2014 character.

## Recent work and current state

The paper went through five multi-agent review rounds between 2026-04-08 and 2026-04-30, plus a structural simplification on 2026-05-02. Trajectory of findings: Critical 2 → 1 → 0 → 0 → 0; Major 11 → 12 → 6 → 2 → 0. The paper is **content-complete** as of 2026-05-02, pending external blockers.

What landed across the rounds, in case you need to know why a section looks the way it does:

- **Restructure (2026-04-12)**: paper reorganized around "one principle, three instances" (sum-type impossibility, orbit closure, typed chains) with the body of §6 promoted to its own role.
- **Entropy-form §5.3 (2026-04-12)**: confidentiality bound rewritten as `H(X | view) >= H(X) - log2 |orbit|` (Theorem 5.3), with the set-form `conf >= 1 - |orbit|/|X|` (Corollary 5.4) following. The prior candidate-set definition was a tautology and is gone; do not reintroduce it.
- **Typed-chain generalization (2026-04-12)**: Proposition 5.5 carries arity `a_i` per chain step, with the recurrence `N_0 = m, N_{i+1} = N_i^{a_i}` and bound `sum N_i`. Unary (`a_i=1`) and single-value-start (`m=1`) cases recover earlier bounds as special cases.
- **Experimental rerun (2026-04-30)**: Tables 1, 2, 3 now report mean ± SD across 5 seeds. The driver is `src/cipher-maps/examples/experiment_paper_tables.py`; output goes to `src/cipher-maps/docs/paper-numbers.md`. Most striking finding: AND-chain FPR diverges from the Bernoulli prediction by 35× at k=3 and 12,160× at k=5, while OR chains stay within 10% of theory across k=1..5.
- **Cipher TM removal (2026-05-02)**: §6 now describes a single realization, expression-tree decomposition. The cipher TM was a degenerate special case (one cut point at the transition step, every other operation in plaintext) and was dropped as redundant once the @cipher_node + plain-Python framing was articulated. If you find yourself rebuilding it, stop and check that the expression-tree framing doesn't already cover what you want.

**Carry-forward open items** (external blockers, not content rewrites):

- **M7**: paper still uses `\documentclass[11pt]{article}`. If the venue is PLAS (the natural fit), swap to `\documentclass[sigconf,nonacm=true]{acmart}` and add CCS concepts. If IACR ePrint or arXiv, current class is fine.
- **M9**: three `@misc` self-citations in `references.bib` (`towell2026cipher`, `towell2026bernoulli`, `towell2026maxconf`) say "Manuscript in preparation". Posting to arXiv or IACR ePrint and updating the bib entries closes the reviewer concern about unverifiable load-bearing references.

**A useful operational pattern from the review history**: when a body-level fix is applied (e.g., a proposition's space bound updates from `O(|Q|·|Γ|)` to `O(|Q|²·|Γ|)`), sweep the abstract, intro contributions list, and conclusion for the same numerical claim. The 2026-04-29 verification round flagged two propagation defects from a body-only fix in the prior round; the lesson is mechanical.

## Companion repositories and where to look for things

- **`../cipher-maps/paper/`**: foundation paper (cipher map abstraction, four properties, batch construction). Most theorems in this paper cite into `[cite:towell2026cipher]`. If the foundation paper changes a definition or numbering, this paper's preliminaries (§3) are the first thing to reconcile.
- **`../../src/cipher-maps/`**: Python implementation backing the Section 7 experiments (PHF-backed cipher maps, the cipher Boolean type with AND/OR/NOT, `@cipher_node` decorator, 20 Newsgroups benchmark). All empirical numbers in §7.3 trace back to commits in that repo. Re-running the paper-side benchmarks: `cd src/cipher-maps && PYTHONPATH=. python examples/experiment_paper_tables.py --n-seeds 5 --n-docs 5000 --n-trials-fpr 1000 --out docs/paper-numbers.md` (~14 minutes single-threaded). The library has its own `PAPER-INTEGRATION.md` documenting the cross-paper handshake.
- **`~/github/bernoulli/papers/bernoulli_data_type/`**: companion paper on the accuracy side (Kronecker factorization of confusion matrices, error propagation through type constructors). Cited as `[cite:towell2026bernoulli]`.
- **`../../.archive/algebraic_cipher_types-legacy/`**: the 2019 to 2022 C++ notebook this paper was extracted from. Source of original ideas (cipher Booleans, cipher unions, cipher TM). Archived 2026-04-29; see its `ARCHIVED.md` for provenance and the idea-map. Do not edit; do not build. Companion living roadmap is `../../FUTURE-RESEARCH.md`.
- **`../maximizing-confidentiality/`**: sibling paper using the entropy-ratio framework. Cited as `[cite:towell2026maxconf]`.
