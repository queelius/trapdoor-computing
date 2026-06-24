#!/usr/bin/env bash
#
# sync-from-maph.sh -- regenerate the self-contained artifact from a PINNED maph
# commit. This is the single mechanism that keeps artifact/ in step with the
# upstream source of record; never hand-edit the synced files.
#
# Usage:
#   scripts/sync-from-maph.sh [maph-commit]        # default pin below
#   MAPH_REPO=/path/to/maph scripts/sync-from-maph.sh 772d502
#
# Everything is extracted from the git OBJECT at the given commit (not the maph
# working tree), so the result is reproducible regardless of maph's local state.
#
set -euo pipefail

DEFAULT_PIN="be92fa6"
# The upstream repo: lapidary (renamed from "maph"; remote queelius/lapidary, namespace
# lapidary::, header tree include/lapidary/). It lives at bijou/lapidary.
MAPH="${MAPH_REPO:-$HOME/github/bijou/lapidary}"
COMMIT="${1:-$DEFAULT_PIN}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ART="$ROOT/artifact"

if [ ! -d "$MAPH/.git" ]; then
    echo "error: maph repo not found at $MAPH (set MAPH_REPO)" >&2
    exit 1
fi

FULLSHA="$(git -C "$MAPH" rev-parse "$COMMIT")"
CDATE="$(git -C "$MAPH" show -s --format=%ci "$COMMIT")"
SUBJECT="$(git -C "$MAPH" show -s --format=%s "$COMMIT")"

echo "syncing artifact from lapidary@$COMMIT ($FULLSHA)"

# The theorem-gate tests the paper depends on. Vendored under tests/v3/ to mirror
# maph's layout, so the tests' relative includes (e.g. ../../benchmarks/...) resolve
# unchanged and the files stay verbatim.
TESTS="skewed_realizability realizable_set cogirth_robustness cogirth_graded \
       randomized_encoding randomized_boundary prefix_codec gf2"
# Benchmark headers some gates include by relative path.
BENCH="codec_experiment"
# Python analysis scripts that live in maph.
ANALYSIS="cogirth_robustness coincidence_oracle skewed_realizability"

# Regenerate only the synced trees; leave hand-authored files (CMakeLists.txt,
# python/verification/, .gitignore) untouched.
rm -rf "$ART/include" "$ART/tests" "$ART/benchmarks" "$ART/python/maph" "$ART/note"
mkdir -p "$ART/tests/v3" "$ART/benchmarks" "$ART/python/maph" "$ART/note"

# 1. the header-only library (whole tree, pinned). maph is header-only, so this
#    is the clean dependency boundary; the codec/, retrieval/, detail/ headers are
#    what the gates exercise (see PROVENANCE.md).
git -C "$MAPH" archive "$COMMIT" include/lapidary | tar -x -C "$ART/"

# 2. the gates (mirroring tests/v3/) and the benchmark headers they include.
for t in $TESTS; do
    git -C "$MAPH" show "$COMMIT:tests/v3/test_$t.cpp" > "$ART/tests/v3/test_$t.cpp"
done
for b in $BENCH; do
    git -C "$MAPH" show "$COMMIT:benchmarks/$b.hpp" > "$ART/benchmarks/$b.hpp"
done

# 3. maph-side analysis scripts (the verification/ scripts are local, not synced).
for p in $ANALYSIS; do
    git -C "$MAPH" show "$COMMIT:analysis/$p.py" > "$ART/python/maph/$p.py"
done

# 4. the source-of-record note.
git -C "$MAPH" show "$COMMIT:docs/codec_controlled_retrieval.md" \
    > "$ART/note/codec_controlled_retrieval.md"

# 5. refresh the prose snapshot the manuscript references.
{
    printf '<!--\n'
    printf 'PROVENANCE (snapshot, do not edit here; edit the upstream note and re-sync).\n'
    printf 'Source of record: lapidary/docs/codec_controlled_retrieval.md\n'
    printf 'Pinned commit: %s (%s)\n' "$FULLSHA" "$CDATE"
    printf 'Regenerate: scripts/sync-from-maph.sh %s\n' "$COMMIT"
    printf 'This file is a verbatim copy of the upstream note.\n'
    printf -- '-->\n\n'
    cat "$ART/note/codec_controlled_retrieval.md"
} > "$ROOT/source/construction-note.md"

# 6. provenance stamp for the artifact bundle.
cat > "$ART/PROVENANCE.md" <<EOF
# Artifact provenance

This artifact is a self-contained, pinned extract of the lapidary research repository
(formerly maph). It reproduces the computational gates behind every theorem in the
manuscript without requiring a lapidary checkout. Regenerate it with:

    scripts/sync-from-maph.sh $COMMIT

## Pin

- Upstream: lapidary (https://github.com/queelius/lapidary; formerly maph), the
  C++23 perfect-hashing research playground.
- Commit: \`$FULLSHA\`
  ($CDATE)
- Subject: $SUBJECT

lapidary is a research playground and its \`master\` moves; this artifact is pinned to
the commit above and is the stable reference for the manuscript. Do not cite lapidary
\`master\`; cite this pinned bundle (and, at submission, its archived DOI).

## Contents

- \`include/lapidary/\` -- the header-only library at the pinned commit. The gates
  exercise \`codecs/prefix_codec.hpp\`, \`detail/gf2.hpp\`, and (for the empirical
  ribbon checks) \`retrieval/\`. The remaining algorithm headers are carried for a
  clean, self-contained build and are not exercised by the gates.
- \`tests/\` -- the six Catch2 gates, one per cluster of claims (see ../CLAIMS.md).
- \`note/codec_controlled_retrieval.md\` -- the theorem-grade source-of-record note.
- \`python/maph/\` -- analysis scripts (experiment replication).
- \`python/verification/\` -- INDEPENDENT reimplementations (pure Python, rational
  arithmetic) that cross-check the C++ gates and produced the counterexamples in
  the manuscript. Hand-authored, not synced.
- \`CMakeLists.txt\` -- standalone build (FetchContent pulls Catch2 v3).

## Reproduce

    cd artifact
    cmake -S . -B build
    cmake --build build -j
    ctest --test-dir build --output-on-failure
    # and the independent Python checks:
    cd python/verification && python3 item2.py && python3 item1_general.py
EOF

echo "done. artifact synced to $ART (lapidary@$FULLSHA)"
