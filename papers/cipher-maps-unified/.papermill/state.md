---
title: "Cipher Maps: A Unified Framework for Oblivious Function Approximation Through Algebraic Structures and Bernoulli Models"
stage: revision
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"
    affiliation: "Southern Illinois University Edwardsville"
    scholar: "E9mnFzQAAAAJ"

thesis:
  claim: "Cipher maps unify algebraic cipher functors, Bernoulli approximation models, and oblivious data structures through the cipher functor (a proper functor on the category of monoids), achieving information-theoretic optimal space complexity of -log2(epsilon) + mu bits per element with strong privacy guarantees."
  novelty: "Treats cipher functors as total functions on bit strings (trapdoor computing paradigm) where the untrusted machine sees only opaque bits through opaque lookup tables, unifying previously separate notions of homomorphic encryption, probabilistic data structures, and oblivious computation."
  refined: "Pending trapdoor reframing -- approved design doc replaces 'oblivious' paradigm with formal four-property definition (totality, representation uniformity, eta-bounded correctness, composability) under the trusted/untrusted machine model."

prior_art:
  last_survey: null
  key_references:
    - "gentry2009fully: Fully homomorphic encryption (FHE baseline)"
    - "bloom1970space: Bloom filters, probabilistic data structures"
    - "cormode2005improved: Count-Min sketches"
    - "barthe2009formal: Category-theoretic approaches to cryptography"
    - "mac2003categories: General theory of functors"
    - "goldreich1996software: Software protection / obfuscation"
    - "elgamal1985public: ElGamal encryption (used in Example 2.2)"
  gaps: "No formal obliviousness/trapdoor definition yet; 9 uncited bib entries (boneh2011homomorphic, brakerski2014leveled, cash2013highly, dwork2006calibrating, goldreich2001foundations, paillier1999public, rivest1978data, shamir1979share, yao1982protocols) need to be woven in or pruned."

experiments: []

venue:
  target: null
  candidates:
    - "IEEE Transactions on Information Theory (probabilistic DS + info theory angle)"
    - "STACS/ISAAC (theory of computation)"
    - "CCS/PETS/IEEE S&P (crypto venue -- requires formal security definitions, blocked by M1)"
    - "SODA/APPROX (space complexity angle)"

review_history:
  - date: "2026-02-18"
    reviewer: "papermill"
    recommendation: "major-revision"
    summary: "3 CRITICAL, 4 MAJOR, 13 MINOR. Critical issues: (1) no explicit construction of c_A*, (2) mu not derived / lower bound missing, (3) cyclic group example mathematically broken."
    resolution: "All 3 CRITICAL fixed: split Def 2.2/2.3 with representation selector rho; added Def 6.1 + reordered Section 6 + added proofs; changed to (Z_p*, cdot) with ElGamal citation."
  - date: "2026-02-22"
    reviewer: "papermill"
    recommendation: "major-revision"
    summary: "0 CRITICAL, 8 MAJOR, 18 MINOR. Acknowledged improvements from Review 1 fixes. Key remaining issues: M1 (obliviousness undefined), M2 (Thm 3.5 broken), M3 (functoriality well-definedness gap), M4 (figures missing), M5 (Thm 6.4 no proof), M6 (Thm 2.1 quotient monoid mismatch), M7 (Ex 2.2 representation multiplicity broken), M8 (Thm 6.2 Step 3 independence gap)."
    resolution: "Unresolved. Design doc DESIGN-trapdoor-reframing.md approved to address M1 via trapdoor computing paradigm. Remaining issues tracked in next_actions below."

related_papers:
  - path: ~/github/trapdoor-computing/formalism/cipher-map-formalism.md
    rel: supersedes
    label: "Formal definitions being developed to replace paper's informal treatment"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli set model -- provides the error/approximation framework"
  - path: ~/github/oblivious-computing/papers/cipher_maps_unified
    rel: origin
    label: "Original location before migration to trapdoor-computing repo"
  - path: ~/github/oblivious-computing/papers/algebraic_cipher_types
    rel: merged-source
    label: "Merged into this paper (A3, 10pp) -- algebraic foundations, encoding set theory, functoriality"
  - path: ~/github/oblivious-computing/papers/cipher_maps
    rel: merged-source
    label: "Merged into this paper as base (A4, 10pp) -- Bernoulli integration, SHM construction"
---

## Notes

Initialized by papermill on 2026-03-19. Migrated from `.papermill.md`.

### Provenance

- **Created**: 2026-02-18 by merging algebraic_cipher_types (A3, 10pp) + cipher_maps (A4, 10pp)
- **Base**: A4 (cipher_maps)
- **Added from A3**: Encoding set theory, cyclic group cipher example, functoriality theorem with proof, cipher composition theorem with proof, security reduction, latent-observable duality, induced Bernoulli type, group definition
- **Originals archived**: `archive/original_algebraic_cipher_types.zip`, `archive/original_cipher_maps.zip`

### Review 1 (2026-02-18): 3 CRITICAL, 4 MAJOR, 13 MINOR

All 3 CRITICAL issues resolved:
- CRITICAL 1: Split Def 2.2/2.3, added representation selector rho, rebuilt Thm 2.1+2.2 proofs
- CRITICAL 2: Added Def 6.1 (Mean Encoding Length), reordered lower bound before space complexity, added real proofs, added Corollary (eta=0 matches abstract)
- CRITICAL 3: Changed to (Z_p*, cdot, 1) with primitive root, added ElGamal citation

### Review 2 (2026-02-22): 0 CRITICAL, 8 MAJOR, 18 MINOR

Recommendation: major-revision. Full review preserved in `.papermill-review-results.md`.

**Strengths noted**: Def 2.2/2.3 split is right architecture; Section 6 reordering correct; Def 6.1 resolves mu-derivation gap; Corollary 6.1 correctly bridges abstract to theorem; Thm 7.5 (Cipher Composition) is paper's strongest result with correct proof; quotient monoid remark adds genuine value.

**MAJOR issues (8)**:

| # | Issue | Location | Status |
|---|-------|----------|--------|
| M1 | Obliviousness never formally defined | Def 4.1, Thm 7.3, Prop 4.2 | open -- design doc approved for trapdoor reframing |
| M2 | Thm 3.5 (Bernoulli Entropy) formula wrong, no proof, labeled "theorem" | Thm 3.5 | open |
| M3 | Functoriality proof well-definedness gap (canonical k) | Thm 7.4 | partially addressed |
| M4 | Figures not included in paper | img/fig_shmap.tex, img/fig_shs.tex | open |
| M5 | Thm 6.4 (Collision Resistance) no proof | Thm 6.4, Appendix A.2 | open |
| M6 | Thm 2.1 states monoid but proves only quotient monoid | Thm 2.1 proof | open |
| M7 | Example 2.2 representation multiplicity broken (Fermat's little theorem) | Ex 2.2 | open |
| M8 | Thm 6.2 proof Step 3: seed l non-uniform, need explicit independence argument | Thm 6.2 | open |

**MINOR issues (18)**: m1 notation conflict cisb/Bernoulli, m2 abstract bound three-hop chain, m3 encode/Encode duplicates, m4 Algorithm 1 no termination bound, m5 Prop 2.1 "security" undefined, m6 Thm 6.3 random oracle assumption not in statement, m7 Prop 4.2 no proof/no formal security model, m8 Thm 4.1 proof is non-proof, m9 Def 5.1 vs Algorithm 1 inconsistency, m10 Appendix A no new content, m11 never cites own foundational papers, m12 acknowledgments placeholder, m13 \date{\today} unfixed, m14 three bib entry type errors, m15 nine uncited bib entries, m16 Def 3.1 e(x) random variable vs fixed probability, m17 Thm 7.3 stated but not proved, m18 Thm 7.4 same canonical k assumed without justification. All open.

### Trapdoor Reframing (design doc approved 2026-02-22)

DESIGN-trapdoor-reframing.md approved. Key decisions:
- Rename paradigm from "oblivious computing" to "trapdoor computing"
- Replace informal obliviousness bullets with four formal properties: Totality, Representation Uniformity, Correctness (eta-bounded), Composability
- Introduce trusted/untrusted machine model
- Reframe epsilon from "false positive rate" to noise decode probability / space parameter
- Major rewrite of Section 4; terminology changes throughout Sections 1, 5-10
- Mathematical results, SHM construction, composition theorem, space analysis unchanged
- Proposed new title: "Cipher Maps: A Framework for Trapdoor Computing Through Algebraic Structures and Bernoulli Models"

## Overview

This is the most developed paper in the trapdoor-computing repo, currently on hold pending the trapdoor formalism rewrite. It was created by merging two earlier papers (algebraic_cipher_types + cipher_maps) and has been through two papermill reviews. All CRITICAL issues from Review 1 are resolved. Review 2 identified 8 MAJOR and 18 MINOR issues, the most consequential being the lack of a formal obliviousness definition (M1), which the approved trapdoor reframing design doc addresses. The paper is 17 pages, uses standard LaTeX (pdflatex + bibtex, 3-pass build via `make`), and contains 13 definitions, 11 theorems, 4 propositions, 1 corollary, 4 examples, 1 algorithm, and 16 bibliography entries.

## Structure

| # | Section | Status |
|---|---------|--------|
| 1 | Introduction (Contributions, Organization, Related Work) | Complete |
| 2 | Algebraic Foundations: Cipher Functors | Needs revision (M6: Thm 2.1, M7: Ex 2.2) |
| 3 | Bernoulli Model Framework | Needs revision (M2: Thm 3.5, m16: Def 3.1) |
| 4 | Cipher Maps: Unifying Oblivious Bernoulli Approximations | Major rewrite pending (M1: trapdoor reframing) |
| 5 | The Singular Hash Map Construction | Needs figures (M4), fix Def 5.1 vs Alg 1 (m9) |
| 6 | Theoretical Analysis | Minor gaps (M5: Thm 6.4, M8: Thm 6.2 Step 3) |
| 7 | Connections Between Frameworks | Functoriality gap (M3), m17: Thm 7.3, m18: Thm 7.4 |
| 8 | Applications | Too thin -- bulleted lists, no formal results |
| 9 | Future Directions | OK |
| 10 | Conclusion | OK |
| A | Extended Proofs | A.1 duplicative; A.2 incomplete |
| B | Additional Examples | Thin -- expand or remove |

## Next Actions (Priority Order)

### High Priority (blocks submission)
- [ ] M1: Implement trapdoor reframing per DESIGN-trapdoor-reframing.md -- rewrite Section 4 with four-property definition, trusted/untrusted model
- [ ] M6: Fix Thm 2.1 -- restate for quotient monoid c_A S/~ (proof already works)
- [ ] M7: Fix Example 2.2 -- use ElGamal-style (g^r, a*h^r) pairs for multiple representations
- [ ] M2: Fix Thm 3.5 -- relabel as definition, correct entropy formula to use prior distribution

### Medium Priority (required for rigorous venue)
- [ ] M3: Fix Thm 7.4 functoriality -- choose quotient category or fixed canonical k=0
- [ ] M5: Complete Thm 6.4 proof -- Claim 1: cite birthday bound; Claim 2: counting argument; Claim 3: PRF assumption
- [ ] M8: Fix Thm 6.2 Step 3 -- add sentence on independence of h(x) for non-members under RO model
- [ ] M4: Include figures in Section 5 with proper figure environments

### Lower Priority (polish)
- [ ] Weave in or prune uncited bibliography entries
- [ ] Fix bib entry types (goldreich, elgamal, brakerski)
- [ ] Unify \encode/\Encode commands
- [ ] Add worked numerical example for Algorithm 1
- [ ] Add random oracle assumption to theorem statements (Thm 6.2, 6.3, 6.4)
- [ ] Cite own foundational paper series
- [ ] Fix Def 3.1 e(x) random variable vs fixed probability
- [ ] Expand Section 8 (Applications) with at least one formal proposition
- [ ] Fix \date{\today} to fixed date
- [ ] Complete or remove acknowledgments placeholder
- [ ] Select target venue
