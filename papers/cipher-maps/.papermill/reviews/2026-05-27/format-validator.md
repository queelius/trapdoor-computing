# Format Validator Report, Round 8 (2026-05-27)

## Build status

Build completes successfully via Makefile. PDF: 38 pages (cipher_maps.pdf,
521,209 bytes).

Build sequence: pdflatex -> bibtex -> pdflatex -> pdflatex. No
unresolved citations or missing references.

## Build warnings (from cipher_maps.log)

| Line | Severity | Location | Notes |
|---|---|---|---|
| Overfull \hbox 4.4pt | minor | lines 1692 to 1699 | section 8.1 ("Build the composition directly") |
| Overfull \hbox 7.85pt | minor | lines 2267 to 2276 | section 10.1 (reference implementation, URL or table) |
| Overfull \hbox 14.35pt | major | lines 2460 to 2469 | section 10.3 reproducibility paragraph (e1_bloom_baseline.py URL) |
| Overfull \hbox 1.27pt | minor | lines 2675 to 2680 | section 10.6 ("randomized-encoding defense") |

The R7 CRIT/MAJ 118.9pt overfull at Definition 8.x (Pattern- and
Decode-coincidence attackers) is **closed** via commit e8bbfd3 (the
math expression was pulled onto its own display line).

The 4 remaining overfulls are minor (under 15pt). The 14.35pt overfull
at section 10.3 reproducibility is from the e1 file path
`.papermill/experiments/2026-05-23/e1\_bloom\_baseline.py` which spans
the right margin. Recommendation: break the path with `\allowbreak` or
use `\path{...}` from the `url` package.

## FMT-MAJ-1 (article class, not PoPETs template)

R5 FMT-1 / R6 / R7 carry-over.

The paper uses `\documentclass[11pt]{article}` with `[margin=1in]{geometry}`,
not the PoPETs 2027 template. PoPETs requires their own LaTeX template
with specific formatting requirements (two-column, ACM-derived style,
fixed page limits).

Status: open. Required for submission. Estimated work: 4 to 8 hours
(port + reflow tables and figures).

## FMT-MAJ-2 (page count 38 vs PoPETs target)

R7 MAJ-19 carry-over.

Current page count: 38 pages in article class with 1-inch margins.
PoPETs format is typically 18 to 20 pages in their two-column template,
which corresponds to roughly 22 to 28 pages in single-column article
class.

Pre-port estimate of PoPETs page count: 26 to 30 pages.

PoPETs hard limit: 16 pages of body + unlimited appendix in their
template (verify against 2027 CFP at submission time).

Page-trim candidates (R7 carry-over):
- Section 9.1 (Bernoulli relationship): ~ 20 lines, can be compressed
  to a remark.
- Section 9.4 (Bounded composition as security feature): ~ 50 lines.
  Could be moved to appendix or compressed.
- Section 10.4 (Deniability via correctness parameter): ~ 30 lines.
  Could be appendix.
- Section 10.5 (Further empirical investigations): ~ 20 lines.
  Can be cut to a paragraph in section 10.7 conclusion.
- Section 6.3 (Algorithm 1 with full pseudocode): ~ 30 lines. Could
  be appendix (R7 FMT-SUG-2 carry-over).

Estimated post-trim page count: ~ 32 to 35 pages article class -> 18
to 20 pages PoPETs two-column. Achievable.

## FMT-MAJ-3 (anonymization for double-blind review)

R6 FMT-MIN-7 / R7 FMT-MIN-7 carry-over.

Current title page (lines 47 to 49):
```
\author{Alexander Towell\\\texttt{lex@metafunctor.com}}
\date{March 2026}
```

PoPETs uses double-blind review. Author block must be anonymized for
submission. Standard form: `\author{Anonymous Submission}` or similar
with `\if{...}` toggle.

Other anonymization concerns:
- ORCID in CITATION.cff (file at repo root): not in PDF, OK.
- Footnote URL `https://github.com/queelius/cipher-maps` at section
  10.1 line 2269: identifying author handle. Replace with
  `https://[anonymous]` for submission.
- Footnote URL `https://pypi.org/project/phobic/` at line 2284: not
  author-identifying, OK.
- Acknowledgments paragraph (lines 2786 to 2789): "draw on the
  author's earlier work on the Bernoulli data type library and the
  trapdoor Boolean algebra." Anonymize for submission.
- Companion citations (towell2026*): cite as "anonymous companion
  work" for double-blind, or omit.

Estimated work: 1 to 2 hours.

## FMT-MIN-1 (cleveref vs ref usage consistency)

R7 FMT-MIN-3 carry-over.

The paper uses both `\Cref{...}` (capitalized cleveref) and `\ref{...}`
(plain ref) interchangeably. Counts (approximate, from grep):
- `\Cref{...}`: 4 occurrences (section 1 line 138, section 3.4 line
  376, section 6.2 line 1055, section 10.6 elsewhere).
- `\ref{...}`: ~ 30+ occurrences.
- `\cite[...]{...}` with cleveref-style: ~ 5 occurrences.

Recommendation: standardize on `\Cref` throughout. Cleveref
auto-generates the correct prefix ("Theorem", "Equation", etc.) and
makes refs consistent across the paper.

## FMT-MIN-2 (TikZ figure quality)

Section 6.2 (lines 961 to 1018) defines fig:acceptance-partition as
a TikZ picture inline. The figure renders correctly per the PDF.
File paper/img/ contains additional TikZ source files (fig_shmap.tex,
fig_shs.tex per CLAUDE.md but not verified to be used in current
manuscript).

Recommendation: verify the inline TikZ figure compiles in PoPETs
template (some publishers restrict inline TikZ).

## FMT-MIN-3 (table environment usage)

R7 FMT-MIN-5 carry-over.

Several tables in the paper use `tabular` directly without `table`
environment wrapping:
- Section 6.4 line 1232 ("Construction time table"): bare tabular in
  `\begin{center}...\end{center}`.
- Section 6.4 line 1275 ("Bucketed construction trade-off"): bare
  tabular in center.
- Section 6.6.1 line 1347 ("Parameter instantiation"): bare tabular
  in center.

Without `table` environment, these tables lack: caption, label for
cross-reference, float placement. Recommendation: wrap each in
`\begin{table}[ht]...\end{table}` with caption and label.

## FMT-MIN-4 (title page date)

R7 FMT-MIN-10 carry-over.

Title page date is "March 2026" (line 49). Current date is May 27,
2026. Recommendation: update to "May 2026" before submission, or use
`\today`.

## FMT-MIN-5 (integration comment markers in source)

R7 PROSE-MIN-9 cross-reference.

Source file contains comments:
- Line 1731: `%% [INTEGRATION 2026-05-07] New subsection §8.3`
- Line 2054: `%% [/INTEGRATION 2026-05-07]`
- Line 2224: `%% [INTEGRATION 2026-05-07] New subsection §9.6`
- Line 2259: `%% [/INTEGRATION 2026-05-07]`
- Line 2536: `%% [INTEGRATION 2026-05-07] New subsection §10.6`
- Line 2782: `%% [/INTEGRATION 2026-05-07]`

These do not affect the PDF but should be removed for the submission-
ready source. Cosmetic.

## FMT-MIN-6 (table caption placement)

Tables in the paper place captions above (e.g., Table 4.1 at line 627,
Table 5.1 at line 851) and below (e.g., Table 10.x at lines 2431, 2589)
inconsistently. PoPETs typically requires above.

Recommendation: standardize on `\caption{...}` immediately after
`\begin{table}` (above table).

## FMT-MIN-7 (URL formatting in bibliography)

The bibliography uses `\url{...}` macros for two entries (bernoulli-
types at line 49 and towell2026codec at line 287). These render
correctly but line-break behavior may be poor in two-column PoPETs
format. Use `url` package's `\path{...}` for better line-breaking.

## FMT-SUG-1 (notation table near section 3)

R7 FMT-SUG-1 carry-over.

The paper introduces many symbols: $\hat{f}$, $\enc$, $\dec$, $s$,
$\cipher{X}$, $\cipherS{X}{s}$, $\eta$, $\varepsilon$, $\delta$,
$\mu$, $K(x)$, $D(x)$, $\alpha(y)$, $p$ (entanglement), $L$, $t$.
A notation table near section 3 would help a reader who arrives at
section 8.3 ("at $t = 5$ the uniform Dense partition produces ...")
and needs to refresh which symbol means what.

Recommended location: end of section 3 or appendix.

## FMT-SUG-2 (Algorithm 1 to appendix)

R7 FMT-SUG-2 carry-over.

Algorithm 1 (lines 1078 to 1110) takes 32 lines of body text. For a
page-trim, moving to appendix would help. Lower priority than
FMT-MAJ-2 main trim.

## Findings

### Critical

None.

### Major

**FMT-MAJ-1**: article class not PoPETs template (R5/R6/R7 carry-over).
**FMT-MAJ-2**: page count 38 (PoPETs target 18 to 20 in their template;
need ~ 8 to 10 page trim post-port).
**FMT-MAJ-3**: anonymization for double-blind review.

### Minor

FMT-MIN-1 to 7 as above. Most R7 carry-over.

### Suggestions

FMT-SUG-1 and 2 as above. Lower priority.

## R7 closure verification

| R7 finding | This round status |
|---|---|
| MAJ-6 article class | FMT-MAJ-1, still open |
| MAJ-18 Definition 8.x overfull 118.9pt | CLOSED via commit e8bbfd3 |
| MAJ-19 36 pages | FMT-MAJ-2, still open (now 38 pages) |
| FMT-MIN-3 cleveref | FMT-MIN-1, still open |
| FMT-MIN-5 table env | FMT-MIN-3, still open |
| FMT-MIN-7 anonymize | FMT-MAJ-3, still open (upgraded to major) |
| FMT-MIN-10 title page date | FMT-MIN-4, still open |
| FMT-SUG-1 notation table | FMT-SUG-1, still open |
| FMT-SUG-2 algorithm to appendix | FMT-SUG-2, still open |

R7 critical 118.9pt overfull closed. No new critical or major findings
introduced by R8 content (E1/E3/E4 integrations) beyond what already
existed.
