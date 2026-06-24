# Format Validator Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: HIGH

---

## Overall Assessment

The paper builds cleanly with `make`: no compilation errors, no
undefined references, no undefined control sequences. The PDF is
16 pages. The `\cipher` command (which caused the 2026-04-09 critical
format issue) is now defined in the preamble (line 36:
`\newcommand{\cipher}[1]{\mathsf{C}(#1)}`) and renders correctly at all
three occurrences (lines 740, 758, 860).

Resolution of 2026-04-09 format concerns:

| Prior concern | Status | Comment |
|---|---|---|
| Undefined `\cipher` (MINOR, but critical to output) | Resolved | Now defined in preamble |
| Venue-specific formatting needed (MINOR) | Deferred | Target venue still under consideration |

---

## Build verification

```
$ make
[pdflatex, bibtex, pdflatex x2]
Output written on main.pdf (16 pages, 324217 bytes).
```

No errors. Two warnings present, both cosmetic:

```
Package hyperref Warning: Token not allowed in a PDF string (Unicode):
  removing `math shift' on input line 519.
```

This is caused by `\subsection{Multiple Representations ($K > 1$)}`
containing math in the title. The warning is harmless (hyperref strips
math from PDF bookmarks). To silence it: either use `\texorpdfstring`
or remove the math from the subsection title:

```latex
\subsection{Multiple Representations ($K > 1$)}
```
becomes
```latex
\subsection{Multiple Representations with \texorpdfstring{$K > 1$}{K greater than 1}}
```

**Suggestion**: Apply `\texorpdfstring` fix; MINOR priority.

---

## Reference resolution

All labels defined and resolved. Cross-reference sanity check:

| Label | Target | Status |
|---|---|---|
| `sec:intro` (line 71) | Introduction | OK |
| `sec:related` (line 181) | §2 Related Work | OK |
| `sec:prelim` (line 225) | §3 Preliminaries | OK |
| `def:cipher-map` (line 232) | Def 3.1 | OK |
| `sec:measure` (line 321) | §4 The Confidentiality Measure | OK |
| `def:observed-entropy` (line 333) | Def 4.1 | OK |
| `def:max-entropy` (line 344) | Def 4.2 | OK |
| `def:entropy-ratio` (line 361) | Def 4.3 | OK |
| `thm:entropy-decomposition` (line 388) | Thm 4.1 | OK |
| `eq:entropy-decomp` (line 394) | Eq (4.1) | OK |
| `sec:levers` (line 450) | §5 Three Levers | OK |
| `subsec:noise` (line 454) | §5.1 | OK |
| `thm:noise-dilution` (line 461) | Thm 5.1 | OK |
| `eq:noise-entropy` (line 471) | Eq (5.1) | OK |
| `subsec:multiple-reps` (line 520) | §5.2 | OK |
| `thm:multiplicity` (line 528) | Thm 5.2 | OK |
| `ex:homophonic` (line 563) | Example 5 | OK |
| `subsec:granularity` (line 575) | §5.3 | OK |
| `prop:granularity` (line 591) | Prop 5.3 | OK |
| `sec:composition` (line 652) | §6 Compositional Confidentiality | OK |
| `subsec:correlation-leakage` (line 669) | §6.1 | OK |
| `thm:comp-leakage` (line 680) | Thm 6.1 | OK |
| `thm:fpr-compounding` (line 773) | Thm 6.2 | OK |
| `sec:measurement` (line 868) | §7 Practical Measurement | OK |
| `prop:compression` (line 880) | Prop 7.1 | OK |
| `sec:experiments` (line 954) | §8 Experimental Results | OK |
| `tab:boolean` (line 971) | Table 8.1 | OK |
| `tab:fpr` (line 1000) | Table 8.2 | OK |
| `tab:granularity` (line 1030) | Table 8.3 | OK |
| `tab:case-study` (line 1056) | Table 8.4 | OK |
| `sec:discussion` (line 1077) | §9 Discussion | OK |
| `sec:conclusion` (line 1147) | §10 Conclusion | OK |

All `\ref{}` targets resolve. No "undefined reference" warnings.

---

## Page count vs. venue constraints

The paper is 16 pages with `article` class, 11pt, 1in margins. The
state file lists target as "theory venue (15-20 pages)" with candidates
TCC, CSF, and QIF workshop under consideration.

Approximate page-limit checks for likely targets (without reformatting):

| Venue | Typical limit | Format | Likely fit |
|---|---|---|---|
| TCC 2026 | 30 pages (LNCS) | Springer LNCS | Fits easily |
| CSF (IEEE Computer Security Foundations) | 18 pages (IEEE conf) | IEEE double-column | May exceed; double-column compresses by ~40%, likely 10 to 12 dcol pages |
| QIF workshop | varies | varies | Unknown |
| USENIX Security | 18 pages (body) | USENIX | Would fit with reformatting |
| Eurocrypt / Crypto / Asiacrypt | 30 pages (LNCS) | Springer LNCS | Fits easily |

At 16 pages in `article`-class format, the paper should fit all
named theory venues after venue-specific reformatting. No format-level
length blocker for any of the candidates.

**Observation**: The paper is marked as growing from 13 to 16 pages in
the prompt. The growth is accounted for by:
- New §2 Related Work (approximately 1 page)
- Expanded Thm 5.1 compositional leakage (approximately 0.5 pages)
- Expanded Introduction (approximately 0.5 pages)
- Minor prose across §4, §5

This is a healthy growth pattern; no bloat detected.

---

## Theorem numbering

Theorems are numbered within sections. Current inventory:

| Theorem | Number | Content |
|---|---|---|
| Thm | 4.1 | Entropy ratio decomposition (Pinsker bridge) |
| Thm | 5.1 | Noise dilution |
| Thm | 5.2 | Representation uniformity via multiplicity |
| Prop | 5.3 | Granularity spectrum (inherited) |
| Thm | 6.1 | Compositional leakage |
| Thm | 6.2 | FPR compounding (inherited) |
| Prop | 7.1 | Compression estimator |
| Def | 3.1 | Cipher map |
| Def | 4.1 | Observed entropy |
| Def | 4.2 | Maximum entropy |
| Def | 4.3 | Entropy ratio |
| Ex | 5 (5.1) | Homophonic encryption for Zipf |

The numbering is consistent and sequential. No gaps or duplicates.

---

## Theorem environment styling

The paper uses `\newtheorem` for theorem, lemma, corollary,
proposition, definition, remark, example. Styles:
- `plain` for theorem, lemma, corollary, proposition (bold title,
  italicized statement)
- `definition` for definition (bold title, upright statement)
- `remark` for remark, example (italic title, upright statement)

Rendering in PDF: all theorem environments render correctly. Numbering
follows `[section]` counter, so Thm 4.1, 5.1, 5.2, etc.

No issues.

---

## Tables

Four tables (`tab:boolean`, `tab:fpr`, `tab:granularity`,
`tab:case-study`), all using `booktabs`. Rendering is clean.

Observations:
- `tab:boolean`: 5 rows, 5 columns. Captions match content.
- `tab:fpr`: 5 rows, 6 columns, with `\cmidrule` groupings. Empirical
  "---" for ratios undefined at floor. OK.
- `tab:granularity`: 3 rows, 5 columns.
- `tab:case-study`: 5 rows, 4 columns.

The table caption content quality is a methodology-auditor concern,
not a format concern.

---

## Figures

`img/` directory contains legacy TikZ files (`comm_model.tex`,
`inout.tex`, `perturbed_fake_query.tex`, `pr_model_fig.tex`,
`simple_comm_model.tex`) from the previous 43-page version. **None are
`\input`'d or `\include`'d in main.tex**. The paper has zero figures.

For a theory paper, zero figures is unusual but acceptable. A single
schematic of the cipher map architecture (trusted/untrusted machines,
encode/decode) would aid new readers. The `comm_model.tex` or
`inout.tex` from the legacy directory might be adaptable.

**Suggestion**: Consider adding a single schematic figure in §3 or §4
illustrating the trusted/untrusted model and the cipher-value flow.
Without it, the first-time reader must construct the architecture
mentally from prose. Priority: LOW.

---

## LaTeX hygiene

Custom macros defined in preamble (lines 27 to 37):
- `\fhat, \ghat` (hat notation for cipher maps)
- `\enc, \dec` (encode/decode operators)
- `\im` (Image operator)
- `\TV` (total variation)
- `\B` (binary string)
- `\Uniform` (operator)
- `\cipher{#1}` (mapsto `\mathsf{C}(#1)`)
- `\orbitF` (operator)

All are used in text; none are orphans. The `\im` macro (line 32) is
defined but its usage is indirect via `\mathrm{Im}` which is what
`\im` expands to.

No stale command definitions.

---

## Bibliography

Natbib with `plainnat` style. Compiled `.bbl` contains 10 `\bibitem`s,
matching the 10 cited entries. Author formatting is author-year style
(e.g., "Smith (2009)" in-text, "Smith, Geoffrey. On the Foundations..."
in list). Style is consistent with cipher-maps companion paper.

Note from citation-verifier: 21 entries in `references.bib` are
uncited; these do not appear in the compiled PDF.

---

## Language and spelling

Spot-checked for common typos; none found. American spelling throughout
(e.g., "behavior" not "behaviour", "color" not "colour").

One consistency note: the paper alternates "cipher value" (most
common) and "cipher output" (occasionally). These appear to mean the
same thing. Standardizing would marginally improve readability.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 0 | |
| Minor | 2 | Hyperref bookmark warning at line 519; zero figures |
| Suggestion | 1 | Standardize "cipher value" vs "cipher output" |

The paper builds cleanly. The prior round's critical format issue
(undefined `\cipher`) is resolved. The paper is ready for any theory
venue with only venue-specific reformatting required. Page count fits
all named candidates.
