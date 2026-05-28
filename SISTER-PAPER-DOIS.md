# Sister-paper Zenodo DOI checklist

R8 review (`papers/cipher-maps/.papermill/reviews/2026-05-27/`)
identified MAJ-1 as the only remaining content-side blocker for
cipher-maps minor-revision: four sister-paper citations still say
"Manuscript in preparation."  This file enumerates what needs to
happen to close that.

## What's prepared

`.zenodo.json` files are now in place for each sister paper, with
title, description, keywords, and author metadata matching the
current state of each manuscript:

| Paper | Path | Zenodo prepared? |
|---|---|---|
| Cipher Maps | `papers/cipher-maps/.zenodo.json` | yes (refreshed to v4 thesis) |
| The Entropy Ratio (maxconf) | `papers/maximizing-confidentiality/.zenodo.json` | yes (new) |
| Cipher Rekeying | `papers/cipher-rekeying/.zenodo.json` | yes (new) |
| Algebraic Cipher Types | `papers/algebraic-cipher-types/.zenodo.json` | yes (new) |
| Bernoulli Types | `bernoulli/...` (separate repo) | NOT prepared (see below) |

## What you need to do (~30 min total)

### Step 1: Mint Zenodo DOIs for the three trapdoor-computing sister papers

For each of `maximizing-confidentiality/`, `cipher-rekeying/`, and
`algebraic-cipher-types/`:

1. Ensure the latest PDF is in the paper directory (run `make`).
2. Upload to Zenodo via the web UI, your `zenodo` CLI tool, or
   GitHub-Zenodo integration:
   - If using GitHub integration: tag a release on the trapdoor-computing
     repo (or split into per-paper repos first); Zenodo picks up the
     `.zenodo.json` metadata.
   - If uploading manually: paste the metadata from `.zenodo.json`.
3. Note the resulting DOI (format: `10.5281/zenodo.XXXXXXX`).

### Step 2: Decide on the bernoulli-types citation

The `bernoulli-types` cite in cipher-maps (3 occurrences at lines
156, 2069, 2101 of `cipher_maps.tex`) refers to a manuscript that
covers the Bernoulli error model and the trapdoor Boolean algebra
extension.  Three options:

- **(2a) Post to Zenodo too**: if the bernoulli-types manuscript is
  ready, mint a DOI for it just like the others.  Update the bib
  entry to point at it.
- **(2b) Replace with a specific bernoulli sub-paper**: the bernoulli
  monorepo at `~/github/bernoulli/papers/` has 9 papers; some of them
  (`bernoulli_sets`, `bernoulli_composition`, `bernoulli_maps`) may
  already be more specific references for the claims in cipher-maps.
  Replace the cite with whichever sub-paper actually carries the
  load-bearing claim.
- **(2c) Downgrade to "see also"**: weaken the cite from a load-bearing
  "developed in [bernoulli-types]" to a softer "see also [bernoulli-types]
  for background on the Bernoulli error model."

(2a) is the cleanest if the manuscript is ready; (2b) is preferable if
a specific sub-paper carries the claim; (2c) is the fallback if neither
is feasible before submission.

### Step 3: Send me the DOIs (or trigger the bib update yourself)

Once DOIs are minted, the bib entries currently look like:

```bibtex
@misc{towell2026maxconf,
  title={The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing},
  author={Towell, Alexander},
  year={2026},
  note={Manuscript in preparation}
}
```

I'll replace `note=...` with `doi={10.5281/zenodo.XXXXXXX}` and
`url={https://doi.org/10.5281/zenodo.XXXXXXX}` plus
`howpublished={Zenodo}` for each of the four entries.  Two-line edit
per entry; trivial.

After the bib update, MAJ-1 closes and cipher-maps drops cleanly to
minor-revision territory.

## What blocks each path

- **Zenodo upload**: needs you to be logged in (web UI) or to have
  the `zenodo` CLI configured with your access token.  Free Zenodo
  accounts give DOIs immediately.
- **Bernoulli-types decision**: needs you to either (a) finalize the
  manuscript and post it, (b) inspect the bernoulli sub-papers and
  pick a specific replacement, or (c) decide a downgrade is acceptable
  for submission.

## Reminder of remaining R8 items after MAJ-1 closes

| Item | Status |
|---|---|
| MAJ-1 sister-paper preprints | closes when you mint the DOIs |
| MAJ-4 PoPETs template port | submission-time, ~half day mechanical |
| MAJ-5 page trim (38pp) | depends on template port |
| MAJ-6 anonymization | submission-time, ~10 min |

None of these block continuing to iterate on content; they're the
final pre-submission mechanical steps.
