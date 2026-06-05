# Polish Report

**Date**: 2026-06-05
**Paper**: Codec-Controlled Retrieval (towell2026codec)
**Source**: `paper/codec_retrieval.tex` + `paper/refs.bib`
**Reviewer**: format-validator (polish pass)

---

## Checklist Summary

| Item | Status | Notes |
|------|--------|-------|
| 1. Build | PASS | 23 pages, stable on 4th pass |
| 2. Labels / cross-refs | PASS | 0 undefined in final log |
| 3. Citations / bibliography | PASS (with advisory) | All 19 cited keys resolve; 2 uncited entries remain |
| 4. Em-dashes / typography | PASS | 0 violations found |
| 5. Leftovers | PASS | 0 TODO/TBD/XXX/FIXME; abstract is real prose |
| 6. Notation consistency | PASS | W, class(v), alpha(v), TV, delta(p_0)/delta(p_1), rank pi|_W, log_2 K all consistent |
| 7. Metadata | PASS | Title, author, email, date correct |
| 8. Claim spot-check (M1 fix) | PASS | Factor-2 phrasing gone; Adv=0 intact; delta(p_0) notation throughout |
| 9. Venue compliance | REPORTED | Known camera-ready tasks listed below |

**Trivial fixes made**: none (nothing required safe-fix action)

**Final verdict**: submission-ready modulo camera-ready class switch + anonymization

---

## 1. Build

**Command**: `cd paper && make` (forced rebuild: `touch codec_retrieval.tex && make`)
**Build sequence**: pdflatex (pass 1) -> bibtex -> pdflatex (pass 2) -> pdflatex (pass 3, stable) -> pdflatex (pass 4, stable)
**Result**: SUCCESS
**Page count**: **23 pages** (396829 bytes)
**Note**: The prior state.md recorded 22 pages; the final build is 23 pages. The bibliography and related-work additions from the M1-M3 revision cycle account for the extra page.

Key final-pass log lines:
```
Output written on codec_retrieval.pdf (23 pages, 396829 bytes).
Package rerunfilecheck Info: File `codec_retrieval.out' has not changed.
```

Passes 1-2 produced the expected "Label(s) may have changed. Rerun" (normal for a first build
from scratch); passes 3 and 4 are clean with no Rerun instruction and no Label-changed warning.

---

## 2. Labels / Cross-References

**Result**: PASS

Final log grep for "undefined": 0 matches.
Final log grep for "Rerun" (cross-ref stability): 0 matches beyond the package-load line.
Final log grep for "may have changed": 0 matches.

All `\label{...}` targets used with `\cref`/`\Cref`/`\ref` resolve in the final build. No
dangling `??` markers are present in either the source or the compiled PDF.

**Warnings present (harmless)**:
- 4x `Package hyperref Warning: Token not allowed in a PDF string (Unicode): removing 'math shift' on input line 546`
  Source: `\subsection{The mass on each class is $0$ or $1/K'$}` -- math in a subsection title
  cannot be placed in a PDF bookmark string. This is a known, soft hyperref limitation. The PDF
  renders correctly; the bookmark string is silently stripped. Fix with `\texorpdfstring` if
  bookmark fidelity is required for camera-ready.

- 2x `Overfull \hbox`:
  - `(0.82176pt too wide) in paragraph at lines 940--947` -- the "Covered." bullet in the scope
    section; 0.8pt overflow, invisible to a reader.
  - `(38.27792pt too wide) in paragraph at lines 1304--1320` -- the `\paragraph{Leakage-abuse
    attacks and leakage suppression.}` paragraph heading in related work. 38pt is visible in the
    article class but will reflow on the PoPETs two-column class; not worth fixing in the current
    draft.

---

## 3. Citations and Bibliography

**Result**: PASS (with advisory on two uncited entries)

All 19 bib keys cited in the .tex are present in refs.bib and appear in the compiled .bbl.
BibTeX log: "You've used 19 entries" with 0 BibTeX warnings.

**Cited keys** (19, all resolve):
cash2015leakage, chazelle2004bloomier, cheng2019pmte, dillinger2021ribbon, dillinger2022burr,
filic2022adversarial, graf2020xor, graf2022binaryfuse, grubbs2020pancake, hu2025retrieval,
islam2012access, juels2014honey, kamara2018structured, lacharite2018fse, macwilliams1977,
naveed2015inference, patel2019volumehiding, towell2026ciphermaps, towell_bernoulli_maps

**Uncited bib entries** (2, present in refs.bib but not cited):
- `dietzfelbinger2008succinct` -- retrieval space lower bound
- `dietzfelbinger2019gauss` -- GF(2) Gaussian elimination for banded systems

These will not print. Consistent with the prior review's m7 finding. The prior review recommended
citing both (free, they are already in the bib); not fixed in this pass as it exceeds safe-polish
scope.

**Production notes in the printed bibliography**: PASS. The current .bbl shows:
- `towell2026ciphermaps`: "Manuscript, in revision, 2026." -- clean, no internal annotations.
- `towell_bernoulli_maps`: "Manuscript, 2026." -- clean.

The "Cites towell2026codec." leak flagged as m3 in the prior review is **already gone**. Both
self-citations have `year = {2026}` populated (m4 from the prior review also fixed).

**hu2025retrieval spot-check**: Six authors (Hu, Kuszmaul, Liang, Yu, Zhang, Zhou), arXiv
2510.18237, FOCS 2025, booktitle = "IEEE Symposium on Foundations of Computer Science (FOCS)".
Renders correctly as "Hu et al. (2025)". Prior review advisory to verify exact title/venue before
submission still stands.

---

## 4. Em-Dashes / Typography

**Result**: PASS

Grep for U+2014 (em-dash), U+2013 (en-dash), U+2212 (unicode minus) in both
`paper/codec_retrieval.tex` and `paper/refs.bib`: **0 matches**.

No unicode dash violations. The LaTeX `---` sequences in the source are ASCII and are not
affected by the write-hook ban on unicode em-dashes.

---

## 5. Leftovers

**Result**: PASS

Grep for TODO, TBD, XXX, FIXME, `\textbf{?}`, "to be drafted", "to be written", "placeholder",
"DRAFT", "SKELETON": **0 matches** in codec_retrieval.tex and refs.bib.

The abstract is substantive prose (2391 characters, a single tight paragraph). All 11 sections
plus the appendix contain substantive content. No stub text is present.

---

## 6. Notation Consistency

**Result**: PASS

Spot-checks:

- **W (the span)**: defined as `\W` macro, used consistently as `W` via macro throughout. No bare
  `W` in math contexts that should use `\W`.
- **M1 (idealized model)**: defined at `def:M1` (Definition 2.3), referred to as "M1" and
  "idealized model M1" consistently throughout.
- **class(v)**: defined as `\class` macro (`\mathrm{class}`), used consistently.
- **alpha(v)**: defined as `\al` macro (`\alpha`), used consistently. No bare `\alpha` found in
  prose contexts.
- **TV / d_TV**: defined as `\TV` macro (`d_{\mathrm{TV}}`), used consistently in all formal
  statements. "TV" (unformatted) appears only in prose as a common abbreviation, which is standard.
- **delta(p_0)/delta(p_1)**: the M1 fix is complete. No `delta_0`/`delta_1` subscript notation
  found anywhere in the source (0 grep matches). All occurrences use the function-of-profile form
  `\delta(p_0)` and `\delta(p_1)`.
- **rank pi|_W**: `\rank \proj|_{\W}` used consistently.
- **log_2 K**: `\log_2 K` used consistently throughout.

---

## 7. Metadata

**Result**: PASS

```latex
\title{Codec-Controlled Retrieval:\\
Structural Frequency-Hiding from the Non-Member Channel of XOR Retrieval}
\author{Alexander Towell\\\texttt{lex@metafunctor.com}}
\date{June 2026}
```

Title, author name, email address, and date are all correct and present.

---

## 8. Claim Spot-Check (M1 fix verification)

**Result**: PASS

The M1 fix from the editorial cycle has been applied correctly:

- **Factor-2 phrasing is gone.** Grep for `2(\\delta`, `2(delta`, `delta_0`, `delta_1`: 0 matches.
  The old abstract phrasing "at most $2(\delta_0+\delta_1)$" and theorem statement
  "Adv <= 2 TV(...)" are not present anywhere.

- **Real bound is now a distribution-distance claim.** The theorem (`thm:freqdist-real`)
  states:
  ```latex
  \TV\big(\lawreal(p_0), \lawreal(p_1)\big) \;\le\; \delta(p_0) + \delta(p_1).
  ```
  The proof note at line 894 is explicit: "(No factor of 2 appears: the earlier
  single-observation reading multiplied the per-sample TV by the convention factor; the
  per-observation advantage in this convention is the TV itself.)"

- **Advantage convention `|2Pr[b'=b]-1|`** appears at lines 820, 869, 892 as the standard
  distinguishing advantage *definition* -- this is correct and unrelated to the old factor-2
  bound error.

- **Idealized Adv=0 is intact.** Lines 82, 174, 787, 826, 830-831, 844, 917, 923, 930 all
  confirm `\Adv(\mathcal{A}) = 0` under M1.

- **Abstract uses delta(p_0)+delta(p_1) notation.** Line 84:
  `$\delta(p_0)+\delta(p_1)$ of each other` -- consistent with the body.

---

## 9. Venue Compliance

**Status**: REPORTED (not a blocker for this pass)

The paper uses `\documentclass[11pt]{article}`. Known camera-ready tasks for PoPETs 2027:

1. **Document class switch**: Replace `article` with the official PoPETs/PETS LaTeX template
   (`popets` or `petsymposium` class). The 23-page `article` build will recompose; the proofs
   and appendix may need adjustment to fit the PoPETs page budget (the state file flags the
   appendix-vs-body split as the lever).
2. **Anonymization**: The paper names the author and self-cites "the author's own" work. For
   PoPETs double-blind, remove name and email from `\author{}`, replace "the author's own" with
   "prior work [X]", and ensure the companion relationship (cipher-maps) does not reveal identity.
3. **Abstract notation**: the abstract coincidence-oracle clause does not state the direction
   (concentration defends, not flatness). The prior review's m2 fix ("...pulled the opposite
   way (it is defeated by concentrated, not flat, codespace shares)") is still pending; trivial
   addition of five words.
4. **Two uncited foundational entries**: `dietzfelbinger2008succinct` and `dietzfelbinger2019gauss`
   are in the bib but uncited (prior review m7). Citing them at Section 2.2 and the space claim
   is free.
5. **Subsection math in bookmark string**: `\texorpdfstring` at line 546 would silence the 4
   hyperref "Token not allowed" warnings, relevant if PDF bookmarks are reviewed.

---

## No Fixes Made

No changes were made to the source files in this pass. The build is stable, all references
resolve, the bibliography is clean, and no trivial-safe issue requiring a source edit was found.
