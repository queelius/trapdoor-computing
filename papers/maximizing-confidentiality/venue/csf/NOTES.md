# CSF version notes

The CSF-tailored build of "The Entropy Ratio." Canonical status lives in
`../../.papermill/state.md`; this file holds the venue-specific mechanics.

## What this is
- `main.tex` + `refs.bib`: the CSF submission source, derived from the
  canonical `../../main.tex` + `../../references.bib` (the de-anonymized,
  full, single-column article-class version, which stays the content source
  of truth).
- Build: `make` (pdflatex; bibtex; pdflatex x2). Needs `IEEEtran.cls` and
  `IEEEtranN.bst` (both in TeX Live).

## CSF format requirements (from the CSF 2026 CFP; format stable across years)
Two-column IEEE Proceedings style; body at most 12 pages EXCLUDING
bibliography and well-marked appendices; double-blind review. Re-verify
against the CSF 2027 CFP once it is posted.

## Differences from the canonical version (the venue tailoring)
1. **Format**: `IEEEtran` `conference` 2-column instead of `article` 11pt.
   Kept the amsthm theorem environments and the cipher-map macros; dropped
   `geometry` (IEEEtran sets its own); natbib retained with the
   natbib-compatible `IEEEtranN.bst`, so the existing `\cite` commands and
   the numbered style render unchanged.
2. **Length**: body trimmed to 12 pages (bib + appendices excluded) by
   moving four blocks into clearly-marked appendices, with the affected
   section cross-references repointed to the new appendix labels:
   - Appendix A: Practical Measurement (the measurement methodology:
     compression estimator, Monte Carlo, leakage analyzer).
   - Appendix B: Error Compounding in Boolean Chains (inherited FPR context).
   - Appendix C: Finite-Sample Resolution of delta.
   - Appendix D: Empirical Anchor for the Compression Estimator.
   The headline theory stays in the body: the two scales, the Fannes bridge,
   and the full Assouad lower-bound proof.
3. **Anonymization** (double-blind): author block set to "Anonymous
   Author(s)"; PDF author metadata dropped; in-body self-references were
   already neutral third person ("the cipher map framework [X]"), so no
   prose change was needed; the two self-citations anonymized in this
   directory's `refs.bib` (author = Anonymous; GitHub URL and Zenodo DOI
   removed). `pdftotext main.pdf` shows zero author-identifying strings in
   the rendered PDF (the bibkeys still read `towell2026...`, but bibkeys are
   internal and never rendered).
4. **2-column polish**: the two wide comparison tables wrapped in
   `\resizebox{\columnwidth}{!}{...}`; `\emergencystretch` set to reduce
   prose overfull boxes.
5. **AI disclosure**: NOT yet added. IEEE/CSF may require a
   generative-AI-use statement; add it as back matter (excluded from the
   page count) once the CSF 2027 policy is confirmed.

## Re-applying after canonical changes
When `../../main.tex` changes substantively, re-copy it and re-apply the
deltas above: swap the documentclass / preamble / frontmatter / bibliography,
move the same four blocks into appendices, repoint the moved-label
cross-references (`sec:measurement`, `subsec:fpr-compounding`,
`subsec:finite-sample`), wrap the two wide tables, and re-anonymize
`refs.bib`.
