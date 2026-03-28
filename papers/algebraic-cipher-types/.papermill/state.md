---
title: "Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing"
stage: draft
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Each algebraic type constructor (sum, product, exponential) imposes a specific, unavoidable trade-off between confidentiality and composability when applied to cipher values. Orbit closure under the available operations bounds adversarial knowledge."
  novelty: "Sum-type impossibility theorem (tag hiding vs pattern matching), orbit closure as a quantitative confidentiality tool, cipher TM space complexity independent of domain cardinality."
  refined: null

prior_art:
  last_survey: null
  key_references:
    - "towell2026cipher: Cipher maps (batch construction, four properties)"
    - "towell2026bernoulli: Bernoulli data types (accuracy-side algebraic analysis)"
  gaps: ""

experiments: []

venue:
  target: null
  candidates:
    - "PLAS (Programming Languages and Analysis for Security, at CCS)"
    - "IACR ePrint (technical report)"
    - "TCC (Theory of Cryptography Conference)"

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher map abstraction, four properties, batch construction"
  - path: ~/github/bernoulli/papers/bernoulli_data_type
    rel: companion
    label: "Accuracy-side algebraic types (Kronecker factorization, error propagation)"
  - path: ~/github/trapdoor-computing/papers/algebraic_cipher_types
    rel: origin
    label: "2019-2022 notebook with original ideas (not publishable as-is)"
---

## Notes

New paper started 2026-03-28, drawing on ideas from the algebraic_cipher_types
notebook (2019-2022). Three core results: sum-type impossibility, orbit closure,
cipher Turing machine.

## Next Actions

1. Review proofs (papermill:proof)
2. Review full paper (papermill:review)
3. Target venue and prepare submission
