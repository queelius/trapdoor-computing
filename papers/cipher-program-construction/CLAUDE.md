# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Scope of this file

Single-paper directory inside the `trapdoor-computing` monorepo. Paradigm-level guidance (cipher maps, four properties, the not-ORAM/FHE rule, the two-scale confidentiality framing, the formalism source-of-truth) lives in `../../CLAUDE.md` and is auto-loaded; do not restate it. This file covers what is specific to this paper.

## What this paper is

**Realizing Cipher Programs**: how to turn an ordinary program into a composition of cipher maps the untrusted machine can run, and what that realization leaks. The subject is *whole-program realization*: cut points, upward propagation of ciphering, control-flow obliviousness, and automatic rewriting.

**Spun out of `../algebraic-cipher-types` on 2026-06-03.** Section 3 is the migrated former §6 of that paper. The split was deliberate: algebraic-cipher-types is about cipher *types* and their leakage (it constructs cipher maps only to analyze trade-offs and never evaluates whole-program realization), so the realization material was a distraction there and is the natural subject here.

**Scope boundaries:**
- Single-cipher-map *construction* (PHF/batch, space, the four properties) belongs to the foundation paper `towell2026cipher` (its §6). Cite it; do not re-derive.
- The cipher-*type* algebra, sum-type impossibility, orbit-closure bound, and typed chains belong to `towell2026algebraic`. Cite them; do not re-derive.
- This paper owns: the propagation law, the no-oblivious-short-circuit result and control-flow regimes, the cost model, the decision space, and the tracing rewriter.

## Build

```bash
cd paper && make           # pdflatex + bibtex + pdflatex x2
```
Sanity-check: `grep -iE "warning|undefined|multiply" paper/main.log | grep -v "^Package:"` (clean build emits nothing). Builds at 8 pages.

## Status (important)

This is a **scaffold**, not a finished draft. `stage: scaffold` in `.papermill/state.md`. §1/§2/§4/§5 are freshly written but thin; §3 is migrated and in places still reads as "a section in another paper" (it was). It has no git remote, no `mf` paper_db entry, and is in no series. Before investing in a full draft, decide whether it is a real submission target (see `.papermill/state.md` Next Actions).

## Conventions

- Shared macros match the rest of the family: `\fhat`, `\enc`, `\dec`, `\cipher{X}`, `\cipherS{X}{s}`, `\orbitF`, `\B`.
- Labels in the migrated §3 are stable contracts referenced from prose: `def:cipher-node`, `def:cut-point`, `fig:cipher-tree`, `prop:no-short-circuit`, `rem:mux-cost`, `rem:cipher-propagation`, `sec:branching`, `sec:tm-vs-tree`, `sec:cipher-programs`, `sec:realizing`.
- Unicode em-dash is blocked by a global session hook on file writes; use colons/commas/parentheses, or LaTeX `---` inside `main.tex`.

## Companion repositories

- **`../algebraic-cipher-types/`**: parent. Owns the type algebra, sum impossibility (`thm:sum-impossibility`), orbit bound, typed chains. §3 here cross-references it as `[cite:towell2026algebraic]`.
- **`../cipher-maps/paper/`**: foundation. Cipher map four properties + batch/PHF construction. `[cite:towell2026cipher]`.
- **`../../src/cipher-maps/`**: Python reference implementation; the `@cipher_node` tracing rewriter described in §4 should be reconciled against it (and a commit/tag cited) before the rewriter claims are finalized.
