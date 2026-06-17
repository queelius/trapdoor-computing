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

### Part I: The Paradigm (DRAFTED 2026-06-17; ch1 ~4.5pp, ch2 ~3pp)
- **Extraction (EC-1):** both chapters drafted lift-ready. The position-paper spine is ch1 sec 1.1-1.4 (paradigm, the four cannots, measured-not-negligible, the four claims) + ch2 (the privacy-source thesis and the comparison table). An ~8-12pp position/overview paper can be lifted with light editing (drop the book roadmap 1.4, add a contributions paragraph).
- **Back-port findings, status:**
  - BP-1 (image-relative delta): ch1 sec 1.3 teases the entropy ratio with `H* = log2|im(enc)|`; verified, no ambient leak.
  - BP-2 (canonical four-cannots): ch1 sec 1.2 states them as decode / distinguish-real-from-filler / determine-domain / correct-from-noise, each paired with the blocking property, derived from the spine capability table. No divergence found while drafting; this is now a clean canonical form the papers can cite. ACTION: consider promoting it into the spine.
  - BP-3 (positioning table): ch2 sec 2.5 (`tab:not`) drafted (ORAM / FHE / garbled / SSE-PPE rows). ACTION: candidate to promote into the spine as a shared figure.
  - The access-pattern-drift correction (the no-ORAM guardrail) is now in the book, ch2 sec 2.1 and 2.3, with the rule "any argument resting on access-pattern indistinguishability has drifted" stated for the whole book.
- Fairness held: all ch2 contrasts are about threat-model difference, not "ours is better"; the homophonic mention uses `K(x) propto D(x)`, never `1/D(x)`.

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
