# Logic Checker Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper presents 2 theorems, 4 propositions, 1 corollary, and 1 algorithm, all with proofs. The logical structure is generally sound, with proofs that follow from stated assumptions. The composition theorem (Theorem 8.1) is the strongest result and its proof is correct. However, there are several issues of varying severity.

## Findings

### F1. Composition theorem re-randomization assumption (Major, Medium confidence)
**Location**: Theorem 8.1, proof condition (ii), lines 1081-1084
**Quoted text**: "Assume: (i) f-hat and g-hat use independent seeds, and (ii) g-hat's correctness on f-hat(c) is independent of whether f-hat was correct (re-randomization: the encoding fed to g-hat is a fresh random valid encoding of f(x))."
**Problem**: Condition (ii) is strong and non-trivial. For the hash-based constructions in this paper, when f-hat produces the correct output enc_g(f(x), k) for some specific k, g-hat's correctness may depend on which k was produced. The proof claims this gives a "tight bound" but then Remark 8.1 (lines 1093-1101) partially retracts it, saying the formula is "best understood as an upper bound under the weaker assumption that errors are positively correlated." This tension between the theorem statement (which presents the formula as an equality) and the remark (which says it is an upper bound) is confusing.
**Suggestion**: Either (a) strengthen the theorem statement to explicitly state the re-randomization assumption and note that without it the formula is an upper bound, or (b) state the theorem as an inequality $\eta_{g \circ f} \leq \eta_f + \eta_g - \eta_f \eta_g$ and prove it under the weaker assumption. The current formulation tries to have it both ways.

### F2. Lower bound proof conflates universe size with false positive rate (Major, High confidence)
**Location**: Theorem 7.1, proof, lines 870-902
**Quoted text**: "Setting $\varepsilon = n/|U|$ (the fraction of the universe that decodes validly), this is $n \log_2(1/\varepsilon)$ bits."
**Problem**: The identification $\varepsilon = n/|U|$ is informal and conflates two different quantities. The paper defines $\varepsilon$ as the probability that random bits form a valid codeword (Definition 4.5 / Table 1), which is a property of the encoding scheme. The counting argument gives a lower bound in terms of $|U|/n$, and equating this with $1/\varepsilon$ requires the assumption that the effective universe size equals $n/\varepsilon$. This is the right intuition but the step from the combinatorial bound to the information-theoretic bound via $\varepsilon$ needs more justification: specifically, that any encoding scheme with noise-decode probability $\varepsilon$ must have an effective universe of size at least $n/\varepsilon$.
**Suggestion**: Add a sentence explicitly connecting: "Any encoding scheme where random $n$-bit strings decode to valid output with probability $\varepsilon$ has effective universe size $|U| \geq n/\varepsilon$ (since at most $\varepsilon \cdot 2^n$ of the $2^n$ possible inputs decode validly, and all $n$ stored elements must map to valid inputs)."

### F3. Space complexity proof Step 1: false negative reduction logic (Minor, High confidence)
**Location**: Theorem 7.2, proof Step 1, lines 957-959
**Quoted text**: "When false negatives are permitted at rate eta, only (1-eta)n of the n elements must decode correctly, reducing the effective element count."
**Problem**: This is correct in spirit but the proof says the space is $(1-\eta)n(-\log_2 \varepsilon + \mu)$ bits, meaning it saves space proportional to $\eta$. However, the failing elements still occupy hash table entries (their seeds still exist); what saves space is that the seed search succeeds more easily (fewer constraints). The proof conflates "fewer constraints" with "fewer bits stored." In practice, the seed $\ell$ is a single value regardless of $\eta$, so space savings from $\eta > 0$ come from being able to use smaller hash widths (smaller $n$), not from storing fewer elements.
**Suggestion**: Clarify that $\eta > 0$ reduces the effective information content (fewer bits of entropy in the mapping), not the physical storage. The $(1-\eta)$ factor represents the reduction in information-theoretic requirement, which translates to a smaller feasible $n$.

### F4. AND gate correctness table: case (0,0) formula (Minor, High confidence)
**Location**: Proposition 8.1, table row $(0,0)$, line 1035
**Quoted text**: "$p_1 + p_2 - p_1 p_2$"
**Problem**: Let me verify. When $x_1=0, x_2=0$, the correct output is $\text{AND}(0,0) = 0$. The output is wrong (=1) only when both $B_1=1$ and $B_2=1$, i.e., both are incorrect. $\Pr[\text{wrong}] = (1-p_1)(1-p_2)$. So $\Pr[\text{correct}] = 1 - (1-p_1)(1-p_2) = p_1 + p_2 - p_1 p_2$. This is correct.
**Status**: Verified correct.

### F5. Membership false positive rate derivation (Minor, Medium confidence)
**Location**: Proposition 5.3, proof, lines 671-680
**Quoted text**: "Pr[F(W)_j = 0] = (1/2)^k = 2^{-k} (probability none of the k elements set bit j)"
**Problem**: This is correct under the random oracle model (each element independently sets each bit with probability 1/2). The derivation is sound. However, the step to the false positive formula $(1 - 2^{-(k+1)})^n$ deserves one more line: $\Pr[\text{false positive}] = \Pr[\text{all n bits pass}] = \prod_{j=1}^n \Pr[h(x)_j = 0 \text{ or } F(W)_j = 1] = (1 - \Pr[h(x)_j = 1] \cdot \Pr[F(W)_j = 0])^n = (1 - 2^{-(k+1)})^n$.
**Status**: Correct but could be slightly more explicit.

### F6. Bayesian deniability proposition assumes symmetric error (Minor, High confidence)
**Location**: Proposition 9.1, lines 1331-1348
**Quoted text**: "Pr[y=1 | f(x)=1] = 1-eta (correct positive) and Pr[y=1 | f(x)=0] = eta (false positive)"
**Problem**: The proof assumes the false positive rate equals the false negative rate (both are $\eta$). But the paper's Definition 4.3 defines $\eta$ as the average error rate over all in-domain elements. For Boolean-valued cipher maps, there are two distinct error rates: $\eta_{\text{FN}} = \Pr[\text{dec}(\hat{f}(\text{enc}(x,k))) = 0 \mid f(x) = 1]$ and $\eta_{\text{FP}} = \Pr[\text{dec}(\hat{f}(\text{enc}(x,k))) = 1 \mid f(x) = 0]$. The proposition implicitly assumes $\eta_{\text{FN}} = \eta_{\text{FP}} = \eta$, which is not guaranteed by the construction.
**Suggestion**: Either (a) state the symmetric error assumption explicitly in the proposition, or (b) generalize to separate $\eta_{\text{FN}}$ and $\eta_{\text{FP}}$ parameters. The Bayes formula with asymmetric rates is: $\Pr[f(x)=1 \mid y=1] = \pi(1-\eta_{\text{FN}}) / [\pi(1-\eta_{\text{FN}}) + (1-\pi)\eta_{\text{FP}}]$.

### F7. Composability definition requires type compatibility (Minor, Medium confidence)
**Location**: Definition 4.4, lines 359-367
**Quoted text**: "let (f-hat, enc_f, dec_f, s_f) be a cipher map for f : X -> Y and (g-hat, enc_g, dec_g, s_g) a cipher map for g : Y -> Z. Then g-hat o f-hat..."
**Problem**: The composition $\hat{g} \circ \hat{f}$ is always well-defined as a function $\{0,1\}^n \to \{0,1\}^n$ (both are total functions on the same bit-string space). But for the composition to be a cipher map for $g \circ f$, the encoding $\text{enc}_f$ and decoding $\text{dec}_g$ must be compatible: specifically, $\text{dec}_g(\hat{g}(\hat{f}(\text{enc}_f(x,k))))$ should yield $g(f(x))$. This requires that $\hat{f}$'s output, when correct, is a valid encoding for $\hat{g}$'s input. The definition says "encoding $\text{enc}_f$ and decoding $\text{dec}_g$" but does not make this compatibility condition explicit.
**Suggestion**: Add: "where the output encoding of $\hat{f}$ is compatible with the input encoding of $\hat{g}$: for each $x \in X$ and valid $k$, $\hat{f}(\text{enc}_f(x,k))$ is a valid encoding under $\text{enc}_g$ of $f(x)$ (when the map is correct)."

## Overall Assessment

The logical structure is sound. The main results (composition theorem, space lower bound, space optimality) are correct under their stated assumptions. The primary concern is that the composition theorem's re-randomization assumption is stated as a condition in the proof but the theorem presents the result as an equality, while a subsequent remark walks it back to an upper bound. The lower bound proof could be tightened at the $\varepsilon = n/|U|$ step. The Bayesian deniability proposition assumes symmetric errors without stating it. No fundamental logical errors were found.

**Confidence**: High for most findings. Medium for F1 (the re-randomization issue is subtle) and F7 (type compatibility may be handled implicitly by the bit-string formulation).
