---
title: "Composable oblivious algebraic data types: Defining compound oblivious types from elementary oblivious types"
stage: draft
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Oblivious abstract data types can be defined such that implementations (oblivious object types) only reveal specifiable degrees of uncertainty about object behavior through a restricted interface, and these types compose algebraically (sum, product, exponential) to build compound oblivious types from primitives."
  novelty: "Frames oblivious/trapdoor computing as an algebraic type system with composable monads (cipher, noise/poison, restriction) over standard algebraic data types (void, unit, sum, product, exponential), providing a principled type-theoretic foundation for computing on hidden values."
  refined: |
    Three orthogonal type transformations (restriction, noise/poison, cipher) compose over standard algebraic data types (void, unit, sum, product, exponential) to produce cipher types with quantifiable confidentiality and accuracy. The three-monad pipeline is the direct precursor to the cipher map construction layers (undef, noise, cipher). The paper's unique contribution beyond the error model (now in bernoulli_data_type) is the confidentiality-side analysis: orbit/closure information leak bounds, the sum-type composability/confidentiality trade-off, and the cipher Turing machine as an alternative to lookup-table cipher maps.

prior_art:
  last_survey: null
  key_references:
    - "obmap (oblivious map)"
    - "oset (oblivious set)"
    - "sibool (secure indices for Boolean Encrypted Search)"
    - "phf (Perfect Hash Filter)"
    - "eop (Elements of Programming, Stepanov)"
  gaps: "No existing framework treats oblivious/trapdoor computation as a compositional algebraic type system with formal monadic structure for cipher, noise, and restriction transformations."

experiments: []

venue:
  target: null
  candidates: []

review_history:
  - date: 2026-03-19
    reviewer: "papermill (Claude Opus 4.6)"
    verdict: "mine-for-ideas"
    summary: |
      Early-stage notebook, not a publishable draft. Contains five high-value ideas:
      (1) Three-monad pipeline (restrict -> partial -> embed -> noise -> cipher),
      the direct ancestor of the cipher map construction layers.
      (2) Sum-type composability/confidentiality trade-off (OT(X+Y) vs OT(X)+OT(Y)).
      (3) Orbit/closure analysis of information leaks from operations.
      (4) Cipher Turing machine for large-domain functions.
      (5) Levels-of-obfuscation hierarchy from value through type to steganographic.
      Major issues: no logical spine, extensive duplication (oblivious set defined 3x,
      PHF example 3x, k-ary model 2x), ~15 TODO markers, incomplete sections.
      The error-model content (Bernoulli FPR, binomial distributions) has been
      superseded by bernoulli_data_type/algebraic_types. Recommend mining for ideas
      rather than attempting to revise into publishable form.
    path: ".papermill/reviews/review-2026-03-19.md"

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: companion
    label: "Cipher maps paper builds on algebraic types framework; three-monad pipeline became construction layers"
  - path: ~/github/bernoulli/papers/bernoulli_data_type
    rel: companion
    label: "Bernoulli data type absorbed the error-model half; this paper retains the confidentiality-side analysis"
  - path: ~/github/trapdoor-computing/papers/boolean-algebra-over-trapdoor-sets
    rel: sibling
    label: "Boolean algebra over trapdoor sets specializes the oblivious Boolean algebra section"
  - path: ~/github/trapdoor-computing/papers/encrypted-search
    rel: downstream
    label: "Encrypted search applies oblivious set and predicate types"
---

## Notes

Initialized by papermill on 2026-03-19.
First review completed 2026-03-19.

## Overview

This is an early foundational paper (2019-2022) that develops the theory of oblivious (cipher) algebraic data types. The paper defines the oblivious abstract data type, where implementations are oblivious object types whose values appear uncorrelated with the underlying plain values. The core contribution is an algebraic type-theoretic framework: primitive oblivious types (void, unit, Boolean) compose via sum types, product types, and exponential types (functions/maps) to build compound oblivious types.

Key constructions include: (1) the cipher monad C_{M,N,S} parametrized by number of representations, byte length, and secret; (2) a noise/poison monad that lifts types to include decoy values making outputs appear uniformly random; (3) a restriction monad for partial function evaluation; (4) multiple levels of obfuscation from value obfuscation through type erasure to full black-box models. The paper also covers oblivious Boolean algebras over n-bit strings, cipher Turing machines, information-theoretic entropy analysis, and the false positive rate probabilistic model (Bernoulli-distributed FPR, binomial false positive counts).

The paper is in early draft stage with many TODO notes, incomplete sections, some duplicated content, and informal prose mixed with formal definitions. It contains substantial authentic mathematical content but needs significant restructuring and completion.

## Key Findings from Review

### Ideas worth developing further
1. **Three-monad pipeline**: restrict -> noise -> cipher is the direct precursor to cipher map construction layers
2. **Sum-type trade-off**: OT(X+Y) hides branch but breaks composability; OT(X)+OT(Y) preserves composability but leaks branch -- unique confidentiality-side analysis
3. **Orbit/closure leak analysis**: operations generate orbits revealing cipher values; closure size relative to type size measures confidentiality loss
4. **Cipher Turing machine**: divorces space complexity from domain cardinality; multiple implementations indexed by cipher tags
5. **Regularity connection**: oblivious types are inherently non-regular in the Stepanov sense

### Content superseded by other papers
- Bernoulli FPR model, binomial distributions, k-ary predicate error propagation -> bernoulli_data_type
- Algebraic type error propagation (Kronecker factorization, sum-type non-factorization) -> bernoulli_data_type/algebraic_types
- Cipher map four properties, parameters -> cipher-maps via cipher-map-formalism
