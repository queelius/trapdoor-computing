# Prose Auditor Report, Round 8 (2026-05-27)

This round audits the new Related Work paragraph (homophonic
substitution) and Definition 4.2 rewrites from today's commit, plus
the carryover prose issues from R7.

## Today's prose changes verification

### Related Work homophonic paragraph (lines 314 to 327)

Reads coherently. Five-sentence paragraph: (a) representation
uniformity is modern homophonic substitution, citing Simmons; (b)
introduces D(x) and K(x) notation with explicit forward references;
(c) the standard Simmons prescription K(x) proportional to D(x); (d)
operational explanation (frequent values get more representations);
(e) representation uniformity generalizes homophonic substitution to
arbitrary total functions.

Two minor cosmetic issues:
- Line 318 to 319 says "Writing D(x) for the prior probability that
  the trusted machine encodes latent value x". The phrase "prior
  probability that the trusted machine encodes" is slightly clunky
  (it conflates the distribution from which values are drawn with
  the act of encoding). Cleaner: "Writing D(x) for the prior
  probability that the latent value x is drawn for encoding by the
  trusted machine."
- Line 322 says "the standard Simmons prescription K(x) proportional
  to D(x)". "Standard" is slightly ambiguous (standard in classical
  cryptography literature? standard in this paper?). Cleaner:
  "Simmons's classical prescription K(x) proportional to D(x)" with
  the citation immediately following.

These are minor wording, not blocking.

### Definition 4.2 rewrite (lines 498 to 525)

Reads coherently. The Definition body (lines 500 to 516) defines D as
"the prior probability distribution from which the trusted machine
draws latent values for encoding (the query distribution)". The
parenthetical "(the query distribution)" is the right anchor; it lets
the reader connect D to the operational query stream.

The post-Definition prose (lines 518 to 525) then gives the
operational consequence: "To achieve small delta, assign K(x)
proportional to D(x) encodings per value (the classical Simmons
homophonic prescription [cite]): frequent values get more
representations, so the per-representation query frequency D(x)/K(x)
is constant across x, and Q is flat across cipher values."

The D(x)/K(x) = constant argument is correct and well-stated. The
clarity is up from the pre-commit version (which presumably read
"K(x) proportional to 1/D(x)" with an incoherent operational
reading).

Both rewrites land cleanly. Direction is consistent across the four
flagged sites (verified by logic-checker).

## Carry-over prose issues from R7

### PROSE-MAJ-1 / R7 MAJ-13 (section 8.3 subsubsection style)

Section 8.3 (multi-instance composition leakage) uses three
`\subsubsection*` (unnumbered) headers:
- Line 1745: "The coincidence oracle"
- Line 1853: "Geometric corollary: t-dependent allocation"
- Line 1900: "Randomized encoding as a defense"

These are mixed with numbered subsubsections elsewhere in the paper:
- Line 1308: `\subsubsection{Entropy Cipher Map}` (section 6.6.1,
  numbered)

The inconsistency reads as "section 8.3 is somehow special". Two
resolution paths:
1. Convert all four to numbered `\subsubsection{...}` (consistent
   with §6.6.1). Increases the table of contents by 3 entries.
2. Convert all three to `\paragraph{...}` heading (consistent with
   most other section subdivisions in the paper). Keeps the
   structure but removes the visual "subsubsection" prominence.

Recommendation: path 1 (numbered subsubsections). Multi-instance
composition is the most novel single subsection of the paper; numbered
heads make it findable in the TOC.

R7 MAJ-13 carry-over. Still open.

### PROSE-MAJ-2 / R7 MAJ-14 (section 10.6 paragraph density)

Section 10.6 has seven paragraphs (Setup, Le Cam tightness, (TV, L)
Pareto, Multi-instance, Randomized encoding K sweep, Threat model
scope, Summary), each at 100+ words, without intervening structure.
The cumulative effect is a single long subsection running 120+
manuscript lines.

R7 recommended "Add structure-setting sentence at start of §10.6"
which was not landed. The methodology-auditor in this round
recommends a consolidated experiments table at the top of §10.6
(METH-SUG-1) which would also address this prose density issue.

Recommendation: add an opening sentence to §10.6 along the lines of
"The following five experiments validate the framework's value-side
security claims (Le Cam tightness, (TV, L) Pareto frontier, multi-
instance coincidence leakage, randomized encoding defense, threat
model scope); each is reported as a separate paragraph below."

R7 MAJ-14 carry-over. Still open.

### PROSE-MAJ-3 (NOV-MAJ-2 paragraph split)

The novelty-assessor recommends splitting the "Contribution: framework,
not new construction" paragraph at section 1 lines 123 to 152 into two:
the disclaim about construction novelty (Paragraph A) + the list of
new results within the framework (Paragraph B). This is a prose
clarity recommendation as well: the current single paragraph reads as
"we don't propose a new construction, but here are five new things",
which is internally contradictory in tone.

Recommendation: see novelty-assessor NOV-MAJ-2 for the suggested
split text.

## Prose minor issues

### PROSE-MIN-1 (abstract sentence length)

Abstract sentence 4 (lines 70 to 77) is 100+ words:

> "The construction reduces to a single design choice: an *acceptance
> predicate* that partitions hash space among output values.
> Acceptance predicates expose a Pareto frontier between expected
> codeword length L and TV-leakage; the Shannon-optimal corner (L =
> -log_2 epsilon + H(Y), matching the information-theoretic lower
> bound) and the TV-optimal corner are distinct under integer codeword
> constraints, with the gap reaching 42x in TV at 17% length overhead
> on heavy-tailed value distributions."

This is two sentences run together with a semicolon. Splitting at the
semicolon improves readability:

> "The construction reduces to a single design choice: an *acceptance
> predicate* that partitions hash space among output values. Acceptance
> predicates expose a Pareto frontier between expected codeword length
> L and TV-leakage. The Shannon-optimal corner (L = -log_2 epsilon +
> H(Y), matching the information-theoretic lower bound) and the TV-
> optimal corner are distinct under integer codeword constraints; the
> gap reaches 42x in TV at 17% length overhead on heavy-tailed value
> distributions."

R7 MAJ-15 carry-over. Still open.

### PROSE-MIN-2 (Bernoulli paragraph standalone)

Section 1 lines 154 to 162 contains the "Bernoulli error model"
paragraph as a standalone block, immediately before the "Positioning"
paragraph. The standalone nature of the Bernoulli paragraph (no
forward reference, no integration into the surrounding contribution
narrative) reads as an aside. Two resolution paths:
1. Move to section 3 (the Cipher Map Abstraction) where the
   construction layers are described.
2. Integrate one sentence into the "framework, not new construction"
   paragraph just before it: "The error framework underwriting the
   four-property analysis is the Bernoulli model [cite] which collapses
   per-element error exponential complexity to two parameters via
   element-wise and conditional-independence axioms."

Recommendation: path 2 (integration). Drops a standalone paragraph
from §1 and tightens the contribution narrative.

R7 PROSE-MIN-6 carry-over. Still open.

### PROSE-MIN-3 (the term "coincidence oracle" introduced informally)

Theorem 8.1 (line 1758) is "Coincidence-oracle accuracy". The
preceding prose (lines 1752 to 1757) describes "The simplest attacker,
the *coincidence oracle*, predicts ..." with `\emph{coincidence
oracle}` italics. This is the only place the term is *defined* in
the paper. Subsequent uses (lines 1834, 1841, 1851, 1865, 2655, 2769,
2784) treat it as a known term.

Recommendation: promote the definition to a `\begin{definition}` or
at least a numbered display. Currently it reads as if the term were
already standard, when in fact this is its first appearance in the
literature (per the novelty-assessor).

### PROSE-MIN-4 (section 8.3 "tuple-probe notation" reference)

R7 MAJ-1 was about "Theorem 8.1 verbal definition / proof tuple
mismatch". The current Theorem 8.1 prose (lines 1758 to 1773) and
proof (lines 1782 to 1827) use compatible notation: the verbal
description says "the coincidence oracle, predicts 'in-domain' iff
dec_1(f_hat_1(c)) = ... = dec_t(f_hat_t(c)) and the common decoded
value is not bot", and the proof uses dec_i(f_hat_i(c_i)) = f(x).
The c vs c_i distinction is: the verbal description uses a single
candidate c (then dec_i is applied directly), while the proof uses
c_i = enc_i(x, 0) per-instance.

This is consistent only if "c" in the verbal description means
"a candidate input that is encoded as c_i = enc_i(x, 0) in
instance i". The verbal description should be clarified to make this
explicit. Recommendation: rewrite lines 1752 to 1757 as:

> "The simplest attacker, the *coincidence oracle*, observes the
> decoded values dec_i(f_hat_i(c_i)) for a probe c = (c_1, ..., c_t)
> where each c_i is the per-instance encoding of a candidate input x.
> The attacker predicts 'in-domain' iff all t decoded values agree
> on a common value in Y."

This makes the per-instance encoding explicit.

R7 MAJ-1 partially closed; this round notes the residual ambiguity.

### PROSE-MIN-5 (Huffman saturation encoder gloss)

R7 MAJ-4 was about "Huffman saturation encoder gloss". The current
Remark 8.x (lines 2006 to 2023) gives the closed form for member
coincidence under Huffman. Lines 1945 to 1949 (Proposition 8.2
hypothesis) include the parenthetical "this holds, e.g., for Huffman
codespace classes where K(x) equals the codespace class size 2^(n -
l_{f(x)})".

The "saturation" terminology is introduced at line 1946 without a
formal definition. The reader has to interpret it via the
parenthetical example. This is the same issue logic-checker raises
as LOG-MAJ-4 (saturation vs bijectivity).

Recommendation: add a single Definition between Proposition 8.2 and
Remark 8.x:

> Definition (Encoder saturation). An encoder enc_i for cipher map
> instance i is *saturated* on value y if the restriction enc_i(x,
> .) : {0, ..., K(x)-1} -> A_i(y) is a uniform bijection for every
> latent value x with f(x) = y.

R7 MAJ-4 still open; this round provides the recommended Definition.

### PROSE-MIN-6 (Bernoulli terminology drift)

The paper uses "Bernoulli model" (section 1 line 156), "Bernoulli
framework" (section 9.1 line 2080), "Bernoulli error model" (section
1 line 154), and "Bernoulli axioms" (no occurrence, but mentioned in
state.md and CLAUDE.md). These are slight variants. Recommend
standardizing on "Bernoulli framework" (since the citation is
`bernoulli-types` covering multiple papers) with the parenthetical
"(error axioms + algebraic types)" at first mention.

R7 PROSE-MIN-8 carry-over.

### PROSE-MIN-7 (sampling noise phrasing)

Section 10.6 lines 2643 and 2698 use "sampling-noise scale" and
"sampling noise" without definition. For a methodology-aware reader
this is unambiguous (standard error of the mean across replicates);
for a general reader the term is technical. Recommendation: at first
use, add parenthetical "(standard error of the per-replicate mean,
typically 0.001 to 0.01 at our sample sizes)".

R7 PROSE-MIN-10 carry-over.

### PROSE-MIN-8 ("approximately" vs "~" inconsistency)

Section 8.3 (line 1879) uses "max_y alpha(y) ≈ 0.5" with `\approx`.
Section 10.6 (lines 2657 to 2664) uses both "approximately 0.9999"
(spelled out) and "$\approx$ 132x" (math approx). Recommendation:
pick one convention. In running prose, "approximately" is clearer;
in mathematical expressions, `\approx` is standard. The current
mixing is fine; cosmetic only.

R7 PROSE-MIN-4 carry-over.

### PROSE-MIN-9 (section 9.6 header style)

Section 9.6 ("Threat Model Scope") was added in R7 (line 2225) with
the `[INTEGRATION 2026-05-07]` comment marker still present (lines
2224 and 2259). The marker is OK in source but should be cleaned
before submission. R7 carry-over.

Similarly section 8.3 has integration markers at lines 1731 and 2054.

Recommendation: remove all `[INTEGRATION ...]` comment markers before
PoPETs submission.

## Cross-section narrative arc

Reading section-to-section transitions for coherence:

- Section 1 -> 2 (Intro to Related Work): clean. Intro positions
  cipher maps in QIF tradition; related work draws explicit
  distinctions to prior threads.
- Section 2 -> 3 (Related Work to Abstraction): clean. Related work
  ends on homophonic substitution; abstraction opens with
  preliminaries on hash functions.
- Section 3 -> 4 (Abstraction to Four Properties): clean. Abstraction
  defines the cipher map tuple; four properties parameterize it.
- Section 4 -> 5 (Properties to Trust Model): clean. Properties bound
  what U can observe; trust model formalizes what T and U can do.
- Section 5 -> 6 (Trust Model to Batch Construction): natural. Trust
  model establishes the operational setting; batch construction
  builds the cipher maps.
- Section 6 -> 7 (Batch to Composition): natural. Composition is
  Property 4, formalized after the batch construction is in hand.
- Section 7 -> 8 (Composition to Rep Uniformity / Granularity):
  somewhat abrupt. Composition is about correctness; section 8 is
  about uniformity. The transition is implicit (both are properties).
  A one-sentence bridge at the end of section 7 or the start of
  section 8 would help: "We turn now from correctness composition
  (Property 4) to representation uniformity (Property 2), which has
  its own form of composition: the joint distribution of cipher
  values across multiple cipher maps under shared inputs leaks
  correlation structure that the per-map uniformity property does
  not bound."
- Section 8 -> 9 (Granularity to Discussion): clean.
- Section 9 -> 10 (Discussion to Implementation): clean. Implementation
  empirically validates the framework.

The narrative arc is solid. The only abrupt transition is section 7
to 8.

## Findings

### Critical

None.

### Major

**PROSE-MAJ-1**: section 8.3 subsubsection style (R7 MAJ-13 carry-
over). Three `\subsubsection*` mixed with numbered subsubsections
elsewhere; recommend numbered.

**PROSE-MAJ-2**: section 10.6 paragraph density (R7 MAJ-14 carry-
over). Recommend opening structure-setting sentence and/or
methodology table per METH-SUG-1.

**PROSE-MAJ-3**: section 1 framework-contribution paragraph mixes
disclaim with new-results enumeration. Recommend paragraph split per
NOV-MAJ-2.

### Minor

PROSE-MIN-1 to 9 as above. All R7 carry-over or new minor cosmetics.

### Suggestions

**PROSE-SUG-1**: add direction-summary table per LOG-SUG-1. This is
prose-and-logic cross-recommendation; the table helps both prose
clarity (one place to check direction conventions) and logic
discipline (defensive against the user-flagged direction-error
pattern).

**PROSE-SUG-2**: "How to read this paper" guide paragraph in section
1 (R7 PROSE-SUG-2 carry-over). For a 38-page paper, a brief reading
guide pointing readers to section 6.2 (acceptance predicate, the
single design choice), section 8.3 (multi-instance leakage, the most
novel section), or section 10.6 (empirical validation) would orient
the reader. Optional.

**PROSE-SUG-3**: promote randomized encoding to section 8.4 (R7
PROSE-SUG-3 carry-over). Currently the randomized-encoding defense is
nested inside section 8.3. Promoting to a standalone section 8.4
would make the defense findable and matches its actual prominence in
the multi-instance contribution.
