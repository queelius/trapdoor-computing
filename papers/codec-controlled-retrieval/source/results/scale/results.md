# E3: Deviation-vs-scale sweep (T5 characterization data)

Experiment E3 characterizes how the non-member output distribution of
`encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>>` deviates from the
idealized uniform-on-W law (theorem T1) as a function of the number of stored
keys N. The idealized T1 assumes the ribbon query acts exactly uniformly on W
(the span of the stored canonical patterns); the real ribbon band is only
near-uniform, so the actual non-member distribution deviates slightly. Above
the span threshold "uniform on W" coincides with the codec's codespace shares,
so this deviation is exactly what `measure_tv_to_codespace` reports (the
total-variation distance between the observed non-member distribution and the
codec's `codespace_share` vector). We fix ONE above-threshold configuration:
the balanced M = 8, K = 8 codec (length-3 codewords, equal codespace shares
1/8) storing all 8 distinct values (V(i mod 8) on row i), whose stored
canonical patterns span a rank-3 = log2(8) GF(2) subspace at every N. For each
N in {1e4, 1e5, 1e6, 1e7} we build the ribbon-backed retrieval across R build
seeds (R = 10 for N <= 1e5, 5 for N = 1e6, 3 for N = 1e7, reduced at large N
because a 10M-key ribbon build takes about 30 s) and query 100000 non-members
per build, reporting mean TV with a 95% normal-approximation confidence
interval. `results.csv` holds the raw output; the full sweep ran in under 3
minutes wall clock (peak RSS about 1.7 GB at 10M).

The deviation stays small and essentially FLAT across four orders of magnitude
of N, consistent with the historical sub-3% anchor. Mean TV is 0.0035 at
N = 1e4, 0.0031 at N = 1e5, 0.0035 at N = 1e6, and 0.0028 at N = 1e7. It does
NOT grow with N; if anything it drifts weakly downward (0.0035 to 0.0028 from
1e4 to 1e7), and all four confidence intervals overlap, so the honest
characterization is "flat, possibly weakly shrinking" rather than a clean
monotone trend. The deviation never approaches the 0.1 scale that would signal
a breakdown of codec control, and the 10M point in particular is well behaved:
the ribbon's epsilon auto-scaling (which grows the band as N increases to keep
large systems solvable) does not degrade the codespace-control property, so the
near-uniformity of the real band holds at scale. For the T5 real-incidence
deviation characterization this means the gap between the idealized uniform-on-W
law and the real ribbon band is a small, N-stable constant (order 0.003 in
TV for this codec) rather than a quantity that erodes the codespace-control
guarantee as the stored set grows.
