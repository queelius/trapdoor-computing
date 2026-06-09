# Cross-Paper Consistency Report

**Date**: 2026-06-02
**Scope**: cipher-maps, maximizing-confidentiality (Entropy Ratio), algebraic-cipher-types, cipher-rekeying, adaptive-trapdoor (boolean-algebra-over-trapdoor-sets was archived 2026-06-09; its kernels folded into cipher-maps §9.4 and algebraic-cipher-types)
**Companion**: `cipher-map-formalism.md` (the reconciled spine this report supports)
**Method**: verbatim extraction of every shared definition, theorem, and notation symbol from each paper's `.tex`, compared against the spine and against each other.

This report records what is consistent (the spine holds), what drifted (actionable fixes), and what is cosmetic. Findings are prefixed `C-n` and ordered by severity. C-1 was fixed in the spine during this pass; the rest are open.

---

## Summary: the spine holds

The load-bearing definitions are consistent across all papers. This is the good news and it means the program is coherent at its core:

- **Cipher map tuple** $(\hat{f}, \mathrm{enc}, \mathrm{dec}, s)$ with $\hat{f}: \{0,1\}^n \to \{0,1\}^n$, $\mathrm{enc}: X \times \{0,\dots,K(x){-}1\} \to \{0,1\}^n$, $\mathrm{dec}: \{0,1\}^n \to Y \cup \{\bot\}$: **identical** in all five mature papers. Every paper imports it by citing the hub (`towell2026cipher` Def 1.1); none redefines it.
- **Four properties** $(\eta, \varepsilon, \mu, \delta)$: consistent. All papers reference the hub's Section 4.
- **Representation uniformity** $\delta = d_{\mathrm{TV}}(Q, \mathrm{Uniform}(\{0,1\}^n))$: consistent across all papers and the spine. The comparator is uniform over the full ambient space $\{0,1\}^n$ (not the image), in every paper.
- **Composition theorem** $\eta_{\mathrm{total}} \leq 1 - \prod_i (1 - \eta_i)$, equality under re-randomization: consistent.
- **Space bound** $-\log_2 \varepsilon + H(Y)$ bits/element: consistent.
- **Shared LaTeX macros**: all papers use the same preamble vocabulary (`\fhat`, `\enc`, `\dec`, `\B`, `\cipher`, `\cipherS`, `\orbitF`). No glyph drift in the core objects.

Net: a reader who learns the spine from `cipher-map-formalism.md` can read any paper without re-learning the basics. That was not true before this pass, because the spine doc was a fossil (it predated the entropy ratio, the orbit-closure bound, acceptance predicates, and the coincidence oracle). The reconciled spine now carries all of them.

---

## C-1 (CRITICAL, FIXED this pass): inverted homophonic prescription

**What.** The spine doc stated the multiplicity prescription as $K(x) \propto 1/D(x)$ at three sites (Property 2 construction principle, the parameter table, and §2.3.1). This is inverted and self-contradictory: $1/D(x)$ gives *frequent* values *fewer* codes, yet the surrounding prose claimed "frequent values get more representations."

**Truth (the papers have it right).** The correct prescription is the classical Simmons homophonic rule $K(x) \propto D(x)$: frequent values get **more** codes, flattening the per-cipher-value probability $D(x)/K(x)$. Setting $K(x) = \lceil c\,D(x)\rceil$ gives $d_{\mathrm{TV}}(Q, U_{\mathrm{im}}) \leq |X|/(2\sum_x K(x))$. This is Theorem 4.2 ("Representation uniformity via multiplicity") in the Entropy Ratio paper and the homophonic-allocation result in Cipher Maps. Both papers are correct; only the spine doc was wrong.

**Status.** Fixed in `cipher-map-formalism.md` this pass (all three sites).

**Residual.** The authentic foundation blog `foundations/trapdoor-boolean-algebra.md` (which the spine quoted) may still carry the inverted form. **Do not edit the foundations** (they are the authentic 2023-2024 source of record); instead, if the inverted form is there, note it as a known erratum in that file's vicinity the way the spine already annotates other blog-post errata. Action: grep `foundations/trapdoor-boolean-algebra.md` for `1/` near the multiplicity discussion and add an errata note if present.

---

## C-2 (HIGH): the Algebraic Cipher Types paper has two bibkeys and a stale title

**What.** The same paper is cited under two different keys, and one of its bib entries carries an outdated title.

| Citing paper | Bibkey used | Title in its `.bib` |
|---|---|---|
| cipher-rekeying | `towell2026actypes` | "Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing" (correct) |
| maximizing-confidentiality | `towell2026algebraic` | same correct title |
| cipher-maps | `towell2026algebraic` | "Algebraic Cipher Types: **A Functorial Framework for Structured Computation over Trapdoor Encodings**" (stale) |

The actual paper title (`papers/algebraic-cipher-types/paper/main.tex`) is **"Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing"**.

**Fix.**
1. Canonical key: `towell2026algebraic` (used by 2 of 3 citers). In `papers/cipher-rekeying/paper/`, rename `towell2026actypes` to `towell2026algebraic` in `references.bib` (the `@misc` entry) and at all 20 `\cite` sites in `main.tex`. Delete stale `.aux`/`.bbl` artifacts so they regenerate.
2. In `papers/cipher-maps/paper/references.bib`, update the title string for `towell2026algebraic` to the real title.
3. The root `CLAUDE.md` description of `algebraic-cipher-types` also uses the stale "functorial framework" phrasing; update to match.

---

## C-3 (HIGH): CLAUDE.md conflates two confidentiality measures

**What.** `CLAUDE.md` Core Principle 7 writes the entropy ratio as
$$e = H(X \mid \text{view}) / H^*(X).$$
No paper uses this form. It conflates two distinct measures:
- the **marginal entropy ratio** (Measure M1): $e = H(Q)/n$, the entropy of the *cipher-value* distribution $Q$ relative to uniform, used by Cipher Maps (Prop 5.1) and the Entropy Ratio paper (Thm 3.1); and
- the **orbit-closure residual entropy** (Measure C1): $H(X \mid \mathcal{V}_F(c)) \geq H(X) - \log_2|\mathrm{orbit}_F(c)|$, the residual uncertainty of the *latent* $X$ given an active adversary's view, used by Algebraic Cipher Types. This is unnormalized and is **not** called "the entropy ratio."

The CLAUDE.md formula has the conditional-entropy form of C1 with the normalization of M1, so it is literally neither.

**Fix.** Update CLAUDE.md Core Principle 7 to state the entropy ratio as $e = H(Q)/n$ (Measure M1), with the Fannes bound $e \geq 1 - \delta - h_2(\delta)/n$, and add one clause noting that the active/compositional scale (orbit closure C1, coincidence oracle C2, joint recovery C3) is a *separate* set of measures not controlled by $\delta$. The reconciled spine Section 4A is the reference. (Outside `formalism/`; flagged for a CLAUDE.md edit, not done in this pass.)

---

## C-4 (DOCUMENTATION HAZARD, documented): "Le Cam" names two different things

The two-point method appears at both scales with opposite roles; both papers say "Le Cam" bare.

| Use | Scale | Role | Statement | Owner |
|---|---|---|---|---|
| M2 | marginal | **upper** bound on a single-guess attacker | accuracy $\leq \tfrac12 + \tfrac\delta2$ | Cipher Maps §5.3 |
| C3 | compositional | **lower** bound on the joint-estimation minimax rate | $\mathbb{E}[\mathrm{TV}] \geq c\sqrt{|Y_1||Y_2|/N}$ | Entropy Ratio Thm 5.2 |

Not a bug (both uses are correct), but a reader who sees "by Le Cam" in one paper and "by Le Cam" in the other will assume they mean the same bound. **Status:** documented in spine §4A.3. Recommend each paper add a one-clause footnote at its Le Cam site distinguishing the two roles.

---

## Minor / cosmetic / future (C-5 through C-10)

- **C-5 ($\varepsilon$, $\mu$ declared-not-defined).** Algebraic Cipher Types and Cipher Rekeying list the parameter tuple $(\eta, \varepsilon, \mu, \delta)$ but only operationalize $\eta$ and $\delta$ in-body, relying on the citation for $\varepsilon, \mu$. Acceptable (they cite the hub), but a one-line gloss would help a standalone reader.
- **C-6 (parameter tuple order).** $(\eta, \varepsilon, \mu, \delta)$ vs $(\eta, \varepsilon, \delta, \mu)$ appear in different places, even within the Entropy Ratio paper. Pick one order project-wide. The spine uses $(\eta, \varepsilon, \mu, \delta)$.
- **C-7 (residual citation typo in Cipher Rekeying).** `main.tex` cites `[Rem.~6.2]{towell2026actypes}` for shared-variable correlation; the paper's own citation-verifier review says it should be `[Rem.~6.1]`. One-character fix.
- **C-8 (orbit definition arity).** Algebraic's orbit-closure definition treats every operation as unary; arity is introduced separately in the typed-chain proposition. A future arity-aware orbit definition would remove the seam. Not urgent.
- **C-9 ($H^*$ ambiguity in the Entropy Ratio paper).** $H^* = n$ in the per-query Fannes bound, but $\log_2|X|$ in the $K=1$ relabeling clause of the same theorem. Two concrete values for $H^*$ depending on the clause; a sentence distinguishing them would prevent misreading.
- **C-10 ($U$ vs $U_{\mathrm{im}}$ in the multiplicity theorem).** The multiplicity bound is stated against $U_{\mathrm{im}}$ (uniform over $\mathrm{Im}(\mathrm{enc})$), then lifted to $U$ over $\{0,1\}^n$ via a birthday-bound term $O(\sum K / 2^n)$. The canonical $\delta$ (spine, Property 2) is against $U$ over $\{0,1\}^n$. Consistent, but the two-step should be explicit wherever the multiplicity theorem is invoked.

---

## Recommended order of operations

1. **C-2 bibkey** (mechanical, removes a real compile-time inconsistency): one session, ~20 minutes.
2. **C-3 CLAUDE.md** (one paragraph): protects future sessions from re-importing the conflation.
3. **C-1 residual** (check the foundation blog for the inverted form; add errata note only, do not edit the authentic text).
4. **C-7** (one-character citation fix) while in the Cipher Rekeying `.bib`.
5. **C-4 footnotes, C-5, C-6, C-9, C-10**: fold into each paper's next revision pass; none blocks submission.
6. **C-8**: defer; revisit if a future paper needs arity-aware orbits.

A single shared `trapdoor.bib` plus a common macro preamble (`trapdoor-macros.sty`) `\input` by every paper would prevent C-2, C-5, and C-6 from recurring. Worth doing before the next paper is started.
