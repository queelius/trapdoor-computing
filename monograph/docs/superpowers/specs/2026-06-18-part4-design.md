# Design: Part IV (Confidentiality)

**Author:** Alexander Towell
**Date:** 2026-06-18
**Status:** Design (pre-implementation)
**Parent spec:** `docs/superpowers/specs/2026-06-10-master-design.md`
**Scope:** Section-level outline for chapters 9-10 (Part IV, ~28 pp budget; expect ~12-14 pp at the established density). Authoritative for the ch9-10 implementation plans.

## 1. Purpose

Part IV is the quantitative confidentiality theory: it takes the two scales previewed in Parts II-III and gives each its measure and its sharp bound. Ch 9 is the marginal scale, a single cipher value, where the entropy ratio `e = H/H*` measures leakage and the Fannes-Audenaert bridge ties it to `delta`. Ch 10 is the compositional scale, several evaluations on a shared cipher value, where the latent joint distribution is recoverable at a rate `Theta(|Y_1||Y_2|/xi^2)` that no per-map parameter can move. The part's thesis is the irreducibility of the two scales: small `delta` buys marginal confidentiality and nothing compositional; the compositional channel is intrinsic to composability itself.

## 2. The governing constraint: SUMMARIZE, do not re-prove

**This part is different from Parts II-III.** The fold source, `papers/maximizing-confidentiality` ("The Entropy Ratio"), is a live standalone submission (CSF). The book must **summarize and point**, not reproduce its proofs. State each theorem, give its intuition and the one-line reason it is true, show the case study, and cite the paper for the full proof. Do NOT lift Theorems 3.1, 4.1, 4.2, 5.1, 5.2 verbatim or reproduce their proofs. This is the master spec's self-overlap risk #3 and the spec-auditor should check it. Proof depth here is "statement + intuition + pointer", uniformly; the only full derivations are the elementary identities already established (e.g. `e = 1 - D_KL(Q||U)/H*`).

## 3. The six landmines (ALL live in this part)

Part IV is the densest landmine field in the book. Every one must be carried in its corrected form, and each chapter that touches one cross-references `book/CLAUDE.md`:

| # | Landmine | Correct form | Where |
|---|---|---|---|
| 1 | Fannes, not Pinsker | `e >= 1 - delta - h_2(delta)/H*`, **linear** in delta (Pinsker runs the wrong way) | Ch 9.2 |
| 2 | `K(x) ~ D(x)`, not `1/D(x)` | homophonic: frequent values get MORE representations | Ch 9.3 |
| 6 | image-relative `delta` | `H* = log2|im(enc)|`, normalizer is `H*` not `n` | Ch 9.1-9.2 |
| 5 | mixture entropy `H(C)` not `H(C,B)` | noise injection observed entropy is `H(rho*D + (1-rho)*U_im)`, NOT the source-plus-indicator sum (which is the joint `H(C,B)`, an over-count) | Ch 9.3 |
| 4 | Assouad, not Le Cam | compositional lower bound is Assouad's lemma (`2^{m/2}` packing); Le Cam two-point is a DIFFERENT bound (marginal single-guess upper) | Ch 10.2 |
| 3 | orbit denominator `|X|` | `conf >= 1 - |orbit|/|X|` (from Ch 8; referenced, not re-stated) | Ch 10.1 (callback) |

**The Le Cam / Assouad split (C-4) must be stated explicitly.** Le Cam's two-point method IS used in this framework, correctly, for the MARGINAL single-guess attacker's UPPER bound (accuracy `<= 1/2 + delta/2`). Assouad is used for the COMPOSITIONAL minimax LOWER bound. Ch 10.2 should name both and distinguish their roles, so a reader who meets "Le Cam" twice does not conflate them.

## 4. Cross-cutting commitments

### 4.1 Running threads

| Thread | Action in Part IV |
|---|---|
| Measurable-not-negligible | **Culminates** in Ch 9 (the entropy ratio is the measure the whole book promised) |
| Two-scale confidentiality | **Paid off** in full: Ch 9 marginal, Ch 10 compositional, with the irreducibility theorem the centerpiece |
| `delta` -> leakage (Fannes bridge) | Ch 9.2 (pays off Ch 4.2's `def:uniformity` and the Ch 1.3 entropy-ratio tease) |
| Totality as privacy | Ch 10: totality creates the compositional channel (the same property, now a leakage source) |
| Composition predictability | Ch 10: composability (Ch 4.4) is what makes the compositional channel intrinsic |

### 4.2 Backward debts paid

- Ch 1.3 (`sec:measured-not-negligible`) teased the entropy ratio: Ch 9.1 delivers it.
- Ch 4.2 (`def:uniformity`) left `delta` as a marginal parameter with a forward promise: Ch 9.2's Fannes bridge turns `delta` into a leakage bound, and Ch 10 shows where it stops mattering.
- Ch 8 (`thm:orbit-bound`, `rem:active-vs-marginal`) previewed the compositional scale: Ch 10 delivers C2 (coincidence oracle) and C3 (joint recovery), and Ch 10.1 recalls C1 (orbit) as the active-adversary member of the family.
- Ch 7.4 (`rem:granularity`) forwarded the `O(|Y_1||Y_2|/xi^2)` rate: Ch 10.2 gives it its matching (Assouad) lower bound.

## 5. Chapter 9: The Marginal Scale (~14 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 9.1 | The entropy ratio | ~3 | maximizing-confidentiality §3; spine §4A.1 | Numbered Definition: `e = H(Q)/H*`, `H* = log2|im(enc)|` (IMAGE-RELATIVE, landmine 6), `e = 1 - D_KL(Q||U_im)/H*`, `e in [0,1]`, `e=1` iff uniform. The measure the measurable-not-negligible thread promised. Pays off Ch 1.3. |
| 9.2 | The Fannes bridge | ~3 | maximizing-confidentiality Thm 3.1; spine §4A.1 | The bound `e >= 1 - delta - h_2(delta)/H*`, **LINEAR** in delta (landmine 1: Fannes-Audenaert, not Pinsker; say why Pinsker runs the wrong way). Statement + intuition + pointer. This is what makes `delta` (Ch 4.2) a confidentiality lever. Le Cam single-guess upper bound `<= 1/2 + delta/2` noted here (marginal; landmine 4 first half). |
| 9.3 | Three levers for delta | ~5 | maximizing-confidentiality §4 (Thms 4.1, 4.2); spine §4A | The three `delta`-reduction constructions, each STATED with its cost: (a) noise injection / Fisher dilution `rho^2`, with the observed entropy `H(rho*D + (1-rho)*U_im)` (landmine 5: `H(C)` not `H(C,B)`); (b) multiplicity `K(x) ~ D(x)` homophonic (landmine 2: not `1/D`); (c) joint-encoding granularity (callback Ch 7.4). |
| 9.4 | A worked case study | ~2 | maximizing-confidentiality § casestudy (Table 4) | The end-to-end number: `e` from 0.72 to 0.94 under homophonic multiplicity plus noise (corrected mixture-entropy values 0.72/0.87/0.84/0.94, ~1.05x space, ~1.5x bandwidth). The marginal scale made concrete. Numbers Python-verified. |
| 9.5 | Notes and Provenance | ~1 | fresh | The Entropy Ratio paper is the owner (CSF); this chapter summarizes. Record landmines 1, 2, 5, 6. |

## 6. Chapter 10: The Compositional Scale (~14 pp budget)

| Sec | Title | Pages | Source | Purpose |
|---|---|---|---|---|
| 10.1 | Three ways operations leak | ~3 | spine §4A.2; algebraic-cipher-types | The family of compositional/active measures: C1 orbit closure (recall Ch 8, active adversary), C2 multi-instance coincidence oracle (`accuracy(t) = 1 - (1/2) sum_y alpha(y)^t`, concentrated partitions defend), C3 shared-variable joint recovery. Sets up the headline (C3). |
| 10.2 | The joint-recovery rate | ~5 | maximizing-confidentiality Thm 5.1, 5.2 (SUMMARIZE) | **The headline.** Observing `(f1-hat(c), f2-hat(c))` on shared `c`: MI preserved exactly `I(f1-hat(C);f2-hat(C)) = I(f1(X);f2(X))`; joint recoverable at `Theta(|Y_1||Y_2|/xi^2)`, upper by plug-in, **lower by Assouad's lemma** (landmine 4: NOT Le Cam; the `2^{m/2}` packing). Statement + intuition + pointer to CSF paper. Distinguish the two Le Cam/Assouad roles explicitly (C-4). |
| 10.3 | Why no parameter helps | ~3 | maximizing-confidentiality Rmk (irreducibility); spine §4A | The irreducibility: no per-map parameter, `delta` included, moves the rate. `delta` is necessary but not sufficient. The two scales do not reduce. Totality (Ch 3) and composability (Ch 4.4) are what create the channel: the privacy mechanism and the leakage source are the same property. |
| 10.4 | System-level defenses | ~2 | maximizing-confidentiality §; spine §4A | What DOES help at the compositional scale: reduce shared-`c` observations, raise entanglement `p` (joint encoding, Ch 7.4), inject noise. Marginal tuning alone does not. Forward to `part:constructions` and `part:frontiers`. |
| 10.5 | Notes and Provenance | ~1 | fresh | Owner is the Entropy Ratio paper (CSF headline = Thm 5.1/5.2). Record landmine 4 (Assouad) and the spine §4A.1 normalizer / §4A.2 Le Cam residuals as back-port candidates. |

## 7. Forward / backward reference map

- **Backward (real `\cref`):** Ch 9.1 pays off `sec:measured-not-negligible` (Ch 1.3) and `def:uniformity` (Ch 4.2); Ch 9.2 builds on `def:uniformity`; Ch 9.3(c) recalls `rem:granularity` (Ch 7.4); Ch 10.1 recalls `thm:orbit-bound` and `rem:active-vs-marginal` (Ch 8); Ch 10.2 gives the lower bound `rem:granularity` forwarded; Ch 10.3 recalls `def:totality` and `thm:composition`.
- **Forward (footnote, part labels):** the concrete constructions that realize the defenses `part:constructions`; the open problems `part:frontiers`.
- **External pointer (the owner):** every compositional theorem points to `\cite{towell2026maxconf}` for the full proof.
- **Within Part IV:** ch9 -> ch10.

## 8. Page budget

Ch 9 ~14, Ch 10 ~14 (master ~28). At density expect ~6-7 pp/chapter, ~12-14 pp total. Because this part SUMMARIZES, it is naturally tighter than a proving part; do not pad to budget. The case study (9.4) and the irreducibility argument (10.3) are the priority for care.

## 9. Harvest (back-port: spine §4A residuals)

Drafting Part IV against the corrected Entropy Ratio paper surfaces spine §4A residuals to back-port:

- **BP-5 (NEW): spine §4A.1 entropy-ratio normalizer.** Spine line ~600/603 writes `e = 1 - D_KL/n` and the Fannes bridge `e >= 1 - delta - h_2(delta)/n` with normalizer `n` (ambient). The Entropy Ratio paper uses `H* = log2|im(enc)|` (image-relative, landmine 6). Same family as BP-1/C-11. **Action:** propagate `H*` to the spine §4A entropy-ratio and Fannes-bridge lines.
- **BP-6 (NEW): spine §4A.2 C3 lower-bound attribution.** Spine line ~626 says the joint-recovery lower bound is "Le Cam's two-point method"; the Entropy Ratio paper Thm 5.2 (and book/CLAUDE.md landmine 4) establish it is **Assouad's lemma**. The spine's own §4A.3 hazard table is consistent with Assouad (it names Thm 5.2) but line 626 contradicts it. **Action:** fix spine line 626 to Assouad. Log to HARVEST when ch10 is drafted.
- **Cross-cut:** the two-scale irreducibility statement (Ch 10.3) is a clean candidate canonical phrasing for the spine §4A intro.

## 10. Risks (part-specific)

1. **Self-overlap with the CSF submission (highest).** SUMMARIZE; do not reproduce proofs. The spec-auditor must verify Part IV paraphrases and points.
2. **Landmine reversion (six of them, all here).** Verify each against `book/CLAUDE.md` and the Entropy Ratio CLAUDE.md on every draft; the case-study numbers especially (landmine 5 reproduced the wrong numbers to four decimals once).
3. **Le Cam / Assouad conflation.** State both, distinguish roles (C-4). The compositional lower bound is Assouad.
4. **Equating the two scales.** The entropy ratio `e` (marginal, normalized) and the orbit residual entropy / joint-recovery (compositional, unnormalized) are different quantities; never equate (spine §4A.2 note).

## 11. Out of scope (Part IV)

The concrete constructions realizing the defenses (Part V); the full CSF proofs (cited, in the standalone paper); the adaptive / distributional-drift maintenance (the `adaptive-trapdoor` sibling, a frontier in Part VI).

## 12. Success criteria

- The entropy ratio defined image-relative (`H* = log2|im(enc)|`); Fannes bridge linear (not Pinsker).
- The three `delta` levers stated with costs; mixture entropy `H(C)` not `H(C,B)`; `K ~ D` not `1/D`.
- The compositional rate `Theta(|Y_1||Y_2|/xi^2)` with the lower bound attributed to **Assouad** (not Le Cam), and the Le Cam marginal role distinguished.
- The irreducibility argument (no parameter moves the rate; the two scales do not reduce) stated clearly.
- The case study numbers (0.72 -> 0.94) Python-verified.
- Everything SUMMARIZES with a pointer to `\cite{towell2026maxconf}`; no lifted proofs.
- `make` builds Part IV clean; `HARVEST.md` logs BP-5, BP-6.

## 13. Next step

Draft ch9 then ch10 directly from this spec (as Parts II-III). After Part IV, the master sequencing goes to Part V (Constructions), which realizes the cipher maps and the defenses these two chapters specify.
