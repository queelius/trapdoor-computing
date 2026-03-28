# Novelty Assessor Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper proposes a new abstraction (cipher maps) with four measurable properties, a unifying construction framework (acceptance predicates), and a central technical insight (Shannon-frequency duality). The novelty is real but the contribution sits in an awkward space for PoPETs: it is too theoretical for a systems venue and lacks the formal security definitions PoPETs reviewers expect from a crypto paper.

## Findings

### MAJOR: No formal security definition -- PoPETs will require one

- **Location**: The entire paper; most acutely Section 5 (trust model) and Section 9.5 ("What This Framework Is Not")
- **Problem**: The paper explicitly rejects simulation-based security, game-based security, and differential privacy. It offers instead four "measurable properties" with information-theoretic parameters ($\eta$, $\varepsilon$, $\delta$). But it never defines a security game or experiment that a PoPETs reviewer can evaluate. What does it mean for a cipher map to be "secure"? The paper says the untrusted machine "cannot" do various things (Definition 5.2, lines 477-484), but these are informal claims backed by Property 1 and Property 2, not by a cryptographic definition.

  PoPETs papers that propose new primitives typically define a security game (e.g., IND-CPA, IND-CKA, leakage function + adaptive security). The paper's explicit refusal to do this ("We do not claim that the untrusted machine's view can be simulated") will be seen as a weakness, not a feature, by PoPETs reviewers. At minimum, the paper should formalize what the adversary learns as a leakage function $\mathcal{L}(\cdot)$ and show that the four properties bound $\mathcal{L}$.
- **Severity**: MAJOR
- **Confidence**: HIGH
- **Suggestion**: Define a security experiment: given a cipher map $\hat{f}$, the adversary outputs a guess about $f$. Show that the advantage is bounded by $\delta$ (from representation uniformity) and $\varepsilon$ (from noise-decode probability). This does not require simulation-based security; an indistinguishability-based definition with explicit leakage would suffice.

### MAJOR: No implementation, no experiments -- significant gap for PoPETs

- **Location**: The paper is purely theoretical
- **Problem**: PoPETs is a systems-oriented venue that expects concrete artifacts. The paper has no implementation, no benchmarks, no concrete parameter instantiations beyond toy examples (e.g., the $\alpha = 0.5, 0.9, 0.99$ table and the $\eta = 10^{-6}$ example). A reviewer will ask: "For a realistic encrypted search workload with 10^6 documents, what are the actual space, construction time, and query time?" The paper cannot answer this question as written.
- **Severity**: MAJOR
- **Confidence**: HIGH
- **Suggestion**: At minimum, add a concrete parameter instantiation section: pick a realistic scenario (e.g., encrypted keyword search over 10^5 documents with 10^4 keywords), compute the concrete bits/element, construction time, and query time, and compare against a Bloom filter baseline and an SSE baseline. Ideally, implement a prototype and report measurements.

### Novelty Assessment by Contribution

| Contribution | Novelty | Significance | Notes |
|---|---|---|---|
| C1: Four-property framework | Moderate | High | The decomposition into totality, rep. uniformity, correctness, composability is a clean conceptual contribution. But the individual properties are not new: totality = obfuscation, rep. uniformity = homophonic substitution, correctness = approximate data structure, composability = function composition. The novelty is in the synthesis. |
| C2: Trusted/untrusted model | Low | Moderate | Two-party computation models are well-established. The specific model here is essentially client-server with a static lookup table. |
| C3: Acceptance predicate framework | High | High | This is the paper's strongest contribution. Showing that all batch cipher maps reduce to a choice of acceptance predicate is a genuine unification. |
| C4: Shannon-frequency duality | High | High | The insight that space-optimal coding IS frequency hiding is non-obvious and elegant. This is the paper's central technical insight. |
| C5: Lower bound | Low | Low | Standard information-theoretic lower bound. The decomposition into membership + value components is well-known (see Bloom filter literature, Carter et al.). |
| C6: Composition theorem | Low | Moderate | The formula $1 - \prod(1 - \eta_i)$ is standard for independent error events. The contribution is showing it applies to cipher maps specifically. |
| C7: Encoding granularity | Moderate | Moderate | The entanglement parameter and the marginal-vs-joint distinction are useful but not surprising. |
| C8: Bayesian deniability | Low | Low | Direct application of Bayes' rule to the error model. |

### Overall Novelty Verdict

The paper has two genuinely novel ideas (C3, C4) embedded in a framework (C1) that provides useful conceptual vocabulary. The other contributions (C2, C5, C6, C7, C8) range from standard to modest. For PoPETs, the theoretical contributions alone are insufficient without a formal security definition (which the paper refuses to provide) or experimental validation (which the paper lacks entirely). The paper would be a better fit for a theory venue (STACS, TCC) if it added formal security definitions, or for PoPETs if it added an implementation and evaluation.
