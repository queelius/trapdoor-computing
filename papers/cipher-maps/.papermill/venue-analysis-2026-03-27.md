# Venue Analysis: Cipher Maps Paper

**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Author**: Alexander Towell
**Date**: 2026-03-27
**Current format**: 22 pages, single-column, 11pt article class, ~1536 lines LaTeX

## Paper Characteristics

Before ranking venues, the paper's distinguishing features that affect venue selection:

- **Theoretical contribution**: new privacy model (totality-based, not ORAM/FHE/simulation-based), four formal properties, composition theorem with proof, space lower bound
- **No implementation or benchmarks**: purely theoretical; no empirical evaluation
- **No formal security game**: information-theoretic parameters (eta, epsilon, delta) rather than game-based or simulation-based definitions
- **Interdisciplinary**: straddles privacy/security, data structures (hash constructions, space bounds), and information theory (entropy-optimal encoding)
- **Single author, independent researcher**: no institutional affiliation
- **22 pages single-column**: approximately 11-12 pages in double-column ACM format, or ~18-20 pages in LNCS format

## Venue Shortlist (Ranked)

### 1. PoPETs / PETS (Proceedings on Privacy Enhancing Technologies) -- RECOMMENDED

**Scope fit**: STRONG. PoPETs publishes work on privacy technologies including new privacy models, theoretical foundations, and information-theoretic approaches. The paper's core contribution -- a new privacy model based on totality rather than ORAM/FHE/simulation -- is directly in scope. PoPETs is more receptive to non-standard privacy models than the top-4 security conferences.

**Format fit**: GOOD. Camera-ready limit is 13 pages (body) + unlimited references and appendices. The paper at ~22 single-column pages would need compression to fit within 13 pages using the PoPETs LaTeX template, but this is feasible: the current format has generous margins and spacing. The related work section (2 pages) and some construction details could be condensed. Appendices can absorb proof details.

**Impact/prestige**: HIGH. PoPETs is the top venue specifically for privacy research. Scopus-indexed, widely cited in the privacy community. Not quite the prestige of S&P/CCS/USENIX Security, but the leading specialist venue.

**Acceptance rate**: ~21-26% (148/708 in 2024, 169/644 in 2025). Competitive but not brutally so.

**Review timeline**: 4 rolling deadlines per year, ~2 months from submission to decision. Rejected papers can be revised and resubmitted to the next issue with a shepherd letter.

**Upcoming deadlines**: PoPETs 2026 Issue 4 deadline was 2026-02-28 (passed). PoPETs 2027 deadlines not yet announced but historically follow the same quarterly pattern: ~May 31, Aug 31, Nov 30, Feb 28. The **PoPETs 2027 Issue 1 deadline would be approximately 2026-05-31**.

**Changes needed**:
- Reformat to PoPETs LaTeX template (13-page body limit)
- Condense related work and proof details (move proofs to appendices)
- Strengthen the privacy motivation in the introduction -- PoPETs reviewers will expect clear articulation of the threat model and what privacy guarantees are achieved
- Consider adding a concrete application scenario (encrypted search, outsourced computation) to ground the theory

**Assessment**: Best overall fit. The paper proposes a new privacy model, which is exactly what PoPETs exists to evaluate. The rolling deadline structure gives flexibility. The resubmission mechanism provides a safety net. The lack of implementation is acceptable at PoPETs for a sufficiently strong theoretical contribution.

---

### 2. IEEE Transactions on Information Theory (IEEE T-IT)

**Scope fit**: GOOD. T-IT covers Shannon theory, coding theory, cryptography, and information security. The paper's space lower bound (-log2(epsilon) + H(Y) bits/element), entropy-optimal encoding, and composition theorem are information-theoretic results. The cryptography section of T-IT regularly publishes information-theoretic security papers.

**Format fit**: GOOD. Journal format, up to 50 pages single-column for submission (25 pages double-column final). The paper at 22 pages fits comfortably without cuts. Would need reformatting to IEEE two-column template for the final version.

**Impact/prestige**: VERY HIGH. IF ~2.9-3.2, h-index 285. One of the most prestigious journals in information theory and adjacent fields. Publication here would strongly validate the information-theoretic aspects of the work.

**Acceptance rate**: Low (estimated ~20-25% for regular papers). The editorial board expects strong analytical contributions with novel information-theoretic content.

**Review timeline**: Long -- typically 6-12 months for a first decision. Journal reviews are thorough but slow.

**Upcoming deadlines**: Rolling submissions (journal). No deadline pressure.

**Changes needed**:
- Reformat to IEEE T-IT template
- Strengthen the information-theoretic framing: the space lower bound proof and entropy-optimal encoding should be more prominent
- The privacy/security framing may need to be de-emphasized in favor of the information-theoretic contribution
- Reviewers will expect rigorous proof standards; the random oracle model usage should be carefully justified
- May need to expand the composition theorem and space bound proofs with more detail

**Assessment**: Strong venue if the paper is positioned as an information-theoretic contribution with cryptographic applications. The space-accuracy duality and composition results are genuine IT contributions. The long review time is the main drawback. Best for maximizing prestige.

---

### 3. CANS 2026 (Cryptology and Network Security)

**Scope fit**: GOOD. CANS covers cryptology and network security broadly, including new cryptographic constructions and models. The cipher map abstraction and its three constructions are in scope.

**Format fit**: GOOD. 20 pages in Springer LNCS format. The paper at ~22 single-column pages translates to roughly 18-20 LNCS pages, which fits within the limit or is very close.

**Impact/prestige**: MODERATE. CANS is a well-established cryptography conference (25th edition in 2026), published in Springer LNCS. Not top-tier (not Crypto/Eurocrypt/CCS), but a respected specialist venue. Good for establishing a new concept.

**Acceptance rate**: Estimated ~30-40%. More accessible than top-tier venues.

**Review timeline**: Standard conference cycle. Submission June 10, 2026; notification August 10, 2026. Conference November 23-25, 2026 in Wollongong, Australia.

**Upcoming deadlines**: **June 10, 2026** (submission deadline). This is approximately 10 weeks away.

**Changes needed**:
- Reformat to Springer LNCS template
- Ensure the paper fits within 20 LNCS pages (likely achievable with minor condensation)
- The lack of a formal security game is more of a concern here than at PoPETs; reviewers may expect game-based definitions or at least a comparison to standard security notions

**Assessment**: Good fallback option with a near-term deadline. Lower prestige than PoPETs or T-IT, but more likely to accept a paper that defines a new model without game-based security. The June 10 deadline is tight but achievable if the paper is close to ready.

---

### 4. Designs, Codes and Cryptography (Springer journal)

**Scope fit**: MODERATE-GOOD. The journal bridges design theory, coding theory, and cryptography with emphasis on algebraic and geometric aspects. The hash constructions, space bounds, and algebraic structure of cipher maps (composition, Boolean algebra) fit the coding/cryptography intersection. The privacy model is less central to the journal's scope.

**Format fit**: EXCELLENT. Journal format with no strict page limit. The paper can be submitted as-is with minimal reformatting.

**Impact/prestige**: MODERATE. IF ~1.2-1.6, SJR Q1, h-index 72. A solid specialist journal, well-regarded in the coding theory and cryptography communities.

**Acceptance rate**: Not publicly available, but the journal is selective.

**Review timeline**: Typically 3-6 months. Online publication within 3-5 weeks of acceptance.

**Upcoming deadlines**: Rolling submissions (journal). No deadline pressure.

**Changes needed**:
- Minor reformatting to Springer journal style
- Emphasize the algebraic/combinatorial aspects (perfect hash functions, space bounds, Boolean algebra construction) over the privacy model
- The journal's reviewers would be experts in coding theory and hash functions, so the hash construction analysis should be rigorous and detailed

**Assessment**: Good journal option if the paper is positioned as a coding/cryptography contribution. The algebraic structure of cipher maps and the space lower bound are the most relevant results for this venue. Less ideal for the privacy model contribution.

---

### 5. ACM CCS 2026 (Computer and Communications Security)

**Scope fit**: MODERATE. CCS is a top-4 security conference covering all aspects of security. The paper's new privacy model is in scope, but CCS strongly favors papers with formal security proofs (game-based or simulation-based) or empirical evaluations. A purely theoretical paper defining a new model without a standard security game faces an uphill battle.

**Format fit**: TIGHT. 12 pages double-column in ACM sigconf format, excluding bibliography and appendices. The paper would need significant compression -- the 22 single-column pages translate to roughly 16-18 ACM double-column pages, requiring 4-6 pages of cuts.

**Impact/prestige**: VERY HIGH. Top-4 security conference. Publication here would give the cipher maps concept maximum visibility.

**Acceptance rate**: ~14-17% (declining trend: 22.4% in 2022, 13.9% in 2025). Extremely competitive.

**Review timeline**: Two cycles. Cycle B deadline: abstract April 22, paper April 29, 2026. Notification typically August-September.

**Upcoming deadlines**: **April 22, 2026 (abstract) / April 29, 2026 (paper)** for Cycle B. This is approximately 4 weeks away.

**Changes needed**:
- Massive compression to fit 12 double-column pages
- Add a formal security argument (at minimum, a reduction or game-based characterization of what the adversary cannot learn)
- Add concrete performance analysis or comparison to existing approaches (even theoretical)
- The "what this is not" framing needs to be replaced with a positive security claim that CCS reviewers can evaluate

**Assessment**: Reach venue. The paper's novelty is high but its format (no security game, no empirical evaluation) is a poor match for CCS reviewing norms. The April 29 deadline is also very tight. Would recommend CCS only after the paper has been published elsewhere and the formalism is established, or if a security game can be added.

---

### 6. Journal of Cryptology (Springer / IACR)

**Scope fit**: MODERATE. The flagship journal of the IACR. Publishes the highest-quality cryptography research. The cipher map concept is cryptographic, but the journal strongly expects computational-complexity-based security definitions (PPT adversaries, negligible advantages). The paper's information-theoretic parameters are a different paradigm.

**Format fit**: GOOD. No strict page limit. LaTeX, PDF submission.

**Impact/prestige**: HIGHEST in cryptography. IF ~2.2-2.5, h-index 85. The gold standard for cryptographic research.

**Acceptance rate**: Very low (estimated <15%). Extremely selective.

**Review timeline**: Long -- typically 6-18 months. Reviews are thorough.

**Upcoming deadlines**: Rolling submissions (journal).

**Changes needed**:
- The paper would need a substantial security analysis, likely relating the information-theoretic parameters to computational security notions
- The Bayesian deniability proposition would need to be developed into a full security theorem
- Reviewers will be top cryptographers who expect standard definitions; the paper's explicit rejection of game-based and simulation-based frameworks is a significant mismatch

**Assessment**: Aspirational but likely premature. The cipher maps formalism would need to mature -- with formal security definitions that cryptographers recognize -- before Journal of Cryptology would be receptive. Best revisited after a conference publication establishes the concept.

---

### 7. Asiacrypt 2026 (IACR)

**Scope fit**: MODERATE. One of the three flagship IACR conferences. Covers all areas of cryptology. More theory-friendly than CCS but still expects standard cryptographic formalisms.

**Format fit**: GOOD. Springer LNCS format, typically 30-page limit including references.

**Impact/prestige**: HIGH. One of the top three cryptography conferences (with Crypto and Eurocrypt).

**Acceptance rate**: ~25-30% historically.

**Review timeline**: Submission May 22, 2026; rebuttal July 17-22; notification August 14. Conference December 8-12, 2026 in Melbourne, Australia.

**Upcoming deadlines**: **May 22, 2026**. Approximately 8 weeks away.

**Changes needed**:
- Reformat to LNCS
- The same issue as Journal of Cryptology: reviewers expect standard cryptographic definitions
- The paper would benefit from a formal adversary model, even if the security guarantee is information-theoretic rather than computational
- The random oracle model usage should be explicitly connected to standard ROM results

**Assessment**: Better than CCS for a theoretical paper, but the lack of standard cryptographic security definitions is still a significant barrier. The May 22 deadline gives slightly more time than CCS Cycle B. Consider if the paper can be augmented with a formal adversary model.

---

## Summary Table

| Rank | Venue | Type | Scope Fit | Format Fit | Prestige | Accept Rate | Next Deadline | Changes Needed |
|------|-------|------|-----------|------------|----------|-------------|---------------|----------------|
| 1 | **PoPETs 2027** | Hybrid J/C | Strong | Good (13pp) | High | ~22-26% | ~2026-05-31 | Reformat, compress, strengthen privacy framing |
| 2 | **IEEE T-IT** | Journal | Good | Good (50pp) | Very High | ~20-25% | Rolling | Reformat, strengthen IT framing |
| 3 | **CANS 2026** | Conference | Good | Good (20pp LNCS) | Moderate | ~30-40% | 2026-06-10 | Reformat to LNCS, minor compression |
| 4 | **Des. Codes Crypt.** | Journal | Mod-Good | Excellent | Moderate | Selective | Rolling | Minor reformat, emphasize algebraic aspects |
| 5 | **ACM CCS 2026** | Conference | Moderate | Tight (12pp) | Very High | ~14% | 2026-04-29 | Major: compress, add security game |
| 6 | **J. Cryptology** | Journal | Moderate | Good | Highest | <15% | Rolling | Major: add standard crypto definitions |
| 7 | **Asiacrypt 2026** | Conference | Moderate | Good (LNCS) | High | ~25-30% | 2026-05-22 | Add formal adversary model |

## Recommendation

**Primary target: PoPETs 2027 Issue 1 (deadline ~May 31, 2026)**

Rationale:
1. Best scope alignment -- PoPETs exists to evaluate new privacy models, which is exactly what this paper contributes.
2. The rolling deadline with resubmission option reduces risk -- if the paper receives a "major revision" or "reject with encouragement to resubmit," it can be revised for the next issue without starting over.
3. The 13-page format forces healthy compression that will strengthen the paper.
4. PoPETs does not require game-based or simulation-based security definitions, making the information-theoretic approach acceptable.
5. The privacy community is the natural audience for a paper arguing that "privacy through totality" is a distinct paradigm.

**Backup: CANS 2026 (deadline June 10, 2026)**

Rationale: CANS is a natural home for a new cryptographic construction paper. The 20-page LNCS format accommodates the paper with minimal cuts. The acceptance rate is more forgiving. The June 10 deadline is close to PoPETs 2027 Issue 1, so both could be prepared in parallel (submit to PoPETs first, CANS as fallback if PoPETs is rejected before June 10).

**Long-term: IEEE T-IT (rolling)**

If the paper is rejected from PoPETs and CANS, or if the author wants to pursue maximum prestige, IEEE T-IT is the best journal option. The paper should be repositioned to emphasize the space-accuracy duality and composition theorem as information-theoretic contributions. This would be a 6-12 month process.

## Timeline

| Date | Action |
|------|--------|
| Now - April 15 | Address remaining 12 minor issues from review-2026-03-26 |
| April 15 - May 15 | Reformat to PoPETs template, compress to 13 pages, strengthen privacy framing |
| May 15 - May 28 | Final polish, co-author review |
| ~May 31 | Submit to PoPETs 2027 Issue 1 |
| ~July 31 | PoPETs decision expected |
| June 10 (if needed) | CANS 2026 backup submission |
