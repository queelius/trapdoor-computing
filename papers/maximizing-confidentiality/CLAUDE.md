# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LaTeX research paper: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing" (Alexander Towell, 32 pages, 6 theorems, 4 tables, 5 figures). Theory paper grounded in the cipher map framework. The paper is organized around an explicit **two-scale frame**:

- **Marginal scale** (a single cipher map): the representation-uniformity parameter `delta` (image-relative: TV to uniform on `im(enc)`, see Landmine 6) lower-bounds the entropy ratio via the Fannes-Audenaert continuity inequality, `e >= 1 - delta - h_2(delta)/H*` with `H* = log2|im(enc)|`. Two constructions reduce `delta` (noise injection, multiplicity with `K(x) ~ D(x)`).
- **Compositional scale** (chains of cipher maps): when the untrusted machine observes multiple evaluations on a shared cipher value, the latent joint distribution is recoverable at parametric rate `O(|Y_1||Y_2|/xi^2)`, with mutual information preserved exactly. The matching minimax lower bound (Thm 5.2 via Assouad's lemma, NOT Le Cam, see Mathematical Landmines) makes this rate sharp. **The compositional leakage theorem (Thm 5.1, with Thm 5.2 as the lower bound) is the paper's headline contribution.** The Fannes bridge is supporting infrastructure.

The two scales do not reduce to each other; the compositional channel is intrinsic to the framework's composability, not a bug.

This is **not** a USENIX submission, despite what `README.md` and other artifacts may say. The paper was rewritten from scratch on 2026-04-01. Current target is a theory venue (TCC, CSF, or QIF workshop are open candidates per `.papermill/state.md`); pick one with `/papermill:venue` when ready.

## Build

`make` runs three pdflatex passes plus bibtex (clean build, 29 pages, **zero LaTeX warnings**; one minor sub-18pt overfull hbox remains in a math-dense paragraph, cosmetic). `make quick` is single-pass nonstopmode for fast feedback. `make stats` reports section/theorem/citation counts and PDF page count. `make help` lists everything.

The `git-release` target is interactive and not appropriate for a Claude session, leave it for the human.

## Architecture and Cross-Paper Dependencies

Two propositions in this paper are cited, not re-proven. Future Claude must understand which is which:

- **`towell2026cipher`** at `../cipher-maps/` defines cipher maps, the four properties (totality, representation uniformity, correctness, composability), and the parameter tuple `(eta, epsilon, mu, delta)` (spine-canonical order; align to this). From this paper we inherit:
  - Sec. 7.4 ("Error Accumulation by Gate Type"): gate-type FPR framing. The closed forms `p_T^k` / `1-(1-p_T)^k` are elementary and the explicit forms + empirical validation are actually in `towell2026algebraic` Table 3, NOT cipher-maps; our FPR result is `Proposition` (not Theorem) and cites both. Do not re-credit the closed forms to cipher-maps.
  - Sec. 8 / Prop. 8.1: encoding granularity spectrum (our Prop 4.3 cites it). cipher-maps was renumbered ("QIF-restructured"); granularity is §8, composition/FPR is §7. Verify any new cite to cipher-maps against `cipher_maps.aux` newlabel entries, NOT by eye.
  - Thm 8.2: multi-instance coincidence oracle (Measure C2); cross-referenced from the §9 practical-depth paragraph.
- **`towell2026algebraic`** at `../algebraic-cipher-types/` defines orbit closure (Thm 5.3 is the ENTROPY form `H(X|V) >= H(X) - log2|orbit|`; the set form `conf >= 1 - |orbit|/|X|` uses denominator `|X|`, NOT `2^n` (see Mathematical Landmines)), the sum-type impossibility (Thm 4.2, NOT 4.1, since 4.1 is the product-tradeoff proposition when thm/prop share a counter), and typed composition chains (Sec 5.5, NOT 5.4 which is "Examples"). Used in the §5 active-probing and §9 practical-depth discussions.

The paper's own theorems and contributions:
- Thm 3.1: Fannes bridge (`delta -> e`)
- Thm 4.1: Noise dilution (Fisher-info `rho^2` with explicit `C(D)` constant)
- Thm 4.2: Multiplicity construction (`K(x) = ceil(c * D(x))`, classical homophonic)
- Thm 5.1: Compositional leakage upper bound (mutual-information preservation, plug-in rate)
- Thm 5.2: Compositional leakage lower bound (Assouad's lemma over a `2^{m/2}` hypercube packing, sharp `Theta(|Y_1||Y_2|/xi^2)`; full self-contained proof via Assouad + Hellinger affinity + Tsybakov Thm 2.12, constant ~0.03). NOT "Le Cam's two-point method": two hypotheses cannot produce a dimension-dependent rate. Pairwise TV of the packing is `(2*eps/m)*d_H`, not `(eps/m)*d_H` (factor-2 was a fixed slip).
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

3. **Orbit-closure set form uses `|X|`, not `2^n`.** The active-adversary confidentiality bound is `conf_F(c) >= 1 - |orbit_F(c)|/|X|` (denominator is the latent domain size `|X|`, the spine §4A.2 set form). An earlier version used `2^n` (the ambient cipher space), which over-claims confidentiality since `|X| <= 2^n`. The source theorem (`towell2026algebraic` Thm 5.3) is the ENTROPY form `H(X|V) >= H(X) - log2|orbit|`; the set form is its normalized restatement. If the orbit bound's denominator reads `2^n` again, it has been reverted (fixed 2026-06-02 cross-paper round).

4. **Thm 5.2 is Assouad, not Le Cam.** The compositional lower bound uses a `2^{m/2}` hypercube packing summed over coordinates: that is Assouad's lemma. "Le Cam's two-point method" (two hypotheses) cannot produce the dimension-dependent `sqrt(|Y1||Y2|/N)` rate. The packing's pairwise TV is `(2*eps/m)*d_H(s,s')`. If the proof sketch ever again says "Le Cam's two-point method" for this `2^{m/2}`-packing, or writes `(eps/m)` for the pairwise TV, it has been reverted (fixed 2026-06-02).

5. **Mixture entropy is `H(C)`, not `H(C, B)`.** Noise injection (Thm 4.1 part 1) mixes real queries (dist. `D`) with filler (uniform on the image `im(enc)`) in proportion `rho`. The observed per-element entropy is `H_mix = H(rho*D + (1-rho)*U_im)`, NOT the source-plus-indicator sum `H_b(rho) + rho*H(D) + (1-rho)*H*`. The latter is the JOINT entropy `H(C, B)` of the observation WITH the unobserved real/filler label `B`; it over-counts by `H(B|C)` and is only an UPPER bound (equality iff real and filler supports are disjoint). The untrusted machine never observes `B`. The round-2 review (2026-06-11) caught this: the wrong sum reproduced the case-study numbers (0.88, 0.98) to four decimals; the correct mixture entropy gives 0.84 and 0.94, so the case study is now "72% to 94%" (1.05x space, 1.5x bandwidth). If Thm 4.1 part (1) or Table 4 ever reads the source-plus-indicator sum as an EQUALITY for the observed entropy, it has been reverted (fixed 2026-06-11).

6. **Representation uniformity `delta` is image-relative, not ambient.** `delta = TV(Q, U_im)` is TV to uniform on `im(enc)`, NOT to uniform on `B^n` (which is `~1` for any sparse-image construction, making the ambient definition unsatisfiable). The Fannes bound is therefore `e >= 1 - delta - h_2(delta)/H*` with `H* = log2|im(enc)|`, not `/n`. The ambient (`B^n`) view is the ROM/computational layer (pseudorandom image, birthday term), not the information-theoretic measure. This resolves the paper's old C-9/C-10 cross-paper items but DEVIATES from the spine/cipher-maps, which still define `delta` against ambient `U` (see cross-paper item C-11; Entropy Ratio is now the reference for the corrected form). If Property 2 or Thm 3.1 ever defines `delta` against `U` on `B^n` with normalizer `n`, it has been reverted (fixed 2026-06-11).

Cross-family status of these errors (as of 2026-06-03): cipher-maps `../cipher-maps/` is now CORRECT (`K(x) ∝ D(x)` everywhere; fixed in its homophonic-bound commits 5820806/1202a68/000cf44). The formalism spine (`formalism/cipher-map-formalism.md` Property 2) is correct. The authentic foundation blog `foundations/trapdoor-boolean-algebra.md` preserves the original inverted text but carries a 2026-06-02 erratum note (do NOT edit the authentic text; the erratum is the correct treatment). The only paper still carrying the inversion is `papers/boolean-algebra-over-trapdoor-sets/` (`main_comprehensive.tex`), which ECOSYSTEM-TRIAGE classifies DRIFTED and slates for revert/archive, not spot-patch. So this paper's case study no longer needs a cite-with-correction against cipher-maps; it presents `1/D(x)` only as a pedagogical contrast.

The 2026-06-02 cross-paper round fixed six stale companion-section citations in THIS paper (the companions were renumbered); always verify a cipher-maps/algebraic cite against the companion's `.aux` newlabel entries before trusting a section/theorem number.

## Experimental Harness

Empirical results in §5.4 (finite-sample bias of `delta-hat`), §6.1 (Boolean search), §6.2 (FPR compounding), §6.3 (granularity), and §6.4 (20NG homophonic) all come from the `cipher-maps` Python library at `~/github/trapdoor-computing/src/cipher-maps/`. Every empirical table and figure has a corresponding script in `experiments/` or `examples/`:

- Tables 1, 2, 3: `examples/experiment_paper_tables.py` (n=5 seeds, mean +/- std)
- §5.4 figure: `experiments/finite_sample.py`
- §6.4 figure: `experiments/newsgroups_homophonic.py`
- §6.5 figure (compression estimator): `experiments/compression_validation.py`
- §6.6 figure (Monte Carlo rate validation): `experiments/compositional_rate.py` (S1: compositional joint-recovery rate, Thm 5.1/5.2 upper; S2: noise Fisher dilution, Thm 4.1; S3: lower-bound bake-off, Thm 5.2 sharpness -- four estimators incl. an oracle shrink-to-uniform on the minimax-calibrated Assouad packing, none beats slope -1/2). The S2 rho^2 is a deep-asymptotic limit (rho -> 0); the iid-from-mixture sampling model matters (each element real w.p. rho, NOT a fixed split) or the MC variance drops below the Cramer-Rao bound. Don't "fix" the fixed-split version back in.
- §6.7 figure (realized attack on the real construction): `experiments/realized_attack.py` (builds two trapdoor maps via the library, mounts the joint-recovery attack; H1 confirms the construction reproduces §6.6's rate, c=0.32 vs 0.31). eta is injected in the attack as random decode flips, NOT via build(eta_target=...), which is an upper bound the exact PHF build ignores (it builds eta=0).
- Table 4 (case study): analytical, computed from the closed-form expressions in Theorems 4.1 and 4.2. **2026-06-11:** recomputed with the corrected mixture entropy `H(rho*D + (1-rho)*U_im)` of Thm 4.1 (see Landmine 5); values are now 0.72 / 0.87 / 0.84 / 0.94 (was .../0.88/0.98). Verified by independent Python recompute (`H(D)/log2(m)`, `H(Q_hom)/log2(sumK)`, mixtures at rho=2/3); sumK=10482 (1.05x space).

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
