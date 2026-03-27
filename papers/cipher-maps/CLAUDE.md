# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

The core cipher maps paper: "Cipher Maps: Total Functions as Trapdoor Approximations." Single-author (Alexander Towell), LaTeX, currently in revision. Created by merging two earlier papers (algebraic_cipher_types + cipher_maps); originals archived in `archive/`.

See the parent `CLAUDE.md` at `../../CLAUDE.md` for the conceptual framework, key concepts, core principles, and provenance rules. Do not duplicate that content here.

## Build

```bash
make          # full build (pdflatex x3 + bibtex), copies PDF to repo root
make clean    # remove aux files
make cleanall # remove aux + PDFs
make watch    # rebuild on file changes (requires inotifywait)
```

Source is `paper/cipher_maps.tex` with `paper/references.bib`. The root Makefile delegates to `paper/` and copies the final PDF up. There's also a `paper/Makefile` that can be used directly.

## Paper Structure

The paper has 10 sections plus appendices. Key sections:

| Section | Content |
|---------|---------|
| 3. Cipher Map Abstraction | Definition (tuple), construction strategies, construction layers |
| 4. Four Properties | Totality, Representation Uniformity (δ), Correctness (η), Composability |
| 5. Trusted/Untrusted Model | Formal machine model, what-untrusted-learns analysis |
| 6. Concrete Constructions | HashSet, Entropy Map, Trapdoor Boolean Algebra + comparison table |
| 7. Singular Hash Map | Info-theoretic lower bound, Algorithm 1, space optimality proof |
| 8. Composition | AND gate warm-up, general theorem, chains, error by gate type |
| 9. Encoding Granularity | Joint vs component-wise encoding, entanglement parameter |

TikZ figures live in `paper/img/` (fig_shmap.tex, fig_shs.tex).

## Known Issues

The paper has been through two papermill reviews. Review 2 identified 8 MAJOR issues, tracked in `.papermill/state.md`. The most consequential:

- **M1**: Trapdoor reframing. Approved design doc in `DESIGN-trapdoor-reframing.md` (largely implemented in current tex).
- **M2**: Thm 3.5 (Bernoulli Entropy) needs relabeling/correction
- **M6**: Thm 2.1 states monoid but proves only quotient monoid
- **M7**: Example 2.2 representation multiplicity broken

Full issue table and priority ordering in `.papermill/state.md` under "Next Actions."

## Key Files

- `paper/cipher_maps.tex`: main source (~1400 lines)
- `paper/references.bib`: bibliography (~16 entries, some uncited)
- `DESIGN-trapdoor-reframing.md`: approved design doc for the trapdoor paradigm shift
- `.papermill/state.md`: project state, review history, issue tracker
- `paper/cipher_maps_original.tex`: pre-reframing snapshot for diffing
