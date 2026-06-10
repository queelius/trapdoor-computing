# Artifact provenance

This artifact is a self-contained, pinned extract of the maph research repository.
It reproduces the computational gates behind every theorem in the manuscript
without requiring a maph checkout. Regenerate it with:

    scripts/sync-from-maph.sh 402c8ca

## Pin

- Upstream: maph (https://github.com/queelius/maph), the C++23 perfect-hashing
  research playground.
- Commit: `402c8cadd431093264e7d25090e5b08c3f430ab1`
  (2026-06-10 00:01:28 -0500)
- Subject: fix: fresh-audit corrections to the randomized section, T5, T5b, T5c

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
