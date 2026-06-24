# Logic Checker Report, Round 8 (2026-05-27)

This round focuses on direction-of-inequality and
direction-of-prescription consistency, beyond the standard proof-by-proof
verification. The user has caught three direction errors over the
revision cycle (composition = vs <=, coincidence-oracle defender
direction, Simmons K(x) prescription); the logic checker should look
for additional instances of the same failure mode.

## Verification summary

| Theorem / Proposition / Corollary | Result | Notes |
|---|---|---|
| Theorem 3.1 (Lower bound) | PASS | Argument tight; Stirling subleading dropped honestly |
| Theorem 5.1 (Composition correctness) | PASS | Inequality form consistent with abstract; equality under re-randomization |
| Proposition 5.1 (Confidentiality bound) | PASS WITH CAVEAT | See LOG-MAJ-1 below: support-of-Q gap |
| Theorem 6.1 (Lower bound, restated) | PASS | Identical to 3.1, no double-counting |
| Theorem 6.2 (Space optimality) | PASS | R6 Step 2 separation landed cleanly |
| Proposition 6.1 (Construction time) | PASS | Standard Poisson binomial argument |
| Proposition 6.2 (Bucketed construction) | PASS | Geometric mean handling correct |
| Proposition 6.3 (Entropy cipher map space) | PASS | Restates 6.2 instantiated to prefix-free code |
| Proposition 7.1 (AND gate correctness) | PASS | Four-case table verified |
| Theorem 7.1 (General composition) | PASS | Re-randomization condition correctly stated |
| Corollary 7.1 (Chain composition) | PASS | Inductive form clean |
| Proposition 8.1 (Granularity and privacy) | PASS | Bijection argument correct |
| Theorem 8.1 (Coincidence-oracle accuracy) | PASS | Formula and proof correct; R7 CRIT-1 interpretation fixed |
| Corollary 8.1 (cor:t-geometry) | PASS | Direction reading correct: uniform=worst, concentrated=best |
| Proposition 8.2 (Randomized-encoding defense) | PASS | Saturation assumption stated explicitly |
| Proposition 10.1 (Bayesian deniability) | PASS | Standard Bayes calculation |

## R7 CRIT-1 closure verification

The user retracted the v3 "inversion at t >= 2" claim in commit 3b77c04.
Verified all five flagged sites:

- **Abstract lines 82 to 85**: now reads "Both single-instance and
  multi-instance optima favor concentrated (Huffman-style) partitions;
  when multi-instance leakage exceeds deployment tolerance, the
  appropriate defense is randomized encoding (K(x) > 1) rather than
  codec retuning." Direction correct.

- **Corollary 8.1 (lines 1865 to 1875)**: cor:t-geometry says uniform
  maximizes attacker accuracy (worst defense), concentrating minimizes
  (best defense). "Huffman-style partitions are therefore preferred at
  every t >= 1; there is no codec-choice regime change between t = 1
  and t >= 2." Direction correct.

- **Numerical example (lines 1877 to 1890)**: re-checked arithmetic.
  At |Y| = 8, t = 5, Huffman with max alpha = 0.5 gives
  Sum alpha^5 ~= 0.5^5 + smaller terms = 0.031, attacker accuracy
  1 - 0.031/2 = 0.984. Uniform gives Sum alpha^5 = 8 * (1/8)^5 = 2^-12 =
  2.44e-4, accuracy ~= 1 - 1.2e-4 = 0.9999. Huffman error rate / Uniform
  error rate = 0.016 / 1.2e-4 ~= 133. Matches paper's "132x".

- **Section 10.6 paragraph (lines 2655 to 2664)**: "Huffman therefore
  defends 132x better than uniform" with correct direction reading.

- **Summary item (iv) (lines 2772 to 2778)**: "the Shannon-optimal
  partition is preferred at every t with no codec-choice regime change,
  and randomized encoding provides a free single-instance defense."
  Direction correct.

R7 CRIT-1 is closed.

## K(x) prescription direction verification (today's commit 41210a8)

User reported four sites flagged in pre-commit context (lines 316, 451,
510, 631 in their numbering). Cross-checked against current line
numbering in cipher_maps.tex:

| Stated location | Current line | Text | Verdict |
|---|---|---|---|
| Related Work homophonic paragraph | 323 | "K(x) proportional to D(x) assigns more representations to frequent values" | CORRECT |
| Layer 3 description (section 3.4) | 457 | "Assigning K(x) proportional to D(x) equalizes frequencies" | CORRECT |
| Definition 4.2 post-prose | 521 | "K(x) proportional to D(x) encodings per value (the classical Simmons homophonic prescription)" | CORRECT |
| Table 4.1 (parameter table) | 644 | "Set to proportional to D(x)" | CORRECT |

All four sites consistent. Operational reading at lines 523 to 525:
"frequent values get more representations, so the per-representation
query frequency D(x)/K(x) is constant across x, and Q is flat across
cipher values." Correct: D(x)/K(x) = constant means each cipher value
representation appears at equal expected query frequency. This is the
classical Simmons direction.

The new Related Work paragraph (lines 314 to 327) cleanly introduces
D(x) and K(x) with forward references to section 3 (Definition 3.1
cipher map) and section 4.2 (Definition 4.2 representation
uniformity). Reads coherently.

The Definition 4.2 rewrite at lines 500 to 516 now defines D
explicitly as "the prior probability distribution from which the
trusted machine draws latent values for encoding (the query
distribution)", consistent with the Related Work paragraph's "the
prior probability that the trusted machine encodes latent value x".
Two phrasings, same object. No drift.

## Findings

### Critical

None. The R7 critical is closed and the K(x) direction is now
consistent.

### Major

**LOG-MAJ-1 (Definition 4.2 Q distribution support mismatch).**
Location: lines 498 to 525.

The formula Q(c) = sum_x D(x) * |{k : enc(x,k) = c}| / K(x) defines
a distribution Q on {0,1}^n. For c not in Im(enc), Q(c) = 0. The mass
of Q is concentrated on Im(enc), which has at most sum_x K(x)
representations, typically much less than 2^n in any practical
deployment.

The next equation states TV(Q, Uniform({0,1}^n)) <= delta. But the TV
distance between a distribution supported on a small set and the
uniform distribution on {0,1}^n is large (1 - |support| * 2^-n in the
worst case). For small |support| this is essentially 1, and Property 2
becomes vacuous as written.

The resolution in the paper appears to be implicit: the cipher value
stream actually observed by U includes filler queries (Definition 5.1
item 3: "Inject noise: generate random c from {0,1}^n as filler
queries"). With sufficient filler dilution, Q over the union of real
plus filler becomes approximately uniform on {0,1}^n. But the formula
at line 509 only covers the real-query column, not the dilated
stream.

Three resolution paths:

1. Redefine Q to be the empirical distribution of cipher values
   actually sent to U (real plus filler), with filler ratio r as an
   additional parameter. Then for r large, Q is approximately uniform
   and the TV bound is meaningful.

2. Restrict Property 2 to be a statement about Q restricted to
   Im(enc), using TV(Q | Im(enc), Uniform(Im(enc))) <= delta. This is
   the meaningful per-representation uniformity claim.

3. Strengthen the construction to be a perfect-hash-style total
   covering of {0,1}^n by Im(enc), with sum_x K(x) = 2^n. This is the
   ideal Bernoulli-axiom regime but rarely achievable in practice.

Cross-reference: Proposition 5.1 (line 752) refers to Q as "the cipher
value distribution induced by enc on the B^n ambient space" and
applies Fannes-Audenaert with reference Uniform(B^n). The Fannes
inequality H(Q) >= n(1 - delta) - h_2(delta) only gives a meaningful
lower bound when delta is small relative to 1. For delta close to 1,
H(Q) >= negative, which is trivially true (H >= 0 anyway). So
Proposition 5.1 is technically correct but vacuous unless delta is
genuinely small, which requires resolving the support-of-Q issue.

This is not a new finding (R5 LOG-3 identified the H* / H(Q)/n
normalization mismatch, R6 unified the definition). But the support
issue is upstream of the normalization and was not separately
addressed. Recommendation: add a short paragraph after Definition 4.2
or in Remark 4.x clarifying that delta is well-defined only when the
encoding image fills B^n densely (or with filler), or restate the
definition along path 2.

Suggestion: insert a remark after Definition 4.2:

> Remark (Support of Q). The distribution Q is supported on the image
> of enc, which is the set of bit strings actually used as cipher
> representations. For Q to be TV-close to Uniform({0,1}^n), the
> deployment must either populate B^n densely with sum_x K(x) close to
> 2^n, or dilute the cipher value stream with random filler from B^n
> (Definition 5.1, item 3). The Le Cam bound at section 5.2 item 2 is
> consistent with the latter convention: real and filler queries are
> indistinguishable to U because both are observed as bit strings from
> the same distribution on B^n.

This is the direction-of-prescription pattern the user flagged: the
formula says one thing (Q on B^n) but the prose interpretation reads
another (Q on Im(enc) with filler dilution).

**LOG-MAJ-2 (abstract phrasing: 42x TV reduction direction).**
Location: lines 75 to 77.

Abstract says: "the Shannon-optimal corner (L = -log_2 epsilon + H(Y),
matching the information-theoretic lower bound) and the TV-optimal
corner are distinct under integer codeword constraints, with the gap
reaching 42x in TV at 17% length overhead on heavy-tailed value
distributions."

Read literally: the gap is between L-optimal and TV-optimal. TV-min is
0.0094 (TV-optimal); L-min is Huffman with TV = 0.40. Ratio
0.40 / 0.0094 = 42.55. Length: TV-min L vs Huffman L; the "17% length
overhead" implies TV-min is 17% longer than Huffman.

But the same abstract three sentences later says "Both single-instance
and multi-instance optima favor concentrated (Huffman-style)
partitions." This creates a tension: the abstract recommends
Huffman-style partitions, but also reports a 42x TV reduction
available off Huffman (i.e., by NOT using Huffman). A careful reader
will ask "if Huffman is the recommended single-instance partition, why
report a 42x TV improvement off it as a headline?"

Resolution: the two sentences are reconcilable if "concentrated
(Huffman-style)" is read as "partitions where max alpha(y) is
high", which is true of both Huffman and TV-min on heavy-tailed
distributions (TV-min concentrates more, not less). But the abstract
does not say this.

Recommendation: rewrite the second sentence to be specific:

> Both single-instance frequency hiding (single-instance TV) and
> multi-instance coincidence-oracle leakage are minimized by
> partitions concentrated on the heavy modes of p_y; Huffman is
> always on the (TV, L) Pareto frontier, and the TV-optimal corner
> (which can lie off Huffman under integer codeword constraints)
> provides a separate Pareto-optimal design point.

This avoids the prescription ambiguity. It is also a direction-of-
prescription clarification: "concentrated" is the structural property,
and Huffman + TV-min are two ways to achieve it; the right choice
depends on whether L (space) or TV (leakage) is the operational
objective.

**LOG-MAJ-3 (Theorem 8.1 hypothesis: epsilon dependence not stated).**
Location: lines 1758 to 1780.

Theorem 8.1 states Pr[predict in | filler] = sum_y prod_i alpha_i(y)
and accuracy(t) = 1 - (1/2) sum_y alpha_i(y)^t. The bound assumes
the codec coverage epsilon = sum_y alpha(y) is the same across
instances (so that filler's "predict in" probability is comparable
across instances).

The theorem hypothesis (lines 1763 to 1767) says "each with its own
encoder enc_i, decoder dec_i, and acceptance partition
{alpha_i(y)}_{y in Y}, with K(x) = 1 for all x." It does not state
the per-instance epsilon_i = sum_y alpha_i(y). If instances have
different epsilon_i, the proof goes through (the bound just becomes
prod_i alpha_i(y) for each y, which is what the theorem actually
states for heterogeneous instances at equation 8.1). So the theorem is
correct for arbitrary heterogeneous (alpha_i, epsilon_i), but the
prose at line 1855 to 1858 says "At fixed epsilon = sum_y alpha(y),
this sum is minimized when alpha is uniform" which switches to the
homogeneous case.

The corollary statement (line 1865 "Among acceptance partitions with
fixed epsilon") is OK if "fixed epsilon" means a single design point
where all instances share the same epsilon. Recommendation: add one
clarifying sentence after Theorem 8.1 stating "When all instances
share the same partition alpha_i = alpha, the formula collapses to
Equation 8.2; throughout the rest of this section we assume the
homogeneous instance setting unless noted." This avoids ambiguity
when readers map theorem to corollary.

**LOG-MAJ-4 (Proposition 8.2 saturation assumption: bidirectional
claim).** Location: lines 1938 to 1972.

Proposition 8.2 states the pattern-coincidence probability is
prod_{i=2}^t 1/|A_i(y)| under the saturation assumption. The
saturation hypothesis (lines 1944 to 1949) reads: "the construction
saturates each acceptance region: every bit string in A_i(y) is
reachable as f_hat_i(c) for some member cipher value c encoding a
value-y plaintext (this holds, e.g., for Huffman codespace classes
where K(x) equals the codespace class size 2^(n - l_{f(x)}))."

The proof uses uniformity of f_hat_i(c) over A_i(y). For uniformity to
hold, the saturation must be bijective (each pattern in A_i(y)
reached exactly once, not multiple times) AND uniform (each pattern
reached with equal probability). The hypothesis only states
"reachable" which is the weaker surjectivity. The parenthetical
"(this holds, e.g., for Huffman codespace classes where K(x) equals
the codespace class size 2^(n - l_{f(x)}))" implicitly assumes a
specific encoder construction (Huffman with codespace-class-sized
multiplicity).

The proof step at lines 1981 to 1986 says "the specific pattern
f_hat_i(c_i) in A_i(y) chosen by instance i is uniformly distributed
on the |A_i(y)| patterns" without justifying why surjective +
random-oracle gives uniformity. This is true under the bijective
encoder construction in the parenthetical, but is not generally true
under arbitrary surjective encoders.

Recommendation: tighten the hypothesis to "the encoder achieves a
uniform-over-A_i(y) bijection from {0, ..., K(x)-1} to A_i(y) for
each value-y plaintext x". Or carry the parenthetical condition into
the hypothesis statement and reference it explicitly. The R7 MAJ-2
flag ("Proposition 8.2 needs bijectivity not just saturation") was
marked open in state.md item 2 of next actions; this round it remains
open.

This is again a direction-of-prescription clarity issue: the
hypothesis says "surjective" but the proof needs "bijective and
uniform". Minor in the technical sense (the Huffman construction
satisfies both), major in the sense that a careful reader hits a
gap.

### Minor

**LOG-MIN-1 (line 1009 alpha(y) = epsilon * p_y in caption vs alpha(y)
proportional to p_y in body).** The figure caption says "Under
Shannon-optimal allocation alpha(y) = epsilon * p_y". The body at
line 1054 says "Setting alpha(y) proportional to Pr[f(X) = y]
simultaneously achieves two goals." The first is a specific
normalization; the second is general. Both correct but cosmetically
inconsistent. Recommendation: standardize on
alpha(y) = epsilon * p_y throughout, since this is the actually
implemented allocation.

**LOG-MIN-2 (line 1153 normalization claim).** Step 2 of Theorem 6.2
says "alpha(y) = epsilon * p_y (proportional to value frequency,
normalized so sum_y alpha(y) = epsilon)". This is the same allocation
as the caption above. Cross-reference is implicit; consider explicit
"as in Figure 6.1" reference.

**LOG-MIN-3 (Bayesian deniability formula symmetric error
assumption).** Proposition 10.1 (line 2486) assumes "symmetric error
rate eta (i.e., Pr[y=1 | f(x)=0] = Pr[y=0 | f(x)=1] = eta)". This is
the Warner randomized response equivalence and is correct. But the
cipher map's eta as defined at Property 3 (Definition 4.3) is a
construction error rate, not necessarily symmetric. For Boolean
cipher maps via Shannon-optimal acceptance partition, the per-class
error rates are not in general equal. Worth a one-sentence remark
that Proposition 10.1's eta is the symmetric variant, identifying it
with the construction parameter for the special case of symmetric
errors.

**LOG-MIN-4 (Remark 8.x huffman-member-coincidence formula edge
case).** Line 2013 to 2016 derives Pr[predict in | member] approx
2^(-n(t-1)) * sum_v p_f(v) * 2^(l_v(t-1)). For t = 2, this reduces to
"|Y| / 2^n (each summand contributes ~ 1 under 2^l_v ~ 1/p_f(v))."
The approximation 2^l_v ~ 1/p_f(v) is the asymptotic (long-code)
limit and breaks down for integer-length Huffman codes with small
|Y|. The reduction "|Y| / 2^n" is an approximation, not an equality;
worth stating as "approximately |Y|/2^n under the asymptotic Huffman
length assumption."

**LOG-MIN-5 (cor:t-geometry name vs cor:t-dependent).** State.md says
"Corollary 8.x (renamed cor:t-dependent -> cor:t-geometry)". Verified
the rename landed: label is cor:t-geometry at line 1866. All forward
references in manuscript (lines 1655, 2050, 2655, 2774) consistently
use cor:t-geometry. Closure confirmed.

**LOG-MIN-6 (Definition 8.x pattern/decode attacker names).** Lines
1915 to 1936 define two attackers ("Pattern-coincidence" and
"Decode-coincidence"). The names are descriptive but introduce
"pattern" terminology that does not appear elsewhere in the paper
(the rest of section 8.3 uses "coincidence oracle" without qualifier).
Recommendation: keep both names but add a one-line note "the
coincidence oracle of Theorem 8.1 is the decode-coincidence attacker;
the pattern-coincidence attacker is its private-codec analog" so the
reader can map between the two notations.

### Suggestions

**LOG-SUG-1 (additional direction-of-prescription audit).** As a
proactive defense against the pattern the user flagged, suggest adding
a table or remark at section 5.2 that explicitly lists the direction
of each major prescription:

| Quantity | Goal | Recommendation |
|---|---|---|
| delta | Minimize | Increase K(x), inject filler, raise granularity p |
| epsilon | Minimize for space | Trade off vs eta and construction time |
| eta | Minimize for correctness | Trade off vs construction time and deniability |
| Sum_y alpha(y)^t | Maximize | Concentrate alpha on heavy modes (Huffman-style) |
| L (codeword length) | Minimize | Huffman |
| TV(p, alpha) | Minimize | TV-optimal allocation (may differ from Huffman) |
| K(x) | Set proportional to D(x) | Simmons homophonic; flattens Q |

This is the kind of direction-summary that would have caught all
three errors the user reported. Suggested location: near Table 5.1
("Quantitative confidentiality bounds") at line 851.

**LOG-SUG-2 (codomain-side equality leakage).** The §8.3 multi-instance
attack assumes the latent function f is the same across instances. If
the codomain Y is large and structured (e.g., document IDs), the
coincidence-oracle attacker's accuracy at the same alpha is dominated
by sum_y alpha(y)^t over the same y. For y where alpha(y) is small
across instances, the multi-instance probability is exponentially
small in t. So the practical attacker bound depends on the heaviest
alpha(y) raised to t, not on |Y|. Section 8.3 makes this implicit at
line 1856 ("the sum is dominated by (max alpha)^t"). A one-sentence
operational reading would help: "in deployment terms, the attacker's
effective accuracy is determined by the heaviest acceptance class, not
the average."

**LOG-SUG-3 (consistency check for online construction at section
9.3).** Section 9.3 ("Online Construction") refers to "trapdoor
Boolean algebra" with citation bernoulli-types. The four-property
framework was developed for batch construction; section 9.3 asserts
without proof that online construction also satisfies the four
properties. Either add a one-sentence proof sketch ("totality is
immediate from the hash-based encoding; representation uniformity
holds at construction time; correctness depends on bitwise OR
collision rates; composability is inherited from union-of-hashes
structure") or explicitly defer to the cited companion paper for the
property verification.
