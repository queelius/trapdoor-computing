# Methodology Auditor Report (round 3, 2026-04-29)

## Scope

Verify that today's structural changes (contribution reorder,
two-scale framing) preserve consistency between the experimental
sections and the theory sections. Confirm Tables 1 to 4 still match
the theory after §5 rename and §1 restructure. Note current state of
M9 (CIs, reproducibility, analytical-vs-empirical labels).

## Tables vs. theory consistency

The structural changes did not touch Tables 1 through 4 (lines 1078,
1107, 1137, 1167) or the §7 experimental section.

| Table | Topic | Theory section it validates | Status |
|---|---|---|---|
| Table 1 (Boolean search) | Precision/recall on 20 Newsgroups | Prop 5.2 (FPR compounding) | OK |
| Table 2 (FPR compounding) | Empirical vs. theoretical FPR | Prop 5.2 | OK |
| Table 3 (Granularity) | Cost spectrum for 7-function pipeline | Prop 4.3 (granularity), §4.3 inherited | OK |
| Table 4 (Case study) | Confidentiality improvement | Thm 4.1 (noise) + Thm 4.2 (multiplicity) | OK |

Cross-references in the experimental section that point to theory:

- Line 1091: "The results confirm the FPR compounding theory" (refers
  to Prop 5.2). OK.
- Line 1156: "We demonstrate the two constructions of \S\ref{sec:levers}"
  (refers to §4 noise + multiplicity). OK; matches the rev2 fix that
  removed "three levers" framing.
- Line 1162: "via the two constructions of \S\ref{sec:levers}".
  OK.

The §5 rename (was: "Three Levers for Improving Confidentiality"; is:
"The Compositional Scale") does NOT affect the experimental section,
because the experimental section refers to §4 (where the constructions
live), not §5 (which is now exclusively about composition).

Wait, this requires a careful read. Let me re-check the section
numbering:

- §3: The Confidentiality Measure
- §4: Constructions for Reducing delta (was titled "Three Levers" in
  morning round, then renamed in rev2 cleanup)
- §5: The Compositional Scale (was titled "Compositional
  Confidentiality"; renamed today)

The §4 rename (from "Three Levers" to "Constructions for Reducing
delta") happened during rev2 cleanup or earlier today; the §5 rename
(to "The Compositional Scale") is today. The experimental section's
"two constructions of §\ref{sec:levers}" still refers to §4 via the
`sec:levers` label.

Let me verify this by searching for the label.

The label `sec:levers` is at line 510 (under §4). Line 1156 cites it
correctly. Line 1162 cites it correctly. No broken references.

## Validation of Table 4 numerics (independent recomputation)

Per the logic-checker's verification:

| Row | e | Space | Bandwidth | Verified |
|---|---|---|---|---|
| Baseline | 0.72 | 1.00x | 1.00x | OK |
| + Homophonic | 0.87 | 1.04x | 1.00x | OK (matches paper Example 4.1 derivation) |
| + Noise (R/N=0.5) | 0.88 | 1.00x | 1.50x | OK |
| Combined | 0.98 | 1.04x | 1.50x | OK |
| Theoretical max | 1.00 | inf | inf | OK |

Table 4 is internally consistent. Caption (line 1163) correctly
labels values as "analytical, computed from the Zipf entropy, the
mixture-entropy formula in Theorem~\ref{thm:noise-dilution}, and the
homophonic construction in Example~\ref{ex:homophonic}." This labeling
is the rev2 fix to M9.

## M9 status (carry-over)

Unchanged from rev2:

- **Table 4 caption**: Now correctly labels "Values are analytical."
  (Resolved in rev2.)
- **Tables 1, 2, 3**: Still implicitly experimental. No CIs, no
  trial counts, no reproducibility info. (Open carry-over.)
- **Reproducibility**: No commit hash, no script links. (Open
  carry-over.)

For a theory venue submission, the M9 carry-over is acceptable but
suboptimal. For a systems venue (USENIX, CCS), it would be a hard
requirement.

## Two-scale framing as a methodology question

Today's framing change names "marginal scale" and "compositional
scale" as the spine. The experimental section validates:

- FPR compounding (Table 2): part of Prop 5.2, which is in §5
  (compositional scale).
- Encoding granularity (Table 3): part of §4.3 (cited as inherited
  from companion paper), which is in §4 (constructions for reducing
  delta, which is marginal scale).
- Case study (Table 4): combines marginal-scale constructions
  (homophonic, noise) and demonstrates marginal-scale e improvement.

The experimental section does not validate Thm 5.1 (the headline
result). The compositional leakage theorem is purely theoretical;
no experiment shows the joint distribution being recovered.

This is a structural gap in the experimental story, but it predates
this round and was acknowledged in prior reviews. For a theory
paper this is acceptable; for a systems venue it would be flagged.

A reviewer might ask: "If Thm 5.1 is the headline, why doesn't the
experimental section demonstrate the attack?" The paper's implicit
answer (Thm 5.1 is a sample-complexity bound, not an attack;
demonstrating it would require running the plug-in estimator at
scale) is reasonable but is not articulated.

**Recommendation**: One paragraph in §7 (or §9) acknowledging that
Thm 5.1 is validated theoretically and not experimentally, with a
sentence pointing to the standard plug-in estimator literature.
This would close a small but visible gap in the experimental story.

## Findings (this round)

### New this round

#### Suggestion: Acknowledge the experimental gap for Thm 5.1

- **Location**: §7 (Experimental Results) or §9 (Discussion).
- **Observation**: The experimental section validates FPR
  compounding (Table 2) and the case study (Table 4), but does
  not directly validate Thm 5.1 (the new headline contribution).
- **Suggestion**: Add a sentence in §7 opening or §9 limitations:
  "Theorem~\ref{thm:comp-leakage} is validated theoretically via
  the standard plug-in estimator analysis; we do not run an
  empirical attack, since the parametric rate has been
  characterized in prior work [Cover-Thomas]."
- **Severity**: Suggestion. Not blocking.

### Carry-over open

- **M9 (carry-over)**: Tables 1, 2, 3 still lack CIs and
  reproducibility. Status unchanged.

### Resolved across the three rounds

- **M1 (morning, resolved in rev2)**: Zipf numerics now consistent
  with stated distribution.
- **M9 partial (rev2)**: Table 4 caption now labels values as
  analytical.

## Summary

Tables and theory remain consistent after today's structural
changes. The §5 rename does not break experimental references
because they cite `sec:levers` (§4 label), not the §5 label. Table
4 numerics verified internally consistent. M9 carry-over is
unchanged.

The headline reorder (Thm 5.1 to contribution #1) introduces a small
but real experimental-validation gap: the new headline is not
empirically validated. A one-sentence acknowledgment would close
this. Not blocking.

**Recommendation from methodology-auditor**: minor-revision (M9
carry-over plus the new-headline experimental gap). Not a
regression from rev2.
