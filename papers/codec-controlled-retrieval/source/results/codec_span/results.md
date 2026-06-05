# E1: Span-threshold experiment

Experiment E1 measures the non-member output distribution of
`encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>>` as a function of
the GF(2) rank of the stored canonical patterns, replicated across build seeds.
For each codec configuration we sweep the stored-value support to realize each
achievable rank, and at each rank run R = 20 replications (n_keys = 5000,
n_queries = 50000 non-members per draw), reporting the total-variation distance
between the observed non-member distribution and the codec's `codespace_share`
vector with a 95% normal-approximation confidence interval. `results.csv` holds
the raw output.

The data confirm the T4 sharp-threshold prediction: for the balanced codecs the
mean TV stays high (well above 0.1) for every rank below log2(K) and collapses to
near zero exactly at rank == log2(K). For `balanced_M4_K4` (K = 4, threshold rank
2) TV runs 0.75 at rank 0, 0.50 at rank 1, then drops to 0.0028 (CI upper bound
0.0034) at rank 2; storing a fourth distinct value leaves the rank at 2 (its
canonical pattern is GF(2)-dependent on the others) and TV stays near zero,
showing the controlling axis is the measured rank rather than the distinct-value
count. For `balanced_M8_K8` (K = 8, threshold rank 3) TV runs 0.875, 0.75, 0.50
at ranks 0, 1, 2 and drops to 0.0051 (CI upper bound 0.0056) at rank 3. The
skewed M = 4 codec (shares 1/2, 1/4, 1/4) has no clean power-of-two threshold;
its curve descends monotonically (0.50, 0.25, 0.0024) and reaches near-zero TV
once the stored patterns span the rank-2 codespace the code actually fills.
Below the threshold the confidence intervals are degenerate (lo == hi == mean):
the achievable non-member outputs lie in a fixed proper GF(2) subspace, so every
build seed yields the identical observed TV, and finite-sample query noise (hence
nonzero CI width) appears only at the threshold rank where the outputs fill the
codespace. The transition is therefore not merely sharp in the mean but
essentially deterministic in rank, which matches the theory.
