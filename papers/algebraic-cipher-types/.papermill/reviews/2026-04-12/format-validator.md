# Format Validator Report

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp)
**Date**: 2026-04-12
**Scope**: Build verification, label resolution, venue formatting.

## Summary

The LaTeX build is clean. No warnings, no undefined references, no multiply-defined labels. All `\Cref` and `\ref` calls resolve to existing labels. The restructure preserved cross-reference integrity despite significant reorganization. Output is 17 pages in standard article class with 11pt/1in margins.

The paper remains in article class rather than a PLAS/CCS-appropriate format (ACM sigconf via acmart). This is M8 from the prior review and needs to be addressed before submission if PLAS is the target.

Minor issues: one table is unnumbered, hyperref is used but `hypertexnames=false` is set (fine, but non-default), zero figures in a 17-page paper is an outlier.

---

## Major Issues

### FV-MAJ-1. Document class mismatch for PLAS target (carry-forward of M8)

**Location**: Line 1 of main.tex: `\documentclass[11pt]{article}`.

**Problem**: PLAS (Programming Languages and Analysis for Security) is an ACM CCS workshop and typically uses the ACM sigconf style via `acmart`. Standard article class at 11pt/1in margins produces a wider two-column-less layout than PLAS expects. Submissions in the wrong format can be desk-rejected.

PLAS 2026 CFP should be checked for:
- Document class required
- Page limit (typically 10 to 12 pages in sigconf format)
- Anonymization requirement
- CCS concepts and ACM reference format

Given the 17 pages in article class, the paper may exceed page limits when reformatted to sigconf (which is denser and two-column, so 17 article pages typically maps to 10 to 12 sigconf pages; this is roughly aligned but needs verification).

**Suggestion**: Prepare a PLAS submission branch:

```latex
\documentclass[sigconf,nonacm=true]{acmart}
\settopmatter{printacmref=false}
```

Adjust:
- Replace `\title` and `\author` with `acmart` equivalents.
- Add `\begin{CCSXML}...\end{CCSXML}` and `\ccsdesc` for CCS concepts.
- Add `\keywords{...}`.
- Check that `natbib` is compatible with `acmart` (it is, but numbering style may differ).
- Verify page count after conversion.
- Check anonymization: PLAS may be double-blind; the paper currently has author name and email on the title.

Alternative: if IACR ePrint is the target, article class is fine but 17pp is long for a technical report. Not an issue.

### FV-MAJ-2. Unnumbered table breaks numbered-table convention (carry-forward of m5)

**Location**: Section 7.3, lines 1246 to 1256 (granularity table).

**Problem**: The paper has two tables reporting experimental results. Table 1 (lines 1204 to 1219) is a proper `\begin{table}` with `\caption`, `\label`, and booktabs formatting. The granularity table (lines 1246 to 1256) is a `\begin{center}\begin{tabular}...\end{tabular}\end{center}` without a caption, label, or number. This is inconsistent.

**Suggestion**: Promote to numbered table:

```latex
\begin{table}[ht]
\centering
\caption{Encoding granularity comparison on a 7-function loan approval pipeline (150 inputs).}
\label{tab:granularity}
\begin{tabular}{@{}lccc@{}}
\toprule
Level & Build time & Space & Intermediates \\
\midrule
...
\end{tabular}
\end{table}
```

Then reference as `\Cref{tab:granularity}`.

---

## Minor Issues

### FV-MIN-1. `hypertexnames=false` is non-default and unexplained

**Location**: Line 8: `\hypersetup{hypertexnames=false}`.

**Problem**: This disables hyperref's default name generation for anchors, in favor of counters. Sometimes needed to avoid conflicts (e.g., with chapter-less documents or custom theorem environments). It works here (no undefined refs), but adding a comment explaining why would help future authors.

**Suggestion**: Add a one-line comment: `% hypertexnames=false to avoid conflicts with theorem counters scoped by section`.

### FV-MIN-2. No figures at 17 pages (also noted by prose-auditor)

**Location**: Paper-wide.

**Problem**: Zero `\begin{figure}` environments. For a 17-page theoretical paper introducing orbit closure, typed chains, cipher Turing machines, and expression-tree decomposition, a figure or two would materially help. See PR-SUG-1 (prose-auditor) for specific suggestions.

### FV-MIN-3. `\cite[...]` multiple-argument citations

**Location**: Throughout (e.g., `\cite[Sec.~9]{towell2026cipher}` at line 312, `\cite[Prop.~9.1]{towell2026cipher}` at line 1015).

**Problem**: Multi-arg cites using section or proposition references to a specific page/section of a companion paper are fine in principle, but seven occurrences depend on an unpublished manuscript's internal numbering, which is fragile. See CV-MAJ-4.

### FV-MIN-4. Theorem numbering scheme spans sections

**Location**: `\newtheorem{theorem}{Theorem}[section]` at line 15.

Currently:
- Section 4: Prop 4.1, Thm 4.2
- Section 5: Thm 5.1, Cor 5.2, Thm 5.3, Prop 5.4
- Section 6: Def 6.1, Prop 6.1, Prop 6.2 (using section-based numbering)
- Section 7: Prop 7.1

This is consistent (theorem counter resets per section). No issue. Just noting that propositions/theorems/corollaries share a counter, which is standard AMS practice.

### FV-MIN-5. Definition counter: `\newtheorem{definition}{Definition}[section]`

**Location**: Line 13.

**Problem**: Definitions have their own counter per section. Remarks and Examples each have per-section counters as well. The mixing of counters (Def 4.1 but no Def 4.2 that's actually present; Remark 4.1, 4.2 in Section 4) is internally consistent but leads to some sparse numbering. No action needed; noting for completeness.

---

## Suggestions

### FV-SUG-1. Add a submission branch structure

For two target venues (PLAS, ePrint), maintain separate branches:
- `main`: current article class, target for ePrint.
- `plas-submission`: sigconf class, reformatted for PLAS CFP.

This allows tracking the two versions without forking the repository.

### FV-SUG-2. Consider `cleveref` plural handling

The paper uses `\Cref{sec:products,sec:sums}` and similar multi-label references. `cleveref` handles these nicely ("Sections 4.2 and 4.3"). All current usages resolve correctly. Ensure the `sort&compress` option is enabled if multi-reference ordering matters.

### FV-SUG-3. Page count after reformatting

At 17 pages in article class 11pt/1in, typical conversion to sigconf two-column 9pt produces roughly 60% to 70% of the original page count, so 10 to 12 sigconf pages. PLAS typical page limit is 12 pages for full papers. Should be within budget if no major expansions are made. If expansions are needed (more experiments, more references, more figures), may push to 13 to 14 pages. Budget conservatively.

---

## Build Verification

```
pdflatex main.tex  ->  0 errors, 0 warnings
bibtex main        ->  0 errors
pdflatex main.tex  ->  0 errors, 0 warnings
pdflatex main.tex  ->  0 errors, 0 warnings
Output: main.pdf, 17 pages, 316996 bytes
```

All labels resolve. No dangling `\ref` or `\Cref`. No multiply-defined labels. No overfull or underfull boxes in the log.

---

## Cross-cutting Observations

- **Build health**: Clean. No issues.
- **Label integrity**: Preserved through restructure.
- **Venue readiness**: Needs document class conversion for PLAS (FV-MAJ-1). Otherwise submission-ready structurally.
- **Figures/tables**: One numbered table (Table 1), one unnumbered table (granularity), zero figures. Promoting the unnumbered table and adding at least one figure would improve presentation.
- **Prior-review status**:
  - M8 (wrong document class for PLAS), **not addressed** (FV-MAJ-1).
  - m5 (unnumbered table), **not addressed** (FV-MAJ-2).
