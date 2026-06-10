---
title: "Codec-Controlled Retrieval: Structural Frequency-Hiding from the Non-Member Channel of XOR Retrieval"
bibkey: "towell2026codec"
stage: draft-complete
format: latex
main_file: "paper/codec_retrieval.tex"
bib_file: "paper/refs.bib"
build: "cd paper && make"
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Homogeneous ribbon (XOR) retrieval is a free distribution-transforming decoder: the value returned for a NON-MEMBER key is uniform on the GF(2) span W of the stored codeword patterns, so a public codec fixes the off-set output distribution, and that distribution is INDEPENDENT of how often each value was stored. Codec control holds EXACTLY when W spans the codec's class quotient, a sharp GF(2)-rank threshold (rank pi|_W = log2 K), with no intermediate regime. This yields STRUCTURAL frequency-hiding native to a static data structure: an adversary with oracle access who queries non-members cannot recover storage frequencies (idealized FreqDist advantage exactly zero; real advantage bounded by twice the small, scale-independent, redundancy-governed deviation delta). It is the concrete GF(2)-LINEAR instantiation that the cipher-maps abstraction (random-oracle and RecSplit backends only) does not have."
  novelty: |
    Three-tier novelty ledger (positioned to avoid self-collision):
    1. (A, NOT novel here, cited as baseline) The abstract law "codec codespace allocation controls the non-member output distribution", P(out=v) ~ |class(v)|/2^M, already appears in the author's bernoulli_maps singular-hash-map work (for a RANDOM-ORACLE construction) and is the distribution-transforming-encoder idea of Honey Encryption (juels2014honey; cheng2019pmte). Do NOT headline.
    2. (B, NOVEL) The same law SURVIVES the move to a GF(2)-LINEAR ribbon/XOR retrieval structure, where the output is an XOR of solution rows (not a fresh hash). The entire retrieval literature (Bloomier chazelle2004bloomier; ribbon/BuRR dillinger2022burr; binary-fuse graf2022binaryfuse) treats non-member output as arbitrary junk and never characterizes its distribution.
    3. (C, HEADLINE NOVEL) The sharp GF(2)-span threshold (T4): full codec control holds iff W is transversal to the codec class partition (rank pi|_W = log2 K), a step function of the integer rank. Found nowhere internal or external.
    Security contribution: the FreqDist game, with idealized advantage proven exactly zero (from frequency independence T3) and a real per-observation bound Adv <= delta(p0)+delta(p1) (no factor of 2; corrected 2026-06-09). Framed as INDEPENDENCE (indistinguishability), not a comparative leakage claim, which is what makes it immune to the direction error that inverted the coincidence-oracle reading.
  one_sentence: "The values an XOR (ribbon) retrieval structure returns for non-member keys are not arbitrary junk: they are uniform over the GF(2) span of the stored codewords, so a public codec (not the private data) determines that distribution, exactly when the stored values span the codec's class quotient, which hands a static data structure the frequency-hiding property that online encrypted-database defenses pay for per query."
  refined: "v2 (thesis crystallized, 2026-06-05; see .papermill/thesis-refined-2026-06-05.md). The novelty framing is now 'we turn a uniformly-acknowledged non-member-output-is-arbitrary into a characterized, codec-designable distribution governed by a sharp GF(2)-span threshold, and read off a structural zero-per-query-cost frequency-hiding property as the consequence.' v1 (bootstrap, 2026-06-05): thesis extracted from the completed maph construction note (source of record maph/docs/codec_controlled_retrieval.md @ a79d9c0). The technical substance (T1-T5, FreqDist security, experiments E1-E4) is already proven, computationally verified, and adversarially reviewed in SP2; this paper reshapes it into PoPETs venue form. Headline is the GF(2)-span threshold T4; the abstract codec-output law is cited as baseline (bernoulli_maps, Honey Encryption). PENDING: papermill:thesis sharpening, papermill:outline, then drafting the sections from the source note."

prior_art:
  last_survey: "2026-06-09 (ecosystem-wide adversarial survey, supersedes 2026-06-03 SP3; report at trapdoor-computing/.papermill/prior-art/2026-06-09-ecosystem-survey.md)"
  key_references:
    - "towell_bernoulli_maps: the abstract codec-output formula (singular hash map, RANDOM-ORACLE construction). MUST-DIFFERENTIATE: same formula, different construction."
    - "towell2026ciphermaps: the abstraction this instantiates (random-oracle + RecSplit backends, NO linear backend). MUST-DIFFERENTIATE and cite as home framing. Cites this paper as towell2026codec."
    - "juels2014honey: Honey Encryption distribution-transforming encoder. MUST-DIFFERENTIATE: assumes a uniform seed from a cipher; we PROVE near-uniformity from the linear structure, gated by the span threshold."
    - "cheng2019pmte: Probability Model Transforming Encoders (DTE follow-up)."
    - "dillinger2021ribbon, dillinger2022burr: ribbon retrieval substrate (treats non-member output as junk)."
    - "dietzfelbinger2019gauss: GF(2) Gaussian elimination (the linear-algebra foundation)."
    - "graf2020xor, graf2022binaryfuse: XOR / binary-fuse filters (uniform-random fill of unused slots, the nearest engineering cousin)."
    - "chazelle2004bloomier: Bloomier filter (origin of arbitrary non-member value)."
    - "dietzfelbinger2008succinct: retrieval/AMQ space lower bound."
    - "grubbs2020pancake: PANCAKE frequency smoothing. MUST-DIFFERENTIATE: online access-pattern defense vs our static structural property."
    - "lacharite2018fse: frequency-smoothing encryption (homophonic). MUST-DIFFERENTIATE: cipher layer vs data-structure layer."
    - "naveed2015inference: NKW frequency-analysis attack (the threat the property defends against)."
  gaps:
    # 2026-06-09 survey: the three previously-named gaps are CLOSED. filic2022adversarial (CCS 2022,
    # pp. 1037-1050, simulation-based + membership-only: clean differentiation), patel2019volumehiding
    # (CCS 2019), and hu2025retrieval (FOCS 2025) are all VERIFIED in refs.bib and resolve to the intended
    # papers. Hu-Kuszmaul FOCS 2025 CONFIRMS tier-B novelty: 2025 SOTA leaves off-set output uncharacterized.
    - "MUST-ADD: XorMM (Wang-Sun-Li-Qi-Chen, 'Practical Volume-Hiding Encrypted Multi-Maps with Optimal Overhead and Beyond', CCS 2022). Closest XOR-structure + leakage-hiding + static cousin; uncited; a PoPETs referee will know it; independently corroborates the dynamic-insertion negative (XorMM cannot support insertions). It hides VOLUME, not the non-member value distribution, so novelty is unthreatened."
    - "FRAMING FIX (T4): wire-tap II equivocation theory (incl. 'equivocation matrices', Entropy 2025) already knows 'integer rank controls a security transition' in the abstract. Move one wire-tap-distinguishing sentence INTO the T4 section (the contrast currently lives only in the randenc section ~140 lines later): wire-tap fixes a designed code and asks a secrecy/equivocation question; T4 fixes a public partition and asks a data-dependent output-distribution question. Novelty carriers: the object + the exact K/K' over-weighting with exact-zero step structure."
    - "Optional one-liners: Waffle (SIGMOD 2023, PANCAKE successor); George-Kamara-Moataz-Espiritu ASIACRYPT 2025 (distribution-aware leakage suppression); Goyal-Sridhar-Zheng arXiv 2510.00165 (history-independence: different leak surface, same spirit); Markelon-Filic-Shrimpton CCS 2023; Modern MPHF Survey ACM CSUR 2025 (the 'junk output' anchor)."
    - "VERDICT: tier B SURVIVES (high confidence); tier C / T4 SURVIVES (medium-high). Strongest novelty position of the three mature papers. BibTeX for XorMM + Waffle in the survey report."

experiments:
  - name: "E1: span-threshold cliff (T4)"
    location: "source/results/codec_span/; maph benchmarks/bench_codec_span.cpp"
    status: "complete, replicated with CIs, reviewed"
    note: "TV-to-codespace drops from ~0.5 below rank log2 K to ~0.003 at it. balanced_M4_K4: 0.500 (rank 1) -> 0.00277 (rank 2). balanced_M8_K8: 0.500 (rank 2) -> 0.00505 (rank 3). Sub-threshold CIs degenerate (deterministic in rank). A cliff, not a ramp."
  - name: "E2: FreqDist independence + redundancy (T3/T5)"
    location: "source/results/freq_independence/; maph benchmarks/bench_freq_independence.cpp"
    status: "complete, replicated with CIs + noise-floor baseline, reviewed"
    note: "Cross-profile advantage tracks the noisier build's per-build floor, not the frequency gap. Rich profiles ~0.003; thin-support skew_a (99/0.5/0.5) baseline ~0.019; all three skew_a cross pairs ~0.014 despite different frequency gaps (so it is per-build T5 noise, not frequency leakage)."
  - name: "E3: scale-independence (T5)"
    location: "source/results/scale/; maph benchmarks/bench_codec_span.cpp --mode=scale"
    status: "complete, to N=10M, reviewed"
    note: "Mean TV flat across N: 0.00352 (1e4), 0.00311 (1e5), 0.00352 (1e6), 0.00284 (1e7), CIs overlap. Analytic sampling floor (K=8, n_q=1e5) is 0.00334; measured straddles it, so systematic deviation is at or below resolution. Epsilon auto-scaling at 10M does not degrade control."
  - name: "E4: corrected coincidence oracle"
    location: "source/results/coincidence_oracle/; maph analysis/coincidence_oracle.py"
    status: "complete, Monte Carlo matches closed form for all cells, reviewed"
    note: "acc(t) = 1 - (1/2) sum_v alpha(v)^t. At t=4: uniform 0.99902 (worst defense), huffman 0.96667, intermediate_padded 0.67195 (best). Concentration wins; the inverted 'uniform defends best' reading is corrected. The cipher-maps companion (cor:t-geometry) already states the same correct direction."

venue:
  target: "PoPETs 2027"
  rationale: "Companion to cipher-maps (also PoPETs 2027). PoPETs accepts non-standard privacy models and information-theoretic leakage arguments, and this paper has the implementation-plus-measurement strength cipher-maps lacks. Position as the construction/systems companion to the cipher-maps theory paper."
  candidates:
    - "PoPETs (Privacy Enhancing Technologies Symposium), primary"
    - "CANS 2026 / ESORICS (realistic security home for a new construction with a confidentiality property)"
    - "SEA / ESA (data-structures venue, if pitched as a retrieval-structure result with security as motivation)"
    - "IEEE Transactions on Information Theory (long-term, if recast around the space-accuracy duality)"

next_actions:
  - "Pre-submission only (deferred by design, NOT yet done): switch article -> PETS class + add \\keywords{}, then re-check the page budget (PoPETs 25+2); anonymize for double-blind (author block, self-citations towell2026ciphermaps/bernoulli_maps, repo names maph/bijou); mint the Zenodo artifact DOI and cite it. See SUBMISSION-CHECKLIST.md. (Held back deliberately: pets.cls needs the venue class file; anonymization is submission-time and would obstruct further editing.)"
  - "Optional strengthening: M-METH-2 full re-run with >=10 build seeds at 1e6/1e7 (this pass only SOFTENED the E3 claim + added the rep-cost/floor caveat in prose, not re-run, since a re-run touches the pinned maph artifact). Verify the SWAT author list (abbreviated to 'and others' in refs.bib, flagged in-bib) and the IHOP title before submission."
  - "Optional: scouts' minor extra cites (Modern MPH survey, Non-Malleable Codes from Wire-Tap, Kellaris CCS16, FSE-2024 revisit, Filic ASIACRYPT24) would further round out related work; not required."
---

# Papermill state: Codec-Controlled Retrieval (towell2026codec)

This paper is the construction-and-experiments companion to cipher-maps. Its
technical substance is COMPLETE and reviewed (SP2 in the maph repo); SP3 reshapes
it into PoPETs venue form. The source of record for the technical content is
`maph/docs/codec_controlled_retrieval.md` (commit `a79d9c0`), snapshotted at
`source/construction-note.md`. Experiment data is under `source/results/`.

See the YAML frontmatter for the thesis, the three-tier novelty ledger, the
prior-art and must-differentiate list, the four completed experiments, the venue
plan, and the next actions.

## Draft record (2026-06-05): full body drafted, compiles to 22 pages

`paper/codec_retrieval.tex` is now a complete LaTeX draft realizing the
outline-2026-06-05 structure. It was produced by reshaping `source/construction-note.md`
into PoPETs venue prose (single-orchestrator pass; the technical substance was already
proven and reviewed, so no claims were generated or re-derived). All theorem statements,
bounds, and the E1-E4 numbers were transcribed faithfully and verified against the
`source/results/` CSVs.

- Stage moved drafting -> draft-complete.
- Structure: 1 Intro, 2 Background/linear-retrieval view, 3 T1/T2 (support + idealized
  law), 4 T3 (frequency independence), 5 T4 (sharp threshold, HEADLINE), 6 T5
  (idealized-to-real), 7 Security/FreqDist, 8 two-attacks reconciliation, 9 Evaluation
  (E1-E4 tables), 10 Related work (three-tier ledger + 4 must-differentiate + 3 gap
  cites), 11 Discussion/limitations/conclusion, Appendix A (full R(z)=W induction).
  Theorems labeled: thm:support, thm:idealized, thm:freqindep, lem:subspace-coset,
  thm:threshold, thm:freqdist-ideal, thm:freqdist-real.
- Framing honored: abstract leads with B/C, cites A (bernoulli_maps + Honey DTE) as
  baseline; T1 kept as the M1 idealization; security framed as independence not
  comparative; coincidence-oracle direction corrected (concentrated/Huffman defends
  best); T5 labeled a characterization not a closed-form bound.
- Build: `cd paper && make` -> 22 pages, zero undefined refs/cites, zero overfull boxes,
  no hard errors. Minimal in-directory repairs: escaped an underscore in a refs.bib note
  field; added a 4th pdflatex pass + refs.bib prereq to the Makefile; added a \TVsamp
  preamble macro (since \TV already carries a subscript).
- All 15 cite keys used are in refs.bib (incl. the 3 gap cites filic2022adversarial,
  patel2019volumehiding, hu2025retrieval). dietzfelbinger2008succinct and
  dietzfelbinger2019gauss are present but currently uncited (available if wanted).
- Construction record: `.papermill/drafts/2026-06-05/writing-plan.md`.
- NEXT: papermill:format-validator pass (venue formatting / PoPETs class if switching
  off article); optional move of remaining T1-T4 proofs into the appendix if a page
  budget is imposed; optional citation of the two uncited dietzfelbinger entries.

## Discovery integration (2026-06-08): three open questions resolved + two design-space negatives

Integrated the upgraded maph note (`maph/docs/codec_controlled_retrieval.md` @ `f4855fc`,
branch `sp4-discovery-integration`, snapshotted to `source/construction-note.md` with a
provenance header) into `paper/codec_retrieval.tex`. Three previously-deferred open
questions are now stated results, and two honest negatives were added to the discussion.

RESOLVED OPEN QUESTIONS (now theorems/propositions in the paper):
1. Skewed-codec threshold (was `rem:skewed`, "explicitly deferred as open"). Replaced by
   the T4b GRADED result (new subsection `sec:t4b`, `thm:graded`, `ex:graded`): per-class
   mass `q(v) = h_v * 2^(dim(W cap C_{l_v}) - dim W)`; the realizable masses form a
   NON-INCREASING LADDER in code length (necessary, not sufficient); a uniform target over
   the skew {1,2,3,3} codec is UNREACHABLE (min-TV 1/4); full-span control reproduces the
   designed Kraft law `q(v)=2^(-l_v)`. Full subspace enumeration backing in new
   `app:skewed`.
2. m_min conjecture (was the "Conjecture (qualitative, not proven)" in `rem:t5-bound`).
   Replaced by the T5b COGIRTH theorem (new subsection `sec:t5b`, `thm:cogirth`): the
   matroid cogirth d* of the stored column system over Q is the exact, tight adversarial
   erasure budget (broken step at TV=1/2 at exactly d* deletions); floor((d*-1)/2)
   error-correction; d* >= (K/2)*m_min under full support converts the conjecture to a
   theorem. Framing: RANK governs control (T4); COGIRTH governs robustness (T5b). Scope
   nuance recorded: T5b governs the BINARY control criterion + erasure budget; the
   within-regime delta MAGNITUDE stays the empirical T5 characterization (`rem:t5-bound`
   retained for the magnitude only). Cite-and-differentiate Massey 1993 + Gluesing-Luerssen
   2014.
3. Randomized-encoding angle (Q#5; was a future-work "white-box or randomized-encoding
   angle"). Now `thm:randenc` (new subsection `sec:randenc`): within-class randomized
   encoding leaves the entire non-member law EXACTLY invariant (proven balanced, verified
   skewed) while diverging the white-box solution per build. Snapshot confidentiality at
   zero per-query cost. Primitive = wiretap coset coding (Wyner 1975; Ozarow-Wyner 1984),
   cited; new content is the invariance-plus-divergence statement for a static GF(2)
   structure.

TWO DISCUSSION NEGATIVES (new "Two probed design-space negatives" paragraph in
`sec:conclusion`, honest negatives, NOT theorems):
- SPLIT-PAYLOAD HYBRID is empty: a fused (r fingerprint + (M-r) value) single-system
  retrieval never Pareto-dominates the separate composition (Delta bits/key = 0.00000;
  only saving ~192/N bits of metadata; 1.7x faster build does not move the frontier).
- DYNAMIC-INSERTION OBSTRUCTION: insertion repair is supercritical (back-substitution O(N),
  mean offspring ~W/2.5 >> 1); the band width needed for solvability (W~64) is exactly the
  width that makes repair supercritical, and 8-54% of insertions are infeasible. Local
  re-solve provably loses to periodic rebuild (crossover ~2W). Explains why the structure
  is static. Positioned against Kuszmaul-Walzer STOC 2024, Kuszmaul-Putterman SODA 2025,
  Bercea-Even STOC 2022, Ribbon (build-only), IXOR/IBIF TNSM 2024.

BIB: added massey1993minimal, gluesingluerssen2014fourier (arXiv 1304.1207),
wyner1975wiretap, ozarowwyner1984wiretap, kuszmaulwalzer2024dynamic,
kuszmaulputterman2025incremental (arXiv 2410.10002), berceaeven2022extendable,
reviriego2024ixor (TNSM 2024). Some fields (Kuszmaul-Putterman author list, IXOR/IBIF
exact title/authors) are approximate and flagged in-bib to verify before submission.

ABSTRACT + INTRO updated: abstract now mentions the graded skewed regime, the cogirth
robustness invariant, and the randomized-encoding invariance (briefly); intro contributions
list gained item (D, robustness) and extended item (C) with the graded resolution, plus a
randomized-encoding sentence and a sentence flagging the two negatives. Limitations and
Future-work paragraphs rewritten so the three resolved items are no longer listed as open;
remaining open items are now: the skewed flag-level proofs of robustness and invariance, the
complete realizable-set characterization, and the within-regime continuous-delta-magnitude
bound.

BUILD: `cd paper && make` -> 29 pages (was 23), 0 undefined refs/cites, 0 bibtex warnings.
Two large display overfull boxes I introduced were fixed (reflowed the cogirth definition
and the rank/cogirth separation display); 3 minor overfull boxes remain (two sub-1pt, one
38pt in the PRE-EXISTING leakage-abuse related-work paragraph, not introduced here).
Stage stays draft-complete (results integrated; no new venue/format change).

## Thesis crystallization + abstract tighten (2026-06-09)

papermill:status + papermill:thesis pass. The v2 thesis stands; crystallized it as a
3-tier hierarchy (A baseline / B novel / C headline threshold) so the abstract could
inherit that shape. The abstract was 509 words narrating all nine theorem families at
flat weight; rewrote it to the "spine + duality" scope (~308 words, down from 509, a ~40%
cut; the AskUserQuestion option labels' "~200w" estimate ran low, but the approved preview
text is verbatim what landed, and the real win is structural): the B/C spine, the
sharp balanced threshold, the rank-governs-control / cogirth-governs-robustness duality,
the FreqDist security payoff, and a one-clause coincidence-oracle honesty note. Deferred
to the body (still fully present there): the T4b graded regime, T4c, and the
randomized-encoding result.

Correctness fix folded in: the abstract now states the real FreqDist advantage as
<= delta(p0)+delta(p1) (NO factor of 2), matching thm:freqdist-real and the 2026-06-05
polish note ("Factor-2 phrasing gone"). An interim option preview had reintroduced the
2x; corrected against the body theorem before writing.

Build: cd paper && make -> 32 pages, 0 undefined refs/cites, 0 hard errors, 2 pre-existing
overfull boxes (lines 1377, 1747; not the abstract). Stage unchanged (draft-complete).
Also: created the paper-local CLAUDE.md and added a codec-controlled-retrieval row to
~/github/CLAUDE.md.

NEXT: fresh papermill:review of the current 32pp (prior review predates the +10pp of new
theorems), then polish + anonymize.

## Multi-agent review (2026-06-09)

Ran papermill:review as 8 specialists dispatched in parallel from the main loop (logic,
methodology, novelty, prose, citation, format, + targeted & broad literature scouts), so
the serial fallback that hit the 2026-06-05 run did not recur. Report:
`.papermill/reviews/2026-06-09/review.md`. Verdict: MINOR REVISION (no incorrect core
result; the 5 new theorems are sound, every E1-E4 number matches the CSVs, and both scouts
confirm the headline novelty is SAFE: no prior work characterizes the non-member value
distribution of any retrieval structure).

ONE CRITICAL, fixed this pass: the abstract+intro claimed multi-query FreqDist advantage
<= delta(p0)+delta(p1) in the REAL construction. False for delta>0 (two fixed distinct laws
become perfectly distinguishable as n->inf); the bound is a SINGLE-OBSERVATION cap, exactly
as thm:freqdist-real is scoped. This is the prior review's M1, fixed in the theorem but
never propagated to the front matter; the 2026-06-09 abstract rewrite preserved it. Now
corrected in both abstract and intro (idealized zero holds for any query count; real claim
is per-observation). Cross-verified by logic + prose + methodology.

ALSO fixed this pass: cheng2019pmte had a fabricated author list (corrected to the verified
5 authors); dietzfelbinger2019gauss venue STACS -> ESA 2019; abstract floor wording "at or
below" -> "straddle" (two of four E3 means sit above the analytic floor). Build still clean
(32pp, 0 undefined, no hard errors).

DEFERRED (need author judgment / larger work; in next_actions): M-NOV-1 self-collision with
cipher-maps prop:rand-encoding (the invariance is shared; our white-box-divergence + skewed
counterexample is the genuine delta, currently unflagged); M-PROSE-1/2/3 the headline is
buried under the robustness/refinement material before its security payoff, sec:randenc is
misfiled in the threshold section, contributions bullets overloaded; M-METH-2 large-N reps;
3 Major new citations (Learned Static Function DS, IHOP, SWAT); pets.cls + keywords +
anonymization. Citation-verifier separately CONFIRMED kuszmaulputterman2025incremental (the
author list flagged approximate in the 2026-06-08 record) is in fact correct.

## Full revision pass against the 2026-06-09 review (2026-06-09)

Implemented essentially all review findings except the pre-submission venue items. Build
after: `cd paper && make` -> 33 pages (was 32), 0 undefined refs/cites, 0 hard errors, 1
negligible 0.82pt overfull box (the 38pt related-work box is fixed), 0 em-dashes.

STRUCTURAL (M-PROSE-1/2): full restructure. The four refinement blocks (sec:t4b skewed/
graded + thm:realizable, sec:t5b cogirth, sec:t5c per-rung cogirth, sec:randenc) were moved
out of the spine into a NEW section 9 "Refinements: the skewed regime, robustness, and
randomized encoding" (sec:refinements), placed after the reconciliation section. The spine is
now uninterrupted: threshold (5) -> idealized-to-real (6) -> security (7) -> two-attacks (8) ->
refinements (9) -> evaluation (10). Done via a line-slice reassembly (blocks tile the file
exactly; cleveref kept every cross-ref resolving, verified by a clean build). Added a
forward-pointer at the end of section 5 and a section-9 intro.

CONTENT FIXES applied:
- C1 multi-query overclaim also fixed in the conclusion (was a third copy); abstract+intro
  fixed in the prior pass. M-LOGIC-1: freqdist-real proof prose recast to separate the
  single-observation bound from the (correct) frequency-independence-of-the-separation argument.
- M-PROSE-3: contributions split (item C = threshold only; new item D "refinements and
  robustness" gathers graded/realizable/cogirth/per-rung/randenc with a pointer to
  sec:refinements; dropped the undefined "mass-over-codespace-share"). Removed the redundant
  standalone randenc sentence from the intro (also fixes prose-m1: "saturated" before its def).
- M-NOV-1: one differentiation sentence added to related-work point (2) isolating the genuine
  delta vs cipher-maps prop:rand-encoding (white-box z-divergence + skewed boundary).
- Citations: added oya2022ihop, zheng2024swat, hermann2025learned to refs.bib with prose
  (IHOP/SWAT in the frequency-smoothing paragraph; Learned Static Function as the closest
  mechanical cousin in the intro). m3: FINDINGS.md bound synced to drop the 2(...).
- M-LOGIC-2: saturation-sufficiency now explicitly labeled as the computationally-verified step
  with the general closed form left open. M-METH-2: E3 "flat in N" softened, rep counts + cost
  + the n_q-dependent floor (E1/E2 at 5e4 -> ~0.0047; E3 at 1e5 -> 0.00334) stated.
- Minors: logic m1 (TV>=1/4 justification corrected to total-excess), logic m2 (cogirth
  top-bit wording), MIN-1 (zipf 0.34 -> 0.43), MIN-4 (E4 caption near-saturation SE), prose-m2
  (float labels "punchline"/"witness" -> descriptive), prose-m4 (junk motif trimmed to the
  abstract+conclusion bookend), M-METH-1 straddle (prior pass), 38pt overfull reflow.

CONSCIOUSLY DECLINED (with reason): prose-m5 (move the M1-on-image remark to the appendix) left
in the body because it serves MIN-5 (the realizable-band caveat) where a reader needs it; the
two cosmetic bibkey renames (reviriego/gluesing) skipped as no-factual-consequence; pets.cls /
keywords / anonymization / Zenodo DOI held for the submission pass (see next_actions).

## PoPETs submission port (2026-06-09)

Confirmed PoPETs 2027 reqs: body <= 12 pages excluding bib + clearly-marked appendices; format
acmart sigconf + \usepackage{popets}; double-blind; submit at submit.petsymposium.org. Next firm
deadline Issue 2 = 2026-08-31 (then Nov 30, Feb 28).

Created a SEPARATE submission version, preserving the full article version:
- paper/codec_retrieval.tex + refs.bib = de-anonymized 33pp article version (unchanged).
- paper/codec_retrieval_popets.tex + refs_popets.bib = the PoPETs submission version.

Submission version (build: pdflatex; bibtex; pdflatex x2):
- acmart sigconf (nonacm, anonymous). amssymb \Bbbk clash fixed; remark defined locally (acmart
  predefines theorem/lemma/definition/example but not remark); topmatter + keywords; acmnumeric cites.
- PAGE FIT: §9 Refinements (4 theorem-heavy subsections) MOVED to a new appendix (app:refinements),
  a tight summary kept in body §9. BODY = 12 pages exactly (concl p12, appendix from p13). Hits <=12.
- ANONYMIZED: acmart anonymous hides authors; in-body "the author's X" -> third person; "maph" ->
  "an open-source research codebase"; the 2 self-cite bib entries anonymized in refs_popets.bib.
  Verified pdftotext = 0 identity strings.
- BUILD: 0 errors, 0 undefined. Overflow: fixed 2 wide E-tables (\resizebox) + 2 worst body displays
  (aligned). REMAINING cosmetic: 3 minor body overflows (28/11/10pt) + ~9 appendix overflows
  (worst 66/63/57pt; same aligned/resizebox fix).

REMAINING TO SUBMIT (nothing blocks the essentials; deadline 2026-08-31):
1. Drop official popets.sty into paper/ (PETS author kit; not findable via public URL; built on
   acmart nonacm sigconf as faithful base, popets.sty only changes masthead, not the 12pp fit).
2. Polish ~12 remaining overflow boxes (mechanical aligned/resizebox).
3. Check full PoPETs guidelines for an AI/LLM-disclosure requirement; add a statement if required
   (this paper used multi-agent drafting/review substantially).
4. Human proofread of the anonymized PDF.
5. Zenodo artifact DOI: defer to camera-ready.
6. THE UPLOAD is the user's (authenticated HotCRP at submit.petsymposium.org).

## Polish + AI disclosure complete (2026-06-09)

Finished the submission-version polish. Overflow boxes 25 -> 1 (the last is sub-5pt,
invisible): added \emergencystretch{3em} (cleared most prose boxes), shrank+shortened the
back-substitution verbatim block (\footnotesize + trimmed inline comments), and aligned-broke
the wide appendix displays (flag chain, eq:graded with \frac, the rank/cogirth textsc display)
plus the body TV-triangle display. Added the PoPETs-required \section*{Disclosure of generative
AI use} as back matter (excluded from the page count): honest and specific about drafting/review,
human verification against the artifact gates, and the AI-assisted-then-verified bibliography
(noting the one caught-and-corrected author-list error), per the policy's BibTeX caution. Verified
in the rendered PDF: body still 12 pages, 0 errors, 0 identity strings, disclosure present.
Submission version is now clean modulo the popets.sty masthead swap and a human proofread.

## Venue structure + submission tracker (2026-06-09)

Reorganized for per-venue tailoring (user request). Canonical content stays in
paper/codec_retrieval.tex + paper/refs.bib (article, de-anonymized). The PoPETs version
moved to venue/popets/ (main.tex + refs.bib + Makefile + NOTES.md). Cross-venue status and
the decision log now live in the top-level SUBMISSIONS.md (the submission ledger);
venue/README.md documents the convention. Build the PoPETs version: cd venue/popets && make
(verified: 12pp body, 0 errors, 0 leaks, AI disclosure present). PoPETs status: PREPARED,
pre-submission; remaining = popets.sty swap + proofread + HotCRP upload (deadline 2026-08-31).
