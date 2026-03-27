# Citation Verifier Report

**Date**: 2026-03-26
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The paper has 16 bibliography entries, all of which are cited in the text. No cited keys are missing from the bibliography. The bibliography was recently pruned (the state file noted 9 uncited entries that have been removed). The build produces no citation warnings.

## Findings

### F1. Self-citation [bernoulli-types] is unpublished (Minor, High confidence)
**Location**: Line 93, Section 1
**Bib entry**: `@unpublished{bernoulli-types, ... note = {Working paper}, year = {2024}}`
**Problem**: The paper depends on the Bernoulli model for its error framework, citing [bernoulli-types] which is listed as an unpublished "Working paper" from 2024. Reviewers cannot verify the referenced results. The composition theorem and space bounds reference the Bernoulli model's axioms (element-wise independence, conditional independence of block error rates), but these are not proven in the present paper.
**Suggestion**: Either (a) make the working paper available (e.g., on arXiv) with a stable URL, or (b) include the necessary Bernoulli results as a self-contained appendix in this paper.

### F2. Missing references for key claims (Major, High confidence)
Several claims in the paper rely on well-known results without citation:

1. **Shannon's source coding theorem** (referenced in Theorem 7.1 proof, lines 888-891; Proposition 5.2 proof, lines 588-591): No citation. Should cite Shannon (1948), "A mathematical theory of communication."

2. **Stirling's approximation** (referenced in Theorem 7.1 proof, line 881): No citation needed (standard), but the approximation $\log_2 \binom{|U|}{n} \approx n \log_2(|U|/n)$ is stated without conditions. Should note this requires $|U| \gg n$.

3. **Random oracle model** (used throughout): No foundational citation. Should cite Bellare & Rogaway (1993), "Random oracles are practical: A paradigm for designing efficient protocols."

4. **Total variation distance** (Definition 4.2, line 315): No citation needed (standard definition), but a reader unfamiliar with the concept gets only the formula. Consider adding the operational interpretation sentence currently present (line 318-320) directly into the definition.

### F3. Bib entry type for [bernoulli-types] (Minor, Medium confidence)
**Entry**: `@unpublished` with `note = {Working paper}`
**Problem**: If the paper is available online, `@misc` with a `url` field or `@techreport` with an institution would be more informative. If it is truly unpublished and unavailable, the reliance on it is a concern.
**Suggestion**: Update to `@misc` with a URL if available, or `@techreport` with institutional affiliation.

### F4. [bender2012quotient] title is the paper's subtitle, not the main title (Minor, Low confidence)
**Bib entry**: `title={Don't thrash: How to cache your hash on flash}`
**Actual paper**: The full title is "Don't thrash: How to cache your hash on flash" -- this appears correct. The paper is indeed about quotient filters though the title does not mention them. The citation in the text (line 123) says "Quotient filters [bender2012quotient]" which is accurate usage.
**Status**: No issue.

### F5. Missing references identified by literature survey
The literature context identified several references that would strengthen the paper:
1. **Chase & Kamara (2010)** -- Structured encryption, the most direct parallel framework
2. **Carter & Wegman (1979)** -- Universal hashing, foundational for the ROM usage
3. **Bellare & Rogaway (1993)** -- Random oracle model definition
4. **Shannon (1948)** -- Source coding theorem (referenced but not cited)

Of these, Shannon (1948) and either Carter-Wegman or Bellare-Rogaway are the most important additions.

## Bibliography Quality

- All 16 entries are correctly formatted and cited
- No duplicate entries
- No orphan entries (all cited)
- Publication venues and years appear correct for spot-checked entries
- The bibliography is lean but covers the major relevant works
- The unpublished [bernoulli-types] is the only entry without a stable venue

## Overall Assessment

The bibliography is clean and well-maintained. The most significant issue is the dependence on an unpublished working paper [bernoulli-types] for the Bernoulli error model. Adding citations for Shannon (1948) and the random oracle model (Bellare & Rogaway, 1993) would close the main gaps.
