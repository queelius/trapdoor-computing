# Artifact provenance

This artifact is a self-contained, pinned extract of the lapidary research repository
(formerly maph). It reproduces the computational gates behind every theorem in the
manuscript without requiring a lapidary checkout. Regenerate it with:

    scripts/sync-from-maph.sh be92fa6

## Pin

- Upstream: lapidary (https://github.com/queelius/lapidary; formerly maph), the
  C++23 perfect-hashing research playground.
- Commit: `be92fa6f1ea982f0758851e830e3a9aee94ee357`
  (2026-06-21 02:02:43 -0500)
- Subject: refactor!: rename project maph -> lapidary (namespace, includes, CMake, docs)

lapidary is a research playground and its `master` moves; this artifact is pinned to
the commit above and is the stable reference for the manuscript. Do not cite lapidary
`master`; cite this pinned bundle (and, at submission, its archived DOI).

## Contents

- `include/lapidary/` -- the header-only library at the pinned commit. The gates
  exercise `codecs/prefix_codec.hpp`, `detail/gf2.hpp`, and (for the empirical
  ribbon checks) `retrieval/`. The remaining algorithm headers are carried for a
  clean, self-contained build and are not exercised by the gates.
- `tests/` -- the six Catch2 gates, one per cluster of claims (see ../CLAIMS.md).
- `note/codec_controlled_retrieval.md` -- the theorem-grade source-of-record note.
- `python/maph/` -- analysis scripts (experiment replication).
- `python/verification/` -- INDEPENDENT reimplementations (pure Python, rational
  arithmetic) that cross-check the C++ gates and produced the counterexamples in
  the manuscript. Hand-authored, not synced.
- `CMakeLists.txt` -- standalone build (FetchContent pulls Catch2 v3).

## Reproduce

    cd artifact
    cmake -S . -B build
    cmake --build build -j
    ctest --test-dir build --output-on-failure
    # and the independent Python checks:
    cd python/verification && python3 item2.py && python3 item1_general.py
