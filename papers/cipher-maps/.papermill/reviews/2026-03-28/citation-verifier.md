# Citation Verifier Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The bibliography contains 18 entries (17 from the .bib file + the bernoulli-types @misc entry). All 18 are cited at least once. No undefined references. No orphan entries. The build produces no citation warnings.

## Findings

### MAJOR: Missing citations critical for PoPETs positioning

- **Location**: Throughout, but especially Section 2 (Related Work) and Section 5 (Trust Model)
- **Problem**: For a PoPETs 2027 submission, the following omissions would be flagged by reviewers:

  1. **Leakage-abuse attacks**: The paper positions itself against property-preserving encryption and SSE but does not cite the attack literature that motivates these concerns:
     - Naveed, Kamara, Wright (CCS 2015): "Inference Attacks on Property-Preserving Encrypted Databases" -- directly relevant to the claim that cipher maps avoid PPE leakage
     - Islam, Kuzu, Kantarcioglu (CCS 2012): "Access Pattern Disclosure on Searchable Encryption" -- frequency analysis attacks, which representation uniformity claims to resist
     - Grubbs, Lacharite, Minaud, Paterson, Smart (S&P 2019): leakage abuse attacks on structured encryption
     - Cash, Grubbs, Perry, Ristenpart (CCS 2015): leakage-abuse attacks on SSE

  2. **Honey encryption**: Juels and Ristenpart (EUROCRYPT 2014): "Honey Encryption: Security Beyond the Brute-Force Bound" -- shares the core property that every decryption key produces plausible-looking output (analogous to cipher maps' totality + noise closure). This is the most closely related prior work not cited.

  3. **Entropic security**: Dodis and Smith (EUROCRYPT 2005) or Russell and Wang (EUROCRYPT 2006) -- information-theoretic security definitions based on entropy rather than computational assumptions. The cipher map's information-theoretic parameters ($\varepsilon$, $\delta$) are closest in spirit to entropic security.

- **Severity**: MAJOR (for PoPETs; the missing attack literature is the most critical gap)
- **Confidence**: HIGH
- **Suggestion**: Add at least Naveed et al. (2015) and Juels & Ristenpart (2014) to the bibliography. Discuss in Related Work: "Leakage-abuse attacks [Naveed et al. 2015, Islam et al. 2012] demonstrate that property-preserving encryption schemes leak more than their security definitions suggest. Cipher maps avoid property preservation entirely: the untrusted machine sees a total function on bit strings, not an encrypted comparison or equality test. However, the honest limitations (Section 8, Section 9.5) acknowledge that marginal uniformity alone does not prevent correlation-based attacks." Also: "Honey encryption [Juels & Ristenpart 2014] ensures that every decryption key produces a plausible plaintext, sharing the spirit of totality (every input produces output). Cipher maps generalize this from decryption to arbitrary function evaluation."

### MINOR: Self-citation [bernoulli-types] is cited 3 times but is unpublished

- **Location**: Lines 96, 1201, 1233
- **Quoted text**: "Manuscript in preparation. See \url{https://github.com/queelius/bernoulli_sets}"
- **Problem**: The paper cites bernoulli-types three times, including for the error model foundation (Section 1) and the online construction (Section 9.3). Relying on unpublished work for foundational definitions is risky for peer review. Reviewers may not be able to verify the referenced claims.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Either (a) make the Bernoulli paper available as a preprint (e.g., arXiv) before submission, or (b) include the essential Bernoulli definitions (element-wise independence, conditional independence of block error rates) as a brief appendix, with a note that the full development is in preparation.

### MINOR: Missing DOIs for most bibliography entries

- **Location**: references.bib
- **Problem**: None of the 17 published entries have DOIs. PoPETs submissions benefit from DOIs for verifiability.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Add DOIs for the published entries (all 17 except bernoulli-types).

### Bibliography Integrity Check

| Entry | Cited | Title verified | Year verified | Venue verified |
|---|---|---|---|---|
| gentry2009fully | Yes (x2) | Correct | Correct | STOC 2009 |
| bloom1970space | Yes (x2) | Correct | Correct | CACM 1970 |
| goldreich1996software | Yes (x1) | Correct | Correct | JACM 1996 |
| cash2013highly | Yes (x1) | Correct | Correct | CRYPTO 2013 |
| yao1982protocols | Yes (x2) | Correct | Correct | FOCS 1982 |
| bernoulli-types | Yes (x3) | N/A (unpublished) | 2026 | N/A |
| bender2012quotient | Yes (x1) | Correct | Correct | VLDB 2012 |
| fan2014cuckoo | Yes (x1) | Correct | Correct | CoNEXT 2014 |
| fredman1984storing | Yes (x1) | Correct | Correct | JACM 1984 |
| belazzougui2009hash | Yes (x2) | Correct | Correct | ESA 2009 |
| agrawal2004order | Yes (x1) | Correct | Correct | SIGMOD 2004 |
| boldyreva2009order | Yes (x1) | Correct | Correct | EUROCRYPT 2009 |
| bellare2007deterministic | Yes (x1) | Correct | Correct | CRYPTO 2007 |
| song2000practical | Yes (x1) | Correct | Correct | S&P 2000 |
| curtmola2006searchable | Yes (x1) | Correct | Correct | CCS 2006 |
| simmons1979symmetric | Yes (x1) | Correct | Correct | ACM Surveys 1979 |
| bellare1993random | Yes (x1) | Correct | Correct | CCS 1993 |
| shannon1948mathematical | Yes (x2) | Correct | Correct | BSTJ 1948 |
