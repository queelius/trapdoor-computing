# Iteration Review: Maximizing Confidentiality in Encrypted Search
Date: 2026-03-20
Reviewer: Claude Opus 4.6 (deep iteration pass)
Paper: `papers/maximizing-confidentiality/main.tex` (~2555 lines, 51 pages)
Context: Second-pass review after 5 fixes (3 original + 2 residual) were applied

---

## 1. Fix Consistency Propagation

### 1A. Joint Max Entropy Formula Consistency

**Status: MAJOR -- pre-existing inconsistency between Section 5 and Section 7 remains**

The paper contains two independent derivations of the constrained/joint maximum entropy formula:

- **Section 5** (lines 1148-1173): Constrained maximum entropy theorem. The theorem statement (line 1151) uses:
  ```
  H*(lambda, k, M, n, p) = n * (H*(T|lambda) + H*(A|k) + H*(X|M,p))
  ```
  The proof conclusion (line 1170) uses different parameters:
  ```
  H*(lambda, mu, k, m, n) = n * (H*(T|lambda) + H*(A|k) + H*(N,X|mu,m))
  ```
  These two formulas disagree in both parameter names (M vs m; includes p in one but not the other) and term structure (three separate terms vs. a joint (N,X) term). The fix comment at line 1145 correctly removed the result set term H*(R|N), and line 1168 now explains that result sets contribute no independent entropy. However, the two sub-formulas within this section still disagree with each other.

- **Section 7** (lines 1641-1645): Joint maximum entropy theorem. This is the canonical, fixed version:
  ```
  H*_n = n * [H*(T) + H*(A) + H*(N_trap) + E[N_trap] * H*(Y)]
  ```
  This version correctly decomposes query entropy into cardinality + trapdoor selection and omits result sets.

**The Section 5 formula (line 1151) and Section 7 formula (line 1643) are structurally inconsistent.** Section 5 has `H*(X|M,p)` as a single blob; Section 7 decomposes it into `H*(N_trap) + E[N_trap]*H*(Y)`. Section 5's proof at line 1170 uses `H*(N, X | mu, m)` which is closer to Section 7 but uses different notation (X vs Y, joint notation vs additive). Fix 2 correctly updated Section 7 but the Section 5 versions were not harmonized.

Additionally, the empty paragraph headings at lines 1243-1245:
```latex
\paragraph{Solution for $\entropy^*(\rvhqb \given M,p)$.}
\paragraph{Solution for $\entropy^*(\rv{\mathbb{D}} \given N)$}
```
remain as placeholders with no content. The result set placeholder (H*(D|N)) should be deleted entirely (consistent with the fix removing result set terms), and the query bag placeholder should either be filled or the reader directed to Section 7.

**Severity: MAJOR.** A reader encountering Section 5 first will see a formula that disagrees with the canonical Section 7 version.

**Recommendation:** Delete or heavily condense Section 5's theorem (lines 1148-1174), replacing it with a forward reference: "We derive the full constrained maximum entropy in Section 7 (Theorem X)." This also addresses the redundancy flagged in the thesis refinement.

### 1B. Inter-Arrival Entropy Fix Propagation

**Status: PASS -- no downstream inconsistencies**

Fix 1 corrected the quantized inter-arrival entropy formula at line 1201. The verification report correctly noted that no other locations reference this specific formula. Confirmed:
- The proof body (line 1217) matches the theorem statement.
- The asymptotic form (line 1205) is consistent.
- The appendix derivation (line 2406) derives the same closed-form.
- The continuous version at lines 1179 and 1546 is a separate (correct) result and was not affected.
- No numerical examples or tables in the case study use the quantized inter-arrival entropy formula directly; the case study works with per-trapdoor entropy.

### 1C. Mixture Entropy Fix Propagation

**Status: PASS with MINOR arithmetic issue**

Fix 3 correctly changed the mixture entropy from equality to lower bound (line 2213). The formula now reads:
```
H(X_combined) >= 0.67 * 23.49 + 0.33 * 39.87 ~ 28.90
```

Checking downstream:
- Table 5 (line 2243): Reports "Artificial queries only" efficiency as 0.72. The formula at line 2219 gives 28.90/39.87 = 0.725, which rounds to 0.72. **Consistent.**
- Combined strategy efficiency of 0.85 (line 2244): Not derived from the mixture entropy alone; it combines homophonic + artificial queries. The paper states this as an approximate figure without derivation. **Acceptable as approximate.**

**MINOR: Arithmetic discrepancy.** The formula evaluates to 0.67*23.49 + 0.33*39.87 = 15.7383 + 13.1571 = 28.8954, which the paper rounds to 28.90. The previous version said 28.86. The fix changed the displayed value from 28.86 to 28.90, which is the correct arithmetic. However, the efficiency (line 2219) says "approximately 0.72" and 28.90/39.87 = 0.7249, so the 0.72 figure is slightly low (should be ~0.72 or ~0.73). This is cosmetic.

### 1D. Result Set Entropy Removal Propagation

**Status: MAJOR -- Section 7 has an orphaned result set max-entropy theorem**

The joint max entropy formula (line 1643) correctly omits result set terms after Fix 2. The remark (line 1650) correctly explains why. Section 8 (line 1683) correctly states H(Q,R) = H(Q).

However, **Section 7.5 "Maximum Entropy for Result Sets" (lines 1626-1631) still contains Theorem 7.5 stating the max-entropy distribution for result set cardinality** -- a result that is never used. The joint formula no longer includes any result set terms, so this theorem is dead code. It also has no proof and is imprecisely stated ("geometric or Poisson-like").

**Severity: MAJOR.** This theorem contradicts the paper's own reasoning that result sets add no independent entropy. Its presence confuses the reader about whether result sets contribute to H*.

**Recommendation:** Delete Section 7.5 entirely, or add a brief note: "For completeness, we note the marginal maximum entropy of result set cardinality, though this does not appear in the joint formula because H(R|Q) = 0."

### 1E. Figures and Plots

**Status: PASS -- no plots depend on changed formulas**

Figure 3 (lines 1744-1787) plots accuracy vs. sample size from external data files, parameterized by Zipf exponent s. These data files are simulation results, not derived from the entropy formulas that were changed. The plot is unaffected by the fixes.

Figure 4 (lines 1790-1823) shows a Zipf PMF and homophonic encryption example, also unaffected.

Figure 5 (line 2044-2050) shows inter-arrival time obfuscation, also unaffected.

---

## 2. Remaining Proof Issues

### 2A. NO-PROOF-GIVEN Claims (2 of 22)

**Claim 14: Maximum entropy for result set cardinality (lines 1629-1631)**
Status: Still no proof given. Statement is imprecise ("geometric or Poisson-like").
**Recommended action: DELETE.** Since result sets have been correctly removed from the joint formula (Fix 2), this theorem serves no purpose. Deleting it resolves both the missing proof and the conceptual inconsistency. If retained for marginal analysis, the correct answer is "truncated geometric" and a proof should be given by analogy with Claim 12.
**Severity: MAJOR** (due to inconsistency with the rest of the paper, not just the missing proof)

**Claim 18: Artificial trapdoor entropy theorem (lines 1906-1910)**
Status: Still incomplete. The theorem states:
```
H*(L, Y) = H*(L | mu_L, Y)
```
This is mathematically meaningless as written -- the RHS conditions on Y but also includes Y in the LHS joint. No proof is given.
**Recommended action:** Either complete the statement and proof (the intended decomposition is likely H*(L,Y) = H*(L) + E[L]*H*(Y) by analogy with the query cardinality decomposition), or delete and replace with prose noting the analogy to the query bag decomposition.
**Severity: MAJOR.** This is a key result for Section 8's artificial trapdoors technique.

### 2B. LIKELY-CORRECT Claims (3 of 22)

**Claim 6: Joint distribution corollary (lines 1249-1258)**
On closer inspection: **MINOR ERROR confirmed.** Line 1255 contains a LaTeX syntax error:
```latex
2^{-\alpha) m}
```
The closing parenthesis `)` should be `}`, giving `2^{-\alpha m}`. This will produce a LaTeX compilation error or incorrect rendering. The mathematical content (product of geometric * uniform * uniform) is correct modulo this typo.
**Severity: MINOR** (typo, but may cause compilation failure).

**Claim 7: MLE of maximum entropy (lines 1262-1286)**
On closer inspection: Remains LIKELY-CORRECT. The proof sketch at line 1285 ("Continue on in the same fashion") is not a proof. The m-hat description ("number of unique trapdoors in the sample") is actually the wrong estimator for m under a uniform model -- the MLE should be the maximum observed trapdoor value, not the count of distinct values. However, this is a minor imprecision since the paper works with bit-string trapdoors where the vocabulary size is 2^m (a known constant), not an unknown parameter.
**Severity: MINOR.**

**Claim 11: Expected compressed bit length (lines 1443-1479)**
On closer inspection: Remains LIKELY-CORRECT but mislabeled. The theorem title says "optimally compressed" but the encoding uses unary codes, which are only optimal for Geo(1/2). For general lambda and mu, the optimal code would yield shorter expected lengths equal to the entropy. The computed value (1/lambda + p + mu*(1+m)) is the expected code length for the specific encoding scheme described, not the entropy.
**Severity: MINOR** (labeling error, not mathematical error).

### 2C. Did Fixes Affect VERIFIED Claims?

**No.** The 10 VERIFIED claims (Claims 1, 3, 5, 9, 10, 12, 13, 17, 19 [plausible], 21) are all independent of the three formulas that were changed:
- Fix 1 (inter-arrival entropy) only affected Claim 4's theorem statement, now matching the proof.
- Fix 2 (result set removal from joint formula) only affected Claim 15 and surrounding text.
- Fix 3 (mixture entropy inequality) only affected Claim 20.

None of the verified claims reference or depend on the changed formulas.

### 2D. Additional Proof Issues Identified This Pass

**Asymptotic H* corollary (lines 1314-1322): ERROR persists.**
The corollary claims:
```
H*_n(m, k, lambda, mu) = n * (log2(mu*k/lambda) + mu*(m+1) + const)
```
where const = 2*log2(e). The term `mu*(m+1)` confuses expected code length with entropy. The correct asymptotic maximum entropy should be:
```
n * (log2(1/lambda) + log2(e) + log2(k) + H*(Geo(1/mu)) + mu*log2(m))
```
where H*(Geo(1/mu)) ~ log2(mu) + log2(e) for large mu. This gives:
```
n * (log2(mu*k/lambda) + 2*log2(e) + mu*log2(m))
```
The paper's `mu*(m+1)` = mu*m + mu, while the correct term is mu*log2(m) + log2(mu) + log2(e). For m=10000 and mu=3: paper gives 3*10001 = 30003 bits; correct gives 3*13.29 + 1.58 + 1.44 = 42.89 bits. The paper's formula is off by orders of magnitude.
**Severity: MAJOR.** Although the corollary is embedded in a proof and labeled as an "asymptotic form," it gives wildly wrong numbers. It confuses m (vocabulary size, e.g., 10000) with m (bits per trapdoor, e.g., 128) throughout.

**Unit inconsistency: Nats vs bits.** The inter-arrival time entropy is consistently expressed in nats (natural logarithm): H*(T) = 1 + ln(1/lambda). All other entropies use bits (log base 2). The joint formula at line 1643 adds these together without conversion. Appendix A (line 2429) acknowledges: "Note that we use natural logarithm for differential entropy of continuous distributions, while discrete entropy uses logarithm base 2." But no conversion is performed when the terms are summed.
**Severity: MAJOR.** The joint maximum entropy formula adds nats and bits. For lambda=0.1, H*(T) = 1 + ln(10) = 3.30 nats = 4.76 bits. The difference (1.46 bits) is significant relative to other component entropies (log2(10) = 3.32 bits for agents).

---

## 3. USENIX Readiness

### 3A. Redundancy: Sections 5, 6, and 7

The paper derives maximum entropy results three times:

1. **Section 5 "Principle of maximum entropy"** (lines 1140-1359): First pass. Derives constrained max entropy, inter-arrival time (continuous + quantized), agent identity, MLE estimator, compression estimator, efficiency metric. Contains the inconsistent formula pair (line 1151 vs 1170), empty paragraph placeholders, and the erroneous asymptotic corollary.

2. **Section 6 "Maximum entropy system"** (lines 1363-1516): Second pass. Restates total system entropy (trivial chain rule), agent identity max entropy (same as Section 5), unary code optimality claims, code tables, and the "expected optimally compressed bit length" theorem. Heavy overlap with Section 5 for the identity and timing results.

3. **Section 7 "Maximum Entropy Under Constraints"** (lines 1517-1680): Third pass. Cleanest derivation. Properly states system constraints, derives each component, states the joint maximum entropy (the canonical fixed version), proves it, and derives the minimum mutual information corollary.

**Assessment:** Section 7 is the definitive version. Sections 5 and 6 are earlier drafts that were never removed. Section 5 contributes the compression estimator and efficiency metric (not in Section 7), while Section 6 contributes the code tables and expected code length (not entropy-related).

**CRITICAL recommendation for USENIX cut:** Merge Sections 5, 6, and 7 into a single section. Keep Section 7's theorem statements and proofs. Bring in the efficiency metric definition (from Section 5, line 1342) and compression estimator (from Section 5, line 1294). Move code tables and expected code length analysis to appendix. Delete everything else that is duplicated.

**Estimated savings:** Sections 5+6 are ~380 lines; after extracting the unique content (~80 lines), deleting the rest saves ~300 lines (~6 pages).

### 3B. Unfinished Sections

| Location | Issue | Severity |
|----------|-------|----------|
| Lines 1015-1018 | Algorithm 4: Empty `params` field | MAJOR |
| Lines 1019-1021 | Algorithm 4: Empty `input` field | MAJOR |
| Lines 1034-1035 | Algorithm 4: Placeholder text ("some anonymizer, like a mixnet", "something that delays sending hidden query up to some limit") | MAJOR |
| Lines 1243-1244 | Empty paragraph heading "Solution for H*(X\|M,p)" | MINOR |
| Lines 1245-1245 | Empty paragraph heading "Solution for H*(D\|N)" -- should be deleted per result set fix | MINOR |
| Lines 2072-2078 | Raw notes: "Queue discipline: FCFS discipline..." followed by unfinished prose | MAJOR |
| Lines 2083-2083 | Sentence cut off mid-word: "due to the bu" | MAJOR |
| Lines 2085-2091 | Blank lines and dangling fragments | MINOR |
| Line 1791 | Figure caption "Testing" -- placeholder | MINOR |
| Lines 2004-2007 | Equations that lead nowhere -- incomplete derivation of injecting artificial search agents | MINOR |
| Line 1983 | Sentence fragment: "An onion network is another type of overlay network..." | MINOR |

**For USENIX:** Algorithm 4 should be completed or deleted. The raw notes at lines 2072-2091 must be deleted. The placeholder figure caption must be fixed.

### 3C. Minimum Viable Paper for USENIX (13 pages)

Following the thesis refinement's recommendation, the minimum viable paper would be:

**Body (~13 pages):**
1. Introduction + contributions (1.5 pp) -- trim from 7 to 4 contributions
2. Related work (1 pp) -- condense current 1.5 pp
3. Encrypted search model (1.5 pp) -- keep Definitions 3.1-3.6, Algorithms 1-3; move Algorithm 4 to appendix
4. Entropy framework + metric (1.5 pp) -- entropy definition, efficiency ratio, compression estimator; cite Shannon (not "Postulate 5.1")
5. Maximum entropy derivations (2 pp) -- single clean pass using Section 7 versions; state theorems, move proofs to appendix
6. Techniques for increasing entropy (2 pp) -- homophonic encryption, artificial queries, timing obfuscation; focus on entropy gains and costs
7. Case study (2 pp) -- Table 5 and the 59% -> 85% result; condense Scenarios 2-3 to one paragraph each
8. **Experimental validation (1 pp) -- TO BE WRITTEN** -- synthetic query streams, compression measurement, validation
9. Conclusion (0.5 pp)

**Appendix (~unlimited for USENIX extended version):**
- All detailed proofs
- Algorithm pseudocode for Algorithm 4
- Code tables
- Appendices A-D as currently written

**What must be written or significantly revised:**
1. Experimental validation section (does not exist)
2. Formal adversary model paragraph (current version at line 1367 is a start but needs attack game)
3. Merge of Sections 5/6/7 into one coherent section
4. Resolution of all unfinished content listed in 3B

**Estimated effort:** Major restructuring (2-3 days of focused work), plus new experimental validation section (1-2 days).

### 3D. Content That Can Be Cut Entirely

- Section 6 "Maximum entropy system" (lines 1363-1516): Redundant with Section 7. Unique content (efficiency metric, code tables) can be moved.
- Unary coder discussion (Table 2, lines 1499-1516): Tangential.
- SA code table (Table 1, lines 1481-1497): Tangential.
- Multiple secure indexes subsection (lines 1697-1717): Tangential technique not used in case study.
- Artificial secure indexes subsection (lines 1719-1723): Very brief, undeveloped.
- Query aggregation subsection (lines 1879-1884): One paragraph, no analysis.
- Injecting artificial search agents subsection (lines 1989-2007): Incomplete derivation.
- Obfuscating inter-arrival times queuing theory (lines 2016-2091): Mostly unfinished notes.

Total estimated savings: ~500 lines (~10 pages).

---

## 4. Trapdoor Reframing Status

### 4A. Current State

The paper has **zero explicit connections** to the trapdoor computing framework. The term "trapdoor" appears extensively but only in the encrypted search sense (a one-way hash of a search term). The words "cipher map," "Property 1," "Property 2," "Representation Uniformity," "Totality," and "trapdoor computing" do not appear anywhere in the paper.

The state file (`.papermill/state.md`, line 54) notes:
> Trapdoor reframing pending: homophonic encryption = Property 2 (Representation Uniformity), filler queries = Property 1 (Totality).

### 4B. Natural Connection Points

The connections are conceptually sound but not yet articulated:

1. **Homophonic encryption = Property 2 (Representation Uniformity).**
   - Cipher map Property 2 requires that the ciphertext distribution be (approximately) uniform regardless of the plaintext input distribution.
   - Homophonic encryption (Algorithm 5, Section 8.3) does exactly this: it gives frequent words more ciphertext substitutions to flatten the trapdoor distribution toward uniform.
   - The entropy efficiency metric e_trap = H(Y)/H*(Y) = H(Y)/log2(m) directly measures how close the system is to achieving Property 2.
   - Location to insert: After the efficiency metric definition (line 1342) or in the homophonic encryption subsection (line 1726).

2. **Filler queries = Property 1 (Totality).**
   - Cipher map Property 1 requires that the cipher map be total (every input maps to something), which in the encrypted search context means every time slot has a query -- no gaps that leak information about when authentic activity occurs.
   - Artificial query injection (Section 8.7) fills timing gaps with fake queries, making the query stream appear total/continuous.
   - The arrival rate analysis (Poisson superposition, line 2030) shows that authentic + artificial queries merge into a single exponential process.
   - Location to insert: In the artificial queries subsection (line 1934).

3. **The efficiency metric itself maps to the cipher map correctness parameter eta.**
   - Cipher map Property 3 requires eta-bounded correctness. The entropy efficiency e = H/H* is an information-theoretic analogue: it measures how close the system's observable distribution is to the ideal (maximum entropy = zero leakage).
   - The gap (1 - e) corresponds to exploitable leakage, analogous to 1 - eta being the error probability.

4. **Composability (Property 4).**
   - The decomposition of joint entropy into independent components (timing + identity + query content) parallels cipher map composability: the overall system's confidentiality decomposes into independently improvable components.

### 4C. Work Remaining

**Minimal reframing (1-2 paragraphs):** Add a subsection or remark in the Introduction connecting the entropy framework to the trapdoor computing paradigm. State that the encrypted search system is an instance of a cipher map where the obfuscator implements the encoding function, the ESP implements the cipher map evaluation, and the search agent implements the decoding. Note the correspondence between the four properties and the paper's entropy-based analysis.

**Full reframing (more substantial):** Rewrite the model section to define the encrypted search obfuscator as a cipher map, derive the properties formally, and show that the entropy efficiency metric quantifies Property 2 compliance. This would require revising Sections 3-5.

**Recommendation:** For USENIX, the minimal reframing is sufficient -- add one paragraph in the Introduction and one in the Conclusion connecting to the broader trapdoor computing framework. For a companion paper in the trapdoor-computing series, the full reframing would be needed.

---

## 5. Summary of All Issues

### CRITICAL (blocks submission)

| # | Issue | Location | Action |
|---|-------|----------|--------|
| C1 | Sections 5/6/7 derive the same results three times, with inconsistent formulas | Lines 1140-1680 | Merge into single section using Section 7 as base |
| C2 | Paper is 51 pages; USENIX limit is 13 | Entire paper | Major restructuring per Section 3C above |
| C3 | No experimental validation | Missing | Write synthetic experiment section |

### MAJOR (must fix before submission)

| # | Issue | Location | Action |
|---|-------|----------|--------|
| M1 | Section 5 constrained max entropy has inconsistent formulas (line 1151 vs 1170) | Lines 1148-1174 | Delete or replace with forward reference to Section 7 |
| M2 | Orphaned result set max-entropy theorem (no proof, contradicts fix) | Lines 1626-1631 | Delete or demote to remark |
| M3 | Asymptotic H* corollary confuses code length with entropy; mu*(m+1) is wrong | Lines 1314-1322 | Fix formula or delete corollary |
| M4 | Nats vs bits unit inconsistency in joint formula | Lines 1179, 1546, 1643 | Convert to bits consistently |
| M5 | Artificial trapdoor entropy theorem: incomplete, mathematically meaningless | Lines 1906-1910 | Complete or delete |
| M6 | Algorithm 4 has empty fields and placeholder text | Lines 1011-1040 | Complete or delete |
| M7 | Raw unfinished notes in text | Lines 2072-2091 | Delete |
| M8 | Attack resistance numbers (70%/35%) unsupported | Lines 2257-2261 | Derive, document simulation, or remove |
| M9 | No formal adversary model / security game | Line 1367 | Add formal definition per thesis refinement |

### MINOR

| # | Issue | Location | Action |
|---|-------|----------|--------|
| m1 | LaTeX syntax error: `2^{-\alpha) m}` (mismatched paren) | Line 1255 | Fix to `2^{-\alpha m}` |
| m2 | Indicator function typo: `k in {1,...,k}` should be `a in {1,...,k}` | Line 1235 | Fix |
| m3 | "Optimally compressed" mislabel for unary code | Lines 1443-1444 | Relabel as "expected encoded bit length" |
| m4 | Postulate 5.1 should cite Shannon's theorem, not be called a postulate | Lines 1098-1113 | Cite Shannon |
| m5 | Empty paragraph headings | Lines 1243-1245 | Delete H*(D\|N); fill or redirect H*(X\|M,p) |
| m6 | Figure caption "Testing" is a placeholder | Line 1791 | Fix |
| m7 | Sentence cut off mid-word ("due to the bu") | Line 2083 | Delete or complete |
| m8 | "Consquently" typo | Line 1683 | Fix spelling |
| m9 | "geoemtric" typo | Line 1215 | Fix spelling |
| m10 | Missing closing paren: `$\entropy(\rvhrs[i] \given \rvhqb[i]$` | Line 1689 | Add closing paren |

### SUGGESTION

| # | Suggestion | Context |
|---|-----------|---------|
| S1 | Add minimal trapdoor computing reframing (1-2 paragraphs) | Introduction and Conclusion |
| S2 | Add compression-based entropy experiment on synthetic data | Validates core claim practically |
| S3 | Discuss why Shannon entropy (not min-entropy) suffices, or add min-entropy analysis | Addresses reviewer concern |
| S4 | Connect to SSE leakage literature (Curtmola L1/L2, Cash leakage-abuse) | Positions paper in security community |
| S5 | State that i.i.d. assumption yields conservative (lower) bound on efficiency | Turns limitation into feature |

---

## 6. Recommended Priority Order

1. **Merge Sections 5/6/7** into a single coherent section (resolves C1, M1, M3, and many minor issues)
2. **Delete orphaned result set theorem** at lines 1626-1631 (resolves M2)
3. **Fix nats/bits unit inconsistency** throughout (resolves M4)
4. **Delete unfinished content**: Algorithm 4 placeholders, raw notes at lines 2072-2091, empty headings (resolves M6, M7, m5, m7)
5. **Complete or delete artificial trapdoor entropy theorem** (resolves M5)
6. **Cut paper to 13 pages** following the structure in Section 3C (resolves C2)
7. **Write experimental validation** (resolves C3)
8. **Add formal adversary model** (resolves M9)
9. **Address attack resistance numbers** (resolves M8)
10. **Fix all minor issues** (m1-m10)
11. **Add trapdoor computing reframing** (S1)

Steps 1-5 are preparatory cleanup. Steps 6-8 are the substantive work needed for USENIX submission. Steps 9-11 strengthen the paper but are not strictly blocking.
