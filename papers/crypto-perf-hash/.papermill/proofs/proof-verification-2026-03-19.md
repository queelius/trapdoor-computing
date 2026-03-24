# Deep Proof Verification: Cryptographic Perfect Hash Functions

**Date:** 2026-03-19
**Paper:** paper/paper.tex
**Scope:** Every theorem, corollary, postulate, and formal claim in the paper

---

## Notation Key

Throughout this document:
- m = |A| (cardinality of the set being hashed)
- r = load factor in (0,1]
- N = ceil(m/r) (codomain size)
- p = p(m,r) = success probability per trial
- q = 1 - p
- Q ~ Geometric(p) (trial at which first success occurs)
- L = BL(Q') = floor(log2 Q) (bit length of the encoding)

---

## 1. Theorem (unnumbered, after Definition 3.5): PH Models a Perfect Hash Function

**Claim (tex lines 404-414):** A value of type PH constructed with ph(A,r) models hash_A^r : {0,1}* -> {0,1,...,k-1} where A subset {0,1}* and k = |A|/r.

**Proof walkthrough:**

Step 1: N = ceil(|A|/r), so |codomain| = N >= |A|/r. The load factor is |A|/N <= r. **Correct.**

Step 2: n is chosen as min{j in N : |Y_j| = |A|}, where Y_j = {beta(x,j) : x in A}. The condition |Y_j| = |A| means beta(.,j) restricted to A is injective (no two elements of A map to the same value). **Correct.**

Step 3: The lookup function perfect_hash((n', N), x) computes trunc(hash(x' # n'), k)' mod N = beta(x, n) by definition. Since beta(.,n)|_A is injective and maps into {0,...,N-1}, this is a perfect hash function. **Correct.**

**Issues:**
- The theorem statement says "k = |A|/r" but the construction uses N = ceil(m/r). These differ when m/r is not an integer. The theorem should say N = ceil(|A|/r), not k = |A|/r. This is a minor imprecision, not an error---the proof itself uses the correct quantity.
- The variable k is also used for ceil(log2 N) in the construction, creating a name collision with the k in the theorem statement.

**Verdict: PASS (minor notation issues).**

---

## 2. Theorem (unnumbered, after Algorithm 1): Uniform Distribution of PHF Output

**Claim (tex lines 430-439):** The perfect hash function is a random oracle over X - A and a random k-permutation oracle of A.

**Proof walkthrough:**

Step 1: "b_n is a bit string such that each x in S concatenated with b_n hashes to a unique integer in {1,...,N}." This follows from the construction: n is chosen so that beta(.,n)|_A is injective. **Correct.**

Step 2: "hash approximates a random oracle whose output is uniformly distributed over {0,1}^n." By Assumption 3.2. **Correct by assumption.**

Step 3: "If N = k * 2^n for some integer k, the remainder... is uniformly distributed over {1,...,N}." This is the standard argument about uniformity of modular reduction. When 2^(ceil(log2 N)) >> N (which it generally is not---ceil(log2 N) gives at most 2N), there is a bias of at most 1 part in N. **Approximately correct.**

Step 4 (implicit): For x not in A, hash(x' # n') is independent of the construction event (which depends only on hash evaluations of elements of A concatenated with n'). Under the random oracle model, hash is independent across distinct inputs, so for x not in A, hash(x' # n') is independent and uniformly distributed. **Correct under the random oracle assumption.**

Step 5 (implicit): For x in A, conditioned on the event that beta(.,n)|_A is injective, each injective mapping A -> {0,...,N-1} is equally likely. This is because the random oracle assigns independent uniform values to each input, and conditioning on injectivity produces a uniform random injection (k-permutation). **Correct.**

**Issues:**
- The proof mentions "adding 1" (line 438: "adding 1 is uniformly distributed over {1,...,N}") but the codomain in the construction is {0,...,N-1}, not {1,...,N}. Minor inconsistency.
- The bias from modular reduction when 2^k is not a multiple of N is acknowledged ("approximately uniformly distributed") but not quantified. For cryptographic applications, this bias should be bounded. However, the paper states convergence as n -> infinity, which is correct.

**Verdict: PASS (minor issues with codomain indexing and bias quantification).**

---

## 3. Theorem (tex lines 442-481): Success Probability Per Trial (Theorem 3.2 in the paper's numbering)

**Claim:** p(m,r) = N^{-m} * P^N_m = (m/r)! / ((m/r)^m * (m/r - m)!).

**Proof walkthrough:**

The number of injective functions from A (|A| = m) to {0,...,N-1} is P^N_m = N!/(N-m)! (choose m distinct outputs in order). The total number of functions from A to {0,...,N-1} is N^m. Under the random oracle assumption, each trial selects a function uniformly at random. The probability that a random function is injective is therefore P^N_m / N^m. **Correct.**

The reparameterization: substituting N = m/r gives Equation (11):

p(m,r) = (m/r)! / ((m/r)^m * (m/r - m)!)

**This is correct when N = m/r is an integer.** When N = ceil(m/r) != m/r, there is a discrepancy. For large m with r bounded away from 0, the fractional part of m/r is negligible. The paper should note the asymptotic qualifier.

**Verification by special cases:**
- r = 1, N = m: p(m,1) = m! / m^m. For m=1: p = 1. For m=2: p = 2!/4 = 1/2. Correct (birthday problem with 2 elements in 2 slots).
- r = 1/2, N = 2m: p(m,1/2) = (2m)! / ((2m)^m * m!). For m=1: p = 2!/2 = 1. Correct (1 element in 2 slots is always injective). For m=2, N=4: p = 4!/(16*2!) = 24/32 = 3/4. Check: P(no collision with 2 elements in 4 slots) = 4/4 * 3/4 = 3/4. Correct.

**Verdict: PASS.**

---

## 4. Theorem 3.3 (tex lines 494-543): Expected Coding Size (Space Complexity)

**Claim:** Expected bits/element = log2(e) - (1/r - 1) log2(1/(1-r)).

**This is the paper's central result. The proof has a known flaw that I examine in detail.**

### Step-by-step proof analysis

**Step 1 (lines 504-511):** Define Q ~ Geometric(p(m,r)). E[Q] = 1/p(m,r). **Correct.**

**Step 2 (lines 512-518):** "By Definition 3.1, the n-th trial uniquely maps to a bit string of length m = floor(log2 n). Thus, the expected bit length is given approximately by E[log2 Q] = log2(1/p(m,r))."

**THIS IS THE FLAWED STEP.** The paper equates E[log2 Q] with log2(E[Q]) = log2(1/p). By Jensen's inequality (log is concave):

    E[log2 Q] <= log2(E[Q]) = log2(1/p)

The inequality is strict for non-degenerate distributions. For Q ~ Geometric(p):

    E[log2 Q] = sum_{k=1}^{infty} log2(k) * p * (1-p)^{k-1}

This does not simplify to log2(1/p) in general.

**However, what the paper actually computes in the subsequent steps is not E[log2 Q] but rather log2(1/p)/m, and it claims this equals the bits/element.** Let me verify whether this gives the correct answer despite the flawed justification.

**Step 3 (lines 519-522):** Stirling's approximation: log2(n!) ~ n(log2(n) - log2(e)). **Standard; correct for large n.**

**Step 4 (lines 523-542):** Apply Stirling to compute log2(1/p(m,r)):

    log2(1/p) = m*log2(N) - log2(N!) + log2((N-m)!)

With Stirling:

    = m*log2(N) - [N*log2(N) - N*log2(e)] + [(N-m)*log2(N-m) - (N-m)*log2(e)]
    = m*log2(N) - N*log2(N) + N*log2(e) + (N-m)*log2(N-m) - (N-m)*log2(e)
    = m*log2(N) - N*log2(N) + (N-m)*log2(N-m) + m*log2(e)

Dividing by m (bits/element), with N = m/r:

    = log2(m/r) - (1/r)*log2(m/r) + (1/r - 1)*log2(m/r - m) + log2(e)
    = log2(m/r)*(1 - 1/r) + (1/r - 1)*log2(m(1/r - 1)) + log2(e)

The (1 - 1/r) coefficient is negative (since r < 1 implies 1/r > 1), and (1/r - 1) is positive. Let me expand:

    = (1 - 1/r)[log2(m) + log2(1/r)] + (1/r - 1)[log2(m) + log2(1/r - 1)] + log2(e)

The log2(m) terms: (1 - 1/r)*log2(m) + (1/r - 1)*log2(m) = [(1 - 1/r) + (1/r - 1)]*log2(m) = 0. **The m-dependent terms cancel.** This is the key mathematical fact.

What remains:

    = (1 - 1/r)*log2(1/r) + (1/r - 1)*log2(1/r - 1) + log2(e)
    = -(1/r - 1)*log2(1/r) + (1/r - 1)*log2(1/r - 1) + log2(e)
    = (1/r - 1)*[log2(1/r - 1) - log2(1/r)] + log2(e)
    = (1/r - 1)*log2((1/r - 1)/(1/r)) + log2(e)
    = (1/r - 1)*log2(1 - r) + log2(e)
    = -(1/r - 1)*log2(1/(1-r)) + log2(e)
    = log2(e) - (1/r - 1)*log2(1/(1-r))

**The algebra is correct.** The final formula depends only on r, not on m.

### Is the result correct despite the flawed proof technique?

Yes. The correct statement is: log2(1/p(m,r))/m -> log2(e) - (1/r - 1)*log2(1/(1-r)) as m -> infinity (via Stirling). And E[L]/m -> log2(1/p(m,r))/m as m -> infinity. The reason:

The actual encoding length is L = floor(log2 Q) where Q ~ Geometric(p). From the Appendix (Theorem A.3):

    E[L] = sum_{j=1}^{infty} q^{2^j - 1}

For small p (large m), q is close to 1, and the dominant terms of this series give E[L] ~ -log2(p) + O(1). More precisely, for Q ~ Geometric(p):

    E[floor(log2 Q)] ~ log2(1/p) as p -> 0

This is because floor(log2 Q) ~ log2(Q) for large Q, and Q concentrates near 1/p. The Bernoulli hash function paper handles this correctly by computing:

    E[L] <= E[log2 Q] <= log2(E[Q]) = -log2(p)  (upper bound by Jensen)
    E[L] >= E[log2 Q] - 1                          (since floor(x) >= x-1)
    E[log2 Q] -> -log2(p) as p -> 0

So E[L] = -log2(p) + O(1), giving E[L]/m = log2(1/p)/m + O(1/m).

### Notational errors in the proof

- **Line 512:** "m = floor(log2 n)" should be "BL(n') = floor(log2 n)". The variable m is already used for cardinality.
- **Line 526:** The LHS says E[Q] but the RHS is in bits. It should say E[BL(n')] or E[L].

**Verdict: RESULT CORRECT, PROOF FLAWED.** The proof takes log2 inside the expectation without justification (conflating E[log2 Q] with log2 E[Q]). The result is correct because log2(1/p)/m gives the correct leading-order behavior via Stirling, and E[L]/m -> log2(1/p)/m asymptotically. The proof should be rewritten along the lines of the Bernoulli hash function paper's space complexity proof, which correctly uses the bounding technique E[L] = -log2(p) + O(1).

---

## 5. Paragraph After Theorem 3.3: Entropy Discussion (tex lines 545-553)

**Claim (lines 545-553, not a formal theorem):** The entropy of Q equals the expected bit length E[log2 Q], confirming entropy-optimality.

This paragraph states H(Q) = (1/p - 1)*log2(1/(1-p)) + log2(1/p), and claims this "equals the expected bit length E[log2 Q] derived above."

**This is incorrect as stated.** H(Q) is the entropy of the geometric random variable Q, not the expected bit length of the encoding n'. The relevant quantities are:

- H(Q) = -(1-p)/p * log2(1-p) - log2(p)  (entropy of Q ~ Geometric(p))
- E[BL(n')] = E[floor(log2 Q)] = sum_{j=1}^{infty} q^{2^j-1}  (expected encoding length)

These are different. H(Q) is the minimum expected number of bits needed to encode Q losslessly (Shannon's source coding theorem). E[BL(n')] is the actual expected encoding length using the bijection n <-> n'. For the encoding to be optimal, we need E[BL(n')] to equal or approach the entropy of the *encoding* (not of Q).

The correct entropy to consider is H(n'), the entropy of the bit string n'. Since n' = Q' (the bijection maps Q to its bit-string representation), H(n') = H(Q) (bijections preserve entropy). But E[BL(n')] != H(Q) in general. The claim that the encoding is "entropy-optimal" requires H(n') = E[BL(n')], which means the encoding uses exactly as many bits as its entropy---i.e., it is incompressible.

**Verdict: The claim is conceptually on the right track but the formal argument is muddled.** See the detailed analysis under Theorem 3.5 below.

---

## 6. Theorem 3.5: Maximum Entropy Encoding (tex lines 555-567)

**Claim:** H(N) = E[BL(n')] = log2(e) - (1/r - 1)*log2(1/(1-r)) bits/element, which equals the information-theoretic lower bound.

**This is the paper's most important conceptual claim and the proof is insufficient.**

### What needs to be shown

For the in-place encoding to be "maximum entropy," the paper needs to establish that the bit string n' is incompressible---that is, each bit carries maximum information. Formally, this means:

(a) H(n') = E[BL(n')]

where H(n') is the entropy of the random bit string n' (not the entropy of its length N = BL(n')).

### Decomposing H(n')

By the chain rule of entropy:

    H(n') = H(BL(n')) + H(n' | BL(n'))

where:
- H(BL(n')) = H(N) is the entropy of the length
- H(n' | BL(n')) = E[H(n' | BL(n') = k)] is the conditional entropy

If, conditioned on BL(n') = k, the bit string n' is uniformly distributed over {0,1}^k, then:

    H(n' | BL(n') = k) = k

and therefore:

    H(n' | BL(n')) = E[BL(n')]

giving:

    H(n') = H(N) + E[BL(n')]

Wait---this gives H(n') > E[BL(n')] whenever H(N) > 0, which would mean the encoding requires *more* bits than its length. That seems contradictory. Let me reconsider.

Actually, the entropy H(n') should account for the fact that n' takes values in the union of {0,1}^k for all k >= 0. A bit string of length k is one of 2^k possible strings. The total number of possible values for n' is countably infinite. The entropy is:

    H(n') = -sum_{k=0}^{infty} sum_{b in {0,1}^k} Pr(n'=b) * log2(Pr(n'=b))

If conditioned on BL(n')=k, n' is uniform over {0,1}^k, then:

    Pr(n' = b) = Pr(BL(n')=k) / 2^k    for b in {0,1}^k

and the contribution from length-k strings is:

    -sum_{b in {0,1}^k} Pr(n'=b) * log2(Pr(n'=b))
    = -2^k * (Pr(N=k)/2^k) * log2(Pr(N=k)/2^k)
    = -Pr(N=k) * [log2(Pr(N=k)) - k]
    = -Pr(N=k)*log2(Pr(N=k)) + k*Pr(N=k)

Summing over k:

    H(n') = H(N) + E[N] = H(N) + E[BL(n')]

This is greater than E[BL(n')] by H(N). This is NOT a contradiction: the entropy H(n') measures the total information in n', which includes both the information in its length and the information in its content. The expected bit length E[BL(n')] is the expected number of bits in the encoding. For a variable-length code, having H(code) > E[length] is normal---the "extra" entropy comes from the length itself being informative.

### What "maximum entropy" actually means here

The correct interpretation of "maximum entropy encoding" is:

**Conditional on its length, each bit of the encoding is uniformly distributed and independent.** That is, H(n' | BL(n') = k) = k for all k.

This is the key property that makes the encoding incompressible: you cannot compress the content bits (they are already maximum entropy), and the length is determined by the search process (which is optimal by construction).

### Does the paper prove this?

No. The proof (lines 563-567) says:

> "The entropy of a geometric random variable with success probability p is H(Q) = ... Since the bijection between n and n' preserves information, and the expected bit length equals the entropy, the encoding is optimal."

This argument has multiple problems:

1. "The bijection between n and n' preserves information" is true but does not establish conditional uniformity of n' given its length.

2. "The expected bit length equals the entropy" conflates E[BL(n')] with H(n'). As shown above, H(n') = H(N) + E[N] > E[N].

3. The appeal to "Shannon's source coding theorem" is not directly applicable. Shannon's theorem says you cannot encode a source with fewer bits than its entropy; it does not say that a particular encoding achieves maximum entropy.

### The correct proof

The conditional uniformity follows from the random oracle assumption:

1. Under the random oracle model, each trial n independently succeeds with probability p. The success/failure of trial n is independent of all other trials (because hash(x' # n') involves distinct inputs for distinct n).

2. The algorithm selects the first n that succeeds. Given that BL(n') = k (equivalently, the first success occurs at some trial Q with floor(log2 Q) = k), the specific trial Q is uniformly distributed among the set of trials in {2^k, ..., 2^{k+1}-1} that succeed.

Wait, that is not quite right either. Given BL(n') = k, we know: (a) all 2^k - 1 trials with bit length < k failed; (b) the first success among the 2^k trials of bit length k is Q. Conditional on (a), the 2^k length-k trials are independent Bernoulli(p) variables. The first success among them is uniformly distributed over those that succeed. If exactly one succeeds (which happens with probability 2^k * p * (1-p)^{2^k - 1} when p is small), then n' is determined. If multiple succeed, n' is the lexicographically first one (since the algorithm searches in order).

**Actually, the algorithm searches trials in order n = 1, 2, 3, ..., not randomly within each length level.** So given BL(n') = k, the bit string n' is the smallest trial in {2^k, ..., 2^{k+1}-1} that succeeds. This is NOT uniformly distributed over {0,1}^k. It is biased toward smaller values.

**However**, the mapping n <-> n' maps trials 2^k through 2^{k+1}-1 to bit strings 0...0 through 1...1 (all k-bit strings). Each trial succeeds independently with probability p. The first success among trials 2^k, 2^k+1, ..., 2^{k+1}-1 follows a geometric distribution (first success) over {0, 1, ..., 2^k-1}, which means the bit string n' = (Q - 2^k) in binary has a geometric distribution over {0,1}^k. This is NOT uniform.

**Wait---I need to reconsider the mapping.** By Definition 3.1 (the bijection), the mapping is:

    n = 2^k + sum_{j=1}^{k} 2^{k-j} * b_j

where n' = b_1...b_k. So n = 2^k maps to 0...0, and n = 2^{k+1}-1 maps to 1...1.

Given BL(n') = k, n ranges from 2^k to 2^{k+1}-1. The algorithm picks the smallest n in this range that succeeds. Since each trial succeeds independently with probability p, the index of the first success within this range (offset from 2^k) follows Geometric(p) truncated to {0,...,2^k-1}. This is NOT uniform over {0,...,2^k-1}.

**This means the encoding is NOT maximum entropy conditioned on its length.** The first few bit strings (smaller n values) of each length are more likely to be selected than the last few.

**BUT WAIT**: if 2^k * p << 1 (which is the typical case for the first successful length k), then with high probability exactly 0 or 1 trials of length k succeed. Conditioned on at least one succeeding, the probability of any particular trial being the first success is approximately p (for each trial in the range), and the probability that the first success is trial n is approximately:

    p * (1-p)^{n-2^k} ~ p  (for small n-2^k relative to 1/p)

Since 2^k << 1/p (because 2^k ~ 1/p only for the first successful length), the variation across the range is approximately:

    p * (1-p)^{2^k} ~ p * e^{-p*2^k}

For the *first* length k that has a success, the expected number of successes at that length is approximately 2^k * p. Let us denote f_k = 2^k * p.

From the PMF p_N(k) = q^{2^k - 1}(1 - q^{2^k}), the probability of length k is concentrated around the value of k where q^{2^k} ~ 1/2, i.e., 2^k ~ -1/ln(q) ~ 1/p. So f_k = 2^k * p ~ 1 for the typical length.

When f_k ~ 1, there is approximately 1 success among the 2^k trials of length k, and the first success is approximately uniformly distributed among all 2^k trials (since (1-p)^{2^k} ~ e^{-1} ~ 0.37, which is O(1)). The distribution is geometric with parameter p over a range of size 2^k ~ 1/p, which is approximately uniform for the leading fraction of trials but decays for the tail.

**The conditional distribution is NOT exactly uniform.** It is approximately geometric with rate p over {0,...,2^k-1}. The entropy of this distribution is approximately log2(1/p) ~ k, but strictly less than k bits. The deficit is O(1) bits per string.

### Assessment

The maximum entropy claim, as stated in the paper ("the encoding achieves maximum entropy"), is **approximately but not exactly correct**. The encoding is approximately maximum entropy in the sense that:

    H(n' | BL(n')=k) ~ k - O(1)

for the typical value of k. The deficit is O(1) bits total (not per element), which is negligible per element as m -> infinity. But the claim as stated (an equality, not an asymptotic approximation) is **not rigorously established**.

The Bernoulli hash function paper handles this more carefully by noting "conditioned on having length n, the particular b in {0,1}^n that is found is uniformly distributed (the search order is randomized within each length level)" --- but this requires randomizing the search order within each length level, which the crypto-perf-hash paper's Algorithm 1 does NOT do (it searches sequentially).

**Verdict: PARTIAL FAIL.** The maximum entropy claim is approximately correct (and exactly correct if the search within each length level is randomized) but the proof is insufficient. The paper should either (a) modify Algorithm 1 to randomize the search within each length level, then the conditional uniformity argument works exactly; or (b) state the result as an asymptotic approximation.

---

## 7. Theorem (tex lines 587-596): Minimal PHF Achieves 1.44 bits/element

**Claim:** Setting r -> 1 in the space formula gives log2(e) ~ 1.44 bits/element.

**Proof walkthrough:**

    lim_{r->1} [log2(e) - (1/r - 1)*log2(1/(1-r))]

Let u = 1-r -> 0. Then 1/r - 1 = u/(1-u) -> u. And log2(1/(1-r)) = log2(1/u). The second term becomes:

    (u/(1-u)) * log2(1/u) -> u * log2(1/u) -> 0  as u -> 0

since x*log2(1/x) -> 0 as x -> 0 (by L'Hopital: lim_{x->0} log2(1/x)/(1/x) = lim_{x->0} -1/(x*ln2) / (-1/x^2) = lim x/(ln2) = 0).

Therefore the limit is log2(e) = 1/ln(2) ~ 1.4427.

**Correct.**

**Verdict: PASS.**

---

## 8. Corollary (tex line 598-600): Lower Bound for Arbitrary Load Factor

**Claim:** The lower bound for perfect hash functions with load factor r in (0,1] is given by log2(e) - (1/r - 1)*log2(1/(1-r)).

**This follows directly from Theorem 3.3** (if we accept that result). The argument is: Algorithm 1 finds the smallest (minimum trial index) PHF for any load factor r with uniformly distributed sets. By the optimality of the geometric search (searching in order of increasing bit length), no encoding can achieve a smaller expected bit length for this distribution of sets.

**Caveat:** The claim is about the lower bound for all PHF encodings, not just the one produced by Algorithm 1. The argument implicitly uses the fact that any PHF encoding must specify which of the ~ 1/p possible perfect hash functions was selected, requiring at least log2(1/p) bits of information. This is an information-theoretic argument that should be made explicit.

**Verdict: PASS (but the argument could be more explicit about why the formula gives a lower bound for all encodings, not just Algorithm 1's encoding).**

---

## 9. Postulate 3.1: The 1.44 bits/element Lower Bound

**Claim (tex lines 577-585):** The theoretical lower bound for minimal PHFs has an expected coding size of approximately 1.44 bits/element.

**This is labeled as a "Postulate" but it is a well-known theorem.** The information-theoretic lower bound for MPHFs is derived from a counting argument: the number of minimal perfect hash functions for m elements is m!, and log2(m!) ~ m*log2(m) - m*log2(e) bits are needed to specify one. The per-element lower bound is log2(m!/m^m)/m -> log2(e) ~ 1.44 (by Stirling). This appears in Mehlhorn (1982) and is standard.

**Verdict: NOT AN ERROR, but labeling it as a "Postulate" is misleading.** It should be cited as a theorem (with reference to Mehlhorn 1982 or Fredman-Komlos 1984) or proved as a corollary of the paper's own analysis.

---

## 10. Theorem A.2 (tex lines 883-925): PMF of Random Bit Length

**Claim:** p_N(n|m,r) = q^{2^n - 1}(1 - q^{2^n}).

**Proof walkthrough:**

Step 1: For N = n (bit length equals n), all strings of length < n must fail. There are 2^0 + 2^1 + ... + 2^{n-1} = 2^n - 1 such strings. Each fails independently with probability q. Probability: q^{2^n - 1}. **Correct.**

Step 2: At least one string of length n must succeed. There are 2^n such strings. The probability that ALL fail is q^{2^n}. The complement (at least one succeeds) is 1 - q^{2^n}. **Correct.**

Step 3: By independence (each trial outcome is independent under the random oracle assumption), the joint probability is the product: q^{2^n-1} * (1 - q^{2^n}). **Correct.**

Step 4: Verify this is a valid PMF. Sum over n = 0 to infinity:

    S = sum_{n=0}^{infty} q^{2^n - 1}(1 - q^{2^n})
      = sum_{n=0}^{infty} (q^{2^n - 1} - q^{2^{n+1} - 1})

This is a telescoping sum:

    S = (q^0 - q^1) + (q^1 - q^3) + (q^3 - q^7) + (q^7 - q^15) + ...

Wait, let me recheck. For n=0: q^{2^0 - 1} - q^{2^1 - 1} = q^0 - q^1 = 1 - q.
For n=1: q^{2^1 - 1} - q^{2^2 - 1} = q^1 - q^3 = q - q^3.
For n=2: q^{2^2 - 1} - q^{2^3 - 1} = q^3 - q^7.

Sum: (1 - q) + (q - q^3) + (q^3 - q^7) + ... = 1 - lim_{n->inf} q^{2^n - 1} = 1 - 0 = 1. **Correct** (since 0 < q < 1 implies q^{2^n} -> 0 superexponentially).

**Verdict: PASS. Clean and correct.**

---

## 11. Theorem A.3 (tex lines 936-956): Expected Bit Length from PMF

**Claim:** E[N] = sum_{j=1}^{infty} q^{2^j - 1}.

**Proof walkthrough:**

    E[N] = sum_{j=0}^{infty} j * p_N(j)
         = sum_{j=0}^{infty} j * (q^{2^j - 1} - q^{2^{j+1} - 1})

The j=0 term vanishes (multiplied by 0). For j >= 1:

Expand the first few terms:
- j=1: 1*(q^1 - q^3)
- j=2: 2*(q^3 - q^7)
- j=3: 3*(q^7 - q^15)

Rearranging by grouping the q^{2^j - 1} terms:

The coefficient of q^1 = q: appears in j=1 term as +1*q, and in j=0 term as -0*q. Net: 1*q = q.
The coefficient of q^3: appears in j=2 term as +2*q^3, and in j=1 term as -1*q^3. Net: (2-1)*q^3 = q^3.
The coefficient of q^7: appears in j=3 term as +3*q^7, and in j=2 term as -2*q^7. Net: (3-2)*q^7 = q^7.

General pattern: coefficient of q^{2^j - 1} for j >= 1 is j - (j-1) = 1.

Therefore:

    E[N] = q + q^3 + q^7 + q^15 + ... = sum_{j=1}^{infty} q^{2^j - 1}

**Correct.** The rearrangement is valid because all terms are non-negative and the series converges absolutely (q < 1 so q^{2^j} -> 0 superexponentially fast).

**Numerical verification:** The paper claims (line 957) that this agrees with the closed-form formula from Theorem 3.3. For large m, both should give approximately log2(e) - (1/r-1)*log2(1/(1-r)) bits per element. This is not proved in the paper but is stated as a numerical observation. It would be stronger to prove the asymptotic equivalence analytically, by showing:

    (1/m) * sum_{j=1}^{infty} q^{2^j - 1} -> log2(e) - (1/r-1)*log2(1/(1-r))  as m -> infinity

where q = 1 - p(m,r). This requires the approximation sum_{j=1}^{infty} q^{2^j-1} ~ -log2(q)/ln(2) ~ -log2(1-p)/ln(2) ~ p/ln(2) for small p... actually this is the integral approximation of the sum, which is not straightforward. The Stirling-based derivation provides the asymptotic equivalence via a different route.

**Verdict: PASS.**

---

## 12. Section 5, Theorem: Post-Composition with Injection

**Claim (tex lines 791-801):** Let g : Y -> Z be injective, h_A^r a PHF, and |Z| = (1+alpha)|Y|. Then g o h_A^r is a PHF h_A^{r'} where r' = r/(1+alpha).

**Proof walkthrough:**

1. h_A^r is injective on A (by definition of PHF). g is injective. Therefore g o h_A^r is injective on A. **Correct** (composition of injections is injective).

2. Load factor calculation:
   r = |A|/|Y|, so |Y| = |A|/r.
   |Z| = (1+alpha)|Y| = (1+alpha)|A|/r.
   r' = |A|/|Z| = |A| / ((1+alpha)|A|/r) = r/(1+alpha). **Correct.**

**Issues:**
- The theorem assumes the PHF is surjective (by Assumption 2.1). If h_A^r is surjective onto Y and g is injective from Y to Z, then g o h_A^r is NOT surjective onto Z (its image is g(Y) which is a proper subset of Z when alpha > 0). So the composition is a PHF but not a surjective one. The paper's Assumption 2.1 (surjectivity) would be violated for the composed function. This should be noted.

**Verdict: PASS (with the minor caveat about surjectivity).**

---

## 13. Corollary: Permutation Equivalence Class Ratio

**Claim (tex lines 809-814):** The ratio of permutation-equivalent PHFs to all possible functions is |Y|! / |Y|^|X|.

**Verification:** A single PHF generates |Y|! related PHFs under post-composition with permutations of Y. The total number of functions X -> Y is |Y|^|X|. The ratio is |Y|!/|Y|^|X|.

**Issue:** This ratio does not have an obvious interpretation. It is not the probability that a random function is permutation-equivalent to a given PHF (that would require knowing how many equivalence classes there are). The ratio |Y|!/|Y|^|X| is just the fraction of all functions that lie in one particular permutation equivalence class. For this to be meaningful, we need |Y|! <= |Y|^|X|, which requires |X| >= |Y| (otherwise there are more permutations than total functions).

For a PHF with m = |A| elements in a codomain of size N = |Y| >= m, we need |X| >= N for the ratio to be at most 1. If X = {0,1}* (the typical case), |X| is infinite and the ratio is 0. So this corollary is meaningful only for finite X.

**Verdict: PASS (but the utility of this ratio is questionable for the paper's setting where X = {0,1}*).**

---

## 14. Section 4: Two-Level Construction Analysis

### 14.1. Coupon Collector Analysis (tex lines 741-759)

**Claim:** Processing buckets in order, with bucket j having success probability p_j = (m-j+1)/m, the total expected trials are E(T) = m * H_{m-1}.

**Issue:** The paper describes a two-level construction where the set is partitioned into k buckets and each bucket is processed independently. But the "coupon collector" analysis on lines 747-759 does not match the two-level algorithm (Algorithm 2). Let me trace the discrepancy:

Algorithm 2 partitions X into k buckets X[1],...,X[k] (each of size ~m/k). For each bucket, it searches for a trial index n such that:
- All elements in the bucket map to distinct hashes (birthday problem within the bucket)
- None of those hashes collide with previously assigned hashes

The analysis on lines 747-759 instead considers processing elements one at a time (not buckets), with probability p_j = (m-j+1)/m that the j-th element does not collide with the previous j-1 elements. This is a single-level coupon-collector analysis, not the multi-level analysis that Algorithm 2 requires.

**For Algorithm 2, the correct analysis per bucket l is:**

Let m_l = |X[l]| (bucket size). The success probability for bucket l (trial succeeds) requires:
(a) All m_l elements in bucket l map to distinct values: probability P^N_{m_l}/N^{m_l} (birthday)
(b) None of those m_l values collide with the s already-assigned values: probability C(N-s, m_l)/C(N, m_l) when exactly m_l slots must be chosen from N-s free slots

These are combined multiplicatively. The paper does not compute this correctly.

**The claim that "the expected space per bucket is log2(e) ~ 1.44 bits" (line 761)** is plausible for the per-bucket trial index encoding (since each bucket's search is geometric with some probability, and the encoding cost is logarithmic in 1/p_bucket), but this is not proved.

### 14.2. Variance Formula (tex lines 763-770)

**Claim:** Var(T) = sum_{j=2}^{m} (j-1)/((m-j+1)^2) * m^2.

**Derivation check:** With p_j = (m-j+1)/m, T_j ~ Geometric(p_j), Var(T_j) = (1-p_j)/p_j^2.

    1 - p_j = 1 - (m-j+1)/m = (j-1)/m
    p_j^2 = ((m-j+1)/m)^2 = (m-j+1)^2/m^2

So:

    Var(T_j) = ((j-1)/m) / ((m-j+1)^2/m^2) = (j-1)*m / (m-j+1)^2

The paper writes sum_{j=2}^{m} (j-1)/(m-j+1)^2 * m^2. This has an extra factor of m. The correct formula is:

    Var(T) = sum_{j=2}^{m} (j-1)*m / (m-j+1)^2

not

    Var(T) = sum_{j=2}^{m} (j-1)*m^2 / (m-j+1)^2

**Verdict: ERROR in the variance formula (extra factor of m).** Additionally, the coupon-collector framing does not match the two-level algorithm. The section conflates two different analyses.

---

## Summary Table

| Location | Claim | Verdict | Severity |
|----------|-------|---------|----------|
| Thm after Def 3.5 | PH models a PHF | **PASS** | Minor notation issues (k vs N, variable name collision) |
| Thm after Alg 1 | PHF output is uniform | **PASS** | Minor (codomain indexing {1,...,N} vs {0,...,N-1}) |
| Thm 3.2 equiv | Success probability p(m,r) | **PASS** | Clean |
| Thm 3.3 equiv | Space bound formula | **RESULT CORRECT, PROOF FLAWED** | **Medium**: E[log2 Q] != log2(E[Q]); should use asymptotic bounding |
| Lines 545-553 | Entropy equals expected bit length | **INCORRECT AS STATED** | **Medium**: confuses H(Q), H(n'), E[BL(n')] |
| Thm 3.5 | Maximum entropy encoding | **PARTIAL FAIL** | **Medium-High**: conditional uniformity not established; actually false for deterministic search order; approximately correct if search is randomized within length levels |
| Thm (1.44) | r->1 gives 1.44 bits/elem | **PASS** | Clean |
| Corollary | Formula is a lower bound for all r | **PASS** | Could be more explicit about why |
| Postulate 3.1 | 1.44 bits/elem lower bound | **PASS** (content) | Labeling as "Postulate" is misleading |
| Thm A.2 | PMF of bit length | **PASS** | Clean and correct |
| Thm A.3 | Expected bit length series | **PASS** | Clean and correct |
| Thm 5.1 | Post-composition with injection | **PASS** | Minor (surjectivity caveat) |
| Cor 5.1 | Permutation equivalence ratio | **PASS** | Questionable utility for infinite X |
| Sec 4 analysis | Two-level construction | **MULTIPLE ERRORS** | **Medium**: variance formula wrong (extra factor of m); coupon-collector analysis does not match Algorithm 2; 1.44 bits/bucket claim unproved |

---

## Critical Path for Revision

### Must Fix (correctness issues)

1. **Theorem 3.3 proof:** Replace the E[log2 Q] = log2(E[Q]) step with a proper asymptotic argument. Recommended approach: follow the Bernoulli hash function paper's technique---bound E[L] between E[log2 Q] - 1 and log2(E[Q]) using Jensen and the floor function, then show both bounds converge to -log2(p)/m = the closed-form formula.

2. **Theorem 3.5 (maximum entropy):** Either (a) modify Algorithm 1 to randomize the search within each length level (then conditional uniformity holds exactly), or (b) state the result as "approximately maximum entropy" with the deficit being O(1) bits total. Provide the actual argument: conditional on length k, the bit string is (approximately) uniformly distributed over {0,1}^k.

3. **Lines 545-553:** Rewrite the entropy discussion to correctly distinguish H(Q), H(n'), H(N), and E[BL(n')]. The relevant identity is H(n') = H(N) + E[N] (conditional uniformity given length).

4. **Section 4 variance formula:** Fix the extra factor of m. The correct expression is sum_{j=2}^{m} (j-1)*m/(m-j+1)^2, not sum_{j=2}^{m} (j-1)*m^2/(m-j+1)^2.

### Should Fix (clarity and rigor)

5. **Line 512:** Change "m = floor(log2 n)" to "BL(n') = floor(log2 n)".

6. **Line 526:** Change E[Q] to E[BL(n')] on the LHS.

7. **Section 4 coupon collector:** Either (a) rewrite the analysis to match Algorithm 2's bucket-level structure, or (b) explicitly state that the analysis is for a simplified single-level variant and explain how it differs from Algorithm 2.

8. **Postulate 3.1:** Replace with a cited theorem or derive from the paper's own analysis.

9. **Asymptotic qualifiers:** The Stirling-based derivation is asymptotic in m. State explicitly that the space formula holds "as m -> infinity" and that for finite m, there are O(1/m) correction terms.
