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
| EC-2 | A frontiers / research-agenda paper | Part VI | SoK-adjacent / research agenda | **ch14 DRAFTED**: `sec:next-program` (`tab:directions` ranked directions + the zero-per-query USP) and `sec:field-arrives` (2024 landscape) are the lift-ready spine. Lift with a contributions framing + the survey's citation batch. Seeded by `.papermill/prior-art/2026-06-09-ecosystem-survey.md`. |

## Back-port findings (monograph-driven)

| ID | Finding | Surfaced | Target | Cross-ref | Status |
|---|---|---|---|---|---|
| BP-1 | Image-relative delta (`delta = TV(Q, U_im)`, `H* = log2\|im(enc)\|`) must replace the ambient-`B^n` definition still in the spine Property 2 headline (line ~95) and cipher-maps. | round-2 Entropy Ratio review; **forced in Ch 4.2** (`def:uniformity` defines delta for the whole book). | spine Property 2 headline edit; cipher-maps Property 2 | `cross-paper-consistency.md` C-11 | **DONE 2026-06-18**: book Ch 4.2 + spine Property 2 + cipher-maps def (image-relative) |
| BP-2 | The four "cannots" (decode / distinguish real-filler / determine domain / tell correct-from-noise) should have one canonical statement the papers cite back to; today it is scattered across cipher-maps sec 1 and the spine. | Part I design (Ch 1.2, Ch 2). | spine (promote a canonical list); cipher-maps + papers cite it | (new) | open, drafting Ch 1-2 produced the canonical form |
| BP-3 | The "what trapdoor computing is not" comparison table (Ch 2.5) is the canonical positioning; consider promoting it into the spine as a shared figure the papers reuse. | Part I design (Ch 2). | spine (shared figure) | (new) | open, produced by drafting Ch 2 |
| BP-4 | Composition is `eta_total <= 1 - prod(1-eta_i)` (**inequality**: a stage error can be masked downstream), not `=`. | cipher-maps R3 review (equality/inequality flag); **landed in Ch 4.4** (`thm:composition`, full proof). The spine's FORMAL Property 4 (line ~125) is already `<=`; its headline (line ~122) and a cipher-maps draft write `=`. | spine Property 4 headline; cipher-maps headline wherever `=` | `cross-paper-consistency.md` C-12 | **DONE 2026-06-18**: book Ch 4.4; spine `=`->`<=` (C-12); cipher-maps Thm 7.1 already `<=` |
| BP-5 | Spine §4A.1 entropy-ratio normalizer is `n` (ambient); should be `H* = log2\|im(enc)\|` (image-relative), matching the Entropy Ratio paper and book Ch 4 / Ch 9. Same family as BP-1/C-11. | Part IV Ch 9 drafting (`def:entropy-ratio`, `prop:fannes`). | spine §4A.1 (lines ~600/603: `/n` -> `/H*`) | `cross-paper-consistency.md` C-11 family | **DONE 2026-06-18**: spine §4A.1 normalizer `n`->`H*` (lines ~600/603) + book Ch 9 |
| BP-6 | Spine §4A.2 (line ~626) attributes the joint-recovery LOWER bound to "Le Cam's two-point method"; it is **Assouad's lemma** (`2^{m/2}` packing). The spine's own §4A.3 hazard table names Thm 5.2 (Assouad-consistent), so line 626 self-contradicts. | Part IV Ch 10 drafting (`rem:assouad-not-lecam`). | spine §4A.2 line ~626 (Le Cam -> Assouad) | `book/CLAUDE.md` landmine 4 | **DONE 2026-06-18**: spine §4A.2 line ~626 + §4A.3 reframed (Le Cam marginal / Assouad compositional); C-4 superseded; book Ch 10 |

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

### Part III: Algebra and Types (DRAFTED 2026-06-18; ch6-8; PART III COMPLETE)
- **Harvest is back-port + one cross-cut** (`algebraic-cipher-types` + `foundations/trapdoor-boolean-algebra.md` consolidated; extraction N/A).
- **ch6 (Boolean algebra over trapdoor values), DRAFTED:**
  - The bit-image construction `F(A) = OR of element hashes` (`def:bit-image`), the operations table (`tab:boolean-ops`), a worked bit-level example (`ex:boolean-watchlist`, sets `S` and `V` over `n=8`).
  - **LANDMINE handled (`thm:not-approximate`):** complement is approximate, `~F(A) subseteq F(A^c)`, BETTER for SMALL `|A|` (the corrected direction; the blog erratum claimed the reverse), full pigeonhole proof. Verified: 0 "better for large set", 1 "better...small".
  - The equality channel (`rem:equality-channel`): the `K=1` deterministic baseline leaks value-equality; `K>1` (`def:uniformity`) breaks the bit algebra. The folded kernel of the retired boolean-algebra paper.
  - **Cross-cut candidate:** the Boolean asymmetry (AND/OR exact, NOT approximate, error `~ |A|/2^n`) as a constraint the whole book inherits; candidate to promote into spine §3.4 as the reference treatment.
- **ch7 (algebraic cipher types), DRAFTED:** the type-constructor algebra (`tab:constructors`); product types pass (`prop:product-tradeoff`: joint hides correlations / projections cost a cipher map, vs component-wise / joint leaks at `N=O(|A||B|/xi^2)`), worked `ex:product-pair`; the **sum-type impossibility** (`thm:sum-impossibility`: tag-hiding XOR untrusted-dispatch, the selector-IS-a-distinguisher obstruction; sketch+pointer); encoding granularity / entanglement `p` (`rem:granularity`) PAYS OFF ch4.2's marginal-only note. Cross-cut: `tab:constructors` candidate for the spine.
- **ch8 (orbit closure), DRAFTED:** the active adversary (operates, not just observes); `def:orbit` + `thm:monotonicity` (sketch); the residual-entropy bound `thm:orbit-bound` `H(X|view) >= H(X) - log2|orbit|` (full one-line proof) + the SET FORM `conf >= 1 - |orbit|/|X|`. **LANDMINE handled:** denominator `|X|` (latent space), NOT `2^n`; worked `ex:orbit-names` (orbit 2 -> conf 0.5; orbit 4=|X| -> vacuous). The active-vs-marginal two-scale separation (`rem:active-vs-marginal`: no delta bounds the orbit) + typed-chain preview forwarding the compositional rate `Theta(|Y1||Y2|/xi^2)` to `part:confidentiality`.
- **Part III complete: p27-37 (~11pp), 3 tables, 3 worked examples, 4 theorems + 1 proposition. Both landmines locked (NOT direction ch6, orbit denominator |X| ch8). Next: Part IV (Confidentiality), pays off ch7.4 + ch8's compositional preview.**

### Part IV: Confidentiality (DRAFTED 2026-06-18; ch9-10; PART IV COMPLETE)
- **Posture: SUMMARIZE the Entropy Ratio paper (CSF submission), state+intuition+pointer, no re-proofs.** Extraction N/A; harvest is back-port (spine §4A residuals BP-5, BP-6).
- **ch9 (the marginal scale), DRAFTED:** `def:entropy-ratio` (`e = H(Q)/H*`, `H* = log2|im(enc)|` IMAGE-RELATIVE); `prop:fannes` (`e >= 1 - delta - h2(delta)/H*`, LINEAR, Fannes-Audenaert not Pinsker, with why); `rem:le-cam-marginal` (single-guess upper `1/2+delta/2`, the MARGINAL Le Cam role); three delta levers (`tab:levers`) with costs -- noise injection [mixture entropy `H(rho*D+(1-rho)*U_im)`, NOT `H(C,B)`], multiplicity `K propto D` [not `1/D`], granularity; worked `ex:entropy-ratio` (Python-verified `e=0.87`, `delta=0.25`, Fannes floor `0.34`) + the `0.72->0.94` case study (cited).
- **ch10 (the compositional scale), DRAFTED:** the three compositional measures (`tab:measures`: orbit / coincidence-oracle / joint-recovery, none governed by delta); `thm:joint-recovery` (MI preserved exactly; rate `Theta(|Y1||Y2|/xi^2)`, upper plug-in, **LOWER ASSOUAD**); `rem:assouad-not-lecam` (the `2^{m/2}` packing; the two Le Cam/Assouad roles kept apart -- LANDMINE); `rem:irreducibility` (no parameter moves the rate; the two scales don't reduce; totality+composability CREATE the channel); system-level defenses.
- **All SIX landmines handled** (Fannes-not-Pinsker, `K propto D`, image-relative `H*`, mixture `H(C)`, Assouad-not-Le-Cam, orbit `|X|` callback). All numbers Python-verified.
- **Back-ports surfaced: BP-5 (spine §4A.1 normalizer `n -> H*`), BP-6 (spine §4A.2 line 626 Le Cam -> Assouad).** Logged in the table above; spine edits pending.
- Part IV complete: p39-45 (~7pp, summary part). Next: Part V (Constructions).

### Part V: Constructions (DRAFTED 2026-06-18; ch11-13; PART V COMPLETE)
- **Three construction families realizing the abstract framework.** Mixed posture: ch11 consolidates cipher-maps §6 (realizes Ch 5), ch12 SUMMARIZES the codec paper (live TOPS submission), ch13 folds three drafts via the cipher closure.
- **ch11 (hash-based), DRAFTED:** the PHF batch backend realizing `f-hat` (`sec:phf-backend`); HashSet (`eta=0`, FPR `eps`) + entropy map (`eta` tunable, `mu=H(Y)`) (`tab:instantiations`); the watchlist as a HashSet (`ex:watchlist-hashset`, closes the toy from abstraction to running code); `eta` = Bernoulli FNR, space hits `prop:space-duality` `-log2(eps)+H(Y)`. The `trapdoor_maps` library as the implementation of record.
- **ch12 (GF(2)-linear codec), DRAFTED (SUMMARIZE):** retrieval without a membership gate (totality, linear); `thm:span-output` (junk is designable -- non-member output uniform on the GF(2) span `W`, fixed by a public codec, frequency-independent); `rem:rank-threshold` (`rank(proj|_W)=log2 K`, a step, no graded middle; cogirth robustness); `rem:freq-hiding` + `tab:hiding` (STRUCTURAL frequency-hiding at ZERO per-query cost vs Ch 9's homophonic per-query lever; the coincidence-oracle opposite-pull, Ch 10 C2, a tunable frontier).
- **ch13 (rekeying/closures/programs), DRAFTED:** `def:cipher-closure` (the unifying abstraction -- values/maps/data-structures/secret all cipher closures); code-data duality (dispatch pattern = data-is-code; cipher exponential = code-is-data); `rem:designed-orbit` (data structures leak LENGTH via the orbit, callback `thm:orbit-bound`); `rem:rekeying-functor` (rekeying = a cipher map, a natural transformation); `rem:control-flow` (control flow IS untrusted dispatch on a sum -- callback `thm:sum-impossibility`: a conditional leaks the test or evaluates both branches). The two hard program costs are consequences of earlier-proved properties.
- **Cross-cut / back-port candidates:** the two-ways-to-hide-frequency contrast (ch12 `tab:hiding`: structural codec vs homophonic) across codec + Entropy Ratio; the cipher closure (ch13.1) as a unifying abstraction for the spine; control-flow-is-sum-dispatch ties `cipher-program-construction` to `thm:sum-impossibility` (cross-paper link).
- **New bibkeys added:** `towell2026codec`, `towell2026rekeying` (DOI), `towell2026closures`, `towell2026cipherprog`. `notation.sty` gained `\rank`, `\proj` (codec construction).
- Part V complete: p48-55 (~8pp). Build clean (62pp). Next: Part VI (Frontiers), the last part.

### Part VI: Frontiers (DRAFTED 2026-06-18; ch14; PART VI COMPLETE -- BOOK BODY COMPLETE)
- **Roadmap, not new results** (per master spec). Synthesized from the 2026-06-09 ecosystem survey.
- **ch14 (Open Problems and the Next Program), DRAFTED:**
  - `sec:internal-frontiers`: the open problems the framework raises (orbit-bound tightening for specific operation sets; noise-to-signal through shared-structure chains; intersection-FPR and NOT-error closed forms; the oblivious control-flow decision space). Each was flagged in place in earlier chapters.
  - `sec:field-arrives`: the 2024 field pivot (quantify-then-mitigate SSE; the tunable-measurable-leakage middle ground; adversarial PDS / Filic; approximate-inference-as-privacy). The program's bet validated; the honest claim-scoping note from the survey's taste assessment.
  - `sec:next-program`: the USP (structural frequency-hiding at ZERO per-query cost, ch12) + `tab:directions` (ranked salient directions: Filic FP-law axiom, the zero-per-query frontier point, PML re-expression, adaptive-trapdoor under drift, codec membership for private RAG / vector search).
  - `sec:closing`: the book's argument in six movements; the narrower-but-honest promise; the foundation for the next program.
- **EC-2 produced:** `sec:next-program` + `sec:field-arrives` ARE the lift-ready spine of the frontiers/research-agenda paper. See the extraction table.
- External landscape work pointed to by name+venue (prose), not `\cite` -- a citation pass folds them in later (consistent with the SUMMARIZE/roadmap posture).
- Part VI complete: p57-60 (~4pp). **BOOK BODY COMPLETE: 14 chapters, 6 parts, ~58pp body, 65pp total, builds clean.**
