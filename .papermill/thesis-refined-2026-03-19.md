# Refined Thesis: Cryptographic Perfect Hash Functions

**Date:** 2026-03-19
**Paper:** Cryptographic perfect hash functions: A theoretical analysis on space efficiency and algebraic composition

---

## The Novelty Question

The central result---1.44 bits/element for minimal perfect hash functions---is well established. It appears in Fredman and Komlos (1984), Mehlhorn (1982), and is textbook material. The paper cannot claim this as a contribution. What, then, is genuinely new?

### Assessment of Each Candidate Contribution

**1. The general r-parameterized space formula**

The formula log2(e) - (1/r - 1)log2(1/(1-r)) bits/element, parameterized by load factor r in (0,1], is the paper's strongest standalone result. While the technique (counting injections over birthday-problem combinatorics + Stirling) is standard, the explicit closed-form expression as a function of r does not appear in the standard references (FKS, Mehlhorn, CHD). The 1.44 result is the r=1 limit of this more general formula.

**Verdict: Modest but genuine contribution.** The formula itself is derivable by anyone who tries, but having the clean closed form stated and proved is useful. The key insight that the m-dependent terms cancel (leaving a formula depending only on r) is worth stating explicitly.

**2. The entropy-optimality framing**

The claim that the in-place encoding (trial index as bit string) achieves maximum entropy is the paper's most interesting conceptual contribution---but the proof is insufficient (see proof verification). The correct argument requires showing: (a) conditioned on length n, the successful trial is uniformly distributed over {0,1}^n; (b) therefore each bit of the encoding is uniformly distributed and independent (conditional on length); (c) therefore the encoding is incompressible.

The Bernoulli hash function paper (companion) makes the same claim with a cleaner proof structure (Theorem in entropy.tex: "conditioned on having length n, the particular b in {0,1}^n that is found is uniformly distributed"). The crypto-perf-hash paper should adopt this cleaner formulation.

**Verdict: Genuine contribution in principle, but the proof needs significant strengthening.** The observation that the trial index *is* the encoding, and that this encoding is maximum entropy, connects PHF space bounds to Shannon's source coding in an illuminating way. However, until the proof is rigorous, the claim is aspirational.

**3. The algebraic composition framework (Section 5)**

Post-composition with injections (load factor transforms as r' = r/(1+alpha)) and permutation equivalence classes are correctly stated. However, the development is thin: one theorem, one corollary, three examples. There is no characterization of the algebraic structure (e.g., the symmetric group acts on PHFs by post-composition; the set of PHFs over a fixed A with injective post-compositions forms a category). The composition of two PHFs (h_B o h_A) is not addressed, which is the operation relevant to cipher map composability.

**Verdict: Underdeveloped.** The results are correct but too elementary to constitute a significant contribution on their own. They are useful as supporting infrastructure for the cipher map framework.

**4. Connection to cipher map encoding (mu parameter)**

The paper does not make this connection at all---"oblivious sets and maps" is mentioned once in passing (line 573). Yet this is arguably the paper's most important role in the author's research program. The cryptographic PHF provides the encoding mechanism for cipher maps: the PHF's space bound determines the encoding cost parameter mu = H(Y), and the maximum entropy property ensures the encoding reveals no information about set elements.

**Verdict: Absent from the paper but should be the framing.** This paper is the "encoding layer" of the trapdoor computing stack.

---

## Recommended Framing

### Option A: Standalone Paper (Current Framing, Refined)

**Thesis:** The space complexity of cryptographic perfect hash functions (under the random oracle model) is exactly log2(e) - (1/r - 1)log2(1/(1-r)) bits/element as a function of load factor r, and the in-place encoding achieves maximum entropy. The formula generalizes the known 1.44 bits/element bound for minimal PHFs to arbitrary load factors, and the entropy-optimality establishes that no encoding of the same expected length can carry more information about the hash function.

**Strengths of this framing:**
- Self-contained, understandable without the trapdoor computing context
- The r-parameterized formula and its clean derivation are the core contribution
- The entropy argument, once properly proved, is a nice information-theoretic insight

**Weaknesses:**
- The 1.44 result is well-known; the generalization to arbitrary r is a modest extension
- The algebraic composition section is too thin to be a significant contribution
- Recent practical MPHFs (RecSplit, SicHash, ShockHash) achieve near-1.44 bits with polynomial construction time, making the exponential-time theoretical construction less interesting
- The paper competes poorly with practical MPHF papers

### Option B: Hash Construction Behind Cipher Maps (Recommended)

**Thesis:** The cryptographic perfect hash function is the encoding primitive for cipher maps in the trapdoor computing framework. Its space bound log2(e) - (1/r - 1)log2(1/(1-r)) bits/element determines the encoding cost parameter mu in cipher maps, and its maximum entropy property guarantees that the encoding reveals no information beyond what is accessible through the defined interface. The algebraic composition of PHFs (post-composition with injections, permutation equivalence) directly supports cipher map composability.

**Reframing the paper as "the hash construction behind cipher maps" would:**

1. **Provide a clear motivation.** The paper currently lacks a strong "why should anyone care?" answer. The cipher map connection provides it: this is the encoding layer that makes trapdoor computing space-efficient.

2. **Make the algebraic composition section purposeful.** Currently Section 5 is a collection of correct but unmotivated observations. In the cipher map context, these composition results directly support the composability property of cipher maps (one of the four defining properties).

3. **Position it relative to the Bernoulli hash function paper.** The crypto-perf-hash paper addresses exact membership (r-parameterized, no false positives), while the BHF paper addresses approximate membership (epsilon-parameterized, with false positives). Together they span the design space for hash-based encodings:

   | Paper | Error model | Space bound | Cipher map parameter |
   |-------|------------|-------------|---------------------|
   | crypto-perf-hash | Exact (no FP) | log2(e) - (1/r-1)log2(1/(1-r)) | mu (encoding cost, eta=0) |
   | bernoulli-hash-fn | Approximate (FPR=epsilon) | -log2(epsilon) + mu | epsilon (noise), mu (value encoding) |

4. **Give the entropy result real teeth.** In the cipher map context, maximum entropy is not just an information-theoretic curiosity---it is a *security requirement*. The untrusted machine must not be able to infer anything about the encoded values from the encoding. Maximum entropy guarantees incompressibility, which is necessary for confidentiality.

5. **Make the exponential construction time a feature, not a bug.** In cipher map construction, the trusted machine performs encoding (including PHF construction) once, and the untrusted machine evaluates the cipher map many times. Exponential construction time is acceptable if the resulting encoding is space-optimal and entropy-maximal. This is analogous to how one-time pad construction is trivial but its security properties are optimal.

### Recommended Restructuring (Option B)

1. **Introduction:** Motivate with trapdoor computing / cipher maps. The encoding of a cipher map requires: (a) space efficiency (minimizing mu), (b) maximum entropy (confidentiality), (c) composability (cipher maps compose). State that this paper analyzes the hash construction that achieves all three.

2. **Preliminaries:** Condense current Section 2 heavily (1 page max). Define PHF, load factor, random oracle.

3. **The Cryptographic PHF Construction:** Algorithm 1 + the success probability (current Theorem 3.2). Keep clean.

4. **Space Complexity:** The r-parameterized formula (current Theorem 3.3), with a *fixed* proof that avoids the E[log Q] / log E[Q] conflation. State the 1.44 bits/element result as a corollary (r=1 limit).

5. **Maximum Entropy:** Rigorous proof (strengthen current Theorem 3.5). Make the security interpretation explicit: the encoding is incompressible and reveals no information about the set.

6. **Algebraic Composition and Cipher Map Composability:** Expand current Section 5 with explicit connection to cipher map composition. Add: pre-composition with injective encoders (domain adaptation); composition of two PHFs; the category of cipher map encodings under composition.

7. **Two-Level Construction:** Current Section 4, cleaned up (fix the variance formula, clarify bucket-level vs element-level analysis). Frame as the practical instantiation.

8. **Conclusion:** Explicit connection to the cipher map framework and the Bernoulli hash function paper. State the design space for hash-based cipher map encodings.

---

## Summary of Genuine Contributions (After Revision)

Ranked by significance:

1. **The r-parameterized space formula** and its clean derivation showing m-cancellation (the bits/element depends only on r, not on m). This is the core mathematical result.

2. **The maximum entropy property** of the in-place encoding, with its security interpretation for cipher map confidentiality. This is the core conceptual result, but requires a rigorous proof.

3. **The connection to cipher map encoding cost** (mu parameter). This positions the paper within the trapdoor computing research program.

4. **The algebraic composition framework** for PHFs, supporting cipher map composability. This is supporting infrastructure, not a standalone contribution.

5. **The PMF of the random bit length** and the expected bit length series (Appendix). These are correct and clean but shared with the Bernoulli hash function paper. One paper should cite the other; factor out or cross-reference.

---

## What Is NOT Novel (Acknowledge Explicitly)

- The 1.44 bits/element lower bound for MPHFs (Mehlhorn 1982, Fredman-Komlos 1984)
- The birthday-problem probability P^N_m / N^m
- The geometric search construction (universal in the random oracle model)
- The telescoping sum proof technique for the PMF
- The coupon collector analysis (Section 4)

## Unresolved Questions

1. Is the r-parameterized formula truly novel, or has it appeared in some form in the PHF literature (e.g., in the context of non-minimal PHFs)? A more thorough literature search is needed, particularly in Mehlhorn (1982) and the FKS paper.

2. Does the maximum entropy property hold exactly for finite m, or only asymptotically? The current proof is unclear on this point. The Bernoulli hash function paper's proof (conditional uniformity of the salt given its length) appears to hold for all m, which would be a stronger result.

3. Can the algebraic composition framework be extended to a full categorical treatment? If PHFs under post-composition with injections form a category, what are the functors to the category of cipher maps? This would substantially strengthen the algebraic contribution.
