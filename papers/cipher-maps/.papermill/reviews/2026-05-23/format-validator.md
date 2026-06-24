# Format Validator Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Build status**: clean (36 pages, no undefined refs, no multiply-defined
labels; 5 overfull hboxes)

## Headline finding

Build remains clean with the same 5 overfull hboxes from R7. One is
severe (118.87pt at lines 1914 to 1919 in Definition 8.x). Page count
unchanged at 36 (PoPETs template port still pending). Article class
still in use, not PoPETs template. Anonymization not performed for
double-blind. Title date still says "March 2026".

## Build verification

```
$ cd paper && make 2>&1 | tail -10
make: Nothing to be done for 'all'.
```

The PDF (`cipher_maps.pdf`) is current relative to the .tex source.
Verified via timestamps and the `.log` file (`Output written on
cipher_maps.pdf (36 pages, 511521 bytes)`).

## R7 format issues, R8 status

### NOT FIXED (R7 MAJ-6): Article class, not PoPETs template
- **Location**: cipher_maps.tex line 1
- **Status**: `\documentclass[11pt]{article}` unchanged.
- **Required**: PoPETs uses a specific LaTeX template (Sciendo or
  similar; see https://petsymposium.org/cfp.php for the current
  template).
- **Suggestion**: Port to PoPETs template. Estimated trim to ~22 to 25
  pages.
- Severity MAJOR (carry-over).

### NOT FIXED (R7 MAJ-18): 118.87pt overfull hbox at Definition 8.x
- **Location**: Lines 1914 to 1919 (in
  `\begin{description}...\item[Pattern-coincidence attacker (private-codec threat).]`)
- **Status**: Unchanged.
- **Problem**: Long description-list label combined with long math
  expression overflows margin by approximately 1.6 inches; visible in
  PDF.
- **Suggestion**: Either (a) shorten the item label from
  "Pattern-coincidence attacker (private-codec threat)" to
  "Pattern-coincidence (private codec)", or (b) move the math
  expression after the label to display style.
- Severity MAJOR.

### NOT FIXED (R7 MAJ-19): 36 pages exceeds PoPETs target
- **Location**: Whole paper
- **Status**: Unchanged at 36 pages.
- **PoPETs target**: ~18 to 20 pages in their template. Article-class
  pages translate roughly to 22 to 25 PoPETs pages after template port.
- **Suggestion**: After PoPETs template port plus §9.1 (Bernoulli
  relationship), §9.4 (Bounded composition), §10.4 (Deniability) trim
  candidates, should reach ~20 PoPETs pages.
- Severity MAJOR (carry-over).

### NOT FIXED (R7 FMT-MIN-3): \Cref vs \ref mixed
- **Location**: Throughout paper (verified: 106 instances of \Cref or
  \ref combined; spot check shows both styles used)
- **Status**: Unchanged.
- **Suggestion**: Standardize on \Cref throughout (one-pass sed could
  do most of the work).
- Severity MINOR (carry-over).

### NOT FIXED (R7 FMT-MIN-5): Inline tables not in table env
- **Location**: §6.4 lines 1219 to 1229 (construction-time table), 1262
  to 1274 (bucketing table), §6.6 lines 1335 to 1347 (parameter
  instantiation table)
- **Status**: Unchanged. These are wrapped in `\begin{center}` rather
  than `\begin{table}` env. They lack `\caption` and `\label` and
  cannot be referenced via `\Cref`.
- **Suggestion**: Wrap in `\begin{table}[ht]` with appropriate caption
  and label.
- Severity MINOR (carry-over).

### NOT FIXED (R7 FMT-MIN-7): Author block not anonymized
- **Location**: cipher_maps.tex line 48
- **Status**: Unchanged. `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`
  is present.
- **Suggestion**: Anonymize for double-blind PoPETs submission. The
  PoPETs template typically has an option for this.
- Severity MINOR (carry-over).

### NOT FIXED (R7 FMT-MIN-10): Title page date stale
- **Location**: cipher_maps.tex line 49
- **Status**: `\date{March 2026}` unchanged. Today is 2026-05-23.
- **Suggestion**: Either update to current month or remove via
  `\date{}` for submission.
- Severity MINOR (carry-over).

## R8 new format findings

### FMT-N1 (NEW, MINOR): Three new overfull hboxes are mild
- **Location**: Lines 1679 to 1686 (4.4pt), 1832 to 1839 (18.3pt), 2251
  to 2260 (7.8pt), 2396 to 2402 (14.3pt).
- **Issue**: Four mild overfull hboxes (under 20pt each) exist
  alongside the severe one at lines 1914 to 1919. Could be addressed
  via minor wording adjustments or `\sloppy` blocks.
- Severity MINOR.

### FMT-N2 (NEW, MINOR): TikZ figure (acceptance partition) dimensions could improve
- **Location**: §6.6.1 lines 948 to 1005 (`\begin{figure}`)
- **Issue**: The TikZ figure for the acceptance partition is rendered
  in the article class. After PoPETs template port (two-column),
  the figure dimensions may need adjustment to fit a single column or
  be promoted to `figure*` for full-width.
- **Suggestion**: After template port, audit figure widths.
- Severity MINOR (deferred to template port).

### FMT-N3 (NEW, MINOR): Algorithm 1 placement
- **Location**: §6.5 lines 1065 to 1097
- **Issue**: Algorithm 1 (`\begin{algorithm}`) is in the main text
  body in §6.5. Could be moved to appendix for the PoPETs template
  to reduce main-text page count.
- Severity SUGGESTION.

### FMT-N4 (NEW, MINOR): hypersetup option `hypertexnames=false`
- **Location**: Line 9
- **Issue**: `\hypersetup{hypertexnames=false}` is a workaround for
  duplicate hyperref names, usually indicating an underlying
  structural issue with labels.
- **Status**: Build is clean, so the workaround is operationally fine.
  Could investigate at template port time.
- Severity SUGGESTION.

### FMT-N5 (NEW, INFORMATIONAL): bibtex is clean
- **Location**: cipher_maps.blg (no warnings)
- **Status**: Verified clean. 34 entries, no missing fields, no
  duplicate keys.
- Severity NONE (informational).

### FMT-N6 (NEW, INFORMATIONAL): theorem environment numbering is consistent
- **Location**: Lines 18 to 28 (preamble theorem definitions)
- **Status**: Verified consistent: `definition` numbered by section,
  `theorem/lemma/corollary/proposition` numbered jointly by section,
  `remark/example` numbered by section. Cleanly Theorem 5.1 ->
  Theorem 6.1 -> Theorem 6.2 etc. The label naming is mixed
  (`thm:lower-bound`, `prop:confidentiality`, `cor:t-geometry`) but
  the choices are conventional.
- Severity NONE (informational).

## Summary of format findings

- 0 critical
- 3 major carry-over from R7 (MAJ-6 article class, MAJ-18 118.87pt
  overfull, MAJ-19 36-page count)
- 5 minor carry-over from R7 (FMT-MIN-3 Cref/ref, FMT-MIN-5 inline
  tables, FMT-MIN-7 anonymization, FMT-MIN-10 stale date, plus the
  mild overfulls noted as FMT-N1)
- 2 minor new (FMT-N1 mild overfull hboxes, FMT-N2 figure dimensions)
- 2 suggestions new (FMT-N3 Algorithm 1 to appendix, FMT-N4 hypersetup
  workaround)
- 2 informational (FMT-N5 bibtex clean, FMT-N6 theorem numbering)

**Format-side recommendation**: All three majors require effort
beyond a quick polish: template port (4 to 8 hours), Definition 8.x
overfull fix (10 minutes), and page trim (4 to 6 hours). The minor
items are all quick fixes that can be batched with the template port.
After the template port, the page count should drop to ~22 to 25
PoPETs-template pages; with the suggested trims (§9.1, §9.4, §10.4),
should reach the ~20-page target.
