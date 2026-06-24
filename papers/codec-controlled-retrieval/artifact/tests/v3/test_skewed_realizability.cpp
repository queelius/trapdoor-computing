/**
 * @file test_skewed_realizability.cpp
 * @brief T4b: skewed (variable-length) codecs are GRADED, and the realizable
 *        non-member mass set is structured (a non-increasing ladder in code
 *        length).
 *
 * This is the computational gate for the T4b subsection of
 * docs/codec_controlled_retrieval.md. It is a PURE linear-algebra check on the
 * stored-pattern span W and the codec; it does NOT build a ribbon structure.
 * The bridge from W to actual non-member queries is T1/T2 (R(z) = W, idealized
 * output uniform on W), already proven and exercised by the [span]/[nonmember]
 * tests in test_prefix_codec.cpp.
 *
 * The balanced T4 lemma (single homophone subspace C, mass is 0 or one common
 * 1/K' on every hit class) is SHARP: it forbids two distinct positive masses.
 * For a SKEWED codec the classes are cosets of DIFFERENT within-class subspaces
 * C_l (the flag below), so that lemma does not apply, and the per-class mass can
 * take DISTINCT POSITIVE values. That is the open skewed case, settled here.
 *
 * Notation (matches the note):
 *   - class(v) = { patterns whose top len(v) bits equal codeword(v) }
 *              = coset  aligned(v) + C_{len(v)}.
 *   - C_l      = span of the bottom (M - l) standard basis vectors (the
 *                within-class directions of a length-l codeword). The C_l form a
 *                complete flag  {0} = C_M subset C_{M-1} subset ... subset C_1,
 *                dim C_l = M - l.
 *   - W        = the stored-pattern span (gf2_span(gf2_basis(stored))).
 *   - q(v)     = |class(v) intersect W| / |W|   (the idealized non-member mass).
 *
 * Realizability formula (verified):
 *   q(v) = h_v * 2^( dim(W intersect C_{len(v)}) - dim W ),
 *   h_v = [ aligned(v) in W + C_{len(v)} ]  (the hit indicator).
 * Because the C_l are nested, dim(W intersect C_l) is monotone non-increasing in
 * l, so among hit classes shorter codewords carry >= the mass of longer ones.
 */

#include <catch2/catch_test_macros.hpp>

#include <lapidary/codecs/prefix_codec.hpp>
#include <lapidary/detail/gf2.hpp>

#include <array>
#include <cstdint>
#include <vector>

using namespace lapidary;

namespace {

// The graded witness alphabet: four values A,B,C,D with lengths {1,2,3,3}.
enum class V : uint8_t { A, B, C, D };

// The skew {1,2,3,3} codec on M = 4. Kraft = 1/2 + 1/4 + 1/8 + 1/8 = 1 (tight).
prefix_codec<V, 4> skew_codec() {
    return prefix_codec<V, 4>{{{V::A, 1}, {V::B, 2}, {V::C, 3}, {V::D, 3}}, V::A};
}

// C_l = span of the bottom (M - l) standard basis vectors (bits 0 .. M-l-1).
// Returned already in reduced form (each vector is its own pivot).
std::vector<uint64_t> within_class_subspace(unsigned length, unsigned M) {
    std::vector<uint64_t> basis;
    for (unsigned i = 0; i + length < M; ++i) {
        basis.push_back(uint64_t{1} << i);
    }
    return basis;
}

// dim(W intersect C) via the rank identity
//   dim(W intersect C) = dim W + dim C - dim(W + C),
// using gf2_rank of the union basis. Needs no new GF(2) primitive.
std::size_t intersection_dim(const std::vector<uint64_t>& W_basis,
                             const std::vector<uint64_t>& C_basis) {
    std::vector<uint64_t> uni;
    uni.reserve(W_basis.size() + C_basis.size());
    uni.insert(uni.end(), W_basis.begin(), W_basis.end());
    uni.insert(uni.end(), C_basis.begin(), C_basis.end());
    const std::size_t dim_sum = lapidary::detail::gf2_rank(uni);
    return W_basis.size() + C_basis.size() - dim_sum;
}

// q(v) for every value, computed by ENUMERATION: enumerate W, decode each
// element through the codec, tally per value, normalize by |W|. The masses are
// dyadic rationals over |W|, so they compare exactly (tolerance 1e-9).
std::array<double, 4> mass_by_enumeration(const prefix_codec<V, 4>& cdc,
                                          const std::vector<uint64_t>& stored) {
    const auto basis = lapidary::detail::gf2_basis(stored);
    const auto span = lapidary::detail::gf2_span(basis);
    std::array<double, 4> q{0.0, 0.0, 0.0, 0.0};
    for (uint64_t p : span) {
        q[static_cast<std::size_t>(cdc.decode(p))] += 1.0;
    }
    for (auto& x : q) x /= static_cast<double>(span.size());
    return q;
}

// q(v) by the FLAG FORMULA  q(v) = h_v * 2^(dim(W cap C_len) - dim W).
std::array<double, 4> mass_by_formula(const prefix_codec<V, 4>& cdc,
                                      const std::vector<uint64_t>& stored) {
    constexpr unsigned M = 4;
    const auto W_basis = lapidary::detail::gf2_basis(stored);
    const std::size_t dimW = W_basis.size();

    std::array<double, 4> q{0.0, 0.0, 0.0, 0.0};
    for (const auto& e : cdc.entries()) {
        const auto C_basis = within_class_subspace(e.length, M);
        // hit indicator h_v = [ aligned(v) in W + C_len ]: aligned(v) lies in the
        // union span iff adding it does not raise the rank of (W basis + C basis).
        std::vector<uint64_t> uni = W_basis;
        uni.insert(uni.end(), C_basis.begin(), C_basis.end());
        const std::size_t base_rank = lapidary::detail::gf2_rank(uni);
        uni.push_back(e.prefix_left_aligned);
        const bool hit = lapidary::detail::gf2_rank(uni) == base_rank;

        if (!hit) continue;
        const std::size_t d = intersection_dim(W_basis, C_basis);
        // q = 2^(d - dimW). d <= dimW always (C_len cap W is a subspace of W).
        q[static_cast<std::size_t>(e.value)] =
            std::ldexp(1.0, static_cast<int>(d) - static_cast<int>(dimW));
    }
    return q;
}

constexpr double EXACT = 1e-9;

}  // namespace

// ===== Ground the codewords before asserting anything on them. =====

TEST_CASE("T4b: skew {1,2,3,3} canonical codewords are A=0000 B=1000 C=1100 D=1110",
          "[prefix_codec][skewed][realizability]") {
    auto cdc = skew_codec();
    // Canonical left-aligned assignment, longest classes first by length sort.
    REQUIRE(cdc.encode(V::A) == 0b0000u);  // len 1, class size 8
    REQUIRE(cdc.encode(V::B) == 0b1000u);  // len 2, class size 4
    REQUIRE(cdc.encode(V::C) == 0b1100u);  // len 3, class size 2
    REQUIRE(cdc.encode(V::D) == 0b1110u);  // len 3, class size 2

    // Codespace shares 2^(-len): 1/2, 1/4, 1/8, 1/8 (Kraft = 1, no surplus).
    REQUIRE(cdc.codespace_share(V::A) == 0.5);
    REQUIRE(cdc.codespace_share(V::B) == 0.25);
    REQUIRE(cdc.codespace_share(V::C) == 0.125);
    REQUIRE(cdc.codespace_share(V::D) == 0.125);
}

// ===== The GRADED witness: distinct positive masses on distinct hit classes. =====

TEST_CASE("T4b: skewed codec is GRADED (W = span of all four stored codewords)",
          "[prefix_codec][skewed][realizability]") {
    auto cdc = skew_codec();

    // W = span of all four canonical codewords {0000, 1000, 1100, 1110}.
    // gf2_basis reduces this to {1000, 0100, 0010}, dim W = 3, |W| = 8.
    std::vector<uint64_t> stored{cdc.encode(V::A), cdc.encode(V::B),
                                 cdc.encode(V::C), cdc.encode(V::D)};
    const auto basis = lapidary::detail::gf2_basis(stored);
    REQUIRE(basis.size() == 3u);                 // dim W = 3
    REQUIRE(lapidary::detail::gf2_span(basis).size() == 8u);  // |W| = 8

    auto q = mass_by_enumeration(cdc, stored);

    // q = (1/2, 1/4, 1/8, 1/8): EXACT.
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::A)] - 0.5) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::B)] - 0.25) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::C)] - 0.125) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::D)] - 0.125) < EXACT);

    // GENUINELY GRADED: not all hit-class masses are equal (the balanced lemma
    // forbids this), and at least two distinct positive masses occur. Here the
    // distinct positive masses are {1/2, 1/4, 1/8}: three of them, so a fortiori
    // more than one. This is what the single-homophone-subspace lemma cannot
    // produce.
    const bool all_equal =
        std::abs(q[static_cast<std::size_t>(V::A)] - q[static_cast<std::size_t>(V::B)]) < EXACT &&
        std::abs(q[static_cast<std::size_t>(V::B)] - q[static_cast<std::size_t>(V::C)]) < EXACT &&
        std::abs(q[static_cast<std::size_t>(V::C)] - q[static_cast<std::size_t>(V::D)]) < EXACT;
    REQUIRE_FALSE(all_equal);

    int distinct_positive = 0;
    for (double level : {0.5, 0.25, 0.125}) {
        bool present = false;
        for (double m : q) if (m > EXACT && std::abs(m - level) < EXACT) present = true;
        if (present) ++distinct_positive;
    }
    REQUIRE(distinct_positive >= 2);
}

// ===== The flag / realizability FORMULA, on several explicit W. =====

TEST_CASE("T4b: q(v) = h_v * 2^(dim(W cap C_len) - dim W) for several W",
          "[prefix_codec][skewed][realizability]") {
    auto cdc = skew_codec();

    // A handful of explicit stored-pattern sets (hence subspaces W). For each we
    // assert the enumerated mass equals the flag formula, value by value.
    const std::vector<std::vector<V>> stored_sets = {
        {V::A},                          // dim 0: W = {0}
        {V::A, V::B},                    // dim 1
        {V::B, V::C},                    // dim 1, no A
        {V::A, V::B, V::C},              // dim 2
        {V::B, V::C, V::D},              // dim 2
        {V::A, V::B, V::C, V::D},        // dim 3 (the graded witness)
    };

    for (const auto& vs : stored_sets) {
        std::vector<uint64_t> stored;
        stored.reserve(vs.size());
        for (V v : vs) stored.push_back(cdc.encode(v));

        auto q_enum = mass_by_enumeration(cdc, stored);
        auto q_form = mass_by_formula(cdc, stored);

        for (std::size_t i = 0; i < 4; ++i) {
            REQUIRE(std::abs(q_enum[i] - q_form[i]) < EXACT);
        }

        // The realizable masses are a NON-INCREASING ladder in code length: among
        // hit classes, a shorter codeword carries at least the mass of any longer
        // one (because dim(W cap C_l) is monotone non-increasing along the flag).
        for (const auto& e1 : cdc.entries()) {
            for (const auto& e2 : cdc.entries()) {
                const double q1 = q_enum[static_cast<std::size_t>(e1.value)];
                const double q2 = q_enum[static_cast<std::size_t>(e2.value)];
                if (q1 > EXACT && q2 > EXACT && e1.length <= e2.length) {
                    REQUIRE(q1 >= q2 - EXACT);  // shorter (or equal) => >= mass
                }
            }
        }
    }
}

// ===== The PUNCHLINE: full-span control realizes the designed Kraft law. =====

TEST_CASE("T4b: full-span W = GF(2)^4 gives q(v) = 2^(-len(v)) (designed Kraft shares)",
          "[prefix_codec][skewed][realizability]") {
    auto cdc = skew_codec();

    // W = all of GF(2)^4: take the four standard basis vectors as the span.
    std::vector<uint64_t> full_basis{0b0001u, 0b0010u, 0b0100u, 0b1000u};
    REQUIRE(lapidary::detail::gf2_rank(full_basis) == 4u);

    auto q = mass_by_enumeration(cdc, full_basis);

    // q(v) = 2^(-len(v)) exactly = the codec's codespace shares. Full control of
    // the non-member law reproduces the codec's DESIGNED frequency law.
    for (const auto& e : cdc.entries()) {
        const double share = std::ldexp(1.0, -static_cast<int>(e.length));
        REQUIRE(std::abs(q[static_cast<std::size_t>(e.value)] - share) < EXACT);
        REQUIRE(std::abs(q[static_cast<std::size_t>(e.value)] -
                         cdc.codespace_share(e.value)) < EXACT);
    }
    // Concretely (1/2, 1/4, 1/8, 1/8).
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::A)] - 0.5) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::B)] - 0.25) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::C)] - 0.125) < EXACT);
    REQUIRE(std::abs(q[static_cast<std::size_t>(V::D)] - 0.125) < EXACT);
}

// ===== The IMPOSSIBILITY: a uniform target over the skew codec is unreachable. =====

TEST_CASE("T4b: no stored-codeword span makes the skew codec's q uniform",
          "[prefix_codec][skewed][realizability]") {
    auto cdc = skew_codec();

    // The realizable masses form a non-increasing ladder pinned by len(A)=1 <
    // len(B)=2 < len(C)=len(D)=3. A uniform law q = (1/4,1/4,1/4,1/4) would need
    // q(A) = q(B), but whenever A is a hit class (which it is for any W meeting
    // its class), q(A) is the TOP of the ladder and strictly dominates any
    // shorter-length-deficit class once two distinct lengths are both hit. We
    // check directly that none of the stored-codeword spans yields the uniform
    // vector, and that the witness/full-span W produce a STRICT descent across
    // the distinct lengths (so the ladder cannot be flattened to uniform).
    const std::vector<std::vector<V>> stored_sets = {
        {V::A}, {V::A, V::B}, {V::B, V::C}, {V::A, V::C}, {V::A, V::D},
        {V::A, V::B, V::C}, {V::A, V::B, V::D}, {V::B, V::C, V::D},
        {V::A, V::B, V::C, V::D},
    };

    const std::array<double, 4> uniform{0.25, 0.25, 0.25, 0.25};
    for (const auto& vs : stored_sets) {
        std::vector<uint64_t> stored;
        for (V v : vs) stored.push_back(cdc.encode(v));
        auto q = mass_by_enumeration(cdc, stored);

        bool is_uniform = true;
        for (std::size_t i = 0; i < 4; ++i) {
            if (std::abs(q[i] - uniform[i]) >= EXACT) is_uniform = false;
        }
        REQUIRE_FALSE(is_uniform);
    }

    // The witness W = span of all four codewords: a STRICT descent A > B > C
    // across the three distinct code lengths {1, 2, 3}. A strict descent cannot
    // equal a flat (uniform) vector, so uniform is unreachable by this W.
    std::vector<uint64_t> witness{cdc.encode(V::A), cdc.encode(V::B),
                                  cdc.encode(V::C), cdc.encode(V::D)};
    auto qw = mass_by_enumeration(cdc, witness);
    REQUIRE(qw[static_cast<std::size_t>(V::A)] >
            qw[static_cast<std::size_t>(V::B)] + EXACT);  // 1/2 > 1/4
    REQUIRE(qw[static_cast<std::size_t>(V::B)] >
            qw[static_cast<std::size_t>(V::C)] + EXACT);  // 1/4 > 1/8
}
