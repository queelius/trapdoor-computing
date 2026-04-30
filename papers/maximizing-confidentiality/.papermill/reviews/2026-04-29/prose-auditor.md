# Prose Auditor Report (round 3, 2026-04-29)

## Scope

Per the prompt's primary verification questions:

1. Does the §1 framing flow well after the inserted "Our central
   observation" paragraph?
2. Does the abstract (untouched) align with §1's new two-scale frame?
3. Does the §5 retitle to "The Compositional Scale" combined with
   the rewritten opener work, given §5.2 is about correctness?
4. Are §3 and §4 implicitly the "marginal scale" sections without
   renaming?
5. Are the new `\paragraph{Marginal scale.}` and `\paragraph{Compositional
   scale.}` environments clean given §1's existing paragraph
   environments?

## §1 flow analysis

The introduction now has the structure:

| Lines | Content |
|---|---|
| 78-93 | Setup: cipher map system, four properties, qualitative vs. quantitative |
| 95-105 | NEW: "Our central observation" paragraph naming the two-scale decomposition |
| 107-145 | `\paragraph{Marginal scale.}` (Fannes bridge + two constructions) |
| 147-165 | `\paragraph{Compositional scale.}` (Thm 5.1) |
| 167-170 | Practical measurement (one paragraph, no `\paragraph` heading) |
| 172-205 | `\paragraph{Contributions.}` (numbered list) |
| 207-212 | `\paragraph{What this paper does not do.}` |

### Does the inserted paragraph read as natural or grafted?

Reading the paragraph in sequence, it lands cleanly. The first
sentence ("Our central observation is that confidentiality in cipher
map systems decomposes into two scales") directly answers the
question raised in the prior paragraphs ("how confidential is the
system, and how can it be improved?"). The decomposition into
marginal and compositional scales is named and motivated, and the
final sentence ("This is the structural reason cipher-map
confidentiality cannot be addressed by a single number, and is the
spine of the paper.") sets up the reader for the two `\paragraph`
sections that follow.

The transition is smooth: the reader expects the two `\paragraph`
headings after the spine has been named.

### Cohesion of the marginal/compositional paragraphs

The `\paragraph{Marginal scale.}` paragraph (lines 107-145) does
three things:

1. Names the entropy ratio.
2. Concedes QIF lineage.
3. Introduces the Fannes bridge.
4. Lists the two constructions plus inherited third.

This is a lot for one `\paragraph`. The text was already this dense
before today (this is the existing Fannes-bridge paragraph). What
changed is the heading. The heading change is fine; the density
predates this round.

The `\paragraph{Compositional scale.}` paragraph (lines 147-165) does:

1. Names Thm 5.1.
2. States the rate.
3. Names the "intrinsic to composability" claim.
4. Lists three mitigations.
5. Mentions FPR compounding as inherited.

Also dense, also predates this round. The reorder makes the
compositional paragraph more prominent; previously it was paragraph
#3 (after measurement); now it is paragraph #2 (before measurement
and contributions list).

### Verdict on §1 flow

The flow is acceptable. The two-scale spine is named, motivated, and
delivered through two parallel `\paragraph` sections. A fastidious
reader might notice that "marginal" and "compositional" are now
named labels carrying weight, and might want to see those labels
echo more strongly in the section structure (e.g., §3 retitled to
"Marginal-Scale Confidentiality"). This is a Suggestion, not a
finding.

## Abstract alignment

The abstract (untouched) has the structure:

1. Setup (cipher map system).
2. Entropy ratio as the measure.
3. Fannes bridge: "the central translation."
4. Two constructions plus inherited third.
5. "The paper's main result is a compositional leakage theorem."
6. Experimental validation.

The abstract narratively builds *toward* Thm 5.1, naming it as "main
result" only at point 5. It does not lead with Thm 5.1. The §1
contributions list now leads with Thm 5.1 (contribution #1). This is
a structural mismatch.

### Is this a problem?

The user's note in the prompt says the abstract was deliberately left
untouched: "two-scale frame implicit in narrative arc." That choice
is defensible: the abstract narrates the paper rather than enumerating
contributions. Many strong papers have abstracts that build toward the
main result rather than leading with it.

However, a skeptical reader scanning the abstract first and then the
contributions list will notice:

- Abstract: Fannes bridge first (point 3), Thm 5.1 last (point 5).
- Contributions list: Thm 5.1 first (#1), Fannes bridge second (#2).

The mismatch is real but not necessarily a problem. The abstract is a
narrative; the contribution list is an enumeration. Different organs
serve different purposes.

### Suggestion

A reader is well-served by an abstract that signals the main result
early. One option without rewriting the abstract: shift the "main
result" sentence (point 5) earlier, after the "we develop a
quantitative confidentiality theory" sentence (point 1).

Sample reorder of the abstract (sketched, not prescribed):

> "We develop a quantitative confidentiality theory for cipher map
> systems. Our main result is a compositional leakage theorem: even
> when each cipher map is marginally delta-uniform, observing
> multiple evaluations on a shared cipher value lets the untrusted
> machine recover the latent joint distribution at the standard
> parametric rate `O(|Y_1||Y_2|/xi^2)`, so reducing delta is
> necessary but not sufficient. To make the marginal target
> operational, we connect... [Fannes bridge] ... and analyze two
> constructions ..."

This is a Suggestion. The current abstract is acceptable.

**Severity**: Suggestion. The mismatch is not a defect; it is a
choice with a small cost.

## §5 retitle and opener: alignment with §5.2

The §5 title change from "Compositional Confidentiality" (or "Three
Levers" earlier) to "The Compositional Scale" reflects today's
two-scale framing. §5 contains:

- §5.1: Correlation Leakage from Shared Variables (Thm 5.1)
- §5.2: Error Compounding in Boolean Chains (Prop 5.2)

The prompt asks: does §5.2 (which is about correctness, not leakage)
clash with the title "The Compositional Scale"?

### The §5 opener

Lines 743-755:
> "When cipher maps compose [...], confidentiality moves to a
> different scale than the marginal one [...]. The compositional
> scale has two effects. The primary effect is *correlation
> leakage*: marginal delta-uniformity does not prevent the
> adversary from recovering joint distributions [...]. The secondary
> effect, inherited from [...], is error compounding through
> Boolean chains."

This frames the section as having two sub-effects under the umbrella
"compositional scale." The first sub-effect (correlation leakage) is
about confidentiality. The second sub-effect (error compounding) is
about correctness. The opener calls them "two effects" of
composition; both are scale-related but along different dimensions.

### Does this work?

It is acceptable, but slightly loose. "Compositional scale" was
introduced in §1 as referring specifically to the *confidentiality*
spine of the paper. In §5, the term is used more broadly to
encompass correctness (FPR compounding), which is not a confidentiality
phenomenon.

A reader could find this jarring: the §1 framing names the
"compositional scale" as the confidentiality complement to the
"marginal scale," but §5 then includes correctness material under
the same umbrella.

### Two ways to resolve this

Option A (mechanical): Rename §5 to something more inclusive, e.g.,
"Compositional Behavior" or "Composition." This aligns the title
with the section's actual scope (both leakage and correctness).
Cost: loses the alignment with the §1 two-scale framing.

Option B (structural): Move §5.2 (FPR compounding) out of §5 and
into §3 or §4 (where it would sit with the constructions for
reducing delta). Cost: a larger restructure. Reward: §5 becomes
purely about compositional confidentiality.

Option C (light touch): Keep the current structure but adjust the
§5 opener to clarify that "compositional scale" in §5 refers to
behavior under composition, with confidentiality (§5.1) and
correctness (§5.2) as the two facets.

Option C is cheapest. The current opener says "two effects" already;
just adding a sentence like "Confidentiality at the compositional
scale (§5.1) and error compounding under composition (§5.2) are
distinct facets of the framework's compositional behavior" would
close the gap.

**Severity**: Major. The mismatch is real and a reviewer skimming
the section structure will notice. Suggested fix is light-touch
(one or two sentences).

## §3 and §4 as "marginal scale" without renaming

§3 is "The Confidentiality Measure" (defines entropy ratio and Fannes
bridge). §4 is "Constructions for Reducing delta" (noise, multiplicity,
granularity).

After §1's two-scale naming, the reader expects §3 and §4 to be the
"marginal scale" half of the paper. Neither section title says
"marginal," however.

### Is this clear from §1 alone?

The §1 framing explicitly says (lines 107, 147):

- `\paragraph{Marginal scale.}` ... "[Fannes bridge] ... we analyze
  two constructions [noise, multiplicity] plus a third [granularity]."
- `\paragraph{Compositional scale.}` ... "[Thm 5.1, FPR compounding]"

So §1 telegraphs that §3 and §4 are the marginal scale, and §5 is
the compositional scale. A reader who reads §1 in order and then
encounters §3 and §4 will have the framing in mind.

A reader who skips §1 and dives into §3 will not see the "marginal
scale" label. §3 just opens with "Observed and Maximum Entropy"
under "The Confidentiality Measure." This is a small clarity loss.

### Suggestion

Either:
- Rename §3 to "The Marginal-Scale Confidentiality Measure" and §4
  to "Marginal-Scale Constructions for Reducing delta" (heavy).
- Add a one-sentence opening to §3 that says "Sections~3 and~4
  develop the marginal-scale theory [...]; Section~5 develops the
  compositional-scale theory" (light).

Severity: Minor. The framing is clear from §1 alone; the loss for a
section-skipping reader is small.

## `\paragraph` environment density

§1 now has six `\paragraph` environments:

1. `\paragraph{Marginal scale.}` (line 107)
2. `\paragraph{Compositional scale.}` (line 147)
3. `\paragraph{Contributions.}` (line 172)
4. `\paragraph{What this paper does not do.}` (line 207)

Plus a non-headed paragraph at line 167 ("Finally, we provide
practical measurement tools..."). This last one breaks the rhythm.

### Verdict

The four headed `\paragraph` environments are clean. The unheaded
"Finally, we provide..." paragraph at line 167 looks like it should
be its own `\paragraph{Practical measurement.}` for symmetry. This
is a small polish item.

**Severity**: Minor.

## Findings (this round)

### New this round

#### Major: §5 title vs. §5.2 scope mismatch

- **Location**: §5 title (line 739), §5 opener (lines 743-755),
  §5.2 (line 861).
- **Quoted text**: §5 is titled "The Compositional Scale"; §5.2 is
  titled "Error Compounding in Boolean Chains."
- **Problem**: The §1 framing reserves "compositional scale" for
  the confidentiality complement to the marginal scale. §5.2 is
  about correctness (FPR compounding), not confidentiality. A
  reader expects §5 to be confidentiality-only under the new
  title.
- **Suggestion**: Light-touch fix. Add one sentence to the §5 opener
  clarifying that "compositional scale" here covers two facets:
  confidentiality (§5.1) and correctness (§5.2). Or rename §5 to
  "Composition" or "Compositional Behavior."
- **Severity**: Major (visible in TOC; affects reader's mental
  model). The fix is mechanical.

#### Minor: Abstract / contribution-list ordering mismatch

- **Location**: Abstract (lines 47-70); contribution list (lines
  172-205).
- **Quoted text**: Abstract narrates Fannes bridge first, Thm 5.1 as
  "main result" at point 5. Contribution list leads with Thm 5.1.
- **Problem**: A reader scanning abstract then contributions will
  see different orderings. Defensible (abstract is narrative;
  contributions are enumeration), but a small mismatch.
- **Suggestion**: Optionally reorder the abstract to lead with Thm
  5.1, or accept the narrative arc as-is. User explicitly chose to
  leave it as-is.
- **Severity**: Minor. Per user's choice, not a finding to act on.

#### Minor: §1 paragraph structure asymmetry

- **Location**: §1 line 167 (unheaded "Finally, we provide
  practical measurement tools...").
- **Problem**: Surrounding paragraphs have `\paragraph` headings.
  This one does not.
- **Suggestion**: Add `\paragraph{Practical measurement.}` for
  symmetry.
- **Severity**: Minor (cosmetic).

#### Minor: §3, §4 implicit marginal-scale labeling

- **Location**: §3 title (line 356); §4 title (line 509).
- **Problem**: Neither section title carries the "marginal scale"
  label. A reader skipping §1 has no scale-context.
- **Suggestion**: Add a one-sentence opener to §3 noting that §3
  and §4 are the marginal-scale half of the paper.
- **Severity**: Minor.

### Resolved across rounds

- **M8 (morning)**: Fully resolved. All "three levers" stragglers
  cleared.
- **M12 (rev2)**: Resolved. §9 has a substantive Shannon vs.
  min-entropy paragraph (lines 1205-1225).
- **n1, n2 (rev2)**: Both resolved (§5 title and §7.4 opener
  cleaned).
- **n3 (rev2)**: Resolved (the §9 paragraph fulfills the §2 forward
  reference).

### Carry-over open

- **m1 (Q-notation)**: Open.
- **m2 (§5 opening hook)**: Partially addressed by today's rewrite;
  opener now leads with "two effects" (which is internal to §5).
  Could still lead with "marginal delta is necessary but not
  sufficient." Open as a polish item.
- **m3 (§5.1 ordering)**: Open.
- **m4 (Prelim IT redefinition)**: Open. (The Information-theoretic
  notation paragraph at line 337 is still verbose.)
- **m5 (§5.2 active probing informal)**: Open.
- **m7 (Limitations 5th tightness bullet)**: Open.
- **m8 (Threat model implicit)**: Open.

## Summary

The §1 two-scale framing flows cleanly; the inserted "Our central
observation" paragraph reads as natural rather than grafted. The
contribution-list reorder is consistent with the framing. The §5
retitle introduces one substantive issue: the title "The
Compositional Scale" sets up an expectation that §5 is confidentiality-
only, but §5.2 is correctness. Light-touch fix needed.

The abstract is now slightly out of order with the contribution
list, but per user's stated choice, this is a deliberate narrative
decision rather than a defect.

**Recommendation from prose-auditor**: minor-revision. The §5
title/scope mismatch is the only Major item; remaining items are
Minor or carry-over.
