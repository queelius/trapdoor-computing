# Format Validator Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Format Validator
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Build target**: PDF via `make` in `paper/` directory
**Output**: `paper/cipher_maps.pdf` (375,199 bytes, ~22 pages)

## Summary

The paper builds cleanly with zero warnings. All references resolve. All citations resolve. The bibliography compiles correctly. No formatting issues at the LaTeX level. Two structural items: the paper still uses the article class (will need PoPETs template before submission), and zero figures despite TikZ source files being present in `paper/img/`.

**Findings**: 0 critical, 0 major, 4 minor.

---

## Build verification

### Build process
The Makefile delegates to `paper/Makefile`. Standard pdflatex + bibtex + pdflatex + pdflatex sequence. No errors during build.

### Warnings
Searched build log for "Warning|Error". Only one match found, and it is a package descriptor line ("Package: infwarerr ..."), not an actual warning. The build is clean.

### Reference resolution
- All `\ref{}` resolve.
- All `\cite{}` resolve (verified by citation-verifier).
- All `\label{}` are unique (no duplicate label warnings).
- All `\cleveref` cross-references work.
- No undefined references.

### Bibliography
23 entries; all entries cited at least once; bibtex log is clean.

---

## Minor Findings

### F1. Article class, will need PoPETs template before submission (MINOR, S4 from Round 3)

**Location**: Line 1, `\documentclass[11pt]{article}`

**Problem**: The paper uses `\documentclass[11pt]{article}` which is appropriate for development but not for PoPETs submission. PoPETs uses its own template (currently at `https://petsymposium.org/authors.php`). The template change will:
- Change page count (PoPETs is two-column 10pt; current is one-column 11pt).
- Change figure/table sizing constraints.
- Require anonymization for double-blind review.
- Possibly require restructuring for the conference's expected section ordering.

**Status from Round 3**: Acknowledged as suggestion S4; not addressed in this round.

**Suggestion**: Test-build with the PoPETs template at least once before the next major revision pass. Page count compression in two-column 10pt may require trimming, especially if M1 (security definition) and M2 (experiments) are added. Earlier test-builds avoid last-minute cuts.

### F2. Zero figures despite TikZ source files in `paper/img/` (MINOR, m4 from Round 3 not addressed)

**Location**: Throughout; `paper/img/fig_shmap.tex` and `paper/img/fig_shs.tex` exist but are unused.

**Problem**: Two TikZ source files are present in the figures directory but neither is included in the manuscript. The paper has zero figures in 22 pages. PoPETs reviewers expect at least diagrams of the trust model, the construction, or the acceptance predicate.

**Status from Round 3**: Acknowledged as minor m4; not addressed.

**Suggestion**: Include at least one figure. Recommended priorities:
1. Acceptance predicate partition diagram (showing $A(y_1)$, $A(y_2)$, ..., $A(y_n)$ regions of $\{0,1\}^n$ with sizes proportional to $p_y$). This visually communicates the Shannon-frequency duality.
2. Trusted/untrusted protocol flow (showing $T \to U$ encoded inputs, $U \to T$ outputs). This makes the trust model concrete.
3. Composition chain diagram (showing $\fhat$ then $\ghat$ chained, with cipher value flowing through). This concretizes Property 4.

The existing TikZ files (`fig_shmap.tex`, `fig_shs.tex`) presumably show the singular hash map; including them would be a low-effort improvement.

### F3. Anonymization not done (MINOR, NEW)

**Location**: Title page (line 38-40), `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`

**Problem**: The title page identifies the author by name and email. The Acknowledgments (lines 1528-1531) reference "the author's earlier work." For PoPETs double-blind review, all identifying information must be removed from the submission.

**Status from Round 3**: Implicit; not addressed.

**Suggestion**: Before submission, replace `\author{Alexander Towell...}` with `\author{Anonymous Submission}`. Rephrase Acknowledgments to: "The constructions in this paper draw on the earlier *Bernoulli data type library* and the *trapdoor Boolean algebra* (citations omitted for blind review)." After acceptance, restore.

This can be controlled by a LaTeX flag: `\if\anonymous\author{Anonymous}\else\author{Alexander Towell...}\fi` and toggle with one variable.

### F4. PDF page count is 22 in article class; will likely change in PoPETs format (INFO)

**Location**: PDF output

**Problem**: The current build is 22 pages in `article` class. PoPETs PDF page limits vary by submission track (typically 12 to 15 pages excluding bibliography for full papers). The current paper exceeds this limit even ignoring the format change.

If M1 (security definition) and M2 (experiments) add 2 to 4 pages, total will be 24 to 26 pages in article class, equivalent to roughly 16 to 18 pages in PoPETs two-column format. Likely under the typical limit, but compression will be tight.

**Suggestion**: Plan for compression. The Discussion section restructuring suggested by prose-auditor P1 would help: trimming the six Discussion subsections to two or three would buy 1 to 2 pages.

---

## Items Verified Sound

- Build is reproducible (clean build from `paper/Makefile`).
- No LaTeX warnings.
- BibTeX log is clean (no missing entries, no malformed entries).
- All cross-references resolve via `cleveref`.
- All `\ref{}` and `\cite{}` invocations resolve.
- The paper compiles to a valid PDF without manual intervention.
- Theorem/definition numbering is sectioned and consistent.

## Notes for the orchestrator

The format situation is solid for development but needs the standard pre-submission cleanup:
- Switch to PoPETs template (F1).
- Anonymize for double-blind (F3).
- Add at least one figure (F2).

None of these are content issues; all are procedural. The paper is in a "ready to revise content" state at the format level.

For the user's specific question about what else needs work: F1 (PoPETs template test-build) is the only format issue worth addressing now, because page-count surprises during the M1/M2 revision could force unwanted compression. The other format issues can be deferred to the final pre-submission pass.
