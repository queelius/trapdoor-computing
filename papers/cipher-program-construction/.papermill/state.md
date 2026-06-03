---
title: "Realizing Cipher Programs: Cut-Point Decomposition and Control-Flow Obliviousness"
stage: scaffold
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"
    affiliation: "Southern Illinois University Edwardsville"

metrics:
  pages: 8
  sections: 5
  figures: 1
  citations: 3
  last_built: 2026-06-03

origin: >
  Spun out of papers/algebraic-cipher-types on 2026-06-03. The
  expression-tree -> cipher-program realization material (former §6 of
  that paper) was a distraction there: that paper is about cipher TYPES
  and their leakage, constructs cipher maps only to analyze trade-offs,
  and never evaluates whole-program realization. The realization story
  (propagation, cut points, branching/control-flow obliviousness,
  automatic rewriting) is the subject here. Seed of the migrated §6 is at
  /tmp/sec6_migration.tex (adapted at /tmp/sec6_adapted.tex) at spin-out
  time; the adapted version is embedded as §3 of this paper.

thesis:
  claim: >
    Realizing an ordinary program as a composition of cipher maps is
    governed by a calculus of what is forced, what is chosen, and what
    each choice costs. Ciphering is upward-closed (a cut forces all
    consuming ancestors and sibling inputs to cipher); control flow forces
    an expose-or-hide choice with no oblivious short-circuit (branching is
    untrusted dispatch on a sum type); unbounded data-dependent control
    cannot be made oblivious and leaks the execution trajectory. Within
    these laws, cut-point placement is a multi-dimensional optimization
    over space, build time, and leakage, automatable for the
    straight-line / bounded-conditional fragment.
  novelty: >
    (1) The upward-closure / propagation law for cut-point placement.
    (2) The no-oblivious-short-circuit proposition (operational form of
    the sum-type impossibility) and the three control-flow regimes
    (bounded fixed-shape, total-but-partial, unbounded data-dependent),
    with the boundary "oblivious iff fixed data-independent computation
    graph" and unbounded control = the cipher Turing machine.
    (3) A cost model (oblivious mux O(|R|^2), fuse O(|X|)) and the
    per-node/per-argument decision space. (4) A tracing-based rewriter for
    the tractable fragment.

prior_art:
  key_references:
    - "towell2026algebraic: algebraic cipher types (algebra, sum impossibility, orbit, typed chains). Parent paper."
    - "towell2026cipher: cipher maps foundation (four properties, batch/PHF construction Sec 6)."

venue:
  target: null
  candidates:
    - "PLAS / PL+security venue (compilation + obliviousness framing)"
    - "IACR ePrint / arXiv (technical report)"

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/algebraic-cipher-types
    rel: parent
    label: "Source of §3; owns the cipher-type algebra, sum impossibility, orbit bound, typed chains."
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher map four properties + batch/PHF construction (Sec 6)."
  - path: ~/github/trapdoor-computing/src/cipher-maps
    rel: implementation
    label: "Python reference: @cipher_node tracing rewriter for the straight-line/bounded fragment."
---

## Notes

Scaffold created 2026-06-03 by spinning the whole-program-realization
material out of algebraic-cipher-types. Builds clean at 8 pages.

Structure:
1. Introduction (difficulties-first: the five obstacles the paper is organized around)
2. Background (cipher maps + the algebra/orbit, both cited from the two parent papers)
3. Programs as Cipher-Map Compositions (MIGRATED from algebraic-cipher-types §6):
   3.1 Expression-Tree Decomposition (Def cipher node, granularity, propagation remark, the figure)
   3.2 Branching and the Limits of Oblivious Control (no-short-circuit Prop, three regimes, mux cost)
   3.3 Cut-Point Structure (Def cut point, regex example)
4. Automatic Rewriting and the Decision Space (tracing, the decision space, reference implementation)
5. Open Problems

## Migration adaptation done

The migrated §3 had ~12 cross-references into algebraic-cipher-types
(thm:sum-impossibility, prop:typed-orbit, prop:product-tradeoff, etc.);
all were converted to \cite{towell2026algebraic} with descriptive text.
Internal labels (def:cipher-node, fig:cipher-tree, sec:branching,
sec:tm-vs-tree, rem:cipher-propagation, prop:no-short-circuit,
rem:mux-cost, def:cut-point, ex:regex-cut-points, rem:shared-vars,
sec:cipher-programs, sec:realizing) resolve internally. The self-citation
towell2026cipherprog was removed.

## Next Actions

1. This is a SCAFFOLD, not a finished paper. §1/§2/§4/§5 are freshly
   written but thin; §3 is migrated and may read as a "section in another
   paper" in places (it was). A real drafting pass should reconcile voice.
2. The §4 tracing-rewriter description and the reference-implementation
   claims should be checked against the actual cipher-maps library
   (src/cipher-maps): does it still have the @cipher_node tracer, combiner
   synthesis, and branch-all-paths handling? Cite a commit/tag.
3. No git remote yet; no mf paper_db entry; not in any series. Decide
   whether this becomes a real submission target before investing more.
4. Open problems (§5) are genuine and could each seed a result: cut-point
   optimization complexity, plain-ops-on-cipher-bytes leakage
   characterization, bounded oblivious loops, verified obliviousness.
