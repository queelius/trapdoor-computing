# Format Validator Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Confidence**: HIGH

---

## Overall Assessment

The paper builds cleanly at **17 pages** (was 16 in morning round).
No new errors, no new undefined references, no new label conflicts.
The pre-existing hyperref bookmark warning at line 554 (math in
subsection title) persists -- unchanged from morning. The page growth
is accounted for by the new Numerical Scale remark, the rewritten
Theorem 5.1, and the Sampling Regimes remark.

---

## Build verification

```
$ make
[pdflatex, bibtex, pdflatex x2]
Output written on main.pdf (17 pages, 340182 bytes).
PDF built successfully: main.pdf
```

No errors. Two warnings present, both pre-existing and cosmetic:

```
Package hyperref Warning: Token not allowed in a PDF string (Unicode):
  removing `math shift' on input line 554.
```

This is the same warning from the morning round, now at line 554
(was line 519). Caused by `\subsection{Multiple Representations ($K
> 1$)}` containing math in the title. Same fix applies:
```latex
\subsection{Multiple Representations with \texorpdfstring{$K > 1$}{K greater than 1}}
```
or remove the math from the title.

**Severity unchanged**: Minor.

---

## Page count

The paper is 17 pages with `article` class, 11pt, 1in margins. Growth
from 16 -> 17 is accounted for by:

| Addition | Approx pages |
|---|---|
| Numerical Scale remark (§3.3, after Thm 3.1) | 0.1 |
| Rewritten Theorem 5.1 (4-part with sampling spec) | 0.3 |
| Sampling Regimes remark (§5.1) | 0.1 |
| Updated Example 4.1 (Zipf numerics with c, K, H_b) | 0.2 |
| Other prose tweaks (Pinsker -> Fannes propagation) | 0.0-0.1 |

Total addition: roughly 0.7-0.8 pages, rounding up to 1 new page.
This matches observed 16 -> 17 growth.

**Page-limit checks for likely targets** (unchanged from morning):

| Venue | Typical limit | Format | Likely fit |
|---|---|---|---|
| TCC 2026 | 30 pages (LNCS) | Springer LNCS | Fits easily |
| CSF (IEEE) | 18 pages (IEEE conf) | IEEE double-column | Fits (would compress) |
| QIF workshop | varies | varies | Unknown |
| USENIX Security | 18 pages (body) | USENIX | Fits with reformatting |
| Eurocrypt / Crypto | 30 pages (LNCS) | Springer LNCS | Fits easily |

At 17 pages in `article`-class format, the paper still fits all named
theory venues after venue-specific reformatting.

---

## Reference resolution (full re-check)

All labels and references resolve. Spot-checked the new label
references introduced this round:

| Label | First defined | Referenced from | Status |
|---|---|---|---|
| `thm:entropy-decomposition` | line 400 | abstract, §1, §2, §8 | OK |
| `thm:noise-dilution` | line 496 | §1 (intro), Table 4 caption | OK |
| `thm:multiplicity` | line 569 | §1 (intro), §4.2 cost paragraph | OK |
| `thm:comp-leakage` | line 737 | abstract (implicitly), §1 (intro), §2 | OK |
| `thm:fpr-compounding` | line 845 | §6.2 paragraph | OK |
| `prop:granularity` | line 648 | §6.1 mitigation paragraph | OK |
| `ex:homophonic` | line 613 | Table 4 caption | OK |
| `prop:compression` | line 952 | §7.2 paragraph | OK |
| `sec:related` | line 193 | §1 framing | OK |
| `sec:measure` | line 333 | §1 contributions | OK |
| `sec:levers` | line 485 | §1 contributions, §6 opener, §6.1 mitigation | OK |
| `sec:composition` | line 709 | §1 contributions | OK |
| `sec:measurement` | line 940 | §1 contributions | OK |
| `sec:experiments` | line 1026 | §1 contributions | OK |
| `sec:discussion` | line 1156 | §2 (forward ref to Shannon-vs-min-entropy) | OK as label, but the *content* of the forward ref is missing -- see prose-auditor |
| `sec:conclusion` | line 1228 | (none) | OK (reference to itself) |

**Note**: One **forward reference is broken at the content level**:
§2 line 215 says "We discuss the Shannon-vs-min-entropy choice in
\S\ref{sec:discussion}" but §9 (`sec:discussion`) does not contain
that discussion. The label resolves, but the promised content is
absent. This is a content/prose issue (covered by prose-auditor), not
a format issue per se.

**Verdict**: All `\ref{}` targets resolve cleanly. No undefined
references warnings.

---

## New labels and theorem numbering

The current theorem inventory (verified by reading the source):

| Type | Number | Label | Content |
|---|---|---|---|
| Definition | 3.1 | `def:cipher-map` | Cipher map |
| Definition | 3.2 | `def:observed-entropy` | Observed entropy |
| Definition | 3.3 | `def:max-entropy` | Maximum entropy under constraints |
| Definition | 3.4 | `def:entropy-ratio` | Entropy ratio |
| Theorem | 3.1 | `thm:entropy-decomposition` | Entropy ratio decomposition |
| Theorem | 4.1 | `thm:noise-dilution` | Noise dilution |
| Theorem | 4.2 | `thm:multiplicity` | Representation uniformity via multiplicity |
| Example | 4.1 | `ex:homophonic` | Homophonic encryption for Zipf |
| Proposition | 4.3 | `prop:granularity` | Granularity spectrum (inherited) |
| Theorem | 5.1 | `thm:comp-leakage` | Compositional leakage |
| Theorem | 5.2 | `thm:fpr-compounding` | FPR compounding (inherited) |
| Proposition | 6.1 | `prop:compression` | Compression estimator |
| Remark | (3.1 to 4.x) | (no label) | Numerical Scale, role of $\varepsilon$, role of $\eta$, Sampling Regimes |

**Note on numbering update**: Compared to the morning round, the
section numbering changed because the §3 (Confidentiality Measure)
remained §3, but theorem counters are within sections so e.g. the
Pinsker bridge theorem is still Thm 3.1. The morning-round inventory
showed Thm 4.1 = "Entropy ratio decomposition"; this is incorrect in
my view -- the current document has Thm 3.1 = "Entropy ratio
decomposition" because §3 is "The Confidentiality Measure" and
\newtheorem{theorem}{Theorem}[section]. So the morning format-
validator's table was off by one section. Not a defect now;
flagging only because I noticed.

The current numbering is internally consistent. PDF cross-references
to "Theorem 3.1", "Theorem 4.2", etc. all resolve to the right
content.

---

## Theorem environment styling

Unchanged from morning round: standard `plain`/`definition`/`remark`
styles, sequential numbering within sections, all rendering
correctly.

---

## Tables

Same four tables as morning round (`tab:boolean`, `tab:fpr`,
`tab:granularity`, `tab:case-study`):

| Table | Caption update? | Content update? |
|---|---|---|
| `tab:boolean` (Boolean search) | No | No |
| `tab:fpr` (FPR compounding) | No | No |
| `tab:granularity` (Granularity spectrum) | No | No |
| `tab:case-study` (Confidentiality improvement) | **Yes**: now says "Values are analytical, computed from the Zipf entropy, the mixture-entropy formula in Theorem~\ref{thm:noise-dilution}, and the homophonic construction in Example~\ref{ex:homophonic}." | **Yes**: all values updated to reflect corrected $K(x) \propto D(x)$ construction |

The Table 4 caption update partially addresses the morning
methodology-auditor concern about "Worked Examples" labeling.

---

## Figures

Unchanged from morning: zero figures. The `img/` directory contains
legacy TikZ files from the previous version that are not `\input`'d
in main.tex. No format-level issue, only an opportunity-cost concern
that prose-auditor / methodology-auditor have noted.

---

## LaTeX hygiene

Custom macros defined in preamble (lines 27 to 37) -- unchanged from
morning. All used in text; no orphan definitions.

The `\cipher{}` macro (line 36) is defined and used at three locations
(lines 740, 758, 860 in the morning numbering; let me verify in
current). In the current file:

- `\cipher{Y_1 \times Y_2}` at line 813 (mitigation paragraph)
- `\cipher{X}` at line 830 (Boolean chains)
- `\cipher{\mathrm{Bool}}` at lines 830, 928, 932 (multiple)

All render correctly. No undefined-control-sequence warnings.

---

## Bibliography

Natbib with `plainnat`. Compiled `.bbl` contains 14 `\bibitem`s
(was 10 in morning), reflecting the four newly-cited entries
(Simmons, Fannes, Audenaert, Cover-Thomas). The new citations use
correct natbib formatting with author-year style.

Spot-checked the rendered bibliography in main.bbl:
- Audenaert (2007) ✓
- Cover and Thomas (2006) ✓
- Fannes (1973) ✓
- Simmons (1979) ✓

All four new bibitems compile correctly.

---

## Language and spelling

Spot-checked the new prose (Numerical Scale remark, Sampling Regimes
remark, Theorem 5.1 rewrite, Example 4.1 update). No new typos
detected.

The "cipher value" vs "cipher output" inconsistency from the morning
round persists. Still cosmetic.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 0 | |
| Minor | 1 | Pre-existing hyperref bookmark warning at line 554 (carry-over) |
| Suggestion | 1 | Standardize "cipher value" vs "cipher output" (carry-over) |

The paper builds cleanly at 17 pages with no new build issues. All
new label references resolve. The four new bibliography entries
(Simmons, Fannes, Audenaert, Cover-Thomas) compile correctly. The
single warning is the same hyperref-bookmark warning from the
morning round, unchanged.

No format regressions. The afternoon revision is production-clean.
