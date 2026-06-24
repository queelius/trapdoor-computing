# Novelty Assessor Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Summary

The novelty position is unchanged from R8 and remains solid. The five-part
contribution (framework abstraction; acceptance-predicate knob with (TV, L)
Pareto frontier; multi-instance coincidence-oracle theorem; empirical Le
Cam tightness; three-literature unification) holds. The homophonic-arc
edits this round (Proposition prop:homophonic) actually *strengthen* the
novelty story: the paper now has a self-contained, rigorous TV identity for
homophonic allocation that does not lean on the unpublished maxconf paper.

**Counts**: Critical 0 | Major 1 | Minor 1 | Suggestions 1.

## What the new Proposition does for novelty

Before this round, the representation-uniformity story leaned on a deferral
to maxconf for "tighter constants." Removing that deferral and replacing it
with a proved, hypothesis-free bound (TV < |X|/N for the Simmons
allocation) makes the paper's homophonic-substitution contribution
**self-standing**. The connection "representation uniformity generalizes
homophonic substitution from substitution ciphers to arbitrary total
functions" (line 326-327) is now backed by an exact TV identity rather than
an appeal to a companion paper. This is a net novelty gain: one fewer
load-bearing forward reference, one more standalone result.

The proposition itself is not deeply novel (it is an elementary TV
computation), but it is the right kind of result to include: it makes the
homophonic claim precise and self-contained. Correctly framed as a
"Proposition," not oversold as a "Theorem."

## NOV-MAJ-1: Load-bearing deferral to four unpublished sister papers (carry-over R6/R7/R8 MAJ-1)

**Source**: novelty-assessor, citation-verifier.

The framework's quantitative confidentiality guarantee (Proposition 5.1,
the Fannes-Audenaert bound) still defers its *proof* to
towell2026maxconf Theorem 4.1 part 3. The entropy-ratio definition, the
function-value leakage translation, and the rekeying chain bound similarly
defer. Four "Manuscript in preparation" entries underwrite load-bearing
claims. This is the single biggest novelty-presentation risk: a reviewer
cannot verify the central confidentiality bound without the companion
preprint.

The homophonic proposition this round *reduces* the exposure (the
representation-uniformity story no longer needs maxconf), but Proposition
5.1 still does. Posting the Zenodo DOIs (the user's stated MAJ-1 task)
closes this.

**Suggestion**: Post all four to Zenodo with DOIs before submission. Closes
the major fully. With the homophonic proposition now self-contained, the
*only* remaining hard dependency is Proposition 5.1 on maxconf Thm 4.1
part 3.

## NOV-MIN-1: Section 1 framework-contribution paragraph still mixes disclaim with enumeration (carry-over R8 PROSE-MAJ-3 / NOV-MAJ-2)

**Location**: lines 123-153.

The "Contribution: framework, not new construction" paragraph opens by
disclaiming construction novelty ("We do not propose a new construction
with novel space, time, or correctness guarantees") then immediately
enumerates new formal results (lower bound, composition theorem,
confidentiality bound, multi-instance theorem, empirical evaluation). The
disclaim and the enumeration partly undercut each other: a reader is told
"nothing new" then handed a list of new theorems. The intent (the
*framework* is the contribution, not a new *data structure*) is right but
the rhetoric muddies it.

**Suggestion**: Split into (A) "What is not new: the underlying
constructions (Bloom, prefix coding, perfect hashing)" and (B) "What is
new: the unifying abstraction plus the formal results it enables." This is
a presentation fix, not a novelty defect. Carry-over.

## NOV-SUG-1: Acknowledge the multi-instance lineage

The coincidence-oracle theorem is a clean specialization but should
explicitly position against the multi-snapshot / equality-pattern leakage
lineage (Kellaris-Kollios-Nissim-O'Neill 2016; deterministic-encryption
equality leakage). A one-sentence "prior work characterized equality-pattern
leakage qualitatively; we give a closed form specific to acceptance-predicate
cipher maps" would inoculate against a "this is known" reviewer reaction
without weakening the claim. (carry-over R8 CITE-SUG-1)

## Bottom line

Novelty is sound and slightly improved this round. The framework
contribution is genuinely new; no claim is anticipated fatally by prior
work. The only novelty-presentation risks are the unpublished-sister-paper
deferral (closes with Zenodo DOIs) and the section 1 disclaim/enumeration
tension (one editorial split).
