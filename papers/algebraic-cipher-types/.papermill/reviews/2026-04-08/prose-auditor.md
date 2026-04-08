# Prose Auditor Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Auditor**: prose-auditor (opus)

## Strengths
- Exemplary introduction -- states problem, identifies gap, lists contributions, and explicitly positions against ORAM/FHE/garbled circuits
- Sum-type impossibility (Theorem 3.1) is the strongest result, cleanly presented
- Effective examples -- cipher optionals, Boolean orbit, successor orbit all illuminate the theory
- Respects the reader's time -- concise definitions, no over-elaborate proofs

## Critical Issues (2)
1. **Confidentiality Bound Theorem (Section 4.3)** presents four formulas in quick succession with different denominators (2^n, 2^n - |X|, |X|) -- reader can't identify "the result." Fix: state one clean formula as the theorem, move intermediates to the proof.
2. **Proposition 6.1 (Noise Absorption)** -- proof contradicts the claim. States AND(x, n) in N categorically, but proof shows this happens with only ~5% probability (output is False with <=90% probability). The proposition as stated is false per its own proof.

## Major Issues (5)
3. **C(X) notation never formally defined** -- central notation used everywhere but introduced only as a one-line sentence, not a definition
4. **"Functorial framework" in metadata but no functors in the paper** -- no category theory machinery, no functor definition, no natural transformations
5. **Discussion section overloaded** (~40% of paper body) -- contains new definitions, proofs, experimental results, and implementation details that should be separate sections
6. **Candidate set definition (Def 4.2) ignores the orbit** despite the F subscript
7. **Sum-type impossibility proof gap** -- assumes balanced prior (Pr[v in A] = 1/2) without stating it

## Minor Issues (8)
- Cipher TM pairing operation hand-waved
- K(x) notation used without definition
- delta_T overloaded (TV distance parameter vs. TM transition function)
- Table 1 lacks context (0.39 precision unexplained)
- Encoding granularity table missing 2/3 of space data
- "Cipher value" conflated with "cipher map for constant function"
- No Related Work section
- Occasional passive voice in proofs
