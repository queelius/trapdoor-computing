---
title: "Encrypted Search as Trapdoor Computing"
stage: draft
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Encrypted search is a special case of trapdoor computing, where the standard encrypted search vocabulary (information needs, search agents, secure indexes, hidden queries) maps directly to the four-property cipher map framework."
  novelty: "Reframes encrypted search constructions (Bloom filters, searchable encryption) as instances of the general cipher map abstraction, subsuming domain-specific schemes under a unified formalism parameterized by (eta, epsilon, mu, delta)."
  refined: "Encrypted search is one application of trapdoor computing: the domain-specific vocabulary (SA, ESP, information need, hidden query, secure index) is a relabeling of the general cipher map framework (T, U, latent function, cipher value, cipher map). The four properties specialize meaningfully -- totality gives filler indistinguishability, representation uniformity bounds frequency analysis, correctness provides plausible deniability, composability gives Boolean query composition with predictable error. The contribution is reframing, not construction: showing encrypted search is not sui generis but an instance of a general paradigm."

prior_art:
  last_survey: null
  key_references: []
  gaps: "Paper currently lacks citations; TODO notes indicate formalism paper citation needed and concrete constructions for keyword search, ranked retrieval, and Boolean query composition are planned."

experiments: []

venue:
  target: null
  candidates: []

review_history:
  - date: 2026-03-19
    type: papermill
    verdict: "Clean skeleton, correctly maps vocabulary and properties. Stops at definitions without concrete instantiations. Needs: bibliography, worked examples (keyword search, Boolean composition), comparison table, related work, conclusion. Does not duplicate maximizing-confidentiality (different abstraction level); should cross-reference. Estimated 2-3 sessions to reach submittable short paper."
    files:
      - .papermill/thesis-analysis.md
      - .papermill/reviews/review-2026-03-19.md

related_papers:
  - path: ~/github/trapdoor-computing/papers/maximizing-confidentiality
    rel: companion
    label: "Related encrypted search confidentiality paper"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli set model used for approximate encrypted search"
---

## Notes

Initialized by papermill on 2026-03-19.

## Overview

This paper formalizes encrypted search as an application of trapdoor computing. It establishes a vocabulary mapping between the encrypted search domain (search agents, encrypted search providers, information needs, hidden queries, secure indexes) and the cipher map abstraction (trusted/untrusted machines, latent functions, cipher values, cipher maps with the four properties: totality, representation uniformity, correctness, composability). The paper argues that traditional constructions like Bloom filters and searchable encryption are subsumed by cipher maps, and that encrypted search is just one instance of the general trapdoor computing paradigm. Currently a short draft (~150 lines) with TODO items for concrete constructions, experimental validation, and citations to the formalism paper.
