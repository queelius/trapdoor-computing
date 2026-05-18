# Citation Verifier Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Verify citation accuracy, bibliography integrity, and identify
missing/stale references. Focus on Round 7 deltas.

## CITATION INVENTORY

Bibliography has 33 entries. 30 are properly cited in the manuscript.
3 are special:

- `towell2026maxconf` (4 cites, "Manuscript in preparation")
- `towell2026rekeying` (2 cites, "Manuscript in preparation")
- `towell2026algebraic` (1 cite, "Manuscript in preparation") - NEWLY
  USED in R7 at §10.3 line 2375
- `towell2026codec` (1 cite, "@misc" with URL) - USED in R7 at §10.6
  line 2467

Citation counts have grown by 2 from R6 (added `towell2026codec`,
activated `towell2026algebraic`).

All 33 bib entries are referenced at least once. No orphan entries
in the bib.

## MAJOR FINDINGS

### CITE-1: Sister-paper preprints still pending (carry-over)

**Status**: Carry-over from R5 (CITE-6) and R6 (MAJ-6). Two
load-bearing citations remain at "Manuscript in preparation":

- `towell2026maxconf`, cited at lines 69, 699, 728, 734, 759 ("[Theorem
  4.1, part 3]"), 822 ("[§ 5-6]"). The Theorem 4.1 part 3 cite is
  load-bearing for Proposition 5.1.
- `towell2026rekeying`, cited at lines 373, 585, 2105, 2116 ("[Thm.
  7.1]"). The Theorem 7.1 cite is load-bearing for the
  bounded-composition discussion at §9.5.

PoPETs reviewers will not accept "Manuscript in preparation" for
load-bearing claims. Must post preprints with DOIs before submission.

### CITE-2: Huffman 1952 is missing from bibliography

**Status**: NEW in R7. The §10.6 Pareto-frontier discussion centers
Huffman codes vs TV-optimal allocations. The Huffman algorithm
(Huffman 1952, "A Method for the Construction of Minimum-Redundancy
Codes") is not cited. This is a standard reference that should be in
any paper centering Huffman codes.

**Suggestion**: Add Huffman 1952 reference. Cite at line 1019 ("This
is the entropy cipher map construction") or at §10.6 lines 2528-2535
("Huffman is always on the Pareto frontier").

### CITE-3: `bernoulli-types` "Manuscript in preparation" with broken pattern

**Status**: Carry-over. `bernoulli-types` cited at lines 153 ("Bernoulli
model"), 2059 ("Bernoulli relations and algebraic types work"), 2091
("trapdoor Boolean algebra"). The bib entry says "See
https://github.com/queelius/bernoulli_sets" but this directory was
removed from the github.com/queelius account. The hub repo is now at
`github.com/queelius/bernoulli`. URL is stale.

**Suggestion**: Update the URL or specify which sub-paper(s) of the
bernoulli monorepo the citation refers to. The bernoulli monorepo
contains ~9 papers, each cited differently by cipher-maps. The
current single-key citation pattern is too coarse.

## MINOR FINDINGS

### CITE-MIN-1: §6.4 first RecSplit mention now has citation (R6 carry-over closed)

**Status**: R6 CITE-3 (RecSplit at §6.4 first mention) is now
addressed. §6.4 line 1283 has `\cite{esposito2020recsplit}`.

### CITE-MIN-2: Cover-Thomas not cited for Kraft inequality / coding background

**Location**: §10.6 (TV, L) Pareto frontier discussion.

**Problem**: The discussion of "Kraft slack" (line 2538) and
"Kraft-feasible length assignments" (line 2522) leans on coding theory
background that is not anchored to a textbook citation. Cover-Thomas
2006 (Elements of Information Theory) or MacKay 2003 (Information
Theory, Inference, and Learning Algorithms) would do.

### CITE-MIN-3: QIF multi-instance literature not cited

**Location**: §8.3 (multi-instance composition leakage).

**Problem**: Multi-instance attacks on entropic primitives have a
literature (Geng-Smith 2023/2025, Boyle-Lavigne-Vaikuntanathan 2017,
Bellare-Tessaro-Vardy 2012). §8.3 cites none of them. The novelty
claim NOV-3 would be more credible with at least one acknowledgment
of this neighbor.

### CITE-MIN-4: Patel-Persiano-Yeo-Yung 2019 (volume-hiding STE) is not cited

**Location**: §2 (Related Work) and §9 (Discussion).

**Status**: R6 flagged this as a strong recommendation. Still not
cited. The Kamara-Moataz 2019 cite covers the computational
volume-hiding work, but the Patel-Persiano-Yeo-Yung 2019 work covers
the information-theoretic volume-hiding line that is structurally
closer to the cipher-maps approach. Add.

### CITE-MIN-5: Köpf-Smith 2010 min-entropy leakage not cited despite Shannon vs min-entropy discussion

**Location**: §5.1 lines 718-728.

**Problem**: The paragraph "We use Shannon entropy rather than
min-entropy because..." is exactly the discussion that should cite
Köpf-Smith 2010 as the foundational alternative-measure work.

### CITE-MIN-6: Pouliot-Wright 2016 not cited for §8.2 compositional leakage

**Location**: §8.2 (compositional leakage).

**Problem**: Carry-over. Co-occurrence attacks (Pouliot-Wright 2016)
are directly relevant to the §8.2 compositional-leakage discussion.

### CITE-MIN-7: `towell2026algebraic` cited once for a load-bearing claim

**Location**: §10.3 line 2375.

**Quoted text**:
> "the precise per-construction FP rate depends on how the cipher
> Boolean AND routes noise-region inputs through its PHF, characterized
> in companion work~\cite{towell2026algebraic}."

**Problem**: This load-bearing claim ("the precise FP rate is
characterized in algebraic") is in a "Manuscript in preparation"
companion. The 3-term AND FP arithmetic explanation (CRIT-1 from R6)
is partially resolved by appealing to this unpublished work. If the
algebraic preprint posts in time, this closes. If not, the FP
discrepancy explanation depends on an unverifiable source.

### CITE-MIN-8: DOI fields still absent throughout bib

**Status**: Carry-over from R4 (m11). All 33 bib entries lack DOI
fields. Modern bib hygiene includes DOIs where available.

### CITE-MIN-9: `lecam1986asymptotic` page number for two-point lemma not given

**Location**: §5.2 line 798-799.

**Quoted text**:
> "Le Cam's two-point lemma~\cite{lecam1986asymptotic}"

**Problem**: The two-point lemma is a specific result in a 700-page
book. A page number or section number would help readers locate the
result.

### CITE-MIN-10: `towell2026codec` URL points to bernoulli repo, not a stable archive

**Location**: bib entry for `towell2026codec`.

**Quoted text**:
> "howpublished={Companion experiment suite,
> \url{https://github.com/queelius/bernoulli/tree/main/src/bernoulli/experiments}}"

**Problem**: Cited for experimental claims (Tables in §10.6) that are
load-bearing for novelty. The URL is a github tree URL (commit-pinned
would be more reproducible). For PoPETs, an arxiv preprint of the
experiment writeup or a Zenodo DOI for the experiment code would be
stronger.

### CITE-MIN-11: `kerschbaum2015frequency` Springer page/proceeding details

The bib entry has booktitle and pages but no editor, publisher,
address. Minor bib hygiene.

### CITE-MIN-12: `kamara2019computationally` is in EUROCRYPT 2019 not Annual Conference

Bib entry says "Annual International Conference on the Theory and
Applications of Cryptographic Techniques (EUROCRYPT 2019)". This is
correct but redundant. Standard convention is "Advances in Cryptology
- EUROCRYPT 2019" matching `juels2014honey`.

## SUGGESTIONS

### CITE-SUG-1: Add a "Concurrent and prior work in multi-instance composition" subsection in §2 or §8

After fixing CRIT-1 and CITE-MIN-3, a 2-paragraph subsection on
multi-instance composition prior work would close the literature gap
on the v3 thesis claim #3.

### CITE-SUG-2: Add Warner 1965 cite to Proposition 10.4.1 (Bayesian deniability)

**Status**: R6 NOV-4. Now addressed at line 2406-2407: "the
construction below is a direct restatement of Warner's randomized
response mechanism~\cite{warner1965randomized}". Verified that the
cite is now present.

### CITE-SUG-3: Update `bernoulli-types` to point at specific sub-papers

Replace the single `bernoulli-types` key with multiple keys
(bernoulli_sets, bernoulli_maps, etc.) and cite specifically. The
bernoulli monorepo has clear paper-level structure.

## Summary

- Critical: 0
- Major: 3 (CITE-1 sister-paper preprints carry-over, CITE-2 Huffman
  1952 missing, CITE-3 bernoulli-types URL stale)
- Minor: 12
- Suggestions: 3
