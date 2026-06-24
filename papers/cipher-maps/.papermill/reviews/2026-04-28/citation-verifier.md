# Citation Verifier Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Citation Verifier
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Bibliography**: 23 entries in `paper/references.bib`

## Summary

Bibliography is mostly clean: all 23 entries are well-formatted, all in-text citations resolve. The Round 3 M3 fix added two new entries (cash2015leakage, juels2014honey) and they are properly cited. Two carry-over issues from Round 3: the unpublished self-citation (bernoulli-types) is still cited 3 times for foundational claims, and DOIs are still missing throughout. New issue: the "RecSplit-family PHF" mentioned in the experiments paragraph is not cited (literature scout flagged this independently).

**Findings**: 0 critical, 0 major, 4 minor.

---

## Verification of Round-3 fixes

### Bibliography count

23 `@` entries in references.bib (state file said 19; this round added cash2015leakage and juels2014honey, plus 2 others I cannot identify from the prior review snapshot were possibly already present). Bibliography integrity is good.

### M3 citation additions, VERIFIED

- `cash2015leakage`: properly added with full author list (Cash, Grubbs, Perry, Ristenpart) and venue (CCS 2015 = "Proceedings of the 22nd ACM SIGSAC Conference on Computer and Communications Security"). Cited in the new Leakage-abuse attacks paragraph (line 178).
- `juels2014honey`: properly added (EUROCRYPT 2014). Cited in the new Honey encryption paragraph (line 195).

Both new citations are well-formed and in-text use is appropriate.

---

## Citation integrity check

Cross-referenced all 23 bib entries against in-text citations. Findings:

### Cited entries (verified in text)
- bloom1970space: cited line 124, 1038
- fredman1984storing: cited line 137
- belazzougui2009hash: cited line 138, 927
- gentry2009fully: cited line 109, 213
- yao1982protocols: cited line 111, 212
- goldreich1996software: cited line 105
- curtmola2006searchable: cited line 159
- song2000practical: cited line 158
- cash2013highly: cited line 161
- bellare1993random: cited line 239
- simmons1979symmetric: cited line 225
- naveed2015inference: cited line 150, 174
- islam2012access: cited line 172
- juels2014honey: cited line 195
- cash2015leakage: cited line 178
- agrawal2004order: cited line 148
- boldyreva2009order: cited line 148
- bellare2007deterministic: cited line 149
- bender2012quotient: cited line 128
- fan2014cuckoo: cited line 129
- shannon1948mathematical: cited line 636, 1017
- bernoulli-types: cited line 96, 1347, 1379
- towell2026algebraic: cited line 1446

All 23 entries are cited. No orphan entries.

### In-text citations (verified entries exist)
Spot-checked 10 random `\cite{...}` invocations. All resolve to entries in the bib. No undefined references.

---

## Minor Findings

### C1. Self-citation `bernoulli-types` still unpublished, cited 3 times for foundational claims (MINOR, m10 from Round 3 not addressed)

**Location**: References to bernoulli-types at lines 96, 1347, 1379

**Quoted entry**:
```
@misc{bernoulli-types,
  title={Bernoulli Sets and Maps: A Probabilistic Framework for Approximate Data Structures},
  author={Towell, Alexander},
  year={2026},
  note={Manuscript in preparation. See \url{https://github.com/queelius/bernoulli_sets}}
}
```

**Problem**: The Bernoulli framework is foundational to:
- Line 96: "The error framework underlying cipher maps is the Bernoulli model~\cite{bernoulli-types}" (in the Bernoulli error model paragraph in Introduction)
- Line 1347: "the Bernoulli relations and algebraic types work~\cite{bernoulli-types}" (in §9.1 Relationship to Bernoulli Model)
- Line 1379: "developed in a companion paper~\cite{bernoulli-types}" (in §9.3 Online Construction)

Three citations to a "manuscript in preparation" is a risk. A PoPETs reviewer will likely either (a) fail to find a copy of the cited work and request that the dependent claims be backed by published material, or (b) request the manuscript and judge the paper partially on it.

The GitHub URL helps but is not a substitute for a stable preprint or published paper.

**Status from Round 3**: Not addressed.

**Suggestion**: Three options:
1. Post bernoulli-types as an arXiv preprint before submission. Update the bib entry to `@misc{...,note={arXiv:YYMM.NNNNN}}`. This is a few hours of work and resolves the issue cleanly.
2. Inline the essential definitions as a brief appendix to this paper. The Bernoulli error model fundamentals (FPR/FNR, composition formula) could fit in 1 to 2 pages.
3. Restructure the dependent passages to not require the citation. For instance, line 96 could be rephrased as "Two natural axioms (element-wise independence and conditional independence of block error rates) reduce the error model from exponential complexity to two parameters per element," dropping the citation entirely.

Option 1 is the cleanest. Option 2 is the safest for the paper's standalone value. Option 3 is the cheapest.

### C2. RecSplit-family PHF mentioned but not cited (MINOR, NEW)

**Location**: §6.4, line 934

**Quoted text**:
> "A reference implementation using a RecSplit-family PHF achieves 700 documents per second on the 20~Newsgroups corpus..."

**Problem**: "RecSplit" refers to Esposito-Müller-Pibiri-Venturini "RecSplit: Minimal Perfect Hashing via Recursive Splitting" (ALENEX 2020). The paper names the PHF family but does not cite it. A reader curious about RecSplit has nowhere to go.

**Suggestion**: Add the RecSplit citation to the bibliography:
```
@inproceedings{esposito2020recsplit,
  title={RecSplit: Minimal Perfect Hashing via Recursive Splitting},
  author={Esposito, Emmanuel and Müller, Thomas Mueller and Pibiri, Giulio Ermanno and Venturini, Rossano},
  booktitle={2020 Proceedings of the Workshop on Algorithm Engineering and Experiments (ALENEX)},
  pages={175--185},
  year={2020}
}
```
Then change line 934 to: "A reference implementation using a RecSplit-family PHF~\cite{esposito2020recsplit} achieves..."

### C3. Phobic library mentioned in experiments without context (MINOR, NEW)

**Location**: §9.4, line 1423

**Quoted text**:
> "Construction uses perfect hash functions (via \texttt{phobic})..."

**Problem**: "phobic" is presented as a tool name without explanation or citation. A reader unfamiliar with the library cannot locate it. If "phobic" is the author's own library, this should be made clear (e.g., "via \texttt{phobic}, the author's PHF library, available at [URL]"). If it's a third-party library, it should be cited.

**Suggestion**: Add a footnote or parenthetical explaining what `phobic` is, with either a citation or a URL. If it's the author's own library, this is also an opportunity for an artifact link.

### C4. No DOIs in bibliography (MINOR, m11 from Round 3 not addressed)

**Location**: All 23 entries in references.bib

**Problem**: None of the published entries have DOIs. PoPETs (and most modern venues) prefer DOIs for stable cross-references. Adding DOIs is a mechanical task: for each published entry, look up the DOI and add `doi = {...}` to the bib entry.

**Status from Round 3**: Not addressed.

**Suggestion**: Add DOIs to all 21 published entries (excluding bernoulli-types and towell2026algebraic, both unpublished). This is about 30 minutes of work and is part of standard pre-submission cleanup.

---

## Items Verified Sound

- All in-text `\cite{}` invocations resolve.
- No orphan entries in the bibliography.
- Author names spelled correctly across all entries.
- Venue names are full and unambiguous.
- Page ranges where present are correctly formatted.
- No duplicate entries.
- The new entries from Round 3 (cash2015leakage, juels2014honey) are well-formed and properly cited.

## Summary for the orchestrator

The bibliography itself is in good shape. The four findings are minor and largely procedural (DOIs, RecSplit citation, phobic explanation, bernoulli-types preprint). The single most consequential issue is C1 (unpublished self-citation), but it is rated MINOR because it is a procedural risk rather than a content issue. C2 (RecSplit) is also flagged independently by literature-context as a citation gap.

For the user's specific question about what else needs work: C1 (post bernoulli-types as arXiv) is the single most impactful citation fix before PoPETs submission. Without it, three load-bearing claims hang on a manuscript-in-preparation, which reviewers may flag or may be asked to evaluate in tandem.
