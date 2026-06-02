# Prose Auditor Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Scope**: writing quality, narrative arc, notation consistency, focusing
on the recently edited regions (Definition 4.2, the new Proposition,
the post-proposition prose, the section 10.6 Setup).

## Summary

The recently edited prose reads cleanly. Definition 4.2 with the inline
d_TV definition, the new Proposition prop:homophonic, and the
within-image/full-space clarification remark form a coherent, well-paced
unit. The removed deferral sentence leaves no seam. The section 10.6 Setup
rewrite (per-sweep codec enumeration) reads better than the R8 version.

Notation consistency surfaced two slips this round (kappa(y); n-vs-M),
both also caught by the logic-checker. The standing prose-structure
issues from R7/R8 (section 8.3 subsubsection style, section 10.6 paragraph
density, section 1 disclaim/enumeration) persist.

**Counts**: Critical 0 | Major 0 | Minor 4 | Suggestions 2.

## Recently edited prose: reads well

- **Definition 4.2** (lines 500-521): the inline d_TV definition with both
  the sum form and the sup form is placed correctly (right after the
  delta-uniformity inequality that uses it). Clean.
- **Proposition prop:homophonic** (lines 535-575): statement and proof are
  well-written; the proof's "Summing the absolute differences group by
  group" is clear and easy to follow.
- **Post-proposition remark** (lines 577-581): "The proposition bounds the
  gap to uniformity within the image; the residual gap ... is the noise
  region" is exactly the right bridge sentence. Good.
- **Section 10.6 Setup** (lines 2606-2628): the per-sweep codec enumeration
  ("specific codec sets differ per analysis paragraph below") resolves the
  R8 reader-confusion cleanly.

## PROSE-MIN-1 (NEW): kappa(y) notation slip (cross-listed LOG-MIN-1)

Lines 2098-2101 use kappa(y) where the rest of the paper uses K(x)/K(y).
Undefined symbol. Replace with K(y). (See logic-checker LOG-MIN-1.)

## PROSE-MIN-2 (NEW): n vs M bit-width inconsistency (cross-listed LOG-MIN-3)

Section 10.6 mixes n (Le Cam study) and M (E3/E4) for the cipher-value-space
bit-width, and lines 2005 vs 2748 write the same codespace-class size with
different symbols (2^{n-l} vs 2^{M-l_y}). Standardize on n or note M = n.
(See logic-checker LOG-MIN-3.)

## PROSE-MIN-3: Section 8.3 subsubsection style (carry-over R7 MAJ-13 / R8 PROSE-MAJ-1)

Section 8.3 uses three unnumbered `\subsubsection*` ("The coincidence
oracle", "Geometric corollary", "Randomized encoding as a defense") mixed
with the paper's otherwise-numbered structure. Use numbered subsubsections
or paragraph headings for consistency. Carry-over.

## PROSE-MIN-4: Section 10.6 paragraph density (carry-over R7 MAJ-14 / R8 PROSE-MAJ-2)

Section 10.6 runs seven dense sub-experiment paragraphs (Le Cam, Pareto,
multi-instance, randomized encoding, key-universe scope, summary) with
little intervening structure. A lead-in roadmap sentence or a consolidated
experiments table (also methodology METH-SUG-3) would help the reader.
Carry-over.

## PROSE-MIN-5: Integration comment markers left in source

Six `% [INTEGRATION 2026-05-07]` / `% [/INTEGRATION ...]` markers remain in
the .tex (lines around 1787, 2110, 2280, 2315, 2592, 2848). Cosmetic, but
strip before submission. (cross-listed format FMT-MIN-2)

## PROSE-SUG-1: Direction/parameter-summary table (cross-listed LOG-SUG-1)

Reinforce the logic-checker's recommendation: a small table codifying, per
prescription, "which direction is better defense" plus "which distribution
parameter gives which max alpha" would catch the recurring
direction/parameter errors (the s=1/s=1.2 mislabel this round) at edit time.

## PROSE-SUG-2: Split the section 1 framework-contribution paragraph
(cross-listed NOV-MIN-1)

Disclaim and new-results enumeration read against each other. Split into
"what is not new" and "what is new." Carry-over R8.

## Bottom line

Writing quality is high and improving. The recent edits are clean. The
residual prose issues are all minor/cosmetic and mostly carry-overs; none
blocks submission, though the integration markers and the kappa/n-M slips
should be cleaned up in the editorial pass.
