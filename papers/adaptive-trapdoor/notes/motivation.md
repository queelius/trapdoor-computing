# Motivation

## The static-confidentiality hole

The Entropy Ratio paper assumes a fixed query distribution $D$. The
homophonic prescription $K(x) = \lceil c \cdot D(x) \rceil$ is
optimal at design time. But:

- Vocabulary changes over time. New terms appear; old terms fall out
  of use.
- Per-user distributions differ from population distributions and
  are unknown at design time.
- Concept drift: even at fixed vocabulary, the popularity ordering
  shifts (news topics, seasonal patterns, query trends).
- Threat surface shifts: an adversary may probe more frequently
  along an axis the system was not tuned for.

A $K(x)$ tuned for $D_0$ is mismatched against $D_t$. Confidentiality
$e$ drops. The system was secure when deployed but is no longer
secure now.

## What this paper says

Operational confidentiality is a maintained property, not a delivered
one. The trusted machine must:

1. Observe the query stream and estimate $\hat{D}$.
2. Detect when $\hat{D}$ has drifted enough to warrant retuning.
3. Retune $K(x)$ from the current estimate.
4. Apply the retuning without invalidating already-emitted ciphertext.

Each step has a cost (observation budget, decision threshold, retune
overhead, cryptographic care).

## Why now

The cipher-maps Python library and its experiments harness
(2026-04-29) make the empirical work tractable: the observer,
allocator strategies, and online loop already exist as
`experiments/online_adaptation.py`. Preliminary results show that
the phenomenon is real and quantifiable, and they identify the
specific blocker (no secret-preserving retune in the library).

## Sibling/contrast

- Cipher rekeying (`papers/cipher-rekeying/`) addresses secret
  rotation: the secret changes, latent values stay, $K(x)$ stays.
- Adaptive trapdoor (this paper) addresses allocation retuning: the
  secret stays, latent values stay, $K(x)$ changes.

Both can compose. A deployed system may rotate keys quarterly and
retune $K(x)$ daily.
