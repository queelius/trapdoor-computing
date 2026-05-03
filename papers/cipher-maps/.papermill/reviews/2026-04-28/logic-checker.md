# Logic Checker Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Logic Checker
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations" (1536 lines, 22pp)
**Focus**: Proof correctness, logical chain integrity, claim support

## Summary

All proofs in the paper are structurally correct. The Round-3 inconsistencies in M4 (composition equality vs. inequality) and M5 (space optimality framing) are now resolved. One residual logic issue, a notational/algebraic gap in Theorem 6.2's Step 2, is minor but should be cleaned up. Two new findings on intermediate proof steps.

**Findings**: 0 critical, 1 major, 4 minor.

---

## Verification of Round-3 fixes

### M4 (composition formula consistency), VERIFIED FIXED

Checked all four restatements:
- **Theorem 4.1 (line 447 "Composition correctness")**: Now uses `\leq` with re-randomization equality qualifier (line 453, "with equality under independent errors"). FIXED.
- **Theorem 7.1 (line 1094 "Composition correctness")**: Already used `\leq` in Round 3; still consistent. FIXED.
- **Corollary 7.1 (line 1146 "Chain composition")**: Now uses `\leq` (line 1150) with re-randomization qualifier (line 1152). FIXED.
- **Discussion §9.1 (line 1333)**: Now reads "$\eta_{g \circ f} \leq 1 - (1-\eta_f)(1-\eta_g)$" with "(equality under re-randomization, Theorem~\ref{thm:composition})". FIXED.

The four restatements are now logically consistent. The equality condition (re-randomization) is explained at the same location each time.

### M5 (space optimality framing), VERIFIED FIXED

- **Theorem 6.2 (line 776)**: Renamed "Information-theoretic space complexity"; theorem statement now reads "information-theoretic space complexity" with "This is the information content of the $(1-\eta)n$ correctly encoded elements." FIXED.
- **Proof (lines 787-815)**: Step 1 now talks about "information content" and "the failing elements carry no information about the latent function and contribute zero to the information content." FIXED (no longer reads as a physical-storage claim).
- **Remark 6.3 (line 817)**: New "Information-theoretic vs. physical storage" remark explicitly addresses the gap: "The $(1-\eta)$ factor is an information-theoretic statement about useful content, not an automatic reduction in physical storage" and notes entropy-coded seed table caveat. FIXED.

The framing is now correct. The proof structure is sound.

### M6 (ROM dependence), VERIFIED FIXED (with minor count discrepancy)

- New paragraph at end of §3.1 (lines 245-262) enumerates ROM assumptions. Says "the four properties and every theorem ... depend on the random oracle model" then enumerates assumptions (a), (b), (c). The Round-3 review specified four assumptions (the fourth being for representation uniformity / hash-seed independence). The current text lists three. This is a wording/completeness inconsistency: either the body of the paragraph should enumerate four (adding hash-seed independence for $\delta$), or the lead sentence should be revised. Minor.
- HMAC-SHA256 named as practical instantiation. FIXED.
- Standard-model open question explicitly stated. FIXED.

---

## Major Findings

### L1. Theorem 6.2 proof Step 2: notational sleight of hand around $\alpha(y) \propto p_y$ (MAJOR, could be Minor with fix)

**Location**: Theorem 6.2 proof, Step 2 (lines 794-801)

**Quoted text**:
> "Shannon-optimal allocation sets $\alpha(y_i) \propto p_{y_i}$, giving per-element information cost $-\log_2 \alpha(y_i) \approx -\log_2 p_{y_i}$ and expected cost per element $\sum_y p_y (-\log_2 \alpha(y)) = \mu = H(Y)$."

**Problem**: The proof identifies $-\log_2 \alpha(y_i) \approx -\log_2 p_{y_i}$ via the proportionality $\alpha(y) \propto p_y$. But proportionality means $\alpha(y) = \varepsilon \cdot p_y$ (since $\sum_y \alpha(y) = \varepsilon$ by Definition 6.4), so the precise relationship is $-\log_2 \alpha(y) = -\log_2 \varepsilon - \log_2 p_y$, not $-\log_2 p_y$. The "$\approx$" is doing real work: it conceals the $-\log_2 \varepsilon$ term that then appears as a separate component in Step 3 ($-\log_2 \varepsilon$ "beyond the value encoding"). The total in Step 4 is correct ($-\log_2 \varepsilon + \mu$), but the decomposition into Steps 2 and 3 is presented as if "value encoding cost" and "noise rejection cost" are independent additive contributions, when in fact they emerge from the same quantity $\alpha(y_i)$.

A reader who computes $\sum_y p_y(-\log_2 \alpha(y))$ literally with $\alpha(y) = \varepsilon p_y$ gets $-\log_2 \varepsilon + H(Y)$, which is the *full* per-element cost. Step 3 then double-counts the $-\log_2 \varepsilon$ term, giving $-2\log_2 \varepsilon + H(Y)$, which is wrong.

The fix is to clean up the decomposition. Either:
- (a) Make the conditional probabilities explicit. Define $\tilde p(y) = \alpha(y) / \varepsilon$ (the conditional probability of decoding to $y$ given a valid decode). Show that Shannon-optimal allocation sets $\tilde p(y) = p_y$. Then per-element cost = $-\log_2 \alpha(y_i) = -\log_2 \varepsilon - \log_2 \tilde p_{y_i} = -\log_2 \varepsilon - \log_2 p_{y_i}$, and expected cost = $-\log_2 \varepsilon + H(Y)$.
- (b) Combine Steps 2 and 3 into one calculation, rather than presenting them as additive. Drop Step 3 as separate and just say "the per-element cost is $-\log_2 \alpha(y_i)$, and Shannon-optimal allocation $\alpha(y) = \varepsilon p_y$ gives expected cost $-\log_2 \varepsilon + H(Y)$."

**Suggestion**: Apply (b). The current decomposition is pedagogically nice (separating "noise rejection" from "value encoding") but it requires care to avoid the appearance of double-counting. The shortest fix is to rewrite Step 3 as: "The combined term $\sum_y \alpha(y) = \varepsilon$ controls the total noise-decode probability. The expected per-element cost decomposes as $\mathbb{E}[-\log_2 \alpha(y)] = -\log_2 \varepsilon + H(Y)$, where $-\log_2 \varepsilon$ is the constant cost shared by all valid encodings and $H(Y)$ is the entropy contribution from the value distribution."

**Cross-verified**: Yes, by independent recomputation. With $\alpha(y) = \varepsilon p_y$: $\mathbb{E}_{y \sim p}[-\log_2 \alpha(y)] = -\log_2 \varepsilon + H(Y)$, matching Step 4. So the theorem statement is correct; only the decomposition into Steps 2 and 3 reads as if they are independent contributions.

---

## Minor Findings

### L2. Theorem 6.1 (Lower bound) proof: Stirling step still informal (MINOR, m6 from Round 3 not addressed)

**Location**: Theorem 6.1 proof, lines 627-633

**Quoted text**:
> "For $|U| \gg n$, Stirling's approximation gives $\log_2 \binom{|U|}{n} \approx n \log_2(|U|/n)$ bits, or $\log_2(|U|/n)$ bits per element. Setting $\varepsilon = n/|U|$ (the fraction of the universe that decodes validly), this is $n \log_2(1/\varepsilon)$ bits."

**Problem**: This was minor m6 in the Round 3 review: the identification $\varepsilon = n/|U|$ is correct but should be justified. With acceptance probability $\varepsilon$, the expected number of universe elements that decode validly is $\varepsilon |U|$. For exact correctness ($\eta = 0$) all $n$ stored elements must decode, so $\varepsilon |U| \geq n$, i.e., $\varepsilon \geq n/|U|$. The bound is tight when there are no "wasted" valid-decoding non-elements, giving $\varepsilon = n/|U|$ as the optimal target.

**Status from Round 3**: Not addressed.

**Suggestion**: Insert one sentence after "this is $n \log_2(1/\varepsilon)$ bits": "Here we use $\varepsilon = n/|U|$, the smallest noise-decode probability achievable when all $n$ stored elements must decode and any additional valid hashes are wasted."

### L3. Theorem 7.1 (Composition) proof: union event vs. intersection wording (MINOR)

**Location**: Theorem 7.1 proof (line 1108-1130)

**Quoted text**:
> "The composition is incorrect when at least one map errs."

**Problem**: This is true under one of two assumptions:
1. If both maps err but the errors cancel (e.g., $\fhat$ outputs the wrong $y'$ and $\ghat$ happens to output $g(y') = g(f(x))$ correctly), the composition could still be correct.
2. If we assume errors do not cancel (the worst case), the statement is correct.

The proof says "Loose bound. Dropping $\Pr[A \cap B] \geq 0$ gives the union bound", which is fine for an upper bound. But the equality case ("under re-randomization") implicitly assumes that error events do not cancel. The Remark on garbage propagation (line 1132) acknowledges this informally.

**Suggestion**: Add half a sentence to the proof: "Note that the bound counts errors pessimistically: in some cases, $\fhat$ producing the 'wrong' value may yet decode to the correct final output if $\ghat$ collapses the error. The bound is tight when errors do not cancel."

This is a small clarification that pre-empts a careful reviewer's question about whether $\Pr[A \cup B]$ correctly captures "composition is incorrect."

### L4. Proposition 6.5 (Bucketed construction time) hides an expectation/sup issue (MINOR, m8 from Round 3)

**Location**: Proposition 6.5, lines 889-906

**Quoted text** (Proposition statement):
> "With $k$ buckets of expected size $m/k$ and $\eta = 0$, the expected total construction time is $T(k) = k \cdot (1/\bar{\alpha})^{m/k}$"

**Problem**: This was m8 in Round 3 (not addressed). Construction time for the algorithm is dominated by the largest bucket, not the average. With $m$ elements assigned to $k$ buckets uniformly at random, the maximum bucket size is $\Theta(m/k + \log k / \log(em/k))$ w.h.p. for $k \leq m$. The proof's "Each bucket has $m/k$ elements (in expectation)" then "Summing over $k$ independent buckets" uses linearity of expectation, which is fine for the *sum* of times but not for the parallel/sequential interpretation.

The text seems to intend a *sequential* construction, in which case linearity gives the expected total. So the proposition is correct as stated, but the "expected total" framing should make this explicit.

**Suggestion**: Add to the proof: "We compute the expected sequential time over all $k$ buckets. The maximum-bucket time, relevant for parallel construction, is dominated by the largest bucket size $\Theta(m/k + \log k)$ w.h.p."

### L5. Proposition 6.3 (Per-seed success probability): Poisson binomial citation missing (MINOR)

**Location**: Proposition 6.3, lines 838-862

**Problem**: The proof states "The failure count $F = \sum_i \mathbf{1}[\text{hash}_i \notin A(y_i)]$ is a sum of independent Bernoulli variables. The seed is accepted when $F \leq \lfloor \eta m \rfloor$, giving the Poisson binomial CDF." No citation for the Poisson binomial. This is standard, but a citation (e.g., Wang 1993 "On the number of successes in independent trials") or one sentence noting that the special case of uniform $\alpha$ reduces to a Binomial would help.

**Suggestion**: Add a footnote or one-sentence explanation: "When $\alpha$ varies across elements, the failure count is a Poisson binomial (also called a 'Bernoulli sum') variable; when $\alpha$ is uniform, it reduces to Binomial$(m, 1-\alpha)$."

---

## Items Verified Sound (no action needed)

- **Definition 4.1 (Totality)**: Statement is precise. Random oracle assumption explicit.
- **Definition 4.2 (Representation Uniformity)**: TV distance statement is clean. Conditional cipher value distribution $Q(c)$ correctly defined.
- **Definition 4.3 (Correctness)**: $\eta$-bound is over uniform $x, k$. Clear.
- **Theorem 4.1 (Composition correctness)**: Now consistent with Theorem 7.1.
- **Proposition 6.4 (Bayesian deniability, proposition 8.1 in current text)**: Bayes computation is correct; matches standard noisy-channel formula.
- **Proposition 8.1 (Granularity and privacy)**: First part follows from Definition 4.2. Second part argument is correct: $\enc_i$ injective for fixed $k_i$ implies the joint distribution preserves dependence.

## Open Questions for Cross-verification

The L1 finding (Theorem 6.2 Step 2 notational issue) overlaps with methodology-auditor's concerns about the proof's interpretation. A cross-verification by methodology would confirm whether the issue is purely notational or whether it indicates a deeper conflation.
