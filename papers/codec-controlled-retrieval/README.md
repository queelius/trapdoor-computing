# Codec-Controlled Retrieval (towell2026codec)

**Codec-Controlled Retrieval: Structural Frequency-Hiding from the Non-Member
Channel of XOR Retrieval.** The construction-and-experiments companion to the
cipher-maps paper, targeting PoPETs. It develops the concrete GF(2)-linear
ribbon/XOR retrieval construction whose non-member output distribution is
controlled by a public codec, with a sharp span-threshold theorem and a
frequency-analysis-resistance security result.

## The result in one line

Homogeneous ribbon (XOR) retrieval is a free distribution-transforming decoder: the
value returned for a non-member key is uniform on the GF(2) span `W` of the stored
codewords, so a public codec fixes the off-set output distribution, and that
distribution is independent of storage frequency. Codec control holds exactly when
`W` spans the codec's class quotient (a sharp rank threshold, the headline). This is
structural frequency-hiding native to a static data structure.

## Status

Draft-complete (32 pages). Tracking via papermill (`.papermill/state.md`). The
technical substance is developed, computationally gated, and adversarially reviewed.
Source of record for the technical content: `maph/docs/codec_controlled_retrieval.md`
at pinned commit `772d502`, mirrored in `source/construction-note.md` and
`artifact/note/` here.

## What is proven

T1/T2 (output support is the stored span; idealized law uniform on it), T3
(frequency independence), T4 (sharp control threshold, balanced), T4b (skewed graded
mass and the realizable ladder), T4c (the realizable set characterized completely),
T5b (cogirth is the exact erasure budget), T5c (the per-rung cogirth family for
graded control), the randomized-encoding lemma (balanced invariance unconditional,
skewed invariance under saturation and false otherwise), and the idealized FreqDist
theorem (advantage exactly zero). T5 (the real-band deviation) is characterized
empirically. See `CLAIMS.md` for the claim-to-gate map and `FINDINGS.md` for the
scope ledger and the corrections this work turned up (read FINDINGS first; one
earlier result was reversed).

## Layout

- `paper/codec_retrieval.tex` -- the manuscript (`make` to build the PDF).
- `paper/refs.bib` -- bibliography.
- `CLAIMS.md` -- every theorem to its computational gate and note section.
- `FINDINGS.md` -- scope ledger and corrections (the randomized refutation, etc.).
- `source/construction-note.md` -- the theorem-grade source-of-record note.
- `source/results/` -- the E1 to E4 experiment data.
- `artifact/` -- the self-contained, pinned reproducibility bundle (below).
- `scripts/sync-from-maph.sh` -- regenerates the artifact from a maph commit.
- `SUBMISSION-CHECKLIST.md` -- pre-submission and Zenodo-DOI steps.
- `.papermill/` -- papermill project state.

## Reproducing the gates (no maph checkout needed)

The `artifact/` directory is a self-contained, pinned extract of the maph
repository: the header-only library, the eight Catch2 gates, the source note, and
independent Python cross-checks. It builds and runs without maph (Catch2 is fetched
at configure time).

    cd artifact
    cmake -S . -B build && cmake --build build -j
    ctest --test-dir build --output-on-failure          # 8/8 gates

    cd python/verification                                # independent checks
    python3 item2.py            # the randomized counterexample
    python3 item1_general.py    # the realizable-set characterization
    python3 saturation.py       # saturation sufficiency

See `artifact/PROVENANCE.md` for the pin and contents.

## On maph stability

maph is a research playground and its `master` moves. Do NOT cite maph `master` from
the paper. The artifact is pinned to a specific commit and is the stable reference;
to refresh it against a newer maph commit, run `scripts/sync-from-maph.sh <commit>`.
At submission the artifact is archived to Zenodo for a DOI (see
`SUBMISSION-CHECKLIST.md`), and the paper cites the DOI.

## Relationship to the program

Theory in `bernoulli/` (the abstract codec-output law), constructions in `bijou/`
and `maph/` (this paper's substance), confidentiality applications here in
`trapdoor-computing/`. This paper is cited by `cipher-maps` as `towell2026codec`.

## Build the paper

    cd paper && make        # pdflatex + bibtex, outputs codec_retrieval.pdf
