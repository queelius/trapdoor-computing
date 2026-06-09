/**
 * @file test_randomized_encoding.cpp
 * @brief Randomized-encoding invariance lemma (resolves the deferred Q#5).
 *
 * This is the computational gate for the "Randomized encoding: invariance
 * plus white-box divergence" subsection of docs/codec_controlled_retrieval.md.
 *
 * The result. prefix_codec::encode_random(v, rng) returns a UNIFORM RANDOM
 * pattern inside value v's class: the canonical codeword has its within-class
 * bits (the bottom M - len(v) bits) zero, and encode_random sets them
 * randomly. Those within-class directions are exactly C_{len(v)} = ker(pi)
 * of the value-quotient projection pi (the same nested flag C_l used by T4b).
 * The encoded_retrieval builder calls the CANONICAL encode, not encode_random;
 * wiring encode_random into the builder was the long-deferred open item Q#5.
 *
 * LEMMA (invariance plus divergence). Replacing each stored value's canonical
 * codeword with encode_random(value) (a uniform within-class representative)
 * leaves pi(W) EXACTLY invariant: the added bits live in ker(pi), so the
 * projection of the stored span W onto the value quotient Q is unchanged.
 * Hence the entire non-member output law q(v) = |class(v) intersect W| / |W|
 * (by T1/T2/T4 and the realizability formula) is EXACTLY invariant. Meanwhile
 * the ribbon solution vector z (the white-box snapshot) DIVERGES per build: it
 * now solves a different right-hand side. So within-class randomization is
 * statistically invisible in the off-set output distribution while maximizing
 * the entropy of the white-box snapshot, a snapshot/white-box confidentiality
 * property at zero per-query cost.
 *
 * Notation (matches the note): W is the stored-pattern span, pi the value-
 * quotient projection with kernel the within-class flag C_l, class(v) the
 * decode class of v, q(v) = |class(v) intersect W| / |W| the idealized
 * non-member mass, alpha the codec's codespace share.
 *
 * Three checks below:
 *   (1) EXACT invariance: for every value v, q(v) is bit-identical between the
 *       canonical and a randomized within-class stored set, asserted with EXACT
 *       integer cross-multiplication over many fixed-seed random re-encodings
 *       (|W| itself may change; every class mass is pinned).
 *   (2) EMPIRICAL invariance: a canonical encoded_retrieval and a randomized
 *       ribbon build on the same keys/values agree on the non-member decoded
 *       distribution within sampling noise, and member lookups are correct in
 *       both.
 *   (3) WHITE-BOX divergence: the serialized ribbon solution bytes differ
 *       substantially between the canonical and randomized builds, while the
 *       decoded non-member law is the same.
 */

#include <catch2/catch_test_macros.hpp>

#include <maph/codecs/prefix_codec.hpp>
#include <maph/detail/gf2.hpp>
#include <maph/retrieval/encoded_retrieval.hpp>
#include <maph/retrieval/ribbon_retrieval.hpp>

#include <array>
#include <cmath>
#include <cstdint>
#include <random>
#include <string>
#include <vector>

using namespace maph;

namespace {

// ===== Exact-invariance harness (pure GF(2) linear algebra on the span) =====

// Per-class hit count |class(v) intersect W| for every entry, computed by
// enumerating W = gf2_span(gf2_basis(stored)) and tallying decode classes by
// the SAME top-len-bits mask the codec uses. Returns a vector aligned with
// codec.entries() order, plus |W| (the span size). These are EXACT integers
// (no floating point), so masses compare bit-for-bit via cross-multiplication.
template <typename Codec>
std::pair<std::vector<uint64_t>, uint64_t>
class_hits_and_W(const Codec& codec, const std::vector<uint64_t>& stored, unsigned M) {
    const auto basis = maph::detail::gf2_basis(stored);
    const auto span = maph::detail::gf2_span(basis);

    const auto& entries = codec.entries();
    std::vector<uint64_t> hits(entries.size(), 0);
    for (size_t i = 0; i < entries.size(); ++i) {
        const unsigned l = entries[i].length;
        const uint32_t mask =
            (l >= M) ? static_cast<uint32_t>((uint64_t{1} << M) - 1)
                     : static_cast<uint32_t>((((uint64_t{1} << M) - 1) >> (M - l)) << (M - l));
        const uint32_t code = entries[i].prefix_left_aligned & mask;
        uint64_t c = 0;
        for (uint64_t x : span) {
            if ((static_cast<uint32_t>(x) & mask) == code) ++c;
        }
        hits[i] = c;
    }
    return {hits, static_cast<uint64_t>(span.size())};
}

// A uniform within-class pattern for v: canonical base with the bottom
// M - len(v) bits drawn uniformly. Equivalent to encode_random; reproduced
// here so the exact check does not depend on the codec's private rng plumbing.
template <typename Codec, typename Rng>
uint64_t random_within_class(const Codec& codec, const typename Codec::logical_value& v,
                             Rng& rng) {
    auto [base, count] = codec.class_for(v);
    if (count <= 1) return base;
    std::uniform_int_distribution<uint64_t> dist(0, count - 1);
    return base | dist(rng);
}

// ===== Empirical / white-box harness (real ribbon builds) =====

std::vector<std::string> make_keys(size_t n, uint64_t seed) {
    std::vector<std::string> keys;
    keys.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        keys.push_back("member_key_" + std::to_string(seed) + "_" + std::to_string(i));
    }
    return keys;
}

template <unsigned M>
ribbon_retrieval<M> build_ribbon(const std::vector<std::string>& keys,
                                 const std::vector<uint64_t>& pats, uint64_t seed) {
    typename ribbon_retrieval<M>::builder b;
    for (size_t i = 0; i < keys.size(); ++i) {
        b.add(keys[i], static_cast<typename ribbon_retrieval<M>::value_type>(pats[i]));
    }
    b.with_seed(seed);
    auto r = b.build();
    REQUIRE(r.has_value());
    return std::move(*r);
}

}  // namespace

// ===== (1) EXACT invariance: pi(W), hence q(.), is bit-identical =====

TEST_CASE("randomized encoding: pi(W) and q(.) are EXACTLY invariant (M=4 skew {1,2,3,3})",
          "[prefix_codec][randomized][invariance]") {
    constexpr unsigned M = 4;
    enum class V : uint8_t { A, B, C, D };
    prefix_codec<V, M> codec{{{V::A, 1}, {V::B, 2}, {V::C, 3}, {V::D, 3}}, V::A};

    // A representative stored value multiset: every value present at least once
    // (so the canonical span is the full codeword span), plus repeats. The
    // canonical patterns realize the designed Kraft law (1/2, 1/4, 1/8, 1/8).
    const std::vector<V> base_seq = {V::A, V::B, V::C, V::D, V::A, V::A, V::B};

    std::vector<uint64_t> canon;
    for (V v : base_seq) canon.push_back(codec.encode(v));
    auto [hit_c, W_c] = class_hits_and_W(codec, canon, M);

    // Sanity: the canonical law is the designed (1/2, 1/4, 1/8, 1/8).
    REQUIRE(W_c == 8u);
    REQUIRE(hit_c[0] == 4u);  // A: 4/8 = 1/2
    REQUIRE(hit_c[1] == 2u);  // B: 2/8 = 1/4
    REQUIRE(hit_c[2] == 1u);  // C: 1/8
    REQUIRE(hit_c[3] == 1u);  // D: 1/8

    // Many fixed-seed random within-class re-encodings of the SAME multiset.
    // Each must yield a span whose per-class masses are bit-identical to the
    // canonical ones, even when |W| differs (it can grow to 16 here).
    std::mt19937_64 rng{2026};
    int trials = 400;
    int mismatches = 0;
    bool saw_larger_W = false;
    for (int t = 0; t < trials; ++t) {
        std::vector<uint64_t> rp;
        for (V v : base_seq) rp.push_back(random_within_class(codec, v, rng));
        auto [hit_r, W_r] = class_hits_and_W(codec, rp, M);
        if (W_r > W_c) saw_larger_W = true;
        // q_c(v) == q_r(v)  <=>  hit_c * W_r == hit_r * W_c  (exact integers).
        for (size_t i = 0; i < hit_c.size(); ++i) {
            if (hit_c[i] * W_r != hit_r[i] * W_c) ++mismatches;
        }
    }
    REQUIRE(mismatches == 0);   // EXACT invariance over all trials
    REQUIRE(saw_larger_W);      // |W| genuinely changes yet masses are pinned
}

TEST_CASE("randomized encoding: q(.) EXACTLY invariant across several codecs (M=6)",
          "[prefix_codec][randomized][invariance]") {
    constexpr unsigned M = 6;
    using Codec = prefix_codec<int, M>;

    struct Case {
        const char* tag;
        std::vector<std::pair<int, unsigned>> codes;
    };
    const std::vector<Case> cases = {
        {"huff6", {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 6}}},
        {"skew6_1233", {{0, 1}, {1, 2}, {2, 3}, {3, 3}}},
        {"bal6_222", {{0, 2}, {1, 2}, {2, 2}, {3, 2}}},
    };

    for (const auto& cs : cases) {
        INFO("codec = " << cs.tag);
        Codec codec{cs.codes, 0};

        // Stored multiset: every member once, then a few skewed repeats.
        std::vector<int> seq;
        for (const auto& e : codec.entries()) seq.push_back(e.value);
        const int v0 = codec.entries().front().value;
        for (int r = 0; r < 5; ++r) seq.push_back(v0);

        std::vector<uint64_t> canon;
        for (int v : seq) canon.push_back(codec.encode(v));
        auto [hit_c, W_c] = class_hits_and_W(codec, canon, M);

        std::mt19937_64 rng{7777};
        int mismatches = 0;
        for (int t = 0; t < 300; ++t) {
            std::vector<uint64_t> rp;
            for (int v : seq) rp.push_back(random_within_class(codec, v, rng));
            auto [hit_r, W_r] = class_hits_and_W(codec, rp, M);
            for (size_t i = 0; i < hit_c.size(); ++i) {
                if (hit_c[i] * W_r != hit_r[i] * W_c) ++mismatches;
            }
        }
        REQUIRE(mismatches == 0);
    }
}

// ===== (2) EMPIRICAL invariance + (3) WHITE-BOX divergence on real ribbons =====

TEST_CASE("randomized encoding: off-set law invisible, white-box snapshot divergent",
          "[prefix_codec][randomized][invariance]") {
    constexpr unsigned M = 8;
    using Codec = prefix_codec<int, M>;
    using ribbon = ribbon_retrieval<M>;
    using enc_t = encoded_retrieval<ribbon, Codec>;

    // An 8-bit Huffman-style skewed codec.
    Codec codec{{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 8}}, 0};

    // 2000 member keys with a skewed value assignment (short codes more common),
    // so the stored span is rich.
    const size_t N = 2000;
    auto keys = make_keys(N, 0);
    std::vector<int> vals;
    {
        std::mt19937_64 vrng{12345};
        std::array<double, 9> w = {0.5, 0.25, 0.125, 0.0625, 0.03125,
                                   0.015625, 0.0078125, 0.00390625, 0.00390625};
        std::discrete_distribution<int> vd(w.begin(), w.end());
        for (size_t i = 0; i < N; ++i) vals.push_back(vd(vrng));
    }

    std::vector<uint64_t> canon_pats;
    for (int v : vals) canon_pats.push_back(codec.encode(v));

    std::vector<uint64_t> rand_pats;
    {
        std::mt19937_64 erng{999};
        for (int v : vals) rand_pats.push_back(random_within_class(codec, v, erng));
    }

    // Both pattern sets must decode to the same logical values (within-class
    // randomization does not change the decoded value).
    for (size_t i = 0; i < N; ++i) {
        REQUIRE(codec.decode(canon_pats[i]) == vals[i]);
        REQUIRE(codec.decode(rand_pats[i]) == vals[i]);
    }

    // Canonical build via encoded_retrieval (the production path), and a
    // randomized build by driving the ribbon builder directly with the
    // within-class patterns (the Q#5 variant), then wrapping in the same codec.
    enc_t enc_canon =
        [&] {
            typename enc_t::builder b{codec};
            for (size_t i = 0; i < N; ++i) b.add(keys[i], vals[i]);
            b.with_seed(2024);
            auto r = b.build();
            REQUIRE(r.has_value());
            return std::move(*r);
        }();
    ribbon rib_rand = build_ribbon<M>(keys, rand_pats, 2024);
    enc_t enc_rand{rib_rand, codec};

    // (a) member correctness in both builds.
    for (size_t i = 0; i < N; ++i) {
        REQUIRE(enc_canon.lookup(keys[i]) == vals[i]);
        REQUIRE(enc_rand.lookup(keys[i]) == vals[i]);
    }

    // (b) non-member decoded-value distributions agree within sampling noise.
    const size_t Q = 30000;
    std::array<size_t, 9> cnt_canon{}, cnt_rand{};
    for (size_t i = 0; i < Q; ++i) {
        std::string k = "NONMEMBER_query_" + std::to_string(i);
        int a = enc_canon.lookup(k);
        int b = enc_rand.lookup(k);
        if (a >= 0 && a < 9) cnt_canon[static_cast<size_t>(a)]++;
        if (b >= 0 && b < 9) cnt_rand[static_cast<size_t>(b)]++;
    }
    double tv = 0.0;
    for (int v = 0; v < 9; ++v) {
        tv += std::fabs(static_cast<double>(cnt_canon[static_cast<size_t>(v)]) / Q -
                        static_cast<double>(cnt_rand[static_cast<size_t>(v)]) / Q);
    }
    tv *= 0.5;
    INFO("non-member TV(canonical, randomized) = " << tv);
    REQUIRE(tv < 0.03);  // sampling noise only: the off-set law is invisible

    // (c) WHITE-BOX divergence: the serialized solution bytes differ
    // substantially, while the decoded non-member law is the same.
    auto sc = enc_canon.serialize();
    auto sr = enc_rand.serialize();
    REQUIRE(sc.size() == sr.size());
    size_t diff_bytes = 0;
    for (size_t i = 0; i < sc.size(); ++i) {
        if (sc[i] != sr[i]) ++diff_bytes;
    }
    INFO("white-box solution bytes differing = " << diff_bytes << " / " << sc.size());
    // A substantial fraction of the solution bytes differ (the snapshot is a
    // different RHS solution). Require at least a quarter to differ; in practice
    // it is well over half.
    REQUIRE(diff_bytes * 4 > sc.size());
    REQUIRE(diff_bytes < sc.size());  // not a trivial all-bytes-differ artifact
}
