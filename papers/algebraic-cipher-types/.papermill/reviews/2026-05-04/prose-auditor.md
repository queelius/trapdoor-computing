# Prose Auditor Report

**Date**: 2026-05-04 (cross-paper-informed)
**Reviewer role**: Writing quality, narrative arc, notation consistency.
**This round**: focus on the NEW algebraic material (§4 lead-in, §4.4 props, §4.5 + Table 1) for seams, and re-confirm prior prose residuals.

## Narrative arc of the restored algebraic frame -- clean, no major seams

The 2026-05-04 reframing reads coherently. The §4 lead-in (308-339) sets up "cipher types form an algebra + universal granularity knob + constructor-specific costs"; the per-constructor subsections deliver; §4.5 + Table 1 consolidate; the conclusion (1632-1675) restates in the same order. The abstract (41-66) leads with the algebra and states the entropy-form bound. I looked specifically for places where the older "sum-impossibility is the headline" framing pokes through and found **none that are contradictory**: sum is now consistently presented as the *categorically different* one of three, which is a coherent role, not a leftover headline. The "Sums are categorically different" paragraph (714-724) is the load-bearing reconciliation and it is well-written.

One soft seam (Minor): §4.5's "closure under the orbit framework" paragraph (726-735) and the §4 lead-in's last paragraph (332-339) both forward-reference §5 in similar language; mild redundancy, not a defect.

## Notation consistency
- C(.) functor notation, orbit_F, B^n all used consistently.
- The entropy-form bound H(X | V_F(c)) >= H(X) - log2|orbit_F(c)| is stated identically in abstract (52-56), intro contribution 2 (120-122), Thm 5.3 (854), and conclusion (1639-1641). Consistent. (The proof's internal V-as-set issue is a logic finding, not a notation inconsistency -- the *statement* is uniform.)
- Table numbering: §4.5 introduces **Table 1**, pushing the §7.3 experimental tables to **Tables 2/3/4**. The prose refers to them by `\Cref`, so this is automatically correct in the PDF; but state.md and older review prose call them "Table 1/2/3." Documentation-only drift (already noted 2026-05-23); no paper edit needed.

## Carry-over residuals (from 2026-05-23) -- re-confirmed still present

### MIN (carry-over). Conclusion "10^4" understates Table 2's 12,160.
- **Location**: conclusion, line 1666: "and by $10^4 \times$ at $k = 5$".
- Table 2 (line 1469) shows 12,160. 10^4 is a 1.2x underestimate. Flagged 2026-04-30 and 2026-05-23; fix has not landed. Replace with "over $10^4\times$" or "$\sim\!1.2\times10^4$". 5-second edit. Minor.

### MIN (carry-over). Overfull hbox at line 703.
- Build log: `Overfull \hbox (19.70331pt too wide) in paragraph at lines 703--713` (§4.5 "Universal granularity knob"). Visible in typeset output. Rephrase the opening sentence or insert a break. Minor. (Also in format-validator.)

### MIN (carry-over). "Starting tape configuration" vestige in §6.3.
- **Location**: §6.3 "What bounds the orbit" paragraph, line 1237: "...a single-trajectory bound of $T+1$ orbit elements per starting tape configuration...".
- "tape configuration" is jargon from the removed cipher-TM section (dropped 2026-05-02). With only the expression-tree realization remaining, it reads as a leftover. Rephrase to "per starting cipher value" or "per starting state." Minor.

## New prose nits this round (Minor/Suggestion)
- §4.4 Prop 4.4 proof (608-618): reads as a definition unpacked under a Proof heading. Concur with novelty-assessor: either trim to one sentence or relabel. Presentation.
- §4 lead-in (315-325) "A common knob runs through the algebra" -- strong, keep. The phrase "irreducible information the untrusted machine learns" (312-313) is good and load-bearing for the algebra framing.
- Cross-paper prose hygiene: the Discussion "encoding granularity principle" paragraph (1569-1578) cites foundation "[Sec.~9]" and "[Sec.~9.3]" -- these are the wrong-number defects (see citation-verifier); from a prose standpoint, the sentence is fine, only the bracketed numbers are wrong.

## Strengths
- §7.3 FPR structural-explanation paragraph (1480-1496) is excellent: it turns a surprising empirical result into a crisp mechanistic story (deterministic cipher map composed with itself breaks Bernoulli independence; AND collapses to p_T^k which is easy to overshoot, OR is dominated by the larger term and stays near theory).
- Remarks rem:sum-vs-product (551-561) and the §4.5 observations are tight and quotable.

## Confidence
High. Prose is mature (six rounds). The new §4 material is well-integrated; residuals are all Minor and most are carry-overs that simply have not been applied yet.
