---
title: "Cryptographic Perfect Hash Functions: A Theoretical Analysis on Space Efficiency and Algebraic Composition"
stage: draft
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "A cryptographic perfect hash function (modeled as a random oracle) achieves the information-theoretic lower bound on expected space complexity while its in-place encoding is a maximum-entropy random bit string."
  novelty: "Derives exact space bounds and entropy properties for cryptographic perfect hash functions under the random oracle model, and shows that algebraic composition (post-composition with injections, permutation equivalence classes) preserves the perfect hash property with predictable load factor transformations."
  refined: "The paper's genuine contribution is threefold: (1) the general load-factor-parameterized space formula log2(e) - (1/r-1)log2(1/(1-r)) bits/element, which extends the known 1.44 bits/element MPHF result to arbitrary r; (2) the entropy-optimal in-place encoding argument connecting PHF space bounds to Shannon's source coding; (3) the algebraic composition framework (post-composition with injections, permutation equivalence classes). The main result (the space formula) is correct but the proof of Theorem 3.3 needs repair -- it conflates E[log Q] with log E[Q]. The maximum entropy proof (Theorem 3.5) is insufficiently rigorous. The shared infrastructure with the Bernoulli hash function paper (identical PMF, telescoping sum, series formula) should be explicitly cross-referenced."

prior_art:
  last_survey: "2026-03-19"
  key_references:
    - "Fredman, Komlos, Szemeredi 1984 - O(1) access sparse tables (FKS scheme)"
    - "Dietzfelbinger et al. 1990 - Space-efficient hash tables with worst-case constant access"
    - "Czech, Havas, Majewski 1992 - Family of perfect hashing methods"
    - "Bellare, Rogaway 1993 - Random oracle model"
    - "Botelho, Pagh, Ziviani 2007 - Simple and space-efficient MPHFs"
    - "Belazzougui, Botelho, Dietzfelbinger 2009 - CHD algorithm"
    - "Shannon 1948 - Information theory foundations"
    - "Cover, Thomas 2006 - Elements of Information Theory"
    - "Pagh, Rodler 2004 - Cuckoo hashing"
  gaps: "Prior work focuses on practical construction speed and space efficiency; this paper analyzes fundamental information-theoretic properties when the hash function is a random oracle, showing the in-place encoding achieves the theoretical entropy bound. MISSING from prior art survey: recent practical near-optimal MPHFs (RecSplit 2020, SicHash 2023, ShockHash) that achieve near-1.44 bits/element with polynomial construction time."

experiments:
  - name: "Mathematica derivations and plots"
    path: "research/"
    notebooks:
      - "cryptoph_with_fn.nb"
      - "logq.nb"
      - "math1.nb"
      - "paper_pf.nb"
      - "perfhash.nb"
    status: "complete"

venue:
  target: null
  candidates: []

review_history:
  - date: "2026-03-19"
    reviewer: "papermill"
    verdict: "Needs significant revision"
    key_issues:
      - "Theorem 3.3 proof conflates E[log Q] with log E[Q] -- result is correct, proof technique is flawed"
      - "Theorem 3.5 (maximum entropy) proof is insufficiently rigorous -- needs explicit argument about conditional uniformity of n'"
      - "Section 4 (two-level) has errors: variance formula has extra factor of m; analysis conflates bucket-level and element-level success probabilities"
      - "Postulate 3.1 should be a theorem or cited result, not a postulate"
      - "N notation overloaded (codomain size vs. bit length RV)"
      - "Section 2 too verbose for standard definitions"
      - "No conclusion section"
      - "Missing cross-reference to Bernoulli hash function paper"
      - "Missing comparison with recent practical near-optimal MPHFs"
      - "Redundant introductory paragraphs for Algorithm 1 (lines 421-427)"
    files:
      - ".papermill/reviews/review-2026-03-19.md"
      - ".papermill/reviews/proof-check-2026-03-19.md"
      - ".papermill/thesis-analysis.md"

related_papers:
  - path: ~/github/bernoulli/papers/bernoulli-hash-function
    rel: companion
    label: "Bernoulli hash function paper -- shares identical geometric search / PMF / entropy machinery; addresses approximate membership (epsilon-parameterized) vs. this paper's exact membership (r-parameterized)"
  - path: ~/github/trapdoor-computing/papers/cipher-maps-unified
    rel: companion
    label: "Cipher maps use these hash constructions for encoding; the PHF space bound determines the encoding cost parameter mu = H(Y)"
---

## Notes

Initialized by papermill on 2026-03-19.
First review completed 2026-03-19.

## Overview

Analyzes a theoretical cryptographic perfect hash function with three properties: (1) it is a cryptographic hash function (random oracle); (2) its in-place encoding achieves the theoretical lower bound on expected space complexity; (3) its in-place encoding is a maximum-entropy random bit string.

Key result: Expected space complexity is log2(e) - (1/r - 1)log2(1/(1-r)) bits/element, achieving 1.44 bits/element for minimal perfect hash (r=1).

## Paper Structure

1. **Prior Art** - Survey of perfect hashing literature (FKS, CHD, cuckoo hashing, information theory)
2. **Perfect hash functions** - Formal definitions (sets, hash functions, load factor, bit strings)
3. **Theoretical cryptographic perfect hash function** - Random oracle construction (Algorithm 1), analysis of space complexity and entropy
4. **Practical two-level perfect hash function** - Algorithm 2 with analysis
5. **Algebra of function composition** - Post-composition with injections preserves perfect hashing with load factor r' = r/(1+alpha); permutation equivalence classes; applications (domain adaptation, load factor adjustment, randomization)
6. **Appendix** - Probability mass of random bit length (Algorithm 3)

## Priority Revision Plan

1. Fix Theorem 3.3 proof (E[log Q] vs log E[Q] conflation)
2. Strengthen Theorem 3.5 proof (explicit conditional uniformity argument)
3. Fix Section 4 variance formula and bucket-level analysis
4. Add conclusion section with cipher map / trapdoor computing connections
5. Replace Postulate 3.1 with theorem or cited result
6. Fix N notation overloading
7. Add cross-references to Bernoulli hash function paper
8. Update prior art with recent practical MPHFs
9. Condense Section 2 definitions
