# Format Validator Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Build**: `make` (pdflatex x3 + bibtex)

## Summary

Build is clean. No undefined references, no multiply-defined labels, no
bibtex warnings. Four minor overfull hboxes (max 14.3pt), all cosmetic;
the R7-era 118.9pt overfull stays closed. Page count is 39 (up 1 from R8's
38, due to the new Proposition). The submission blockers are the standing
trio: article class (not PoPETs template), page count over target, and
non-anonymized author block.

**Counts**: Critical 0 | Major 3 | Minor 4 | Suggestions 1.

## Build health (PASS)

- Output: cipher_maps.pdf, 39 pages, 527,677 bytes.
- Undefined references: 0.
- Multiply-defined labels: 0.
- Undefined citations: 0. bibtex: 0 warnings.
- Overfull hboxes: 4. Worst 14.3pt; others 7.8pt, 4.4pt, 1.3pt. The new
  Proposition introduced no severe overfull. R7 critical 118.9pt remains
  closed.
- The new label prop:homophonic is defined once, used 0 times via
  \ref/\Cref. Unreferenced labels are harmless (the proposition is
  introduced by "The following proposition"); no action required.

## FMT-MAJ-1: Article class, not PoPETs template (carry-over R5-R8)

Line 1: `\documentclass[11pt]{article}` with 1-inch margins. PoPETs
requires their two-column ACM-derived template. Porting will change the
page count materially and is a prerequisite for submission. Estimated
4-8 hours. (carry-over R8 MAJ-4)

## FMT-MAJ-2: Page count 39 vs PoPETs target (carry-over R7-R8)

39 pages in article class. After template port, expect ~26-30 pages, over
the 18-20 PoPETs target. Needs an 8-10 page trim. Candidates: section 9.1
(Bernoulli relationship), section 9.4 (bounded composition, to appendix),
section 10.4 (deniability, to appendix), section 10.5 (future
investigations, compress), Algorithm 1 (to appendix). (carry-over R8 MAJ-5)

## FMT-MAJ-3: Author block not anonymized for double-blind (carry-over R7-R8)

- Line 48: `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`
- Line 2325: `\url{https://github.com/queelius/cipher-maps}` (identifying)
- Line 2854-2855: acknowledgments reference "the author's earlier work"
- Companion citations towell2026* reveal authorship
PoPETs is double-blind. Anonymize before submission. Estimated 1-2 hours.
(carry-over R8 MAJ-6)

## FMT-MIN-1: cleveref loaded but barely used

116 `\ref{`, 53 `\S\ref{`, 0 `\cref{`, only 4 `\Cref{`. The paper loads
cleveref but uses raw `\ref` and `\S\ref` almost everywhere. Standardize on
`\Cref`/`\cref` for consistency, or drop cleveref. Cosmetic. (carry-over)

## FMT-MIN-2: Integration comment markers in source

Six `% [INTEGRATION 2026-05-07]` / `% [/INTEGRATION ...]` markers remain.
Strip before submission. (cross-listed prose PROSE-MIN-5)

## FMT-MIN-3: Title page date stale

Line 49: `\date{March 2026}`. Update to submission date (or remove for
anonymized submission). Minor. (carry-over)

## FMT-MIN-4: Inline tables not wrapped in table environment

Several tables (section 6.4 construction-time, section 6.6 bucketing,
section 7.1 AND-gate, section 10.1 parameter instantiation) use bare
`\begin{center}\begin{tabular}` without a `table` float or caption. Wrap
for consistent numbering and placement. Minor. (carry-over)

## FMT-SUG-1: Notation table near section 3

A short notation/glossary table (fhat, enc, dec, s, eta, eps, delta, mu,
K(x), D(x), alpha(y), N, p, n/M) near section 3 would help the reader and
would have surfaced the kappa(y) and n-vs-M slips found this round.
(carry-over)

## Bottom line

The build is production-clean and the overfull situation is well under
control. The three submission blockers (template, page count,
anonymization) are all carry-overs the user already plans to handle in a
pre-submission editorial pass. Nothing in the build itself blocks progress.
