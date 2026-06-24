# Multi-Agent Review Report

**Date**: 2026-04-30 (Round 5)
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Manuscript**: cipher_maps.tex (1841 lines, 26 pages, 31 bib entries)
**Target venue**: PoPETs 2027
**Recommendation**: **major-revision**

## Summary

**Overall Assessment**: The R5 restructure (QIF positioning, entropy
ratio adoption via Proposition 5.1, Operational Consequences
enumeration, new TikZ figure) is a substantive step toward closing the
M1 security-definition gap that has been open since R3. However, the
M1 collapse strategy is **incomplete in three ways**: (1) the proof
sketch of Proposition 5.1 cites the wrong theorem number in the sister
paper and elides a definitional mismatch in $H^*$; (2) the Operational
Consequences enumeration contains two prose-level logic errors that
overstate the bound; (3) the security argument is materially outsourced
to an unpublished sister manuscript. The METH-1 finding that the §10
promotion did not land in the manuscript is a separate concern: the R5
prompt described a Phase 5 §10 evaluation section that does not exist
in the file under review. M2 (no experimental evaluation) therefore
also remains open.

**Strengths**:
1. The acceptance-predicate framework is a genuinely novel
   contribution: the unification of Shannon-optimal coding and
   frequency hiding in one design choice (novelty-assessor NOV-1, NOV-2)
2. The new TikZ figure (acceptance partition) renders cleanly and
   communicates the central allocation idea well (format-validator)
3. The QIF positioning in §1 is correct and well-anchored to the
   Smith/Alvim/Dodis-Smith tradition (literature-context, novelty-assessor)
4. Build is clean: 0 LaTeX errors, 0 undefined references, 1 minor
   overfull hbox (format-validator)
5. The four-property characterization remains a clean conceptual
   contribution and the composition theorem (Theorem 7.1) is sound
   (logic-checker)

**Weaknesses**:
1. **Critical**: Two cross-paper theorem number citations are wrong
   (CITE-1, CITE-2): `[Thm.~7.1]{towell2026rekeying}` should be 6.1,
   `[Theorem~4.3]{towell2026maxconf}` should be 4.1. CITE-2 in
   particular is load-bearing for the M1 collapse (citation-verifier)
2. **Critical**: METH-1: the §10 Implementation and Evaluation
   promotion described in the R5 prompt did not land in the
   manuscript. The experimental content remains as duplicated
   paragraphs in §9.4 (methodology-auditor)
3. **Major**: Proposition 5.1's proof sketch elides a definitional
   mismatch: the cited maxconf Theorem (4.1, not 4.3) bounds $H(Q)/n$;
   cipher-maps Proposition 5.1 claims a bound on $H(X|\fhat,\tau)/H^*(X)$.
   These are not the same quantity (logic-checker LOG-3)
4. **Major**: §5.2 Operational Consequences items 2 and 3 contain
   prose-level logic errors: item 2 overstates Property 1 ("identical"
   should be "$\delta$-close"); item 3 invokes Pinsker in the wrong
   direction (logic-checker LOG-1, LOG-2; prose-auditor PROSE-2)
5. **Major**: The security framework is outsourced to three unpublished
   manuscripts. A reviewer cannot verify the load-bearing claims
   without those papers being public (literature-context,
   novelty-assessor NOV-1, citation-verifier CITE-6)
6. **Major**: Three bib entries are uncited despite being directly
   relevant: Kerschbaum 2015 (closest predecessor for frequency-
   hiding), Kamara-Moataz 2019 (closest analogue to totality),
   Esposito 2020 RecSplit (named in §6.4 but uncited)
   (citation-verifier CITE-3, CITE-4, CITE-5)

**Finding Counts**: Critical: 3 | Major: 14 | Minor: 26 | Suggestions: 19

## Critical Issues

### Critical 1: CITE-2 : Wrong theorem number in load-bearing M1 citation

- **Location**: cipher_maps.tex line 661, inside Proposition 5.1 proof sketch
- **Quoted text**: "Full proof and discussion of tightness in `\cite[Theorem~4.3]{towell2026maxconf}`."
- **Verified against manuscript**: yes, line 661 reads as quoted
- **Verified against sister paper**: confirmed against
  `/home/spinoza/github/trapdoor-computing/papers/maximizing-confidentiality/main.tex`,
  which has `\label{thm:entropy-decomposition}` at line 441 in §4 (the
  only theorem in §4). Section-relative numbering: this is **Theorem 4.1**.
  The Fannes bound is part 3 of Theorem 4.1 (line 473-490).
- **Problem**: This is the load-bearing citation for the M1 collapse
  strategy. A reviewer who follows the citation will not find Theorem 4.3
  in the maxconf paper. The citation chain breaks.
- **Suggestion**: Change `[Theorem~4.3]` to `[Theorem~4.1, part 3]`
  or `[Theorem~4.1]`. Verify by building both PDFs.
- **Source**: citation-verifier CITE-2
- **Cross-verified**: yes, confirmed by reading sister paper directly

### Critical 2: CITE-1 : Wrong theorem number for chain bound citation

- **Location**: cipher_maps.tex line 1749
- **Quoted text**: "values~`\cite[Thm.~7.1]{towell2026rekeying}`"
- **Verified against manuscript**: yes, line 1749 reads as quoted
- **Verified against sister paper**: confirmed against
  `/home/spinoza/github/trapdoor-computing/papers/cipher-rekeying/paper/main.tex`,
  which has `\label{thm:chain-bound}` at line 843 in §6
  ("Information-Theoretic Cost"). Section-relative numbering: this is
  **Theorem 6.1**. §7 in the rekeying paper is "Applications," not the
  chain bound location.
- **Problem**: This citation supports §9.5's "Bounded Composition as a
  Security Feature" subsection. A reviewer checking the bound will not
  find Theorem 7.1 in the rekeying paper.
- **Suggestion**: Change `[Thm.~7.1]` to `[Thm.~6.1]`.
- **Source**: citation-verifier CITE-1
- **Cross-verified**: yes, confirmed by reading sister paper directly

### Critical 3: METH-1 : §10 promotion not in manuscript despite R5 plan

- **Location**: cipher_maps.tex §9.4 (lines 1677-1704)
- **Quoted text**: §9.4 contains two duplicated paragraphs about the
  20 Newsgroups experiments (single-trial, no baselines, no error
  bars, no hardware spec, no query distribution)
- **Verified against manuscript**: yes, the manuscript ends at §9
  (Discussion); there is no §10. The latex source confirms only 9
  numbered sections (intro, related, abstraction, properties, trust
  model, batch, composition, granularity, discussion).
- **Problem**: The R5 prompt described a Phase 5 §10 promotion as the
  fix for MAJ-2 (no experimental evaluation). This work did not land
  in the file under review. The user has confirmed that a parallel
  Claude Code session was editing the manuscript concurrently and
  reverted or never applied the §10 promotion. M2 therefore remains open.
- **Suggestion**: Two paths:
  - **Option A** (minimum): Keep §9.4 as preliminary-only. Remove
    duplication, add reproducibility metadata (URL, commit hash, hardware,
    seed, query distribution, trial count). Acknowledge in §1 that full
    evaluation is in companion algebraic-cipher-types work or future work.
  - **Option B** (preferred): Promote §9.4 to a §10 evaluation section
    with proper structure (Setup / Construction / Single-term /
    Multi-term / Reproducibility) and run additional experiments to
    fill in baselines, error bars, and parameter sweeps. The 2-4 week
    budget in the state file's next-actions applies.
- **Source**: methodology-auditor METH-1
- **Cross-verified**: yes, confirmed directly against §9.4 (lines 1677-1704)
  and verified the manuscript has only 9 sections via grep

## Major Issues

### Major 1: LOG-3 : $H^*$ definitional mismatch between cipher-maps and cited maxconf

- **Location**: cipher_maps.tex lines 642-662 (Proposition 5.1 + proof
  sketch); definition of $H^*(X)$ at line 631-633
- **Quoted text** (definition): "$H^*(X)$ is the maximum entropy of $X$
  under any constraints publicly visible to $U$ (the 'baseline ignorance'
  against which leakage is measured)."
- **Verified against manuscript**: yes
- **Verified against sister paper**: maxconf §4 normalizes by $H^* = n$
  (cipher value space size, lines 449, 466 of maxconf). cipher-maps
  uses $H^*(X)$, the latent input space.
- **Problem**: maxconf's Theorem 4.1 part 3 establishes
  $H(Q) \geq n(1 - \delta) - h_2(\delta)$, a bound on the cipher-value
  marginal entropy normalized by $n$. cipher-maps Proposition 5.1
  claims a bound on $H(X|\fhat,\tau)/H^*(X)$ where $H^*(X)$ is the
  latent input entropy bound. These are different quantities. The proof
  sketch's "composing the two yields [eq:fannes-bridge]" elides the
  bridge.
- **Suggestion**: Reconcile the two definitions. Either (a) cipher-maps
  Proposition 5.1 should normalize by $H^* = n$ (matching maxconf),
  or (b) the proof sketch should spell out the data-processing step
  from "cipher value marginal $\delta$-close to uniform" to "latent
  input entropy bounded below given the trace." Currently the citation
  chain is broken at this transition.
- **Source**: logic-checker LOG-3
- **Cross-verified**: yes, by reading maxconf §4 directly

### Major 2: LOG-1 : §5.2 Operational Consequence #2 overstates Property 1

- **Location**: cipher_maps.tex lines 691-694 (§5.2, item 2)
- **Quoted text**: "Real and filler queries are statistically equivocal
  (Property~1, totality). Both produce $n$-bit output through the same
  total function; the joint distribution of the trace under any
  $T$-chosen real-vs-filler partition is identical."
- **Verified against manuscript**: yes
- **Problem**: Property 1 (Definition 4.1, totality) only states that
  $\fhat$ is total and that for $c$ uniformly drawn from
  $\B^n \setminus \im(\enc)$, $\fhat(c)$ is uniform. Real queries hit
  $\im(\enc)$ which is $\delta$-fraction of the cipher value space.
  Real and filler distributions are not identical: filler queries hit
  the rejection region with probability $1 - \varepsilon$, real queries
  hit $\bigcup_y A(y)$. The actual bound is $\TV \leq \delta$
  (consistent with Table 2 row 1). The §5.2 prose contradicts the
  table.
- **Suggestion**: Replace lines 691-694 with: "Real and filler queries
  are $\delta$-equivocal in distribution (Properties 1 and 2 together):
  both are observed as $n$-bit cipher values, and the cipher value
  distribution is $\delta$-close to uniform by Property 2. Consequently,
  no statistical test distinguishes real from filler with advantage
  exceeding $\delta$."
- **Source**: logic-checker LOG-1, prose-auditor PROSE-2
- **Cross-verified**: yes, two specialists agree on the issue

### Major 3: LOG-2 : §5.2 Operational Consequence #3 invokes Pinsker in wrong direction

- **Location**: cipher_maps.tex lines 695-699 (§5.2, item 3)
- **Quoted text**: "Domain identification is bounded by $\delta$
  (Property~2). $U$'s posterior on which inputs are 'real domain
  elements' versus 'noise' is at most $\delta$ in total variation from
  the prior, by Pinsker-style arguments combined with
  Proposition~\ref{prop:confidentiality}."
- **Verified against manuscript**: yes
- **Problem**: Pinsker's inequality is $\TV(P, Q) \leq \sqrt{D_{KL}(P \| Q)/2}$,
  bounding TV in terms of KL. The text wants to bound posterior TV in
  terms of $\delta$ (itself a TV bound). The chain of reasoning is
  unclear. The sister paper maxconf §4 (lines 487-490) explicitly
  notes that Pinsker goes the wrong direction and Fannes-Audenaert is
  the correct tool. So invoking "Pinsker-style arguments" here
  contradicts the sister paper's own caveat.
- **Suggestion**: Replace "by Pinsker-style arguments" with "by
  data-processing applied to Property 2 (the cipher value distribution
  is $\delta$-close to uniform, so posteriors of any function of the
  cipher trace are $\delta$-close to the priors of the same function
  under uniform)." Or more conservatively: drop "Pinsker-style" and
  write "by Property 2 combined with Proposition 5.1."
- **Source**: logic-checker LOG-2, prose-auditor PROSE-2
- **Cross-verified**: yes, two specialists agree

### Major 4: NOV-1 : Novelty story has fragmented across three unpublished manuscripts

- **Location**: Abstract (lines 55-81), §1 (lines 122-142), §5.1
  (lines 622-640)
- **Problem**: Three load-bearing components are deferred to companion
  papers: (1) entropy ratio framework to towell2026maxconf; (2) chain
  bound to towell2026rekeying; (3) algebraic cipher type system to
  towell2026algebraic. What remains uniquely in cipher-maps is the
  four-property characterization, the acceptance-predicate framework,
  the space-optimality theorems, and the composition theorem. This is
  a credible novel contribution by itself, but the abstract and §1
  sell the QIF positioning and entropy ratio as the headline before
  deferring them.
- **Suggestion**: Pick one of:
  - **Option A** (commit to outsourcing): Add explicit "Scope"
    paragraph in §1 making clear the security framework lives in
    companion work; recast headline novelty as
    "acceptance-predicate framework + space-optimality + composition."
  - **Option B** (commit to in-paper): Inline Proposition 5.1's full
    proof and the bridge to maxconf's Theorem 4.1 (with corrected
    number per Critical 1), so a self-contained argument exists in
    cipher-maps. ~1 page of additional text.
- **Source**: novelty-assessor NOV-1
- **Cross-verified**: yes, prose-auditor PROSE-1 corroborates from
  the prose-discontinuity angle

### Major 5: PROSE-1 : Intro QIF positioning collides with §6-9 tuple-form prose

- **Location**: §1 lines 122-142 vs §6 lines 1158-1264 vs §9 (Discussion)
- **Problem**: The §1 voice positions cipher maps in the QIF tradition
  with parameterized leakage. The §6+ voice mechanically describes a
  tuple. The transition between voices is abrupt and §6+ never
  re-engages with the QIF framing. The §6.5 "Property status"
  enumeration ("Totality: yes. Representation uniformity: achievable...")
  feels disconnected from §5.1's entropy ratio.
- **Suggestion**: Add 1-2 sentence "QIF-bridge" connectives at end of
  §6.5, start of §7, end of §9.4. Each is a short addition but
  restores the narrative arc the §1 sets up.
- **Source**: prose-auditor PROSE-1
- **Cross-verified**: complementary to NOV-1 (the novelty-assessor's
  framing concern is a different facet of the same underlying issue)

### Major 6: NOV-2, CITE-4 : Kerschbaum 2015 frequency-hiding OPE in bib but uncited

- **Location**: §2 (Related Work, no Frequency-hiding paragraph
  exists); references.bib (kerschbaum2015frequency, lines 238-244)
- **Problem**: Kerschbaum 2015 is the closest published predecessor
  for "frequency-hiding via output distribution shaping," which is the
  R5 paper's central novel mechanism. Omission is conspicuous. A
  PoPETs reviewer will spot it. The state file flagged this as a "gap"
  two rounds ago; it persists.
- **Suggestion**: Add to §2 the suggested paragraph (NOV-2 / CITE-4):
  "Kerschbaum's frequency-hiding OPE injects random ranks on duplicate
  inserts; cipher maps achieve the same goal structurally by shaping
  the acceptance partition $A(y)$ so $\alpha(y) \propto p_y$, which
  simultaneously minimizes per-element space and equalizes the cipher
  value frequency profile (Theorem 6.2). The two mechanisms are
  complementary."
- **Source**: novelty-assessor NOV-2, citation-verifier CITE-4,
  literature-context section A
- **Cross-verified**: three sources converge on this finding

### Major 7: NOV-3, CITE-5 : Kamara-Moataz 2019 volume-hiding STE in bib but uncited

- **Location**: §2 (Related Work, no volume-hiding line); references.bib
  (kamara2019computationally, lines 254-261)
- **Problem**: Volume-hiding STE is the closest analogue to cipher
  maps' totality property; both eliminate the "in-domain vs
  out-of-domain" signal. Kamara-Moataz uses simulation-based
  machinery; cipher maps use totality + Property 2. The comparison is
  natural and missing. PoPETs reviewers in the SSE community will
  flag it.
- **Suggestion**: Add the suggested paragraph (NOV-3 / CITE-5):
  "The volume-hiding line~[kamara2019computationally] is closer to
  cipher maps' approach: rather than analyzing leakage, it engineers
  indistinguishability via simulation-based constructions. Cipher maps
  achieve a related guarantee structurally (totality + Property 2) at
  lower per-query cost."
- **Source**: novelty-assessor NOV-3, citation-verifier CITE-5,
  literature-context section C
- **Cross-verified**: three sources converge

### Major 8: CITE-3 : RecSplit cited by name but no \cite{} invocation

- **Location**: cipher_maps.tex line 1154
- **Quoted text**: "A reference implementation using a RecSplit-family
  PHF achieves 700 documents per second on the 20~Newsgroups corpus"
- **Problem**: `esposito2020recsplit` is in references.bib (lines
  246-252) but never invoked. Active citation error.
- **Suggestion**: Insert `\cite{esposito2020recsplit}` after
  "RecSplit-family PHF" at line 1154.
- **Source**: citation-verifier CITE-3
- **Cross-verified**: yes, by direct grep

### Major 9: METH-2 : Construction-time numbers lack confidence intervals

- **Location**: §9.4 lines 1683-1685, 1692; §6.4 line 1154
- **Problem**: All construction-time measurements are single-trial.
  "843 docs/sec," "25.6 seconds," "700 documents per second" are
  reported with no variance. The construction algorithm uses random
  shuffle, so trial-to-trial variance is real and unreported.
- **Suggestion**: Run construction 30 times, report mean and 95% CI.
  If CI is tight, one number is fine but "averaged over 30 trials"
  attribution is needed.
- **Source**: methodology-auditor METH-2

### Major 10: METH-3 : Precision metric depends on query distribution, not stated

- **Location**: §9.4 lines 1684-1685
- **Problem**: "single-term queries achieve perfect recall (1.0) with
  precision 0.39." The precision number depends entirely on which
  queries were sampled. Without query distribution stated, the number
  is uninterpretable.
- **Suggestion**: Add: "queries sampled uniformly from the corpus
  vocabulary, restricted to terms appearing in $\geq 5$ documents,
  $N = 100$ queries per setting." (or whatever the actual protocol was)
- **Source**: methodology-auditor METH-3

### Major 11: METH-4 : "cipher-maps Python library" not characterized

- **Location**: §9.4 line 1678
- **Problem**: Implementation cited informally with no URL, commit
  hash, version, or DOI. The `phobic` library at line 1683 has the
  same issue. State file's R4 next-actions (`nm16`) and METH-S2 of R5
  flagged this; persists.
- **Suggestion**: Add footnote: "Available at
  `\url{https://github.com/queelius/cipher-maps}`, commit `XXXXXX`
  (April 2026)." Same for `phobic`.
- **Source**: methodology-auditor METH-4

### Major 12: FMT-1 : Document class is `article`, not PoPETs

- **Location**: line 1
- **Problem**: State file targets PoPETs 2027 but document class is
  plain `article`. Template port may surface formatting issues.
- **Suggestion**: Port to PoPETs template before further revision
  rounds. ~1 day of work.
- **Source**: format-validator FMT-1

### Major 13: PROSE-2 : §5.2 Operational Consequences mixes registers

- **Location**: §5.2 lines 685-704
- **Problem**: Four items use four different formal frameworks
  (computational, statistical, probabilistic, decision-theoretic).
  Registers don't cohere. Items 2 and 3 also contain logic errors
  (LOG-1, LOG-2 above).
- **Suggestion**: Rewrite as a single coherent register
  (decision-theoretic). Each item: "By Proposition 5.1, for adversary
  goal $G$, advantage is bounded by $X$." Demote item 1 (hash
  inversion) to a Remark. Fix items 2 and 3 per LOG-1 and LOG-2.
- **Source**: prose-auditor PROSE-2
- **Cross-verified**: by logic-checker LOG-1 and LOG-2

### Major 14: CITE-6 : Three sister papers are "Manuscript in preparation"

- **Location**: references.bib (bernoulli-types, towell2026maxconf,
  towell2026rekeying, towell2026algebraic)
- **Problem**: Four bib entries are `@misc{...}` with `note={Manuscript
  in preparation}`. None has a DOI, arXiv ID, or permanent URL. The
  load-bearing M1 collapse (Proposition 5.1) cites
  towell2026maxconf, which a reviewer cannot verify.
- **Suggestion**: Mint Zenodo DOIs at minimum. arXiv preprints
  preferred. Update bib entries with permanent identifiers. For
  PoPETs survivability, post both maxconf and rekeying as arXiv
  preprints **before** submitting cipher-maps.
- **Source**: citation-verifier CITE-6, literature-context section
  "Unpublished sister-paper risk"

## Minor Issues

### Logic / proofs (logic-checker)

1. **LOG-4** (Minor): Theorem 6.1 lower-bound proof drops the Stirling
   $n \log_2 e$ term ($\approx 1.44n$ bits) without justification.
   "Approximate to leading order" handwave. The bound is fine as
   loose, but the proof should say so.
2. **LOG-5** (Minor): Proposition 5.1 missing condition $\delta \leq 1/2$
   (Fannes-Audenaert requires it). Sister paper states the condition;
   cipher-maps omits it.
3. **LOG-6** (Minor): Theorem 6.2 Step 2 still elides the independence
   assumption (under ROM, fraction of seeds satisfying constraint is
   $\alpha(y_i)$). Better than R4 but explicit independence note would
   close it.
4. **LOG-7** (Minor): Composition theorem (Theorem 7.1) error-cancellation
   note is correct but creates ambiguity: is the bound tight or
   pessimistic? Both, depending on conditions; should be made explicit.

### Methodology (methodology-auditor)

5. **METH-5** (Minor): The 5%/90%/5% partition asserted but unjustified
   in §9.4. Reader expects motivation.
6. **METH-6** (Minor): No comparison to standard Bloom filter at
   equivalent FPR. Remark 6.8 invites this comparison; §9.4 doesn't
   deliver.
7. **METH-7** (Minor): Construction-time table at lines 1086-1098 is
   theoretical (Poisson binomial calculation), not empirical, but the
   distinction isn't labeled in caption.
8. **METH-8** (Minor): "phobic" library named at line 1683 but never
   described or cited. R4 nm16 flagged this; persists.
9. **METH-9** (Minor): "OR and NOT lose recall (0.97 and 0.88)" stated
   without showing calculation. Should match Theorem 7.1 prediction
   for 5/90/5 partition; would strengthen connection between theory
   and experiments.

### Citations (citation-verifier)

10. **CITE-7** (Minor): No DOI fields anywhere in the bibliography.
    Modern crypto venues expect DOIs.
11. **CITE-8** (Minor): Shannon 1948 BSTJ citation cites only volume
    27 part 1 (pages 379-423); standard form cites both parts.
12. **CITE-S3** (Minor): `bernoulli-types` is titled "Bernoulli Sets
    and Maps" but the in-text references treat it as covering the
    trapdoor Boolean algebra. Either add a separate bib entry for the
    Boolean algebra paper or clarify scope.

### Prose (prose-auditor)

13. **PROSE-3** (Minor): Abstract sentence flow has clause pile-up.
    The 50-word sentence with three parentheticals exceeds working
    memory.
14. **PROSE-4** (Minor): "Manuscript in preparation" ~12 in-text
    references reads as constant deferral. Consider a clustered
    "Roadmap" footnote in §1 or §3.
15. **PROSE-5** (Minor): "Notational convention" paragraph is dense;
    leads with categorical detail before the simple substitution rule.
16. **PROSE-6** (Minor): Two "Honest limitations" passages (§5.2 and
    §8.2) are redundant.
17. **PROSE-7** (Minor): §9.4 experimental paragraphs are duplicated
    (R4 issue persists).
18. **PROSE-8** (Minor): "We" used inconsistently in single-author paper.

### Novelty (novelty-assessor)

19. **NOV-4** (Minor): Bayesian deniability proposition (§9.4) is
    textbook randomized response; framing as Proposition suggests
    novelty where none exists. Demote to Remark or cite Warner 1965.
20. **NOV-5** (Minor): Shannon-vs-min-entropy QIF distinction not
    addressed. Sister paper acknowledges it; cipher-maps doesn't.
21. **NOV-6** (Minor): Acceptance-predicate unification is novel but
    not contrasted with what it replaces in prior work.
22. **NOV-7** (Minor): "Bounded composition is a feature" framing
    lacks citations to sub-Turing models tradition.

### Format (format-validator)

23. **FMT-2** (Minor): 3 dead-weight bib entries. Either cite per
    CITE-3/4/5 or remove.
24. **FMT-3** (Minor): One overfull hbox at lines 1542-1549 (4.4pt).
25. **FMT-4** (Minor): No author affiliation in `\author{}`.
26. **FMT-5** (Minor): No anonymization for double-blind review.
27. **FMT-6** (Minor): `plainnat` style with `[numbers]` mode is
    stylistically inconsistent.

## Suggestions

1. **CITE-S1**: Add Köpf-Smith 2010 to broaden QIF citation base.
2. **CITE-S2**: Cite Warner 1965 (randomized response) for the
   deniability proposition.
3. **NOV-S1**: Commit to a "release plan" for sister-paper preprints
   (arXiv) before cipher-maps submission.
4. **NOV-S2**: Reframe §9.7 "What This Framework Is Not" with positive
   comparisons (Smith QIF, etc.) instead of negations.
5. **PROSE-S1**: Add "Reading guide" early in §1 to help reviewers
   navigate.
6. **PROSE-S2**: Replace `\textbf{yes/achievable/yes/yes}` enumerations
   in §6.5 with prose.
7. **PROSE-S3**: Split or categorize the 6 Open Questions in §9.6.
8. **PROSE-S4**: One canonical introduction of "trapdoor Boolean
   algebra" instead of three piecemeal mentions.
9. **PROSE-S5**: Split intro's last 250-word paragraph at the
   positioning sentence.
10. **METH-S1**: Promote the §6.4 "RecSplit 700 docs/sec vs seed
    search 10 docs/sec" 70x speedup to a small construction-time
    table.
11. **METH-S2**: Add a "validation experiment" measuring each property
    empirically (using cipher-maps Python library).
12. **FMT-S1**: Increase vertical separation in TikZ figure labels.
13. **FMT-S2**: Add colon to table captions for crypto-venue convention.
14. **FMT-S3**: Rename `alg:singular-hash` label to `alg:batch-cipher-map`.
15. **FMT-S4**: Either remove `cleveref` (used once) or migrate to it
    consistently.
16. **LOG-S1**: Clarify Definition 7.1 inconsistency with same-secret
    composition (re-randomization requires independent seeds, but
    composition is for same-$s$ in §4.4).
17. **LOG-S2**: Add a small numerical example to the deniability
    proposition (e.g., $\eta = 0.05, \pi = 0.1 \Rightarrow$ posterior
    $\approx 0.68$).
18. **PRESUB-1**: PoPETs page-count optimization (~3-5 page trim).
19. **PRESUB-2**: Anonymization pass before double-blind submission.

## Detailed Notes by Domain

### Logic and Proofs

The R5 restructure introduces three new formal items in §5: Definition
5.1 (entropy ratio), Proposition 5.1 (confidentiality bound), and the
Operational Consequences enumeration. Two prior theorems (6.1 lower
bound, 6.2 space-optimal) were edited per R4 MAJ-1.

The proofs are mostly sound. Theorem 6.1 (lower bound), Theorem 6.2
(space optimality), Theorem 7.1 (composition correctness), Corollary
7.2 (chain), Propositions 6.4, 6.5, 6.7, 7.1, 9.4 all check out at the
level of the proof sketches given.

The principal logic concerns are concentrated in §5.1-5.2: Proposition
5.1 has a definitional gap with the cited maxconf theorem (LOG-3), the
§5.2 enumeration items 2 and 3 have prose-level logic errors (LOG-1,
LOG-2). Since §5 is the load-bearing R5 contribution to closing M1,
these are major concerns.

A separate concern: the Stirling step in Theorem 6.1 drops a $1.44n$
term (LOG-4); fine for an asymptotic lower bound but should be flagged.

### Novelty and Contribution

The genuinely novel contributions of cipher-maps R5:
1. Acceptance-predicate framework as the unifying construction
   primitive
2. Shannon-frequency duality (Shannon-optimal allocation IS frequency
   hiding)
3. Four-property characterization (totality, $\delta$-uniformity,
   $\eta$-correctness, composability) as a clean abstraction
4. Composition theorem as Bernoulli error accumulation in a
   trapdoor-aware setting
5. Bounded-composition-as-feature framing (with rekeying chain bound
   citation)

What R5 added: QIF positioning, entropy ratio bridge via
Fannes-Audenaert, Operational Consequences enumeration. These are
correct positioning but most of the content lives in companion papers.

The Kerschbaum 2015 (frequency-hiding OPE) and Kamara-Moataz 2019
(volume-hiding STE) citations are missing despite being in the bib;
both are the closest published comparators for the R5 novel claims.

### Methodology

The single largest open issue is that the R5 prompt's planned §10
promotion did not land. The experimental content remains as duplicated
paragraphs in §9.4. Reproducibility is thin: no hardware spec, no
software version pins, no random seed, no trial count, no CIs, no
query distribution, no baselines. Reproducibility checklist (PoPETs
format) is satisfied for 1 of 10 items (corpus identified).

The decision the author must make: defer evaluation explicitly to
companion work (Option A in METH-1) or do the §10 promotion
substantively (Option B, 2-4 weeks).

### Writing and Presentation

The R5 prose is largely fine but the QIF-positioning seams are
visible. The intro and §5 are written in the new QIF-aware register;
§6 and onwards retain the original tuple-form prose. The transitions
are abrupt and the QIF framing is not sustained through §6-9.

The §5.2 Operational Consequences enumeration has both register
issues (PROSE-2) and logic issues (LOG-1, LOG-2). Rewriting it as a
single coherent register would fix both.

The §9.4 paragraph duplication (PROSE-7) and the "Manuscript in
preparation" repetition (PROSE-4) are the two most visible cumulative
prose issues.

### Citations and References

Build is clean: 0 undefined references, 0 BibTeX errors, 28 of 31 bib
entries cited.

Two critical theorem-number mistakes (CITE-1, CITE-2) and three
uncited but bib-present entries (CITE-3, CITE-4, CITE-5) are the
priority fixes. CITE-2 in particular is load-bearing for the M1
strategy.

The "Manuscript in preparation" cluster (4 entries) is the
unpublished-sister-paper risk; arXiv preprints should be posted before
PoPETs submission.

### Formatting and Production

Build is clean (1 minor overfull hbox at 4.4pt). The TikZ figure
renders correctly. Page count is 26, will need a ~3-5 page trim for
PoPETs format. Pre-submission tasks (template port, anonymization,
DOIs) remain open from the R4 next-actions list.

## Literature Context Summary

Cipher maps now sit across three communities (SSE/PPE,
QIF, approximate data structures) and a fourth (QIF) that R5 adopts
explicitly. The literature support is correct but uneven:

- **Already-cited correctly**: Smith 2009, Alvim 2012, Dodis-Smith 2005
  (QIF foundations); Bloom 1970, Belazzougui 2009, Fredman-Komlos-Szemeredi
  1984 (approximate data structures); Curtmola 2006, Cash 2013, Cash 2015,
  Naveed 2015, Islam 2012 (SSE); Bellare-Rogaway 1993 (ROM); Yao 1982,
  Gentry 2009, Goldreich-Ostrovsky 1996 (secure computation); Juels-Ristenpart
  2014 (honey encryption).
- **In bib but uncited (closes-by-citation)**: Kerschbaum 2015,
  Kamara-Moataz 2019, Esposito 2020 RecSplit. All three are directly
  relevant to R5 claims.
- **Not in bib but worth considering**: Köpf-Smith 2010 (min-entropy
  leakage tradition), Patel-Persiano-Yeo-Yung 2019 (volume-hiding
  STE direct competitor), McIver-Morgan-Meinicke-Smith-Geldenhuys
  2014 (channel ordering). Lower priority but would strengthen QIF
  positioning.

The principal literature risk: QIF positioning is correct but thin
(three pointers to a literature, not a program). For PoPETs, this is
acceptable but lean. A Kopf-Smith citation and a Shannon-vs-min-entropy
acknowledgment would strengthen it.

## Review Metadata

- **Agents used**: literature-scout-broad, literature-scout-targeted,
  logic-checker, methodology-auditor, novelty-assessor, prose-auditor,
  citation-verifier, format-validator (7 specialists + literature
  scouts; 3 specialists generated this round, 4 from prior partial run)
- **Cross-verifications performed**:
  - LOG-1, LOG-2 (logic) cross-verified by prose-auditor PROSE-2
  - LOG-3 (logic) cross-verified by reading sister paper directly
  - CITE-1, CITE-2 cross-verified by reading sister papers directly
  - METH-1 (§10 promotion missing) cross-verified by user confirmation
    in prompt + direct manuscript inspection
  - NOV-2/CITE-4 (Kerschbaum) cross-verified by 3 sources
  - NOV-3/CITE-5 (Kamara-Moataz) cross-verified by 3 sources
- **Disagreements noted**: None substantive. The four prior specialists
  and three current specialists converge on the same major issues.
- **Hallucination check**: All quoted manuscript text was verified
  against the manuscript file directly. All cross-paper theorem
  citations were verified against the sister-paper sources.

## Recommendation Detail: major-revision

The R5 round made substantive progress on M1 (security definition gap)
through the QIF restructure and Proposition 5.1, but the M1 collapse
is incomplete:

1. The load-bearing citation [Theorem 4.3]{maxconf} is wrong (should
   be 4.1). Critical fix.
2. The proof sketch elides a definitional mismatch in $H^*$. Major
   fix.
3. The §5.2 enumeration contains prose-level logic errors that
   contradict the bound itself. Major fix.
4. The security framework is materially outsourced to an unpublished
   manuscript. Major risk.

M2 (no experimental evaluation) remains entirely open: the §10
promotion did not land in the manuscript.

These are not small fixes. The author has a clear path forward:
- Critical/Major fixes 1-3 are 1-2 days of editorial work
- Critical fix 4 (METH-1) requires a strategic decision (Option A
  defer or Option B do)
- Sister-paper preprints (CITE-6) should be posted before PoPETs
  submission

Once those are addressed, the paper would be in **minor-revision**
territory: the four-property framework, acceptance-predicate
unification, space-optimality, and composition theorem are all sound
and constitute a credible PoPETs contribution.

What would close M1 if Option A (defer) is chosen:
- Fix CITE-2 (theorem number)
- Add a Scope paragraph in §1 acknowledging the security framework
  lives in companion work
- Post maxconf as arXiv preprint with permanent DOI before submission
- Fix LOG-1 and LOG-2 in §5.2 prose

What would close M1 if Option B (in-paper proof) is chosen:
- Inline Proposition 5.1's full proof (~1 page)
- Resolve the $H^*$ definitional mismatch (LOG-3)
- Fix LOG-1 and LOG-2 in §5.2 prose
- Then maxconf citation becomes optional rather than load-bearing

Either path is feasible. The user should pick one.
