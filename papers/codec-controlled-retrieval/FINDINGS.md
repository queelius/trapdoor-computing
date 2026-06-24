# Findings, corrections, and scope ledger

This is the orientation a reviewer (or a future reader of this project) needs that
the manuscript itself, for length, states only in passing. It records what is
proven versus measured versus open, and the corrections that the development
process turned up, including one reversal of a previously-claimed result.

## Corrections to be aware of (read these first)

### 1. `thm:randenc`: skewed randomized-encoding invariance is FALSE in general

An earlier draft claimed that storing a uniform within-class representative leaves
the non-member law invariant for every codec ("computationally verified for skewed
codecs; flag-level proof a follow-on"). That is wrong, and the wrongness is not a
gap but a counterexample.

- A skewed codec has no single `ker(pi)`. A within-class draw of a value of length
  `l'` adds a vector in `C_{l'} = ker(pi_{l'})`, which is invisible to `pi_{l'}` but
  VISIBLE to `pi_l` for `l > l'`. So randomizing a SHORT value can enlarge a LONGER
  value's projection and light up a previously-missed class.
- Exact counterexample (skew `{1,2,3,3}`, store `{A,A,B}`): canonical law
  `(1/2,1/2,0,0)`; the draw `A->0000, A->0100, B->1000` gives `(1/2,1/4,1/4,0)`.
  Over all 256 within-class draws, four distinct laws occur (only 64 reproduce the
  canonical one).
- Why the earlier tests missed it: every store they used had FULL SUPPORT, which
  saturates every projection (`pi_l(W) = GF(2)^l`), and a full projection cannot
  change. The tests passing was real but only sampled the saturated regime.
- Corrected statement: balanced invariance is UNCONDITIONAL; skewed invariance
  holds for every draw under SATURATION (a SUFFICIENT, not necessary, condition that
  full support meets) and fails otherwise. Verified over 128 exhaustive draws and
  12000 redraws across five codecs (`test_randomized_boundary`, `python/verification/{item2,saturation}.py`).

Lesson: a "computationally verified" claim is only as strong as the regime the tests
sample. Here the regime where the claim is true was exactly the regime the tests
populated.

### 2. `thm:realizable`: the local conditions are sufficient only for thin codecs

The realizable-set conditions (dyadic probability vector, mass `>=` codespace share,
the ladder) are necessary always. They are SUFFICIENT for the `{1,2,3,3}` codec (the
realizable set is exactly the eight laws they admit) but NOT in general. The codec
`{2,2,3,3,3,3}` has clean-but-unrealizable laws (e.g. `(1/4,1/4,1/4,1/4,0,0)`)
because of a HIT-GEOMETRY constraint: the length-3 hits `100,101` force
`pi_3(W) = {000,001,100,101}`, whose truncation `pi_2(W) = {00,10}` has dimension 1
and so misses the length-2 codeword `01` the law needs hit. The constructive
subspace-chain form is the only complete description; do not read the local
conditions as a full characterization.

### 3. The uniform vector is unreachable because of mass `>=` share, NOT the ladder

The uniform law is itself a flat (non-increasing) ladder, so the ladder admits it.
It is unreachable because it violates mass `>=` codespace share at the shortest
value: `q(A) = 1/4 < 2^{-1} = 1/2`. Mass-share is the clean general form of the
"`q(A)` is in `{1/2, 1}`" dimension constraint.

### 4. `thm:cogirth-graded` cascade: the later change-points are not the per-rung cogirths

The graded erasure cascade first changes the law at `d*_graded = min over hit rungs
of d*_rung(v)`. The SUBSEQUENT change-points are the cogirths of the progressively
REDUCED systems, not the original `{d*_rung(v)}`. In the witness the law changes at
3, 6, 9 while the per-rung cogirths are `9, 3, 3, 3` (6 is not among them). Only the
first change-point equals `min_v d*_rung(v)`.

### 5. (2026-06-09 fresh audit) The T3 rider overclaimed frequency-independence of the deviation

The T3 lemma's rider said the real per-build deviation is "independent of the storage
frequencies" with "no frequency-dependent term in the T5 error budget." The note's own
E2 data contradict that: delta is 0.0036 at 50/25/25 but 0.0190 at 99/0.5/0.5 with the
same support and codec, and T5b/T5c prove the mechanism (per-class redundancy = a
function of the multiplicities). Corrected to the gap-independence form: nothing in the
law or the deviation grows with the frequency GAP (E2: cross-profile distance sits at
the same-profile rebuild floor), but the deviation MAGNITUDE leaks per-class
redundancy: an observer can learn a class is thinly stored, never the frequency
vector's direction or shape.

### 6. (2026-06-09 fresh audit) The original T2 "span check" was vacuous; replaced by a raw gate

The old confirmation re-encoded the DECODED output before testing membership in `W`.
For a Kraft-tight codec whose canonical patterns all lie in `W`, that re-encoded
pattern lies in `W` for EVERY conceivable raw output (decoding erases exactly the
within-class bits where a violation would live), so the check could not fail and had
zero falsification power for the containment "reachable outputs subset W". The
falsifiable replacement is the `[span][raw]` gate (`test_prefix_codec.cpp`): it drives
the ribbon directly with canonical right-hand sides and asserts the UNDECODED M-bit
non-member output lies in `W`, where only 4 of 16 (above threshold) and 2 of 16
(sub-threshold) raw patterns do. The old checks are retained, rescoped as class-level
law checks. Same lesson as correction 1: a passing check is only as strong as what
could have made it fail.

### 7. (2026-06-09 fresh audit) Mechanism and precision fixes in T4/T4b

The T4b "class A is always hit" step was justified by the dimension of `C_1`, which is
non-probative (a length-1 codeword `1` with `W = {0}` has the same dimension and is
missed); the true mechanism is that A's codeword is all-zero, so `aligned(A) = 0` lies
in `W + C_1` for every `W` (T4c condition (c)). Also tightened: "non-member outputs
span W" (the span is over all keys; non-member outputs alone are only contained in
`W`); the T4 sharpness claim (the mass PROFILE is a step function of the rank; which
classes are hit depends on `pi(W)` itself); the ladder-vs-dimension scope (jointly
complete only for `{1,2,3,3}`, per T4c); and T4c gained an operational-scope note (the
canonical-subset image equals the subspace image for `{1,2,3,3}`, verified by
enumeration; contained in it in general).

### 8. (2026-06-09/10 second fresh audit) The randomized boundary is FULL SUPPORT, not saturation

This lemma has now been corrected twice. The original claim (skewed invariance in
general) was refuted by `{A,A,B}` (correction 1). The same-day patch (SATURATION,
every `pi_l(W)` full, is sufficient) is ALSO false: on `{2,2,2,3,3}` the saturated
store `{B,C,E}` has 16 of its 32 within-class draws change the law (the draw
`C -> 1010` collapses D from 1/8 to 0). A full `pi_l(W)` can owe its fullness to
SHORT generators' images, which the redraw moves. The correct boundary is FULL
SUPPORT (every value stored), proven by sibling contraction on the complete code
tree and confirmed across eight complete codes. Both wrong claims share one blind
spot: each was "verified" only on full-support stores, which are saturated, so the
test never entered the regime where the weaker condition fails. Gated by
`test_randomized_boundary.cpp` (3) and `python/verification/randomized_full_support.py`.

### 9. (2026-06-09/10) T5b "error duality" was a category error; it is a corruption budget

T5b claimed `floor((d*-1)/2)` corrupted stored equations are CORRECTABLE,
transporting the textbook decoding radius. That radius protects a codeword of a
code with minimum distance `d*`; here EVERY column multiset is a legal build, two
legal systems can differ in a single column, and no decoder (even knowing the true
column multiset) can identify which equations were corrupted. The claim is
withdrawn. What `d*` actually is, besides the erasure budget, is the exact
CORRUPTION (substitution) budget: control survives every substitution of fewer
than `d*` stored values, and `d*` well-chosen substitutions break it. Gated by a
new persistence/tightness check in `test_cogirth_robustness.cpp`.

### 10. (2026-06-09/10) T5c edge cases: pinned hit rungs and the balanced cascade length

Two T5c clauses were wrong at edges. (a) The per-rung threshold was ill-defined for
a saturated HIT rung (`rank pi_v(W) = 0`, `q(v) = 1`, the cascade's terminal
state): `(T5c.1)`'s max ranges over the empty functional set. Fixed with a PINNED
rung case (`d*_rung = infinity`, the rung never changes). (b) Claim (5) said the
balanced cascade "collapses to one change point"; it does not: the cascade runs
through ranks `k-1, ..., 0` (e.g. `{2,2,2,2}` at m=3 changes at 6 and again at 9
erasures). T5b describes only the FIRST step. Gated by a new pinned-rung check in
`test_cogirth_graded.cpp`.

## Scope ledger

### Proven (theorem, with a computational gate)

- T1/T2 (`thm:support`, `thm:idealized`): non-member output support is the stored
  span; the idealized law is uniform on it.
- T3 (`thm:freqindep`): the non-member law is independent of storage frequency.
- T4 (`thm:threshold`): sharp control threshold for the balanced codec,
  `rank pi|_W = log2 K`.
- T4b (`thm:graded`): the skewed codec is graded; mass is a non-increasing ladder.
- T4c (`thm:realizable`): the realizable set is exactly the image of the
  subspace-chain map (constructive, complete); local conditions necessary, codec-
  dependent sufficiency.
- T5b (`thm:cogirth`): the matroid cogirth is the exact balanced erasure budget,
  `>= (K/2) m_min` under full support.
- T5c (`thm:cogirth-graded`): the graded per-rung cogirth family; T5b is the
  single-rung collapse.
- `thm:randenc`: balanced invariance unconditional; skewed invariance under
  saturation, false otherwise.
- `thm:freqdist-ideal`: idealized FreqDist advantage is exactly zero.

### Measured (characterized, not a closed-form bound)

- T5: the real-band deviation `delta = TV(law_real, law_M1)` is small, scale-
  independent, and at or below the query-sampling floor (`0.00334` at `1e5` queries)
  up to `1e7` keys. This is an empirical characterization plus a labeled big-O.
- `thm:freqdist-real`: the per-observation real advantage is bounded by
  `delta(p0)+delta(p1)` (NO factor of 2; the earlier `2(...)` form multiplied the
  per-sample TV by the Adv convention factor and was corrected 2026-06-09), with
  `delta` measured as above. The binary control criterion it governs is the theorem
  T5b/T5c; the within-regime `delta` magnitude is the measured part.

### Open (declared)

- A structural closed-form bound on the MAGNITUDE of `delta` inside the intact
  regime, in terms of per-class redundancy.
- A clean NECESSITY characterization for randomized-encoding invariance (saturation
  is sufficient; necessity is false, but the exact boundary is not characterized).
- A sharper description of the hit-geometry object (which truncation-compatible
  subspace chains arise), beyond knowing the local conditions are insufficient.
- Out of perimeter by design: access-pattern, volume, and size leakage; dynamic
  insertion (the structure is static); the multi-instance coincidence oracle is
  reconciled, not defended in general.
