# Full-paper proof verification (2026-06-03)

Scope: every formal claim in `paper/cipher_maps.tex` (5 theorems, 9
propositions, 3 corollaries, 13 definitions; 14 proof blocks). Method:
three independent parallel audits (two logic auditors over disjoint proof
groups + one numerics auditor recomputing every quantitative claim in
Python), cross-checked by hand on the load-bearing items.

Overall: the mathematical core is SOUND. The two intricate arguments
(Prop 4.1 homophonic tightness, Prop 5.1 Fannes bridge) are correct;
composition (M4) and the coincidence-oracle direction (R7 CRIT-1) are
confirmed resolved. The serious items are OVERCLAIMS / IDEALIZATIONS in
the space-optimality and (TV, L)-frontier presentation, not wrong
theorems.

================================================================
CRITICAL (headline number; needs a decision)
================================================================

## C1. "42x TV reduction at 17% length overhead" conflates two allocations
Sites: abstract (~line 76), intro (~151), §6.2 (~1157, added this
session), §10 frontier bullet (2711-2714).

The §10 method is defined (line 2701) as Kraft-feasible LENGTH
ASSIGNMENTS {l_y} with alpha(y)=2^{-l_y} (one codeword per value). Under
that method, for heavy-tail p=(0.9, 0.0143 x7) at n=6, recomputed three
ways (numerics agent + hand):
  - Huffman:                       TV=0.400, L=1.286
  - TV-min length assignment:      TV=0.205, L=1.500 (+16.7%)  -> 1.95x
  - Homophonic multiplicity m/2^n: TV=0.0093 (43x) but L_eff=0.751 (-42%)
So 42x is achievable ONLY via homophonic multiplicity (alpha=m/2^n,
the Property-2 K(x)>1 lever), which is SHORTER, not +17%. At the +17%
length-assignment corner the reduction is only ~2x. The sentence stitches
the 42x (multiplicity) to the 17% (length assignment): no single
allocation yields both.

Resolution options (user decision):
  (a) Keep the length-assignment frontier framing; correct the number to
      "~2x at 17% overhead" (honest but much weaker headline).
  (b) Reframe 42x as the homophonic-multiplicity result (the paper's
      actual confidentiality mechanism), reporting its true cost
      (storage / multiplicity K>1, length-neutral-to-shorter), NOT a
      length overhead. Requires the source experiment's cost metric.
  (c) Report BOTH corners correctly: length-assignment frontier ~2x at
      +17% L; homophonic multiplicity 42x at storage cost.
Recommendation: (c) or (b). (b)/(c) keep the strong 42x but attribute it
to the right lever. (a) is the safe fallback if the multiplicity cost
cannot be restated cleanly from the library data.

================================================================
MAJOR (achievability / space-optimality; proposed fixes, related to C1)
================================================================

## M1. Thm 6.2 + Corollary 6.3 "matches the lower bound": storage vs info-content
Thm 6.2 / Cor "Asymptotic optimality" (1219-1287); Remark rem:physical
-storage (1271-1282). The proof establishes an INFORMATION-CONTENT figure
(1-eta)(-log2 eps + mu); Remark concedes physical STORAGE is
-log2 eps + mu regardless of eta. But the theorem says "bound matches the
lower bound of Thm 6.1" (1227) and the corollary says "achieves ...
matching the information-theoretic lower bound" (1286). Thm 6.1 is a
STORAGE bound; the matched quantity is info-content; they coincide only
at eta=0 and only under entropy-coded storage. This is the recurring M5.
Fix: state matching only at eta=0 / under entropy coding; call Thm 6.2 an
information-content characterization, not a storage-optimality result.

## M2. Exact "= H(Y)" ignores the Shannon one-bit gap (dyadic-only)
Thm 6.2 Step 2 (1242-1256) and Prop 6.6 (1467-1476) write expected
prefix-free length exactly = H(Y). True only for dyadic p_y; in general
H(Y) <= L < H(Y)+1. This contradicts the paper's own line 1156 / 2720
("coincide only when p_y is dyadic"). Fix: H(Y) <= L < H(Y)+1 with
equality iff dyadic, or asymptotic via block coding. (Lower bound Thm 6.1
unaffected.) Related to C1 (same dyadic subtlety).

================================================================
MINOR (safe corrections)
================================================================

- m-sign. §7.2 proof line 1605: "positively correlated (Pr[A∩B] <= eta_f
  eta_g)" has the inequality BACKWARDS; positive correlation gives
  Pr[A∩B] >= eta_f eta_g. The stated conclusion (union-bound RHS is
  conservative) is correct. Fix: <= -> >=.
- Thm 8.2 (1893): add normalization "sum_y alpha_i(y) = eps_i <= 1" so the
  filler-coincidence formula is not misread as summing to 1.
- Cor 8.3 (1958-1963): "concentrating on the heaviest values" is loose;
  the exact minimizer of sum alpha(y)^t at fixed eps is a SINGLE value
  (Huffman approximates). Add the convexity / Schur-convexity
  justification (the corollary currently has no proof).
- Prop 8.4 (2042-2075): the clean product prod 1/|A_i(y)| for the
  pattern-coincidence attacker tacitly assumes ALIGNED acceptance regions
  (a common bit string across instances). Under independent seeds it is
  generally an inequality. Fix: add "assume aligned/homogeneous codecs"
  hypothesis (consistent with the homogeneous-codec framing of §8.3) or
  state as <=. (Borderline major if multi-codec deployment is intended.)
- Prop 10.1 (2578): reuses eta for a SYMMETRIC two-sided error, but
  Def 4.3 eta is a one-sided bound. The hash/PHF construction gives
  one-sided errors; the symmetric-channel (Warner) model is an extra
  assumption. Fix: rename eta_sym or add a reconciling sentence.
- Le Cam terminology (2335): "value-only Le Cam bound of 0.572" is a
  MEASURED accuracy, not the bound; the bound is 1/2+0.153/2 = 0.577.
  Relabel.
- Table le-cam-tight (2679-2683): Dense(n=4) UB printed 0.610, recompute
  0.609; Huffman(n=4) best-attacker 0.575 exceeds its UB 0.560 by 0.015,
  just outside the stated "within 0.014" envelope. Fix the two cells /
  widen the envelope statement to 0.015.
- Thm 6.1 (993-999): "subleading" for the +1.44n term is imprecise (it is
  Theta(n), same order). Dropping a POSITIVE term only weakens the lower
  bound (safe). Fix: "constant per-element (~1.44 bits)".
- Thm 6.1 (1000-1005): eps = n/|U| reads as defined-into-existence.
  Reframe: fix target eps, take |U| = n/eps.
- Prop 5.1 (849-851): make the implicit step log2(2^n - 1) <= n explicit.
- Prop 6.4 (1306): "expected seeds = 1/p" needs the across-trial i.i.d.
  premise (fresh seed l per trial under ROM). Add one sentence.
- Prop 6.5 (1345-1357): bucket sizes are random; by Jensen the stated
  T(k) is a LOWER bound on expected time, not the expectation. Reframe as
  "equal-load approximation" or T(k) >=.
- Def 3.1 (405-407): enc domain X x {0..K(x)-1} is a dependent sum, not a
  Cartesian product; minor notation abuse. Optionally write
  {(x,k): 0<=k<K(x)}.

================================================================
VERIFIED SOUND (independently confirmed)
================================================================

- Prop 4.1 Homophonic allocation: TV(Q,U) = (1/2)sum|D(x)-K(x)/N| and the
  proper-subset bound TV < (|X|-1)/N, constant tight. Confirmed by hand +
  script (n=3 ratio 1.293 vs the superseded |X|/(2N); sweep n=2..8).
- Prop 5.1 Confidentiality (Fannes-Audenaert): e >= 1 - delta -
  h2(delta)/n correct; delta<=1/2 guard valid (conservative); "proof"
  (not "sketch") justified.
- Thm 6.1 Lower bound: valid as a LOWER bound (counting + source coding;
  dropping +1.44n is safe direction). Presentational nits only.
- Thm 4.2 / Thm 7.2 composition: M4 RESOLVED. All sites use
  eta_total <= 1 - prod(1-eta_i) with "equality under re-randomization";
  the lone "=" (1646) is the correct algebraic identity inside the bound.
- Prop 7.1 AND-gate: all four cases verified by direct computation.
- Def 7.1 re-randomization, Cor 7.3 chain: sound; induction correct.
- Prop 8.1 granularity: both parts sound.
- Thm 8.2 coincidence oracle: accuracy = 1 - (1/2) sum alpha(y)^t correct;
  R7 CRIT-1 direction RESOLVED (concentrated/Huffman defends better;
  ~132x at t=5 verified ~128x, rounding).
- Prop 8.4 decode-coincidence branch: correct (randomized encoding gives
  no protection under a public codec). Pattern branch needs the alignment
  caveat (minor above).
- Prop 10.1 deniability: Bayes posterior correct; boundary cases right.
- Numerics MATCH: homophonic, coincidence oracle, Bloom/space table
  (4.5x, FPRs), AND-gate noise-floor (the old "12 vs 0.6" is correctly
  handled: 0.6 is the rejected independence prediction, 12 < noise-floor
  UB), Le Cam 1/2+delta/2, deniability.
- Dependency / circularity audit: CLEAN. No proof relies on a later
  result or on an unposted companion for a load-bearing step.

================================================================
NUMBERING NOTE (note, do not fix)
================================================================
Definitions and theorems use SEPARATE counters, so the section number
collides: Def 4.1 (totality) vs Prop 4.1 (homophonic); Def 5.1 (trusted)
vs Prop 5.1 (confidentiality); Def 6.1 (acceptance) vs Thm 6.1 (lower
bound). Disambiguated in text by the environment word ("Proposition 4.1"
vs "Definition 4.1"). Do NOT unify counters: it would renumber
everything and break maxconf's verified cross-refs (Def 3.1, Prop 4.1,
Thm 6.1, Thm 8.2, Prop 8.1).

================================================================
CANNOT-VERIFY
================================================================
The §10 "14 configurations / TV-optimal differs in 7/14" counts depend on
an unstated grid (numerics agent reconstructed 22 configs). Qualitative
claims (Huffman on the frontier; not always TV-optimal; TV-optimal iff
dyadic) reproduce robustly. Either pin the exact config list or soften to
the qualitative statement.

================================================================
ACTIONS
================================================================
RESOLUTION (2026-06-03, all applied per author direction "do what you
think is appropriate" + greenlight):
- C1 (42x): resolved as option (c) across all FIVE sites (abstract,
  intro, §6.2, §10 bullet, §10 summary). The length-assignment frontier
  is reported honestly as ~2x (1.9x) at +17% L; the 42x is attributed to
  the homophonic multiplicity lever (K(y) propto p_y, alpha=K/2^n,
  K=(57,1..1)) at a STORAGE cost (length-neutral), verified analytically
  (TV 0.40 -> 0.009). No library data needed.
- M1: Thm 6.2 statement reworded ("encodes ... bits of information";
  physical storage = -log2 eps + mu regardless of eta, pointer to
  rem:physical-storage); corollary scoped to storage at eta=0.
- M2: Prop 6.6 statement + proof now carry the one-bit gap
  (H(Y) <= L < H(Y)+1, dyadic-only). (Thm 6.2 Step 2 left as-is: it uses
  continuous alpha=eps*p_y, exact for threshold/range predicates.)
- Prop 8.4: common-acceptance-geometry (homogeneous-codec) hypothesis
  added to statement + proof; heterogeneous case noted as an upper bound.
- MINORS applied: sign slip 1605 (<= -> >=), Thm 8.2 normalization clause,
  Cor 8.3 single-value + Schur-convexity, Le Cam 0.572 relabel, table
  cells (0.560 -> 0.561, 0.610 -> 0.609), Prop 10.1 eta_sym note, Thm 6.1
  "constant per-element" + safe-direction note, Prop 6.4 i.i.d. clause,
  Prop 6.5 Jensen/equal-load note, Prop 5.1 explicit log2(2^n-1)<=n step.
- DEFERRED (cosmetic, self-consistent, not errors): Thm 6.1 eps=n/|U|
  framing; Def 3.1 dependent-sum notation. Numbering collision: left
  as-is (renumbering would break maxconf cross-refs).
- Build clean after all edits: 39 pp, 0 undefined references.
