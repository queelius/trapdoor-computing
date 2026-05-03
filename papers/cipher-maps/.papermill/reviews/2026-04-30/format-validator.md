# Format Validator Report (Round 5, 2026-04-30)

**Specialist**: format-validator
**Manuscript**: cipher_maps.tex (1841 lines)
**PDF**: cipher_maps.pdf (26 pages, 427 KB)
**Bibliography**: references.bib (31 entries)

## Summary

The build is clean with no errors or undefined references. The R5 TikZ
figure (acceptance partition) renders correctly. Citation count is
reasonable (28 cited of 31 in bib). Page count of 26 is appropriate
for a 10-section theory paper targeting PoPETs.

Two stylistic format concerns: the document class (article, not
PoPETs) and the lack of a venue-specific anonymization pass. Neither
blocks current evaluation but both are pre-submission requirements.

**Findings**: 0 critical, 1 major, 6 minor, 4 suggestions.

## Critical findings

None.

## Major findings

### FMT-1 (Major): Document class is `article`, not PoPETs format

**Location**: line 1
**Quoted text**: `\documentclass[11pt]{article}`

**Problem**: The state file targets PoPETs 2027 (`venue.target` field).
The PoPETs venue uses a specific document class (`sigplanconf` historically,
or a recent PoPETs class). Submitting in plain `article` would require a
template port that may surface formatting issues (margin fit, theorem
environments, citation style). Better to do the port now and catch
issues early than at submission deadline.

The R4 next-actions list flagged this as `nm17` ("Test-build with
PoPETs template"). It remains unaddressed.

**Suggestion**: Download the PoPETs 2027 template (or use the most
recent available), copy `cipher_maps.tex` into it, and run a
test-build. Common issues to watch for:
- Theorem environment numbering (some venue classes redefine).
- Bibliography style (`plainnat` vs PoPETs's preferred style).
- Paragraph spacing (PoPETs typically tighter than `article` 11pt).
- Hyperref behavior (some classes load it differently).
- Algorithm package compatibility.

This may surface additional format fixes; doing it now is cheap (one
day of work) and prevents last-minute surprises.

## Minor findings

### FMT-2 (Minor): Three uncited bib entries (dead weight)

**Location**: references.bib
**Entries**: `esposito2020recsplit`, `kerschbaum2015frequency`, `kamara2019computationally`

**Problem**: BibTeX log shows 28 entries used; the bib has 31. The
three uncited entries are flagged in the citation-verifier report as
CITE-3, CITE-4, CITE-5 (each should be cited per the recommendations
there).

If they are kept uncited, they should be removed from the bib. Cleaner:
add the citations as the citation-verifier suggests.

**Suggestion**: Add the citations per CITE-3, CITE-4, CITE-5 (this is
the load-bearing fix). If for some reason they cannot be cited, remove
them from the bib.

### FMT-3 (Minor): Overfull hbox at lines 1542-1549

**Location**: cipher_maps.log: "Overfull \hbox (4.3997pt too wide) in paragraph at lines 1542-1549"

**Problem**: One overfull hbox of 4.4pt. Located in §8.2 (Compositional
Leakage), in the "Mitigation strategies" description list. The visual
impact is minor (4pt is roughly one character width), but PoPETs
production may flag it.

**Suggestion**: Adjust the wording slightly in lines 1542-1549. Likely
candidate: insert a manual line break or reword "Construct a single
cipher map for the composed function $g(x) = f_3(f_1(x), f_2(x))$ as
one batch construction." The em-style joins of "f_3(f_1(x), f_2(x))"
are the likely culprit.

### FMT-4 (Minor): No author affiliation in `\author{}`

**Location**: line 48
**Quoted text**: `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`

**Problem**: PoPETs requires author affiliation for non-anonymous
submissions. Currently only name and email are shown.

**Suggestion**: Add affiliation line:
`\author{Alexander Towell\\Southern Illinois University Edwardsville\\\texttt{lex@metafunctor.com}}`

Or use the venue's `\affiliation{}` command if available.

### FMT-5 (Minor): No anonymization for double-blind review

**Location**: throughout (author name in title, "the author's earlier
work" in Acknowledgments, repeated `towell2026XXX` self-citations)

**Problem**: PoPETs uses double-blind review. The current draft is
fully attributed:
- `\author{Alexander Towell...}` on line 48
- `\section*{Acknowledgments}` lines 1833-1836: "the author's earlier
  work on the Bernoulli data type library and the trapdoor Boolean
  algebra"
- 8 in-text citations to `towell2026XXX` papers (clearly self-citations)
- 5 in-text citations to `bernoulli-types` (also self-citation)

For double-blind submission, all of these need anonymization:
- `\author{Anonymous}` (or whatever PoPETs convention is)
- Replace acknowledgments with placeholder
- Replace self-citations with `[cite anonymized]` or recast as
  "Companion work [Author 2026a]" with anonymized refs.

**Suggestion**: The R4 next-actions (`nm18`) flagged this. Address
before submission. Note: anonymizing self-citations to unpublished
work is awkward; one common practice is to cite the work as
"[Author 2026]" with an annotation "(reference anonymized for review)."

### FMT-6 (Minor): Bibliography style inconsistency

**Location**: line 1838
**Quoted text**: `\bibliographystyle{plainnat}`

**Problem**: `plainnat` is fine for `natbib` numbered citations, but
the paper uses `[numbers,square]{natbib}` (line 7), which suggests
square-bracket numbered citations. `plainnat` produces author-year
formatted entries that may not look right with `[numbers]` mode.

The PDF actually renders [N] style citations because of the package
options, but the bibliography entries use the author-year layout from
plainnat. The result is mixed: cite mark `[3]` resolves to a
plainnat-formatted entry. Functionally OK but stylistically inconsistent.

**Suggestion**: Switch to `\bibliographystyle{abbrvnat}` or
`\bibliographystyle{IEEEtranN}` (or whatever PoPETs uses). At minimum,
verify that the bibliography section visually matches the citation
style in the body.

### FMT-7 (Minor): No DOI fields anywhere in the bibliography

**Location**: references.bib (all 31 entries)

**Problem**: Citation-verifier CITE-7 confirms no DOI fields. PoPETs
PC increasingly expects DOI-resolvable entries. Many of the cited
works have DOIs available via crossref.org.

**Suggestion**: Add DOI fields. ~1 hour of mechanical work. Already in
state file next-actions as `m11`.

## Suggestions

- **FMT-S1**: The TikZ figure (`fig:acceptance-partition`) at lines
  823-880 is well-drawn and renders correctly. One small improvement:
  the labels `$A(y_1)$`, `$A(y_2)$`, `$A(y_3)$` are at the same y-coord
  as the bracket annotations below the figure; the spacing is tight.
  Consider increasing the vertical separation by ~5pt.

- **FMT-S2**: The two tables (Table 1 parameters, Table 2 confidentiality
  bounds) use `booktabs` correctly. Consider numbering captions as
  "Table 1: Cipher map parameters." (with colon) for consistency with
  many crypto venue conventions; currently they use period only.

- **FMT-S3**: The Algorithm 6.3 (`alg:singular-hash`) is the only
  algorithm in the paper. Consider naming it more descriptively (e.g.,
  `alg:batch-cipher-map`) since the title in the algorithm caption
  says "Batch Cipher Map Construction" but the label is
  `alg:singular-hash` (legacy from a previous draft, presumably).

- **FMT-S4**: The `cleveref` package is loaded (line 11) and used once
  at line 917 (`\Cref{fig:acceptance-partition}`). The rest of the
  paper uses `\ref{}`, `\S\ref{}`, `Theorem~\ref{}`, etc. Consider
  either removing `cleveref` (if unused beyond one place) or migrating
  to `cleveref` consistently. Currently it's a minor inconsistency.

## Verification matrix

| Check | Result |
|---|---|
| Document compiles cleanly (pdflatex x3 + bibtex) | OK |
| No undefined references | OK |
| No undefined citations | OK |
| No missing labels | OK |
| Bibliography resolves all `\cite` calls | OK |
| Figure renders | OK (Fig 1 acceptance partition, TikZ-based) |
| Algorithm renders | OK (Alg 6.3) |
| Tables render | OK (3 tables: parameters, guarantees, alpha-eta) |
| Hyperref links work | OK (213 named destinations in PDF) |
| Page count reasonable | OK (26 pages, target PoPETs ~14-20pp; trim needed for venue but OK for review draft) |
| Cross-paper citations resolve to bib | OK (3 manuscript-in-prep entries) |
| Internal `\ref` and `\cref` consistent | OK (1 `\Cref`, rest `\ref` style) |
| Author info present | Partial (no affiliation) |
| Anonymization for double-blind | NOT DONE |
| Venue template applied | NOT DONE (article class) |
| DOIs in bib | NOT DONE |

## Build hygiene

- `cipher_maps.aux`: 22 KB, looks normal (high label count due to
  many theorems / propositions / definitions / cross-refs).
- `cipher_maps.bbl`: 8.4 KB, 28 entries formatted.
- `cipher_maps.blg`: 927 bytes, no warnings.
- `cipher_maps.log`: 33 KB, one Overfull hbox warning (FMT-3 above),
  no other issues.
- `cipher_maps.out`: 7.3 KB hyperref bookmarks, looks complete.
- `cipher_maps.pdf`: 428 KB for 26 pages with one TikZ figure. Reasonable.

## Page count vs PoPETs limits

PoPETs 2027 (per the recent CFPs) typically allows 18-20 pages
exclusive of bibliography and appendices. Current: 26 pages including
bibliography. Without bibliography (which spans ~3 pages) the body is
~23 pages.

This will need a trim of ~3-5 pages for PoPETs format. Candidate
sections to compress:
- §2 (Related Work) currently spans ~4 pages with paragraph headers
  for each subtopic; could be tightened.
- §6.4 (Construction Time and Bucketing) has multiple tables and
  could be condensed.
- §9.4 (Application: Encrypted Search) has duplicated experimental
  paragraphs (PROSE-7 issue).
- §9.6 (Open Questions) has 6 items that could be a paragraph.

The PoPETs trim is a separate task from current review.

## Recommendation

The R5 build is clean. The TikZ figure renders correctly. Citation
hygiene is mostly fine (3 dead-weight entries to be cited per CITE-3
through CITE-5). The principal format issues are pre-submission tasks:
PoPETs template port (FMT-1), anonymization (FMT-5), DOI fields
(FMT-7).

No critical format issues block the current review iteration. The
content is presentable in its current `article`-class form for further
revision rounds.

For PoPETs submission specifically, FMT-1 (template port) should
happen before page-count optimization, since the template will affect
how much content fits per page.
