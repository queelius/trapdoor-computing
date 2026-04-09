# Logic Checker Report

**Paper**: "Quantitative Confidentiality for Cipher Maps"
**Date**: 2026-04-09

---

## Overall Assessment

The paper has 4 theorems, 2 propositions, 1 corollary-level claim, and several informal arguments. The logical chain from cipher map parameters to entropy ratio to the three levers is coherent in structure. However, there are significant issues in the formal proofs: one theorem statement is mathematically incorrect, one proof conflates two different quantities, and one key equation has a subtle error.

**Confidence**: HIGH for critical findings, MEDIUM for the Pinsker bound issue.

---

## Findings

### CRITICAL: Theorem 3.1 part (3) -- Pinsker bound is incorrect

**Location**: Theorem 3.1 (Entropy ratio decomposition), part (3), lines 335-337, proof at lines 350-356.

**Quoted text (statement)**: "The entropy ratio is bounded by $e \geq 1 - \delta \cdot \log_2(2^n / \delta)$ for small $\delta$, via Pinsker's inequality."

**Quoted text (proof)**: "by Pinsker's inequality [...] $\TV(Q, U) \leq \sqrt{D_{\mathrm{KL}}(Q \| U) / 2}$. Since $\TV(Q, U) \leq \delta$, we have $D_{\mathrm{KL}}(Q \| U) \leq 2\delta^2$. Then $H(Q) = \log_2 2^n - D_{\mathrm{KL}}(Q \| U) \geq n - 2\delta^2$, and $e \geq 1 - 2\delta^2/n$."

**Problem**: Two issues compound:
1. The statement claims $e \geq 1 - \delta \cdot \log_2(2^n / \delta)$ but the proof derives $e \geq 1 - 2\delta^2/n$. These are different expressions. The proof's bound is tighter and more useful; the statement's bound is looser and has the wrong form.
2. More fundamentally, the identity $H(Q) = \log_2 2^n - D_{\mathrm{KL}}(Q \| U)$ is correct (since $U$ is uniform on $2^n$ elements, $D_{\mathrm{KL}}(Q \| U) = \log_2 2^n - H(Q)$). The Pinsker-derived bound $D_{\mathrm{KL}}(Q \| U) \leq 2\delta^2$ is also correct. So the proof's conclusion $e \geq 1 - 2\delta^2/n$ is valid. But the theorem *statement* $e \geq 1 - \delta \cdot \log_2(2^n/\delta)$ does not follow from this derivation. The statement appears to be a remnant of a different derivation path.

**Suggestion**: Replace the statement of part (3) with the bound actually derived: $e \geq 1 - 2\delta^2/n$. This is both correct and more informative.

### MAJOR: Theorem 3.1 main equation -- conflation of $\delta$ and $\delta'$

**Location**: Theorem 3.1, equation (2), lines 322-328.

**Quoted text**: "$H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) \cdot H^* = H^*(1 - \delta')$ where $U$ is the uniform distribution on $\B^n$ and $\delta'$ captures the deviation from uniformity."

**Problem**: The first equality $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) \cdot H^*$ is incorrect. The correct identity is $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U)$ (without the multiplicative $H^*$ on the KL term). To see this: $H^* = \log_2 2^n = n$ bits, and $D_{\mathrm{KL}}(Q \| U) = \sum_c Q(c) \log_2(Q(c)/U(c)) = \sum_c Q(c) \log_2(Q(c) \cdot 2^n) = n + \sum_c Q(c) \log_2 Q(c) = n - H(Q)$. Therefore $H(Q) = n - D_{\mathrm{KL}}(Q \| U) = H^* - D_{\mathrm{KL}}(Q \| U)$.

The paper writes $H^* - D_{\mathrm{KL}}(Q \| U) \cdot H^*$, which would give $e = 1 - D_{\mathrm{KL}}(Q \| U)$ (since dividing both sides by $H^*$). But the correct derivation gives $e = 1 - D_{\mathrm{KL}}(Q \| U)/H^*$. The second form $H^*(1 - \delta')$ with $\delta' = D_{\mathrm{KL}}(Q \| U)/H^*$ is consistent with the correct identity, but the explicit formula with the extra $H^*$ factor is wrong.

**Suggestion**: Fix to $H(Q) = H^* - D_{\mathrm{KL}}(Q \| U) = H^*(1 - D_{\mathrm{KL}}(Q \| U)/n)$ where $n = H^* = \log_2 2^n$.

### MAJOR: Theorem 4.1 proof part (1) -- mixture entropy formula is informal

**Location**: Theorem 4.1 (Noise dilution), part (1), lines 396-401, proof at lines 413-418.

**Quoted text (statement)**: "$H_{\mathrm{mix}} = H_b(\rho) + \rho \cdot H(D) + (1 - \rho) \cdot n$"

**Quoted text (proof)**: "By the chain rule, the per-element entropy is the entropy of the mixing indicator plus the conditional entropy given the indicator."

**Problem**: This formula is correct only when (a) the mixing indicator (real vs. filler) is observable or can be conditioned on, AND (b) the two components are independent. The chain rule $H(C) = H(Z) + H(C|Z)$ where $Z$ is the indicator gives $H(C) = H_b(\rho) + \rho \cdot H(C|Z=\text{real}) + (1-\rho) \cdot H(C|Z=\text{filler})$. Here $H(C|Z=\text{real})$ is the entropy of cipher values given they are real queries, which equals $H(D)$ only if enc is injective (K(x)=1). With K(x) > 1, the entropy per real query could be higher than $H(D)$. The proof does not address this interaction.

More precisely: if the system uses multiple representations (K(x) > 1, from Section 4.2), the entropy of a real cipher value is not $H(D)$ but rather $H(Q_{\text{real}})$ which accounts for the randomness of the encoding choice. The formula should use $H(Q_{\text{real}})$ instead of $H(D)$.

**Suggestion**: Either (a) state that Theorem 4.1 assumes K(x) = 1 (simple substitution), or (b) replace $H(D)$ with $H(Q_{\text{real}})$ and note that $H(Q_{\text{real}}) \geq H(D)$ with equality when K(x) = 1.

### MAJOR: Theorem 4.1 part (3) -- Fisher information claim lacks rigor

**Location**: Theorem 4.1, part (3), lines 405-410, proof at lines 422-433.

**Quoted text**: "the adversary needs $\Omega((1 + R/N)^2)$ observations to achieve the same estimation accuracy as observing $N$ pure real queries."

**Problem**: The proof sketches that Fisher information is "reduced by a factor of $\rho^2$." This is stated without derivation. For a general mixture model $P_{\text{mix}}(c) = \rho \cdot D(c) + (1-\rho) \cdot U(c)$, the Fisher information about a parameter $\theta$ of $D$ is $I_{\text{mix}}(\theta) = \rho^2 \cdot I_D(\theta) / P_{\text{mix}}(c)$ integrated appropriately. The factor is not simply $\rho^2$ in general; it depends on the ratio $D(c)/P_{\text{mix}}(c)$. The $\rho^2$ scaling is an approximation valid when $\rho$ is small (so $P_{\text{mix}} \approx U$), but this condition is not stated.

**Suggestion**: Either provide the full Fisher information calculation for the mixture, or state the $\rho^2$ factor as an approximation valid for $\rho \ll 1$ with a reference.

### MINOR: Proposition 5.1 part (2) -- "preserves all correlations" is imprecise

**Location**: Proposition 5.1, line 715.

**Quoted text**: "The joint distribution $(\fhat_1(c), \fhat_2(c))$ preserves all correlations between $f_1(x)$ and $f_2(x)$."

**Problem**: "Preserves all correlations" is informal. What is preserved is the joint distribution of $(f_1(x), f_2(x))$ up to relabeling (since the cipher maps are deterministic given the encoding). But correlation (Pearson, rank, mutual information) depends on the marginal distributions, which are relabeled. The mutual information $I(f_1(X); f_2(X))$ is preserved exactly since it is invariant under bijection, but Pearson correlation is not (it depends on the numerical values). The claim should be stated in terms of mutual information.

**Suggestion**: Replace "preserves all correlations" with "preserves mutual information: $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X); f_2(X))$."

### MINOR: Informal claims in Section 5 about orbit/confidentiality

**Location**: Lines 556-572.

**Quoted text**: "The confidentiality $\mathrm{conf}_F(c)$ measures how much uncertainty the adversary retains [...] it is $1$ when the adversary has learned nothing and $0$ when the latent value is uniquely determined."

**Problem**: The paper cites this from [towell2026algebraic] but does not define $\mathrm{conf}_F(c)$ precisely here. The bound $\mathrm{conf}_F(c) \geq 1 - |\mathrm{orbit}_F(c)|/2^n$ is stated but the definition of confidentiality in terms of the adversary's posterior is left vague. Since this is cited from a companion paper, this is acceptable for a theory paper, but a sentence defining the adversary's uncertainty model (e.g., "the fraction of latent values consistent with the observed orbit") would improve readability.

### SUGGESTION: Make the assumption structure explicit

The paper has several implicit assumptions that interact: random oracle model, independence of cipher map evaluations, K(x) = 1 vs. K(x) > 1, i.i.d. queries. A consolidated assumption block at the beginning of Section 3 or 4 would make the logical dependencies clear.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 1 | Theorem 3.1 part (3) statement/proof mismatch |
| Major | 3 | Theorem 3.1 equation error, Theorem 4.1 H(D) assumption, Fisher info claim |
| Minor | 2 | Correlation preservation imprecise, orbit/conf underspecified |
| Suggestion | 1 | Consolidated assumption block |
