# Proof Verification: Maximizing Confidentiality in Encrypted Search Through Entropy Optimization

**Date**: 2026-03-19
**Reviewer**: papermill (Claude Opus 4.6)
**Paper**: `papers/maximizing-confidentiality/main.tex`

---

## Summary

The paper contains approximately 15 theorems/corollaries and 4 formal definitions with proofs. The information-theoretic results are mostly standard applications of well-known theorems to the encrypted search domain. Several proofs are incomplete or contain errors. No result is novel in the mathematical sense; the contribution is the application to encrypted search.

**Verdict**: 8 of 15 results are correct; 3 are incomplete; 2 have errors; 2 are not actually proven.

---

## Detailed Verification

### 1. Bit Rate Theorem (lines 757-789)

**Statement**: The average bit rate of the hidden query and result set streams is O(lambda(m*mu + theta)).

**Verification**: CORRECT but trivially so. The proof correctly computes expected bit length per query as mu*m + O(1) for the query encoding and O(theta) for the result set, then multiplies by the arrival rate lambda. This is a straightforward calculation, not really a "theorem." The big-O notation hides constants that could matter in practice.

**Issue**: The proof claims O(theta) for result set encoding but does not specify the encoding. If result sets are subsets of {1,...,N}, the encoding cost per result is ceil(log2(N)), making the result set contribution O(theta * log2(N)), not O(theta). The theta term should be theta * ceil(log2(N)).

**Severity**: Minor error in the proof (but the big-O claim is technically fine since N is a constant).

---

### 2. Constrained Maximum Entropy (lines 1145-1171)

**Statement**: The maximum entropy of the sequence of random tuples factors as:
```
H*(lambda, k, N, M, n, p) = n * (H*(T|lambda) + H*(A|k) + H*(X|M,p) + H*(D|N))
```

**Verification**: INCOMPLETE PROOF. The proof claims independence maximizes joint entropy (correct by the subadditivity of entropy), but the jump from general to i.i.d. is not justified. The proof states "the random tuples are identically distributed" because "we are interested in the maximum entropy distribution" -- this is circular reasoning. The correct argument is: among all distributions with the given marginal constraints, the product of marginal maximum entropy distributions maximizes joint entropy (by the fact that H(X,Y) <= H(X) + H(Y) with equality iff independent).

**Issue**: The proof also contains an inconsistency. The statement (line 1148) uses parameters (lambda, k, N, M, n, p), but the "proof" conclusion (line 1167) uses different parameters (lambda, mu, k, m, n) with different letters. These two expressions are supposed to be the same result but have different parameter lists and different structures.

**Severity**: Major -- the proof is not a proof, and the two versions of the formula are inconsistent.

---

### 3. Maximum Entropy for Inter-Arrival Times (lines 1173-1190, repeated at 1534-1554)

**Statement**: Subject to E[T] = 1/lambda, the maximum entropy distribution is exponential with entropy 1 + ln(1/lambda).

**Verification**: CORRECT. This is a standard result. Among continuous distributions on R_>0 with fixed mean 1/lambda, the exponential distribution maximizes differential entropy. The proof via calculus of variations (or equivalently, Lagrange multipliers on the entropy functional) is well-known and correctly stated.

**Note on units**: The entropy is given in nats (natural logarithm), not bits (log base 2). This creates an inconsistency when combined with discrete entropies measured in bits elsewhere in the paper. The correct bits version would be (1 + ln(1/lambda)) / ln(2) = log2(e) + log2(1/lambda).

---

### 4. Quantized Inter-Arrival Times (lines 1193-1215)

**Statement**: The optimal compression for quantized exponentially distributed inter-arrival times with precision tau has expected length:
```
H(T|lambda,tau) = (1/(lambda*tau)) * log2(1/(lambda*tau)) + (1/(lambda*tau) - 1) * log2(1/(lambda*tau) - 1)
```

**Verification**: ERROR. The stated formula does not match the entropy of a geometric distribution.

The geometric distribution Geo(p = lambda*tau) has entropy:
```
H = (-(1-p)*log2(1-p) - p*log2(p)) / p
```

The paper's proof states this formula correctly at line 1212, but the theorem statement (lines 1196-1197) gives a different, incorrect formula. Let q = 1-p = 1-lambda*tau. The correct expansion is:
```
H = (-q*log2(q) - p*log2(p)) / p
```

The theorem statement appears to use (1/p)*log2(1/p) + (1/p - 1)*log2(1/p - 1), which is:
```
(1/(lambda*tau)) * log2(1/(lambda*tau)) + (1/(lambda*tau) - 1) * log2(1/(lambda*tau) - 1)
```

This does not equal the geometric entropy. The geometric entropy is:
```
(-q*log2(q) - p*log2(p)) / p = -(1-p)/p * log2(1-p) - log2(p)
```

Setting p = lambda*tau, this is -(1/(lambda*tau) - 1)*log2(1-lambda*tau) - log2(lambda*tau), which is different from the stated formula.

The asymptotic form (line 1200) is approximately correct: as lambda*tau -> 0, the geometric entropy approaches log2(1/(lambda*tau)) + log2(e), which can be rewritten as log2(1/lambda) + log2(1/tau) + log2(e). This matches the stated limit.

**Severity**: Error in theorem statement; proof derivation has the right formula; limit is correct.

---

### 5. Maximum Entropy for Agent Identities (lines 1217-1236, repeated at 1559-1579)

**Statement**: Subject to k search agents, H*(A|k) = log2(k) via uniform distribution.

**Verification**: CORRECT. Standard result. Among discrete distributions on k outcomes with no additional constraints, the uniform distribution maximizes entropy with value log2(k).

**Minor issue**: The pmf at line 1230 has a typo: the indicator function uses "k in {1,...,k}" which should be "a in {1,...,k}".

---

### 6. Maximum Entropy Corollary - Joint Distribution (lines 1244-1253)

**Statement**: The maximum entropy tuple distribution is:
```
p(t,a,y) = lambda*(1-lambda)^{t-1} * (1/k) * (1/mu)*(1-1/mu)^{alpha-1} * 2^{-alpha*m}
```

**Verification**: ERROR. The formula has a syntax error: `2^{-alpha) m}` has a mismatched parenthesis (line 1250), but more importantly, the mathematical content has issues.

The geometric component for query cardinality should be (1/mu)*(1-1/mu)^{alpha-1} where alpha = |y| (number of trapdoors). This is correct for the cardinality distribution.

The trapdoor selection component should be (1/2^m)^alpha = 2^{-alpha*m} for uniform selection from {0,...,2^m-1}. This is correct.

However, the inter-arrival time component uses lambda*(1-lambda)^{t-1}, which is a geometric distribution with parameter lambda. The earlier analysis (Theorem 3, line 1173) used an exponential distribution. This is inconsistent unless we interpret the corollary as working in the quantized domain where the precision tau is incorporated into lambda. This should be stated explicitly.

**Severity**: Minor (notational error, implicit quantization assumption needs stating).

---

### 7. MLE of Maximum Entropy (lines 1257-1285)

**Statement**: The MLE of H* is the plug-in estimator H*(m-hat, k-hat, lambda-hat, mu-hat).

**Verification**: CORRECT in principle but the proof is incomplete. The proof invokes the invariance property of MLEs (if theta-hat is MLE of theta, then g(theta-hat) is MLE of g(theta)). This is a valid application. The individual MLEs are:
- k-hat = max(a_1,...,a_n): Correct for uniform on {1,...,k}
- lambda-hat = n/sum(t_i): Correct for geometric
- mu-hat = (1/n)*sum(dim(x_i)): Correct for geometric mean

The "proof" says "Continue on in the same fashion for the other random variables" (line 1280) which is not a proof.

**Severity**: Proof is a sketch, not a complete proof.

---

### 8. Compression-Based Entropy Estimator (lines 1289-1320)

**Statement**: A positively biased estimator of H_n is the bit length of the compressed encoding.

**Verification**: CORRECT. Any lossless compressor produces output at least as long as the entropy (source coding theorem lower bound). A suboptimal compressor produces output longer than the entropy, so the estimator has positive bias. The proof correctly invokes this.

**Issue**: The embedded corollary (lines 1307-1317) gives an asymptotic form:
```
H* = n*(log2(mu*k/lambda) + mu*(m+1) + const)
```
where const = 2*log2(e). This appears to combine:
- log2(1/lambda) from inter-arrival times (but this should be log2(e) + log2(1/lambda) for the geometric entropy)
- log2(k) from agent identities
- mu*m from trapdoor encoding (mu trapdoors times m bits each)
- additional terms from geometric distribution of query cardinality

The formula does not clearly derive from the component entropies. The mu*(m+1) term suggests mu*m for trapdoor bits plus mu*1 for the unary coding of each trapdoor count, but this is the expected code length, not the entropy. The const = 2*log2(e) is unexplained.

**Severity**: The asymptotic formula is plausible but not rigorously derived.

---

### 9. Total System Entropy (lines 1365-1378, Section 6)

**Statement**: Joint entropy decomposes by chain rule; simplifies to n*H(Q-hat) under i.i.d.

**Verification**: CORRECT. This is the chain rule for joint entropy, which is a basic identity, not a theorem requiring proof.

---

### 10. Poisson Process Superposition (lines 2019-2030)

**Statement**: If k agents each generate Poisson process queries with rates lambda_1,...,lambda_k, the superposition is a Poisson process with rate lambda_1+...+lambda_k.

**Verification**: CORRECT. This is a standard result in stochastic processes (superposition of independent Poisson processes). The proof correctly uses the additive property of Poisson random variables.

---

### 11. Maximum Entropy for Query Cardinality (lines 1584-1601, Section 7)

**Statement**: Subject to E[N_trap] = mu with N_trap in {1,...,u}, the approximate max-entropy distribution is geometric with p = 1/mu.

**Verification**: CORRECT with caveat. The geometric distribution maximizes entropy among distributions on positive integers with a given mean. When truncated at u, the actual maximum entropy distribution is a truncated geometric, but the paper correctly notes that truncation effects are negligible for large u/mu ratios.

---

### 12. Maximum Entropy for Trapdoor Selection (lines 1606-1619, Section 7)

**Statement**: With vocabulary size m and no frequency constraints, max-entropy is uniform with H* = log2(m).

**Verification**: CORRECT. Standard result for finite discrete distributions with no constraints beyond support size.

---

### 13. Joint Maximum Entropy (lines 1631-1656, Section 7)

**Statement**: Under independence, the total max-entropy for n tuples is:
```
H*_n = n * [H*(T) + H*(A) + H*(N_trap) + E[N_trap]*H*(Y) + H*(N_results) + E[N_results]*log2(N)]
```

**Verification**: MOSTLY CORRECT. The decomposition of query entropy as H*(N_trap) + E[N_trap]*H*(Y) is correct: this is the entropy of a random-length sequence where the length has entropy H*(N_trap) and each element, given the length, has entropy H*(Y). Formally, H(N,Y_1,...,Y_N) = H(N) + E[N]*H(Y) when Y_i are i.i.d. conditional on N and independent of N.

**Issue**: The result set term E[N_results]*log2(N) assumes uniform selection of documents, but this conflicts with the earlier observation that result sets are deterministic given the query. This inconsistency is a conceptual error in the maximum entropy model (see Major Weakness 5 in the review).

**Severity**: Conceptual error regarding result sets.

---

### 14. Homophonic Encryption Entropy (Case Study, lines 2157-2192)

**Statement**: Homophonic encryption with n_i = ceil(p(x_1)/p(x_i)) substitutions for the top b words raises trapdoor entropy to approximately 10.2 bits.

**Verification**: PLAUSIBLE but not rigorously computed. The paper does not show the full calculation. For a Zipf(s=1) distribution with m=10000, the top b=100 words account for about 52% of probability mass. Making them approximately uniform (with respect to the 100th-ranked word) redistributes that mass. The claimed 10.2 bits (up from 7.83) is plausible but would need numerical computation to verify exactly.

The space overhead calculation (518 additional trapdoors per document) is stated without derivation. For b=100 words with n_i = ceil(p(x_1)/p(x_i)), we need:
- n_1 = 1 (reference word)
- n_2 = ceil(1/0.5) = 2
- n_3 = ceil(1/0.333) = 3
- ...
- n_100 = ceil(1/0.01) = 100

Total additional trapdoors = sum_{i=1}^{100}(n_i - 1) = sum_{i=1}^{100}(ceil(i) - 1) = sum_{i=2}^{100} ceil(i-1) ~ sum_{i=1}^{99} i = 4950. This is much larger than the claimed 518.

Wait -- the Zipf distribution has p(x_i) = 1/(i*H_{m,1}), so n_i = ceil(p(x_1)/p(x_i)) = ceil(i). The sum is sum_{i=1}^{100} i - 100 = 5050 - 100 = 4950 additional trapdoors (in the index for one instance), not 518.

But the 518 may refer to additional trapdoors *per document*, where only a fraction of words appear in each document. If a document has |D| unique words, the expected additional trapdoors per document would be the sum over words in D of (n_i - 1). For documents with ~100-500 unique words, 518 per document is plausible if the Zipf-frequent words are common in documents.

**Severity**: Ambiguous -- the claim may be correct given unstated assumptions about document composition, but the derivation is absent.

---

### 15. Combined Entropy (Case Study, line 2199)

**Statement**: Combined entropy of authentic (67%) and artificial (33%) queries:
```
H_combined = 0.67 * 23.49 + 0.33 * 39.87 = 28.86 bits
```

**Verification**: INCORRECT METHODOLOGY. The entropy of a mixture is not the weighted average of component entropies. For a mixture distribution p(x) = alpha*p1(x) + (1-alpha)*p2(x):
```
H(mixture) >= alpha*H(p1) + (1-alpha)*H(p2)   (by concavity of entropy)
```

The weighted average is a *lower bound* on the mixture entropy, not an estimate. The actual mixture entropy also includes the entropy of mixing itself. For two very different distributions, the mixture entropy can be substantially higher than the weighted average. So the paper's estimate of 28.86 bits is conservative (a lower bound), and the true efficiency improvement would be even better than claimed. This makes the claimed 0.72 efficiency a conservative estimate.

**Severity**: Methodological error, but conservative (understates the improvement).

---

## Unfinished / Missing Proofs

1. **Solution for H*(X|M,p)** (line 1238): Labeled as a paragraph heading but contains no content.
2. **Solution for H*(D|N)** (line 1240): Labeled as a paragraph heading but contains no content.
3. **Theorem on artificial trapdoor entropy** (line 1895-1899): Statement is incomplete (H*(L,Y) = H*(L|mu_L, Y) but right-hand side is unexpanded) and no proof is given.
4. **Result set cardinality max-entropy** (line 1624-1626): Statement says "geometric or Poisson-like" without deriving which one or computing the entropy.
5. **Algorithm 4 - Generative Model** (lines 1011-1040): Empty parameter and input fields. Contains placeholder text ("something that delays sending hidden query up to some limit").

---

## Summary Table

| # | Result | Location | Verdict | Severity |
|---|--------|----------|---------|----------|
| 1 | Bit rate theorem | 757 | Correct (trivial) | -- |
| 2 | Constrained max entropy | 1145 | Incomplete proof, inconsistent | Major |
| 3 | Max entropy inter-arrival | 1173/1534 | Correct | -- |
| 4 | Quantized inter-arrival | 1193 | Error in statement | Medium |
| 5 | Max entropy agents | 1217/1559 | Correct | -- |
| 6 | Joint distribution corollary | 1244 | Minor notational errors | Minor |
| 7 | MLE of max entropy | 1257 | Sketch, not proof | Minor |
| 8 | Compression estimator | 1289 | Correct; asymptotic formula unclear | Minor |
| 9 | Total system entropy | 1365 | Correct (trivial) | -- |
| 10 | Poisson superposition | 2019 | Correct | -- |
| 11 | Max entropy cardinality | 1584 | Correct with caveat | -- |
| 12 | Max entropy trapdoor | 1606 | Correct | -- |
| 13 | Joint max entropy | 1631 | Conceptual error (result sets) | Major |
| 14 | Homophonic entropy | 2157 | Plausible, unverified | Medium |
| 15 | Combined mixture entropy | 2199 | Incorrect methodology | Medium |

---

## Recommendations for Proof Revision

1. **Consolidate the maximum entropy derivations** into a single clean presentation (Section 7 should be canonical; delete the redundant Section 6 derivations).

2. **Fix the quantized inter-arrival entropy formula** (Theorem 4) to match the geometric distribution entropy stated in the proof body.

3. **Resolve the result set determinism issue**: either derive conditional maximum entropy H*(result | query) = 0 and remove result set terms from the joint formula, or model result sets differently (e.g., with artificial documents adding randomness).

4. **Complete the missing derivations**: H*(X|M,p), H*(D|N), and the artificial trapdoor entropy theorem.

5. **Fix the mixture entropy calculation** in the case study. Use the actual mixture entropy formula, not the weighted average. The correction actually strengthens the paper's claims.

6. **Choose consistent units**: either nats (natural log) or bits (log2) throughout. Currently the inter-arrival time entropy uses nats while everything else uses bits.
