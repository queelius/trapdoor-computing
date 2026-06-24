---
title: "Cipher Closures: Cipher Data Structures and the Code-Data Duality in Trapdoor Computing"
stage: draft
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"
    affiliation: "Southern Illinois University Edwardsville"

metrics:
  pages: 14
  tex_lines: 1033
  sections: 10
  citations: 14
  last_built: 2026-06-03

thesis:
  claim: "In trapdoor computing the cipher map is a universal carrier for both code and data, and the cipher closure (a procedure capturing a secret and exposing an operation interface) makes the resulting code-data duality precise. Data is code: a cipher data structure is realized as a single cipher map, via the dispatch pattern (operation interface folded into a query tag) and designed orbits (sequential structure encoded in the shape of an orbit under a hash chain). Code is data: a cipher map is a point of the cipher exponential C(A->B). Cipher values, cipher maps, and cipher data structures are all cipher closures; cipher rekeying (transforming the captured secret) is one instance of the general move that everything in trapdoor computing is cipher data carried by cipher maps."
  novelty: "(1) The code-data duality for trapdoor computing, made precise via cipher closures (homoiconicity over a secret). (2) Designed orbits: XOR-orbit hash chains that encode lists, maps, and vectors inside a single cipher map, inverting the orbit-as-leakage reading of algebraic-cipher-types into an orbit-as-construction primitive. (3) The dispatch pattern: a multi-operation cipher data structure as one tagged cipher map. (4) An information-theoretic leakage analysis of orbit-encoded data structures (length and iteration order leak; per-element confidentiality bounded by the orbit-closure bound). (5) The unification: values, functions, data structures, and the secret are all cipher data, with the cipher exponential and cipher rekeying as the two known endpoints."
  refined: 2026-06-03

prior_art:
  last_survey: null
  key_references:
    - "abelson1996sicp: SICP closures-as-data, homoiconicity"
    - "landin1964mechanical: Landin SECD, closures as captured environments"
    - "towell2026cipher: cipher maps (the carrier); maps treated as functions, data structures not considered"
    - "towell2026algebraic: orbit closure (read as leakage only here) and the cipher exponential identity Prop 4.3 (code is data)"
    - "towell2026rekeying: cipher rekeying, the secret-as-data instance of the duality"
    - "wang2014oblivious: oblivious data structures (contrast: access-pattern hiding vs structure-as-cipher-map)"
    - "goldreich1996software: ORAM (contrast)"
  gaps: "Need: homoiconicity / reflection literature beyond SICP; functional data structures (Okasaki); oblivious data structure successors; possibly a hash-chain / authenticated-data-structure reference for the XOR-orbit construction. Confirm wang2014oblivious author list and venue before submission."

experiments: []

venue:
  target: null
  candidates:
    - "PLAS (Programming Languages and Analysis for Security, at CCS)"
    - "POPL / ICFP (for the homoiconicity / closures framing)"
    - "TCC (Theory of Cryptography Conference)"
    - "IACR ePrint (technical report)"

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher map abstraction (the universal carrier), four properties"
  - path: ~/github/trapdoor-computing/papers/algebraic-cipher-types
    rel: foundation
    label: "Orbit closure (Thm 5.3) and the cipher exponential identity (Prop 4.3, code is data)"
  - path: ~/github/trapdoor-computing/papers/cipher-rekeying
    rel: sibling
    label: "Cipher rekeying: the secret-as-data instance of the duality; source of the extracted dispatch/closure material"
---

## Notes

### Origin (2026-06-03)

Scaffolded after recognizing that the closure / cipher-data-structure /
dispatch-pattern material in the cipher-rekeying paper is a separable
contribution, not needed for any rekeying result, and is in fact the
thesis of an already-planned paper. The program had logged this twice:

- `FUTURE-RESEARCH.md` idea 2 ("XOR-orbit cipher iterators"), suggested
  artifact "Designed Orbits: Cipher Data Structures via Hash Chains",
  explicitly flagged "deserves to be a separate paper". Source files:
  the archived C++ notebook's `cipher_map_list.hpp`, `cipher_map_map.hpp`,
  `cipher_vec.hpp`. (Provenance only; the published paper must not cite
  the notebook, per the cipher-rekeying scrub.)
- `FUTURE-RESEARCH.md` idea 3 (selector-driven cipher Turing machines)
  and the cut cipher-TM section of algebraic-cipher-types: the "code as
  a fully general data structure" frontier, future work here.

The unifying frame (code-data duality / homoiconicity) is broader than
idea 2 as written: idea 2 is the data-to-code half (designed orbits);
the cipher exponential of algebraic-cipher-types (Prop 4.3) is the
code-to-data half; cipher rekeying is the secret-as-data instance. This
paper makes the cipher closure the homoiconic object that carries all
three.

### The duality (paper spine)

| direction | construction | home |
|---|---|---|
| data to code | data structure as a tagged cipher map (dispatch) / designed orbit (hash chain) | this paper, the new content |
| code to data | cipher map as a point of C(A->B) (cipher exponential) | algebraic-cipher-types Prop 4.3, recalled here |
| secret to data | cipher rekeying transforms the captured secret | cipher-rekeying, cited as an instance |

### Outline (10 sections, see paper/main.tex)

1. Introduction: code-data duality (SICP homoiconicity), the cipher map as universal carrier, three directions, contributions.
2. Preliminaries: cipher map tuple, cipher spaces, orbit closure, cipher closure definition.
3. Cipher Closures: three subclasses (value / map / data structure), the closure as the homoiconic object. [migrate + expand from cipher-rekeying]
4. Data is Code: The Dispatch Pattern: multi-op data structure as one tagged cipher map. [seeded from cipher-rekeying §3.2]
5. Designed Orbits: XOR-orbit hash chains encode lists/maps/vectors in one cipher map. [seeded from FUTURE-RESEARCH idea 2]
6. Leakage of Orbit-Encoded Data Structures: length, order, per-element confidentiality via the orbit bound.
7. Code is Data: The Cipher Exponential: C(A->B) = cipher maps (Prop 4.3); the reverse direction.
8. The Duality, Unified: the table; rekeying and the exponential as endpoints; mutability.
9. Related Work: homoiconicity, oblivious data structures (contrast), ORAM, QIF.
10. Conclusion: future work (random access, mutable orbit reshaping, cipher TMs).

### Status

Full draft (2026-06-03). `paper/main.tex` is a complete 14 pp manuscript:
all `\stub{}` placeholders replaced with real prose, the `\stub` macro
removed, the §4 dispatch seed and §5 XOR-orbit seed expanded into full
constructions. Builds clean (exit 0, 0 LaTeX errors, 0 undefined refs,
0 overfull boxes, no `??`, 14/14 citations resolving). Self-contained:
0 provenance leaks (no notebook/.hpp/class-name/filesystem references),
0 forbidden crypto macros, information-theoretic model throughout.

### Drafting pass (2026-06-03)

Expanded the skeleton end to end. Section construction and the
proved/recalled/conjectured/open ledger are recorded in
`drafts/2026-06-03/writing-plan.md`. Highlights:

- §1/§10 (bookends) written in lead-author voice: SICP cons/car/cdr
  framing, three directions, contributions, distinct positioning vs
  cipher-maps / algebraic-cipher-types / rekeying / cipher-program-
  construction. Conclusion separates proved results from the conjecture
  and the open problems.
- §2 recalls cipher map Def 3.1, the four properties, orbit-closure
  Def 5.1 + Thm 5.3 (cited as towell2026cipher / towell2026algebraic).
- §3 presents the three subclasses + cipher Boolean / cipher pair /
  mutable counter self-contained (the material rekeying now defers
  here via towell2026closures), each with its honest leakage caveat.
- §4 (dispatch) expanded: m-operation generalization, the tag-is-
  visible qualification, the shared cut boundary with
  towell2026cipherprog, four-properties carry-over.
- §5 (designed orbits) expanded: precise XOR-chain recurrence, history
  accumulator, sentinel termination, two-level maps, indexed vectors,
  single-map-many-structures, random-access open problem (Rem 5.1).
- §6 (leakage) is the rigorous core: Assumption 6.1 (random oracle);
  Prop 6.1 length leakage (PROVED); order leakage via sequentiality;
  Prop 6.2 per-element bound (PROVED, direct from Thm 5.3); Conjecture
  6.3 per-element hiding (MARKED OPEN, not overclaimed); collisions/
  cycles handled by construction-time sentinel placement.
- §7 recalls the cipher exponential (Prop 4.3) and makes the "two
  directions, one carrier" synthesis; §8 unifies (table + two charted
  endpoints + mutability = immutable-replay leakage profile).
- §9 related work: homoiconicity (SICP/Landin/McCarthy), ORAM +
  oblivious DS as orthogonal access-pattern axis (Goldreich-Ostrovsky,
  Path ORAM, Wang), functional DS (Okasaki), QIF (Shannon, Smith).

Bib grew 9 -> 14 (added towell2026cipherprog, mccarthy1960recursive,
okasaki1998purely, smith2009foundations, merkle1987digital,
stefanov2013path). Self-citation bibkey is towell2026closures (already
cited by the rekeying paper).

## Next Actions

1. Slim cipher-rekeying: remove the dispatch pattern and the heavy
   cipher-data-structure material; keep only the lightweight
   "closures over a secret" framing rekeying needs; demote its
   contribution 1 to point here.
2. Draft §5 (designed orbits) in full from FUTURE-RESEARCH idea 2:
   the list construction, two-level maps, indexed vectors, the
   single-map-many-structures point.
3. Draft §6 (leakage): prove the length / order / per-element bounds.
4. Draft §7 (code is data): restate the cipher exponential identity
   and make the two-directions-one-carrier point precise.
5. Prior-art survey: homoiconicity/reflection, oblivious + functional
   data structures; confirm wang2014oblivious metadata.
6. Decide title and directory final name (cipher-closures vs
   designed-orbits); register the canonical bibkey for self-citation.

## Provenance

Per the trapdoor-computing root CLAUDE.md: information-theoretic, not
ORAM/FHE/simulation-based. The orbit-closure bound and the cipher
exponential come from the ecosystem (algebraic-cipher-types). The
closure framing is from SICP. The category-theoretic language (functor,
exponential object) is organizing machinery, not load-bearing in
proofs. The XOR-orbit construction originates in the author's earlier
unpublished work; it is reformulated here in the mature cipher-map
framework and must be presented self-contained (no notebook reference
in the published paper).
