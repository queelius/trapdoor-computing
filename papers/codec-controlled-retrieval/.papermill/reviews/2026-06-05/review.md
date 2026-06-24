# Multi-Agent Editorial Review Report

**Date**: 2026-06-05
**Paper**: Codec-Controlled Retrieval: Structural Frequency-Hiding from the Non-Member Channel of XOR Retrieval
**Author**: Alexander Towell
**Target venue**: PoPETs 2027 (companion to cipher-maps)
**Manuscript**: `paper/codec_retrieval.tex` (22 pp, builds clean via `cd paper && make`)
**Recommendation**: **minor revision**

> Process note: the orchestration harness could not spawn sub-agent specialists (the
> Task tool is unavailable inside this run). The area chair therefore executed every
> specialist lens directly: literature scouting, logic/proof checking, novelty,
> methodology/evaluation, prose, citation verification, and format validation. Every
> Critical and Major finding below was verified by the reviewer against the manuscript
> source and, where relevant, against `source/construction-note.md` and the
> `source/results/*` CSVs. Findings are attributed to the lens that produced them.

---

## Summary

**Overall Assessment.** This is a strong, unusually honest paper with a genuinely
novel headline (the sharp GF(2)-rank codec-control threshold) and a clean security
payoff (structural, zero-per-query frequency-hiding). The technical substance was
pre-proven and computationally verified, and that shows: I found no incorrect theorem,
no number that disagrees with the committed result CSVs, and no undefined reference or
build error. The novelty positioning is careful and the three-tier ledger defuses the
main self-collision risk well. The paper is close to submittable. The issues that
remain are about **claim precision** (one security bound is stated more broadly than its
proof supports), **a few defensible-but-overconfident novelty assertions**, and
**venue/formatting polish** (PoPETs class, abstract notation, related-work depth). None
is a correctness defect in the core results; the recommendation is minor revision, with
one Major item (M1) that should be fixed before submission because a PoPETs reviewer
will catch it.

**Strengths** (see "What is strong" for the full list):
1. The headline threshold (Thm 4.5) is a clean, correct, and as far as I can determine
   genuinely new result, with an exact worked example and a matching empirical cliff.
   *(logic, novelty)*
2. Exemplary intellectual honesty: explicit M1 idealization vs real-construction split,
   a tier-A/B/C novelty ledger that cites the author's own prior work as baseline, an
   "independence not comparative" framing, and a self-corrected sign error. *(novelty, prose)*
3. Every number in the paper is faithfully transcribed from the committed experiment
   CSVs; I verified all four tables cell-by-cell. *(methodology)*
4. The build is clean: 22 pp, zero undefined refs/cites, all 15 bib entries resolve.
   *(format)*

**Weaknesses**:
1. The real-construction FreqDist bound `Adv <= 2(delta0+delta1)` (Thm 7.5 / abstract)
   is proven only for a *single* observation, but the threat model grants the adversary
   unboundedly many adaptive queries. As stated it does not cap the multi-query
   advantage. *(logic)* is **Major (M1)**.
2. Two novelty claims ("appears nowhere... internal or external"; "as of 2025
   uncharacterized") are stated with more certainty than a literature search can
   underwrite, and the related-work section omits the coding-theory lineage (coset
   weight distributions / MacWilliams) that is the nearest external analogue of the
   threshold. *(novelty, citations)* is **Major (M2)**.
3. Related work is thin on the encrypted-search/structured-encryption leakage lineage
   that a PoPETs audience expects (only NKW/PANCAKE/FSE/volume-hiding/Filic-Paterson).
   *(citations)* is **Major (M3)**.
4. The manuscript uses the `article` class, not the PoPETs/PETS template; abstract
   notation (`delta_0`) diverges from body notation (`delta(p_0)`); minor prose and
   bib-hygiene nits. *(format, prose, citations)* are **Minor**.

**Finding Counts**: Critical: 0 | Major: 3 | Minor: 7 | Suggestions: 6

---

## Critical Issues

**None.** No theorem is wrong, no headline claim is unsupported by the evidence on
record, the coincidence-oracle direction is stated correctly (concentration defeats the
oracle), the security framing is an independence/indistinguishability claim (not a
comparative leakage claim), and every table matches its CSV. The paper has no blocker
that would force rejection.

---

## Major Issues

### M1. The real FreqDist bound is a single-query bound, but the threat model grants many queries (source: logic-checker)

- **Location**: Theorem 7.5 (`thm:freqdist-real`, ll. 843-862); abstract (l. 82-85);
  Def 7.3 (`def:freqdist`, ll. 791-809); restated in scope (l. 897) and conclusion
  (l. 1254).
- **Quoted text** (proof, l. 849-850): "The standard fact that distinguishing advantage
  is bounded by total variation gives, for any adversary observing samples from one of
  the two laws, $\Adv(\mathcal{A}) \le 2\,\TV(\lawreal(p_0), \lawreal(p_1))$." And the
  parenthetical (l. 854): "the optimal single-sample distinguisher achieves exactly the
  TV." Meanwhile Def 7.3 (l. 802-804): "$\mathcal{A}$ issues non-member queries,
  observes the decoded outputs, and outputs a guess," with the idealized theorem
  (l. 816-817) granting "computationally unbounded and adaptive" adversaries
  "regardless of the number ... of queries."
- **Problem**: For two *fixed, distinct* distributions at TV distance `d > 0`, an
  adversary that draws `n` i.i.d. samples does **not** have advantage bounded by `2d`;
  the n-sample total-variation distance grows with `n` and the advantage tends to 1
  (this is exactly how distribution-distinguishing/identity-testing works). The
  parenthetical "single-sample distinguisher" is the tell: the inequality
  `Adv <= 2 TV(law(p0), law(p1))` bounds the advantage of an adversary that sees **one**
  output, not the advantage of the Def-7.3 adversary that adaptively issues many
  non-member queries. The idealized `Adv = 0` (Thm 7.4) is genuinely immune because the
  two laws are *identical* (n-sample TV stays 0 for all n), so M1's robustness is real.
  But the **real** bound as written, and as headlined in the abstract ("at most
  $2(\delta_0+\delta_1)$"), overclaims: with `delta ~ 0.003` to `0.017` per query and
  unbounded queries, a determined adversary's advantage is not capped at `0.012` to `0.04`.
  This is the single most important precision issue in the paper and a PoPETs reviewer
  will flag it.
- **Why it is fixable (not fatal)**: The *qualitative* security story survives intact.
  The substantive content is (i) the idealized channel is perfectly frequency-independent
  (Adv = 0 for any number of queries), and (ii) the real channel deviates from that ideal
  by a small, frequency-*independent*, redundancy-governed `delta` whose **shape** E2
  confirms does not grow with the frequency gap. What an unbounded-query adversary can
  eventually learn is the *real per-build law on W* to arbitrary precision, but that law
  is itself frequency-independent up to `delta`, and crucially the part that *would* let
  the adversary win (a frequency-gap-dependent difference between the `p0`-law and the
  `p1`-law) is bounded by `delta(p0)+delta(p1)` and is what E2 shows stays at the noise
  floor. So the honest claim is about the **gap between the two real laws**, not a
  per-query advantage cap.
- **Suggested fix** (pick one, in order of rigor):
  1. **Reframe as a distribution-distance claim, not an advantage cap.** State Thm 7.5 as
     "the real `p0`-law and `p1`-law are within total variation `delta(p0)+delta(p1)` of
     each other (frequency-independently)," and note that consequently the *single-query*
     distinguishing advantage is `<= 2(delta0+delta1)` while a multi-query adversary can
     drive the advantage up only to the extent these two *fixed* laws differ, i.e. it
     can learn each real per-build law but not separate them beyond their `delta`-bounded
     difference. This is the correct and still-strong statement.
  2. **Restrict the game to a budget.** If a per-query-cap headline is wanted, define
     FreqDist with a query budget `q` and state `Adv <= 2 q (delta0+delta1)` (or the
     tighter `1 - exp(-O(q d^2))`-style bound from the standard sample-complexity of
     distinguishing), and update the abstract accordingly. The plugged-in `0.012`/`0.04`
     numbers should then be labeled "per query."
  3. At minimum, **move the "single-sample" qualifier from a parenthetical into the
     theorem statement and the abstract**, and add one sentence explaining why the
     idealized `Adv = 0` (identical laws) is not subject to multi-query amplification while
     the real bound is per-observation. This is the smallest honest patch.
- **Cross-verified** (methodology-auditor lens): E2's design actually supports fix (1)
  directly. The experiment measures `TV(dist(p0 build), dist(p1 build))` (the cross-profile
  *distribution distance*), not a multi-query attacker's realized success rate, and shows it
  tracks the noisier build's per-build `delta` rather than the frequency gap. So the data is
  already a measurement of "how far apart the two real laws are," which is exactly the
  quantity fix (1) elevates to the headline. The empirical claim is sound; only the
  game-theoretic *wording* of the cap needs correcting. Agreement between lenses: the result
  is correct; the bound is mislabeled as a per-adversary advantage rather than a per-sample
  / distribution-distance quantity.

### M2. Two "nobody, anywhere" novelty claims are stronger than a search can support, and the nearest external analogue (coset weight distributions) is uncited (source: novelty-assessor + citation-verifier)

- **Location**: l. 161 ("This threshold appears nowhere we are aware of, internal or
  external."); l. 1201-1203 ("This appears nowhere we are aware of, internal or external:
  absent from the random-oracle treatments ... and absent from the retrieval literature");
  ll. 124-126 and 1192-1193 ("As of 2025, the state of the art in static
  retrieval~\cite{hu2025retrieval} leaves the off-set output distribution
  uncharacterized").
- **Problem**: Two distinct sub-issues.
  - **(a) The "uncharacterized off-set distribution" claim is defensible but rests on a
    single citation.** The retrieval/static-function literature (Bloomier, ribbon/BuRR,
    XOR, binary-fuse) does treat the non-member return as a don't-care and, to the best of
    my knowledge, does not characterize its *value distribution*; this novelty claim is
    very likely correct. But leaning the entire "silence persists to 2025" assertion on
    `hu2025retrieval` alone is fragile. The claim would be much more robust if it (i)
    acknowledged that XOR/fuse filters *do* specify the unused-slot fill (uniform-random or
    zero) as an engineering choice, which is adjacent to characterizing the off-set output,
    and explicitly distinguished "specifying the fill of unused *slots*" from
    "characterizing the decoded *value* distribution on non-member *keys*," and (ii) cited
    one or two more recent static-function works so the "as of 2025" is not a single-point
    claim. graf2020xor/graf2022binaryfuse are already in the bib and are the right place to
    plant the "fill is specified but the induced value law is not studied" boundary.
  - **(b) The threshold's nearest *external* analogue, coset weight enumeration in coding
    theory, is neither cited nor distinguished.** Thm 4.5 is, structurally, a statement
    about how a stored subspace `W` intersects the cosets of the homophone subspace `C`
    (`Lemma 4.3`, subspace-meets-coset). The behavior "a subspace meets each coset it
    touches in a constant number of points" is a standard fact in coding theory (it is the
    content behind coset weight distributions, syndrome/coset decoding, and the MacWilliams
    machinery), and a coding-theory-literate PoPETs reviewer will recognize the lemma as
    folklore linear algebra. The *novel* combination here is (i) interpreting the constant
    coset-hit count as a non-member *value* law and (ii) the all-or-nothing
    `rank pi|_W = log2 K` control threshold with the gf2_rank engineering bridge; that
    framing does appear new. But claiming the threshold "appears nowhere ... external" while
    not citing or distinguishing the coset-weight lineage reads as a gap in scholarship
    rather than a strength.
- **Suggested fix**:
  1. Soften the two absolute claims from "appears nowhere we are aware of" to "we are not
     aware of a prior treatment that characterizes the non-member *value* distribution of a
     linear retrieval structure or states this transversality threshold; the closest
     *technique*, coset weight enumeration in coding theory, gives the constant-coset-hit
     count (Lemma 4.3) as folklore, but has not, to our knowledge, been used to characterize
     a retrieval structure's off-set output or to derive a codec-control threshold." Add a
     one-line citation to a standard coding-theory reference for coset weight distributions
     (e.g. MacWilliams-Sloane, *The Theory of Error-Correcting Codes*) at Lemma 4.3.
  2. In Tier B (l. 1188-1194), add the explicit "unused-slot fill is specified, value law is
     not" distinction so the "uncharacterized" claim is robust to the obvious reviewer
     objection that XOR/fuse filters already say what fills empty slots.
- **Cross-verified** (logic-checker lens): Lemma 4.3 (`lem:subspace-coset`) is proven
  correctly and is indeed elementary; reading it as a coset-weight fact is accurate, which is
  precisely why the external-analogue acknowledgement is needed. The *headline* (the control
  threshold as a security-relevant codec design rule) remains novel after this acknowledgement,
  it weakens the rhetoric, not the contribution.

### M3. Related work under-covers the encrypted-search / structured-encryption leakage lineage a PoPETs audience expects (source: citation-verifier + literature scouting)

- **Location**: Section 9 (`sec:related`, ll. 1158-1239); intro motivation (ll. 103-126).
- **Problem**: The security framing positions the paper squarely in the
  encrypted-database leakage-suppression conversation (NKW inference, PANCAKE, FSE,
  volume-hiding, Filic-Paterson). That core is correct and the must-differentiate
  set is handled well. But for a PoPETs venue the related-work coverage of *leakage in
  searchable/structured encryption* is thin: there is no acknowledgement of (i) the
  leakage-abuse attack line beyond NKW (e.g. the count/access-pattern attacks of Cash et
  al. CCS'15 "Leakage-Abuse Attacks Against Searchable Encryption," and Islam-Kuzu-Kantarcioglu
  NDSS'12), which is the canonical "leakage is exploitable" backdrop; (ii) the
  leakage-suppression / structured-encryption framework (Kamara-Moataz-Ohrimenko
  "Structured Encryption and Leakage Suppression," CRYPTO'18) that volume-hiding lives
  inside; or (iii) frequency-hiding ORAM / oblivious data structures as the heavyweight
  alternative the paper's "zero per-query cost" pitch is implicitly contrasting against.
  A reviewer will not require all of these, but the current three-paragraph related-work
  will read as under-situated for the claimed security contribution.
- **Suggested fix**: Add a short paragraph (4-6 citations) situating the work in
  searchable/structured-encryption leakage: cite at least one leakage-abuse attack
  (Cash et al. CCS'15 and/or Islam et al. NDSS'12) as the "why leakage matters" anchor
  alongside NKW, and the Kamara-Moataz-Ohrimenko leakage-suppression framing as the home
  for the volume-hiding cousin. Optionally one sentence distinguishing from frequency-hiding
  ORAM (much heavier, dynamic) to sharpen the "static, zero per-query" pitch. This also
  strengthens M2(a) by giving the "online defenses pay per query" claim concrete referents.
- **Cross-verified** (prose-auditor lens): this is a coverage gap, not a framing error;
  the existing positioning is honest and well-written, so the fix is additive and low-risk.

---

## Minor Issues

### m1. Abstract notation diverges from body notation (source: prose-auditor)
- **Location**: abstract l. 82 (`$2(\delta_0+\delta_1)$`) vs body ll. 165, 845, 861, 1081
  (`$2(\delta(p_0)+\delta(p_1))$`).
- **Problem**: The abstract writes the deviation as `delta_0, delta_1` (subscripted) while
  the entire body writes `delta(p_0), delta(p_1)` (function-of-profile). Minor but a careful
  reader notices the inconsistency on page 1.
- **Fix**: Use `delta(p_0)+delta(p_1)` in the abstract too (or define the shorthand
  `delta_b := delta(p_b)` once). Trivial.

### m2. Abstract coincidence-oracle clause risks the very inversion the paper corrects (source: prose-auditor)
- **Location**: abstract ll. 86-88: "a coincidence oracle with accuracy
  $1-\tfrac12\sum_v \al(v)^t$ ... pulls the codec the opposite way."
- **Problem**: The abstract gives the accuracy formula but not the *direction* (that
  concentration, not uniformity, defeats it). Given that the body devotes Remark 8.1 to
  correcting exactly the "uniform defends best" sign error, an abstract that states the
  formula without the direction invites a skimming reader to re-derive the wrong direction.
- **Fix**: Append a half-clause: "...pulls the codec the opposite way (it is defeated by
  *concentrated*, not flat, codespace shares)..." Five words, removes the foot-gun.

### m3. Production note leaked into the printed bibliography (source: citation-verifier)
- **Location**: refs.bib l. 109, rendered .bbl l. 98-99: the cipher-maps entry's note reads
  "In revision, PoPETs 2027. Cites towell2026codec."
- **Problem**: "Cites towell2026codec" is an internal production note that has leaked into
  the printed bibliography (it will appear verbatim in the references). It is also slightly
  awkward that the companion "cites" this paper by a bibkey that is this paper's own key.
- **Fix**: Strip the "Cites towell2026codec." sentence from the printed `note`; keep such
  cross-reference bookkeeping in the papermill state, not the .bib `note` field. Same for
  the bernoulli_maps note ("Contains the abstract codec-output formula."), fine as a private
  annotation, but consider whether it should print.

### m4. Two unpublished self-citations have empty year (source: citation-verifier / format-validator)
- **Location**: bibtex log: "Warning--empty year in towell2026ciphermaps" and "...in
  towell_bernoulli_maps"; .bbl renders them as "Towell(a)" / "Towell(b)" with no year.
- **Problem**: The keys imply a 2026 year but the entries carry no `year` field, so natbib
  emits `(a)/(b)` disambiguators and no date. For a submission, dated entries read better and
  avoid the bare `(a)`.
- **Fix**: Add `year = {2026}` (and a `note`/`howpublished` if you want "manuscript" /
  "in revision") to both `@unpublished` entries. Also "empty booktitle in dillinger2021ribbon"
  (it is an arXiv preprint), give it `howpublished = {arXiv:2103.02515}` or a `booktitle`/
  `journal` so it does not render as a bare year.

### m5. E1 table caption / prose lean on data not shown in the table (source: methodology-auditor)
- **Location**: Table 1 (`tab:e1`, ll. 1005-1022) shows only the two flanking ranks for the
  two balanced configs; the surrounding prose (ll. 1028-1033) cites the full sub-threshold
  ladder ("0.875, 0.750, 0.500 at ranks 0, 1, 2") and the skewed config's "0.251 at rank 1"
  / "0.00238 at rank 2," none of which are in the table.
- **Problem**: All these numbers are correct (verified against `codec_span/results.csv`), but
  a reader cannot see the cliff *as a ladder* from the table, only two points per config. The
  determinism-below-threshold story (the headline of E1) is told in prose but not visualized.
- **Fix**: Either expand Table 1 to show every rank (0..log2 K) for at least balanced_M8_K8 so
  the step is visible, or add a small inline plot of TV-vs-rank. This materially strengthens the
  "cliff not ramp" claim for the price of a few table rows. (Data is all present in the CSV.)

### m6. "junk is a designable object" repetition / register (source: prose-auditor)
- **Location**: abstract l. 70 ("We show that junk is a designable object."); echoed in intro
  (l. 128) and conclusion (l. 1244).
- **Problem**: It is a good hook, but it appears three-plus times (abstract, intro, conclusion).
  PoPETs prose can carry one memorable framing; three repetitions of the same "silence/junk/
  designable" motif starts to feel like a refrain rather than an argument.
- **Fix**: Keep it once (the abstract), and let the intro/conclusion restate the *result*
  rather than the *slogan*. Purely stylistic.

### m7. Uncited-but-present bib entries (source: citation-verifier)
- **Location**: `dietzfelbinger2008succinct` and `dietzfelbinger2019gauss` are in refs.bib
  but cited nowhere (confirmed: 0 `\cite` occurrences).
- **Problem**: Not an error (they simply will not print, since bibtex only emits cited keys),
  but the GF(2)-Gaussian-elimination foundation (`dietzfelbinger2019gauss`) is *exactly* the
  right citation for the "lookup is a GF(2)-linear form / banded system" machinery in Section 2,
  and the retrieval space lower bound (`dietzfelbinger2008succinct`) supports the "near-optimal
  space" claims. Leaving them uncited is a missed grounding.
- **Fix**: Cite `dietzfelbinger2019gauss` at the banded-system solve (Section 2.2, around
  eq. `eq:member`/l. 243-253) and `dietzfelbinger2008succinct` at the "near the
  information-theoretic minimum" claim (l. 251). They are already in the bib; this is free.

---

## Suggestions (optional improvements)

1. **PoPETs class switch (production, not a review blocker).** The manuscript uses
   `\documentclass[11pt]{article}` (l. 1). PoPETs/PETS requires the `popets`/`petsymposium`
   LaTeX template (specific title block, author/affiliation macros, anonymization for
   submission, and a structured abstract in some cycles). Plan a camera-ready pass onto the
   official class; expect the 22 article-pages to recompose, and check that the proofs still
   fit the PoPETs page budget (the appendix-vs-body split flagged in the state file is the lever).
2. **Anonymization.** The paper names the author and self-cites bernoulli_maps/cipher-maps as
   "the author's own." For PoPETs double-blind submission these must be neutralized
   ("prior work [X]" rather than "the author's own [X]"), and the cipher-maps companion
   relationship stated without revealing identity. This interacts with the tier-A honesty
   framing: keep the *substance* of the differentiation, drop the first-person attribution.
3. **Give the "zero per-query cost" pitch a concrete contrast number.** The recurring claim
   that PANCAKE/FSE "pay bandwidth per query" while this is free would land harder with even a
   one-line quantitative contrast (e.g. PANCAKE's replication/fake-query overhead vs the static
   structure's nil query-time cost). This is the paper's strongest practical selling point and
   currently asserted rather than quantified.
4. **State the threat model's "single instance" assumption earlier and louder.** The FreqDist
   game assumes a single deployed instance; the coincidence oracle assumes `t` redeployments.
   The boundary between "one instance" (frequency game) and "many instances" (coincidence game)
   is the spine of the security story and the abstract gestures at it, but a reader benefits
   from seeing the single-vs-multi-instance axis named explicitly in the threat-model paragraph
   (l. 174-181) rather than discovered in Section 8.
5. **Consider folding Remark 3.1 ("Why we adopt M1 on the image, not the band support,"
   ll. 388-400) into an appendix.** It is excellent and correct, but it is a defensive
   technical aside that interrupts the main line at exactly the point the reader wants the
   frequency-independence payoff; PoPETs readers will tolerate it better as an appendix note.
6. **E4 prose could name the `t = 1` degeneracy.** At `t = 1` every codec gives acc = 0.5
   (visible in the CSV), i.e. the coincidence oracle is useless against a single instance,
   which is *why* attack 1 (frequency) is the relevant single-instance threat and attack 2 only
   bites under redeployment. Stating this ties the two-attacks synthesis together cleanly.

---

## Detailed Notes by Domain

### Logic and Proofs (logic-checker lens)
I spot-checked all five theorems, the lemma, the worked example, and the appendix induction
against `source/construction-note.md`. Findings:
- **Thm 3.1 (output support, R(z) = W)**: correct. Both inclusions are sound; the appendix
  induction on decreasing column index (ll. 1318-1336) is valid and the genericity caveat
  (Remark 3.2, free-slots-zero / no-salt) is the right hypothesis to flag.
- **Thm 3.4 (idealized law)** and **Thm 4.1 (frequency independence)**: correct, and the
  `span(multiset) = span(set)` argument (`g XOR g = 0`) is exactly right. The
  "idealized vs real" hedging after each (ll. 383-386, 443-448) is precise and welcome.
- **Lemma 4.3 (subspace meets coset)**: correct and elementary (this is the coset-weight fact;
  see M2). **Thm 4.5 (sharp threshold)**: correct; the `K' = |pi(W)| = 2^rank` counting via
  rank-nullity is clean, and the gf2_rank bridge (eq. `eq:bridge`, requiring left-alignment so
  `W cap C = {0}`) is valid. Example 4.7 (M=4, K=4) is arithmetically exact (I verified
  D = 0100 XOR 1000 = 1100 enters W at rank 2). The skewed-case open-problem deferral
  (Remark 4.8) is honest and correctly scoped.
- **Thm 7.4 (idealized Adv = 0)**: correct and robust to unbounded adaptive queries (identical
  laws). **Thm 7.5 (real bound)**: the TV-to-advantage step and triangle inequality are correct
  *as a single-observation statement*; the gap is that the bound is presented as a cap on the
  Def-7.3 (many-query) adversary. **This is M1, the one substantive precision issue.**
- **Coincidence oracle (eqs. `eq:acc`, ll. 936-953; Remark 8.1)**: direction is **correct**.
  `acc(t) = 1 - S(t)/2`, smaller `S(t)` gives higher accuracy gives worse defense, so uniform
  worst, concentrated best. The self-correction of the prior sign error is stated cleanly and
  matches E4. No issue.

### Novelty and Contribution (novelty-assessor lens)
The three-tier ledger is the right instrument and is executed well. Tier A (the abstract
codec-output law) is correctly *not* claimed and is credited to bernoulli_maps (random-oracle)
and Honey-Encryption DTE. The differentiation from the author's own work is defensible: the
delta from bernoulli_maps is real (random-oracle fresh-hash output has no stored span `W` and
hence no transversality threshold; the linear-structure constraint to `W` and the resulting
rank threshold are genuinely absent there), and the cipher-maps boundary (no linear backend;
query-marginal vs non-member-output concern) is clean. Tier C (the threshold) is the genuine
headline and I believe it is new *as a security-relevant codec-control result*, with the
caveats in M2 (the coset-weight technique is folklore; soften "nowhere external" and cite it).
Tier B (the law survives to the linear structure) is a fair, well-supported novel claim once the
"unused-slot fill is specified but value law is not" boundary (M2a) is added. Net: novelty is
**solid and honestly positioned**; the only fixes are rhetorical softening and two acknowledgements,
not a re-scoping.

### Methodology and Evaluation (methodology-auditor lens)
Reproducibility and data fidelity are a strength. I verified all four tables cell-by-cell
against the CSVs:
- **E1 (Table 1)**: balanced_M4_K4 rank-2 = 0.002773 -> paper 0.00277 ok; balanced_M8_K8 rank-3
  = 0.005054 -> 0.00505 ok; sub-threshold 0.5/0.5 ok; skewed rank-1 0.250952 -> 0.251 ok, rank-2
  0.002378 -> 0.00238 ok. Degenerate sub-threshold CIs (lo=hi=mean) confirmed in CSV.
- **E2 (Table 2)**: every baseline and cross value matches (uniform baseline 0.002919 -> 0.00292,
  skew_a 0.018966 -> 0.01897, uniform-vs-skew_a 0.013361 -> 0.01336, etc.) ok.
- **E3 (Table 3)**: 0.003522/0.003107/0.00352/0.00284333 -> 0.00352/0.00311/0.00352/0.00284 with
  matching CIs ok; reps 10/10/5/3 ok.
- **E4 (Table 4, t=4 slice)**: uniform 0.999023 -> 0.99902, intermediate_zipf 0.982396 -> 0.98240,
  huffman 0.966667 -> 0.96667, intermediate_padded 0.671950 -> 0.67195; MC matches ok.
- **Sampling-floor analysis (Sec 6, l. 681-712)**: the 0.00334 floor (de Moivre binomial MAD,
  K=8, p=1/8, n_q=1e5) and the sqrt(2/pi) normal cross-check are correctly reasoned, and the
  "straddles the floor" conclusion is honestly hedged (the quadrature decomposition is explicitly
  labeled heuristic). This is a model of careful empirical characterization. The one methodology
  presentation gap is m5 (E1 shows two points, prose cites the full ladder). Replication counts
  are modest at scale (R=3 at 1e7) but appropriately caveated and the claim (flat in N) is
  conservative. No methodological error found.

### Writing and Presentation (prose-auditor lens)
The prose is well above average for a draft: confident, precise, and structurally sound (the
narrative arc theory-to-threshold-to-security-to-evaluation-to-honesty lands). Notation is
consistent in the body (the one slip is m1, abstract `delta_0`). The honesty apparatus (M1 flags,
tier ledger, sign-error correction, scope boundary) is the paper's signature and reads as a
strength, not a hedge. Issues are stylistic: the "junk/silence/designable" motif is over-repeated
(m6), the abstract coincidence clause omits its direction (m2), and Remark 3.1 interrupts the
payoff (suggestion 5). No em-dashes (compliant with house style). Sentences occasionally run long
(the abstract is a single dense 250-word block; PoPETs tolerates it but consider one paragraph
break).

### Citations and References (citation-verifier lens)
- **Resolution**: all 15 cited keys are defined in refs.bib and all 15 resolve in the `.bbl`
  (I initially mis-grepped and thought several were missing; on direct inspection of
  `codec_retrieval.bbl` every entry is present and correctly formatted, withdrawn). Zero
  undefined citations. ok
- **bibtex warnings**: empty year on the two self-citations (m4), empty booktitle on
  dillinger2021ribbon (m4). Cosmetic but should be fixed for submission.
- **Printed-note leakage**: the cipher-maps `note` prints "Cites towell2026codec." (m3).
- **Accuracy of canonical entries** (verified against my knowledge): Naveed-Kamara-Wright CCS'15,
  PANCAKE USENIX Sec'20, Lacharite-Paterson FSE/ToSC'18, Juels-Ristenpart Honey Enc. EUROCRYPT'14,
  Chazelle et al. Bloomier SODA'04, Patel et al. volume-hiding CCS'19, Filic et al. adversarial-PDS
  CCS'22, all correct venue/year. Graf-Lemire XOR (JEA'20) and Binary Fuse (JEA'22) correct.
  Dillinger-Walzer ribbon (2021, arXiv then SEA/RecSplit line) and Dillinger et al. BuRR
  (SEA'22) correct. `hu2025retrieval` (Hu-Kuszmaul, "Static Retrieval Revisited," FOCS'25): I
  cannot independently confirm this specific FOCS'25 paper exists with that exact title/authors
  from my knowledge. **The citation-verifier flags it as plausible-but-unconfirmed; the author
  should double-check the exact title, authorship, and venue/year before submission**, since the
  novelty claim leans on it (see M2a). `cheng2019pmte` (PMTE, USENIX Sec'19) is correct.
- **Completeness**: see M3 (leakage-abuse / structured-encryption lineage missing) and m7
  (two foundational dietzfelbinger entries present but uncited).

### Formatting and Production (format-validator lens)
- **Build**: `cd paper && make` produces a 22-page PDF with zero undefined refs/cites, zero
  overfull/underfull boxes reported in the relevant log scan, and only cosmetic hyperref
  "Token not allowed in a PDF string" warnings (math in section/bookmark titles, harmless; can be
  silenced with `\texorpdfstring` if desired). cleveref/natbib/amsthm all load cleanly.
- **Label/ref integrity**: all 39 defined labels resolve; every `\cref`/`\Cref` target exists
  (verified by set comparison). No dangling references.
- **Venue class**: `article`, not PoPETs (suggestion 1), a camera-ready production task, correctly
  noted in the state file as a non-blocker for this review.
- **Makefile**: runs 4 pdflatex passes + bibtex; fine. The appendix uses a `verbatim` code block
  (ll. 1302-1310), acceptable, but on the PoPETs class confirm it does not overflow the column.

---

## Literature Context Summary

(Assembled by the reviewer in lieu of the unavailable literature-scout agents; flagged where a
live database search would be needed to upgrade confidence.)

- **Retrieval / static-function lineage** (Bloomier, ribbon/BuRR, XOR, binary-fuse, succinct
  retrieval, GF(2) Gaussian elimination): well represented in the bib. The "non-member output is
  arbitrary" framing is an accurate characterization of this literature's stance, and to my
  knowledge no work in it characterizes the non-member *value distribution*, so the Tier-B/C
  novelty is defensible. The nearest engineering-adjacent fact is that XOR/fuse filters *specify*
  the unused-slot fill (uniform-random or zero); the paper should distinguish this from
  characterizing the decoded value law (M2a).
- **External analogue of the threshold**: coding theory's coset weight distributions /
  syndrome decoding / MacWilliams identities are the closest external technique to Lemma 4.3
  and the transversality threshold. This is folklore linear algebra over GF(2); the novelty is in
  the *application* (non-member value law + codec-control threshold), not the lemma. Must be
  acknowledged (M2b).
- **Encrypted-DB leakage suppression**: NKW (the attack), PANCAKE/FSE (online frequency smoothing),
  volume-hiding STE (Patel et al.), and Filic-Paterson (adversarial PDS) are the right cousins and
  are differentiated correctly. Missing for venue-completeness: leakage-abuse attacks
  (Cash et al. CCS'15; Islam et al. NDSS'12) and the structured-encryption leakage-suppression
  framework (Kamara-Moataz-Ohrimenko CRYPTO'18); optionally frequency-hiding ORAM as the heavy
  alternative (M3).
- **DTE / Honey Encryption**: correctly credited as Tier-A baseline and correctly distinguished
  (DTE *assumes* a uniform seed from a cipher; this paper *derives* near-uniformity from the linear
  structure, gated by the threshold, and measures the gap). I found no reason to believe a
  DTE/Honey follow-up already derives seed-uniformity from a concrete retrieval data structure, so
  the distinction stands, but this is exactly the kind of claim a live literature search would
  firm up.
- **Net novelty verdict**: the headline (sharp GF(2)-span codec-control threshold as a
  security-relevant design rule) and the frequency-independence security reading are, to the best
  of the evidence on record and my knowledge, **new and defensible**. The required fixes (M2, M3)
  strengthen scholarship and rhetoric; they do not re-scope the contribution. The self-collision
  risk (the #1 editorial concern) is **handled well**: the abstract law is cited as baseline, and
  the bernoulli_maps / cipher-maps boundaries are clean.

---

## What is strong

1. **A genuinely novel, correct headline.** The sharp GF(2)-rank codec-control threshold
   (Thm 4.5: full control iff `rank pi|_W = log2 K`, a step function with no graded regime) is the
   kind of clean, surprising, checkable result that makes a paper. It is proven, illustrated with an
   exact worked example (Example 4.7), bridged to an engineering rule (gf2_rank of stored patterns),
   and confirmed by a measured cliff (E1). I could not break it.
2. **Intellectual honesty as a method, not a disclaimer.** The M1-idealization-vs-real split is
   maintained rigorously throughout (theorems are labeled conditional-on-M1 or unconditional); the
   three-tier novelty ledger credits the author's own prior work as baseline rather than burying it;
   the security claim is framed as independence, not a comparative leakage ratio (which the paper
   correctly identifies as the framing that previously admitted a sign error); and a real sign error
   in the coincidence-oracle direction is openly corrected (Remark 8.1) and independently re-validated
   (E4). This is exactly how contested, self-adjacent work should be written.
3. **Data fidelity and reproducibility.** Every one of the four result tables matches the committed
   CSVs to the digit, the experiments are generated by named artifacts, and the sampling-floor
   analysis (deciding whether the measured 0.003 is signal or query noise) is a careful, honestly
   hedged piece of statistical reasoning rather than hand-waving.
4. **Self-collision handled.** The #1 editorial risk (the author's bernoulli_maps "singular hash map"
   shares the abstract codec-output formula, and cipher-maps is the abstraction this instantiates) is
   defused cleanly: the formula is cited as Tier-A baseline and not claimed, and the genuine delta
   (the law's *survival* under linear retrieval plus the span threshold) is what is claimed. The
   differentiation is defensible.
5. **A clean build and a tight narrative arc.** 22 pages, zero undefined refs, a spine that the reader
   can feel (silence -> designable object -> threshold -> security -> evaluation -> honest boundary),
   and a memorable framing. The production gap to a PoPETs submission is small and mechanical.

---

## Review Metadata
- **Specialist lenses applied** (by the area chair, sub-agents unavailable): literature-scout
  (broad + targeted), logic-checker, novelty-assessor, methodology-auditor, prose-auditor,
  citation-verifier, format-validator.
- **Cross-verifications performed**: 3 (M1 logic vs methodology; M2 novelty vs logic; M3
  citations vs prose). All converged: the core results are correct; the issues are precision,
  scholarship-completeness, and production.
- **Disagreements noted**: 0 (no lens contradicted another; the M1 logic finding and the E2
  methodology finding are complementary, the experiment measures exactly the distribution-distance
  quantity that the corrected bound should headline).
- **Data fidelity**: all 4 result tables verified cell-by-cell against `source/results/*.csv`;
  all theorem/bound statements verified against `source/construction-note.md`; build reproduced
  (22 pp, clean).
- **One citation to confirm before submission**: `hu2025retrieval` (Hu-Kuszmaul, FOCS'25),
  exact title/authors/venue unverified by the reviewer and load-bearing for the novelty claim.
