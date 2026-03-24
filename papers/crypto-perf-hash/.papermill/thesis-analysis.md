# Thesis Analysis: Cryptographic Perfect Hash Functions

## Main Claim

A cryptographic perfect hash function---constructed by exhaustive search over random oracle outputs---achieves the information-theoretic lower bound on expected space complexity while its in-place encoding is a maximum-entropy random bit string. The expected space is:

```
log2(e) - (1/r - 1) log2(1/(1-r))  bits/element
```

which yields 1.44 bits/element for minimal perfect hash functions (r = 1).

## What Is Novel

1. **Random oracle framing of PHF space bounds.** The paper analyzes perfect hash functions where the underlying hash is modeled as a random oracle (Definition 3.2), and derives exact space complexity from first principles: the search over salts is geometric, and the salt *is* the encoding. This gives a clean derivation of the 1.44 bits/element lower bound as a limiting case of a more general formula parameterized by load factor r.

2. **Entropy-optimal in-place encoding.** The paper argues that the trial index n, encoded via the standard bit-string bijection (Definition 3.1), is itself the encoding of the perfect hash function. Since the first success of a geometric search has entropy equal to E[log2 Q], the in-place encoding is claimed to be entropy-optimal (Theorem 3.5). This connects space optimality to Shannon's source coding theorem.

3. **General load-factor formula.** The space bound log2(e) - (1/r - 1)log2(1/(1-r)) parameterized by r generalizes the well-known 1.44 bits/element result for MPHFs to arbitrary load factors. As r -> 0, the bound approaches 0 bits/element, which is consistent with having many more slots than elements.

4. **Algebraic composition theory (Section 5).** Post-composition with injections preserves the perfect hash property with a predictable load factor transformation r' = r/(1+alpha). Permutation equivalence classes group PHFs into families of size |Y|!. This provides a formal algebraic framework for constructing PHF families from primitives.

5. **Two-level construction analysis (Section 4).** The coupon-collector analysis of the two-level construction shows expected trials of m*H_{m-1} per bucket, with each bucket's trial index independently geometric, achieving the same 1.44 bits/element per bucket on average.

## Connection to Cipher Map Encoding

In the trapdoor computing framework, a **cipher map** is a total function on bit strings implementing a trapdoor approximation of a latent function. The trusted machine encodes values into opaque bit strings; the untrusted machine evaluates cipher maps blindly.

The cryptographic perfect hash function provides the **encoding mechanism** for cipher maps:

- **Set membership encoding:** A cipher map representing set membership uses a PHF to map set elements to slot indices. The PHF's space bound (1.44 bits/element for MPHF) determines the encoding cost parameter mu = H(Y) in the cipher map framework.

- **Obliviousness:** The maximum entropy property ensures the encoding reveals no information about the set elements beyond what is accessible through the defined interface, which is the confidentiality requirement for untrusted-machine computation.

- **Composability:** The algebraic composition results (Section 5) directly support cipher map composability. If cipher maps compose, the underlying PHFs must compose predictably, which the injection post-composition and permutation equivalence theorems guarantee.

- **Relationship to Bernoulli model:** The Bernoulli hash function paper (companion in ~/github/bernoulli/papers/bernoulli-hash-function/) uses the same geometric-search-over-salts construction but for approximate sets/maps (with false positive rate epsilon). The crypto-perf-hash paper addresses the *exact* case (perfect hashing, no false positives among set members), which corresponds to the eta = 0 (zero error) case in the cipher map correctness parameter.

## Key Relationship Between the Two Papers

| Property | crypto-perf-hash | bernoulli-hash-function |
|----------|-----------------|------------------------|
| Error model | Perfect (no FP among members) | Bernoulli (FPR = epsilon) |
| Space bound | log2(e) - (1/r-1)log2(1/(1-r)) b/elem | -log2(epsilon) + mu b/elem |
| Entropy | Maximum entropy in-place encoding | Maximum entropy salt encoding |
| Construction | Geometric search, exponential time | Geometric search, exponential time |
| Practical variant | Two-level (Algorithm 2) | Adaptive threshold (polynomial time) |
| Load factor | r in (0,1] | Implicit via epsilon |

The crypto-perf-hash paper can be seen as the r-parameterized *exact* case, while the bernoulli-hash-function paper is the epsilon-parameterized *approximate* case. Together they span the design space for hash-based encodings in the trapdoor computing framework.
