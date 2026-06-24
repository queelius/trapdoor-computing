# Literature Context Packet

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp)
**Date**: 2026-04-12
**Scope**: Merged broad field survey + targeted prior-art comparison.

This document combines what a literature survey would flag for the review: where the paper sits in the broader field, which specific papers it most closely resembles, and which gaps in the bibliography are the most consequential.

---

## Field Positioning

The paper draws on four literatures:

### 1. Confidential computation frameworks

**Direct comparators** (the paper positions explicitly against these):

- **Fully Homomorphic Encryption (FHE)**: Gentry 2009 (cited, [4]), Brakerski-Gentry-Vaikuntanathan, more recently CKKS (Cheon et al. 2017) and TFHE (Chillotti et al. 2020). Cipher maps differ in: (a) information-theoretic parameterization vs. game-based; (b) total functions with bounded error vs. exact arithmetic. The paper's framing vs. FHE is clear.

- **Functional Encryption (FE)**: Boneh-Sahai-Waters 2011 (cited, [2]). Cipher maps differ in: (a) random-oracle modeled hash hiding vs. key-based; (b) approximate output vs. exact. Lower bounds on FE (e.g., Goldwasser-Kalai-Popa-Vaikuntanathan-Zeldovich 2013) could sharpen the sum-type impossibility.

- **Oblivious RAM (ORAM)**: Goldreich-Ostrovsky 1996 (cited, [5]). Cipher TMs explicitly do NOT hide access patterns, unlike ORAM. Explicit comparison in Remark 6.1.

- **Garbled Circuits / Yao's protocols**: Yao 1982 (cited, [10]). Cipher maps are not protocols; single-party untrusted-machine evaluation vs. two-party communication.

**Adjacent but uncited**:

- **Order-Revealing and Order-Preserving Encryption (OPE/ORE)**: Boldyreva et al. 2009 (OPE), Lewi-Wu 2016 (ORE). Leakage-abuse attacks on OPE/ORE (Grubbs et al. 2017) strengthen the "avoid property preservation" argument in Related Work.

- **SSE with simulation-based security**: Curtmola et al. 2006 (cited, [3]). The paper positions against SSE but does not cite more recent, stronger attacks (Cash et al. 2015 leakage-abuse, Kellaris et al. 2016 generic attacks).

### 2. Language-based security and information flow

**Direct comparators**:

- **Denning 1976 "A Lattice Model of Secure Information Flow"**: the foundational work on implicit information flow. Sum-type pattern matching is a canonical implicit flow example. Not cited.

- **Sabelfeld-Myers 2003 "Language-based Information-Flow Security"**: cited ([7]) as the main IFC reference. Good fit.

- **Volpano-Smith-Irvine 1996 "A Sound Type System for Secure Flow Analysis"**: type-based IFC. Could strengthen the "type-theoretic approach to security" framing.

- **Type-based information flow in modern languages**: FlowCaml (Pottier-Simonet 2002), Jif (Myers 1999, with Sabelfeld-Myers updates), F* for security. Modern recent work on dependent types for security (Ahman et al. 2017, Protzenko et al.).

- **Gradual typing for security / hybrid type checking**: Disney-Flanagan 2011.

**Adjacent**:

- **Secure Multi-Party Computation compilers**: Frigate, ObliVM, MOTION, MP-SPDZ. Language-level support for secure computation. Cipher-map compilation via @cipher_node is a different flavor but belongs in the same discussion.

### 3. Obfuscation and program hiding

**Direct comparators** (important for cipher TM positioning):

- **Barak et al. 2001 "On the (Im)possibility of Obfuscation"**: VBB impossibility. Establishes what obfuscators cannot do.

- **Goldwasser-Rothblum 2007 "Best-Possible Obfuscation"**: IND-obfuscation, weaker than VBB.

- **Indistinguishability obfuscation (iO)**: Garg et al. 2013, more recent constructions 2020 to 2023 (Jain-Lin-Sahai 2021 assumes LWE + LPN + PRG). Cipher TMs are not iO (no game-based security).

- **Cryptographic obfuscation of finite-state machines**: Lynn-Prabhakaran-Sahai 2004, Paneth-Sahai 2012. This is the closest prior work to cipher TMs in spirit.

Cipher TMs should be positioned against this literature: they are a lookup-table-based hiding mechanism with representation uniformity, not an obfuscator in the cryptographic sense. The paper currently does not make this comparison; it should.

### 4. Type theory and algebraic data types in security

**Direct**:

- **Algebraic data types** (sums, products, recursive types): folklore, but cryptographic treatment is rare. The closest is the "Bernoulli data type" literature the author has developed (cited as towell2026bernoulli).

- **Type-directed compilation for security**: relatively few entries. Bauer et al., Murray et al. on seL4 types.

- **Dependent types for cryptography**: CryptHOL (Lochbihler 2017), Barthe et al. on EasyCrypt. Not directly relevant, but adjacent.

**Concept-specific**:

- **Kronecker-factored encoding** (referenced implicitly via "Bernoulli data types"): this is the accuracy-side analogue the paper complements. The author's own prior work.

---

## Targeted Prior-Art Comparison

This section addresses specific novelty claims in the paper.

### Claim 1: "Sum-type impossibility" is novel

**Status**: Appears genuinely new as stated but belongs to a recognized family.

**Closest prior**:
- Determinism leakage in encrypted databases: any deterministic encryption leaks equality. The sum-type impossibility is structurally similar (deterministic tag-classification leaks the tag).
- Goldwasser-Micali 1984 showed deterministic encryption cannot be IND-CPA secure. Cipher sum-type tag-hiding corresponds to a ciphertext-indistinguishability variant for the tag bit.
- Lower bounds on FE for branching programs / circuits (Goldwasser-Kalai-Popa-Vaikuntanathan-Zeldovich 2013, Agrawal-Wichs 2017): structural impossibilities for FE reuse.

**Verdict**: The paper's theorem is stated in a distinct framework (representation uniformity, not game-based), for a distinct setting (algebraic sum types, not keyword encryption), and as an exact rather than amortized statement. Genuine novelty, but the paper should explicitly differentiate from the above. See NV-MAJ-2 in novelty-assessor.

### Claim 2: Orbit closure as a confidentiality measure

**Status**: New application of an old concept.

**Closest prior**:
- Reachability analysis in program verification: standard in model checking, abstract interpretation (Cousot-Cousot 1977).
- Reachability in probabilistic programs for information leakage: Clarkson-Schneider hyperproperties.
- Knowledge sets in epistemic logic: Fagin-Halpern-Moses-Vardi 1995.
- Orbits of group actions under cryptographic operations: Katz-Lindell textbook treatment.

**Verdict**: "Orbit closure" is a reachable-state computation. The novelty is the application to cipher-value transition systems and the connection to confidentiality. The paper should acknowledge the reachability origin (NV-MAJ-1 in novelty-assessor).

### Claim 3: Typed composition chains as a design-time budget

**Status**: Framing-novel; the underlying technique is mundane.

**Closest prior**:
- Type-based staging: multi-stage programming (MetaOCaml, Taha), where staging types control where computation happens.
- Session types: Honda-Vasconcelos-Kubo 1998, subsequent Caires-Pfenning 2010. Types control communication patterns.
- Type-based IFC: Denning's lattice, Sabelfeld-Myers. Types prevent information flow.
- Effect systems: Gifford-Lucassen 1986, Koka (Leijen).

**Verdict**: The idea that types constrain available operations is classic. The novelty is applying it specifically to cipher-space typing to bound orbit size. A mild novelty claim would read as fair; a strong one would need more differentiation.

### Claim 4: Expression-tree decomposition via @cipher_node

**Status**: Genuinely new as a construct (to the reviewer's knowledge), though structurally similar to MPC/FHE compiler passes.

**Closest prior**:
- MPC compilers (Frigate, Obliv-C, MP-SPDZ, MOTION): compile programs to MPC circuits.
- FHE compilers (Cingulata, EVA, HEIR, Concrete): compile programs to FHE circuits.
- Partial evaluation: specialize a function at specific arguments (Jones-Gomard-Sestoft 1993).
- Circuit partitioning for secure computation: various, e.g., GraphSC.

**Verdict**: @cipher_node is a distinct construct because it is specifically designed for cipher-map placement with a trusted-machine tracing stage. The novelty claim is reasonable. The paper should explicitly compare to MPC/FHE compilers to earn the "practical realization" framing.

### Claim 5: Cipher TM with head-movement leakage explicit

**Status**: Semi-novel. The idea of an encrypted TM exists in prior work; the explicit treatment of head movement as leakage in this framework is new.

**Closest prior**:
- Goldreich 1987 "Towards a Theory of Software Protection and Simulation by Oblivious RAMs": an oblivious RAM hides both data and access patterns.
- Goldreich-Ostrovsky 1996: ORAM, the formal version.
- Lynn-Prabhakaran-Sahai 2004: cryptographic obfuscation of finite-state machines and point functions.
- Ananth-Jain 2015 and follow-ups on randomized encodings of computation.

**Verdict**: The specific framing (cipher TM as lookup-table-based with representation-uniform transitions, exposing head movement as a distinct leakage channel) is a new articulation within this framework. Not a headline novelty but a reasonable secondary contribution.

### Claim 6: FPR compounding anomaly (Bernoulli model vs. empirical)

**Status**: Genuinely novel empirical finding.

**Closest prior**:
- Bloom filter composition theorems: standard, assume independence of hashes.
- Bernoulli composition for approximate sets: towell2026bernoulli.
- Compositionality of cryptographic games with correlated adversaries: more abstract.

**Verdict**: The observation that AND-chain composition violates Bernoulli independence at the cipher-map level is a non-trivial empirical observation, worth its own subsection. Currently underclaimed (see NV-MIN-4).

---

## Most Consequential Bibliography Gaps

Ranking by importance for review quality:

1. **Recent SSE leakage-abuse attacks** (Cash et al. 2015, Kellaris et al. 2016, Grubbs et al. 2017): directly relevant to positioning cipher maps as an alternative to SSE.

2. **Modern FHE compilers and tools** (Viand et al. 2021 SoK, EVA, HEIR, Concrete): positions cipher-program realization against FHE compilers.

3. **Cryptographic obfuscation of automata** (Lynn et al. 2004, Ananth-Jain 2015): closest prior to cipher TMs.

4. **Information flow type systems** (Volpano-Smith 1996 beyond Sabelfeld-Myers, Pottier-Simonet 2002 FlowCaml): sharpens the PL angle.

5. **20 Newsgroups dataset** (Lang 1995): basic reproducibility.

6. **Bloom filters** (Bloom 1970, already in bib but uncited): cipher Boolean uses Bloom-style allocation.

7. **Perfect hashing** (Fredman-Komlos-Szemeredi 1984, already in bib but uncited): PHF is central to the implementation.

8. **Shannon** (Shannon 1948, already in bib but uncited): "Shannon-optimal allocation" is explicitly named without citation.

Items 6 to 8 are already in the .bib; citing them in-text is a half-hour edit. Items 1 to 5 require research and selection.

---

## Venue Fit Assessment

**PLAS (Programming Languages and Analysis for Security at CCS)**:

The paper fits PLAS well:
- Type-theoretic framing (sum/product/exponential) matches the PL side.
- Sum-type impossibility is a clean type-level result.
- Typed-chain discipline as an orbit-budget mechanism has a direct PL flavor.
- @cipher_node implementation is a PL-level construct.

**What could strengthen the PLAS fit**:
- Connect more explicitly to information flow type systems in Related Work.
- Position typed-chain discipline against effect systems, session types, or gradual typing.
- Cite recent PL/security intersection work post-2020.
- Frame @cipher_node as a staging annotation (multi-stage programming terminology).

**IACR ePrint (technical report)**:

Lower bar. Any reasonable submission will appear. Does not provide the peer-review signal of a workshop. Current format is fine.

**TCC (Theory of Cryptography)**:

Weaker fit. TCC prefers game-based definitions and full cryptographic proofs. The paper's information-theoretic parameterization is unusual for TCC.

**Recommendation**: PLAS as primary, IACR ePrint as fallback (or co-publication).

---

## Summary for Area Chair

- **Positioning**: Clear and mostly correct; the paper knows where it sits relative to FHE, FE, ORAM, SSE, and PPE.
- **Genuine novelty**: Strongest in the sum-type impossibility (Thm 4.2) and the FPR compounding anomaly. Moderate in orbit closure (new application, old technique) and @cipher_node (new construct, adjacent to existing compilers). Weakest in cipher TM (overlaps with long history of encrypted-execution literature).
- **Bibliography**: Needs expansion for PLAS. Priority additions: recent SSE/FHE work, obfuscation of FSMs, information flow types.
- **Self-citation dependency**: High. The paper depends on an unpublished companion for core definitions; post that first if possible.
