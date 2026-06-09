/**
 * @file test_cogirth_graded.cpp
 * @brief T5c: for a SKEWED (graded) codec, the robustness of codec control under
 *        key erasure is a per-rung FAMILY of matroid cogirths, one per code
 *        length, with T5b the length-uniform single-rung collapse.
 *
 * This is the computational gate for the T5c subsection of
 * docs/codec_controlled_retrieval.md. Like the T4b gate
 * (test_skewed_realizability.cpp) it is a PURE GF(2) linear-algebra check on the
 * stored-pattern span W and the codec; it does NOT build a ribbon structure. The
 * bridge from W to actual non-member queries is T1/T2 (R(z) = W, idealized output
 * uniform on W), already proven and exercised by the [span]/[nonmember] tests.
 *
 * Where T4 (balanced) and T5b (balanced) act through a SINGLE class-naming
 * projection pi onto the top k codeword bits, a skewed codec has a DIFFERENT
 * within-class subspace C_{l_v} per code length, forming the nested flag
 * {0} = C_M subset ... subset C_1 (dim C_l = M - l). T5c indexes both control and
 * robustness by that flag.
 *
 * The per-rung projection. pi_v : GF(2)^M -> GF(2)^M / C_{l_v} keeps the top l_v
 * bits (two patterns agree mod C_{l_v} iff their top l_v bits agree).
 *
 * The bridge identity (per-rung control formula). By rank-nullity on pi_v|_W
 * (ker pi_v = C_{l_v}),  rank pi_v(W) = dim W - dim(W cap C_{l_v}),  so the T4b
 * flag formula rewrites as
 *
 *     q(v) = h_v * 2^( - rank pi_v(W) ),     h_v = [ pi_v(aligned(v)) in pi_v(W) ].
 *
 * Hence q(v) depends on W ONLY through pi_v(W): the per-rung analogue of T4's
 * "control is a function of pi(W)".
 *
 * The per-rung cogirth. Because q(v) is a function of pi_v(W) alone, and pi_v(W)
 * (a finite-dimensional span) changes under erasure iff its rank drops, the
 * minimum number of stored-key erasures (with multiplicity) that changes q(v) for
 * a HIT rung v is exactly the matroid cogirth / dual distance of the pi_v-PROJECTED
 * stored column multiset:
 *
 *     d*_rung(v) = total - max over functionals a nontrivial on the columns of
 *                  #{ projected columns c : <c, a> = 0 }.
 *
 * For a MISSED rung (h_v = 0) erasure only shrinks W, so pi_v(aligned(v)) stays
 * outside pi_v(W); q(v) is pinned at 0 and d*_rung(v) = infinity.
 *
 * The graded threshold and the cascade.
 *   - The whole law q first changes at  d*_graded = min over HIT rungs of d*_rung(v).
 *   - Past it the law degrades RUNG BY RUNG: a GRADUAL multi-threshold cascade
 *     (first change at d*_graded, then further breaks at the cogirths of the REDUCED
 *     systems; the witness changes at 3, 6, 9, and 6 is not a per-rung cogirth),
 *     mass conserved and redistributed per the T4b flag formula, NOT the single
 *     sharp TV = 0.5 step of T5b.
 *   - T5b is the length-uniform collapse: when all l_v are equal there is one
 *     subspace C_k, one projection, one cogirth d* = (K/2) m shared by every rung,
 *     and the cascade becomes the single T5b step.
 *
 * Witness: skew {1,2,3,3} on M = 4, uniform multiplicity m = 3 (12 stored keys).
 *   q = (1/2, 1/4, 1/8, 1/8);  per-rung cogirth (A,B,C,D) = (9, 3, 3, 3);
 *   d*_graded = 3;  cascade thresholds at 3, 6, 9.
 *
 * 4-space indent, 100-char lines, no em-dashes.
 */

#include <catch2/catch_test_macros.hpp>

#include <maph/codecs/prefix_codec.hpp>
#include <maph/detail/gf2.hpp>

#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

using namespace maph;

namespace {

// The graded witness alphabet: A,B,C,D with lengths {1,2,3,3}.
enum class V : uint8_t { A, B, C, D };
constexpr unsigned M = 4;
constexpr std::size_t INF = std::numeric_limits<std::size_t>::max();
constexpr double EXACT = 1e-9;

using Codec = prefix_codec<V, M>;

// Skew {1,2,3,3} codec on M = 4. Kraft = 1/2 + 1/4 + 1/8 + 1/8 = 1 (tight).
Codec skew_codec() {
    return Codec{{{V::A, 1}, {V::B, 2}, {V::C, 3}, {V::D, 3}}, V::A};
}

// Balanced length-2 codec on M = 4: K = 4 classes, k = 2, all lengths equal. The
// single-rung (T5b) regime.
Codec balanced_codec() {
    return Codec{{{V::A, 2}, {V::B, 2}, {V::C, 2}, {V::D, 2}}, V::A};
}

constexpr std::array<V, 4> ALPHABET = {V::A, V::B, V::C, V::D};

std::size_t idx(V v) { return static_cast<std::size_t>(v); }

unsigned length_of(const Codec& cdc, V v) {
    for (const auto& e : cdc.entries())
        if (e.value == v) return e.length;
    return 0;
}

// pi_v image rep: keep the top `length` bits, zero the bottom (M - length).
uint64_t project_mod_C(uint64_t pattern, unsigned length) {
    if (length >= M) return pattern & ((uint64_t{1} << M) - 1);
    const uint64_t mask = (((uint64_t{1} << M) - 1) >> (M - length)) << (M - length);
    return pattern & mask;
}

// Encode a list of stored VALUES to their canonical left-aligned patterns.
std::vector<uint64_t> encode_all(const Codec& cdc, const std::vector<V>& values) {
    std::vector<uint64_t> out;
    out.reserve(values.size());
    for (V v : values) out.push_back(cdc.encode(v));
    return out;
}

// q(v) for every value by ENUMERATION of W: enumerate the span, decode each
// element, tally per value, normalize by |W|. Dyadic rationals, exact compare.
std::array<double, 4> mass_by_enumeration(const Codec& cdc,
                                          const std::vector<uint64_t>& stored) {
    const auto basis = detail::gf2_basis(stored);
    const auto span = detail::gf2_span(basis);
    std::array<double, 4> q{0.0, 0.0, 0.0, 0.0};
    for (uint64_t p : span) q[idx(cdc.decode(p))] += 1.0;
    for (auto& x : q) x /= static_cast<double>(span.size());
    return q;
}

// rank pi_v(W): apply pi_v to a basis of W, take the GF(2) rank of the images.
std::size_t proj_rank(const std::vector<uint64_t>& W_basis, unsigned length) {
    std::vector<uint64_t> img;
    img.reserve(W_basis.size());
    for (uint64_t w : W_basis) img.push_back(project_mod_C(w, length));
    return detail::gf2_rank(img);
}

// hit indicator h_v = [ pi_v(aligned(v)) in pi_v(W) ].
bool hit_indicator(const Codec& cdc, V v, const std::vector<uint64_t>& W_basis) {
    const unsigned l = length_of(cdc, v);
    std::vector<uint64_t> img;
    img.reserve(W_basis.size());
    for (uint64_t w : W_basis) img.push_back(project_mod_C(w, l));
    return detail::gf2_in_span(project_mod_C(cdc.encode(v), l), detail::gf2_basis(img));
}

// q(v) by the BRIDGE IDENTITY  q(v) = h_v * 2^(-rank pi_v(W)).
std::array<double, 4> mass_by_bridge(const Codec& cdc,
                                     const std::vector<uint64_t>& stored) {
    const auto W_basis = detail::gf2_basis(stored);
    std::array<double, 4> q{0.0, 0.0, 0.0, 0.0};
    for (V v : ALPHABET) {
        if (!hit_indicator(cdc, v, W_basis)) continue;
        const std::size_t r = proj_rank(W_basis, length_of(cdc, v));
        q[idx(v)] = std::ldexp(1.0, -static_cast<int>(r));
    }
    return q;
}

// The pi_v-projected stored column multiset (one projected column per stored key).
std::vector<uint64_t> projected_columns(const Codec& cdc, V v,
                                        const std::vector<V>& stored_values) {
    const unsigned l = length_of(cdc, v);
    std::vector<uint64_t> cols;
    cols.reserve(stored_values.size());
    for (V sv : stored_values) cols.push_back(project_mod_C(cdc.encode(sv), l));
    return cols;
}

// Matroid cogirth of a column multiset over GF(2)^M: the minimum number of columns
// (with multiplicity) whose deletion drops the column rank. Ambient-functional
// form: d* = total - max over functionals a that are NONTRIVIAL on the columns of
// #{ c : <c,a> = 0 }. A functional a is nontrivial on the columns iff some column
// lies outside ker(a), i.e. (#in_ker < total); this excludes a perpendicular to
// span(columns). Returns INF when the columns have rank 0 (nothing to drop).
std::size_t cogirth_projected(const std::vector<uint64_t>& cols) {
    const std::size_t total = cols.size();
    long long best_in = -1;
    for (uint64_t a = 1; a < (uint64_t{1} << M); ++a) {
        std::size_t in_ker = 0;
        for (uint64_t c : cols)
            if ((__builtin_popcountll(c & a) & 1) == 0) ++in_ker;
        if (in_ker < total)  // a is nontrivial on the columns (a proper hyperplane)
            best_in = std::max(best_in, static_cast<long long>(in_ker));
    }
    if (best_in < 0) return INF;  // rank 0: no proper hyperplane, unbreakable
    return total - static_cast<std::size_t>(best_in);
}

// d*_rung(v): hit rungs use the projected cogirth, missed rungs are pinned at INF.
std::size_t d_star_rung(const Codec& cdc, V v, const std::vector<V>& stored_values) {
    const auto W_basis = detail::gf2_basis(encode_all(cdc, stored_values));
    if (!hit_indicator(cdc, v, W_basis)) return INF;
    return cogirth_projected(projected_columns(cdc, v, stored_values));
}

// d*_graded: the minimum per-rung cogirth over HIT rungs (the first whole-law change).
std::size_t d_star_graded(const Codec& cdc, const std::vector<V>& stored_values) {
    std::size_t best = INF;
    for (V v : ALPHABET) best = std::min(best, d_star_rung(cdc, v, stored_values));
    return best;
}

// EXHAUSTIVE ground truth: the minimum size of a stored-key erasure that CHANGES
// q(target), over all 2^n erasure subsets. Returns INF if no erasure changes it
// (a missed rung, pinned at 0). n is small (<= 12 here), so 2^n is cheap.
std::size_t exhaustive_first_change(const Codec& cdc, V target,
                                    const std::vector<V>& stored_values) {
    const std::size_t n = stored_values.size();
    const double q0 = mass_by_enumeration(cdc, encode_all(cdc, stored_values))[idx(target)];
    std::size_t best = INF;
    for (uint32_t mask = 1; mask < (uint32_t{1} << n); ++mask) {
        std::vector<V> surv;
        for (std::size_t i = 0; i < n; ++i)
            if (!(mask & (uint32_t{1} << i))) surv.push_back(stored_values[i]);
        const double q = mass_by_enumeration(cdc, encode_all(cdc, surv))[idx(target)];
        if (std::abs(q - q0) > EXACT) {
            const std::size_t sz = static_cast<std::size_t>(__builtin_popcount(mask));
            best = std::min(best, sz);
        }
    }
    return best;
}

// Build [A x m, B x m, C x m, D x m] (uniform multiplicity over the full alphabet).
std::vector<V> uniform_support(std::size_t m) {
    std::vector<V> out;
    for (V v : ALPHABET)
        for (std::size_t j = 0; j < m; ++j) out.push_back(v);
    return out;
}

}  // namespace

// ===== The bridge identity: q(v) = h_v * 2^(-rank pi_v(W)) on several W. =====

TEST_CASE("T5c: bridge identity q(v) = h_v * 2^(-rank pi_v(W)) matches enumeration",
          "[cogirth][graded]") {
    auto cdc = skew_codec();

    // For each stored-value set (hence subspace W) the bridge formula must agree
    // with the enumerated mass, value by value. This is the T4b flag formula
    // rewritten through rank-nullity (rank pi_v(W) = dim W - dim(W cap C_{l_v})),
    // so it also re-confirms T4b on these W.
    const std::vector<std::vector<V>> stored_sets = {
        {V::A}, {V::A, V::B}, {V::B, V::C}, {V::A, V::B, V::C},
        {V::B, V::C, V::D}, {V::A, V::B, V::C, V::D},
    };
    for (const auto& vs : stored_sets) {
        const auto stored = encode_all(cdc, vs);
        const auto q_enum = mass_by_enumeration(cdc, stored);
        const auto q_brdg = mass_by_bridge(cdc, stored);
        for (std::size_t i = 0; i < 4; ++i)
            REQUIRE(std::abs(q_enum[i] - q_brdg[i]) < EXACT);
    }
}

// ===== The witness: per-rung cogirth family (9,3,3,3), d*_graded = 3. =====

TEST_CASE("T5c: witness skew {1,2,3,3}, m=3 has per-rung cogirth (A,B,C,D)=(9,3,3,3)",
          "[cogirth][graded]") {
    auto cdc = skew_codec();
    const std::vector<V> stored = uniform_support(3);  // 12 keys
    REQUIRE(stored.size() == 12u);

    // Baseline graded law q = (1/2, 1/4, 1/8, 1/8): all four rungs hit, distinct
    // positive masses (the T4b graded regime).
    const auto q0 = mass_by_enumeration(cdc, encode_all(cdc, stored));
    REQUIRE(std::abs(q0[idx(V::A)] - 0.5) < EXACT);
    REQUIRE(std::abs(q0[idx(V::B)] - 0.25) < EXACT);
    REQUIRE(std::abs(q0[idx(V::C)] - 0.125) < EXACT);
    REQUIRE(std::abs(q0[idx(V::D)] - 0.125) < EXACT);

    // The per-rung cogirth FAMILY: the coarse short-codeword rung A is the most
    // redundantly supported (9 of 12 projected columns carry its top bit), so it
    // is the LAST to break; the three thin length-3 rungs break first at 3.
    REQUIRE(d_star_rung(cdc, V::A, stored) == 9u);
    REQUIRE(d_star_rung(cdc, V::B, stored) == 3u);
    REQUIRE(d_star_rung(cdc, V::C, stored) == 3u);
    REQUIRE(d_star_rung(cdc, V::D, stored) == 3u);

    // The whole-law erasure budget is the thinnest hit rung.
    REQUIRE(d_star_graded(cdc, stored) == 3u);

    // The family is genuinely NON-CONSTANT across rungs (this is what makes T5c
    // strictly richer than T5b: a skewed codec has rungs of different robustness).
    REQUIRE(d_star_rung(cdc, V::A, stored) != d_star_rung(cdc, V::B, stored));
}

// ===== The cogirth IS the exact q(v)-change threshold (exhaustive ground truth). =====

TEST_CASE("T5c: per-rung cogirth equals the exhaustive first-change threshold",
          "[cogirth][graded]") {
    auto cdc = skew_codec();
    const std::vector<V> stored = uniform_support(3);  // 12 keys, 2^12 subsets

    // The closed-form per-rung cogirth must equal the exact minimum erasure size
    // that changes q(v), found by exhaustive search over all 2^12 subsets. This is
    // the load-bearing claim: d*_rung(v) is the real adversarial budget for rung v.
    for (V v : ALPHABET) {
        const std::size_t closed = d_star_rung(cdc, v, stored);
        const std::size_t exact = exhaustive_first_change(cdc, v, stored);
        REQUIRE(closed == exact);
    }

    // Below the per-rung threshold q(v) is EXACTLY invariant for EVERY erasure of
    // that size; the exhaustive search returning the cogirth (not less) encodes
    // exactly that. Spot-check the universal direction for the thin rungs: no
    // single or double erasure changes q(C) (its cogirth is 3).
    REQUIRE(exhaustive_first_change(cdc, V::C, stored) >= 3u);
}

// ===== A MISSED rung is pinned at 0 under every erasure (d*_rung = INF). =====

TEST_CASE("T5c: a missed rung stays at 0 under every erasure (d*_rung = infinity)",
          "[cogirth][graded]") {
    auto cdc = skew_codec();

    // Store only A and B (m = 2 each): the length-3 classes C and D are MISSED.
    const std::vector<V> stored = {V::A, V::A, V::B, V::B};
    const auto q0 = mass_by_enumeration(cdc, encode_all(cdc, stored));
    REQUIRE(std::abs(q0[idx(V::C)]) < EXACT);  // C missed
    REQUIRE(std::abs(q0[idx(V::D)]) < EXACT);  // D missed

    // Missed rungs are pinned: no erasure makes them positive (erasure only shrinks
    // W, and a missed class never becomes hit). d*_rung = INF.
    REQUIRE(d_star_rung(cdc, V::C, stored) == INF);
    REQUIRE(d_star_rung(cdc, V::D, stored) == INF);
    REQUIRE(exhaustive_first_change(cdc, V::C, stored) == INF);
    REQUIRE(exhaustive_first_change(cdc, V::D, stored) == INF);

    // The two HIT rungs A, B still have finite budgets (graded family is partial).
    REQUIRE(d_star_rung(cdc, V::A, stored) != INF);
    REQUIRE(d_star_rung(cdc, V::B, stored) != INF);
}

// ===== The CASCADE: gradual, multi-threshold, mass-conserving. =====

TEST_CASE("T5c: the law degrades RUNG BY RUNG at thresholds 3, 6, 9 (gradual cascade)",
          "[cogirth][graded]") {
    auto cdc = skew_codec();
    // Stored order A,A,A, B,B,B, C,C,C, D,D,D  (indices 0..11).
    const std::vector<V> stored = uniform_support(3);

    // Adversary erases in the worst order B, C, D, A (thinnest hit rungs first):
    // indices 3,4,5 then 6,7,8 then 9,10,11 then 0,1,2.
    const std::vector<std::size_t> order = {3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2};

    std::vector<bool> erased(stored.size(), false);
    std::array<double, 4> prev = mass_by_enumeration(cdc, encode_all(cdc, stored));
    std::vector<std::size_t> change_points;
    std::vector<std::array<double, 4>> snapshots;

    for (std::size_t step = 1; step <= order.size(); ++step) {
        erased[order[step - 1]] = true;
        std::vector<V> surv;
        for (std::size_t i = 0; i < stored.size(); ++i)
            if (!erased[i]) surv.push_back(stored[i]);
        const auto q = mass_by_enumeration(cdc, encode_all(cdc, surv));

        bool changed = false;
        for (std::size_t i = 0; i < 4; ++i)
            if (std::abs(q[i] - prev[i]) > EXACT) changed = true;
        if (changed) {
            change_points.push_back(step);
            snapshots.push_back(q);
            prev = q;
        }
    }

    // GRADUAL multi-threshold: the law changes at 3, then 6, then 9 (not one step).
    REQUIRE(change_points == std::vector<std::size_t>{3, 6, 9});

    // The snapshots match the predicted rung-by-rung redistribution. Each broken
    // rung sheds its mass onto surviving hit rungs (longer, equal, OR shorter in
    // codeword length: here B -> {C,D}, then C -> D, then D -> A) per the T4b flag
    // formula on the shrunken W, and the law stays a valid distribution (sums 1).
    REQUIRE(snapshots.size() == 3u);
    // @3 erasures (B gone): q = (1/2, 0, 1/4, 1/4).
    REQUIRE(std::abs(snapshots[0][idx(V::A)] - 0.5) < EXACT);
    REQUIRE(std::abs(snapshots[0][idx(V::B)] - 0.0) < EXACT);
    REQUIRE(std::abs(snapshots[0][idx(V::C)] - 0.25) < EXACT);
    REQUIRE(std::abs(snapshots[0][idx(V::D)] - 0.25) < EXACT);
    // @6 erasures (B, C gone): q = (1/2, 0, 0, 1/2).
    REQUIRE(std::abs(snapshots[1][idx(V::A)] - 0.5) < EXACT);
    REQUIRE(std::abs(snapshots[1][idx(V::C)] - 0.0) < EXACT);
    REQUIRE(std::abs(snapshots[1][idx(V::D)] - 0.5) < EXACT);
    // @9 erasures (B, C, D gone): q = (1, 0, 0, 0).
    REQUIRE(std::abs(snapshots[2][idx(V::A)] - 1.0) < EXACT);

    for (const auto& q : snapshots) {
        const double sum = q[0] + q[1] + q[2] + q[3];
        REQUIRE(std::abs(sum - 1.0) < EXACT);  // mass conserved through the cascade
    }
}

// ===== T5b is the single-rung collapse: length-uniform => all cogirths equal. =====

TEST_CASE("T5c: length-uniform codec collapses the family to the single T5b cogirth",
          "[cogirth][graded]") {
    auto cdc = balanced_codec();  // {2,2,2,2}, K = 4, k = 2

    // Balanced full support, uniform multiplicity m: one within-class subspace C_2,
    // one projection, so EVERY rung shares the same projected column system and the
    // same cogirth. That common value is the T5b closed form (K/2) m = 2 m.
    for (std::size_t m : {2u, 5u, 10u}) {
        const std::vector<V> stored = uniform_support(m);
        const std::size_t expect = (4u / 2u) * m;  // (K/2) m

        std::size_t common = d_star_rung(cdc, V::A, stored);
        REQUIRE(common == expect);
        for (V v : ALPHABET)
            REQUIRE(d_star_rung(cdc, v, stored) == common);  // single-rung regime

        // The whole-law budget equals the single shared cogirth (the T5b step).
        REQUIRE(d_star_graded(cdc, stored) == expect);
    }

    // Cross-check against the exhaustive threshold at m = 2 (8 keys, 2^8 subsets):
    // the single T5b cogirth (K/2) m = 4 is the exact first-change for every rung.
    const std::vector<V> stored2 = uniform_support(2);
    for (V v : ALPHABET)
        REQUIRE(exhaustive_first_change(cdc, v, stored2) == 4u);
}
