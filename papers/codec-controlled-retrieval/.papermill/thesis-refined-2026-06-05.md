# Thesis (refined, 2026-06-05)

## One-sentence thesis

The values an XOR (ribbon) retrieval structure returns for non-member keys are not
arbitrary junk: they are uniform over the GF(2) span of the stored codewords, so a
public codec (not the private data) determines that distribution, exactly when the
stored values span the codec's class quotient, which hands a static data structure
the frequency-hiding property that online encrypted-database defenses pay for per
query.

## The contribution, sharpened

The retrieval-structures literature (Bloomier, ribbon/BuRR, XOR, binary-fuse) is
unanimous on one point and silent on another. Unanimous: for a key in the stored
set, the structure returns its value in near-optimal space. Silent: for a key NOT
in the set, the structure returns "an arbitrary value", "junk", a don't-care. This
paper fills exactly that silence, and shows the silence was hiding a designable,
provable object.

Three tiers, stated honestly:

- (A, baseline, cited not claimed) That a value codec's codespace allocation can
  shape a non-member output distribution is known: it is the author's own
  bernoulli_maps result for a random-oracle construction, and the
  distribution-transforming-encoder idea behind Honey Encryption.
- (B, novel) The same control survives the move to a GF(2)-LINEAR retrieval
  structure, where the non-member output is a XOR of solution rows constrained to a
  linear subspace, not a fresh uniform hash. Uniformity is no longer assumed; it is
  a theorem about the row space, and it can fail.
- (C, headline) It fails or holds by a SHARP THRESHOLD: codec control holds iff the
  stored codewords span the codec's class quotient over GF(2), rank pi|_W = log2 K,
  a step function of an integer rank with no graded regime. Below it, whole codec
  classes receive exactly zero probability; at it, the public codec shares are
  realized exactly.

## The security claim (the "so what")

Because the span depends only on WHICH values are stored, never on HOW OFTEN, the
non-member output channel is provably independent of storage frequency. Formalized
as a distinguishing game (FreqDist): an adversary with oracle access who queries
non-members has advantage exactly zero in the idealized model, and at most twice a
small, measured, scale-independent deviation in the real construction. This is
STRUCTURAL frequency-hiding: a property of the static bytes, with zero per-query
cost, where PANCAKE/FSE pay bandwidth or re-encoding online. It is the concrete
linear-retrieval instantiation that the cipher-maps abstraction (random-oracle and
RecSplit backends only) does not contain.

## What this paper is NOT claiming

- Not claiming the abstract codec-output law as new (tier A is cited).
- Not a general confidentiality result: it defends the value-frequency channel of
  non-member outputs, not access-pattern or volume leakage, and not the
  multi-instance coincidence oracle (a different game, defeated by the opposite
  codec choice, which the paper reconciles rather than hides).
- Not an online/dynamic guarantee: the structure is static.

## Novelty in one line (for the abstract and the related-work opener)

We turn a uniformly-acknowledged "non-member output is arbitrary" into a
characterized, codec-designable distribution governed by a sharp GF(2)-span
threshold, and read off a structural, zero-per-query-cost frequency-hiding
property as the consequence.
