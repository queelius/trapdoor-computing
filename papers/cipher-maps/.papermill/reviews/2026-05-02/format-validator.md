# Format Validator, Round 6 (2026-05-02)

Verified the LaTeX build, label resolution, venue formatting, and
production-quality issues.

## Build Status

```
Output written on cipher_maps.pdf (28 pages, 448460 bytes).
```

Build passes. No errors. No undefined references. No multiply-defined
labels.

### Warnings detected

```
Overfull \hbox (4.3997pt too wide) in paragraph at lines 1579--1586
Overfull \hbox (7.84608pt too wide) in paragraph at lines 1787--1796
Overfull \hbox (104.33095pt too wide) in paragraph at lines 1875--1880
Overfull \hbox (14.3484pt too wide) in paragraph at lines 1910--1916
```

4 overfull hboxes:
1. Lines 1579-1586 (4.4 pt): inside section 8.2 (Compositional Leakage),
   minor wrapping issue. Cosmetic.
2. Lines 1787-1796 (7.8 pt): inside section 10.1 (Reference
   Implementation). Cosmetic.
3. **Lines 1875-1880 (104.3 pt)**: inside section 10.3 Setup itemize,
   the long URL/path "examples/corpus_benchmark.py,
   examples/encrypted_search.py" overflows. **Significant cosmetic
   issue, visible in PDF**.
4. Lines 1910-1916 (14.3 pt): inside section 10.3 Reproducibility
   paragraph. Cosmetic.

**Recommendation FMT-N1**: Fix the 104.3pt overfull at lines 1875-1880
by either:
(a) breaking the URL line with `\allowbreak` or `\sloppy`, or
(b) shortening the prose ("from the published library benchmarks
\texttt{examples/}; see footnote for full paths").

The other 3 are cosmetic and below the typical PoPETs reviewer
threshold. Severity (FMT-N1): **minor**.

## Label and Reference Resolution

All `\ref{}` and `\Cref{}` resolve. No "?" in the rendered PDF for
forward/backward references. The hyperref configuration
`\hypersetup{hypertexnames=false}` works as intended.

The cleveref package is loaded but only used in 2 places:
- Line 916: `\Cref{fig:acceptance-partition}`.
- Line 1564: `\Cref{thm:comp-leakage}` (wait, this is actually
  referenced in §8.2).

Let me verify... actually line 1564 references
`Proposition~\ref{prop:granularity}`. The use of `\Cref` is mostly
inconsistent with `\ref` throughout. **Recommend** standardize on
`\Cref` throughout for consistent capitalization, or remove cleveref
if not used systematically. Severity (FMT-N2): **suggestion**.

## Venue Formatting

### Document class

Line 1: `\documentclass[11pt]{article}`.

For PoPETs 2027, the venue requires the `popets` LaTeX class (or its
predecessor; PoPETs uses the `petsymposium` template). The current
`article` class is generic.

The conversion to PoPETs format requires:
- Switch class to `\documentclass[runningheads,a4paper]{petsymposium}` or
  the current PoPETs template.
- Adjust margins, font, and bibliography style to venue spec.
- Reformat author block per venue style.
- Possibly remove `\usepackage[margin=1in]{geometry}` (venue class sets
  margins).
- Adjust section heading styles.

**Estimated effort**: 1-2 hours for a clean port, 4-6 hours if there
are class-specific quirks (e.g., custom theorem environments that
collide with the venue class).

Severity (FMT-1, carry-over): **major** (must be done before submission,
but is mechanical work).

### Page count

PDF is 28 pages. PoPETs main body is typically 18-20 pages plus
references. Trimming required:
- §10.5 Further Empirical Investigations could compress to a single
  paragraph.
- §9.2 Algebraic Structure could compress (it's already brief, but
  could be a footnote).
- §6.4 Construction Time and Bucketing has two tables that could be
  combined.
- Some §2 paragraphs could compress.

Estimated trim: 5-8 pages without losing technical content.

Severity (FMT-N3, related to FMT-1): **minor** (page count is a
follow-on of class change; venue class typically uses tighter margins
and may bring page count down before any trimming).

### Anonymization

Line 48: `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`
Line 1789: `\url{https://github.com/queelius/cipher-maps}`
Line 1804: `\url{https://pypi.org/project/phobic/}` (also author's own).

For double-blind submission:
- Author block must be `\author{Anonymous Authors}` or removed.
- Library URLs must be replaced with `\url{[redacted for review]}`
  or similar placeholder.
- Acknowledgments section (line 1971) must be removed for submission.
- The bib should not contain `note={... github URL}` for the
  bernoulli-types entry (line 49) since the URL identifies the author.

Severity (FMT-5, carry-over): **major** (must be done before
submission). Estimated effort: 30 minutes.

## Hyperref Configuration

`\hypersetup{hypertexnames=false}` is a workaround for cleveref/hyperref
interaction. It works but is non-default. PoPETs class may have its own
hyperref config; merge carefully on port.

### Internal links work

Spot-checked PDF: clicking `\Cref{fig:acceptance-partition}` jumps to
Figure 1. Clicking `Theorem~\ref{thm:composition}` jumps to §7.2.
Bibliography back-references work. **Functional**.

## Theorem Environment Numbering

The paper uses 4 theorem-style environments (definition, theorem,
lemma, corollary, proposition, remark, example). The numbering is
section-scoped (`[section]`) for definition and theorem (with lemma,
corollary, proposition sharing theorem's counter). This produces
"Theorem 6.1" (section 6, first theorem), "Definition 4.4" (section 4,
fourth definition), etc.

Verified: numbering renders correctly. The "Definition 5.1" expected
by the user's narrative does not exist because the entropy ratio is
defined inline rather than in a Definition environment (covered by
LOG-N1).

## Figure and Table Quality

- Figure 1 (TikZ acceptance partition, line 860-917): clean, readable,
  well-captioned. Good.
- Table 1 (Cipher map parameters, line 558-580): clean, readable.
- Table 2 (Quantitative confidentiality bounds, line 753-771): clean,
  readable.
- Embedded tables in §6.4 (line 1124-1134, 1167-1179): bare tabular
  inside center, no caption. **Recommend** wrap in `\begin{table}` for
  caption/numbering. Severity (FMT-N4): **suggestion**.
- Algorithm 1 (line 977-1009): clean, well-formatted.
- Embedded table in §6.6.1 (line 1237-1250): bare tabular inside
  center, no caption. **Recommend** wrap in `\begin{table}`. Severity
  (FMT-N5): **suggestion**.

## Bibliography Style

Line 1976: `\bibliographystyle{plainnat}`.

PoPETs requires their own bibliography style (typically a venue-
specific .bst file or `splncs04.bst`). Will need to switch on port.
Severity: **part of FMT-1**.

## Production-Quality Summary

- 0 critical (build passes, all references resolve).
- 0 new major.
- 2 carry-over major (FMT-1 venue port, FMT-5 anonymization).
- 2 minor (FMT-N1 104pt overfull, page count trim required).
- 4 suggestions (FMT-N2 cleveref consistency, FMT-N3 follow-on trim,
  FMT-N4 §6.4 table wrapping, FMT-N5 §6.6.1 table wrapping).

Net: production quality is solid. Build is clean. The main work
remaining is the venue port (FMT-1) plus anonymization (FMT-5),
which are both mechanical. The 104pt overfull at line 1875-1880
should be fixed quickly as it is visible in the PDF.

Page count of 28 is over PoPETs target; will likely trim to 22-24
after venue class port (tighter margins) and modest content
compression.
