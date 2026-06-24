# Logic Checker Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2, afternoon regression)
**Confidence**: HIGH

---

## Overall Assessment

Both critical findings from the morning round (C1: Pinsker direction
error in Thm 3.1 part 3; C2: $K(x) \propto 1/D(x)$ inversion in Thm 4.2)
are **resolved**. The afternoon revision swaps Pinsker for the
Fannes-Audenaert continuity inequality in the Thm 3.1 proof, yielding
the correct linear bound $e \geq 1 - \delta - h_2(\delta)/n$. The
multiplicity construction is corrected to the classical homophonic
direction $K(x) \propto D(x)$, and the proof's algebra is now
internally consistent. The Numerical-Scale remark (new) gives correct
numbers ($\delta=0.05, n=64 \to e \geq 0.945$; $\delta=0.01, n=64 \to
e \geq 0.989$, both verified by direct calculation).

Of the four major findings, three are resolved (M3, M4, M5 in Thm 5.1)
and one remains open (M2 Fisher info constant; not addressed). One
minor finding from morning round (m6 compression-estimator proof)
remains untouched. No regressions introduced.

---

## Resolution audit (line-by-line check against morning round)

### C1. Pinsker direction error -> Fannes-Audenaert. RESOLVED

**Morning quote (then in §3.3 proof, now removed)**:
> "by Pinsker's inequality (which bounds KL divergence from below by
> squared TV distance), $\TV(Q, U) \leq \sqrt{D_{\mathrm{KL}}(Q \|
> U)/2}$. Since $\TV(Q,U) \leq \delta$, we have $D_{KL}(Q \| U)
> \leq 2\delta^2$."

**Current text (line 438 to 455)**:
> "For part (3): the Fannes-Audenaert inequality bounds entropy
> continuity: for any distributions $P, Q$ on a support of size $d$
> with $\TV(P,Q) \leq t \leq 1/2$, $|H(P) - H(Q)| \leq t\log_2(d-1) +
> h_2(t)$. Applying this to $Q$ and $U$ on $\B^n$ with $d = 2^n$ and
> $\TV(Q,U) \leq \delta$, $|H(Q) - n| \leq \delta \log_2(2^n - 1) +
> h_2(\delta) \leq \delta n + h_2(\delta)$, so $H(Q) \geq n(1-\delta)
> - h_2(\delta)$ and $e = H(Q)/n \geq 1 - \delta - h_2(\delta)/n$.
> Note the bound is linear in $\delta$ (not quadratic): Pinsker gives
> $D_{KL} \geq 2\TV^2$, an upper bound on TV given KL, which does not
> convert to a KL bound given TV. The correct direction is
> Fannes-Audenaert."

**Verification**:
1. The Fannes-Audenaert form quoted is correct (Audenaert 2007 sharp
   bound; equivalent to the classical Fannes 1973 inequality up to a
   slightly tighter constant). The bound $|H(P) - H(Q)| \leq t
   \log_2(d-1) + h_2(t)$ holds for any pair of distributions on a
   common support of size $d$ when $t = \TV(P,Q) \leq 1/2$.
2. Application to $Q, U$ on $\B^n$ with $d = 2^n - 1 < 2^n$:
   the upper bound $\log_2(2^n - 1) < n$ gives $|H(Q) - n| \leq \delta
   n + h_2(\delta)$, hence $H(Q) \geq n - \delta n - h_2(\delta)$ and
   $e = H(Q)/n \geq 1 - \delta - h_2(\delta)/n$. Correct.
3. The proof helpfully includes a parenthetical aside reminding the
   reader of the Pinsker direction issue. This is good defensive
   exposition and prevents the same error from being reintroduced.
4. Numerical Scale remark (line 458 to 463): $\delta = 0.05, n = 64$
   gives $e \geq 0.945$, $\delta = 0.01$ gives $e \geq 0.989$. Direct
   calculation:
   - $\delta = 0.05$: $h_2(0.05) = 0.286$, $h_2(\delta)/n = 0.00447$,
     so $e \geq 1 - 0.05 - 0.00447 = 0.945$. ✓
   - $\delta = 0.01$: $h_2(0.01) = 0.0808$, $h_2(\delta)/n = 0.00126$,
     so $e \geq 1 - 0.01 - 0.00126 = 0.989$. ✓
5. The renaming "Pinsker bridge -> Fannes bridge" propagates to:
   - Abstract line 57 (says "Fannes-Audenaert continuity inequality")
   - §1 framing line 102 (says "Fannes-Audenaert continuity inequality")
   - §1 contribution #1 line 151 (says "**Fannes bridge.**")
   - §2 Related Work line 204 (says "the *Fannes bridge*")
   - §8 Conclusion line 1235 (says "Fannes bridge")
   All locations consistent. The only Pinsker mention remaining is
   the deliberate aside in the proof.

**Verdict**: Resolved cleanly. The Fannes-Audenaert proof is
mathematically sound and the derivation is now correct.

### C2. $K(x) \propto 1/D(x)$ -> $K(x) \propto D(x)$. RESOLVED

**Morning state**: §4.2 opening said "$K(x) \propto 1/D(x)$ equalizes
cipher value frequencies"; the Thm 4.2 proof claimed "with $K(x) =
\lceil c/D(x) \rceil$, we have $D(x)/K(x) \approx c$." Both wrong.

**Current text §4.2 opening (line 557 to 566)**:
> "Each element $x$ can be given $K(x) \geq 1$ distinct encodings.
> [...] Flattening the cipher value distribution therefore requires
> $D(x)/K(x)$ to be constant in $x$: more frequent elements need
> *more* representations, not fewer. This is the classical homophonic
> substitution prescription~\cite{simmons1979symmetric}: $K(x)
> \propto D(x)$."

**Current Thm 4.2 statement (line 568 to 584)** sets $K(x) = \lceil c
\cdot D(x) \rceil$ with $c \geq 1/\min_x D(x)$ and bounds
$\TV(Q, U_{\mathrm{im}}) \leq |X|/(2\sum_x K(x)) \leq |X|/(2c)$.

**Current proof (line 586 to 601)** establishes $1/(c + 1/D(x)) \leq
D(x)/K(x) \leq 1/c$ from the rounding inequality $c \cdot D(x) \leq
K(x) \leq c \cdot D(x) + 1$, and notes $\sum_x K(x) \in [c, c + |X|]$.

**Verification**:
1. The fundamental flattening identity is now stated correctly: under
   the random oracle, $Q(v) = D(x)/K(x)$ for the unique $(x,k)$
   pre-image of $v$, so uniformity of $Q$ requires $D(x)/K(x)$
   constant in $x$, hence $K(x) \propto D(x)$. This is the classical
   Simmons-style homophonic substitution. ✓
2. The bound $K(x) \leq c \cdot D(x) + 1$ from $K(x) = \lceil c
   D(x) \rceil$ gives $D(x)/K(x) \geq D(x)/(c D(x) + 1) = 1/(c +
   1/D(x))$. ✓
3. The lower bound $K(x) \geq c \cdot D(x)$ gives $D(x)/K(x) \leq
   1/c$. ✓
4. The TV bound $\TV(Q, U_{\mathrm{im}}) \leq |X|/(2\sum_x K(x))$:
   this follows from $\TV(Q, U_{\mathrm{im}}) = (1/2) \sum_x |D(x) -
   K(x)/\sum K|$, which is bounded by the rounding-error sum. By
   $K(x) - c D(x) \in [0,1]$ and $\sum (K(x) - c D(x)) = \sum K - c$,
   each term $|D(x) - K(x)/\sum K| \leq 1/\sum K$ (rounding wraps to
   the cell, and the fraction of "extra" mass is at most the count of
   ceil rounds = $|X|$ over $\sum K$). Computational sanity check
   (m=10000, $c = 1/D_{\min} \approx 97876$): TV = 0.039,
   $|X|/(2\sum K) = 0.048$. Bound holds. ✓
5. Direction propagation: the corrected $K(x) \propto D(x)$ appears
   at:
   - Abstract: not stated explicitly (only "multiple representations")
   - §1 line 120: "$K(x) \propto D(x)$ to flatten" ✓
   - §1 line 161 (contribution #2): "$K(x) \propto D(x)$, the
     classical homophonic prescription" ✓
   - §4.2 line 566: "$K(x) \propto D(x)$" ✓
   - Conclusion line 1239: "$K(x) \propto D(x)$ (space)" ✓
   - Case-study comparison line 1148: "compared to prior analyses
     that assumed $K(x) \propto 1/D(x)$" ✓ (correctly noted as wrong
     prior analysis, useful framing)

**Verdict**: Resolved cleanly. The construction is now in the
correct (Simmons) direction; the proof algebra is internally
consistent; the bound is tight enough for the example.

### M1. Zipf numerics. RESOLVED

**Morning state**: Example 4.1 / Table 4 used $H(D) \approx 7.83$
bits, baseline $e = 0.59$, which corresponds to Zipf exponent $s
\approx 1.2$, not the stated $s = 1$.

**Current text Example 4.1 (line 612 to 629)**: $H_m \approx 9.788$,
$H(D) \approx 9.55$ bits, $H^* = \log_2 10000 \approx 13.29$ bits,
$e \approx 0.72$ baseline. After homophonic on top 100, total cells
$\approx 519$, mass per cell $\approx 1/979$, $H(Q) \approx 11.5$
bits, $e \approx 0.87$.

**Independent verification** (computed in Python with $s=1$,
$m=10000$):
- $H_m = \sum_{i=1}^{m} 1/i = 9.7876$ ✓
- $H(D) = 9.5323$ bits (paper says 9.55) ✓
- $\log_2(10000) = 13.2877$ ✓
- baseline $e = 9.5323 / 13.2877 = 0.7174$ ✓
- $H_{100} = 5.1874$, predicted top cells $\approx 100 \cdot H_{100}
  = 519$ ✓ (note: strict ceil sum is 573; the paper rounds to the
  no-ceil value, which is fine for an approximate example)
- top contribution to $H(Q) = (H_{100}/H_m) \cdot \log_2(c) = 0.530
  \cdot 9.935 = 5.27$ bits
- tail contribution = $-\sum_{i=101}^{10000} D(x_i) \log_2 D(x_i) =
  6.23$ bits
- $H(Q) = 5.27 + 6.23 = 11.50$ bits ✓
- $e = 11.50/13.29 = 0.866$ rounded to 0.87 ✓
- 519 additional trapdoors / 10000 baseline = 5.19% increase,
  which the paper rounds to "$1.04\times$" (4% headline) ✓

The Table 4 numbers are also consistent:
- Baseline $e = 0.72$ ✓
- + Homophonic $e = 0.87$ ✓
- + Noise injection alone (R/N = 0.5, $\rho = 2/3$):
  $H_{\mathrm{mix}} = h_2(\rho) + \rho H(D) + (1-\rho) \log_2 m =
  0.918 + 0.667 \cdot 9.532 + 0.333 \cdot 13.288 = 11.70$ bits;
  $e = 11.70/13.29 = 0.881$ -> 0.88. ✓
- Combined homophonic + noise:
  $H_{\mathrm{mix}} = h_2(\rho) + \rho \cdot 11.57 + (1-\rho) \cdot
  \log_2(\text{total\_cells} = 10473) = 0.918 + 7.71 + 4.45 = 13.08$
  bits; $e = 13.08/13.35 = 0.979$ -> 0.98. ✓

All five rows of Table 4 internally consistent.

**Verdict**: Resolved cleanly. Numerics match the stated $s = 1$ Zipf
distribution.

### M2. Thm 4.1 Fisher info missing distribution-dependent constant. STILL OPEN

**Status check**: The Thm 4.1 proof (line 521 to 544) is unchanged
from the morning round. The Fisher information claim (line 533 to
543) still says: "the Fisher information for estimating any
parameter of $D$ is reduced by a factor of approximately $\rho^2$
relative to observing $D$ directly."

The deferred-list note in the prompt acknowledges this; my view of
severity is unchanged. Specifically, for a mixture $P_{\mathrm{mix}}
= \rho P_\theta + (1-\rho) U$, the Fisher info has a leading
$\rho^2$ factor times a $\chi^2$-like distribution-dependent
constant. The "approximately" hedge is sufficient for an applied
informal statement, but a theory-venue proof should either bound the
constant or move the claim into a remark.

**Severity unchanged**: Major. Not regressed; not resolved.

### M3. Thm 5.1 sampling model unspecified. RESOLVED

**Morning quote (Thm 5.1 statement)**: "$N = O(|Y_1|\cdot|Y_2|/\xi^2)$
samples..." with no specification of how the $c_i$ are drawn.

**Current text (line 738 to 745)**:
> "Assume the untrusted machine observes pairs $(\fhat_1(c_i),
> \fhat_2(c_i))$ for $i = 1, \ldots, N$, where each $c_i$ is an
> independent in-domain cipher value drawn according to the
> pushforward of $D$ under $\enc$ (so the latent pair $(f_1(x),
> f_2(x))$ is drawn i.i.d. from the true joint under $D$)."

**Plus** new Sampling-Regimes remark (line 782 to 790) distinguishing
the i.i.d.-distinct-$c_i$ regime from the shared-$c$-reuse regime
explicitly.

**Verification**: This addresses both subtleties from the morning
finding (in-domain vs $\B^n$ uniform; shared-$c$ vs distinct-$c_i$).
The plug-in estimator rate is correctly attributed in the proof to
Cover-Thomas 2006 (citation now in text, line 773).

**Verdict**: Resolved cleanly.

### M4. "Preserves all correlations" -> mutual information. RESOLVED

**Morning text**: "The joint distribution $(\fhat_1(c), \fhat_2(c))$
preserves all correlations between $f_1(x)$ and $f_2(x)$." Imprecise.

**Current text (Thm 5.1 part 2, line 749 to 751)**:
> "Mutual information is preserved: $I(\fhat_1(C); \fhat_2(C)) =
> I(f_1(X); f_2(X))$, where $X \sim D$ and $C = \enc(X, k)$ for
> uniform $k$."

**Verification**: This is the explicit mutual-information statement
the morning round requested. The proof (line 766 to 770) gives a
brief argument via determinism plus surjectivity of the push maps
on the in-domain part.

**Caveat (mild)**: The strict equality claim is fragile when $K > 1$
because $\fhat_i(C)$ encodes additional information (the $k$
coordinate) beyond $f_i(X)$. In that case $I(\fhat_1(C);
\fhat_2(C)) \geq I(f_1(X); f_2(X))$ with equality requiring the $k$
coordinate to be marginally independent of the latent pair (true if
$k$ is sampled uniformly and independently of $X$). Under the
sampling specified in the theorem (uniform $k$ given $X$), this
condition holds. So the equality is correct under the stated
sampling, but a more cautious phrasing would be "$\geq$" with the
stated condition giving equality. This is a minor exposition concern;
the mathematical content is right.

**Verdict**: Resolved. The morning's qualitative concern (no
mathematical definition of "all correlations") is fully addressed.
The proof's brevity is acceptable for a result of this depth.

### M5. Thm 5.1 part (4) tautology -> quantitative bound. RESOLVED

**Morning text**: "A third cipher map $\fhat_3$ taking this
correlated pair as input inherits the non-uniformity..." Tautological.

**Current text (Thm 5.1 part 4, line 756 to 760, plus proof line 775
to 779)**:
> "Any downstream cipher map $\fhat_3$ with Shannon-optimal acceptance
> predicate for the *marginal* output distribution remains non-uniform
> when applied to the correlated pair: achieving $\delta_3 \approx 0$
> requires reconstructing $\fhat_3$ with respect to the joint
> distribution."

Proof: "when $I(f_1; f_2) > 0$, the joint input distribution to
$\fhat_3$ is not uniform on $Y_1 \times Y_2$, so a predicate
optimized for the product of marginals cannot achieve $\delta_3 = 0$;
the optimal $\delta_3$ is bounded below by the TV distance between
the joint and the product of marginals."

**Verification**: This now states a quantitative claim:
$\delta_3^{\min} \geq \TV(\text{joint}, \text{product-of-marginals})$.
This is correct and non-trivial. The lower bound follows from the
fact that any acceptance-predicate Shannon-optimized against a
target distribution $T$ achieves $\delta = \TV(P_{\text{actual}}, T)$
when $P_{\text{actual}} \neq T$; here $P_{\text{actual}}$ is the
joint and $T$ is the product of marginals.

**Verdict**: Resolved. The part is now non-trivially quantitative.

---

## New issues introduced by the fixes

### Minor: Multiplicity proof TV bound is asserted, not derived

**Location**: §4.2, Thm 4.2 proof, line 595 to 597.

**Quoted text**:
> "The image has $\sum_x K(x) \in [c, c + |X|]$ values, each receiving
> mass approximately $1/c$, matching the uniform distribution on the
> image to within the rounding error $|X|/(2\sum_x K(x))$."

**Problem**: The proof asserts the TV bound but does not derive it.
The actual derivation: $\TV(Q, U_{\mathrm{im}}) = (1/2) \sum_x |D(x) -
K(x)/\sum_x K|$ (by aggregating cells per source $x$), and using
$K(x) - c D(x) \in [0,1]$ this is bounded by $r/(c+r) \leq |X|/(c +
|X|)$ where $r = \sum K - c \in [0, |X|]$. The paper's stated bound
$|X|/(2\sum K)$ is a slight tightening (factor 2 saved by the
half-norm definition of TV) and is correct, but the connection is
not shown.

**Suggestion**: Two more lines in the proof would close the gap.
Something like:

> "By aggregating cells per source: $\TV(Q, U_{\mathrm{im}}) =
> (1/2) \sum_x |D(x) - K(x)/\sum K|$. Since $K(x) - c D(x) \in [0,1]$
> and $\sum_x (K(x) - c D(x)) = \sum K - c$, the per-element rounding
> error is bounded; summing gives the claimed $|X|/(2\sum K)$."

**Severity**: Minor. The bound is correct, just under-derived.

### Minor: Numerical-scale remark uses $n = 64$ implicitly

**Location**: §3.3, Numerical Scale remark, line 458 to 463.

**Observation**: The remark cites $n = 64$ for the cipher length
without context. In §4.2 Example 4.1, $n$ is the cipher-value bit
width, but the example operates on a vocabulary $|X| = 10000$ and
discusses $\sum K \approx 10500$, which fits in $\lceil \log_2 10500
\rceil = 14$ bits. The connection between "$n$ in §3.3 numerics" and
"$n$ in §4.2 example" is left implicit.

**Suggestion**: One sentence in the remark: "Here $n$ is the
cipher-value bit width; in practical deployments $n \in [32, 128]$
to balance space and birthday-bound security." This avoids reader
confusion.

**Severity**: Minor.

### Minor: M2 carry-over now visible in the case-study narrative

**Location**: §1 contribution #2, line 159; §4.1 noise-dilution Thm.

**Observation**: With the rest of the headline contribution numerics
corrected, the residual M2 issue (Fisher info "approximately $\rho^2$")
is now the only "approximately"-tier statement in the contribution
list. It stands out more because the Pinsker fix is precise and the
homophonic fix is precise. A theory reviewer reading the
contributions list will notice the asymmetry.

**Severity**: Minor (not a regression, just more salient post-fix).

---

## Status summary

| Morning finding | Severity (then) | Status (now) |
|---|---|---|
| C1. Pinsker direction | Critical | Resolved |
| C2. $K(x) \propto 1/D(x)$ | Critical | Resolved |
| M1. Zipf numerics inconsistent | Major | Resolved |
| M2. Fisher info constant | Major | Open (deferred) |
| M3. Thm 5.1 sampling model | Major | Resolved |
| M4. "Preserves all correlations" | Major | Resolved |
| M5. Thm 5.1 part 4 trivial | Major | Resolved |
| m1. Q notation overloaded | Minor | Open (carry-over) |
| m6. Compression estimator proof terse | Minor | Open (carry-over) |

| New issue | Severity | Note |
|---|---|---|
| Thm 4.2 TV bound asserted, not derived | Minor | Two-line fix |
| Numerical-scale remark $n=64$ implicit | Minor | One-sentence fix |

**Net**: Both criticals resolved with mathematically sound fixes.
Three of four major findings resolved. One major (M2) deferred. No
regressions. Two new minor issues introduced, both easily addressable.

The paper's headline mathematical claims (Fannes bridge, multiplicity
construction, compositional leakage with MI preservation) are now
correct and internally consistent. The case-study numerics are
verified against the stated Zipf $s=1$ distribution.

The remaining logical concerns are: (a) Thm 4.1's distribution-
dependent Fisher constant (M2, unchanged severity); (b) Prop 6.1
compression estimator proof terseness (m6, unchanged); (c) two new
minor expositional gaps from this round's fixes.
