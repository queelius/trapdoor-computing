# Codec-Controlled Retrieval (towell2026codec)

The construction-and-experiments companion to the cipher-maps paper. It develops
the concrete GF(2)-linear ribbon/XOR retrieval construction whose non-member
output distribution is controlled by a public codec, with a sharp span-threshold
theorem and a frequency-analysis-resistance security result.

## Status

Bootstrapped (SP3, June 2026). Tracking via papermill (`.papermill/state.md`).
The full technical substance is already developed and reviewed; this paper
reshapes it into venue form. Source of record for the technical content:
`maph/docs/codec_controlled_retrieval.md` (commit `a79d9c0` on `master`), with a
snapshot in `source/construction-note.md` here.

## The result in one line

Homogeneous ribbon (XOR) retrieval is a free distribution-transforming decoder:
the value returned for a non-member key is uniform on the GF(2) span `W` of the
stored codewords, so a public codec fixes the off-set output distribution, and
that distribution is independent of storage frequency. Codec control holds
exactly when `W` spans the codec's class quotient (a sharp rank threshold, the
headline). This is structural frequency-hiding native to a static data structure.

## Layout

- `paper/codec_retrieval.tex`: the manuscript (skeleton; `make` to build).
- `paper/refs.bib`: bibliography (seeded from the bijou hub bib).
- `source/construction-note.md`: snapshot of the maph note (the technical source).
- `source/results/`: the E1 to E4 experiment result data.
- `.papermill/`: papermill project state and tracking.

## Relationship to the program

Theory in `bernoulli/` (the abstract codec-output law), constructions in `bijou/`
and `maph/` (this paper's substance), confidentiality applications here in
`trapdoor-computing/`. This paper is cited by `cipher-maps` as `towell2026codec`.

## Build

```
cd paper && make
```
