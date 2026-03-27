---
title: "Cipher Maps: Total Functions as Trapdoor Approximations"
stage: revision
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Privacy in encrypted computation need not come from access-pattern hiding (ORAM), exact algebraic homomorphism (FHE), or simulation-based security (garbled circuits). A total function on bit strings -- where domain, correctness, and function identity exist only behind a one-way trapdoor -- provides a distinct, quantifiable privacy model with predictable composition and information-theoretically optimal space."
  novelty: "The privacy mechanism is totality itself: the untrusted machine cannot distinguish real queries from noise, one encoding from another, or correct results from errors. This is not access-pattern hiding or computational hardness beyond the one-way hash."
  refined: "Variant C (contrast-forward). Leads with what's genuinely different, positions against ORAM/FHE/garbled circuits, signals quantifiability. Abstract rewritten 2026-03-27."

prior_art:
  last_survey: null
  key_references:
    - "bloom1970space: Bloom filters (HashSet subsumes as k=1 special case)"
    - "fredman1984storing: FKS perfect hashing"
    - "belazzougui2009hash: Minimal perfect hash functions (CHD)"
    - "gentry2009fully: FHE (exact computation on ciphertexts, high overhead)"
    - "yao1982protocols: Garbled circuits (one-time use, exact)"
    - "goldreich1996software: ORAM (access-pattern hiding)"
    - "curtmola2006searchable: SSE with simulation-based security (IND-CKA)"
    - "bellare1993random: Random oracle model"
    - "simmons1979symmetric: Homophonic substitution (historical connection)"
  gaps: ""

experiments: []

venue:
  target: null
  candidates:
    - "PETS (Privacy Enhancing Technologies Symposium)"
    - "IEEE Transactions on Information Theory"
    - "STACS/ISAAC (theory of computation)"

review_history:
  - date: "2026-03-19"
    reviewer: "papermill"
    recommendation: "major-revision"
    summary: "Paper rebuilt from scratch using formalism doc. 8/9 proofs PASS, 1 minor."
    resolution: "All issues addressed in rebuild."
  - date: "2026-03-26"
    reviewer: "papermill (8-specialist)"
    recommendation: "minor-revision"
    summary: "0 critical, 3 major (composition equality/inequality, ROM undefined, trust model ordering), 12 minor, 5 suggestions."
    resolution: "All 3 majors fixed: composition stated as inequality, ROM prelim added with Bellare-Rogaway cite, trust model moved before constructions."

related_papers:
  - path: ~/github/trapdoor-computing/papers/boolean-algebra-over-trapdoor-sets
    rel: companion
    label: "Online construction (trapdoor Boolean algebra) instantiated in cipher-maps"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli axioms provide the error model cipher maps inherit"
  - path: ~/github/bernoulli/papers/bernoulli-hash-function
    rel: foundation
    label: "BHF is the optimal cipher map construction for batch strategy"
  - path: ~/github/bernoulli/papers/bernoulli_maps
    rel: foundation
    label: "Bernoulli maps ARE cipher maps at the mathematical level"
---

## Notes

Paper rebuilt from scratch 2026-03-19 using formalism/cipher-map-formalism.md.
Original preserved as cipher_maps_original.tex.

Thesis refined 2026-03-27: Variant C (contrast-forward). Abstract rewritten.

## Next Actions

1. Target a venue (PETS most likely)
2. Address remaining 12 minor issues from review-2026-03-26
3. Consider adding a figure (construction comparison or trust model protocol)
