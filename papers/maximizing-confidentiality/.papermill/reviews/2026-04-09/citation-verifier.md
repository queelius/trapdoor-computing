# Citation Verifier Report

**Paper**: "Quantitative Confidentiality for Cipher Maps"
**Date**: 2026-04-09

---

## Overall Assessment

The bibliography contains 25 entries. Several important references are missing (see Literature Context). One entry has incomplete bibliographic data. All cited references appear to be real publications. The paper relies heavily on three companion papers by the same author, which is appropriate for a paper within a research program but creates a dependency chain that reviewers may question.

**Confidence**: HIGH

---

## Findings

### MAJOR: Critical missing references in Quantitative Information Flow

**Problem**: The paper's central measure (entropy ratio) is a normalized Shannon leakage, a well-studied concept in the QIF literature. The following references are critical for a theory venue:

1. **Smith (2009)**: "On the Foundations of Quantitative Information Flow." FoSSaCS. Defines min-entropy leakage; the paper's entropy ratio is the Shannon analog.
2. **Alvim, Chatzikokolakis, Palamidessi, Smith (2020)**: "The Science of Quantitative Information Flow." Springer. Comprehensive monograph covering exactly the kind of entropy-based leakage measurement this paper develops.

Without these, a reviewer at IEEE Trans. IT will likely flag the paper as insufficiently grounded in the existing information-theoretic security literature.

**Suggestion**: Add both references and discuss how the entropy ratio relates to Shannon leakage in QIF.

### MAJOR: Missing SSE leakage mitigation references

**Problem**: The paper's three levers (noise injection, multiplicity, granularity) have direct parallels in the SSE literature that are not cited:

1. **Bost & Fouque (2017)**: "Thwarting Leakage Abuse Attacks against Searchable Encryption." CCS. Proposes dummy queries (= noise injection lever).
2. **Demertzis, Papadopoulos, Papamanthou, Shintre (2020)**: "SEAL: Attack Mitigation for Encrypted Databases via Adjustable Leakage." USENIX Security. Tunable leakage-functionality trade-off.

**Suggestion**: Cite both in a Related Work section and distinguish the cipher map approach (information-theoretic) from the SSE approach (simulation-based).

### MINOR: Bibliographic entry for grubbs2018pump is incomplete

**Location**: references.bib, lines 143-148.

**Quoted text**:
```
@article{grubbs2018pump,
  title={Why your encrypted database is not secure},
  ...
  journal={Proceedings of the ACM on Management of Data},
  year={2018}
}
```

**Problem**: Missing volume, number, and pages. The venue name may also be incorrect -- the paper was originally presented at the 2018 ACM Conference on Management of Data (SIGMOD), not a journal called "Proceedings of the ACM on Management of Data." The full citation should include the conference name, pages, and DOI.

**Suggestion**: Update to the correct venue and add missing fields.

### MINOR: Three self-citations are unpublished manuscripts

**Location**: references.bib, entries towell2026cipher, towell2026algebraic, bernoulli-types.

**Problem**: All three companion papers are listed as `@unpublished` or `@misc` with notes like "Manuscript" or "Manuscript in preparation." At a peer-reviewed venue, reviewers may question the dependability of results cited from unpublished manuscripts. The paper's core definitions (cipher map, four properties, composition theorem) all depend on [towell2026cipher], which has no peer-reviewed publication record.

This is not unusual for papers within an active research program, but the reviewer should be aware that the entire theoretical foundation rests on an unpublished companion paper.

**Suggestion**: (1) Ensure the companion papers are available (the GitHub links work). (2) In the cover letter to the venue, note that the companion papers are available as manuscripts. (3) Consider submitting the cipher maps paper first or simultaneously.

### MINOR: Some cited references are not used in the text

I checked all 25 bibliography entries against the manuscript text. The following appear to be cited only in the bibliography but not referenced in the text:

- **sayood2017introduction**: Not explicitly cited in any `\cite{}` command visible in the manuscript. The compression discussion references Shannon (1948) but not Sayood.
- **mackay2003information**: Same -- not explicitly cited in the text.

**Suggestion**: Either add explicit citations where these references support claims, or remove them from the bibliography.

### SUGGESTION: Additional references to strengthen positioning

Beyond the critical QIF references, the following would strengthen the paper:

- **Bellare, Boldyreva, O'Neill (2007)**: CRYPTO. Deterministic encryption security via min-entropy.
- **Dodis & Smith (2005)**: TCC. Entropic security.
- **Fuller et al. (2017)**: IEEE S&P. SoK on encrypted database search.
- **Oya & Kerschbaum (2021)**: USENIX Security. Search pattern leakage.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 2 | Missing QIF references, missing SSE mitigation references |
| Minor | 3 | grubbs2018pump incomplete, unpublished companion dependencies, unused bib entries |
| Suggestion | 1 | Additional references for positioning |
