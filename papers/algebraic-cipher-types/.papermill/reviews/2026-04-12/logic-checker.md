# Logic Checker Report

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp, 1398 lines)
**Date**: 2026-04-12
**Scope**: Proof correctness, logical chain integrity, claim support.

## Summary

The 2026-04-08 logic-checker flagged two critical issues. C1 (Proposition 6.1 noise absorption falsity) was fixed cleanly by reformulating to "noise unreliability" (current Prop 7.1). C2 (inconsistent formulas in Theorem 4.3 and disconnected candidate-set definition) was only partially fixed: the cleanup to a single formula is good, but the candidate-set definition (now Def 5.2) still fails to use the orbit in a non-trivial way, because the added clause is a tautology.

Two new issues surfaced:
- The typed-chain orbit bound (Prop 5.4) is stated using a unary chain signature but the examples are binary, and the bound `1+k` is wrong for multi-argument operations in full orbit closure.
- Minor dimensional/interpretive inconsistency between the candidate-set definition (using |X| as denominator) and the theorem (using 2^n).

The seven formal results audit as follows:

| Result | Status | Notes |
|--------|--------|-------|
| Prop 4.1 (product trade-off) | Sound | |
| Thm 4.2 (sum impossibility) | Sound (as stated) | Balanced-prior case handled; unbalanced mentioned. |
| Thm 5.1 (monotonicity) | Sound, trivial | |
| Cor 5.2 (empty ops) | Sound, trivial | |
| Def 5.2 + Thm 5.3 (conf bound) | **Remaining issue** | Tautological clause in Def 5.2; proof uses informal reasoning rather than the stated definition. |
| Prop 5.4 (typed chain bound) | **Issue** | Orbit bound `1+k` holds only for unary chains; Example 5.4 uses binary AND, making the bound inapplicable as stated. |
| Prop 6.1 (cipher-TM space) | Sound | |
| Prop 6.2 (head-movement leakage) | Sound, trivial | |
| Prop 7.1 (noise unreliability) | Sound | Reformulation of old Prop 6.1 succeeds. |

---

## Critical Issues

### LC-CRIT-1. Candidate-set definition (Def 5.2) still does not use the orbit

**Location**: Section 5.3, Definition 5.2 (lines 637 to 648).

**Quoted text**:
> Cand_F(c) = { x in X | exists k s.t. enc(x, k) = c and orbit_F(enc(x,k)) = orbit_F(c) }.

**Problem**: The orbit function depends only on its cipher-string argument. Therefore whenever enc(x, k) = c, the equality orbit_F(enc(x,k)) = orbit_F(c) is automatic (both equal orbit_F(c)). The second clause is a tautology. The definition reduces to

  Cand_F(c) = { x in X | exists k s.t. enc(x, k) = c },

which does not depend on F at all. The subscript F on Cand_F remains misleading. This is the same defect C2 flagged in the 2026-04-08 review; the restructure added a clause that looks relevant but does no work.

The proof of Thm 5.3 (lines 672 to 689) silently uses a *different*, informal notion: "every orbit element is a valid encoding of a distinct latent value. The adversary then knows the latent value is one of at most |orbit_F(c)| possibilities out of |X| total." This treats orbit elements as distinguishable equivalence-class representatives, not candidates encoding c. The formal definition and the proof are incompatible.

**Suggestion**: Redefine Cand_F(c) to require consistency across the orbit, not just at c. For instance:

  Cand_F(c) = { x in X | there exists an assignment
      x_{c'} in X cup {noise} for each c' in orbit_F(c) such that
      x_c = x and for every (c', c'') in orbit_F(c)^2 with f(c') = c''
      (some f in F), f_latent(x_{c'}) = x_{c''} is satisfiable }.

Alternatively, present the theorem in terms of the cipher-space coverage `|orbit_F(c)| / 2^n` directly (information-theoretic leakage) and drop the candidate-set detour. The informal argument in the proof is essentially an entropy-style argument: if the adversary sees k distinct cipher values, they learn at most log_2 k bits about the latent value. Formalizing that directly would be cleaner.

**Cross-verification**: Confirmed by the orbitF function being a pure function of its bit-string argument (Def 5.1, lines 550 to 563), which makes the added clause tautological.

---

## Major Issues

### LC-MAJ-1. Typed composition chain bound (Prop 5.4) is wrong for binary operations

**Location**: Section 5.5, Definition 5.4 (lines 810 to 817), Proposition 5.4 (lines 824 to 847), Example 5.4 (lines 849 to 866).

**Quoted text**:
> A typed composition chain of depth k is a sequence of cipher maps f_0, ..., f_{k-1} where f_i : C(A)_i -> C(A)_{i+1} ...
>
> [Prop 5.4:] |orbit_F(c)| <= 1 + k, where each step adds at most one new cipher value (the output of f_i applied to the previous result).

**Problem**: The signature `f_i : C(A)_i -> C(A)_{i+1}` is unary. The proof walks through `c -> f_0(c) -> f_1(f_0(c)) -> ...` producing exactly one new cipher value per step. Under this signature, the bound `1+k` is correct.

But Example 5.4 defines `AND_0 : C(Bool)_0 x C(Bool)_0 -> C(Bool)_1`, a binary operation. With binary operations and full orbit closure, multiple distinct values at each level are reachable. For instance, with two starting cipher Booleans c_a, c_b in C(Bool)_0:

- Level 0: {c_a, c_b} (size 2)
- Level 1: {AND_0(c_a, c_a), AND_0(c_a, c_b), AND_0(c_b, c_a), AND_0(c_b, c_b)}, up to 4 new values
- Level 2: AND_1 applied to pairs of level-1 values, up to 16 new values
- Total orbit size could be 2 + 4 + 16 = 22, not 1 + 2 = 3.

The orbit closure definition (Def 5.1) takes a single starting c, and cipher maps f_i in F can be any arity (the paper nowhere restricts to unary). If the paper means the orbit of a *single* c under binary operations, then AND_0(c, c) is the only level-1 reachable value, AND_1(AND_0(c,c), AND_0(c,c)) is the only level-2 reachable, so one new per level, and bound `1+k` is recovered. But Example 5.4's language ("AND queries of depth 2") strongly suggests multiple starting cipher values (the terms of the Boolean query).

**Suggestion**: Either
(a) Restrict Prop 5.4 to unary chains and add a separate treatment of binary/multi-ary chains, with orbit bound of the form `1 + |C(A)_0| + |C(A)_0|^2 + ...` or similar;
(b) State the proposition for the orbit of a single starting value under an arity-agnostic chain with explicit argument about why self-combinations are controlled; or
(c) Rework Example 5.4 to a unary chain (e.g., successor or NOT) so the proposition and example match.

Option (b) is most faithful to the intended message ("typed spaces prevent unbounded growth"). The correct bound for binary chains with k levels starting from m initial values is something like `sum_{i=0}^{k} m^{2^i}`, still finite, still bounded by the type system, but not `1+k`.

### LC-MAJ-2. Denominator switch in Theorem 5.3 proof is not rigorously justified

**Location**: Section 5.3, Theorem 5.3 and proof (lines 661 to 689).

**Quoted text**:
> [Def 5.3:] conf_F(c) = 1 - |Cand_F(c)| / |X|.
>
> [Thm 5.3:] conf_F(c) >= 1 - |orbit_F(c)| / 2^n.

**Problem**: The definition uses |X| as the denominator (fraction of the latent space ruled out). The theorem uses 2^n (fraction of the cipher space explored). These are different quantities. The proof bridges them with: "Since |X| <= 2^n (at most 2^n distinct encodings), the fraction of the cipher space explored is |orbit_F(c)| / 2^n, and the remaining unexplored fraction bounds the confidentiality."

This is actually mathematically defensible but the path is obscure. Cleanly:
- Proof argument: `|Cand_F(c)| <= |orbit_F(c)|` (under the "every orbit element encodes a distinct latent value" worst case).
- Hence `conf_F(c) = 1 - |Cand|/|X| >= 1 - |orbit|/|X|`.
- Since `|X| <= 2^n`, we have `|orbit|/|X| >= |orbit|/2^n`, so `1 - |orbit|/|X| <= 1 - |orbit|/2^n`.

Wait: if we have `1 - |orbit|/|X| <= 1 - |orbit|/2^n`, and we want to conclude `conf >= 1 - |orbit|/2^n`, we'd need `conf >= 1 - |orbit|/|X| >= 1 - |orbit|/2^n`. But `>=` then `<=` gives no transitive `>=` relation. The substitution from `|X|` to `2^n` in the denominator goes the wrong way, yielding a weaker (smaller) lower bound, which does NOT follow from the tighter one.

To make the claim `conf_F(c) >= 1 - |orbit_F(c)| / 2^n` rigorous, you need `|Cand_F(c)| / |X| <= |orbit_F(c)| / 2^n`, i.e., `|Cand_F(c)| <= |orbit_F(c)| * |X| / 2^n`. This requires an argument about how many latent values can correspond to the orbit, taking density into account.

**Suggestion**: State the theorem with `|X|` in the denominator: `conf_F(c) >= 1 - |orbit_F(c)| / |X|` (assuming the candidate-set fix from LC-CRIT-1). This follows directly from `|Cand| <= |orbit|` and the definition of `conf`. If `|orbit|/2^n` is desired for pedagogical reasons (it matches "fraction of cipher space explored"), state it as a corollary under the additional assumption `|X| = 2^n` (perfect packing).

Alternative, more honest version: bound confidentiality by entropy. If the adversary observes k distinct cipher values in the orbit, and the encoding is uniform, they learn at most log_2 k bits about the latent value, so the conditional entropy is H(X) - log_2 k, where k = |orbit|. Confidentiality in entropy units is then `H(X | view) >= H(X) - log_2 |orbit|`. This is cleaner and decouples from |X|/2^n arithmetic.

---

## Minor Issues

### LC-MIN-1. Cipher TM head direction: inconsistent framing

**Location**: Section 6.1, Definition 6.1 (lines 906 to 923).

**Quoted text**:
> ... obtains a cipher encoding of (next state, symbol to write, head direction). The head direction is not cipher-encoded: it is in the clear, ...

**Problem**: The output is described as "a cipher encoding of (next state, symbol to write, head direction)" but then the head direction is "not cipher-encoded." If the triple is packaged as a single cipher value, the direction cannot be in the clear. The actual construction must be: output is a pair (cipher(next state, symbol), direction_cleartext). The phrasing conflates these.

**Suggestion**: Rewrite to: "...obtains a pair (cipher value c', direction d) where c' is a cipher encoding of (next state, symbol to write) and d in {L, R, S} is in the clear."

### LC-MIN-2. Cipher TM requires a pairing cipher map that is never constructed

**Location**: Section 6.1, Definition 6.1 (lines 906 to 923).

**Problem**: "At each step the untrusted machine evaluates delta_T on the cipher encoding of (current state, symbol read)", this requires the untrusted machine to combine two cipher values (state and symbol) into a single cipher value that delta_T can consume. No such pairing cipher map is given in the text. This was m3 in the 2026-04-08 review and is still unaddressed.

**Suggestion**: Either (a) require state and symbol to be stored as a single cipher value per tape cell, eliminating the pairing; or (b) acknowledge that a pairing cipher map pi : C(Q) x C(Gamma) -> C(Q x Gamma) must be constructed by the trusted machine, with its own space/correctness budget.

### LC-MIN-3. "Up to correctness eta" parenthetical in Example 5.1 is loose

**Location**: Section 5.4, Example 5.1 (lines 705 to 733).

**Quoted text**:
> Now, AND(x, NOT(x)) = 0 for all x (up to correctness eta).

**Problem**: The parenthetical "(up to correctness eta)" is ambiguous. Does the adversary observe the exact cipher encoding of FALSE with probability 1 - eta, or is there an eta-fraction of the time that the output is something else? The quantitative effect on the orbit-size claim is not stated. With eta > 0 the orbit could be strictly larger (including noise outputs) or strictly smaller (if the adversary can't recognize FALSE outputs with certainty). The example is meant to be pedagogical so full rigor isn't required, but a one-sentence clarification would help.

**Suggestion**: "For eta > 0, the output c_2 agrees with a canonical cipher encoding of FALSE with probability >= 1 - eta; deviations inflate the orbit with noise-valued offspring whose confidentiality contribution is treated in Section 7.2."

### LC-MIN-4. "No intermediate encoding achieves both" (Thm 4.2) proof hides the PR bound

**Location**: Section 4.3, proof of Theorem 4.2, third part (lines 438 to 462).

**Problem**: The third part of the proof tries to formalize an impossibility for arbitrary encodings, but the argument reduces to: "pattern matching with success probability >= 1 - gamma gives advantage >= (1 - gamma) - max(p, 1-p) over random guessing." Tag hiding requires this advantage to be <= delta'. Both are bounds on distinguishability. However, "tag hiding" as given in part (1) of the theorem statement uses total variation `delta` (distance of cipher-value distribution from uniform), not the distinguishing advantage of tau. The theorem statement and the proof use two different "tag hiding" notions.

The statement says: "advantage better than delta (the representation uniformity parameter)." If delta is TV distance of the cipher-value distribution from uniform, this is a marginal property, not a distinguishing advantage for tau. For a formal proof, the theorem needs a cleaner definition of "tag hiding advantage" that connects to the distinguishability of tau.

**Suggestion**: Split the theorem statement into "marginal tag hiding" (distribution close to uniform, parameterized by delta) and "operational tag hiding" (no efficient distinguisher, parameterized by advantage bound). Note that marginal tag hiding implies operational tag hiding against a passive adversary, but the proof of the impossibility really needs operational tag hiding. Alternatively, restate with a single clearly-defined notion.

### LC-MIN-5. "All three produce zero errors" is definitional, not empirical

**Location**: Section 7.3, line 1257: "All three produce zero errors on the full domain (150 inputs)."

**Problem**: For a PHF-backed cipher map built over the full domain, zero errors on that domain is guaranteed by construction (this is what "PHF-backed" means: perfect hash, exact lookup). Stating this as an experimental finding is misleading. This is m6 from the prior review and still present.

**Suggestion**: "As expected from the PHF construction, all three produce zero errors on the full domain (150 inputs)."

### LC-MIN-6. "Order of magnitude" not quantified

**Location**: Section 7.3, "FPR compounding" paragraph (lines 1228 to 1242).

**Quoted text**:
> ... AND chains diverge at depth > 2: the empirical FPR exceeds p_T^k by an order of magnitude at k = 3.

**Problem**: The actual numeric value is never stated. The Bernoulli prediction for k=3, p_T=0.05 is 1.25e-4. "An order of magnitude" means 1.25e-3, but the reader has to guess. This is m5 from the prior review and still open.

**Suggestion**: State the empirical value: "the empirical FPR at k=3 is approximately 1.3 x 10^-3, while p_T^3 = 1.25 x 10^-4, a 10x excess." Even better, add a table (Table 2: predicted vs. empirical FPR) with 5 chain lengths.

---

## Suggestions

### LC-SUG-1. Clarify the two realizations' relationship via orbit closure

The cut-point synthesis (Section 6.3) argues that both realizations "share a common pattern" but does not state the orbit-closure correspondence. For a cipher TM, the orbit grows as the tape evolves (one new cipher value per step at most); for expression-tree decomposition, the orbit is bounded by the DAG topology. Making this explicit, "in both realizations, the orbit bound of Prop 5.4 applies with k equal to the longest path in the computation graph", would earn the synthesis.

### LC-SUG-2. Consider presenting the confidentiality bound in entropy form

`H(X | orbit view) >= H(X) - log_2 |orbit_F(c)|` is cleaner than the fraction form, makes the information-theoretic nature explicit, and avoids the |X| vs 2^n denominator issue. It would also connect naturally to the PLAS audience's familiarity with min-entropy and information-flow measures.

### LC-SUG-3. The "branching" example (Ex 5.3) deserves a typed-chain resolution

Example 5.3 discusses branching as a leakage source. The typed-chain discipline (Section 5.5) could be cited as a principled mitigation: branches producing outputs in distinct cipher spaces prevent the adversary from composing them further. This closes the loop between the leakage example and the discipline proposed to manage it.

---

## Cross-cutting Observations

- **Restructure integrity**: All labels resolve; no dangling \Cref or \ref. The promotion of Cipher Boolean to Section 7 and the new Section 6.3 synthesis subsection flow logically.
- **Restructure quality**: The new Section 6 structure (Cipher TM + Expression tree + cut-point synthesis) works at the level of exposition but the synthesis in Section 6.3 is thin (about 15 lines). It would benefit from a running example that illustrates cut-point placement in both realizations side-by-side.
- **Prior-review status**:
  - C1 (noise absorption), **fixed**.
  - C2 (confidentiality bound), **partially fixed**. Formulas cleaned up; candidate-set clause added but is tautological (LC-CRIT-1). Denominator inconsistency remains (LC-MAJ-2).
  - M1 (balanced-prior assumption), **addressed**. Unbalanced case mentioned at end of proof.
  - m3 (pairing operation), **not addressed** (LC-MIN-2).
  - m8 (conf_F undefined before use), **fixed** by Def 5.3.
