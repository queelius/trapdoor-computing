# venue/ : per-venue tailored builds

The canonical paper lives in `../paper/` (`codec_retrieval.tex` + `refs.bib`): the full,
de-anonymized, article-class version that is the content source of truth.

Each subdirectory here is that paper **tailored to one venue's** format, length, and
submission rules (a derivative, not a fork of the science). Each is self-contained
(`main.tex` + `refs.bib` + a `Makefile` + `NOTES.md`) and builds independently.

| Dir | Venue | Format | Status |
|---|---|---|---|
| `tops/` | ACM TOPS | acmart acmsmall (single-col) | **active target**; built, refinements in-body, 30pp |
| `popets/` | PoPETs 2027 | acmart sigconf + popets | fallback; built, 12pp body, refinements in appendix |

Cross-venue status and the decision log are in `../SUBMISSIONS.md`. When the canonical
paper changes substantively, re-apply each venue's documented deltas (see its `NOTES.md`).
Add a new venue by creating `venue/<name>/` with its own `main.tex`, `refs.bib`,
`Makefile`, and `NOTES.md`, and add a row to `../SUBMISSIONS.md`.
