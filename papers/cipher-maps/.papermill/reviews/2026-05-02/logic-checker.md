# Logic Checker, Round 6 (2026-05-02)

Verified each theorem, proposition, and proof against the manuscript at
`/home/spinoza/github/trapdoor-computing/papers/cipher-maps/paper/cipher_maps.tex`.

## Round 5 Critical Logic Findings, Round 6 Status

### CITE-2 (was critical, now resolved)

**R5 issue**: Citation `\cite[Theorem~4.3]{towell2026maxconf}` did not exist
in maxconf (which has only Theorem 4.1).

**R6 verification**: Line 688 now reads `\cite[Theorem~4.1, part~3]{towell2026maxconf}`.
I read maxconf section 4 directly: Theorem 4.1 ("Entropy ratio decomposition")
appears at line 451 with three numbered parts:
- Part (1): perfect uniformity case
- Part (2): K(x)=1 case
- Part (3): the Fannes-Audenaert continuity bound (line 470-477 of maxconf)

The cipher-maps Proposition 5.1 proof sketch references the Fannes-Audenaert
bound, which is exactly part (3) of maxconf Theorem 4.1. **Resolved**.

### CITE-1 (was critical due to reviewer error, now resolved)

**R5 issue (incorrect)**: Reviewer claimed Theorem 7.1 should be 6.1.

**R6 verification**: Line 1699 reads `\cite[Thm.~7.1]{towell2026rekeying}`.
I read rekeying section 7 ("Information-Theoretic Cost") directly: Theorem 7.1
("Rekeying chain confidentiality bound") appears at line 842, stating
$H(X | \mathcal{V}_F) \geq H(X) - \log_2(n+1)$. This matches what
cipher-maps cites at line 1699. The R5 reviewer was wrong; R6 correctly
reverted to 7.1. **Resolved (R5 finding was a false positive)**.

### LOG-1 (was major, now resolved)

**R5 issue**: section 5.2 item 2 said real and filler are "statistically equivocal"
with "joint distribution... identical."

**R6 verification**: Line 722-728 now reads:
> "Real and filler queries are $\delta$-equivocal in distribution
> (Properties 1 and 2 together). Both are observed as $n$-bit cipher
> values, and the cipher value distribution is $\delta$-close to uniform
> by Property 2. Consequently, no statistical test distinguishes real
> from filler with advantage exceeding $\delta$ (Le Cam's two-point
> lemma applied to the cipher value marginals)."

Le Cam's two-point lemma is the correct citation: it states that for
any test distinguishing two distributions $P_0, P_1$ on the same
space, the sum of Type I and Type II error probabilities is at least
$1 - \TV(P_0, P_1)$. Equivalently, the testing advantage is bounded by
$\TV/2 \leq \delta/2$ (or $\delta$ depending on normalization).

**Sub-finding (LOG-1a, minor)**: The statement says "advantage exceeding $\delta$",
but the standard Le Cam bound gives advantage $\leq \TV/2$, not $\TV$. If
$\TV(Q, U) \leq \delta$, then for filler $\sim U$ and real $\sim Q$, advantage
$\leq \delta/2$. The factor of 2 matters in tight bounds. **Either** restate
as "advantage at most $\delta$" (loose, OK) **or** "advantage at most
$\delta/2$" (tight, with explicit normalization comment).

### LOG-2 (was major, now resolved)

**R5 issue**: section 5.2 item 3 used "Pinsker-style arguments", but Pinsker
goes the wrong direction (KL gives TV, not the other way).

**R6 verification**: Line 729-736 now reads:
> "Domain identification is bounded by $\delta$ (Property 2). For any
> binary discrimination question $U$ poses (e.g., 'is this cipher value
> a real domain element or noise?'), $U$'s advantage over random guessing
> is at most $\delta$, by the data-processing inequality applied to
> Property 2's TV bound. Aggregated over $N$ independent observations,
> $U$'s advantage on a recovery game grows no faster than the entropy
> ratio bound of Proposition 5.1 permits."

Data-processing inequality is correct: any post-processing of a
distribution within TV distance $\delta$ remains within TV distance $\delta$
of the corresponding post-processing of the reference. Therefore any
binary test on the post-processed values has advantage at most $\delta$.
**Resolved**.

**Sub-finding (LOG-2a, minor)**: "advantage grows no faster than the entropy
ratio bound permits" is a hand-wave; the actual aggregation rate depends
on independence assumptions and the specific discrimination question.
For independent observations, advantage compounds as $1 - (1-\delta)^N$;
for adversarial query selection, the rate may be worse. The current
phrasing is OK because it says "no faster", which is at least
non-misleading, but a careful reader will want a citation or pointer.

### LOG-3 (was major, now mostly resolved with one remaining issue)

**R5 issue**: Definition of entropy ratio mismatched between cipher-maps and
maxconf.

**R6 verification**: Line 644-660 of cipher-maps now defines
$e(\fhat, \tau) = H(Q)/n$ where $Q$ is the cipher value distribution
and $n$ is the cipher-value-space dimension. This matches the
maxconf §4.2 definition (which I verified by reading maxconf line 462:
$e = H(Q)/H^*$, and in section 4.1 of maxconf, $H^* = n$ for the cipher-value
space because the maximum-entropy reference is uniform on $\B^n$).

**Resolved on the headline definition**. The Proposition 5.1 proof sketch
correctly applies Fannes-Audenaert to $H(Q)$ vs $n$. **Resolved**.

**Remaining issue (LOG-3a, minor)**: section 5.2 item 4 (line 737-741) reads:
> "Function-value leakage is bounded by the entropy ratio. For any
> function $g(f)$ that $U$ wishes to extract, $U$'s expected advantage
> over guessing under $H^*(X)$ is bounded by $1 - e(\fhat, \tau)$."

The notation $H^*(X)$ appears here without definition in cipher-maps.
$H^*$ is defined in maxconf as the maximum entropy over the support;
$H^*(X)$ presumably means $\log_2 |X|$. But:

- The entropy ratio defined at line 649 is $H(Q)/n$, normalized by the
  *cipher value* space dimension $n$.
- The "guessing under $H^*(X)$" claim normalizes against $\log_2|X|$
  (the *latent* space dimension).
- These are not the same.

The bound "$U$'s advantage $\leq 1 - e$" requires a data-processing
argument from $H(Q)$ to $H(X | \text{view})$, which involves both
spaces. The current text glosses this. The maxconf paper handles it
properly via Theorem 4.1; cipher-maps needs either:
(a) a forward reference to maxconf for the latent-vs-cipher
normalization, or
(b) a one-sentence note that "for the encoded latent space, the
advantage bound transports via the data-processing inequality (see
maxconf Theorem 4.1)."

The abstract at line 130 also references $H^*(X)$ without definition,
inheriting the same gap.

**This is a residual logic issue, severity: major.** Specifically, item 4 of
the operational consequences is the most consequential claim
("function-value leakage is bounded"), and its mathematical justification
is currently incomplete.

## Round 5 Major Findings That Carry Forward

### LOG-S1 (R5 minor): Same-secret composition with re-randomization

**Status**: Unaddressed. Definition 7.2 (re-randomization condition) at
line 1352 says "(i) $\fhat$ and $\ghat$ use independent seeds, and
(ii) ...". But Definition 4.4 (Composability, line 505) at line 510-511
specifies "both under the same secret $s$". The composition theorem
under same-secret composition therefore inherits the inequality, not
the equality, from the re-randomization condition.

The text at line 528 ("agreeing exactly under the re-randomization
condition") is misleading: same-secret composition cannot satisfy
condition (i) of re-randomization (which requires *independent* seeds).
Therefore the equality case never applies in single-secret cipher
algebra (the very framework section 4.4 sets up).

**Recommendation**: Either (a) relax Definition 7.2 to allow domain-
separated subkeys derived from the same master secret (which is
genuinely independent under random oracle separation), and clarify
that "same secret" in section 4.4 means "same master secret with
domain-separated derivations", or (b) acknowledge that under same-secret
composition the equality never holds and the theorem is purely an
inequality.

This is the same issue noted as LOG-S1 in R5; it remains open.
Severity: **major**.

### LOG-S2 (R5 minor): Bayesian deniability needs numeric example

**Status**: Unaddressed. Proposition 9.4 at line 1926 gives the
Bayes formula but no numeric instantiation. A reader gets little
intuition. **Recommend** add: "For example, with prior $\pi = 0.1$ and
$\eta = 0.05$, the posterior given observation $y=1$ is $0.68$, giving
adversary advantage $0.58$ over the prior. Tuning $\eta = 0.20$ drops
the posterior to $0.31$, advantage $0.21$." Severity: **minor**.

### LOG-7 (R5 minor): Cancellation note pessimistic vs tight

**Status**: Theorem 7.1 proof at line 1383-1389 now includes the
cancellation note: "$\Pr[A \cup B]$ is pessimistic: it counts every
case in which at least one map errs as a composition error, but
occasional error cancellation occurs when $\fhat$ produces a wrong
intermediate value $y' \neq f(x)$ on which $\ghat$ nonetheless evaluates
to $g(f(x))$. Such cancellations are rare in well-chosen codomains and
we do not attempt to credit them in the bound below."

This addresses the pessimism but the wording "rare in well-chosen
codomains" is a hand-wave. **Recommend** add one quantitative parenthetical:
"(specifically, cancellations require $\fhat$ to err *and* $\ghat$ to
map both $f(x)$ and the actual intermediate $\fhat(\enc(x,k))$ to the
same value; for cipher Boolean codomains with Shannon-optimal partition
this occurs with probability roughly $\eta_g \cdot p_{f(x)}$)."
Severity: **minor**.

## New Findings Introduced by R6 Restructure

### LOG-N1 (new, major): Definition vs. inline math at section 5.1

The user's prompt described "Definition 5.1" defining the entropy ratio.
But in the manuscript at line 644-660, the entropy ratio is introduced
in flowing prose with inline math `\[ e(\fhat, \tau) = H(Q)/n \]`,
**not** as a numbered \begin{definition} environment. There is no
"Definition 5.1" in the manuscript.

This is a small but consequential issue:
- The Operational Consequences section refers to "the entropy ratio"
  as if it were a defined object, but cannot reference a definition
  number.
- Proposition 5.1 (line 668) refers to "the entropy ratio of $U$'s
  view satisfies..." without an explicit definition pointer.
- A reviewer asking "where is the entropy ratio formally defined in
  this paper?" gets an inline equation in a paragraph, which is weaker
  than a Definition environment.

**Recommendation**: Wrap line 644-660 in a `\begin{definition}[Entropy
ratio]\label{def:entropy-ratio}...\end{definition}` and reference
`Definition~\ref{def:entropy-ratio}` from Proposition 5.1 and from
each Operational Consequences item that uses $e$. Severity: **major**.

This was not a Round 5 finding because R5 expected the user to add
the definition properly; the user's R6 fix narrative says
"Definition 5.1 now defines `e = H(Q)/n`" but the manuscript only has
prose, not a Definition environment.

### LOG-N2 (new, major): Section 5.2 item 4 references undefined H*(X)

Already covered as LOG-3a above. Re-iterate: section 5.2 line 739 uses
$H^*(X)$ which is defined in maxconf, not in cipher-maps. This is the
same problem as the entropy ratio definition. Severity: **major**
(combined with LOG-3a, this is one finding split across two
locations, but both manifest as undefined notation).

### LOG-N3 (new, minor): "no statistical test distinguishes...with advantage exceeding $\delta$"

Le Cam normalization issue, already covered as LOG-1a above.

### LOG-N4 (new, minor): The cipher value space "dimension" $n$

Definition 4.1 (Cipher map) at line 343 defines $\fhat: \{0,1\}^n \to
\{0,1\}^n$, calling $n$ the cipher value width. But §5.1 line 651-653
calls $n$ "the cipher value space dimension." These are the same
quantity in the binary case, but "dimension" is not a standard term
for binary string length. **Recommend** standardize on "cipher value
width" or "bit-string length." Severity: **suggestion**.

## Other Logic Findings (Standalone, R6)

### LOG-N5 (new, major): Theorem 6.2 Step 2 attribution under Shannon-optimal

The Theorem 6.2 proof at line 1041-1072 says:
- Step 2: per-element bit cost via the acceptance predicate.
- "$h(\ell) \oplus h(x_i) \in A(y_i)$ ... under the random oracle model
  this occurs with probability $\alpha(y_i)$, so the information cost of
  pinning down a single element's acceptance is $-\log_2 \alpha(y_i)$ bits."

The "information cost of pinning down a single element's acceptance" is
loose. What's actually being measured is the *amount of seed search work*
per element, which is $\log_2(1/\alpha(y_i))$ trials in expectation (one
per pass-event under independence). This is a *time* cost, not directly a
*space* cost.

The transition from per-element acceptance probability to per-element
bit cost goes through the seed-table size: each element's "needed seed"
is one of $1/\alpha(y_i)$ alternatives, so storing the choice of seed
requires $\log_2(1/\alpha(y_i))$ bits. Step 3 calls this "information
content per element" which is consistent. But Step 2 conflates two
different "$\log_2(1/\alpha)$" interpretations (search work vs. storage),
which is what previous review rounds flagged.

**Recommendation**: tighten Step 2 by replacing "the information cost of
pinning down a single element's acceptance is $-\log_2 \alpha(y_i)$ bits"
with "the seed table must record $\log_2(1/\alpha(y_i))$ bits per element
to identify which of the $1/\alpha(y_i)$ candidate seeds achieves the
acceptance constraint." Severity: **major** (this is the same MAJ-1 from
Round 4 / pre-R5 reviews; not fully resolved, just rephrased).

### LOG-N6 (new, minor): Stirling drop in Theorem 6.1

Line 817: $\log_2 \binom{|U|}{n} = n \log_2(|U|/n) + n \log_2 e + O(\log n)$.

The $n \log_2 e$ term is dropped from "leading order." It is in fact
$1.443n$ bits, not negligible compared to the leading term $n \log_2(|U|/n)$
when $|U|/n$ is small (e.g., $|U|/n = 100$ gives $n \log_2 100 = 6.64n$
leading + $1.44n$ next-order = a 22% relative error if dropped).

**Recommendation**: add a parenthetical "(the $n \log_2 e$ term contributes
roughly $1.44n$ bits per element and becomes relatively smaller as
$|U|/n$ grows; we drop it in the standard leading-order convention)."
Severity: **minor** (LOG-4 from R5, still unaddressed).

### LOG-N7 (new, minor): $\delta \leq 1/2$ condition missing on Proposition 5.1

The Fannes-Audenaert continuity inequality applies for $\TV \leq 1/2$.
For $\TV > 1/2$ the inequality flips direction (the entropy difference
is bounded by $1$ rather than $h_2(\TV)$). Proposition 5.1 should
explicitly state $\delta \leq 1/2$.

The maxconf paper at line 492 has the condition: "for any distributions
$P, Q$ on a support of size $d$ with $\TV(P, Q) \leq t \leq 1/2$".
Cipher-maps Proposition 5.1 inherits this implicitly via the citation,
but does not state it. Severity: **minor** (LOG-5 from R5, unaddressed).

### LOG-N8 (new, minor): Theorem 6.2 Step 2 independence note

Step 2 of Theorem 6.2 derives the per-element cost using independence
of acceptance events under the random oracle, but doesn't explicitly
state that the per-element costs are independent. For the
sum-over-elements claim in Step 3 to hold, one needs the independence
to lift to additivity, which is true under ROM. **Recommend** add:
"(by independence of $h(x_i \| s_j)$ across distinct $x_i$ in the
random oracle model)." Severity: **minor** (LOG-6 from R5, unaddressed).

## Summary

- 1 new MAJOR (LOG-N1: Definition environment missing for entropy ratio).
- 1 new MAJOR (LOG-N5: Theorem 6.2 Step 2 still loose attribution of
  "$-\log_2 \alpha$" to bit cost).
- 1 carried-over MAJOR (LOG-3a / LOG-N2: undefined $H^*(X)$ in section 5.2 item 4).
- 1 carried-over MAJOR (LOG-S1: composability/re-randomization mismatch
  on same-secret composition).
- 5 carried-over MINOR (LOG-1a, LOG-2a, LOG-7 elaboration, LOG-N6, LOG-N7, LOG-N8).
- 0 critical (R5 critical CITE-1 and CITE-2 both resolved; METH-1 §10
  promotion is in methodology-auditor's domain).

Net: R6 closed all 3 critical R5 findings on logic. Three majors persist
or were introduced by R6 (1 new structural, 2 carry-over). Logic is
substantially better than R5 but not yet clean.
