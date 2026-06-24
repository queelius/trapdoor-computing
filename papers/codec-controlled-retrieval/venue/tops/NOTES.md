# ACM TOPS version notes

The ACM TOPS (Transactions on Privacy and Security) build of `towell2026codec`. Status
is in the top-level `SUBMISSIONS.md`; this file holds the venue-specific mechanics.

## What this is
- `main.tex` + `refs.bib`: the TOPS submission source, derived from the canonical
  `../../paper/codec_retrieval.tex` + `../../paper/refs.bib` (the content source of truth).
- Build: `make` (pdflatex; bibtex; pdflatex x2). Needs `acmart.cls` (in TeX Live).
- Current: 30 pages, 0 errors, 0 undefined, 0 overfull boxes. **Refinements are in-body**
  (the whole reason we chose this venue over PoPETs).

## Why TOPS (vs the PoPETs build)
- **Rolling deadline** (no fixed registration to miss, which is what closed the PoPETs window).
- **No 12-page cap and no per-page overlength fees** (TOPS limit is 35 pages total; we are at
  30). So the cogirth-robustness, randomized-encoding, and graded-codec refinements stay
  first-class **in the body** (no appendix demotion, unlike `../popets/`).
- IEEE TIFS was the first pick but charges ~$220/page overlength from page 11 (~$900-1400
  here); TOPS has the same privacy scope with no such fee.

## Differences from the canonical version
1. **Format**: `acmart` `acmsmall` (single-column ACM journal) instead of `article`. acmart
   provides amsmath/amsthm/booktabs/hyperref/natbib; we add mathtools/amssymb/cleveref, fix
   the amssymb `\Bbbk` clash, and define `remark` (acmart predefines the others). Single-column,
   so the 2-column overflow fixes the PoPETs build needed do not apply here.
2. **AI disclosure**: a `\section*{Disclosure of generative AI use}` added before the
   bibliography, per ACM's generative-AI policy.
3. **NOT anonymized** (see below). The body is the canonical text (refinements in-body).

## Blinding: CONFIRM before submitting
TOPS's review model (single-blind vs double-anonymous) was not confirmable from public pages
(ACM DL returned 403). This build is **de-anonymized** (real author block; matches canonical;
correct if TOPS is single-blind). **If TOPS requires double-anonymous review**, do this:
- Add `anonymous` to the documentclass: `\documentclass[acmsmall,review,anonymous]{acmart}`
  (hides the author block and adds line numbers).
- Apply the same body anonymization deltas used in `../popets/` (they are documented there and
  in `../popets/NOTES.md`): neutralize the in-body "the author's X" to third person, scrub the
  repo name, and anonymize the two self-citations (`towell_bernoulli_maps`, `towell2026ciphermaps`)
  in a forked `refs.bib` (author = Anonymous, "omitted for double-blind review"). The exact edits
  are in `../popets/main.tex` and `../popets/refs.bib`. (Ask the assistant to apply them; ~2 minutes.)

## Length
30 pages (acmsmall). TOPS rejects over 35 pages without review; we are comfortably under,
with no per-page fees.

## AI-disclosure text for the submission system (if ACM asks on the form)
> This submission used LLM-based tools: (1) drafting/editing by an agentic multi-tool
> writing-and-review system, all reviewed and approved by the authors; (2) all theorems,
> proofs, bounds, and numbers verified by the authors against the artifact's computational
> gates and result files (no result originated from an LLM); (3) LLM-assisted literature
> search and some BibTeX drafting, each verified against primary sources (one LLM-introduced
> author-list error was caught and corrected). The authors take full responsibility; no AI
> system is an author.

## Re-deriving after a canonical content change
If `../../paper/codec_retrieval.tex` changes, re-apply the format deltas above (preamble swap,
AI disclosure). The body is otherwise identical to canonical, so most content edits can be
copied directly.
