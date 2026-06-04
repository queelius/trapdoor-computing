# Cipher Closures: drafting pass writing plan (2026-06-03)

Lead author: orchestrator (direct authorship). The constructions required
tight coherence with precise foundational statements recalled verbatim from
the ecosystem (cipher map Def 3.1, orbit-closure Thm 5.3, cipher exponential
Prop 4.3), so sections were written in one coherent voice rather than
dispatched to parallel specialists. The skeleton already supplied the
abstract, the dispatch seed (S4), and the XOR-orbit seed (S5).

## Section assignment table

| Section | Role | Source / dependency | Status |
|---|---|---|---|
| 1 Introduction | bookend (orchestrator voice) | full-draft framing; SICP cons/car/cdr; three directions; contributions; positioning | written |
| 2 Preliminaries | formal recall | cipher map Def 3.1 (towell2026cipher), four properties, orbit-closure Def 5.1 + Thm 5.3 (towell2026algebraic); cipher closure def kept from skeleton | written |
| 3 Cipher Closures | formal + examples | three subclasses (value/map/data-structure); cipher Boolean, cipher pair (cons/car/cdr), mutable counter, with honest leakage caveats; self-contained reframe of material rekeying defers here | written |
| 4 Dispatch Pattern | method (EXPAND seed) | kept seed tagged-map equations; generalized to m-operation closures; related to expression-tree cut points of towell2026cipherprog / towell2026algebraic (same boundary, two views); four-properties carry-over | expanded |
| 5 Designed Orbits | method (EXPAND seed) | kept seed XOR-orbit list; developed advance step, sentinel, history accumulator; two-level maps, indexed vectors, single-map-many-structures; random-access open problem (Rem 5.1) | expanded |
| 6 Leakage | results / formal | Assumption 6.1 (random oracle); Prop 6.1 length leak (proved); order leak (sequentiality); Prop 6.2 per-element via Thm 5.3 (proved); Conjecture 6.3 per-element hiding (marked open); collisions/cycles via sentinel; constructive-vs-destructive duality | written |
| 7 Cipher Exponential | formal recall + synthesis | Prop 7.1 = Prop 4.3 (recalled, not reproved); "two directions, one carrier" synthesis; categorical language flagged as bookkeeping | written |
| 8 Duality Unified | results / synthesis | kept/expanded skeleton table; rekeying + exponential as two charted endpoints; mutability via captured cells; mutable closure orbit-profile = immutable replay | written |
| 9 Related Work | literature | homoiconicity (SICP, Landin, McCarthy); ORAM/oblivious DS (Goldreich-Ostrovsky, Path ORAM, Wang) as orthogonal access-pattern axis; functional DS (Okasaki); QIF (Shannon, Smith) | written |
| 10 Conclusion | bookend (orchestrator voice) | what was shown (not just done); proved-vs-conjecture split restated; future work: random access, mutable orbit reshaping, cipher TMs | written |

## Provenance discipline (verified clean)

- 0 references to C++ notebook, .hpp files, class names, filesystem paths,
  "reference library", "the implementation", "FUTURE-RESEARCH".
- 0 forbidden crypto macros (\Adv, \Simulator, \Trace, \PPT).
- Privacy model information-theoretic throughout (one-way hash + uniform
  representation + finite orbit). Category theory flagged as organizing
  device, not load-bearing (Intro scope para, S7 closing para).

## Honesty ledger

- PROVED: Prop 6.1 (length leakage = H(L) <= log2(n+1)); order leakage
  (chain sequentiality); Prop 6.2 (per-element H(Xi|V) >= H(Xi) - log2(L+1),
  direct from Thm 5.3).
- RECALLED (not reproved): Thm 2.1 (= Thm 5.3), Prop 7.1 (= Prop 4.3),
  cipher map four properties.
- CONJECTURE (marked): Conjecture 6.3 (per-element hiding up to orbit bound)
  -- not proved; cross-element correlations from shared f-hat + accumulator
  not controlled by the counting bound.
- OPEN PROBLEMS (marked): oblivious random access for cipher vector
  (Rem 5.1); tighter orbit bound for hash-chain advance; min-entropy/
  g-leakage forms; mutable orbit reshaping; cipher Turing machines.

## Bibliography additions this pass

towell2026cipherprog (sibling positioning), mccarthy1960recursive
(homoiconicity root), okasaki1998purely (functional DS), smith2009foundations
(QIF refinements), merkle1987digital (hash chains; available, used implicitly
via random-oracle framing), stefanov2013path (Path ORAM, modern ORAM contrast).
All verified to exist; 14 entries, bibtex 0 warnings.

## Build

`cd paper && make` -> exit 0, 14 pp, 0 LaTeX errors, 0 undefined refs,
0 overfull boxes, no `??` in PDF, 0 remaining stubs.
