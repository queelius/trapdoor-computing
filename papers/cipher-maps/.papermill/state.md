---
title: "Cipher Maps: Total Functions as Trapdoor Approximations"
stage: revision
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "A cipher map is fully determined by a single design choice: the acceptance predicate. Shannon-optimal allocation of the acceptance predicate simultaneously minimizes space (achieving -log2(eps) + H(Y) bits per element), maximizes output indistinguishability (noise and real outputs share the same frequency profile), and enables predictable error composition."
  novelty: "The unification of space optimality and frequency hiding as the same optimization (Shannon-optimal acceptance allocation), and the collapse of the entire batch construction to one parameterized algorithm."
  refined: "v2 (acceptance-predicate-forward). Contrast-forward opening retained but the claim now centers on the acceptance predicate framework and the Shannon duality. Abstract rewritten 2026-03-28. R5 (2026-04-30): QIF positioning adopted via Proposition 5.1; the M1 collapse strategy now defers the formal entropy-ratio framework to companion work (towell2026maxconf). R6 (2026-05-02): Path A applied. CITE-1/CITE-2 verified, §10 promotion landed, §5.1/§5.2 LOG fixes landed."

prior_art:
  last_survey: "2026-05-02"
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
  gaps:
    - "Patel-Persiano-Yeo-Yung 2019 volume-hiding STE (NOT in bib; R6 strong recommend)"
    - "Alvim et al 2020 Science of QIF textbook (NOT in bib; R6 recommend)"
    - "Kopf-Smith 2010 min-entropy leakage (NOT in bib; R6 strong recommend - foundational measure choice)"
    - "Pouliot-Wright 2016 Kraken co-occurrence attack (NOT in bib; R6 recommend for §8.2)"
    - "Bellare-Ristenpart-Rogaway-Stegers 2009 FPE (NOT in bib; R6 consider)"
    - "Warner 1965 randomized response for deniability proposition (NOT in bib; carry-over)"

experiments:
  - name: "20 Newsgroups encrypted search"
    location: "§10.3 lines 1853-1915"
    status: "promoted to §10 in R6; structurally complete but arithmetic inconsistencies discovered (R6 CRIT-1)"
    note: "R6 §10 promotion landed (5 subsections: Reference Implementation, Application, 20 Newsgroups, Deniability, Future Investigations). However, R6 review found CRIT-1: 3-term AND FP count (12) is 5x-20x higher than the model prediction p_T^k for independent terms (0.6-2.3 expected). Either correlated terms within corpus or noise floor in cipher Boolean implementation. Also MAJ-4: throughput numbers (700 in §6.4 vs 843 at 5K vs 713 at 18K in §10.3) inconsistent. Single-run, no replicates, no Bloom filter baseline (METH-2 carry-over)."

venue:
  target: "PoPETs 2027"
  candidates:
    - "PETS (Privacy Enhancing Technologies Symposium)"
    - "IEEE Transactions on Information Theory"
    - "STACS/ISAAC (theory of computation)"

review_history:
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
    resolution: "Pending. R6 closed all 3 R5 critical findings. R6 introduced 1 critical and 4 major from §10 promotion exposure (CRIT-1 arithmetic, MAJ-2 missing definition env, MAJ-4 throughput inconsistency) and §5 refactor residuals (MAJ-1 entropy ratio mismatch, MAJ-3 Theorem 6.2 carry-over). Path to minor-revision: 4-8 hours focused editorial work to close MAJ-1+MAJ-2 (single Definition env + intro update), MAJ-3 (Theorem 6.2 Step 2 separation of search vs storage), MAJ-4 (consistent throughput reporting), MAJ-5 (1-paragraph framework framing in §1), plus CRIT-1 resolution (depends on what experiment actually measured)."

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
---

## Notes

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

## Next Actions

Ordered by impact-per-effort:

1. **R6 critical fix (1-4 hours)**:
   - Fix CRIT-1: resolve the 3-term AND FP arithmetic. Either:
     (a) Document term correlation in the test query selection (likely cause; reword "approximately p_T^k for independent terms; observed 12 vs predicted 0.6-2.3 indicates correlated terms in test queries").
     (b) Document a noise floor in the cipher Boolean AND implementation if one exists.
     (c) Re-run the 3-term experiment with explicitly random independent triples and report the actual result.
     The fix depends on understanding what the experiment actually measured.

2. **R6 major editorial fixes (4-8 hours)**:
   - Fix MAJ-1 + MAJ-2 together: pick `e = H(Q)/n` everywhere (matches §5.1 and maxconf); update intro line 129-130 from `H(X|view)/H*(X)` to `H(Q)/n`; wrap §5.1 line 644-660 in `\begin{definition}[Entropy ratio]\label{def:entropy-ratio}`; update Proposition 5.1 and §5.2 items 2-4 to reference `Definition~\ref{def:entropy-ratio}`.
   - Fix MAJ-3: rewrite Theorem 6.2 Step 2 to separate search-time cost (`1/α(y)` trials) from seed-table storage cost (`log₂(1/α(y))` bits per element). Lead with storage; mention search time as a parenthetical.
   - Fix MAJ-4: report consistent throughput across §6.4 (rounded full-corpus number) and §10.3 (per-cell numbers with explicit corpus size). Add one sentence on per-document scaling: "throughput drops from 843 docs/sec at 5K to 713 at 18K, reflecting growing PHF construction cost per document."
   - Fix MAJ-5: add 1-paragraph "framework contribution" framing to §1 (e.g., "This paper does not propose a new construction; it identifies a framework that unifies existing approximate-membership and frequency-hiding constructions under measurable parameters (η, ε, δ). Bloom filters become cipher maps with K(x)=1, prefix-free coding gives the entropy cipher map, Shannon-optimal partition shaping unifies space optimality with frequency hiding.").
   - Fix MAJ-7 (LOG-S1): clarify in Definition 4.4 or §7.2 that "same secret" means "same master secret with domain-separated subkeys"; relax Definition 7.2 (i) to subkey independence.

3. **Sister-paper preprint posting (1-2 days; closes MAJ-6 = CITE-6)**:
   - Post `towell2026maxconf` as arXiv preprint with permanent DOI.
   - Post `towell2026rekeying` as arXiv preprint with permanent DOI.
   - Post `towell2026algebraic` as arXiv preprint with permanent DOI (lower priority; currently UNUSED in cipher-maps).
   - Update bib entries with arXiv IDs / DOIs (closes CITE-6 + CITE-N1).

4. **R6 minor backlog (2-3 days)**:
   - LOG-1a: Le Cam normalization (advantage at most δ vs δ/2).
   - LOG-N6 (R5 LOG-4): note Stirling 1.44n drop in Theorem 6.1 proof.
   - LOG-N7 (R5 LOG-5): add δ ≤ 1/2 condition to Proposition 5.1.
   - LOG-N8 (R5 LOG-6): explicit independence note in Theorem 6.2 Step 2.
   - METH-N3 / R5 METH-3: note uniform query distribution is the strawman; acknowledge or report at least one non-uniform alternative (Zipf or empirical log).
   - METH-N4: add Bloom filter strawman comparison cell at matched FPR (1-2 hours).
   - METH-N7: expand hardware/software spec (CPU model, RAM, library versions, random seed).
   - NOV-1 residual: add explicit "Scope" subsection at end of §1 listing what cipher-maps contributes vs what is deferred.
   - NOV-4 (CITE-S2): cite Warner 1965 randomized response for Proposition 10.4.1.
   - NOV-5: add Shannon vs min-entropy QIF rationale in §5.1.
   - PROSE-N1: add 1-sentence transitions between §10.2/§10.3, §10.3/§10.4, §10.4/§10.5.
   - PROSE-N3: shorten §5.2 item 4 to a forward-pointer to maxconf for the latent-vs-cipher normalization.
   - CITE-N1: cite or remove `towell2026algebraic`.
   - CITE-3 sub: add `\cite{esposito2020recsplit}` at §6.4 line 1192 first mention.
   - CITE-7 (R4 m11): add DOI fields throughout bib.
   - CITE-S3: split bernoulli-types cite key into specific paper references.
   - FMT-N1: fix 104pt overfull at line 1875-1880 (long URL line in §10.3 Setup itemize).
   - R4 m3: K(x) → κ(x) rename, or remove from backlog.
   - R4 m9: hash notation unification, or remove from backlog.

5. **R6 suggestions (optional polish)**:
   - NOV-N1: sharpen abstract novelty claim with one sentence.
   - NOV-N4: connect §10.3 OR/NOT recall to §7.4 gate analysis with quantitative prediction.
   - PROSE-N4: promote §9.5 framing to a sentence in §1.
   - PROSE-N6: soften "achieving the information-theoretic lower bound" abstract phrasing.
   - PROSE-N8: anchor "sub-Turing" with a one-line operational gloss.
   - FMT-N2: standardize on `\Cref` throughout.
   - FMT-N4, FMT-N5: wrap embedded tables in §6.4, §6.6.1 in `\begin{table}` environments.
   - METH-N6: add a proper LaTeX table for §10.3 query results.
   - METH-N8: lead §10.3 Construction paragraph with query latency, not throughput.

6. **Pre-submission cleanup**:
   - FMT-1: port to PoPETs 2027 template (1-2 hours; mechanical work, brings page count down).
   - FMT-5: anonymize for double-blind review (30 minutes; remove author block, replace library URLs with placeholders).
   - PoPETs page-count optimization (~3-5 page trim; partly handled by template port).
   - Address remaining R4 minor backlog (m1 demonstrate→illustrate; m3 K(x)→κ(x); etc.).

## R6 Review Summary

- Critical: 1 (CRIT-1: multi-term AND FP arithmetic discrepancy)
- Major: 7 (MAJ-1 entropy ratio defn mismatch, MAJ-2 missing Definition env, MAJ-3 Thm 6.2 Step 2 loose, MAJ-4 throughput inconsistency, MAJ-5 NOV-N2 framing, MAJ-6 CITE-6 preprints pending, MAJ-7 LOG-S1 carry-over)
- Minor: ~22
- Suggestions: ~10
- Build: clean (4 overfull hboxes, one significant 104pt at line 1875-1880)
- Page count: 28 (need 8-10 page trim for PoPETs target 18-20)
- Recommendation: major-revision

R6 progress vs R5: closed all 3 R5 critical findings. The §10 promotion exposed the empirical numbers to closer scrutiny; one arithmetic discrepancy emerged (CRIT-1). The §5 refactor closed the LOG prose issues but left two definitional residuals (MAJ-1 mismatched definitions across §1/§5; MAJ-2 missing Definition environment).

Path to minor-revision: 4-8 hours focused editorial work on MAJ-1+MAJ-2 (single Definition env + intro fix), MAJ-3 (Step 2 separation), MAJ-4 (consistent throughput), MAJ-5 (framework framing paragraph in §1), MAJ-7 (Definition 7.2 subkey clarification), plus resolving CRIT-1 (depends on what experiment actually measured). With sister-paper preprints + Bloom baseline + anonymization + venue port, the paper is plausibly PoPETs-submittable.

Path to ready: items above plus 3-replicate variance characterization and at least one head-to-head baseline comparison.

Honest PoPETs survivability: technical content is solid. Production gaps and the four major editorial items are addressable in 1-2 weeks if sister-paper preprints can be posted in parallel, 3-4 weeks otherwise. The R6 §10 promotion was the right move strategically; it surfaced empirical issues that needed surfacing. Once CRIT-1 is resolved and the four major editorial items land, R7 should drop to minor-revision.
