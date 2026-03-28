# Logic Checker Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper contains 4 theorems, 5 propositions, 1 corollary, and 7 definitions. All proofs are present and structurally complete. The logical chain from definitions through properties to constructions and composition is coherent. Two issues remain from incomplete prior-round fixes, and one new issue was identified.

## Findings

### MAJOR: Composition equality/inequality inconsistency between Theorem 4.1 and Theorem 7.1

- **Location**: Theorem 4.1 (line 391) vs. Theorem 7.1 (line 1002)
- **Quoted text (Thm 4.1)**: "$\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g) = \eta_f + \eta_g - \eta_f \eta_g$"
- **Quoted text (Thm 7.1)**: "$\eta_{g \circ f} \leq \eta_f + \eta_g - \eta_f \eta_g = 1 - (1 - \eta_f)(1 - \eta_g)$"
- **Problem**: These are the same theorem (Thm 4.1 cross-references Thm 7.1 for its proof). But Thm 4.1 states the result as an equality while Thm 7.1 states it as an inequality. Additionally, Corollary 7.1 (line 1052) uses equality "$\eta_{\mathrm{total}} = 1 - \prod_{i=1}^{m}(1 - \eta_i)$" and Discussion Section 9.1 (line 1189) uses equality. The abstract (line 59) uses the correct inequality form. This was flagged as M1 in the prior review and claimed resolved, but the fix was only applied to Theorem 7.1; the forward reference (Theorem 4.1) and the corollary were not updated.
- **Severity**: MAJOR
- **Confidence**: HIGH
- **Suggestion**: Change Theorem 4.1 to use $\leq$. Change Corollary 7.1 to use $\leq$, with equality under re-randomization. Update Discussion line 1189 to use $\leq$.

### MAJOR: Space optimality theorem (Thm 6.2) conflates information-theoretic requirement with physical storage

- **Location**: Theorem 6.2 (lines 704-739)
- **Quoted text**: "The batch construction achieves space complexity $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits per element"
- **Problem**: The $(1-\eta)$ factor in the space formula is logically unsound as an achievability claim about physical storage. The data structure (seed table + acceptance predicate) does not shrink when $\eta > 0$. All $n$ elements are still hashed; the seed table has the same number of entries. What $\eta > 0$ buys is relaxed constraints on the seed search, reducing construction time. The failing elements still occupy their hash positions -- they just map to incorrect outputs. The proof's Step 4 says "$(1-\eta)n$ elements are stored," but this is wrong: all $n$ elements are stored. The seed simply fails to correctly map $\eta n$ of them.

  The claim would be correct if interpreted as: "the information content of the structure is $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits per element, because $\eta n$ elements carry no useful information." But this is an information-theoretic statement about the useful capacity, not a claim about achievable space.
- **Severity**: MAJOR
- **Confidence**: MEDIUM (the interpretation issue may be resolvable with better framing)
- **Suggestion**: Either (a) restate the theorem as an information-theoretic bound on the useful capacity rather than achievable space, or (b) explain that when $\eta > 0$, the structure can store the $(1-\eta)n$ correct elements in $(1-\eta)n(-\log_2 \varepsilon + \mu)$ bits, with the $\eta n$ failing elements simply not represented (i.e., the structure only commits to encoding the passing elements). This latter interpretation requires clarifying that failing elements are not stored at all -- they simply fall through to noise.

### MINOR: Lower bound proof $\varepsilon = n/|U|$ identification is informal

- **Location**: Theorem 6.1 proof (line 569)
- **Quoted text**: "Setting $\varepsilon = n/|U|$ (the fraction of the universe that decodes validly)"
- **Problem**: The noise-decode probability $\varepsilon$ (Definition 6.1) is the probability that a random hash value falls in any acceptance set: $\varepsilon = \sum_y \alpha(y)$. The proof identifies this with $n/|U|$, the base rate of stored elements in the universe. These are related but not identical: $\varepsilon$ is a property of the acceptance predicate, while $n/|U|$ is a property of the dataset. The step works because for optimal space, the acceptance probability per element is set so that $\varepsilon$ controls the false positive rate, which in the counting argument corresponds to $n/|U|$. But the identification needs one sentence of justification.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Add: "In any space-optimal encoding, the effective universe size seen by the structure is $1/\varepsilon$ per stored element, since $\varepsilon$ is the probability that a random input decodes validly."

### MINOR: Corollary 7.1 chain composition uses equality but derives from inequality theorem

- **Location**: Corollary 7.1 (line 1052), proof (line 1062)
- **Quoted text**: "$\eta_{\mathrm{total}} = 1 - \prod_{i=1}^{m}(1 - \eta_i)$"
- **Problem**: The corollary is stated as equality, but its proof says "By induction on Theorem 7.1," which states an inequality. The inductive step should propagate the inequality.
- **Severity**: MINOR (subsumed by the major issue above, but noted for completeness)
- **Confidence**: HIGH

### MINOR: AND gate (0,0) case correctness should be stated as $1-(1-p_1)(1-p_2)$, not $p_1+p_2-p_1 p_2$

- **Location**: Proposition 7.1, line 972
- **Quoted text**: "$p_1 + p_2 - p_1 p_2$"
- **Problem**: While algebraically identical, the form $1-(1-p_1)(1-p_2)$ is more recognizable as the inclusion-exclusion / composition formula and would make the connection to Theorem 7.1 more transparent. The current form obscures the pattern.
- **Severity**: MINOR (notational preference, not a correctness issue)
- **Confidence**: HIGH
- **Suggestion**: Use $1-(1-p_1)(1-p_2)$ to match the composition formula form.

### VERIFIED CORRECT: Remaining proofs

- **Theorem 6.1 (Lower bound)**: Correct. The decomposition into membership + value components is sound. The entropy chain rule justification for additivity is appropriate.
- **Proposition 6.1 (Per-seed success probability)**: Correct. The Poisson binomial distribution application is standard.
- **Proposition 6.2 (Bucketed construction time)**: Correct under independence assumption.
- **Proposition 5.1 (Entropy cipher map space)**: Correct. Follows from Shannon source coding.
- **Proposition 8.1 (AND gate correctness)**: Correct (all four cases verified).
- **Theorem 7.1 (Composition correctness)**: Correct as stated (inequality with equality condition).
- **Corollary 7.1 (Chain composition)**: Correct under re-randomization (should be stated as inequality otherwise).
- **Proposition 8.2 (Granularity and privacy)**: Correct. Both directions are sound.
- **Proposition 9.1 (Bayesian deniability)**: Correct. The symmetric error assumption is now explicit (fixed from prior review).
