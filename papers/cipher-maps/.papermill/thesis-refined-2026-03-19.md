# Thesis Refinement: Cipher Maps Unified
Date: 2026-03-19

## Current Thesis (as stated in paper)

From the abstract:

> We present cipher maps, a comprehensive theoretical framework unifying oblivious function approximation, algebraic cipher types, and Bernoulli data models. Building on the mathematical foundations of cipher functors that lift monoids into cipher monoids, we develop oblivious Bernoulli maps that provide privacy-preserving function approximation with controllable error rates. These maps satisfy strong obliviousness conditions while maintaining space-optimal implementations. We introduce the Singular Hash Map, achieving -log2(epsilon) + mu bits per element asymptotically --- matching information-theoretic lower bounds. Our framework bridges three key concepts: (1) algebraic cipher types that define homomorphic transformations over monoids, (2) Bernoulli approximations that model probabilistic errors in computation, and (3) entropy-based constructions that achieve space-optimal oblivious implementations. We formalize the cipher functor as a proper functor on the category of monoids, develop encoding set theory characterizing the security--efficiency design space, and prove that nested cipher compositions yield predictable error rates. Applications span encrypted search, privacy-preserving data structures, secure multi-party computation, and differential privacy systems.

From the introduction:

> This paper introduces cipher maps --- a comprehensive theoretical framework that bridges algebraic cipher types, Bernoulli approximation models, and oblivious data structures to provide privacy-preserving function approximation with provable guarantees.

## Problems with Current Thesis

### 1. Wrong framing: "oblivious" is undefined in the paper

The abstract claims cipher maps "satisfy strong obliviousness conditions" but the paper never defines obliviousness formally. This was identified as M1 (the most critical open issue). The formalism document (cipher-map-formalism.md) correctly reframes the paradigm around four concrete properties (totality, representation uniformity, correctness, composability) under a trusted/untrusted machine model. The paper still uses the old "oblivious" language without grounding it.

### 2. The "unification" claim is overstated and vague

The paper claims to "unify" algebraic cipher types, Bernoulli models, and oblivious data structures. But the actual connection between these three is thin:
- The algebraic cipher functor section (Section 2) is largely self-contained and disconnected from the Singular Hash Map construction (Section 5).
- The Bernoulli model section (Section 3) is a summary of known ideas with no new results.
- The "connections" section (Section 7) asserts connections (Theorem 4.1, Proposition 7.1, Theorem 7.3) but proves them weakly or not at all.

The real unification is in the formalism document: cipher maps are total functions on bit strings that approximate latent functions, with four measurable properties. The three "things being unified" are actually three construction strategies for the same abstraction.

### 3. False claims of novelty in well-established areas

The abstract and related work make overreaching claims:
- "Our cipher functors provide a more general algebraic framework that encompasses but is not limited to traditional FHE" -- this is false. FHE provides computational security for arbitrary computation; the cipher functor construction here provides no computational security at all (it relies on information-theoretic properties of hashing).
- Claims about MPC, OT, PIR in Section 8 are hand-waving with no formal results.
- The category-theoretic "functor" claim is technically correct but trivial once you note it operates on the quotient monoid, where decode is an isomorphism.

### 4. The actual contribution is buried

The genuine novelty -- that you can build space-optimal total functions on bit strings that approximate arbitrary latent functions, with privacy deriving from one-way hashing and representation uniformity rather than computational hardness -- is never stated clearly. Instead, it is obscured by grandiose claims about "unifying" disparate fields.

### 5. The four-property framework is absent

The formalism document's main insight -- that cipher maps are characterized by four orthogonal properties (totality, representation uniformity, eta-correctness, composability) arising from three construction layers (undef, noise, cipher) -- does not appear in the paper at all. This is the actual structural contribution.

### 6. Applications section is content-free

Section 8 is a bulleted list of buzzwords (MPC, OT, PIR, differential privacy) with no formal results, no constructions, and no evidence that cipher maps provide anything useful in these areas. This undermines credibility.

## Genuine Contributions

Ranked by significance:

### 1. The cipher map abstraction with four properties (HIGH -- currently missing from paper)

**What it is**: A cipher map is a total function on bit strings that approximates a latent function known only to a trusted party. It is characterized by four measurable properties:
- **Totality**: defined on all inputs; out-of-domain inputs produce random-looking output
- **Representation uniformity** (delta-bounded): cipher values are delta-close to uniform in total variation distance
- **Correctness** (eta-bounded): in-domain elements decode correctly with probability >= 1 - eta
- **Composability**: composition of cipher maps has predictable error eta_total = 1 - (1-eta_f)(1-eta_g)

**Why it matters**: This is a clean abstraction that captures what Bloom filters, entropy maps, and trapdoor boolean algebras have in common. The four properties are independent (a construction can satisfy some without others), measurable (each has a concrete parameter), and sufficient (they characterize what the untrusted machine can and cannot learn).

**This is the paper's real thesis.** It is currently absent.

### 2. The composition theorem (HIGH -- present but poorly motivated)

**What it is**: Theorem 7.5 / Theorem 3.1 in the formalism. Cipher maps compose with predictable error: eta_{g o f} = 1 - (1 - eta_f)(1 - eta_g). For chains of m maps, eta_total = 1 - prod(1 - eta_i).

**Why it matters**: This is the key result enabling trapdoor computing as a paradigm -- you can chain cipher maps on the untrusted machine and bound the end-to-end error. The derivation from the noisy AND gate analysis (formalism Section 3.1) is elegant and the independence assumption is honestly characterized.

**Status in paper**: Present as Theorem 7.5 with a correct proof. But it is buried in Section 7 and its significance is not explained.

### 3. Space optimality of the Singular Hash Map (MEDIUM -- present)

**What it is**: The SHM achieves -log2(epsilon) + H(Y) bits per element, matching the information-theoretic lower bound when eta = 0.

**Why it matters**: Establishes that the cipher map abstraction is not just conceptually clean but also practically achievable at optimal cost.

**Status in paper**: Present as Theorem 6.1 + Theorem 6.2 + Corollary 6.1. The proofs need some repair (M8: independence argument in Step 3) but the results are fundamentally correct.

### 4. Three construction strategies as instances (MEDIUM -- partially present)

**What it is**: HashSet, entropy map, and trapdoor boolean algebra are all instances of the cipher map abstraction, with different parameter trade-offs. HashSet is the simplest (membership only, no representation uniformity). Entropy map is the most general (arbitrary functions, optimal space). Trapdoor boolean algebra supports algebraic operations (union, intersection, complement) but with degrading accuracy.

**Why it matters**: Demonstrates the abstraction's generality and provides a taxonomy for comparing constructions.

**Status in paper**: The three constructions appear but are not cleanly presented as instances of a common abstraction. The formalism document (Section 2) does this properly.

### 5. Trusted/untrusted machine model (LOW-MEDIUM -- currently missing)

**What it is**: The formalism's Section 5: two machines, one holding the trapdoor (enc, dec, seed), the other holding only the cipher map (a total function on bit strings). What each can and cannot do.

**Why it matters**: Makes precise what "privacy" means in this context. Not ORAM, not FHE, not differential privacy -- it is information-theoretic privacy from one-way hashing plus representation uniformity.

**Status in paper**: Absent. The paper vaguely gestures at "obliviousness" without defining the adversary model.

### 6. Construction layers (undef/noise/cipher) (LOW -- currently missing)

**What it is**: The three orthogonal type transformations from formalism Section 1.2 that produce the four properties.

**Why it matters**: Explains *why* each property exists and makes the abstraction less arbitrary.

**Status in paper**: Absent.

### Non-contributions (things the paper claims that are not genuinely novel)

- **Cipher functor as functor on Mon**: Technically correct but trivial once you work on the quotient monoid. The lifted operation is just "decode, compute, re-encode." This is not a deep categorical result.
- **Encoding set theory**: The definitions (complete, generating, minimal) are standard algebraic concepts applied to a new setting. The "security-efficiency tradeoff" (Proposition 2.1) is informal and not proved.
- **Bernoulli model framework**: Section 3 summarizes known ideas from the blog posts. No new theorems.
- **Applications**: Section 8 has no formal results. The claimed connections to FHE, MPC, OT, PIR, and differential privacy are unsupported.

## Refined Thesis

**Claim**: Cipher maps -- total functions on bit strings that approximate latent functions through one-way hashing -- are characterized by four independent, measurable properties (totality, representation uniformity, correctness, composability) that compose predictably: chaining m cipher maps yields end-to-end correctness 1 - prod(1 - eta_i), and space-optimal constructions achieving -log2(epsilon) + H(Y) bits per element exist.

**Novelty**:
1. The four-property abstraction that captures what Bloom filters, entropy maps, and trapdoor boolean algebras have in common.
2. The composition theorem with honest treatment of the independence assumption.
3. The information-theoretic space bound realized by the Singular Hash Map.
4. The trusted/untrusted machine model as a precise adversary model for hash-based privacy.

**Evidence needed**:
1. Formal definitions of all four properties with concrete parameters (from formalism Section 1.3).
2. Proof that three concrete constructions satisfy (or fail to satisfy) each property with specific parameter values (from formalism Section 2).
3. Proof of the composition theorem with explicit statement of the independence assumption (from formalism Section 3).
4. Proof of the information-theoretic lower bound and that SHM matches it (already in paper Sections 6.1-6.2, needs repair).
5. Formal statement of the trusted/untrusted model and what the four properties guarantee against the untrusted machine (from formalism Section 5).

## Thesis Variants

### Variant A: Theory of Computing / Information Theory venue (e.g., IEEE Trans. Information Theory, SODA)

**Title**: Cipher Maps: Space-Optimal Approximation of Hidden Functions Through Total Functions on Bit Strings

**Pitch**: We define cipher maps as total functions on bit strings that approximate latent functions, characterize them by four properties with concrete information-theoretic parameters, prove composition with predictable error accumulation, and show the Singular Hash Map achieves information-theoretic optimal space. Three constructions from the literature (Bloom filters, entropy maps, trapdoor boolean algebras) are cleanly captured as instances.

**Strength**: Clean formalism, provable bounds, concrete constructions. The information-theoretic angle is strong.

**Weakness**: The novelty bar at top venues requires comparison with the broader probabilistic data structure literature (especially succinct/compressed data structures). Must demonstrate the abstraction provides insight beyond what was already known.

### Variant B: Cryptography / Privacy venue (e.g., CCS, PETS)

**Title**: Trapdoor Computing: A Framework for Privacy-Preserving Function Evaluation Through One-Way Hashing

**Pitch**: We introduce the trapdoor computing paradigm where a trusted machine holds a one-way trapdoor and an untrusted machine evaluates opaque total functions on bit strings. Cipher maps provide four measurable guarantees against the untrusted machine: totality (no error signals), representation uniformity (frequency analysis bounded), eta-correctness (controllable error), and composability (predictable error accumulation). We give the precise adversary model, characterize what is and is not hidden (marginal uniformity only, joint correlations may leak), and prove space optimality.

**Strength**: Honest adversary model, explicit limitations (Section 4 of formalism: encoding granularity, marginal-only uniformity). Distinguishes cleanly from ORAM, FHE, and DP.

**Weakness**: The privacy model is weaker than standard cryptographic definitions (no computational security, no simulation-based proof). Must be framed as a complementary paradigm for a different threat model.

### Variant C: Systems / Data Structures venue (e.g., VLDB, SIGMOD, ESA)

**Title**: A Unified Abstraction for Space-Optimal Probabilistic Data Structures with Privacy Properties

**Pitch**: Bloom filters, entropy maps, and trapdoor boolean algebras all compute approximate functions whose domain is hidden behind one-way hashing. We provide a unified abstraction (cipher maps) that captures their common structure, proves they compose with predictable error, and identifies the information-theoretic space bound they share. The abstraction guides the design of new constructions by making the four key properties explicit and independently tunable.

**Strength**: Practical framing, connects to well-known data structures, constructive.

**Weakness**: Must include experimental evaluation showing the abstraction leads to better designs or implementations.

## Recommended Path

The paper should be restructured around the formalism document's organization:

1. **Section 1**: Introduction + trusted/untrusted model (formalism Section 5)
2. **Section 2**: Cipher map definition + four properties + construction layers (formalism Sections 1.1-1.3)
3. **Section 3**: Composition theorem (formalism Section 3)
4. **Section 4**: Three concrete constructions as instances (formalism Section 2)
5. **Section 5**: Space analysis + SHM construction (current Sections 5-6)
6. **Section 6**: Representation uniformity and encoding granularity (formalism Section 4)
7. **Section 7**: Discussion + honest limitations

**Remove**: The cipher functor / category theory material (Section 2 of current paper) should be demoted to a remark or appendix. It adds complexity without insight. The applications section (Section 8) should be removed entirely unless formal results are added. The "connections" section (Section 7) should be absorbed into the main development rather than being a separate section that asserts connections after the fact.

**Key principle**: The paper should say one thing and prove it rigorously, rather than claiming to unify three fields with hand-waving connections.
