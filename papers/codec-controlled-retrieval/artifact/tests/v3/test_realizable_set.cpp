/**
 * @file test_realizable_set.cpp
 * @brief Complete characterization of the realizable non-member-mass set for a
 *        skewed codec (the open item T4b flagged: the ladder is necessary, not
 *        sufficient).
 *
 * For a fixed prefix codec, the realizable laws are exactly the image of the
 * subspace map W |-> q, q(v) = |class(v) intersect W| / |W|, over all subspaces
 * W of GF(2)^M (the constructive characterization). This test enumerates that
 * image exactly for M = 4 and checks the clean NECESSARY conditions, the corrected
 * diagnosis of why the uniform vector is unreachable, the SUFFICIENCY of the clean
 * conditions for the thin {1,2,3,3} codec, and a SHARP witness ({2,2,3,3,3,3})
 * where the clean conditions are NOT sufficient.
 *
 * Clean necessary conditions on a realizable q:
 *   - q is a dyadic probability vector;
 *   - q(v) in {0} union {2^-r : 0 <= r <= l_v} (so the reduced denominator is a
 *     power of two at most 2^{l_v}, numerator 0 or 1);
 *   - a value whose codeword is all-zero is ALWAYS hit (q(v) > 0);
 *   - mass >= codespace share: q(v) > 0 implies q(v) >= 2^{-l_v};
 *   - the ladder: l(u) <= l(v) and both hit implies q(u) >= q(v) (so hit values of
 *     the same length carry equal mass).
 *
 * The paper's earlier "uniform vector is unreachable" remark is sharpened here: the
 * uniform law fails the MASS >= SHARE bound (q(A) = 1/4 < 2^{-l_A} = 1/2), not the
 * ladder (which the uniform vector satisfies). And the clean conditions are not a
 * complete local description: {2,2,3,3,3,3} has clean laws no subspace realizes,
 * because which same-length codewords are simultaneously hit is a HIT-GEOMETRY
 * constraint of the subspace chain, not a per-value condition.
 *
 * Pure exact-integer GF(2) algebra; 4-space indent, 100 cols, no em-dashes.
 */

#include <catch2/catch_test_macros.hpp>

#include <maph/codecs/prefix_codec.hpp>
#include <maph/detail/gf2.hpp>

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <set>
#include <vector>

using namespace maph;

namespace {

constexpr unsigned M = 4;

// A reduced fraction (num, den); a Law is one reduced mass per codec entry, in
// entries() order. Exact, so laws compare and dedup with no floating point.
using Frac = std::pair<uint64_t, uint64_t>;
using Law = std::vector<Frac>;

Frac reduce(uint64_t n, uint64_t d) {
    const uint64_t g = std::gcd(n, d);
    return g ? Frac{n / g, d / g} : Frac{0, d};
}

// Top-l-bit mask on M bits.
uint32_t mask_top(unsigned l) {
    return (l >= M) ? static_cast<uint32_t>((uint64_t{1} << M) - 1)
                    : static_cast<uint32_t>((((uint64_t{1} << M) - 1) >> (M - l)) << (M - l));
}

// All subspaces of GF(2)^M, each as a sorted vector of its elements. Enumerate by
// taking every subset of {0..2^M-1} of size <= M as a spanning set (M=4: 2^16
// masks, popcount <= 4), spanning and deduping.
std::vector<std::vector<uint64_t>> all_subspaces() {
    std::set<std::vector<uint64_t>> seen;
    const uint32_t N = 1u << M;  // 16 universe elements
    for (uint32_t sub = 0; sub < (1u << N); ++sub) {
        if (static_cast<unsigned>(__builtin_popcount(sub)) > M) continue;
        std::vector<uint64_t> gens;
        for (uint32_t i = 0; i < N; ++i)
            if (sub & (1u << i)) gens.push_back(i);
        auto span = maph::detail::gf2_span(maph::detail::gf2_basis(gens));
        std::sort(span.begin(), span.end());
        seen.insert(std::move(span));
    }
    return {seen.begin(), seen.end()};
}

// q(v) = |class(v) intersect S| / |S| for each codec entry, reduced.
template <typename Codec>
Law law_of_subspace(const Codec& codec, const std::vector<uint64_t>& S) {
    const uint64_t n = S.size();
    Law q;
    for (const auto& e : codec.entries()) {
        const uint32_t m = mask_top(e.length);
        const uint32_t code = static_cast<uint32_t>(e.prefix_left_aligned) & m;
        uint64_t c = 0;
        for (uint64_t x : S)
            if ((static_cast<uint32_t>(x) & m) == code) ++c;
        q.push_back(reduce(c, n));
    }
    return q;
}

template <typename Codec>
std::set<Law> realizable_set(const Codec& codec) {
    std::set<Law> R;
    for (const auto& S : all_subspaces()) R.insert(law_of_subspace(codec, S));
    return R;
}

bool is_power_of_two(uint64_t x) { return x && ((x & (x - 1)) == 0); }

// q(v) >= 2^{-l}  <=>  num * 2^l >= den.
bool ge_share(const Frac& q, unsigned l) {
    return (q.first << l) >= q.second;
}

template <typename Codec>
bool mass_ge_share(const Codec& codec, const Law& q) {
    const auto& es = codec.entries();
    for (std::size_t i = 0; i < es.size(); ++i)
        if (q[i].first != 0 && !ge_share(q[i], es[i].length)) return false;
    return true;
}

template <typename Codec>
bool ladder(const Codec& codec, const Law& q) {
    const auto& es = codec.entries();
    for (std::size_t i = 0; i < es.size(); ++i) {
        for (std::size_t j = 0; j < es.size(); ++j) {
            if (q[i].first == 0 || q[j].first == 0) continue;     // hits only
            if (es[i].length <= es[j].length) {
                // q[i] >= q[j]  <=>  num_i * den_j >= num_j * den_i
                if (q[i].first * q[j].second < q[j].first * q[i].second) return false;
            }
        }
    }
    return true;
}

template <typename Codec>
bool dyadic_capped(const Codec& codec, const Law& q) {
    const auto& es = codec.entries();
    for (std::size_t i = 0; i < es.size(); ++i) {
        if (q[i].first == 0) continue;
        if (q[i].first != 1) return false;                 // nonzero mass is 2^-r
        if (!is_power_of_two(q[i].second)) return false;
        if (q[i].second > (uint64_t{1} << es[i].length)) return false;  // r <= l_v
    }
    return true;
}

bool sums_to_one(const Law& q) {
    // common denominator is a power of two <= 2^M; scale to 2^M and sum.
    uint64_t acc = 0;
    const uint64_t D = uint64_t{1} << M;
    for (const auto& f : q) acc += f.first * (D / f.second);
    return acc == D;
}

// Is the codeword of entry i all-zero (so the value is always hit)?
template <typename Codec>
bool zero_codeword(const Codec& codec, std::size_t i) {
    const auto& e = codec.entries()[i];
    return (static_cast<uint32_t>(e.prefix_left_aligned) & mask_top(e.length)) == 0;
}

// The allowed reduced masses for entry i: {0} union {2^-r : 0<=r<=l}, dropping 0
// when the codeword is all-zero (always hit).
template <typename Codec>
std::vector<Frac> allowed(const Codec& codec, std::size_t i) {
    std::vector<Frac> out;
    if (!zero_codeword(codec, i)) out.push_back({0, 1});
    const unsigned l = codec.entries()[i].length;
    for (unsigned r = 0; r <= l; ++r) out.push_back({1, uint64_t{1} << r});
    return out;
}

// All candidate laws satisfying the clean conditions (sum 1, mass>=share, ladder).
template <typename Codec>
std::set<Law> clean_candidates(const Codec& codec) {
    const std::size_t k = codec.entries().size();
    std::vector<std::vector<Frac>> opt(k);
    for (std::size_t i = 0; i < k; ++i) opt[i] = allowed(codec, i);

    std::set<Law> out;
    std::vector<std::size_t> idx(k, 0);
    for (;;) {
        Law q(k);
        for (std::size_t i = 0; i < k; ++i) q[i] = opt[i][idx[i]];
        if (sums_to_one(q) && mass_ge_share(codec, q) && ladder(codec, q)) out.insert(q);
        // odometer increment
        std::size_t p = 0;
        for (; p < k; ++p) {
            if (++idx[p] < opt[p].size()) break;
            idx[p] = 0;
        }
        if (p == k) break;
    }
    return out;
}

enum class V4 : uint8_t { A, B, C, D };

prefix_codec<V4, M> skew_codec() {
    return prefix_codec<V4, M>{{{V4::A, 1}, {V4::B, 2}, {V4::C, 3}, {V4::D, 3}}, V4::A};
}

// {2,2,3,3,3,3}: two length-2 codewords and four length-3 codewords, Kraft = 1.
prefix_codec<int, M> mix_codec() {
    return prefix_codec<int, M>{{{0, 2}, {1, 2}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}, 0};
}

}  // namespace

// ===== {1,2,3,3}: the realizable set, the necessary conditions, the uniform diagnosis. =====

TEST_CASE("realizable set: skew {1,2,3,3} has exactly 8 realizable laws, all clean",
          "[prefix_codec][realizable]") {
    auto cdc = skew_codec();
    const auto R = realizable_set(cdc);

    REQUIRE(R.size() == 8u);  // the complete realizable image of the subspace map

    // Every realizable law satisfies the clean necessary conditions.
    for (const auto& q : R) {
        REQUIRE(sums_to_one(q));
        REQUIRE(dyadic_capped(cdc, q));
        REQUIRE(mass_ge_share(cdc, q));
        REQUIRE(ladder(cdc, q));
        // The all-zero-codeword value A is always hit.
        REQUIRE(q[static_cast<std::size_t>(V4::A)].first != 0);
    }

    // Two anchors are present: the designed Kraft law and the degenerate W = {0}.
    const Law kraft = {{1, 2}, {1, 4}, {1, 8}, {1, 8}};
    const Law allA = {{1, 1}, {0, 1}, {0, 1}, {0, 1}};
    REQUIRE(R.count(kraft) == 1u);
    REQUIRE(R.count(allA) == 1u);
}

TEST_CASE("realizable set: uniform is unreachable via MASS-SHARE, not the ladder",
          "[prefix_codec][realizable]") {
    auto cdc = skew_codec();
    const auto R = realizable_set(cdc);

    // The uniform law (1/4,1/4,1/4,1/4).
    const Law uniform = {{1, 4}, {1, 4}, {1, 4}, {1, 4}};

    REQUIRE(R.count(uniform) == 0u);          // not realizable
    REQUIRE(sums_to_one(uniform));
    REQUIRE(ladder(cdc, uniform));            // the ladder does NOT exclude it
    REQUIRE_FALSE(mass_ge_share(cdc, uniform));  // q(A)=1/4 < 2^-1: THIS is why

    // Sharpened: the obstruction is the codespace-share floor on the shortest value,
    // not the non-increasing ladder the earlier draft invoked.
}

TEST_CASE("realizable set: for {1,2,3,3} the clean conditions are SUFFICIENT (clean == R)",
          "[prefix_codec][realizable]") {
    auto cdc = skew_codec();
    const auto R = realizable_set(cdc);
    const auto clean = clean_candidates(cdc);
    REQUIRE(clean == R);  // complete local description for this thin codec
}

// ===== {2,2,3,3,3,3}: the clean conditions are NOT sufficient (hit-geometry). =====

TEST_CASE("realizable set: {2,2,3,3,3,3} has clean laws no subspace realizes",
          "[prefix_codec][realizable]") {
    auto cdc = mix_codec();
    const auto R = realizable_set(cdc);
    const auto clean = clean_candidates(cdc);

    // The clean conditions are strictly weaker than realizability here.
    REQUIRE(clean.size() > R.size());
    for (const auto& q : R) REQUIRE(clean.count(q) == 1u);  // R is contained in clean

    // A concrete clean-but-unrealizable witness: both length-2 values at 1/4 and
    // two of the four length-3 values at 1/4 (the other two missed). It satisfies
    // sum = 1, mass >= share, and the ladder, yet no subspace realizes it. The two
    // length-3 hits 100,101 at mass 1/4 force pi_3(W) = span{100,101} =
    // {000,001,100,101}; its truncation to the top 2 bits is {00,10}, dimension 1,
    // so the length-2 codeword 01 is missed (mass 0) instead of 1/4. But the two
    // length-2 hits at 1/4 demanded pi_2(W) full (dim 2). The rungs clash under
    // truncation: a hit-geometry obstruction no per-value condition can see.
    const Law witness = {{1, 4}, {1, 4}, {1, 4}, {1, 4}, {0, 1}, {0, 1}};
    REQUIRE(sums_to_one(witness));
    REQUIRE(mass_ge_share(cdc, witness));
    REQUIRE(ladder(cdc, witness));
    REQUIRE(clean.count(witness) == 1u);   // clean
    REQUIRE(R.count(witness) == 0u);       // but NOT realizable
}
