# Citation Verifier Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Bibliography**: paper/references.bib (34 entries)

## Headline finding

Bibliography has 34 properly-formatted entries (verified clean by
bibtex; no warnings in the build log). All cited entries are used in
the manuscript. Four "Manuscript in preparation" entries remain
(`towell2026maxconf`, `towell2026rekeying`, `towell2026algebraic`,
`bernoulli-types`); two of these are load-bearing for the formal
results.

## R7 citation issues, R8 status

### NOT FIXED (R7 MAJ-5): Sister-paper preprints still pending
- **Location**: `towell2026maxconf` (lines 197 to 202),
  `towell2026rekeying` (lines 204 to 209)
- **Status**: Both still listed as "Manuscript in preparation".
- **Load-bearing usage**:
  - `towell2026maxconf` cited at Proposition 5.1 (line 762,
    `\cite[Theorem~4.1, part~3]{towell2026maxconf}`) for the
    Fannes-Audenaert continuity bound. Round 6 verified this cite is
    correct (Theorem 4.1 part 3 in maxconf is the relevant Fannes-
    Audenaert bound).
  - `towell2026rekeying` cited at §9.5 (line 2126,
    `\cite[Thm.~7.1]{towell2026rekeying}`) for the chain
    confidentiality bound. Round 6 verified this cite is correct.
- **Suggestion**: Post arXiv preprints with DOIs before PoPETs
  submission. PoPETs reviewers will rightly object to load-bearing
  citations pointing to unpublished manuscripts.
- Severity MAJOR (carry-over).

### NOT FIXED (R7 MAJ-16): Huffman 1952 missing from bibliography
- **Location**: §10.6 lines 2528 to 2563 (Pareto frontier discussion),
  §6.6 (acceptance predicates Shannon-optimal discussion)
- **Status**: Unchanged. The bibliography does not contain Huffman
  1952. The paper mentions Huffman 60+ times.
- **Suggestion**: Add `huffman1952method` to bib. Standard reference:
  Huffman, D. A. (1952). "A method for the construction of minimum-
  redundancy codes." Proceedings of the IRE, 40(9), 1098-1101. Cite
  at §6.6 first Huffman mention.
- Severity MAJOR (carry-over).

### NOT FIXED (R7 MAJ-17): bernoulli-types URL stale
- **Location**: References.bib line 49
- **Status**: Unchanged. URL points to
  `github.com/queelius/bernoulli_sets` which is now part of the
  bernoulli monorepo at `github.com/queelius/bernoulli`.
- **Suggestion**: Update URL to `github.com/queelius/bernoulli`. Or
  split bernoulli-types into specific sub-paper refs (bernoulli-sets,
  bernoulli-maps, bernoulli-relations, etc.).
- Severity MAJOR (carry-over).

### NOT FIXED (R7 CITE-MIN-2 to MIN-9): Carry-over minors
- **CITE-MIN-2**: Cover-Thomas 2006 missing for Kraft inequality
  background. Carry-over from R6.
- **CITE-MIN-3**: QIF multi-instance literature (Geng-Smith 2025 or
  equivalent) not cited despite §8.3's multi-instance contribution.
  Carry-over from R6.
- **CITE-MIN-4**: Patel-Persiano-Yeo-Yung 2019 (volume-hiding STE)
  missing. Carry-over from R6.
- **CITE-MIN-5**: Köpf-Smith 2010 (min-entropy leakage) missing despite
  §5.1 now explicitly justifying Shannon over min-entropy. Carry-over
  from R6.
- **CITE-MIN-6**: Pouliot-Wright 2016 (Kraken co-occurrence attack)
  missing. Carry-over from R6.
- **CITE-MIN-7**: `towell2026algebraic` cited once at §10.3 line 2385
  for the noise-floor mechanism. Load-bearing for the noise-floor
  derivation; preprint posting recommended.
- **CITE-MIN-8**: DOI fields absent throughout. Carry-over from R6.
- **CITE-MIN-9**: Le Cam 1986 cite (line 802) does not give a specific
  page or theorem number for the two-point lemma. Standard practice
  is to cite the specific page/theorem.
- All severity MINOR.

## R8 new citation findings

### CITE-N1 (NEW, MINOR): `towell2026codec` URL points to repository, not stable archive
- **Location**: References.bib line 283 to 289
- **Issue**: `towell2026codec` is cited as `@misc` with URL
  `https://github.com/queelius/bernoulli/tree/main/src/bernoulli/
  experiments`. This is a moving target (tree/main URLs change as
  the codebase evolves).
- **Suggestion**: Either point to a specific commit hash (e.g.,
  `tree/abc123/.../experiments`) or to a Zenodo-archived snapshot.
- Severity MINOR.

### CITE-N2 (NEW, MINOR): `kerschbaum2015frequency` bib title formatting
- **Location**: References.bib lines 238 to 244
- **Issue**: The title "Frequency-hiding order-preserving encryption"
  is in standard caps; no issues. Verified clean.
- Severity NONE (informational).

### CITE-N3 (NEW, MINOR): `kamara2019computationally` bib redundancy
- **Location**: References.bib lines 265 to 272
- **Issue**: The booktitle "Annual International Conference on the
  Theory and Applications of Cryptographic Techniques (EUROCRYPT
  2019)" is verbose; the parenthetical (EUROCRYPT 2019) duplicates
  what's effectively in the conference name.
- **Suggestion**: Shorten to "EUROCRYPT 2019" or
  "Advances in Cryptology--EUROCRYPT 2019" to match other entries.
- Severity MINOR.

### CITE-N4 (NEW, MINOR): `naveed2015inference` is cited twice
- **Location**: Citation count check: §2 line 223 (Property-preserving
  encryption paragraph), §2 line 266 (Leakage-abuse attacks
  paragraph). Both are appropriate; just noting the doubled use.
- Severity NONE (informational, not a problem).

### CITE-N5 (NEW, MINOR): `dodis2005entropic` citation appears once
- **Location**: §1 line 138, abstract via via the QIF positioning
  paragraph
- **Issue**: Dodis-Smith 2005 is cited only for entropic security as
  the historical positioning of cipher maps. This is appropriate.
- Severity NONE (informational).

## Summary of citation findings

- 0 critical
- 3 major carry-over from R7 (MAJ-5 sister preprints, MAJ-16 Huffman,
  MAJ-17 bernoulli-types URL)
- 8 minor carry-over from R7 (Cover-Thomas, QIF multi-instance,
  Patel-Persiano-Yeo-Yung, Köpf-Smith, Pouliot-Wright,
  towell2026algebraic preprint, DOIs, Le Cam page)
- 3 minor new (CITE-N1 towell2026codec URL, CITE-N3 Kamara-Moataz
  redundancy, plus the informational CITE-N2/N4/N5 which are clean)

**Citation-side recommendation**: Bibliography is technically clean
(34 entries, all properly cited, bibtex passes without warnings). The
major issues are the 3 carry-overs (sister-paper preprints, Huffman
1952, bernoulli-types URL). The 8 minor carry-overs are mostly missing
references that would strengthen positioning but are not blockers.
Posting the 2 load-bearing sister-paper preprints before PoPETs
submission is the single highest-impact citation action.
