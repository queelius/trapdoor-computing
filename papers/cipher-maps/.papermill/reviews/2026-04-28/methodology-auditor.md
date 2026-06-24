# Methodology Auditor Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Methodology Auditor
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Focus**: Experimental design, statistical rigor, reproducibility, parameter justification

## Summary

The paper is primarily theoretical; methodology concerns center on (a) the formal model the security claims operate in, (b) the limited experimental section that has been added, (c) reproducibility of the named numbers, and (d) parameter choices in the worked examples. The Round 3 M5 (space optimality framing) and M6 (ROM dependence) fixes are clean. M1 (security definition) and M2 (broader experimental evaluation) remain open as Round 3 flagged.

**Findings**: 0 critical, 2 major, 6 minor.

---

## Verification of Round-3 fixes

### M5 framing, VERIFIED FIXED

The new Remark 6.3 (line 817) cleanly distinguishes information-theoretic capacity from physical storage. The two-level hash construction's actual storage is now explicitly stated as $-\log_2 \varepsilon + \mu$ bits per element regardless of $\eta$, with the $(1-\eta)$ factor describing useful information content. This eliminates the misleading reading that motivated my Round 3 finding.

### M6 ROM enumeration, VERIFIED FIXED with caveats

The new ROM paragraph (lines 245-262) names HMAC-SHA256 with seed-as-key as the practical instantiation, lists three ROM assumptions (a, b, c), and notes the standard-model open question. Two issues:

1. The Round 3 M6 suggestion enumerated *four* assumptions; the fourth being independence of representation-uniformity computation from the seed. The current text lists three; assumption (c) collapses what could be split into "independence across maps" and "independence within a map (across encodings)." Not wrong, but the prose says "the four properties" depend on ROM, then lists three labeled-by-property dependencies. This is a small inconsistency. See L1-style finding in prose-auditor.

2. The phrase "domain-separated keyed hashes (HMAC-SHA256 with seed $\ell$ as the key)" is the only place a concrete instantiation is named. This is good but isolated; it would benefit from being repeated in Algorithm 1's description and in the Entropy Cipher Map section so that a reader picking up §6 in isolation knows what hash to use.

---

## Major Findings

### M-A1. The "Experimental validation" paragraph (lines 1419-1434) is reproducibility-thin (MAJOR)

**Location**: §9.4 "Application: Encrypted Search," paragraph at lines 1419-1446

**Quoted text**:
> "A reference implementation (\texttt{cipher-maps}, Python) validates the encrypted search application on the 20 Newsgroups corpus (18,266 documents, 58,903 unique words). Construction uses perfect hash functions (via \texttt{phobic}) with $n = 8$-bit cipher Booleans ($p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$). At 5,000 documents: construction takes 5.9 seconds (843 documents per second), single-term queries achieve perfect recall (1.0) with precision 0.39 (matching the theoretical false positive rate $p_T = 0.05$ per document). Multi-term AND queries improve precision (FP drops from 248 to 12 for 3-term AND) while maintaining perfect recall. OR and NOT queries lose recall (0.97 and 0.88 respectively) due to noise propagation through the cipher Boolean operations. The full 18,266-document index builds in 25.6 seconds."

**Problem**: This paragraph is the only experimental content in the paper. It introduces specific numerical claims:
- 843 documents per second construction throughput
- precision 0.39 at 5,000 documents
- FP count 248 to 12 for 1-term to 3-term AND
- recall 0.97 (OR), 0.88 (NOT)
- 25.6 seconds full-index build for 18,266 documents

But it does not specify:
- (a) Hardware (CPU, RAM, single-thread or multi-thread)
- (b) What single-term queries: drawn from where, what query distribution, what corpus stop-words excluded
- (c) Number of trials and variance: is "843 docs/sec" an average over runs?
- (d) Definition of "false positive" in this setting: per-document or per-query
- (e) Whether the 12 FP count for 3-term AND is over the 5,000-document index or a subset
- (f) The cipher Boolean partition fractions $p_T, p_F, p_N$ are repeated below (line 1438) but the relationship between these and the 0.05 false positive rate is not derived
- (g) Implementation details: does \texttt{phobic} mean a specific RecSplit-family library? PHF parameters?
- (h) Comparison baselines: a Bloom filter on the same corpus would take what fraction of construction time and space?

**Significance**: A PoPETs reviewer would treat this as either "promising preliminary evidence" or "unsupported claims," depending on charity. It is currently below the threshold of "experimental validation" as PETS typically uses the term. The paper's own abstract doesn't claim this section as experimental evaluation; it appears as a paragraph inside §9.4 (Discussion / Application). But the absence of a dedicated experimental section will be the second-most-cited weakness in any review (after the missing security definition).

**Suggestion**: Three options, in increasing order of work:
1. **Minimum**: Move this paragraph to a small dedicated subsection (e.g., §9.5 "Reference Implementation"), add reproducibility metadata (hardware, trial count, variance, query distribution), provide a footnote URL to the implementation.
2. **Better**: Add a comparison row, Bloom filter at the same false-positive rate has space $X$ bytes/element vs cipher map $Y$ bytes/element; SSE-style index has construction time $T_1$ vs cipher map $T_2$ for $N$ documents.
3. **Ideal**: Promote to a §10 "Implementation and Evaluation" with a parameter-sweep figure (FP rate vs. AND query depth, recall vs. NOT depth, construction time vs. corpus size) and a comparison table.

The paper's plan likely depends on the user's stated reluctance to invest in M2 work. But option 1 is a few hours of work and would dramatically improve the paragraph's defensibility.

**Cross-verification needed**: Logic-checker should verify whether "perfect recall (1.0) with precision 0.39 matching the theoretical false positive rate $p_T = 0.05$" actually checks out arithmetically. (Quick: with FP rate 0.05, query yields about 250 hits in 5000-doc corpus; if the true positives are around 100, precision is about 100/350 = 0.29, not 0.39. The 0.39 figure depends on the ratio of true to false positives, which depends on query frequency. Without query distribution, the "matching" claim is unverifiable. This may be a numerical issue worth flagging.)

### M-A2. Construction-time table (lines 866-877) toy parameters limit external validity (MAJOR persists from M2)

**Location**: §6.4 (Construction Time and Bucketing), table at lines 868-877

**Quoted text** (table):
> "$m = 100$ ... $\alpha = 0.5$, $\eta = 0$: $2^{100}$"

**Problem**: The table uses $m = 100$ stored elements as the running parameter. For PETS-relevant scales ($m \in [10^4, 10^7]$), the same calculation yields construction times that are off-scale for the table's structure. The reader is left to extrapolate.

The bucketed-construction subsection that follows handles the realistic case implicitly (showing that $k = m$ buckets yield linear construction), but a single table that interpolates between toy and realistic parameters would be more useful. For instance: $m = 10^4$, $k = 100$ buckets, $\bar{\alpha} = 0.5$, bucket size 100, per-bucket time $2^{100}$, total $100 \cdot 2^{100}$, still infeasible. With $k = 1000$ buckets, bucket size 10, per-bucket time $2^{10} \approx 10^3$, total about $10^6$ seed checks, feasible.

**Suggestion**: Replace the $m=100$ table with a table that holds $\bar{\alpha} = 0.5$ fixed and varies $(m, k)$ across realistic scales: $(10^4, 100)$, $(10^4, 1000)$, $(10^6, 10^3)$, $(10^6, 10^5)$. This gives the reader a feasibility map for the bucketed construction at PETS-relevant scales.

---

## Minor Findings

### M-A3. Adversary model still not formalized (MINOR, m7 from Round 3 not addressed)

**Location**: Section 5 (Trust Model), Definition 5.2

**Problem**: Round 3 minor m7 noted that the adversary $U$ is implicitly honest-but-curious, but this is never stated. Today's revision did not add this. A PoPETs reviewer will ask whether $U$ is malicious (could $U$ return wrong $\fhat$ outputs to mislead $T$?), HBC, or covert. The four properties make sense only under HBC.

**Suggestion**: Add one sentence to Definition 5.2: "We model $U$ as honest-but-curious: $U$ correctly evaluates $\fhat$ on each input and returns the result, but attempts to learn information about $f$, $X$, or $Y$ from its observations of cipher values and outputs. Malicious $U$ that returns adversarial outputs requires a verifiable computation layer outside the scope of this paper."

### M-A4. Hash construction notation inconsistency persists (MINOR, m9 from Round 3 not addressed)

**Location**: Algorithm 1 (line 737, $h(\ell) \oplus h(x)$); §6.5 Entropy Cipher Map (line 958, $h(x \| s)$); §3.1 ROM paragraph (line 257, "HMAC-SHA256 with seed $\ell$ as the key").

**Problem**: Three different conventions for "hash an element with a secret":
1. $h(\ell) \oplus h(x)$ in Algorithm 1
2. $h(x \| s)$ in Entropy cipher map
3. HMAC-SHA256(key=$\ell$, msg=$x$) in ROM paragraph

These are not equivalent in general. Even under ROM, $h(\ell) \oplus h(x)$ and $h(x\|s)$ have different cryptographic properties (the XOR construction has known weaknesses for related-key attacks). The HMAC suggestion is the most cryptographically defensible.

A reader cannot tell which is the canonical construction or whether the differences matter.

**Suggestion**: Pick one convention (HMAC-SHA256 with seed as key is the strongest) and use it throughout. Add a brief note: "Throughout, $H(s, x)$ denotes a domain-separated keyed hash, instantiated as HMAC-SHA256(seed=$s$, msg=$x$) in practice. Equivalent constructions like $h(s \| x)$ or $h(s) \oplus h(x)$ are acceptable under ROM but the keyed form is preferred for standard-model arguments."

### M-A5. False positive precision calculation in 20 Newsgroups paragraph is unverifiable (MINOR)

**Location**: Lines 1426-1429

**Quoted text**:
> "single-term queries achieve perfect recall (1.0) with precision 0.39 (matching the theoretical false positive rate $p_T = 0.05$ per document)"

**Problem**: With $p_T = 0.05$ and 5,000 documents, the expected number of false-positive document hits per query is $5000 \cdot 0.05 = 250$. If the average true positive count per single-term query is $X$, then precision = $X / (X + 250)$. Setting precision $= 0.39$ gives $X / (X + 250) = 0.39$, so $X \approx 160$. Is this consistent with the average word frequency in 20 Newsgroups? Plausible for moderately frequent terms, but the paper does not state this.

The "matching the theoretical false positive rate" phrasing implies a tight numerical match, but the link between $p_T$ and precision depends on query distribution. The paragraph should explain.

**Suggestion**: Reformulate: "single-term queries achieve perfect recall (1.0) with mean precision 0.39 over [N] queries drawn from [distribution X]; this is consistent with $p_T = 0.05$ (expected $5000 \cdot 0.05 = 250$ false-positive document hits per query)."

### M-A6. cipher Boolean partition (5%/90%/5%) is asymmetric without justification (MINOR)

**Location**: Lines 1424-1425, lines 1438-1442

**Problem**: The partition $p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$ is justified nowhere in the paper. Why not 50%/45%/5% or 33%/33%/33%? The cipher Boolean type's design choice should be motivated either by the Shannon-optimality argument from §6.2 (in which case $p_T$ should match the empirical fraction of true predicates in the corpus, which is roughly $\#$members $/ \#$documents) or by an attack-resistance argument.

For the 20 Newsgroups corpus with 5000 documents and per-keyword "true" rate (e.g., 5% of documents contain the keyword), $p_T = 0.05$ makes sense as Shannon-optimal. A sentence to this effect would justify the choice.

**Suggestion**: Add to the Experimental validation paragraph: "The cipher Boolean partition $(p_T, p_F, p_N) = (0.05, 0.90, 0.05)$ is Shannon-optimal for the 20 Newsgroups corpus, where keyword presence has empirical mean about 5% across documents. The 5% noise region $p_N$ provides additional totality margin without affecting recall."

### M-A7. "Encryption" vs. "encoding" terminology drift (MINOR)

**Location**: Throughout, but most visible in §5

**Problem**: The paper consistently uses "cipher map" and "encoding," but occasionally slips to "encryption" (e.g., "Property-preserving encryption" paragraph (line 146), "encrypted computation" (abstract, line 47), "encrypted search" (§9.4)). This is mostly fine since these are accepted shorthand, but in places the slippage is sharp.

Most notably, line 47 "Privacy in encrypted computation" sets the abstract's frame as if the paper is about encryption, then the rest of the paper carefully distinguishes cipher maps from encryption. A reviewer who reads the abstract first may form expectations the paper later disclaims (§9.5 "Not differential privacy. Not simulation-based security."). The paper benefits from being more precise in the abstract about what kind of "privacy" is on offer.

**Suggestion**: Reformulate the opening sentence of the abstract: "Privacy in computation outsourced to an untrusted evaluator..." (drop "encrypted" since cipher maps are not formally encryption).

### M-A8. The "Experimental validation" paragraph is *duplicated* within §9.4 (MINOR)

**Location**: Lines 1419-1434 and 1436-1446

**Problem**: The 20 Newsgroups paragraph at lines 1419-1434 and the cipher Boolean paragraph at lines 1436-1446 both report "perfect recall for AND queries with false positives decreasing from 248 (single term) to 12 (3-term AND)." The cipher Boolean partition $(0.05, 0.90, 0.05)$ also appears in both. This is a redundancy from the editorial process; likely the second paragraph was added later without removing duplicate content from the first.

**Suggestion**: Consolidate into a single Experimental validation paragraph, with the cipher Boolean type explanation moved earlier (perhaps to §7 Composition or §8 Granularity, since it relies on those concepts).

---

## Items Verified Sound

- The four-property parameterization $(\eta, \varepsilon, \mu, \delta)$ is clean and well-organized.
- Algorithm 1's early-stop logic is correct and the shuffling motivation is sound.
- The construction strategies (batch vs. online) are well-distinguished.
- The Bayesian deniability proposition (line 1451) is methodologically clean.
- The honest limitations sections (Remark 4.1, §8 Honest Limitations) are well-calibrated.

## Notes on M1 (no formal security definition) and M2 (no experimental evaluation)

These are unchanged from Round 3. The author's question is whether *other* issues exist beyond M1/M2. My answer:

**Yes, M-A1 and M-A2 are independent of M1/M2 work and addressable now.** M-A1 (the experimental paragraph reproducibility) is a PoPETs reviewer's first complaint after the missing-security-definition complaint. M-A2 (toy parameters in the construction-time table) is independent of any new experiments; it's just a re-presentation of computations the paper already does.

**Other items (M-A3 through M-A8) are minor and individually small.** Together they represent maybe a half-day of editorial work that would substantially polish the paper independent of the M1/M2 questions.

**Overall assessment for PoPETs survival**: M1 and M2 are real obstacles. But even with M1+M2 addressed, the paper would still benefit from M-A1 (experimental section structure) and M-A2 (parameter table at realistic scales) before submission. A reviewer's natural reading order is: abstract, introduction, experiments, security model, details. The paper currently inverts this: security model is before experiments, experiments are buried in a Discussion subsection. Promoting experiments to a top-level section would help.
