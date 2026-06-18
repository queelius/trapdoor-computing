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
| BP-1 | Image-relative delta (`delta = TV(Q, U_im)`, `H* = log2\|im(enc)\|`) must replace the ambient-`B^n` definition still in the spine Property 2 headline (line ~95) and cipher-maps. | round-2 Entropy Ratio review; **forced in Ch 4.2** (`def:uniformity` defines delta for the whole book). | spine Property 2 headline edit; cipher-maps Property 2 | `cross-paper-consistency.md` C-11 | **DONE 2026-06-18**: book Ch 4.2 + spine Property 2 + cipher-maps def (image-relative) |
| BP-2 | The four "cannots" (decode / distinguish real-filler / determine domain / tell correct-from-noise) should have one canonical statement the papers cite back to; today it is scattered across cipher-maps sec 1 and the spine. | Part I design (Ch 1.2, Ch 2). | spine (promote a canonical list); cipher-maps + papers cite it | (new) | open, drafting Ch 1-2 produced the canonical form |
| BP-3 | The "what trapdoor computing is not" comparison table (Ch 2.5) is the canonical positioning; consider promoting it into the spine as a shared figure the papers reuse. | Part I design (Ch 2). | spine (shared figure) | (new) | open, produced by drafting Ch 2 |
| BP-4 | Composition is `eta_total <= 1 - prod(1-eta_i)` (**inequality**: a stage error can be masked downstream), not `=`. | cipher-maps R3 review (equality/inequality flag); **landed in Ch 4.4** (`thm:composition`, full proof). The spine's FORMAL Property 4 (line ~125) is already `<=`; its headline (line ~122) and a cipher-maps draft write `=`. | spine Property 4 headline; cipher-maps headline wherever `=` | `cross-paper-consistency.md` C-12 | **DONE 2026-06-18**: book Ch 4.4; spine `=`->`<=` (C-12); cipher-maps Thm 7.1 already `<=` |

## Per-part harvest

### Part I: The Paradigm (DRAFTED 2026-06-17; ch1 ~4.5pp, ch2 ~3pp)
- **Extraction (EC-1):** both chapters drafted lift-ready. The position-paper spine is ch1 sec 1.1-1.4 (paradigm, the four cannots, measured-not-negligible, the four claims) + ch2 (the privacy-source thesis and the comparison table). An ~8-12pp position/overview paper can be lifted with light editing (drop the book roadmap 1.4, add a contributions paragraph).
- **Back-port findings, status:**
  - BP-1 (image-relative delta): ch1 sec 1.3 teases the entropy ratio with `H* = log2|im(enc)|`; verified, no ambient leak.
  - BP-2 (canonical four-cannots): ch1 sec 1.2 states them as decode / distinguish-real-from-filler / determine-domain / correct-from-noise, each paired with the blocking property, derived from the spine capability table. No divergence found while drafting; this is now a clean canonical form the papers can cite. ACTION: consider promoting it into the spine.
  - BP-3 (positioning table): ch2 sec 2.5 (`tab:not`) drafted (ORAM / FHE / garbled / SSE-PPE rows). ACTION: candidate to promote into the spine as a shared figure.
  - The access-pattern-drift correction (the no-ORAM guardrail) is now in the book, ch2 sec 2.1 and 2.3, with the rule "any argument resting on access-pattern indistinguishability has drifted" stated for the whole book.
- Fairness held: all ch2 contrasts are about threat-model difference, not "ours is better"; the homophonic mention uses `K(x) propto D(x)`, never `1/D(x)`.

### Part II: The Cipher Map Abstraction (DRAFTED 2026-06-18; ch3 ~5pp, ch4 ~5pp, ch5 ~4pp; KEYSTONE COMPLETE)
- **Harvest is back-port; extraction N/A** (Part II consolidates the cipher-maps paper, the PoPETs target).
- **Back-port findings, status:**
  - **BP-1 (image-relative delta): LANDED** in ch4 sec 4.2 (`def:uniformity`): `delta = TV(Q, U_im)`, `U_im = Uniform(im(enc))`, `H* = log2|im(enc)|`, with the worked `ex:delta-watchlist` (0.15 -> 0 under `K propto D`) and the homophonic identity `delta = TV(D, K/N) <= (|X|-1)/N`. ch3 sec `sec:totality-support` + `ex:watchlist-numbers` set up the populated-support distinction the definition rests on. The spine's Property 2 headline (line ~95) still carries the ambient `Uniform({0,1}^n)` form. **ACTION:** edit spine Property 2 + cipher-maps Property 2 to image-relative (C-11).
  - **BP-4 (composition `<=` not `=`): LANDED** in ch4 sec 4.4 (`thm:composition`) with a full short proof; stated as an inequality because a stage error can be masked by a downstream stage. The spine's formal box (line ~125) already has `<=`; its headline (line ~122) writes `=`. **ACTION:** align the spine headline and any cipher-maps `=` to `<=`.
  - **Cleaner-statement candidates:** the four properties as one numbered set (`def:totality`/`def:uniformity`/`def:correctness`/`def:composability`) and the parameter-tuple table (`tab:parameters`, canonical order `(eta, eps, mu, delta)`). If sharper than the paper, note for the next cipher-maps revision.
- **ch5 (acceptance predicate + space duality), cleaner-statement / cross-cut candidates:** the acceptance partition `{A(y)}` (`def:acceptance`, `alpha(y)=|A(y)|/2^n`, `eps=sum alpha`) as the single device unifying hash-set / entropy-map / membership-index; the space-accuracy duality `-log2(eps)+H(Y)` as one abstract law (`prop:space-duality`, with derivation). **Cross-cut worth flagging to two papers:** the SPACE-optimal region allocation (`|A(y)| propto Pr[f(X)=y]`, Shannon) and the CONFIDENTIALITY-optimal allocation (concentrated / Huffman, minimizing the multi-instance coincidence-oracle sum, spine sec 4A) are DIFFERENT choices of the same knob, a tension to state once in cipher-maps and the Entropy Ratio paper. Forward to `part:confidentiality`.
- **Enrichment pattern (per 2026-06-18 density calibration: figures + worked examples):** ch3 = protocol figure (`fig:two-machines`) + transformations table (`tab:transformations`) + worked example (`ex:watchlist-numbers`); ch4 = two worked examples (`ex:delta-watchlist`, `ex:composition`) + two tables (`tab:compounding`, `tab:parameters`) + theorem/proof; ch5 = acceptance-partition figure (`fig:acceptance`) + proposition/derivation + two worked examples (`ex:acceptance-watchlist`, `ex:space-watchlist`). Density ~4-5pp/chapter (dense prose; rich elements present; all numbers Python-verified).
- Landmines held: `delta` image-relative (0 ambient leak); composition `<=`; `K propto D` not `1/D`; `eta` = Bernoulli FNR -> appendix; no em-dash / banned phrase.

### Part III: Algebra and Types (ch6 DRAFTED 2026-06-18; ch7-8 pending)
- **Harvest is back-port + one cross-cut** (`algebraic-cipher-types` + `foundations/trapdoor-boolean-algebra.md` consolidated; extraction N/A).
- **ch6 (Boolean algebra over trapdoor values), DRAFTED:**
  - The bit-image construction `F(A) = OR of element hashes` (`def:bit-image`), the operations table (`tab:boolean-ops`), a worked bit-level example (`ex:boolean-watchlist`, sets `S` and `V` over `n=8`).
  - **LANDMINE handled (`thm:not-approximate`):** complement is approximate, `~F(A) subseteq F(A^c)`, BETTER for SMALL `|A|` (the corrected direction; the blog erratum claimed the reverse), full pigeonhole proof. Verified: 0 "better for large set", 1 "better...small".
  - The equality channel (`rem:equality-channel`): the `K=1` deterministic baseline leaks value-equality; `K>1` (`def:uniformity`) breaks the bit algebra. The folded kernel of the retired boolean-algebra paper.
  - **Cross-cut candidate:** the Boolean asymmetry (AND/OR exact, NOT approximate, error `~ |A|/2^n`) as a constraint the whole book inherits; candidate to promote into spine §3.4 as the reference treatment.
- ch7 (algebraic cipher types: product passes, sum-type impossibility) and ch8 (orbit closure, `|X|`-denominator landmine) pending.

### Part IV: Confidentiality
_(to fill; this is where BP-1 gets forced)_

### Part V: Constructions
_(to fill)_

### Part VI: Frontiers
_(to fill; EC-2 lives here)_
