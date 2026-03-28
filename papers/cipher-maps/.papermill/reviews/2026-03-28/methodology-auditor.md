# Methodology Auditor Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper is a formalism paper: definitions, theorems, proofs. There are no experiments. Methodological evaluation focuses on the formal framework's soundness, the appropriateness of the random oracle model, and the completeness of the parameter analysis.

## Findings

### MAJOR: Random oracle model dependency is pervasive but the implications are not discussed

- **Location**: Section 3.1 (Preliminaries, line 195-200), and throughout
- **Quoted text**: "Throughout, $h : \{0,1\}^* \to \{0,1\}^n$ denotes a cryptographic hash function modeled as a random oracle"
- **Problem**: The paper correctly defines the ROM in Section 3.1 (this was fixed from the prior review). However, the paper never discusses the implications of the ROM assumption. All four properties depend on the ROM:
  - Totality depends on hash outputs being uniform (ROM)
  - Representation uniformity depends on hash values being independent (ROM)
  - Correctness analysis assumes independent Bernoulli trials per element (ROM)
  - Composition analysis assumes independence across maps (ROM)

  In the standard model (real hash functions), these properties degrade. How much? The paper does not say. For SHA-256, the independence assumption is well-supported empirically, but the paper should at least note that all results are in the ROM and that practical instantiation requires hash functions with good pseudorandom properties.
- **Severity**: MAJOR (for PoPETs; moderate for a theory venue)
- **Confidence**: HIGH
- **Suggestion**: Add a paragraph discussing ROM vs. standard model: "All results in this paper are stated in the random oracle model. Practical instantiation uses a cryptographic hash function such as SHA-256, for which the ROM assumptions (uniformity, independence) are well-supported empirically but not provable. The key ROM-dependent results are: [list]. Extending to the standard model (e.g., via universal hash families) is an open question."

### MINOR: No adversary model -- what can the adversary do?

- **Location**: Section 5 (Trust Model)
- **Problem**: The trust model defines what $T$ and $U$ can do, but it does not define an adversary model. Is $U$ honest-but-curious? Malicious? Can $U$ choose which queries to evaluate? Can $U$ refuse to return results? Can $U$ observe timing or access patterns? The paper implicitly assumes honest-but-curious $U$ (evaluates faithfully, observes passively), but this is never stated.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Add: "We model $U$ as honest-but-curious: $U$ evaluates $\hat{f}$ correctly on all inputs and returns all results, but attempts to learn information about $f$, $X$, or $Y$ from its observations."

### MINOR: Bucketed construction (Prop 6.2) assumes uniform bucket sizes

- **Location**: Proposition 6.2 (lines 800-817)
- **Quoted text**: "Each bucket has $m/k$ elements (in expectation)"
- **Problem**: The proof assumes each bucket has exactly $m/k$ elements, but with hash-based bucketing the sizes follow a balls-into-bins distribution. For $m$ elements and $k$ buckets, the maximum bucket size is $\Theta(m/k + \log k / \log \log k)$ with high probability. The construction time is dominated by the largest bucket, not the average. The stated formula $T(k) = k \cdot (1/\bar{\alpha})^{m/k}$ is the expected total across all buckets assuming equal sizes, but the actual expected time should account for variance.
- **Severity**: MINOR (the formula is correct in expectation; the issue is that variance matters for practical construction time)
- **Confidence**: HIGH
- **Suggestion**: Add a note: "In practice, bucket sizes vary. The expected construction time is dominated by the largest bucket, which has size $\Theta(m/k + \log k)$ with high probability, giving a construction time multiplicatively worse by $\exp(O(\log k))$."

### MINOR: Algorithm 1 hash construction $h(\ell) \oplus h(x)$ -- is XOR sufficient?

- **Location**: Algorithm 1 (line 665)
- **Quoted text**: "$\text{hash} \gets h(\ell) \oplus h(x)$"
- **Problem**: The construction uses XOR of two independent hash values. Under the ROM, $h(\ell) \oplus h(x)$ is uniform for any fixed $\ell$ and varying $x$, which is correct. But in practice, if $h$ has any weaknesses (e.g., related-key attacks), XOR could introduce correlations. The standard construction for parametric hashing is $h(\ell \| x)$ (concatenation), which is simpler and avoids any XOR-related issues. The paper uses $h(\ell \| x)$ in the entropy cipher map description (Section 6.5, line 860: "$h(x \| s)$") but $h(\ell) \oplus h(x)$ in Algorithm 1. This inconsistency is confusing.
- **Severity**: MINOR
- **Confidence**: MEDIUM
- **Suggestion**: Unify the hash construction. Either use $h(\ell \| x)$ everywhere (simpler, standard) or explain why XOR is preferred in Algorithm 1.

### MINOR: The paper conflates "cipher map" as abstraction and as data structure

- **Location**: Throughout, but especially Sections 3 and 6
- **Problem**: A cipher map is defined as a tuple $(\hat{f}, \text{enc}, \text{dec}, s)$ -- an abstract mathematical object. But the batch construction section treats it as a concrete data structure with specific space complexity. The lower bound (Theorem 6.1) applies to "any data structure representing an approximate map," which is broader than cipher maps. The space optimality (Theorem 6.2) applies to the specific batch construction. The paper sometimes blurs the line between the abstract definition and the concrete instantiation.
- **Severity**: MINOR
- **Confidence**: MEDIUM
- **Suggestion**: Add a clarifying sentence when transitioning from the abstract framework to the concrete construction: "The following results concern the batch construction specifically; the abstract cipher map definition admits other instantiations with different space-time trade-offs."

### Methodology Assessment

| Aspect | Rating | Notes |
|---|---|---|
| Formal definitions | Good | Clear, precise, consistent notation |
| Proof correctness | Good | All proofs verified (see logic-checker) |
| ROM justification | Adequate | Now defined; implications not discussed |
| Adversary model | Weak | Implicit honest-but-curious; not formalized |
| Parameter analysis | Good | Clear decomposition of $(\eta, \varepsilon, \mu, \delta)$ |
| Reproducibility | N/A | No experiments to reproduce |
| Completeness | Adequate | All claimed results are proved; some gaps in practical analysis |
