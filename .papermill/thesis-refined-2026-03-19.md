# Thesis Refinement: Maximizing Confidentiality in Encrypted Search Through Entropy Optimization

Date: 2026-03-19

## Current Thesis

From the abstract:

> We model encrypted search activities as random processes and measure their entropy, comparing observed entropy against the maximum entropy possible under system constraints [...] the ratio of observed to maximum entropy provides a quantitative measure of confidentiality bounded between 0 and 1.

Distilled: **Confidentiality = H_observed / H_max**, measurable via compression, improvable via entropy-maximizing techniques.

## Problems with Current Thesis

1. **"Measure of confidentiality" is undefined against any adversary.** The paper asserts that higher entropy means better confidentiality but never defines confidentiality formally. A USENIX Security paper requires a concrete adversary model and a theorem relating the metric to adversary advantage. Without this, the claim is an intuition, not a result.

2. **The metric conflates independent leakage channels.** The joint maximum entropy formula (line 1634) sums entropy contributions from timing, identity, query content, and result sets as if they are independent channels. But result sets are deterministic given queries (acknowledged at line 1672), so including result set entropy as an independent term is internally inconsistent. The paper cannot simultaneously claim H(result|query)=0 (Section 8) and include result set entropy additively in H* (Section 7).

3. **Independence assumption is load-bearing but unjustified.** The entire framework assumes i.i.d. query tuples. Real encrypted search has temporal correlations (burst patterns), query-result determinism, and user-specific behavior. The maximum entropy under independence is an unattainable upper bound, making the denominator of the efficiency ratio artificially large and the metric systematically biased downward.

4. **Shannon entropy is the wrong security metric without justification.** Shannon entropy measures average unpredictability. Security requires worst-case bounds (min-entropy). A system with e=0.85 under Shannon entropy could still have a highly predictable most-likely query. The paper never discusses why Shannon entropy suffices or what security guarantee it provides.

5. **The thesis is too broad for what is actually proven.** The paper claims a "quantitative measure of confidentiality" but actually shows: (a) standard maximum entropy derivations applied to encrypted search components, (b) a ratio metric with no proven security semantics, (c) a case study with analytical (not experimental) numbers.

## Genuine Contributions

Ranked by novelty and importance:

1. **The entropy efficiency metric e = H/H* as a design tool (Novel application).** While entropy measurement is standard and maximum entropy derivations are textbook, applying the ratio as a single-number confidentiality score for encrypted search systems is new. This is genuinely useful for practitioners comparing configurations, even without a formal security theorem. The bounded [0,1] range and component-wise decomposition are actionable.

2. **Quantified cost-benefit analysis of countermeasures (Practical).** The case study showing 59% to 85% efficiency with 1.52x space and 1.5x bandwidth is the paper's strongest concrete result. The decomposition into homophonic encryption (space cost) vs. artificial queries (bandwidth cost) gives practitioners a menu of options. Scenarios 2 and 3 show the framework adapts to different scales.

3. **Compression-based estimation as practical measurement (Sound but unvalidated).** The idea that system operators can measure confidentiality by compressing query logs, without needing to know the underlying distribution, is useful if true. But it remains entirely theoretical -- no compression experiment is ever run.

4. **Connection between encrypted search techniques and entropy.** Homophonic encryption = distribution flattening = entropy increase. Artificial queries = noise injection = correlation attenuation. These connections are well-observed, though not formally novel.

5. **Component-wise maximum entropy derivations (Standard but correctly applied).** Exponential for inter-arrival times, uniform for identities, geometric for cardinality, uniform for trapdoor selection. These are textbook results correctly applied to the encrypted search domain.

## Refined Thesis

**Claim**: For encrypted search systems under passive frequency-analysis attacks, the ratio of observed Shannon entropy to constrained maximum entropy of the observable query stream provides a practical design metric that: (a) decomposes into independently improvable components (timing, identity, query content), (b) can be estimated without explicit distributional modeling via lossless compression, and (c) guides cost-effective countermeasure selection, as demonstrated by improving a typical system from 59% to 85% efficiency with 1.52x space and 1.5x bandwidth overhead.

**Novelty**: The entropy ratio metric itself -- applying e = H/H* component-wise to encrypted search observables -- and the quantified cost-benefit analysis of countermeasures. The maximum entropy derivations are standard; the application and the resulting design framework are new.

**Evidence needed**:
1. A formal passive adversary model (frequency-analysis game) with a theorem bounding adversary advantage as a function of the entropy gap (H* - H). Even a weak bound would suffice.
2. Experimental validation of compression-based estimation on synthetic query streams with known parameters.
3. Resolution of the result set determinism inconsistency: either remove result sets from the joint formula or model them conditionally.
4. A brief discussion of why Shannon entropy (not min-entropy) is the appropriate metric, or supplementary analysis with min-entropy.

## Thesis Variants

### Variant A: Pure measurement paper (weakest security claim, easiest to prove)

**Claim**: "We propose entropy efficiency as a diagnostic metric for encrypted search design, derive closed-form bounds for each observable component, and validate compression-based estimation against synthetic benchmarks."

- **Pro**: Avoids security claims entirely; focuses on measurement. Defensible with current results plus compression experiments.
- **Con**: Harder sell at USENIX Security. Better suited for a workshop paper or short paper.
- **Framing**: "Measuring information leakage" rather than "bounding adversary advantage."

### Variant B: Information leakage quantification (moderate claim, needs one theorem)

**Claim**: "The entropy gap H* - H upper-bounds the mutual information between observable and plaintext query streams, and we show how to close this gap efficiently."

- **Pro**: True by the data processing inequality + Fano's inequality path. Connects entropy to information leakage without needing a full game-based model.
- **Con**: Requires careful treatment of the independence assumption and the result set determinism.
- **Framing**: "Entropy ratio measures information leakage" -- this is the better answer to the question posed.

### Variant C: Security reduction paper (strongest claim, hardest to prove)

**Claim**: "We prove that the adversary's advantage in a query-indistinguishability game is bounded by a function of the entropy efficiency, and demonstrate that our techniques reduce advantage from X to Y."

- **Pro**: This is what USENIX reviewers want. If proven, this is a strong paper.
- **Con**: Requires defining and proving a security game. The proof may not go through cleanly because Shannon entropy does not directly bound distinguishing advantage (min-entropy does). May need to work with Renyi entropy or prove a weaker bound.
- **Framing**: "Entropy ratio bounds adversary advantage."

### Recommendation: Variant B with elements of C

The paper should claim that entropy efficiency measures information leakage (Variant B) and provide a partial security reduction showing that for frequency-analysis attacks specifically, the entropy gap bounds attack accuracy (partial Variant C). The existing Figure 3 (accuracy vs. sample size for various entropies) already suggests this relationship empirically -- formalizing it into a theorem would be sufficient.

**The answer to the framing question**: "Entropy ratio measures information leakage" is the defensible claim. "Entropy ratio bounds adversary advantage" is aspirational and requires either a security reduction (hard) or a scope restriction to specific attack classes (feasible).

## USENIX Scoping Advice

### Cutting from 51 pages to 13 pages

**Keep (body, ~13 pages)**:
1. Introduction + contributions (1.5 pages). Trim to 3-4 contributions. Lead with the metric, not the derivations.
2. Model (1.5 pages). Consolidate the encrypted search model to essential definitions: hidden query stream, adversary model, system parameters. Drop the bit-string formalism (B_n etc.), the three algorithms (move to appendix), and the example with two search agents.
3. Entropy framework + metric definition (2 pages). Define entropy, the efficiency ratio, and the compression estimator. State the key insight: "maximum entropy = minimum leakage." Remove the "postulate" framing; cite Shannon's source coding theorem.
4. Maximum entropy derivations (2 pages). One clean pass through all components (currently split across Sections 5, 6, and 7 with redundancy). Use the Section 7 versions. State theorems; put proofs in appendix.
5. Techniques for increasing entropy (2 pages). Homophonic encryption (Algorithm 5), artificial queries, timing obfuscation. Focus on entropy gains and costs, not the queuing theory digression.
6. Experimental evaluation (2 pages, TO BE WRITTEN). Synthetic query streams, compression-based measurement, validation against theoretical predictions. This is the missing piece.
7. Case study (1.5 pages). Keep Table 5, the 59% to 85% result, and cost analysis. Scenarios 2 and 3 can be condensed to a paragraph each.
8. Conclusion (0.5 pages).

**Move to appendix**:
- All detailed proofs (currently inline)
- Algorithm pseudocode for Algorithms 1-4
- Code tables (Tables 2-3)
- The generative model (Algorithm 4, currently unfinished)
- Detailed derivations from current Appendices A-C

**Delete entirely**:
- Section 6 (redundant with Section 7)
- The unary coder discussion and SA code table
- Incomplete sections (lines 2060-2078, placeholder text in Algorithm 4)
- Empty paragraph headings (lines 1238-1240)

### Structural changes needed

1. **Add a formal adversary model paragraph early.** The current "Adversary Model" paragraph at line 1362 is a start but needs: (a) explicit capabilities (passive observation of the untrusted channel), (b) explicit goal (distinguish queries, recover plaintext, or link queries to users), (c) a measure of success (advantage in a defined game, or accuracy of inference).

2. **Fix the result set issue.** Either: (a) acknowledge that H(result|query)=0 and remove result set terms from H*, redefining the metric over (timing, identity, query content) only; or (b) model the result set contribution as H(result set) conditional on the adversary not knowing the query, which requires a different formula.

3. **Add experimental validation.** Generate 10,000-100,000 synthetic query tuples from known distributions (Zipf for words, exponential for timing, uniform for agents). Compress with gzip/zstd. Verify compression ratio tracks theoretical entropy. Apply homophonic encryption and artificial queries; show compressed size approaches H*. This validates both the metric and the estimation method.

4. **Connect to SSE leakage literature.** Curtmola et al. security definitions (L1/L2 leakage), Cash et al. leakage-abuse attacks, Bost et al. forward/backward privacy. Position entropy efficiency as complementary: leakage profiles say *what* is leaked; entropy efficiency measures *how much*.

5. **Address the independence assumption explicitly.** State that the i.i.d. assumption yields an upper bound on achievable entropy, and that the efficiency metric under independence is a lower bound on the "true" efficiency under a more realistic dependent model. This turns a weakness into a conservative bound.
