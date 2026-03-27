# Format Validator Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Build Status

- **Compilation**: Successful (pdflatex + bibtex, 3-pass build)
- **Warnings**: 9 total
  - 6 hyperref warnings (tokens not allowed in PDF string) -- cosmetic, from math in section titles
  - 3 pdfTeX warnings (duplicate PDF destination identifiers for table.1, table.2, table.3)
- **Errors**: None
- **Undefined references**: None
- **Undefined citations**: None
- **Pages**: 20

## Findings

### F1. Duplicate PDF destination warnings (Minor, High confidence)
**Location**: Build log
**Problem**: Three warnings: "destination with the same identifier (name{table.N}) has been already used". This occurs because the paper has both `\begin{table}` environments (3 instances: lines 397, 733, 826) and `\begin{center}` environments containing tabulars (5 instances: lines 467, 553, 625, 698, 1027). The hyperref package assigns sequential table IDs to both, causing collisions.
**Suggestion**: Either wrap the center tabulars in `table` environments with captions (preferred -- they would then be numbered and referenceable) or suppress the duplicate destination warning with `\hypersetup{hypertexnames=false}`.

### F2. \date{\today} produces dynamic date (Minor, High confidence)
**Location**: Line 40
**Problem**: Every compilation produces a different date. For submission, the date should be fixed.
**Suggestion**: Replace with `\date{March 2026}` or the target submission date.

### F3. No venue-specific formatting (Minor, Medium confidence)
**Location**: Document class, line 2
**Problem**: The paper uses `\documentclass[11pt]{article}` with custom margins. No conference or journal template is used. This is fine for a working paper but will need reformatting for submission. The state file lists several candidate venues but none is selected.
**Suggestion**: When a venue is selected, reformat to the venue's template. For now, the article class is appropriate.

### F4. Hyperref token warnings from math in section titles (Minor, Low confidence)
**Location**: Build log (6 warnings)
**Problem**: Section titles containing math (e.g., "$\delta$-bounded") produce hyperref warnings about tokens not allowed in PDF strings. These are cosmetic and do not affect the output.
**Suggestion**: Use `\texorpdfstring` for section titles with math: e.g., `\subsection{Property 2: Representation Uniformity (\texorpdfstring{$\delta$}{delta}-bounded)}`.

### F5. Figures exist but are not included (Minor, High confidence)
**Location**: `paper/img/fig_shmap.tex`, `paper/img/fig_shs.tex`
**Problem**: Two TikZ figure files exist in the img/ directory but are not included in the paper via `\input` or `\includegraphics`. The paper has zero figures across 20 pages.
**Suggestion**: Include the figures using `\input{img/fig_shmap.tex}` and `\input{img/fig_shs.tex}` in appropriate locations (Section 7 for the Singular Hash Map, Section 5 for constructions).

### F6. Unnumbered tabulars lack reference labels (Minor, Medium confidence)
**Location**: Lines 467-480, 553-567, 625-637, 698-710, 1027-1038
**Problem**: Five parameter instantiation tables in the constructions section use `\begin{center}...\end{center}` with tabular environments. These are not numbered, captioned, or labeled, so they cannot be cross-referenced. The paper's three formal tables (Tables 1-3) are properly numbered and captioned.
**Suggestion**: Convert at least the parameter instantiation tables to numbered table environments, or acknowledge them as inline displays (which is acceptable for brief parameter summaries).

### F7. No page numbers or headers (Suggestion)
**Location**: Document class
**Problem**: The article class with default settings produces page numbers at the bottom center but no running headers. For a 20-page paper, running headers (author name / short title) would help navigation.
**Suggestion**: Add `\usepackage{fancyhdr}` with appropriate running headers if desired. This is a style preference, not a requirement.

## Overall Assessment

The paper builds cleanly with no errors and no undefined references. The main formatting issues are: (1) the three duplicate PDF destination warnings from mixed table/center environments, (2) the dynamic date, and (3) the absence of included figures despite existing figure files. These are all minor and straightforward to fix. The paper is in good shape for a working paper; venue-specific reformatting will be needed at submission time.
