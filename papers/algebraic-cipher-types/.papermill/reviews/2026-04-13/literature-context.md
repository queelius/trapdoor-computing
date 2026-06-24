# Literature Context (2026-04-13)

## Note on this scout pass

The Task tool was unavailable in this orchestration. The literature-context summary below is compiled from the paper's own bibliography, the prior 2026-04-12 literature-context document on file, and the area chair's own knowledge of the field. It is therefore lighter than a true subagent-driven scout. The bibliography expansion (10 to 21 cites) is large enough that the literature gap is no longer the dominant issue; the gaps that remain are listed below.

## State of bibliography

The paper now cites 21 entries; all 21 are referenced in the body.

By topic coverage:
- ORAM: Goldreich-Ostrovsky 1996 (foundational only).
- FHE: Gentry 2009 (foundational only). No FHE compiler papers (Concrete, HEIR, Viand 2021 SoK).
- Garbled circuits: Yao 1982 (foundational only). No succinct garbling, garbled TMs, or recent practical implementations.
- Functional encryption: Boneh-Sahai-Waters 2011 (foundational only).
- SSE: Song 2000, Curtmola 2006, Islam 2012, Cash 2015, Grubbs 2017, Naveed 2015. Strong coverage of foundational + leakage attacks.
- Information-flow type systems: Sabelfeld-Myers 2003. Single citation for the entire IFC tradition.
- Quantitative information flow: Smith 2009. Single citation. The entropy-form confidentiality bound puts the paper inside QIF; one entry is thin.
- Random oracles: Bellare-Rogaway 1993. Standard.
- PHF: Fredman-Komlos-Szemeredi 1984. Foundational only; no modern PHF papers (cite-PHF, RecSplit, etc.).
- Bloom filter: Bloom 1970. Foundational only.
- Source coding: Shannon 1948. Foundational.
- Turing machine: Turing 1936. Foundational.
- Dataset: Lang 1995 (20 Newsgroups).
- Self-citations: towell2026cipher (16x), towell2026bernoulli (4x), towell2026maxconf (1x).

## Gaps that a venue reviewer would flag

### Critical for cipher-TM section
**Obfuscation of FSMs/TMs.** A "cipher Turing machine" with O(|Q|*|Gamma|) space and access-pattern leakage is in the same neighborhood as obfuscated finite-state machines, garbled TMs, and indistinguishability obfuscation (iO) for TMs. The paper cites none of:
- Lynn, Prabhakaran, Sahai 2004 "Positive results and techniques for obfuscation": obfuscatable point functions, structural results.
- Wichs, Zirdelis 2017 "Obfuscating compute-and-compare programs": LWE-based, related primitive.
- Garbled TM literature (Goldwasser-Kalai-Popa-Vaikuntanathan-Zeldovich 2013, Lu-Ostrovsky 2013, Goyal-Koppula-Waters 2015).

A PLAS or TCC reviewer will ask: "how does this differ from obfuscation/iO?" The paper preempts ORAM, FHE, FE, and garbled circuits but not these.

### Major for the @cipher_node decorator framing
**FHE compiler annotations.** The "@cipher_node" decorator is structurally similar to FHE compiler annotations:
- Concrete (Zama, 2020+): MLIR-based FHE compiler with TFHE backend.
- HEIR (Google, 2023+): MLIR FHE compiler.
- CHET (Microsoft, 2019): tensor FHE compiler.
- Viand, Jattke, Hithnawi 2021 "SoK: fully homomorphic encryption compilers" (S&P).

Citing Viand et al. would acknowledge the design-space ancestry. Without this, the @cipher_node decorator looks unprecedented when in fact it is a well-known compiler pattern transposed to a different cryptographic primitive.

**Multi-stage programming.** The cut-point construction is a staged compilation pattern (Taha-Sheard 2000, Sheard-Peyton-Jones 2002). Mentioning the staging connection grounds the design in PL theory.

### Minor (publishable without)
**FE lower bounds.** The sum-type impossibility belongs to a recognized family of FE/predicate-encryption lower bounds (Boneh-Sahai-Waters 2011 already cited gives the upper bound side; Agrawal-Pellet-Mary 2020 or similar gives the lower bound side). One sentence acknowledgement suffices.

**Reachability/orbit literature.** Orbit closure is a model-checking / state-exploration construct. Acknowledging the dynamical-systems origin (one sentence) is good practice and was suggested in the prior review.

## Conclusion on bibliography state

The 2026-04-12 expansion to 21 cites is a meaningful improvement over the 6-cite version of 2026-04-08 and the 10-cite version mid-revision. The remaining gaps are concentrated in two specific places:
1. Cipher TM positioning vs. obfuscation literature.
2. @cipher_node positioning vs. FHE compilers.

Neither is critical. PLAS submissions of comparable length typically have 25-35 cites; 21 is on the lower end but no longer thin.

The dataset and SSE-attacks coverage is now fine. QIF coverage is minimal but adequate for a single result. The IFC coverage is thinner than ideal (one cite for an entire tradition) but workable.

## Venue fit

PLAS remains the natural primary target given the type-theoretic framing, the sum-type impossibility, and the typed-chain discipline. The bibliography no longer disqualifies the paper for venue fit.

IACR ePrint is a valid fallback. TCC is a weaker fit: TCC typically expects game-based proofs; this paper deliberately does not provide them.

## Genuinely novel positioning

The strongest novelty positioning is:
- Sum-type impossibility (information-theoretic, not game-based; for cipher values, not encrypted equality predicates).
- Orbit closure as a confidentiality measure for cipher-value transition systems (the QIF framework specialized to cipher-value reachability).
- Typed composition chains as a design-time orbit budget.

The cipher Turing machine is on weaker ground: without obfuscation-literature citations the comparison story is incomplete.

The empirical FPR-compounding finding (Bernoulli independence breaks for cipher-map AND chains at depth > 2) is the paper's only standalone-publishable empirical observation. Underclaimed in the current draft.
