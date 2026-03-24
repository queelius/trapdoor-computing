# Verification Report: Three Critical Fixes

**Paper:** `paper/paper.tex` (Cryptographic Perfect Hash Functions)
**Date:** 2026-03-20
**Reviewer:** Claude Opus 4.6

---

## Fix 1: Theorem 3.3 Proof -- Jensen's Inequality

**Location:** Lines 512--545
**Status:** PASS

### What was fixed

The original proof computed `E[log_2 Q]` and treated it as `log_2(E[Q])`, which is a Jensen's inequality violation (log is concave, so `E[log_2 Q] <= log_2(E[Q])` with equality only for degenerate distributions). The fix replaces this with `log_2(E[Q])/m` and justifies it as the bit length of the expected trial index.

### Verification

**Algebra check (line 517 to 544):**

Let `N = m/r`. We have `E[Q] = N^m (N-m)! / N!`.

1. `log_2(E[Q])/m = log_2(N) + (1/m)[log_2((N-m)!) - log_2(N!)]` -- matches lines 517--520.
2. Applying Stirling (`log_2(n!) ~ n(log_2 n - log_2 e)`):
   - `log_2(N!) ~ (m/r)(log_2(m/r) - log_2 e)`
   - `log_2((N-m)!) ~ (m/r - m)(log_2(m/r - m) - log_2 e)`
   - Substitution yields lines 529--533. Verified correct.
3. Collecting terms:
   - `(1/r - 1)[log_2(m/r - m) - log_2(m/r)] + log_2 e`
   - `= (1/r - 1) log_2((m/r - m)/(m/r)) + log_2 e`
   - `= (1/r - 1) log_2(1 - r) + log_2 e`
   - `= log_2 e - (1/r - 1) log_2(1/(1-r))`
   - Matches lines 537--544. Verified correct.

**Final result:** The space formula (Equation `eq:code_size`, line 498) is unchanged: `log_2 e - (1/r - 1) log_2(1/(1-r))` bits/element.

**Justification subtlety:** The quantity `log_2(E[Q])/m` is the bit length to encode the *expected* trial number, not the expected bit length `E[log_2 Q]/m`. However, the paragraph at lines 548--556 shows that the entropy `H(Q)` of the geometric distribution equals this formula per element, confirming the result is correct. The entropy argument provides the rigorous bridge: the expected bit length of the optimal encoding equals the entropy, which equals `log_2(E[Q])/m` for this particular geometric distribution. No new errors introduced.

---

## Fix 2: Theorem 3.5 -- Maximum Entropy Encoding

**Location:** Lines 558--581
**Status:** PASS

### What was fixed

The original theorem claimed maximum entropy encoding without qualification. This is false for deterministic search order: within each bit-length level, a geometric (first-success) distribution biases toward smaller indices, so the conditional distribution given the level is not uniform.

### Verification

**Theorem statement (lines 563--572):** Now correctly requires "the search order within each bit-length level is randomized (i.e., for each length l, the 2^l candidate bit strings are tested in a uniformly random permutation)." Also includes the weaker deterministic claim: "With the deterministic search order of Algorithm 1, the encoding achieves entropy within O(1) bits of this maximum."

**Proof (lines 573--577):** Correctly notes that randomized intra-level search makes the selected bit string uniformly distributed among candidates of that length, which is the condition needed for the encoding to be entropy-optimal.

**Remark (lines 579--581):** Explains the subtlety clearly: with deterministic search, the within-level deficit is at most `log_2(1/p)` bits total (independent of `m`), hence `O(1)`. This is correct because the within-level position is a geometric random variable whose entropy is bounded by `log_2(1/p)`, which depends only on `p = p(m,r)` and is `O(1)` for fixed `r`.

**Consistency check:** The theorem is now true as stated. The deterministic fallback claim (`O(1)` bits) is also correct. The remark references `bernoulli-hash-function` construction as handling randomization correctly, which is consistent with the broader project. No new errors introduced.

---

## Fix 3: Two-Level Variance Formula

**Location:** Lines 782--788
**Status:** PASS

### What was fixed

The original formula had an extra factor of `m`, giving `Var(T_j) = m^2(j-1)/(m-j+1)^2` and overall variance `O(m^3)`. The fix removes the extra factor.

### Verification

**Derivation check:** Given `p_j = (m-j+1)/m`:
- `1 - p_j = (j-1)/m`
- `p_j^2 = (m-j+1)^2 / m^2`
- `Var(T_j) = (1-p_j)/p_j^2 = [(j-1)/m] / [(m-j+1)^2/m^2] = m(j-1)/(m-j+1)^2`

This matches line 786: `sum_{j=2}^{m} (j-1) * m / (m-j+1)^2`. Verified correct.

**Asymptotic check (O(m^2)):** Substituting `k = m-j+1` (so `j-1 = m-k`, `k` from `1` to `m-1`):

`Var(T) = m * sum_{k=1}^{m-1} (m-k)/k^2 = m^2 sum 1/k^2 - m sum 1/k`

Since `sum 1/k^2 -> pi^2/6` and `sum 1/k ~ ln m`, we get `Var(T) ~ pi^2 m^2/6 - m ln m = O(m^2)`.

This is the known variance for the coupon collector's problem, confirming correctness. The claim at line 788 ("This variance is O(m^2)") is correct.

**Dimensional consistency:** The variance of the total number of trials `T` is `O(m^2)`. The standard deviation is `O(m)`, which is comparable to the mean `E[T] = m H_m ~ m ln m`. This is physically reasonable: the coefficient of variation is `O(1/ln m)`, meaning relative fluctuations decrease slowly. With the original `O(m^3)`, the standard deviation would be `O(m^{3/2})`, which would dominate the mean for large `m` -- unreasonable for a sum of independent geometric random variables.

---

## Overall Verdict: PASS

All three fixes are mathematically correct, consistent with surrounding text, and introduce no new errors. The final formulas (space complexity, entropy, variance) are all correct as stated.
