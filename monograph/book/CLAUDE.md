# CLAUDE.md (monograph: book/)

Guidance for Claude Code and the bookwright drafting agents (section-writer,
notebook-author, math-auditor, cross-ref-auditor, spec/quality auditors)
working in this monograph. Read this before drafting any chapter.

## What this is

"Trapdoor Computing: Computing on Opaque Encodings" - a research monograph
that consolidates the trapdoor-computing paper family into one coherent
treatment and closes with an open-problems frontier. Audience: researchers
and graduate students in security, cryptography, and information theory.

The parent repository is `trapdoor-computing/`; its root `CLAUDE.md` holds
the conceptual framework, key concepts, and provenance rules. The canonical
source of truth for shared definitions is `../../formalism/cipher-map-formalism.md`
(the reconciled spine). When this book and the spine disagree on a shared
definition, the spine wins.

## Build

```bash
cd book && make        # pdflatex x1 + biber + pdflatex x2
make clean             # remove aux files
make cleanall          # also remove the PDF
```

`make` must exit clean before any chapter is considered done. The build is
currently a scaffold: six empty parts plus one stub chapter
(`chapters/ch01-overview.tex`), and it compiles end to end including biber.

## Provenance constraint (CRITICAL - do not drift)

Privacy in this framework comes from one-way hashing and uniform
representation, NOT from hiding access patterns. Prior sessions drifted the
formalism toward ORAM-style access-pattern indistinguishability, which is
the WRONG model.

- Do NOT import ORAM, differential-privacy, simulation-based, or game-based
  crypto definitions. If you find yourself writing `\Adv`, `\Simulator`,
  `\Trace`, or `\PPT`, stop: that is the wrong formalism.
- Confidentiality is measurable (quantitative information flow), not
  negligible (cryptographic reductions).
- Two confidentiality scales, do not conflate them: the MARGINAL scale
  (single cipher map, parameter delta, Fannes-Audenaert bound) and the
  COMPOSITIONAL/ACTIVE scale (orbit closure, coincidence oracle, joint
  recovery). Spine section 4A is the authority.
- Mathematical landmines that must not revert: Fannes (linear in delta),
  not Pinsker (quadratic); homophonic K(x) proportional to D(x), not
  1/D(x); the orbit set-form denominator is |X|, not 2^n; the compositional
  lower bound is Assouad, not Le Cam.

## Part map and fold sources

| Part | Title | Folds from |
|---|---|---|
| I  | The Paradigm | `foundations/`, spine sec 1-3 |
| II | The Cipher Map Abstraction | `papers/cipher-maps`, spine sec 2-4 |
| III| Algebra and Types | `papers/algebraic-cipher-types`, `foundations/trapdoor-boolean-algebra.md` |
| IV | Confidentiality | `papers/maximizing-confidentiality` (SUMMARIZE only; published standalone at CSF), spine sec 4A |
| V  | Constructions | `papers/codec-controlled-retrieval`, `cipher-rekeying`, `cipher-closures`, `cipher-program-construction`, `src/cipher-maps` |
| VI | Frontiers | `.papermill/prior-art/2026-06-09-ecosystem-survey.md` |

Part IV note: the Entropy Ratio paper is its own CSF submission. In the
book, summarize its two-scale result and the compositional rate with a
pointer to the standalone paper; do not re-prove Theorems 5.1/5.2 in full.

## Notation

Project macros live in `book/notation.sty` (mirrors spine section 8):
`\fhat \ghat \enc \dec \B \TV \cipher{X} \orbitF \eratio`. Add new symbols
there, never inline in a chapter, so all agents render them identically.

## Label conventions

Form: `<type>:<chapter-slug>-<name>` to avoid cross-chapter collisions.
Types: `thm prop lem cor def rem ex eq fig tab ch sec part app`. Examples:
`\label{thm:compositional-rate}`, `\label{ch:abstraction}`,
`\label{part:confidentiality}`. Reference with `\cref{...}` / `\Cref{...}`.

## Notebooks

Stack: Python + uv (`notebook_stack: python-uv`). Notebooks live in
`../notebooks/`, paired one-per-chapter where a chapter has numerical
content, named `chNN-<topic>.ipynb`. A cipher-maps Python library already
exists at `../../src/cipher-maps/` (package `trapdoor_maps`); reuse it for
worked examples rather than reimplementing constructions. Numerical-sanity
targets for each notebook are set in the chapter plan under
`docs/superpowers/plans/`.

## Banned phrases (soul-voice hook)

The soul plugin's hook scans every `.tex`, `.sty`, and `.md` write in this
project and BLOCKS the write if it finds a banned phrase. Known triggers:

- The em-dash character (Unicode U+2014). In LaTeX use `---` (it compiles
  to an em-dash and is allowed); in prose and Markdown use commas, colons,
  or parentheses. The literal U+2014 character is blocked even though
  `---` is fine.
- A set of banned buzzwords from the soul conventions. One that has already
  bitten this project: the verb meaning "to use a thing to maximum
  advantage" (begins with "lev"). Prefer plain words: use, exploit, build on.

For the full list see the soul plugin's SKILL.md. When a write is blocked
the hook reports which phrase tripped it; just rephrase and rewrite.

## Workflow

Scaffold by `/bookwright:init` (done). Next: `/bookwright:design master`
to produce the chapter map and per-part plans under
`docs/superpowers/plans/`, then `/bookwright:design part1` (etc.) to detail
each part, then `/bookwright:write` to draft. Drafting agents read this
file, the relevant plan, and prior chapters before writing.
