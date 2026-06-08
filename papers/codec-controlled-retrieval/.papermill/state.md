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
    Security contribution: the FreqDist game, with idealized advantage proven exactly zero (from frequency independence T3) and a real bound Adv <= 2(delta(p0)+delta(p1)). Framed as INDEPENDENCE (indistinguishability), not a comparative leakage claim, which is what makes it immune to the direction error that inverted the coincidence-oracle reading.
  one_sentence: "The values an XOR (ribbon) retrieval structure returns for non-member keys are not arbitrary junk: they are uniform over the GF(2) span of the stored codewords, so a public codec (not the private data) determines that distribution, exactly when the stored values span the codec's class quotient, which hands a static data structure the frequency-hiding property that online encrypted-database defenses pay for per query."
  refined: "v2 (thesis crystallized, 2026-06-05; see .papermill/thesis-refined-2026-06-05.md). The novelty framing is now 'we turn a uniformly-acknowledged non-member-output-is-arbitrary into a characterized, codec-designable distribution governed by a sharp GF(2)-span threshold, and read off a structural zero-per-query-cost frequency-hiding property as the consequence.' v1 (bootstrap, 2026-06-05): thesis extracted from the completed maph construction note (source of record maph/docs/codec_controlled_retrieval.md @ a79d9c0). The technical substance (T1-T5, FreqDist security, experiments E1-E4) is already proven, computationally verified, and adversarially reviewed in SP2; this paper reshapes it into PoPETs venue form. Headline is the GF(2)-span threshold T4; the abstract codec-output law is cited as baseline (bernoulli_maps, Honey Encryption). PENDING: papermill:thesis sharpening, papermill:outline, then drafting the sections from the source note."

prior_art:
  last_survey: "2026-06-03 (SP3 scouts: targeted novelty check + broad field map; ledger in the note)"
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
    - "Filic-Paterson CCS 2022 (adversarial correctness/privacy for AMQ-PDS): the closest EXTERNAL filter-confidentiality formalism; covers membership PDS, not the retrieval value-distribution. Read before claiming first-to-characterize. NOT yet in refs.bib."
    - "Patel-Persiano-Yeo-Yung 2019 volume-hiding STE: closest information-theoretic cousin (shape an observable to a public target via a structural construction). NOT yet in refs.bib."
    - "Static Retrieval Revisited (Hu-Kuszmaul FOCS 2025) and Learned Static Function Data Structures (2025): confirm the off-S distribution is still uncharacterized in 2025 SOTA. Strengthens novelty. NOT yet in refs.bib."

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
  - "papermill:thesis (sharpen the central claim and the one-sentence novelty)"
  - "papermill:outline (section-by-section plan; the skeleton in paper/codec_retrieval.tex already mirrors the note)"
  - "Add the three gap citations to refs.bib (Filic-Paterson, Patel et al., Hu-Kuszmaul)"
  - "papermill:draft (multi-agent draft from source/construction-note.md)"
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
