# Novelty Assessor Report (round 3, 2026-04-29)

## Scope

Assess whether the contribution-list reorder (Thm 5.1 promoted to
contribution #1, Fannes bridge demoted to #2) and the explicit
two-scale framing in §1 strengthen or weaken the paper's reviewer-
defensible novelty story. Re-evaluate carry-over concerns M10 (Fannes
bridge as headline) and M11 (Thm 5.1 plug-in rate as standard) under
the new ordering.

## The reorder, evaluated

### Pre-rev2 framing (was)

- Contribution 1: Fannes bridge (delta-to-e translation)
- Contribution 2: Two constructions reducing delta
- Contribution 3: Compositional leakage theorem (Prop, then
  promoted to Thm in rev2)
- Contribution 4: Practical measurement

### Today's framing (is)

- Contribution 1: **Compositional leakage theorem** (Thm 5.1)
- Contribution 2: Fannes bridge
- Contribution 3: Two constructions
- Contribution 4: Practical measurement and validation

The reorder reflects rev2's recommendation (Suggestion 2). It
addresses the area-chair-flagged concern that the headline was
"weaker" than the strongest mathematical content the paper contains.

### Why this is reviewer-defensible

1. **Thm 5.1 carries quantitative content** that the Fannes bridge
   does not: parts (2) MI preservation, (3) parametric rate, (4)
   joint TV bound on optimal `delta_3`. After rev2's polish, parts
   (2) and (4) are not tautologies.
2. **Thm 5.1 is structurally distinctive**: the "shared-c implies
   joint recovery" claim does not appear (verbatim) in QIF or SSE
   literature. The closest results are SSE joint-leakage attacks
   (Cash, Kellaris, Oya-Kerschbaum), which exploit query-pattern
   correlations across distinct queries. Thm 5.1 exploits
   cipher-map composability, a structural rather than statistical
   channel.
3. **The Fannes bridge is a textbook application** of Fannes-
   Audenaert; its novelty is the *framing* (delta as the operational
   handle) rather than the *theorem* (which is a plug-in inequality).

### Why a skeptical reviewer might still push back

A reviewer reading "compositional leakage theorem" as the headline
might object:
- "The rate `O(|Y_1||Y_2|/xi^2)` is the standard plug-in estimator
  rate (Cover-Thomas). What's new?"
- "MI preservation is data-processing equality under a deterministic
  push, which is also standard."

The paper's defense (already partially present in §5 and §2) is:
- The novelty is the *application*. Cipher-map systems are designed
  to hide information at the marginal level. Showing that they leak
  the joint at standard rate, despite marginal uniformity, is a
  conceptual surprise even if the rate itself is standard.
- The "shared-c" hypothesis is what makes the result distinctive.
  Without shared-c, you have two independent estimation problems and
  no joint recovery. The composability of cipher maps is what makes
  shared-c the natural observation model.

**Verdict on the reorder**: The new ordering reads as confident
rather than defensive. The contribution text now explicitly says
"main result" and frames the Fannes bridge as supporting (necessary
but not sufficient). This is the correct rhetorical position for
the paper's actual content.

## M10 status (Fannes bridge as headline contribution)

**Resolved by reorder.** With Thm 5.1 promoted to contribution #1, the
Fannes bridge is no longer claimed as the headline. The contribution
text at line 185-190 frames the Fannes bridge as "making delta the
operational handle for confidentiality engineering", a framing role
rather than a theorem role. This matches the actual mathematical
content (Fannes-Audenaert is a textbook continuity inequality; the
contribution is the application to cipher-map systems).

The bridge is honestly framed as a translation tool, not as new
mathematics. M10 is closed.

## M11 status (Thm 5.1 plug-in rate as standard)

**Partially mitigated by reorder.** The rate itself is still
standard plug-in estimation. The reorder strengthens the framing.
The result is now sold not on the rate but on:

- The shared-c hypothesis (composability-induced).
- MI preservation (Part 2).
- The TV lower bound on optimal `delta_3` (Part 4).

A skeptical reviewer who fixates on Part 3 alone could still argue
"this is plug-in estimation." The matching lower bound (Le Cam /
Fano) suggested in rev2 is still not added. M11 remains a weak
point of the contribution claim.

**Recommendation from novelty-assessor**: Add a short remark or
footnote in §5.1 noting that the rate is information-theoretically
optimal (Le Cam / Fano matching lower bound), or position the
quantitative content as Part (2) MI preservation (the most
distinctive non-rate piece) rather than Part (3).

## Two-scale framing as a novelty contribution

The two-scale framing is *new this round* and was not previously
reviewed. Three angles:

### 1. Is it a genuine structural insight?

The decomposition into "marginal scale" (single cipher map; delta
controls leakage) and "compositional scale" (multiple cipher maps;
shared-c enables joint recovery regardless of delta) reflects two
genuinely different attack surfaces.

A confidentiality engineer who solves only the marginal problem
(small delta) does not get compositional confidentiality for free.
This is non-obvious and is the paper's core practical insight.

The framing is not just rebranding the existing content; it gives
the reader a conceptual handle for understanding why two of the
paper's three constructions (noise injection, multiple
representations) target one scale, while the third (granularity)
spans both.

### 2. Does it overclaim?

No. The framing is honest in three ways:
- It names the marginal scale as the "starting point" with the
  Fannes bridge.
- It names the compositional scale as the "main result" with Thm
  5.1.
- It explicitly says "engineering at one scale does not engineer at
  the other."

The framing does not claim the paper *solves* the compositional
scale. It shows the leakage is intrinsic and lists three possible
mitigations (noise, granularity, observation-count limits).

### 3. Connection between scales

The prompt asks: "the Fannes bridge is a marginal-scale tool but Thm
5.1's premise (each cipher map has `delta_i ~ 0`) explicitly uses
the marginal scale to define the compositional setting. So the scales
do *connect*."

This is a real subtlety. Thm 5.1 assumes `delta_i ~ 0` (marginal
uniformity) as input. So the marginal-scale tools (noise,
multiplicity) are *prerequisites* for the compositional-scale claim
to be interesting.

The paper handles this acceptably:
- §1 line 102-105: "The two scales do not reduce to each other:
  engineering at one does not engineer at the other."
- The "do not reduce" is the right precision: solving one does not
  solve the other.

A reviewer could ask: "Does Thm 5.1 still apply when delta_i is
non-trivial?" The answer is yes (the proof goes through for any
delta_i; the marginal uniformity hypothesis is for cleanness, not
necessity), but the paper does not state this. A one-sentence remark
clarifying that Thm 5.1 holds without marginal uniformity (it merely
becomes "even when each cipher map is marginally protected") would
sharpen the framing.

This is a Suggestion-level item.

## Findings (this round)

### New this round

#### Suggestion: Strengthen the "scales connect" precision

- **Location**: §1, lines 95-105 (the "two scales" paragraph) and §5
  opener (lines 743-755).
- **Quoted text (§1)**: "The two scales do not reduce to each
  other: engineering at one does not engineer at the other."
- **Observation**: The two scales are linked by the marginal-
  uniformity hypothesis of Thm 5.1. Stating that Thm 5.1 holds for
  any `delta_i` (with the bound becoming weaker but still
  parametric) would sharpen the framing.
- **Suggestion**: Add a footnote or sentence after Thm 5.1: "The
  marginal-uniformity hypothesis is for cleanness; the rate
  argument in part (3) holds for any `delta_i` with a constant that
  depends on the marginal-uniformity gap."
- **Severity**: Suggestion. Not blocking.

### Resolved this round

- **M10 (carry-over)**: Resolved by the reorder. The Fannes bridge
  is no longer claimed as headline.

### Carry-over open

- **M11 (carry-over)**: Partially mitigated by reorder; the rate
  itself is still plug-in. Adding a Le Cam / Fano lower bound would
  upgrade the result from "rate" to "impossibility." Still open.

## Summary

The contribution-list reorder is reviewer-defensible and reads as
confident rather than defensive. The two-scale framing is a genuine
structural insight, not repackaging. Mathematical novelty content
is unchanged (Thm 5.1 is unchanged); the rhetorical framing is
sharper. M10 closed; M11 still open at the same severity.

**Recommendation from novelty-assessor**: minor-revision (the M11
plug-in rate concern has not been mathematically resolved, but the
framing change makes the contribution story stronger and more
defensible). The remaining novelty work (matching lower bound for
the rate) is a "sharpening pass" for a future round.
