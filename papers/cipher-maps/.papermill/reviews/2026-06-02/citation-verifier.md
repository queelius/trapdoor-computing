# Citation Verifier Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Bibliography**: paper/references.bib (34 entries)

## Summary

Bibliography integrity is clean: 34 cite-keys used, 34 bib entries, no
orphans, no undefined citations, no bibtex warnings. The standing issue is
the four "Manuscript in preparation" entries (the MAJ-1 Zenodo blocker),
one of which (towell2026maxconf) is load-bearing for Proposition 5.1. The
homophonic-arc edits this round did not add or break any citations; the
removed deferral sentence correctly removed a maxconf citation that is no
longer needed there.

**Counts**: Critical 0 | Major 1 | Minor 3 | Suggestions 1.

## Integrity check (PASS)

- `\cite` keys used: 34. Bib entries: 34. Exact match, no orphans.
- bibtex run: 0 warnings, 0 errors (cipher_maps.blg clean).
- No undefined-citation warnings in the LaTeX log.
- The removed deferral sentence (commit c9e830b) removed an inline
  `\cite{towell2026maxconf}` that pointed at an unverified tighter-constant
  claim; this was the correct removal and leaves no dangling citation.

## CITE-MAJ-1: Four "Manuscript in preparation" entries (carry-over R6/R7/R8)

**Entries** (references.bib):
- line 45-50: bernoulli-types ("Manuscript in preparation. See [URL]")
- line 190-195: towell2026algebraic ("Manuscript in preparation")
- line 197-202: towell2026maxconf ("Manuscript in preparation")
- line 204-209: towell2026rekeying ("Manuscript in preparation")

**Load-bearing forward references that must resolve at submission**:
- maxconf Theorem 4.1 part 3 (Proposition 5.1 proof; line 831)
- maxconf section 4 (entropy ratio definition; lines 771, 806)
- maxconf sections 5-6 (function-value leakage translation; line 894)
- rekeying Theorem 7.1 (chain confidentiality bound; line 2198)

These were verified in R6 against the actual companion-paper sources
(maxconf Thm 4.1 has 3 parts, part 3 is Fannes-Audenaert; rekeying section 7
has Theorem 7.1, the chain bound). The cite *targets* are correct; the
*availability* is the problem. A PoPETs reviewer cannot follow these to a
DOI.

**Net change this round**: exposure is slightly reduced. The homophonic
proposition is now self-contained, so the representation-uniformity story no
longer needs maxconf. The hard remaining dependency is Proposition 5.1 on
maxconf Thm 4.1 part 3.

**Suggestion**: Post all four to Zenodo with DOIs (user's MAJ-1 task).
Add `doi = {...}` fields. Closes the major. Estimated 1-2 days.

## CITE-MIN-1: Huffman 1952 missing (carry-over R7 CITE-2 / R8 CITE-MAJ-2)

The paper centers Huffman codes (the entropy cipher map, the Huffman-vs-TV
distinction, the "Shannon-optimal Huffman partition," the section 10.6
Pareto analysis) but never cites Huffman's 1952 paper. Conspicuous omission
given how load-bearing Huffman is. Strong recommend: add
`@article{huffman1952method, ...}` and cite at first Huffman mention
(line 1364 entropy cipher map, or line 1089 prefix-free code). The
distribution mislabel found this round (s=1 vs s=1.2; see logic LOG-MAJ-1)
is precisely about a Huffman code's behavior, which reinforces that the
Huffman reference belongs in the paper.

## CITE-MIN-2: Cover & Thomas 2006 missing (carry-over R8 CITE-MAJ-3)

Section 10.6 enumerates "all Kraft-feasible length assignments" (line 2667)
without a source-coding textbook citation. Cover-Thomas (or MacKay) for the
Kraft inequality and prefix-code background. Recommend.

## CITE-MIN-3: Multi-instance lineage uncited (carry-over R8)

Section 8.3's coincidence oracle should cite the multi-snapshot /
equality-pattern leakage lineage: Kellaris-Kollios-Nissim-O'Neill 2016
(generic reconstruction attacks) and/or the deterministic-encryption
equality-leakage line. Recommend, also flagged by novelty-assessor.

## CITE-SUG-1: DOI fields throughout

The bib lacks DOI fields on most entries. Camera-ready polish; PoPETs
prefers DOIs. (carry-over)

## Bottom line

Bibliography is internally clean. The only blocker is the four unpublished
companion papers (MAJ-1), which the user intends to resolve via Zenodo. The
three recommended adds (Huffman 1952, Cover-Thomas, multi-instance lineage)
are camera-ready-quality and non-blocking, though Huffman 1952 is the one a
careful reviewer is most likely to notice.
