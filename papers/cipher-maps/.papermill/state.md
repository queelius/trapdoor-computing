---
title: "Cipher Maps: Total Functions as Trapdoor Approximations"
stage: revision
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "A cipher map -- a total, trapdoored function on bit strings whose privacy rests on TOTALITY (the untrusted machine sees only a total function and cannot distinguish real inputs from noise) -- makes outsourced approximate function evaluation private with leakage that is MEASURABLE rather than negligible, characterized by four properties: totality, representation uniformity (delta), correctness (eta), and composability (eta_total <= 1 - prod(1-eta_i)). The cipher-map ABSTRACTION is the unit of analysis; the acceptance-predicate design lever, the (TV, length) leakage-size frontier (distinct space-optimal and TV-optimal corners; 42x TV reduction at 17% length overhead), and the unification of three literatures (approximate data structures, frequency-hiding encryption, encrypted search) are CONSEQUENCES of the abstraction, not the headline."
  novelty: |
    1. The cipher-map ABSTRACTION as the unit of analysis: a total, trapdoored function characterized by four MEASURABLE properties (totality, delta, eta, composability), replacing negligible-in-security-parameter framing with measurable leakage (QIF tradition). Totality (noise-in -> noise-out) is the foundational privacy mechanism; the acceptance-predicate lever and the unification are consequences of the abstraction. This is the headline framework contribution.
    2. Self-contained quantitative confidentiality: the delta -> leakage bound is proved IN-PAPER (prop:confidentiality via Fannes-Audenaert, plus prop:homophonic's tight achievable-delta TV < (|X|-1)/N), so no load-bearing claim is deferred. Companion towell2026maxconf is cited only for the broader entropy-ratio program.
    3. The acceptance predicate as the single design lever within the abstraction, with the (TV, L) Pareto frontier refining the Shannon-frequency duality: the space-optimal (Shannon/Huffman) and leakage-optimal (TV) corners are DISTINCT under integer codeword constraints (42x TV reduction at 17% length overhead), not one simultaneous optimum.
    4. Predictable composition: the chain bound eta_total <= 1 - prod(1-eta_i), plus a closed-form multi-instance coincidence-oracle bound (accuracy = 1 - 1/2 sum_y alpha(y)^t for t shared-f instances under independent seeds), defended by randomized encoding (K(x) > 1) rather than codec retuning. Concentrated (Huffman-style) partitions are optimal at every t.
    5. Unification of three previously-disconnected literatures (approximate data structures, frequency-hiding encryption, encrypted search) as instances of one abstraction, with empirical Le Cam tightness across the codec sweep confirming the bound is realized by Bayes-optimal attackers (not just an information-theoretic upper bound).
  refined: "v5 (abstraction-forward redirection + self-contained confidentiality, 2026-06-03). Two changes from v4. (1) Thesis re-pointed at the cipher-map ABSTRACTION (the four measurable properties, with totality / noise-in -> noise-out as the foundational privacy mechanism) as the unit of analysis; the acceptance-predicate lever and the three-literature unification are reframed as CONSEQUENCES, not the headline. (2) The delta -> leakage confidentiality bound is now SELF-CONTAINED in-paper (prop:confidentiality + prop:homophonic's tight TV < (|X|-1)/N); companion towell2026maxconf demoted from formal home of a load-bearing claim to cite-for-depth on the broader entropy-ratio program -- motivated by maxconf being unposted (MAJ-6/CITE-6) and the 2026-06-02 finding that maxconf's |X|/(2N) multiplicity constant is wrong for n>=3 while cipher-maps' own bound is correct and tight. Also corrects the stale 'Shannon-optimal allocation does space + leakage simultaneously' framing to 'distinct corners of a frontier'. Prior versions: v1 (2026-03-19), v2 acceptance-predicate-forward (2026-03-27), v3 framework-first + Pareto + incorrect inversion (2026-05-04), v4 inversion corrected (2026-05-17). PENDING manuscript propagation: abstract '(formal framework in companion work)' hedge -> self-contained, intro positioning paragraph, parent CLAUDE.md 'simultaneously' line. OPEN (under discussion 2026-06-03): whether to fold the C(f) vs C(A->B) functorial-notation clarification into the cipher-maps section 2.1 convention note -- C as type constructor on A->B yields the cipher space C(A->B); C as functorial action on morphism f yields the cipher map C(f) = fhat; coherence = algebraic-cipher-types Prop 4.3 (points of C(A->B) are exactly the maps C(A)->C(B))."

prior_art:
  last_survey: "2026-05-17"
  key_references:
    - "bloom1970space: Bloom filters (HashSet subsumes as k=1 special case)"
    - "fredman1984storing: FKS perfect hashing"
    - "belazzougui2009hash: Minimal perfect hash functions (CHD)"
    - "gentry2009fully: FHE (exact computation on ciphertexts, high overhead)"
    - "yao1982protocols: Garbled circuits (one-time use, exact)"
    - "goldreich1996software: ORAM (access-pattern hiding)"
    - "curtmola2006searchable: SSE with simulation-based security (IND-CKA)"
    - "bellare1993random: Random oracle model"
    - "simmons1979symmetric: Homophonic substitution (historical connection)"
    - "naveed2015inference: Inference attacks on PPE (added in M3 fix)"
    - "islam2012access: SSE access pattern disclosure (added in M3 fix)"
    - "cash2015leakage: Leakage-abuse attacks on SSE (added 2026-04-28)"
    - "juels2014honey: Honey encryption (added 2026-04-28)"
    - "smith2009foundations: QIF foundations (R5 positioning)"
    - "alvim2012measuring: Generalized gain functions (R5 positioning)"
    - "dodis2005entropic: Entropic security (R5 positioning)"
    - "kerschbaum2015frequency: Frequency-hiding OPE (added R6 fix)"
    - "kamara2019computationally: Volume-hiding STE (added R6 fix)"
    - "esposito2020recsplit: RecSplit MPHF (added R6 fix)"
    - "lecam1986asymptotic: Le Cam two-point lemma (used at §5.2)"
    - "warner1965randomized: Randomized response (added R6 NOV-4)"
    - "towell2026codec: Companion experiment suite (added R7 §10.6)"
    - "towell2026algebraic: Companion algebraic types (now used at §10.3 R7)"
  gaps:
    - "Huffman 1952 (NOT in bib; R7 CITE-2 strong recommend - paper centers Huffman codes)"
    - "Patel-Persiano-Yeo-Yung 2019 volume-hiding STE (NOT in bib; R6/R7 strong recommend)"
    - "Alvim et al 2020 Science of QIF textbook (NOT in bib; R6/R7 recommend)"
    - "Kopf-Smith 2010 min-entropy leakage (NOT in bib; R6/R7 strong recommend - foundational measure choice)"
    - "Cover-Thomas 2006 (NOT in bib; R7 recommend - Kraft inequality and coding background)"
    - "Pouliot-Wright 2016 Kraken co-occurrence attack (NOT in bib; R6/R7 recommend for §8.2)"
    - "Geng-Smith 2025 or equivalent QIF multi-instance work (NOT in bib; R7 CITE-MIN-3 recommend for §8.3)"
    - "Bellare-Ristenpart-Rogaway-Stegers 2009 FPE (NOT in bib; R6 consider)"

experiments:
  - name: "20 Newsgroups encrypted search"
    location: "§10.3 lines 2307-2391"
    status: "R6 CRIT-1 noise-floor explanation landed; R7 verified consistent. Single-run, no Bloom baseline (R7 MAJ-10)."
    note: "R6 CRIT-1 (3-term AND FP arithmetic) is now addressed via explicit noise-floor formula at §10.3 lines 2366-2375 with the derivation deferred to towell2026algebraic. Throughput numbers consistent (713 docs/sec full corpus, 843 at 5K). R7 carries over the single-run / no-replication / no-Bloom-baseline limitations."
  - name: "Codec security empirical study (R7 new)"
    location: "§10.6 lines 2455-2647"
    status: "R7 introduced; setup careful, formula and numerical values verified correct, but interpretation inverted (R7 CRIT-1)"
    note: "5 codecs x 5 t-values = 25 cells, 24/25 inside Wilson 95% CI. The formula 1 - (1/2) sum_y alpha(y)^t and the empirical numbers (0.9999 uniform, 0.9844 Huffman at t=5) match perfectly. The Corollary 8.x interpretation ('uniform defends 16x better at t>=2') is the direction-reversed reading: higher attacker accuracy = WORSE defense, so uniform is WORSE defense. Huffman wins at every t. Source experiment bernoulli/.../14_coincidence_oracle.py / RESULTS_14.md has the same inversion in its writeup."
  - name: "Le Cam tightness sweep (R7 new)"
    location: "§10.6 lines 2485-2516"
    status: "R7 introduced; clean result, well-supported"
    note: "Three attacker classes (Bayes, logistic, 1-NN) achieve same accuracy to within 0.014 sampling noise at n=5000; mean Bayes gap to Le Cam UB is -0.0004 (statistically zero). Empirical confirmation that Le Cam UB is realized by Bayes-optimal attackers in practice."
  - name: "(TV, L) Pareto frontier (R7 new)"
    location: "§10.6 lines 2518-2554"
    status: "R7 introduced; sharp empirical finding, no direction issues"
    note: "14 configurations enumerated as |Y| x n x p_y shape combinations. Huffman is on the Pareto frontier in 14/14, TV-optimal in 7/14. Heavy-tailed p_y = (0.9, 0.0143, ...) gives 42x TV reduction (0.40 to 0.0094) at 17% L overhead. 14 configs not enumerated in detail (R7 MAJ-9)."

venue:
  target: "PoPETs 2027"
  candidates:
    - "PETS (Privacy Enhancing Technologies Symposium)"
    - "IEEE Transactions on Information Theory"
    - "STACS/ISAAC (theory of computation)"

review_history:
  - date: "2026-06-02"
    reviewer: "papermill (Round 9 single-orchestrator; subagent dispatch unavailable)"
    recommendation: "minor-revision (conditional on MAJ-1 sister-paper Zenodo DOIs + LOG-MAJ-1 one-char skew fix)"
    summary: "0 critical, 2 major (LOG-MAJ-1/METH-MAJ-1 NEW: Zipf skew mislabeled s=1 at section 8.3 line 1934 and section 10.6 Setup line 2609, but headline numbers max alpha=0.5 / acc 0.984 / 132x require s=1.2 which is what source experiment 14_coincidence_oracle.py line 77 actually uses [1/(i+1)^1.2]; literal Huffman on s=1 gives max alpha=0.25 and does not reproduce; MAJ-1 sister-paper preprints carry-over R6/R7/R8 [exposure reduced: new homophonic prop now self-contained, only Prop 5.1 still defers to maxconf Thm 4.1 part 3]), 9 minor (METH-MIN-1 NEW E1 table caption claims m up to 18266 but experiment ran on 11,004-doc training split; LOG-MIN-1 kappa(y) undefined lines 2098-2101; LOG-MIN-3 n-vs-M bit-width unreconciled section 10.6; LOG-MIN-2 Prop 8.2 saturation informal carry-over; METH-MIN-2/3/4 single-run Le Cam/key-universe/Pareto carry-overs; CITE-MIN-1 Huffman 1952; presentation carry-overs), 6 suggestions. Format majors FMT-MAJ-1/2/3 (article class + 39pp + anonymization) carry-over, counted per-domain."
    resolution: "Pending. THE ROUND'S CENTERPIECE VERIFIED CLEAN: new Proposition prop:homophonic (exact TV identity + Simmons bound TV<|X|/N) is mathematically correct [confirmed numerically 6 configs], fully self-contained [no maxconf, no unproven general-n result], correctly targets within-image uniformity with clean prose bridge to full-space delta. K(x) propto D(x) direction correct at all 5 sites, D/K defined before use. d_TV-inline + removed-deferral + codec-inventory edits introduced NO regressions. R8 MAJ-2 (codec inventory) + MAJ-3 (E4 H1 wording) both CLOSED. 16 proofs re-verified all PASS. R7 CRIT-1 + K prescription stay closed. The aggressive direction/parameter sweep found a FOURTH error of the user-flagged family: s=1 mislabel (a parameter/constant slip, not direction; evaded R8 because ratio was checked vs formula without reconstructing Huffman code from stated skew). Fix is one char at 2 sites; numbers stay correct [validated vs E3 CSV max_q=0.5]. Direct answer to user: paper IS submission-ready once (a) Zenodo DOIs minted and (b) s=1.2 fix applied, plus the planned template/anonymization editorial pass. NO substantive technical work remains: no proof needs fixing, no experiment needs rerunning, no claim unsupported once s=1.2 and m=11004 labels corrected. Confidence: high."
  - date: "2026-03-19"
    reviewer: "papermill"
    recommendation: "major-revision"
    summary: "Paper rebuilt from scratch using formalism doc. 8/9 proofs PASS, 1 minor."
    resolution: "All issues addressed in rebuild."
  - date: "2026-03-26"
    reviewer: "papermill (8-specialist)"
    recommendation: "minor-revision"
    summary: "0 critical, 3 major (composition equality/inequality, ROM undefined, trust model ordering), 12 minor, 5 suggestions."
    resolution: "All 3 majors fixed: composition stated as inequality, ROM prelim added with Bellare-Rogaway cite, trust model moved before constructions."
  - date: "2026-03-28"
    reviewer: "papermill (8-specialist) Round 3"
    recommendation: "major-revision"
    summary: "0 critical, 6 major (M1 no security def, M2 no experiments, M3 missing leakage-abuse + honey encryption citations, M4 composition formula inconsistency persists, M5 space optimality framing, M6 ROM implications), 11 minor, 4 suggestions."
    resolution: "M3, M4, M5, M6 addressed 2026-04-28 in same-day editorial pass. M1 and M2 deferred."
  - date: "2026-04-28"
    reviewer: "papermill (Round 4 single-orchestrator multi-specialist)"
    recommendation: "major-revision"
    summary: "0 critical, 5 major (MAJ-1 Theorem 6.2 Step 2 reads as double-counting, MAJ-2 experimental paragraph reproducibility-thin, MAJ-3 abstract framing creates expectations later disclaimed, MAJ-4 §9.5 disclaims standard frameworks without positive positioning, MAJ-5 ROM paragraph promises 4 assumptions lists 3), 26 minor (10 carry-over from Round 3 + 16 new), 8 suggestions."
    resolution: "Round 4 majors mostly addressed via R5 restructure: MAJ-1 (Theorem 6.2 Step 2 rewritten), MAJ-3 (abstract rewritten with QIF positioning), MAJ-4 (§5 added Confidentiality Measure subsection in QIF tradition), MAJ-5 (ROM paragraph now lists 4 assumptions). MAJ-2 (experimental paragraph) NOT addressed; §10 promotion did not land."
  - date: "2026-04-30"
    reviewer: "papermill (Round 5 single-orchestrator multi-specialist; resumed after rate-limit)"
    recommendation: "major-revision"
    summary: "3 critical (CITE-1 wrong theorem# rekeying, CITE-2 wrong theorem# maxconf load-bearing, METH-1 §10 promotion not in manuscript), 14 major (LOG-1 §5.2 #2 overstates, LOG-2 §5.2 #3 wrong Pinsker direction, LOG-3 H* mismatch with maxconf, NOV-1 novelty fragmented across 3 unpublished, PROSE-1 intro/§6+ register seam, NOV-2/CITE-4 Kerschbaum uncited, NOV-3/CITE-5 Kamara-Moataz uncited, CITE-3 RecSplit uncited, METH-2 no CIs, METH-3 query distribution unstated, METH-4 library uncited, FMT-1 article class not PoPETs, PROSE-2 §5.2 mixed registers, CITE-6 4 Manuscript-in-prep entries), 26 minor, 19 suggestions."
    resolution: "R6 (2026-05-02) Path A applied. CITE-2 corrected to Theorem 4.1 part 3. CITE-1 reverted to Theorem 7.1 (R5 reviewer's miscount). METH-1 §10 promotion landed (5 subsections). LOG-1/LOG-2 prose fixes landed (Le Cam, data-processing). LOG-3 partially addressed via redefinition. NOV-2/CITE-4 Kerschbaum cite added with mechanism contrast. NOV-3/CITE-5 Kamara-Moataz cite added. CITE-3 RecSplit cited at §10.1 (still missing at §6.4 first mention). METH-3 query distribution stated. METH-4 library cited. PROSE-1 register seam fixed via §5 restructure. PROSE-2 §5.2 register unified. CITE-6 still pending sister-paper preprint posting. FMT-1 venue port still pending."
  - date: "2026-05-02"
    reviewer: "papermill (Round 6 single-orchestrator; subagent dispatch unavailable)"
    recommendation: "major-revision"
    summary: "1 critical (CRIT-1: 3-term AND FP arithmetic 12 observed vs 0.6-2.3 expected under independence model; breaks headline empirical claim), 7 major (MAJ-1 entropy ratio defined H(X|view)/H*(X) in intro vs H(Q)/n in §5.1; MAJ-2 entropy ratio not in Definition environment; MAJ-3 Theorem 6.2 Step 2 still loose conflating search-time and storage cost; MAJ-4 throughput numbers inconsistent across §6.4 and §10.3; MAJ-5 NOV-N2 framework contribution needs explicit framing in §1; MAJ-6 CITE-6 load-bearing sister paper preprints not yet posted; MAJ-7 LOG-S1 same-secret composition vs Definition 7.2 independent seeds mismatch carry-over), 22 minor, 10 suggestions."
    resolution: "R7 (2026-05-17) confirmed: CRIT-1 noise-floor formula landed at §10.3 with explicit derivation and bound; MAJ-1+MAJ-2 entropy ratio Definition env landed at §5.1; MAJ-3 Theorem 6.2 Step 2 separation of storage vs search costs landed; MAJ-4 throughput consistent (713 docs/sec full corpus); MAJ-5 framework framing landed at §1 lines 120-149; MAJ-6 sister-paper preprints still pending; MAJ-7 master-secret vs operational-subderivation clarified at Remark 4.x."
  - date: "2026-05-27"
    reviewer: "papermill (Round 8 single-orchestrator; subagent dispatch unavailable)"
    recommendation: "minor-revision (conditional on MAJ-1 sister-paper Zenodo posting)"
    summary: "0 critical (R7 CRIT-1 closed, K(x) prescription direction closed), 6 major (MAJ-1 sister-paper preprints carry-over R6/R7; MAJ-2 codec inventory mismatch between section 10.6 Le Cam table and E3 multi-instance table; MAJ-3 E4 H1 within-0.01 wording overstates (2 of 15 cells exceed; mean 0.004 is correct); MAJ-4 article class not PoPETs template carry-over; MAJ-5 38 pages exceeds PoPETs target carry-over; MAJ-6 anonymization for double-blind upgraded from minor), 28 minor, 12 suggestions."
    resolution: "Pending. MAJ-1 closes with 1-2 days Zenodo DOI posting. MAJ-2 closes with 30 min Setup-level note or rerun of Le Cam table on E3 codec set. MAJ-3 closes with one-clause wording fix. MAJ-4 + MAJ-5 + MAJ-6 close with 1-2 days editorial (template port + page trim + anonymization). With MAJ-1 closed and identified majors addressed, plausibly ready for PoPETs submission. R7 closure rate this round: 5 R7 majors fully closed (CRIT-1 + MAJ-8 + MAJ-12 + MAJ-17 + MAJ-18), 3 partially closed (MAJ-1 + MAJ-7 + MAJ-10), 11 still open. R8 introduced 0 new critical findings; mismatches identified are precision-of-wording, not data fabrication. Direction-of-prescription audit performed: 15+ propto and 20+ min/max/favor sites verified consistent. Confidence: moderate-high that this paper is ready for PoPETs once sister-paper DOIs land."
  - date: "2026-05-17"
    reviewer: "papermill (Round 7 single-orchestrator; subagent dispatch unavailable)"
    recommendation: "major-revision"
    summary: "1 critical (CRIT-1: t-dependent allocation recommendation in abstract/Corollary 8.x/§10.6 is direction-inverted; formula and empirical numbers correct but interpretation reverses defender-vs-attacker), 19 major (MAJ-1 Theorem 8.1 verbal-def-vs-proof tuple mismatch, MAJ-2 Proposition 8.2 needs bijectivity not just saturation, MAJ-3 Prop 8.2 homogeneous-instances formula, MAJ-4 Huffman saturation encoder gloss, MAJ-5 sister-paper preprints carry-over, MAJ-6 article class carry-over, MAJ-7 §10.6 single-run, MAJ-8 no Bloom baseline carry-over, MAJ-9 14 Pareto configs unenumerated, MAJ-10 §10.3 single-run carry-over, MAJ-11 attacker-tie sample-size, MAJ-12 abstract inverts wording, MAJ-13 §8.3 subsubsection style, MAJ-14 §10.6 paragraph density, MAJ-15 abstract Pareto sentence, MAJ-16 Huffman 1952 missing, MAJ-17 bernoulli-types URL stale, MAJ-18 118.9pt overfull, MAJ-19 36 pages exceeds PoPETs target), 49 minor, 17 suggestions."
    resolution: "Pending. R7 critical (CRIT-1) is a regression in interpretation introduced by the new §8.3 multi-instance content. The formula and empirical numbers from the bernoulli experiment file are correct, but the cipher-maps paper (and the source experiment writeup) reads the defender-vs-attacker direction backwards. Resolution requires v4 thesis revision: either preserve formula and fix interpretation (Huffman wins at every t; randomized-encoding defense becomes headline), or redefine attacker to make a genuine inversion exist (distinguish-which-value attacker). Path A (preserve formula, fix interpretation) takes ~4-6 hours editorial plus a half-day thesis restructure. R7 also closed R6 issues: entropy ratio definition unified, Theorem 6.2 Step 2 separated, throughput consistent, framework framing landed."

related_papers:
  - path: ~/github/trapdoor-computing/papers/boolean-algebra-over-trapdoor-sets
    rel: companion
    label: "Online construction (trapdoor Boolean algebra) instantiated in cipher-maps"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli axioms provide the error model cipher maps inherit"
  - path: ~/github/bernoulli/papers/bernoulli-hash-function
    rel: foundation
    label: "BHF is the optimal cipher map construction for batch strategy"
  - path: ~/github/bernoulli/papers/bernoulli_maps
    rel: foundation
    label: "Bernoulli maps ARE cipher maps at the mathematical level"
  - path: ~/github/trapdoor-computing/papers/maximizing-confidentiality
    rel: sister
    label: "R6 verified: Theorem 4.1 part 3 is the Fannes-Audenaert bound; cite chain correct. Still Manuscript-in-prep; preprint posting pending."
  - path: ~/github/trapdoor-computing/papers/cipher-rekeying
    rel: sister
    label: "R6 verified: Theorem 7.1 is the chain bound at §7 Information-Theoretic Cost; cite chain correct. Still Manuscript-in-prep; preprint posting pending."
  - path: ~/github/bernoulli/src/bernoulli/experiments/14_coincidence_oracle.py
    rel: source
    label: "R7 source experiment for §10.6 multi-instance results. RESULTS_14.md has the same direction-inverted interpretation that cipher-maps inherits. Fix needed in both places."
---

## Notes

2026-06-03 (thesis): Refined to v5 -- abstraction-forward. Re-pointed the thesis at the cipher-map ABSTRACTION (four measurable properties; totality / noise-in -> noise-out as the foundational privacy mechanism) as the unit of analysis, with the acceptance-predicate lever and the three-literature unification reframed as consequences. Confidentiality made self-contained (prop:confidentiality + prop:homophonic, TV < (|X|-1)/N); maxconf demoted to cite-for-depth. Corrected the stale "Shannon-optimal does space + leakage simultaneously" framing to "distinct corners of a frontier". Manuscript propagation (abstract / intro / parent CLAUDE.md) and the C(f) vs C(A->B) notation note are pending discussion.

2026-06-03 (proof, full-paper audit): Verified all 17 proved claims via 3 independent audits (2 logic + 1 numerics) + hand cross-check. Core SOUND: Prop 4.1 homophonic (|X|-1)/N tight, Prop 5.1 Fannes, Thm 6.1 lower bound, composition (M4 confirmed resolved), coincidence oracle (R7 CRIT-1 confirmed resolved), AND-gate, granularity, deniability all correct. Found 1 CRITICAL (the "42x at 17% overhead" headline conflates homophonic multiplicity with length-assignment frontier: at +17% the reduction is only ~2x; 42x needs multiplicity and is length-neutral-to-shorter; in abstract/intro/§6.2/§10), 2 MAJOR (Thm 6.2 "matches lower bound" conflates storage with info-content when eta>0 [recurring M5]; exact "=H(Y)" ignores the one-bit Shannon gap, dyadic-only, contradicts line 1156), and ~12 MINOR (incl. sign slip line 1605 <= should be >=). Full report: .papermill/proofs/proof-verification-2026-06-03.md. Headline items (C1/M1/M2/Prop 8.4) await author decision; safe minors pending.

Paper rebuilt from scratch 2026-03-19 using formalism/cipher-map-formalism.md.
Original preserved as cipher_maps_original.tex.

Thesis refined 2026-03-27: Variant C (contrast-forward). Abstract rewritten.

Round 4 review 2026-04-28 confirmed M3, M4, M5, M6 fixes landed cleanly. Five new majors (mostly editorial), 16 new minors. M1 and M2 remained principal threats to PoPETs survivability.

R5 (2026-04-30) restructure: QIF positioning adopted in §1, §5 reorganized (new §5.1 Confidentiality Measure, Proposition 5.1 Fannes-Audenaert bound, §5.2 Operational Consequences), notation `\cipherS{X}{s}` adopted, new §9.5 "Bounded Composition as a Security Feature", new TikZ figure for acceptance partition. Round 5 review found: R4 MAJ-1, MAJ-3, MAJ-4, MAJ-5 mostly addressed, MAJ-2 not addressed. R5 introduced new issues: 3 critical (CITE-1, CITE-2 wrong theorem numbers; METH-1 §10 promotion absent), 14 major (logic errors in §5.2, definitional mismatch in Proposition 5.1, novelty fragmentation across unpublished sister papers, missing citations).

R5 review history: orchestrator was rate-limited mid-execution; 4 specialists landed (literature-context, citation-verifier, logic-checker, methodology-auditor). Resumed 2026-04-30 with 3 missing specialists (novelty-assessor, prose-auditor, format-validator) and unified synthesis. All 7 specialist reports + literature context + unified review now in `.papermill/reviews/2026-04-30/`.

R6 (2026-05-02) Path A fixes applied earlier in the day:

- CITE-2 corrected: `\cite[Theorem~4.3]{towell2026maxconf}` to `\cite[Theorem~4.1, part~3]{towell2026maxconf}`. Verified against maxconf §4: Theorem 4.1 has 3 parts; part 3 is the Fannes-Audenaert bound.
- CITE-1 reverted: kept `\cite[Thm.~7.1]{towell2026rekeying}`. R5 reviewer had miscounted; rekeying §7 ("Information-Theoretic Cost") contains Theorem 7.1 (chain confidentiality bound). Verified by direct read.
- METH-1 (§10 promotion): landed. New top-level §10 with five subsections (Reference Implementation, Application: Encrypted Search, 20 Newsgroups Validation with Setup/Construction/Single-term/Multi-term/Reproducibility paragraphs, Deniability via Correctness Parameter, Further Empirical Investigations). Old §9.4 Application: Encrypted Search subsection deleted from Discussion.
- LOG-1: §5.2 item 2 rewritten to use δ-equivocal in distribution + Le Cam two-point lemma.
- LOG-2: §5.2 item 3 rewritten to use data-processing inequality on Property 2's TV bound (Pinsker-style language removed).
- LOG-3: §5.1 confidentiality measure paragraph rewritten to define `e = H(Q)/n` matching maxconf normalization. Proposition 5.1 proof sketch applies Fannes-Audenaert with reference Uniform(B^n).
- CITE-4 Kerschbaum 2015 cited in new "Frequency-hiding constructions" paragraph in §2 with mechanism contrast.
- CITE-5 Kamara-Moataz 2019 cited in SSE paragraph as closest SSE-side analogue to totality.

R6 review (2026-05-02) found:

- All 3 R5 critical findings closed.
- 1 new critical (CRIT-1): the §10 promotion exposed a genuine arithmetic discrepancy in the multi-term AND FP claim. Observed 12 FPs is 5x-20x higher than the p_T^k=0.05^3 model prediction (0.6 expected at 5K, 2.3 at 18K). Either correlated terms or noise floor; needs documentation or recomputation.
- 4 new major: MAJ-1 entropy ratio definition mismatch between intro (`H(X|view)/H*(X)`) and §5.1 (`H(Q)/n`); MAJ-2 entropy ratio not in `\begin{definition}` environment despite user's narrative claiming "Definition 5.1"; MAJ-3 Theorem 6.2 Step 2 still conflates search-time cost (`1/α(y)` trials) with storage cost (`log₂(1/α(y))` bits); MAJ-4 construction throughput inconsistent (700 in §6.4 vs 843 at 5K vs 713 at 18K in §10.3).
- 1 new framing major: MAJ-5 (NOV-N2) framework contribution needs explicit positioning in §1.
- 2 carry-over major: MAJ-6 (CITE-6) load-bearing sister-paper preprints still pending; MAJ-7 (LOG-S1) same-secret composition mismatches Definition 7.2 independent-seeds requirement.

R6 review history: subagent dispatch unavailable in this orchestrator session; orchestrator performed all specialist reads directly. 7 specialist reports + literature context + unified review in `.papermill/reviews/2026-05-02/`.

R7 (2026-05-17) verified R6 closures and reviewed new content:

R6 closures confirmed:
- R6 CRIT-1 (3-term AND FP arithmetic): RESOLVED via noise-floor formula at §10.3 lines 2366-2375; observed 12 FPs = 2.4e-3 consistent with k=3 upper bound 6.5e-3 under noise-floor model.
- R6 MAJ-1+MAJ-2 (entropy ratio definition unification): RESOLVED via Definition 5.1 at lines 701-716 with `e = H(Q)/n`; consistent across §1 line 168 and §5.1.
- R6 MAJ-3 (Theorem 6.2 Step 2): RESOLVED via separation of storage cost (per-element seed-table) from search-time cost (parenthetical) at lines 1132-1158.
- R6 MAJ-4 (throughput consistency): RESOLVED; §6.4 line 1283 says "713 documents per second on the full 20 Newsgroups corpus" matching §10.3's "25.6 seconds / 18,266 docs". §10.3 also reports 843 docs/sec at 5K with explicit corpus size.
- R6 MAJ-5 (framework framing in §1): RESOLVED via new paragraph at lines 120-149 "Contribution: framework, not new construction".
- R6 MAJ-7 (master vs operational subkeys): RESOLVED via Remark 4.x "Master secret vs operational sub-derivations" at lines 563-574.
- R6 MAJ-6 (sister-paper preprints): NOT addressed; carry-over as R7 MAJ-5.

R7 critical (CRIT-1): t-dependent allocation recommendation direction inverted. The Round 7 commit 6a0f594 added §8.3 (multi-instance composition leakage), the abstract "inverts the single-instance Shannon recommendation at t >= 2" claim, Corollary 8.x ($t \geq 2$ optimum: uniform allocation), §10.6 paragraph "Multi-instance leakage and the coincidence oracle" with "uniform defends 16x better at large t", and Summary item (iv) verification claim. All five locations encode the same direction-inverted reading. The formula 1 - (1/2) sum_y alpha(y)^t is the attacker's classification accuracy; higher accuracy = attacker more successful = worse for defender. By Jensen, uniform minimizes sum alpha^t, which MAXIMIZES attacker accuracy (worst defense). Skewed Huffman keeps sum larger, MINIMIZES attacker accuracy (best defense). Numerical verification: at |Y|=8, t=5: uniform attacker acc 0.99988, Huffman attacker acc 0.98387; Huffman has 132x higher attacker error rate (better defense). The paper inherits the inversion from the bernoulli experiment writeup RESULTS_14.md which makes the same misreading.

R7 introduced majors: 19 total. 6 logic-side (Theorem 8.1 verbal-vs-proof tuple, Proposition 8.2 saturation-vs-bijectivity, Prop 8.2 homogeneous-instances formula, Huffman saturation encoder gloss, sister-paper preprints carry-over, article class carry-over); 5 methodology-side (§10.6 single-run, no Bloom baseline, unenumerated 14 configs, §10.3 single-run, attacker-tie sample-size); 4 prose-side (abstract inverts wording, §8.3 subsubsection style, §10.6 paragraph density, abstract Pareto sentence); 2 citation-side (Huffman 1952, bernoulli-types URL); 2 format-side (118.9pt overfull, 36-page count).

R7 review history: subagent dispatch unavailable; orchestrator performed all specialist reads directly. 6 specialist reports (logic, novelty, methodology, prose, citation, format) + literature context + unified review in `.papermill/reviews/2026-05-17/`.

## Next Actions

Ordered by impact-per-effort:

1. **R7 critical fix (4-6 hours editorial + half-day v3 thesis revision)**:
   - Fix CRIT-1: revise the v3 thesis (claim field above) and the manuscript to drop the "inversion" framing. Path A (recommended) preserves the formula and fixes the interpretation:
     - Abstract lines 80-83: replace "inverts the single-instance Shannon recommendation at t >= 2" with something like "shows the Shannon-optimal allocation provides both single-instance frequency hiding and high coincidence cover at large t (the dominant value supplies a high-probability decoy lane for filler queries)".
     - Corollary 8.x lines 1846-1858: replace the "$t \geq 2$ optimum: uniform allocation" bullet with "$t \geq 2$ optimum: allocations with larger $\max_y \alpha(y)$ (e.g., Shannon-optimal Huffman) provide more coincidence cover, slowing the attacker's accuracy growth at rate $\max_y \alpha(y)$ rather than $\varepsilon/|Y|$".
     - §10.6 lines 2555-2573 (paragraph "Multi-instance leakage and the coincidence oracle"): rewrite "the uniform allocation defends 16x better" as "the Huffman allocation provides 132x higher attacker error rate, i.e. better defense, in this configuration". Update "Dense dominates at t >= 2" to "Huffman dominates at every t (single-instance TV-min AND multi-instance coincidence cover)".
     - §10.6 Summary item (iv) lines 2640-2643: replace "verified" with the corrected reading.
     - state.md thesis claim and novelty bullet 3: mark v4 pending; restate without "inversion".
     - Also update the source experiment file bernoulli/.../RESULTS_14.md Defense implications section to match.

2. **R7 major editorial fixes (4-8 hours)**:
   - MAJ-1: Rewrite Theorem 8.1 verbal definition (lines 1738-1740) to use tuple-probe notation matching the proof.
   - MAJ-2: Replace "saturates" with "uniform-saturating" (bijectivity) in Proposition 8.2 statement (lines 1918-1926).
   - MAJ-3: Restrict Proposition 8.2 to homogeneous instances or clarify that $A_i(y)$ is codec-level.
   - MAJ-4: Add construction note showing how the Huffman encoder achieves the bijection.
   - MAJ-7: Run 3 replicates for §10.6 headline numbers and report mean ± std.
   - MAJ-8: Add Bloom row to Table tab:le-cam-tight at matched $\varepsilon$.
   - MAJ-12: Rewrite abstract sentence to match corrected CRIT-1 interpretation.
   - MAJ-13: Replace §8.3 subsubsection* with paragraph headings or numbered subsubsections.
   - MAJ-14: Add structure-setting sentence at start of §10.6.
   - MAJ-18: Fix 118.9pt overfull at Definition 8.x by moving math to display style.

3. **Sister-paper preprint posting (1-2 days; closes MAJ-5)**:
   - Post `towell2026maxconf` as arXiv preprint with DOI.
   - Post `towell2026rekeying` as arXiv preprint with DOI.
   - Lower priority: `towell2026algebraic` (now used at §10.3 R7), `bernoulli-types` (split into per-paper citations).

4. **R7 minor backlog (2-3 days)**:
   - CITE-MIN-2: Add Huffman 1952 to bib; cite at first Huffman mention.
   - CITE-MIN-3: Add Cover-Thomas for Kraft inequality background.
   - CITE-MIN-4 to 6: Add Patel-Persiano-Yeo-Yung, Köpf-Smith, Pouliot-Wright (carry-overs).
   - CITE-MIN-7: Add QIF multi-instance cite (Geng-Smith 2025 or equivalent).
   - CITE-MIN-8: Add DOI fields throughout bib.
   - CITE-MIN-9: Add Le Cam page number for two-point lemma.
   - METH-MIN-1 to 7: §10.6 setup paragraph density, codec naming, Padded(y_0) missing, $n=5$ codec ambiguity, key-feature attacker thin, Pareto frontier definition, §10.3 uniform query.
   - PROSE-MIN-1 to 10: bulleted list in §8.3, prose-to-theorem bridge, coincidence-oracle terminology, $\sim$ vs approximately, §9.6 header style, §1 Bernoulli paragraph standalone, abstract sentence length, Bernoulli terminology drift, §10.6 "sampling noise" wording.
   - FMT-MIN-3: Standardize on \Cref throughout.
   - FMT-MIN-5: Wrap §6.4 / §6.6.1 tables in table env.
   - FMT-MIN-7: Anonymize author block for double-blind.
   - FMT-MIN-10: Update title page date.

5. **R7 suggestions (optional polish)**:
   - SUG-1: Add threat-model summary table (logic + format cross-ref).
   - SUG-2: Add reproducibility appendix.
   - SUG-3: After CRIT-1, consider leading with (TV, L) Pareto frontier as headline.
   - METH-SUG-1: §10.7 Reproducibility and Limitations subsection.
   - METH-SUG-2: Move setup tables to appendix.
   - METH-SUG-3: Codec sweep at larger |Y|.
   - PROSE-SUG-2: "How to read this paper" guide paragraph in §1.
   - PROSE-SUG-3: Promote randomized encoding to §8.4.
   - CITE-SUG-1: "Concurrent and prior work in multi-instance composition" subsection.
   - CITE-SUG-3: Split bernoulli-types into specific sub-paper refs.
   - FMT-SUG-1: Add glossary or notation table near §3.
   - FMT-SUG-2: Move Algorithm 1 to appendix.

6. **Pre-submission cleanup (R6/R7 carry-over)**:
   - MAJ-6/FMT-2: Port to PoPETs 2027 template (closes MAJ-19 partially).
   - FMT-MIN-7: Anonymize for double-blind review.
   - Page trim: §9.1 (Bernoulli relationship), §9.4 (Bounded composition), §10.4 (Deniability) candidates for compression.

## R9 Review Summary (2026-06-02)

- Critical: 0
- Major: 2 (LOG-MAJ-1/METH-MAJ-1 NEW Zipf skew s=1 should be s=1.2; MAJ-1 sister-paper preprints carry-over)
- Minor: 9 (METH-MIN-1 NEW E1 m=11004 vs claimed 18266; LOG-MIN-1 kappa undefined; LOG-MIN-3 n-vs-M; LOG-MIN-2 Prop 8.2 saturation; METH-MIN-2/3/4 single-run carry-overs; CITE-MIN-1 Huffman 1952; presentation carry-overs)
- Suggestions: 6
- Build: clean (39 pages, 0 undefined refs, 0 bibtex warnings, 4 overfulls max 14.3pt; R7 critical 118.9pt stays closed)
- Recommendation: minor-revision (conditional on MAJ-1 + LOG-MAJ-1)
- Mode: orchestrator-direct (subagent dispatch unavailable, as R6/R7/R8)
- Reports: .papermill/reviews/2026-06-02/ (review.md + 6 specialist reports + literature-context.md)

### What this round verified (the homophonic arc)

The new Proposition prop:homophonic is the centerpiece and it is CLEAN:
- Exact identity TV(Q, Uniform(im enc)) = (1/2) sum_x |D(x) - K(x)/N| = TV(D, A): confirmed numerically across 6 random (X, D, c) configs.
- Simmons bound TV < |X|/N for K(x)=ceil(c D(x)): confirmed; triangle-inequality proof arithmetic is right (1/(2N) prefactor cancels to R/N < |X|/N).
- Fully self-contained: uses only injectivity + def of Q + def of TV + triangle inequality. No maxconf, no unproven general-n |X|/(2N) result, no c >= 1/min D hypothesis. The removed deferral sentence (commit c9e830b) was the correct call.
- Correctly targets within-image uniformity; the prose remark after the proof cleanly bridges to the full-space delta of Definition 4.2 (the residual gap is the noise region).

K(x) propto D(x) direction: correct at all 5 sites (lines 323, 457, 526, 547, 700). D and K introduced at line 318-320 before formal use; redefined in Definition 4.2.

No regressions from d_TV-inline (Definition 4.2 lines 515-520), removed deferral (no dangling refs), or codec-inventory fix (section 10.6 Setup now enumerates per-sweep codec sets).

R8 MAJ-2 (codec inventory) and MAJ-3 (E4 H1 "within 0.01" -> "within 0.02, 13 of 15 within 0.01") both CLOSED (commit 9b60c2b verified in current text).

### The NEW finding (LOG-MAJ-1 / METH-MAJ-1): Zipf skew mislabel

Lines 1934 (section 8.3) and 2609 (section 10.6) say "Zipf ... skew s = 1".
But:
- Literal Huffman on Zipf(s=1), |Y|=8: p[0]=0.368, lengths [2,2,3,3,4,4,4,4], max alpha=0.25, t=5 acc ~0.999. Does NOT match the paper's max alpha=0.5 / acc 0.984 / 132x.
- Source experiment 14_coincidence_oracle.py line 77 uses 1/(i+1)^1.2 = Zipf s=1.2: p[0]=0.4286, lengths [1,3,3,4,4,4,5,5], max alpha=0.5, sum alpha^5=0.0313, acc=0.9843. MATCHES exactly. E3 results.csv max_q=0.5 for Huffman(M=4,p_f) confirms.

So the numbers are correct and validated; only the stated skew is wrong. Fix: s=1 -> s=1.2 at lines 1934, 2609. One char each. Triple cross-verified (independent Huffman build + source file + E3 CSV).

This is the FOURTH direction/parameter error of the user-flagged family caught over the revision cycle (after K direction, CRIT-1 inversion, K prescription). It evaded R8 because that round checked the ratio against the formula without reconstructing the Huffman code from the stated skew. RECOMMENDATION (LOG-SUG-1, now urgent): add a direction/parameter-summary table pairing each distribution with its resulting max alpha and each prescription with its better-defense direction, so the next such error is visible at edit time.

### Honest verdict for the user

YES, submission-ready once: (a) Zenodo DOIs minted (MAJ-1, user task, 1-2 days), and (b) s=1.2 skew label fixed at 2 sites (LOG-MAJ-1, 5 minutes). Plus the already-planned template port + page trim + anonymization editorial pass (FMT majors, 1-2 days). NO substantive technical work remains: no proof needs fixing, no experiment needs rerunning (artifacts are correct), no claim is unsupported once the s=1.2 and m=11004 labels are corrected. Minor adds (E1 m label, kappa, n-vs-M, Huffman 1952 cite) are 1-2 hours total. Confidence: high.

## R7 Review Summary

- Critical: 1 (CRIT-1: t-dependent allocation direction inverted across abstract, Corollary 8.x, §10.6 paragraph, Summary; formula and empirical numbers correct, interpretation reversed)
- Major: 19 (6 logic, 5 methodology, 4 prose, 2 citation, 2 format)
- Minor: 49 (7 logic, 7 methodology, 10 prose, 12 citation, 10 format, plus 3 cross-listed)
- Suggestions: 17 (3 logic, 3 methodology, 3 prose, 3 citation, 3 format, plus 2 cross-listed)
- Build: clean (5 overfull hboxes, one severe 118.9pt at Definition 8.x lines 1905-1910)
- Page count: 36 (up from R6's 28 due to §8.3 + §10.6 additions; need 8-10 page trim for PoPETs target 18-20 in their template)
- Recommendation: major-revision

R7 progress vs R6: closed all 7 R6 majors (entropy ratio definition unified, Theorem 6.2 Step 2 separated, throughput consistent, framework framing landed, master/operational subkey clarified, RecSplit cite at §6.4; sister-paper preprints still pending). R6 CRIT-1 (3-term AND FP arithmetic) closed via noise-floor formula. R7's §8.3 + §10.6 additions are technically motivated but exposed a critical direction-of-inequality error in the central new contribution.

Path to minor-revision: 4-6 hours CRIT-1 editorial + half-day v4 thesis revision + 4-8 hours R7 major editorial fixes + sister-paper preprint posting. Total ~1-2 weeks if preprints can be posted in parallel.

Path to ready: above plus 3-replicate variance characterization for §10.6 and §10.3 + Bloom baseline cell + PoPETs template port + anonymization + Huffman 1952 cite + bernoulli-types URL fix.

Honest PoPETs survivability: NOT survivable without CRIT-1 fix; a careful reviewer will catch the direction error in the abstract. WITH CRIT-1 fix (Path A) and sister-paper preprints posted, plausibly minor-revision territory in 1-2 reviewing cycles. The framework contribution and three-literature unification remain strong; the (TV, L) Pareto frontier with 42x TV reduction is a sharp non-controversial finding; the Le Cam tightness empirical validation is clean. The technical content is solid; the issue is one of interpretation in the new multi-instance content.

## Source-experiment cross-reference

The R7 critical finding (CRIT-1) is rooted in a misreading shared between
the cipher-maps paper and its source experiment in the bernoulli repo.
Both should be updated:

- `bernoulli/src/bernoulli/experiments/14_coincidence_oracle.py` lines
  34-37 docstring claim "uniform codecs (Dense) are better defenses
  against multi-instance attacks". This is the same inversion.
- `bernoulli/src/bernoulli/experiments/RESULTS_14.md` lines 99-117
  "Defense implications" section repeats the inverted reading
  ("Dense defends best at large t", "At t=1 prefer Huffman, at large
  t prefer Dense"). Should be corrected to match the formula.

The formula is correct in both files; the empirical numbers are
correct in both files; only the defender-vs-attacker direction reading
is reversed in both files. Fixing one without the other will leave a
visible inconsistency.
