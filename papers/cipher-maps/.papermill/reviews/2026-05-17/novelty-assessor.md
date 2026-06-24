# Novelty Assessor Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Assess the v3 thesis novelty claims against the v3 narrative and the
manuscript content. Five claims to verify:

1. The cipher map abstraction with four measurable properties as unit
   of analysis (framework contribution).
2. Acceptance predicate as universal knob, with the (TV, L) Pareto
   frontier refining Shannon-frequency duality.
3. Multi-instance composition theorem (coincidence-oracle accuracy
   formula).
4. Empirical Le Cam tightness across codec sweep.
5. Unification of three previously-disconnected literatures.

## CLAIM-BY-CLAIM ASSESSMENT

### NOV-1: Framework contribution (v3 thesis claim #1)

**Status**: Well-supported by §3 (Cipher Map Abstraction), §4 (Four
Properties), and §5 (Trusted/Untrusted Machine Model). The framework
is precisely formalized: a cipher map is a tuple $(\fhat, \enc, \dec,
s)$ characterized by $(\eta, \varepsilon, \delta, \mu)$ via four
properties. The §1 paragraph "Contribution: framework, not new
construction" at lines 120-149 explicitly frames the contribution as a
framework rather than a new construction.

**Differentiation from priors**: The framework is genuinely new as a
unified abstraction. Individual elements (totality, multiplicity,
correctness, composition) exist in priors (Bloom for AMQ, Simmons for
homophonic substitution, garbled circuits for total lookup tables),
but their packaging into four measurable properties parameterized by
$(\eta, \varepsilon, \delta, \mu)$ is original.

**Concern**: The "framework" framing is now slightly undercut by the
multi-instance composition theorem (v3 thesis claim #3), which IS a
new construction-level result, not a framework-level synthesis. Mixing
"we propose a framework, not a new construction" with "we prove a
new composition theorem" creates a small framing tension. A one-line
acknowledgment at the framework paragraph that "the framework also
admits new technical results (Theorem 8.1, the empirical Le Cam
tightness study)" would tighten the narrative.

### NOV-2: (TV, L) Pareto frontier (v3 thesis claim #2)

**Status**: Supported by §10.6 "(TV, L) Pareto frontier and the
Shannon duality refinement" at lines 2518-2554. The empirical study
covers 14 configurations and demonstrates Huffman is always on the
Pareto frontier (14/14) but is TV-optimal only when $p_y$ is
near-dyadic (7/14). The 42× TV reduction at 17% length overhead for
heavy-tailed $p_y$ is concrete and compelling.

**Differentiation from priors**: The observation that integer-codeword
constraints separate the Shannon-optimal and TV-optimal corners is, to
my knowledge, novel as an explicit framing. The Kraft inequality and
prefix-free coding tradeoff is classical (Huffman 1952, Cover-Thomas),
but the application to frequency-hiding via acceptance partition
allocation is new.

**Concern**: Huffman 1952 is not cited (per literature-context).
Without it, the "Huffman is suboptimal for TV" claim risks looking
naive to coding-theory readers. Adding the citation strengthens the
positioning.

**Concern**: The thesis claim "refining the Shannon-frequency duality"
sets up a high standard. The actual refinement is "integer codeword
constraints make L-optimal and TV-optimal distinct, with TV gap up to
42× on heavy-tailed $p_y$." This is a sharp empirical finding but is
not yet a structural theorem with closed-form bounds. The reader may
expect a tightness result of the form "TV-optimal allocation
achieves $L \leq H(Y) + g(\text{skew})$" or similar. The current
treatment is empirical-only.

### NOV-3: Multi-instance composition theorem (v3 thesis claim #3)

**Status**: STRUCTURALLY WEAKENED by CRIT-1 in the logic-checker
report. The formula (Theorem 8.1) is correct, but the central
"inversion" claim built on it is the opposite of what the formula
implies (uniform allocation has HIGHER attacker accuracy, not lower).

**Differentiation from priors**: Multi-instance attacks on cipher
constructions have a long history (key reuse, IV reuse, password
salting). The specific coincidence-oracle attacker as a closed-form
lower bound on Bayes-optimal accuracy is original. The formula
$\text{acc}(t) = 1 - \tfrac{1}{2} \sum_y \alpha(y)^t$ is a clean
result.

**Concern**: After CRIT-1 is addressed, the "inversion" framing is
gone and what remains is "Huffman wins at every $t$ because it
provides both single-instance frequency hiding and high
coincidence-cover at large $t$." That is still a publishable finding,
but it is less striking than the inversion claim, and it reorganizes
the thesis significantly. The novelty bullet 3 in `state.md` should be
revised to match.

**Concern**: The randomized-encoding defense (Proposition 8.2) IS
genuinely novel and interesting: it shows multiplicity $K(x) > 1$
defends against the pattern-coincidence attacker (private-codec
threat) but not the decode-coincidence attacker (public-codec threat).
This threat-model distinction is original and clean. After fixing
CRIT-1, this could absorb some of the thesis weight that the
"inversion" claim currently carries.

### NOV-4: Empirical Le Cam tightness (v3 thesis claim #4)

**Status**: Well-supported by §10.6 "Le Cam tightness across
attackers" table and prose at lines 2485-2516. Three attacker classes
(Bayes, logistic, 1-NN) tie to within 0.014 sampling noise, and the
mean Bayes gap to the Le Cam bound is statistically zero (-0.0004).

**Differentiation from priors**: The Le Cam bound is well-known (Le
Cam 1986). The empirical validation that the bound is realized in
practice by Bayes-optimal classifiers across a codec sweep is novel
as an integration: it links the QIF theory (TV bounds the attacker's
advantage) to the ML practice (Bayes classifier saturates the bound).
The novelty here is empirical rather than theoretical, but it is a
clean and useful demonstration.

**Concern**: The novelty claim "empirically realized by the
Bayes-optimal attacker (not just an information-theoretic upper
bound)" is fine but slightly oversells. The Le Cam bound IS a tight
bound information-theoretically, achieved by the likelihood-ratio
test. What the experiment shows is that practical attacker
implementations (Bayes, logistic, 1-NN) all achieve this bound on
realistic codecs, which is reassuring but not surprising. A sharper
novelty claim: "the gap between Le Cam upper bound and best-realized
attacker accuracy is statistically zero across all tested codecs,
suggesting deployment-time evaluation can use the Le Cam bound as a
tight predictor of attacker capability rather than a loose upper
bound."

### NOV-5: Three-literature unification (v3 thesis claim #5)

**Status**: Well-supported by §2 (Related Work) and the framework's
ability to subsume each literature's flagship constructions. Bloom
filters are cipher maps with $K(x) = 1$ (Remark on set membership).
Kerschbaum's FH-OPE attacks the same threat by a different mechanism
(Frequency-hiding paragraph). SSE constructions provide different
guarantees (Searchable symmetric encryption paragraph).

**Differentiation from priors**: The cross-literature unification is
the central novelty contribution and is genuinely new. No prior work
(to my knowledge) treats Bloom filters, frequency-hiding encryption,
and encrypted search as instances of a single framework with
measurable parameters.

**Concern**: The "sister-paper deferrals" sentence ("formal
entropy-ratio proof to towell2026maxconf, bounded-Turing chain bound
to towell2026rekeying") in the thesis statement creates dependence on
unpublished work. After MAJ-5 (sister-paper preprints) is closed,
this concern lifts.

## OVERALL NOVELTY ASSESSMENT

The framework contribution (NOV-1) and the three-literature unification
(NOV-5) are the strongest novelty pillars and are uncontested.

The empirical Le Cam tightness (NOV-4) is solid empirical novelty.

The (TV, L) Pareto frontier (NOV-2) is a sharp empirical finding that
could be strengthened by a closed-form bound but stands as-is.

The multi-instance composition theorem (NOV-3) is the most ambitious
new claim for Round 7, but it is structurally compromised by CRIT-1.
After the inversion claim is dropped or restated, what remains is
still novel (the formula, the randomized-encoding defense, the
threat-model distinction), but the framing needs rework.

**Net**: The framework is novel enough for PoPETs. The headline
multi-instance claim needs to be reworked before the paper survives
review. The v3 thesis can be salvaged with the (TV, L) Pareto
frontier and the randomized-encoding defense doing more of the
narrative work, and the "inversion" framing dropped.

## RECOMMENDATIONS TO STRENGTHEN NOVELTY

1. After fixing CRIT-1, restructure the v3 thesis to lead with
   (a) the framework contribution, (b) the (TV, L) Pareto frontier
   with concrete 42× TV reduction empirically, (c) the
   coincidence-oracle formula AND its corrected interpretation (Huffman
   is uniformly best), (d) the randomized-encoding defense and the
   threat-model distinction (private codec vs public codec), and
   (e) the empirical Le Cam tightness. Drop the "inversion" framing.

2. Cite Huffman 1952 in the (TV, L) Pareto frontier discussion. Add
   Cover-Thomas for the Kraft inequality background.

3. Cite at least one QIF multi-instance paper (Geng-Smith 2025 or
   equivalent) to anchor NOV-3 in the literature.

4. Post sister-paper preprints to close NOV-N concerns about
   load-bearing citations to unpublished work.

5. Sharpen the NOV-4 claim to "tight predictor of attacker capability"
   rather than "realized by the Bayes-optimal attacker (not just
   information-theoretic upper bound)".

## Summary

- Critical: 0 (the inversion issue is logic, attributed to logic-checker
  as CRIT-1; the novelty implication is captured above as NOV-3 concern)
- Major: 1 (NOV-3 structurally compromised pending CRIT-1 fix)
- Minor: 3 (NOV-1 framing tension, NOV-2 missing Huffman cite, NOV-4
  oversold claim)
- Suggestions: 5
