/**
 * @file test_randomized_boundary.cpp
 * @brief The skewed randomized-encoding invariance is FALSE in general; FULL
 *        SUPPORT is the proven sufficient condition (not necessary), and the
 *        intermediate SATURATION condition is refuted here too.
 *
 * This corrects the skewed half of the randomized-encoding lemma in
 * docs/codec_controlled_retrieval.md. The BALANCED case is unconditionally true
 * (single projection pi onto the top k bits, all within-class randomization lives
 * in ker pi, so pi(W) is fixed) and is gated by test_randomized_encoding.cpp.
 *
 * The skewed case is different: there is no single ker(pi). Randomizing a value of
 * length l' adds a vector in C_{l'} = ker(pi_{l'}). That vector is invisible to
 * pi_{l'} (and to any pi_l with l <= l'), but VISIBLE to pi_l for l > l' (a longer
 * codeword keeps more top bits). So randomizing a SHORT value can enlarge a LONGER
 * value's projection pi_l(W) and light up classes that were missed canonically.
 * Concretely, two independent randomizations of the length-1 value A inject two
 * top-3-bit directions; together with B's pattern they fill pi_3(W), turning the
 * missed length-3 classes C, D into hits. The non-member law q then CHANGES.
 *
 * The existing [randomized] test passes only because every case it stores has FULL
 * SUPPORT (one of each value); full support is the proven sufficient condition
 * (sibling-contraction argument in the note). SATURATION (every pi_l(W) full) was
 * an intermediate, WRONG sufficient condition: a saturated store can owe a
 * projection's fullness to short generators whose images move under redraw.
 *
 * Three gates:
 *   (1) COUNTEREXAMPLE: store {A,A,B} on skew {1,2,3,3}. Canonical q =
 *       (1/2,1/2,0,0). Exhaustively over all 256 within-class draws, more than one
 *       distinct law occurs (invariance FAILS), with an explicit breaking draw.
 *   (2) FULL SUPPORT: store {A,B,C,D} on {1,2,3,3}. Exhaustively over all 128
 *       within-class draws, EVERY draw reproduces the canonical law
 *       (1/2,1/4,1/8,1/8), the designed Kraft law.
 *   (3) SATURATION REFUTED: on {2,2,2,3,3}, the store {B,C,E} is saturated
 *       (pi_2 and pi_3 both full) WITHOUT full support, yet 16 of its 32
 *       within-class draws change the law (C -> 1010 collapses D to 0), while the
 *       full-support store {A..E} is invariant over all 256 draws.
 *
 * Pure exact-integer GF(2) algebra (no ribbon build); 4-space indent, 100 cols,
 * no em-dashes.
 */

#include <catch2/catch_test_macros.hpp>

#include <lapidary/codecs/prefix_codec.hpp>
#include <lapidary/detail/gf2.hpp>

#include <array>
#include <cstdint>
#include <numeric>
#include <set>
#include <vector>

using namespace lapidary;

namespace {

enum class V : uint8_t { A, B, C, D };
constexpr unsigned M = 4;

using Codec = prefix_codec<V, M>;

Codec skew_codec() {
    return Codec{{{V::A, 1}, {V::B, 2}, {V::C, 3}, {V::D, 3}}, V::A};
}

std::size_t idx(V v) { return static_cast<std::size_t>(v); }

// A law as four reduced (numerator, denominator) per-class masses, so distinct
// laws compare and hash exactly with no floating point.
using Law = std::array<std::pair<uint64_t, uint64_t>, 4>;

// q(v) = |class(v) intersect W| / |W| for every value, by enumerating W and
// decoding, returned as reduced fractions.
Law law_of(const Codec& cdc, const std::vector<uint64_t>& stored) {
    const auto basis = lapidary::detail::gf2_basis(stored);
    const auto span = lapidary::detail::gf2_span(basis);
    std::array<uint64_t, 4> hits{0, 0, 0, 0};
    for (uint64_t p : span) hits[idx(cdc.decode(p))] += 1;
    const uint64_t W = span.size();
    Law q;
    for (std::size_t i = 0; i < 4; ++i) {
        const uint64_t g = std::gcd(hits[i], W);
        q[i] = {g ? hits[i] / g : 0, g ? W / g : W};
    }
    return q;
}

// The class members of v: base | i for i in [0, count), where class_for gives
// (base, count = 2^(M - len(v))).
std::vector<uint64_t> class_members(const Codec& cdc, V v) {
    auto [base, count] = cdc.class_for(v);
    std::vector<uint64_t> out;
    out.reserve(count);
    for (uint64_t i = 0; i < count; ++i) out.push_back(base | i);
    return out;
}

// Rank of pi_l(W): project a basis of W onto its top l bits, take the GF(2) rank.
std::size_t proj_rank(const std::vector<uint64_t>& W_basis, unsigned l) {
    const uint64_t mask =
        (l >= M) ? ((uint64_t{1} << M) - 1)
                 : ((((uint64_t{1} << M) - 1) >> (M - l)) << (M - l));
    std::vector<uint64_t> img;
    img.reserve(W_basis.size());
    for (uint64_t w : W_basis) img.push_back(w & mask);
    return lapidary::detail::gf2_rank(img);
}

// Saturated iff every code length's projection pi_l(W) is full (dim l).
bool saturated(const Codec& cdc, const std::vector<uint64_t>& stored) {
    const auto basis = lapidary::detail::gf2_basis(stored);
    std::set<unsigned> lengths;
    for (const auto& e : cdc.entries()) lengths.insert(e.length);
    for (unsigned l : lengths)
        if (proj_rank(basis, l) != l) return false;
    return true;
}

std::vector<uint64_t> encode_all(const Codec& cdc, const std::vector<V>& vs) {
    std::vector<uint64_t> out;
    out.reserve(vs.size());
    for (V v : vs) out.push_back(cdc.encode(v));
    return out;
}

}  // namespace

// ===== (1) COUNTEREXAMPLE: skewed invariance FAILS on a partial-support store. =====

TEST_CASE("randomized boundary: skewed invariance FAILS for store {A,A,B}",
          "[prefix_codec][randomized][boundary]") {
    auto cdc = skew_codec();
    const std::vector<V> store = {V::A, V::A, V::B};  // A length-1 twice, B once, C/D unstored

    // Canonical law is (1/2, 1/2, 0, 0): W = span{0000,1000} = {0000,1000}.
    const Law canon = law_of(cdc, encode_all(cdc, store));
    REQUIRE(canon[idx(V::A)] == std::pair<uint64_t, uint64_t>{1, 2});
    REQUIRE(canon[idx(V::B)] == std::pair<uint64_t, uint64_t>{1, 2});
    REQUIRE(canon[idx(V::C)] == std::pair<uint64_t, uint64_t>{0, 1});
    REQUIRE(canon[idx(V::D)] == std::pair<uint64_t, uint64_t>{0, 1});

    // This store is NOT saturated: pi_3(W) is not full, which is what lets
    // short-value randomization create length-3 hits.
    REQUIRE_FALSE(saturated(cdc, encode_all(cdc, store)));

    // Exhaust all within-class draws (A: 8 members, A: 8, B: 4 = 256) and collect
    // the distinct realized laws. More than one occurs: invariance is broken.
    const auto Aopt = class_members(cdc, V::A);
    const auto Bopt = class_members(cdc, V::B);
    std::set<Law> laws;
    std::size_t canon_count = 0, total = 0;
    Law breaking{};
    bool found_breaking = false;
    for (uint64_t a1 : Aopt) {
        for (uint64_t a2 : Aopt) {
            for (uint64_t b : Bopt) {
                const Law q = law_of(cdc, {a1, a2, b});
                laws.insert(q);
                ++total;
                if (q == canon) ++canon_count;
                else if (!found_breaking) { breaking = q; found_breaking = true; }
            }
        }
    }

    REQUIRE(total == 256u);
    REQUIRE(laws.size() > 1u);          // INVARIANCE FAILS: many distinct laws
    REQUIRE(canon_count < total);       // not every draw reproduces the canonical law
    REQUIRE(found_breaking);

    // The explicit breaking draw A1=0000, A2=0100, B=1000 yields (1/2,1/4,1/4,0):
    // B drops from 1/2 to 1/4 and C lights up from 0 to 1/4.
    const Law q_break = law_of(cdc, {0b0000u, 0b0100u, 0b1000u});
    REQUIRE(q_break != canon);
    REQUIRE(q_break[idx(V::B)] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(q_break[idx(V::C)] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(q_break[idx(V::D)] == std::pair<uint64_t, uint64_t>{0, 1});
}

// ===== (2) FULL SUPPORT is the proven sufficient condition. =====

TEST_CASE("randomized boundary: full support restores EXACT invariance",
          "[prefix_codec][randomized][boundary]") {
    auto cdc = skew_codec();
    const std::vector<V> store = {V::A, V::B, V::C, V::D};  // full support

    // The canonical law is the designed Kraft law. (The store is incidentally also
    // saturated, but FULL SUPPORT is the operative, proven sufficient condition;
    // gate (3) below shows saturation alone is not enough.)
    const Law canon = law_of(cdc, encode_all(cdc, store));
    REQUIRE(canon[idx(V::A)] == std::pair<uint64_t, uint64_t>{1, 2});
    REQUIRE(canon[idx(V::B)] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(canon[idx(V::C)] == std::pair<uint64_t, uint64_t>{1, 8});
    REQUIRE(canon[idx(V::D)] == std::pair<uint64_t, uint64_t>{1, 8});
    REQUIRE(saturated(cdc, encode_all(cdc, store)));

    // Exhaust all within-class draws (A:8, B:4, C:2, D:2 = 128). Under full
    // support EVERY draw reproduces the canonical (designed Kraft) law.
    const auto Aopt = class_members(cdc, V::A);
    const auto Bopt = class_members(cdc, V::B);
    const auto Copt = class_members(cdc, V::C);
    const auto Dopt = class_members(cdc, V::D);
    std::set<Law> laws;
    std::size_t total = 0;
    for (uint64_t a : Aopt)
        for (uint64_t b : Bopt)
            for (uint64_t c : Copt)
                for (uint64_t d : Dopt) {
                    laws.insert(law_of(cdc, {a, b, c, d}));
                    ++total;
                }

    REQUIRE(total == 128u);
    REQUIRE(laws.size() == 1u);            // EXACT invariance over every draw
    REQUIRE(*laws.begin() == canon);
}

// ===== (3) SATURATION REFUTED: a saturated, non-full-support store breaks. =====
//
// On the codec {2,2,2,3,3} (canonical A=0000, B=0100, C=1000 of length 2;
// D=1100, E=1110 of length 3) the store {B, C, E} has every code-length
// projection FULL (pi_2 images {01,10,11}; pi_3 images {010,100,111}), i.e. it
// is saturated, but A and D are unstored. A redraw can drop a full projection:
// fullness here owes to SHORT generators' images, which move. The draw
// C -> 1010 makes 0100 ^ 1010 = 1110 = E's generator, collapsing dim W' to 2
// and the law from the designed (1/4,1/4,1/4,1/8,1/8) to (1/4,1/4,1/4,0,1/4).
// Exhaustively, 16 of the 32 draws of this store change the law. The
// full-support store {A..E} on the same codec is invariant over all 256 draws.

TEST_CASE("randomized boundary: SATURATION is not sufficient ({2,2,2,3,3} store {B,C,E})",
          "[prefix_codec][randomized][boundary]") {
    constexpr unsigned M5 = 4;
    enum class V5 : uint8_t { A, B, C, D, E };
    prefix_codec<V5, M5> cdc{
        {{V5::A, 2}, {V5::B, 2}, {V5::C, 2}, {V5::D, 3}, {V5::E, 3}}, V5::A};

    // Ground the canonical codewords this gate's arithmetic relies on.
    REQUIRE(cdc.encode(V5::A) == 0b0000u);
    REQUIRE(cdc.encode(V5::B) == 0b0100u);
    REQUIRE(cdc.encode(V5::C) == 0b1000u);
    REQUIRE(cdc.encode(V5::D) == 0b1100u);
    REQUIRE(cdc.encode(V5::E) == 0b1110u);

    // Exact law over 5 values: reduced (num, den) per class, by enumerating W.
    using Law5 = std::array<std::pair<uint64_t, uint64_t>, 5>;
    auto law5 = [&](const std::vector<uint64_t>& stored) {
        const auto span = lapidary::detail::gf2_span(lapidary::detail::gf2_basis(stored));
        std::array<uint64_t, 5> hits{0, 0, 0, 0, 0};
        for (uint64_t p : span) hits[static_cast<std::size_t>(cdc.decode(p))] += 1;
        Law5 q;
        for (std::size_t i = 0; i < 5; ++i) {
            const uint64_t g = std::gcd(hits[i], static_cast<uint64_t>(span.size()));
            q[i] = {g ? hits[i] / g : 0, g ? span.size() / g : span.size()};
        }
        return q;
    };
    auto proj_rank5 = [&](const std::vector<uint64_t>& stored, unsigned l) {
        const uint64_t mask = (((uint64_t{1} << M5) - 1) >> (M5 - l)) << (M5 - l);
        std::vector<uint64_t> img;
        for (uint64_t b : lapidary::detail::gf2_basis(stored)) img.push_back(b & mask);
        return lapidary::detail::gf2_rank(img);
    };
    auto members5 = [&](V5 v) {
        auto [base, count] = cdc.class_for(v);
        std::vector<uint64_t> out;
        for (uint64_t i = 0; i < count; ++i) out.push_back(base | i);
        return out;
    };

    // The saturated, non-full-support store {B, C, E}: every projection full.
    const std::vector<uint64_t> canon{cdc.encode(V5::B), cdc.encode(V5::C),
                                      cdc.encode(V5::E)};
    REQUIRE(proj_rank5(canon, 2) == 2u);  // pi_2 full
    REQUIRE(proj_rank5(canon, 3) == 3u);  // pi_3 full: SATURATED

    const Law5 q0 = law5(canon);  // the designed Kraft law (1/4,1/4,1/4,1/8,1/8)
    REQUIRE(q0[0] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(q0[1] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(q0[2] == std::pair<uint64_t, uint64_t>{1, 4});
    REQUIRE(q0[3] == std::pair<uint64_t, uint64_t>{1, 8});
    REQUIRE(q0[4] == std::pair<uint64_t, uint64_t>{1, 8});

    // Exhaust all 4 * 4 * 2 = 32 within-class draws: the law is NOT invariant.
    std::set<Law5> laws;
    std::size_t total = 0, breaking = 0;
    for (uint64_t b : members5(V5::B))
        for (uint64_t c : members5(V5::C))
            for (uint64_t e : members5(V5::E)) {
                const Law5 q = law5({b, c, e});
                laws.insert(q);
                ++total;
                if (q != q0) ++breaking;
            }
    REQUIRE(total == 32u);
    REQUIRE(laws.size() == 2u);   // exactly two laws: designed + collapsed
    REQUIRE(breaking == 16u);     // half of all draws break invariance

    // The explicit breaking draw: C -> 1010 collapses D (E doubles).
    const Law5 qb = law5({cdc.encode(V5::B), 0b1010u, cdc.encode(V5::E)});
    REQUIRE(qb != q0);
    REQUIRE(qb[3] == std::pair<uint64_t, uint64_t>{0, 1});  // D: 1/8 -> 0
    REQUIRE(qb[4] == std::pair<uint64_t, uint64_t>{1, 4});  // E: 1/8 -> 1/4

    // Contrast: the FULL-SUPPORT store {A..E} is invariant over all 256 draws.
    const std::vector<uint64_t> full{cdc.encode(V5::A), cdc.encode(V5::B),
                                     cdc.encode(V5::C), cdc.encode(V5::D),
                                     cdc.encode(V5::E)};
    const Law5 qf = law5(full);
    std::size_t ftotal = 0;
    bool all_same = true;
    for (uint64_t a : members5(V5::A))
        for (uint64_t b : members5(V5::B))
            for (uint64_t c : members5(V5::C))
                for (uint64_t d : members5(V5::D))
                    for (uint64_t e : members5(V5::E)) {
                        ++ftotal;
                        if (law5({a, b, c, d, e}) != qf) all_same = false;
                    }
    REQUIRE(ftotal == 256u);
    REQUIRE(all_same);
}
