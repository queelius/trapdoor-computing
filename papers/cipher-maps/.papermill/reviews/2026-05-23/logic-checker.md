# Logic Checker Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Manuscript file**: paper/cipher_maps.tex (2676 lines)

## Headline finding

The Round 7 critical issue (CRIT-1: direction-inverted interpretation
of the multi-instance composition recommendation) is RESOLVED. The
manuscript at lines 1840 to 1885 now correctly states that
concentrated (Huffman-style) partitions defend better at every t >= 1,
and there is no codec-choice regime change between single-instance and
multi-instance. The numerical illustration at lines 1864 to 1877 gives
Huffman defending 132x better than uniform (error rate ratio
0.016 / 0.00012) at t = 5 in the Zipf, |Y| = 8 configuration. The
§10.6 Summary item (iv) at lines 2654 to 2660 reads correctly.

## R7 carry-over verification

### CLOSED (R7 CRIT-1)
- **Abstract lines 80 to 86**: Now reads "Both single-instance and
  multi-instance optima favor concentrated (Huffman-style) partitions;
  when multi-instance leakage exceeds deployment tolerance, the
  appropriate defense is randomized encoding (K(x) > 1) rather than
  codec retuning." No "inversion" wording.
- **Corollary 8.x (cor:t-geometry, lines 1852 to 1862)**: Now reads
  correctly: "the coincidence-oracle attacker's accuracy... is maximized
  (worst for the defender) by the uniform allocation... and minimized
  (best for the defender) by concentrating alpha on the heaviest values."
- **§10.6 paragraph (lines 2565 to 2588)**: Now reads "There is no
  single-instance versus multi-instance trade-off in codec choice:
  Huffman dominates at every t."
- **Summary item (iv) (lines 2654 to 2660)**: Reads "the
  coincidence-oracle accuracy is maximized by uniform allocation and
  minimized by concentrated Huffman-style allocation..., so the
  Shannon-optimal partition is preferred at every t with no
  codec-choice regime change."

### NOT FIXED (R7 MAJ-1)
- **Theorem 8.1 verbal definition at lines 1741 to 1743**: Still reads
  "predicts 'in-domain' iff dec_1(\fhat_1(c)) = \cdots = \dec_t(\fhat_t(c))"
  using a single c. The proof (lines 1773 to 1798) correctly uses tuple
  notation c_i = enc_i(x, 0). These are different attack models in
  general (single shared probe c versus per-instance tuple of probes).
  The Definition 8.x (pattern/decode-coincidence attackers, lines 1902
  to 1920) uses the tuple notation correctly.
- **Suggestion**: Rewrite the verbal definition to use tuple notation,
  e.g., "given a probe tuple (c_1, ..., c_t) constructed by the
  trusted side as c_i = enc_i(x, 0), the coincidence oracle predicts
  'in-domain' iff dec_1(\fhat_1(c_1)) = \cdots = \dec_t(\fhat_t(c_t))
  and the common decoded value is in Y." Carries severity MAJOR.

### NOT FIXED (R7 MAJ-2)
- **Proposition 8.2 member-case proof, lines 1922 to 1948**: Still
  reads "assume the construction *saturates* each acceptance region:
  every bit string in A_i(y) is reachable as \fhat_i(c) for some
  member cipher value c encoding a value-y plaintext."
- **Problem**: Saturation only ensures reachability; the proof at lines
  1958 to 1970 needs uniformity of the induced distribution on A_i(y)
  when k is drawn uniformly. This requires bijectivity of
  k -> \fhat_i(enc_i(x, k)) with K(x) = |A_i(y)|.
- **Suggestion**: Replace "saturates" with "uniform-saturating"
  (bijection between the K(x) multiplicities and A_i(y)). Add a
  construction note for the Huffman case showing the explicit bijection.
  Carries severity MAJOR.

### NOT FIXED (R7 MAJ-3)
- **Proposition 8.2 formula, lines 1938 to 1944**: Still implicitly
  assumes homogeneous A_i(y) across instances. The formula
  prod_{i=2}^t 1/|A_i(y)| is correct only when all A_i(y) coincide
  (homogeneous instances or codec-level acceptance sets shared across
  instances).
- **Suggestion**: Add a single sentence restricting to homogeneous
  instances OR clarifying that A_i(y) refers to a codec-level
  acceptance set shared across instances. Carries severity MAJOR.

### NOT FIXED (R7 MAJ-4)
- **Remark 8.x on Huffman saturation, lines 1990 to 2007**: The remark
  acknowledges saturation with |A_i(v)| = 2^{n - \ell_v} but does not
  show how the encoder maps distinct k values to distinct patterns in
  A(y). The construction is left implicit.
- **Suggestion**: Add a one-paragraph construction note showing that
  for Huffman codespace classes, the encoder enc_i(x, k) can be
  defined as concatenating the prefix-free codeword of f(x) with the
  k-th element of {0,1}^{n - \ell_{f(x)}} in canonical order. This
  makes the bijection explicit. Carries severity MAJOR.

## R8 new findings

### LOG-N1 (NEW, MINOR): Master-vs-operational subkey clarification
intersects with multi-instance independent seeds
- **Location**: Remark 4.x (lines 566 to 577) versus Theorem 8.1
  (line 1747)
- **Issue**: The master-secret/operational-subkey paragraph at
  Remark 4.x establishes that distinct cipher maps under the same
  master secret have independent operational seeds via domain
  separation. The Theorem 8.1 statement "under independent secret
  seeds" should be linked to this remark explicitly, since most
  practical multi-instance deployments will share a master secret
  with per-instance domain separators rather than having truly
  independent master secrets.
- **Suggestion**: At line 1747, add a parenthetical: "(in the sense
  of Remark~\ref{rem:master-vs-op}: distinct operational sub-derivations
  of a shared master secret suffice under the random oracle model)".
  Severity MINOR.

### LOG-N2 (NEW, MINOR): Composition theorem inequality direction is
correctly stated, but a remark could clarify when equality is reached
- **Location**: Theorem 6.2 (Theorem~\ref{thm:composition}) at lines
  1466 to 1477
- **Status**: The statement reads "with equality under the
  re-randomization condition (Definition~\ref{def:re-randomization})"
  which is correct. The proof at lines 1479 to 1507 correctly
  derives the bound via inclusion-exclusion.
- **Issue**: The "occasional error cancellation" sentence at lines
  1485 to 1489 suggests the bound is loose even with independence
  (because some errors cancel), which contradicts the "equality under
  re-randomization" claim of the theorem statement. The reader has to
  reconcile two slightly inconsistent claims: (i) equality under
  re-randomization, (ii) cancellation makes the bound loose.
- **Resolution**: These are not contradictory; the re-randomization
  case is the upper bound on Pr[A union B] under independence
  (eta_f + eta_g - eta_f eta_g), and the cancellation refers to the
  fact that even this bound is loose if you credit error cancellation
  (which the theorem does not). The text could make this clearer by
  saying "without crediting cancellation, equality holds under
  re-randomization" or similar.
- Severity MINOR.

### LOG-N3 (NEW, MINOR): Section 5.1 entropy ratio definition unification holds
- **Location**: Definition 5.1 (lines 701 to 719) and §1 line 168
- **Status**: Verified e = H(Q)/n is consistent across §1, §5.1, and
  the maxconf citation chain. R6 MAJ-1 closure landed in R7 and
  remains landed.
- **Status**: CLOSED, no action needed.

### LOG-N4 (NEW, MINOR): Theorem 6.3 (cor:chain) inductive step
- **Location**: Lines 1538 to 1547
- **Status**: The induction is correct. The base case m=2 is the
  composition theorem. The inductive step composes the (m-1)-map
  composition with map m via Theorem 6.2 again. Both the bound and
  the equality-under-re-randomization clause carry through.
- **Status**: CLEAN, no action needed.

### LOG-N5 (NEW, MINOR): Proposition 5.1 (Fannes-Audenaert) bound
direction is correct
- **Location**: Equation (5.x) (\eqref{eq:fannes-bridge}, lines 745 to
  748)
- **Status**: e >= 1 - delta - h_2(delta)/n; the inequality direction
  is correct (more uniformity -> higher entropy ratio lower bound).
  Verified by recomputing the Fannes-Audenaert continuity inequality
  with the appropriate normalization (n is the cipher value space
  dimension, so the reference uniform distribution has entropy n bits).
- **Status**: CLEAN, no action needed.

## Summary of logic-side findings

- 0 critical (R7 CRIT-1 is fully closed)
- 4 major carry-over from R7 (MAJ-1 verbal definition tuple, MAJ-2
  saturation vs bijectivity, MAJ-3 homogeneous instances, MAJ-4 Huffman
  saturation construction). All are editorial polish on the new §8.3
  content; none invalidate the formal results.
- 2 minor new (LOG-N1 independent seeds link to master-vs-operational,
  LOG-N2 composition theorem cancellation remark wording)
- 3 minor verifications (LOG-N3, LOG-N4, LOG-N5 all clean)

**Logic side recommendation**: After the R7 MAJ-1 to MAJ-4 fixes are
applied, the formal apparatus is publication-ready. The CRIT-1 fix
landed cleanly without introducing any regression.
