# Writing Plan: Quantitative Confidentiality for Cipher Maps

## Rewrite Strategy

Complete rewrite of the 43-page "Maximizing Confidentiality in Encrypted Search" paper,
grounding it in the cipher map formalism. Target: 15-20 pages, theory venue.

## What Was Kept from the Old Paper

1. Entropy ratio e = H/H* as the confidentiality measure
2. Noise injection (filler queries, artificial trapdoors)
3. Homophonic encoding (multiple representations, K(x) > 1)
4. Compression-based entropy estimation
5. Case study numbers (59% -> 85% improvement)
6. Maximum entropy under constraints (Jaynes principle)

## What Was Dropped

1. All 43 pages of the old formalism (replaced by cipher map framework)
2. All custom notation (rv{X}, qb, hqb, rvhrs, etc.)
3. The probabilistic model section (replaced by cipher map parameters)
4. The generative model (Algorithm 3)
5. Queueing theory for inter-arrival times
6. Mix network discussion
7. Artificial search agents section
8. Appendices (entropy derivations, compression estimation, hypothesis testing)
9. All TikZ figures from the old paper
10. The ORAM discussion (incompatible with cipher map privacy model)

## What Was Added

1. Grounding in the cipher map framework (cite, don't re-derive)
2. Theorem connecting entropy ratio to the four parameters (eta, epsilon, delta, mu)
3. Noise dilution theorem with Fisher information argument
4. Multiplicity theorem with TV distance bound
5. Encoding granularity principle (from cipher-maps and algebraic-cipher-types)
6. Compositional confidentiality (FPR compounding, correlation leakage)
7. Orbit closure as a confidentiality bound (from algebraic-cipher-types)
8. Experimental results from three cipher-maps experiments
9. Leakage analyzer concept

## Section Assignment

| Section | Pages | Source |
|---------|-------|--------|
| Introduction | 2 | Written by orchestrator (full-draft context) |
| Preliminaries | 1 | Cites cipher-maps paper; notation recap |
| Confidentiality Measure | 2 | Core theory: entropy ratio + parameter connection |
| Three Levers | 4 | Noise, multiplicity, granularity |
| Compositional Confidentiality | 2 | FPR compounding + correlation leakage |
| Practical Measurement | 1.5 | Compression estimation + Monte Carlo |
| Experimental Results | 2 | Tables from cipher-maps experiments |
| Discussion | 1 | Open questions + limitations |
| Conclusion | 0.5 | Summary |

Total: ~16 pages (13 actual, within target)

## Key Design Decisions

1. **Do not re-derive the cipher map definition.** Cite [towell2026cipher] for the
   definition, four properties, composition theorem, and acceptance predicates.

2. **Do not use simulation-based security.** No Adv, Sim, PPT, game-based definitions.
   Privacy is information-theoretic throughout.

3. **Match the cipher-maps paper notation.** Use fhat, enc, dec, s, eta, epsilon,
   delta, mu, TV, B^n. Same theorem environments.

4. **The entropy ratio connects the old and new formalisms.** The old paper's good
   idea (entropy as confidentiality measure) is now grounded in the cipher map
   parameters.

5. **Three levers map to cipher map properties.** Noise -> totality, multiplicity ->
   representation uniformity, granularity -> composability.
