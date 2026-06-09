# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

This is one paper directory inside the `trapdoor-computing` monorepo. The
monorepo-level `../../CLAUDE.md` governs shared rules: the formalism spine
(`formalism/cipher-map-formalism.md`), the provenance/authenticity discipline
(do NOT import ORAM/FHE/simulation-based definitions), the two-scale
confidentiality framing, and the subtree workflow. Read it for anything that
spans papers. This file covers only what is specific to and non-obvious about
**codec-controlled-retrieval** (`towell2026codec`).

## What this paper is

**Codec-Controlled Retrieval: Structural Frequency-Hiding from the Non-Member
Channel of XOR Retrieval.** The construction-and-experiments companion to the
cipher-maps theory paper, targeting PoPETs 2027. `cipher-maps` cites it as
`towell2026codec`.

One-line result: in homogeneous ribbon (XOR) retrieval, the value returned for a
**non-member** key is uniform on the GF(2) span `W` of the stored codewords, so a
public codec fixes the off-set output distribution and that distribution is
**independent of storage frequency**. Codec control holds *exactly* when `W`
spans the codec's class quotient: a sharp GF(2)-rank threshold
(`rank pi|_W = log2 K`), the headline (T4). This is frequency-hiding native to a
static data structure, at zero per-query cost.

## Source-of-record architecture (read before editing anything technical)

The theorem-grade content does **not** originate in this directory. It originates
in the `maph` repo (`maph/docs/codec_controlled_retrieval.md`) at a **pinned
commit**, and is pulled here. The pin is recorded in `artifact/PROVENANCE.md`
(currently `772d502`).

Generated / synced files, do **not** hand-edit (edit upstream in maph and re-sync):
- `source/construction-note.md`: verbatim snapshot of the upstream note (carries a provenance header).
- `artifact/include/`, `artifact/tests/`, `artifact/benchmarks/`, `artifact/python/maph/`, `artifact/note/`: extracted from the pinned maph git object.

Hand-authored files (safe to edit here):
- `paper/codec_retrieval.tex`, `paper/refs.bib`: **the manuscript itself** (reshaped from the note into venue prose; this is the primary deliverable that lives here).
- `artifact/python/verification/`: INDEPENDENT pure-Python cross-checks (`fractions.Fraction`, exact rational arithmetic). These produced the manuscript's counterexamples and are deliberately not synced.
- `artifact/CMakeLists.txt`, the `*.md` ledgers (`CLAIMS.md`, `FINDINGS.md`, `README.md`, `SUBMISSION-CHECKLIST.md`), `scripts/`, `.papermill/`.

To repin against a newer maph commit: `scripts/sync-from-maph.sh <sha>`. It
rewrites the synced trees, refreshes `source/construction-note.md` and
`artifact/PROVENANCE.md`, and leaves hand-authored files untouched. Do **not**
cite maph `master` from the paper; cite the pinned bundle (its Zenodo DOI at
submission).

There is no dedicated subtree remote for this directory (it was spun out 2026-06
and is edited in place within the monorepo).

## Read FINDINGS.md first

`FINDINGS.md` is the scope ledger and correction log. It records what is **proven**
(theorem + computational gate) vs **measured** (characterized, not closed-form) vs
**open**, plus corrections the development turned up, including one *reversed*
result. Two landmines a careless edit will re-break:
- `thm:randenc`: skewed randomized-encoding invariance is **FALSE in general** (a `{A,A,B}` counterexample under skew `{1,2,3,3}`). It holds *unconditionally for balanced* codecs, and for skewed codecs only *under saturation* (sufficient, not necessary). Earlier tests passed only because they all sampled the saturated full-support regime.
- The coincidence-oracle direction: **concentrated/Huffman codecs defend best**, uniform defends worst (`rem:sign` in the paper corrects an earlier inverted reading). `acc(t) = 1 - (1/2) sum_v alpha(v)^t`.

## Commands

```bash
# Build the manuscript (pdflatex x4 + bibtex; outputs codec_retrieval.pdf, ~33pp)
cd paper && make
make clean        # remove aux/log/bbl/pdf etc.
# (paper/.gitignore ignores *.pdf and all LaTeX aux files)

# Run the 8 theorem gates from the self-contained artifact (no maph checkout needed;
# FetchContent pulls Catch2 v3.5.2 at configure time; needs a C++23 compiler)
cd artifact
cmake -S . -B build && cmake --build build -j
ctest --test-dir build --output-on-failure          # expect 8/8

# Run a single gate (by ctest name or directly)
ctest --test-dir build -R prefix_codec --output-on-failure
./build/test_prefix_codec "[threshold]"              # Catch2 tag filter

# Independent Python cross-checks (exact rational arithmetic; no build step)
cd artifact/python/verification
python3 item2.py            # the skewed randomized-encoding counterexample
python3 item1_general.py    # the T4c realizable-set characterization
python3 saturation.py       # saturation sufficiency / necessity-is-false
```

`artifact/build/` is gitignored and regenerable (~100MB; safe to delete).

## Verification architecture: claim, gate, note

Every theorem is triangulated. `CLAIMS.md` is the authoritative map from each
manuscript label to (a) a Catch2 gate in `artifact/` and (b) a section of the
source note, and lists which Python script independently cross-checks it. When you
change a theorem statement, update all three corners and re-run the gate. The eight
gates and their theorem clusters:

| Gate | Covers |
|---|---|
| `gf2` | GF(2) toolkit the proofs rest on |
| `prefix_codec` | T1/T2/T3/T4 balanced: `thm:support`, `thm:idealized`, `thm:freqindep`, `thm:threshold` |
| `skewed_realizability` | T4b `thm:graded` (graded mass, realizable ladder) |
| `realizable_set` | T4c `thm:realizable` (realizable set fully characterized) |
| `cogirth_robustness` | T5b `thm:cogirth` (cogirth = erasure budget, balanced) |
| `cogirth_graded` | T5c `thm:cogirth-graded` (per-rung cogirth family) |
| `randomized_encoding` | `thm:randenc` balanced/saturated invariance |
| `randomized_boundary` | `thm:randenc` skewed counterexample + saturation boundary |

The security theorems (`thm:freqdist-ideal`, `thm:freqdist-real`) are backed by the
E1 to E4 experiment data under `source/results/`, not by a unit test.

## Manuscript framing to preserve (subtle; easy to drift on a rewrite)

- **Two governing quantities, kept distinct.** RANK governs *control* (T4: full control iff transversality). COGIRTH governs *robustness* (T5b: the matroid cogirth `d*` is the exact erasure budget). Do not conflate them.
- **Three-tier novelty ledger** (see `.papermill/state.md` thesis block). Tier A, the abstract codec-output law `P(out=v) ~ |class(v)|/2^M`, is **baseline, NOT novel here** (it predates this in the author's bernoulli_maps random-oracle work and in Honey Encryption DTEs); cite it, do not headline it. The novelty is B (the law survives the move to a GF(2)-linear ribbon structure) and C (the sharp span threshold T4, the headline).
- **Security is framed as INDEPENDENCE (indistinguishability), not a comparative leakage claim.** This framing is what makes it immune to the direction error that inverted the coincidence-oracle reading. Idealized FreqDist advantage is exactly zero (for any number of queries). The real **per-observation** advantage is `<= delta(p0)+delta(p1)` (**NO factor of 2**: single-observation Le Cam bound; corrected 2026-06-09, and the abstract/intro/conclusion were fixed so they do not claim a multi-query cap, only frequency-independence of the per-build separation). `delta` is small, scale-independent, and straddles the query-sampling floor (its *magnitude* is measured, labeled a characterization, not a closed-form bound: `rem:t5-bound`).

## Submission state

The canonical article version (`paper/codec_retrieval.tex`, ~33 pp, article class) is
de-anonymized and full; **keep it that way** (do not strip the author block or
self-citations from it). The PoPETs submission version is **prepared and anonymized**
under `venue/popets/` (see `## Venue submissions` below). Cross-venue status and the
decision log are in `SUBMISSIONS.md`; papermill state in `.papermill/state.md`; the path
to camera-ready (Zenodo DOI, de-anon) in `SUBMISSION-CHECKLIST.md`.

## Where the pieces live in the program

Theory in `bernoulli/` (the abstract codec-output law); the concrete construction
in `maph/` (the source of record, header-only C++23); confidentiality framing here
in `trapdoor-computing/`. This paper instantiates the `cipher-maps` abstraction
with the GF(2)-linear backend that the abstraction (random-oracle + RecSplit
backends only) does not itself have.

## Venue submissions

Per-venue tailored builds live in `venue/<venue>/` (canonical content stays in `paper/`).
`venue/popets/` is the PoPETs 2027 submission version (acmart sigconf, anonymized, 12-page
body, AI disclosure); build with `cd venue/popets && make`. Cross-venue status, deadlines,
and the decision log are in `SUBMISSIONS.md` (the submission ledger); per-venue mechanics
(e.g. the popets.sty masthead swap) live in each `venue/<v>/NOTES.md`. Update SUBMISSIONS.md
on every status change.
