# Literature Context (Round 7, single-orchestrator synthesis)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Subagent dispatch was unavailable in this orchestrator session (consistent
with R5/R6). The orchestrator consolidated the literature context from
prior rounds (R5 2026-04-30, R6 2026-05-02) and updated for items
salient to the v3 thesis (framework-first, multi-instance, Pareto
frontier).

## Closest priors to the cipher-maps thesis

### Approximate-data-structure axis (claim subsumption #1)

- **Bloom 1970** (`bloom1970space`, cited): canonical AMQ. Subsumed by
  HashSet remark with `K(x) = 1`. Verified.
- **Fredman-Komlos-Szemerédi 1984** (`fredman1984storing`, cited):
  FKS perfect hashing. Cited at §2.
- **Belazzougui-Botelho-Dietzfelbinger 2009** (`belazzougui2009hash`,
  cited): minimal PHF (CHD). Cited at §2 and §6.4.
- **Esposito-Mueller Graf-Vigna 2020** (`esposito2020recsplit`, cited):
  RecSplit, closest engineering analogue used by the reference
  implementation. Cited at §6.4 line 1283 and §10.1 line 2260.
- **Bender et al. 2012 quotient** plus **Fan et al. 2014 cuckoo**: cited
  at §2 (cache locality, deletion).
- **Pibiri 2024 PTHash**, NOT cited but worth noting as a more recent
  MPHF that competes with RecSplit on construction time and lookup
  latency. Low-priority addition for FMT polish.

### Frequency-hiding, property-preserving axis (claim subsumption #2)

- **Kerschbaum 2015** (`kerschbaum2015frequency`, cited): frequency-hiding
  OPE, the closest mechanism analogue. Cited at §2 with explicit
  mechanism contrast (Kerschbaum randomizes duplicate ranks, cipher
  maps shape acceptance partition).
- **Kamara-Moataz 2019** (`kamara2019computationally`, cited):
  computationally volume-hiding STE. Cited at §2 as closest SSE-side
  analogue to totality.
- **Patel-Persiano-Yeo-Yung 2019** (volume-hiding STE, CCS 2019), NOT
  in bib, flagged R6, still missing. This is the information-theoretic
  volume-hiding work, the closest formal cousin to the cipher map's
  noise-floor approach. Recommend adding.
- **Boldyreva et al. 2009** (`boldyreva2009order`, cited).
- **Bellare-Boldyreva-O'Neill 2007** (`bellare2007deterministic`,
  cited).

### Encrypted-search axis (claim subsumption #3)

- **Curtmola et al. 2006** (`curtmola2006searchable`, cited).
- **Cash et al. 2013** (`cash2013highly`, cited): Boolean SSE.
- **Song-Wagner-Perrig 2000** (`song2000practical`, cited).

### Leakage-abuse, inference attacks

- **Islam-Kuzu-Kantarcioglu 2012** (`islam2012access`, cited).
- **Naveed-Kamara-Wright 2015** (`naveed2015inference`, cited).
- **Cash-Grubbs-Perry-Ristenpart 2015** (`cash2015leakage`, cited).
- **Pouliot-Wright 2016** (Kraken co-occurrence attack), NOT in bib,
  flagged R6. Low priority.
- **Grubbs et al. 2017** (snapshot attack on EDB), NOT in bib. Would
  be useful for the §2 leakage-abuse paragraph.

### Honey encryption, every-input-decodes

- **Juels-Ristenpart 2014** (`juels2014honey`, cited).
- **Jaeger-Ristenpart-Tang 2016** (cracking-resistant PW vaults via
  honey encryption), NOT in bib. Minor extension, cipher maps already
  cite the foundational work.

### Quantitative information flow, parameterized leakage

- **Smith 2009** (`smith2009foundations`, cited): foundations of QIF.
- **Alvim et al. 2012** (`alvim2012measuring`, cited): generalized
  gain functions.
- **Dodis-Smith 2005** (`dodis2005entropic`, cited): entropic security.
- **Köpf-Smith 2010** (min-entropy leakage), NOT in bib. Flagged R6
  as foundational for the measure choice. Cipher-maps now justifies
  Shannon vs min-entropy at §5.1 line 718-728, and could cite
  Köpf-Smith for the min-entropy contrast. Medium priority.
- **Alvim-Chatzikokolakis-McIver-Morgan-Palamidessi-Smith 2020** (*Science
  of Quantitative Information Flow* textbook), NOT in bib. Standard
  reference for the QIF tradition. Recommend adding for credibility.

### Multi-instance, shared-key composition (new in R7)

- **Bellare-Tessaro-Vardy 2012** (semantic security for the wiretap
  channel), relates information-theoretic security under repeated
  use, somewhat analogous to the multi-instance question.
- **Geng-Smith 2025** (multi-instance security for entropic primitives),
  recent line on what happens when a primitive is reused. The cipher
  maps multi-instance claim sits in the same intellectual territory and
  would benefit from acknowledging this neighbor. NOT in bib. Medium
  priority.
- **Boyle-Lavigne-Vaikuntanathan 2017** (adaptive vs static
  multi-instance security), broader crypto multi-instance literature.
  NOT in bib, low priority.
- **Geng-Smith 2023, Cherubin-Chatzikokolakis-Palamidessi**, QIF-side
  work on attacker accuracy after many observations. Adjacent to the
  Le Cam bound plus multi-instance results. NOT in bib, medium priority.

### Coding theory background for the (TV, L) Pareto frontier

- **Huffman 1952**, NOT in bib. Surprising omission given that the
  paper centers Huffman codes in its acceptance-predicate apparatus
  and contrasts them with TV-optimal partitions. Strong recommend.
- **Cover-Thomas 2006** (*Elements of Information Theory*), NOT in
  bib. Standard reference. Shannon source coding is cited via
  `shannon1948mathematical`, but the Kraft inequality and integer
  codeword constraints discussion in §10.6 could lean on a textbook
  reference for clarity. Medium priority.
- **Shannon 1948** (`shannon1948mathematical`, cited).
- **Le Cam 1986** (`lecam1986asymptotic`, cited): two-point lemma.

### Sister-paper deferrals

- **`towell2026maxconf`** (`towell2026maxconf`, cited): "Manuscript in
  preparation". Theorem 4.1 part 3 (Fannes-Audenaert bound) is the
  load-bearing dependency. Round 6 verified cite chain. Preprint
  posting still pending.
- **`towell2026rekeying`** (`towell2026rekeying`, cited): "Manuscript in
  preparation". Theorem 7.1 (chain confidentiality bound) is the
  load-bearing dependency. Round 6 verified cite chain. Preprint
  posting still pending.
- **`towell2026algebraic`** (`towell2026algebraic`, cited at §10.3 line
  2375 only): NEWLY USED in this round for the noise-floor mechanism
  discussion. Previously unused (the R6 minor backlog had
  "CITE-N1: cite or remove", now resolved).
- **`towell2026codec`** (`towell2026codec`, cited at §10.6 line 2467):
  experiment suite, listed as `@misc` with URL to bernoulli
  repository. Appropriate for a companion experiment suite.

### What the literature scouting did NOT surface

No new direct competitors to the cipher-maps abstraction itself. The
framework remains a synthesis across three previously-disconnected
literatures rather than a competitor to any single existing approach.
The novelty arc is solid, and the gaps are in positioning citations
(QIF textbook, Huffman, Pouliot-Wright, Patel-Persiano-Yeo-Yung) rather
than in technical competition.

## Implications for Round 7 review

- The framework contribution (v3 thesis #1) is well-positioned against
  the literature scouted in R5/R6.
- The (TV, L) Pareto frontier (v3 thesis #2) needs a Huffman 1952
  citation to be properly grounded.
- The multi-instance composition theorem (v3 thesis #3) needs at least
  one QIF multi-instance citation (Geng-Smith 2025, or equivalent).
- The empirical Le Cam tightness (v3 thesis #4) is supported by the
  existing literature (Smith 2009, Le Cam 1986).
- The three-literature unification (v3 thesis #5) is well-positioned.
  Add Patel-Persiano-Yeo-Yung as the strongest missing volume-hiding
  cite.
