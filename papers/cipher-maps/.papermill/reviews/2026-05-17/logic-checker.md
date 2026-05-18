# Logic Checker Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Single-orchestrator pass focused on the Round 7 deltas: Theorem 8.1
(coincidence-oracle accuracy), Proposition 8.2 (randomized-encoding
defense, two threat models), Corollary 8.x (t-dependent allocation),
Definition 8.x (pattern-coincidence and decode-coincidence attackers),
Remark on member coincidence under Huffman, and consistency of these
with the abstract, intro, and §10.6 empirical claims.

## CRITICAL FINDINGS

### CRIT-1: Direction of the t-dependent allocation recommendation is inverted

**Location**: Abstract line 80-83, Corollary 8.x at lines 1846-1858,
prose at lines 1860-1876, §10.6 paragraph "Multi-instance leakage and
the coincidence oracle" at lines 2555-2573, Summary item (iv) at
lines 2640-2643.

**Quoted text (abstract)**:
> "a coincidence-oracle bound (accuracy $1 - \tfrac{1}{2} \sum_y
> \alpha(y)^t$ for $t$ shared-$f$ instances under independent seeds)
> characterizes multi-instance leakage and inverts the single-instance
> Shannon recommendation at $t \geq 2$."

**Quoted text (Corollary 8.x)**:
> "$t \geq 2$ shared-$f$ optimum: $\alpha(y) = \varepsilon/|Y|$
> (uniform allocation) minimizes coincidence-oracle leakage by
> equalizing the geometric tail of the non-member distribution."

**Quoted text (§10.6)**:
> "At $t = 5$, the uniform Dense partition achieves accuracy
> $\approx 0.9999$ while the Shannon-optimal Huffman partition achieves
> $\approx 0.984$; the uniform allocation defends $\approx 16\times$
> better at large $t$ in this configuration."

**Problem**: The formula and empirical numbers are correct, but the
direction of the conclusion is inverted. The coincidence-oracle
accuracy is the attacker's classification accuracy. Higher accuracy
means the attacker correctly distinguishes member from non-member more
often, which is worse for the defender, not better. The text reads
the inequality backwards.

Concretely, from Theorem 8.1:
$$\text{accuracy}(t) = 1 - \tfrac{1}{2} \sum_y \alpha(y)^t.$$

Subject to $\sum_y \alpha(y) = \varepsilon$ fixed, by Jensen, convexity
of $x^t$ for $t \geq 1$:

- Uniform allocation $\alpha(y) = \varepsilon/|Y|$ MINIMIZES
  $\sum_y \alpha(y)^t$, which MAXIMIZES the attacker's accuracy.
- Skewed Huffman allocation MAXIMIZES $\sum_y \alpha(y)^t$ (or at
  least keeps it larger), which MINIMIZES the attacker's accuracy.

So Huffman gives the defender BETTER protection at every $t$, not
worse. The empirical numbers confirm this: at $t = 5$, the
attacker's accuracy is 0.9999 under uniform vs 0.984 under Huffman,
so uniform allows the attacker to be MORE successful (0.0001 error
rate vs 0.016 error rate). Huffman has roughly $160\times$ higher
attacker error rate, i.e. is roughly $160\times$ stronger defense
in this configuration (the paper's stated $16\times$ figure is also
off, by an order of magnitude, comparing the wrong direction).

There is therefore NO INVERSION of the single-instance recommendation:
Huffman is the optimum at $t = 1$ (smallest TV at the single-instance
level) AND at $t \geq 2$ (smallest coincidence-oracle accuracy). The
v3 thesis claim that the optimum "inverts" is structurally wrong.

**Cross-check against the source experiment**: `bernoulli/src/bernoulli/
experiments/RESULTS_14.md` reports the same inverted conclusion at
its "Defense implications" section (line 117): "the codec with the
SMALLEST $\max_v q_v$ defends best at large $t$", and "At $t=1$,
prefer Huffman; at large $t$, prefer Dense." The cipher-maps paper
inherits the bernoulli writeup's misreading. The numerical values in
the experiment match the formula, but the interpretation reverses the
defender-vs-attacker direction.

**Asymptotic sanity check**: As $t \to \infty$, for any allocation
with finite $\max_y \alpha(y) < 1$, $\sum_y \alpha(y)^t \to 0$ and the
attacker's accuracy tends to $1$. Codecs with smaller $\max_y \alpha(y)$
reach this saturation FASTER (worse for defender). Codecs with larger
$\max_y \alpha(y)$ retain residual cover longer because at least one
value continues to coincidentally agree across instances with
non-negligible probability. Huffman with $\alpha_1 \approx 0.5$ on the
dominant value provides a "free decoy lane" of about $0.5^t$
probability for fillers to all land in $y_1$ and look like members.
Uniform with $\alpha = 1/|Y|$ provides only $|Y|^{1-t}$ such cover,
which collapses much faster.

**Cross-verification**: The numerical equality between the formula's
prediction and the empirical sweep at 24/25 cells is genuine evidence
that the formula and experiment agree; the issue is one of
interpretation, not arithmetic. The empirical attacker accuracies
support the corrected reading (Huffman is better defense), not the
inverted reading the paper currently states.

**Suggestion**: Pick one of two paths.

Path A (preserve the formula, fix the interpretation): rewrite the
abstract to say something like "the coincidence-oracle bound shows
that single-instance Shannon-optimal codecs remain Pareto-relevant
at $t \geq 2$, and that the defense slows attacker accuracy growth at
rate $\max_y \alpha(y)$ rather than $\varepsilon/|Y|$, contrary to
the intuition that uniform allocation always defends best."
Rewrite Corollary 8.x to say "$t \geq 2$ optimum: $\alpha(y)$ that
maximizes $\max_y \alpha(y)$ subject to $\sum_y \alpha(y) =
\varepsilon$ defends best, because the dominant value provides a
high-probability decoy lane for fillers to coincide on." Rewrite the
§10.6 paragraph and Summary item (iv) the same way. The thesis loses
the "inversion" framing but recovers a true (and arguably more
interesting) finding: Huffman wins at every $t$ because it provides
both single-instance frequency hiding and multi-instance
coincidence cover.

Path B (preserve the inversion intuition, redefine the attacker):
introduce a different attacker model that genuinely does invert. One
candidate: the "distinguish-which-value" attacker that observes the
common coincidence value and tries to recover $f(x)$, not just
membership. Under uniform $\alpha$, the common value is uniformly
distributed in $Y$ on fillers, providing no information beyond the
coincidence event. Under Huffman, the common value distribution
reveals more about whether the input is a member of a frequent or
rare value class. This is a different attacker than the coincidence
oracle and would need fresh formal analysis.

Either path requires substantive revision of the v3 thesis. The
"inversion" framing is the new headline contribution for Round 7, so
this is not a small fix.

**Cross-verified**: Yes, against bernoulli experiment file
`RESULTS_14.md`, the Python source `14_coincidence_oracle.py` (verified
the accuracy formula is classification accuracy, computed as
correct/n_total), and the theorem proof itself (which correctly
derives accuracy = $1 - \tfrac{1}{2} \sum_y \alpha(y)^t$). The
formula and empirical numbers are correct, the interpretation is
inverted.

## MAJOR FINDINGS

### MAJ-1: Theorem 8.1 prose definition uses a single c, proof uses tuple

**Location**: Lines 1738-1740 (verbal definition of coincidence
oracle) and lines 1770-1798 (proof).

**Quoted text (verbal definition)**:
> "the \emph{coincidence oracle}, predicts ``in-domain'' iff
> $\dec_1(\fhat_1(c)) = \cdots = \dec_t(\fhat_t(c))$ and the common
> decoded value is not~$\bot$."

**Quoted text (proof, member case)**:
> "the trusted side publishes one cipher value per instance, $c_i =
> \enc_i(x, 0)$"

**Problem**: The verbal definition writes a single $c$ across all $t$
cipher maps, suggesting the attacker observes one cipher value being
fed to multiple instances. The proof switches to a tuple $(c_1, \ldots,
c_t)$ where each $c_i$ comes from instance $i$'s own encoder
$\enc_i(x, 0)$. These are different attack models. The proof's
version is the correct one (each instance has its own encoder, so
the same plaintext $x$ produces different cipher values $c_i$ at
each instance), but the verbal definition obscures this.

**Suggestion**: Rewrite the verbal definition at line 1738-1740 to:
> "the coincidence oracle, given a probe $\mathbf{c} = (c_1, \ldots,
> c_t)$ where the trusted side has constructed $c_i = \enc_i(x, 0)$
> for a candidate input $x$, predicts ``in-domain'' iff
> $\dec_1(\fhat_1(c_1)) = \cdots = \dec_t(\fhat_t(c_t))$ and the
> common decoded value is not $\bot$."

This matches the proof setup and the Definition 8.x (pattern- and
decode-coincidence attackers) at lines 1893-1911, which already uses
this tuple-probe formulation.

### MAJ-2: Proposition 8.2 member-case proof needs bijectivity, not just saturation

**Location**: Lines 1918-1926 (statement) and lines 1950-1961 (proof).

**Quoted text (statement)**:
> "assume the construction \emph{saturates} each acceptance region:
> every bit string in $A_i(y)$ is reachable as $\fhat_i(c)$ for some
> member cipher value $c$ encoding a value-$y$ plaintext"

**Quoted text (proof)**:
> "the specific pattern $\fhat_i(c_i) \in A_i(y)$ chosen by instance
> $i$ is uniformly distributed on the $|A_i(y)|$ patterns and
> statistically independent across instances."

**Problem**: Saturation as stated only ensures every pattern in
$A_i(y)$ is REACHABLE. It does not ensure the distribution induced by
uniform $k_i \sim \mathrm{Unif}(\{0, \ldots, K(x){-}1\})$ is uniform on
$A_i(y)$. For the proof to go through, we need either:

(a) The map $k \mapsto \fhat_i(\enc_i(x, k))$ is a bijection from
$\{0, \ldots, K(x){-}1\}$ to $A_i(y)$ when $f(x) = y$, with $K(x) =
|A_i(y)|$. This makes the distribution uniform on $A_i(y)$.

(b) Some weaker condition, plus an additional symmetry argument
involving the random oracle.

The current proof asserts uniformity from saturation alone, which is
not implied. The Huffman example at line 1923-1924 ($K(x) = 2^{n -
\ell_{f(x)}} = |A_i(f(x))|$) makes the bijection case the natural one,
but this needs to be stated as the assumption.

**Suggestion**: Replace the saturation assumption with the explicit
bijectivity assumption:
> "assume the construction is \emph{uniform-saturating}: the map
> $k \mapsto \fhat_i(\enc_i(x, k))$ is a bijection from $\{0, \ldots,
> K(x){-}1\}$ to $A_i(y)$ when $f(x) = y$ (which requires $K(x) =
> |A_i(y)|$). This holds, e.g., for Huffman codespace classes where
> $K(x) = 2^{n - \ell_{f(x)}}$."

The proof then follows because uniform $k$ plus bijection gives
uniform pattern.

### MAJ-3: Proposition 8.2 member coincidence formula is wrong under heterogeneous $A_i(y)$

**Location**: Line 1929-1932.

**Quoted text**:
> "$\Pr[\text{predict in} \mid \text{member, } f(x) = y]
> = \prod_{i=2}^{t} \frac{1}{|A_i(y)|}$"

**Problem**: This formula is correct only when all $A_i(y)$ are
identical (homogeneous instances). For heterogeneous $A_i(y)$:

Let $P_i$ be the pattern from instance $i$, uniform on $A_i(y)$,
independent across $i$. We want $\Pr[P_1 = P_2 = \cdots = P_t]$. By
conditioning on $P_1$:

$$\Pr[\text{all equal}] = \sum_{p \in A_1(y)} \frac{1}{|A_1(y)|}
  \prod_{i=2}^{t} \mathbf{1}[p \in A_i(y)] \cdot \frac{1}{|A_i(y)|}
  = \frac{|\bigcap_{i=1}^{t} A_i(y)|}{\prod_{i=1}^{t} |A_i(y)|}.$$

When all $A_i(y)$ coincide, $|\bigcap A_i(y)| = |A(y)|$ and the
formula collapses to $|A(y)|/|A(y)|^t = 1/|A(y)|^{t-1}$, which is
the homogeneous result. For heterogeneous $A_i(y)$, the formula in
the proposition is wrong (it gives $1/\prod_{i=2}^t |A_i(y)|$ rather
than $|\bigcap A_i(y)| / \prod_{i=1}^t |A_i(y)|$).

Under independent seeds, however, the per-instance random oracle
implies that the relabeled acceptance regions are random subsets of
$\B^n$, so the "natural" interpretation is that $A_i(y)$ refers to
the same acceptance set in the structural (codec-level) sense and
the seed only affects which bit strings map into it. In that case,
$A_i(y)$ does coincide across instances at the codec-level, and the
formula is fine.

**Suggestion**: Clarify that $A_i(y)$ refers to the codec-level
acceptance region (defined by the acceptance predicate), which is the
same across all instances sharing the codec, and that the
per-instance variation is only in WHICH bit strings the cipher map
sends into it. Add a one-line "Under homogeneous instances (shared
codec across instances), $A_i(y) = A(y)$ and the formula reduces to
$1/|A(y)|^{t-1}$." Or restrict the proposition statement to
homogeneous instances explicitly, matching the way Theorem 8.1's
homogeneous corollary is stated.

### MAJ-4: Saturation example for Huffman is potentially imprecise

**Location**: Line 1923-1924.

**Quoted text**:
> "(this holds, e.g., for Huffman codespace classes where $K(x)$
> equals the codespace class size $2^{n - \ell_{f(x)}}$)."

**Problem**: For prefix-free Huffman with codeword length $\ell_v$,
the acceptance set $A(v) = \{c \in \B^n : c \text{ starts with}
\mathrm{code}(v)\}$ has size $|A(v)| = 2^{n - \ell_v}$. To get
uniform sampling of $A(v)$ via $k \in \{0, \ldots, K(x)-1\}$, the
multiplicity $K(x)$ must equal $|A(v)| = 2^{n - \ell_{f(x)}}$ AND
each $k$ must produce a distinct pattern in $A(v)$. The latter
requires the encoder to map distinct $k$ values to distinct
multiplicity-encoded inputs that the hash function distributes
across $A(v)$. The Huffman example glosses over the encoder-side
mechanism.

In practice, the natural construction would be: $\enc(x, k)$ produces
a unique probe per $k$, and the seed-search algorithm guarantees
that the $K(x)$ probes for input $x$ land in $A(f(x))$, but without
ensuring they are distinct or cover all of $A(f(x))$. The bijection
condition would need to be enforced by an additional construction
step.

**Suggestion**: Add a short construction note showing how the encoder
achieves the bijection in the Huffman case (e.g., by indexing into
the codespace class directly, or by an additional injectivity
constraint in the seed search). Without this, the saturation
assumption is plausible but not justified by the cited construction.

### MAJ-5: Sister-paper preprints still pending (carry-over from R6 MAJ-6)

**Location**: References.bib lines 49, 194, 201, 208.

**Quoted text**: Four entries with `note={Manuscript in preparation}`:
`bernoulli-types`, `towell2026algebraic`, `towell2026maxconf`,
`towell2026rekeying`.

**Problem**: Two of these are load-bearing for cipher-maps results:

- `towell2026maxconf` is the formal-framework backing for the entropy
  ratio bound (Proposition 5.1, cited at line 759 as "[Theorem 4.1,
  part 3]").
- `towell2026rekeying` provides the chain bound for bounded composition
  (cited at line 2116 as "[Thm. 7.1]").

Both R5 (CITE-1/CITE-2) and R6 (MAJ-6) flagged this. Without
preprint DOIs, the citation chains are unverifiable to external
reviewers. PoPETs reviewers will not accept "Manuscript in
preparation" for load-bearing technical claims.

**Suggestion**: Post arXiv preprints for `towell2026maxconf` and
`towell2026rekeying` before submission. Update bib entries with
arXiv IDs. Optional: post `towell2026algebraic` and `bernoulli-types`
as well for completeness, though they are less critical for
cipher-maps survival.

### MAJ-6: Article class still in use, not PoPETs template (carry-over)

**Location**: Line 1 of cipher_maps.tex.

**Quoted text**: `\documentclass[11pt]{article}`

**Problem**: PoPETs has its own LaTeX template. The current
`article`-class build produces 36 pages, well over the PoPETs page
target. Porting to the template typically reduces page count by 30%
to 40%, bringing the paper closer to PoPETs limits.

**Suggestion**: Port to the PoPETs template as part of the
pre-submission pass. Mechanical work, but it surfaces overfull boxes
and forces a re-pass on figure sizing.

## MINOR FINDINGS

### MIN-1: Theorem 8.1 "members" case implicitly uses K(x) = 1

The statement is for "canonical encoding ($K(x) = 1$)", but the proof
writes $\enc_i(x, 0)$ explicitly, which is the natural notation. Fine,
but a one-line note that the proof choice corresponds to the canonical
convention $K(x) = 1$ would tighten the link.

### MIN-2: Remark on general prior π says "at any π ≥ 1/2", crossover analysis is correct

The remark correctly identifies the crossover at $(1-\pi) \sum_y
\prod_i \alpha_i(y) = \pi$, and notes the coincidence-oracle rule
wins for $\pi \geq 1/2$. Verified by direct calculation.

### MIN-3: §10.6 Le Cam tightness table reports "best attacker" but tie across all three classes is not stated explicitly in the table

The paragraph text says "All three attackers achieve the same accuracy
to within 0.014 sampling noise" but the table only reports "Best
attacker". A column for each attacker class (Bayes, logistic, 1-NN)
would make the tie visible without forcing the reader back to the
prose. Low priority.

### MIN-4: §10.6 (TV, L) Pareto frontier analysis cites 14 configurations but does not list them

"Across 14 configurations covering $|Y| \in \{4, 6, 8\}$, $n \in \{4,
6\}$, and four $p_y$ shapes (uniform, Zipf, two-mode, heavy-tail), we
find:". Reproducibility would benefit from a supplementary table
enumerating the configurations and per-configuration TV gaps. Low
priority.

### MIN-5: §6.4 "noise floor" derivation in §10.3 is plausible but not fully justified

The formula
$\Pr[\text{FP}_{k\text{-AND}}] \lesssim p_T^k + k \cdot p_N \cdot
p_T \cdot (1-p_N)^{k-1}$ is presented with the noise term dominating
at $k \geq 2$. The derivation is plausible (each term has a noise
input with probability $k p_N (1-p_N)^{k-1}$, and the AND result
matches True with rate $p_T$), but the formal calculation is
deferred to `towell2026algebraic`. For a load-bearing empirical
claim, the derivation should be self-contained, or at least sketched
in a footnote.

### MIN-6: Pareto frontier mechanism explanation could be clearer

"Mechanism: Huffman saturates Kraft, dumping all surplus codespace
onto the heavy mode; TV-min leaves Kraft slack and pushes long
codewords onto the tail to better match $p_y$." This is correct but
dense. Three sentences would be clearer than one. Low priority.

### MIN-7: Remark on member coincidence under Huffman is good, the t = 2 collapse argument deserves a sentence

The remark is technically correct (the t=2 case reduces to $|Y|/2^n$
under $2^{\ell_v} \approx 1/p_f(v)$), but readers will want one
extra line on what "approximately" means quantitatively. For Huffman
this is exact when codeword lengths exactly equal $-\log_2 p_f(v)$
(dyadic case) and approximate otherwise.

## SUGGESTIONS

### SUG-1: Add a "Threat-model summary" table

§5 (single-instance trust model), §8.3 (multi-instance attackers, two
flavors), and §9.6 (value-side vs key-side) introduce three different
threat models. A short table summarizing what each one assumes about
the adversary (codec public/private, single/multi-instance, key
universe structured/random) would help readers track the regime each
result applies in.

### SUG-2: Add a "Reproducibility appendix"

The empirical claims are now load-bearing. A short appendix with
seed values, package versions, and command-line invocations would
strengthen reproducibility beyond the "single command reproduces the
table" mention. Optional, but PoPETs increasingly expects this.

### SUG-3: After fixing CRIT-1, consider whether the (TV, L) Pareto frontier finding becomes the headline

If the multi-instance "inversion" claim is dropped or revised, the
strongest empirical finding becomes the (TV, L) Pareto frontier and
the 42× TV reduction at 17% length overhead on heavy-tailed
distributions. This is a clean, single-instance result with no
direction-of-inequality risk, and it has a clear deployment
implication (use TV-min, not Huffman, when value distribution is
heavy-tailed). The thesis could be reframed around this without
needing the multi-instance story at all.

## Summary

- Critical: 1 (CRIT-1 direction of t-dependent recommendation is inverted)
- Major: 6 (MAJ-1 to MAJ-6 above)
- Minor: 7
- Suggestions: 3
