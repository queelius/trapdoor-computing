# Literature Context Packet, Round 8 (2026-05-27)

This packet merges the broad-survey and targeted-comparison views of
prior art relevant to the cipher maps paper. It is intended to anchor
the specialist reviews against the wider literature and to flag
direct comparison points the paper either makes or should make.

## 1. Field landscape (broad scout)

Cipher maps sit at a four-way intersection.

### Approximate membership data structures

Cited: Bloom (1970), Cuckoo filters (Fan et al. 2014), Quotient
filters (Bender et al. 2012), RecSplit (Esposito et al. 2020). The
HashSet instance subsumes Bloom at eta = 0.

Missing comparison: Xor filters (Graf and Lemire 2020,
CoRR abs/1912.08258) and Ribbon filters (Dillinger and Walzer 2021)
achieve below-Bloom space and are the strong modern baseline for any
approximate-membership space claim. The E1 Bloom-baseline result
(4.5x practical, 1.07x theoretical asymptote) would land more
convincingly against Xor or Ribbon as a third row.

### Frequency-hiding and property-preserving encryption

Cited: OPE (Agrawal et al. 2004, Boldyreva et al. 2009),
deterministic encryption (Bellare et al. 2007), frequency-hiding OPE
(Kerschbaum 2015).

Closest active research thread: format-preserving encryption
(Bellare-Ristenpart-Rogaway-Stegers 2009), which has the same
totality flavor (every input produces output of the right format) but
is exact and lacks representation-uniformity reasoning. Worth a
one-paragraph contrast at section 2.

### Searchable symmetric encryption and leakage-abuse

Cited: Song-Wagner-Perrig 2000, Curtmola et al. 2006, Cash et al.
2013, Naveed et al. 2015, Islam et al. 2012, Cash et al. 2015.

Volume-hiding STE: Kamara-Moataz 2019 cited. Patel-Persiano-Yeo-Yung
2019 (an alternative volume-hiding construction with explicit leakage
profile) still not cited despite being the most directly comparable
PoPETs-area work. R6 and R7 carry-over.

Pouliot-Wright 2016 (Kraken co-occurrence attack) is the canonical
reference for cross-query correlation attacks discussed informally at
section 8.2 (compositional leakage). Still uncited.

### Quantitative information flow and entropic security

Cited: Smith 2009, Alvim et al. 2012, Dodis-Smith 2005.

Alvim-Chatzikokolakis-McIver-Morgan-Palamidessi-Smith 2020 (Springer
textbook, *The Science of Quantitative Information Flow*) is the
current standard reference for the entropy-ratio framing and should
back the "QIF tradition" claim in the abstract and section 1. Still
uncited.

Köpf-Smith 2010 (min-entropy leakage in side-channel analysis) is the
obvious comparison for the Shannon-vs-min-entropy choice the paper
makes at section 5.1. Still uncited.

### Information-theoretic coding background

Huffman 1952 ("A Method for the Construction of Minimum-Redundancy
Codes"): the paper centers Huffman codes in sections 6, 8.3, and
10.6 but does not cite the original paper. R7 CITE-2 carry-over.

Cover-Thomas 2006 (*Elements of Information Theory*): the standard
reference for Kraft's inequality (invoked implicitly at section 10.6
in the Pareto frontier paragraph) and Shannon's source coding theorem
(cited only via shannon1948mathematical). Add as textbook reference
at sections 6.1 and 10.6.

### Multi-instance composition in QIF

The coincidence-oracle bound (Theorem 8.1) is in the spirit of
Geng-Smith 2014 ("A coupling argument for the random assignment
problem" and related QIF work) on multi-trial amplification, and of
Cherubin et al. 2019 ("F-BLEAU"-style iterated-attacker analysis).
Neither cited. The paper would benefit from one paragraph positioning
section 8.3 as the QIF-style multi-instance amplification for cipher-map
deployments.

## 2. Direct comparison points (targeted scout)

### Same problem, same techniques

**Bloom filter as cipher map (Remark 7.1, section 10.3).** The
HashSet/Bloom relation is well-stated. The Bloom-baseline experiment
(E1) is the right kind of comparison. Missing comparisons are Xor and
Ribbon (see above). The "4.5x practical, 1.07x theoretical"
decomposition is honest and well-supported by e1/results.csv.

**Frequency-hiding via partition shaping (section 6.2, section 10.6).**
Kerschbaum 2015 is the closest active line. The contrast paragraph at
section 2 lines 246 to 259 is the right framing: Kerschbaum
randomizes per-insert ranks to flatten frequency-of-rank, while
cipher maps shape alpha(y) proportional to p_y to flatten
frequency-of-decoded-value. Different mechanism, same threat
(frequency analysis on encrypted records). Adequate.

**Homophonic substitution (section 2 lines 314 to 327, section 4.2
lines 521 to 525).** This is the load-bearing classical reference for
the multiplicity mechanism K(x) > 1. Today's commit (41210a8)
correctly fixed the K(x) proportional to D(x) direction: frequent
values get more representations, not fewer ("more representations to
frequent values so that each cipher representation is queried with
equal expected frequency"). Cross-checked all four sites flagged
(lines 318 to 327 Related Work, lines 504 to 525 Definition 4.2 plus
post-prose, lines 642 to 644 Table 4.1, line 788 Remark 5.x).
Direction now consistent. The Simmons 1979 citation is appropriate.
A modern reference (Massey 1988 "An introduction to contemporary
cryptology" section V, or Stinson 2005 *Cryptography: Theory and
Practice* section 2.4) could be added.

### Same problem, different techniques

**Garbled circuits (Yao 1982).** Cited. The "static lookup table vs
per-gate encryption" contrast at section 2 lines 303 to 312 is
adequate. The deeper structural parallel (garbled circuits also use
total functions on cipher labels) is not drawn out. Worth one
paragraph at section 2 or section 9.5.

**FHE (Gentry 2009).** Cited. The "exact algebra vs approximate
trapdoor" contrast is adequate but generic. A more specific contrast
to CKKS (Cheon-Kim-Kim-Song 2017), the approximate-FHE scheme that
explicitly trades precision for performance, would sharpen the
"approximation as a design dimension" framing in section 1. Not
blocking.

**ORAM (Goldreich-Ostrovsky 1996).** Cited. The "access patterns vs
value frequencies" contrast at section 1 and section 9.5 is clear.

**Randomized response (Warner 1965).** Cited as the deniability
mechanism (section 10.4). The connection to differential privacy
(Dwork-McSherry-Nissim-Smith 2006) is the natural follow-up cite, but
the paper explicitly says "Not differential privacy" at section 9.5,
so this is appropriate restraint.

### Concurrent work on Pareto frontiers in coding and leakage

**Issa-Wagner-Kamath 2020** ("An operational approach to information
leakage", IEEE TIT) develops an operational leakage measure (the
maximal-leakage measure) with a Pareto structure closely related to
the (TV, L) frontier reported in section 10.6. The frontier the paper
reports is in a different metric space (TV instead of maximal
leakage), but the methodology, that is, enumerate all Kraft-feasible
length assignments and compute Pareto-optimal points, is similar. A
one-sentence forward reference would be helpful, even without
changing the analysis.

**Saraf-Smith 2024** (or any 2024 QIF compendium with multi-trial
amplification) is a natural anchor for section 8.3.

## 3. Modern context for the section 8.3 multi-instance contribution

The coincidence oracle and randomized-encoding defense (section 8.3,
Theorem 8.1, Proposition 8.2) are the most novel single section of
the paper. The closest prior work:

- **Naveed-Kamara-Wright 2015** (frequency attacks on PPE): these are
  single-instance frequency attacks. The section 8.3 work is the
  multi-instance analogue on cipher maps. The proper framing is
  "what Naveed et al did for single-instance PPE, we do for multi-
  instance cipher maps under independent seeds."

- **Kellaris-Kollios-Nissim-O'Neill 2016** ("Generic attacks on
  secure outsourced databases"): multi-query attacks on range and
  SSE. The closest published precedent for "attacker observing t
  snapshots of a structure under the same latent function." Not
  cited. Should be added at section 8.3 as the prior
  multi-query/multi-snapshot baseline.

- **Cash-Grubbs-Perry-Ristenpart 2015** (cited): multi-document
  query-recovery attacks. Connection to section 8.3's "t cipher maps
  for the same f" is clear but unstated.

## 4. Recommendations for the citation-verifier

Strong adds (paper is materially weaker without these):

- Huffman 1952 (R7 carry-over, paper centers Huffman codes)
- Patel-Persiano-Yeo-Yung 2019 (R6 and R7 carry-over, closest STE work)
- Kellaris-Kollios-Nissim-O'Neill 2016 (multi-snapshot attacks)
- Köpf-Smith 2010 (Shannon vs min-entropy comparison at section 5.1)
- Alvim et al 2020 (current QIF textbook)
- Cover-Thomas 2006 (Kraft inequality reference at section 10.6)

Should-have:

- Pouliot-Wright 2016 (cross-query correlation, section 8.2)
- Geng-Smith 2014 or equivalent QIF multi-instance work (section 8.3)
- Xor filter (Graf-Lemire 2020) and Ribbon (Dillinger-Walzer 2021)
  for section 10.3 Bloom baseline comparison

Nice-to-have:

- Issa-Wagner-Kamath 2020 (operational leakage, section 10.6)
- CKKS reference at section 2 FHE paragraph
- Format-preserving encryption (Bellare-Ristenpart-Rogaway-Stegers
  2009) at section 2

## 5. Notable papers NOT to cite that orchestrator scouts checked

- ORAM hardware constructions (Path ORAM, Ring ORAM, etc.). The paper
  is explicit at section 1 and section 9.5 that it is not in this
  design space.
- DP literature (Dwork et al., Kifer-Lin, etc.). The paper is
  explicit at section 9.5 that it is not differentially private.
  Restraint correct.
- Garbled-circuit constructions beyond Yao 1982 (Bellare-Hoang-Rogaway
  2012, Yakoubov 2017 surveys). Generic constructions, not
  load-bearing for this paper.
- Lattice-based PPE (e.g., Lewi-Wu 2016 OPE). Narrow line, not the
  cipher map framing.
- ChaCha-Poly1305 and AEAD literature. Wrong abstraction layer.
