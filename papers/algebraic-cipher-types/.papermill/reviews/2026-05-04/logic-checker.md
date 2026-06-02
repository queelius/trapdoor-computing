# Logic Checker Report

**Date**: 2026-05-04 (cross-paper-informed, sixth substantive round)
**Reviewer role**: Proof correctness, logical-chain integrity, claim support.
**Scope this round**: (1) the NEW algebraic material (Prop 4.4, Prop 4.5, Table 1); (2) cross-paper logical consistency against the foundation paper `cipher_maps.tex`; (3) independent re-adjudication of the Thm 5.3 proof-gap raised by the immediately-preceding 2026-05-23 round.

All foundation line/label numbers verified against `cipher_maps.tex` and `cipher_maps.aux` (both build clean; foundation is 39pp, ACT is 21pp).

---

## A. New algebraic material (cold read)

### Prop 4.4 "Cipher exponential is the cipher map abstraction" (ACT 598-618) -- SOUND, but definitional

The statement (C(A->B) is precisely the set of cipher maps for f:A->B; a function is a well-formed element iff it satisfies the four properties) is **correct**. The proof is a definitional unpacking: a cipher map for f:A->B *is* a total function on B^n correct on encodings of A, and conversely. There is no hidden step and no error.

Cross-paper check: the facts the proof leans on -- "a cipher map is a total function over B^n satisfying the four properties" -- are exactly Foundation **Def 3.1** (`def:cipher-map`, cipher_maps.tex:388) plus the four properties of Foundation **§4** (`sec:properties`). I confirm the foundation does **not** itself use any "exponential type" / B^A framing anywhere (grep of the full foundation .tex: no occurrence of exponential-as-function-type). The closest the foundation comes is the *functorial* shorthand C_s(.) as a functor from latent types to Cipher_s (cipher_maps.tex:366-385), which is explicitly deferred to companion rekeying work and not used. So ACT's generic `(per~\cite{towell2026cipher})` at line 612 supports the cipher-map facts **without over-attributing** the type-theoretic exponential framing to the foundation. Verdict: attribution is correct; the exponential framing is genuinely ACT's. (No over-attribution defect.)

Presentation note (concur with 2026-05-23 MIN): a "Proposition + Proof" frame slightly oversells what is an identity-by-definition. This is cosmetic, not a soundness issue.

### Prop 4.5 "Exponential confidentiality trade-off" (ACT 630-665) -- SOUND

Part (1) (component-wise application reveals the computation pattern: two distinct cipher-map invocations are visible) is correct and follows from the untrusted machine seeing two separate total functions applied. Part (2) (joint application as one product cipher map for (f,g)(a,c)=(f(a),g(c)) hides which constituents were applied; costs O(|A|.|C|) vs O(|A|)+O(|C|)) is correct.

The size claim O(|A|.|C|) is attributed to "the lookup-table cost in [Sec.~6] of the foundation" (ACT:664). Cross-paper check: Foundation **§6** ("The Batch Construction", `sec:batch`) states space as **bits per element** (Thm 6.2 `thm:space-optimal`, cipher_maps.tex:1187: `(1-eta)(-log2 eps + mu)` bits/elem), and the lookup table has one entry per domain element. A construction over domain A x C therefore has |A|.|C| entries, so total table size is proportional to |A|.|C|. The ACT claim is **supported**, though the foundation expresses it as per-element cost rather than as a table-size big-O; a reader chasing the cite finds bits/element, not a literal "O(|A|.|C|) lookup-table cost" statement. Recommend ACT either (i) keep [Sec.~6] but phrase as "domain size |A|.|C| entries, each of the per-element cost of [Foundation Thm 6.2]", or (ii) cite Foundation Thm 6.2 specifically. Minor.

The closing sentence (ACT:667-670, the part-(2) asymmetry "recapitulates the product-type trade-off") is logically consistent with Prop 4.1.

### Table 1 (ACT:681-700) vs prose and per-constructor results -- CONSISTENT

Row-by-row against the propositions:
- void/unit: "N/A" / "nothing to hide/leak" -- matches §4.1.
- A x B (Prop 4.1): joint hides "correlations between a,b"; component-wise leaks "joint distribution as N->inf" -- matches Prop 4.1 parts (1),(2) verbatim in substance.
- A + B (Thm 4.2): joint hides "the tag"; component-wise leaks "the tag, by impossibility" -- matches Thm 4.2. The "by impossibility" cell correctly encodes the categorical (not asymptotic) nature.
- A -> B (Prop 4.5): joint hides "the computation pattern"; component-wise leaks "which functions are being applied" -- matches Prop 4.5 parts (2),(1).

The three prose observations (universal granularity knob; sums categorically different; closure under orbit framework) are each supported. The "sums categorically different" observation (ACT:714-724) is the one genuine seam to watch (see §C below) but it is logically correct: products/exponentials admit intermediate encodings with asymptotic-only recovery, sums admit none. No internal contradiction.

**Algebraic frame is coherent end-to-end.** The lead-in (§4 intro, 308-339), the per-constructor subsections, Table 1, and the conclusion all tell the same "one algebra, universal granularity knob, three constructor-specific costs, sum is categorically different" story. I found no place where the old "sum-impossibility-is-the-headline" framing contradicts the restored algebra; sum is now correctly presented as one of three results, distinguished by being categorical rather than by being primary.

---

## B. Cross-paper logical consistency

### B1 (MAJOR, cross-paper). Composability misstated as strict equality.

- **ACT §3, line 262-263** states Property 4 (Composability) as a strict equality:
  > the composition g^.f^ has correctness eta_{g.f} = 1 - (1-eta_f)(1-eta_g).
- **Foundation Thm 4.2** (`thm:composition-correctness`, cipher_maps.tex:660-672) states it as an **inequality with a qualifier**:
  > eta_{g.f} <= eta_f + eta_g - eta_f eta_g = 1 - (1-eta_f)(1-eta_g), with equality under the re-randomization condition.
- **Confirmed**: ACT's preliminaries misstate the foundation's own theorem. The foundation deliberately switched to `<=` (re-randomization, Foundation Def 7.1 `def:re-randomization`, is what makes equality the typical-but-not-universal case; see Foundation rem:master-vs-op 635-646).
- **Load-bearing assessment**: I traced every downstream use of composition-correctness in ACT §4-§7. **Nothing in ACT relies on the equality being exact.** The orbit-closure framework (§5) is correctness-agnostic (Def 5.1 depends only on the cipher maps as total functions, explicitly *not* on eta). The typed-chain bound (Prop 5.5) counts reachable cipher values, not error. The cipher-Boolean experiments (§7) measure FPR empirically and never invoke the multiplicative composition law as an equality. The only place eta-composition appears substantively downstream is the noise/error discussion, which does not need exactness. **So this is a fidelity-to-source defect, not a propagating logical error.** Fix is a one-line restatement.
- **Suggested fix**: ACT:262-263 ->
  > the composition g^.f^ has correctness eta_{g.f} <= 1 - (1-eta_f)(1-eta_g), with equality under the foundation's re-randomization condition.
- **Severity**: Major (it misquotes a cited theorem; an external reviewer who is also the foundation author will catch it), but cheap and non-propagating.

### B2. Citation-number defects affecting logical claims.

These are tabulated fully in the citation-verifier report and the unified review's cross-paper section. From a logic standpoint, the one that matters most is **ACT:1168** `[Prop.~9.1]` for "the joint distribution of (enc_f(x), enc_g(x)) preserves the correlation" in the shared-variable Remark (rem:shared-vars). The supporting result is Foundation **Prop 8.1** `prop:granularity` (cipher_maps.tex:1678) -- and more directly Foundation **§8.2 "Compositional Leakage"** (cipher_maps.tex:1720-1742), which proves *exactly* the shared-input claim ("the untrusted machine observes both y^=f^1(c) and z^=f^2(c) for the same cipher value c ... the joint distribution preserves the latent correlation"). The cited claim is **true and supported**; only the number (9.1 -> 8.1) is wrong. So this is wrong-number, not wrong-claim. Recommend citing Foundation §8.2 (compositional leakage) in addition, since it is the precise match for the shared-variable scenario.

---

## C. Re-adjudication of the Thm 5.3 proof gap (2026-05-23 MAJ-1) -- CONFIRMED, and sharpened

The 2026-05-23 logic-checker flagged a soundness gap and rated it "medium-high, second pair of eyes would help." I independently re-derived it. **I confirm the finding and sharpen the diagnosis.**

- **ACT setup (841-844)**: "let V_F(c) = orbit_F(c) denote the adversary's view: the set of cipher values reachable from c under F."
- **ACT proof (858-867)**: "The view V_F(c) takes at most |orbit_F(c)| distinct values as X ranges ... Therefore I(X;V_F(c)) <= H(V_F(c)) <= log2|orbit_F(c)|, and H(X|V_F(c)) = H(X) - I(X;V_F(c))."

The earlier round framed the gap as "set vs single value" and suggested the realization count is bounded by the number of distinct starting values c. That is true but **points away from the intended theorem**. The sharper diagnosis:

The paper's own Remark (after Def 5.1, ACT:775-782) stresses that **the orbit depends only on c and F, not on x / the latent value / the trapdoor.** Therefore, taken literally, `V_F(c) = orbit_F(c)` is the *same set* for every realization of X (once c is fixed): it is a **constant** random variable. A constant has `H(V) = 0`, so `I(X;V) = 0`, and the proof's own chain yields `H(X|V) >= H(X) - 0 = H(X)` -- the **vacuous** bound, not the claimed `H(X) - log2|orbit|`. The displayed inequality `H(V_F(c)) <= log2|orbit_F(c)|` is being read as if V ranges *over* the orbit, but the setup says V *is* the orbit.

So the statement of Thm 5.3 is fine (and the intended reading is a textbook QIF fact), but the proof as written either proves a vacuous statement (literal reading) or silently swaps the random variable (intended reading). This is a genuine Major proof defect, **independent of any cross-paper issue.**

- **Clean fix** (the 2026-05-23 option (b), which I endorse): prove the set-form first by an injective-decoder argument, then derive the entropy form.
  1. The adversary's distinguishing observable is which element of orbit_F(c) it lands on (or, more conservatively, the equivalence class its probes induce). Call this observable W; W takes at most |orbit_F(c)| values.
  2. Any deterministic deduction from W to a latent candidate is a function, so the ambiguity set S_F(c) satisfies |S_F(c)| <= |range(W)| <= |orbit_F(c)| (this is Corollary 5.4's content; its current proof at 881-887 hand-waves "distinguished ... by at least one observable feature" -- replace with the injectivity argument).
  3. Then H(X | W) >= H(X) - log2|S_F(c)| >= H(X) - log2|orbit_F(c)|.
  State Thm 5.3 with W (the orbit-landing observable) as the conditioning variable rather than the orbit-as-set. About 30 minutes of editing; the theorem *statement* (and hence the abstract/intro/conclusion which quote it) is unchanged.

- **Cross-paper note that strengthens the fix**: ACT's orbit measure is genuinely distinct from the foundation's confidentiality measure. Foundation **Prop 5.1** (`prop:confidentiality`, cipher_maps.tex:808) bounds the **entropy ratio** `e = H(Q)/n` (Q = marginal cipher-value distribution; Foundation Def 5.3 `def:entropy-ratio`, 773) via Fannes-Audenaert. That is a *marginal-uniformity* quantity (about delta), not a *reachability* quantity. ACT's H(X|view) >= H(X) - log2|orbit| is about how many cipher values the adversary can *reach by composition*. These do not conflict and one is not derivable from the other. So the repaired Thm 5.3 occupies clean, non-overlapping ground relative to the foundation; the fix does not need to defer to the foundation's bound.

**Severity**: Major (load-bearing theorem; proof as written does not establish the claim). Recoverable without changing the statement. Cross-verified by my own re-derivation plus the methodology lens (the probabilistic-structure setup is wrong; the underlying leakage-bounded-by-orbit-size claim is sound).

---

## D. Confirmed sound (re-verification, condensed)

- **Thm 4.2 sum-type impossibility** (459-549): correct. Three-part argument is tight; the balanced-case simplification (1/2 - gamma <= delta') and the "unbalanced makes it stronger" remark are right.
- **Prop 4.1 product trade-off** (402-441): correct; part (2) convergence argument is standard.
- **Thm 5.2 monotonicity** (790-810): correct (trivial induction).
- **Prop 5.5 typed-chain orbit bound** (1034-1069): correct. Partition-by-level, N_{i+1}=N_i^{a_i}, special cases m=1 -> 1+k and a_i=1 -> m(k+1) all check out. This remains the paper's cleanest designer-actionable result.
- **Prop 7.x noise unreliability** (1318-1341): correct.
- **Table 2 (FPR compounding) numerics** (1454-1478): re-verified. Theoretical AND = p_T^k, OR = 1-(1-p_T)^k for p_T=0.05 reproduce the displayed values; ratios 1.01/2.96/35.2/256/12160 (AND), 0.90-1.02 (OR) reproduce. Structural explanation (deterministic cipher map composed with itself breaks Bernoulli independence) is logically sound.

## Confidence

High. The Thm 5.3 gap is real (independently re-derived, sharpened: literal reading is vacuous because the orbit is x-independent). The composability =/<= mismatch is confirmed verbatim against Foundation Thm 4.2 and is non-propagating. The new Props 4.4/4.5 are sound. No new soundness problems in the algebraic restructure.
