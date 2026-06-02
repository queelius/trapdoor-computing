# Novelty Assessor Report, Round 8 (2026-05-27)

This round audits the framework-contribution framing, the
sister-paper deferral risk (MAJ-6 carry-over), and the differentiation
claims against prior art.

## Novelty inventory (per state.md and confirmed against manuscript)

1. **Framework**: cipher map abstraction with four measurable
   properties (totality, representation uniformity, correctness,
   composability) as unit of analysis for parameterized-leakage
   outsourced computation. Manuscript anchor: section 1
   "Contribution: framework, not new construction" (lines 123 to 152).
2. **Acceptance predicate as universal knob**: Pareto frontier
   between expected codeword length L and TV-leakage; Shannon-optimal
   (Huffman) and TV-optimal allocations distinct under integer
   constraints. Manuscript anchor: section 6.2 (lines 944 to 1073)
   and section 10.6 (lines 2599 to 2634).
3. **Multi-instance composition theorem**: closed-form
   coincidence-oracle accuracy = 1 - (1/2) sum_y alpha(y)^t for t
   shared-f instances under independent seeds; concentrated Huffman
   partitions optimal at every t; randomized encoding K(x) > 1 as
   deployment-side defense. Manuscript anchor: section 8.3 (lines
   1730 to 2054).
4. **Empirical Le Cam tightness**: across codec sweep + cross-attacker
   comparison, Bayes / logistic / 1-NN attackers achieve the same
   accuracy to within sampling noise. Manuscript anchor: section
   10.6 (lines 2566 to 2596).
5. **Unification of three literatures**: approximate data structures,
   frequency-hiding encryption, encrypted search, all subsumed under
   cipher map formalism with measurable parameters. Manuscript anchor:
   section 1 lines 134 to 142, section 2 (related work), section 10.3
   (20 Newsgroups), section 10.6 (codec security).

## Differentiation assessment

### Against prior cipher-map-like constructions

The framework contribution is the most novel piece. The four-property
formalism (totality / representation uniformity / correctness /
composability) does not appear as a unit in any existing work. The
closest:

- Bloom (1970) and successors: data structures, no value-side privacy
  reasoning.
- SSE/PPE: simulation-based or game-based security definitions, not
  measurable parameters.
- QIF: entropy-based leakage measures but no specific construction.
- Frequency-hiding (Kerschbaum 2015): one mechanism (per-insert
  randomization), no unifying framework.

The cipher map framework draws all four threads into one. This is
genuinely new.

### Against multi-instance composition prior art

The coincidence-oracle theorem (Theorem 8.1) is a closed-form
amplification result. Closest published analogues:

- Naveed-Kamara-Wright 2015 (cited): single-instance frequency
  attacks on PPE.
- Kellaris-Kollios-Nissim-O'Neill 2016 (uncited): multi-query
  attacks on SSE / range queries. The closest published precedent
  for "attacker observing t snapshots of a structure under the same
  latent function". Should be cited.
- Cash et al. 2015 (cited): multi-document recovery attacks.

The Theorem 8.1 closed form is specific to the cipher map setting
(homogeneous instances, independent seeds, public codec). The
randomized-encoding defense (Proposition 8.2) is a direct application
of the multiplicity mechanism already in Property 2; the novelty is
the per-instance pattern-coincidence analysis under randomized
encoding (saturation condition + member coincidence probability).
Genuine but incremental over Property 2's foundation.

### Against acceptance-predicate / Pareto-frontier prior art

The (TV, L) Pareto frontier (section 10.6) is the most surprising
single result. The Shannon-optimal corner (L-min via Huffman) is well
known. The TV-optimal corner under integer codeword constraints is
not in the literature in this form. Closest:

- Issa-Wagner-Kamath 2020 (uncited): operational-leakage Pareto
  framework. Different metric (maximal leakage), same methodological
  approach (enumerate Kraft-feasible assignments, identify Pareto
  optima).
- Coding theory: Huffman vs Shannon-Fano vs arithmetic codes are well
  studied for L; not for L vs TV-from-target-distribution under
  integer constraints.

The 42x TV reduction at 17% L overhead is a concrete and surprising
empirical finding. It would benefit from a one-paragraph framing
that positions the result against Issa-Wagner-Kamath 2020 or similar.

## NOV-MAJ-1 (sister-paper deferral risk)

R6 / R7 MAJ-6 carry-over.

Four citations remain "Manuscript in preparation" in the bibliography:
- `bernoulli-types` (general Bernoulli framework citation): used at
  section 3.4 line 156 ("error framework underlying cipher maps is
  the Bernoulli model"), section 9.1 line 2085 (algebraic types),
  and section 9.3 line 2117 (trapdoor Boolean algebra).
- `towell2026algebraic` (functorial framework): used at section 10.3
  line 2401 ("characterized in companion work towell2026algebraic")
  for the AND noise-floor mechanism explanation.
- `towell2026maxconf` (entropy ratio framework): used heavily.
  Section 1 line 176, section 3.4 line 380, section 5.1 line 715,
  section 5.1 proof of Prop 5.1 line 775, section 5.2 line 838,
  section 8.1 line 1660, section 10.1 line 2274, section 10.5 line
  2530.
- `towell2026rekeying` (rekeying functor): used at section 3.4 line
  383, section 4.4 line 601, section 9.4 line 2129.

The most load-bearing single deferral is to `towell2026maxconf`:
- Proposition 5.1 (cipher map confidentiality bound) cites the
  full proof and discussion of tightness to "[Theorem 4.1, part 3]"
  of that paper.
- Section 5.1 to 5.2 (the entire entropy-ratio framing) depends on
  the formal definition published there.
- Section 5.2 item 4 (function-value leakage bound) defers
  translation of bit-bound to guessing-advantage bound to
  "[Sections 5 to 6]" of that paper.

If `towell2026maxconf` is not posted as a preprint at submission
time, three load-bearing forward references in this paper become
unverifiable. PoPETs reviewers will flag this; it is one of the
clearest blockers to "minor-revision" status.

The user has stated intent to mint Zenodo DOIs for these companion
papers. That is a sufficient resolution (Zenodo DOIs are citable and
checkable). Recommendation: post all four sister papers to Zenodo
before submission. Estimated work: 1 to 2 days. Closes MAJ-6 fully.

Alternative resolution paths if Zenodo posting is not feasible:
- Inline the load-bearing results: copy the Fannes-Audenaert
  derivation from `towell2026maxconf` into Prop 5.1's proof at
  cipher-maps section 5.1 (~ 2 paragraphs). Trades 2 paragraphs of
  manuscript length for 3 citations closed.
- Defer the affected results: drop section 5.1 entropy ratio
  framing, fall back to section 5.2 operational consequences as the
  security argument. Loses the QIF framing the paper introduced in
  R5 and would require thesis revision.

## NOV-MAJ-2 (framework contribution: vague vs sharp)

Section 1 lines 123 to 152 is the new "Contribution: framework, not
new construction" paragraph that R6 MAJ-5 / R7 closed. Reading it
fresh:

"We do not propose a new construction with novel space, time, or
correctness guarantees; rather, we identify a *framework* (the cipher
map abstraction with four measurable properties and the acceptance
predicate apparatus) that unifies several existing approximate-
membership and frequency-hiding constructions under a single
formalism with measurable parameters."

This is honest about not proposing a new construction. Good.

But then the paragraph continues to describe several specific
contributions:
- Information-theoretic lower bound matched by construction
  (Theorems 3.1, 6.2)
- Composition theorem (Theorem 7.1)
- Confidentiality bound (Prop 5.1)
- Multi-instance composition theorem (Theorem 8.1)
- Empirical Le Cam tightness

Several of these (especially the composition theorem and multi-
instance theorem) are arguably new constructions / new theorems, not
just framework-level. The paragraph is currently doing two jobs:
- Disclaiming construction novelty (good)
- Listing five specific contributions including theorems and empirical
  results (which are construction-level)

A reader could read this as "we don't propose a new construction, but
here are five new things we did", which weakens the disclaim. The
disclaim is appropriate for the framework framing (the four properties
+ acceptance predicate apparatus + parameter decomposition); the
specific theorems and empirical results are clearly novel and should
be listed as such, separate from the framework claim.

Recommendation: split the paragraph in two:

Paragraph A (Framework contribution): "We do not propose a new
approximate-membership construction. The contribution is a unifying
framework: the cipher map abstraction with four measurable properties
(totality, representation uniformity, correctness, composability), the
acceptance predicate as the universal design knob, and the parameter
decomposition into (eta, epsilon, delta, mu). Bloom filters, frequency-
hiding encryption, perfect-hash-based approximate maps, and encrypted-
search secure indexes are instances. The framework is the value of
this paper."

Paragraph B (New results within the framework): "Within the framework
we prove: an information-theoretic lower bound matched by the entropy
cipher map (Theorems 3.1, 6.2); a chain composition theorem
(Theorem 7.1) with explicit re-randomization condition; a confidentiality
bound tying representation uniformity to the entropy ratio (Prop 5.1,
deferring the full Fannes-Audenaert derivation to companion work); a
multi-instance composition theorem with closed-form coincidence-oracle
accuracy (Theorem 8.1) and randomized encoding as the deployment-side
defense (Prop 8.2). We validate the framework empirically: a Le Cam
attacker bound is realized by Bayes-optimal attackers across a codec
sweep, a (TV, L) Pareto frontier reveals a 42x TV reduction off the
Shannon-optimal corner on heavy-tailed value distributions, and a
20 Newsgroups encrypted-search application demonstrates per-document
trapdoor isolation at 4.5x the space of an optimal Bloom filter."

This separation makes the framework claim crisp and lets the specific
theorems / empirical results stand as new contributions within the
framework.

## NOV-MIN-1 (acceptance predicate framing precedence)

Section 6.2 (acceptance predicate definition + Shannon-optimal allocation)
is the closest the paper comes to a new mathematical construction. The
acceptance predicate as "a family of disjoint sets A(y) subseteq
{0,1}^n with decoder dec(hash) = y iff hash in A(y)" generalizes the
standard prefix-free coding setup. The novelty is treating the
A(y) partition as a tunable design knob (not just the natural Huffman
prefix-free partition), enabling explicit Pareto-frontier exploration
in section 10.6.

This is genuinely useful as a design abstraction. But the paper does
not explicitly claim it as new. Recommendation: add a one-sentence
note at the start of section 6.2 ("The acceptance predicate, as the
explicit tunable parameter, is the technical lever distinguishing
this framework from standard prefix-free coding approaches.") to make
the contribution visible.

## NOV-MIN-2 (Bernoulli framework citation chain)

The `bernoulli-types` citation is a placeholder for the full Bernoulli
sets/maps/data-types framework. Per state.md the Bernoulli work is split
into multiple papers in `~/github/bernoulli/papers/`. Section 9.1 (line
2081) cites it for the type hierarchy (Bool, Set, Map, Relation, Type),
section 9.3 (line 2117) for the trapdoor Boolean algebra, and the
intro (line 156) for the error model.

The citation chain is brittle: a single placeholder citation
("bernoulli-types") stands in for at least three distinct
contributions (Bernoulli error axioms, algebraic types, trapdoor
Boolean algebra). When the bernoulli papers are posted with
individual DOIs, this paper should cite the specific sub-paper at
each site. R7 CITE-SUG-3 carry-over.

## NOV-MIN-3 (functorial framing in section 3.4)

Section 3.4 (line 372 to 384) introduces the functorial framing
(`cipherS{X}{s}` as a functor, `Cipher_s` category, rekeying functor)
with explicit deferral to `towell2026rekeying`. This is a clarifying
shorthand, not a contribution. The placement and the deferral are
appropriate.

But the framework framing in section 1 ("framework, not new
construction") is silent on the categorical machinery. A reader who
encounters the functor talk at section 3.4 may wonder if the paper
claims category-theoretic novelty. Clarifying note at section 3.4
("the categorical apparatus is used here only as a clarifying
notation; the contribution to the categorical / algebraic structure
lives in companion work") would help.

## NOV-MIN-4 (online construction novelty disclaimer)

Section 9.3 ("Online Construction") mentions the trapdoor Boolean
algebra as a separate construction strategy, citing `bernoulli-types`
(line 2117). The four properties are claimed to hold for online
construction too (line 2120: "Both strategies produce objects
satisfying Definition 3.1"). But the property verification for online
construction is deferred to the companion citation.

This is the right scope decision (the paper is about the framework;
online construction details are companion-work territory). The
deferral is honest. Worth a one-sentence note that "the property
verification for the trapdoor Boolean algebra is in [bernoulli-types]"
to make the deferral explicit rather than implicit.

## Honest PoPETs survivability assessment

Given:
- R7 CRIT-1 is closed.
- K(x) prescription direction fixed today.
- E1, E3, E4 empirical results integrate honestly.

The remaining blockers:
- MAJ-6 sister-paper preprints (4 entries in bib). Highest impact;
  closes with 1 to 2 days of Zenodo posting.
- Methodology issues (codec inventory mismatch, H1 wording, Pareto
  enumeration). Soft blockers; closes with editorial pass.
- Direction-of-prescription audit additions (LOG-SUG-1 table).
  Defensive improvement.

If MAJ-6 closes (DOIs minted) and the methodology issues get an
editorial pass, this paper is plausibly minor-revision at PoPETs.
The framework contribution is sharp once NOV-MAJ-2 paragraph-split
lands. The empirical work is honest. The (TV, L) Pareto frontier is
surprising and underwritten.

What carries risk to PoPETs:
- The 38-page count vs PoPETs target 18 to 20 in their template
  (R7 MAJ-19 carry-over). Article class still used (R7 MAJ-6
  carry-over). These are out-of-scope for this review but block
  submission.
- The sister-paper deferral pattern: even with Zenodo DOIs, four
  papers in flight reviewed in parallel is a coordination risk a
  reviewer may flag. Worth being transparent about the publication
  strategy in the cover letter.
- Direction-of-prescription pattern: the user has caught three errors
  this cycle. The defensive addition of an explicit direction-summary
  table (LOG-SUG-1) at section 5.2 would signal that direction
  discipline is now codified.

Confidence: moderate-high that this paper, with MAJ-6 closed and the
identified majors addressed, is ready for PoPETs submission.
