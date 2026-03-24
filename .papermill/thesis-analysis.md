# Thesis Analysis: Composable Oblivious Algebraic Data Types

**Paper**: `papers/algebraic_cipher_types/`
**Date**: 2026-03-19
**Stage**: Early draft (2019-2022)

---

## 1. Main Claim

Oblivious (cipher) data types can be defined as algebraic data types -- void, unit, sum, product, exponential -- composed with three monadic transformations (cipher, noise/poison, restriction), such that the resulting compound types hide the values behind a trapdoor while preserving specifiable functional behavior through a restricted interface.

The paper frames this as a type-theoretic answer to the question: given a plain abstract data type T with computational basis F, how do we construct an oblivious object type OT(T) that implements a restricted subset of F while revealing minimal information to an adversary?

## 2. What Is Novel

### 2.1 The three-monad decomposition (cipher, noise, restriction)

The paper identifies three orthogonal type transformations that together produce a cipher type:

1. **Cipher monad** C_{M,N,S}: parametrized by number of representations M, byte length N, and secret S. Maps values to opaque bit strings with multiple representations per value. This is the core "trapdoor" construction.

2. **Noise/poison monad**: lifts a type T to Poison(T) by adding decoy values. As n/p -> 0 (ratio of real to poison values), inputs and outputs approach uniform distributions over the extended type. This is the mechanism for totality and indistinguishability.

3. **Restriction monad**: restricts a function f: X -> Y to a subset A of X, yielding a partial function. This controls what the untrusted machine can compute and bounds the space complexity.

The paper explicitly describes the composition pipeline (Section "Exponential types"):
- restrict(f, A) -> partial(f_1, noise_values) -> embed(f_2, noise_outputs) -> noise(f_3) -> cipher(f_4)

This layered decomposition is **the direct precursor** to the "three construction layers" (undef, noise, cipher) in the cipher-map-formalism.md. The formalism document even cites "algebraic cipher types, 2019" as the source of these layers.

### 2.2 Algebraic type constructors for cipher types

The paper systematically considers how obfuscation interacts with each algebraic constructor:

- **Void**: OT(Void) = Void (no values, no obfuscation needed)
- **Unit**: OT(Unit) necessary for completeness; reveals type if adversary knows it is unit
- **Sum types**: OT(X) + OT(Y) vs OT(X + Y) -- the latter hides which branch, but impairs composability (trade-off between confidentiality and composability)
- **Product types**: OT(X) x OT(Y) vs OT(X x Y) -- the latter hides correlations between components
- **Exponential types**: cipher maps; black-box vs. structured implementations

This is **the algebraic foundation** that the bernoulli_data_type/algebraic_types paper later formalizes for the error-propagation side (AT(T) for void, unit, Bool, sum, product, exponential).

### 2.3 Levels of obfuscation hierarchy

The paper identifies a hierarchy of obfuscation levels for functions:
1. Value obfuscation: inputs/outputs are cipher values
2. Function obfuscation: the mapping itself is a black box (cipher map)
3. Type obfuscation: the types of inputs/outputs are hidden (type erasure)
4. Pair obfuscation: correlations between inputs are hidden
5. Full black box: even the fact that a function is being evaluated is hidden

This is illustrated through the progressive obfuscation of set membership:
- `contains : P(OT(X)) x OT(X) -> Bool` (leaks membership)
- `contains : P(OT(X)) x OT(X) -> OT(Bool)` (oblivious result)
- `contains : OT(P(X) x X) -> OT(Bool)` (oblivious pair)
- Full steganographic hiding

### 2.4 Information leak analysis through orbits and closures

The paper develops the insight that operations generate "orbits" that progressively reveal cipher values:
- and(x, not(x)) = false reveals OT(false)
- Default construction of OT(0) followed by OT(0) + OT(0) reveals representations
- Successor/division operations cascade to reveal the entire type

The principle: the computational basis must be carefully restricted because sufficient operations always break obfuscation.

### 2.5 Cipher Turing machine

Extends the cipher type framework to Turing machines: replace states, alphabet, and transitions with cipher versions. This provides a computational model that can evaluate cipher functions without the space blow-up of lookup-table cipher maps, at the cost of revealing execution patterns (head movements). The observation that multiple implementations indexed by cipher tags can mitigate this is prescient.

## 3. Relationship to Trapdoor Computing Formalism

### Direct lineage

The cipher-map-formalism.md (Section 1.2) explicitly derives from this paper:

| This paper (2019-2022) | Cipher map formalism (2026) |
|---|---|
| Restriction monad | Layer 1: Undefined injection (undef) |
| Noise/poison monad | Layer 2: Noise closure (noise) |
| Cipher monad C_{M,N,S} | Layer 3: Multiple representations (cipher) |
| Approximate functions with FPR | Property 3: Correctness (eta-bounded) |
| Composition of cipher maps | Property 4: Composability |
| Trusted/untrusted machine partition | Trusted/untrusted model (Section 5) |

### What the formalism sharpened

- The "oblivious" framing (hiding *what* a type is) became the "trapdoor" framing (one-way function hiding the decoder)
- The three monads became three *construction layers* with an explicit caveat about not claiming formal monad laws
- The vague "levels of obfuscation" became the four concrete properties with measurable parameters (eta, epsilon, mu, delta)
- The Bernoulli FPR model was separated into its own paper (bernoulli_data_type)

### What this paper has that the formalism lacks

- The algebraic type theory perspective: void, unit, sum, product, exponential as first-class cipher type constructors
- The composability/confidentiality trade-off analysis for sum types (OT(X+Y) vs OT(X)+OT(Y))
- The orbit/closure analysis of information leaks
- The cipher Turing machine as an alternative to lookup-table cipher maps
- The explicit connection to Stepanov's "Elements of Programming" concept of regularity

## 4. Relationship to bernoulli_data_type/algebraic_types

The bernoulli_data_type/algebraic_types paper is the **error-model counterpart** to this paper:

| This paper | bernoulli_data_type/algebraic_types |
|---|---|
| OT(T) -- cipher/oblivious types | AT(T) -- random approximate types |
| Cipher monad C_{M,N,S} | Bernoulli approximation B_T |
| Focuses on *confidentiality* (what adversary learns) | Focuses on *accuracy* (error propagation) |
| Sum types: composability vs confidentiality trade-off | Sum types: tag errors break Kronecker factorization |
| Product types: correlation hiding | Product types: Kronecker factorization preserved |
| Exponential types: cipher maps | Exponential types: Bernoulli maps |
| FPR as Bernoulli-distributed (max entropy) | Bernoulli model with per-element independence |

The two papers are complementary halves: this one asks "how do we hide values behind algebraic cipher types?" while the Bernoulli paper asks "how do errors propagate through algebraic approximate types?" A unified paper would combine both perspectives: cipher types that are also approximate, with quantified error propagation and confidentiality.
