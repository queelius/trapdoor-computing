# Artifact provenance

This artifact is a self-contained, pinned extract of the maph research repository.
It reproduces the computational gates behind every theorem in the manuscript
without requiring a maph checkout. Regenerate it with:

    scripts/sync-from-maph.sh 772d502

## Pin

- Upstream: maph (https://github.com/queelius/maph), the C++23 perfect-hashing
  research playground.
- Commit: `772d50200df3fb484a67e3f90c9b3e4e5e61351d`
  (2026-06-08 21:39:31 -0500)
- Subject: feat: T4c complete characterization of the realizable non-member-mass set

maph is a research playground and its `master` moves; this artifact is pinned to
the commit above and is the stable reference for the manuscript. Do not cite maph
`master`; cite this pinned bundle (and, at submission, its archived DOI).

## Contents

- `include/maph/` -- the header-only library at the pinned commit. The gates
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
