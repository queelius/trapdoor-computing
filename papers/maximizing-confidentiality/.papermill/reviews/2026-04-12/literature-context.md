# Literature Context (Merged)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing" by Alexander Towell
**Date**: 2026-04-12
**Sources**: Prior round scout output (2026-04-09) updated against current manuscript; area chair verification against manuscript

---

## Context note

The Task-dispatched scouts could not be launched in this environment.
The following context is distilled from (a) the 2026-04-09 scout output
(archived at `.papermill/reviews/2026-04-09/literature-context.md`) and
(b) direct verification against the 2026-04-12 manuscript. 2024 to 2026
items are limited to those known to the area chair; a fresh targeted
search may surface additional work.

---

## 1. Resolution of 2026-04-09 "Priority Missing" list

| Prior priority | Reference | Status in 2026-04-12 manuscript |
|---|---|---|
| HIGH | Smith 2009 | **Cited in §2** (smith2009foundations) |
| HIGH | Alvim et al. 2020 | **Cited in §2** (alvim2020science) |
| MEDIUM | Bost and Fouque 2017 | **Cited in §2** (bost2017thwarting; venue may need verification, see citation-verifier) |
| MEDIUM | Demertzis et al. 2020 | **Cited in §2** (demertzis2020seal) |
| HIGH | Oya and Kerschbaum 2021 | **Not cited** |
| MEDIUM | Bellare, Boldyreva, O'Neill 2007 | Not cited |
| MEDIUM | Dodis and Smith 2005 | Not cited |
| MEDIUM | Fuller et al. 2017 (SoK) | Not cited |
| LOW | Blackstone et al. 2020 | Not cited |
| LOW | Kamara and Moataz 2019 | Not cited |
| LOW | Cachin 1997 | Not cited |

Net: the three highest-priority gaps (Smith, Alvim, Oya-Kerschbaum)
are two-thirds resolved. Oya-Kerschbaum 2021 remains a gap
(search-pattern leakage is directly relevant to §6 compositional
leakage).

---

## 2. New concerns surfaced by the refined thesis

The refined thesis (2026-04-12) narrowed the novelty claim to two
items: (1) the Pinsker bridge from representation uniformity $\delta$
to entropy ratio $e$, and (2) the compositional leakage theorem. This
narrowing requires checking for prior art on these *specific* items.

### 2.1 Pinsker bridges for cryptographic distinguishability

Pinsker's inequality bridging total-variation to KL-divergence is a
workhorse in cryptography for translating game-based security
(distinguishing advantage, TV-close) to information-theoretic leakage
(KL or Shannon). Known applications:

- **Sahai and Vadhan 2003** (JACM). Use of statistical distance
  (= TV) and KL in zero-knowledge.
- **Dodis, Ostrovsky, Reyzin, Smith 2008** (fuzzy extractors, SIAM J
  Computing). Statistical distance versus min-entropy loss.
- **Vadhan 2012** textbook *Pseudorandomness*. Chapter 4 discusses
  statistical distance and its relation to entropy loss for
  distinguishers.

None of these formulate the bridge as "$\delta$-uniform
representation implies $e \geq 1 - 2\delta^2/n$" in the specific
cipher-maps/trapdoor-computing context. The *framing* is
novel to this paper; the *inequality* is textbook. Given the
logic-checker's finding that the direction of Pinsker is misapplied,
the practical bound in the paper should be Fannes-type, and
Fannes-type bounds are also well-known (Fannes 1973, Audenaert 2007,
Petz 2008).

### 2.2 Compositional leakage from shared variables in encrypted computation

The specific compositional statement "marginal $\delta$-uniform cipher
maps leak the joint distribution when evaluated on shared cipher
values, at rate $O(|Y_1||Y_2|/\xi^2)$" connects to several existing
research threads:

- **Kellaris, Kollios, Nissim, O'Neill 2016** (CCS). Generic attacks
  from access patterns. Shows that systems with uniform individual
  query responses still leak the joint structure of query sets. The
  spirit matches Theorem 6.1 but the adversary model differs.
- **Grubbs, McPherson, Naveed, Ristenpart, Shmatikov 2016** (CCS).
  Encrypted DB leakage from joint structure (query graphs).
- **Grubbs et al. 2017** (HotOS). "Why your encrypted database is
  not secure": general argument that joint leakage kills encrypted
  databases.
- **Cash, Grubbs, Perry, Ristenpart 2015** (CCS, *cited already*).
  Leakage-abuse attacks demonstrating joint leakage in SSE.
- **Oya and Kerschbaum 2021** (USENIX Security). Search-pattern
  leakage survives access-pattern hiding. Directly relevant to the
  "marginal-not-enough" claim.

None of these papers state the quantitative rate
$O(|Y_1||Y_2|/\xi^2)$ in the specific cipher-map trapdoor setting.
The paper's contribution is the *quantitative* bound within the
cipher-maps framework; the *spirit* (marginal uniformity is
insufficient) is established in the SSE attack literature.

**Recommendation**: §2 Related Work should add a paragraph citing
the SSE joint-leakage thread (Kellaris et al. 2016; Cash et al. 2015
already cited elsewhere in bib but not in text; Oya and Kerschbaum
2021). The paper should position Thm 6.1 as the *information-theoretic
quantitative counterpart* of these access-pattern attack results, not
as a wholly new observation.

---

## 3. 2024 to 2026 work likely relevant (area-chair list)

The following 2024 to 2026 work is likely relevant but could not be
scout-verified. The area chair's awareness (not exhaustive):

### 3.1 Quantitative information flow

- Ongoing work by Alvim and co-authors on quantitative risk in
  machine learning models and LLM prompt leakage (2023 to 2025).
- Bordenabe, Palamidessi and others on g-leakage for adaptive
  adversaries (continuing from the 2020 monograph).
- Work extending QIF to differentially-private mechanisms; overlap
  with but not identical to the cipher-maps setting.

### 3.2 SSE leakage and defenses

- Continued work on volume-hiding SSE (Kamara-Moataz school),
  often via structured encryption tricks.
- Recent (2023 to 2025) forward-secure SSE schemes with
  quantified leakage profiles, typically cast in simulation-based
  security rather than entropy-ratio terms.

### 3.3 Trapdoor / total-function-style constructions

- The cipher-maps framework itself (towell2026cipher) is the most
  direct relative; no other 2024 to 2026 work adopts the specific
  "total function on bit strings" formalism with four properties
  $(\eta, \varepsilon, \delta, \mu)$.
- Adjacent work on homomorphic filters, approximate MPC, and
  lossy encryption has related flavor but different security
  models.

### 3.4 Approximate secure computation

- Dwork, Rothblum and others on approximate differential privacy
  (continuing stream).
- Indyk and collaborators on approximate nearest-neighbor secure
  computation.

None of the above (to the area chair's knowledge) provides a
Pinsker-style bridge from marginal uniformity to Shannon leakage in a
cryptographic setting, so the paper's specific framing remains
distinctive even though its mathematical content is textbook.

---

## 4. Benchmark context (carry-over)

**20 Newsgroups is still not a standard encrypted search benchmark.**
Standard benchmarks for SSE papers are Enron email, Wikipedia dumps,
and synthetic Zipf data. 20 Newsgroups is commonly used in text
classification, not encrypted search.

The paper could justify 20 Newsgroups as a small, well-understood
corpus suitable for validating theoretical predictions rather than
benchmarking system performance. The 2026-04-09 review suggested
this and it has not been addressed in the 2026-04-12 revision.

**Recommendation**: Add one sentence in §8 header (line 957 to 960)
justifying the corpus choice.

---

## 5. Assessment of novelty claims against current prior art

| Claim | 2026-04-12 framing | Prior art | Assessment |
|---|---|---|---|
| Entropy ratio = H/H* | Explicitly conceded to QIF | Smith 2009, Alvim 2020 (cited) | **Honest, no over-claim** |
| Pinsker bridge $\delta \to e$ | Headline | Pinsker 1964, Fannes 1973 (not cited); QIF uses Pinsker-like bridges; the specific *cipher-map framing* is new | **Framing novelty; proof error per logic-checker** |
| Noise injection analysis | "Two constructions, we analyze" | Bost and Fouque 2017 (cited); Chen, Papamanthou, Kellaris 2018 (not cited); DP noise is classical | **Packaging novelty; technique inherited** |
| Multiple representations (homophonic) | "Two constructions, we analyze" | Simmons 1979 (in bib, NOT cited in text) | **Simmons cite gap per citation-verifier; construction stated backwards per logic-checker** |
| Encoding granularity | Explicitly inherited from companion | towell2026cipher Prop 9.1 (cited) | **Honest, no over-claim** |
| Compositional leakage | Headline | Kellaris et al. 2016 (not cited), Oya and Kerschbaum 2021 (not cited); SSE attack literature | **Quantitative bound is novel in cipher-maps framing; spirit is established** |
| FPR compounding | Explicitly inherited | towell2026cipher Sec 8; Bloom 1970 (not cited) for set-oriented precedent | **Honest, no over-claim** |

Net assessment: the refined thesis is honest; the remaining gaps are
missing related-work threads (SSE joint leakage; Oya and Kerschbaum
search pattern) and missing classical citations (Simmons, Pinsker,
Fannes).

---

## 6. Recommendations

1. **Add SSE joint-leakage paragraph to §2**: one paragraph citing
   Kellaris et al. 2016, Oya and Kerschbaum 2021, and the existing
   Cash et al. 2015 entry (bring it into the text).
2. **Cite Simmons 1979 in §5.2 and Example 5**: per citation-verifier.
3. **Justify 20 Newsgroups choice in §8**: one sentence.
4. **Explicit Pinsker/Fannes citations in §4.3**: cite Cover and Thomas
   2006 §11.6 (Pinsker) and the primary Fannes reference if the proof
   is rewritten via Fannes (per logic-checker).
5. **Position Thm 6.1 against the SSE joint-leakage thread**: one
   sentence in §6 or §2 explaining what is *quantitatively new* (the
   specific bound) versus *conceptually established* (the attack
   class).

These five additions are low-cost and would strengthen the paper's
defensibility at any theory venue.
