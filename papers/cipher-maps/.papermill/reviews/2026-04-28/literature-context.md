# Literature Context Packet, cipher-maps Round 4

**Date**: 2026-04-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Bibliography**: 23 entries (was 19 in prior state file; cash2015leakage and juels2014honey added in this round)

This packet merges what a broad field survey and a targeted comparison survey would surface for this Round 4 review. The paper now engages with leakage-abuse attacks and honey encryption (M3 fix), but the literature still contains several prominent recent works that bear on cipher maps' positioning.

## 1. Closest direct competitors and overlapping claims

### 1.1 Frequency-hiding order-preserving encryption (Kerschbaum, CCS 2015)

Kerschbaum, "Frequency-Hiding Order-Preserving Encryption" (CCS 2015) is the closest published predecessor for the *frequency hiding* half of the paper's "Shannon-frequency duality" claim. Kerschbaum shows that an OPE scheme can be modified so frequencies of plaintexts do not match frequencies of ciphertexts, defeating the Naveed-Kamara-Wright attacks on the frequency channel.

- **Status in paper**: NOT cited.
- **Significance**: PoPETs reviewers in the SSE/PPE space know this paper. The cipher maps mechanism (multiple representations $K(x) \propto 1/D(x)$) is functionally similar to Kerschbaum's randomized assignment of order tokens. The paper would benefit from a one-sentence acknowledgment.
- **Action**: Add to Section 2 (Property-preserving encryption paragraph) or to the homophonic substitution paragraph. Kerschbaum's work is a modern instantiation of the same intuition the paper attributes to Simmons 1979.

### 1.2 Volume-hiding SSE (Kamara, Moataz, Ohrimenko / Patel et al.)

A line of work specifically targets attacks that exploit response-volume leakage:
- Patel, Persiano, Yeo, Yung, "Mitigating Leakage in Secure Cloud-Hosted Data Structures: Volume-Hiding for Multi-Maps via Hashing" (CCS 2019)
- Kamara & Moataz, "Computationally Volume-Hiding Structured Encryption" (EUROCRYPT 2019)

These papers explicitly engage with the leakage-abuse attacks (Cash-Grubbs et al. 2015; Blackstone-Kamara-Moataz 2020) and propose constructions that bound or eliminate volume leakage. The cipher maps approach (every input decodes; output frequency matches design distribution) achieves volume hiding "for free" via Shannon-optimal acceptance, but the paper does not position itself against these.

- **Status in paper**: NOT cited.
- **Significance**: For a PoPETs reviewer who works on SSE, the absence of these citations signals the author may not be tracking the SSE side of the literature.
- **Action**: Add at least one citation in the SSE paragraph, either Patel-Persiano-Yeo-Yung 2019 or Kamara-Moataz 2019, and note that cipher maps achieve marginal-frequency volume-hiding by construction.

### 1.3 Forward-private SSE (Bost, Minaud, Ohrimenko)

Bost, "Sigma-o-phi-o-s: Forward Secure Searchable Encryption" (CCS 2016) and Bost-Minaud-Ohrimenko "Forward and Backward Private Searchable Encryption from Constrained Cryptographic Primitives" (CCS 2017) are the standard SSE references for resisting injection-style attacks.

- **Status in paper**: NOT cited.
- **Significance**: Lower priority. The paper's threat model is static (no updates), so forward/backward privacy is orthogonal. But the paper's claim "cipher maps target the upstream causes of these attacks" is a strong claim that invites comparison to the SSE community's response, which is forward-private SSE.
- **Action**: Optional. If the paper claims structural resistance to leakage-abuse attacks, a sentence acknowledging that the SSE community has its own response (forward privacy) would be honest. Could be a single citation in the leakage-abuse-attacks paragraph.

### 1.4 Information-theoretic security via parameterized leakage

The paper rejects sim-based and game-based security in §9.5, claiming guarantees are "parameterized ($\delta$, $\varepsilon$) rather than negligible in a security parameter." This positions cipher maps as an information-theoretic primitive.

Closest published frameworks:
- **Entropic security**: Russell-Wang "How to Fool an Unbounded Adversary with a Short Key" (EUROCRYPT 2002); Dodis-Smith "Entropic Security and the Encryption of High Entropy Messages" (TCC 2005). These define security in terms of plaintext min-entropy rather than key length. The "$\delta$-close to uniform" condition in cipher maps is closely related to the entropic security framework.
- **Quantitative information flow (QIF)**: Smith "On the Foundations of Quantitative Information Flow" (FoSSaCS 2009); Alvim-Chatzikokolakis-Palamidessi-Smith "Measuring Information Leakage Using Generalized Gain Functions" (CSF 2012). The paper's sister paper "maximizing-confidentiality" cites QIF; this paper does not.
- **Differential privacy (rejected by author)**: While DP is not the right model, the *style* of parameterized leakage is. The TCC/PETS communities increasingly accept ($\delta, \varepsilon$)-style guarantees.

- **Status in paper**: NOT cited (entropic security or QIF). DP is mentioned and rejected.
- **Significance**: The paper says "we reject all standard frameworks" but does not say "here is the framework family our parameterization belongs to." Citing entropic security or QIF would give the parameterization a home in the literature.
- **Action**: Add one citation to entropic security (Dodis-Smith 2005) and one to QIF (Smith 2009 or Alvim et al. 2012) in §9.5 or in the Trust Model section. This costs two bib entries and a sentence; it lets the reviewer place the paper in a recognized tradition.

### 1.5 Honey encryption follow-ups

The paper now cites Juels-Ristenpart 2014. Notable follow-ups:
- Jaeger-Ristenpart-Tang "Honey Encryption Beyond Message Recovery Security" (EUROCRYPT 2016) extends to multi-message security.
- Tyagi-Wang-Wen-Zuo "Honey Encryption Applications" (CSF 2018) provides domain-specific applications.

- **Status in paper**: Only the original Juels-Ristenpart 2014 is cited.
- **Significance**: Low. The current discussion in the Honey Encryption paragraph (lines 194-209) is well-calibrated and doesn't need expansion. One Jaeger-Ristenpart-Tang reference would be courteous.

## 2. Acceptance-predicate framing and minimal perfect hashing

The paper claims "the entire batch construction reduces to a single design choice: an acceptance predicate." This is a unification claim about prior MPHF/PHF literature (Belazzougui-Botelho-Dietzfelbinger CHD 2009, RecSplit, PTHash). The paper cites belazzougui2009hash but not RecSplit or PTHash.

- Esposito, Müller, Pibiri, Venturini, "RecSplit: Minimal Perfect Hashing via Recursive Splitting" (ALENEX 2020).
- Pibiri & Trani, "PTHash: Revisiting FCH Minimal Perfect Hashing" (SIGIR 2021).
- Lehmann, Sanders, Walzer, "ShockHash: Minimal Perfect Hashing Beyond Brewer's Bound" (ESA 2023).

- **Status in paper**: One reference (belazzougui2009hash). RecSplit named in the experiments paragraph (line 934 says "RecSplit-family PHF") but not cited.
- **Significance**: Moderate. The paper claims acceptance predicate unification; a reviewer who works on PHFs will ask whether this framing actually unifies the recent constructions. RecSplit and PTHash are now the standard references; not citing them looks dated.
- **Action**: Add RecSplit (Esposito et al. 2020) and PTHash (Pibiri-Trani 2021) to the bib. Cite at least RecSplit where it is named in line 934. Optional: cite ShockHash (Lehmann-Sanders-Walzer 2023) as the current state of the art.

## 3. Compositional error in approximate primitives

The composition theorem $\eta_{\mathrm{total}} \leq 1 - \prod_i (1 - \eta_i)$ is presented as a standalone result. This formula appears in many places:
- Standard Bloom filter analyses for stacked / partitioned filters.
- Mitzenmacher's "Compressed Bloom filters" (Networking 2002) covers composition of false-positive rates.
- The author's own bernoulli-types work (cited).

- **Status**: Composition formula attributed to Bernoulli framework (cited). Inclusion-exclusion proof is standard.
- **Significance**: Low. Not a contested claim. But a one-sentence acknowledgment that this is the standard error-composition formula in approximate data structures (with citation to Mitzenmacher or analogous) would prevent a reviewer from thinking the paper claims novelty here.

## 4. PoPETs taste check

PoPETs typically expects:
- (a) A clear adversary model and security definition (sim-based, game-based, or information-theoretic with explicit leakage function).
- (b) Concrete instantiations with parameter choices.
- (c) Implementation and benchmarks against baselines.
- (d) Engagement with the relevant attack literature (now satisfied via M3 fix).
- (e) Reproducibility (artifact evaluation).

Recent PoPETs-style theory papers that succeeded with limited or no implementation:
- Backes et al. "Anonymous RAM" (ESORICS 2016) provides a formal model with security proofs.
- Fuller et al. "Reusable Fuzzy Extractors" (PETS 2020) has security definitions central.
- Patel-Persiano-Yeo-Yung "What Storage Access Privacy Is Achievable with Small Overhead?" (PoPETs 2019) develops formal lower bounds.

Common pattern: theory papers at PoPETs without experiments still have *formal security definitions*. The cipher maps paper currently has neither. This is the structural risk the prior review identified as M1+M2.

Recent PoPETs papers in the SSE/encrypted-search space:
- Falzon et al. "VSE: A Volume-hiding SSE Scheme" (PoPETs 2024).
- Dauterman et al. "Snoopy: Surpassing the Scalability Bottleneck of Oblivious Storage" (SOSP 2021).
- Kim, Lee, et al. (volume-hiding SSE).

The cipher maps paper does not engage with any of these. This is the strongest single signal that the literature footing for PoPETs is thin.

## 5. Concrete citation gaps to fix before submission

Ranked by importance:

**High priority** (visible to PoPETs reviewers, low cost to add):
1. Kerschbaum 2015 "Frequency-Hiding Order-Preserving Encryption", direct prior art for the frequency-hiding mechanism.
2. Patel-Persiano-Yeo-Yung 2019 (or Kamara-Moataz 2019), volume-hiding SSE.
3. Esposito et al. 2020 (RecSplit), already named in the text but uncited.

**Medium priority** (good for placing the paper in a tradition):
4. Dodis-Smith 2005 (Entropic security), for the parameterized-security framing in §9.5.
5. Smith 2009 or Alvim et al. 2012 (QIF), same purpose; consistent with the sister "maximizing-confidentiality" paper.
6. Pibiri-Trani 2021 (PTHash), current PHF state of the art.

**Low priority** (nice-to-have):
7. Bost-Minaud-Ohrimenko 2017 (forward-private SSE), for the leakage-abuse-attack response.
8. Mitzenmacher 2002 (compressed Bloom filters), for the composition formula's literature home.
9. Jaeger-Ristenpart-Tang 2016 (honey encryption follow-up), courtesy citation.

## 6. Honest assessment of the paper's standing in the literature

**Strengths in literature positioning**:
- The four-property framework is an original synthesis. No published paper presents totality + representation uniformity + correctness + composability as a unified framework.
- The "acceptance predicate" framing is a useful pedagogical reduction that does not appear in this exact form in the PHF or AMQ literature.
- The "Shannon-frequency duality" is a tight rhetorical formulation; while the underlying observation is implicit in entropy-coded cipher constructions, framing it as a duality is non-trivial and clean.

**Weaknesses in literature positioning** (beyond the M1/M2 issues already known):
- The paper's "what this is not" exclusions (§9.5) currently exclude all standard frameworks without giving reviewers a positive label. Entropic security or QIF would provide that label.
- The paper claims structural resistance to leakage-abuse attacks but does not engage with the SSE community's own recent responses (volume-hiding SSE, forward-private SSE). Reviewers from the SSE community may read this as the author being unaware.
- The paper names RecSplit in the text but does not cite it. Small but visible.

**Overall**: The literature engagement has improved in this round (M3). But three high-priority citations (Kerschbaum 2015, Patel-Persiano-Yeo-Yung 2019, Esposito et al. 2020) are essentially required for PoPETs and would each take less than 30 minutes to add.
