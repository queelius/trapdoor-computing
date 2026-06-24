# Standalone build for the codec-controlled-retrieval theorem gates.
#
# Self-contained: depends only on a C++23 compiler and network access at configure
# time (FetchContent pulls Catch2 v3). No maph checkout required; the pinned
# header-only library is vendored under include/lapidary (see PROVENANCE.md).
#
#   cmake -S . -B build && cmake --build build -j && ctest --test-dir build
#
cmake_minimum_required(VERSION 3.20)
project(codec_controlled_retrieval_artifact CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# One Catch2 binary per gate. Each maps to a cluster of theorems in CLAIMS.md.
set(GATES
    gf2                     # the GF(2) toolkit the proofs rest on
    prefix_codec            # T1/T2/T3/T4 (balanced): span, nonmember, threshold, contrastive
    skewed_realizability    # T4b: graded mass, the realizable ladder
    realizable_set          # T4c: the realizable set, completely characterized
    cogirth_robustness      # T5b: cogirth is the erasure budget (balanced)
    cogirth_graded          # T5c: per-rung cogirth family (graded)
    randomized_encoding     # randomized encoding: balanced/saturated invariance
    randomized_boundary     # randomized encoding: skewed counterexample + saturation
)

foreach(g ${GATES})
    add_executable(test_${g} tests/v3/test_${g}.cpp)
    target_link_libraries(test_${g} PRIVATE Catch2::Catch2WithMain pthread)
    target_compile_features(test_${g} PRIVATE cxx_std_23)
    add_test(NAME ${g} COMMAND test_${g})
endforeach()
