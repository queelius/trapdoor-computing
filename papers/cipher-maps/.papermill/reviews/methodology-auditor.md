# Methodology Auditor Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

This is a theory paper with no experiments. The methodology consists of definitions, constructions, proofs, and parameter analyses. There are no benchmarks, implementations, or empirical evaluations. The methodological audit therefore focuses on: (1) whether the definitions are well-formed, (2) whether the constructions are complete and implementable, (3) whether the proofs establish what they claim, and (4) whether the parameter analyses are rigorous.

## Findings

### F1. Random oracle model used without formal statement (Major, High confidence)
**Location**: Throughout (Definitions 4.1, 5.1, 5.3; Theorems 7.1, 7.2; Propositions 8.2, 8.3)
**Problem**: The paper relies heavily on the random oracle model (ROM) but never formally states it as an assumption. The notation section (line 38 of the formalism) says "Throughout, $h : \{0,1\}^* \to \{0,1\}^n$ denotes a cryptographic hash modeled as a random oracle" but the paper itself has no such global statement. The ROM appears in Definition 4.1 ("under the random oracle model"), Proposition 5.3 ("under the random oracle model"), and the proof of Theorem 7.2 ("under the random oracle model"), but it is never defined.
**Suggestion**: Add a notation/preliminaries paragraph at the start of Section 3 stating: "Throughout, $h$ denotes a cryptographic hash function modeled as a random oracle: a truly random function $h : \{0,1\}^* \to \{0,1\}^n$ accessible to all parties via oracle queries."

### F2. HashSet construction time is exponential but presented matter-of-factly (Minor, High confidence)
**Location**: Section 5.1, lines 501-507
**Quoted text**: "Each candidate seed succeeds with probability $2^{-n|A|}$ (all $|A|$ elements must hash to $0^n$), so the expected number of trials is $2^{n|A|}$."
**Problem**: The expected construction time is $2^{n|A|}$, which is doubly exponential in the number of elements. The paper notes this "motivates the two-level construction of S7" but does not discuss feasibility. For $n=20$ and $|A|=10$, this is $2^{200}$ trials -- utterly infeasible. The HashSet as described is a theoretical construction only, but this is not stated.
**Suggestion**: Add a sentence clarifying: "The single-seed HashSet is a theoretical reference construction establishing the information-theoretic lower bound; practical implementations use the two-level approach of Section 7."

### F3. Entropy map construction time: $\varepsilon^{-\ell}$ grows exponentially in bucket size (Minor, Medium confidence)
**Location**: Section 5.2, lines 539-543
**Quoted text**: "Each candidate seed succeeds independently with probability $\varepsilon^\ell$ (all $\ell$ items must land in valid codewords). The expected number of trials per bucket is $\varepsilon^{-\ell}$, geometric."
**Problem**: The construction time per bucket is $\varepsilon^{-\ell}$, which grows exponentially in bucket size $\ell$. The paper does not state what bucket sizes are practical. For typical $\varepsilon = 2^{-10}$ and $\ell = 3$, this is $2^{30} \approx 10^9$ trials per bucket -- feasible but slow. For $\ell = 5$, it is $2^{50} \approx 10^{15}$ -- infeasible. The paper should discuss practical bucket size limits.
**Suggestion**: Add a sentence: "For feasible construction, bucket sizes are limited to $\ell \leq \lfloor \log_2 T / \log_2(1/\varepsilon) \rfloor$ where $T$ is the trial budget." (The formalism doc has this formula but the paper omits it.)

### F4. Algorithm 1 has no termination guarantee (Minor, High confidence)
**Location**: Algorithm 1 (Singular Hash Map Construction), lines 906-928
**Problem**: The while loop (line 912: "While true") has no termination condition. Under the random oracle model, termination is guaranteed with probability 1 (geometric distribution), but the expected number of trials can be astronomical. The algorithm does not include a trial budget or failure mode.
**Suggestion**: Add a maximum trial count $L_{\max}$ with a failure return when exceeded. The remark on construction with $\eta > 0$ (lines 936-942) partially addresses this by relaxing the correctness constraint, but the algorithm itself should have an explicit termination condition.

### F5. Definition of correctness uses uniform distribution over X (Minor, Medium confidence)
**Location**: Definition 4.3, lines 335-342
**Quoted text**: "For $x$ chosen uniformly from $X$ and $k$ chosen uniformly from $\{0, \ldots, K(x)-1\}$:"
**Problem**: The correctness parameter $\eta$ is defined with respect to the uniform distribution over $X$. But the paper elsewhere discusses distributions $D$ on $X$ (Definition 4.2 for representation uniformity uses an arbitrary distribution $D$). If the distribution over queries is non-uniform, the effective correctness may differ from $\eta$. For the batch constructions (HashSet, entropy map), the failing elements are deterministic for a given seed, so the effective error rate depends on how often those specific elements are queried.
**Suggestion**: Note that $\eta$ is the worst-case (uniform) correctness and that for a specific query distribution $D$, the effective error rate is $\eta_D = \sum_{x \in X} D(x) \cdot \mathbf{1}[\text{dec}(\hat{f}(\text{enc}(x,k))) \neq f(x)]$.

### F6. No experimental validation of any construction (Suggestion)
**Problem**: The paper is purely theoretical. While this is fine for a theory paper, even a small worked example demonstrating the Singular Hash Map on a concrete dataset (e.g., 10 elements, $n=16$ bits) would make the constructions more tangible. The paper has a worked example for the composition chain (100 maps at $\eta = 10^{-6}$, line 1144-1146) but no corresponding example for construction.
**Suggestion**: Add a worked example of the SHM construction for a small dataset, showing the seed search, prefix-free coding, and space achieved.

## Overall Assessment

The methodology is appropriate for a theory paper. The definitions are well-formed, the constructions are clearly specified, and the proofs establish their claims under stated assumptions. The main methodological gap is the lack of a formal ROM assumption statement, which underpins most of the results. The construction time analyses are honest about exponential costs but should be more explicit about practical feasibility limits.

**Reproducibility**: High for theory (definitions and proofs can be verified). Low for implementation (no code, no benchmarks, no concrete parameters for practical use). This is expected for a theory paper.
