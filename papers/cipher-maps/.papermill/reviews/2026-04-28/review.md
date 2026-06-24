# Multi-Agent Review Report

**Date**: 2026-04-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Author**: Alexander Towell
**Pages**: 22 (article class; will change in PoPETs template)
**Target Venue**: PoPETs 2027
**Review Round**: 4 (prior rounds: 2026-03-19, 2026-03-26, 2026-03-28)
**Recommendation**: major-revision

## Summary

**Overall Assessment**: The Round 3 fixes (M3 citations, M4 composition formula, M5 space optimality framing, M6 ROM dependence) are all clean and integrate well with the surrounding text. The bibliography is healthy at 23 entries. The proofs are correct under stated assumptions. The Round 3 review's most consequential structural concerns (M1 missing security definition, M2 missing experimental evaluation) remain as the principal threats to PoPETs survivability. Beyond M1 and M2, this round identifies several editorial issues that are independent of the heavy lift work and that, together, would substantially polish the paper before submission. The single most useful editorial move is to give the parameterized-leakage style a positive label (entropic security or QIF tradition) rather than just disclaiming standard frameworks.

**Strengths**:
1. The Round 3 M3 fix landed cleanly: the new Leakage-abuse attacks paragraph (lines 169-192) and Honey encryption paragraph (lines 194-209) are crisp and well-calibrated, with explicit mechanism-by-mechanism comparison to prior work (novelty-assessor, prose-auditor)
2. The Round 3 M4 fix landed cleanly: all four restatements of the composition bound now consistently use ≤ with re-randomization equality qualifier (logic-checker)
3. The Round 3 M5 fix landed cleanly: Theorem 6.2 is now framed as "information-theoretic space complexity" with new Remark 6.3 distinguishing physical from info-theoretic storage (logic-checker, methodology-auditor)
4. The Round 3 M6 fix added a clear ROM dependence paragraph naming HMAC-SHA256 as the practical instantiation; the standard-model open question is explicitly stated (methodology-auditor)
5. The acceptance predicate framing (Definition 6.4) and the Shannon-frequency duality paragraph (lines 700-719) remain the paper's strongest contributions; these are genuinely original (novelty-assessor)
6. The honest limitations sections (Remark 4.1, §8 Honest Limitations, §9.5) continue to set clear expectations (prose-auditor)
7. Build is clean: zero LaTeX warnings, all references resolve, all citations resolve, BibTeX log clean (format-validator)
8. Bibliography is well-formatted: all 23 entries cited, no orphans, new Round 3 additions (cash2015leakage, juels2014honey) well-formed (citation-verifier)

**Weaknesses**:
1. Theorem 6.2 proof Step 2 has a notational sleight that could read as double-counting, though the final result is correct (logic-checker L1)
2. The §3.1 ROM paragraph promises four assumptions but enumerates three (lettered a, b, c); Property 2 dependence is conspicuously absent (logic-checker, prose-auditor)
3. The "Experimental validation" paragraph in §9.4 is reproducibility-thin: hardware, query distribution, trial count, comparison baselines all missing (methodology-auditor M-A1)
4. The §9.4 experimental content is duplicated within itself (lines 1419-1434 and lines 1436-1446 both report "FP drops from 248 to 12 for 3-term AND") (methodology-auditor M-A8, prose-auditor)
5. The abstract sets up an "encrypted computation" frame that §9.5 later disclaims, creating a structural mismatch that PoPETs reviewers will notice (prose-auditor P1)
6. §9.5 "What This Framework Is Not" disclaims three frameworks (ORAM, DP, sim-based) without giving the parameterized-leakage style a positive label (entropic security or QIF tradition) (novelty-assessor N2)
7. Several Round 3 minor findings (m1, m2, m3, m4, m5, m7, m8, m9, m10, m11) were not addressed in this round; individually small but collectively a half-day of editorial work
8. RecSplit is named in §6.4 (line 934) but not cited; phobic library mentioned in §9.4 without explanation or URL (citation-verifier C2, C3)
9. The bernoulli-types self-citation remains unpublished and is cited 3 times for foundational claims (citation-verifier C1, m10 from Round 3)
10. M1 (no formal security definition) and M2 (no experimental evaluation beyond a brief paragraph) remain as Round 3 flagged

**Finding Counts**: Critical: 0 | Major: 5 (1 logic, 2 methodology, 1 prose, 1 novelty) | Minor: 26 (across all specialists) | Suggestions: 8

---

## Critical Issues

None.

---

## Major Issues

### MAJ-1. Theorem 6.2 proof Step 2 reads as double-counting (source: logic-checker L1)
- **Location**: §6.3 Theorem 6.2 proof, Step 2 (lines 794-801)
- **Quoted text**: "Shannon-optimal allocation sets $\alpha(y_i) \propto p_{y_i}$, giving per-element information cost $-\log_2 \alpha(y_i) \approx -\log_2 p_{y_i}$ and expected cost per element $\sum_y p_y (-\log_2 \alpha(y)) = \mu = H(Y)$."
- **Problem**: With $\alpha(y) = \varepsilon p_y$ (the proportionality is precisely this normalization), we have $-\log_2 \alpha(y) = -\log_2 \varepsilon - \log_2 p_y$, not $-\log_2 p_y$. The "$\approx$" hides the $-\log_2 \varepsilon$ term, which then appears as a separate component in Step 3 (acceptance cost). A naive recomputation of the expected cost using $\alpha(y) = \varepsilon p_y$ yields $-\log_2 \varepsilon + H(Y)$, the *full* per-element cost. Step 3 then adds $-\log_2 \varepsilon$ on top, suggesting double-counting. The final Step 4 result is correct, but the decomposition is presented in a way that requires careful reading.
- **Suggestion**: Combine Steps 2 and 3 into one calculation. Replace with: "The per-element cost is $-\log_2 \alpha(y_i)$; with Shannon-optimal allocation $\alpha(y) = \varepsilon p_y$, the expected cost decomposes as $\mathbb{E}[-\log_2 \alpha(y)] = -\log_2 \varepsilon + H(Y)$, where $-\log_2 \varepsilon$ is the constant noise-rejection cost shared by all valid encodings and $H(Y)$ is the entropy contribution from the value distribution."
- **Cross-verified**: Yes, by methodology check. The arithmetic is correct ($\mathbb{E}_{y \sim p}[-\log_2(\varepsilon p_y)] = -\log_2 \varepsilon + H(Y)$, matching Step 4). The issue is purely presentational. Methodology cross-verification confirms: this is a clarity issue, not a bug. Severity: MAJOR for the misleading decomposition; could be downgraded to MINOR with the suggested rewrite.

### MAJ-2. Experimental validation paragraph is reproducibility-thin (source: methodology-auditor M-A1)
- **Location**: §9.4, paragraph at lines 1419-1434 (with duplicate content at lines 1436-1446)
- **Quoted text**: "A reference implementation (\texttt{cipher-maps}, Python) validates the encrypted search application on the 20 Newsgroups corpus (18,266 documents, 58,903 unique words). Construction uses perfect hash functions (via \texttt{phobic}) with $n = 8$-bit cipher Booleans ($p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$). At 5,000 documents: construction takes 5.9 seconds (843 documents per second), single-term queries achieve perfect recall (1.0) with precision 0.39..."
- **Problem**: The paragraph introduces specific numerical claims (843 docs/sec, precision 0.39, FP count 248 to 12 for 1-term to 3-term AND, recall 0.97 / 0.88 for OR / NOT, 25.6 sec for full-index build) without specifying hardware, query distribution, trial count, variance, definition of false positive, or baseline comparisons. The phrase "matching the theoretical false positive rate $p_T = 0.05$ per document" is unclear: precision 0.39 and per-document FPR 0.05 are different quantities, and the relationship is not derived. Additionally, the paragraph is internally duplicated: the cipher Boolean partition and the 248 to 12 FP claim both appear in two adjacent paragraphs.
- **Suggestion**: Three options. (Minimum) Move to a small dedicated subsection with reproducibility metadata (hardware, trial count, query distribution, URL to implementation). (Better) Add a comparison row against Bloom filter and SSE baselines at the same false-positive rate. (Ideal) Promote to a §10 "Implementation and Evaluation" with a parameter-sweep figure and comparison table. Either way, deduplicate the two paragraphs into one. Even the minimum option is a few hours of work and substantially improves defensibility.
- **Cross-verified**: Logic check on the precision-FPR relationship: with $p_T = 0.05$ and 5000 docs, expected FP per query is 250; precision 0.39 with FP 250 implies TP ~160, consistent with 3.2%-frequency terms. The numerical claim is internally consistent but the wording "matching" misleads. Cross-verification supports flagging.

### MAJ-3. Abstract framing creates expectations the paper later disclaims (source: prose-auditor P1)
- **Location**: Abstract (lines 47-63), specifically the opening "Privacy in encrypted computation"
- **Quoted text**: "Privacy in encrypted computation need not come from access-pattern hiding (ORAM), exact algebraic homomorphism (FHE), or simulation-based security (garbled circuits). We show that a *cipher map* ... provides a distinct, quantifiable privacy model."
- **Problem**: The opening phrase frames the paper as proposing an encryption scheme, but §9.5 explicitly disclaims being any standard cryptographic primitive: "Not differential privacy. Not simulation-based security." A PoPETs reviewer who reads "encrypted computation" forms expectations (security definitions, standard model assumptions, indistinguishability proofs) that the paper does not deliver. The structural mismatch contributes to M1 (no formal security definition) feeling like a gap rather than a deliberate design choice.
- **Suggestion**: Rewrite the abstract opening to set the right frame: "Outsourcing computation to an untrusted evaluator typically requires either oblivious RAM (hiding access patterns), fully homomorphic encryption (exact computation on ciphertexts), or garbled circuits (encrypted lookup tables, single-use). Each comes with substantial cost. We propose a *cipher map*: a total function on bit strings whose privacy properties emerge from totality, hash-based one-wayness, and frequency-equalized output distributions. Cipher maps trade exactness ($\eta > 0$) and a parameterized leakage budget ($\delta, \varepsilon$) for static lookup tables and predictable error composition." This frames the contribution accurately and aligns the reviewer's expectations with what the paper delivers.
- **Cross-verified**: Yes, novelty-assessor N1 independently flags the abstract for underclaiming the duality. Same root cause.

### MAJ-4. §9.5 disclaims three frameworks without positive positioning (source: novelty-assessor N2)
- **Location**: §9.5 "What This Framework Is Not" (lines 1510-1524)
- **Quoted text**: "Not ORAM ... Not differential privacy ... Not simulation-based security."
- **Problem**: The section disclaims three standard frameworks but does not name what cipher maps *are*. The parameterized leakage ($\delta$, $\varepsilon$) belongs to a recognized tradition: entropic security (Russell-Wang 2002, Dodis-Smith 2005) and quantitative information flow (Smith 2009, Alvim et al. 2012). The sister paper "maximizing-confidentiality" already cites QIF; this paper does not. A PoPETs reviewer reads §9.5 as the author rejecting all standard formalisms, which sounds either crank-adjacent or under-informed. The truth is that the paper is doing constructive parameterized-leakage work in a recognized style; it just hasn't said so.
- **Suggestion**: Add a positive label. Sample rewrite: "The cipher map framework belongs to the *quantitative information flow* tradition (Smith 2009; Alvim et al. 2012): security is parameterized rather than negligible, and leakage is measured as a continuous quantity ($\delta$, $\varepsilon$) rather than a binary event. We are not proposing a new security paradigm; we are giving a constructive recipe for primitives whose leakage is bounded by these parameters." Cost: two bib entries (Dodis-Smith 2005 and Smith 2009 or Alvim et al. 2012), one paragraph rewrite. The conceptual content does not change. This is the cheapest single change that would shift the paper's reception.
- **Cross-verified**: Yes, prose-auditor agrees the disclaimer-without-positioning is a structural prose problem; literature scout confirms Dodis-Smith 2005 and Smith 2009 are the standard citations for entropic security and QIF respectively.

### MAJ-5. ROM paragraph promises four ROM assumptions, lists three (source: logic-checker, prose-auditor, methodology-auditor)
- **Location**: §3.1 ROM paragraph (lines 245-262)
- **Quoted text**: "All four properties and every theorem in this paper depend on the random oracle model. ... The critical ROM assumptions are: (a) uniform hash output on non-stored elements (Property 1, totality, and the noise-decode probability $\varepsilon$); (b) independence of hash values across distinct elements (Property 3, correctness analysis...); (c) independence across maps with distinct seeds (Property 4, composition)."
- **Problem**: The lead sentence references "all four properties" depending on ROM. The enumeration is by property: (a) Property 1, (b) Property 3, (c) Property 4. Property 2 (representation uniformity) is absent from the enumeration. A reader expecting four lettered assumptions finds three, with a hole at Property 2. The Round 3 M6 review specifically suggested four assumptions including hash-seed independence for $\delta$.
- **Suggestion**: Add a fourth item: "(d) independence of cipher value distributions $\enc(x, k)$ across distinct multiplicities $k$ (Property 2, representation uniformity)." This makes the count consistent and addresses the gap.
- **Cross-verified**: Yes, three specialists (logic-checker, prose-auditor, methodology-auditor) independently flagged the count discrepancy. Treating as one issue.

---

## Minor Issues

### Carry-overs from Round 3 (still not addressed)

#### m1 (continued). Abstract "demonstrate" still overclaims (source: novelty-assessor N3, prose-auditor P3)
- **Location**: Abstract, lines 60-62
- **Quoted text**: "we ... demonstrate the construction on arbitrary maps, set membership, and encrypted search"
- **Suggestion**: Change "demonstrate" to "illustrate."

#### m2 (continued). Discussion section overloaded with seven subsections (source: prose-auditor P1, novelty-assessor N4)
- **Location**: §9 (lines 1321-1525)
- **Suggestion**: Promote §9.4 (encrypted search) to a top-level "Implementation and Validation" section. Move §9.6 (What This Framework Is Not) to the Introduction. Combine §9.1 and §9.2 into a single Connections section. Trim Open Questions from six items to three.

#### m3 (continued). $K(x)$ notation conflicts with Kolmogorov complexity (source: prose-auditor P4)
- **Location**: Definition 3.1 (line 273)
- **Suggestion**: Use $\kappa(x)$ or $\mathrm{mult}(x)$ throughout.

#### m4 (continued). Zero figures in 22 pages (source: prose-auditor P5, format-validator F2)
- **Location**: Throughout; TikZ source files exist in `paper/img/` but unused
- **Suggestion**: Include at least one figure showing acceptance predicate partition of hash space.

#### m5 (continued). "4th-order Bernoulli Boolean" used without sufficient explanation (source: prose-auditor P6)
- **Location**: §7.1, line 1085
- **Suggestion**: Drop the term in favor of "four-case correctness profile."

#### m7 (continued). Adversary model not formalized (source: methodology-auditor M-A3, prose-auditor P7)
- **Location**: §5 Definition 5.2
- **Suggestion**: Add: "We model $U$ as honest-but-curious: $U$ correctly evaluates $\fhat$ on each input and returns the result, but attempts to learn information about $f$, $X$, or $Y$ from its observations."

#### m8 (continued). Bucketed construction time hides expectation/sup distinction (source: logic-checker L4)
- **Location**: Proposition 6.5 (lines 889-906)
- **Suggestion**: Add to the proof: "We compute the expected sequential time over all $k$ buckets. The maximum-bucket time, relevant for parallel construction, is dominated by the largest bucket size $\Theta(m/k + \log k)$ w.h.p."

#### m9 (continued). Hash construction notation inconsistency persists (source: methodology-auditor M-A4)
- **Location**: Algorithm 1 ($h(\ell) \oplus h(x)$, line 737); Entropy cipher map ($h(x \| s)$, line 958); ROM paragraph (HMAC-SHA256, line 257)
- **Suggestion**: Pick one convention (HMAC-SHA256 with seed as key is strongest) and use it throughout.

#### m10 (continued). bernoulli-types self-citation still unpublished, cited 3 times (source: citation-verifier C1)
- **Location**: Bibliography entry; cited at lines 96, 1347, 1379
- **Suggestion**: Post as arXiv preprint before submission. Update the bib entry. Resolves the issue cleanly.

#### m11 (continued). No DOIs in bibliography (source: citation-verifier C4)
- **Location**: All entries in references.bib
- **Suggestion**: Add DOIs for all 21 published entries; standard pre-submission cleanup.

### New minor findings (Round 4)

#### nm1. Lower bound proof Stirling step still informal (source: logic-checker L2, m6 from Round 3)
- **Location**: Theorem 6.1 proof, lines 627-633
- **Suggestion**: Insert one sentence justifying the identification $\varepsilon = n/|U|$.

#### nm2. Composition theorem proof: union event vs. intersection wording (source: logic-checker L3)
- **Location**: Theorem 7.1 proof (lines 1108-1130)
- **Suggestion**: Add half a sentence noting the bound counts errors pessimistically; in some cases, $\fhat$ producing the wrong value may yet decode correctly if $\ghat$ collapses the error.

#### nm3. Per-seed success probability proposition lacks Poisson binomial reference (source: logic-checker L5)
- **Location**: Proposition 6.3 (lines 838-862)
- **Suggestion**: Add a sentence explaining that the failure count is a Poisson binomial; for uniform $\alpha$, reduces to Binomial.

#### nm4. Construction-time table uses toy parameters $m=100$ (source: methodology-auditor M-A2)
- **Location**: §6.4 table (lines 868-877)
- **Suggestion**: Replace with a table that varies $(m, k)$ across realistic scales: $(10^4, 100)$, $(10^4, 1000)$, $(10^6, 10^3)$, $(10^6, 10^5)$.

#### nm5. False positive precision calculation in §9.4 is unverifiable as stated (source: methodology-auditor M-A5)
- **Location**: Lines 1426-1429
- **Suggestion**: Reformulate to clarify that "matching the theoretical false positive rate $p_T = 0.05$ per document" refers to per-document FPR ($250 / 4840 \approx 0.052$), not to precision.

#### nm6. Cipher Boolean partition (5%/90%/5%) lacks justification (source: methodology-auditor M-A6)
- **Location**: Lines 1424-1425, 1438-1442
- **Suggestion**: Add a sentence noting the partition is Shannon-optimal for the 20 Newsgroups corpus where keyword presence has empirical mean about 5%.

#### nm7. "Encryption" vs. "encoding" terminology drift (source: methodology-auditor M-A7)
- **Location**: Throughout, most visible in abstract and §5
- **Suggestion**: Tighten terminology in the abstract and §5; cipher maps are not formally encryption.

#### nm8. Experimental validation paragraph duplicated within §9.4 (source: methodology-auditor M-A8, prose-auditor)
- **Location**: Lines 1419-1434 and 1436-1446 both report "FP drops from 248 to 12 for 3-term AND" and "(0.05, 0.90, 0.05) cipher Boolean partition"
- **Suggestion**: Consolidate into a single Experimental validation paragraph.

#### nm9. "Re-randomization condition" used four times without single labeled definition (source: prose-auditor P9)
- **Location**: Theorem 4.1, Theorem 7.1, Corollary 7.1, §9.1
- **Suggestion**: Add a labeled Definition stating the re-randomization condition once, then refer to it by label.

#### nm10. Title "Total Functions as Trapdoor Approximations" but abstract uses "trapdoor" only once (source: prose-auditor P8)
- **Location**: Title vs. Abstract
- **Suggestion**: Optional. Add a sentence to the abstract briefly naming the trapdoor mechanism.

#### nm11. Acceptance predicate framing buried; novelty understated (source: novelty-assessor N2)
- **Location**: §6.2 Definition 6.4
- **Suggestion**: Promote the unification claim. Add a Proposition or emphatic Remark stating that prefix-free, threshold, and range-partition constructions all instantiate the same abstract acceptance predicate.

#### nm12. Online construction underdeveloped (source: novelty-assessor N3)
- **Location**: §9.3 (lines 1368-1383)
- **Suggestion**: Either promote to a brief top-level section with concrete error bounds for union/intersection/complement, or mute §3.3's "two strategies" framing.

#### nm13. Cipher Boolean type appears only in experimental paragraph (source: novelty-assessor N5)
- **Location**: Lines 1436-1446
- **Suggestion**: Add a short Example 6.1 in §6 showing the cipher Boolean type as a worked example of the four properties.

#### nm14. Granularity / entanglement parameter lacks comparison to similar trade-offs (source: novelty-assessor N4)
- **Location**: §8.1 Encoding Granularity Principle
- **Suggestion**: Add a sentence noting analogous granularity / cost trade-offs in oblivious RAM and PIR.

#### nm15. RecSplit named but not cited (source: citation-verifier C2)
- **Location**: §6.4, line 934
- **Suggestion**: Add Esposito et al. 2020 to bib; cite at line 934.

#### nm16. phobic library mentioned without explanation (source: citation-verifier C3)
- **Location**: §9.4, line 1423
- **Suggestion**: Add a footnote explaining what `phobic` is (URL or citation).

#### nm17. Article class will need PoPETs template before submission (source: format-validator F1)
- **Location**: Line 1
- **Suggestion**: Test-build with PoPETs template at least once before next major revision pass.

#### nm18. Anonymization not done (source: format-validator F3)
- **Location**: Title page, Acknowledgments
- **Suggestion**: Before submission, anonymize author and rephrase "the author's earlier work."

---

## Suggestions

### S1. Engage with closely-related literature (source: literature-context)
Three high-priority citations would substantially strengthen the literature footing:
- Kerschbaum 2015 "Frequency-Hiding Order-Preserving Encryption" (CCS 2015) is direct prior art for the frequency-hiding mechanism.
- Patel-Persiano-Yeo-Yung 2019 (or Kamara-Moataz 2019) for volume-hiding SSE.
- Esposito et al. 2020 (RecSplit) is already named in §6.4 and just needs to be in the bib.

### S2. Add entropic security / QIF citations (source: literature-context, novelty-assessor N2)
Two citations would give the parameterized-leakage style a positive label in the literature:
- Dodis-Smith 2005 "Entropic Security and the Encryption of High Entropy Messages" (TCC).
- Smith 2009 "On the Foundations of Quantitative Information Flow" (FoSSaCS) or Alvim et al. 2012.

### S3. Promote experimental content to a top-level section (source: methodology-auditor M-A1, prose-auditor P1)
Even without expanding the experiments, moving the §9.4 experimental paragraph to a §10 "Implementation and Validation" section with a few sentences of reproducibility metadata would dramatically improve how the paper reads. Cost: a few hours.

### S4. Add at least one figure (source: prose-auditor P5, format-validator F2)
A figure showing the acceptance predicate partition with regions sized by $p_y$ would visually communicate the Shannon-frequency duality. The TikZ source files exist; just include them.

### S5. Test-build with PoPETs template early (source: format-validator F1)
Page-count surprises during the M1/M2 revision could force unwanted compression. Earlier test-builds avoid last-minute cuts.

### S6. Pick one hash construction notation and use it throughout (source: methodology-auditor M-A4)
HMAC-SHA256(seed, msg) is the strongest notation. Pick one and unify Algorithm 1, §6.5 Entropy Cipher Map, and §3.1 ROM paragraph.

### S7. Post bernoulli-types as arXiv preprint before submission (source: citation-verifier C1)
Three load-bearing citations to a "manuscript in preparation" is a reviewer risk. arXiv resolves this cleanly.

### S8. Address the Round 3 minor backlog as a single editorial pass (source: synthesis)
m1, m3, m5, m7, m8, m9, nm1, nm2, nm3 together represent maybe a half-day of editorial work. Doing them as one pass before the next major revision would make the paper noticeably tighter.

---

## Detailed Notes by Domain

### Logic and Proofs
All proofs are structurally correct. The Round 3 M4 (composition) and M5 (space optimality) inconsistencies are now resolved across all four restatements and the proof, respectively. One residual issue: Theorem 6.2 proof Step 2 has a notational sleight that reads as double-counting on first pass, though the final result is correct (MAJ-1). Two carryover minor proof issues (Stirling justification in Theorem 6.1, Poisson binomial citation in Proposition 6.3) and one new minor (union event wording in Theorem 7.1) round out the logic findings. The lower bound proof would benefit from one sentence explaining $\varepsilon = n/|U|$.

### Novelty and Contribution
The paper has two strong novel contributions (acceptance predicate unification, Shannon-frequency duality) and three or four moderate ones. The Round 3 M3 fix substantially improved the novelty positioning by making the contrast with leakage-abuse attacks and honey encryption explicit. The remaining novelty risks are framing risks: the abstract underclaims the duality (MAJ-3), and §9.5 disclaims standard frameworks without giving the parameterized-leakage style a positive label (MAJ-4). Both are cheap to fix and would substantially shift the paper's reception. The bigger risks (M1 missing security definition, M2 missing experiments) remain Round 3 issues.

### Methodology
The formal framework is sound. The Round 3 M5 reframing and M6 ROM paragraph fixes are clean. The §9.4 experimental paragraph is the largest methodology issue: hardware, query distribution, trial count, and baselines are all missing (MAJ-2). Several minor methodology issues persist from Round 3 (adversary model not formalized, hash construction notation inconsistent). One numerical claim (precision 0.39 "matching" $p_T = 0.05$) is internally consistent but worded misleadingly. The construction-time table at toy parameters ($m = 100$) limits external validity for PETS-relevant scales.

### Writing and Presentation
The prose is consistently clean and intellectually honest. The Round 3 M3 reorganization landed with high quality: new paragraphs read as crisp positioning rather than literature dumps. Three structural prose issues persist: the Discussion section is overloaded (seven subsections), the abstract sets a frame the paper later disclaims (MAJ-3), and several Round 3 minors were not addressed in this round ($K(x)$ notation, zero figures, "4th-order Bernoulli Boolean"). The honest limitations sections continue to be a strength.

### Citations and References
Bibliography integrity is excellent: 23 entries, all cited, all well-formed, no orphans. The Round 3 M3 additions (cash2015leakage, juels2014honey) are properly integrated. Four minor issues: bernoulli-types still unpublished, no DOIs, RecSplit named but not cited, phobic library mentioned without context.

### Formatting and Production
Build is clean: zero warnings, all references resolve, all citations resolve. The article class needs to be replaced with the PoPETs template before submission (page-count change). Anonymization not done (standard pre-submission). Zero figures despite TikZ source files being available in `paper/img/`.

---

## Literature Context Summary

The paper now engages with leakage-abuse attacks (Naveed 2015, Islam 2012, Cash-Grubbs 2015) and honey encryption (Juels-Ristenpart 2014). This addresses Round 3 M3 cleanly. Three additional citations would substantially strengthen the literature footing:

1. **Kerschbaum 2015** "Frequency-Hiding Order-Preserving Encryption" is the closest published predecessor for the frequency-hiding mechanism. The cipher maps mechanism (multiple representations $K(x) \propto 1/D(x)$) is functionally similar to Kerschbaum's randomized token assignment.

2. **Volume-hiding SSE** (Patel-Persiano-Yeo-Yung 2019; Kamara-Moataz 2019) is the SSE community's response to the same leakage-abuse attacks the paper cites. The paper's claim of "structural resistance" invites this comparison.

3. **Entropic security and QIF** (Dodis-Smith 2005; Smith 2009 or Alvim et al. 2012) would give §9.5's parameterized-leakage style a positive home in the literature, addressing MAJ-4.

The acceptance predicate unification is genuinely original. The Shannon-frequency duality is implicit in entropy-coded cipher constructions (e.g., honey encryption) but the explicit "duality" framing is novel.

The paper does not engage with recent PoPETs literature on encrypted indices, leakage frameworks, or privacy-preserving primitives. This is the strongest single signal that the literature footing for PoPETs is thin and would benefit from a brief survey of 2019-2024 PoPETs papers in adjacent areas.

---

## Honest Assessment of PoPETs Survivability

The user's specific question is whether the paper's current shape can survive PoPETs review with M1+M2 addressed. Honest answer:

**With M1 and M2 properly addressed: Likely accept-or-minor-revision.** The conceptual contribution (acceptance predicate unification + Shannon-frequency duality) is real and publishable. The four-property framework is a useful synthesis. With a formal security definition (M1) and a real experimental section with baseline comparisons (M2), the paper would have a credible case at PoPETs.

**With only M1 addressed: Likely major-revision.** A formal security definition without experimental validation positions the paper as theory; PoPETs accepts theory papers but expects experimental backing for primitives intended for practical use.

**With only M2 addressed: Likely major-revision or reject.** Experimental validation without a security definition leaves the four "$U$ cannot ..." claims (Definition 5.2) unsubstantiated by formal argument. PoPETs reviewers will press on this.

**Without addressing M1 and M2: Likely reject.** The paper would read as theory without security proofs and applications without experimental backing.

Beyond M1 and M2, the highest-impact editorial moves are:
- MAJ-3 (abstract framing) and MAJ-4 (positive label for §9.5) together cost a few hours and would substantially shift the paper's reception.
- S1 (three high-priority citations) costs an hour and forecloses the "the author isn't tracking the literature" reaction.
- MAJ-2 (experimental paragraph reproducibility) is independent of M2 work; even minimum-effort fixes substantially help.
- m10 / S7 (post bernoulli-types as arXiv) eliminates a reviewer risk.

**Most efficient path forward**: spend 1-2 days on the editorial cleanup (MAJ-1 through MAJ-5, plus the carry-over Round 3 minors), then begin M1 (security definition). The editorial work substantially reduces the perceived size of the M1+M2 gap.

---

## Review Metadata
- **Specialists**: literature-scout (broad and targeted, merged), logic-checker, methodology-auditor, novelty-assessor, prose-auditor, citation-verifier, format-validator
- **Cross-verifications performed**: 4
  - L1 (Theorem 6.2 Step 2 notational sleight) cross-verified by methodology check on the arithmetic; confirmed correct in result, misleading in presentation. Severity retained as MAJOR.
  - MAJ-3 (abstract framing) cross-verified by novelty-assessor (independently flagged as N1). Same root cause.
  - MAJ-5 (ROM paragraph count) cross-verified by three specialists (logic-checker, prose-auditor, methodology-auditor). Treated as one issue.
  - M-A5 (precision = 0.39 "matching" p_T = 0.05) cross-verified by recomputation: numerically consistent, wording misleading. Severity: MINOR.
- **Disagreements noted**: 0 substantive
- **Round 3 issues checked**:
  - M3 (citations): VERIFIED FIXED
  - M4 (composition formula): VERIFIED FIXED across all four restatements
  - M5 (space optimality): VERIFIED FIXED with new Remark 6.3
  - M6 (ROM): VERIFIED FIXED, with the count discrepancy noted as MAJ-5
  - M1 (security definition): NOT addressed (per user expectation)
  - M2 (experimental evaluation): partially addressed (one paragraph in §9.4); see MAJ-2
  - Round 3 minors m1, m2, m3, m4, m5, m7, m8, m9, m10, m11: NOT addressed; carried forward
