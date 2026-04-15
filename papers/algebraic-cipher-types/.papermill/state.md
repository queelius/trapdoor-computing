---
title: "Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing"
stage: revising
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"
    affiliation: "Southern Illinois University Edwardsville"

metrics:
  pages: 19
  tex_lines: ~1460
  sections: 10
  citations: 21
  last_built: 2026-04-12

thesis:
  claim: "Every algebraic operation the untrusted machine can perform on cipher values enlarges their orbit closure and, by information-theoretic bound, reduces confidentiality. Each algebraic type constructor (product, sum, exponential) therefore induces a quantifiable confidentiality cost, culminating in a sum-type impossibility (tag hiding and untrusted pattern matching cannot coexist), and a typed cipher-program discipline, realized concretely via expression-tree cut points, turns those costs into a design-time budget."
  novelty: "(1) Information-theoretic confidentiality bound via orbit closure, independent of construction and not derived from ORAM, FHE, functional encryption, or simulation-based definitions. (2) Sum-type impossibility theorem with direct implications for encrypted schema design. (3) Typed composition chains as a design-time confidentiality budget. (4) Expression-tree decomposition via @cipher_node cut points as the practical realization, with the cipher Turing machine as a second realization sharing the same cut-point structure."
  refined: 2026-04-12
  previous_claim: "Each algebraic type constructor (sum, product, exponential) imposes a specific, unavoidable trade-off between confidentiality and composability when applied to cipher values. Orbit closure under the available operations bounds adversarial knowledge."
  refinement_notes: "Reframed from 'three independent results' to 'one principle with three instances plus two realizations'. Replaced 'confidentiality vs composability' (wrong: composability holds throughout) with 'confidentiality vs untrusted structural access'. Elevated typed-chain discipline and expression-tree realization; demoted cipher TM from headline to second realization."

prior_art:
  last_survey: null
  key_references:
    - "towell2026cipher: Cipher maps (batch construction, four properties)"
    - "towell2026bernoulli: Bernoulli data types (accuracy-side algebraic analysis)"
  gaps: "Review flagged thin bibliography (6 cites in 15pp). Need information flow type systems (Sabelfeld & Myers 2003), functional encryption (BSW 2011), SSE (Curtmola 2006). Target 20-30 refs for PLAS."

experiments:
  - name: "Cipher Boolean search over 20 Newsgroups"
    status: integrated
    note: "Precision/recall + AND-chain FPR compounding finding (independence breaks)"
  - name: "Encoding granularity comparison"
    status: partial
    note: "Space column missing for 2/3 granularity levels (flagged M6)"

venue:
  target: null
  candidates:
    - "PLAS (Programming Languages and Analysis for Security, at CCS)"
    - "IACR ePrint (technical report)"
    - "TCC (Theory of Cryptography Conference)"

review_history:
  - date: 2026-04-08
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 2 | Major: 11 | Minor: 12 | Suggestions: 6"
    location: ".papermill/reviews/2026-04-08/"
    status: partially-addressed
    notes: "C1 (noise absorption), C2 (orbit confidentiality bound), and 3 major issues fixed in commits c052809 + a6b5c60. Remaining: experimental baselines/error bars, bibliography expansion, Discussion-section rebalance."
  - date: 2026-04-12
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 1 | Major: 12 | Minor: 18 | Suggestions: 14"
    location: ".papermill/reviews/2026-04-12/"
    status: partially-addressed
    notes: "Post-restructure review. C1 (candidate-set tautology, new critical finding) fixed by rewriting Section 5.3 in entropy form: conditional-entropy bound H(X|view) >= H(X) - log2 |orbit| as primary theorem, set-form bound conf >= 1 - |orbit|/|X| as corollary. Dropped the disconnected candidate-set definition. M1 (typed-chain arity mismatch) fixed by generalizing Def/Prop 5.4 to arbitrary arities with the correct bound sum N_i, N_{i+1} = N_i^{a_i}. Example 5.4 corrected. M11 (denominator switch) resolved by the entropy-form rewrite. LC-MIN-1/LC-MIN-2 (TM head direction framing, pairing cipher map) fixed by storing (state, symbol) as one cipher value per cell and making the head direction explicitly cleartext on output. M6 (bibliography) partially addressed: 21 cites now (up from 10), including all 7 previously dead entries plus 4 new refs (Smith 2009 QIF, Cash 2015 leakage attacks, Grubbs 2017, Lang 1995 20 Newsgroups). M8 (thin Section 6.3 synthesis) addressed by adding formal cut-point definition, explicit mapping to both realizations, and a regex-matching worked example. Remaining: M2/M3/M4/M5 (experimental baselines and error bars, FPR table, granularity space data), M7 (document class for PLAS), M9 (self-citations unpublished)."

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
  - path: ~/github/trapdoor-computing/papers/maximizing-confidentiality
    rel: sibling
    label: "Entropy-ratio confidentiality framework (same ecosystem)"
---

## Notes

Paper started 2026-03-28 from the algebraic_cipher_types notebook (2019-2022).
Restructured 2026-04-12 around one principle with three instances plus two
realizations. Current structure:

1. Introduction
2. Related Work
3. Preliminaries (cipher maps recap)
4. Cipher Type Constructors (static: void/unit, product, sum, exponential)
5. Orbit Closure and Information Leakage (dynamic: definition, monotonicity,
   confidentiality bound, examples, typed composition chains)
6. Realizing Cipher Programs
   6.1 Cipher Turing machines (brief: definition, space, head-movement
       leakage, ORAM comparison)
   6.2 Expression-tree decomposition (cipher-node annotation,
       granularity control, @cipher_node tracing implementation)
   6.3 Cut-point structure common to both realizations
7. Cipher Boolean Algebra and Evaluation
   7.1 Cipher Boolean type
   7.2 Noise unreliability (proposition + remarks + practical allocation)
   7.3 Experimental validation (Boolean search, FPR compounding,
       encoding granularity)
8. Discussion (relationships, encoding granularity principle, open
   questions)
9. Conclusion

Theoretical results (by label): Prop:product-tradeoff, Thm:sum-impossibility,
Thm:monotonicity, Thm:confidentiality-bound, Prop:typed-orbit,
Prop:cipher-tm-space, Prop:head-determinism, Prop:noise-unreliability.

Implementation (commit cc8ff90) integrates empirical results from the
`cipher-maps` Python library: Boolean search over 20 Newsgroups, AND-chain
FPR compounding (notable because empirical FPR exceeds the Bernoulli
independence prediction by ~1 order of magnitude at k=3).

## Review Summary (2026-04-08)

Multi-agent editorial review recommended major-revision. Strengths:
introduction positioning against ORAM/FHE/garbled circuits, the elegance
of the sum-type impossibility, and honesty about limitations (component-wise
encoding leaks correlations, no simulation-based security).

Critical issues fixed in post-review commits:
- **C1** Proposition 6.1 (noise absorption): reformulated
- **C2** Theorem 4.3 (confidentiality bound): orbit correctly integrated
  into candidate-set definition, single formula as the theorem
- **M1** Sum-type impossibility: balanced-prior assumption made explicit
- **M3** Discussion overload: Related Work + Conclusion split out

Still outstanding from the review:
- **M2** Bibliography thin (6 cites); need IFC, FE, SSE refs; unused .bib
  entries to be cited or removed
- **M4** Table 1 lacks baselines and error bars (5+ seeds, mean ± SD)
- **M5** FPR compounding reported in prose only; needs table/figure
- **M6** Encoding granularity table missing space for 2/3 levels

## Next Actions

1. **Experiments (carries forward as M2/M3/M4/M5 in the 2026-04-12
   review)**: re-run the 20 Newsgroups Boolean search in the
   `cipher-maps` library with (a) a plaintext baseline and a Bloom-filter
   baseline in Table 1, (b) 5+ seeds with mean and standard deviation,
   (c) a new Table 2 for FPR-vs-chain-length for both AND and OR chains
   (k=1..5), (d) measured space for the intermediate and leaf
   annotations in the granularity table. The paper's one genuinely
   novel empirical finding is buried in prose; promote it to a table.
2. **Venue commitment and document class (M7)**: if PLAS, create a
   submission branch with `\documentclass[sigconf,nonacm=true]{acmart}`,
   add CCS concepts, verify page count under the acmart template. If
   IACR ePrint or arXiv is the target instead, current article class
   is fine.
3. **Self-citations (M9)**: post `towell2026cipher` and
   `towell2026bernoulli` to IACR ePrint or arXiv before final
   submission so the load-bearing preliminaries are publicly
   verifiable; alternatively expand §3 Preliminaries with the verbatim
   composition theorem and representation-uniformity statements so
   this paper is self-contained.
4. **Optional strengtheners** from the 2026-04-12 review's suggestions:
   add an explicit definition of $\cipher{X}$ in Preliminaries
   (LC-MIN m2), rename the Turing-transition $\delta_T$ to avoid
   notation clash with TV-distance $\delta$ (LC-MIN m1), qualify the
   "zero errors on the full domain" sentence as "as expected from the
   PHF construction" (LC-MIN-5).

## Restructure Log (2026-04-12)

Reorganized the paper around a clearer thesis. Changes to structure,
not to the underlying results:

- Added new §6 "Realizing Cipher Programs" as the unifying home for
  two realizations. §6.1 compresses the old §6 Cipher Turing Machine
  from ~180 lines to ~60. §6.2 promotes the expression-tree /
  @cipher_node material from the old Discussion to a proper
  subsection. §6.3 is new prose making the cut-point pattern explicit.
- Promoted old §7.2 "Cipher Boolean Algebra" from subsection to full
  section §7, with three subsections (type / noise unreliability /
  experimental validation) so evaluation has its own heading.
- Created new §8 "Discussion" holding the three Relationship
  paragraphs (previously inlined in old §7.1) and the Open Questions
  block. Added a fifth open question about cut-point placement as
  constrained optimization.
- Updated abstract, intro contributions list, and conclusion to match.
  Cipher TM drops from the headline; typed-chain discipline and
  expression-tree realization are elevated.
- All theorem/proposition/definition labels preserved; the four
  dropped labels (sec:cipher-tm-def, sec:cipher-tm-space,
  sec:head-leakage, and the subsection-label form of sec:cipher-bool)
  were not referenced from elsewhere in the paper.
- PDF builds clean at 17 pages with no undefined references.

## Second-Round Fixes (2026-04-12, post-review)

After the second multi-agent review:

- **§5.3 confidentiality bound rewritten in entropy form.** Dropped
  the candidate-set detour (whose orbit-containing clause was a
  tautology, per C1 in the second review) in favour of a conditional
  entropy bound $H(X \mid \mathcal{V}_F(c)) \geq H(X) - \log_2
  |\mathrm{orbit}_F(c)|$ as the primary theorem, with the set-form
  bound $\mathrm{conf}_F(c) \geq 1 - |\mathrm{orbit}_F(c)|/|X|$ as a
  corollary. This also resolves the M11 denominator switch.
- **§5.5 typed-chain proposition generalized** (M1). The chain
  signature now carries explicit arity $a_i$, and the orbit bound is
  $\sum_i N_i$ with $N_0 = m$, $N_{i+1} = N_i^{a_i}$. Unary ($a_i=1$)
  and single-value-start ($m=1$) cases recover the previous $m(k+1)$
  and $1+k$ bounds respectively. Example 5.4 updated to reflect the
  binary-AND arity explicitly.
- **§6.1 cipher TM definition cleaned** (LC-MIN-1, LC-MIN-2). Each
  tape cell is now a single cipher value in $\cipher{Q \times \Gamma}$
  with a distinguished state marking the head, eliminating the implicit
  pairing cipher map. Head direction is explicitly cleartext on the
  output pair $(c', d)$.
- **§6.3 cut-point synthesis strengthened** (M8). Added a formal
  Definition 6.3 of cut point and cut-point set, explicit mapping of
  each realization onto this structure, explicit statement of what the
  typed-chain bound says in each case, and a worked regex-matching
  example that plays the same computation out as both a cipher TM and
  an expression tree.
- **Bibliography expanded** (M6). 21 cites (up from 10). All 7
  previously dead entries now cited: Bloom 1970 (cipher Boolean as
  Bloom-like), Fredman et al. 1984 (PHF backing), Shannon 1948
  (source coding for the allocation), Song et al. 2000 (original SSE),
  Islam et al. 2012 (access-pattern attacks), Turing 1936 (cipher TM
  preliminaries), towell2026maxconf (sibling work). Four new:
  Smith 2009 (quantitative information flow, grounding the
  entropy-form bound), Cash et al. 2015 and Grubbs et al. 2017
  (SSE leakage-abuse attacks), Lang 1995 (20 Newsgroups dataset).
- **PDF now 19 pages, builds clean, no undefined references.**
