# Submission checklist (PoPETs + artifact / Zenodo)

A running checklist for taking this from draft-complete to submitted, with the
artifact archived for a stable DOI. Nothing here is done until checked.

## Manuscript

- [ ] Switch `\documentclass[11pt]{article}` to the current PoPETs/PETS class and
      reflow (the paper is currently in a generic article class).
- [ ] Anonymize for double-blind review: remove the author block; neutralize
      self-citations (cipher-maps `towell2026ciphermaps`, the bernoulli-maps
      manuscript) to third-person ("prior work [N]"); scrub identifying repository
      names (maph, bijou, github handle) from the body and reproducibility section,
      referencing the anonymized artifact archive instead.
- [ ] Final pass on the abstract and intro contributions against the current theorem
      set (T1-T5c, `thm:realizable`, `thm:randenc` with its boundary).
- [ ] `cd paper && make` builds clean: 0 undefined references, 0 undefined
      citations. (Currently: 32 pages, clean.)
- [ ] Verify every `\cref` resolves and every `\cite` has a bib entry; re-verify the
      three previously-flagged citations are still correct.
- [ ] Re-read `FINDINGS.md` corrections against the manuscript: the randomized
      refutation, the realizable-set codec-dependent sufficiency, the mass-share
      uniform diagnosis, and the T5c cascade subtlety are all stated correctly.

## Artifact

- [ ] Land any final theorem/test changes in maph; re-run its full `ctest` (green).
- [ ] Tag the maph commit (e.g. `git -C maph tag codec-artifact-v1 <sha>`) so the
      pin cannot be lost to a rebase.
- [ ] `scripts/sync-from-maph.sh <final-sha>` to repin `artifact/` and refresh
      `source/construction-note.md` and `PROVENANCE.md`.
- [ ] Standalone reproduce from a clean checkout, no maph present:
      `cd artifact && cmake -S . -B build && cmake --build build -j && ctest --test-dir build`
      (expect 8/8), plus the `python/verification/` checks.
- [ ] Confirm `artifact/PROVENANCE.md` pins the tagged commit and the contents list
      is current.
- [ ] Anonymize the artifact for review (strip the github URL / handle from
      PROVENANCE; keep the pinned SHA).

## Zenodo / DOI

- [ ] Create a Zenodo deposit of the `artifact/` tree (the self-contained bundle).
      This is the same archival pattern as the cmri cluster (compendium DOI).
- [ ] Record the DOI in `paper/refs.bib` as the artifact reference, and cite it from
      the reproducibility paragraph instead of maph `master`.
- [ ] For the anonymized submission, use an anonymized artifact link (Zenodo
      supports restricted/anonymous sharing) or the PoPETs artifact-submission
      mechanism; de-anonymize for camera-ready.

## After acceptance

- [ ] De-anonymize: restore author block, self-citations, repository names, and the
      real artifact DOI.
- [ ] Cross-update `cipher-maps` (`towell2026ciphermaps`) once this paper has a
      stable citation / DOI, since it cites this as the construction companion.
