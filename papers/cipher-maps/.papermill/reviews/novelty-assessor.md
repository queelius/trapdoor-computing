# Novelty Assessor Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Claimed Contributions

The paper claims the following contributions (extracted from abstract and introduction):

1. **Definition of cipher maps** with four formal properties (totality, representation uniformity, correctness, composability)
2. **Three construction layers** (undefined injection, noise closure, multiple representations) explaining why each property exists
3. **Three concrete instantiations**: HashSet, entropy map, trapdoor Boolean algebra
4. **Composition theorem** with proof ($\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$)
5. **Trusted/untrusted machine model** formalization
6. **Singular Hash Map** achieving the information-theoretic lower bound of $-\log_2 \varepsilon + H(Y)$ bits/element
7. **Space lower bound** proof
8. **Bayesian deniability proposition** for encrypted search application

## Assessment by Contribution

### Contribution 1: Cipher map definition (Moderate novelty)
The abstraction of "total function on bit strings as encrypted function approximation" is a genuine conceptual contribution. It packages several known ideas (hash-based data structures, trapdoor functions, homophonic substitution) into a clean four-property framework. The novelty is in the packaging and formalization, not in the individual ingredients. This is comparable to how the concept of "streaming algorithm" packages several algorithmic ideas into a unified model.

**Differentiator from prior work**: The key distinction from structured encryption (Chase & Kamara, 2010) is the use of information-theoretic parameters ($\eta, \varepsilon, \delta$) rather than simulation-based security. The key distinction from Bloom filters is the abstraction from membership to arbitrary functions. Both distinctions are genuine.

### Contribution 2: Construction layers (Low-moderate novelty)
The three-layer decomposition (undef, noise, cipher) is conceptually helpful but the paper itself acknowledges it is "conceptual scaffolding" and not a formal algebraic decomposition. Whether the layers satisfy monad laws is listed as an open question. This reduces the contribution to an organizational framework rather than a formal result.

### Contribution 3: Three instantiations (Moderate novelty)
Showing that three different constructions (membership, function, set algebra) all satisfy the same four-property framework is the primary evidence that the abstraction is useful. The individual constructions are known (Bloom filters, perfect hashing, bitwise set operations), but the unified presentation under one framework is the contribution. The trapdoor Boolean algebra instantiation is the most interesting, since it shows how approximate Boolean algebra over hash values fits the cipher map model.

### Contribution 4: Composition theorem (Low novelty, high value)
The formula $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$ is the standard error accumulation formula for independent events. It appears in reliability theory, Bayesian networks, and other domains. The novelty is not in the formula but in (a) proving it holds for cipher map composition under stated assumptions and (b) connecting it to the Bernoulli model. The proof is correct and the connection is valuable.

### Contribution 5: Trust model (Low-moderate novelty)
The trusted/untrusted machine model is clearly presented but relatively thin as a formal contribution. The definitions of $T$ and $U$ (Definitions 6.1, 6.2) are lists of capabilities. The security guarantees (Table 3) are stated informally and the honest limitation about correlation leakage is good but not formalized. This section would benefit from a formal theorem about what $U$ can and cannot learn.

### Contribution 6-7: Singular Hash Map and lower bound (Moderate novelty)
The space lower bound $-\log_2 \varepsilon + H(Y)$ bits/element decomposes into membership and value components. Both components are known individually (the membership bound is classical; the value bound is Shannon's source coding theorem). The contribution is the clean decomposition and the proof that the two components are additive. The SHM construction achieving this bound is a concrete algorithm that combines prefix-free coding with seed search.

### Contribution 8: Bayesian deniability (Low novelty)
This is a straightforward application of Bayes' rule to the cipher map correctness parameter. The formula is standard. The contribution is the interpretation: connecting $\eta$ to deniability in the encrypted search context. This is a minor but nice observation.

## Overall Novelty Assessment

The paper's primary contribution is the **unifying abstraction**: showing that Bloom filters, perfect hash functions, and bitwise set operations are all instances of a single framework (cipher maps with four properties). This is a genuine intellectual contribution -- it provides a vocabulary and parameter space for reasoning about a class of hash-based cryptographic-adjacent data structures that has not been unified before.

The paper does NOT claim to:
- Provide a new security notion (it explicitly distances itself from simulation-based security)
- Achieve better asymptotic bounds than known constructions
- Introduce fundamentally new constructions

What it provides:
- A clean abstraction layer that connects data structures, cryptography, and information theory
- Formal proofs of composition and space optimality within this abstraction
- Honest accounting of limitations (marginal uniformity only, no joint distribution hiding, equality pattern leakage)

**Significance**: Moderate. The paper would be well-suited for a theory-oriented venue that values clean abstractions (e.g., STACS, ISAAC, or a journal like TCS or Algorithmica). It is likely too thin on formal security guarantees for a top crypto venue (CCS, CRYPTO) and too abstract for a systems venue.

## Key Differentiation Gaps

1. The paper should cite and explicitly compare to structured encryption (Chase & Kamara, 2010), which is the most similar existing framework.
2. The paper should clarify whether the four-property framework is strictly more general than, a specialization of, or orthogonal to structured encryption.
3. The encoding granularity principle (Section 9) is potentially the most novel conceptual contribution but is underdeveloped -- it deserves a theorem rather than just a proposition.
