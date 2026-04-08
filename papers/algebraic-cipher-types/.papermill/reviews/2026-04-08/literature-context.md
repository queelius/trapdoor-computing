# Literature Context Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Sources**: broad and targeted literature analysis

## 1. Field Positioning

The paper draws on three research areas simultaneously:
- **Encrypted computation**: FHE, ORAM, MPC, functional encryption, property-preserving encryption
- **Programming language security**: information flow type systems, security type systems
- **Approximate/probabilistic data structures**: Bloom filters, perfect hash functions, cuckoo filters

The trapdoor computing paradigm is distinct from all three in its privacy model (one-way hash + uniform representation, no game-based or simulation-based security), but a PLAS reviewer will expect the paper to position itself relative to all three.

---

## 2. Competing Approaches

### Fully Homomorphic Encryption (FHE)
- Gentry 2009 (cited), Brakerski-Vaikuntanathan 2011, GSW 2013
- FHE supports arbitrary computation on ciphertexts with simulation-based security
- Cipher maps: total functions with hash-based privacy, O(1) evaluation, but limited to functions materializable as lookup tables
- **Key difference**: FHE has provable semantic security; cipher maps have weaker property-based guarantees but O(1) evaluation and no bootstrapping

### Oblivious RAM (ORAM)
- Goldreich-Ostrovsky 1996 (cited), Path ORAM (Stefanov et al. 2013)
- ORAM hides access patterns; cipher maps do NOT hide access patterns
- Cipher TM head movement leakage is an explicit non-ORAM property
- **Key difference**: Cipher TM leaks head movement; ORAM does not. But cipher TM has no O(log N) overhead.

### Functional Encryption
- Boneh, Sahai, Waters (TCC 2011) -- NOT CITED, should be
- Functional encryption allows computing specific functions on ciphertexts with formal security
- Cipher maps are closer to functional encryption than FHE conceptually (specific functions, not arbitrary computation)
- **Key difference**: Functional encryption has game-based security definitions; cipher maps use representation uniformity

### Property-Preserving Encryption
- Naveed et al. 2015 (in bib, NOT CITED)
- Order-preserving encryption (Boldyreva et al. 2009, 2011)
- Deterministic encryption (Bellare et al. 2007)
- These reveal specific properties (order, equality) for functionality; cipher maps reveal different properties
- **Key difference**: PPE leaks specific algebraic properties by design; cipher maps leak through orbit closure and type structure

### Searchable Symmetric Encryption (SSE)
- Song et al. 2000 (in bib, NOT CITED), Curtmola et al. 2006, Cash et al. 2013
- SSE supports keyword search on encrypted data
- The Boolean search experiment (Table 1) is directly comparable to SSE
- **Key difference**: SSE provides formal leakage profiles (search pattern, access pattern); cipher maps provide probabilistic guarantees (FPR, representation uniformity)

---

## 3. Type-Theoretic Security Literature

### Information Flow Type Systems
- Sabelfeld & Myers (IEEE J-SAC 2003) -- NOT CITED, should be for PLAS
- Volpano, Irvine, Smith (JCS 1996)
- These use type systems to track information flow and prevent leakage
- The sum-type impossibility has a direct analogue in information flow: sum types require case analysis, which reveals the tag (the "implicit flow" problem)
- **This connection is not made in the paper and should be.**

### Security Type Systems for Cryptographic Protocols
- Fournet, Kohlweiss, Strub (POPL 2011) -- typed crypto using refinement types
- Barthe, Gregoire, et al. -- computer-verified crypto implementations
- These apply type theory to cryptographic protocols; this paper applies type theory to a specific encryption paradigm

### Typed Approaches to FHE
- Crockett, Peikert (CRYPTO 2018) -- A Toolkit for Ring-LWE Cryptography
- HElib, SEAL, and other FHE libraries have type systems for organizing operations
- But none formally study how sum/product/exponential types interact with encryption

---

## 4. Closest Prior Work to Each Contribution

### Sum-Type Impossibility
**Closest**: The implicit flow problem in information flow control. When you branch on a secret, the branch taken leaks the secret. This is precisely the sum-type impossibility: pattern matching (branching) reveals the tag (which branch). The paper should cite and compare.

### Orbit Closure
**Closest**: Functional graph analysis in cryptography (cycle structure of permutations). Also related to algebraic attacks on block ciphers (linear/differential cryptanalysis). The orbit concept itself is standard in group theory (orbits under group actions). No direct prior application to cipher map confidentiality.

### Cipher TM
**Closest**: RAM model of ORAM (Goldreich-Ostrovsky). Also related to Oblivious Turing Machines (Pippenger-Fischer 1979). The cipher TM is weaker (leaks head movement) but avoids the O(log N) overhead.

---

## 5. Potential Reviewer Objections

1. **"Why not use FHE?"** The paper should explain more clearly what cipher maps provide that FHE does not (O(1) evaluation, no bootstrapping, practical for lookup-table-sized functions) and what they sacrifice (no provable semantic security, limited to materializable functions).

2. **"The privacy model is too weak."** A crypto reviewer will note the lack of game-based security definitions. The paper explicitly disavows these, but should provide a more detailed argument for WHY the weaker model is appropriate and sufficient for the intended applications.

3. **"The orbit closure is just graph reachability."** True in the abstract, but the application to cipher map confidentiality is novel. The paper should acknowledge the standard nature of the tool and emphasize the application.

4. **"Only 6 references?"** A PLAS paper should cite 20-30 references. Six is far too few for any venue.

5. **"The experiments are toy-scale."** 150 inputs for the granularity experiment, 5,000 documents for Boolean search. A reviewer may question whether these scale.
