# PoPETs version notes

The PoPETs-tailored build of `towell2026codec`. Status lives in the top-level
`SUBMISSIONS.md`; this file holds the venue-specific mechanics.

## What this is
- `main.tex` + `refs.bib`: the PoPETs submission source, derived from the canonical
  `../../paper/codec_retrieval.tex` + `../../paper/refs.bib` (the de-anonymized, full,
  article-class version, which stays the content source of truth).
- Build: `make` (pdflatex; bibtex; pdflatex x2). Needs `acmart.cls` (in TeX Live) and,
  for the final masthead, `popets.sty` (see below).

## Differences from the canonical version (the venue tailoring)
1. **Format**: `acmart` `sigconf` 2-column (PoPETs base) instead of `article`. acmart
   provides amsmath/amsthm/booktabs/hyperref/natbib; we add mathtools/amssymb/cleveref,
   fix the amssymb `\Bbbk` clash, and define `remark` (acmart predefines the others).
2. **Length**: PoPETs caps the body at 12 pages (bib + clearly-marked appendices
   excluded). The four `\S9` Refinements subsections were moved to a clearly-marked
   appendix (`app:refinements`) with a tight summary kept in the body. Body = 12 pages.
3. **Anonymization** (double-blind): `anonymous` class option hides the author block;
   in-body self-references neutralized to third person; the repo name scrubbed; the two
   self-citations anonymized in this directory's `refs.bib` (author = Anonymous).
4. **AI disclosure**: a `\section*{Disclosure of generative AI use}` was added as back
   matter (excluded from the page count), per the PoPETs 2027 AI policy.
5. **2-column polish**: wide tables wrapped in `\resizebox`; wide displays broken with
   `aligned`; the verbatim block shrunk; `\emergencystretch` for prose. ~0 visible
   overflow boxes.

## The masthead swap (do at final upload, once popets.sty is present)
Download the author-kit zip from https://submit.petsymposium.org/ , drop `popets.sty`
into this directory, then change the top of `main.tex`:

    - \documentclass[sigconf,nonacm,anonymous,balance=false]{acmart}
    - \settopmatter{printacmref=false, printfolios=true}
    - \setcopyright{none}
    + \documentclass[sigconf,anonymous]{acmart}
    + \usepackage{popets}

`popets.sty` manages the copyright/folio/ref-block settings we currently set by hand, so
those lines come out. It changes the masthead/headers only, not the body geometry, so
the 12-page fit holds. Rebuild and re-check the body page count after the swap.

## AI-disclosure text for the HotCRP submission form
(PoPETs wants the disclosure in the paper AND the submission form. Paste this in the form.)

> This submission used LLM-based tools as follows. (1) Drafting/editing: an agentic
> multi-tool writing-and-review system reshaped pre-existing, author-developed technical
> results into venue prose, copy-edited, and ran editorial review passes, all reviewed
> and approved by the authors. (2) Verification: every theorem, proof, bound, and number
> was checked by the authors against the artifact's computational gates and committed
> result files; no result originated from an LLM. (3) Literature/bibliography:
> LLM-assisted web search located related work and drafted some BibTeX entries, each
> verified against primary sources (one LLM-introduced author-list error was caught and
> corrected). The authors take full responsibility for the entire manuscript; no AI
> system is an author.

## Re-deriving after a canonical content change
If `../../paper/codec_retrieval.tex` changes substantively, re-apply the deltas above to
`main.tex` (format, the `\S9` appendix split, anonymization). For small wording fixes,
edit both. There is no automated sync; the canonical version is the content authority.
