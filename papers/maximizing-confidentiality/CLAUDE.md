# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LaTeX research paper: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing" (Alexander Towell, 22 pages, 6 theorems, 4 tables, 2 figures). Theory paper grounded in the cipher map framework. The paper is organized around an explicit **two-scale frame**:

- **Marginal scale** (a single cipher map): the representation-uniformity parameter `delta` lower-bounds the entropy ratio via the Fannes-Audenaert continuity inequality, `e >= 1 - delta - h_2(delta)/n`. Two constructions reduce `delta` (noise injection, multiplicity with `K(x) ~ D(x)`).
- **Compositional scale** (chains of cipher maps): when the untrusted machine observes multiple evaluations on a shared cipher value, the latent joint distribution is recoverable at parametric rate `O(|Y_1||Y_2|/xi^2)`, with mutual information preserved exactly. The matching minimax lower bound (Thm 5.2 via Le Cam) makes this rate sharp. **The compositional leakage theorem (Thm 5.1, with Thm 5.2 as the lower bound) is the paper's headline contribution.** The Fannes bridge is supporting infrastructure.

The two scales do not reduce to each other; the compositional channel is intrinsic to the framework's composability, not a bug.

This is **not** a USENIX submission, despite what `README.md` and other artifacts may say. The paper was rewritten from scratch on 2026-04-01. Current target is a theory venue (TCC, CSF, or QIF workshop are open candidates per `.papermill/state.md`); pick one with `/papermill:venue` when ready.

## Build

`make` runs three pdflatex passes plus bibtex (clean build, 22 pages, **zero warnings**). `make quick` is single-pass nonstopmode for fast feedback. `make stats` reports section/theorem/citation counts and PDF page count. `make help` lists everything.

The `git-release` target is interactive and not appropriate for a Claude session, leave it for the human.

## Architecture and Cross-Paper Dependencies

Two propositions in this paper are cited, not re-proven. Future Claude must understand which is which:

- **`towell2026cipher`** at `../cipher-maps/` defines cipher maps, the four properties (totality, representation uniformity, correctness, composability), and the parameter tuple `(eta, epsilon, delta, mu)`. From this paper we inherit:
  - Sec. 8: FPR compounding (Thm 5.3 here cites it)
  - Sec. 9 / Prop. 9.1: encoding granularity spectrum (Prop 4.3 here cites it)
- **`towell2026algebraic`** at `../algebraic-cipher-types/` defines orbit closure; used only in the §5.2 active-probing discussion.

The paper's own theorems and contributions:
- Thm 3.1: Fannes bridge (`delta -> e`)
- Thm 4.1: Noise dilution (Fisher-info `rho^2` with explicit `C(D)` constant)
- Thm 4.2: Multiplicity construction (`K(x) = ceil(c * D(x))`, classical homophonic)
- Thm 5.1: Compositional leakage upper bound (mutual-information preservation, plug-in rate)
- Thm 5.2: Compositional leakage lower bound (Le Cam two-point method, sharp `Theta(|Y_1||Y_2|/xi^2)`)
- Prop 6.1: Compression-based entropy estimator

Don't promote inherited results to "our contribution" or demote our results to "follows from cipher-maps."

## Notation

All notation matches the cipher-maps companion paper. Custom macros at the top of `main.tex`:

- `\fhat`, `\ghat` for cipher-map approximations of latent functions
- `\enc`, `\dec` for encoding/decoding (only the trusted machine has these)
- `\TV` for total variation distance, `\B` for `{0,1}` (so `\B^n` is bit strings)
- `\cipher{X}` for cipher type over `X` (renders as `\mathsf{C}(X)`)
- `\orbitF` for the orbit operator from the algebraic-cipher-types paper

Theorem environments share a counter (`definition`, `theorem`, `lemma`, `corollary`, `proposition`, `remark`, `example`), so promoting a `proposition` to a `theorem` does NOT renumber surrounding labels. If you add new notation, define it as a `\newcommand` near the top, do not introduce inline ad-hoc symbols.

Math in section/subsection titles uses `\texorpdfstring{$math$}{ascii}` to keep PDF bookmarks warning-free. Two such titles exist (§4 "Constructions for Reducing delta", §4.2 "Multiple Representations (K > 1)", §5.4 "Finite-Sample Resolution of delta"). If you add another math-bearing title, mirror the pattern.

## Mathematical Landmines

Two errors were caught in the 2026-04-12 multi-agent review and fixed. They were in the original draft and inherited from the cipher-maps companion paper. Future Claude must not revert them:

1. **Fannes, not Pinsker.** Pinsker's inequality gives `D_KL >= 2 * d_TV^2`, which is a lower bound on KL given TV. To bound `H(Q)` from above given `TV(Q, U) <= delta`, the correct tool is the Fannes-Audenaert continuity inequality, which is **linear** in delta: `e >= 1 - delta - h_2(delta)/n`. If Theorem 3.1 part (3) ever reads `e >= 1 - 2*delta^2/n` (quadratic), it has been reverted.

2. **`K(x) ~ D(x)`, not `K(x) ~ 1/D(x)`.** Under the paper's sampling model `Q(v) = D(x)/K(x)`, equalizing cipher-value frequencies requires `K(x)` proportional to `D(x)` (classical homophonic substitution: frequent elements get more code symbols, see Simmons 1979). The reverse direction concentrates mass and makes the distribution more skewed. If Theorem 4.2 or Example 4.1 (Zipf homophonic) ever again use `1/D(x)`, this has been reverted.

The same errors **may** still appear in the cipher-maps paper at `../cipher-maps/`. Last verified 2026-04-12; status not re-checked since. The cite-with-correction approach used here keeps this paper internally consistent.

## Experimental Harness

Empirical results in §5.4 (finite-sample bias of `delta-hat`), §6.1 (Boolean search), §6.2 (FPR compounding), §6.3 (granularity), and §6.4 (20NG homophonic) all come from the `cipher-maps` Python library at `~/github/trapdoor-computing/src/cipher-maps/`. Every empirical table and figure has a corresponding script in `experiments/` or `examples/`:

- Tables 1, 2, 3: `examples/experiment_paper_tables.py` (n=5 seeds, mean +/- std)
- §5.4 figure: `experiments/finite_sample.py`
- §6.4 figure: `experiments/newsgroups_homophonic.py`
- Table 4 (case study): analytical, computed from the closed-form expressions in Theorems 4.1 and 4.2

When regenerating tables, parameters in script and paper must match. `experiment_paper_tables.py` was originally written for the algebraic-cipher-types paper; the Boolean cipher parameters `(p_T = 0.05, p_F = 0.90, p_N = 0.05, n_bits = 8)` happen to be the same.

**Notable empirical finding (Table 2, §6.2):** AND-chain FPR settles at a noise floor ~4e-3 for k>=3 rather than continuing to decay as `p_T^k`. This is a construction-level residual, not a violation of the FPR theorem; the paper now reframes it as a defender's confidentiality budget. Don't "fix" this back to zero.

## Workflow: papermill State Is the Source of Truth

The paper's research metadata lives in `.papermill/`, not in the LaTeX:

- `.papermill/state.md`: current thesis claim, novelty statement, target venue, stage, related papers, refinement chain. **Required reading at session start.**
- `.papermill/thesis-refined-YYYY-MM-DD.md`: refinement history with the rationale for each change. The latest is `2026-04-12.md`, which has accreted multiple same-day and follow-up subsections; read it bottom to top for the trajectory.
- `.papermill/reviews/YYYY-MM-DD/`: multi-agent review reports. Three rounds so far (`2026-04-12/`, `2026-04-12-rev2/`, `2026-04-29/`). Most recent review's recommendation was **minor-revision**, only carry-over polish items remain.
- `.papermill/drafts/YYYY-MM-DD/`: historical drafts and writing plans (read-only history).

Do not edit thesis claims in `main.tex` without also updating `.papermill/state.md`. The contribution audit (which results are proven here vs. cited from cipher-maps) lives in the latest thesis-refined doc.

Common skill invocations: `/papermill:status` (read state), `/papermill:thesis` (refine claim), `/papermill:review` (multi-agent review), `/papermill:venue` (pick venue), `/papermill:polish` (pre-submission checklist).

## Stale Artifacts (Do Not Trust)

These predate the 2026-04-01 rewrite and have not been updated:

- `README.md`: describes the 51-page USENIX draft, with wrong section list, wrong page counts, and the old `59% -> 85%` case study. Tell the user before fixing it on your own.
- `main_new.log`, `main_new.out`: transition leftovers; harmless. (`main_new.pdf` was deleted in the 2026-04-29 commit.)
- `data/`: pgfplots Monte Carlo data from the old paper. Not used in the current `main.tex`.
- `img/comm_model.{tex,pdf}`, `img/inout.{tex,pdf}`, `img/perturbed_fake_query.{tex,pdf}`, `img/pr_model_fig.{tex,pdf}`, `img/simple_comm_model.tex`: TikZ figures from the old paper. Not `\includegraphics{}`'d in current `main.tex`.

The two **active** images are `img/finite_sample_gap.png` and `img/newsgroups_homophonic.png`. Both are PNGs generated by the cipher-maps experimental harness; they were added 2026-04-29.

## Parent Repository

This paper sits inside the `trapdoor-computing/` monorepo. The parent `CLAUDE.md` covers the broader provenance: the cipher-maps formalism source of truth (`foundations/`, `formalism/`), the trusted/untrusted model, and the explicit rule against drifting toward ORAM/FHE/simulation-based formalisms. If a session involves cross-paper reasoning or you encounter mentions of "oblivious computing" (the old name), read it.

There is also a sibling paper at `../adaptive-trapdoor/` (idea-stage scaffold, no draft yet) that addresses confidentiality maintenance under distributional drift. It builds on this paper as background.
