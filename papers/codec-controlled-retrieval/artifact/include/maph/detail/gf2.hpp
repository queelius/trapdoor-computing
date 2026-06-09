#pragma once

// GF(2)^M linear-algebra toolkit.
//
// Patterns are packed into uint64_t (up to 64 bits per pattern). All arithmetic
// is over GF(2): addition = XOR, multiplication = AND.
//
// Public API (namespace maph::detail):
//   gf2_basis(patterns)        -> reduced row-echelon basis
//   gf2_rank(patterns)         -> number of linearly independent patterns
//   gf2_in_span(v, basis)      -> true if v is in the span of basis
//   gf2_span(basis)            -> all 2^|basis| XOR-combinations
//
// Restriction: gf2_span asserts |basis| <= 63 (the 1<<|basis| shift bound); keep
// it well under about 24 in practice, since 2^24 entries already cost 128 MB.

#include <cassert>
#include <cstdint>
#include <vector>

namespace maph::detail {

// Compute a reduced row-echelon basis for the GF(2) span of `patterns`.
// Each basis element is stored keyed by its leading (highest-set) bit so that
// gf2_in_span can reduce v in O(|basis|) time.
//
// Algorithm: for each pattern b in input order,
//   1. Reduce b by XORing out every basis element whose pivot bit is set in b.
//   2. If the remainder is nonzero, add it to the basis (with its pivot bit as
//      key). Never call __builtin_clzll on 0.
inline std::vector<uint64_t> gf2_basis(const std::vector<uint64_t>& patterns) {
    // basis_[i] holds a basis element whose highest bit is at position i.
    // Using a fixed-size array indexed by bit position gives O(1) pivot lookup.
    uint64_t basis_by_pivot[64] = {};  // zero-initialized = "no element at this pivot"

    std::size_t count = 0;  // number of basis elements added so far

    for (uint64_t b : patterns) {
        // Reduce b against the current basis.
        for (int pos = 63; pos >= 0; --pos) {
            if (!(b & (uint64_t(1) << pos))) continue;
            if (!basis_by_pivot[pos]) break;  // no basis element at this pivot; b is independent, insert it
            b ^= basis_by_pivot[pos];
        }
        if (b == 0) continue;  // linearly dependent, discard

        // b is a new independent vector. Insert at its pivot position.
        int pivot = 63 - __builtin_clzll(b);  // __builtin_clzll is safe: b != 0
        basis_by_pivot[pivot] = b;
        ++count;
    }

    // Collect the basis elements in decreasing pivot order.
    std::vector<uint64_t> result;
    result.reserve(count);
    for (int pos = 63; pos >= 0; --pos) {
        if (basis_by_pivot[pos]) {
            result.push_back(basis_by_pivot[pos]);
        }
    }
    return result;
}

// Return the GF(2) rank of `patterns` (number of linearly independent vectors).
inline std::size_t gf2_rank(const std::vector<uint64_t>& patterns) {
    return gf2_basis(patterns).size();
}

// Return true if `v` is in the span of `basis` (a basis produced by gf2_basis).
// Reduces v by XORing out basis elements; v is in the span iff the remainder is 0.
inline bool gf2_in_span(uint64_t v, const std::vector<uint64_t>& basis) {
    for (uint64_t b : basis) {
        if (v == 0) break;
        // The leading bit of b is its pivot. If that bit is set in v, eliminate it.
        int pivot = 63 - __builtin_clzll(b);  // safe: basis elements are nonzero
        if (v & (uint64_t(1) << pivot)) {
            v ^= b;
        }
    }
    return v == 0;
}

// Enumerate all 2^|basis| XOR-combinations in the span of `basis`.
// The caller must ensure |basis| is small (at most ~24) to keep memory bounded.
inline std::vector<uint64_t> gf2_span(const std::vector<uint64_t>& basis) {
    assert(basis.size() <= 63 && "gf2_span: basis too large; caller must limit size (about 24) for memory");
    std::vector<uint64_t> result;
    result.reserve(std::size_t(1) << basis.size());
    result.push_back(0);

    // For each basis element, double the current set by XORing it into every
    // existing element and appending the results.
    for (uint64_t b : basis) {
        std::size_t prev_size = result.size();
        for (std::size_t i = 0; i < prev_size; ++i) {
            result.push_back(result[i] ^ b);
        }
    }
    return result;
}

}  // namespace maph::detail
