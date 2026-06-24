/**
 * @file codec_experiment.hpp
 * @brief Shared harness for codec-controlled non-member distribution
 *        experiments over encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>>.
 *
 * The research result this supports: for a ribbon-based encoded_retrieval,
 * the non-member output distribution is governed by the codec's codespace
 * allocation, and full codec control holds iff the GF(2) rank of the stored
 * canonical patterns reaches log2(K) (K = number of codec values). This
 * header provides the reusable measurement pieces:
 *
 *   - mean_ci(xs)                  normal-approximation confidence interval
 *   - measure_nonmember_dist(..)   one build: observed non-member distribution
 *   - measure_tv_to_codespace(..)  one trial: build + query + TV to codec
 *   - stored_rank(..)              GF(2) rank of distinct stored patterns
 *   - replicate(n, trial)          run a trial across seeds, return mean_ci
 *
 * Everything is deterministic given the seeds, so results are reproducible.
 * 4-space indent, 100-char lines, no em-dashes.
 */

#pragma once

#include <lapidary/codecs/prefix_codec.hpp>
#include <lapidary/detail/gf2.hpp>
#include <lapidary/retrieval/encoded_retrieval.hpp>
#include <lapidary/retrieval/ribbon_retrieval.hpp>

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <numeric>
#include <span>
#include <string>
#include <unordered_set>
#include <vector>

namespace lapidary::bench {

// Mean and a normal-approximation confidence interval over a sample.
//
//   mean +/- z * s / sqrt(n)
//
// where s is the sample standard deviation (n-1 denominator). If n < 2 the
// interval is degenerate: lo = hi = mean.
struct sample_stats {
    double mean;
    double lo;
    double hi;
};

inline sample_stats mean_ci(const std::vector<double>& xs, double z = 1.96) {
    const size_t n = xs.size();
    if (n == 0) {
        return {0.0, 0.0, 0.0};
    }
    double sum = std::accumulate(xs.begin(), xs.end(), 0.0);
    double mean = sum / static_cast<double>(n);
    if (n < 2) {
        return {mean, mean, mean};
    }
    double ss = 0.0;
    for (double x : xs) {
        double d = x - mean;
        ss += d * d;
    }
    double variance = ss / static_cast<double>(n - 1);
    double stddev = std::sqrt(variance);
    double half = z * stddev / std::sqrt(static_cast<double>(n));
    return {mean, mean - half, mean + half};
}

// Total-variation distance between two distributions over a shared index set:
//   TV(a, b) = 0.5 * sum_i |a_i - b_i|.
// The vectors must be the same length and indexed identically.
inline double total_variation_distance(const std::vector<double>& a,
                                        const std::vector<double>& b) {
    assert(a.size() == b.size() && "total_variation_distance: length mismatch");
    double tv = 0.0;
    const size_t n = a.size() < b.size() ? a.size() : b.size();
    for (size_t i = 0; i < n; ++i) {
        tv += std::abs(a[i] - b[i]);
    }
    return 0.5 * tv;
}

// GF(2) rank of the DISTINCT stored canonical patterns.
//
// Each distinct value in `stored` is mapped through codec.encode to its
// canonical (left-aligned) M-bit pattern; the rank of that pattern set over
// GF(2) is returned. Note the all-zero canonical pattern (assigned to the
// lexicographically first codeword) contributes no rank, so storing k
// distinct values typically yields rank k-1. That is expected: it is exactly
// the quantity that must reach log2(K) for full codec control.
template <unsigned M, typename V>
size_t stored_rank(const prefix_codec<V, M>& codec, const std::vector<V>& stored) {
    std::unordered_set<uint64_t> distinct_patterns;
    for (const V& v : stored) {
        distinct_patterns.insert(codec.encode(v));
    }
    std::vector<uint64_t> patterns(distinct_patterns.begin(), distinct_patterns.end());
    return lapidary::detail::gf2_rank(patterns);
}

// Build encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>> from
// (keys, stored) using build_seed, query n_queries deterministic non-member
// keys derived from query_seed, and return the OBSERVED non-member output
// distribution over `alphabet` (the normalized decoded-value counts).
//
// The alphabet is supplied explicitly: the distribution is over exactly these
// values (the support the codec was designed for). Non-member keys are
// "NM_<seed>_<index>" so distinct seeds give disjoint, reproducible streams.
// Counts are normalized over queries that decoded to an alphabet value; for a
// complete prefix code (Kraft == 1) every pattern decodes inside the alphabet
// so the denominator equals n_queries.
//
// Returns an empty vector (a sentinel) if the ribbon build fails, so a caller
// running replications can skip that draw.
template <unsigned M, typename V>
std::vector<double> measure_nonmember_dist(const prefix_codec<V, M>& codec,
                                           const std::vector<std::string>& keys,
                                           const std::vector<V>& stored,
                                           std::span<const V> alphabet,
                                           size_t n_queries,
                                           uint64_t build_seed,
                                           uint64_t query_seed) {
    using Enc = encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>>;

    auto built = typename Enc::builder(codec)
        .with_seed(build_seed)
        .add_all(std::span<const std::string>{keys}, std::span<const V>{stored})
        .build();
    if (!built.has_value()) {
        return {};
    }

    // Index each alphabet value to a dense position for tallying.
    std::vector<size_t> counts(alphabet.size(), 0);
    auto index_of = [&](const V& v) -> long {
        for (size_t i = 0; i < alphabet.size(); ++i) {
            if (alphabet[i] == v) return static_cast<long>(i);
        }
        return -1;
    };

    std::string seed_tag = "NM_" + std::to_string(query_seed) + "_";
    size_t total_in_alphabet = 0;
    for (size_t i = 0; i < n_queries; ++i) {
        V decoded = built->lookup(seed_tag + std::to_string(i));
        long idx = index_of(decoded);
        if (idx >= 0) {
            counts[static_cast<size_t>(idx)]++;
            ++total_in_alphabet;
        }
    }

    std::vector<double> observed(alphabet.size(), 0.0);
    double denom = total_in_alphabet > 0 ? static_cast<double>(total_in_alphabet)
                                         : static_cast<double>(n_queries);
    for (size_t i = 0; i < alphabet.size(); ++i) {
        observed[i] = static_cast<double>(counts[i]) / denom;
    }
    return observed;
}

// One trial. Builds the structure (via measure_nonmember_dist) and returns the
// total-variation distance between the observed non-member distribution and the
// codec's codespace_share vector over `alphabet`.
//
// Returns -1.0 (a sentinel) if the ribbon build fails, so a caller running
// replications can skip that draw.
template <unsigned M, typename V>
double measure_tv_to_codespace(const prefix_codec<V, M>& codec,
                               const std::vector<std::string>& keys,
                               const std::vector<V>& stored,
                               std::span<const V> alphabet,
                               size_t n_queries,
                               uint64_t build_seed,
                               uint64_t query_seed) {
    std::vector<double> observed = measure_nonmember_dist<M>(
        codec, keys, stored, alphabet, n_queries, build_seed, query_seed);
    if (observed.empty()) {
        return -1.0;
    }

    std::vector<double> predicted(alphabet.size(), 0.0);
    for (size_t i = 0; i < alphabet.size(); ++i) {
        predicted[i] = codec.codespace_share(alphabet[i]);
    }

    return total_variation_distance(observed, predicted);
}

// Run `trial(rep_index)` for rep = 0 .. n_reps-1, collect the non-sentinel
// results (< 0 is treated as a failed/skipped draw), and return mean_ci over
// them. If every draw was a sentinel the result is a degenerate {0,0,0}.
inline sample_stats replicate(size_t n_reps, const std::function<double(uint64_t)>& trial) {
    std::vector<double> samples;
    samples.reserve(n_reps);
    for (uint64_t rep = 0; rep < n_reps; ++rep) {
        double v = trial(rep);
        if (v >= 0.0) {
            samples.push_back(v);
        }
    }
    return mean_ci(samples);
}

}  // namespace lapidary::bench
