# Plan: Chapter 1, Computing on Opaque Encodings

**Date:** 2026-06-17
**Chapter:** 1 (Part I, The Paradigm)
**Design specs:** `specs/2026-06-10-master-design.md`, `specs/2026-06-16-part1-design.md`
**Base SHA:** bf7a374
**Build:** `cd book && make` (pdflatex + biber + pdflatex x2)

## Goal

Draft Chapter 1 (~12 pp), the book's voice-setting opener. Open on the
concrete oblivious-service scenario, introduce the trusted/untrusted lens
and the central question, establish the measurable-not-negligible stance,
and roadmap the book. No formalism (no tuple, no theorem); those land in
Part II. Written lift-ready: self-contained, forward-references in
footnotes only.

## Architecture / tech stack

LaTeX `book` class; `book/notation.sty` (canonical macros, mirrors spine
sec 8); biblatex/biber over `book/references.bib`. The chapter is one file,
`book/chapters/ch01-opaque-encodings.tex`, with `\section` per 1.1-1.5.
Part I includes it via `book/parts/part1.tex`.

## Source material (reformulate, do not copy)

| Source | Use for |
|---|---|
| Existing stub `chapters/ch01-overview.tex` | Seed for 1.1/1.4 (already states the paradigm, trusted/untrusted, measurable-not-negligible, hash+uniformity). Reuse the framing; expand. |
| `../formalism/cipher-map-formalism.md` sec 1 (1.1 Setting, 1.3 Four Properties) and the capability-blocking **table near line 713** ("Distinguish real from filler / ... | Property | mechanism") | 1.2 the four cannots (the table is the canonical source, match it; do not invent a different list), and the trusted/untrusted setting. AUTHORITY on shared definitions. |
| `../foundations/` (bernoulli-model.md, trapdoor-boolean-algebra.md, entropy-maps.md, noisy-gates.md, README.md) | 1.1 intuition and the authentic origin; 1.5 provenance pointers. NOTE: `trapdoor-boolean-algebra.md` carries the inverted-homophonic erratum, do not echo `1/D(x)`. |
| `../papers/maximizing-confidentiality/` (the Entropy Ratio, corrected) | 1.3 the entropy-ratio tease in its CORRECTED image-relative form. |

## Lessons inherited (apply to every task)

- **Banned phrases (soul hook):** no U+2014 em-dash character (use `---` in
  LaTeX, commas/colons/parens in prose); avoid the soul plugin's banned
  buzzwords (notably the verb meaning "to use to maximum advantage", the one
  that begins with "lev"). The hook reports the offender if tripped.
- **Page budget:** ~12 pp total; per-section budgets below. If 1.2 or 1.3
  runs long, tighten prose, do not add a section.
- **Cross-ref discipline (build-critical):** forward-references point ONLY
  to the existing **part labels** (`part:abstraction`, `part:algebra`,
  `part:confidentiality`, `part:constructions`, `part:frontiers`), never to
  chapter/definition/theorem labels in later parts (they do not exist yet;
  `\cref` to them breaks the build). Forward-refs go in footnotes, in prose
  ("formalized in \Cref{part:abstraction}").
- **Landmines:** 1.3 uses image-relative delta (`TV(Q,U_im)`,
  `H*=log2|im(enc)|`), NOT ambient `B^n` (harvest BP-1). If homophonic is
  mentioned anywhere, `K(x) propto D(x)`, never `1/D(x)`. No ORAM /
  DP / simulation / game definitions (that is Chapter 2's guardrail; do not
  pre-empt it incorrectly here).
- **No theorems, no proofs, no exercises.** The four properties appear as a
  named prose preview list, not a numbered definition.
- **Header comment block:** every chapter/section file opens with the
  cross-reference block (labels DEFINED, labels REFERENCED), per the book
  convention.

## File structure

- Rename `chapters/ch01-overview.tex` -> `chapters/ch01-opaque-encodings.tex`
  (the stub's content is the seed; rewrite it). Update the `\input` in
  `parts/part1.tex`.
- One file, `\chapter{Computing on Opaque Encodings}\label{ch:opaque-encodings}`,
  with five `\section`s.

## Cross-reference map

**Defines:** `ch:opaque-encodings`; `sec:oblivious-service`,
`sec:untrusted-sees`, `sec:measured-not-negligible`, `sec:book-shape`,
`sec:ch1-notes`.
**References (footnote, part labels only):** `part:abstraction` (the tuple
and four properties), `part:confidentiality` (the entropy ratio, two
scales), `part:constructions` (the realized constructions),
`part:frontiers`. Plus `\nocite`-free real `\cite`s (see Task 6).

## Tasks

### Task 1, Scaffold
Rename the stub to `ch01-opaque-encodings.tex`; update `parts/part1.tex`
`\input`. Write the header comment block (DEFINES/REFERENCES per the map),
`\chapter{Computing on Opaque Encodings}\label{ch:opaque-encodings}`, and
five empty `\section{...}\label{...}` stubs in order. Remove the old
`\nocite{...}` placeholder once Task 6 adds real cites. Build must stay
clean with empty sections.
Budget: n/a. Commit: `monograph: ch01 scaffold (rename overview -> opaque-encodings)`.

### Task 2, Section 1.1 The oblivious service (~3 pp)
Checklist: open on the scenario (a search engine that cannot read your
queries or its own answers); the trusted machine `T` holds enc/dec, the
untrusted machine `U` evaluates total functions on opaque bit strings;
"opaque bits through opaque lookup tables"; light notation sidebar
introducing `enc`, `dec`, `T`, `U` at first use (match notation.sty); name
the object at the end, the *cipher map* (informally, no tuple). Plant the
trusted/untrusted thread. Lift-ready: stands without the later parts.
Commit: `monograph: ch01 sec 1.1 (the oblivious service)`.

### Task 3, Section 1.2 What the untrusted machine sees (~3 pp)
Checklist: the central question (how much does `U` learn?); totality as the
first privacy mechanism; the four cannots, MATCHED to the spine capability
table (~line 713): cannot decode, cannot distinguish a real query from
filler, cannot determine the domain / which in-domain inputs are real,
cannot tell a correct result from noise (eta-deniability). State them as a
named prose list, each paired with the property that blocks it (preview of
the four properties, not a definition). Harvest BP-2: this is the canonical
four-cannots list; note in HARVEST.md if it diverges from any paper's.
Commit: `monograph: ch01 sec 1.2 (what the untrusted machine sees)`.

### Task 4, Section 1.3 Measured, not negligible (~3 pp)
Checklist: the stance separating this from cryptography-as-usual,
confidentiality is a measured quantity, not an asymptotic negligible-
advantage claim; contrast the two idioms fairly; tease the entropy ratio
`e = H/H*` in its CORRECTED image-relative form (`H* = log2|im(enc)|`),
one sentence, with a footnote pointing to \Cref{part:confidentiality} for
the development. Plant the measurable-not-negligible thread. No Fannes, no
formal QIF machinery (that is Part IV).
Commit: `monograph: ch01 sec 1.3 (measured, not negligible)`.

### Task 5, Section 1.4 The shape of the book (~2 pp)
Checklist: the through-line in one place (one abstraction unifies a family
of constructions; confidentiality at two scales; composition predictable;
privacy = hash + uniformity); a short six-part roadmap; forward-pointers to
the part labels only. Lift-ready note: the position-paper version drops
this section and substitutes a one-paragraph contributions list (record in
HARVEST.md EC-1).
Commit: `monograph: ch01 sec 1.4 (the shape of the book)`.

### Task 6, Section 1.5 Notes and Provenance (~1 pp) + bib
Checklist: the authentic 2023-2024 `foundations/` sources named; the
synthesis note (formal development and full proofs live in later parts and
the standalone papers); QIF citations. ADD to `book/references.bib` (reuse
the Entropy Ratio `references.bib` entries verbatim where they exist):
`smith2009foundations`, `alvim2020science`; confirm `shannon1948mathematical`
or `shannon1949communication` is present. Replace the scaffold `\nocite`
with real `\cite`s here and in 1.1-1.4. Provenance: spine is authority;
note the `trapdoor-boolean-algebra.md` erratum.
Commit: `monograph: ch01 sec 1.5 (notes and provenance) + bib`.

### Task 7, Integration
Build clean (`cd book && make`): 0 undefined refs, 0 LaTeX warnings, all
forward-refs resolve to part labels. Verify page count (~12 pp for the
chapter; check the chapter's span in the PDF). Verify landmines (image-
relative delta in 1.3; no `1/D`; no ORAM/crypto drift). Update
`HARVEST.md` Part I section (EC-1 lift-readiness confirmed; any BP-2
finding from the four-cannots reconciliation). Quality pass: dispatch the
quality-auditor on the chapter to confirm the voice is locked (this is the
book's tone-setter). Commit:
`monograph: ch01 integration (build clean, harvest update)`.

## Out of scope (this chapter)
The cipher map tuple and any numbered definition; any theorem/proof; the
Fannes bridge and formal QIF measures; constructions; the Bernoulli model
beyond a one-line mention. All deferred per the part spec.

## Next step
`/bookwright:draft ch01` (or dispatch section-writer per task). Then
`/bookwright:plan ch02`.
