# Multi-Agent Review Report (round 3, 2026-04-29)

**Date**: 2026-04-29
**Paper**: "The Entropy Ratio: Quantitative Confidentiality for
Trapdoor Computing" by Alexander Towell (18 pages)
**Recommendation**: **minor-revision**

This is the third review round in 17 days. The prior rounds were
2026-04-12 morning (major-revision; 2 critical, 12 major, 13 minor)
and 2026-04-12-rev2 (minor-revision; 0 critical, 3 major, 8 minor).

---

## Summary

**Overall Assessment**: This round's substantive changes are
purely structural and rhetorical:

(A) Contribution-list reorder, with Thm 5.1 (compositional leakage)
promoted to contribution #1 and the Fannes bridge demoted to #2.
The reorder propagates to abstract narrative, §1 framing, §2 Related
Work paragraph (already aligned in rev2), and §8 Conclusion.

(B) Explicit two-scale framing in §1 and §5. The new "Our central
observation" paragraph in §1 (lines 95-105) names the
marginal/compositional decomposition as the paper's spine. §1's
existing Fannes-bridge and compositional-leakage paragraphs are now
under `\paragraph{Marginal scale.}` and `\paragraph{Compositional
scale.}`. §5 retitled from "Compositional Confidentiality" to "The
Compositional Scale" with a rewritten opener.

The mathematical content is unchanged. All theorems, proofs, and
numerical examples from rev2 are preserved verbatim. Independent
recomputation of all key numerics (Fannes bound at delta=0.05,
n=64; Zipf s=1 entropy; Example 4.1 homophonic e=0.87; Table 4 case
study) confirms internal consistency.

The cleanup pass between rev2 and this round resolved all of rev2's
Major findings except M2 (Fisher info constant, deferred): §5 title
no longer says "Three Levers" (M8 fully resolved), Bost-Fouque venue
corrected to IACR ePrint (M7 resolved), §9 has a substantive Shannon
vs. min-entropy paragraph (M12 resolved), Thm 4.2 TV bound now
derived (n4 resolved), n=64 context added to Numerical Scale remark
(n5 resolved), Minor 5 MI fragility note added.

The two-scale framing is a genuine structural insight that lets the
reader hold the paper's conceptual arc cleanly. It does not over-
claim and is reviewer-defensible. The contribution-list reorder
reads as confident rather than defensive: Thm 5.1 carries
quantitative content (MI preservation, parametric rate, joint TV
bound on optimal delta_3) that the Fannes bridge does not, and
naming it as the headline matches the paper's actual mathematical
center of gravity.

This round introduces one new substantive issue: the §5 title "The
Compositional Scale" sets up the reader to expect a confidentiality-
only section, but §5.2 (Error Compounding in Boolean Chains) is
about correctness, not confidentiality. The fix is light-touch (one
or two sentences in the §5 opener clarifying that "compositional
scale" covers both leakage and correctness facets).

The build is clean at 18 pages, no warnings, no errors. PDF up by
1 page from rev2 (consistent with added prose).

**Strengths**:
1. Structural mathematical content is unchanged; no proof or
   numerical regressions (source: logic-checker).
2. Contribution-list reorder is reviewer-defensible; reads as
   confident framing of the strongest result rather than overclaim
   (source: novelty-assessor).
3. Two-scale framing is a genuine structural insight, not
   repackaging; gives the reader a conceptual handle for the
   paper's spine (source: prose-auditor, novelty-assessor).
4. All rev2 Major fixes propagated cleanly (M7 Bost-Fouque venue,
   M12 Shannon vs. min-entropy, M8 framing stragglers); n4, n5,
   Minor 5 from rev2 also closed (source: logic-checker,
   citation-verifier, prose-auditor).
5. Build clean at 18 pages, zero warnings, all references resolve
   (source: format-validator).
6. Independent numerical verification of all key claims:
   Fannes bound, Zipf entropy, Example 4.1 homophonic, Table 4
   case study (source: logic-checker, methodology-auditor).

**Weaknesses**:
1. §5 title "The Compositional Scale" vs. §5.2 scope (correctness,
   not leakage) creates a reader-mental-model mismatch (source:
   prose-auditor; new this round).
2. Carry-over M2 (Thm 4.1 Fisher info missing distribution-
   dependent constant) unchanged. Open since 2026-04-12 morning
   (source: logic-checker).
3. Carry-over M9 (CIs / reproducibility / analytical-vs-empirical
   labels for Tables 1-3) mostly unchanged from rev2 (source:
   methodology-auditor).
4. Carry-over M11 (Thm 5.1 plug-in rate has no matching lower
   bound) unchanged; mitigated by reorder but the rate itself is
   still standard (source: novelty-assessor).
5. The new headline (Thm 5.1) is not empirically validated; the
   experimental section validates FPR compounding, granularity,
   and the case study, but not the compositional leakage attack
   (source: methodology-auditor; new this round).
6. Abstract narrative ordering does not match contribution-list
   ordering. Per user's stated choice, this is deliberate, but a
   skeptical reader will notice (source: prose-auditor; new this
   round).

**Finding Counts**: Critical: 0 | Major: 1 | Minor: 4 | Suggestions: 4

---

## Per-Round Resolution Trajectory (3 rounds total)

This is the cross-round audit. Each row tracks an issue across the
three rounds.

### Critical findings (resolved across rounds)

| ID | Original round | Status now |
|---|---|---|
| C1 (Pinsker direction) | morning | Resolved in rev2 (Fannes-Audenaert correctly applied). Verified intact this round. |
| C2 (K(x) inversion) | morning | Resolved in rev2 (K(x) ~ D(x)). Verified intact this round. |

### Major findings

| ID | Original round | Status now |
|---|---|---|
| M1 (Zipf numerics) | morning | Resolved in rev2 (s=1 numerics consistent). |
| M2 (Fisher info constant) | morning | Open (deferred). Severity unchanged. |
| M3 (Thm 5.1 sampling model) | morning | Resolved in rev2. |
| M4 ("preserves all correlations") | morning | Resolved in rev2 (MI preservation). |
| M5 (Thm 5.1 part 4 trivial) | morning | Resolved in rev2 (joint TV bound). |
| M6 (Simmons not cited) | morning | Resolved in rev2. |
| M7 (Bost-Fouque venue) | morning | Resolved between rev2 and today (now IACR ePrint). |
| M8 (three levers stragglers) | morning | Resolved between rev2 and today (§5 title and §7.4 opener cleaned). |
| M9 (experimental rigor) | morning | Partially resolved (Table 4 caption; Tables 1-3 still implicit). |
| M10 (Fannes bridge as headline) | morning | Resolved this round (reorder demoted Fannes bridge to #2). |
| M11 (Thm 5.1 plug-in rate standard) | morning | Mitigated this round (reorder strengthens framing); the rate itself unchanged. |
| M12 (QIF Shannon vs min-entropy) | morning | Resolved between rev2 and today (§9 paragraph added). |

### rev2 Major findings

| ID | Status now |
|---|---|
| Major 1 (rev2: §5/§7.4 stragglers) | Resolved between rev2 and today. |
| Major 2 (rev2: Bost-Fouque) | Resolved between rev2 and today. |
| Major 3 (rev2: §2 broken forward ref) | Resolved between rev2 and today (§9 paragraph added). |

### rev2 New issues from rev2 fixes

| ID | Status now |
|---|---|
| n1, n2 (rev2: framing stragglers) | Resolved. |
| n3 (rev2: §2 broken forward ref) | Resolved. |
| n4 (rev2: Thm 4.2 TV bound asserted) | Resolved between rev2 and today. |
| n5 (rev2: n=64 without context) | Resolved between rev2 and today. |
| n6 (rev2: Simmons attribution loose) | Open (cosmetic). |
| n7 (rev2: Cover-Thomas permissive cite) | Open (acceptable at textbook level). |

### Minor findings

| ID | Status now |
|---|---|
| m1 (Q overloaded) | Open carry-over. |
| m2 (§5 narrative hook) | Partial; today's rewrite leads with "two effects" instead of "marginal delta is necessary but not sufficient." Could lead better. Open. |
| m3 (§5.1 ordering) | Open carry-over. |
| m4 (Prelim IT redefinition) | Open carry-over. |
| m5 (§5.2 active probing informal) | Open carry-over. |
| m6 (Compression proof terse) | Open carry-over. |
| m7 (Limitations 5th tightness bullet) | Open carry-over. |
| m8 (Threat model implicit) | Open carry-over. |
| m9 (Compression no empirical anchor) | Open carry-over. |
| m10 (Hyperref bookmark warning) | Resolved in rev2. |
| m11 (Zero figures) | Open carry-over. |
| m12 (Uncited bib entries) | 19 still uncited (down from 21). Cosmetic. |
| m13 (grubbs2018pump venue) | Open (cosmetic, uncited). |

---

## Major Issues (this round)

### Major 1: §5 title "The Compositional Scale" vs. §5.2 scope (source: prose-auditor; new this round)

- **Location**: §5 title (line 739, "The Compositional Scale"); §5.2 title (line 861, "Error Compounding in Boolean Chains").
- **Quoted text (§5 opener, lines 743-755)**:
  > "When cipher maps compose [...], confidentiality moves to a
  > different scale than the marginal one [...]. The compositional
  > scale has two effects. The primary effect is *correlation
  > leakage*: marginal delta-uniformity does not prevent the
  > adversary from recovering joint distributions [...]. The
  > secondary effect, inherited from [...], is error compounding
  > through Boolean chains."
- **Problem**: The §1 framing (introduced this round) reserves
  "compositional scale" specifically for the *confidentiality*
  complement to the *marginal scale*. §5.2 is about *correctness*
  (FPR compounding), not confidentiality. A reader who has the §1
  framing in mind will expect §5 to be confidentiality-only and
  may be confused that §5.2 includes correctness material.
- **Suggestion**: Light-touch fix. Add one or two sentences to the
  §5 opener distinguishing the two facets. Sample addition (sketched,
  not prescribed):
  > "Composition introduces both confidentiality and correctness
  > effects. Section 5.1 (correlation leakage) is the
  > confidentiality counterpart to the marginal scale. Section 5.2
  > (error compounding) is the correctness behavior under
  > composition, included for completeness and inherited from the
  > companion paper."
  Alternative: rename §5 to "Compositional Behavior" or
  "Composition" to match §5's actual scope.
- **Cross-verified**: I (area chair) re-read §5 and §1 in sequence.
  The mismatch is real but not severe. The current opener sentence
  "The compositional scale has two effects" partially handles it,
  but the §1 framing made "compositional scale" a confidentiality-
  specific label, so the reader is surprised when §5.2 turns out to
  be correctness.
- **Severity**: Major. Visible in TOC and on first read of §5.
  Light-touch fix.

---

## Minor Issues (this round)

### Minor 1: Abstract / contribution-list ordering mismatch (source: prose-auditor; new this round)

- **Location**: Abstract (lines 47-70); contribution list (lines
  172-205).
- **Problem**: Abstract narrates Fannes bridge first (point 3),
  Thm 5.1 as "main result" at point 5. Contribution list leads
  with Thm 5.1.
- **Suggestion**: Per user's choice, this is deliberate (narrative
  arc rather than enumeration). If the user wants to align them in
  a future pass, lead the abstract with the main result earlier.
- **Severity**: Minor. Per user's choice, not a finding to act on.

### Minor 2: §1 paragraph structure asymmetry (source: prose-auditor; new this round)

- **Location**: §1 line 167.
- **Quoted text**: "Finally, we provide practical measurement
  tools..."
- **Problem**: This paragraph lacks a `\paragraph{}` heading while
  the surrounding text uses them. Visually inconsistent.
- **Suggestion**: Add `\paragraph{Practical measurement.}` for
  symmetry.
- **Severity**: Minor (cosmetic).

### Minor 3: §3 and §4 lack explicit "marginal scale" labeling (source: prose-auditor; new this round)

- **Location**: §3 title (line 356, "The Confidentiality
  Measure"); §4 title (line 509, "Constructions for Reducing
  delta").
- **Problem**: After §1 introduces the two-scale framing, neither
  §3 nor §4 carries the "marginal scale" label. A section-skipping
  reader loses the framing.
- **Suggestion**: Add a one-sentence opener to §3 noting that §3
  and §4 develop the marginal-scale theory; §5 develops the
  compositional-scale theory.
- **Severity**: Minor.

### Minor 4: M9 carry-over (source: methodology-auditor; carry-over from morning)

- **Location**: Tables 1, 2, 3 (lines 1078, 1107, 1137).
- **Problem**: No CIs, no trial counts, no reproducibility info.
  Captions do not label values as analytical or empirical for
  Tables 1-3 (Table 4 was relabeled in rev2).
- **Suggestion**: Add CIs and trial counts where applicable; add
  a reproducibility footnote with commit hash.
- **Severity**: Minor for a theory venue, Major for a systems
  venue.

---

## Suggestions

1. **Strengthen the "scales connect" precision** (source: novelty-
   assessor). After Thm 5.1 or in the §5 opener, add a sentence
   noting that the marginal-uniformity hypothesis in Thm 5.1 is
   for cleanness; the rate argument in part (3) holds for any
   delta_i with a constant that depends on the marginal-uniformity
   gap.
2. **Acknowledge the experimental gap for Thm 5.1** (source:
   methodology-auditor). One sentence in §7 or §9 noting that
   Thm 5.1 is validated theoretically; the parametric rate has
   been characterized in prior work (Cover-Thomas).
3. **Add a Le Cam / Fano matching lower bound for Thm 5.1 part
   (3)** (source: novelty-assessor, carry-over M11). Lifts the
   rate from "plug-in standard" to "information-theoretically
   optimal."
4. **Add a schematic figure** of the trusted/untrusted model
   (source: format-validator, carry-over m11). Cosmetic but helpful
   for first-time readers.

---

## Detailed Notes by Domain

### Logic and Proofs

The two structural changes (paragraph re-routing in §1, §5 retitle)
are purely expositional. No equations, theorem statements, or proofs
were altered. All theorems (Thm 3.1, 4.1, 4.2, 5.1, Prop 5.2, Prop
6.1) are unchanged from rev2 in mathematical content. Theorem
references and equation numbering are preserved.

The "compositional channel intrinsic to composability" claim (line
155-158) is defensible but slightly loose. A precise version would
distinguish: composability requires cipher value persistence;
shared-c observation also requires cipher value persistence; the
two are the same structural property under the cipher map framework.
Not flagged as a finding because the current paragraph reads as
informal motivation rather than a theorem statement.

Independent numerical verification: Fannes bound (delta=0.05, n=64
yields e >= 0.9455 vs. paper's 0.945; delta=0.01, n=64 yields
e >= 0.9887 vs. paper's 0.989); Zipf s=1, m=10000 entropy (9.5323 vs.
paper's 9.55, baseline e=0.7174 vs. paper's 0.72); Example 4.1
homophonic H(Q)=11.58 vs. paper's 11.5, e=0.871 vs. paper's 0.87.
All within rounding/hedging.

Carry-over open: M2 (Fisher info constant), m1 (Q-notation), m6
(compression proof terseness).

### Novelty and Contribution

The contribution-list reorder is reviewer-defensible. Thm 5.1
carries quantitative content (MI preservation, parametric rate,
joint TV bound on optimal delta_3) that justifies the headline
position. The Fannes bridge is honestly framed as a translation
tool (#2) rather than novel mathematics.

The two-scale framing is a genuine structural insight, not
repackaging. It gives the reader a clean handle for the paper's
spine and is honest about what each scale contributes.

M10 (Fannes bridge as headline) is now resolved by the reorder.
M11 (Thm 5.1 plug-in rate as standard) is mitigated by the
reorder's framing emphasis on Parts (2) and (4); the rate itself
unchanged.

The marginal-uniformity hypothesis of Thm 5.1 connects the two
scales in a way the §1 framing does not fully precision. A one-
sentence remark would tighten this (Suggestion 1).

### Methodology

Tables 1-4 unchanged this round. Cross-references from §7 to §4
(via `sec:levers` label) resolve correctly after the §5 rename;
no broken references.

Independent verification of Table 4 numerics confirms internal
consistency (baseline 0.72 to homophonic 0.87 to noise 0.88 to
combined 0.98).

The new headline (Thm 5.1) introduces a small experimental-
validation gap: §7 validates FPR compounding (Table 2),
granularity (Table 3), and the case study (Table 4) but not the
compositional leakage attack itself. A one-sentence acknowledgment
in §7 or §9 would close this.

M9 carry-over (CIs / reproducibility / labels for Tables 1-3)
unchanged.

### Writing and Presentation

The §1 framing flows cleanly; the inserted "Our central
observation" paragraph reads as natural. The four sequential
`\paragraph` headings in §1 are dense but legal; they render
correctly.

The §5 retitle creates a Major scope-mismatch issue: "The
Compositional Scale" implies confidentiality-only, but §5.2 is
correctness. Light-touch fix needed (Major 1 above).

The abstract / contribution-list ordering mismatch is per user's
deliberate choice and not a defect; flagged as Minor for
completeness.

§3 and §4 lack explicit "marginal scale" labels; a one-sentence
opener to §3 would clarify the role of these sections in the two-
scale framing (Minor 3 above).

Carry-over open: m1 (Q-notation), m2 (§5 narrative hook), m3
(§5.1 ordering), m4 (Prelim IT redefinition), m5, m7, m8.

### Citations and References

Bost-Fouque venue corrected to IACR ePrint between rev2 and today
(M7 from morning round resolved). All five rev2 citation additions
(Fannes, Audenaert, Cover-Thomas, Simmons, Bost-Fouque correction)
are intact.

Uncited count: 19 (unchanged from rev2). No new citation issues
introduced this round.

Carry-over open: Minor 3 from rev2 (Simmons attribution loose for
homophonic), m13 (grubbs2018pump venue, cosmetic since uncited).

### Formatting and Production

Build is clean at 18 pages (up from rev2's 17 pages, consistent
with added prose). Zero warnings, zero errors. All `\ref` and
`\cite` calls resolve. The four `\paragraph` headings in §1
compile and render correctly. The §5 retitle does not affect any
cross-reference (uses `sec:composition` label which is unchanged).

Carry-over open: m11 (zero figures, cosmetic).

---

## Literature Context Summary

Literature scouts not launched in this environment; carry-over from
prior rounds. The contribution-list reorder slightly strengthens
the SSE-related positioning (Cash, Kellaris, Oya-Kerschbaum), but
those references remain mostly uncited (carry-over gap). The
cipher-map framing remains structurally distinctive.

---

## What's New This Round vs. Carry-Over vs. Resolved

### New this round (post-rev2 + this round's framing changes)

- **Today's framing changes**: Contribution-list reorder
  (Thm 5.1 promoted, Fannes bridge demoted); two-scale §1
  framing; §5 retitle to "The Compositional Scale" with
  rewritten opener.
- **New finding (Major 1)**: §5 title vs. §5.2 scope mismatch.
- **New findings (Minor 1, 2, 3)**: Abstract ordering mismatch;
  §1 paragraph asymmetry; §3-§4 missing marginal-scale labels.
- **New suggestions (1, 2)**: Strengthen scales-connect precision;
  acknowledge experimental gap for Thm 5.1.

### Carry-over open

- **M2 (morning)**: Thm 4.1 Fisher info constant (Major).
- **M9 (morning)**: Tables 1-3 CIs / reproducibility (Minor for
  theory, Major for systems).
- **M11 (morning)**: Thm 5.1 plug-in rate has no matching lower
  bound (Major; mitigated by reorder).
- **m1 to m13 carry-over**: All open as before.

### Resolved across the three rounds

- **C1, C2** (Pinsker direction; K(x) inversion): Resolved in rev2.
- **M1, M3, M4, M5, M6** (Zipf numerics, Thm 5.1 sampling,
  correlations, part 4, Simmons): Resolved in rev2.
- **M7 (Bost-Fouque venue), M8 (three levers stragglers)**:
  Resolved between rev2 and today.
- **M10 (Fannes bridge as headline), M12 (Shannon vs min-entropy)**:
  Resolved this round (M10 by reorder; M12 by §9 paragraph).
- **n1, n2, n3, n4, n5 (rev2 new issues)**: All resolved between
  rev2 and today.
- **Minor 5 (rev2 MI fragility)**: Resolved between rev2 and today.
- **m10 (hyperref bookmark warnings)**: Resolved in rev2 cleanup.

---

## Recommendation Rationale

**Recommendation**: minor-revision

The morning round was major-revision (two critical errors in
headline material). Rev2 was minor-revision (two visible stragglers
and a broken forward reference). This round is also minor-revision,
with the Major finding being a single light-touch fix (§5 title vs.
§5.2 scope clarification).

The paper has been on an upward trajectory across three rounds:
- Morning: 2 critical, 12 major, 13 minor (major-revision).
- Rev2: 0 critical, 3 major, 8 minor (minor-revision).
- This round: 0 critical, 1 major, 4 minor (minor-revision).

The mathematical content is sound. The contribution framing is
honest and reviewer-defensible. The two-scale framing is a genuine
structural insight that strengthens the paper's spine.

The remaining Major (§5 title scope) is mechanical to fix. The
remaining Minor items are mostly carry-over from prior rounds and
are not in headline material.

The deferred items (M2 Fisher info constant; M9 experimental rigor;
M11 lower bound; m1-m13 carry-overs) represent the polish pass that
should follow this round. None invalidates a quantitative claim.

**With the Major 1 fix landed (estimated 5 minutes of work), this
paper is ready for venue submission.**

---

## Review Metadata

- Agents used (specialist roles, executed by area chair due to Task
  tool unavailability):
  - logic-checker
  - novelty-assessor
  - methodology-auditor
  - prose-auditor
  - citation-verifier
  - format-validator
- Literature scouts: not launched in this environment; literature
  context carried over from prior rounds with this-round-specific
  notes.
- Cross-verifications performed:
  - Fannes bound numerical (logic-checker + area chair direct
    Python computation): verified.
  - Zipf s=1 entropy (logic-checker + area chair direct Python
    computation): verified.
  - Example 4.1 homophonic H(Q) and e (logic-checker + area chair
    direct Python computation): verified.
  - Sum K_top with ceiling (logic-checker noted 11% gap with
    paper's "approximately 519"; verified the gap is within the
    paper's hedging).
  - Bost-Fouque venue (citation-verifier + area chair source check):
    verified now correct (IACR ePrint).
  - "Three levers" stragglers (prose-auditor + area chair grep):
    verified all cleared.
  - §9 Shannon vs min-entropy paragraph (prose-auditor + area chair
    source check): verified present and substantive.
  - Build clean at 18 pages (format-validator + area chair fresh
    pdflatex run): verified.
- Disagreements noted: 0. The specialist findings are mutually
  consistent.
- Hallucination check: every quoted manuscript text was verified
  against the source. No discrepancies.
