# CSF version notes

The CSF-tailored build of "The Entropy Ratio." Canonical status lives in
`../../.papermill/state.md`; this file holds the venue-specific mechanics.
Re-derived 2026-06-13 from the round-2 canonical (commit 018583b).

## What this is
- `main.tex` + `refs.bib`: the CSF submission source, derived from the
  canonical `../../main.tex` + `../../references.bib` (the de-anonymized,
  full, single-column article-class version, which stays the content source
  of truth). Most of the port is produced by a deterministic script; see the
  re-application note at the bottom.
- Build: `make` (pdflatex; bibtex; pdflatex x2). Needs `IEEEtran.cls` and
  `IEEEtranN.bst` (both in TeX Live).

## CSF format requirements (CSF 2026 CFP; format stable across years)
Two-column IEEE Proceedings style; body at most 12 pages EXCLUDING
bibliography and well-marked appendices; double-blind review. Re-verify
against the CSF 2027 CFP once posted.

## Differences from the canonical version (the venue tailoring)
1. **Format**: `IEEEtran` `conference` 2-column instead of `article` 11pt.
   amsthm theorems and the cipher-map macros kept; `geometry` dropped;
   natbib retained with the natbib-compatible `IEEEtranN.bst`, so the
   existing `\cite` commands and numbered style render unchanged.
2. **Length**: body is 12 pages (conclusion ends p12; appendices p13+; bib
   last). Five blocks are moved to clearly-marked appendices, with the
   affected cross-references repointed:
   - Appendix A: Practical Measurement (compression estimator, Monte Carlo,
     leakage analyzer, finite-sample resolution, empirical anchor).
   - Appendix B: Error Compounding in Boolean Chains (the FPR/correctness
     facet of composition; defines $p_T$).
   - Appendix C: Encrypted Boolean Search Evaluation (was the search demo).
   - Appendix D: Encoding Granularity (Experiment).
   - Appendix E: Homophonic Encoding Evaluation.
   The headline theory stays in the body: the two scales, the Fannes bridge,
   the full Assouad lower-bound proof, and the FPR / Monte-Carlo /
   realized-attack / case-study results that anchor the abstract.
   (Two more experiment blocks moved than the first port: the round-2
   canonical added ~1pp of remarks, so the body needed more headroom.)
3. **Anonymization** (double-blind): author block "Anonymous Author(s)";
   PDF author metadata empty; in-body self-references are neutral third
   person; the two self-citations anonymized in this `refs.bib`
   (author = Anonymous; GitHub URL and Zenodo DOI removed); AND the in-body
   artifact URL `github.com/queelius/...` replaced with an
   `anonymous.4open.science` link.
   **LESSON (round-1 false negative):** a line-based `pdftotext | grep`
   MISSED the artifact URL, because `xurl` line-breaks the URL across the
   2-column layout and grep is line-based. Always sweep with the lines
   JOINED: `pdftotext main.pdf - | tr -d '\n' | grep -ciE "queelius|towell|..."`.
   Current sweep (joined) returns 0.
4. **2-column polish**: the five wide tables wrapped in
   `\resizebox{\columnwidth}{!}{...}`; the two multi-equality display chains
   in the noise and Assouad proofs broken with `aligned`;
   `\emergencystretch` set. Zero overfull boxes over 20pt remain (three
   small sub-20pt boxes are cosmetic).
5. **Seam fixes** (after the appendix moves): the section-6 opening no longer
   says "we treat both facets in this section" (it defers the correctness
   facet to Appendix B); $p_T$ is defined in the body FPR experiment before
   first use (its full development is Appendix B); the Contribution-1 FPR
   pointer now targets Appendix B, not section 6.

## Remaining before submission (not blocking the build)
- **AI-use disclosure** and a brief **ethics / responsible-disclosure**
  statement as back matter (excluded from the page count), once the CSF 2027
  CFP confirms the requirements (IEEE security venues increasingly expect
  both, the latter for attack-flavored papers).
- Minor seam-audit polish (each a one-line patch): expand FPR on first use
  in the abstract; tag the appendix-resident figures with their appendix in
  the reproducibility manifest; one orienting sentence atop Appendix A.

## Re-applying after canonical changes
The structural port is scripted (Python): copy `../../main.tex` to
`main.tex` and `../../references.bib` to `refs.bib`, then (a) swap the
preamble / frontmatter / bibliography to the IEEEtran/anonymized forms,
(b) move the five blocks above into `\appendices` (retitling each leading
`\subsection` to `\section`), (c) repoint the `\S\ref`/`Section~\ref` to
`sec:measurement`, `subsec:fpr-compounding`, `subsec:finite-sample` to
`Appendix~\ref`, (d) anonymize the two `refs.bib` self-cites and the
in-body artifact URL, (e) wrap the five wide tables in `\resizebox` and
break the two display chains, then re-apply the seam fixes in section 5
above. Verify: body <= 12pp (conclusion page from `main.aux`), 0 undefined
refs, line-joined anonymization sweep = 0.
