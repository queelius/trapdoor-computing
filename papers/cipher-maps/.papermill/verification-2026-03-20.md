# Verification Report: cipher-maps (rebuilt)
Date: 2026-03-20

## Proof Verification

| # | Claim | Verdict | Notes |
|---|-------|---------|-------|
| 1 | **Prop 3.1** (Entropy map space) | **PASS** | Proof correctly decomposes space into noise-rejection ($-\log_2 \varepsilon$) and value-encoding ($H(Y)$) components, citing Shannon's source coding theorem. Additivity claim is justified by disjoint bit allocation. |
| 2 | **Prop 3.2** (Membership FP rate) | **PASS** | Proof correctly derives $\varepsilon_{\in}(k,n) = (1 - 2^{-(k+1)})^n$. Each bit independently rejects with probability $2^{-(k+1)}$ (product of $\Pr[h(x)_j=1]=1/2$ and $\Pr[F(W)_j=0]=2^{-k}$). All $n$ bits must pass. Sound under ROM. |
| 3 | **Prop 6.1** (AND gate correctness) | **PASS** | The (1,0) case is verified in detail: wrong output requires $B_1=1$ (prob $p_1$) AND $B_2=1$ (prob $1-p_2$), giving $\Pr[\text{correct}] = 1 - p_1(1-p_2)$. The other three cases follow analogously and are stated correctly in the table. |
| 4 | **Thm 6.2** (Composition correctness) | **PASS** | Union bound gives $\eta_f + \eta_g$. Tight bound under independence gives $(1-\eta_f)(1-\eta_g)$ for joint correctness, yielding $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$. Assumptions (independent seeds, re-randomization) are explicitly stated. The remark on the independence assumption honestly notes this is best understood as an upper bound when re-randomization does not hold. |
| 5 | **Cor 6.3** (Chain composition) | **PASS** | Induction on Thm 6.2 is correct. Base case $m=2$ is the theorem. Inductive step: composing $m-1$ maps with error $1 - \prod_{i=1}^{m-1}(1-\eta_i)$ with map $m$ gives $1 - \prod_{i=1}^m (1-\eta_i)$. Small-$\eta$ approximation via $\ln(1-\eta) \approx -\eta$ is standard. |
| 6 | **Thm 5.1** (Lower bound) | **MINOR-ISSUE** | The proof structure is correct: membership component requires $n \log_2(1/\varepsilon)$ bits (counting argument, cite Bloom 1970), value component requires $nH(Y)$ bits (Shannon). The claim "both components are jointly necessary" is stated but the argument for independence/additivity of the two requirements could be more rigorous -- it relies on the implicit assumption that the noise-rejection and value-encoding bits occupy disjoint portions of storage, which is true for the constructions but is asserted rather than formally proved as a general lower bound. |
| 7 | **Thm 5.3** (Space complexity of Singular Hash Map) | **PASS** | Four-step proof is clear: (1) false negative reduction to $(1-\eta)n$ elements, (2) per-element cost from prefix-free code under ROM, (3) false positive control via $-\log_2 \varepsilon$ additional bits, (4) multiplication gives $(1-\eta)n(-\log_2 \varepsilon + \mu)$. The corollary for $\eta=0$ matching the lower bound follows immediately. |
| 8 | **Prop 5.4** (Expected construction trials) | **PASS** | Under ROM, hash values for distinct elements are independent. Per-element success probability $2^{-|c_{y_i}|}$ gives failure probability $e_i = 1 - 2^{-|c_{y_i}|}$. Product formula for joint success follows from independence. Geometric distribution with parameter $p$ gives expected trials $1/p$. |
| 9 | **Prop 7.1** (Granularity and privacy) | **PASS** | First part follows directly from Def 2.2 applied to joint cipher map. Second part: even with $\delta=0$ marginal uniformity, deterministic $\enc_i(x_i, k_i)$ preserves the correlation structure of $(x_1, x_2)$ under $D$ in the joint cipher value distribution. The proof correctly identifies that marginal uniformity is a single-observation property insufficient for joint hiding. |

**Summary**: 8 PASS, 1 MINOR-ISSUE. All proofs are logically valid. The only minor concern is that the lower bound theorem (Thm 5.1) could state the additivity of the two components more carefully as an information-theoretic argument.


## Definition Precision

| Definition | Assessment |
|------------|------------|
| **Def 2.1** (Cipher map) | Precise. Four-tuple $(\hat{f}, \enc, \dec, s)$ with types specified. $K$ is introduced but not explicitly defined until Def 2.2 -- this is acceptable since it appears as a range parameter. Consistent with formalism Def 1.1. |
| **Def 2.2** (Totality) | Precise. States $\hat{f}(c) \in \{0,1\}^n$ for all $c$, plus distributional property on out-of-image inputs under ROM. Matches formalism Property 1. |
| **Def 2.3** (Representation uniformity) | Precise. Formally defines induced distribution $Q(c)$ and requires $d_{\mathrm{TV}}(Q, \mathrm{Uniform}) \leq \delta$. All symbols defined. Matches formalism Property 2. |
| **Def 2.4** (Correctness) | Precise. Probability over uniform $x \in X$ and uniform $k$. Matches formalism Property 3. |
| **Def 2.5** (Composability) | Precise. Defines composition as function composition $\hat{g} \circ \hat{f}$ and states the correctness formula. Matches formalism Property 4. **Note**: This is slightly unusual as a "definition" since it contains a derived result (the formula), but the formalism doc also bundles them. Acceptable since the proof is deferred to Section 6. |
| **Def 5.1** (Trusted machine) | Precise. Enumerated capabilities. Consistent with formalism Def 5.1. |
| **Def 5.2** (Untrusted machine) | Precise. Enumerated capabilities and limitations. Consistent with formalism Def 5.2. |
| **Def 7.1** (TV distance) | Precise. Standard definition with both summation and max formulations. Matches formalism Def 4.1. |
| **Def 7.2** (Encoding granularity) | Precise. Defines granularity as the type $X$. Matches formalism Def 4.2. |
| **Def 7.3** (Entanglement parameter) | Precise. Defines $p$ and the type $\mathrm{cipher}(\{0,1\}^p)^{k/p}$. Matches formalism Def 4.3. |

**All definitions are mathematically precise with no informal bullets used as definitions.** All symbols are defined at point of use or referenced.


## Internal Consistency

### Notation consistency
- $\hat{f}$ (`\fhat`) used consistently for cipher maps throughout.
- $\enc$, $\dec$ used consistently for encoding/decoding.
- $\eta$, $\varepsilon$, $\mu$, $\delta$ used consistently with the parameter table (Table 1).
- $K(x)$ introduced in Def 2.1 (as range of $k$) and used consistently in Defs 2.2, 2.4.
- $d_{\mathrm{TV}}$ notation is consistent between Def 2.2 and Def 7.1.

### Cross-references
- Def 4.1 (composability) correctly references eq (6) and defers proof to Section 6. Section 6 (Thm 6.2) proves it. **Consistent.**
- Section 4 constructions correctly reference Property 1-4 from Section 3. **Consistent.**
- Remark 2.2 (marginal uniformity only) is referenced from Section 4.3 (trapdoor Boolean algebra) and Section 7.2 (encoding granularity). **Consistent.**
- Table 2 (comparison) correctly summarizes the parameter instantiations from Sections 4.1-4.3. **Consistent.**
- Corollary after Thm 5.3 correctly references Thm 5.1 (lower bound). **Consistent.**

### Concrete constructions vs. abstract properties
- **HashSet** (Section 4.1): Correctly identified as satisfying Totality (yes), Rep Uniformity (no, $K=1$), Correctness ($\eta=0$), Composability (yes). $\varepsilon = 2^{-n}$. **Consistent** with abstract definitions.
- **Entropy Map** (Section 4.2): Correctly identified as satisfying all four properties with appropriate qualifications. Space formula $-\log_2 \varepsilon + H(Y)$ is consistent with eq (9). **Consistent.**
- **Trapdoor Boolean Algebra** (Section 4.3): Correctly identified with Totality (yes), Rep Uniformity (marginal only), Correctness (partial -- union exact, intersection/NOT approximate). **Consistent** with abstract definitions and formalism errata notes.

### Minor inconsistency found
- In the cipher map definition (Def 2.1), $\enc$ takes $K{-}1$ as the upper bound of the second argument: $\enc : X \times \{0, \ldots, K{-}1\} \to \{0,1\}^n$. But later, $K(x)$ is element-dependent (Def 2.3, 2.4). The definition should use $K(x)-1$ rather than a global $K-1$. The formalism doc uses global $K$ in Def 1.1 too, so this is inherited. **MINOR-ISSUE**: Both paper and formalism use global $K$ in Def 1.1 but element-dependent $K(x)$ in Properties 2-3.

**Overall**: Internal consistency is strong. One minor inherited inconsistency in the $K$ vs $K(x)$ notation.


## Formalism Alignment

### Section-by-section comparison

| Paper Section | Formalism Section | Status |
|---------------|-------------------|--------|
| S2 (Abstraction) | F1 (Cipher Map Abstraction) | **ALIGNED** -- Def 2.1, two construction strategies, construction layers, values-as-functions remark all match. |
| S3 (Four Properties) | F1.3 (Four Properties) | **ALIGNED** -- All four properties match. Parameter table matches. Space decomposition eq (9) matches. |
| S4 (Constructions) | F2 (Concrete Constructions) | **ALIGNED** -- All three constructions match. Errata corrections from formalism (intersection approximate, NOT degrades with set size, subset predicate correction) are incorporated correctly. |
| S5 (Trust Model) | F5 (Trusted/Untrusted) | **ALIGNED** -- Definitions of $T$ and $U$ match. Information flow protocol matches. Guarantee table matches. Reseeding capability included. |
| S6 (Composition) | F3 (Composition Theorem) | **ALIGNED** -- AND gate warm-up matches. General theorem matches. Chain composition matches. Interval arithmetic mentioned. |
| S7 (Uniformity) | F4 (Rep Uniformity & Granularity) | **ALIGNED** -- TV distance definition, encoding granularity principle, entanglement parameter, honest limitations all match. |
| S8 (Discussion) | F6 (Summary) | **ALIGNED** -- Open questions match formalism's open questions. |

### What's in the formalism but missing from the paper

1. **Errata notes** from formalism Section 2.3 (blog post's reversed `F(cap) = |` / `F(cup) = &`, and reversed subset predicate `a | b = a`): These corrections are silently incorporated into the paper without explicitly noting the blog post errors. This is appropriate for a paper (errata notes belong in the formalism doc, not the paper).

2. **Formalism Section 2.3.1** (Marginal Uniformity appendix material): The paper covers this in Remark 2.2 and Section 7, which is adequate.

3. **Formalism Section 4.3** (Entanglement parameter spectrum table): The paper includes Definition 7.3 and the three granularity levels but omits the full spectrum table ($p=1,2,p,k$). **MINOR GAP** -- the spectrum table would strengthen Section 7 but is not essential.

4. **Formalism Section 5.4** (What $T$ can do): The paper's Def 5.1 includes all five capabilities listed in the formalism (encode, decode, inject noise, verify, reseed). **Complete.**

5. **Formalism Section 6.1** (Gap resolution table): Not included in the paper. **Appropriate** -- this is meta-documentation, not paper content.

6. **Entanglement parameter $p$** in the parameter table: Formalism Section 1.4 includes $p$ in the parameter table; the paper's Table 1 omits $p$. **MINOR GAP** -- could be added to Table 1 for completeness.

### What's in the paper but not in the formalism

1. **Section 8.2** (Algebraic Structure discussion): Mentions monoid homomorphisms, quotient structure, category-theoretic framing. The formalism does not develop this. **Acceptable** -- the paper explicitly says "we note this connection but do not develop it further."

2. **Remark on "Approximation as privacy"** (after Def 2.4): Present in both paper and formalism. **Consistent.**

3. **"What this is not" paragraph** (Section 1): Explicit comparison to ORAM, FHE, garbled circuits. Not in formalism. **Good addition** for a paper.

4. **Section 8.4** ("What this framework is not"): Explicit disclaimers about ORAM, differential privacy, simulation-based security. Not in formalism. **Good addition.**

### Contradictions
**None found.** The paper faithfully implements the formalism.


## Provenance Check

### ORAM / simulation-based formalism
- **\Adv**: NOT FOUND in new paper. PASS.
- **\Simulator**: NOT FOUND in new paper. PASS.
- **\Trace**: NOT FOUND in new paper. PASS.
- **\PPT**: NOT FOUND in new paper. PASS.
- **ORAM**: Appears only in explicit "what this is not" disclaimers (Section 1 paragraph, Section 8.4). PASS.
- **Simulation-based**: Appears only in Section 8.4 as an explicit disclaimer ("We do not claim that the untrusted machine's view can be simulated"). PASS.
- **Game-based**: NOT FOUND. PASS.

### Privacy model
The paper's privacy model is entirely based on:
- One-way hash (random oracle model)
- Representation uniformity ($\delta$-bounded TV distance from uniform)
- Trapdoor (secret $s$ held by trusted machine)

No cryptographic games, no simulation paradigm, no indistinguishability experiments, no adversary definitions beyond the informal "untrusted machine $U$." The privacy model is exactly the one-way hash + uniform representation model from the formalism.

**PROVENANCE CHECK: PASS**


## Salvaged Content Check

### Singular Hash Map construction
- **Algorithm 1** in the new paper matches Algorithm 1 in the original paper. The core loop (search for seed $\ell$ such that $h(\ell) \oplus h(x)$ decodes correctly for all stored elements) is identical.
- The XOR combination $h(\ell) \oplus h(x)$ is preserved correctly.
- Query evaluation $\hat{f}(c) = h(\ell) \oplus h(c)$ with prefix-free decode is stated correctly.
- Space formula $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits per element matches the original's Thm 5.2.
- **CORRECT.**

### Composition formula
- $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g) = \eta_f + \eta_g - \eta_f \eta_g$
- This matches the original paper's Thm 7.3 (cipher composition). The formula is correct.
- Chain composition $\eta_{\mathrm{total}} = 1 - \prod(1-\eta_i)$ is also correctly carried over.
- **CORRECT.**

### Properly excluded from original paper

1. **Cipher Monoid** (original Thm 2.1, Def 2.2-2.5): The original paper's cipher monoid construction is entirely excluded. The new paper mentions monoid structure only in Section 8.2 as a connection, not as a formal development. **CORRECTLY EXCLUDED** -- the cipher monoid was part of the Claude-drifted algebraic framework.

2. **Multiplicative group cipher** (original Example 2.2): The original paper's $\mathbb{Z}_p^*$ construction with discrete logarithm security reduction is excluded. **CORRECTLY EXCLUDED** -- this was a Claude fabrication not grounded in the blog posts.

3. **Bernoulli entropy theorem** (original Thm 3.5): The original paper's "Bernoulli Entropy" theorem ($H(\text{Bernoulli}) = -\sum_{i,j} q_{ij} \log q_{ij}$) is excluded. **CORRECTLY EXCLUDED** -- this was a trivially restated definition of joint entropy dressed up as a theorem.

4. **Encoding set theory** (original Section 2.3): The original paper's generating/minimal/complete encoding set framework is excluded. **CORRECTLY EXCLUDED** -- this was Claude-generated algebraic scaffolding not from the blog posts.

5. **Cipher functor / functoriality theorem** (original Thm 7.1): The original paper's formal functoriality proof is excluded. The new paper mentions category-theoretic connections as future work (Section 8.2). **CORRECTLY EXCLUDED.**

6. **Security reduction** (original appendix proof): The adversary/reduction proof style ($\mathcal{A}$, $\mathcal{B}$, challenge pairs) is excluded. **CORRECTLY EXCLUDED** -- this was simulation-based cryptographic formalism.

7. **Applications section** (original Section 7): The original's speculative applications (encrypted search, MPC, differential privacy, oblivious transfer) are excluded. **CORRECTLY EXCLUDED** -- these were Claude-generated application claims without grounding.

8. **Confusion matrix representation** (original Def 3.2): Excluded. **CORRECTLY EXCLUDED.**

9. **"Oblivious" terminology**: The original paper uses "oblivious" 20+ times as a core concept. The new paper does not use "oblivious" at all (verified by the provenance check). **CORRECTLY EXCLUDED** -- the framework is based on trapdoor + totality + representation uniformity, not obliviousness.

### What was correctly salvaged
- Singular Hash Map algorithm and space analysis
- Composition formula and chain composition
- Information-theoretic lower bound
- Connection between entropy maps and Bloom filters (as a remark)
- The basic construction idea (seed search, prefix-free codes, XOR combination)


## Overall Verdict: PASS

The rebuilt paper is a faithful, rigorous implementation of the formalism document. It is internally consistent, mathematically precise, free of ORAM/simulation-based contamination, and correctly excludes the Claude-drifted content from the original paper while salvaging the authentic constructions.

## Issues requiring attention

1. **MINOR**: Thm 5.1 (lower bound) -- the additivity of the membership and value components is asserted rather than formally proved. Consider adding a sentence noting this relies on the components occupying disjoint portions of the hash output (which is true by construction).

2. **MINOR**: $K$ vs $K(x)$ inconsistency -- Def 2.1 uses global $K$ in the range of $\enc$'s second argument, but Properties 2 and 3 (Defs 2.3, 2.4) use element-dependent $K(x)$. This is inherited from the formalism doc. Consider changing Def 2.1 to use $K(x)$ throughout.

3. **MINOR GAP**: The entanglement parameter $p$ could be added to the parameter table (Table 1) for completeness, as the formalism doc includes it.

4. **MINOR GAP**: The formalism's entanglement spectrum table ($p=1,2,p,k$ with privacy/space trade-offs) could strengthen Section 7 but is not essential.

None of these issues are blocking. The paper is ready for further development.
