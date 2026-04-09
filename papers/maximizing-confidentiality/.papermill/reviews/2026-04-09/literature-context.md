# Literature Context (Merged)

**Paper**: "Quantitative Confidentiality for Cipher Maps" by Alexander Towell
**Date**: 2026-04-09
**Sources**: Broad field survey + targeted direct comparisons

---

## 1. Competing Approaches for Quantifying Leakage

### 1.1 Leakage Functions / Leakage Profiles (SSE Standard)

The dominant approach in SSE literature defines security via leakage functions L that enumerate exactly what an adversary learns:

- **Curtmola et al. (2006)**: CCS. Introduced L-security simulation paradigm for SSE. *Already cited.*
- **Chase & Kamara (2010)**: ASIACRYPT. Extended leakage functions to structured encryption. *Missing.*
- **Kamara & Moataz (2019)**: EUROCRYPT. Volume-hiding structured encryption. *Missing.*
- **Fuller et al. (2017)**: IEEE S&P. SoK on cryptographically protected database search. *Missing.*

### 1.2 Quantitative Information Flow (QIF)

A mature research area measuring information leakage in bits, directly comparable to the entropy ratio:

- **Smith (2009)**: FoSSaCS. Min-entropy leakage foundations. *CRITICAL missing reference.*
- **Alvim et al. (2012)**: CSF. Generalized gain functions for leakage. *Missing.*
- **Alvim et al. (2020)**: Springer monograph, "The Science of QIF." *Important missing reference.*
- **Braun, Chatzikokolakis, Palamidessi (2009)**: MFPS. Compares Shannon vs. min-entropy leakage. *Missing.*
- **Chatzikokolakis, Palamidessi, Panangaden (2008)**: Journal of Computer Security. Shannon/min-entropy for information hiding. *Missing.*
- **Kopf & Basin (2007)**: CCS. Shannon entropy for adaptive side-channel attacks. *Missing.*

### 1.3 Information-Theoretic Crypto Measures

- **Dodis & Smith (2005)**: TCC. Entropic security for high-entropy messages. *Missing.*
- **Bellare, Boldyreva, O'Neill (2007)**: CRYPTO. Min-entropy security for deterministic encryption. *Missing.*
- **Cachin (1997)**: ETH PhD thesis. Entropy measures and unconditional security. *Missing.*
- **Massey (1994)**: IEEE ISIT. Guessing and entropy connection. *Missing.*

### 1.4 Differential Privacy

- **Dwork (2006)**: ICALP. Different model (worst-case per-record) but widely expected as comparison point.

## 2. SSE Attack Literature (Post-2015, Missing)

- **Oya & Kerschbaum (2021)**: USENIX Security. Search pattern leakage persists even with access pattern hiding. *Important missing reference -- directly relevant to cipher map representation uniformity.*
- **Blackstone, Kamara, Moataz (2020)**: NDSS. Systematizes attack assumptions.
- **Gui, Johnson, Stange (2019)**: CCS. Volume attacks against range queries.
- **Kornaropoulos et al. (2021)**: IEEE S&P. Parametric leakage-abuse attacks.

## 3. Leakage Suppression (Direct Parallels to Three Levers)

- **Bost & Fouque (2017)**: CCS. Dummy queries for SSE -- directly comparable to noise injection lever. *Missing.*
- **Demertzis et al. (2020)**: USENIX Security. SEAL: tunable leakage-functionality trade-off. *Missing.*
- **Chen, Papamanthou, Kellaris (2018)**: INFOCOM. DP-based query noise for SSE. *Missing.*

## 4. Field Positioning Assessment

The paper occupies an unusual niche:
- NOT simulation-based (mainstream SSE approach)
- NOT differential privacy
- IS information-theoretic, using Shannon entropy (not min-entropy)
- Applies to a specific construction (cipher maps) rather than general encrypted search

This makes it **orthogonal** to most SSE literature. Closest relatives:
1. Quantitative Information Flow (Smith 2009, Alvim et al.)
2. Entropic security (Dodis & Smith 2005)
3. Leakage quantification subfield of SSE

**Key gap**: The paper positions only against ORAM/FHE/simulation-based. It must also position against QIF and entropic security.

## 5. Benchmark Context

**20 Newsgroups is NOT a standard encrypted search benchmark.** Standard SSE benchmarks:
- Enron email corpus (most common in SSE literature)
- Wikipedia dumps
- Synthetic datasets with controlled distributions

20 Newsgroups is defensible for proof-of-concept but should be justified.

## 6. Overlapping Claims Assessment

| Claim | Novelty | Prior art |
|-------|---------|-----------|
| Entropy ratio as confidentiality measure | Moderate -- normalized Shannon leakage from QIF applied to cipher maps | Smith (2009), Cachin (1997), Kopf & Basin (2007) |
| Three levers | Individual techniques known; packaging as unified framework is novel | Bost & Fouque (2017), Simmons (1979), Chase & Kamara (2010) |
| FPR compounding | Standard probabilistic analysis; connection to confidentiality is novel | Standard probability theory |
| Encoding granularity spectrum | **Genuinely novel** as formal framework | No direct prior work with this lens |
| Compression-based entropy estimation | Well-known technique; application to cipher maps is new | Ziv & Merhav (1993), source coding theorem |

## 7. Priority Missing References

| Priority | Reference | Reason |
|----------|-----------|--------|
| HIGH | Smith (2009) | Entropy ratio is a QIF measure; must engage |
| HIGH | Alvim et al. (2020) | Comprehensive QIF monograph |
| HIGH | Oya & Kerschbaum (2021) | Search pattern leakage directly relevant |
| MEDIUM | Bost & Fouque (2017) | Direct competitor for noise injection |
| MEDIUM | Demertzis et al. (2020) | Tunable leakage trade-off parallel |
| MEDIUM | Bellare, Boldyreva, O'Neill (2007) | Entropy-based deterministic encryption security |
| MEDIUM | Dodis & Smith (2005) | Entropic security |
| MEDIUM | Fuller et al. (2017) | SoK for encrypted database search |
| LOW | Blackstone et al. (2020) | Systematizes attack assumptions |
| LOW | Kamara & Moataz (2019) | Volume hiding |
| LOW | Cachin (1997) | Foundational |

## 8. Bibliographic Issues Found

- **grubbs2018pump**: Venue listed as "Proceedings of the ACM on Management of Data" -- should be corrected with volume, pages, or proper conference name.
