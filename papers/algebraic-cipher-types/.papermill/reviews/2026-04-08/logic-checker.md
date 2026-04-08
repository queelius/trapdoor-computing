# Logic Checker Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Checker**: logic-checker

## Summary

The paper contains 7 formal results (2 theorems, 3 propositions, 1 corollary, plus definitions). Two have critical logical issues; two have major gaps; the rest are sound.

---

## Theorem 3.2: Sum-Type Impossibility

**Verdict**: Major gap in the "no intermediate" direction.

**The two directions are sound**: Joint encoding achieves tag hiding (by representation uniformity) but blocks pattern matching (any distinguisher tau contradicts tag hiding). Component-wise encoding permits pattern matching (tag in the clear) but leaks the tag. These are correct.

**The "no intermediate" argument has a gap**: The advantage calculation computes `(1 - gamma) - 1/2 = 1/2 - gamma`. The subtraction of 1/2 assumes a balanced prior: that A-values and B-values are equally likely. For an arbitrary distribution with Pr[v in A] = p, a trivial distinguisher that always guesses the majority type achieves advantage |p - 1/2| without any encoding information. The correct baseline is max(p, 1-p), not 1/2.

**Fix**: Either (a) state the theorem for balanced distributions (p = 1/2) and note the generalization requires adjusting the baseline, or (b) reformulate the advantage as the distinguishing advantage over the optimal uninformed strategy: advantage = Pr[tau correct] - max(p, 1-p), which must be at most delta'.

**Severity**: Major. The core impossibility is correct, but the quantitative bound in the "no intermediate" case is only tight for balanced distributions.
**Confidence**: High.

---

## Proposition 3.1: Product Confidentiality Trade-off

**Verdict**: Sound with minor imprecision.

Part (1) is correct by representation uniformity.

Part (2): The convergence argument is correct in principle -- the empirical joint distribution of cipher-value pairs converges to a mixture of the latent joint. The sample complexity claim N = O(|A| * |B| / xi^2) is a standard TV-distance convergence rate and is correct.

**Minor issue**: The argument says "each cipher value maps to at most one latent value (given a fixed representation index)." This is the injectivity of enc(., k) for fixed k, which is assumed implicitly but should be stated explicitly (it is part of the cipher map construction, not a definition-level property).

**Severity**: Minor.
**Confidence**: High.

---

## Theorem 4.1: Monotonicity of Orbit Closure

**Verdict**: Sound.

The induction is correct and complete. Base case: c in both orbits by definition. Inductive step: if c' in orbit_F(c), then for any f_i in F subset G, f_i(c') is in orbit_G(c). The conclusion follows.

This is a straightforward consequence of the subset relationship between operation sets and is not a deep result.

**Severity**: N/A (no issues).
**Confidence**: High.

---

## Corollary 4.2: Empty Operations

**Verdict**: Sound. Trivial consequence of Definition 4.1.

---

## Theorem 4.3: Confidentiality Bound

**Verdict**: Critical logical issues.

**Issue 1: Multiple inconsistent formulas.** The theorem presents four formulas:
1. Fraction excluded <= |orbit_F(c)| / 2^n
2. |Cand_F(c)| <= |X| * (1 - (|orbit_F(c)| - |X|) / (2^n - |X|))
3. |Cand_F(c)| / |X| <= |orbit_F(c)| / |X|
4. conf_F(c) >= 1 - |orbit_F(c)| / 2^n

Formula (3) simplifies to |Cand_F(c)| <= |orbit_F(c)|, which is a different kind of bound than formula (1) or (4). Formula (3) can exceed 1 when orbit_F(c) > |X|, making it vacuous as a "fraction" bound. The proof does not clearly derive formulas (2) or (3); it primarily argues for (4).

**Issue 2: Candidate set definition disconnect.** Definition 4.2 defines Cand_F(c) = { x in X | exists k s.t. enc(x, k) = c }. This is the set of latent values consistent with c alone -- it does not use F or the orbit at all, despite the F subscript. The subsequent text says "if the untrusted machine can additionally check..." but this checking is not formalized. The theorem then bounds |Cand_F(c)| using the orbit, but Cand_F(c) as defined does not depend on F.

**Issue 3: The "worst case" argument is imprecise.** The proof says "in the worst case, every element of orbit_F(c) is a valid encoding and each encodes a distinct latent value." But the orbit includes c itself, which already encodes a specific value. The adversary learns the orbit structure (which values map to which under each operation), not just the orbit size. The bound treats orbit elements as independent random samples, which they are not -- they are connected by deterministic cipher maps.

**Fix**: (a) Redefine Cand_F(c) to use the orbit, e.g., Cand_F(c) = { x in X | there exists an assignment of latent values to orbit elements, consistent with all operations in F, that assigns x to c }. (b) State a single clean bound as the theorem statement; move derivations to the proof. (c) Acknowledge that the bound is loose for structured orbits.

**Severity**: Critical. The theorem as stated contains formulas that are not all derived from the proof, and the candidate set definition does not match its usage.
**Confidence**: High.

---

## Proposition 5.1: Cipher TM Space Complexity

**Verdict**: Sound with a caveat.

The claim that hat(delta_T) has space O(|Q| * |Gamma|) is correct: the cipher map for the transition function has domain Q x Gamma.

**Caveat**: The proposition says "independent of the input domain size |X|." This is correct for the transition cipher map, but the tape itself requires space proportional to the number of cells used. The proposition acknowledges this in the proof ("the tape itself requires space proportional to the number of tape cells used") but the proposition statement does not mention it. A reader might infer that the total space of the cipher TM is O(|Q| * |Gamma|), which would be incorrect.

**Severity**: Minor (the proof is honest about the caveat, but the statement could be clearer).
**Confidence**: High.

---

## Proposition 5.2: Head Movement Determinism

**Verdict**: Sound for eta = 0.

For eta = 0, the cipher transition function is exact, so the head movement sequence is identical to the plaintext TM. Two inputs producing different head sequences are distinguishable. This is correct.

The eta > 0 case is discussed in Remark 5.5 and correctly notes that errors introduce noise into the head movement, providing weak obfuscation. The remark also correctly notes this is unreliable (systematic errors, not random).

**Severity**: N/A (no issues).
**Confidence**: High.

---

## Proposition 6.1: Noise as Absorbing Element

**Verdict**: Critical -- proposition statement contradicts its proof.

The proposition states categorically:
- AND(x, n) in N for any x in T union F and n in N
- OR(x, n) in N for any x in T union F and n in N
- NOT(n) in N for n in N

The proof says: "a noise input produces noise output with probability >= 0.05 and a False output with probability <= 0.90."

This means AND(x, n) is in N only about 5% of the time; it lands in F about 90% of the time. The proposition claims a deterministic property ("for any"); the proof demonstrates a probabilistic one. The proposition as stated is false.

**Fix**: Either (a) reformulate as a probabilistic statement: "AND(x, n) is not in T union F with high probability" (but even this is wrong -- 90% of the time it IS in F), or (b) redefine what "noise absorption" means: operations on noise inputs produce outputs that are uncorrelated with the intended result, even if the output appears to be in T or F. The point is that the output is unreliable, not that it is necessarily in N.

**Severity**: Critical. The formal statement is false per the paper's own proof.
**Confidence**: High.

---

## Definition Consistency Check

| Notation | Defined | First used | Issue |
|----------|---------|------------|-------|
| C(X) | Line 198 (informal) | Throughout | Should be a formal definition |
| K(x) | Never defined | Line 215 | Missing definition |
| delta_T | Sec 2 (TV distance) | Sec 5 (TM transition) | Overloaded |
| enc, dec | Def 2.1 | Throughout | OK |
| orbit_F | Def 4.1 | Throughout | OK |
| Cand_F | Def 4.2 | Thm 4.3 | F subscript unused in definition |
| conf_F | Thm 4.3 | Once | Never formally defined, appears only in theorem |
