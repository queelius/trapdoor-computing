# Logic Checker Report (Round 5, 2026-04-30)

**Specialist**: logic-checker
**Manuscript**: cipher_maps.tex (1841 lines)

## Summary

The R5 restructure introduces three new formal items in §5: Definition 5.1 (entropy ratio), Proposition 5.1 (confidentiality bound), and the Operational Consequences enumeration. Two prior theorems (6.1 lower bound, 6.2 space-optimal) were edited to address MAJ-1 from R4. The composition theorem and its corollary remain unchanged structurally.

I traced through every numbered statement in the paper (3 theorems, 5 propositions, 5 definitions, 1 corollary). The proofs are mostly sound, but **Proposition 5.1 has a delicate gap**, **Operational Consequence #2 is logically overstated**, and **Operational Consequence #3 invokes Pinsker in the wrong direction**.

**Findings**: 0 critical, 3 major, 4 minor.

## Critical findings

None.

## Major findings

### LOG-1 (Major): Operational Consequence #2 overstates Property 1

**Location**: cipher_maps.tex lines 691-694 (§5.2, item 2 in the enumeration)
**Quoted text**:
> "Real and filler queries are statistically equivocal (Property 1, totality). Both produce $n$-bit output through the same total function; the joint distribution of the trace under any $T$-chosen real-vs-filler partition is identical."

**Problem**: The claim that the joint distribution is **identical** does not follow from Property 1 alone. Property 1 (Definition 4.1, totality) states only that for $c$ chosen uniformly at random from $\{0,1\}^n \setminus \mathrm{Im}(\enc)$, the distribution of $\fhat(c)$ is uniform over $\{0,1\}^n$ under the random oracle model. Real queries are drawn from $\mathrm{Im}(\enc)$, which is a strict subset of $\{0,1\}^n$ of measure $\varepsilon \cdot |X| / 2^n$ or thereabouts. Filler queries are uniform over $\{0,1\}^n$.

These two distributions are NOT identical: filler queries hit the rejection region with probability $1 - \varepsilon$, real queries (by construction) hit $\bigcup_y A(y)$ with high probability. An adversary observing **the inputs** $c_i$ alone cannot distinguish (assuming $\enc$ randomizes via $K(x) > 1$ or otherwise covers the image space close to uniform). An adversary observing **outputs** $\fhat(c_i)$ can: real-query outputs decode to valid $y$ with probability $\approx 1 - \eta$; filler-query outputs decode to valid $y$ with probability $\varepsilon$ (much smaller).

The actual bound is $\TV \leq \delta$ as stated in Table 1 row 1. The §5.2 #2 prose contradicts the table.

**Cross-verification**: the table is consistent with Property 2; the inline prose is not. Fannes-Audenaert (Proposition 5.1) bounds entropy via $\delta$; the prose's "identical" claim would require $\delta = 0$.

**Suggestion**: Replace lines 691-694 with: "Real and filler queries are $\delta$-equivocal in distribution (Properties 1 and 2 together): both are observed as $n$-bit cipher values, and the cipher value distribution is $\delta$-close to uniform by Property 2. Consequently, no statistical test distinguishes real from filler with advantage exceeding $\delta$."

### LOG-2 (Major): Operational Consequence #3 invokes Pinsker in the wrong direction

**Location**: cipher_maps.tex lines 695-699
**Quoted text**:
> "Domain identification is bounded by $\delta$ (Property 2). $U$'s posterior on which inputs are 'real domain elements' versus 'noise' is at most $\delta$ in total variation from the prior, by Pinsker-style arguments combined with Proposition 5.1."

**Problem**: Pinsker's inequality is $\TV(P, Q) \leq \sqrt{D_{KL}(P \| Q) / 2}$, bounding TV in terms of KL. The text wants to bound posterior TV in terms of $\delta$, which is itself a TV bound on Property 2. The chain of reasoning is unclear: how does a TV bound on the cipher value marginal give a TV bound on posteriors?

The sister paper maxconf §4 explicitly notes (lines 487-490): "Pinsker gives $D_{KL} \geq 2\,\TV^2$, an upper bound on TV given KL, which does not convert to a KL bound given TV. The correct direction is Fannes-Audenaert." So Proposition 5.1 itself relies on Fannes-Audenaert, not Pinsker. Invoking "Pinsker-style arguments" here in the consequence statement contradicts the sister paper's own caveat.

The actual derivation of "posterior is $\delta$-close to prior" requires either:
(a) a Le Cam style argument from $\TV(\text{cipher}, \text{uniform}) \leq \delta$ to bound posterior advantage; or
(b) a data-processing inequality from Fannes-Audenaert.

Neither is "Pinsker-style."

**Suggestion**: Replace "by Pinsker-style arguments" with "by data-processing applied to Property 2 (the cipher value distribution is $\delta$-close to uniform, so posteriors of any function of the cipher trace are $\delta$-close to the priors of the same function under the uniform distribution)." Or, more conservatively, drop "Pinsker-style" and write "by Property 2 combined with Proposition 5.1."

### LOG-3 (Major): Proposition 5.1 proof sketch under-specifies the binding to $\delta$

**Location**: cipher_maps.tex lines 642-662 (Proposition 5.1 + proof sketch)
**Quoted text**:
> "The Fannes-Audenaert continuity inequality bounds entropy differences by total variation distance, and Property 2 gives $\TV(Q, \mathrm{Uniform}) \leq \delta$ where $Q$ is the cipher value distribution induced by $\enc$. Composing the two yields [eq:fannes-bridge]."

**Problem**: The proposition is about the entropy ratio $e = H(X | \fhat, \tau) / H^*(X)$, which is an entropy ratio of the **latent input distribution** conditioned on the **trace** $\tau$. The proof sketch deploys Fannes-Audenaert against the **cipher value distribution** $Q$ versus uniform. The bridge between "entropy of cipher value distribution close to $n$" and "entropy of latent input given trace close to $H^*(X)$" requires an additional step.

The sister paper maxconf Theorem 4.1 part 3 (line 473-490) establishes $H(Q) \geq n(1 - \delta) - h_2(\delta)$, which is about $H(Q)$, the marginal entropy of cipher values. It does NOT directly establish $H(X | \fhat, \tau) \geq H^*(X)(1 - \delta - h_2(\delta)/n)$, which is what cipher-maps Proposition 5.1 claims.

The connection is that the trace $\tau$ is a function of cipher values (and the cipher map itself), so $H(X | \fhat, \tau) = H(X | \fhat, \text{cipher values}) \geq$ something. But this requires either (a) the trace contains no information beyond the cipher values, which is plausible but unstated; or (b) a separate argument that observed cipher values give $\delta$-close-to-uniform information.

**Cross-verification**: I read maxconf §4 carefully. Theorem 4.1 there gives the entropy ratio in terms of $H(Q)$ and $H^*$, where it appears that for the maxconf framework $H^* = n$ (lines 449, 466). Cipher-maps Proposition 5.1 uses $H^*(X)$, the maximum entropy of the latent input under public constraints, which may not be $n$ at all.

This is a **definitional mismatch**: maxconf normalizes by $H^* = n$ (the cipher value space size), cipher-maps normalizes by $H^*(X)$ (the latent input space). The two entropy ratios are not the same quantity, and the citation `[Theorem 4.3]{towell2026maxconf}` does not establish what cipher-maps Proposition 5.1 needs.

**Suggestion** (this is the load-bearing M1 issue and worth user attention):
1. Reconcile the two definitions. Either cipher-maps Proposition 5.1 should use $H^* = n$ (matching maxconf), or maxconf should be reframed to use $H^*(X)$.
2. If $H^*$ is the cipher value space dimension (i.e., $n$ bits), say so explicitly in cipher-maps Definition (currently stated as "maximum entropy of $X$ under any constraints publicly visible to $U$" at line 632, which is the latent input space).
3. The proof sketch needs to spell out: "By Property 2, the cipher value marginal $Q$ has $\TV(Q, U) \leq \delta$. By Fannes-Audenaert, $|H(Q) - n| \leq \delta n + h_2(\delta)$. The trace $\tau$ is a deterministic function of the cipher values and $\fhat$, so $H(X | \fhat, \tau)$ is bounded below by [data processing argument]."

This is the M1 load-bearing claim. If a PoPETs reviewer checks the chain Proposition 5.1 -> maxconf Theorem 4.1, they will notice the $H^*$ mismatch.

## Minor findings

### LOG-4 (Minor): Theorem 6.1 lower-bound proof has a Stirling subtlety

**Location**: cipher_maps.tex lines 769-789 (Theorem 6.1 proof)
**Quoted text** (lines 779-782):
> "For $|U| \gg n$, Stirling's approximation $\log_2 \binom{|U|}{n} = n \log_2(|U|/n) + n \log_2 e + O(\log n)$ gives $\log_2 \binom{|U|}{n} \approx n \log_2(|U|/n)$ bits to leading order"

**Problem**: The Stirling step "$+ n \log_2 e$" is dropped without justification. $n \log_2 e \approx 1.44 n$, which is comparable to (and larger than) the leading correction the bound's information-theoretic statement neglects. The "leading order" handwave swallows about 1.44 bits per element.

**Resolution path**: This is fine for the lower bound (the bound is loose by $O(1)$ bits per element regardless), but the proof should say so. "We retain only the dominant term $n \log_2(|U|/n)$; the additive $1.44 n$ from Stirling and the $O(\log n)$ correction do not affect the per-element rate." Then identifying this with $-\log_2 \varepsilon$ should also note that the matching is up to $O(1)$ additive bits per element.

The current proof presents the result as exact when it is asymptotic.

### LOG-5 (Minor): Proposition 5.1 missing condition $\delta \leq 1/2$

**Location**: cipher_maps.tex line 643-650 (Proposition 5.1 statement)

**Problem**: The Fannes-Audenaert continuity inequality $|H(P) - H(Q)| \leq t \log_2(d-1) + h_2(t)$ holds for $t \leq 1/2$. The sister paper maxconf §4 explicitly states this condition (line 475: "for any distributions $P, Q$ on a support of size $d$ with $\TV(P, Q) \leq t \leq 1/2$"). Cipher-maps Proposition 5.1 omits the $\delta \leq 1/2$ condition.

For the cipher map regime, $\delta \leq 1/2$ is essentially always true (large $\delta$ defeats the construction's purpose), but mathematical rigor requires the condition.

**Suggestion**: Add "for $\delta \leq 1/2$" to the statement of Proposition 5.1.

### LOG-6 (Minor): Theorem 6.2 (space optimality) Step 2 phrasing

**Location**: cipher_maps.tex lines 1010-1029 (Theorem 6.2 proof Step 2)
**Status**: This was the MAJ-1 fix from R4. The text now reads:
> "Each correctly stored element $x_i$ must satisfy $h(\ell) \oplus h(x_i) \in A(y_i)$ (Definition 6.1); under the random oracle model this occurs with probability $\alpha(y_i)$, so the information cost of pinning down a single element's acceptance is $-\log_2 \alpha(y_i)$ bits."

**Problem**: This is better than the R4 version, but the link from "occurs with probability $\alpha(y_i)$" to "information cost is $-\log_2 \alpha(y_i)$" still elides a step. Probability of an event is not directly the information cost of pinning the event down.

The actual logic: the seed must be chosen such that for each element, the hash falls in the prescribed acceptance set. Under ROM, hash values are uniform, so the fraction of seeds that satisfy a given element's constraint is $\alpha(y_i)$. The information needed to specify a satisfying seed (vs an arbitrary seed) is $-\log_2 \alpha(y_i)$ bits per element (assuming independence across elements).

**Suggestion**: Rephrase Step 2 to "the seed must be chosen so that for each element $x_i$, $h(\ell) \oplus h(x_i) \in A(y_i)$. Under ROM, the fraction of seeds satisfying a given element's constraint is $\alpha(y_i)$. The information cost of specifying such a seed (relative to an arbitrary seed) is $-\log_2 \alpha(y_i)$ bits per element, by independence of constraints across elements under ROM."

This makes explicit the assumption (independence) that the original R4 version glossed.

### LOG-7 (Minor): Composition theorem (Theorem 7.1) error-cancellation note is correct but counterproductive

**Location**: cipher_maps.tex lines 1342-1352 (Theorem 7.1 proof)

The R6 fix (nm2 from R4) added: "Note that the bound $\Pr[A \cup B]$ is pessimistic: it counts every case in which at least one map errs as a composition error, but occasional error cancellation occurs..."

This is logically correct. But it sits awkwardly inside a proof that then proves the bound is exact under the re-randomization condition (Definition 7.1). The reader is left wondering: is the bound tight or is it pessimistic?

**Resolution**: The bound is **pessimistic** if errors cancel; **tight** if they are independent (re-randomization condition). The proof says both but doesn't explicitly draw the distinction.

**Suggestion**: Add a sentence at the end of the proof: "Thus the bound is exact under re-randomization (Definition 7.1) and pessimistic otherwise; both bounds and the gap are upper-bounded by the cancellation rate, which is bounded by $\eta_f \eta_g \cdot \Pr[\text{value-equivalent error in } \fhat]$."

## Suggestions

- **LOG-S1**: The Definition 7.1 (re-randomization condition) introduces "$\fhat$ and $\ghat$ use independent seeds" as part (i). But §4.4 Composability and Theorem 7.1 assume "both under the same secret $s$" (line 491). The two are inconsistent: either re-randomization requires independent seeds (so it can never hold for same-secret composition), or it's defined for some other notion of independence. Worth clarifying.

- **LOG-S2**: The Bayesian deniability proposition (§9.4, lines 1709-1727) has a closed-form posterior derivation that is correct. But the prose "for $\eta = 0$, the posterior equals 1 (no deniability); for $\eta = 1/2$, the posterior equals $\pi$ (observation is useless)" omits the intermediate cases. A small numerical example (e.g., "for $\eta = 0.05$ and $\pi = 0.1$, the posterior is $\approx 0.68$, an order of magnitude reduction in adversary confidence") would strengthen the claim.

## Cross-paper logic verification

I read the cited maxconf §4 Theorem 4.1 part 3 in detail. Its proof of $H(Q) \geq n(1 - \delta) - h_2(\delta)$ is correct: it correctly applies Fannes-Audenaert with $d = 2^n$ and $\TV(Q, U) \leq \delta$, recovering the linear-in-$\delta$ bound.

The mismatch between maxconf's $H(Q)/n$ entropy ratio and cipher-maps' $H(X|\fhat,\tau)/H^*(X)$ entropy ratio remains the open issue (LOG-3). The maxconf framework normalizes by $n$ (cipher value space size); cipher-maps normalizes by $H^*(X)$ (latent input space entropy). These are different quantities, and the citation chain is broken at this transition.

I read the cited rekeying §6 Theorem 6.1 (incorrectly cited as 7.1 in cipher-maps; see citation-verifier CITE-1). Its statement and proof are correct: the orbit argument bounds the rekeying chain at $n+1$ values, and the entropy bound follows from the orbit-size cardinality argument.

## Summary table

| Item | Status | Severity |
|---|---|---|
| Theorem 6.1 (lower bound) | Sound, asymptotic handwave | Minor |
| Theorem 6.2 (space optimality) | Sound, Step 2 phrasing | Minor |
| Theorem 7.1 (composition) | Sound, cancellation note | Minor |
| Corollary 7.2 (chain) | Sound | OK |
| Proposition 5.1 (confidentiality bound) | $H^*$ mismatch with cited maxconf | **Major** |
| Proposition 6.4 (per-seed success) | Sound | OK |
| Proposition 6.5 (bucketed time) | Sound | OK |
| Proposition 6.7 (entropy cipher map space) | Sound | OK |
| Proposition 7.1 (AND gate) | Sound | OK |
| Proposition 9.4 (Bayesian deniability) | Sound, textbook | OK |
| Definition 5.1 (entropy ratio) | $H^*$ definition vs maxconf | **Major** |
| Definition 7.1 (re-randomization) | Inconsistent with same-secret composition | Suggestion |
| §5.2 #2 (real vs filler equivocal) | Overstated | **Major** |
| §5.2 #3 (Pinsker invocation) | Wrong direction | **Major** |

## Recommendation

The R5 restructure is largely sound, but the M1 collapse via Proposition 5.1 has a definitional gap with the cited sister-paper theorem (LOG-3) and the §5.2 enumeration has two prose-level logic errors (LOG-1, LOG-2). Given that the M1 collapse is the load-bearing strategy for the round, these are major issues that should be addressed before submission.
