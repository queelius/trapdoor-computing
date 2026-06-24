# Novelty Assessor (2026-04-13)

## Scope

Third-round assessment after two rounds of major edits. The contribution structure is now stable: one principle (orbit-closure-bounded confidentiality), three instances (product/sum/exponential type costs), two realizations (expression tree, cipher TM), one practical specialization (cipher Boolean algebra). Focus on whether the contributions are now well-positioned and whether the second-round fixes preserve novelty claims.

## Summary

The paper's contribution structure has stabilized into something coherent. The sum-type impossibility theorem remains the strongest standalone novelty. The orbit-closure framework is a reasonable framing-novel contribution but the second-round entropy-form rewrite has improved its rigor at the cost of introducing minor notational confusion (see logic-checker). The typed-chain orbit budget is sound and well-motivated. The two-realization presentation now earns its unification more fully than in 2026-04-12, though the regex example added in §6.3 is incorrect (see logic-checker).

The bibliography expansion to 21 entries closes the largest gap from 2026-04-12. Two remaining positioning gaps surface for the cipher TM section: vs. obfuscation literature and vs. FHE compilers.

## Contribution-by-contribution assessment

### Contribution 1. Sum-type impossibility (Theorem 4.2)

**Status: strong, well-stated, novel in framing.**

The information-theoretic separation between tag hiding and untrusted pattern matching for `A + B` is the paper's flagship result. The balanced-prior case (`p = 1/2`) and unbalanced case are both treated. The result is construction-independent, which is the right framing for a type-system paper.

**Adjacency to known results**: deterministic-encryption tag leakage is a classical observation in the SSE/PPE literature. The framing here is novel in that it places the impossibility at the type-constructor level rather than at the equality-predicate level.

**Outstanding positioning gap**: One paragraph acknowledging FE lower bounds (Boneh-Sahai-Waters 2011 already cited gives the upper bound; the lower-bound family of FE results would be a natural cousin). Not critical.

### Contribution 2a. Orbit closure (Definition 5.1) and confidentiality bound (Theorem 5.3)

**Status: framework-novel; entropy-form rewrite improves rigor; minor positioning gap.**

The orbit closure as a confidentiality measure for cipher-value transition systems is a framing contribution. The 2026-04-13 rewrite to entropy form (`H(X | view) >= H(X) - log_2 |orbit|`) places the result in the QIF tradition of Smith 2009 (now cited).

**Logic-checker note**: The new theorem's proof has a notational confusion between "view = orbit set" and "view = element of orbit set". The result is sound under either reading, but the proof as written needs tightening.

**Adjacency**: orbit/reachability constructs are old (model checking, dynamical systems, epistemic logic). The novelty is the application to cipher-value transition systems, not the construct itself. A one-paragraph acknowledgment of the dynamical-systems origin (suggested in 2026-04-12) is still missing and would preempt "is this just reachability?" questions.

### Contribution 2b. Typed composition chains (Definition 5.4, Proposition 5.5)

**Status: clean and sound after the M1 fix. Genuinely useful design discipline.**

The 2026-04-12 review flagged the unary-vs-binary arity mismatch. The 2026-04-13 fix introduces explicit arity `a_i` and the recurrence `N_{i+1} = N_i^{a_i}`. The two special cases (single-value start, unary chain) recover prior bounds.

**Logic-checker verification**: walking through the proof and the example confirms the recurrence is sound and the example matches.

**Novelty positioning**: typed-chain depth as a confidentiality budget is genuinely new in this framework. Adjacent to staged compilation in PL but with a distinct goal (orbit bound, not just typed binding times).

### Contribution 3a. Cipher Turing machine (Definition 6.1, Propositions 6.1-6.2)

**Status: cleaner after the LC-MIN-1/LC-MIN-2 fix; new defect introduced in shift cipher map analysis; positioning gap vs. obfuscation literature persists.**

The 2026-04-13 fix replaces "(state, symbol, direction)" cipher with joint cell encoding `C(Q x Gamma)` plus cleartext direction on output. This is structurally cleaner.

**Logic-checker note**: The "second cipher map for the shift operation" is invoked but unanalyzed. Its space cost may be quadratic in `|Q| x |Gamma|` if it operates on adjacent cell pairs jointly. Proposition 6.1's claim of `O(|Q| x |Gamma|)` for `delta_T` does not include the shift cipher map.

**Outstanding positioning gap**: The cipher TM is structurally close to obfuscated FSMs/TMs (Lynn-Prabhakaran-Sahai 2004; garbled TM literature; iO for TMs). The paper preempts ORAM, FHE, FE, and garbled circuits but not these. A PLAS or TCC reviewer will ask "how does this differ from obfuscation/iO?" One paragraph is sufficient.

### Contribution 3b. Expression-tree decomposition with @cipher_node (Definition 6.2)

**Status: well-positioned as the practical realization. FHE-compiler positioning gap persists.**

The decorator-based abstraction is well-described. Encoding granularity controlled by cipher-node placement is a clean design knob.

**Outstanding positioning gap**: @cipher_node is structurally similar to FHE compiler annotations (Concrete, HEIR, CHET, Viand 2021 SoK). The paper does not cite any FHE compiler. This is the same kind of positioning gap as cipher TM vs. obfuscation: not strictly necessary but expected.

### Contribution 3c. Cut-point unification (§6.3)

**Status: better than 2026-04-12 but the new regex example is incorrect.**

The 2026-04-12 review asked for a strengthened §6.3 with a formal cut-point definition, explicit mapping of both realizations, and a worked example. All three are now present.

**Issues**:
- The formal Definition 6.3 of cut point is reasonable.
- The mapping paragraph conflates the typed-chain bound (which requires distinct cipher spaces) with the cipher TM (which does not have distinct cipher spaces between steps; it self-loops). The cipher TM's `1+T` bound comes from determinism, not typed chains. See logic-checker LC-NEW-1.
- The regex example fabricates an exponential cost for the expression-tree decomposition. Both realizations should have `O(ell * |Q| * |Sigma|)` total space; the example's claim of `C(Q)^ell` combiner domain is a strawman. See logic-checker Fix #4.

**Net effect**: §6.3 is more substantive than in 2026-04-12 but has not landed cleanly. The fixes added two new defects.

### Contribution 4. Cipher Boolean algebra and experiments (§7)

**Status: largely unchanged from 2026-04-12. Carry-forward issues persist.**

The cipher Boolean type with T/F/N partition, the noise-unreliability proposition, and the 20 Newsgroups experiments are essentially unchanged. The carry-forward issues (no baselines, no error bars, FPR-compounding finding in prose only, granularity space data missing) are all still open.

The FPR-compounding empirical finding remains the paper's only standalone-publishable empirical result. Promoting it to a proper subsection with a table would strengthen the empirical contribution materially.

## Bibliography state and venue fit

Bibliography is now 21 entries, all cited. The 2026-04-12 expansion closed the largest gap. Remaining gaps:
1. Obfuscation of FSMs/TMs (none cited; would help positioning of cipher TM).
2. FHE compilers (none cited; would help positioning of @cipher_node).
3. Optional: FE lower bounds, multi-stage programming, modern PHF papers, reachability/model-checking.

Venue fit: PLAS remains the strongest target. IACR ePrint is a valid fallback. TCC is weak (game-based proofs expected).

## Disagreements with prior reviews

None. The 2026-04-13 fixes resolve the prior C1 (candidate-set tautology) and prior M1 (typed-chain arity) cleanly. New defects identified are localized and tractable.

## Net novelty assessment

The paper has three solid contributions:
1. Sum-type impossibility theorem (publishable as a standalone result).
2. Orbit closure framework with typed-chain budget (publishable as a design discipline).
3. Cipher Boolean algebra with empirical FPR-compounding finding (publishable as an experimental observation if expanded).

Cipher TM is on weaker ground because of the obfuscation positioning gap and the new shift-cipher-map issue, but it is presented as a "second realization" rather than a headline contribution, which is appropriate.

The paper is a coherent piece of work with one clear thesis and well-organized supporting structure. The recommendation should turn primarily on the new defects in §6.1 and §6.3, plus the carry-forward experimental issues.
