# Plan

## Section sketch (12-15pp target)

1. Introduction (1.5pp)
   - Static confidentiality is the wrong abstraction for deployed
     systems. Drift exists. Tuning becomes stale. Operational
     confidentiality must be maintained.

2. Background (1pp)
   - Cipher map basics; refer to cipher-maps paper.
   - Entropy ratio and homophonic prescription; refer to The Entropy
     Ratio.

3. Formal model: drift and staleness (2pp)
   - $D_t$ is a process. $K_t$ is the active allocation.
   - Define $\delta_t$ and $e_t$ as functions of time.
   - Define drift magnitude and staleness window.

4. Online observation and tuning (3pp)
   - Streaming observer (empirical $\hat D$ with smoothing).
   - Allocators (refer to experiments/tuning.py).
   - Retune cadence: naive, threshold, change-point.

5. Secret-preserving retune (3pp)
   - The retune algorithm (library extension).
   - Theorem: confidentiality of old cipher values under the new
     map. Bound via orbit closure of the joint cipher space.

6. Experiments (3pp)
   - Synthetic drift (Zipf alpha shift).
   - Real-corpus drift (TBD which dataset).
   - Cadence comparison.
   - Cost (retune budget vs $\delta$ trajectory).

7. Discussion (1pp)
   - Composition with rekeying.
   - Adversarial drift (open question).

8. Related work (1pp)
9. Conclusion (0.5pp)

## Order of work

1. Library feature (retune_k method) and tests.
2. Real-drift dataset selection and preprocessing.
3. Cadence experiments.
4. Theory: regret bounds, orbit-closure extension.
5. Drafting.

Estimated total: 1-2 months focused.
