# Iteration Review: Cryptographic Perfect Hash Functions (Post-Fix)

**Paper:** `paper/paper.tex`
**Date:** 2026-03-20
**Reviewer:** Claude Opus 4.6
**Scope:** Second-pass review after 3 fixes applied (Jensen's inequality, max entropy qualification, two-level variance)

---

## 1. Fix Consistency Propagation

### 1.1. Theorem 3.3 space bound: log2(E[Q])/m propagation

**Severity: MAJOR**

The proof of Theorem 3.3 (lines 512--545) now correctly uses `log2(E[Q])/m` instead of `E[log2 Q]`. However, the informal paragraph at lines 548--556 still confuses the quantities:

> "This entropy equals the expected bit length log2(E[Q])/m derived above (per element), confirming that the geometric coding of trial indices is entropy-optimal."

This sentence equates H(Q) (entropy of the geometric random variable Q) with log2(E[Q])/m (a ratio involving the expected trial count). These are different quantities with different units:
- H(Q) is in bits (total, not per element)
- log2(E[Q])/m is in bits/element

The correct chain of reasoning should be:
1. E[BL(n')] = sum q^{2^j-1} (from Theorem A.3)
2. E[BL(n')]/m ~ log2(1/p)/m asymptotically (from the bounding argument)
3. The formula log2(e) - (1/r-1)log2(1/(1-r)) is log2(1/p)/m after Stirling

The paragraph attempts to bridge Theorem 3.3 and Theorem 3.5 but does so incorrectly. The quantities H(Q), H(N), E[BL(n')], and log2(E[Q])/m are all different; the paragraph treats them as interchangeable.

**Status: NOT ADDRESSED by the 3 fixes.** This was flagged in the original proof verification (Section 5, lines 545--553) as "confuses H(Q), H(n'), E[BL(n')]" and remains unfixed.

**Recommendation:** Rewrite lines 548--556 to clearly distinguish:
- H(Q) = entropy of trial number Q ~ Geometric(p)
- H(N) = entropy of bit length N = floor(log2 Q)
- E[N] = E[BL(n')] = expected encoding length (from Appendix Theorem A.3)
- log2(E[Q])/m = the quantity computed in the Theorem 3.3 proof

State explicitly that E[N]/m ~ log2(E[Q])/m ~ H(Q)/m all converge to the same limit as m -> infinity, but they are not identical for finite m.

### 1.2. Maximum entropy theorem: Algorithm 1 consistency

**Severity: MAJOR**

Theorem 3.5 (lines 563--572) now correctly states that maximum entropy requires randomized intra-level search. The remark (lines 579--581) explains the deterministic search deficit.

However, **Algorithm 1 (lines 619--657) was not updated** to reflect this. Algorithm 1 still searches deterministically (`For n <- 1 To infinity`), which means the encoding it produces does NOT achieve maximum entropy -- only the O(1)-bit weaker version. The paper now has a theorem that requires randomized search and an algorithm that does deterministic search, with no algorithm for the randomized variant.

This creates a gap: the strongest claim (exact maximum entropy) has no corresponding algorithm in the paper.

**Options:**
1. Add a variant of Algorithm 1 that randomizes within each bit-length level (as the BHF paper does in its construction algorithms, which explicitly "draw a bit string of length n uniformly at random from {0,1}^n without replacement")
2. Weaken Theorem 3.5 to only claim the deterministic result (within O(1) bits), removing the randomized search prerequisite
3. Keep both claims but add a brief algorithmic description of the randomized variant

Option 3 is recommended -- it preserves the strongest result while keeping Algorithm 1 as the simple presentation.

### 1.3. Two-level variance: downstream conclusions

**Severity: MINOR**

The variance formula (line 786) is now correct: `sum (j-1)*m / (m-j+1)^2 = O(m^2)`. The statement at line 788 ("This variance is O(m^2)") is consistent. No downstream conclusions rely on the variance beyond this asymptotic claim, so the fix propagates cleanly.

However, the text still says "the actual number of trials can vary significantly for any particular set" (line 788). With Var(T) = O(m^2) and E[T] = O(m ln m), the standard deviation is O(m) while the mean is O(m ln m), giving a coefficient of variation O(1/ln m) -- the variation is actually moderate relative to the mean. The qualitative claim could be more precise.

---

## 2. Remaining Technical Issues

### 2.1. Entropy discussion (lines 548--556)

**Severity: MAJOR** (see Section 1.1 above)

Not addressed by Fix 1. The paragraph still conflates H(Q) with E[BL(n')]/m. The equation at line 550:

    H(Q) = -(1-p)/p * log2(1-p) - log2(p)

is correct as the entropy of Q ~ Geometric(p). But the sentence "This entropy equals the expected bit length log2(E[Q])/m derived above" is wrong:
- H(Q) is a total quantity (not per element)
- H(Q) != log2(E[Q]) in general (they are approximately equal for geometric distributions with small p, but this needs to be stated as an asymptotic result, not an equality)

### 2.2. Section 5 (algebraic composition): underdeveloped

**Severity: SUGGESTION**

Section 5 is correct but thin. Three specific improvements would strengthen it:

1. **Pre-composition theorem.** The paragraph after Theorem 3.1 (lines 416--418) informally notes that pre-composing with an injective encoder preserves perfect hashing. This should be formalized as a theorem in Section 5, parallel to the post-composition theorem. This is especially important because the paper's own construction uses pre-composition (concatenating x' with n').

2. **Composition of two PHFs.** What happens when you compose h_B o h_A where both are PHFs over different sets? Under what conditions is the result a PHF? This is directly relevant to cipher map composability (one of the four defining properties in the trapdoor computing framework).

3. **Group action structure.** The permutation equivalence class (Section 5.2) describes a group action of Sym(Y) on PHFs. Stating this explicitly (the symmetric group acts on PHFs by post-composition, with orbits being the equivalence classes) would turn a collection of observations into a structural result.

### 2.3. Missing recent MPHFs in related work

**Severity: MINOR**

The Prior Art (Section 1) cites FKS (1984), CHD (2009), BPZ (2007), and cuckoo hashing (2004). It does not cite any post-2010 practical MPHFs. Key missing references:

| Construction | Space (bits/elem) | Year | Reference |
|-------------|-------------------|------|-----------|
| RecSplit | ~1.56 | 2020 | Esposito, Graf, Vigna |
| SicHash | ~1.50 | 2023 | Lehmann, Sanders |
| ShockHash | ~1.489 | 2023 | Lehmann, Sanders |

These are directly relevant because they approach the 1.44 lower bound with polynomial construction time, which contextualizes the paper's exponential-time construction. The paper should acknowledge that the 1.44 bound is now nearly achievable in practice.

---

## 3. Paper Quality and Completeness

### 3.1. Missing conclusion section

**Severity: MAJOR**

The paper still has no conclusion. It ends with the Appendix (probability mass function derivation), which is mathematically clean but gives the paper no closure. A conclusion should:

1. Summarize the three contributions (r-parameterized space formula, maximum entropy property, algebraic composition)
2. Connect to the trapdoor computing program (the PHF provides the encoding layer for cipher maps; its space bound determines the mu parameter)
3. State the relationship to the Bernoulli hash function paper
4. Identify open questions (e.g., tighter finite-m bounds, categorical treatment of PHF composition)

### 3.2. Postulate 3.1: should be a theorem

**Severity: MINOR**

Postulate 3.1 (lines 592--599) states the 1.44 bits/element lower bound as a "postulate." This is a well-known theorem (Mehlhorn 1982, Fredman-Komlos 1984). Moreover, the paper *derives it* as a corollary of its own Theorem 3.3 (the r -> 1 limit). Calling it a postulate is misleading -- it suggests the result is assumed rather than proved.

**Recommendation:** Replace with either:
- A cited theorem: "Theorem (Mehlhorn 1982). The information-theoretic lower bound..."
- A definition/notation: "The lower bound is known to be log2(e) ~ 1.44 [citation]; we derive this as a consequence of our more general formula."

The current Theorem 3.6 (lines 601--610) already proves the result, making Postulate 3.1 both misleading and redundant.

### 3.3. N notation overloading

**Severity: MINOR**

The symbol N is used for two different things:
- **Section 3:** N = ceil(m/r), the codomain size of the PHF (lines 363, 635)
- **Appendix:** N = sample_bit_length(m,r), the random variable for the bit length of the encoding (Definition A.1, line 889)

Additionally, Theorem 3.5 (line 567) uses N in the equation H(N) = E[BL(n')], referring to the bit-length random variable, while N in the surrounding context (Sections 3-4) means the codomain size.

**Recommendation:** Rename the bit-length random variable to L (as the BHF paper does: "L = floor(log2 Q)"). This eliminates the overloading. The change affects Definition A.1, Theorem A.2, Theorem A.3, Figure A.1, and Theorem 3.5.

### 3.4. Other minor issues (carried over from first review, still present)

| Line | Issue | Severity |
|------|-------|----------|
| 161 | `|A|` should be `|\mathbbm{A}|` for consistency | MINOR |
| 295 | "The bit set {0,1} is denoted by {0,1}" -- tautology | MINOR |
| 376 | "rated-distorted" -- undefined term | MINOR |
| 421--427 | Two redundant paragraphs introducing Algorithm 1 | MINOR |
| 587 | Citations `[phf,pmf]` for "oblivious sets and maps" -- these papers are about hash tables, not oblivious computing | MINOR |
| 761 | Section 4 coupon-collector analysis describes element-by-element processing but Algorithm 2 processes buckets; these are different analyses | MAJOR |

---

## 4. Relationship to Bernoulli Hash Function Paper

### 4.1. Shared machinery

The two papers share the following results with identical or near-identical proofs:

| Shared Element | crypto-perf-hash | bernoulli-hash-function |
|---------------|------------------|------------------------|
| PMF of bit length | Theorem A.2: q^{2^n-1}(1-q^{2^n}) | Theorem 7 (Sec 6): identical |
| Expected bit length series | Theorem A.3: sum q^{2^j-1} | Appendix: identical |
| Telescoping sum proof | Appendix proof | Appendix proof: identical |
| Maximum entropy claim | Theorem 3.5 (qualified) | Theorem 6 (Sec 6): cleaner |
| Geometric search construction | Algorithm 1 | Algorithms 1-3 (more sophisticated) |

### 4.2. What's unique to THIS paper

1. **The r-parameterized space formula.** The BHF paper's space bound is `-log2(epsilon) + mu` bits/element, parameterized by false positive rate epsilon and value encoding cost mu. This paper's formula `log2(e) - (1/r-1)log2(1/(1-r))` is parameterized by load factor r. These are different parameterizations of different problems:
   - crypto-perf-hash: exact membership (no false positives), variable load factor
   - BHF: approximate membership (controlled false positive rate), no load factor concept

2. **The m-cancellation observation.** The fact that the space formula depends only on r (not on m) after Stirling simplification is specific to the birthday-problem combinatorics of perfect hashing. The BHF paper's space bound is trivially m-independent because p = epsilon^m / 2^{m*mu} gives log2(1/p)/m = -log2(epsilon) + mu directly.

3. **The algebraic composition framework.** The BHF paper has set operations (intersection, union convergence) but not algebraic composition of hash functions. Section 5's post-composition with injections and permutation equivalence classes are unique to this paper.

4. **The two-level construction** (Section 4) has no counterpart in the BHF paper.

### 4.3. What's unique to the BHF paper

1. **Generalized acceptance predicates** (equality, threshold, adaptive threshold)
2. **False positive/negative rate parameterization** and the epsilon-FNR tradeoff
3. **The price of FPR certainty** theorem (adaptive vs fixed threshold)
4. **Cardinality estimation** from encoding length
5. **Bernoulli map construction** (key-value, not just key membership)
6. **Significantly more polished proofs** -- the BHF paper correctly uses the bounding technique (Jensen + floor bounds) for the space proof, which this paper should adopt

### 4.4. Should they be merged or kept separate?

**Recommendation: Keep separate, but cross-reference explicitly and factor shared proofs.**

The papers address genuinely different problems:
- **crypto-perf-hash:** Perfect hash functions (collision-free, r-parameterized load factor, no false positives)
- **BHF:** Approximate membership/lookup (epsilon-parameterized, with false positives/negatives)

Merging would create an unfocused paper. However:

1. **The shared PMF/expected-length/telescoping machinery should be cited, not re-derived.** One paper should be primary for this material and the other should cite it. The BHF paper has cleaner proofs, so the crypto-perf-hash paper should cite the BHF paper for the PMF derivation (or at minimum cross-reference it). Alternatively, both could cite a shared technical lemma.

2. **The maximum entropy proof should be aligned.** The BHF paper's proof (Theorem 6, entropy.tex lines 10--29) is cleaner: it explicitly states "conditioned on having length n, the particular b in {0,1}^n that is found is uniformly distributed (the search order is randomized within each length level)." The crypto-perf-hash paper's Theorem 3.5 now states the same condition but with a less clean proof.

3. **Cross-references needed:**
   - crypto-perf-hash should cite BHF for the shared geometric-search framework and note that the BHF paper handles the randomized search correctly
   - BHF should cite crypto-perf-hash for the r-parameterized formula (as the exact-membership special case)
   - Both should note the design space: exact membership (this paper) vs approximate membership (BHF)

---

## 5. Top Improvements for Publishability

### Ranked by impact:

**1. Fix the entropy discussion (lines 548--556) and align with Theorem 3.5.**
Severity: MAJOR. The paragraph between Theorem 3.3 and Theorem 3.5 is the conceptual bridge of the paper -- it connects space complexity to entropy-optimality. Currently it is incorrect (confuses H(Q) with E[BL(n')]/m). Rewrite to clearly distinguish the quantities and state the asymptotic equivalence.

**2. Add a conclusion section.**
Severity: MAJOR. The paper currently ends with the Appendix. A conclusion that frames the contributions, connects to the trapdoor computing program, and relates to the BHF paper would significantly improve the paper's impact and readability.

**3. Add or reference a randomized-search algorithm variant.**
Severity: MAJOR. Theorem 3.5 (the paper's most conceptually interesting result) requires randomized intra-level search, but no algorithm in the paper implements this. Either add Algorithm 1' (randomized variant) or strengthen the reference to the BHF paper's construction which does this correctly.

**4. Reclassify Postulate 3.1 and resolve the Section 4 analysis mismatch.**
Severity: MINOR + MAJOR respectively. Replace the postulate with a cited theorem. Fix the Section 4 analysis to match Algorithm 2 (bucket-level, not element-level).

**5. Cite recent practical MPHFs and rename the overloaded N variable.**
Severity: MINOR. Both are straightforward edits that would improve the paper's positioning in the literature and internal consistency.

---

## Summary

| Category | Critical | Major | Minor | Suggestion |
|----------|----------|-------|-------|------------|
| Fix propagation | 0 | 2 (entropy paragraph, algo consistency) | 1 (variance wording) | 0 |
| Remaining technical | 0 | 1 (entropy discussion) | 1 (missing MPHFs) | 1 (Section 5 depth) |
| Quality/completeness | 0 | 2 (no conclusion, Section 4 mismatch) | 3 (postulate, N overload, minor edits) | 0 |
| BHF relationship | 0 | 0 | 0 | 3 (cross-ref, factor proofs, align max-entropy) |
| **Total** | **0** | **5** | **5** | **4** |

The three applied fixes are mathematically correct and verified (per the 2026-03-20 verification report). The main remaining issues are: (a) the entropy discussion paragraph that was not addressed by the fixes, (b) the algorithm gap for the randomized-search maximum entropy claim, and (c) structural completeness (missing conclusion, Postulate 3.1, Section 4 analysis mismatch). No critical errors remain.
