# Iteration Review: cipher-maps (second pass)
Date: 2026-03-20
Reviewer: Claude Opus 4.6 (1M context)
Previous: verification-2026-03-20.md (first pass, 8 PASS / 1 MINOR-ISSUE)

This review focuses on issues the first verification might have missed: proof rigor at the edge, missing content relative to the formalism, exposition gaps, formula-level correctness, and publication readiness.

---

## 1. Proof Completeness and Rigor

### 1.1 Theorem 5.1 (Lower Bound) -- Additivity argument

**Severity: MAJOR**

The first-pass flagged this as MINOR, but on closer reading the issue is more serious. The proof claims additivity of the membership and value components via the entropy chain rule:

> $H(\text{membership}, \text{value}) = H(\text{membership}) + H(\text{value} \mid \text{membership})$

This is correct as a statement about entropy, but the proof then asserts "conditioning on membership does not reduce the entropy of the value assignment, since the values $(f(x_1), \ldots, f(x_n))$ are an independent degree of freedom." This is a modelling assumption, not a consequence of the chain rule. The lower bound is really:

- Membership distinguishing requires $n \log_2(1/\varepsilon)$ bits (Bloom 1970 counting argument).
- Value encoding requires $n H(Y)$ bits (Shannon source coding).
- Additivity holds because any structure that encodes both must encode them jointly, and these are independent information-theoretic requirements.

The problem: the Bloom 1970 counting argument gives a lower bound on structures that distinguish $n$ elements from non-elements with FP rate $\varepsilon$. The paper cites Bloom but does not state or reproduce the counting argument. A referee would ask: "Where is the actual lower bound proof for the membership component? Citing Bloom 1970 gives the *Bloom filter* construction, not a lower bound." The actual membership lower bound is from Carter et al. (1978) or Mitzenmacher and Upfal (2005), or can be derived from the information-theoretic counting argument.

**Fix**: Either (a) state the counting argument inline (number of subsets of size $n$ from a universe $U$, requiring $\log_2 \binom{|U|}{n}$ bits to distinguish them, which for $|U| \gg n$ gives $\approx n \log_2(|U|/n)$ bits, and relate this to $\varepsilon$), or (b) cite a proper lower bound reference (not Bloom 1970, which is a construction paper).

### 1.2 Theorem 5.3 (Space Complexity of Singular Hash Map) -- "False negative reduction"

**Severity: MAJOR**

Step 1 of the proof says: "When false negatives are permitted at rate $\eta$, only $(1-\eta)n$ of the $n$ elements must decode correctly, reducing the effective element count."

This is an upper bound argument, not a tight equality. Allowing $\eta n$ failures does not mean the structure stores exactly $(1-\eta)n$ elements -- it means the *constraints* on the seed search are relaxed. The space formula $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits/element is stated as an achieved equality (Theorem statement says "achieves space complexity"), but the proof only establishes an upper bound.

More precisely: the Singular Hash Map construction (Algorithm 1) searches for a single global seed $\ell$ such that $h(\ell) \oplus h(x)$ decodes correctly for ALL stored elements. There is no mechanism to "permit" $\eta$ failures in Algorithm 1 -- the algorithm loops until all elements succeed. If $\eta > 0$ failures are permitted, Algorithm 1 would need modification (e.g., accept a seed that fails on at most $\eta n$ elements). But this modification is not shown.

**Fix**: Either (a) modify Algorithm 1 to accept $\eta n$ failures (changing `success = false; break` to a counter), or (b) state the theorem for $\eta = 0$ only and note that $\eta > 0$ is achievable with a modified construction, or (c) clarify that $(1-\eta)$ is the fraction of elements that must satisfy the constraint, and show how the seed search is modified.

### 1.3 Proposition 4.2 (Membership FP rate) -- Edge case $k=0$

**Severity: MINOR**

The formula $\varepsilon_\in(k,n) = (1 - 2^{-(k+1)})^n$ is proved for $|W| = k$ where $x \notin W$. When $k=0$ (empty set), $F(W) = 0^n$, and the test $h(x) \mathbin{\&} F(W) = h(x)$ becomes $0^n = h(x)$, which is true only if $h(x) = 0^n$, probability $2^{-n}$. The formula gives $(1 - 2^{-1})^n = 2^{-n}$. Correct. Edge case passes.

### 1.4 Proposition 6.1 (AND gate) -- Case (0,0) verification

**Severity: MINOR**

The table states $\Pr[\text{correct}] = p_1 + p_2 - p_1 p_2$ for the $(0,0)$ case. Verification: correct output is $0$. Output is wrong ($=1$) when both $B_1=1$ (incorrect, prob $1-p_1$) and $B_2=1$ (incorrect, prob $1-p_2$). So $\Pr[\text{wrong}] = (1-p_1)(1-p_2)$ and $\Pr[\text{correct}] = 1 - (1-p_1)(1-p_2) = p_1 + p_2 - p_1 p_2$. Matches the blog post (noisy-gates.md Table 6). Correct.

### 1.5 Theorem 6.2 (Composition) -- Re-randomization assumption

**Severity: MAJOR**

The composition theorem proves $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$ under two assumptions: (i) independent seeds, (ii) re-randomization. The remark after the proof says this is "best understood as an upper bound under the weaker assumption that errors are positively correlated."

But the paper does not justify why errors would be positively correlated. In fact, errors could be negatively correlated: if $\hat{f}$ fails on element $x$ (producing a random-looking output), the random output fed to $\hat{g}$ might accidentally be a correct encoding of $f(x)$, giving $\hat{g}$ a *better* chance of producing the right answer. This would make the composition error *smaller* than $\eta_f + \eta_g - \eta_f \eta_g$, meaning the formula is an upper bound anyway -- but for the wrong reason.

More fundamentally: when $\hat{f}$ fails, it produces output that does not decode to $f(x)$. This output is fed to $\hat{g}$. The question is what $\hat{g}$ does with a wrong input. $\hat{g}$ being total, it produces *some* output -- but there's no reason to expect this output decodes to $g(f(x))$. So the composition is incorrect whenever $\hat{f}$ is incorrect (unless a miraculous double-error occurs). This means:

$$\Pr[\text{composition correct}] = \Pr[\hat{f} \text{ correct}] \cdot \Pr[\hat{g} \text{ correct} \mid \hat{f} \text{ correct}]$$

Under the independence assumption, $\Pr[\hat{g} \text{ correct} \mid \hat{f} \text{ correct}] = 1 - \eta_g$, giving the formula. But the proof should make clear that when $\hat{f}$ fails, the composition is essentially guaranteed to fail (probability of "accidental correctness" through $\hat{g}$ is negligible). The current proof's union bound path ($\eta_f + \eta_g$) implicitly accounts for the possibility of double-error cancellation, which is the wrong framing.

**Fix**: Restructure the proof to make the conditional structure explicit:
$$\Pr[\text{correct}] = \Pr[\hat{f} \text{ correct}] \cdot \Pr[\hat{g} \text{ correct} \mid \hat{f} \text{ correct}] + \Pr[\hat{f} \text{ incorrect}] \cdot \Pr[\hat{g} \circ \hat{f} \text{ accidentally correct} \mid \hat{f} \text{ incorrect}]$$
Then argue the second term is negligible (random output from a failed $\hat{f}$ passes through $\hat{g}$ to produce the correct answer with probability at most $\varepsilon \cdot (\text{something small})$).

### 1.6 Proposition 7.1 (Granularity and privacy) -- Proof of second part

**Severity: MINOR**

The proof of the second part (component-wise encoding leaks correlations even with $\delta = 0$) states that the adversary can "estimate the joint distribution and recover the correlation structure." This is correct but imprecise about the sample complexity. The proof should note that the adversary needs $O(1/\delta'^2)$ samples to detect a correlation of magnitude $\delta'$ in the joint distribution, where $\delta'$ depends on the correlation strength of $(x_1, x_2)$ under $D$. As stated, the proof gives the right qualitative conclusion but a referee might ask for quantification.

---

## 2. Missing Content (vs. Formalism)

### 2.1 Entanglement spectrum table

**Severity: MINOR**

The formalism (Section 4.3) contains a table showing the spectrum from $p=1$ to $p=k$ with privacy guarantees and space costs ($O(1)$, $O(|Y|^2)$, $O(|Y|^p)$, $O(|Y|^k)$). The paper has the three granularity levels as a description list but not the table. The table is more informative at a glance.

### 2.2 Perfect hashing connection (entropy map)

**Severity: SUGGESTION**

The formalism (Section 2.2) contains a remark connecting the two-level hash to perfect hashing: "With $b = n$ (one item per bucket), the two-level hash reduces to a perfect hash function with implicit $\log_2(1/\varepsilon)$-bit fingerprints." This connection is missing from the paper and would help readers familiar with minimal perfect hash functions.

### 2.3 Equality pattern leakage

**Severity: MINOR**

The formalism (Section 4.4, item 4) discusses equality pattern leakage: "Any deterministic encoding leaks the equality pattern of its inputs: observing $\mathrm{enc}(x_1, k_1) = \mathrm{enc}(x_2, k_2)$ reveals $x_1 = x_2$." The paper's "honest limitations" section (end of Section 7) mentions this at item 3, but in a compressed form. Given that this is a fundamental limitation, it deserves a brief example or more prominent placement (perhaps a Remark environment rather than a bullet in an unnumbered list).

### 2.4 Information flow diagram

**Severity: SUGGESTION**

The formalism (Section 5.2) contains an ASCII information flow diagram showing the $T \leftrightarrow U$ protocol. The paper has the protocol as a numbered list, which is fine, but a figure (even a simple one with tikz arrows) would improve readability of the trust model section.

### 2.5 Construction time bound for entropy map

**Severity: MINOR**

The formalism (Section 2.2) gives a feasibility condition for the two-level hash: "choose $b \geq n / \ell_{\max}$ where $\ell_{\max} = \lfloor \log T / \log(1/\varepsilon) \rfloor$ for a trial budget $T$ per bucket." The paper states the construction time $O(b \cdot \varepsilon^{-\ell})$ but not this feasibility constraint. For a paper claiming practical constructions, this omission matters.

---

## 3. Exposition Quality

### 3.1 Abstract claims vs. actual content

**Severity: MINOR**

The abstract says: "We derive the composition theorem with proof, formalize the trusted/untrusted machine model, and present the Singular Hash Map -- a construction achieving the information-theoretic lower bound of $-\log_2 \varepsilon + H(Y)$ bits per element."

The paper does all of these. However, the abstract does not mention the AND gate warm-up (Section 6.1), which is actually one of the more interesting contributions -- it shows how the composition formula connects to concrete gate-level analysis. A brief mention would better represent the paper's content.

### 3.2 Notation jump: $c$ used for two things

**Severity: MINOR**

In Section 2 (Definition 2.1), $c$ is used as a generic bit string ($c \in \{0,1\}^n$). In the entropy map construction (Section 3.2), $c_y$ and $c_{y_i}$ denote prefix-free codes for value $y$. In Theorem 5.3's proof, $|c_{y_i}|$ denotes the code length. The overloading of $c$ (cipher value vs. codeword) could confuse readers. The paper should use a different letter for codewords -- perhaps $w_y$ or keep $C_y$ (which is already used for the code set).

### 3.3 Section 4.3 (Trapdoor Boolean Algebra) length

**Severity: SUGGESTION**

This subsection is the longest in the constructions section (about 2.5 pages), compared to ~1 page each for HashSet and entropy map. The length is justified by the content (multiple operations, approximate vs. exact, space analysis), but a referee might suggest splitting it into its own section or adding subsubsections for readability.

### 3.4 Missing forward reference in Definition 3.5 (Composability)

**Severity: MINOR**

Definition 3.5 contains the composition formula and says "The proof of (4) is given in Section 6." This is good practice. However, the definition *includes the formula as part of the definition*, which makes it look like the formula is definitional rather than derived. A cleaner approach: define composability as the requirement that $\hat{g} \circ \hat{f}$ is a cipher map for $g \circ f$, then state the formula as a theorem.

### 3.5 "Remark" after HashSet construction

**Severity: SUGGESTION**

The remark "The HashSet demonstrates that the four properties are independent: a construction can satisfy some without others" is a valuable observation but is stated without proof of independence. Strictly, demonstrating independence requires four constructions, each satisfying a different subset. The HashSet satisfies {Totality, Correctness, Composability} but not Rep. Uniformity. To show independence, one would also need a construction satisfying Rep. Uniformity but not one of the others. The paper implicitly has this (the trapdoor Boolean algebra has Rep. Uniformity but only partial Correctness), but the remark overstates by claiming full independence from a single example.

---

## 4. Technical Correctness (Deep)

### 4.1 Space formula dimensional consistency

**Severity: PASS**

Equation (9): bits/element = $-\log_2 \varepsilon + H(Y)$. Both terms are in bits. $-\log_2 \varepsilon$ where $\varepsilon \in (0,1)$ gives a positive number of bits. $H(Y) = -\sum p_y \log_2 p_y$ is in bits. Dimensionally consistent.

### 4.2 Proposition 4.2: formula verification for small $k$

**Severity: PASS**

$k=1$: $\varepsilon_\in(1, n) = (1 - 2^{-2})^n = (3/4)^n$. For $n=8$: $(3/4)^8 \approx 0.1$. Reasonable -- with 8 bits and 1 element, about 10% FP rate.

$k=2$: $\varepsilon_\in(2, n) = (1 - 2^{-3})^n = (7/8)^n$. For $n=8$: $(7/8)^8 \approx 0.34$. Higher FP rate with more elements in the set. This matches intuition.

### 4.3 HashSet $\varepsilon$ parameter

**Severity: MAJOR**

The HashSet section states $\varepsilon = 2^{-n}$, meaning the probability that a random $c$ satisfies $h(c \| s) = 0^n$ is $2^{-n}$. This is the false positive rate.

But the space is stated as $n = -\log_2 \varepsilon$ bits/element. With $\varepsilon = 2^{-n}$, this gives $n = n$ bits/element, which is circular. The issue is that $n$ serves double duty: it is both the hash width (number of bits in the output of $h$) and the space per element.

The circularity is real but not technically wrong -- it is saying that a HashSet using $n$-bit hashes has FP rate $2^{-n}$ and space $n$ bits/element. The parameter $\varepsilon$ is determined by the hash width. A referee would note that this circularity makes the "parameter" $\varepsilon$ redundant for the HashSet -- it is not independently tunable but is mechanically determined by the hash width.

Actually, on further reflection, this depends on the construction. The HashSet as described requires $h(x \| s) = 0^n$ for all $x \in A$. The "space" is the seed $s$, not $n$ per element. The actual space analysis is: the expected number of trials to find $s$ is $2^{n|A|}$ (stated in the "Construction complexity" paragraph). The *storage* is just the seed $s$ itself (a single value), plus the hash function description. So what does "bits per element" mean here?

**This is a conceptual confusion in the paper.** The HashSet stores a single seed $s$. The "bits per element" should be $|s| / |A|$, which for a single global seed search is negligible per element (the seed is a fixed-size value). The actual per-element cost arises when using a **two-level** construction (one seed per bucket), which the paper discusses for the entropy map but not for the HashSet.

The paper says "Space: $n = -\log_2 \varepsilon$ bits/element" but does not explain what constitutes the per-element storage in the single-seed HashSet construction. Arguably, the "storage" is the implicit fingerprint embedded in the seed's satisfaction of the $0^n$ constraint -- each element "costs" $n$ bits of constraint satisfaction. But this is not storage in the traditional sense (the seed itself is one number).

**Fix**: Clarify that $n$ bits/element refers to the information-theoretic content of the construction (the seed implicitly encodes $n$ bits of constraint per element), not to explicit per-element storage. Or switch to the two-level construction for the HashSet too.

### 4.4 Entropy map: $\varepsilon$ definition

**Severity: MINOR**

The entropy map parameter table says $\varepsilon$ is "Code-dependent: $\Pr[\text{random bits} \in \bigcup_y C_y]$." But the *total* probability mass of a prefix-free code over $\{0,1\}^n$ is always $\leq 1$ by the Kraft inequality, and for a complete code it equals 1. If the code is complete (every $n$-bit string decodes to some $y$), then $\varepsilon = 1$, which is useless.

The resolution: the code is *not* complete. The prefix-free code $\bigcup_y C_y$ covers only a fraction of the $n$-bit space, and $\varepsilon = |\bigcup_y C_y| / 2^n$ is the probability that a random $n$-bit string falls in any codeword. The remainder of the space is "noise" (strings that decode to $\bot$).

The paper does not make this explicit. A reader might wonder: how can a prefix-free code on $n$-bit strings *not* cover the entire space? The answer is that the codes are prefixes of the $n$-bit hash output, and only certain prefixes are valid. The paper should clarify that the code is deliberately incomplete, leaving $(1-\varepsilon)$ fraction of the hash space as noise/undefined.

### 4.5 Singular Hash Map: XOR construction correctness

**Severity: PASS**

Algorithm 1 computes $h(\ell) \oplus h(x)$ and checks that $\dec(\text{result}) = y$. Query: $\hat{f}(c) = h(\ell) \oplus h(c)$. Under ROM, $h(\ell) \oplus h(x)$ for stored $x$ is a deterministic function of the seed $\ell$. For non-stored $x$, $h(x)$ is independent of $h(\ell)$ and of stored elements' hashes, so $h(\ell) \oplus h(x)$ is uniformly distributed. This correctly gives FP rate $\varepsilon$.

However: note that $h(\ell) \oplus h(x_i)$ for different stored elements $x_i$ are NOT independent -- they all share the same $h(\ell)$ term. The proof of Proposition 5.4 claims independence: "hash values $h(\ell) \oplus h(x_i)$ for distinct $x_i$ are independent uniformly distributed bit strings." Under ROM, $h(x_i)$ are independent for distinct $x_i$, and $h(\ell)$ is a fixed (for given $\ell$) value. So $h(\ell) \oplus h(x_i)$ are independent because XOR with a fixed value is a bijection on $\{0,1\}^n$, preserving the independence and uniform distribution of $h(x_i)$. This is correct.

### 4.6 AND gate: table entry for (0,0) case

**Severity: MINOR (editorial)**

The paper's AND gate table (Proposition 6.1) states:
- $(0,0)$: $\Pr[\text{correct}] = p_1 + p_2 - p_1 p_2$

The first-pass verification says this matches. Let me double-check against the blog source (noisy-gates.md):
- Blog Table 6, row $(0,0)$: `p1 + p2 - p1*p2`

Match confirmed. However, I note that this is equal to $1 - (1-p_1)(1-p_2)$, which is the composition formula $\eta_{g \circ f}$ with $\eta_f = 1-p_1$ and $\eta_g = 1-p_2$. The paper does not explicitly connect the $(0,0)$ case to the composition formula, which would strengthen the AND-gate-to-composition bridge. This is a missed pedagogical opportunity.

### 4.7 Construction complexity of HashSet

**Severity: MINOR**

"Each candidate seed succeeds with probability $2^{-n|A|}$ (all $|A|$ elements must hash to $0^n$)."

Under ROM, for a given seed $s$, each $h(x_i \| s) = 0^n$ with probability $2^{-n}$, and these are independent across $x_i$ (since the $x_i$ are distinct). So the probability all $|A|$ succeed is $(2^{-n})^{|A|} = 2^{-n|A|}$. Correct.

But the expected number of trials is $2^{n|A|}$, which for $|A| > 1$ is astronomically large. The paper acknowledges this ("exponential construction time motivates the two-level construction"), which is good. But it does not give the two-level construction for the HashSet -- only for the entropy map. A reader wanting to build a HashSet is left without a practical algorithm.

---

## 5. Publication Readiness

### 5.1 Top 3 Referee Complaints (predicted)

1. **Lower bound proof (Theorem 5.1)**: The citation to Bloom 1970 is incorrect for the lower bound claim. Bloom's paper gives the Bloom filter construction, not the membership lower bound. The counting argument is sketched but not proved. A referee in information theory or data structures would reject on this basis.

2. **Singular Hash Map $\eta > 0$ claim (Theorem 5.3)**: Algorithm 1 searches for a seed where ALL elements succeed. The theorem claims space $(1-\eta)(-\log_2 \varepsilon + \mu)$ for $\eta > 0$, but the algorithm does not implement $\eta > 0$. Either the algorithm or the theorem needs modification.

3. **Composition theorem independence assumption**: The re-randomization assumption (condition ii) is stated but not validated for any of the three concrete constructions. A referee would ask: "For which of your constructions does re-randomization actually hold? Can you demonstrate the composition formula on a specific example?"

### 5.2 Weakest Section

**Section 5 (Singular Hash Map)** is the weakest. It makes the strongest claim (space optimality) but has the most proof gaps:
- Lower bound proof cites wrong reference
- Space complexity theorem is stated for $\eta > 0$ but Algorithm 1 only handles $\eta = 0$
- No worked example of the construction
- No comparison to existing approaches (e.g., MPHF + fingerprinting, Cuckoo hashing + codes)

### 5.3 Missing for Complete Submission

1. **Bibliography**: Only 4 of 16 bib entries are actually cited. The .bbl file shows only bloom1970space, gentry2009fully, goldreich1996software, and yao1982protocols. The remaining 12 entries in references.bib are unused -- these are leftovers from the original (Claude-drifted) paper. Clean up the .bib file.

2. **Missing citations**: The paper mentions Shannon's source coding theorem (at least 3 times) but never cites Shannon 1948. It mentions "counting argument" and "information-theoretic lower bound" without citing the actual source (Carter et al. 1978, or Pagh et al. 2005 for the membership lower bound).

3. **No related work section**: The introduction has a "What this is not" paragraph distinguishing from ORAM, FHE, and garbled circuits, but there is no proper related work section discussing:
   - Bloom filters and variants (the closest existing work)
   - Minimal perfect hash functions (directly related to the two-level construction)
   - Searchable symmetric encryption (Cash et al. 2013 is in the bib but uncited)
   - Oblivious transfer and MPC (the paper disclaims these but should discuss the distinction more precisely)

4. **No experimental evaluation or concrete numbers**: The paper is purely theoretical, which is fine for a theory venue, but even theory papers benefit from a table of concrete parameter values (e.g., "for $|X| = 10^6$, $|Y| = 256$, the Singular Hash Map uses 28 bits/element with FP rate $2^{-20}$ and $H(Y) = 8$ bits").

5. **Duplicate table identifiers**: The LaTeX log shows three "destination with same identifier" warnings for table.1, table.2, table.3. This is because unnumbered `\begin{center}...\end{center}` tables in the construction sections conflict with the numbered `\begin{table}` environments. Fix by using consistent table environments.

### 5.4 Target Venue

Given the paper's content (information-theoretic bounds, hash-based constructions, privacy model), suitable venues include:

- **IEEE Transactions on Information Theory**: Strong fit for the information-theoretic content (lower bounds, entropy, composition). Would need the proof gaps fixed and more comparison to existing hash-based data structures.
- **ACM CCS or IEEE S&P (workshop track)**: If the privacy/trust model angle is emphasized. Would need a threat model more precisely defined than the current informal $T$/$U$ model.
- **ISAAC or ESA**: Algorithms conference. Good fit for the construction aspects (Singular Hash Map, two-level hashing). Would need experimental evaluation.
- **arXiv preprint**: Most realistic near-term target. Publish as-is (after fixing the issues above) to establish priority and get community feedback.

**Recommendation**: Target arXiv first. Fix the MAJOR issues, add citations, clean the bibliography. Then submit to IEEE Trans. Info. Theory after incorporating feedback.

---

## Summary Table

| # | Section | Finding | Severity |
|---|---------|---------|----------|
| 1.1 | Thm 5.1 | Lower bound cites Bloom 1970 (construction) instead of a lower bound reference; counting argument not proved | MAJOR |
| 1.2 | Thm 5.3 | Algorithm 1 only handles $\eta=0$; theorem claims result for $\eta > 0$ | MAJOR |
| 1.5 | Thm 6.2 | Composition proof does not handle the "what happens when $\hat{f}$ fails" case explicitly; re-randomization assumption not validated for any construction | MAJOR |
| 4.3 | S4.1 | HashSet "bits/element" is information-theoretic content of seed, not explicit storage; potentially confusing | MAJOR |
| 5.3a | Bib | Only 4 of 16 bib entries cited; 12 are unused leftovers | MINOR |
| 5.3b | Bib | Shannon 1948 never cited despite 3+ invocations of Shannon's theorem | MINOR |
| 5.3c | Structure | No related work section | MINOR |
| 3.2 | Notation | $c$ overloaded: cipher value vs. codeword | MINOR |
| 3.4 | Def 3.5 | Composition formula bundled into definition rather than stated as theorem | MINOR |
| 4.4 | S3.2 | Entropy map $\varepsilon$ -- paper does not clarify that the prefix-free code is deliberately incomplete | MINOR |
| 2.1 | S7 | Entanglement spectrum table from formalism omitted | MINOR |
| 2.3 | S7 | Equality pattern leakage deserves more prominent treatment | MINOR |
| 2.5 | S3.2 | Feasibility constraint for two-level construction omitted | MINOR |
| 1.6 | Prop 7.1 | Sample complexity for correlation detection not quantified | MINOR |
| 4.7 | S3.1 | No practical construction given for HashSet (only exponential single-seed) | MINOR |
| 5.3d | Build | Duplicate table identifiers in LaTeX causing hyperref warnings | MINOR |
| 3.1 | Abstract | AND gate warm-up not mentioned in abstract | SUGGESTION |
| 2.2 | S3.2 | Perfect hashing connection from formalism not mentioned | SUGGESTION |
| 2.4 | S4 | Information flow diagram would improve trust model section | SUGGESTION |
| 3.3 | S3.3 | Trapdoor Boolean Algebra subsection is long; could use subsubsections | SUGGESTION |
| 3.5 | S3.1 | "Independence" remark overstated from single example | SUGGESTION |
| 4.6 | S6.1 | $(0,0)$ case connection to composition formula is a missed pedagogical opportunity | SUGGESTION |
| 5.3e | -- | No experimental evaluation or concrete parameter table | SUGGESTION |

**Overall**: 4 MAJOR, 12 MINOR, 6 SUGGESTION. The paper is mathematically sound in its core arguments but has proof-presentation gaps that would concern a referee. The four MAJOR issues are all fixable without changing the paper's structure or claims -- they are proof-completeness issues, not incorrectness. After fixing the MAJOR items, the paper would be suitable for arXiv and, with additional related work and citations, for journal submission.
