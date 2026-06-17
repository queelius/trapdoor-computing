# Monograph harvest log

Drafting the monograph is, by design, two things besides writing the book:
a **cross-paper QA pass** (it forces all eight papers into one frame, which
surfaces every place they disagree) and a **synthesis engine** (the
cross-cutting view exposes salient results no single paper isolated). This
log captures those two payoffs as they surface, so they feed the papers
instead of evaporating.

- **Extraction candidates**: salient papers the cross-cutting view reveals.
  Concentrated at the bookends (Part I and Part VI); Parts II-V consolidate
  papers that already exist, so they are not extraction sources.
- **Back-port findings**: inconsistencies or cleaner statements to push into
  a paper or the spine. Formal shared-definition issues are ALSO logged in
  `../formalism/cross-paper-consistency.md` (items C-n); this log is the
  monograph-driven feeder plus the paper-todo ledger.

Update rule: when a part is drafted, fill its section below before moving on.

---

## Extraction candidates

| ID | Candidate | From | Kind | Status |
|---|---|---|---|---|
| EC-1 | "Trapdoor Computing: Computing on Opaque Encodings" (the paradigm paper) | Part I | position / overview, ~8-12 pp | Part I is being written **lift-ready** (2026-06-16 part1 design). The program has no standalone paradigm paper today; this is the gap. Candidate venues: a security-magazine / CACM-style position piece, or an arXiv overview. |
| EC-2 | A frontiers / research-agenda paper | Part VI | SoK-adjacent / research agenda | Pending Part VI; seeded by `.papermill/prior-art/2026-06-09-ecosystem-survey.md`. |

## Back-port findings (monograph-driven)

| ID | Finding | Surfaced | Target | Cross-ref | Status |
|---|---|---|---|---|---|
| BP-1 | Image-relative delta (`delta = TV(Q, U_im)`, `H* = log2\|im(enc)\|`) must replace the ambient-`B^n` definition still in cipher-maps and the spine Property 2. | round-2 Entropy Ratio review; will be **forced** when Part IV (Ch 9) reconciles three deltas into one. | cipher-maps revision; spine Property 2 edit | `cross-paper-consistency.md` C-11 | open |
| BP-2 | The four "cannots" (decode / distinguish real-filler / determine domain / tell correct-from-noise) should have one canonical statement the papers cite back to; today it is scattered across cipher-maps sec 1 and the spine. | Part I design (Ch 1.2, Ch 2). | spine (promote a canonical list); cipher-maps + papers cite it | (new) | open, drafting Ch 1-2 will produce the canonical form |
| BP-3 | The "what trapdoor computing is not" comparison table (Ch 2.5) is the canonical positioning; consider promoting it into the spine as a shared figure the papers reuse. | Part I design (Ch 2). | spine (shared figure) | (new) | open, produced by drafting Ch 2 |

## Per-part harvest

### Part I: The Paradigm (designed 2026-06-16; not yet drafted)
- **Extraction:** EC-1 (the paradigm paper). Sections 1.1-1.4 are its spine; written self-contained so 1.1-1.3 stand without the book roadmap.
- **Back-port / reconcile while drafting:** BP-1 (the 1.3 entropy-ratio tease must use image-relative delta, not ambient), BP-2 (verify the four-cannots verbatim against the spine and produce the canonical list), BP-3 (the Ch 2 table). Fairness watch: keep the Ch 2 contrasts about threat-model difference, never "ours is better"; never echo the inverted `1/D(x)` homophonic erratum from the authentic `foundations/trapdoor-boolean-algebra.md`.

### Part II: The Cipher Map Abstraction
_(to fill when designed/drafted)_

### Part III: Algebra and Types
_(to fill)_

### Part IV: Confidentiality
_(to fill; this is where BP-1 gets forced)_

### Part V: Constructions
_(to fill)_

### Part VI: Frontiers
_(to fill; EC-2 lives here)_
