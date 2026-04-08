---
title: "Quantitative Confidentiality for Cipher Maps"
stage: draft-complete
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Confidentiality in cipher map systems can be quantitatively measured as the entropy ratio e = H/H*, and systematically improved via three levers (noise injection, multiple representations, encoding granularity) expressible in terms of the four cipher map parameters."
  novelty: "Information-theoretic confidentiality theory grounded in the cipher map framework, connecting the entropy ratio to the four properties (totality, representation uniformity, correctness, composability) with explicit cost/benefit trade-offs for each improvement lever."
  refined: "2026-04-01: Complete rewrite from cipher map formalism. Old 43-page paper replaced by 13-page theory paper."

prior_art:
  last_survey: null
  key_references:
    - "towell2026cipher - Cipher maps framework (four properties, composition, acceptance predicates)"
    - "towell2026algebraic - Algebraic cipher types (sum/product trade-offs, orbit closure)"
    - "Shannon 1949 - Communication Theory of Secrecy Systems"
    - "Jaynes 1957 - Maximum entropy principle"
    - "Islam et al. 2012 - Access pattern leakage attacks"
    - "Cash et al. 2015 - Leakage-abuse attacks"
    - "Simmons 1979 - Homophonic substitution"
  gaps: "Prior work treats confidentiality qualitatively or via simulation-based security. This paper provides information-theoretic confidentiality grounded in the cipher map framework."

experiments:
  - name: "Boolean search on 20 Newsgroups"
    description: "Precision/recall vs confidentiality trade-off. 5000 docs, 8-bit cipher Booleans."
  - name: "FPR compounding"
    description: "AND/OR chains k=1..5, empirical vs theoretical FPR."
  - name: "Encoding granularity"
    description: "Root/intermediate/leaf encoding of 7-function pipeline."
  - name: "Case study"
    description: "Confidentiality improvement from 59% to 85% via combined homophonic + noise."

venue:
  target: "Theory venue (15-20 pages)"
  candidates: []

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher maps formalism (four properties, composition, acceptance predicates)"
  - path: ~/github/trapdoor-computing/papers/algebraic-cipher-types
    rel: companion
    label: "Algebraic cipher types (sum/product trade-offs, orbit closure, confidentiality bound)"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli model provides the error framework"
---

## Notes

Initialized by papermill on 2026-03-19.

### 2026-04-01: Complete rewrite

Rewrote the paper from scratch, grounding it in the cipher map formalism.

- **Old paper**: main.tex (43 pages, USENIX target, pre-cipher-map formalism)
- **New paper**: main_new.tex (13 pages, theory venue, grounded in cipher map framework)
- **Bibliography**: references_new.bib (25 entries, matching cipher-maps paper conventions)

Key changes:
1. Replaced all custom notation with cipher-maps paper notation (fhat, enc, dec, eta, epsilon, delta, mu)
2. Replaced the 15-section structure with 8 focused sections
3. Grounded the entropy ratio in the four cipher map properties
4. Added encoding granularity (from cipher-maps and algebraic-cipher-types papers)
5. Added compositional confidentiality (FPR compounding, correlation leakage)
6. Added orbit closure as a confidentiality bound
7. Added experimental results from cipher-maps library (three experiments)
8. Dropped ORAM, queueing theory, mix networks, and all appendices

The paper compiles cleanly (13 pages, no errors, no warnings).

Writing plan saved to .papermill/drafts/2026-04-01/writing-plan.md.

## Overview

13-page paper developing quantitative confidentiality theory for cipher map systems. Defines confidentiality as the entropy ratio e = H/H* in [0,1]. Connects e to the four cipher map parameters (eta, epsilon, delta, mu). Identifies three levers for improving confidentiality: noise injection (trades bandwidth), multiple representations (trades space), encoding granularity (trades functionality). Analyzes confidentiality under composition (FPR compounding, correlation leakage). Provides practical measurement via compression-based entropy estimation. Validates on 20 Newsgroups corpus with three experiments.
