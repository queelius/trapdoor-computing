# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LaTeX research paper: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing" (Alexander Towell, ~17 pages). Theory paper grounded in the cipher map framework. The thesis: representation uniformity (delta) lower-bounds the entropy ratio via the Fannes-Audenaert continuity inequality, giving `e >= 1 - delta - h_2(delta)/n`, which reduces confidentiality engineering to minimizing delta.

This is **not** a USENIX submission, despite what `README.md` and other artifacts may say. The paper was rewritten from scratch on 2026-04-01 (the old 43-page USENIX draft is gone). Current target is a theory venue (TCC, CSF, or QIF workshop are open candidates per `.papermill/state.md`); pick one with `/papermill:venue` when ready.

## Build

`make` runs three pdflatex passes plus bibtex (clean build, ~17 pages, no warnings beyond two cosmetic hyperref/PDF-string issues from math in subsection titles). `make quick` is single-pass nonstopmode for fast feedback. `make stats` reports section/theorem/citation counts and PDF page count. `make help` lists everything.

The `git-release` target is interactive and not appropriate for a Claude session, leave it for the human.

## Architecture and Cross-Paper Dependencies

Two propositions in this paper are cited, not re-proven. Future Claude must understand which is which:

- **`towell2026cipher`** at `../cipher-maps/` defines cipher maps, the four properties (totality, representation uniformity, correctness, composability), and the parameter tuple $(\eta, \varepsilon, \delta, \mu)$. From this paper we inherit:
  - Sec. 8: FPR compounding (Theorem 5.2 here cites it)
  - Sec. 9 / Prop. 9.1: encoding granularity spectrum (Proposition 4.3 here cites it)
- **`towell2026algebraic`** at `../algebraic-cipher-types/` defines orbit closure; used only in the §5 active-probing discussion.

The paper's own contributions are: the Fannes bridge `delta -> e`, the noise-dilution theorem (4.1), the multiplicity construction (4.2), and the compositional leakage theorem (5.1). Don't promote inherited results to "our contribution" or demote our results to "follows from cipher-maps."

## Notation

All notation matches the cipher-maps companion paper. Custom macros at the top of `main.tex`:

- `\fhat`, `\ghat` for cipher-map approximations of latent functions
- `\enc`, `\dec` for encoding/decoding (only the trusted machine has these)
- `\TV` for total variation distance, `\B` for `{0,1}` (so `\B^n` is bit strings)
- `\cipher{X}` for cipher type over $X$ (renders as `\mathsf{C}(X)`)
- `\orbitF` for the orbit operator from the algebraic-cipher-types paper

Theorem environments share a counter (`definition`, `theorem`, `lemma`, `corollary`, `proposition`, `remark`, `example`), so promoting a `proposition` to a `theorem` does NOT renumber surrounding labels. If you add new notation, define it as a `\newcommand` near the top, do not introduce inline ad-hoc symbols.

## Mathematical Landmines

Two errors were caught in the 2026-04-12 multi-agent review and fixed. They were in the original draft and inherited from the cipher-maps companion paper. Future Claude must not revert them:

1. **Fannes, not Pinsker.** Pinsker's inequality gives `D_KL >= 2 * d_TV^2`, which is a lower bound on KL given TV. To bound `H(Q)` from above given `TV(Q, U) <= delta`, the correct tool is the Fannes-Audenaert continuity inequality, which is **linear** in delta: `e >= 1 - delta - h_2(delta)/n`. If Theorem 3.1 part (3) ever reads `e >= 1 - 2*delta^2/n` (quadratic), it has been reverted.

2. **`K(x) ~ D(x)`, not `K(x) ~ 1/D(x)`.** Under the paper's sampling model `Q(v) = D(x)/K(x)`, equalizing cipher-value frequencies requires `K(x)` proportional to `D(x)` (classical homophonic substitution: frequent elements get more code symbols, see Simmons 1979). The reverse direction concentrates mass and makes the distribution more skewed. If Theorem 4.2 or Example 4.1 (Zipf homophonic) ever again use `1/D(x)`, this has been reverted.

The same errors still appear in the cipher-maps paper at the time of writing. Fixing them upstream is a separate task; the cite-with-correction approach used here keeps this paper internally consistent.

## Workflow: papermill State Is the Source of Truth

The paper's research metadata lives in `.papermill/`, not in the LaTeX:

- `.papermill/state.md`: current thesis claim, novelty statement, target venue, stage, related papers
- `.papermill/thesis-refined-YYYY-MM-DD.md`: refinement history with the rationale for each change (today's is `2026-04-12.md`, which captures both the morning sharpening and the post-review fixes)
- `.papermill/reviews/YYYY-MM-DD/`: multi-agent review reports, most recent is what's been responded to
- `.papermill/drafts/YYYY-MM-DD/`: historical drafts and writing plans (read-only history)

Do not edit thesis claims in `main.tex` without also updating `.papermill/state.md`. The contribution audit (which results are proven here vs. cited from cipher-maps) lives in the latest thesis-refined doc.

Common skill invocations: `/papermill:status` (read state), `/papermill:thesis` (refine claim), `/papermill:review` (multi-agent review), `/papermill:venue` (pick venue), `/papermill:polish` (pre-submission checklist).

## Stale Artifacts (Do Not Trust)

These predate the 2026-04-01 rewrite and have not been updated:

- `README.md`: describes the 51-page USENIX draft, with wrong section list, wrong page counts, and the old `59% -> 85%` case study. Tell the user before fixing it on your own.
- `main_new.pdf`, `main_new.log`, `main_new.out`: transition leftovers; harmless, ignored by the build.
- `data/` and `img/`: pgfplots Monte Carlo data and TikZ figures from the old paper. The current `main.tex` has zero figures and four tables. None of these files are `\input{}`'d or `\includegraphics{}`'d. Do not assume they are wired into the build; do not regenerate from them without checking what's actually used.

## Parent Repository

This paper sits inside the `trapdoor-computing/` monorepo. The parent `CLAUDE.md` covers the broader provenance: the cipher-maps formalism source of truth (`foundations/`, `formalism/`), the trusted/untrusted model, and the explicit rule against drifting toward ORAM/FHE/simulation-based formalisms. If a session involves cross-paper reasoning or you encounter mentions of "oblivious computing" (the old name), read it.
