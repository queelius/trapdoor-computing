# Methodology Auditor Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: MEDIUM-HIGH

---

## Overall Assessment

The paper combines theoretical development with experimental validation.
The theoretical methodology (information-theoretic, probabilistic) is
sound in its choice of tools but (per the logic-checker's findings) has
two critical derivation errors in the core theorems. The experimental
methodology retains most of the prior round's weaknesses, with only
minor movement: no confidence intervals, no reproducibility pointers,
and the case study is still ambiguous about analytical vs. empirical.

Resolution of the 2026-04-09 methodology concerns:

| Prior concern | Status | Comment |
|---|---|---|
| Experimental scale too small (MAJOR) | Unresolved | Tables 1, 2, 3, 4 still have no sample sizes, no CIs |
| No baselines / comparative evaluation (MAJOR) | Unresolved | No comparison to SSE schemes; internal-consistency only |
| Case study methodology unclear (MAJOR) | Unresolved | Table 4 still presented as experimental; values appear analytical |
| Reproducibility gaps (MINOR) | Unresolved | No library version, no scripts pointer, no commit hash |

---

## MAJOR: Theorem 5.1 sample-complexity claim requires operational context

**Location**: Section 5.1, Theorem 5.1 part (3), lines 691 to 694.

**Problem**: The theorem states "$N = O(|Y_1| \cdot |Y_2|/\xi^2)$ samples
suffice for TV accuracy $\xi$." This is the correct plug-in estimator
rate (covered by Weissman et al. 2003; see also Han et al. 2015 for
minimax rates in empirical distribution estimation). However, the
applicability of this rate to the cipher-maps setting has subtleties that
the paper's methodology does not address:

1. **Sampling model**: The rate assumes i.i.d. samples from the true
   joint distribution on $Y_1 \times Y_2$. In the cipher maps setting,
   the adversary observes $(\fhat_1(c_i), \fhat_2(c_i))$ pairs for
   various $c_i$. For the rate to apply, the $c_i$ must be sampled
   i.i.d. from a distribution that makes the pair (after applying the
   deterministic $\fhat_1, \fhat_2$) follow the true latent joint. This
   requires $c_i \sim$ (pushforward of $X \sim D$ under $\enc$), not
   $c_i$ uniform on $\B^n$. The distinction matters: under the second
   sampling model, most $c_i$ are out-of-domain and contribute uniform
   noise, making the effective sample size much smaller.

2. **Shared vs. distinct cipher values**: The theorem says "$N$ shared-$c$
   observations" but in a typical cipher-map deployment, each query
   corresponds to a distinct $c_i$. The adversary accumulates
   observations over many distinct $c_i$, not many evaluations at the
   same $c$. The paper should clarify which sampling regime it models.
   If the regime is distinct $c_i$, the estimator averages over
   $c \sim Q$ and recovers the joint of $(\fhat_1, \fhat_2)$ under $Q$,
   not just the latent joint of $(f_1, f_2)$.

3. **Tightness**: No lower bound is proven. A lower bound (showing that
   no estimator can do better than $\Omega(|Y_1||Y_2|/\xi^2)$) would
   upgrade the result from a statistical rate to an
   information-theoretic impossibility. Without this, the result says
   only "the obvious estimator works"; it does not rule out better
   estimators.

**Suggestion**:
1. Specify the sampling model explicitly in the theorem statement.
2. Distinguish "observations at a single shared $c$" (what the theorem's
   proof assumes implicitly) from "observations across distinct
   $c_i \sim Q$" (the deployment-realistic regime).
3. Add a remark: "This rate is achieved by the plug-in estimator; a
   matching lower bound via Le Cam's method is sketched in Appendix X."

---

## MAJOR: Experimental claims remain unsubstantiated (carry-over from 2026-04-09)

**Location**: Section 7 (Experimental Results), Tables 1, 2, 3, 4.

**Problem**: The same concerns from the prior review remain:

- **Table 1 (Boolean search)**: 5,000 documents, no stated trial count,
  no CIs. Precision 0.39 / 0.76 / 0.97: the paper does not say whether
  these are means over queries (and how many), nor variance.
- **Table 2 (FPR compounding)**: AND chain empirical = 0.000 for
  $k = 3, 4, 5$ hits the measurement floor. The paper acknowledges
  "below measurable levels" (line 1016) but does not quote the sample
  size, so the floor is not quantified. With $p_T = 0.05$ and $k = 3$,
  theoretical FPR is $1.25 \times 10^{-4}$, requiring $N \sim 10^5$
  trials to observe single-digit events. Was that the trial size? The
  paper is silent.
- **Table 3 (Encoding granularity)**: 150 inputs is a toy scale for a
  "7-function decision pipeline"; the bits/element numbers (33.5, 64.2,
  112.9) are deterministic given the build, so they are analytical
  results, not experimental measurements. Labeling them as experimental
  is misleading.
- **Table 4 (Case study)**: Values are computed from the formulas in
  §4; they are analytical, not empirical. Labeling "59% to 85%" as
  "experimental validation" is misleading. Additionally, per the
  logic-checker, the construction underlying $e = 0.77$ is miscomputed
  (the $K(x) \propto 1/D(x)$ direction is backwards).

**Suggestion**:
1. Relabel §7.3 (Encoding Granularity) and §7.4 (Case Study) as
   "Worked Examples" or add a clear statement that the values are
   computed analytically from the theory and confirmed by a single
   deterministic build, not measured across trials.
2. Table 2: add the trial count $N$ and replace 0.000 with the upper
   confidence limit (e.g., "$< 1/N = 10^{-5}$" rather than 0.000).
3. Table 1: add CI columns or at minimum state the query set size
   and whether per-query variance is reported.
4. Correct the $e$ values in Table 4 once the $K(x)$ direction is
   fixed; the corrected baseline Zipf entropy is approximately 9.53 bits
   (not 7.83), giving baseline $e \approx 0.72$ (not 0.59).

---

## MAJOR: Case study values do not match the stated distribution

**Location**: Section 4.2 Example 5 (line 562 to 572) and Section 7.4 Case Study (Table 4).

**Problem**: The example states "Zipf distribution $D(x_i) \propto 1/i$"
on $m = 10000$ and claims $H(D) \approx 7.83$ bits, $e \approx 0.59$.
An independent numerical calculation (verified by this reviewer):

```python
# Zipf s=1, m=10000
H_m = sum(1/i for i in range(1, m+1))  # = 9.7876
D = [1/(i*H_m) for i in range(1, m+1)]
H = -sum(d * log2(d) for d in D)  # = 9.532 bits
```

So $H(D) = 9.532$ bits, $e = H(D)/\log_2 10000 = 9.532/13.287 = 0.717$,
not the paper's claimed 0.59.

To get $H(D) \approx 7.83$ and $e \approx 0.59$, the Zipf exponent must
be approximately $s = 1.2$, not $s = 1$ (exponents 1.2 gives $H \approx
7.19$; exponent 1.15 gives $H \approx 8.33$). The paper's stated
"$\propto 1/i$" is Zipf $s = 1$, which does not produce the claimed
$e = 0.59$.

This error propagates through Example 5, Table 4 row 1 (Baseline), and
the 52%/50% overhead narrative in the Conclusion.

**Suggestion**:
1. Specify the Zipf exponent explicitly (e.g., "Zipf-Mandelbrot with
   exponent $s = 1.2$") and recompute $H(D)$ from that.
2. Alternately, use $s = 1$ and report corrected numbers: $e = 0.72$
   baseline, and corresponding improvements under (correctly-directed)
   homophonic + noise.
3. The "518 additional trapdoors per document" number in Example 5 also
   does not reconcile with $b = 100, K(x_i) = i$ (which gives 5050 new
   reps total across vocabulary, not 518 per document). Either justify
   or correct.

---

## MAJOR: No reproducibility information

**Location**: Section 7, header line 957 to 960.

**Problem**: The paper states "We validate the theoretical predictions
using the `cipher-maps` Python library" and references the 20 Newsgroups
corpus, but provides:
- No library version or commit hash
- No link to experimental scripts or notebooks
- No random seed or deterministic-build details
- No 20 Newsgroups version (many exist: original, train-only, 3.0, etc.)
- No specification of which 5,000 documents were used in Table 1

For a paper that makes numerical claims (FPR ratios of 0.97, 1.01; exact
entropy ratios 0.59, 0.77), reproducibility is essential for peer
verification.

**Suggestion**: Add a "Reproducibility" paragraph or footnote in §7
giving: library commit hash, python version, random seed, corpus URL
and version, script repository URL. A typical template:

> "All experiments use `cipher-maps` v0.X.Y (commit abcdef) on Python
> 3.11, with seed 42. The 20 Newsgroups corpus is the 'by-date'
> variant from scikit-learn (sklearn.datasets.fetch_20newsgroups).
> Scripts and configuration available at URL."

---

## MINOR: Threat model is implicit

**Location**: Throughout, especially §3.1 and §5.1.

**Problem**: The paper assumes an honest-but-curious adversary that
observes the cipher-value stream and can apply any exposed cipher map,
but this is never stated as a threat model. Thm 5.1 implicitly assumes
the adversary can observe repeated evaluations on shared $c$ values;
this capability is not standard and depends on what the deployment
exposes.

The 2026-04-09 review suggested adding an explicit threat model. This
has not landed.

**Suggestion**: Add a "Threat model" paragraph to §3.1 stating:
- What the adversary holds (the cipher map function $\fhat$ and its
  exposed operations; the cipher-value stream).
- What the adversary can compute (any polynomial-time function of the
  observed stream; any composition of exposed cipher maps).
- What the adversary tries to learn (the query distribution $D$, the
  latent values $f(x)$, or the pre-image $x$).
- What is out of scope (side channels, timing, bandwidth, compromised
  trusted machine).

---

## MINOR: Compression estimator evaluation has no empirical anchor

**Location**: Section 6.1, lines 879 to 899.

**Problem**: The compression estimator is claimed as a "practical" tool,
but no experiment demonstrates it on the 20 Newsgroups cipher-value
streams. The closest check would be: for a known-entropy synthetic
stream, compute $\hat{H}$ via gzip and compare to the true $H$; then
repeat on an actual cipher-value stream and report $\hat{H}$.

Without such a check, "practical" is aspirational. A simple experiment
(one table with "stream type, true $H$, gzip $\hat{H}$, error") would
materially strengthen §6.

**Suggestion**: Add a small experiment validating the compression
estimator against known-entropy synthetic streams and report the bias
empirically. This would also substantiate the "positively biased"
claim in the proposition.

---

## SUGGESTION: Add entropy-gap reporting to Table 4

Table 4 reports $e$ values but not the absolute entropy gap
$H^* - H = n \cdot (1 - e)$ in bits. For a practitioner thinking about
"bits leaked per query", the gap is more operationally meaningful than
the ratio. Adding a "bits leaked" column would clarify the stakes (e.g.,
$e = 0.85$ with $n = 64$ means 9.6 bits leaked per query, which is
easier to reason about than "15% of max entropy").

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 4 | Thm 5.1 sampling model unspecified; experimental stats gaps (carry-over); case study values do not match stated Zipf; no reproducibility info (carry-over) |
| Minor | 2 | Implicit threat model; no empirical anchor for compression estimator |
| Suggestion | 1 | Add entropy-gap column to Table 4 |

The theoretical methodology is appropriate for the claimed contributions,
but two central theorems have correctness issues (per logic-checker).
The experimental methodology is unchanged from the prior round and has
the same gaps. The numerical inconsistency in Example 5 / Table 4 (Zipf
$s=1$ does not give the claimed $H$) is a significant newly-identified
issue that undermines the case-study narrative.
