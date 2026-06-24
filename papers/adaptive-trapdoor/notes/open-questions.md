# Open Questions Blocking Publication

These are the items that must be resolved before the paper can be
written up.

## 1. Secret-preserving retune (library)

Currently the experiments rebuild the cipher map from scratch on
every retune step. A real deployed system cannot do that without
invalidating already-emitted cipher values. The fix:

- Add `PHFCipherMap.retune_k(new_k_input_fn)` to cipher-maps.
- The method preserves `enc_key`, `decode_secret`, `scramble_key`.
- It rebuilds the PHF and slot table for the new (x, rep) keys.
- Old cipher values, encoded with the old $K(x)$, must still
  decode under the new map (their (x, rep) keys are still valid).

Theoretical question: does retuning preserve confidentiality
guarantees on old cipher values? (The new cipher map can decode
them, but does the orbit-closure bound apply to the union of old
and new cipher spaces?)

Estimated work: 1-2 days for the library feature, plus 1 week to
work out the information-theoretic accounting.

## 2. Real distribution drift datasets

Synthetic Zipf-shift is an existence proof. Reviewers will ask for
real corpus drift. Candidates:

- 20 Newsgroups split by topic (induced drift across categories).
- Reddit comments split by month or year.
- Query logs with explicit timestamps (AOL? MSN? a more recent log?).
- News article frequencies by day (Wikipedia pageviews? Common
  Crawl?).

For each, characterize: drift rate (KL divergence over time),
stationarity assumption, vocabulary stability.

## 3. Retune cadence theory

When should retuning fire?

Options:
- Every batch (naive, expensive).
- Threshold on $\TV(\hat D_t, \hat D_{t-k})$.
- Adaptive doubling-period schedules.
- Sequential change-point detection (CUSUM, online Bayes).

Need: regret bound. If we retune at times $t_1, t_2, \ldots$, what
is the average $\delta$ over time? How does it depend on the cadence
strategy and the drift process?

## 4. Adversarial drift

The paper threat model assumes natural drift. But an adversary may
deliberately shift its query pattern to widen the staleness window.
- Is this a meaningful attack? Quantify the leakage.
- Is the defence the same (faster retuning) or different (drift-
  detection that distinguishes natural vs adversarial)?

This may be a separate follow-on paper.

## 5. Composition with secret rotation

If both rekeying (`papers/cipher-rekeying/`) and retuning happen,
do they compose? When?
- A retune that does not change the secret is straightforward.
- A rekey that does not change $K(x)$ is straightforward.
- Doing both at once: order matters?
