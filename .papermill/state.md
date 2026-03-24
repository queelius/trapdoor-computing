---
title: "Maximizing Confidentiality in Encrypted Search Through Entropy Optimization"
stage: revision
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Confidentiality in encrypted search can be quantitatively measured as the ratio of observed entropy to maximum entropy under system constraints, yielding a principled score between 0 and 1 that guides systematic improvement through entropy maximization techniques."
  novelty: "Information-theoretic confidentiality metric for encrypted search based on entropy ratios, with closed-form maximum entropy solutions and practical compression-based estimation without explicit probabilistic models."
  refined: null

prior_art:
  last_survey: null
  key_references:
    - "Shannon 1949 (Communication Theory of Secrecy Systems) - confusion/diffusion foundations"
    - "Song et al. 2000 - practical encrypted search"
    - "Curtmola et al. 2006 - searchable symmetric encryption security definitions"
    - "Islam et al. 2012 - access pattern leakage attacks"
    - "Cash et al. 2015 - leakage-abuse attacks"
    - "Grubbs et al. 2017 - volume leakage reconstruction"
    - "Jaynes 1957 - maximum entropy principle"
    - "Goh 2003 - secure indexes via Bloom filters"
  gaps: "Prior work treats confidentiality qualitatively or via computational hardness; no information-theoretic framework quantifies confidentiality as entropy ratio or derives maximum entropy under encrypted search constraints."

experiments:
  - name: "Case study"
    description: "Demonstrates confidentiality improvement from 59% to 85% entropy efficiency with moderate space and bandwidth overhead using homophonic encryption, filler queries, and query aggregation."

venue:
  target: "USENIX Security Symposium"
  candidates: []

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps-unified
    rel: companion
    label: "Cipher maps formalism used in encrypted search framework"
  - path: ~/github/trapdoor-computing/papers/encrypted-search
    rel: companion
    label: "Related encrypted search paper"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli model provides the error framework"
---

## Notes

Initialized by papermill on 2026-03-19.

Trapdoor reframing pending: homophonic encryption = Property 2 (Representation Uniformity), filler queries = Property 1 (Totality).

## Overview

51-page paper presenting an information-theoretic framework for encrypted search confidentiality. Defines confidentiality as the ratio of observed to maximum entropy, bounded [0,1]. Derives closed-form maximum entropy distributions under system constraints (query rates, vocabulary size, collection size). Shows entropy can be estimated practically via lossless compression. Demonstrates three improvement techniques -- homophonic encryption, artificial query injection, query aggregation -- each trading specific resources for entropy gains. Case study shows 59% to 85% efficiency improvement. 15 sections including appendices on entropy derivations, compression-based estimation, maximum entropy optimization, hypothesis testing, and notation reference.
