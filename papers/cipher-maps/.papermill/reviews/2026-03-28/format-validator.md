# Format Validator Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper builds cleanly with no errors or warnings. All cross-references resolve. The bibliography compiles correctly. However, the paper does not use the PoPETs/PETS template, which would be required for submission.

## Findings

### MAJOR: Wrong document class for PoPETs

- **Location**: Line 1 of cipher_maps.tex
- **Quoted text**: `\documentclass[11pt]{article}`
- **Problem**: PoPETs uses its own LaTeX template based on the `scitepress` or `popets` class (or the ACM `acmart` class with PoPETs-specific options, depending on the submission year). The current paper uses `article` with 1-inch margins, which produces a different layout. PoPETs papers typically have 2-column format or a specific single-column format with specific margin and font requirements. The paper would need to be reformatted for submission.
- **Severity**: MAJOR (for submission; not a content issue)
- **Confidence**: HIGH
- **Suggestion**: Download the PoPETs 2027 LaTeX template from the PoPETs website and reformat. Key changes: document class, page limits (typically 20 pages in PoPETs format, which is different from 20 pages in article format), bibliography style, author block format.

### MINOR: Page count may exceed PoPETs limit after reformatting

- **Location**: The paper is currently 19 pages in article class with 1-inch margins
- **Problem**: PoPETs papers are typically limited to ~20 pages in the PoPETs template, which has different line spacing and margins. 19 pages in `article` class with 1-inch margins may expand or contract when reformatted. The paper needs to be tested in the target template.
- **Severity**: MINOR
- **Confidence**: MEDIUM
- **Suggestion**: Reformat in the PoPETs template early to assess page count.

### MINOR: No anonymization infrastructure

- **Location**: Line 39
- **Quoted text**: `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`
- **Problem**: PoPETs uses double-blind review. The paper includes the author name and email in the author block. Submission would require removing these.
- **Severity**: MINOR (trivial to fix)
- **Confidence**: HIGH

### Build Report

| Check | Result |
|---|---|
| Clean build | PASS (0 errors, 0 warnings) |
| Pages | 19 |
| Output size | 358,128 bytes |
| All \ref resolved | PASS |
| All \cite resolved | PASS |
| No multiply-defined labels | PASS |
| No hyperref collisions | PASS (hypertexnames=false set) |
| Algorithm package | PASS (algorithm, algpseudocode) |
| Bibliography compiles | PASS (plainnat style) |

### TikZ Figures

Two TikZ figure source files exist in `paper/img/`:
- `fig_shmap.tex` (Singular Hash Map figure)
- `fig_shs.tex` (Singular Hash Set figure)

Neither is included in the paper. These may be from an earlier version and may not compile with the current document structure. If figures are to be added, these should be tested.

### Package Usage

The paper uses standard packages: amsmath, amssymb, amsthm, mathtools, natbib, booktabs, hyperref, cleveref, algorithm, algpseudocode. No PoPETs-specific packages are loaded. The tikz package is NOT loaded despite TikZ figure files existing.
