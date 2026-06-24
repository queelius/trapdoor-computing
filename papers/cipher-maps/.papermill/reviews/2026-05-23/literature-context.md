# Literature Context (Round 8, single-orchestrator synthesis)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Status**: Consolidated from R5/R6/R7 scouting. Subagent dispatch
unavailable in this orchestrator session (consistent with R5 to R7).

## Carry-over context

The R7 literature context (`.papermill/reviews/2026-05-17/
literature-context.md`) remains the authoritative consolidated scout
report. No new direct competitors to the cipher-maps abstraction were
identified across rounds. Three subsumption claims are well-grounded:
approximate data structures (Bloom 1970, FKS 1984, BDZ 2009, RecSplit
2020), frequency-hiding/property-preserving encryption (Kerschbaum
2015, Kamara-Moataz 2019, Boldyreva 2009, Bellare-Boldyreva-O'Neill
2007), and encrypted search (Curtmola 2006, Cash 2013, Song 2000).
Leakage-abuse literature (Islam 2012, Naveed 2015, Cash-Grubbs 2015)
is properly cited; honey encryption (Juels-Ristenpart 2014) is
properly cited; QIF foundations (Smith 2009, Alvim 2012, Dodis 2005)
are properly cited.

## R7 carry-over gaps (still missing as of 2026-05-23)

These were flagged in R6 and R7 and remain absent from the bibliography:

1. **Huffman 1952** (`huffman1952method`): strong recommend. Paper
   centers Huffman codes in the acceptance-predicate apparatus and in
   the (TV, L) Pareto frontier finding. Carrier-grade reference.
2. **Patel-Persiano-Yeo-Yung 2019** (volume-hiding STE, CCS 2019):
   strong recommend. Closest information-theoretic volume-hiding
   formal cousin to the cipher map noise-floor approach.
3. **Köpf-Smith 2010** (min-entropy leakage): strong recommend.
   Foundational measure-choice paper; the cipher maps paper now
   explicitly chooses Shannon over min-entropy at §5.1 lines 718-728
   and should cite Köpf-Smith for the contrast.
4. **Cover-Thomas 2006** (*Elements of Information Theory*): medium.
   Textbook reference for Kraft inequality and integer-codeword
   constraints in §10.6.
5. **Pouliot-Wright 2016** (Kraken co-occurrence attack): low.
   Adjacent leakage-abuse reference for §8.2.
6. **Geng-Smith 2025** (or equivalent QIF multi-instance work): medium.
   §8.3 introduces a multi-instance composition theorem; QIF
   multi-instance literature should be cited.
7. **Alvim et al. 2020** (*Science of Quantitative Information Flow*
   textbook): medium. Standard QIF reference.

## R8 new observations

The Round 7 critical fix (CRIT-1 inversion correction) is fully landed
in §10.6, the Corollary, and the §10.6 Summary item (iv). The abstract
and Corollary 8.x both now read the defender-vs-attacker direction
correctly (Huffman dominates at every t). The fix preserved the
formula and changed only the interpretation, exactly as Path A
recommended. This is a clean Round 8 win.

The downstream consequence: the v3 thesis bullet 3 ("inversion at
t >= 2") is no longer present in the paper, so the headline narrative
shifts to (a) the (TV, L) Pareto frontier with 42x reduction, (b) the
empirical Le Cam tightness, and (c) the framework synthesis. These
three are now the headline contributions.

No new direct competitors surfaced. The framework remains a synthesis
across three previously-disconnected literatures.

## Implications for Round 8 review

- The CRIT-1 fix is landed cleanly; no logic-side regression.
- The remaining gaps are production/polish rather than substance.
- Sister-paper preprint posting (towell2026maxconf, towell2026rekeying)
  remains the single largest pre-submission blocker after CRIT-1.
- Page count (36) and template port (article -> PoPETs) remain blockers.
- The framework, (TV, L) Pareto frontier, and Le Cam tightness are
  the strong pillars; the multi-instance theorem is solid after the
  CRIT-1 correction but no longer makes a counterintuitive claim.
