# Experiment Batch E1 + E3 + E4 (2026-05-23 design)

Three experiments to close the empirical-rigor surface for §10 of the
cipher-maps paper.  Designed to be executable independently; each has
explicit success criteria and incorporation-vs-cut thresholds so the
decision to include results in the paper is mechanical, not aesthetic.

**Status**: design landed 2026-05-23.  E1 script drafted in this
directory; E3 and E4 to be implemented by extending bernoulli
experiments 14 and 15 with replicate loops.

**Execution order**: E3 first (validates §10.6 before E4 builds on it),
then E4, then E1 (independent).

**Output convention**: each experiment writes `results.csv` and a
`summary.md` to its own subdirectory.

---

## E1: Bloom-filter baseline at matched FPR

**Hypothesis**: Cipher set space cost is within a small constant
factor of the optimal Bloom filter at matched per-document
false-positive rate.  Two regimes:

- *Theoretical lower bound*: when the cipher Boolean cell stores only
  the region tag (~2 bits for True/False/Noise), bits/element is
  `PHF_bits_per_key + 2 ≈ 5` at typical PHF efficiency, comparable to
  or slightly better than Bloom's `1.44 · log_2(1/ε) ≈ 6.2` at
  `ε = 0.05`.
- *Practical implementation*: when the cell stores the full `n_bits`
  cipher value (typical PHF + slot construction), bits/element is
  `PHF_bits_per_key + n_bits ≈ 3 + 8 = 11` at `n_bits = 8`,
  approximately 2× Bloom.

The experiment measures both, gives an honest accounting of the cost
of choosing one over the other.

### Variables
- *Independent*: corpus size `m ∈ {1000, 5000, 18266}` (20 Newsgroups),
  target FPR `ε ∈ {0.01, 0.05, 0.10}`
- *Dependent*: cipher-set bits/element (theoretical + practical),
  Bloom bits/element (theoretical + practical via Python implementation),
  ratio of practical, ratio of theoretical, measured FPR vs target
- *Controlled*: corpus (20 Newsgroups), tokenization (`[a-zA-Z]+`,
  lowercase), test query set (5000 held-out random terms not in the
  document's vocabulary), hash function (SHA-256 truncated)

### Methodology
1. Load 20 Newsgroups via sklearn; tokenize lowercase alphabetic.
2. Take first `m` documents; for each, extract token vocabulary.
3. For each `(m, ε)`:
   - **Cipher set build**: choose `n_bits = ceil(log_2(1/ε)) + 2`
     (gives partition granularity for `p_T = ε`); build PHF over
     vocabulary using phobic; for each slot, store the cipher Boolean
     cell (True for member, slot left as random for non-members).
   - **Bloom build**: choose `(k, mbits)` for optimal Bloom at target
     `ε` given vocabulary size; hand-roll the Bloom filter (Python set
     of bit positions to keep dependencies light).
4. Measure space three ways per construction:
   - *Theoretical info-bound*: cipher set
     `(1.18 + ceil(log_2(3)))` bits/element = ~3 bits/element with
     region-tag storage; Bloom `1.44 · log_2(1/ε)` bits/element
   - *Practical theoretical*: cipher set
     `(PHF_bits_per_key + n_bits)` bits/element; Bloom
     `1.44 · log_2(1/ε)` bits/element
   - *Serialized bytes*: actual disk size of the constructed object
     divided by element count
5. Verify empirical FPR: 5000 held-out queries per document; report
   measured FPR vs target.
6. Aggregate across documents at each `(m, ε)`: mean, std of each
   measurement.

### Success criteria
- *Strong include* (favorable): practical ratio ≤ 2.5 across all `(m, ε)`
  → §10.3 augmented with comparison row claiming "space-comparable to
  Bloom with totality, frequency-hiding, and composition as additional
  capabilities"
- *Honest include* (cost-of-trapdoor): practical ratio 2.5-5 → §10.3
  augmented with comparison row framing the cost honestly; §9
  limitations note discusses the trade-off
- *Discuss-only* (unfavorable): practical ratio > 5 → don't add to
  §10.3; mention in §10.5 future-work as "implementation overhead is
  significant; theoretical lower bound is competitive"
- *Bonus*: identify if the theoretical lower bound is achievable in
  practice (e.g., via region-tag-only storage); if yes, suggest as a
  future optimization
- *Closes*: R5 MIN-6, R6 MIN-6, R7 methodology-auditor (likely)

### Effort
Half-day.  Script in `e1_bloom_baseline.py` (this directory).

---

## E3: Replicated codec-security study

**Hypothesis**: The §10.6 single-run results are robust to replicate
noise; the Le Cam upper bound is empirically realized to within
sampling noise across all `(codec, t)` cells.  Specifically, for at
least 28/30 cells, the theoretical prediction
`1 - 1/2 · Σ α(y)^t` lies inside the empirical Wilson 95% CI computed
from 10 replicates × 5000 queries per class per cell.

### Variables
- *Independent*: codec ∈ {Dense(n=4), Padded(n=4, default=v0),
  Padded(n=4, default=v7), Huffman(n=4), Huffman(n=5), AntiHuffman(n=5)},
  t ∈ {1, 2, 3, 4, 5}
- *Dependent*: empirical attacker accuracy per cell (mean across 10
  replicates), Wilson 95% CI from pooled trials, gap from theoretical
  prediction (`1 - 1/2 · Σ α(y)^t`)
- *Controlled*: `|S| = 2000`, `|Y| = 8`, `n_eval = 5000` queries per
  class per cell, value distribution Zipf(s=1.2) over |Y|=8
- *New vs §10.6*: 10 replicates per cell (vs current 1 run); fresh
  RNG seeds per replicate; build sets resampled per replicate

### Methodology
1. Reuse `bernoulli/src/bernoulli/experiments/14_coincidence_oracle.py`
   per-cell evaluation.
2. Wrap in a 10-iteration loop with reseeded RNG per iteration.
   Resample both the build set `S` and the evaluation query set per
   replicate.
3. Per cell, compute:
   - *Per-replicate accuracy*: 5000 evaluation queries → attacker
     correctness count
   - *Mean accuracy across 10 replicates*: average per-replicate
     accuracy
   - *Wilson 95% CI*: from pooled 10·5000·2 = 100,000 trials
     (member + filler classes combined at balanced prior)
   - *Theoretical prediction*: `1 - 1/2 · Σ_y α(y)^t` from
     Theorem 8.1
   - *Gap*: empirical mean - theoretical prediction
   - *Prediction in CI*: True iff `theoretical_prediction ∈ Wilson_CI`
4. Tabulate: 6 codecs × 5 t-values × {mean, CI_low, CI_high, gap,
   in_CI} = 30 rows × 5 columns.
5. Aggregate: count of cells with `in_CI = True`, mean absolute gap
   across all cells, max absolute gap.
6. Plot (optional): predicted vs empirical accuracy across codecs and
   t-values, with error bars; the line `y = x` for visual reference.

### Success criteria
- *Strong include* (≥ 28/30 in CI): §10.6 Table 1 augmented with mean
  and CI columns; "tight up to sampling noise" claim retained, now
  empirically supported by replicates; methodology-auditor critique
  closed
- *Weak include* (24-28/30): present results honestly; identify which
  cells deviate and why (likely AntiHuffman at large t, where the sum
  is tiny and sampling noise dominates the absolute gap); reframe §10.6
  as "matches in 24+ of 30 cells; the deviations are at sampling-noise
  scale (`|gap| < 0.01` in all cases)"
- *Cut & re-investigate* (< 24/30): theorem-vs-empirical gap is wider
  than the single-run paper claimed; possibly the homogeneity
  assumption is being violated, or the seed-independence assumption is
  weaker than claimed for the bernoulli construction; needs deeper
  analysis before publishing
- *Closes*: R5/R6/R7 methodology-auditor "single run, no replicates"
  critique

### Effort
~1 day (~30 cells × 10 replicates × 5000 queries each ≈ 1.5M
evaluations; bernoulli source runs fast on a laptop).

### Implementation outline
```python
# bernoulli/src/bernoulli/experiments/14b_coincidence_oracle_replicated.py
import random
from collections.abc import Callable

CODECS = ["Dense(n=4)", "Padded(n=4, v0)", "Padded(n=4, v7)",
          "Huffman(n=4)", "Huffman(n=5)", "AntiHuffman(n=5)"]
T_VALUES = [1, 2, 3, 4, 5]
N_REPLICATES = 10

def run_cell(codec_name: str, t: int, seed: int) -> tuple[int, int]:
    rng = random.Random(seed)
    # ... build cipher map per codec, run 5000 queries per class,
    # ... return (n_correct, n_total)
    pass

def wilson_ci(successes: int, trials: int, z: float = 1.96) -> tuple[float, float]:
    # standard Wilson score interval; closed form
    p = successes / trials
    denom = 1 + z**2 / trials
    center = (p + z**2 / (2*trials)) / denom
    halfwidth = z * (p*(1-p)/trials + z**2/(4*trials**2))**0.5 / denom
    return (center - halfwidth, center + halfwidth)

for codec in CODECS:
    for t in T_VALUES:
        cum_correct, cum_total = 0, 0
        per_rep = []
        for rep in range(N_REPLICATES):
            seed = hash((codec, t, rep)) & 0xFFFFFFFF
            c, n = run_cell(codec, t, seed)
            cum_correct += c
            cum_total += n
            per_rep.append(c / n)
        mean = sum(per_rep) / len(per_rep)
        ci_lo, ci_hi = wilson_ci(cum_correct, cum_total)
        prediction = theoretical_accuracy(codec, t)
        in_ci = ci_lo <= prediction <= ci_hi
        gap = mean - prediction
        # write row to CSV
```

---

## E4: Randomized-encoding defense validation (multi-instance, multi-K)

**Hypothesis**: Proposition 8.2's predictions hold empirically across a
`K(x)` sweep.  Three sub-hypotheses:

- **H1** (pattern-coincidence under randomized): member coincidence
  rate decays as `1/κ^(t-1)` where `κ = K(x)`, within sampling error
- **H2** (decode-coincidence under randomized): unchanged from
  canonical encoding (invariant under `K`)
- **H3** (Dense saturation): no defense benefit when `K(x)` cannot
  increase (codespace already saturated)

### Variables
- *Independent*: `K(x) ∈ {1, 2, 4, 8, 16}`, `t ∈ {2, 3, 4, 5}`,
  codec ∈ {Huffman(n=4), Huffman(n=5), Dense(n=3), Dense(n=4)}
- *Dependent*: pattern-coincidence accuracy (mean + Wilson CI),
  decode-coincidence accuracy (mean + Wilson CI), gap from
  Proposition 8.2 prediction for each attacker
- *Controlled*: `|S| = 1000`, `|Y| = 8`, `n_eval = 5000` per class per
  cell, value distribution Zipf(s=1.2)
- *New*: 5 replicates per cell; `K(x)` sweep at 5 levels (vs current
  empirical study at 1-2 K levels)

### Methodology
1. Reuse `bernoulli/src/bernoulli/experiments/15_randomized_encoding.py`
   setup.
2. Extend K-sweep to {1, 2, 4, 8, 16}; for each value, ensure the codec
   has enough codespace slack to accommodate (Dense partitions may
   bottom out at K=1, which is the H3 boundary).
3. For each `(codec, K, t)`:
   - Build cipher maps with the specified codec and `K(x)` (uniform
     across all `x` for simplicity)
   - Run both pattern-coincidence and decode-coincidence attackers on
     the same underlying data (shared queries, different attacker
     algorithms)
   - 5 replicates per cell, each with fresh seeds
4. Per cell, compute:
   - *Empirical pattern-coincidence accuracy*: mean + Wilson CI
   - *Empirical decode-coincidence accuracy*: mean + Wilson CI
   - *Theoretical pattern prediction*: `1 - 1/2 · (1/κ)^(t-1)` for
     homogeneous κ at balanced prior (approximation; exact form is
     more complex per Proposition 8.2)
   - *Theoretical decode prediction*: `1 - 1/2 · Σ_y α(y)^t` from
     Theorem 8.1
   - *Gap from each prediction*: empirical - theoretical
   - *Sub-hypothesis verification*:
     - H1: pattern accuracy decreases monotonically with K at fixed
       (codec, t), and gap from prediction is sampling-noise-scale
     - H2: decode accuracy is flat across K at fixed (codec, t),
       within sampling noise
     - H3: for Dense at the saturation boundary (e.g., Dense(n=3) with
       |Y|=8 has K_max = 1), pattern accuracy at K > 1 falls back to
       the K=1 value (i.e., randomized encoding is forbidden by
       codespace)
5. Tabulate: 4 codecs × 5 K-values × 4 t-values × {pattern, decode}
   × {mean, CI, gap, prediction-in-CI} = 80 rows × ~7 columns.
6. Plot: pattern-coincidence accuracy vs K for each (codec, t) family;
   include theoretical curve and empirical error bars; decode-coincidence
   should be a flat line per (codec, t) family.

### Success criteria
- *Strong include* (H1 + H2 + H3 all hold within CI):
  - New §10.7 subsection "Randomized-Encoding Defense at Scale"
  - Two figures: pattern-coincidence decay with K; decode-coincidence
    invariance
  - V4 thesis's randomized-encoding-as-defense claim is empirically
    validated; the public-codec vs private-codec threat-model
    distinction is empirically distinguishable
- *Partial include* (H1 holds but H2 or H3 fails):
  - Include the H1 part with caveat; the failure of H2 or H3 indicates
    Proposition 8.2's threat-model boundary is more complex than
    stated
  - Revisit Proposition 8.2 in light of the failure pattern
- *Cut & re-investigate* (H1 fails):
  - Proposition 8.2's saturation assumption may be wrong for the
    construction being tested
  - Don't add §10.7; mark as future work
  - Consider weakening the v4 thesis claim about randomized encoding
- *Bonus signal*: identify the K(x) "knee" beyond which defense
  saturates (decreasing returns); this informs deployment recommendation
  (e.g., "K(x) = 8 captures most of the defense benefit; further
  multiplicity yields diminishing returns")

### Effort
1-2 days (~80 cells × 5 replicates × 5000 queries each ≈ 2M
evaluations; modest compute).

---

## Combined incorporation decision tree

After all three experiments are run, evaluate against:

| Result pattern | Action |
|---|---|
| All strong include | §10.3 augmented with E1, §10.6 augmented with E3, new §10.7 from E4; paper grows to ~38pp; multi-instance defense story empirically airtight |
| E3 strong + E4 strong + E1 honest | §10.3 augmented with honest framing of cipher-set vs Bloom cost; §10.6 + §10.7 as above |
| E3 weak + others strong | Honest report of §10.6 weak cells; current "matches to within sampling noise" claim downgraded to "matches in 24+ of 30 cells with deviations at sampling-noise scale" |
| E4 cut + others strong | Don't add §10.7; v4 thesis's randomized-encoding claim is empirical-fragile; weaken from "validates Proposition 8.2 empirically" to "Proposition 8.2 predicts X; empirical validation is future work" |
| E1 unfavorable + others fine | Include with honest framing; the trapdoor cost is real, justified by capabilities |
| Anything else | Decide case-by-case |

---

## Required resources

**Data**: 20 Newsgroups (already available via sklearn); synthetic Zipf
distributions over `|Y| = 8` for codec-security work.

**Code**:
- `e1_bloom_baseline.py` (this directory; drafted): self-contained
- `bernoulli/src/bernoulli/experiments/14b_coincidence_oracle_replicated.py`
  (to be drafted by extending Experiment 14 with replicate loop)
- `bernoulli/src/bernoulli/experiments/15b_rand_encoding_sweep.py`
  (to be drafted by extending Experiment 15 with K-sweep)

**Compute**: All three runnable on a laptop in single-digit hours.

**Library dependencies**:
- E1: `phobic` (PHF), `scikit-learn` (20NG), Python stdlib
- E3/E4: existing bernoulli package + Python stdlib

**Output convention**: each experiment writes
`.papermill/experiments/2026-05-23/eN/{results.csv, summary.md}`.

---

## Author

Alexander Towell, designed 2026-05-23.
