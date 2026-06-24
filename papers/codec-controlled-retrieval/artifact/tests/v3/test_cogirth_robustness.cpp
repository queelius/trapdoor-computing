/**
 * @file test_cogirth_robustness.cpp
 * @brief T5b: the matroid COGIRTH of the stored column system governs the
 *        ROBUSTNESS of codec control under adversarial key erasure.
 *
 * This is the computational gate for the T5b subsection of
 * docs/codec_controlled_retrieval.md. T4 proved that codec control holds iff the
 * stored canonical patterns reach GF(2) rank log2 K (transversality, rank pi|_W =
 * log2 K). T5b asks the dual robustness question: how many stored keys may an
 * adversary erase before that rank, and with it codec control, collapses.
 *
 * Setup (T4 balanced scope). Balanced codec, K = 2^k classes, value quotient
 * Q = GF(2)^k, projection pi onto the top k codeword bits. For the left-aligned
 * balanced prefix_codec, pi(canonical(v)) is just v's k-bit value pattern. The
 * STORED COLUMN SYSTEM over Q has one column g_x = pi(canonical(value(x))) per
 * stored KEY x, WITH MULTIPLICITY: a value stored m times contributes m identical
 * columns. By T4, control holds iff the surviving columns have rank k over Q.
 *
 * The invariant. d* = the matroid COGIRTH of that column system = the minimum
 * number of columns (counting multiplicity) whose deletion drops the rank below
 * k. Closed form:
 *
 *     d* = (total columns) - max over hyperplanes H of Q of (columns lying in H).
 *
 * A hyperplane of Q = GF(2)^k is the kernel of a nonzero dual vector a; there are
 * 2^k - 1 of them, and a column g lies in ker(a) iff <g, a> = 0 (XOR-parity zero).
 *
 * The theorem (transport through the sharp T4 step):
 *   (1) deleting fewer than d* stored keys leaves rank = k for EVERY deletion
 *       (control intact, TV at the floor); deleting d* well-chosen keys drops the
 *       rank by one and steps control to the T4 BROKEN regime, where the broken
 *       value is exactly the T4 step TV = 0.5 for the K' = K/2 collapse. So d* is
 *       the exact, tight, adversarial erasure budget.
 *   (2) d* is ALSO the exact CORRUPTION (substitution) budget: control survives
 *       every corruption of fewer than d* stored keys' values, and d* well-chosen
 *       substitutions (into a maximizing hyperplane) break it. (An earlier
 *       "floor((d*-1)/2) errors correctable" claim was withdrawn: no code
 *       constraint anchors decoding here; see the note's CORRECTION 2026-06-09.)
 *   (3) d* >= (K/2) * m_min, where m_min is the minimum per-class store count.
 *       This LOWER-BOUNDS the cogirth by per-class redundancy and converts the
 *       previously-open T5 m_min conjecture into a theorem.
 *
 * Verified instances (this file):
 *   - Full K-value support, uniform multiplicity m: d* = (K/2) * m exactly.
 *     For M = 8, K = 8 (k = 3), m = 10, n = 80 keys: d* = 80 - 40 = 40.
 *   - Basis support (k independent values, m each): d* = m.
 *   - The broken-step TV at r = d* is exactly 0.5 (the T4 step).
 *   - A NON-UNIFORM full-support profile binds d* = (K/2) * m_min when the K/2
 *     thinnest stacks lie outside the maximizing hyperplane.
 *
 * CRITICAL: the invariant is defined over the stored MULTISET (with
 * multiplicities). Without multiplicity the budget cannot see per-class
 * redundancy (a class stored a thousand times and one stored once contribute the
 * same single column), so the count would be a function of the support alone.
 * With multiplicities, d* is a genuinely new number (= (K/2) m for the grid,
 * = m for a basis), distinct from log2 K.
 *
 * Measurement reuses benchmarks/codec_experiment.hpp (TV-to-codespace). 4-space
 * indent, 100-char lines, no em-dashes.
 */

#include <catch2/catch_test_macros.hpp>

#include "../../benchmarks/codec_experiment.hpp"

#include <lapidary/codecs/prefix_codec.hpp>
#include <lapidary/detail/gf2.hpp>
#include <lapidary/retrieval/encoded_retrieval.hpp>
#include <lapidary/retrieval/ribbon_retrieval.hpp>

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>
#include <span>
#include <string>
#include <unordered_set>
#include <vector>

using namespace lapidary;

namespace {

enum class V : uint8_t { V0 = 0, V1, V2, V3, V4, V5, V6, V7 };
constexpr unsigned M = 8;
constexpr unsigned K = 8;  // codec classes
constexpr unsigned k = 3;  // log2 K

using Codec = prefix_codec<V, M>;

// The balanced length-3 codec: 8 classes, share 1/8 each. With canonical
// left-aligned assignment the top 3 bits of value i equal i, so pi(canonical(Vi))
// = i in Q = GF(2)^3. Default V0.
Codec make_codec() {
    return Codec({{V::V0, 3}, {V::V1, 3}, {V::V2, 3}, {V::V3, 3},
                  {V::V4, 3}, {V::V5, 3}, {V::V6, 3}, {V::V7, 3}}, V::V0);
}

constexpr std::array<V, 8> ALPHABET = {V::V0, V::V1, V::V2, V::V3,
                                       V::V4, V::V5, V::V6, V::V7};

// The Q-vector (top-k bits of the canonical pattern) of a value.
uint32_t qvec(const Codec& codec, V v) {
    return static_cast<uint32_t>(codec.encode(v) >> (M - k));
}

// Deterministic distinct 16-byte member keys.
std::vector<std::string> gen_keys(size_t n, uint64_t seed = 42) {
    std::vector<std::string> out;
    out.reserve(n);
    std::mt19937_64 rng{seed};
    std::uniform_int_distribution<int> b(0, 255);
    std::unordered_set<std::string> seen;
    while (out.size() < n) {
        std::string s(16, '\0');
        for (auto& c : s) c = char(b(rng));
        if (seen.insert(s).second) out.push_back(std::move(s));
    }
    return out;
}

// GF(2) rank of the DISTINCT surviving stored canonical patterns = rank(pi|_W)
// for the surviving support (by T4, pi injective on W for the left-aligned codec).
size_t surviving_rank(const Codec& codec, std::span<const V> stored_values) {
    std::unordered_set<uint64_t> distinct;
    for (const V& v : stored_values) distinct.insert(codec.encode(v));
    std::vector<uint64_t> pats(distinct.begin(), distinct.end());
    return detail::gf2_rank(pats);
}

// Matroid cogirth d* of the stored column multiset over Q. Columns = one
// Q-vector g_v per stored KEY (multiplicity mult[i] for distinct value
// distinct_values[i]). Returns d* = total - max over hyperplanes of (columns in
// H), or 0 if the support is already below full rank (control already broken).
size_t cogirth(const Codec& codec,
               const std::vector<V>& distinct_values,
               const std::vector<size_t>& mult) {
    std::vector<uint32_t> g;
    g.reserve(distinct_values.size());
    for (V v : distinct_values) g.push_back(qvec(codec, v));

    std::vector<uint64_t> gp(g.begin(), g.end());
    if (detail::gf2_rank(gp) < k) return 0;

    const size_t total = std::accumulate(mult.begin(), mult.end(), size_t{0});
    size_t best_in = 0;
    for (uint32_t a = 1; a < (1u << k); ++a) {  // nonzero dual vector (functional)
        size_t in_H = 0;
        for (size_t i = 0; i < g.size(); ++i) {
            // g lies in ker(a) = H iff the XOR-parity <g, a> is even.
            if ((__builtin_popcount(g[i] & a) & 1) == 0) in_H += mult[i];
        }
        best_in = std::max(best_in, in_H);
    }
    return total - best_in;
}

// Mean TV-to-codespace over several independent build seeds. Two regimes matter
// and they SEPARATE cleanly by mean:
//   - BROKEN (surviving rank k - 1): the T4 step law is realized EXACTLY on every
//     build (4 hit classes at 1/4, 4 missed at 0), so TV = 0.5 deterministically,
//     mean 0.5, zero build-to-build spread (the residual band noise lives on the
//     within-class bits, which the length-3 codec quotients away).
//   - INTACT (surviving rank k): TV is the T5 deviation from Uniform(W). For RICH
//     support it is at the floor (~0.004); at the THRESHOLD EDGE (a class backed by
//     a single surviving key, the worst case of a d* - 1 erasure) it is REDUNDANCY-
//     ELEVATED (mean ~0.13, individual builds up to ~0.43) and does NOT shrink with
//     query count. That elevation is exactly the T5b redundancy story; the
//     load-bearing INTACT invariant is therefore the RANK (= k), with the mean TV
//     used only to confirm a clear gap below the 0.5 broken step.
// Sentinel builds (-1) are skipped.
double mean_tv_over_builds(const Codec& codec,
                           const std::vector<std::string>& keys,
                           const std::vector<V>& values,
                           size_t n_q, size_t n_builds, uint64_t build_seed0) {
    if (keys.empty()) return -1.0;
    std::vector<double> tvs;
    tvs.reserve(n_builds);
    for (size_t b = 0; b < n_builds; ++b) {
        double tv = bench::measure_tv_to_codespace<M>(
            codec, keys, values, std::span<const V>{ALPHABET},
            n_q, build_seed0 + b * 7919, 0xD1B54A32D192ED03ULL);
        if (tv >= 0.0) tvs.push_back(tv);
    }
    if (tvs.empty()) return -1.0;
    return std::accumulate(tvs.begin(), tvs.end(), 0.0) / static_cast<double>(tvs.size());
}

// Build the stored (keys, values) for a per-distinct-value multiplicity profile:
// mult[i] copies of support[i]. Returns the flattened (values, keys).
struct stored_set {
    std::vector<V> values;
    std::vector<std::string> keys;
};

stored_set build_stored(const std::vector<V>& support, const std::vector<size_t>& mult) {
    stored_set s;
    for (size_t i = 0; i < support.size(); ++i)
        for (size_t j = 0; j < mult[i]; ++j) s.values.push_back(support[i]);
    s.keys = gen_keys(s.values.size());
    return s;
}

// A modest but adequate query budget keeps the test fast. The T4 broken step
// (mean TV = 0.5 exactly) and the INTACT regime (mean TV <= ~0.13 even at the
// threshold edge) separate cleanly by mean; the rank check is the primary gate.
constexpr size_t N_Q = 40000;
constexpr size_t N_BUILDS = 8;

// Thresholds. The broken step is 0.5 exactly; BROKEN_TV asserts the mean is at
// the step. The INTACT regime mean stays well under INTACT_GAP, clearly below the
// step, even at the threshold edge. RICH_FLOOR is the rich-support floor.
constexpr double BROKEN_TV = 0.45;     // mean at the 0.5 T4 step
constexpr double INTACT_GAP = 0.35;    // mean clearly below the step (rank k)
constexpr double RICH_FLOOR = 0.05;    // rich, redundant support floor

}  // namespace

// ===== Closed form for d* on the canonical configs. =====

TEST_CASE("T5b: cogirth closed form d* = (K/2)*m on full support, d* = m on a basis",
          "[cogirth][robustness]") {
    Codec codec = make_codec();

    // Ground the geometry: a hyperplane of GF(2)^3 contains exactly K/2 = 4 of the
    // 8 value-patterns (including 0, which lies in every hyperplane). Confirm via
    // the cogirth helper at multiplicity 1: full support, m = 1 gives
    // d* = 8 - 4 = 4 = K/2.
    {
        std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
        std::vector<size_t> ones(8, 1);
        REQUIRE(cogirth(codec, full, ones) == K / 2);
    }

    // Full support, uniform multiplicity m: d* = (K/2) * m exactly.
    for (size_t m : {1u, 2u, 3u, 5u, 10u, 25u}) {
        std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
        std::vector<size_t> mult(8, m);
        REQUIRE(cogirth(codec, full, mult) == (K / 2) * m);
    }

    // Basis support {V1, V2, V4} = {e0, e1, e2}, uniform m: every value essential,
    // rank = 3 = k, and d* = m exactly (the per-value essential cogirth).
    for (size_t m : {1u, 3u, 10u, 25u}) {
        std::vector<V> basis = {V::V1, V::V2, V::V4};
        std::vector<size_t> mult(3, m);
        REQUIRE(cogirth(codec, basis, mult) == m);
    }

    // d* is genuinely NEW: for the full grid at m = 10 it is 40, distinct from
    // log2 K = 3 and from the distinct-pattern cogirth 1.
    {
        std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
        std::vector<size_t> mult(8, 10);
        const size_t dstar = cogirth(codec, full, mult);
        REQUIRE(dstar == 40u);
        REQUIRE(dstar != k);
        REQUIRE(dstar != 1u);
    }
}

// ===== Above-threshold control intact at the floor. =====

TEST_CASE("T5b: balanced above-threshold structure has codec control intact",
          "[cogirth][robustness]") {
    Codec codec = make_codec();

    // Full support, m = 10: n = 80 stored keys, stored value-patterns over Q are
    // 10 copies of each of the 8 patterns. rank = 3 = log2 K, control intact.
    std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
    std::vector<size_t> mult(8, 10);
    stored_set s = build_stored(full, mult);
    REQUIRE(s.values.size() == 80u);
    REQUIRE(surviving_rank(codec, s.values) == k);

    double tv = mean_tv_over_builds(codec, s.keys, s.values, N_Q, N_BUILDS, 0x1234);
    REQUIRE(tv >= 0.0);
    REQUIRE(tv < RICH_FLOOR);  // near the codespace floor (rich, redundant support)
}

// ===== Adversarial erasure: targeted at d* breaks; d* - 1 stays intact. =====

TEST_CASE("T5b: targeted erasure of d* keys breaks control (TV = T4 step ~0.5); "
          "d* - 1 keeps it intact",
          "[cogirth][robustness]") {
    Codec codec = make_codec();

    std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
    std::vector<size_t> mult(8, 10);
    const size_t dstar = cogirth(codec, full, mult);
    REQUIRE(dstar == 40u);

    stored_set s = build_stored(full, mult);  // 80 keys, 10 per value
    const size_t N = s.values.size();

    // The maximizing hyperplane is ker(a = 1) = { g : bit0 = 0 } = {V0,V2,V4,V6}.
    // Its complement (the worst-case cocircuit) is { g : bit0 = 1 } = {V1,V3,V5,V7},
    // m = 10 copies each = 40 columns. Verify these four values are exactly the
    // odd-pattern stacks.
    std::vector<V> outside;   // value-stacks OUTSIDE the hyperplane (to delete)
    std::vector<V> inside;    // value-stacks INSIDE the hyperplane (to keep)
    for (V v : full) {
        if (__builtin_popcount(qvec(codec, v) & 1u) & 1) outside.push_back(v);
        else inside.push_back(v);
    }
    REQUIRE(outside.size() == 4u);
    REQUIRE(inside.size() == 4u);

    auto in_outside = [&](V v) {
        return std::find(outside.begin(), outside.end(), v) != outside.end();
    };

    // ADVERSARIAL: delete all 40 keys whose value lies outside the hyperplane,
    // keeping only the 4 inside-stacks (40 keys). Surviving columns all lie in the
    // hyperplane, so rank drops to 2 and control breaks to the T4 step.
    {
        std::vector<V> surv;
        std::vector<std::string> surv_keys;
        for (size_t i = 0; i < N; ++i) {
            if (!in_outside(s.values[i])) {
                surv.push_back(s.values[i]);
                surv_keys.push_back(s.keys[i]);
            }
        }
        REQUIRE(surv.size() == N - dstar);          // 40 survivors
        REQUIRE(surviving_rank(codec, surv) == k - 1);  // rank dropped to 2

        double tv = mean_tv_over_builds(codec, surv_keys, surv, N_Q, N_BUILDS, 0x4321);
        REQUIRE(tv >= 0.0);
        // Broken: the K' = K/2 = 4 hit classes sit at 1/4, the 4 missed at 0, so
        // TV-to-codespace = 0.5 EXACTLY on every build (the T4 step, realized with
        // zero T5 deviation). Assert the mean is at the step.
        REQUIRE(tv >= BROKEN_TV);
        REQUIRE(std::abs(tv - 0.5) < 1e-6);  // the step is exact, build-independent
    }

    // d* - 1 = 39 erasures keep control INTACT for EVERY choice: 41 survivors
    // cannot all lie in a hyperplane (max-in-hyperplane is 40). Delete 39 of the
    // 40 adversarial keys (one outside-stack key survives), leaving 41 keys whose
    // rank is still k.
    {
        std::vector<V> surv;
        std::vector<std::string> surv_keys;
        size_t deleted = 0;
        for (size_t i = 0; i < N; ++i) {
            if (in_outside(s.values[i]) && deleted < dstar - 1) {
                ++deleted;  // erase this adversarial key
            } else {
                surv.push_back(s.values[i]);
                surv_keys.push_back(s.keys[i]);
            }
        }
        REQUIRE(deleted == dstar - 1);              // 39 erased
        REQUIRE(surv.size() == N - (dstar - 1));    // 41 survivors
        // The load-bearing INTACT invariant (T4 control): rank is still k. This is
        // exact and deterministic, the real guarantee the cogirth delivers at d* - 1.
        REQUIRE(surviving_rank(codec, surv) == k);

        // This worst-case d* - 1 erasure strands one class at a SINGLE surviving
        // key (the outside-stack), so W sits at the threshold edge and the T5
        // deviation is redundancy-elevated (mean ~0.13, not the rich floor); it is
        // NOT sampling noise (stable in query count). What matters is the clear gap
        // below the 0.5 broken step: control is intact, the law has not collapsed.
        double tv = mean_tv_over_builds(codec, surv_keys, surv, N_Q, N_BUILDS, 0x9876);
        REQUIRE(tv >= 0.0);
        REQUIRE(tv < INTACT_GAP);  // clearly below the T4 step: control intact
    }

    // CONTRAST (the multiplicity payoff): deleting one whole value-stack (10 keys)
    // does NOT break control, because the full grid is redundant. Over DISTINCT
    // patterns the cogirth would be 1; the multiplicity makes d* = 40, and a
    // single non-essential class is recoverable from the others.
    {
        std::vector<V> surv;
        std::vector<std::string> surv_keys;
        for (size_t i = 0; i < N; ++i) {
            if (s.values[i] != V::V1) {
                surv.push_back(s.values[i]);
                surv_keys.push_back(s.keys[i]);
            }
        }
        REQUIRE(surviving_rank(codec, surv) == k);  // intact: redundant grid
    }
}

// ===== Basis support: d* = m, the targeted break lands exactly at r = m. =====

TEST_CASE("T5b: basis support {V1,V2,V4} breaks exactly at r = d* = m, TV = 0.5",
          "[cogirth][robustness]") {
    Codec codec = make_codec();
    const size_t m = 10;

    std::vector<V> basis = {V::V1, V::V2, V::V4};
    std::vector<size_t> mult(3, m);
    const size_t dstar = cogirth(codec, basis, mult);
    REQUIRE(dstar == m);

    stored_set s = build_stored(basis, mult);  // 30 keys, 10 per value
    const size_t N = s.values.size();

    // TARGETED: delete all m copies of the essential value V4 (column e2). At
    // r = m the V4 stack is gone, surviving support {V1,V2} = {e0,e1} has rank 2,
    // control breaks. At r = m - 1 the rank is still 3.
    auto delete_first_r_of = [&](V target, size_t r) {
        std::vector<V> surv;
        std::vector<std::string> surv_keys;
        size_t seen = 0;
        for (size_t i = 0; i < N; ++i) {
            if (s.values[i] == target) {
                if (seen >= r) { surv.push_back(s.values[i]); surv_keys.push_back(s.keys[i]); }
                ++seen;
            } else {
                surv.push_back(s.values[i]);
                surv_keys.push_back(s.keys[i]);
            }
        }
        return stored_set{std::move(surv), std::move(surv_keys)};
    };

    // r = d* - 1 = 9: rank still k, control intact (the real guarantee). The
    // surviving V4 stack is down to a single key, so the T5 deviation is
    // edge-elevated; the rank check is the gate, with the mean TV confirming a
    // clear gap below the 0.5 step.
    {
        stored_set surv = delete_first_r_of(V::V4, dstar - 1);
        REQUIRE(surviving_rank(codec, surv.values) == k);  // control intact
        double tv = mean_tv_over_builds(codec, surv.keys, surv.values, N_Q, N_BUILDS, 0x2468);
        REQUIRE(tv >= 0.0);
        REQUIRE(tv < INTACT_GAP);
    }

    // r = d* = m = 10: V4 fully erased, rank drops to 2, control breaks to the
    // T4 step. Surviving image pi(W) = span{e0,e1} = the hyperplane {V0,V1,V2,V3},
    // 4 hit classes at 1/4 and 4 missed at 0, so TV-to-codespace = 0.5 exactly.
    {
        stored_set surv = delete_first_r_of(V::V4, dstar);
        REQUIRE(surviving_rank(codec, surv.values) == k - 1);
        double tv = mean_tv_over_builds(codec, surv.keys, surv.values, N_Q, N_BUILDS, 0x1357);
        REQUIRE(tv >= 0.0);
        REQUIRE(tv >= BROKEN_TV);             // the T4 broken step
        REQUIRE(std::abs(tv - 0.5) < 1e-6);   // exact, build-independent
    }
}

// ===== The m_min lower bound (converts the open T5 conjecture into a theorem). =====

TEST_CASE("T5b: d* >= (K/2)*m_min on non-uniform profiles, with equality when the "
          "thin stacks bind",
          "[cogirth][robustness]") {
    Codec codec = make_codec();
    std::vector<V> full(ALPHABET.begin(), ALPHABET.end());

    // (a) A non-uniform profile: seven values stored 10x, one stored 3x. m_min = 3,
    // (K/2)*m_min = 12. The bound holds (here d* = 33, loose: the fat stacks
    // outside any hyperplane keep d* high).
    {
        std::vector<size_t> mult(8, 10);
        mult[5] = 3;  // V5 thin
        const size_t dstar = cogirth(codec, full, mult);
        const size_t m_min = *std::min_element(mult.begin(), mult.end());
        REQUIRE(m_min == 3u);
        REQUIRE(dstar >= (K / 2) * m_min);  // 33 >= 12
        REQUIRE(dstar == 33u);              // exact, for the record
    }

    // (b) The BINDING construction: put the K/2 = 4 thinnest stacks (m_min = 3 each)
    // OUTSIDE the hyperplane ker(a = 1) = {V0,V2,V4,V6}, and the 4 fat stacks
    // (m = 10) INSIDE. Then the maximizing hyperplane captures 40 fat columns, its
    // complement carries 4 * 3 = 12, and d* = (K/2)*m_min = 12 EXACTLY. This is the
    // case where per-class redundancy m_min is the binding resource.
    {
        std::vector<size_t> mult(8, 0);
        for (V v : full) {
            const bool inside = (__builtin_popcount(qvec(codec, v) & 1u) & 1) == 0;
            mult[static_cast<size_t>(v)] = inside ? 10u : 3u;
        }
        const size_t dstar = cogirth(codec, full, mult);
        const size_t m_min = *std::min_element(mult.begin(), mult.end());
        REQUIRE(m_min == 3u);
        REQUIRE(dstar >= (K / 2) * m_min);
        REQUIRE(dstar == (K / 2) * m_min);  // equality: thin stacks bind, d* = 12
    }

    // (c) The bound holds across many random non-uniform profiles (the general
    // guarantee: control survives at least (K/2)*m_min adversarial erasures).
    {
        std::mt19937_64 rng{7};
        std::uniform_int_distribution<int> md(1, 30);
        for (int t = 0; t < 24; ++t) {
            std::vector<size_t> mult(8);
            for (auto& x : mult) x = static_cast<size_t>(md(rng));
            const size_t dstar = cogirth(codec, full, mult);
            const size_t m_min = *std::min_element(mult.begin(), mult.end());
            REQUIRE(dstar >= (K / 2) * m_min);
            REQUIRE(dstar >= m_min);  // the weaker per-value bound, also always true
        }
    }
}

// ===== T5b claim (2): d* is ALSO the exact CORRUPTION (substitution) budget. =====
//
// Corrupting a stored key substitutes its value (its column moves to another
// value-pattern); unlike erasure the column count is preserved. Persistence:
// with fewer than d* corruptions the untouched columns are the survivors of a
// deletion of size < d*, which still span Q, and the corrupted system contains
// them, so control (rank k) holds for EVERY corruption pattern and EVERY choice
// of substituted values. Tightness: substituting the d* keys whose columns lie
// outside a maximizing hyperplane with values INSIDE it (V0's column 000 lies in
// every hyperplane) drops the rank to k-1. This replaces a withdrawn
// "floor((d*-1)/2) errors are correctable" claim, which transported the textbook
// decoding radius into a setting with no code constraint on legal builds
// (CORRECTION 2026-06-09; see the note).

TEST_CASE("T5b: cogirth d* is the exact corruption (substitution) budget",
          "[cogirth][robustness]") {
    auto codec = make_codec();
    const size_t m = 3;
    std::vector<V> full(ALPHABET.begin(), ALPHABET.end());
    std::vector<size_t> mult(ALPHABET.size(), m);

    // Stored multiset: full support, multiplicity m each; d* = (K/2) m.
    const size_t dstar = cogirth(codec, full, mult);
    REQUIRE(dstar == (K / 2) * m);

    std::vector<V> stored;
    for (V v : ALPHABET)
        for (size_t j = 0; j < m; ++j) stored.push_back(v);
    REQUIRE(surviving_rank(codec, stored) == k);

    // (a) PERSISTENCE: corrupt exactly d* - 1 keys, random positions and random
    // replacement values, many trials: the corrupted multiset's rank stays k.
    std::mt19937_64 rng{2026};
    std::uniform_int_distribution<size_t> pos(0, stored.size() - 1);
    std::uniform_int_distribution<int> val(0, static_cast<int>(K) - 1);
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<V> corrupted = stored;
        std::set<size_t> sites;
        while (sites.size() < dstar - 1) sites.insert(pos(rng));
        for (size_t s : sites) corrupted[s] = static_cast<V>(val(rng));
        REQUIRE(surviving_rank(codec, corrupted) == k);
    }

    // (b) TIGHTNESS: find a maximizing hyperplane ker(a*), substitute every key
    // whose column lies OUTSIDE it with V0 (column 000, inside every hyperplane).
    // Exactly d* substitutions, and the rank drops to exactly k - 1.
    uint32_t a_star = 0;
    size_t best_in = 0;
    for (uint32_t a = 1; a < (1u << k); ++a) {
        size_t in_ker = 0;
        for (V v : stored)
            if ((__builtin_popcount(qvec(codec, v) & a) & 1) == 0) ++in_ker;
        if (in_ker > best_in) { best_in = in_ker; a_star = a; }
    }
    REQUIRE(stored.size() - best_in == dstar);  // the maximizer realizes d*

    std::vector<V> adversarial = stored;
    size_t substituted = 0;
    for (auto& v : adversarial) {
        if ((__builtin_popcount(qvec(codec, v) & a_star) & 1) != 0) {
            v = V::V0;  // move the column into ker(a*)
            ++substituted;
        }
    }
    REQUIRE(substituted == dstar);
    REQUIRE(surviving_rank(codec, adversarial) == k - 1);  // broken: exactly k-1
}
