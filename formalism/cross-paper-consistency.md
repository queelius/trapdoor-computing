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

---

## 2026-06-11 round-2 update (Entropy Ratio major revision)

The round-2 (Fable) review of the Entropy Ratio paper drove a major
revision (logged in its `.papermill/reviews/2026-06-11/`) that touches
three items here:

- **C-9 RESOLVED (in Entropy Ratio).** $H^*$ is now uniformly
  $H^* = \log_2|\mathrm{im}(\enc)|$ throughout: Property 2, the Fannes
  bound (Thm 3.1 part 3), the $K=1$ clause (part 2, now an equality), the
  noise theorem, and the case study all normalize by the populated-support
  log-size. The old $n$-vs-$\log_2|X|$ split is gone.
- **C-10 RESOLVED (in Entropy Ratio).** Representation uniformity is now
  defined against $U_{\mathrm{im}}$ (Property 2); the ambient-$U$ / $\B^n$
  statement is demoted to the ROM/computational layer (birthday term).
- **C-11 (NEW): the spine and Cipher Maps still carry the ambient-$\delta$
  definition.** Spine Property 2 and `cipher-maps` define
  $\delta = \mathrm{TV}(Q, U)$ against uniform on $\B^n$, which is $\approx
  1$ for any sparse-image construction (the defect the Entropy Ratio paper
  just fixed). Entropy Ratio now DEVIATES from the spine here, in the
  correct direction. **Action:** propagate the image-relative definition
  to the spine (Property 2) and `cipher-maps`; until then this is a
  documented, deliberate deviation, not drift. Entropy Ratio is the
  reference for the corrected form. (Also fixed in this round, not a
  cross-paper item: Thm 4.1 part 1 mixture entropy $H(C)$ vs $H(C,B)$,
  Entropy Ratio CLAUDE.md Landmine 5.)

## 2026-06-18 update (monograph Part II keystone back-port)

Drafting the monograph keystone (Part II, ch3-5) forced two corrections into
the spine and `cipher-maps`, both now applied:

- **C-11 RESOLVED (spine + Cipher Maps).** Spine Property 2 and `cipher-maps`
  Def. (representation uniformity) now read
  $\delta = \mathrm{TV}(Q, \mathrm{Uniform}(\mathrm{Im}(\mathrm{enc})))$ with
  $H^* = \log_2|\mathrm{Im}(\mathrm{enc})|$, the image-relative form, *not*
  ambient $\{0,1\}^n$. All three (spine, Cipher Maps, Entropy Ratio) now
  agree; the monograph (`monograph/book/chapters/ch04`, `def:uniformity`) is
  the book-side definition of record.
- **C-12 (NEW; RESOLVED in spine, Cipher Maps already $\le$): composition is
  an inequality.** $\eta_{\mathrm{total}} \le 1 - \prod_i (1-\eta_i)$, not
  $=$: "every stage correct" is sufficient but not necessary (a stage error
  can be masked by a downstream stage). The spine headline (Property 4) and
  the §3.3-3.5 displays said $=$; now $\le$, with a masking note at §3.3.
  `cipher-maps` Theorem 7.1 (and Theorem 4.1) already state $\le$; the $=$
  that remains there is the algebraic identity
  $1-(1-\eta_f)(1-\eta_g) = \eta_f+\eta_g-\eta_f\eta_g$, which is correct.
  This closes the spine side of the paper's review item M4. Monograph `ch04`
  `thm:composition` carries the canonical $\le$ form with a full short proof.
- **BP-5 RESOLVED (spine §4A.1).** The entropy-ratio normalizer is now
  $H^* = \log_2|\mathrm{Im}(\mathrm{enc})|$ (image-relative), not the ambient
  $n$: line ~600 ($e = 1 - D_{\mathrm{KL}}(Q\|U_{\mathrm{im}})/H^*$) and the
  Fannes bridge line ~603 ($/H^*$). Matches Property 2 (BP-1) and the Entropy
  Ratio paper; the C-11 image-relative family is now uniform across the spine.
- **BP-6 RESOLVED + C-4 SUPERSEDED (spine §4A.2/§4A.3).** The C3
  joint-recovery lower bound is **Assouad's lemma** ($2^{m/2}$ packing), not
  "Le Cam's two-point method": line ~626 is fixed, and §4A.3 is retitled and
  corrected (Le Cam two-point is the MARGINAL M2 tool; Assouad is the
  COMPOSITIONAL C3 tool; they are different methods, not one method in two
  roles, and the table now has a Method column). C-4's "the two-point method
  appears at both scales" framing was stale, predating the Entropy Ratio
  round-2 Assouad fix, and is superseded by the corrected §4A.3. Monograph
  `ch10` `rem:assouad-not-lecam` carries the canonical distinction.
