# Citation Verifier Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Verifier**: citation-verifier

## Summary

The bibliography file contains 12 entries, but only 6 are cited in the paper. The cited references are accurate but sparse -- a 15-page paper on encrypted computation with type-theoretic structure should cite significantly more related work.

---

## 1. Citation Accuracy

### Cited References (6)

| Key | Accuracy | Context |
|-----|----------|---------|
| bellare1993random | Correct (CCS 1993) | Used for random oracle model -- appropriate |
| gentry2009fully | Correct (STOC 2009) | Used to position against FHE -- appropriate |
| goldreich1996software | Correct (JACM 1996) | Used to contrast with ORAM -- appropriate |
| towell2026bernoulli | Correct (manuscript) | Used for Bernoulli error model -- appropriate |
| towell2026cipher | Correct (manuscript) | Foundation paper -- heavily cited, appropriate |
| yao1982protocols | Correct (FOCS 1982) | Used to contrast with garbled circuits -- appropriate |

### Uncited References in .bib (6)

The following entries exist in references.bib but are never cited:

| Key | Should be cited? |
|-----|-----------------|
| bloom1970space | Yes -- Bloom filters are directly relevant to the PHF-backed cipher map construction |
| fredman1984storing | Yes -- perfect hashing is the backbone of the cipher map construction |
| islam2012access | Yes -- access pattern attacks are directly relevant to the cipher TM head movement leakage |
| naveed2015inference | Yes -- inference attacks on property-preserving encryption are the closest attack model |
| shannon1948mathematical | Possibly -- entropy concepts are used but could be considered common knowledge |
| song2000practical | Yes -- searchable encryption is the most direct application domain |
| towell2026maxconf | Could be cited in the encoding granularity discussion |
| turing1936computable | Could be cited in the cipher TM section |

**Severity**: Major. Six references in the bib file that should be cited are not. This appears to be an oversight from a draft stage where citations were prepared but not yet inserted into the text.
**Confidence**: High.

---

## 2. Missing References

### Critical Missing

**Functional Encryption**: The paper discusses encoding functions as cipher maps (exponential types) but does not cite:
- Boneh, Sahai, Waters. "Functional Encryption: Definitions and Challenges." TCC 2011.
- This is the most direct comparison for the exponential type section.
**Severity**: Major.

**Symmetric Searchable Encryption**: The experimental results are about encrypted Boolean search, but the only searchable encryption reference (Song et al. 2000) is in the bib file and not cited:
- Curtmola, Garay, Kamara, Ostrovsky. "Searchable Symmetric Encryption: Improved Definitions and Efficient Constructions." CCS 2006.
- Cash, Jarecki, et al. "Highly-Scalable Searchable Symmetric Encryption with Support for Boolean Queries." CRYPTO 2013.
**Severity**: Major.

### Strongly Recommended

**Information Flow Type Systems**: The paper's core contribution is about type constructors and confidentiality, but does not cite the information flow literature:
- Sabelfeld, Myers. "Language-Based Information-Flow Security." IEEE J-SAC 2003.
- Volpano, Irvine, Smith. "A Sound Type System for Secure Flow Analysis." JCS 1996.
**Severity**: Major for PLAS venue (this IS the venue's core topic).

**Perfect Hash Functions**: The experimental construction uses PHF but does not cite:
- Czech, Havas, Majewski. "An optimal algorithm for generating minimal perfect hash functions." IPL 1992.
- Botelho, Pagh, Ziviani. "Practical perfect hashing in nearly optimal space." ISA 2013.
**Severity**: Minor (implementation detail, but useful for reproducibility).

### Recommended

**Property-Preserving Encryption Analysis** (beyond Naveed et al.):
- Boldyreva, Chenette, O'Neill. "Order-Preserving Encryption Revisited." EUROCRYPT 2011.
- Grubbs, Lacharite, Minaud, Paterson. "Pump up the Volume: Practical Database Reconstruction from Volume Leakage on Range Queries." CCS 2018.

**Algebraic/Categorical Approaches to Crypto**:
- Abadi, Rogaway. "Reconciling Two Views of Cryptography (The Computational Soundness of Formal Encryption)." JCSS 2007.

**20 Newsgroups Dataset**:
- Lang. "Newsweeder: Learning to filter netnews." ICML 1995.
- Or the standard sklearn reference.

---

## 3. Self-Citation Pattern

Three of six cited references are unpublished manuscripts by the same author:
- towell2026cipher (foundation -- necessary and appropriate)
- towell2026bernoulli (error model -- necessary)
- towell2026maxconf (in bib but NOT cited -- should either be cited or removed)

**Assessment**: Citing two unpublished companion papers is acceptable when they provide genuine foundations. The concern is that a reviewer cannot verify the properties this paper depends on (four cipher map properties, Bernoulli composition theorem, encoding granularity principle). 

**Recommendation**: Post towell2026cipher to IACR ePrint or arXiv before submitting this paper, so reviewers have access. Alternatively, expand the Preliminaries to be more self-contained.

**Severity**: Major (for reviewability, not for scientific content).
**Confidence**: High.

---

## 4. Bibliography Formatting

| Issue | Severity |
|-------|----------|
| Uncited entries should be removed from .bib before submission | Minor |
| towell2026maxconf in .bib but not cited -- dead reference | Minor |
| Two Towell 2026 entries disambiguated as (2026a) and (2026b) by natbib -- this is correct | N/A |
| No DOIs for any reference | Suggestion (not required for workshop) |
| Consistent use of @inproceedings vs @article -- correct | N/A |
