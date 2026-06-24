# Format Validator Report (round 3, 2026-04-29)

## Build verification

Fresh build from scratch:

```
pdflatex main.tex (pass 1) -> exit 0
bibtex main      -> exit 0
pdflatex main.tex (pass 2) -> exit 0
pdflatex main.tex (pass 3) -> exit 0
```

Final pass log scan for warnings/errors: NONE.

PDF metadata:

- Pages: 18
- Page size: 612 x 792 pts (letter)
- Producer: pdfTeX-1.40.25
- Creator: LaTeX with hyperref

The 18-page count matches the prompt and is up from rev2's 17 pages
by 1 page. The increase is consistent with today's added "Our
central observation" paragraph in §1 plus minor rewording of the §5
opener.

## Hyperref bookmark warnings

The prompt notes that all 5 hyperref bookmark warnings were cleared
via `\texorpdfstring` in the rev2 cleanup. Verification:

- §4 title `\section{Constructions for Reducing \texorpdfstring{$\delta$}{delta}}` (line 509). OK.
- §4.2 `\subsection{Multiple Representations \texorpdfstring{($K > 1$)}{(K > 1)}}` (line 579). OK.

Searching the build log for "Token not allowed in a PDF string"
(the canonical hyperref-bookmark warning text): NONE.

## Paragraph environment rendering

The prompt asks: "Paragraph environments (`\paragraph{Marginal scale.}`,
`\paragraph{Compositional scale.}`), do they render acceptably given
§1's existing `\paragraph{Contributions.}` and `\paragraph{What this
paper does not do.}` immediately after?"

§1 now has four `\paragraph{...}` environments in sequence:

1. `\paragraph{Marginal scale.}` (line 107)
2. `\paragraph{Compositional scale.}` (line 147)
3. `\paragraph{Contributions.}` (line 172)
4. `\paragraph{What this paper does not do.}` (line 207)

The article class renders `\paragraph` as bold inline text followed
by a period and the paragraph body on the same line. Four sequential
`\paragraph` headings are unusual but legal LaTeX. They render
correctly in the PDF. The visual rhythm in §1 is dense (a heading
every 30-50 lines), which is heavier than typical introductions.

This is a Suggestion-level item from the prose-auditor's perspective,
not a format-validator issue. The format-validator confirms the
paragraphs compile and render without issue.

## Reference resolution

All `\ref{...}` and `\cite{...}` calls resolve. From the log:

- Theorem references: thm:comp-leakage, thm:entropy-decomposition,
  thm:noise-dilution, thm:multiplicity, thm:fpr-compounding. All
  resolved.
- Section references: sec:intro, sec:related, sec:prelim,
  sec:measure, sec:levers, sec:composition, sec:measurement,
  sec:experiments, sec:discussion, sec:conclusion. All resolved.
- Subsection references: subsec:noise, subsec:multiple-reps,
  subsec:granularity, subsec:correlation-leakage. All resolved.
- Definition/Example references: def:cipher-map,
  def:observed-entropy, def:max-entropy, def:entropy-ratio,
  ex:homophonic. All resolved.
- Proposition references: prop:granularity, prop:compression. All
  resolved.

## Table formatting

Tables 1-4 unchanged. The booktabs format is consistent (toprule,
midrule, bottomrule). No \hline misuse.

## Findings (this round)

### New this round: NONE

The build is clean, no warnings, no errors. The two structural
changes (paragraph re-routing in §1, §5 retitle) compile correctly
and render acceptably. PDF page count increased from 17 to 18,
which is consistent with the added prose.

### Resolved across rounds

- **m10 (morning, hyperref bookmark warning)**: Resolved. Cleared
  via `\texorpdfstring` in rev2 cleanup.

### Carry-over

- **m11 (morning, zero figures)**: Open. Same status as prior rounds.
  A schematic of the trusted/untrusted model would help readers,
  but the paper functions without one.

## Summary

The build is clean at 18 pages. Zero warnings, zero errors. The
two structural changes from this round compile and render correctly
without regression. All references resolve.

**Recommendation from format-validator**: ready (no blocking
formatting issues). Optional: add a schematic figure (m11 carry-
over).
