# Trapdoor Computing: Computing on Opaque Encodings

A research monograph consolidating the trapdoor-computing paper family into
one coherent treatment, closing with a frontier of open problems. Scaffolded
by `/bookwright:init` on 2026-06-10.

## Layout

```
monograph/
  book/
    book.tex            master file (frontmatter, six parts, backmatter)
    preamble.tex        packages + theorem environments
    notation.sty        canonical cipher-map macros (mirrors the spine)
    references.bib      bibliography (per-paper .bib folded in during design)
    Makefile            cd book && make  (pdflatex + biber + pdflatex x2)
    CLAUDE.md           agent guidance: build, provenance, labels, banned phrases
    frontmatter/        title page (+ preface, added later)
    parts/              part1..part6 (part dividers + chapter includes)
    chapters/           chapter .tex (ch01-overview is the only stub so far)
    appendices/         free under a venue page limit; folded standalone proofs
  notebooks/            Python + uv Jupyter notebooks, one per numeric chapter
  papers/               empty; source papers git-subtree-added here if desired
  docs/superpowers/
    bookwright.config.yaml   project config (stack, part/fold map, landmines)
    specs/  plans/           chapter plans land here during /bookwright:design
```

## Build

```bash
cd book && make
```

The scaffold compiles end to end (six part dividers, a stub Overview
chapter, a working biber bibliography).

## Six-part structure

1. The Paradigm
2. The Cipher Map Abstraction
3. Algebra and Types
4. Confidentiality
5. Constructions
6. Frontiers

See `book/CLAUDE.md` for the fold map (which paper feeds which part) and the
provenance constraints, and `docs/superpowers/bookwright.config.yaml` for
the machine-readable project config.

## Next steps

- `/bookwright:design master` to produce the chapter map and per-part plans.
- `/bookwright:design part1` (and so on) to detail each part.
- `/bookwright:write` to draft chapters once a part is planned.

## Note

The Entropy Ratio paper (`../papers/maximizing-confidentiality`) is a
standalone CSF submission. Part IV summarizes its results with a pointer
rather than re-proving them. The soul plugin should be installed so the
voice hook fires on `.tex`/`.md` writes (it enforces the banned-phrase list
described in `book/CLAUDE.md`).
