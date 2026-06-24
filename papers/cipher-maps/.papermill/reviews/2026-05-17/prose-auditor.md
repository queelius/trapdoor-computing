# Prose Auditor Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Scope

Focus on Round 7 deltas: revised abstract, §8.3 (multi-instance
composition leakage), §10.6 (codec security empirical study), and
consistency of the v3 thesis framing across these sections and §1.

## MAJOR FINDINGS

### PROSE-1: "Inverts the single-instance Shannon recommendation" in abstract is misleading

**Location**: Abstract lines 80-83.

**Quoted text**:
> "a coincidence-oracle bound (accuracy $1 - \tfrac{1}{2} \sum_y
> \alpha(y)^t$ for $t$ shared-$f$ instances under independent seeds)
> characterizes multi-instance leakage and inverts the single-instance
> Shannon recommendation at $t \geq 2$."

**Problem**: This is the prose embodiment of CRIT-1 (logic-checker).
Independent of the technical issue, the prose framing creates a
specific expectation in the reader: "at $t=1$ use Huffman, at $t \geq 2$
use Dense." The §10.6 empirical evidence does not support this
expectation; Huffman dominates at every $t$. Even if the logic
checker's interpretation is wrong (which it is not), this prose
creates a high-impact claim that the rest of the paper does not
deliver on.

**Suggestion**: After fixing CRIT-1 in the logic content, the abstract
should say something like: "a coincidence-oracle bound (accuracy
$1 - \tfrac{1}{2} \sum_y \alpha(y)^t$ for $t$ shared-$f$ instances
under independent seeds) characterizes multi-instance leakage and
shows that Shannon-optimal allocations provide both single-instance
and multi-instance defense; a randomized-encoding defense
(Proposition 8.2) further reduces pattern-coincidence leakage under
a private-codec threat model."

### PROSE-2: Multi-instance subsection (§8.3) has subsubsection title style that does not match the rest of the paper

**Location**: Lines 1729, 1837, 1878.

**Quoted text**:
> "\subsubsection*{The coincidence oracle}"
> "\subsubsection*{Geometric corollary: $t$-dependent allocation}"
> "\subsubsection*{Randomized encoding as a defense}"

**Problem**: §8.3 uses three unnumbered subsubsections introduced by
\subsubsection*{...}. The rest of the paper uses either numbered
subsections, paragraph headings, or italicized inline labels. The
mixed style draws attention to §8.3 as "an integrated module" rather
than as part of the natural flow.

**Suggestion**: Replace the three \subsubsection*{...} headings with
either paragraph headings (\paragraph{...}) for short blocks or
numbered \subsubsection{...} headings if they are conceptually
co-equal. The latter would also give them numbers (§8.3.1, 8.3.2,
8.3.3) that could be cross-referenced.

### PROSE-3: §10.6 paragraph headings duplicate the theorem/proposition labels

**Location**: Lines 2485, 2518, 2555, 2575, 2590, 2625.

**Quoted text**: §10.6 has paragraphs titled "Le Cam tightness across
attackers", "$(\text{TV}, L)$ Pareto frontier and the Shannon duality
refinement", "Multi-instance leakage and the coincidence oracle",
"Randomized encoding", "Threat model scope: value-side versus
key-side channels", "Summary".

**Problem**: These paragraph headings replicate the section structure
that already exists in §8.3 and §9.6. The reader experiences §10.6 as
a one-paragraph-per-claim recap of the formal results. This is
defensible (it is an empirical-validation section, and each paragraph
validates one formal claim), but the prose density is high and the
narrative arc within §10.6 is not strong.

**Suggestion**: Add one sentence at the start of §10.6 stating the
section's structure (e.g., "The empirical study verifies five claims
from §5, §8.3, and §9.6; each paragraph below covers one claim and is
labeled by the formal result it validates."). This makes the §10.6
structure visible and intentional.

### PROSE-4: Abstract sentence on (TV, L) Pareto frontier is awkward

**Location**: Abstract lines 72-77.

**Quoted text**:
> "Acceptance predicates expose a Pareto frontier between expected
> codeword length $L$ and TV-leakage; the Shannon-optimal corner
> ($L = -\log_2 \varepsilon + H(Y)$, matching the
> information-theoretic lower bound) and the TV-optimal corner are
> distinct under integer codeword constraints, with the gap reaching
> $42\times$ in TV at $17\%$ length overhead on heavy-tailed value
> distributions."

**Problem**: This is a 49-word sentence with three semicolon-joined
clauses. The reader needs to parse three layers: (a) Pareto frontier
exists, (b) two corners are distinct under integer constraints, (c)
42× gap. The "matching the information-theoretic lower bound" aside
is parenthetical but breaks the flow.

**Suggestion**: Split into three sentences:
> "Acceptance predicates expose a Pareto frontier between expected
> codeword length $L$ and TV-leakage. Under integer codeword
> constraints, the Shannon-optimal corner ($L = -\log_2 \varepsilon +
> H(Y)$) and the TV-optimal corner are distinct. On heavy-tailed
> value distributions, the TV-optimal allocation can achieve a $42
> \times$ leakage reduction at $17\%$ length overhead."

## MINOR FINDINGS

### PROSE-MIN-1: §8.3 "deployment pattern arises whenever" sentence list could be a bulleted list

**Location**: Lines 1724-1727.

> "This deployment pattern arises whenever the same data is published
> multiple times under different keys, when a cipher map is updated
> and both versions remain accessible, or when an attacker collects
> observations across multiple cipher map snapshots."

Three comma-separated cases; would read more cleanly as a bulleted
list.

### PROSE-MIN-2: §8.3 "deployment pattern" prose-then-formal-theorem transition is abrupt

The §8.3 opening sets up the deployment pattern (multiple cipher maps
of the same f, observed by the same adversary), then immediately
jumps to Theorem 8.1's formal statement. A one-sentence bridge ("We
now characterize the attacker's accuracy in closed form.") would
smooth the transition.

### PROSE-MIN-3: §8.3 "coincidence-oracle predicate" terminology drifts

"coincidence oracle" appears as both a noun (the attacker) and an
adjective ("coincidence-oracle accuracy", "coincidence-oracle leakage",
"coincidence-oracle predicate"). The hyphenation is consistent but the
density is high. Consider: introduce "coincidence-oracle" as the
attacker name in the verbal definition, then refer to "the oracle" or
"the attacker" in subsequent prose to vary the language.

### PROSE-MIN-4: §10.6 "$\sim$" notation drift

Line 1283: "$\sim$~713 documents per second". Line 1285: "approximately
10 documents per second". Two equivalent quantifiers. Standardize to
one (suggest "approximately" or "$\approx$").

### PROSE-MIN-5: §10.6 "Marginal output distribution at $t = 1$ is identical between canonical and randomized encoding to within $0.001$" is dense

Lines 2584-2586. The sentence is technically correct but compresses
three pieces of information (the marginal, the encoding modes, the
tolerance). Split into "Marginal output distribution at $t = 1$ is
identical between canonical and randomized encoding to within $0.001$
absolute deviation. This confirms the defense is free in the
single-instance regime."

### PROSE-MIN-6: §9.6 "Out of scope: structured key universes" paragraph header is informal

The paragraph header "Out of scope:..." uses italic, while other
paragraph headers in §9 use bold (`\paragraph{...}`). Minor
inconsistency.

### PROSE-MIN-7: §1 Bernoulli model paragraph stands alone awkwardly

Lines 151-159 (the "Bernoulli error model" paragraph) is one sentence
of motivation followed by one sentence of where the model lives. It
reads as a footnote that has been promoted to a paragraph. Either
absorb into the framework-contribution paragraph or footnote.

### PROSE-MIN-8: Abstract "We formalize..." sentence is the longest in the paper

Lines 83-88: "We formalize the framework through four measurable
properties, prove the space-optimality, composition, and
multi-instance theorems, validate the Le Cam attacker bound empirically
across a codec sweep, and illustrate the construction on arbitrary
maps, set membership, and encrypted search." This is a 4-clause
"we did" sentence. Two-clause split would read more cleanly.

### PROSE-MIN-9: "Bernoulli axiom" in §5.1 vs §9.1 differs

§5.1 references "Bernoulli axioms"; §9.1 says "Bernoulli framework
organizes approximation into a layered type hierarchy". Both refer to
the same underlying ideas but use different framings. Standardize.

### PROSE-MIN-10: §10.6 "single miss is sampling noise at 0.003 absolute" phrasing is informal

"Sampling noise" is the *cause* of the miss, but the *quantity* 0.003
is the *magnitude* of the deviation. Reword: "the single miss is a
deviation of 0.003 from the CI boundary, attributable to sampling
noise."

## SUGGESTIONS

### PROSE-SUG-1: After CRIT-1 is addressed, sweep §10.6 Summary for direction-of-claim errors

Specifically, item (iv) in the Summary at lines 2640-2643 says "the
$t$-dependent acceptance allocation (Corollary 8.x) is verified".
Once Corollary 8.x is fixed, this Summary line needs to match the
corrected text.

### PROSE-SUG-2: Add a short "How to read this paper" paragraph at the start of §1

For a 36-page paper covering framework, formal proofs, empirical
validation, and threat-model decomposition, a one-paragraph reader's
guide ("§3-5 set up the framework, §6-8 prove the technical results,
§9 discusses scope and limits, §10 validates empirically") would
help.

### PROSE-SUG-3: Consider folding §8.3.4 (Randomized encoding as a defense) into a separate subsection §8.4

The "Randomized encoding as a defense" content is conceptually
co-equal with "Multi-instance composition leakage" (it is the defense
against the attack §8.3 sets up). Promoting it to §8.4 would give it
visible structural weight matching its importance to the v3 thesis.

## Summary

- Critical: 0 (logic-side, attributed to logic-checker as CRIT-1; the
  prose embodiment is PROSE-1)
- Major: 4
- Minor: 10
- Suggestions: 3
