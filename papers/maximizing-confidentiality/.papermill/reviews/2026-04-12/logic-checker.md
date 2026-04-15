# Logic Checker Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: HIGH

---

## Overall Assessment

The paper contains three theorems and one proposition that collectively carry
the headline contribution (Pinsker bridge, two constructions, compositional
bound). Two of these carry **critical mathematical errors** that survive from
the prior round in revised form: the Pinsker bridge (Thm 3.1 part 3) is
derived by applying Pinsker's inequality in the wrong direction, and the
multiplicity construction (Thm 4.2) has the heuristic $K(x) \propto 1/D(x)$
backwards. It makes the cipher distribution *more* non-uniform, not less.
The noise dilution theorem (Thm 4.1) has a Fisher-information claim that is
correct in scaling but missing a distribution-dependent constant, and the
compositional leakage theorem (Thm 5.1) is directionally correct but
underspecified in how the joint is characterized.

The prior critical finding (C1, extra $H^*$ factor in Eq. 2) has been fixed
cleanly. The prior critical mismatch (C1a, statement vs proof of part 3) has
been fixed. But the fix introduced a new, deeper error: the Pinsker step
itself is mis-applied.

---

## CRITICAL: Pinsker's inequality is used in the wrong direction (Thm 3.1 part 3)

**Location**: Section 3.3, Theorem 3.1 part (3), proof at lines 421 to 428.

**Quoted text (proof)**:
> "For part (3): by Pinsker's inequality (which bounds KL divergence from
> below by squared TV distance), $\TV(Q, U) \leq \sqrt{D_{\mathrm{KL}}(Q \|
> U) / 2}$. Since $\TV(Q, U) \leq \delta$, we have $D_{\mathrm{KL}}(Q \| U)
> \leq 2\delta^2$."

**Problem**: Pinsker's inequality states (in nats)
$D_{KL}(P \| Q) \geq 2\, d_{TV}(P, Q)^2$,
equivalently $d_{TV} \leq \sqrt{D_{KL}/2}$. This gives an **upper bound on
$d_{TV}$ given $D_{KL}$**, i.e., a **lower bound on $D_{KL}$ given
$d_{TV}$**. The proof asserts the reverse: "$d_{TV} \leq \delta$ implies
$D_{KL} \leq 2\delta^2$." This **does not follow** from Pinsker (and in
general is false). To upper-bound $H^* - H(Q) = D_{KL}(Q \| U)$ from a TV
bound, one needs Fannes-type inequalities, not Pinsker.

Concretely, with $Q = (1-\delta) U + \delta \cdot \mathbf{1}_{c_0}$ (point
mass at $c_0$), we have $d_{TV}(Q, U) = \Theta(\delta)$ while
$D_{KL}(Q \| U) = \Theta(\delta \cdot n)$, not $O(\delta^2)$. This
counterexample shows the paper's derivation is invalid. The **correct**
Fannes bound gives $e \geq 1 - \delta - h(\delta)/n$ (linear in $\delta$),
not $1 - 2\delta^2/n$ (quadratic in $\delta$). For $\delta = 0.05, n=64$:
paper claims $e \geq 0.9999$; Fannes gives $e \geq 0.945$. The gap is
meaningful: 5 percentage points of leakage per query, compounding rapidly
under multiple observations.

There is also a unit inconsistency: the equality
$H(Q) = n - D_{KL}(Q \| U)$ requires $D_{KL}$ in bits, but Pinsker as
written ($D_{KL} \geq 2 d_{TV}^2$) is the natural-log (nats) form. In bits,
the constant is $2/\ln 2 \approx 2.885$.

**Impact**: This is the paper's **headline novelty**, the "Pinsker bridge
making $\delta$ the operational handle for confidentiality engineering." It
is the first contribution claimed in the abstract, Introduction, and
Theorem 3.1. The derivation is mathematically invalid, and the resulting
quantitative bound is provably too tight by a factor of $n/(2\delta)$ or
more.

**Suggestion**:
1. Replace the Pinsker step with a Fannes-type inequality.
   The standard form (Fannes 1973; cf. Alicki and Fannes 2004): for
   $d_{TV}(Q, U) \leq \delta \leq 1/2$ on a support of size $2^n$,
   $|H(Q) - H(U)| \leq \delta \log_2(2^n - 1) + h_2(\delta)$
   where $h_2$ is binary entropy in bits. This yields
   $e \geq 1 - \delta - h_2(\delta)/n$.
2. Update the abstract, Introduction, and contribution list to reflect the
   linear-in-$\delta$ bound (not quadratic).
3. If the quadratic bound is essential to the narrative, restrict to the
   case where $D_{KL}(Q \| U)$ is small (by assumption, not derivation),
   and use Pinsker to translate that into a TV bound. That is the opposite
   direction, which is sound.

---

## CRITICAL: Multiplicity construction $K(x) \propto 1/D(x)$ is backwards (Thm 4.2, Example 5)

**Location**: Section 4.2, lines 524 to 525 (intro), Theorem 4.2 proof at
lines 538 to 551, Example 5 at lines 562 to 572. Also Introduction, line 113.

**Quoted text (§4.2 intro)**:
> "Assigning $K(x) \propto 1/D(x)$ equalizes the cipher value frequencies,
> achieving $\delta \approx 0$."

**Quoted text (Thm 4.2 proof)**:
> "With $K(x) = \lceil c / D(x) \rceil$, we have $D(x) / K(x) \approx c$ for
> all $x$."

**Problem**: This algebra is wrong and the prescription is backwards.

Step-by-step: the trusted machine samples $x \sim D$, then $k$ uniformly
from $\{0,\ldots,K(x)-1\}$, and maps to $\enc(x, k)$. Under random oracle
(no collisions), the cipher value distribution $Q(v)$ for the unique
$(x, k)$ mapping to $v$ is $Q(v) = D(x) \cdot (1/K(x)) = D(x)/K(x)$.

For $Q$ to be uniform, we need $D(x)/K(x) = \text{const}$ across all $x$,
i.e., **$K(x) \propto D(x)$** (heavier elements get more representations,
not fewer).

With the paper's $K(x) = c/D(x)$:
$D(x)/K(x) = D(x) / (c/D(x)) = D(x)^2/c$,
which depends on $D(x)$ and is **not** constant. This does not equalize
cipher frequencies; it actually spreads the rare elements' mass across
many cipher cells while leaving the heavy element's mass concentrated in
few cells.

A worked example confirms: take $D(a) = 0.9, D(b) = 0.1$. Paper's
prescription: $K(a) = c/0.9 \approx 1, K(b) = c/0.1 \approx 9$.
Cipher distribution: one cipher for $a$ at mass 0.9; nine ciphers for $b$
at mass $\approx 0.011$ each. This is **more** skewed than the original,
not flatter.

Correct construction (classical homophonic substitution, Simmons 1979):
$K(a) = 9, K(b) = 1$. Nine ciphers for $a$ at mass $0.1$ each; one cipher
for $b$ at mass $0.1$. Uniform.

The prose in the paper even says the right thing ("frequent values get
more representations", cf. the cipher-maps companion paper line 339 to 340,
which also contradicts its own formula), but the formula states the
opposite.

**Impact**: This is the paper's second headline construction. Both the
formula and the TV bound derived in Thm 4.2 are incorrect. The error
propagates to Example 5 (Zipf homophonic), Table 4 (case study), and the
Introduction bullet list (line 113 "$K(x) \geq 1$ encodings, with
$K(x) \propto 1/D(x)$ to flatten the cipher value distribution").

Note: the error also appears in the cipher-maps companion paper's
definition of the same construction (`cipher_maps.tex` line 187 and line
338). The companion paper is outside this review's scope, but the error
propagates inward.

**Suggestion**:
1. Replace every occurrence of "$K(x) \propto 1/D(x)$" with
   "$K(x) \propto D(x)$", the correct classical homophonic rule.
2. Rewrite the proof of Thm 4.2: under random oracle, if $K(x) = \lceil
   c \cdot D(x) \rceil$ for a constant $c \geq 1/D_{\min}$, then
   $D(x)/K(x) \in [1/(c \cdot D_{\min}), \,1/c]$, giving
   $\TV(Q, U) \leq C/(c \cdot D_{\min})$ for an explicit constant.
3. Update Example 5 and Table 4 with correctly-computed homophonic
   entropies (this reviewer's independent computation: for Zipf $s=1$,
   $m = 10000$, correctly-flattened top-100 gives $e \approx 0.93$; paper
   currently claims $e = 0.77$ with the backwards prescription).

---

## MAJOR: Fisher information reduction by $\rho^2$ under-specified (Thm 4.1 part 3)

**Location**: Section 4.1, Theorem 4.1 part (3), proof at lines 496 to 509.

**Quoted text**:
> "When $\rho \ll 1$ (filler dominates), the mixture is approximately
> uniform and the Fisher information for estimating any parameter of $D$
> is reduced by a factor of approximately $\rho^2$ relative to observing
> $D$ directly."

**Problem**: For a mixture $P_{\text{mix}}(c) = \rho P_\theta(c) + (1-\rho) U(c)$,
a careful computation gives
$I^{\text{mix}}(\theta) = \rho^2 \sum_c (\partial_\theta P_\theta)^2 / P_{\text{mix}}(c)$.

As $\rho \to 0$, $P_{\text{mix}} \to U$ (not $P_\theta$), so
$I^{\text{mix}}(\theta) \to \rho^2 \sum_c (\partial_\theta P_\theta)^2 / U(c)$.

Compared to $I^{\text{pure}}(\theta) = \sum_c (\partial_\theta P_\theta)^2 / P_\theta(c)$, the ratio is
$\rho^2 \cdot \frac{\sum_c (\partial_\theta P_\theta)^2 / U(c)}{\sum_c (\partial_\theta P_\theta)^2 / P_\theta(c)}$.

This ratio is $\rho^2$ multiplied by a **distribution-dependent constant**
($\chi^2(P_\theta, U)$-like quantity) that can be much larger than 1 when
$P_\theta$ is non-uniform. The proof implicitly assumes $P_\theta \approx U$,
which is the *opposite* of the interesting case (where $P_\theta = D$ is
skewed and the adversary is trying to recover the skew).

The scaling "$\rho^2$" is correct as an asymptotic growth exponent in
$\rho \to 0$, but the leading constant is distribution-dependent and not
universal.

**Suggestion**: State Theorem 4.1 part (3) as: "the Fisher information
$I^{\text{mix}}(\theta) \leq C(D) \cdot \rho^2 \cdot I^{\text{pure}}(\theta)$
for a constant $C(D)$ depending on the ratio $\max_c D(c)/U(c)$." Or,
alternately, provide the full mixture Fisher formula with the leading
constant made explicit. The current informal "approximately $\rho^2$" is
adequate as a heuristic but should not be presented as the main conclusion
of a theorem.

---

## MAJOR: Theorem 5.1 "preserves all correlations" is imprecise

**Location**: Section 5.1, Theorem 5.1 part (2), line 689 to 690.

**Quoted text**:
> "The joint distribution $(\fhat_1(c), \fhat_2(c))$ preserves all
> correlations between $f_1(x)$ and $f_2(x)$."

**Problem**: This is handwavy language for a theorem statement. "All
correlations" is undefined. What the joint actually preserves (given
determinism of $\fhat_i$) is the conditional distribution
$P_{(\fhat_1, \fhat_2) | C = c}$ as a Dirac mass, and marginalizing over
$c \sim Q$ gives a joint distribution over $Y_1 \times Y_2$ whose
**mutual information** equals $I(f_1(X^\ast); f_2(X^\ast))$ where $X^\ast$
is distributed according to the pushforward of $Q$ under $\enc^{-1}$ (in
the in-domain case) or uniform in the out-of-domain case.

The prior 2026-04-09 review raised the same concern (m4). The fix (going
from "correlation" to "mutual information") has not landed. The sample
complexity in part (3) is correct but part (2)'s language remains
imprecise.

**Suggestion**: Replace with: "The joint distribution preserves mutual
information: $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X^\ast); f_2(X^\ast))$,
where $X^\ast \sim Q \circ \enc^{-1}$."

Additionally, clarify whether $C$ is drawn uniformly from $\B^n$
(includes out-of-domain $c$) or uniformly from $\text{Im}(\enc)$
(in-domain only). The two cases give different answers:
- Out-of-domain dominant: $\fhat_i(c)$ is uniform and uncorrelated, so
  joint is approximately uniform on $Y_1 \times Y_2$ and leaks nothing.
- In-domain: $\fhat_i(c) = f_i(\dec(c))$ and the joint leaks the latent
  $(f_1, f_2)$ correlation.

The distinction matters: the theorem's sample complexity is useful only
when the adversary can restrict observation to in-domain cipher values,
which is a nontrivial capability not derivable from the four cipher map
properties.

---

## MAJOR: Theorem 5.1 part (4) reduces to a banal fact

**Location**: Section 5.1, Theorem 5.1 part (4), line 695 to 698.

**Quoted text**:
> "A third cipher map $\fhat_3$ taking this correlated pair as input
> inherits the non-uniformity, even if $\fhat_3$'s acceptance predicate
> is Shannon-optimal for the marginal distribution of its output."

**Problem**: Part (4) says: if $\fhat_3$'s input is non-uniform, its
output is non-uniform. This is trivially true of any deterministic
function. Without further structure (e.g., a specific rate for how the
non-uniformity propagates through $\fhat_3$'s acceptance predicate), this
is a qualitative remark rather than a theorem bullet. It adds no
quantitative content beyond parts (1), (2), and (3).

**Suggestion**: Downgrade part (4) to a remark following the theorem, or
replace with a quantitative version: "If $\fhat_3$'s acceptance predicate
is Shannon-optimal with respect to the uniform-marginal assumption, then
$\delta_3 \geq \delta_3^\ast(I(f_1, f_2))$, i.e., the minimum achievable
$\delta$ for $\fhat_3$ grows with the mutual information of the joint
input."

---

## MINOR: Theorem 4.1 Part (1) entropy identity correct but needs K(x)=1 caveat

**Location**: Section 4.1, Theorem 4.1, Equation (eq:noise-entropy), line 471.

**Status**: The assumption "$K(x) = 1$" is now stated at line 462 to 463, which
addresses the prior 2026-04-09 finding M3. However, the assumption
appears only inside the theorem statement, not in the section
introduction. Readers approaching Section 4.2 (multiplicity) may mix the
two levers implicitly. A single "levers interact additively?" remark at
the end of §4 would close the gap.

---

## MINOR: Proposition 6.1 proof is too terse

**Location**: Section 6.1, Proposition 6.1 (compression estimator), proof
at lines 893 to 899.

**Problem**: The claim "$\hat{H} \geq H/N$ in expectation" requires
identifying $\mathrm{Compress}$ with an actual coding scheme and invoking
source coding, but the proof skips the reduction. In particular, Shannon's
source coding theorem gives $E[|\mathrm{Compress}(\mathbf{c})|] \geq
H(C_1, \ldots, C_N) - O(1)$ only for optimal codes; real compressors
(gzip, zstd) are at least Huffman-like and satisfy $E[\text{length}]
\leq H + 1$ per symbol, not $\geq H$. The direction matters for the
positive-bias claim.

For LZ-based compressors, $(1/N) |\mathrm{Compress}| \to H_\infty$ almost
surely as $N \to \infty$, where $H_\infty$ is the entropy rate of a
stationary source. This is not the same as $H(C_1, \ldots, C_N)/N$ for
general (non-stationary) sequences.

**Suggestion**: Either cite a specific reference for the bias claim (e.g.,
Ziv 1978; Wyner and Ziv 1989) or weaken the proposition to an asymptotic
statement.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 2 | Pinsker applied in wrong direction (Thm 3.1 pt 3); $K(x) \propto 1/D(x)$ is backwards (Thm 4.2) |
| Major | 3 | Fisher info missing distribution-dependent constant (Thm 4.1 pt 3); "preserves all correlations" imprecise (Thm 5.1 pt 2); Thm 5.1 pt 4 trivial |
| Minor | 2 | Noise-theorem K=1 caveat placement; Proposition 6.1 proof terse |

The two Critical findings are both in the headline contributions and
together invalidate the main quantitative claims of Sections 3 and 4. The
theoretical framework (entropy ratio as a measure, $\delta$ as the
handle) is sensible, but the *quantitative bridge* from $\delta$ to $e$
and the *quantitative construction* for reducing $\delta$ are currently
broken. Both are fixable in a revision: Fannes for the bridge, inversion
of the formula for the construction. The compositional leakage theorem
(Thm 5.1) is directionally correct but needs tightening.
