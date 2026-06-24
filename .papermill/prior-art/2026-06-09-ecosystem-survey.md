# Ecosystem Prior-Art Survey, Research Directions, and Saliency Assessment

**Date**: 2026-06-09
**Scope**: cipher-maps, maximizing-confidentiality (The Entropy Ratio), codec-controlled-retrieval; plus forward directions and a portfolio taste assessment.
**Method**: four parallel adversarial literature scouts (one targeted scout per paper, briefed with verbatim theses and instructed to find the paper that sinks each claim; one broad field-landscape scout across six themes). Every reference below was web-verified by the scouts this session unless marked UNVERIFIED. Full scout transcripts in the session record.

**One-paragraph summary**: All headline theorems survive adversarial review; none of the papers has a correctness problem. What the survey found instead is a consistent **claim-scoping gap**: each paper's strongest result is genuinely novel, but each paper currently also claims (or implies) a broader qualitative discovery that adjacent literature anticipates: Tao-of-Inference for the entropy-ratio paper's two-scale separation, Saad et al. (POPL 2020) for cipher-maps' two-corner frontier geometry, wire-tap equivocation theory for the codec paper's "sharpness is new" framing. The fixes are citation-and-reframing work, not new research. Meanwhile the field moved toward this program in 2024 (SWAT, q-leakage, the Filic PDS line), which validates the program's bet and gives it live conversations to enter.

---

## Part I: cipher-maps (towell2026cipher)

### Novelty verdicts

| Claim | Verdict | The threat | Required action |
|---|---|---|---|
| (TV, L) Pareto frontier; Shannon-optimal and TV-optimal corners distinct under integer constraints | **AT RISK: reframe required** (high confidence) | **Saad, Freer, Rinard, Mansinghka, "Optimal Approximate Sampling from Discrete Probability Distributions," POPL 2020**: the same two-distinct-corners phenomenon (entropy-optimal vs accuracy/TV-optimal under dyadic constraints), proven for sampling. Also adjacent: Charalambous et al. TV-ball robust coding (arXiv 1202.0136); Bocherer distribution matching (KL-to-target). | Cite all three; state explicitly that the trade-off geometry is known in IT/sampling and the contribution is the **security instantiation**: TV-to-uniform as leakage, acceptance-predicate parameterization, Le Cam attacker-accuracy semantics. The KL-vs-TV gap against the DM line is the actual novelty wedge; say so. |
| Coincidence oracle: acc(t) = 1 - (1/2) sum_y alpha(y)^t; concentrated partitions defend best at every t | **LIKELY SAFE** as a specific closed form (medium-high) | Surrounding ideas well-trodden: Bellare-Ristenpart-Tessaro CRYPTO 2012 (multi-instance security); Kopf-Basin CCS 2007 (uncertainty vs number of measurements); Espinoza-Smith FAST 2011 (cascade). | Frame as a specialization of known repeated-observation leakage to the cipher-map partition, with the alpha-profile closed form + the Huffman-defends-best prescription as the new content. Cite all three. |
| Framework synthesis (subsumes Bloom filters, FHE-free frequency hiding, encrypted Boolean search) | **SAFE as synthesis; "first to quantify" fragile** (medium) | Lacharite-Paterson frequency-smoothing encryption (ePrint 2017/1068): identical K(x) ∝ D(x) lever, explicitly lacking leakage quantification; **"Revisiting Frequency-Smoothing Encryption" (Cybersecurity, 2024)** tackles exactly that quantification gap. | Keep the framework claim. Narrow any "first to quantify" language; head-to-head with the 2024 FSE paper before claiming priority on quantification. |

### Verified citation gaps (all confirmed to exist; all absent from references.bib)

Ready-to-paste BibTeX:

```bibtex
@article{huffman1952method,
  title={A Method for the Construction of Minimum-Redundancy Codes},
  author={Huffman, David A.},
  journal={Proceedings of the IRE}, volume={40}, number={9}, pages={1098--1101}, year={1952}
}
@inproceedings{patel2019volumehiding,
  title={Mitigating Leakage in Secure Cloud-Hosted Data Structures: Volume-Hiding for Multi-Maps via Hashing},
  author={Patel, Sarvar and Persiano, Giuseppe and Yeo, Kevin and Yung, Moti},
  booktitle={ACM CCS}, pages={79--93}, year={2019}
}
@book{alvim2020science,
  title={The Science of Quantitative Information Flow},
  author={Alvim, M{\'a}rio S. and Chatzikokolakis, Konstantinos and McIver, Annabelle and Morgan, Carroll and Palamidessi, Catuscia and Smith, Geoffrey},
  publisher={Springer}, year={2020}
}
@inproceedings{kopf2010vulnerability,
  title={Vulnerability Bounds and Leakage Resilience of Blinded Cryptography under Timing Attacks},
  author={K{\"o}pf, Boris and Smith, Geoffrey},
  booktitle={IEEE CSF}, pages={44--56}, year={2010}
}
@book{cover2006elements,
  title={Elements of Information Theory},
  author={Cover, Thomas M. and Thomas, Joy A.},
  edition={2}, publisher={Wiley-Interscience}, year={2006}
}
@inproceedings{pouliot2016shadow,
  title={The Shadow Nemesis: Inference Attacks on Efficiently Deployable, Efficiently Searchable Encryption},
  author={Pouliot, David and Wright, Charles V.},
  booktitle={ACM CCS}, pages={1341--1352}, year={2016}
}
@inproceedings{kopf2007adaptive,
  title={An Information-Theoretic Model for Adaptive Side-Channel Attacks},
  author={K{\"o}pf, Boris and Basin, David},
  booktitle={ACM CCS}, pages={286--296}, year={2007}
}
@inproceedings{espinoza2012cascade,
  title={Min-Entropy Leakage of Channels in Cascade},
  author={Espinoza, Barbara and Smith, Geoffrey},
  booktitle={Formal Aspects of Security and Trust (FAST 2011)}, series={LNCS 7140}, pages={70--84}, year={2012}
}
@inproceedings{bellare2009format,
  title={Format-Preserving Encryption},
  author={Bellare, Mihir and Ristenpart, Thomas and Rogaway, Phillip and Stegers, Till},
  booktitle={SAC 2009}, series={LNCS 5867}, pages={295--312}, year={2009}
}
@article{saad2020optimal,
  title={Optimal Approximate Sampling from Discrete Probability Distributions},
  author={Saad, Feras A. and Freer, Cameron E. and Rinard, Martin C. and Mansinghka, Vikash K.},
  journal={Proc. ACM Program. Lang.}, volume={4}, number={POPL}, pages={36:1--36:31}, year={2020}
}
@inproceedings{bellare2012multi,
  title={Multi-Instance Security and Its Application to Password-Based Cryptography},
  author={Bellare, Mihir and Ristenpart, Thomas and Tessaro, Stefano},
  booktitle={CRYPTO 2012}, year={2012}
}
```

Also recommended in-text (already partially in bib or context-dependent): Lacharite-Paterson FSE (ePrint 2017/1068); "Revisiting Frequency-Smoothing Encryption" (Cybersecurity 2024); Kamara-Moataz-Ohrimenko CRYPTO 2018 (the 2019 EUROCRYPT paper is cited, the 2018 is not); Bocherer distribution-matching line; Charalambous TV-ball coding. The "Weiss-Shmatikov synthetic frequency-hiding" reference from the earlier review notes is UNVERIFIED (likely a mis-citation; nearest real work is Oya-Kerschbaum USENIX 2021).

---

## Part II: The Entropy Ratio (towell2026maxconf)

### Novelty verdicts

| Claim | Verdict | The threat | Required action |
|---|---|---|---|
| Two-scale separation (marginal does not control joint) | **NOT unclaimed qualitatively** (high confidence) | **Bindschaedler, Grubbs, Cash, Ristenpart, Shmatikov, "The Tao of Inference in Privacy-Protected Databases," PVLDB 11(11), 2018** (ePrint 2017/1078): analytically optimal multinomial attack, explicitly extended across correlated columns (96.9% multi-column recovery, ~6x over single-column). The encrypted-database instantiation of the qualitative claim. Also: Kawamoto-Chatzikokolakis-Palamidessi LMCS 2017 (QIF compositionality bounds; notes component leakages do not determine total under correlation). | **Cite and differentiate both.** Reposition the headline: not "we discovered the separation" but "we prove the sharp information-theoretic counterpart (matching minimax rate) of an empirically and analytically known phenomenon." |
| Sharp two-sided rate Theta(\|Y1\|\|Y2\|/xi^2) with Assouad lower bound + exact MI preservation | **SURVIVES: genuinely unclaimed in this form** (medium-high) | Tao-of-Inference proves attack optimality but no minimax lower bound and no dimension-dependent rate; KCP gives bounds, not rates; SSE co-occurrence attacks are heuristic. | This is the defensible headline. Lead with it. |
| Fisher-information noise dilution (Thm 4.1) | **Conceptually anticipated** (medium) | Farokhi-Sandberg: "Fisher Information as a Measure of Privacy" (IEEE Trans. Smart Grid 2018), "Ensuring Privacy with Constrained Additive Noise by Minimizing Fisher Information" (Automatica 2019). | Cite; reframe Thm 4.1 as instantiating the Fisher-information privacy measure for the cipher-map noise construction (the closed-form rho^2 dilution with explicit C(D) remains new). |
| Homophonic multiplicity K(x) ∝ D(x) (Thm 4.2) | Solid, but under-cited | Simmons 1979 is a survey mention, not the rigorous treatment. | Add Gunther, "A Universal Algorithm for Homophonic Coding" (EUROCRYPT 1988) and/or Jendal-Kuhn-Massey, "An Information-Theoretic Treatment of Homophonic Substitution" (EUROCRYPT 1989). |

### Recommended citation additions (7, each closes a reviewer attack surface)

```bibtex
@article{bindschaedler2018tao,
  title={The Tao of Inference in Privacy-Protected Databases},
  author={Bindschaedler, Vincent and Grubbs, Paul and Cash, David and Ristenpart, Thomas and Shmatikov, Vitaly},
  journal={Proceedings of the VLDB Endowment}, volume={11}, number={11}, pages={1715--1728}, year={2018}
}
@article{kawamoto2017compositionality,
  title={On the Compositionality of Quantitative Information Flow},
  author={Kawamoto, Yusuke and Chatzikokolakis, Konstantinos and Palamidessi, Catuscia},
  journal={Logical Methods in Computer Science}, volume={13}, number={3}, year={2017}
}
@article{farokhi2019ensuring,
  title={Ensuring Privacy with Constrained Additive Noise by Minimizing Fisher Information},
  author={Farokhi, Farhad and Sandberg, Henrik},
  journal={Automatica}, volume={99}, pages={275--288}, year={2019}
}
@inproceedings{gunther1988universal,
  title={A Universal Algorithm for Homophonic Coding},
  author={G{\"u}nther, Christoph G.},
  booktitle={EUROCRYPT 1988}, series={LNCS 330}, year={1988}
}
@inproceedings{jendal1989information,
  title={An Information-Theoretic Treatment of Homophonic Substitution},
  author={Jendal, Henrik N. and K{\"u}hn, Yves J. B. and Massey, James L.},
  booktitle={EUROCRYPT 1989}, series={LNCS 434}, year={1989}
}
@inproceedings{smith2017tight,
  title={Tight Bounds on Information Leakage from Repeated Independent Runs},
  author={Smith, David M. and Smith, Geoffrey},
  booktitle={IEEE CSF}, year={2017}
}
@inproceedings{duchi2013local,
  title={Local Privacy and Statistical Minimax Rates},
  author={Duchi, John C. and Jordan, Michael I. and Wainwright, Martin J.},
  booktitle={IEEE FOCS}, pages={429--438}, year={2013}
}
```

Plus in-text: Cash-Grubbs-Perry-Ristenpart 2015 at the compositional-scale related work; LEAKER (Kamara et al., EuroS&P 2022) as the empirical counterpart (also justifies the 20NG corpus choice in one sentence); optional primary assouad1983 entry.

---

## Part III: codec-controlled-retrieval (towell2026codec)

### Novelty verdicts: the strongest position of the three papers

| Tier | Verdict | Evidence |
|---|---|---|
| B (codec-output law survives the move to GF(2)-linear structures) | **SURVIVES, HIGH confidence** | Web-confirmed: Hu-Kuszmaul-Liang-Yu-Zhang-Zhou, "Static Retrieval Revisited: To Optimality and Beyond" (FOCS 2025) is a space-optimality paper that leaves the off-set output distribution uncharacterized; ShockHash (Algorithmica 2025), MorphisHash (ESA 2025), parallel BuRR (2024), Learned Static Function DS (2025) all treat non-member output as junk. First-to-characterize stands. |
| C (sharp span threshold T4) | **SURVIVES, MEDIUM-HIGH confidence** | One honest framing risk: wire-tap II equivocation theory (incl. "equivocation matrices," Entropy 2025) already knows "an integer rank controls a security transition" in the abstract. T4's novelty carriers: the object (output law of a data-dependent span vs designed code; lookup-output distribution vs message equivocation) and the exact K/K' over-weighting + exact-zero step structure, found nowhere. |

All three previously-named gaps verified: Filic-Paterson-Unnikrishnan-Virdia CCS 2022 (pp. 1037-1050; simulation-based, membership-only: clean differentiation); Patel-Persiano-Yeo-Yung CCS 2019; Hu-Kuszmaul FOCS 2025. Bibkeys in refs.bib confirmed to resolve to the intended papers.

### Actions

1. **Add XorMM** (Wang, Sun, Li, Qi, Chen, "Practical Volume-Hiding Encrypted Multi-Maps with Optimal Overhead and Beyond," CCS 2022): the closest XOR-structure + leakage-hiding + static cousin; uncited; a PoPETs referee will know it; independently corroborates the dynamic-insertion negative ("XorMM cannot support insertions").
2. **Move one wire-tap-distinguishing sentence into the T4 section** (currently the contrast lives only in the randenc section ~140 lines later): wire-tap fixes a designed code and asks a secrecy/equivocation question; T4 fixes a public partition and asks a data-dependent output-distribution question.
3. Optional one-liners: Waffle (SIGMOD 2023, PANCAKE successor); George-Kamara-Moataz-Espiritu (ASIACRYPT 2025, distribution-aware leakage suppression); Goyal-Sridhar-Zheng (arXiv 2510.00165, history-independence: different leak surface, same spirit); Markelon-Filic-Shrimpton (CCS 2023); Modern MPHF Survey (ACM CSUR 2025) as the "junk output" anchor.

```bibtex
@inproceedings{wang2022xormm,
  title={Practical Volume-Hiding Encrypted Multi-Maps with Optimal Overhead and Beyond},
  author={Wang, Jianfeng and Sun, Shi-Feng and Li, Tianci and Qi, Saiyu and Chen, Xiaofeng},
  booktitle={ACM CCS}, pages={2825--2839}, year={2022}
}
@inproceedings{maiyya2023waffle,
  title={Waffle: An Online Oblivious Datastore for Protecting Data Access Patterns},
  author={Maiyya, Sujaya and Vemula, Sharath Chandra and Agrawal, Divyakant and El Abbadi, Amr and Kerschbaum, Florian},
  booktitle={Proc. ACM Manag. Data (SIGMOD)}, year={2023}
}
```

---

## Part IV: Field Landscape (2023-2026) and Ranked Research Directions

### Where the field is (one line per theme)

1. **SSE/leakage**: bifurcated; attacks still loudest (Jigsaw USENIX 2024: 90% recovery, robust to countermeasures), but 2024 pivoted to quantify-then-mitigate (q-leakage PETS 2024; SWAT VLDB 2024): the program's natural home.
2. **Private queries at scale**: sublinear single-server PIR is hot (Piano S&P 2024); private semantic search is OSDI/CCS-grade (Compass 2025, Panther 2025); everything pays per-query. The "tunable measurable leakage middle ground" crystallized as a named space in 2024.
3. **QIF**: mature operational measures (maximal leakage, alpha-leakage, PML); live threads are composition + correlated secrets (Dalenius). The program under-cites its own methodological home.
4. **Adversarial PDS**: consolidating subfield (Filic CCS 2022 onward; FKKU 2025 open-problems paper). The program is a native citizen with a different privacy notion: a hazard and an opportunity.
5. **Private ML inference / vector search**: very hot; approximate-inference-as-privacy is independently emerging (2023-2025), converging on the program's eta-as-privacy thesis; embedding inversion is OWASP LLM08:2025.
6. **Privacy under drift**: fragmented; nobody owns "maintain a quantified leakage bound while the distribution drifts": the adaptive-trapdoor lane is open, with Waffle (no-prior-knowledge obliviousness, per-query cost) as the foil.

### Ranked directions (impact-per-effort, descending)

| # | Direction | Builds on | Field gap | Venue | Effort |
|---|---|---|---|---|---|
| 1 | **Codec-controlled false-positive output distribution as a new privacy axiom for the Filic PDS model** | T4 | FKKU 2025 open-problems list has correctness + a privacy notion, but not "the FP answer distribution as a controllable, frequency-independent design object" | CCS / S&P / PoPETs | Low (result already proven; best payoff per unit work) |
| 2 | **Position as the zero-marginal-cost point on the tunable-leakage frontier** (head-to-head vs SWAT + q-leakage) | Pareto frontier + structural frequency hiding | Every system in the 2024 tunable-leakage space pays per-query; the program's static structure does not | PoPETs | Low (framing + one table) |
| 3 | **Re-express the leakage knob in maximal-leakage / alpha-leakage / PML currency; prove a composition statement there** | Two-scale theorem | PML + correlated-secrets composition is the active CSF thread; the two-scale result is the constructive instance of the Dalenius phenomenon | CSF | Low-medium |
| 4 | **Adaptive K(x) retuning under drift, framed against Waffle, with a maintained leakage bound** | adaptive-trapdoor + homophonic allocation | Nobody owns quantified-leakage-under-drift; Waffle pays per-query | PoPETs / VLDB | Medium |
| 5 | **Codec-controlled membership layer for private RAG / encrypted vector search** | ribbon construction + library | Compass/Panther pay ORAM/HE; embedding inversion is a recognized top-10 risk | USENIX Sec / OSDI | High |
| 6 | **Approximation-as-privacy made rigorous** (tie eta to an operational leakage bound) | Property 3 remark | ML-privacy community independently arriving at the same thesis (2023-2025) | CSF / PoPETs | Low |
| 7 | **Structural frequency-hiding vs PPE: attack-resistance comparison** (DCPE / FH-OPE broken by frequency attacks) | T4 frequency independence | DCPE+HNSW proposed 2025 with weaker guarantees | PoPETs / ESORICS | Medium |
| 8 | **DP-free frequency-flattening sketch** (structural alternative to DP count-min) | representation uniformity + codec control | Pool-inference attacks on Apple CMS exposed the noise approach's limits | PETS / PODS | Speculative |

Directions 1-3 are framing-level wins that convert already-proven results into adjacent live conversations. Direction 4 is the natural next paper. Direction 5 is the biggest audience and the biggest lift.

---

## Part V: Saliency / Taste Assessment (frank)

**The program's taste in problems is good and is now externally validated.** The bet placed in 2023-2024 (measurable, tunable leakage as a legitimate design point between plaintext and ORAM/FHE) was contrarian then; in 2024 the field arrived (SWAT, q-leakage, the Filic line, approximate-inference-as-privacy). Being early and right is the best position. The unique selling point that emerged from this survey: **structural frequency-hiding at zero per-query cost in a static data structure**. Every neighbor pays per-query bandwidth, rounds, or noise.

**The program's taste in claims has been the weak spot.** A consistent pattern across all three papers: the theorems are sound and the strongest results survive adversarial review, but each paper reached for a broader qualitative "first" that adjacent literature anticipates (two-scale separation: Tao of Inference; two-corner frontier: Saad et al.; sharpness rhetoric: wire-tap equivocation). The root cause is under-reading adjacent vocabularies (sampling theory, Fisher-information privacy, distribution matching, wire-tap coding) while reading the home vocabulary (SSE, QIF, retrieval structures) well. None of this is fatal; all of it is the difference between a defensive review cycle and a clean one.

**Paper-by-paper saliency ranking**:
1. **codec-controlled-retrieval: the best-tasting paper.** A concrete new object (the non-member output law), a sharp theorem (T4), an honest three-tier novelty ledger that pre-emptively declines to claim the anticipated part, and external confirmation (FOCS 2025 still leaves the gap). It also has the cleanest story for a systems-security audience. Its discipline (tier A explicitly not claimed) is the model the other papers should copy.
2. **The Entropy Ratio: the strongest single theorem, one repositioning away from solid.** The matching-bounds compositional rate is the program's most reviewer-proof result. The required fix (cite Tao-of-Inference + KCP, lead with the rate not the separation) makes the paper more honest and harder to reject simultaneously.
3. **cipher-maps: the most valuable and the most exposed.** As the hub it carries the paradigm, and the framework synthesis is real. But it has the largest claim surface, the most "at risk" verdict (the frontier), and the longest history of review churn. It should be submitted after the other two have established the program's credibility, with the frontier reframed as a security instantiation.

**Portfolio-level observations**:
- Eight papers, zero submissions remains the central risk. The survey strengthens the case for sequencing: Entropy Ratio first (after the ~1-day citation fix), codec second (after XorMM + the T4 sentence), cipher-maps third.
- The retirement of boolean-algebra-over-trapdoor-sets was good taste: the survey confirms the judgment (its construction is FSE/deterministic-encryption territory).
- The scaffold papers (cipher-program-construction, cipher-closures) should stay parked until at least one mature paper is submitted.
- The simulation-based-definitions headwind is real: a Kamara-school reviewer will ask for a leakage profile and a simulator. Direction 3 (speak alpha-leakage/PML) is the cheapest insurance; the QIF stance should be defended as a feature (measurable, composable, operational) in one paragraph per paper, not apologized for.
- One unsearched steelman remains (flagged by the landscape scout's self-critique): a dedicated pass on "frequency-smoothing encryption limitations 2023-2026" to fully pre-empt the "isn't this FSE rebranded?" objection. Worth one hour before any submission.

## Part VI: Recommended action order

1. Entropy Ratio: apply the 7-citation fix + headline repositioning (one session) and submit (CSF or PoPETs).
2. Codec: add XorMM + the wire-tap sentence in T4 (one hour); finish drafting from the source note; submit to PoPETs.
3. cipher-maps: apply the 11-entry citation batch + frontier reframe (one session); hold for third.
4. Start Direction 1 (Filic-axiom paper) as the next new work: best payoff per unit work, result already proven.
5. Fold Directions 2/6 framing into the existing papers' related-work sections during the above.

---

## Part VII: The FSE Steelman (follow-up scout, same day)

A dedicated adversarial scout steelmanned the strongest hostile-reviewer objection: "this program is frequency-smoothing encryption, rebranded." Full report in the session record; verdicts here.

### Differentiator verdicts

| # | Claimed differentiator | Verdict | Honest assessment |
|---|---|---|---|
| 1 | Totality (no fake-traffic protocol) | **HOLDS (qualified)** | Genuinely different mechanism from PANCAKE's injected fake queries, but the GOAL (real vs filler indistinguishable) is identical; frame as a how, not a what. |
| 2 | Measured leakage (delta, e, Le Cam, composition) | **PARTIALLY HOLDS** | The toolset (QIF scalar + Fannes bridge + composition + minimax) is absent from the FSE line, but "quantify FSE leakage" is exactly what Chen-Yang-Lv (Cybersecurity 2024) set out to do with game-based definitions. Must cite it for the toolset claim to stick. |
| 3 | (L, TV) Pareto frontier | **HOLDS** | Cleanest standalone novelty among the five; nothing in the smoothing line plots length-vs-TV. |
| 4 | GF(2)-linear structural frequency-hiding, zero per-query cost | **HOLDS** | The program's strongest differentiator: a build-time theorem (rank test), no stream for IHOP-style correlated-query attacks to exploit. |
| 5 | Two-scale separation | **PARTIALLY HOLDS** | The QUALITATIVE insight (marginal flattening does not hide joint structure) is already present in the Cao et al. VLDB 2023 frequency-revealing attacks on FH-OPE. The formal half (no delta moves the rate; matching Assouad bound) is new. Frame as "we prove the bound the attack literature observed." |

None fails outright. The steelman's strongest TRUE core is bibliographic, not substantive: the flagship theory paper distinguishes itself from frequency smoothing without citing frequency smoothing.

### Per-paper exposure (most to least)

1. **Entropy Ratio: MOST EXPOSED.** Verified by file inspection: it cites only Simmons 1979 for homophonic substitution; no Lacharite-Paterson, no PANCAKE, no FH-OPE, no Revisiting-FSE 2024, despite being built around the homophonic delta-reduction lever and listing "homophonic substitution" in its keywords. Pure literature-gap exposure, severe because the paper's real contribution (the C3 minimax bound, which IS novel against the FSE line) hides behind the un-cited frame.
2. **cipher-maps: MODERATE.** Cites FH-OPE (Kerschbaum) and NKW but not FSE or PANCAKE by name; FSE is the direct homophonic-encryption ancestor and its absence is conspicuous.
3. **codec-controlled-retrieval: LEAST.** Already cites FSE, PANCAKE, IHOP, SWAT, Filic, NKW, volume-hiding, draws the layer boundary explicitly, and concedes Tier A. The model to copy.

### Required additions (verified citations)

```bibtex
@article{lacharite2018frequency,
  title={Frequency-Smoothing Encryption: Preventing Snapshot Attacks on Deterministically Encrypted Data},
  author={Lacharit{\'e}, Marie-Sarah and Paterson, Kenneth G.},
  journal={IACR Transactions on Symmetric Cryptology}, volume={2018}, number={1}, pages={277--313}, year={2018}
}
@article{chen2024revisiting,
  title={Revisiting Frequency-Smoothing Encryption: New Security Definitions and Efficient Construction},
  author={Chen, Haobin and Yang, Ji and Lv, Siyi},
  journal={Cybersecurity}, volume={7}, number={15}, year={2024}
}
@inproceedings{grubbs2020pancake,
  title={PANCAKE: Frequency Smoothing for Encrypted Data Stores},
  author={Grubbs, Paul and Khandelwal, Anurag and Lacharit{\'e}, Marie-Sarah and Brown, Lloyd and Li, Lucy and Agarwal, Rachit and Ristenpart, Thomas},
  booktitle={USENIX Security}, year={2020}
}
@inproceedings{kerschbaum2015frequency,
  title={Frequency-Hiding Order-Preserving Encryption},
  author={Kerschbaum, Florian},
  booktitle={ACM CCS}, pages={656--667}, year={2015}
}
@article{cao2023frequency,
  title={Frequency-Revealing Attacks against Frequency-Hiding Order-Preserving Encryption},
  author={Cao, Xinle and Liu, Jian and Shen, Yongsheng and Ye, Xiaohua and Ren, Kui},
  journal={Proceedings of the VLDB Endowment}, volume={16}, number={11}, pages={3124--3136}, year={2023}
}
```

(Author list for cao2023frequency from the VLDB page; verify at insertion. grubbs2020pancake and kerschbaum2015frequency are already in the codec paper's bib; copy from there.)

### The one sentence each paper must add

- **Entropy Ratio**: "Frequency-smoothing encryption (Lacharite-Paterson 2018; revisited with rigorous definitions by Chen-Yang-Lv 2024) and access-pattern smoothing (PANCAKE 2020) target the same frequency-analysis threat via online homophone allocation or fake traffic and evaluate leakage empirically or via indistinguishability games; we instead reduce the per-map marginal to a single parameter delta, bridge it to entropy by Fannes-Audenaert, and prove a matching minimax lower bound showing that no delta controls the compositional joint-recovery rate, a quantitative separation absent from that line."
- **cipher-maps**: "Unlike frequency-smoothing encryption (Lacharite-Paterson 2018), which allocates homophones per record to flatten the ciphertext marginal, representation uniformity is a property of a total cipher map evaluated blindly by the untrusted machine: filler and real queries are indistinguishable structurally rather than by injected traffic (cf. PANCAKE 2020), and the same delta that bounds the marginal provably does not bound joint leakage under composition."
- **codec** (sharpening only): "What distinguishes this from every prior frequency-smoothing mechanism is that the property is decidable at build time by a GF(2)-rank test and incurs zero per-query cost: there is no access stream for a correlated-query attack such as IHOP to exploit, because the non-member value law never reads storage frequency."

The steelman's ready-made hostile paragraph and full rebuttal paragraph are preserved in the scout report (session record); the rebuttal is only deliverable after the citation gaps above are fixed.
