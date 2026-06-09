#include <catch2/catch_test_macros.hpp>
#include <maph/detail/gf2.hpp>
#include <cstdint>
#include <vector>

using namespace maph::detail;

TEST_CASE("gf2 rank of independent patterns", "[gf2]") {
    // {0001, 0010, 0100} are three nonzero, pairwise-independent vectors: rank 3.
    std::vector<uint64_t> v{0b0001, 0b0010, 0b0100};
    REQUIRE(gf2_rank(v) == 3);
}

TEST_CASE("gf2 rank ignores zero vector and dependent vectors", "[gf2]") {
    // 1100 = 1000 XOR 0100, so it is in the span of 0100 and 1000.
    // The zero vector never contributes to rank.
    // Basis is {0100, 1000}, rank 2.
    std::vector<uint64_t> v{0b0000, 0b0100, 0b1000, 0b1100};
    REQUIRE(gf2_rank(v) == 2);
}

TEST_CASE("gf2 span enumeration", "[gf2]") {
    // span{0100, 1000} = {0000, 0100, 1000, 1100}, exactly 4 elements.
    std::vector<uint64_t> basis = gf2_basis({0b0100, 0b1000});
    std::vector<uint64_t> span = gf2_span(basis);
    REQUIRE(span.size() == 4);
    REQUIRE(gf2_in_span(0b1100, basis));
    REQUIRE_FALSE(gf2_in_span(0b0010, basis));
}

TEST_CASE("gf2 edge cases: empty input, zero vector, empty basis", "[gf2]") {
    // Rank of nothing, and of a single zero vector, is 0.
    REQUIRE(gf2_rank({}) == 0);
    REQUIRE(gf2_rank({0}) == 0);

    // Span of an empty basis is just {0}.
    std::vector<uint64_t> empty_basis = gf2_basis({});
    std::vector<uint64_t> span0 = gf2_span(empty_basis);
    REQUIRE(span0.size() == 1);
    REQUIRE(span0[0] == 0);

    // The zero vector is in every span; a nonzero vector is not in the empty span.
    std::vector<uint64_t> basis = gf2_basis({0b0100, 0b1000});
    REQUIRE(gf2_in_span(0, basis));
    REQUIRE(gf2_in_span(0, empty_basis));
    REQUIRE_FALSE(gf2_in_span(0b0010, empty_basis));
}
