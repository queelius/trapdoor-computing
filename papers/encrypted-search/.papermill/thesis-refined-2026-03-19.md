# Thesis Refinement: Encrypted Search as Trapdoor Computing

**Date**: 2026-03-19
**Prior**: thesis-analysis.md, reviews/review-2026-03-19.md
**Question**: Is this a standalone paper, or a section of cipher-maps-unified?

---

## 1. Standalone Viability Assessment

**Verdict: Not viable as currently written. Marginally viable if a specific theorem is added.**

The paper as it stands is a vocabulary dictionary: five definitions mapping encrypted search terms to cipher map terms. The cipher-maps-unified paper already has a Section 7.2 ("Encrypted Search Systems") and Section 7.3 ("Privacy-Preserving Search") that cover the same ground in bullet-point form. The encrypted-search paper adds more careful definitions, but the contribution is still definitional -- it establishes a correspondence without proving anything new follows from it.

A reframing paper can be a legitimate contribution, but only if the reframing **produces something the original framing could not**. Vocabulary mappings alone do not clear this bar. Reviewers will ask: "What does calling a secure index a cipher map buy me that I didn't already have?"

### What would make it standalone-viable

The paper needs at least one of these:

**Option A: A universality theorem.** Prove that every encrypted search scheme satisfying standard security definitions (IND-CKA1/CKA2, or the leakage-function framework of Curtmola et al.) is a cipher map satisfying the four properties, and conversely, that every cipher map with appropriate parameter choices yields an IND-CKA-secure encrypted search scheme. This would establish an equivalence, not just a vocabulary mapping. The forward direction (SSE => cipher map) is likely provable: totality is immediate from any stateful encryption scheme, correctness is standard, the other two properties need careful treatment. The reverse direction is harder and more interesting.

**Option B: Tighter bounds from the formalism.** Take a specific encrypted search construction (e.g., Curtmola's SSE-2 or Cash et al.'s OXT) and derive its eta, epsilon, mu, delta parameters. Then show that the composition theorem (eta_total = 1 - prod(1-eta_i)) gives tighter or more informative error bounds for Boolean query composition than the ad hoc analyses in those papers. If the cipher map framework yields a result the SSE literature does not already have, that is a paper.

**Option C: The plausible deniability angle.** The observation that nonzero eta provides plausible deniability is noted in the paper (line 107) and in the formalism (Section 1.3, Property 3 remark). This is genuine and appears to be novel. If this can be formalized -- showing that a cipher map with eta > 0 satisfies a formal deniability definition (e.g., the ESP cannot distinguish a true positive from a false positive with advantage better than some function of eta) -- that is a theorem worth a paper. This would connect cipher map correctness to a notion of result privacy that is distinct from query privacy.

**Option D: A comparison table with derived parameters.** Map 3-4 existing encrypted search constructions to cipher map parameters, with actual derivations (not just labels). Show where each construction sits in the (eta, epsilon, mu, delta) space. If the mapping reveals a gap -- e.g., no existing construction achieves small delta with small eta simultaneously -- that is a finding.

Without at least one of A-D, the paper should be absorbed.

---

## 2. Absorption into cipher-maps-unified

The cipher-maps-unified paper already has:
- Section 7.2: "Encrypted Search Systems" (3 bullet points)
- Section 7.3: "Privacy-Preserving Search" (Example 7.1: 4-item list)

These sections are thin -- just bullet points with no definitions or analysis. The encrypted-search paper's vocabulary mapping (Definitions 2.1-2.5) is more careful and more complete. The natural move is:

**Replace Sections 7.2 and 7.3 of cipher-maps-unified with a single expanded subsection** incorporating:
- The five definitions from encrypted-search
- The four-property specialization
- The Bloom filter remark
- A worked example (keyword search as cipher map with derived parameters)

This would strengthen cipher-maps-unified's applications section and avoid publishing a paper whose sole contribution is a vocabulary mapping.

**Cost of absorption**: The encrypted-search paper's framing that encrypted search is "one application among many" gets lost slightly, because cipher-maps-unified already makes this point. But the precise vocabulary mapping adds concrete value to the applications section.

---

## 3. What Makes the Reframing Non-Trivial

The reframing is currently trivial because it is bijective: each encrypted search concept maps to exactly one cipher map concept, and the mapping is obvious once you see both definitions side by side. Non-triviality requires the mapping to **do work** -- to produce an insight, bound, or construction that is not apparent from the encrypted search side alone.

Candidate non-trivial consequences:

1. **Composition for free.** The SSE literature handles Boolean queries ad hoc (each scheme supports specific query types). The cipher map framework gives composition as a general property with the chain formula. If you can show that composing SSE-2 with an OR cipher map gives a multi-keyword search scheme with predictable error, and the SSE literature does not already have this result, the composition theorem is doing work.

2. **Representation uniformity as a new security metric.** The SSE security definitions (IND-CKA) are computational. The delta parameter is information-theoretic and measures a different thing: TV distance from uniform. If delta captures a leakage that IND-CKA does not (e.g., frequency analysis that is not modeled by the IND-CKA game), that is a genuine contribution.

3. **The plausible deniability theorem.** Formalizing the eta-deniability connection (see Option C above) would be new. The SSE literature does not discuss false positives as a privacy feature; it treats them as a cost.

4. **Space lower bounds.** The formalism's space bound (-log2(epsilon) + H(Y) bits/element) is information-theoretic. If this bound is tighter than known space bounds for specific SSE constructions, the reframing reveals inefficiency.

---

## 4. Sharpest Possible Thesis

### If standalone (requires Option A or C):

> **Thesis**: Every encrypted search scheme satisfying standard leakage-function security is an instance of a cipher map with quantifiable (eta, epsilon, mu, delta) parameters. The cipher map framework reveals structure invisible to the SSE security model: (1) the composition theorem gives predictable error bounds for Boolean queries without per-scheme analysis, (2) the representation uniformity parameter delta captures frequency leakage orthogonal to IND-CKA security, and (3) nonzero correctness error eta provides formal plausible deniability -- the untrusted provider cannot distinguish true positives from false positives.

This thesis has three prongs, each requiring a proof. It is ambitious for a short paper but defensible if the proofs are tight.

### If absorbed into cipher-maps-unified:

The encrypted search material becomes a worked example illustrating the four properties, with a comparison table mapping 2-3 existing SSE constructions to cipher map parameters. No independent thesis needed; it serves the unified paper's thesis.

---

## 5. Recommendation

**Short-term**: Absorb the vocabulary mapping into cipher-maps-unified (replacing the thin Sections 7.2-7.3). This is a net improvement to the unified paper at no cost.

**Medium-term**: If the plausible deniability theorem (Option C) can be formalized and proven, extract it back out as a standalone paper. The theorem statement would be:

> For a cipher map with correctness eta > 0, no PPT adversary holding only the cipher map f-hat can distinguish "dec(f-hat(enc(x,k))) = f(x)" from "dec(f-hat(enc(x,k))) != f(x)" with advantage greater than g(eta), where g is a concrete function of eta.

If this holds, the paper's contribution is not vocabulary but a theorem connecting approximation error to privacy, instantiated via encrypted search.

**Bottom line**: The paper as written is not paper-worthy. The vocabulary mapping is correct but trivial. Either add a theorem (plausible deniability is the best candidate) or absorb into cipher-maps-unified.
