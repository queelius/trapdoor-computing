/**
 * @file test_prefix_codec.cpp
 * @brief Tests for prefix_codec + non-member distribution measurement.
 *
 * The static tests check the codec's contract: prefix-free assignment,
 * encode/decode round-trip, codespace shares, Kraft validation.
 *
 * The empirical test measures the relationship between stored-value
 * frequency distribution and non-member query distribution under
 * encoded_retrieval<ribbon_retrieval<M>, prefix_codec<V, M>>. This
 * is the cipher-map "codespace dominates" claim made concrete.
 */

#include <catch2/catch_test_macros.hpp>

#include <lapidary/codecs/prefix_codec.hpp>
#include <lapidary/concepts/codec.hpp>
#include <lapidary/detail/gf2.hpp>
#include <lapidary/retrieval/encoded_retrieval.hpp>
#include <lapidary/retrieval/ribbon_retrieval.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <random>
#include <string>
#include <vector>

using namespace lapidary;

namespace {

enum class V : uint8_t { A, B, C, D };

std::vector<std::string> make_keys(size_t n, uint64_t seed = 42) {
    std::vector<std::string> keys;
    keys.reserve(n);
    std::mt19937_64 rng{seed};
    std::uniform_int_distribution<int> b(0, 255);
    for (size_t i = 0; i < n; ++i) {
        std::string k(16, '\0');
        for (auto& c : k) c = static_cast<char>(b(rng));
        keys.push_back(std::move(k));
    }
    std::sort(keys.begin(), keys.end());
    keys.erase(std::unique(keys.begin(), keys.end()), keys.end());
    return keys;
}

}  // namespace

// ===== Static contract: codec interface =====

TEST_CASE("prefix_codec satisfies codec concept", "[prefix_codec][concept]") {
    STATIC_REQUIRE(codec<prefix_codec<V, 4>>);
    STATIC_REQUIRE(codec<prefix_codec<V, 8>>);
}

TEST_CASE("prefix_codec: complete code (Kraft = 1)", "[prefix_codec]") {
    // {A: 1 bit, B: 2 bits, C: 2 bits} - Kraft = 1/2 + 1/4 + 1/4 = 1
    prefix_codec<V, 4> c({{V::A, 1}, {V::B, 2}, {V::C, 2}}, V::D);

    // Round-trip: encode then decode returns the original.
    REQUIRE(c.decode(c.encode(V::A)) == V::A);
    REQUIRE(c.decode(c.encode(V::B)) == V::B);
    REQUIRE(c.decode(c.encode(V::C)) == V::C);

    // Class sizes match prefix lengths.
    REQUIRE(c.codespace_share(V::A) == 0.5);
    REQUIRE(c.codespace_share(V::B) == 0.25);
    REQUIRE(c.codespace_share(V::C) == 0.25);
    // No surplus (Kraft = 1).
    REQUIRE(c.codespace_share(V::D) == 0.0);

    // All 16 patterns should decode to A, B, or C.
    std::array<int, 4> counts{0, 0, 0, 0};
    for (uint64_t p = 0; p < 16; ++p) {
        counts[static_cast<size_t>(c.decode(p))]++;
    }
    REQUIRE(counts[static_cast<size_t>(V::A)] == 8);  // class size 8 of 16 = 0.5
    REQUIRE(counts[static_cast<size_t>(V::B)] == 4);  // 4 of 16 = 0.25
    REQUIRE(counts[static_cast<size_t>(V::C)] == 4);
    REQUIRE(counts[static_cast<size_t>(V::D)] == 0);
}

TEST_CASE("prefix_codec: incomplete code routes surplus to default", "[prefix_codec]") {
    // {A: 2, B: 2, C: 2} - Kraft = 3/4 < 1, surplus = 1/4
    prefix_codec<V, 4> c({{V::A, 2}, {V::B, 2}, {V::C, 2}}, V::D);
    REQUIRE(c.codespace_share(V::A) == 0.25);
    REQUIRE(c.codespace_share(V::B) == 0.25);
    REQUIRE(c.codespace_share(V::C) == 0.25);
    REQUIRE(c.codespace_share(V::D) == 0.25);  // surplus

    std::array<int, 4> counts{0, 0, 0, 0};
    for (uint64_t p = 0; p < 16; ++p) {
        counts[static_cast<size_t>(c.decode(p))]++;
    }
    REQUIRE(counts[static_cast<size_t>(V::A)] == 4);
    REQUIRE(counts[static_cast<size_t>(V::B)] == 4);
    REQUIRE(counts[static_cast<size_t>(V::C)] == 4);
    REQUIRE(counts[static_cast<size_t>(V::D)] == 4);
}

TEST_CASE("prefix_codec: Kraft inequality is enforced", "[prefix_codec]") {
    // {A: 1, B: 1} - Kraft = 1.0 + 0 = 1, OK
    REQUIRE_NOTHROW((prefix_codec<V, 4>{{{V::A, 1}, {V::B, 1}}, V::C}));
    // {A: 1, B: 1, C: 1} - Kraft = 1.5 > 1, illegal
    REQUIRE_THROWS_AS((prefix_codec<V, 4>{{{V::A, 1}, {V::B, 1}, {V::C, 1}}, V::D}),
                      std::invalid_argument);
}

TEST_CASE("prefix_codec: from_frequencies builds a Huffman code", "[prefix_codec]") {
    // Skewed: A is dominant.
    auto c = prefix_codec<V, 8>::from_frequencies(
        {{V::A, 0.90}, {V::B, 0.05}, {V::C, 0.05}}, V::D);

    // A should have a shorter codeword than B or C.
    auto e_a = c.entries();
    auto find_len = [&](V v) -> unsigned {
        for (const auto& e : e_a) if (e.value == v) return e.length;
        return 0;
    };
    unsigned la = find_len(V::A), lb = find_len(V::B), lc = find_len(V::C);
    REQUIRE(la <= lb);
    REQUIRE(la <= lc);
    // Round-trip works for each.
    REQUIRE(c.decode(c.encode(V::A)) == V::A);
    REQUIRE(c.decode(c.encode(V::B)) == V::B);
    REQUIRE(c.decode(c.encode(V::C)) == V::C);
}

// ===== encoded_retrieval<ribbon, prefix_codec> round-trip =====

TEST_CASE("encoded_retrieval<ribbon, prefix_codec>: keys in S round-trip",
          "[prefix_codec][integration]") {
    auto keys = make_keys(500);
    std::vector<V> values;
    values.reserve(keys.size());
    std::mt19937_64 rng{7};
    std::uniform_int_distribution<int> pick(0, 2);
    for (size_t i = 0; i < keys.size(); ++i) {
        values.push_back(static_cast<V>(pick(rng)));
    }

    prefix_codec<V, 4> c({{V::A, 1}, {V::B, 2}, {V::C, 2}}, V::D);
    using Enc = encoded_retrieval<ribbon_retrieval<4>, prefix_codec<V, 4>>;
    auto built = Enc::builder(c).add_all(keys, values).build();
    REQUIRE(built.has_value());

    for (size_t i = 0; i < keys.size(); ++i) {
        REQUIRE(built->lookup(keys[i]) == values[i]);
    }
}

// ===== Empirical claim: non-member distribution =====
//
// The cipher-map framing claims that for a skewed value distribution,
// non-member queries reproduce the skew. The mechanism via prefix_codec
// is: stored patterns concentrate within frequent values' codespace,
// so ribbon's solution_ also concentrates there, and XOR of solution_
// entries has the same distribution as the (frequency-weighted) stored
// patterns.

TEST_CASE("non-member distribution matches codec codespace (not stored frequency)",
          "[prefix_codec][nonmember]") {
    // KEY EMPIRICAL FINDING: ribbon's solution entries become approximately
    // uniform random over GF(2)^M after Gaussian elimination of a sparse
    // system. So non-member XORs are approximately uniform M-bit patterns.
    // What controls the decoded distribution is therefore the CODEC, not
    // the stored-value frequencies.
    //
    // Stored values 90% A / 5% B / 5% C,
    // Codec with prefix lengths {A: 1, B: 2, C: 2} (Kraft = 1):
    //   A's class fraction = 0.5
    //   B's class fraction = 0.25
    //   C's class fraction = 0.25
    //
    // Predicted non-member fractions: 0.50 / 0.25 / 0.25, NOT 0.90 / 0.05 / 0.05.

    auto keys = make_keys(2000);
    std::vector<V> values;
    values.reserve(keys.size());
    std::mt19937_64 rng{42};
    for (size_t i = 0; i < keys.size(); ++i) {
        double r = std::uniform_real_distribution<double>{}(rng);
        if (r < 0.90) values.push_back(V::A);
        else if (r < 0.95) values.push_back(V::B);
        else values.push_back(V::C);
    }
    // Even though we use Huffman lengths derived from frequencies, the
    // resulting class fractions are powers of 2 (0.5 / 0.25 / 0.25), not
    // the raw 0.9 / 0.05 / 0.05.
    prefix_codec<V, 4> cdc({{V::A, 1}, {V::B, 2}, {V::C, 2}}, V::D);

    using Enc = encoded_retrieval<ribbon_retrieval<4>, prefix_codec<V, 4>>;
    auto built = Enc::builder(cdc).add_all(keys, values).build();
    REQUIRE(built.has_value());

    // In-S round-trip.
    for (size_t i = 0; i < keys.size(); ++i) {
        REQUIRE(built->lookup(keys[i]) == values[i]);
    }

    // Non-member distribution.
    std::array<size_t, 4> counts{0, 0, 0, 0};
    const size_t N_unknown = 30000;
    for (size_t i = 0; i < N_unknown; ++i) {
        std::string u = "UNKNOWN_KEY_" + std::to_string(i);
        counts[static_cast<size_t>(built->lookup(u))]++;
    }
    double frac_a = double(counts[0]) / N_unknown;
    double frac_b = double(counts[1]) / N_unknown;
    double frac_c = double(counts[2]) / N_unknown;
    double frac_d = double(counts[3]) / N_unknown;

    // Each fraction within +/- 3% of the codespace share. With 30K
    // samples and a ~uniform underlying distribution, sample stddev
    // is sqrt(p(1-p)/N) ~= 0.003, so 3% is generous.
    REQUIRE(std::abs(frac_a - 0.50) < 0.03);
    REQUIRE(std::abs(frac_b - 0.25) < 0.03);
    REQUIRE(std::abs(frac_c - 0.25) < 0.03);
    REQUIRE(frac_d < 0.005);  // no surplus in this codec

    // Cipher-map design implication: codec controls non-member behavior.
    // To bias non-members toward a default value V, give V a larger
    // codespace class via shorter prefix; the stored-value distribution
    // itself does NOT determine non-member output.
}

TEST_CASE("non-member distribution: same codec, different storage frequencies",
          "[prefix_codec][nonmember][contrastive]") {
    // Direct test of the claim that non-member output depends on the
    // codec, not the stored-value frequencies. We build two structures
    // with the SAME codec but radically different value distributions,
    // and verify the non-member distributions match each other (and
    // the codec's class shares).

    auto keys_a = make_keys(2000, /*seed=*/1);
    auto keys_b = make_keys(2000, /*seed=*/2);
    REQUIRE(keys_a.size() == keys_b.size());

    // Storage 1: 99% A, 0.5% B, 0.5% C.
    std::vector<V> values_a;
    values_a.reserve(keys_a.size());
    std::mt19937_64 rng_a{11};
    for (size_t i = 0; i < keys_a.size(); ++i) {
        double r = std::uniform_real_distribution<double>{}(rng_a);
        if (r < 0.99) values_a.push_back(V::A);
        else if (r < 0.995) values_a.push_back(V::B);
        else values_a.push_back(V::C);
    }

    // Storage 2: 50% A, 25% B, 25% C.
    std::vector<V> values_b;
    values_b.reserve(keys_b.size());
    std::mt19937_64 rng_b{22};
    for (size_t i = 0; i < keys_b.size(); ++i) {
        double r = std::uniform_real_distribution<double>{}(rng_b);
        if (r < 0.50) values_b.push_back(V::A);
        else if (r < 0.75) values_b.push_back(V::B);
        else values_b.push_back(V::C);
    }

    // Identical codec for both.
    prefix_codec<V, 4> cdc({{V::A, 1}, {V::B, 2}, {V::C, 2}}, V::D);

    using Enc = encoded_retrieval<ribbon_retrieval<4>, prefix_codec<V, 4>>;
    auto built_a = Enc::builder(cdc).add_all(keys_a, values_a).build();
    auto built_b = Enc::builder(cdc).add_all(keys_b, values_b).build();
    REQUIRE(built_a.has_value());
    REQUIRE(built_b.has_value());

    // Both should round-trip on their own keys (definitional).
    for (size_t i = 0; i < keys_a.size(); ++i)
        REQUIRE(built_a->lookup(keys_a[i]) == values_a[i]);
    for (size_t i = 0; i < keys_b.size(); ++i)
        REQUIRE(built_b->lookup(keys_b[i]) == values_b[i]);

    // Non-member distributions should be approximately equal despite the
    // wildly different storage distributions.
    auto measure = [](const Enc& e, const std::string& prefix) {
        std::array<size_t, 4> counts{0, 0, 0, 0};
        const size_t N = 30000;
        for (size_t i = 0; i < N; ++i) {
            counts[static_cast<size_t>(e.lookup(prefix + std::to_string(i)))]++;
        }
        std::array<double, 4> fracs;
        for (size_t i = 0; i < 4; ++i) fracs[i] = double(counts[i]) / N;
        return fracs;
    };
    auto fa = measure(*built_a, "UNK_A_");
    auto fb = measure(*built_b, "UNK_B_");

    // Each fraction within 3% of the codec's codespace share (0.5/0.25/0.25).
    REQUIRE(std::abs(fa[0] - 0.50) < 0.03);
    REQUIRE(std::abs(fa[1] - 0.25) < 0.03);
    REQUIRE(std::abs(fa[2] - 0.25) < 0.03);
    REQUIRE(std::abs(fb[0] - 0.50) < 0.03);
    REQUIRE(std::abs(fb[1] - 0.25) < 0.03);
    REQUIRE(std::abs(fb[2] - 0.25) < 0.03);

    // ===== T3: frequency independence (explicit check) =====
    //
    // T3 says W = span_GF(2){ c(x) : x in S } depends only on the SET of
    // distinct stored canonical patterns, not on their multiplicities. The
    // two structures share the codec and the value support {A,B,C} but have
    // radically different storage frequencies (99/0.5/0.5 vs 50/25/25), so by
    // T3 they share the same W and (by T1/T2) the same idealized non-member
    // output law. We verify both directly.

    // W from the SHARED support, computed once (multiplicities irrelevant).
    std::vector<uint64_t> stored{cdc.encode(V::A), cdc.encode(V::B), cdc.encode(V::C)};
    auto basis = lapidary::detail::gf2_basis(stored);

    // Both structures' non-member outputs must re-encode into this same W,
    // independent of which storage frequencies produced each build.
    const size_t N_span = 3000;
    for (size_t i = 0; i < N_span; ++i) {
        V out_a = built_a->lookup("SPAN_A_" + std::to_string(i));
        V out_b = built_b->lookup("SPAN_B_" + std::to_string(i));
        REQUIRE(lapidary::detail::gf2_in_span(cdc.encode(out_a), basis));
        REQUIRE(lapidary::detail::gf2_in_span(cdc.encode(out_b), basis));
    }

    // Independence: the two non-member distributions agree to sampling-noise
    // scale, far tighter than the old 0.05 bound. The difference of two
    // independent frequency estimates each ~ p with N=30000 samples has
    // standard error se = sqrt(2 p (1-p) / N); for p ~ 0.25, se ~ 0.0035. We
    // target 4*se (~0.014) per category. Any residual is the per-build T5
    // deviation from uniform-on-W (each build has its own solution matrix z),
    // NOT a storage-frequency effect: if frequency leaked, fa and fb would
    // track the 99/0.5/0.5 vs 50/25/25 gap, which is orders of magnitude
    // larger than 4*se.
    for (size_t i = 0; i < 3; ++i) {
        double p = 0.25;
        double se = std::sqrt(2.0 * p * (1.0 - p) / 30000.0);
        REQUIRE(std::abs(fa[i] - fb[i]) < 4.0 * se);
    }
}

TEST_CASE("encode_random spreads stored patterns across class",
          "[prefix_codec][encode_random]") {
    // With encode_random, the stored patterns for a value should span
    // its codespace class, not collapse to a canonical pattern.
    prefix_codec<V, 8> c({{V::A, 1}, {V::B, 2}, {V::C, 2}}, V::D);
    std::mt19937_64 rng{2026};

    std::array<int, 256> hits{};
    for (int i = 0; i < 10000; ++i) {
        uint64_t p = c.encode_random(V::A, rng);
        REQUIRE(p < 256);
        hits[p]++;
    }

    // A's class is the top half of the codespace (128 patterns).
    int hit_count = 0;
    for (int p = 0; p < 128; ++p) if (hits[p] > 0) ++hit_count;
    int wrong_count = 0;
    for (int p = 128; p < 256; ++p) wrong_count += hits[p];

    // Should hit most of A's class with 10K samples.
    REQUIRE(hit_count > 100);
    REQUIRE(wrong_count == 0);
}

// ===== T2 span check: non-member outputs land in the stored-pattern span =====

TEST_CASE("non-member outputs land exactly in the stored-pattern span (T2)",
          "[prefix_codec][nonmember][span]") {
    // Store k=3 distinct canonical patterns A,B,C; their GF(2) span has
    // size 4. Every non-member output's canonical pattern must lie in W,
    // and the observed non-member value frequencies must match the
    // span-restricted prediction P(v) = |class(v) ∩ W| / |W|.
    auto keys = make_keys(2000);
    std::vector<V> values; values.reserve(keys.size());
    for (size_t i = 0; i < keys.size(); ++i) values.push_back(static_cast<V>(i % 3)); // A,B,C
    prefix_codec<V, 4> cdc({{V::A, 2}, {V::B, 2}, {V::C, 2}, {V::D, 2}}, V::A); // balanced length-2

    using Enc = encoded_retrieval<ribbon_retrieval<4>, prefix_codec<V, 4>>;
    auto built = Enc::builder(cdc).add_all(keys, values).build();
    REQUIRE(built.has_value());

    // W from the stored canonical patterns A,B,C.
    std::vector<uint64_t> stored{ cdc.encode(V::A), cdc.encode(V::B), cdc.encode(V::C) };
    auto basis = lapidary::detail::gf2_basis(stored);
    auto span  = lapidary::detail::gf2_span(basis);

    // (a) Every non-member output re-encodes into W.
    const size_t N = 30000;
    std::array<size_t, 4> counts{0,0,0,0};
    for (size_t i = 0; i < N; ++i) {
        V out = built->lookup("SPANCHK_" + std::to_string(i));
        uint64_t pat = cdc.encode(out);
        REQUIRE(lapidary::detail::gf2_in_span(pat, basis));
        counts[static_cast<size_t>(out)]++;
    }

    // (b) Span-restricted prediction: P(v) = |class(v) ∩ W| / |W|.
    // Enumerate W, decode each element, tally per value, normalize by |W|.
    std::array<double, 4> predicted{0,0,0,0};
    for (uint64_t p : span) predicted[static_cast<size_t>(cdc.decode(p))] += 1.0;
    for (auto& q : predicted) q /= static_cast<double>(span.size());

    for (size_t i = 0; i < 4; ++i) {
        double obs = static_cast<double>(counts[i]) / static_cast<double>(N);
        REQUIRE(std::abs(obs - predicted[i]) < 0.03);
    }
}

// ===== T4: the sharp codec-control threshold (transversality) =====
//
// This is a PURE linear-algebra check on the stored-pattern span W and the
// codec; it does NOT build a ribbon structure. The bridge from W to actual
// non-member queries is T1/T2 (R(z) = W; idealized output uniform on W),
// already established and exercised by the [span]/[nonmember] tests above.
//
// Claim (T4) for the BALANCED length-2 codec on M=4, K=4. The codec
// partitions GF(2)^4 into K=4 classes, each a coset of the homophone
// subspace C = { patterns whose top log2(K)=2 codeword bits are zero }
// (dim C = M - log2 K = 2, |C| = 4), so alpha(v) = |C|/2^M = 1/4 for every
// value. Let pi project onto the quotient Q = GF(2)^M / C (the two codeword
// bits); the K classes are the K points of Q. For the left-aligned canonical
// patterns the stored patterns lie in a transversal of C (low bits zero), so
// pi restricted to the stored patterns is injective and rank pi|_W equals
// gf2_rank(stored). The predicted per-value mass is the step function
//   q[v] = |class(v) intersect W| / |W| = 1/K' if pi(W) hits class v, else 0,
// where K' = |pi(W)| = 2^(rank pi|_W). FULL control (q == alpha == 1/K for
// every v) holds IFF rank pi|_W = log2 K, i.e. iff pi(W) = Q (transversal).
// The transition is SHARP: below threshold the K' hit classes are each
// OVER-weighted to 1/K' > 1/K and the remaining classes are exactly zero;
// there is no intermediate regime.
//
// Canonical patterns confirmed by reading prefix_codec.hpp's canonical
// assignment and by /tmp probe: with codes {A:2,B:2,C:2,D:2} (default A),
// after the (length, value) sort the consecutive codewords 0,1,2,3 are
// left-aligned into M=4 bits, giving exactly
//   A = 0b0000, B = 0b0100, C = 0b1000, D = 0b1100,
// each class of size 4, alpha = 1/4. (These are the same patterns the
// [span] test and docs/CODESPACE_NONMEMBERS.md use.)
TEST_CASE("T4: sharp codec-control threshold at rank == log2 K (transversality)",
          "[prefix_codec][threshold]") {
    // Balanced length-2 codec on M=4, K=4. Default A (matches [span] test).
    prefix_codec<V, 4> cdc({{V::A, 2}, {V::B, 2}, {V::C, 2}, {V::D, 2}}, V::A);

    // Confirm the exact canonical patterns before asserting anything on them.
    REQUIRE(cdc.encode(V::A) == 0b0000u);
    REQUIRE(cdc.encode(V::B) == 0b0100u);
    REQUIRE(cdc.encode(V::C) == 0b1000u);
    REQUIRE(cdc.encode(V::D) == 0b1100u);
    // Each class has size 4, alpha = 1/4.
    REQUIRE(cdc.codespace_share(V::A) == 0.25);
    REQUIRE(cdc.codespace_share(V::B) == 0.25);
    REQUIRE(cdc.codespace_share(V::C) == 0.25);
    REQUIRE(cdc.codespace_share(V::D) == 0.25);

    // Helper: predicted per-value mass q[v] = |class(v) intersect W| / |W|,
    // computed by enumerating W = gf2_span(gf2_basis(stored)), decoding each
    // element through the codec, tallying per value, and normalizing by |W|.
    // This is the exact rational mass over the enumerated span (T1's formula),
    // so it can be compared with exact equality up to a tiny tolerance.
    auto predicted_mass = [&](const std::vector<uint64_t>& stored) {
        auto basis = lapidary::detail::gf2_basis(stored);
        auto span = lapidary::detail::gf2_span(basis);
        std::array<double, 4> q{0.0, 0.0, 0.0, 0.0};
        for (uint64_t p : span) {
            q[static_cast<size_t>(cdc.decode(p))] += 1.0;
        }
        for (auto& x : q) x /= static_cast<double>(span.size());
        return q;
    };

    // Exact-rational comparison: the masses are dyadic rationals over |W|,
    // so any nonzero tolerance below the smallest gap (here 1/4) is exact.
    constexpr double EXACT = 1e-9;

    SECTION("below threshold: rank 1 < log2 K = 2 -> hit classes over-weighted, misses zero") {
        // Store values {A, B} only -> canonical patterns {0000, 0100}.
        std::vector<uint64_t> stored{cdc.encode(V::A), cdc.encode(V::B)};

        // rank pi|_W = gf2_rank(stored) = 1, strictly below log2 K = 2.
        REQUIRE(lapidary::detail::gf2_rank(stored) == 1u);

        auto q = predicted_mass(stored);
        // K' = |pi(W)| = 2^1 = 2 hit classes (A, B); each gets 1/K' = 1/2,
        // STRICTLY GREATER than alpha = 1/4. The non-hit classes C, D get
        // exactly zero. This is the sharp under-threshold signature.
        REQUIRE(std::abs(q[static_cast<size_t>(V::A)] - 0.5) < EXACT);
        REQUIRE(std::abs(q[static_cast<size_t>(V::B)] - 0.5) < EXACT);
        REQUIRE(q[static_cast<size_t>(V::C)] == 0.0);  // class C missed: exactly zero
        REQUIRE(q[static_cast<size_t>(V::D)] == 0.0);  // class D missed: exactly zero
        // The hit-class mass is over-weighted by the factor K/K' = 4/2 = 2.
        REQUIRE(q[static_cast<size_t>(V::A)] > cdc.codespace_share(V::A));
        REQUIRE(q[static_cast<size_t>(V::B)] > cdc.codespace_share(V::B));
    }

    SECTION("at threshold: rank 2 == log2 K -> full control, alpha for all four") {
        // Store values {A, B, C} -> canonical patterns {0000, 0100, 1000}.
        std::vector<uint64_t> stored{cdc.encode(V::A), cdc.encode(V::B), cdc.encode(V::C)};

        // rank pi|_W = gf2_rank(stored) = 2 = log2 K: pi(W) = Q (surjective).
        REQUIRE(lapidary::detail::gf2_rank(stored) == 2u);

        auto q = predicted_mass(stored);
        // FULL control: every class hit, each mass = alpha = 1/K = 1/4. Note D
        // is hit although never stored, because 1100 = 0100 XOR 1000 is in W;
        // membership of a class in pi(W) is what matters, not storage.
        REQUIRE(std::abs(q[static_cast<size_t>(V::A)] - 0.25) < EXACT);
        REQUIRE(std::abs(q[static_cast<size_t>(V::B)] - 0.25) < EXACT);
        REQUIRE(std::abs(q[static_cast<size_t>(V::C)] - 0.25) < EXACT);
        REQUIRE(std::abs(q[static_cast<size_t>(V::D)] - 0.25) < EXACT);
        // Each equals the codec's codespace share (the transversal condition).
        for (V v : {V::A, V::B, V::C, V::D}) {
            REQUIRE(std::abs(q[static_cast<size_t>(v)] - cdc.codespace_share(v)) < EXACT);
        }
    }
}

// ===== T2 RAW containment: the falsifiable span gate =====
//
// The other [span]/[contrastive] checks in this file verify the CLASS-LEVEL
// law: they decode the output and re-encode the decoded value's canonical
// pattern before testing membership in W. For a Kraft-tight codec whose
// canonical patterns all lie in W, that re-encoded pattern is in W for EVERY
// conceivable raw output (decode is total), so those checks cannot falsify
// the T2 containment "reachable outputs subset W": the decode step erases
// exactly the within-class bits where a violation would live.
//
// This test is the falsifiable gate. It drives the ribbon DIRECTLY with the
// same canonical right-hand sides the codec composition stores, and checks
// the RAW (undecoded) M-bit lookup output of non-member queries lies in W.
// Above threshold |W| = 4 of 16 possible raw patterns; sub-threshold
// |W| = 2 of 16. A theorem violation has most of the output space to land on.

TEST_CASE("T2 raw containment: undecoded non-member outputs lie in W",
          "[prefix_codec][span][raw]") {
    constexpr unsigned M = 4;
    enum class V : uint8_t { A, B, C, D };
    prefix_codec<V, M> cdc({{V::A, 2}, {V::B, 2}, {V::C, 2}, {V::D, 2}}, V::A);
    using ribbon = ribbon_retrieval<M>;

    // --- Above-threshold instance: store A, B, C (rank 2 = log2 K). ---
    auto keys = make_keys(2000);
    std::vector<uint64_t> pats;
    pats.reserve(keys.size());
    for (size_t i = 0; i < keys.size(); ++i) {
        pats.push_back(cdc.encode(static_cast<V>(i % 3)));  // A,B,C canonical RHS
    }

    typename ribbon::builder b;
    for (size_t i = 0; i < keys.size(); ++i) {
        b.add(keys[i], static_cast<typename ribbon::value_type>(pats[i]));
    }
    b.with_seed(7);
    auto rib = b.build();
    REQUIRE(rib.has_value());

    // W = span{enc(A), enc(B), enc(C)}; the gate is NON-VACUOUS: |W| = 4 < 16,
    // so 12 of the 16 possible raw outputs would fail the containment check.
    std::vector<uint64_t> stored{cdc.encode(V::A), cdc.encode(V::B), cdc.encode(V::C)};
    auto basis = lapidary::detail::gf2_basis(stored);
    REQUIRE(lapidary::detail::gf2_span(basis).size() == 4u);

    // (a) member RAW lookups reproduce the exact stored canonical patterns.
    for (size_t i = 0; i < keys.size(); ++i) {
        REQUIRE(static_cast<uint64_t>(rib->lookup(keys[i])) == pats[i]);
    }

    // (b) non-member RAW outputs all lie in W: the T2 containment, falsifiably.
    for (size_t i = 0; i < 30000; ++i) {
        const uint64_t raw =
            static_cast<uint64_t>(rib->lookup("RAWSPAN_" + std::to_string(i)));
        REQUIRE(lapidary::detail::gf2_in_span(raw, basis));
    }

    // --- Sub-threshold instance: store only A, B (rank 1 < log2 K = 2). ---
    // W2 = {enc(A), enc(B)} has |W2| = 2 of 16: an even sharper gate, and the
    // decoded outputs realize the T4 step (classes C and D missed exactly).
    auto keys2 = make_keys(1000, 99);
    std::vector<uint64_t> pats2;
    pats2.reserve(keys2.size());
    for (size_t i = 0; i < keys2.size(); ++i) {
        pats2.push_back(cdc.encode(static_cast<V>(i % 2)));  // A,B only
    }
    typename ribbon::builder b2;
    for (size_t i = 0; i < keys2.size(); ++i) {
        b2.add(keys2[i], static_cast<typename ribbon::value_type>(pats2[i]));
    }
    b2.with_seed(11);
    auto rib2 = b2.build();
    REQUIRE(rib2.has_value());

    std::vector<uint64_t> stored2{cdc.encode(V::A), cdc.encode(V::B)};
    auto basis2 = lapidary::detail::gf2_basis(stored2);
    REQUIRE(lapidary::detail::gf2_span(basis2).size() == 2u);

    for (size_t i = 0; i < 15000; ++i) {
        const uint64_t raw =
            static_cast<uint64_t>(rib2->lookup("RAWSUB_" + std::to_string(i)));
        REQUIRE(lapidary::detail::gf2_in_span(raw, basis2));
        const V out = cdc.decode(raw);
        // T4 step at rank 1: only the two hit classes can appear.
        REQUIRE((out == V::A || out == V::B));
    }
}
