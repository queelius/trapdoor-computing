# Format-Validator Report, Round 5 (2026-06-02)

**Paper**: "The Entropy Ratio" (`main.tex`)
**Build command**: `make` (3 pdflatex passes + bibtex)
**Result**: exit 0, **25 pages**, PDF produced.

---

## F-1 (LOW): four overfull hboxes, a regression against the "zero warnings" invariant

The build is NOT warning-free. There are **four unique** overfull `\hbox`
warnings (each printed three times, once per pass; 12 lines total in the
log):

| Location (lines) | Overfull amount |
|---|---|
| 588 to 596 | 17.19 pt |
| 686 to 693 | 4.38 pt |
| 915 to 927 | 10.76 pt |
| 1384 to 1403 | 45.05 pt |

These are typographic (text too wide for the column), not reference/label
errors. All `\ref` and `\cite` resolve; no undefined references, no multiply
defined labels, no missing citations.

**Why this is flagged.** Both `CLAUDE.md` ("zero warnings") and the
2026-05-23 review's format-validator claim "zero warnings." That claim was
internally contradictory in the 2026-05-23 report, which simultaneously
listed "Four overfull hboxes (4-45pt)." So this is not new breakage; it is a
pre-existing inconsistency between the stated invariant and the actual build.
The honest status is: **clean compile, correct cross-references, four
cosmetic overfull boxes.** For a theory-venue submission these are
survivable, but they should not be described as "zero warnings."

**Fix (optional, cosmetic).** The 45pt box at 1384 to 1403 (the
reproducibility paragraph, which has long `\texttt{...}` URLs/paths) is the
worst; a `\sloppy` block or a `\url{}` line break would clear it. The 588 to
596 box (17pt) is in the Thm 3.1 region. The other two are minor (<11pt).
None blocks submission; all are below the threshold most venues care about.

## F-2 (none): figures and labels

Three active figures (`finite_sample_gap`, `newsgroups_homophonic`,
`compression_validation`) all resolve via `\includegraphics`. The stale TikZ
figures and `data/` directory noted in `CLAUDE.md` are not `\include`d and do
not affect the build. PDF metadata (title, author, subject, keywords) is
populated via `\hypersetup{}`. Hyperref bookmarks are warning-free (the two
`\texorpdfstring` math-titles plus the new math-bearing subsection titles
all use the pattern). No bookmark warnings in the log.

## F-3 (none): cross-reference integrity

All `\label`/`\ref`/`\cref` pairs resolve. The theorem counter sharing
(definition/theorem/lemma/corollary/proposition share one counter, remark
and example separate) is intact; promoting/demoting did not desync any
label. Equation, table, and figure numbering are continuous.

---

## Page-count and structure note

25 pages, up from 18 at 2026-04-29, consistent with the §6.5 addition (new
subsection + figure), the §9 practical-depth paragraph, and the Table 1 to 3
refresh. Section count and theorem count match the `CLAUDE.md` description
(6 theorems, 4 tables, now 3 figures).

---

## Summary

| ID | Finding | Severity |
|---|---|---|
| F-1 | Four overfull hboxes; "zero warnings" invariant is inaccurate | LOW |

The build is healthy: it compiles in three passes, produces 25 pages, and
every reference resolves. The only correction is documentary: the paper has
four cosmetic overfull boxes, so the "zero warnings" claim in `CLAUDE.md` and
the prior review should be updated to "clean compile, four cosmetic overfull
hboxes" (or the boxes should be cleared). No regression in reference
resolution or structure.
