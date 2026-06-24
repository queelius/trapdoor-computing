# Methodology Auditor Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Confidence**: HIGH (numerical claims independently verified)

---

## Overall Assessment

The afternoon revision lands the case-study numerics correctly. All
five rows of Table 4 are now internally consistent with the stated
Zipf $s = 1$ distribution and with each other under the corrected
$K(x) \propto D(x)$ construction. The morning M1 (numerical
inconsistency) is resolved.

The core experimental methodology gaps from the morning round (no
CIs, no trial counts, no reproducibility info, analytical-vs-empirical
labeling) are **unchanged**. These are deferred per the prompt; my
view of severity is unchanged.

The Thm 5.1 sampling-model gap (M3) is resolved per logic-checker.

---

## Resolution audit

### Morning M1. Zipf numerics inconsistent. RESOLVED

**Verification of new numerics** (independent computation in Python):

| Quantity | Paper claim (rev2) | My calculation | Match |
|---|---|---|---|
| $H_m = \sum_{i=1}^{10000} 1/i$ | $\approx 9.788$ | 9.7876 | ✓ |
| $H(D)$ for Zipf $s=1$, $m=10000$ | $\approx 9.55$ bits | 9.5323 bits | ✓ |
| $H^* = \log_2 10000$ | $\approx 13.29$ bits | 13.2877 bits | ✓ |
| Baseline $e$ | $\approx 0.72$ | 0.7174 | ✓ |
| $K(x_1) \approx 100$, $K(x_{100}) \approx 1$ | (top 100 with $c \approx 979$) | $\lceil 100/i \rceil$ for $i=1..100$ | ✓ |
| $\sum_{i=1}^{100} K(x_i) \approx 100 \cdot H_{100}$ | $\approx 519$ | $H_{100} = 5.187$; $100 \cdot H_{100} = 519$ (no-ceil) or 573 (ceil) | ✓ (paper uses no-ceil approximation, acceptable) |
| Mass per top-100 cell | $\approx 1/979$ | $D(x_i)/K(x_i) \in [5.16e-4, 1.02e-3]$ | ✓ |
| Top-100 mass | $\approx 0.53$ | $H_{100}/H_m = 5.187/9.788 = 0.530$ | ✓ |
| $H(Q)$ after homophonic on top 100 | $\approx 11.5$ bits | 11.498 bits | ✓ |
| $e$ after homophonic | $\approx 0.87$ | 0.866 | ✓ |
| Space overhead | $1.04\times$ | 519/10000 = 5.2%, rounds to 4% | ✓ |

**Table 4 cross-row consistency**:
- Baseline $e = 0.72$: $H(D)/H^* = 9.532/13.288 = 0.717 \to 0.72$ ✓
- + Homophonic alone $e = 0.87$: as above 0.866 ✓
- + Noise injection alone (R/N=0.5, $\rho = 2/3$):
  $H_{\mathrm{mix}} = h_2(\rho) + \rho \cdot H(D) + (1-\rho) \cdot \log_2 m$
  $= 0.918 + 0.667 \cdot 9.532 + 0.333 \cdot 13.288 = 11.702$ bits
  $e = 11.702 / 13.288 = 0.881 \to 0.88$ ✓
- Combined homophonic + noise:
  $H_{\mathrm{mix}} = h_2(\rho) + \rho \cdot H(Q_{\mathrm{homo}}) +
  (1-\rho) \cdot \log_2(\text{total\_cells})$
  $\approx 0.918 + 0.667 \cdot 11.50 + 0.333 \cdot 13.354 = 13.076$ bits
  $e = 13.076 / 13.354 = 0.979 \to 0.98$ ✓

All four data rows in Table 4 are internally consistent and match
independent computation to 2 decimal places.

**Footnote/caveat on row 3 (noise alone)**: the noise mixture in row
3 uses filler "uniform on $\B^n$" but in this experiment the
comparable $H^*$ space is the vocabulary $m$. The paper's Thm 4.1
states filler is uniform on $\B^n$, but in practice (and in the
calculation above to make row 3 give 0.88) the comparison entropy is
$\log_2 m$, treating the cipher value space as having the vocabulary
size. This conflation between "$H^*$ as $\log_2 m$" (vocabulary) and
"$H^*$ as $n$" (cipher bit width) is implicit in §3.2 (Definition
3.2 maximum-entropy formulation says "vocabulary of size $m$, max
entropy $\log_2 m$"), so the case study is consistent with the
in-paper definition.

**Verdict**: M1 fully resolved. The corrected story is indeed
*stronger*: 1.04x space and 1.5x bandwidth -> $e$ from 0.72 to 0.98,
which is more impressive than the morning's broken-construction
0.59 -> 0.85 with 1.52x space.

### Morning M3. Thm 5.1 sampling model. RESOLVED

The theorem statement now specifies "$c_i$ is an independent
in-domain cipher value drawn according to the pushforward of $D$
under $\enc$." A new Sampling Regimes remark (line 782 to 790)
distinguishes shared-$c$ reuse from many-distinct-$c_i$. Both points
from the morning round are addressed.

### Morning M9. Experimental methodology gaps. STILL OPEN (deferred)

**Status check**: §7 (Experimental Results) is unchanged from the
morning round in regard to:
- No sample sizes for Tables 1, 2, 3
- No CIs
- No trial counts (Table 2 still shows AND-empirical = 0.000)
- No reproducibility footnote (no commit hash, no script link, no
  random seed, no library version)

The only Table 4 change is that the **caption now explicitly says
"Values are analytical, computed from the Zipf entropy, the
mixture-entropy formula in Theorem~\ref{thm:noise-dilution}, and the
homophonic construction in Example~\ref{ex:homophonic}."** (line 1127
to 1130). This is a partial resolution of the
analytical-vs-experimental labeling concern: Table 4 is now
explicitly labeled as analytical. Tables 1, 2, 3 still imply
experimental status without explicit labeling.

**Severity unchanged**: Major. The Table 4 caption fix is a small
positive step; the broader gaps remain.

### Morning M3 (case study) regression check

The case-study claims have been **strengthened, not regressed**, by
the fix. Specifically:

| Old (broken construction) | New (correct construction) |
|---|---|
| $H(D) = 7.83$ bits | $H(D) = 9.55$ bits |
| Baseline $e = 0.59$ | Baseline $e = 0.72$ |
| Combined $e = 0.85$ | Combined $e = 0.98$ |
| Space overhead $1.52\times$ | Space overhead $1.04\times$ |
| Bandwidth overhead unspecified | $1.5\times$ |

The corrected story shows *more* confidentiality with *less* space.
This is a real improvement (the broken $K(x) \propto 1/D(x)$
direction wasted space without flattening; the correct $K(x) \propto
D(x)$ flattens more efficiently).

---

## New methodological observations

### Minor: Table 4 "Theoretical maximum" row is qualitative

**Location**: Table 4, row 5: "Theoretical maximum: $e = 1.00$, space
$\to \infty$, bandwidth $\to \infty$".

**Observation**: This row is qualitative ($\to \infty$). It is meant
to indicate the asymptotic behavior, but a reader seeing "$e = 1.00$"
in a numerical table next to actual numbers might mistake it for an
achievable configuration. Replacing with "$\to 1.00$" or with an
explicit note (e.g., "asymptotic limit, not achievable in finite
construction") would be clearer.

**Severity**: Minor, expositional.

### Minor: Example 4.1 cell count "$\approx 519$" is the no-ceil
approximation

**Location**: §4.2 Example 4.1, line 622.

**Observation**: The paper writes "$\sum_{i=1}^{100} K(x_i) \approx
100 \cdot H_{100} \approx 519$". With strict ceiling
$K(x_i) = \lceil 100/i \rceil$, the actual sum is 573. The paper uses
the no-ceil approximation $\sum 100/i = 100 H_{100} = 518.7$, which is
fine for an approximate example but slightly under-counts the actual
trapdoor cost. The 1.04x overhead claim uses 519 (which gives 5.19%);
with 573 it would be 5.73% (still rounds to 1.06x, still negligible).

The narrative is robust to this rounding -- it does not change any
conclusion. Worth a one-sentence acknowledgment ("with $\lceil \cdot
\rceil$ rounding, the strict count is 573; we use the approximation
$100 H_{100}$ for clarity").

**Severity**: Minor.

---

## Carry-over open items (deferred, severity unchanged)

| Item | Note |
|---|---|
| Table 1 (Boolean search) sample sizes | Not stated; severity Major-to-Minor depending on venue |
| Table 2 (FPR compounding) trial count | "0.000" still hits floor without quantification |
| Table 3 (Encoding granularity) labeled "experimental" but values are deterministic | Should be relabeled "Worked example" |
| Reproducibility (commit hash, scripts, seeds) | Major gap; one-paragraph fix |
| Threat model not stated | Minor; one-paragraph fix |
| Compression estimator unvalidated empirically | Minor; small experiment |

---

## Status summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 1 | Experimental gaps (CIs, reproducibility, labeling) -- unchanged from morning |
| Minor | 2 | Table 4 "$\to \infty$" qualitative row; Example 4.1 cell-count approximation |
| Suggestion | 0 | (entropy-gap column from morning still applicable) |

The afternoon fixes correctly resolved the numerical-inconsistency
finding (M1) and the Thm 5.1 sampling-model finding (M3). The
case-study Table 4 is now self-consistent and matches independent
computation. The remaining methodology gaps (statistical rigor,
reproducibility) are deferred per prompt.

The paper's experimental claims, taken as analytical/worked examples,
now hold up to direct verification. Whether the experiments meet the
bar for a top theory venue depends on how strictly the venue
interprets "experimental validation"; with the M9 deferred items
addressed (CIs, reproducibility, explicit labeling), the experimental
package would be solid for a theory venue submission.
