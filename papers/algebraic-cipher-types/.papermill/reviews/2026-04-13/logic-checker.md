# Logic Checker (2026-04-13)

## Scope

This review focuses on the second-round fixes (entropy-form confidentiality bound, typed-chain recurrence, cipher TM cleanup, regex example) and on whether any new defects were introduced.

## Summary

| Result | Status | Note |
|---|---|---|
| Prop 4.1 (product trade-off) | sound | unchanged from 2026-04-12 |
| Thm 4.2 (sum-type impossibility) | sound | unchanged from 2026-04-12 |
| Thm 5.1 (monotonicity) | sound | unchanged from 2026-04-12 |
| Cor 5.2 (empty operations) | sound | unchanged from 2026-04-12 |
| **Thm 5.3 (confidentiality bound, entropy form)** | **mostly sound, notational defect** | new in 2026-04-13 |
| **Cor 5.4 (set form)** | **informally argued, defensible** | new in 2026-04-13 |
| **Prop 5.5 (typed chain orbit bound)** | **sound** | recurrence and example consistent |
| Prop 6.1 (cipher TM space) | sound for delta_T alone, **incomplete for shift cipher map** | new defect |
| Prop 6.2 (head-movement leakage) | sound | unchanged |
| Prop 7.1 (noise unreliability) | sound | unchanged from 2026-04-12 |

## Verification of second-round fixes

### Fix #1. Entropy-form confidentiality bound (replaces tautological candidate-set definition; prior C1)

**Status: largely sound, with a notational confusion that does not invalidate the result.**

The new theorem (Thm 5.3, lines 674-682):
```
H(X | V_F(c)) >= H(X) - log_2 |orbit_F(c)|
```

The proof argues:
1. V_F(c) takes at most |orbit_F(c)| distinct values.
2. So I(X; V_F(c)) <= H(V_F(c)) <= log_2 |orbit_F(c)|.
3. Hence H(X | V_F(c)) = H(X) - I(X; V_F(c)) >= H(X) - log_2 |orbit_F(c)|.

**Defect**: The view is *defined* (line 669-670) as `V_F(c) = orbit_F(c)`, i.e., the orbit *set* itself. But the proof treats the view as a scalar random variable taking values *in* the orbit. These two readings give different things: the cardinality of the orbit set is `|orbit_F(c)|`, but the support size of "a single bit-string drawn from the orbit" is at most `|orbit_F(c)|`. The bound `H(V_F) <= log_2 |orbit_F(c)|` only makes sense under the second reading.

The right way to state this: let `Y` be a bit-string the adversary can derive from `c` via cipher-map composition; `Y in orbit_F(c)` always; so `H(Y) <= log_2 |orbit_F(c)|`. The bound `H(X | Y) >= H(X) - log_2 |orbit_F(c)|` follows.

**Suggestion**: Drop the `V_F(c) = orbit_F(c)` set-equality and instead say: "Let `Y` be any bit-string the adversary can derive from `c` by composing maps in `F`. Then `Y in orbit_F(c)`, so `H(Y) <= log_2 |orbit_F(c)|`." The mutual information argument then goes through cleanly.

**This is not a tautology** (the prior C1 was that the candidate-set definition was a tautology). The fix's underlying mathematical content is sound. The defect is purely notational and easily fixable in one paragraph.

**The C1 status: cleanly resolved at the structural level (no tautology); minor notational tightening still desirable.**

### Fix #2. Typed-chain recurrence with arity (Prop 5.5; prior M1)

**Status: sound. Proposition, proof, and example are consistent.**

Definition 5.4 (typed composition chain): `f_i : C(A)_i^{a_i} -> C(A)_{i+1}` with `a_i >= 1` and distinct cipher spaces. Clean.

Proposition 5.5 (orbit bound): `|orbit_F(V_0)| <= sum_i N_i` with `N_0 = m` and `N_{i+1} = N_i^{a_i}`.

**Walking through the proof** (lines 884-895):
- Partition orbit by level: `L_0 = V_0`, `L_{i+1} = image(f_i, L_i^{a_i})`.
- Distinct cipher spaces prevent backreferences, so each orbit element is in exactly one `L_i`.
- `|L_{i+1}| <= |L_i|^{a_i} = N_i^{a_i} = N_{i+1}` by induction.
- `|orbit_F(V_0)| = sum_i |L_i| <= sum_i N_i`.

**The argument is correct**. The bound `|L_{i+1}| <= |L_i|^{a_i}` follows because `L_{i+1}` is the image of `f_i` over at most `|L_i|^{a_i}` distinct `a_i`-tuples, so produces at most `|L_i|^{a_i}` distinct outputs.

**Special cases:**
- `m=1` (single value start): `N_0=1, N_1=1^{a_0}=1, ..., N_k=1`. Sum is `k+1`, written `1+k`. Match.
- `a_i=1` (unary chain): `N_{i+1}=N_i^1=N_i=m` at every level. Sum is `m(k+1)`. Match.

**Verifying Example 5.4** (binary AND, depth 2, m=1 start):
- `L_0 = {c}`, `|L_0|=1`.
- `L_1 = AND_0(c, c)`, single value, `|L_1|=1`.
- `L_2 = AND_1(L_1, L_1)`, single value, `|L_2|=1`.
- Total: 3 = 1+k = 1+2.
- Match.

**Verifying multi-start case (m=2, depth 2, binary AND)**:
- `N_0 = 2, N_1 = 2^2 = 4, N_2 = 4^2 = 16`. Sum = 2+4+16 = 22.
- The example states `m + m^2 + m^4`, which for m=2 gives 2+4+16=22.
- Match (the formula `m + m^2 + m^4` is `N_0 + N_0^2 + N_0^4 = N_0 + N_1 + N_2` under the recurrence).

**M1 status: fully resolved.** The recurrence is correct, the proof is rigorous, and the example matches.

### Fix #3. Cipher TM cleanup (LC-MIN-1, LC-MIN-2)

**Status: partial. Pair-cipher-map issue resolved by joint encoding; head direction now explicitly cleartext. New issue: shift cipher map's space cost not accounted for.**

The new Definition 6.1 (lines 960-987):
- Each tape cell is a single cipher value in `C(Q x Gamma)`. (Good: no separate pair-cipher-map.)
- Head position marked by a distinguished state `varnothing`. (Good.)
- Output of `delta_T` is `(c', d)` where `c' in C(Q x Gamma)` and `d in {L, R, S}` is in the clear. (Good.)
- The untrusted machine "writes c' back to the current cell, shifts the head marker according to d (by swapping the state component of the neighbouring cell with the current cell via a second cipher map for the shift operation)".

**New defect**: The "second cipher map for the shift operation" is invoked but not analyzed. This shift cipher map operates on two adjacent cipher cells (current + neighbour), each in `C(Q x Gamma)`, so its natural domain is `C(Q x Gamma) x C(Q x Gamma)` and its codomain is the same. Space: `O((|Q| x |Gamma|)^2)`.

This contradicts Proposition 6.1's claim that the cipher TM has space `O(|Q| x |Gamma|)`. The proposition refers only to `delta_T`; the shift cipher map adds a quadratic term that the paper does not mention.

**Alternatively**, the shift could be a unary cipher map on one cell: "extract state" `C(Q x Gamma) -> C(Q)` followed by "place state in neighbour" `C(Q x Gamma) x C(Q) -> C(Q x Gamma)`. Both are smaller (`O(|Q| x |Gamma|)`). But Definition 6.1 says "swap the state component", which is a binary operation on two cells.

**Suggestion**: Either (a) explicitly factor the shift into two unary cipher maps and analyze their space (`O(|Q| x |Gamma|)`), or (b) acknowledge the shift cipher map as a separate sub-construction with its own space cost. The current text glosses the issue.

**Cipher-TM cleanup status: partial. Joint encoding and explicit cleartext direction are improvements; shift cipher map analysis is incomplete.**

### Fix #4. Regex example in Section 6.3 (prior M8)

**Status: contains errors. Both the cipher-TM analysis and the expression-tree analysis are off.**

Example 6.1 (lines 1167-1183):

Claim 1: "As a cipher TM, Q is the set of DFA states for R (size O(r))."

**Defect**: The DFA for a regular expression of size `r` has up to `O(2^r)` states (subset construction over the NFA). NFA states are `O(r)`; DFA states are exponential in worst case. The example does not qualify this.

Specific cases where DFA size is polynomial in `r`: regexes without alternation or with bounded ambiguity. For general regexes, DFA blowup is exponential.

**Suggestion**: Either (a) say "minimal DFA states for R (in the worst case `2^r`, but `O(r)` for regexes without exponential blowup)", or (b) use the NFA and accept the resulting non-deterministic transitions as part of the leakage profile, or (c) use a specific regex class where the DFA is bounded.

Claim 2: "delta_T is a single cipher map of space O(r * |Sigma|), evaluated ell times per match."

**Defect**: If `Q` has `O(r)` states (the questionable claim above), then `delta_T : C(Q x Sigma) -> C(Q x Sigma) x {L, R, S}` has domain `|Q| x |Sigma| = O(r * |Sigma|)`. So the cipher map's space is `O(r * |Sigma|)`. *Conditional on Claim 1, this is fine.* But the conditional is fragile.

Claim 3: "As an expression tree, the program is a fold over the string with ell cut points at the transition function; the combiner cipher map above them has domain C(Q)^ell so its construction cost is exponential in ell."

**Defect**: This is wrong as a construction-cost claim. The natural typed-chain decomposition of a fold over a length-`ell` string with state in `C(Q)` is:
- `delta_0 : C(Q) x C(Sigma) -> C(Q)_1`
- `delta_1 : C(Q)_1 x C(Sigma) -> C(Q)_2`
- ...
- `delta_{ell-1} : C(Q)_{ell-1} x C(Sigma) -> C(Q)_ell`

Each of these has space `O(|Q| x |Sigma|)`. Total: `O(ell * |Q| * |Sigma|)`, **linear** in `ell`, not exponential.

The example forces an exponential cost by considering a "single combiner cipher map above all `ell` cut points with domain `C(Q)^ell`". But this is a strawman decomposition: it inflates `ell` separate functions into one giant function over `ell`-tuples. The natural typed-chain decomposition does not do this.

**The example is constructed to make the cipher TM look better than the expression tree by choosing an artificially bad expression-tree decomposition.** Both realizations should have the same `O(ell * |Q| * |Sigma|)` total space for regex matching. The actual difference is in *what leaks*: cipher TM leaks `ell` (head movement); expression tree with typed chain also leaks `ell` (the chain has `ell` cut points). Neither has an exponential cost for this problem.

**Suggestion**: Replace the example with a problem where the two realizations genuinely differ. Or correct the expression-tree analysis: say `O(ell * |Q| * |Sigma|)` total, with `ell` cut points and `ell` distinct cipher state spaces, and observe that BOTH realizations leak `ell`. The cut-point placement choice is real but the magnitude of the cost difference in this example is fabricated.

**Regex example status: incorrect. Both halves contain errors. This was added as the new worked example for M8 and is a fresh defect.**

## Other findings

### LC-NEW-1. Section 6.3 typed-chain bound applied to cipher TM (lines 1151-1165)

The text says: "For a cipher TM running for T steps with self-loop at a single (binary-arity, if state and symbol are distinct inputs) cut point, a naive reading gives N_i = 1 for a single initial tape configuration so the orbit is bounded by 1 + T."

**Defect**: The cipher TM is a self-loop, NOT a typed chain. Definition 5.4 of typed composition chains explicitly requires *distinct* cipher spaces at each level; the cipher TM has a *single* cipher space `C(Q x Gamma)` reused at every step. Proposition 5.5 does not directly apply.

The bound `1 + T` (or `m * (T+1)` for `m` distinct starts) for the cipher TM does hold, but for a different reason: deterministic computation produces a single trajectory of length `T`, so at most `T+1` distinct cipher values are reachable on that trajectory. This is a deterministic-trajectory argument, not a typed-chain argument.

The paragraph mixes the two arguments: "Typing the cipher spaces between cut points is what prevents the self-loop in either realization from degenerating into an unbounded orbit." For the expression tree this is correct; for the cipher TM it is not , the cipher TM is *not* typed in the chain sense. Its bound comes from determinism alone.

**Suggestion**: Distinguish the two arguments. The cipher TM's `1 + T` bound is from deterministic trajectory; the expression tree's `sum N_i` bound is from typed-chain orbit closure. Both are finite, but they are not the same theorem. Section 6.3 conflates them.

### LC-NEW-2. Conflation of "view = orbit set" with "view = element of orbit" (Thm 5.3)

(Already discussed under Fix #1.) The notational confusion between V_F as a set vs. V_F as a scalar in that set is a minor formal defect. The result is sound under the charitable reading. Worth tightening in revision.

### LC-MIN-3 (carry-forward from 2026-04-12, not addressed)

`delta` (TV distance) and `delta_T` (TM transition) still collide notationally. Suggest renaming TM transition.

### LC-MIN-4 (carry-forward from 2026-04-12)

Cipher value/cipher map conflation acknowledged in remark. OK as-is.

### LC-MIN-5 (carry-forward from 2026-04-12)

Line 1377 "All three produce zero errors on the full domain" is definitional from PHF construction, not empirical. Suggest qualifying.

### LC-MIN-6 (carry-forward from 2026-04-12)

Example 5.1 "up to correctness eta" is loose. Acceptable but could be tightened.

## Cross-verification of claimed fixes from the orchestrator

| Item | Claim | Verified? |
|---|---|---|
| C1 entropy-form rewrite | Tautology dropped, conditional entropy as primary, set-form as corollary | YES (with minor notational defect, see Fix #1) |
| M1 typed-chain | `N_{i+1} = N_i^{a_i}`, sum bound, special cases | YES, fully verified (see Fix #2) |
| M11 denominator switch | Resolved by entropy-form rewrite | YES, the corollary cleanly uses `|X|` |
| LC-MIN-1 head direction | Cleartext direction on output | YES |
| LC-MIN-2 pairing cipher map | Eliminated by joint encoding `C(Q x Gamma)` per cell | PARTIAL , shift cipher map is a new sub-construction (see Fix #3) |
| M8 regex example | New formal example added | NO, the example has errors (see Fix #4) |

## Verdict

Of the six second-round fixes verified by the orchestrator's instructions, four are sound (C1 modulo notation, M1, M11, LC-MIN-1), one is partial (LC-MIN-2 introduces a new shift cipher map issue), and one is incorrect (the regex example fabricates an exponential cost for the expression-tree decomposition).

The C1 fix removes the prior tautology cleanly. The M1 recurrence is mathematically sound and the example matches. These are the two most important verifications and both pass.

The new defects in §6.1 (shift cipher map space) and §6.3 (regex example, typed-chain misapplication) are fresh issues introduced by the second-round work. They are tractable in revision but visible to a careful reviewer.
