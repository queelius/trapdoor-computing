# Format Validator (2026-04-13)

## Scope

Build verification, label resolution, table/figure presence, document class, structural integrity.

## Build verification

```
pdflatex main.tex; bibtex main; pdflatex main.tex; pdflatex main.tex
EXIT=0
Output written on main.pdf (19 pages, 348806 bytes).
```

No errors. No undefined references. No undefined citations. No overfull boxes flagged. Build is clean.

## Cross-reference integrity

- Total `\label{}` declarations: 54
- Total `\Cref{}`/`\ref{}`/`\cref{}` references: 17 unique label keys
- Labels never referenced: 37 (mostly definition/theorem/example labels, expected behaviour)
- References to nonexistent labels: 0

All cross-references resolve.

## Citation integrity

- Total bib keys: 21
- Total `\cite{}` invocations: 29 (some keys cited multiple times)
- Bib keys never cited: 0
- Citation keys without bib entries: 0

All citations resolve.

## Tables and figures

- Numbered tables: 1 (`tab:boolean-search` at lines 1324-1339)
- Unnumbered tables: 1 (granularity table, lines 1366-1376, in a `center` environment without table caption)
- Figures: 0

### FV-CF-1. Granularity table unnumbered (carry-forward of m7/prior m5)

The granularity table at lines 1366-1376 uses `\begin{center}\begin{tabular}` without `\begin{table}` wrapping. As a result it has no caption, no number, no label, and cannot be referenced.

**Suggestion**: promote to `\begin{table}[ht]\centering\caption{...}\label{tab:granularity}...\end{table}`. The 2026-04-08 review flagged this; 2026-04-12 review flagged this; 2026-04-13 not addressed.

### FV-CF-2. Zero figures (carry-forward)

A 19-page theoretical paper with zero figures is unusual. Candidate figures:
1. Orbit-closure illustration in §5.
2. Cut-point structure showing both realizations side by side in §6.3.
3. Log-scale FPR-vs-chain-length plot in §7.3.

**Suggestion**: at minimum, one figure for the cut-point structure would visually carry the unification message that §6.3 makes textually.

## Document class and venue formatting

### FV-CF-3. Wrong document class for PLAS (carry-forward of M7)

```
\documentclass[11pt]{article}
```

PLAS at CCS uses ACM `sigconf` via `acmart`. Article class is not accepted in submission.

Status: not addressed in 2026-04-13. The state file notes that this is "pending venue commitment". Acceptable as long as venue commitment happens before submission.

For IACR ePrint or arXiv, article class is fine.

## Page count and length

- Page count: 19 (was 17 in 2026-04-12).
- Length growth between 2026-04-12 and 2026-04-13: ~2 pages, consistent with the §6.3 expansion (Definition 6.3, mapping/leakage/typed-chain/bound paragraphs, Example 6.1) and the §5.3 entropy-form rewrite.

If PLAS sigconf, the equivalent length will be approximately 12-13 pages, likely within typical PLAS limits but worth verifying once the swap to acmart happens.

## Notation collisions

### FV-NEW-1. delta vs delta_T (carry-forward of m1)

- `delta` = TV distance (representation uniformity), introduced at line 237.
- `delta_T` = Turing machine transition function, introduced at line 966.

Both are used together in §6.1. No actual ambiguity in context, but a reader has to switch interpretations. Suggestion: rename TM transition.

## Structural integrity

The section structure matches the abstract and the introduction's contributions list:

- §1 Introduction : present.
- §2 Related Work : present, five paragraphs.
- §3 Preliminaries : present.
- §4 Cipher Type Constructors : present, four subsections (void/unit, products, sums, exponentials).
- §5 Orbit Closure and Information Leakage : present, five subsections (def, monotonicity, conf bound, examples, typed chains).
- §6 Realizing Cipher Programs : present, three subsections (cipher TM, expression tree, cut-point structure).
- §7 Cipher Boolean Algebra and Evaluation : present, three subsections.
- §8 Discussion : present.
- §9 Conclusion : present.
- Acknowledgments : present.
- Bibliography : present.

All section labels (`sec:intro`, `sec:related`, ..., `sec:cipher-bool`) referenced in the body resolve.

## Theorem environment usage

- Definitions: 9 (`def:cipher-map`, `def:machines`, `def:orbit`, `def:typed-chain`, `def:cipher-tm`, `def:cipher-node`, `def:cut-point`, `def:cipher-bool`, plus internal).
- Theorems: 2 (`thm:sum-impossibility`, `thm:monotonicity`, `thm:confidentiality-bound`). Wait, that's 3.
- Propositions: 5 (`prop:product-tradeoff`, `prop:typed-orbit`, `prop:cipher-tm-space`, `prop:head-determinism`, `prop:noise-unreliability`).
- Corollaries: 2 (`cor:empty-ops`, `cor:confidentiality-set`).
- Remarks: 8.
- Examples: 6.

Numbering uses `[section]` counter for definitions, examples, and remarks; theorems/propositions/corollaries share a single counter scoped to section. The numbering displayed in the PDF should be consistent. Spot-checking: Theorem 5.3 (entropy bound) is the third numbered formal result in §5; Theorem 5.1 is monotonicity; Corollary 5.2 is empty-ops. Numbering is consistent.

## Hyperref behavior

`\usepackage[numbers,square]{natbib}` plus `\usepackage{hyperref}` plus `\usepackage{cleveref}`. The `hypertexnames=false` option is set. Cleveref produces "Theorem 5.3" rather than just "5.3" for `\Cref{thm:confidentiality-bound}`. Style is consistent with PLAS and IACR conventions.

## Verdict

Build is clean. Cross-references resolve. Bibliography integrity is intact. Three findings:

- FV-CF-1: granularity table needs to be promoted to a numbered table. Easy fix.
- FV-CF-2: zero figures, suggest at least one cut-point diagram. Moderate fix.
- FV-CF-3: document class is article, needs swap to acmart for PLAS. Pending venue commitment.

No new format-level defects introduced by the 2026-04-13 second-round fixes.
