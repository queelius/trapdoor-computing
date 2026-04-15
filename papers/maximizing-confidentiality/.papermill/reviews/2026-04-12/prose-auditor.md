# Prose Auditor Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: HIGH

---

## Overall Assessment

The paper is generally well-written with a clear narrative arc. The
2026-04-12 revision successfully:
1. Tightened the Introduction to lead with the concrete problem
   (cipher-map system designer needs quantitative answers) and announce
   the two-construction-plus-inherited framing.
2. Added a Related Work section (previously missing) that engages QIF
   and SSE literature with reasonable brevity.
3. Reordered Section 5 so that correlation leakage (the novel
   contribution) appears first and error compounding (inherited) appears
   second.

The two-construction framing reads cleanly, not apologetically. The
phrase "inherited from the cipher maps framework" is exactly the right
register. The Related Work QIF paragraph is honest about prior art
without being self-deprecating. The conclusion is appropriate.

However, the conclusion and abstract still say "three levers for
improving confidentiality" which contradicts the refined two-plus-one
framing in the Introduction. And the Related Work section is just barely
long enough (3 paragraphs, less than 1 page). Some citations promised by
the refined thesis do not actually appear in the text.

Resolution of 2026-04-09 prose concerns:

| Prior concern | Status | Comment |
|---|---|---|
| No Related Work section (MAJOR) | Resolved | §2 added with QIF, SSE leakage, PPE paragraphs |
| Preliminaries re-derives standard IT defs (MINOR) | Partially resolved | Shortened but still present (lines 301 to 316) |
| Q used for both cipher dist and IT convention (MINOR) | Unresolved | Still uses Q for cipher value distribution |
| "Preserves all correlations" imprecise (MINOR) | Unresolved | Same language in Thm 5.1 |
| Informal convergence arguments (MINOR) | Unresolved | §5.2 still has informal paragraphs |

---

## MAJOR: Abstract and conclusion contradict refined "two-plus-inherited" framing

**Location**: Abstract line 56 to 58; Conclusion lines 1150 to 1158.

**Quoted text (abstract)**:
> "We identify three levers for improving confidentiality, noise
> injection, multiple representations, and encoding granularity, and
> prove how each affects the entropy ratio through the cipher map
> parameters $(\eta, \varepsilon, \delta, \mu)$."

**Quoted text (conclusion)**:
> "Three levers, noise injection, multiple representations, and encoding
> granularity, offer distinct cost/benefit trade-offs for improving $e$,
> all expressible in terms of the cipher map parameters
> $(\eta, \varepsilon, \delta, \mu)$."

**Problem**: The Introduction (lines 102 to 123) and Contributions list
(lines 148 to 163) now correctly say "two constructions we analyze plus
a third we inherit from the cipher maps framework." The Abstract and
Conclusion still use the old "three levers, and prove how each affects"
language, which over-claims by saying the paper proves the granularity
effect (which is actually cited, not proven here).

A reviewer who skims only abstract and conclusion will see an
inconsistent claim relative to §1 and §4.

**Suggestion**: Align the abstract and conclusion with the refined
framing. Proposed abstract fix:
> "We analyze two constructions that reduce $\delta$ with explicit
> costs (noise injection, multiple representations) and use a third
> (encoding granularity) inherited from the cipher maps framework to
> analyze the confidentiality/functionality trade-off."

Conclusion fix:
> "Two constructions we analyze (noise injection, multiple
> representations) and a third we inherit from the cipher maps framework
> (encoding granularity) offer distinct cost/benefit trade-offs..."

---

## MAJOR: The "Pinsker bridge" is introduced without motivating the unit issue

**Location**: Section 3.3, Theorem 3.1 part (3) and proof; also line 99
in Introduction.

**Problem**: The paper says "$e \geq 1 - 2\delta^2/n$, via Pinsker's
inequality," which is a clean formula. But the proof writes $D_{KL}(Q \|
U)$ without specifying bits vs nats, and the Pinsker bound used
($D_{KL} \geq 2 d_{TV}^2$) is the natural-log form. In base-2 logs (the
paper's stated convention), the constant is $2/\ln 2 \approx 2.885$.
Either the bound should be stated in nats throughout or the paper should
explicitly derive the base-2 form.

Beyond the unit issue (see logic-checker for the deeper direction issue),
the prose hides the subtlety. A theory reviewer will check the units in
the Pinsker step; the current text makes the check harder than necessary.

**Suggestion**: Either (a) state "using base-$e$ logs in this proof" and
convert at the end, or (b) write the Pinsker inequality in bits
explicitly: "$d_{TV}(P, Q) \leq \sqrt{(\ln 2 / 2) D_{KL}(P \| Q)}$ when
$D_{KL}$ is measured in bits."

(This is primarily a logic issue, but it surfaces first as a clarity
problem for the prose.)

---

## MAJOR: Related Work QIF paragraph is honest but thin

**Location**: Section 2, lines 184 to 203.

**Observation**: The QIF paragraph concedes the measure to QIF and
claims only the bridge and compositional bound as novel. This is the
right framing. However, the paragraph is 19 lines of dense prose in a
single block, and it does not engage with QIF at the level of
*measures* (min-entropy leakage vs. Shannon leakage vs. g-leakage)
that a QIF-literate reviewer expects.

Specifically, Smith 2009 argues *against* Shannon leakage in favor of
min-entropy leakage on the grounds that Shannon averages over
outcomes and misses worst-case queries. The paper's §7 Limitations
point 1 raises exactly this issue, but §2 Related Work does not
mention it. A QIF reviewer will notice.

**Suggestion**: Split the QIF paragraph into two:
1. First paragraph: state the entropy ratio = normalized Shannon
   leakage, cite Smith, Alvim.
2. Second paragraph: address the Shannon-vs-min-entropy choice, say
   why Shannon is appropriate for this work (e.g., "cipher map systems
   face a distribution-estimation adversary rather than a single-query
   guessing adversary"), and point to §7 Limitation 1 for the caveat.

This doubles the QIF engagement with modest length cost (maybe 10
additional lines) and preemptively addresses the canonical QIF
reviewer objection.

---

## MAJOR: Notation Q is overloaded

**Location**: Throughout, especially §3.3 and §4.

**Problem**: The paper uses $Q$ for the cipher-value distribution. This
conflicts with the textbook IT convention where $Q$ denotes the
reference distribution in $D_{KL}(P \| Q)$. The paper writes
$D_{KL}(Q \| U)$ which forces the reader to mentally re-map $Q$ from
"reference" to "true/observed" and $U$ from "true/observed" to
"reference." This is momentarily jarring.

The prior review (2026-04-09, m3) flagged this. No fix landed.

**Suggestion**: Rename the cipher-value distribution to $P_C$ or
$\Pi$ throughout. This is a global search-and-replace affecting
approximately 20 occurrences; the benefit is consistent notation with
the IT textbook convention.

---

## MAJOR: §5 opening reorder is correct but the transition is abrupt

**Location**: Section 5 opening paragraph, lines 655 to 666.

**Quoted text**:
> "We treat correlation leakage first because it exposes a fundamental
> limit of the constructions in §4: reducing $\delta$ to zero is
> necessary but not sufficient when variables recur."

**Observation**: This sentence is critical to the paper's narrative arc
(it signals the payoff of §5.1). It appears at the *end* of §5's opening
paragraph, after a discussion of two effects. A stronger version puts
this framing *first*:

> "Even when marginal $\delta$-uniformity is achieved by the
> constructions of §4, a fundamental compositional leakage remains:
> shared cipher values evaluated by multiple cipher maps expose the
> joint distribution of latent functions, even under
> Shannon-optimal marginal allocation. We prove this first (§5.1) and
> contextualize it with the inherited FPR compounding result (§5.2)."

This gives the reader the narrative hook before the two-effect
breakdown, which reinforces the paper's compositional novelty claim.

**Suggestion**: Rewrite §5's opening paragraph to lead with the
"marginal $\delta$ is insufficient" framing, then state the two-effect
structure.

---

## MAJOR: The "Why this matters" paragraph (line 720) is the best part of §5.1 and should lead

**Location**: Section 5.1, lines 720 to 728.

**Observation**: The paragraph after Thm 5.1's proof ("Why this
matters...") is crisp, operational, and exactly the takeaway a reviewer
wants. Currently it is buried after a technical proof. A cleaner
structure puts the takeaway up front:

1. Prose explanation (currently "Why this matters").
2. Theorem statement as formalization.
3. Proof.
4. Mitigation paragraph.

**Suggestion**: Reorder §5.1 to lead with the operational takeaway,
then the theorem, then the proof, then mitigations. This matches the
"result-first" style of top theory venues.

---

## MINOR: Some paragraphs read as drafts

**Location**: Section 5.2 subsection "Active probing via Boolean
operations," lines 830 to 865.

**Observation**: This subsection introduces an attack ("given cipher
values $c_1, c_2$, compute AND$(c_1, c_1)$ and check...") and loosely
claims it recovers Boolean equivalence classes over "many such probes."
The number of probes, the assumptions on the adversary's access, and
the rate of recovery are all left qualitative. The subsection reads as
a working note rather than a polished section.

**Suggestion**: Either (a) formalize the active-probing attack into a
lemma with a concrete rate (e.g., "after $O(|C|)$ probes, the adversary
recovers all Boolean equivalence classes with probability 1 - neg"),
or (b) trim to a single paragraph: "active probing via exposed
operations enlarges the reachable orbit; the rate at which the orbit
fills is an open problem."

---

## MINOR: Preliminaries still re-derives standard IT definitions

**Location**: Section 3, lines 301 to 316.

**Observation**: The prior review (2026-04-09, m2) flagged the
re-derivation of Shannon entropy, conditional entropy, mutual
information, and KL divergence as unnecessary at a theory venue. The
current text is somewhat shorter than before but still present. At a
top theory venue the audience knows these.

**Suggestion**: Replace with a single sentence: "We use standard
information-theoretic notation following Cover and Thomas 2006. All
logarithms are base 2."

(Add a `\cite{cover2006elements}` to use the bibliography entry
currently orphan in the .bib.)

---

## MINOR: Limitations section is strong; consider one more bullet

**Location**: Section 7, Limitations, lines 1124 to 1143.

**Observation**: The four limitations listed are honest and useful. A
fifth bullet worth considering, given the Pinsker bridge is the
headline: a note on the *tightness* of the bound. "The
$\delta \to e$ bound is an inequality, not an equality. The actual $e$
for a specific $Q$ may be much higher or much lower than the Pinsker
prediction depending on the shape of $Q - U$."

This preempts a reviewer challenge on whether the bound is useful in
practice.

**Suggestion**: Add Limitation 5.

---

## SUGGESTION: Tighten Introduction's "what this paper does not do" paragraph

**Location**: Lines 171 to 176.

**Observation**: The paragraph says "we do not use ORAM, FHE, or
simulation-based security definitions." This is scope-setting but
reads as defensive. A more constructive framing:

> "The framework is information-theoretic: privacy comes from the
> one-way hash, the totality of $\fhat$, and representation uniformity.
> No computational hardness assumption beyond the hash function is
> invoked, and no access-pattern indistinguishability is claimed."

This says the same thing without listing what's absent.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 5 | Abstract/conclusion contradict 2-plus-1 framing; Pinsker unit issue; QIF paragraph thin on min-entropy; Q notation overloaded; §5 opening and §5.1 ordering |
| Minor | 3 | §5.2 active-probing informal; Prelim re-derivation; add 5th limitation |
| Suggestion | 1 | Tighten "what this paper does not do" |

The 2026-04-12 prose improvements land well: the two-plus-one framing
is clean in §1, the Related Work section is a real improvement, and
the §5 reorder is correct. The residual prose issues are: abstract and
conclusion lag the §1 framing, the QIF paragraph does not go far
enough, and several 2026-04-09 minor issues were not addressed. None
of these are blocking, but an aligned revision would close them
quickly.
