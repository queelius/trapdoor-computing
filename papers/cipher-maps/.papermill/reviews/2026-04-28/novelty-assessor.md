# Novelty Assessor Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Novelty Assessor
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Focus**: Contribution clarity, differentiation, significance for PoPETs 2027

## Summary

The paper has two genuinely strong contributions (acceptance predicate unification, Shannon-frequency duality) and several modest framework-level contributions. The core conceptual innovation is real and well-articulated. The principal novelty risk for PoPETs remains the absence of either (a) a formal security definition that would make the four properties operational against an adversary, or (b) experimental validation that would demonstrate the practical advantages over Bloom filters and SSE schemes. With Round 3's M3 (citations) addressed, the paper now situates itself more cleanly relative to prior work, but the unresolved M1 and M2 still bound how the paper will be read.

**Findings**: 0 critical, 2 major, 3 minor.

---

## What is novel and well-supported

### N+1. Acceptance predicate unification (STRONG novelty)

§6.2 introduces the acceptance predicate as a single design choice that subsumes prefix-free codes, threshold predicates, and range partitions. The framing is original: while individual constructions (PHF with prefix codes; FKS hashing; Bloom filters as $A(\text{true}) = \{c : \text{accept}(c)\}$) exist, no published paper that I am aware of presents these as instances of one $A : Y \to 2^{\{0,1\}^n}$ family.

The "acceptance probability $\alpha(y) = |A(y)|/2^n$" framing directly connects to:
- the per-element coding cost $-\log_2 \alpha(y)$
- the noise-decode probability $\varepsilon = \sum_y \alpha(y)$
- the false-positive rate per non-stored element

This collapses three independent constructions into one parameter family. That is a real unification.

**Novelty: HIGH.** **Support: STRONG** (Definition 6.4, three instantiations, Theorem 6.2).

### N+2. Shannon-frequency duality (STRONG novelty)

The §6.2 paragraph "Shannon-optimal allocation and frequency hiding" makes the central conceptual claim of the paper: setting $\alpha(y) \propto p_y$ simultaneously achieves Shannon-optimal coding (space minimum) and frequency hiding (output indistinguishability from noise queries). The key sentence ("These are not two independent optimizations that happen to coincide. Shannon-optimal coding IS frequency hiding") is the paper's strongest single sentence.

This duality is implicit in entropy-coded cipher constructions (e.g., honey encryption's distribution-conforming encoding) but the explicit "duality" framing is, to my knowledge, original. It gives the paper a one-line slogan that is both true and non-obvious.

**Novelty: HIGH.** **Support: ADEQUATE.** The argument occupies one paragraph (lines 700-719). For the paper's central claim, it deserves more room (perhaps a worked example with a specific distribution, or a small figure showing acceptance regions sized by $p_y$).

### N+3. Four-property framework as a measurement vocabulary (MODERATE novelty)

The framework {Totality, Representation Uniformity ($\delta$), Correctness ($\eta$), Composability} is a useful taxonomy. Each property is independently measurable and tunable. The framework's pedagogical utility is high: it gives reviewers a checklist for evaluating any new cipher-map-like construction.

The contribution is more in the synthesis than in the individual properties. Totality appears in honey encryption; correctness as a tunable parameter appears in any approximate data structure; composability under approximation appears in noisy gates and Bernoulli compositions. The synthesis is original.

**Novelty: MODERATE.** **Support: STRONG** (each property has a definition, often a theorem, and is connected to construction-level parameters).

### N+4. Construction layers as a conceptual decomposition (MODERATE novelty)

§3.3 introduces three orthogonal "layers" (Undefined injection, Noise closure, Multiple representations) that produce the four properties. The decomposition is pedagogically valuable: it gives the reader a mental model of how to *build* a cipher map from a latent function.

The careful disclaimer that these are "conceptual scaffolding ... not algebraic monads" is a strength: it pre-empts a category-theory reviewer's objection while leaving a hook for future work.

**Novelty: MODERATE.** **Support: ADEQUATE** (one subsection, no theorems, but the connection to the four properties is clear).

### N+5. Encoding granularity / entanglement parameter $p$ (MODERATE novelty)

§8.1 introduces the entanglement parameter $p$ (the number of correlated values encoded as a single unit) and shows that it controls the trade-off between correlation-hiding and space cost. The Proposition 8.1 makes the formal claim that component-wise encoding (small $p$) preserves correlations while joint encoding (large $p$) hides them.

This is a useful diagnostic: it tells implementers how to think about the granularity decision. The claim that joint encoding is the only way to hide correlations is sharper than typical "we cannot hide everything" disclaimers.

**Novelty: MODERATE.** **Support: ADEQUATE.** Proposition 8.1 makes the claim; §8.2 discusses mitigation strategies. A worked example (e.g., what does $p = 4$ look like for a Boolean circuit?) would strengthen this.

---

## Major Findings on novelty positioning

### N1. The novelty pitch is buried in §6.2; the abstract underclaims (MAJOR)

**Location**: Abstract (lines 46-63) vs. §6.2 paragraph "Shannon-optimal allocation and frequency hiding" (lines 700-719)

**Quoted text** (abstract):
> "an *acceptance predicate* that partitions hash space among output values. Shannon-optimal allocation of this partition simultaneously minimizes space ... maximizes output indistinguishability ... and enables predictable error composition"

**Quoted text** (§6.2):
> "These are not two independent optimizations that happen to coincide. Shannon-optimal coding IS frequency hiding."

**Problem**: The abstract states the result (the three things happen simultaneously) but does not state the *unification claim* (these are the same optimization, not three coincident ones). A PoPETs reviewer scanning the abstract sees a list of three properties and may read it as "this primitive does three nice things." The §6.2 paragraph is the actual claim: there is one optimization, with three faces.

The paper's strongest sentence is in the middle of §6.2; the abstract describes the result but does not communicate the conceptual move. This is a missed opportunity in framing.

**Suggestion**: Rewrite the abstract's central sentence. Current: "Shannon-optimal allocation of this partition simultaneously minimizes space ... maximizes output indistinguishability ... and enables predictable error composition." Proposed: "We show that Shannon-optimal allocation of the acceptance predicate is simultaneously the space-minimizing choice and the frequency-hiding choice; these are not coincident optimizations but the same optimization with two interpretations." Then add a separate sentence for composition.

**Cross-verification**: prose-auditor likely flags abstract framing independently.

### N2. The "What this is not" exclusions in §9.5 leave the contribution un-positioned (MAJOR)

**Location**: §9.5 "What This Framework Is Not" (lines 1510-1524)

**Quoted text**:
> "Not ORAM ... Not differential privacy ... Not simulation-based security."

**Problem**: §9.5 disclaims three frameworks but does not name what the paper *is*. The paper's parameterized guarantees ($\delta$, $\varepsilon$) are an instance of *information-theoretic* security with *quantitative leakage*, a recognized tradition that includes:
- Entropic security (Russell-Wang 2002, Dodis-Smith 2005)
- Quantitative information flow (Smith 2009, Alvim et al. 2012)
- Non-malleable extractors and randomness extractors (Dodis-Wichs 2009)

A PoPETs reviewer reads §9.5 as "the author is rejecting all standard formalisms," which sounds like either crankery or a lack of awareness. The truth is closer to: "the parameterized-leakage style is not new; we are connecting cipher maps to the entropic / QIF tradition rather than to sim-based or game-based crypto."

The sister paper "maximizing-confidentiality" already cites QIF; this paper does not. The asymmetry suggests this is a curable framing problem rather than a real disagreement with the literature.

**Suggestion**: Rewrite §9.5 to add a positive label. Sample: "The cipher map framework belongs to the *quantitative information flow* tradition (Smith 2009; Alvim et al. 2012): security is parameterized rather than negligible, and leakage is measured as a continuous quantity ($\delta$, $\varepsilon$) rather than a binary event. We are not proposing a new security paradigm; we are giving a constructive recipe for building primitives whose leakage is bounded by these parameters."

This is the cheapest single change that would shift the paper's reception. Cost: two bib entries (Dodis-Smith 2005 and Smith 2009 or Alvim 2012), one paragraph rewrite. The conceptual content of §9.5 does not change.

**Cross-verification**: prose-auditor for the framing impact; literature scout for the citation correctness.

---

## Minor Findings

### N3. Abstract's "demonstrate" still overclaims (MINOR, m1 from Round 3 not addressed)

**Location**: Abstract, lines 60-62

**Quoted text**:
> "we ... demonstrate the construction on arbitrary maps, set membership, and encrypted search"

**Problem**: This was minor m1 in the prior review (recommended changing "demonstrate" to "illustrate"). Set membership is one Remark (15 lines); encrypted search is a Discussion subsection. Round 3's suggestion was to soften "demonstrate," and that was not done.

**Suggestion**: As prior review: change "demonstrate" to "illustrate."

### N4. Online construction (trapdoor Boolean algebra) deserves more space (MINOR)

**Location**: §9.3 "Online Construction" (lines 1368-1383)

**Problem**: The online construction is contrasted with the batch construction throughout the paper, but is treated only as a 16-line subsection in the Discussion. For a paper that claims "two construction strategies" as a core taxonomic contribution (§3.2), the online side is under-developed. The companion paper (towell2026algebraic) presumably handles this, but the current paper's reader has no way to evaluate "exponential in set size" without seeing the construction.

This is also where compositional leakage matters most: the trapdoor Boolean algebra accumulates errors more aggressively than batch constructions because every Boolean op is a cipher map composition. A PoPETs reviewer cannot tell, from the current paper, which scenario favors batch and which favors online.

**Suggestion**: Promote §9.3 to a brief top-level section (perhaps called "Online Constructions and Algebraic Composition") with concrete error bounds for union/intersection/complement. Even three paragraphs and one error formula would be useful. If the companion paper is the intended detail venue, cite it more prominently and explain *why* the batch focus is right for this paper.

This was also m2 from the prior review (Discussion section overloaded). Not addressed.

### N5. The cipher Boolean type appears only in the experimental paragraph (MINOR)

**Location**: Lines 1436-1446 (cipher Boolean explanation in Discussion)

**Problem**: The cipher Boolean type (True / False / Noise partition with 5%/90%/5%) is the running example in the experiments, the natural test bed for the Shannon-optimality claim, and the simplest concrete instantiation of the four properties. But it does not appear as a worked example in §6 or §7 where it would be most useful. It only appears in §9.4 as a side note.

A worked example of the cipher Boolean type in §6 or §7 would help readers understand the framework concretely *before* the experimental section uses it.

**Suggestion**: Add a short Example 6.1 (in §6.5 or §6.6) titled "The cipher Boolean type" that shows: (a) acceptance predicate $A(\text{True})$, $A(\text{False})$, $A(\text{Noise}) = \emptyset$; (b) Shannon-optimal allocation $|A(y)| \propto p_y$; (c) typical numbers (e.g., for $p = 0.05$ keyword frequency, $\alpha_T = 0.05$, $\alpha_F = 0.90$, $\varepsilon = 0.95$, with the 5% noise margin).

---

## Items where novelty is solid

- The unification of "online" (algebraic) and "batch" (seed search) construction strategies under one cipher map definition is clean.
- Bayesian deniability proposition gives the $\eta$ parameter a precise privacy interpretation.
- The honest limitations sections (Remark 4.1; §8 Honest Limitations; §9.5) are intellectually honest in a way that improves novelty positioning rather than weakens it.

## Overall novelty assessment

The paper has a real conceptual contribution. The acceptance predicate unification + Shannon-frequency duality together constitute a publishable insight, even at PoPETs.

The risk to publication is not novelty per se but *positioning*. Currently, the abstract underclaims (N1) and §9.5 disclaims-without-positioning (N2). A PoPETs reviewer who lands on §9.5 first will see "this is not any standard framework" and may downweight the paper. The same reviewer landing on §6.2 first will see "Shannon-optimal coding IS frequency hiding" and recognize a real result.

Fixing N1 and N2 before submission is essentially editorial. Fixing M1 (security definition) and M2 (experiments) is the real revision work.

**For the user's specific question (what else needs work besides M1/M2)**: N1 and N2 are the highest-impact editorial moves. They cost a few hours, change no theorems, and dramatically improve how the paper is read.
