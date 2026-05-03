# Literature Context Packet (Round 5, 2026-04-30)

## Field state

Cipher maps sit at an intersection of three communities and a fourth (QIF) that the paper now explicitly adopts.

### 1. Searchable encryption / property-preserving encryption
- **Curtmola et al. 2006** (cited): IND-CKA, simulation-based.
- **Cash et al. 2013** (cited): Boolean queries with sublinear search; large-scale OXT.
- **Cash et al. 2015** (cited): leakage-abuse attacks against SSE, with concrete recovery of queries from leakage profiles even under simulation-secure schemes.
- **Naveed et al. 2015** (cited): inference attacks on PPE with auxiliary data.
- **Islam et al. 2012** (cited): access pattern attack.
- **Kerschbaum 2015** (in bib, NOT cited): frequency-hiding OPE. The closest direct predecessor for the "frequency-hiding via output-distribution shaping" mechanism cipher maps now build on.
- **Kamara & Moataz 2019** (in bib, NOT cited): computationally volume-hiding SE, an analogue to cipher maps' totality eliminating "in-domain vs out-of-domain" signal.
- **Patel-Persiano-Yeo-Yung 2019** (NOT in bib): volume-hiding STE construction. Direct competitor to the operational guarantees in Table 1.
- **Wang-Chow 2022 / Bost-Minaud-Ohrimenko 2017** (NOT in bib): forward-private SE; orthogonal but worth a sentence.

### 2. Quantitative information flow (QIF), newly adopted positioning
- **Smith 2009** (cited): foundations of QIF, gain functions, multiplicative leakage.
- **Alvim et al. 2012** (cited): generalized gain functions; expected gain leakage measure.
- **Dodis-Smith 2005** (cited): entropic security, the prior "negligible-leakage-on-high-entropy-messages" model that QIF generalizes.
- **Köpf-Smith 2010**, **Espinoza-Smith 2013** (NOT in bib): Shannon and min-entropy leakage measures with operational interpretations. Relevant if cipher-maps wants to motivate Shannon entropy specifically over min-entropy.
- **McIver-Morgan-Meinicke-Smith-Geldenhuys 2014** (NOT in bib): "Abstract Channels and Their Robust Information-Leakage Ordering," relevant for the lattice ordering of cipher map confidentiality.

### 3. Approximate data structures and perfect hashing
- **Bloom 1970** (cited): canonical comparison.
- **Bender et al. 2012**, **Fan et al. 2014** (cited): cuckoo, quotient.
- **Fredman-Komlós-Szemerédi 1984** (cited): FKS perfect hashing.
- **Belazzougui-Botelho-Dietzfelbinger 2009** (cited): CHD, MPHF.
- **Esposito-Mueller-Vigna 2020** (in bib, NOT cited): RecSplit. The construction the paper's evaluation paragraph names but doesn't cite. This is an active error.
- **Pibiri-Trani 2021**, **Limasset-Rizk-Chikhi 2017**: more recent MPHF benchmarks. Less critical.

### 4. Garbled circuits, FHE, ORAM
- **Yao 1982**, **Gentry 2009**, **Goldreich-Ostrovsky 1996** (all cited).
- **Bellare-Rogaway 1993** (cited): ROM.
- **Asharov-Naor-Segev-Shahaf 2016**: optimal ORAM lower bounds, could position cipher maps' "no-protocol" advantage.

### 5. Honey encryption and decoy-based privacy
- **Juels-Ristenpart 2014** (cited).
- **Tyagi-Wang-Wen-Zappala 2018** ("Honey Chatting"): broader honey-style. Optional.

## Direct competitors / overlapping claims

### A. The "frequency-hiding via Shannon-optimal acceptance partition" claim
**Closest predecessor**: Kerschbaum's frequency-hiding OPE (2015). Kerschbaum hides frequency by injecting random ranks on duplicate inserts. Cipher maps hide frequency by allocating hash-space partition widths $\alpha(y) \propto p_y$. These are different mechanisms, but both attack frequency analysis, and the omission of citation is conspicuous given the paper now leans hard on the frequency-hiding angle.

**Action**: cipher-maps must cite Kerschbaum 2015 with a one-sentence contrast, of the form "Kerschbaum hides frequency by random rank injection in OPE; we hide it by partition shaping in the acceptance predicate, exploiting that Shannon-optimal allocation already matches output distribution."

### B. The QIF positioning
The paper adopts smith2009foundations + alvim2012measuring as positioning. This is correct but one-sided. Smith's framework uses **min-entropy leakage** (one-try guessing advantage) as the canonical operational measure, while cipher-maps uses **Shannon entropy** for the entropy ratio. The Shannon-vs-min-entropy distinction is a fault line in QIF; the paper should at least acknowledge it (the sister paper does, in §4 of maximizing-confidentiality).

### C. The "totality eliminates access-pattern attacks" claim
The paper's §2 (Related Work, leakage-abuse paragraph) frames totality as eliminating in-domain vs out-of-domain signal. This is exactly what Kamara-Moataz 2019 "computationally volume-hiding STE" does, but with simulation-based machinery rather than totality. The paper has Kamara-Moataz in its bib but never cites it. This is also conspicuous given that the abstract opens by listing ORAM/FHE/garbled circuits as the comparison baselines. Kamara-Moataz is in the same regime and a natural fourth comparator.

### D. Theorem 6.2 (space optimality) vs. minimal perfect hash literature
Belazzougui et al. 2009 achieves $1.83$ bits per element for MPHF. Cipher maps achieve $-\log_2 \varepsilon + H(Y)$ bits/element. The relationship: when $Y = \{1, \ldots, n\}$ (the MPHF case), $H(Y) = \log_2 n$ and the cipher map bound becomes $-\log_2 \varepsilon + \log_2 n$. Setting $\varepsilon = 1$ (no rejection) recovers the MPHF cost up to constants. This connection is asserted in §2 ("a perfect hash function with a different optimization target") but never made precise.

**Action**: a one-sentence formal correspondence theorem would help, of the form "When $\varepsilon = 1$ and $Y$ is the index set, the entropy cipher map reduces to a minimal perfect hash function in the sense of Belazzougui et al. [...]."

### E. The deniability proposition (Bayesian, §9.4)
This is a textbook Bayes-rule application. The framing is fine, but identical results appear in:
- Differential privacy literature on randomized response (Warner 1965, currently uncited and probably should be).
- The honey encryption paper (juels2014honey, cited).

The paper presents this as if it's a result; it's a basic posterior calculation. This is a *novelty/significance* concern more than a correctness concern.

## Gaps and risks specific to PoPETs survival

### Unpublished sister-paper risk
Three "Manuscript in preparation" entries:
- towell2026maxconf (Theorem 4.3 cited as load-bearing)
- towell2026rekeying (Theorem 7.1 cited)
- towell2026algebraic (algebraic cipher types)

A PoPETs reviewer who follows the citation to verify Proposition 5.1 will find an unpublished manuscript. The user mentions Zenodo DOI plans. This is necessary minimum but a Zenodo DOI does not establish peer review. Stronger: arXiv preprint with permanent timestamp.

### The "QIF positioning" is correct but thin
Two citations (Smith 2009, Alvim 2012) plus Dodis-Smith do not constitute a QIF program; they constitute three pointers to a literature. PoPETs reviewers expert in QIF will notice the absence of:
- The min-entropy leakage tradition (Köpf-Smith 2010).
- The g-leakage operational interpretations (Alvim et al. 2014, 2016).
- Recent QIF + crypto bridges (Backes-Berg-Köpf 2011 on cache leakage, Smith 2015 on the "rationality of leakage measures").

The bridge paragraph in §1 cites three foundational papers and waves at the rest. For PoPETs, this is acceptable but lean.

### MPHF literature comparison missing in evaluation
The §6.4 evaluation cites RecSplit (with no bibliography entry, see error A) at "700 docs/sec" and seed-search at "10 docs/sec". This is the only concrete construction-time number. It is not benchmarked against:
- CHD (belazzougui2009hash, cited): construction time and space.
- BBHash (Limasset-Rizk-Chikhi 2017, NOT cited): reference modern PHF baseline.
- Standard Bloom filter at the same FPR.

A PoPETs methodology reviewer will flag this immediately.

## Synthesis

The R5 restructure (QIF positioning + Proposition 5.1 + Operational Consequences) lands the cipher map clearly in the parameterized-leakage tradition. The literature support is correct but uneven. Kerschbaum 2015 (most relevant frequency-hiding predecessor) is in the bib but uncited, RecSplit is mentioned but uncited, Kamara-Moataz volume-hiding SE (most relevant totality analogue) is in the bib but uncited. These are all already-fixed-by-having-the-bib problems, where an editorial pass to drop in citations and a sentence each would close them.

The deeper literature concern is that the QIF positioning is currently thin enough that a QIF-expert reviewer will want more, at minimum a min-entropy/Shannon-entropy distinction acknowledged, ideally a Köpf-Smith citation.

The unpublished-sister-paper risk for Theorem 4.3 of maxconf and Theorem 7.1 (actually 6.1, see citation-verifier) of rekeying is real and not mitigatable by Zenodo alone. arXiv preprints are the floor.
