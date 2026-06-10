# venue/ : per-venue tailored builds

The canonical paper lives in `../` (`main.tex` + `references.bib`): the full,
de-anonymized, single-column article-class version that is the content source
of truth.

Each subdirectory here is that paper tailored to one venue's format, length,
and submission rules (a derivative, not a fork of the science). Each is
self-contained (`main.tex` + `refs.bib` + `Makefile` + `NOTES.md`) and builds
independently with `make`.

| Dir | Venue | Format | Status |
|---|---|---|---|
| `csf/` | CSF (IEEE Computer Security Foundations) | IEEEtran conference, 2-col | active target; built, 12pp body, proofs/measurement in appendices A-D, anonymized for double-blind |

When the canonical paper changes substantively, re-apply each venue's
documented deltas (see its `NOTES.md`). Add a new venue by creating
`venue/<name>/` with its own `main.tex`, `refs.bib`, `Makefile`, and
`NOTES.md`.
