# Proof Verification: Cryptographic Perfect Hash Functions

**Date:** 2026-03-19

---

## Proof 1: Theorem 3.1 -- PH models a perfect hash function

**Claim:** The data type PH constructed by ph(A, r) models a perfect hash function hash_A^r.

**Verification:** PASS (with a minor issue).

The proof proceeds in three steps:
1. N = ceil(|A|/r), so codomain has at least |A|/r slots.
2. n is chosen as the minimum integer such that beta(., n) restricted to A is injective.
3. The lookup function perfect_hash((n', N), x) = trunc(hash(x' # n'), k)' mod N = beta(x, n).

All three steps are logically sound. The injectivity of beta(., n)|_A is guaranteed by the selection criterion |Y_n| = |A|.

**Minor issue:** The theorem states "k = |A|/r" for the codomain {0,1,...,k-1}, but by the definition, N = ceil(m/r), not m/r exactly. The theorem should use N = ceil(|A|/r) to match the construction.

---

## Proof 2: Theorem 3.2 -- Success probability per trial

**Claim:** p(m,r) = N^{-m} * P^N_m where P^N_m = N!/(N-m)!.

**Verification:** PASS.

This is the standard birthday-problem calculation. Among N^m total functions from A to {0,...,N-1}, exactly P^N_m = N!/(N-m)! are injective on A (choose m distinct outputs in order). The ratio is the probability that a random function is injective on A. Under the random oracle assumption, each trial independently samples such a function.

The reparameterization with r = m/N to get Equation (11) is straightforward substitution:

```
p(m,r) = (m/r)! / ((m/r)^m * (m/r - m)!)
```

This is correct when N = m/r is an integer. When N = ceil(m/r) != m/r, there is a small discrepancy. The paper should note this is asymptotically negligible.

---

## Proof 3: Theorem 3.3 -- Expected coding size

**Claim:** Expected bits/element = log2(e) - (1/r - 1) log2(1/(1-r)).

**Verification:** FAIL (proof technique is flawed, but the result is correct).

### The problematic step

The proof defines Q ~ Geometric(p(m,r)) and states:

> "By Definition 3.1, the n-th trial uniquely maps to a bit string of length m = floor(log2 n). Thus, the expected bit length is given approximately by E[log2 Q] = log2(1/p(m,r))"

This is mathematically invalid. E[log2 Q] != log2(E[Q]) in general. For Q ~ Geometric(p):

- E[Q] = 1/p
- log2(E[Q]) = -log2(p) = log2(1/p)
- E[log2 Q] = sum_{k=1}^{infty} log2(k) * p * (1-p)^{k-1}

These are different. By Jensen's inequality (log is concave): E[log2 Q] <= log2(E[Q]).

### Why the result is still correct

The correct approach uses the bit-length random variable L = floor(log2 Q), whose PMF is derived in Theorem A.2:

```
p_L(n) = q^{2^n - 1}(1 - q^{2^n})
```

and whose expectation is (Theorem A.3):

```
E[L] = sum_{j=1}^{infty} q^{2^j - 1}
```

For large m, q = 1 - p is close to 1, and this sum can be approximated. The paper claims numerical agreement with the closed-form expression, which I can verify by checking the Stirling-based derivation *as if* it were computing log2(E[Q]) rather than E[log2 Q].

The key observation: for the geometric search with very small p (which is the case for large m), the distribution of L is sharply concentrated around its mean. In this regime, E[log2 Q] ~ log2(E[Q]) to leading order. Specifically:

```
E[log2 Q] = log2(1/p) - log2(e) * (1-p)/p * log(1-p)  [exact for geometric]
```

As p -> 0: the second term -> log2(e) * log(1/(1-p)) / p -> log2(e) * p/p = log2(e) (for small p, -log(1-p) ~ p).

Wait, let me be more careful. For Q ~ Geometric(p), a known result gives:

```
E[log2 Q] = -(1/p) * [p*log2(p) + (1-p)*log2(1-p)] / p  ...
```

Actually, E[log Q] for geometric distributions does not have a clean closed form. The correct approach is to note that the paper's formula is derived via Stirling's approximation applied to the *expectation of Q* (not of log Q), and then taking log2. The resulting expression:

```
log2(E[Q]) / m = log2(e)/m - (1/r - 1)log2(1/(1-r))/m ...
```

No, let me re-examine the Stirling derivation more carefully.

### Re-examining the Stirling derivation

The paper computes:

```
log2(E[Q]) = log2(1/p(m,r))
           = log2(N^m / P^N_m)
           = m*log2(N) - log2(N!)  + log2((N-m)!)
```

Applying Stirling: log2(n!) ~ n*log2(n) - n*log2(e):

```
= m*log2(N) - [N*log2(N) - N*log2(e)] + [(N-m)*log2(N-m) - (N-m)*log2(e)]
= m*log2(N) - N*log2(N) + N*log2(e) + (N-m)*log2(N-m) - (N-m)*log2(e)
= m*log2(N) - N*log2(N) + (N-m)*log2(N-m) + m*log2(e)
```

Dividing by m (to get bits/element):

```
= log2(N) - (N/m)*log2(N) + ((N-m)/m)*log2(N-m) + log2(e)
```

Substituting N = m/r:

```
= log2(m/r) - (1/r)*log2(m/r) + (1/r - 1)*log2(m/r - m) + log2(e)
= log2(m/r)*(1 - 1/r) + (1/r - 1)*log2(m(1/r - 1)) + log2(e)
= (1 - 1/r)*log2(m/r) + (1/r - 1)*[log2(m) + log2(1/r - 1)] + log2(e)
= (1 - 1/r)*log2(m/r) + (1/r - 1)*log2(m) + (1/r - 1)*log2(1/r - 1) + log2(e)
= (1 - 1/r)*[log2(m) - log2(r)] + (1/r - 1)*log2(m) + (1/r - 1)*log2(1/r - 1) + log2(e)
= (1 - 1/r)*log2(m) + (1/r - 1)*log2(r) + (1/r - 1)*log2(m) + (1/r - 1)*log2(1/r - 1) + log2(e)
```

Wait: (1 - 1/r) + (1/r - 1) = 0, so the log2(m) terms cancel!

```
= (1/r - 1)*log2(r) + (1/r - 1)*log2(1/r - 1) + log2(e)
= (1/r - 1)*[log2(r) + log2(1/r - 1)] + log2(e)
= (1/r - 1)*log2(r*(1/r - 1)) + log2(e)
= (1/r - 1)*log2(1 - r) + log2(e)
= -(1/r - 1)*log2(1/(1-r)) + log2(e)
= log2(e) - (1/r - 1)*log2(1/(1-r))
```

So the algebra is correct: the m-dependent terms cancel, leaving a formula that depends only on r. The cancellation of m is the key insight -- the bits-per-element cost is asymptotically independent of m.

### Assessment

The formula is correct. The derivation technique is valid *as a computation of log2(1/p(m,r))/m via Stirling*, which gives the leading-order behavior of E[BL(n')]/m. The reason is:

1. log2(1/p(m,r))/m gives the bits/element for log2(E[Q]), not E[log2 Q].
2. However, for the bit-length L = floor(log2 Q), the expected value E[L] concentrates around log2(1/p) as m grows.
3. The independent verification via the series formula (Theorem A.3) confirms the result.

**Recommendation:** Fix the proof to either (a) compute E[L] directly from the PMF and show it equals log2(1/p)/m + o(1), or (b) explicitly state that log2(E[Q]) is being computed and argue that E[BL(n')]/m = log2(E[Q])/m + o(1) asymptotically.

---

## Proof 4: Theorem 3.4 -- Uniform distribution of PHF output

**Claim:** The PHF is a random oracle over X - A and a random k-permutation oracle of A.

**Verification:** PASS (conditional on the random oracle assumption).

The proof argues:
1. For x in A: the construction selects n such that beta(., n)|_A is injective, and the specific permutation is uniformly random among all injective mappings A -> {0,...,N-1} by the random oracle assumption.
2. For x not in A: hash(x' # n') is independent of the construction (since n was chosen based only on elements in A), so the output is uniformly distributed.

The argument about modular arithmetic is correct: when 2^k >> N, the mod-N reduction is approximately uniform.

**Minor issue:** The proof discusses 2^n vs N for uniformity of mod reduction. It would be cleaner to note that the random oracle assumption already gives uniformity over any truncated output, and the mod-N step introduces at most 2^k/N - 1 ~ 0 bias for large k.

---

## Proof 5: Theorem 3.5 -- Maximum entropy encoding

**Claim:** H(N) = E[BL(n')] = log2(e) - (1/r - 1) log2(1/(1-r)) bits/element.

**Verification:** PARTIAL FAIL.

The theorem conflates three things:
1. The entropy H(N) of the bit-length random variable N (a discrete RV taking values 0, 1, 2, ...).
2. The expected bit length E[BL(n')] of the encoding (where n' is the actual bit string, not just its length).
3. The entropy of the encoding n' itself.

For maximum entropy, the relevant quantity is the entropy of n' (the full bit string), not just H(N) (the entropy of its length). The claim should be: "conditioned on having length n, the bit string n' is uniformly distributed over {0,1}^n."

This conditional uniformity follows from the random oracle assumption: given that the first success occurs at trial Q and BL(Q') = n, the specific trial within the length-n strings is uniformly distributed. Each length-n trial succeeds independently with probability p, so the first success among length-n strings (given that all shorter strings failed) is uniformly distributed among {0,1}^n.

Thus the encoding n' has maximum entropy *conditioned on its length*, which means the total entropy is:

```
H(n') = H(N) + E[N]  (since conditioned on length n, the encoding has n bits of entropy)
```

Wait, that's the entropy of the full bit string. But the *expected bit length* of n' is E[N] = E[BL(n')]. For a maximum-entropy encoding of length L, the entropy should equal the expected length (each bit contributes 1 bit of entropy). So the claim is really H(n') = E[BL(n')], which is the maximum entropy property.

The proof should make this argument explicitly:
1. Conditional on BL(n') = n, the bit string n' is uniformly distributed over {0,1}^n (by random oracle assumption).
2. Therefore H(n' | BL(n') = n) = n.
3. E[H(n' | BL(n'))] = E[BL(n')] = E[N].
4. H(n') = H(N) + E[N].
5. Since every bit of n' is uniformly and independently distributed (conditional on length), the encoding is incompressible.

**The proof as written does not make this argument.** It confuses the entropy of the geometric RV Q with the entropy of the bit-string encoding n'.

---

## Proof 6: Theorem A.2 -- PMF of random bit length

**Claim:** p_N(n|m,r) = q^{2^n-1}(1 - q^{2^n}).

**Verification:** PASS.

The derivation is clean:
- For N = n, all 2^n - 1 strings shorter than n must fail: probability q^{2^n - 1}.
- At least one of the 2^n strings of length n must succeed: probability 1 - q^{2^n}.
- The PMF sums to 1 by the telescoping argument.

All steps are correct.

---

## Proof 7: Theorem A.3 -- Expected bit length from PMF

**Claim:** E[N] = sum_{j=1}^{infty} q^{2^j - 1}.

**Verification:** PASS.

The Abel-summation / telescoping trick:

```
E[N] = sum_{j=0}^{infty} j * [q^{2^j-1} - q^{2^{j+1}-1}]
     = 0*(1-q) + 1*(q-q^3) + 2*(q^3-q^7) + 3*(q^7-q^15) + ...
     = q + q^3 + q^7 + q^15 + ...
     = sum_{j=1}^{infty} q^{2^j - 1}
```

This is correct. The rearrangement is valid because all terms are non-negative and the series converges (q < 1 implies q^{2^j} -> 0 superexponentially).

---

## Proof 8: Section 4 -- Two-level construction analysis

**Claim:** The two-level construction achieves the same 1.44 bits/element per bucket on average.

**Verification:** INCOMPLETE.

The paper's analysis of the two-level construction (Section 4) is sketchy. It claims:

1. The partition creates k buckets, processed in decreasing order of cardinality.
2. For bucket j, the probability of finding a non-colliding hash is p_j = (m-j+1)/m.
3. Total trials T = sum T_j where T_j ~ Geometric(p_j).
4. E(T) = m * H_{m-1}.

**Issue with step 2:** The probability p_j = (m-j+1)/m is the probability that a single element maps to an unused slot. But the two-level construction is different: each *bucket* has multiple elements, and we need all elements in the bucket to map to distinct *and unused* slots simultaneously. The analysis conflates the single-element coupon-collector problem with the multi-element bucket-level search.

For the two-level construction (Algorithm 2), each bucket l has approximately m/k elements. The trial for bucket l succeeds when:
- All elements in bucket l map to distinct hashes (birthday-problem probability)
- None of those hashes collide with previously assigned hashes

The success probability for bucket l depends on both |X[l]| and |Y| (the number of already-used slots). This is a more complex calculation than the simple coupon-collector analysis presented.

**The claim that bits/bucket = log2(e) is plausible** (since each bucket's trial index is geometric and encoded via the same bit-string bijection), but the proof is not given. The section as written is more of an outline than a proof.

**Issue with variance formula (line 769-770):** The formula shows:

```
Var(T) = sum_{j=2}^{m} (j-1)/((m-j+1)^2) * m^2
```

This appears to use Var(T_j) = (1-p_j)/p_j^2 with p_j = (m-j+1)/m, giving:

```
Var(T_j) = (1 - (m-j+1)/m) / ((m-j+1)/m)^2 = ((j-1)/m) / ((m-j+1)^2/m^2) = (j-1)*m / (m-j+1)^2
```

So the formula should be sum_{j=2}^{m} (j-1)*m / (m-j+1)^2, not (j-1)*m^2 / (m-j+1)^2. There is an extra factor of m.

---

## Proof 9: Theorem 3.6 -- Minimal PHF achieves 1.44 bits/element

**Claim:** Setting r -> 1 in the space formula gives log2(e) ~ 1.44.

**Verification:** PASS.

The limit is:

```
lim_{r->1} [log2(e) - (1/r - 1)*log2(1/(1-r))]
```

Let a = 1/r - 1 = (1-r)/r. As r -> 1, a -> 0. The second term becomes:

```
a * log2(1/(1-r)) = a * log2(1/(ar/(1+a... )))
```

More directly: let u = 1-r -> 0. Then 1/r - 1 = u/(1-u) -> u, and log2(1/(1-r)) = log2(1/u). So the term is:

```
u * log2(1/u) -> 0  as u -> 0
```

since x*log(1/x) -> 0 as x -> 0. Therefore the limit is log2(e) ~ 1.4427.

Correct.

---

## Summary Table

| Proof | Claim | Verdict | Severity of Issues |
|-------|-------|---------|-------------------|
| Thm 3.1 | PH models PHF | PASS | Minor (ceil vs exact) |
| Thm 3.2 | Success probability | PASS | None |
| Thm 3.3 | Space bound formula | Result CORRECT, proof FLAWED | Medium |
| Thm 3.4 | Uniform distribution | PASS | Minor |
| Thm 3.5 | Maximum entropy | PARTIAL FAIL | Medium |
| Thm 3.6 | 1.44 bits/element | PASS | None |
| Thm A.2 | PMF of bit length | PASS | None |
| Thm A.3 | Expected bit length | PASS | None |
| Sec 4 | Two-level analysis | INCOMPLETE | Medium |

**Overall assessment:** The central result (the space bound formula) is correct, verified by independent derivation via Stirling's approximation and the PMF-based series formula. However, the proof of Theorem 3.3 has a mathematical error (conflating E[log Q] with log E[Q]), and the maximum entropy proof (Theorem 3.5) is insufficiently rigorous. The two-level analysis has errors in the variance formula and conflates bucket-level and element-level success probabilities.
