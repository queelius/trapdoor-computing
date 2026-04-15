# Citation Verifier Report

**Paper**: Algebraic Cipher Types (2026-04-12 restructure, 17pp)
**Date**: 2026-04-12
**Scope**: Citation accuracy, missing references, bibliography integrity.

## Summary

The bibliography file contains 17 entries; 10 are cited in the paper, 7 are dead (never referenced in the text). The paper expanded from 6 cited references (prior review M2) to 10, which is an improvement but still far below the 20 to 30 expected for a PLAS paper. Critical gaps remain: no recent (post-2020) references, no dataset citation for 20 Newsgroups, no Bloom filter citation despite using the concept, no perfect-hashing citation despite relying on PHF, and three of the 10 cited references are unpublished self-citations.

---

## Major Issues

### CV-MAJ-1. Seven dead bib entries (not a regression, unchanged from prior review)

**Location**: `references.bib`.

**Dead entries** (present in bib, never cited):
1. `bloom1970space` (Bloom filters)
2. `fredman1984storing` (FKS perfect hashing)
3. `islam2012access` (access pattern attacks on SSE)
4. `shannon1948mathematical` (Shannon information theory)
5. `song2000practical` (practical encrypted search)
6. `towell2026maxconf` (Maximizing Confidentiality, self)
7. `turing1936computable` (Turing machines)

**Problem**: bibtex emits no warnings for unused entries, but dead references in a submitted .bib are a sign of incomplete editing. They also occupy space in a reviewer's perception of the bibliography.

**Suggestion**: For each, either (a) cite in-place where relevant, or (b) remove from the bib.

Recommended placements for those worth keeping:
- `bloom1970space`, **cite** at Section 7.1 when introducing the cipher Boolean type (the False region behaves like a Bloom filter's "definitely not in set" region; the cipher type is a Bloom-like construction with additional noise). This is a natural fit.
- `fredman1984storing`, **cite** at Section 6.2 (line 988) where "PHF-backed cipher map" appears; and at Section 7.1 when introducing the cipher Boolean construction.
- `shannon1948mathematical`, **cite** at Remark 7.1 where "Shannon-optimal allocation" appears. The parenthetical "(Shannon-optimal allocation)" without citation is exactly where this reference belongs.
- `turing1936computable`, **cite** at Section 6.1 where cipher Turing machines are introduced.
- `song2000practical`, **cite** at Section 2 Related Work (SSE paragraph) or Section 7.3 (experimental comparison).
- `islam2012access`, **cite** at Section 2 Related Work near the Naveed et al. 2015 citation on inference attacks.
- `towell2026maxconf`, **cite** somewhere or remove. The author's companion paper on maximizing confidentiality is thematically very close; Section 5 or Section 8 should mention it.

Each missed citation is a small issue; collectively they add up to "the author put references in the bib but forgot to use them."

### CV-MAJ-2. Missing high-relevance recent references (carry-forward of M2)

**Location**: Paper-wide.

**Problem**: The paper cites exactly one reference newer than 2015 (the author's own 2026 manuscripts). This is insufficient for PLAS (a venue that expects engagement with current work). Specific relevant literature:

**For Section 2 (Related Work)**:
- Kellaris et al., "Generic Attacks on Secure Outsourced Databases" (CCS 2016): leakage-abuse attacks.
- Grubbs et al., "Leakage-Abuse Attacks against Order-Revealing Encryption" (S&P 2017): direct relevance to "cipher maps avoid property preservation."
- Cash et al., "Leakage-Abuse Attacks Against Searchable Encryption" (CCS 2015): SSE baseline.
- Cash et al., "Dynamic Searchable Encryption via Blind Storage" (S&P 2014).
- Grubbs et al., "Why Your Encrypted Database Is Not Secure" (HotOS 2017).

**For information flow and types**:
- Murray et al., "seL4: from General Purpose to a Proof of Information Flow Enforcement" (S&P 2013).
- Rajani-Garg, "On the Expressiveness of Information Flow Types for Security" or similar type-systems-for-security work 2017 to 2023.
- Hritcu et al., work on F* for security verification.

**For FHE and compilation**:
- Cheon et al., "Homomorphic Encryption for Arithmetic of Approximate Numbers" (ASIACRYPT 2017): CKKS, the currently dominant approximate FHE scheme.
- Viand, Jattke, Hithnawi, "SoK: Fully Homomorphic Encryption Compilers" (S&P 2021): compilers that automatically transform programs to use FHE.
- Gouert-Boemer-Tsoutsos, "HELM: Navigating Homomorphic Encryption through Gates and Lookup Tables" (2023): relevant to cipher-map-as-lookup-table framing.

**For PL/security intersection**:
- Pottier & Simonet, "Information Flow Inference for ML" (POPL 2002 and later): type-system analogues to orbit analysis.
- O'Neill & Schreuder, more recent IFC work.

**Suggestion**: Add 8 to 12 of these references across Section 2 (Related Work), Section 5 (Orbit Closure), and Section 7 (Cipher Boolean). Target bibliography size: 20 to 25 entries. Focus on the FHE compilers and SSE leakage literature for strongest fit.

### CV-MAJ-3. 20 Newsgroups dataset uncited (carry-forward of m10)

**Location**: Section 7.3, lines 1192 to 1194.

**Problem**: The 20 Newsgroups corpus is mentioned twice ("20 Newsgroups Boolean search task" in abstract; "the 20 Newsgroups corpus (18,266 documents, 58,903 unique words)" in Section 7.3) but never cited. Standard practice is to cite Lang 1995 or the scikit-learn data documentation.

**Suggestion**: Add to .bib:

```
@misc{lang1995newsweeder,
  title={{NewsWeeder}: Learning to filter netnews},
  author={Lang, Ken},
  booktitle={Proceedings of the 12th International Conference on Machine Learning},
  year={1995}
}
```

Cite at first mention of the corpus.

### CV-MAJ-4. Three of 10 cited references are unpublished self-citations (carry-forward of M9)

**Location**: references.bib, specifically `towell2026cipher`, `towell2026bernoulli`, `towell2026maxconf` (not currently cited but present in bib).

**Problem**: `towell2026cipher` is cited 16 times in the paper (including 6 specific section-level cites like `[9, Sec. 9]`, `[9, Prop. 9.1]`). The paper depends critically on this reference for:
- Cipher map definition (Def 3.1)
- Four properties (Section 3)
- Encoding granularity principle (Section 4.2, Section 8)
- Four-property composition (Section 6.1 Prop 6.1)
- Proposition 9.1 referenced in Remark 6.2

`towell2026bernoulli` is cited 4 times as the source of the Bernoulli error model (Section 3, Section 7.3, Section 8, Conclusion).

Both are "manuscript in preparation" and therefore not accessible to reviewers. A reviewer who cannot access the cipher-maps paper cannot fully evaluate Theorem 5.3 (which references representation uniformity from [9]) or Section 6.1 Prop 6.1 (which cites [9, Sec. 6]).

**Suggestion**: This issue is largely a logistics problem (post the companion papers to arXiv/ePrint before submission) but the paper itself could help by:
(a) **Expanding Preliminaries** (Section 3): the four properties are currently listed but the composition theorem is only stated in line 215. A standalone paragraph giving the composition theorem, its proof sketch, and the encoding granularity principle would make this paper more self-contained. Target: +1 page of Preliminaries material.
(b) **Provide an anonymized/public companion document**: even a short technical-report version of towell2026cipher on ePrint would satisfy reviewers.
(c) **Reduce dependency**: for each specific citation like `[9, Sec. 9.3]` or `[9, Prop. 9.1]`, include the statement inline rather than just a pointer.

For PLAS submission deadlines, (a) plus (b) is the safe path. Without them, two of the paper's central theorems (Thm 5.3 assumes delta close to 0 from [9]; Prop 6.1 cites [9, Sec. 6] for space accounting) are not independently verifiable by reviewers.

---

## Minor Issues

### CV-MIN-1. "towell2026cipher" author field style inconsistent

**Location**: references.bib, entries 1, 8, 15.

**Problem**: The entries use:
- `author={Towell, Alexander}`

This is consistent with itself, but the bibstyle is plainnat (checked line 1395 of main.tex). plainnat would render as "A. Towell" in the text. Fine. No issue.

### CV-MIN-2. Bib key style inconsistent: year suffix vs. first-word suffix

**Location**: references.bib.

The bib mixes styles:
- `towell2026cipher` (year + first word of title)
- `gentry2009fully` (year + first word of title)
- `bloom1970space` (year + first word of title)
- `yao1982protocols` (year + first word of title)
- `sabelfeld2003language` (year + first word of title)

Actually consistent on inspection. No issue.

### CV-MIN-3. "phobic" PHF library is uncited

**Location**: Section 7.3, line 1193: "reference implementation (cipher-maps, Python with PHF backend via phobic)".

**Problem**: `phobic` is a dependency that a reproducibility-conscious reader will want to find. A URL or citation is expected.

**Suggestion**: Add a footnote or note: "phobic is available at https://github.com/[path]." Or cite a paper if one exists for the library.

### CV-MIN-4. `bellare1993random` citation placement

**Location**: Section 3, line 202.

**Quoted text**: "Out-of-domain outputs are indistinguishable from uniform under the random oracle model [1]."

**Problem**: The random oracle model *as a concept* dates to Bellare-Rogaway 1993 (cited). However, the out-of-domain-uniform claim specifically is a property of hash-based cipher-map constructions (documented in towell2026cipher presumably). The current citation is fine but slightly generic; the reader may wonder if the specific claim is proven in Bellare-Rogaway (it is not).

**Suggestion**: "Out-of-domain outputs are indistinguishable from uniform under the random oracle model [1] for hash-based cipher map constructions (see [9, Prop. 4.2] for the formal statement)."

### CV-MIN-5. Related Work does not cite `naveed2015inference` inline

**Location**: Section 2, "Searchable symmetric encryption" paragraph (lines 165 to 175).

The reference IS cited: "Naveed et al. [6] demonstrated inference attacks on property-preserving encryption." This is fine. Just noting that the citation is present and in the right place.

Note: `islam2012access` would fit naturally in this same paragraph as a companion citation on access-pattern attacks. See CV-MAJ-1.

---

## Suggestions

### CV-SUG-1. Bibliography target for PLAS: 22 to 28 references

PLAS papers typically cite 20 to 30 references across ACM sigconf format. Currently cited: 10. Delta: 12 to 18 additions needed. A reasonable distribution:
- 4 to 6 FHE / encrypted computing (3 currently, gentry, bloom missing, cipher-maps self)
- 3 to 4 SSE / encrypted search (2 currently, Curtmola + Naveed)
- 3 to 4 information flow / language-based security (1 currently, Sabelfeld-Myers)
- 2 to 3 functional encryption / obfuscation (1 currently)
- 2 to 3 foundational crypto (Yao, ORAM, random oracle, each cited)
- 2 to 3 on perfect hashing and Bloom filters (0 cited; 2 in dead bib)
- 2 to 3 on ORAM / obfuscation (1 cited)
- 1 to 2 dataset / tooling citations (0 currently)

### CV-SUG-2. Use `natbib` more expressively

The paper uses `\cite{...}` exclusively. With natbib, `\citet{boneh2011functional}` would render as "Boneh et al. [2]" and read more naturally than "Functional encryption [2]" at line 153. Minor but improves readability.

### CV-SUG-3. Consider citing the author's own sister paper more prominently

`towell2026maxconf` (Maximizing Confidentiality under Trapdoor Computing) is in the .bib but unused. Given the thematic overlap (both papers are about confidentiality in the trapdoor-computing ecosystem), and given the state.md lists it as a "sibling" paper, explicit cross-citation is warranted. Section 5 or Section 8 could include a brief pointer: "The quantitative entropy-ratio framing complementary to orbit-closure confidentiality is developed in [towell2026maxconf]."

---

## Cross-cutting Observations

- **Bibliography integrity**: Improved since prior review (6 to 10 cited), but 7 dead entries remain, and 12 to 18 more are needed for PLAS.
- **Self-citation**: 3 of 10 cited references are author's own unpublished manuscripts. High dependency on cipher-maps paper in particular.
- **Verifiability**: The paper's two most important external dependencies (representation uniformity delta, four-property composability) are sourced to an unpublished paper. This is a significant problem for a submission.
- **Prior-review status**:
  - M2 (bibliography thin), **partially addressed**: 6 to 10, still short of 20.
  - M9 (unpublished self-citations), **not addressed**: the 3 self-citations remain; post the companion to ePrint.
  - m10 (20 Newsgroups uncited), **not addressed**.
