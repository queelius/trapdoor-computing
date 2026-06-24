# Novelty Assessor Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Contribution inventory after R7 CRIT-1 fix

The v3 thesis "inversion" framing was removed in the R7 manuscript edit
(landed on disk by 2026-05-17, verified clean in this review). What
remains is a five-contribution package that the abstract now states
consistently:

1. **Framework contribution (NOV-1)**: cipher map abstraction as the
   unit of analysis for parameterized-leakage outsourced computation;
   four measurable properties (totality, delta, eta, composability)
   plus the acceptance-predicate apparatus. Well-positioned at §1
   "Contribution: framework, not new construction" paragraph (lines
   120 to 149).

2. **(TV, L) Pareto frontier with Shannon duality refinement (NOV-2)**:
   integer-codeword constraints split the L-optimal corner (Huffman)
   from the TV-optimal corner. Headline empirical result: 42x TV
   reduction at 17% length overhead on heavy-tailed p_y (§10.6 lines
   2528 to 2563). This is the strongest novel empirical finding.

3. **Multi-instance composition theorem (NOV-3)**: closed-form
   coincidence-oracle accuracy 1 - (1/2) sum_y alpha(y)^t for t
   shared-f cipher maps under independent seeds. The randomized-encoding
   defense (multiplicity K(x) > 1) is the deployment-side
   countermeasure. The R7 CRIT-1 fix removed the "inversion" claim;
   what remains is the formula plus the structural geometry (Huffman
   wins at every t) plus the randomized-encoding defense.

4. **Empirical Le Cam tightness across attacker classes (NOV-4)**:
   Bayes, logistic, 1-NN classifiers tie within 0.014 sampling noise
   across the codec sweep. Mean Bayes gap to Le Cam UB is -0.0004
   (statistically zero). Clean confirmation that the Le Cam upper
   bound is realized by Bayes-optimal attackers in practice.

5. **Three-literature unification (NOV-5)**: approximate data structures
   (Bloom 1970, FKS 1984, BDZ 2009), frequency-hiding encryption
   (Kerschbaum 2015, Boldyreva 2009), encrypted search (Curtmola 2006,
   Cash 2013, Kamara-Moataz 2019) under one formalism with measurable
   parameters and explicit sister-paper deferrals.

## Novelty-side findings

### CLOSED (R7 NOV-1, NOV-3 partial): CRIT-1 inversion fix landed
- The R7 CRIT-1 fix transformed NOV-3 from a counterintuitive
  inversion claim (potentially false as written) into a
  conventionally-stated multi-instance theorem (true, modest, useful).
  The novelty shifts from "we invert the codec choice at t >= 2" to
  "we give the closed-form coincidence-oracle accuracy and identify
  randomized encoding as the deployment-side defense."
- This is a downgrade in headline drama but an upgrade in correctness.
  The right reading of the literature is that NOV-3 now contributes
  the closed-form formula plus the threat-model decomposition
  (pattern-coincidence vs decode-coincidence, with the randomized-
  encoding defense distinguishing the two), rather than a
  counterintuitive recommendation.

### NOV-N1 (NEW, MINOR): Headline narrative needs explicit re-anchoring
- **Location**: Abstract (lines 51 to 92), §1 contribution paragraph
  (lines 120 to 149)
- **Issue**: After the R7 CRIT-1 fix, the headline novelty narrative
  is split across NOV-2 (Pareto frontier with 42x) and NOV-4 (Le Cam
  tightness). The abstract does emphasize the 42x finding ("gap
  reaching 42x in TV at 17% length overhead") but the Le Cam tightness
  is mentioned only via "validate the Le Cam attacker bound
  empirically." Neither contribution is currently identified as THE
  headline.
- **Suggestion**: Promote the 42x finding to the abstract's opening
  positioning, e.g., "Acceptance predicates expose a Pareto frontier
  between expected codeword length and TV-leakage with a sharp
  trade-off: on heavy-tailed value distributions, spending 17% in
  expected codeword length buys 42x lower TV-leakage." This refines
  rather than replaces the framework framing.
- Severity MINOR.

### NOV-N2 (NEW, MINOR): Randomized encoding novelty understated
- **Location**: §8.3 "Randomized encoding as a defense" (lines 1887 to
  2007), abstract (line 86 to 89)
- **Issue**: The randomized-encoding defense distinguishes pattern-
  coincidence (private-codec threat, where randomized encoding helps)
  from decode-coincidence (public-codec threat, where randomized
  encoding does not help). This threat-model distinction is novel
  in the cipher map setting and the analysis (Proposition 8.2) is
  clean. The abstract mentions randomized encoding only obliquely
  ("the appropriate defense is randomized encoding rather than codec
  retuning"); the threat-model distinction is invisible at the abstract
  level.
- **Suggestion**: Either add a sentence in the abstract about the
  threat-model distinction, or promote it to a paragraph in §1
  alongside the framework contribution.
- Severity MINOR.

### NOV-N3 (NEW, MINOR): Framework unification claim grows stronger
when the CRIT-1 fix preserves the formal apparatus
- **Location**: §10.6 Summary (lines 2640 to 2663)
- **Issue**: The Summary item (iv) now reads correctly. The
  unification claim (NOV-5: cipher maps subsume Bloom filters,
  frequency-hiding encryption, and encrypted search) is strengthened
  because the multi-instance theorem (with the correct interpretation)
  applies uniformly across all three instances. Bloom filters with
  K(x) = 1 and uniform Dense partition are exactly the worst-case
  multi-instance defense; Huffman-allocated frequency-hiding encryption
  is the best-case multi-instance defense; encrypted search inherits
  whichever codec choice is made.
- **Suggestion**: Add a sentence in §10.6 Summary or in §1 that the
  multi-instance theorem provides a uniform leakage account across
  the three subsumed literatures.
- Severity MINOR (it is a positive observation rather than an issue).

### NOV-N4 (NEW, MINOR): Sister-paper deferrals create novelty fragility
- **Location**: Citations of `towell2026maxconf`, `towell2026rekeying`,
  `towell2026algebraic`, `bernoulli-types` throughout
- **Issue**: Four "Manuscript in preparation" citations remain. Two
  are load-bearing: `towell2026maxconf` is cited for the
  Fannes-Audenaert bound (Proposition 5.1), and `towell2026rekeying`
  is cited for the chain bound (§9.5). PoPETs reviewers may discount
  novelty contributions that hinge on unpublished sister work, even
  when the formal result is self-contained in the current paper.
- **Suggestion**: Post arXiv preprints before submission. The
  cipher-maps paper's novelty claims are self-contained as stated,
  but the citation infrastructure should be unblocked.
- Severity MINOR (formal contribution is self-contained; this is a
  presentation issue) but PRACTICAL HIGH for submission readiness.

## Summary of novelty findings

- 0 critical
- 0 major new (NOV-N4 is a high-priority but presentation-only issue)
- 4 minor new (NOV-N1 headline narrative, NOV-N2 randomized encoding,
  NOV-N3 unification strengthening, NOV-N4 sister-paper preprints)

**Novelty-side recommendation**: The post-CRIT-1 contribution
inventory is solid and novel. The framework synthesis, (TV, L) Pareto
frontier with 42x finding, and Le Cam tightness empirical confirmation
form a coherent narrative. The multi-instance theorem is sound after
the interpretation fix. The R7 critical regression has been cleanly
absorbed without losing the contribution structure.
