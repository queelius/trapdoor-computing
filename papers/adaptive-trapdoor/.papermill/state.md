---
title: "Adaptive Trapdoor Computing"
stage: idea
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Operational confidentiality of a trapdoor system is a maintained
    property under distributional drift, not a delivered one. Online
    observation and retuning of K(x) keep delta near its analytical
    optimum at a query-budget cost, with secret-preserving retune
    keeping already-emitted ciphertext valid."
  novelty: "Drift-aware confidentiality theory. None of the existing
    cipher-maps / algebraic-types / entropy-ratio / rekeying papers
    address temporal dynamics."
  refined: ""

prior_art:
  last_survey: null
  key_references:
    - cipher-maps (sibling)
    - The Entropy Ratio (sibling, prerequisite)
    - cipher-rekeying (sibling)
    - Gama et al. 2014 (concept drift)

experiments:
  preliminary:
    location: ~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py
    figures: experiments/figures/online_stationary.png, online_drift.png
    finding: "Drift jumps predicted TV from 0.034 to 0.434 instantly;
      adaptive retuning recovers it to 0.25 within two batches."
  needed:
    - real drift dataset
    - cadence comparison
    - secret-preserving retune validation

venue:
  target: null
  candidates:
    - PoPETs
    - CCS (workshop)
    - ESORICS

review_history: []

next_action: "Implement PHFCipherMap.retune_k() in the cipher-maps
  library; pick a real drift dataset; draft the formal model section."
---
