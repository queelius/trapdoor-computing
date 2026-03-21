---
title: "Trapdoor Computing"
stage: idea
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "A cipher map is a total function on bit strings. Privacy comes from one-way hash + uniform representation, not access-pattern hiding."
  novelty: "Reframes 'oblivious computing' as trapdoor computing: four formal properties (totality, representation uniformity, correctness, composability) grounded in authentic 2023-2024 blog posts, correcting prior ORAM-style drift."
  refined: "A cipher map is a total function on bit strings, parameterized by a one-way trapdoor (secret seed), that approximates a latent function f: X -> Y. The trusted machine (holding the trapdoor) encodes, decodes, and verifies; the untrusted machine sees only opaque bits flowing through opaque functions. This paradigm, trapdoor computing, is characterized by four formal properties: totality, representation uniformity (delta-close to uniform), eta-bounded correctness, and composability (eta_total = 1 - (1-eta_f)(1-eta_g)). The space cost is information-theoretic: -log_2(epsilon) + H(Y) bits per element. Three concrete constructions (HashSet, entropy map, trapdoor Boolean algebra) instantiate this abstraction with different parameter trade-offs."

prior_art:
  last_survey: null
  key_references: []
  gaps: ""

experiments: []

venue:
  target: null
  candidates: []

review_history:
  - date: "2026-03-19"
    reviewer: "papermill (Claude Opus 4.6)"
    verdict: "major-revision (rewrite required)"
    files:
      - ".papermill/thesis-analysis.md"
      - ".papermill/reviews/review-2026-03-19.md"
      - ".papermill/reviews/proof-check-2026-03-19.md"
    summary: "8 MAJOR issues. Core problem: paper uses 'oblivious' framing that was superseded by the trapdoor computing reframing. Obliviousness never formally defined. Privacy model absent. Unification not demonstrated. Functoriality theorem is incorrect (monoid only on quotient, not on representations). Cipher-Bernoulli Correspondence has no real proof. Security reduction incomplete. Space bound and composition formula are sound. Paper should be rebuilt from formalism/cipher-map-formalism.md."
    critical_issues:
      - "Obliviousness undefined (Def 4.1 has three informal bullets, not four formal properties)"
      - "Trusted/untrusted machine model absent"
      - "Thm 2.1 (Cipher Monoid) is wrong: monoid only on quotient c_A S / ~, not on c_A S"
      - "Thm 7.1 (Functoriality) is wrong: identity preservation fails, composition preservation fails"
      - "Thm 4.2 (Cipher-Bernoulli Correspondence) has no proof"
      - "Thm 5.4 (Collision Resistance) claim 2 likely wrong, appendix reduction incomplete"
      - "Thm 5.5 AM-GM bound direction reversed (p <= not p >=)"
      - "Thm 3.4 formula uses conditional Q as if it were joint distribution"
  - date: "2026-03-19"
    paper: "maximizing-confidentiality"
    reviewer: "papermill (Claude Opus 4.6)"
    verdict: "major-revision"
    files:
      - ".papermill/thesis-analysis-maximizing-confidentiality.md"
      - ".papermill/reviews/review-maximizing-confidentiality-2026-03-19.md"
      - ".papermill/reviews/proof-check-maximizing-confidentiality-2026-03-19.md"
    summary: "5 MAJOR, 5 MINOR issues. Entropy ratio metric (e=H/H*) is sound in principle but paper lacks formal adversary model, has no experimental evaluation, is 3-4x too long for USENIX (51pp vs 13pp target), and has structural redundancy (same results derived 2-3 times). Proofs: 8/15 correct, 3 incomplete, 2 have errors. Key proof issues: constrained max entropy has inconsistent parameter lists, quantized inter-arrival formula wrong, mixture entropy in case study uses weighted average instead of actual mixture entropy. Result set determinism creates inconsistency with joint max entropy formula. Case study 59%->85% result is the strongest selling point."
    critical_issues:
      - "No formal adversary model or security reduction connecting entropy to adversary advantage"
      - "Independence assumption critical but unrealistic; no quantification of gap"
      - "No experimental evaluation (case study is purely analytical)"
      - "3-4x too long for USENIX; massive structural redundancy"
      - "Result set entropy included in joint formula despite being deterministic given query"

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps-unified
    rel: supersedes
    label: "Most developed paper, on hold pending trapdoor formalism rewrite. Moved from oblivious-computing."
  - path: ~/github/trapdoor-computing/papers/boolean-algebra-over-trapdoor-sets
    rel: companion
    label: "Trapdoor set operations paper. Pre-July 2024 commits (549091a) are authentic, later drifted. Moved from oblivious-computing."
  - path: ~/github/trapdoor-computing/papers/crypto-perf-hash
    rel: companion
    label: "Hash constructions underpinning encoding scheme. Moved from oblivious-computing."
  - path: ~/github/trapdoor-computing/papers/maximizing-confidentiality
    rel: companion
    label: "System-level encrypted search confidentiality via entropy optimization. USENIX target, 51pp. Reviewed 2026-03-19: major-revision (5 MAJOR issues). Needs formal adversary model, experimental eval, 3x length reduction. Trapdoor reframing pending: homophonic encryption = Property 2, filler queries = Property 1."
---

## Notes

Initialized by papermill on 2026-02-22. Migrated from `.papermill.md` to `.papermill/state.md` on 2026-02-26.

## Overview

Repository for developing the **trapdoor computing** paradigm: computing with values whose meaning is hidden behind a one-way trapdoor (cryptographic hash). Reframing of prior "oblivious computing" work with corrected formalism.

**Origin**: Recovery from Claude-drifted "oblivious computing" papers; authentic source is 2023-2024 blog posts.

## Repository Structure

```
trapdoor-computing/
├── foundations/              # Authentic 2023-2024 blog posts (source of truth)
│   ├── bernoulli-model.md   # B_T(x), confusion matrices, HashSet, -log2(ε)
│   ├── noisy-gates.md       # Composable Bernoulli logic gates, interval arithmetic
│   ├── trapdoor-boolean-algebra.md  # Approximate homomorphism F via crypto hash
│   └── entropy-maps.md      # Prefix-free codes, μ=H(Y), two-level hash
├── formalism/               # Design docs and formal development
│   └── DESIGN-trapdoor-reframing.md  # Four properties, parameter decomposition
├── papers/                  # Papers (empty, formalism first)
├── ECOSYSTEM-TRIAGE.md      # Classification of all related papers/code
├── CLAUDE.md
└── README.md
```

## Foundations Inventory

| Document | Date | Lines | Key Content |
|----------|------|-------|-------------|
| bernoulli-model.md | 2023-06-17 | 321 | Bernoulli types B_T(x), latent/observed duality, confusion matrices, HashSet construction, -log₂ε bits/element, functions as values |
| noisy-gates.md | 2023-06-17 | 155 | Noisy AND gate analysis, 4th-order output from 1st-order inputs, interval arithmetic for error tracking through circuits |
| trapdoor-boolean-algebra.md | 2023-06-17 | 797 | Homomorphism F: P(X*) → {0,1}^n, AND/OR exact, NOT approximate, single-level and two-level hashing, C++ implementation, marginal uniformity |
| entropy-maps.md | 2024-02-18 | 176 | Prefix-free hash codes for function approximation, μ=H(Y) space bound, Bernoulli set-indicator, two-level hash algorithm, oblivious entropy maps |

## Formalism: Four Properties of a Cipher Map

Defined in `DESIGN-trapdoor-reframing.md`:

1. **Totality**: f-hat defined on all inputs. Noise has probability epsilon of becoming valid codeword.
2. **Representation Uniformity**: Multiple encodings per value, delta-close to uniform.
3. **Correctness**: eta-bounded error for in-domain elements.
4. **Composability**: eta_total = 1 - (1-eta_f)(1-eta_g).

## Parameter Decomposition

| Parameter | Controls | Affects |
|-----------|----------|---------|
| **eta** | Correctness: fraction of in-domain elements with wrong answers | Trusted machine |
| **mu** | Value encoding cost: bits per element for function values (= H(Y)) | Space |
| **epsilon** | Noise decode probability: probability random bits form valid codeword | Space budget |
| **|c_A S|/|S|** | Representation multiplicity: frequency equalization | Adversary observing traffic |
| **delta** | Representation uniformity: closeness to uniform distribution | Adversary with partial knowledge |

## Related Work and Software

Full classification in `ECOSYSTEM-TRIAGE.md`. Key relationships:

- **cipher-maps-unified** (`papers/cipher-maps-unified/`): Most developed paper. On hold pending trapdoor formalism rewrite. Review 3 (2026-03-19): 8 MAJOR issues, 6 proof errors found. Rewrite required from formalism/cipher-map-formalism.md.
- **maximizing-confidentiality** (`papers/maximizing-confidentiality/`): Entropy ratio metric for encrypted search confidentiality. Review (2026-03-19): 5 MAJOR issues (no formal adversary model, no experiments, 3x too long for USENIX). Proofs: 8/15 correct, 2 errors, 3 incomplete. 59%->85% case study is strongest result.
- **boolean-algebra-over-trapdoor-sets** (`papers/boolean-algebra-over-trapdoor-sets/`): Pre-July 2024 commits (549091a) authentic; later drifted with ORAM formalism.
- **crypto-perf-hash** (`papers/crypto-perf-hash/`): Hash constructions underpinning the encoding scheme.
- **bernoulli/**: C++ library and papers. Semi-separate; provides the error model. User also working on this independently.

### Ecosystem Summary

| Classification | Items |
|----------------|-------|
| **Authentic** | 4 blog posts (foundations/), C++ bernoulli_data_type library, bernoulli/papers/, A10 (IEEE 2016, now at `~/github/papers/estimating-es-conf-mab`), A8 thesis (now at `~/github/papers/encrypted-search-thesis`) |
| **Claude-expanded** | F1 (Bernoulli Theory), good formalization of author's ideas |
| **Mixed** | F3, F4, cipher_maps_unified, application papers A1-A9 |
| **Drifted** | F2 (ORAM formalism, not author's work), boolean-algebra-over-trapdoor-sets post-549091a |

## Next Actions

### Formalism (current priority)
- [x] Tighten the four properties against concrete constructions from blog posts → `formalism/cipher-map-formalism.md` §2 (2026-03-08)
- [x] Connect noisy-gates composition story to cipher map composition theorem → `formalism/cipher-map-formalism.md` §3 (2026-03-08)
- [x] Formalize the trusted/untrusted machine model → `formalism/cipher-map-formalism.md` §5 (2026-03-08)
- [ ] Decide what to do with drifted papers (archive, revert, or rebuild)
- [ ] Resolve open questions from formalism document (δ metric, NOT tight bounds, noise-to-signal under composition, adaptive granularity)

### Paper Development (after formalism)
- [ ] Write cipher maps paper using trapdoor computing formalism
- [ ] Rewrite Section 4 of cipher_maps_unified with formal trapdoor definition
- [ ] Update title, abstract, and introduction
- [ ] Select target venue

### Ecosystem Cleanup
- [ ] Decide fate of foundational/ and extensions/ dirs in oblivious-computing (Claude-generated)
- [ ] Revert or archive boolean-algebra-over-trapdoor-sets post-549091a
- [ ] Correct "oblivious" → "trapdoor" in salvageable papers

## Provenance

- **Created**: 2026-02-22
- **Method**: Recovery of authentic 2023-2024 blog posts + formalism discussion
- **Git**: github.com/queelius/trapdoor-computing
- 2026-02-26 (init refresh): Migrated `.papermill.md` → `.papermill/state.md`. Added YAML schema (thesis, prior_art, experiments, venue, review_history, related_papers). All legacy data preserved in Notes.
