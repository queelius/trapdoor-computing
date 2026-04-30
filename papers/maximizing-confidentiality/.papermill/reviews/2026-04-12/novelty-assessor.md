# Novelty Assessor Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: HIGH

---

## Overall Assessment

The refined thesis (2026-04-12) makes the novelty claim much more honest
than the prior version: it concedes the entropy ratio as QIF-standard,
concedes FPR compounding and encoding granularity as inherited from the
companion paper, and retains only (1) the Pinsker bridge $\delta \to e$
and (2) the compositional leakage bound as the paper's own contributions.
This is a substantial improvement in framing. The QIF and SSE literature
is now engaged in §2 Related Work.

However, the novelty claim now rests almost entirely on two pillars, and
both have issues. Pillar (1), the Pinsker bridge, is a mathematical
derivation, not a conceptual novelty (and per the logic-checker, that
derivation is incorrect). Pillar (2), the compositional leakage bound,
is a genuine contribution but is a fairly direct consequence of
determinism plus a plug-in estimator bound; the insight that "marginal
$\delta$ is insufficient under shared variables" is worth isolating, but
the *quantitative* form (Theorem 5.1 with $O(|Y_1||Y_2|/\xi^2)$ samples)
is standard.

The paper's honest residual novelty is then:
- **Conceptual**: framing $\delta$ as an engineering handle bridging TV
  closeness to Shannon leakage in cipher maps. (Valid, but a framing
  contribution, not a theorem.)
- **Quantitative**: the sample-complexity bound for shared-variable
  joint recovery. (Technically sound given the correct statement, but
  off-the-shelf from learning theory.)
- **Packaging**: the explicit cost/benefit analysis of two constructions
  (noise, multiplicity) expressed in terms of $\delta$-reduction. (A
  legitimate engineering contribution if correct; per logic-checker the
  multiplicity construction is currently stated backwards.)

**Resolution of the 2026-04-09 novelty concerns:**

| Prior concern | Status | Comment |
|---|---|---|
| Entropy ratio = QIF-standard (MAJOR) | Partially resolved | Now acknowledged in §1 and §2. No residual over-claim in abstract, intro, or conclusion. |
| Individual techniques are well-known (MAJOR) | Partially resolved | Bost and Fouque cited; Demertzis et al. cited. Simmons *not* cited for homophonic (gap). |
| Encoding granularity under-developed (MINOR) | Deliberately deferred | Correctly demoted to "inherited" from companion paper. Honest resolution. |

---

## Residual novelty concerns

### MAJOR: Pinsker bridge is a single-line application, not a contribution

**Location**: Abstract line 52 to 66; Introduction "Contributions" #1
line 141 to 146; Theorem 3.1 part (3).

**Problem**: The refined thesis elevates "Pinsker bridge making $\delta$
the operational handle" to the top contribution. But Pinsker's inequality
is a standard result; applying it to bound one distance by another is
not a novel theorem. The *framing* (as an "engineering handle") is
plausible, but the mathematical content is an elementary invocation of a
textbook inequality (Cover and Thomas 2006 §11.6).

Compounding this: per the logic-checker, the Pinsker step as written is
applied in the wrong direction. Even the textbook invocation does not
hold. The claimed bound requires Fannes, which is also textbook and
similarly not a novel result.

**Suggestion**: Either (a) treat the $\delta \to e$ connection as a
*framing remark* (one paragraph in the Introduction, one remark in §3),
*not* a theorem-level contribution; or (b) prove something non-trivial
about the tightness of the bound, the composition behavior (how $\delta$
propagates through chained cipher maps), or the achievability of the
bound under specific constructions. Without such a non-trivial
development, claiming the Pinsker bridge as a headline contribution is
hard to defend to a theory reviewer.

### MAJOR: Theorem 5.1 sample complexity is standard plug-in estimator rate

**Location**: Section 5.1, Theorem 5.1 part (3), lines 691 to 694.

**Problem**: The claim "$N = O(|Y_1| \cdot |Y_2|/\xi^2)$ observations
recover the joint to TV-accuracy $\xi$" is the standard rate for
empirical distribution estimation over a support of size $K = |Y_1|
|Y_2|$. This is covered in any learning-theory textbook and is not a
novel theoretical result. The paper's framing is that this rate applies
*even* to the shared-$c$ regime, which matches the component-wise regime
from Prop 4.3 (also cited as inherited). The **insight** is that
shared-$c$ does not hide the joint, which is valuable, but the
**quantitative bound** has no novel probability content.

The insight is novel as a framing ("marginal $\delta$ is necessary but
not sufficient under shared variables"), but not as a theorem. The
2026-04-12 refinement promotes this to Theorem 5.1 with a formal proof;
the proof is a direct invocation of determinism and plug-in estimator
bounds. This is fine as a proposition but does not warrant theorem
status if the bar for "theorem" is substantive technical novelty.

**Suggestion**: Either (a) keep it as a theorem but add a *lower bound*
counterpart showing the rate is tight (e.g., no estimator does better,
so the bound is information-theoretic, not just statistical); or (b)
downgrade to a proposition with the current proof, and use the prose to
emphasize the *framing* insight.

### MAJOR: Under-claimed novelty: the "two constructions + one inherited" structure obscures the real engineering contribution

**Location**: Introduction, lines 102 to 123; Contributions list, lines 139 to 169.

**Problem**: The refined framing correctly disclaims the granularity
lever as inherited. But in doing so, it under-claims the *synthesis*:
the *explicit cost decomposition* (bandwidth $1+R/N$, space
$\sum K(x)$, functionality cost from granularity) framed as a unified
design space is the paper's most genuinely useful contribution. A
practitioner reading this paper gets a *toolkit* with costs attached,
which is not in QIF (which focuses on measurement), not in SSE (which
uses ad hoc constructions), and not in the cipher-maps framework (which
is the definitional layer).

The current framing presents the toolkit as "we analyze these two
constructions (noise, multiplicity) rigorously." A sharper framing:
"*we assemble the first unified design space for $\delta$-reduction in
cipher maps, with explicit cost functions and a compositional
sufficiency theorem*." This would honestly claim what the paper actually
does beyond the Pinsker invocation.

**Suggestion**: Add a "Design space" paragraph to §1 that positions the
paper as providing the *cost-attached toolkit*, not just the bridge. The
paper could support this with a table: lever, cost type, cost formula,
$\delta$-effect, under what assumptions. Such a table would also make
the inheritance claims easier to audit.

### MINOR: Simmons 1979 is referenced in spirit but not cited in text

**Location**: Section 4.2 (Multiple Representations) and Example 5.

**Problem**: The refined thesis (2026-04-12) states "homophonic cites
Simmons." `simmons1979symmetric` is in references.bib but is not
`\cite`d anywhere in main.tex. The prior review (2026-04-09) did not
flag this explicitly, but given the refinement's own claim, the
execution falls short. Multiple representations is classical homophonic
substitution; the earliest rigorous treatment is Simmons, and §4.2 is
the natural citation point.

**Suggestion**: Add `\cite{simmons1979symmetric}` to §4.2 opening and/or
to Example 5. While the multiplicity construction as stated is actually
backwards (per logic-checker), the *intent* matches Simmons, and the
correct version of the formula is what Simmons described.

### MINOR: The inherited-but-useful FPR compounding section is long relative to its contribution weight

**Location**: Section 5.2 (Error Compounding in Boolean Chains),
lines 755 to 865.

**Observation**: The FPR compounding subsection (§5.2) runs roughly
3 pages, longer than the novel compositional leakage subsection (§5.1)
and longer than the multiplicity construction (§4.2). Most of §5.2 is
interpretive commentary ("Convergence under deep composition," "Active
probing via Boolean operations") rather than a novel theorem.

This is not a novelty problem per se, but it inflates the apparent
size of the paper's compositional contribution while what is *proven*
in §5 is just Thm 5.1. A reviewer counting theorems vs. prose density
may perceive the paper as heavier than its core theoretical content
warrants.

**Suggestion**: Trim §5.2 interpretive paragraphs ("Convergence under
deep composition," "Active probing via Boolean operations") to a single
page. Reserve narrative space for Thm 5.1's framing and its cost
implications.

### SUGGESTION: Min-entropy remark is cheap and valuable

**Location**: Section 7 (Discussion), currently absent.

**Observation**: The 2026-04-12 thesis refinement notes "a one-paragraph
min-entropy remark is cheap; a full bound would require work" and flags
this as "not yet decided." Adding the cheap remark is worth the small
cost: it preemptively addresses the QIF reviewer's first question ("why
Shannon and not min-entropy?") and signals awareness of the standard
debate.

**Suggestion**: Add to §7 Discussion: "The entropy ratio we analyze is
the normalized Shannon leakage; an analogous min-entropy ratio
$e_\infty = H_\infty(Q)/H_\infty(U) = H_\infty(Q)/n$ captures
worst-case leakage. For cipher map systems where the attacker's goal
is to guess a single high-probability query (e.g., a most-searched
term), min-entropy is the natural measure. The Pinsker bridge does not
extend directly to min-entropy (which requires $\ell_\infty$-closeness,
not TV-closeness); the corresponding analogue would require the
stronger property $\max_c |Q(c) - U(c)| \leq \delta_\infty$."

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 3 | Pinsker bridge is a single-line invocation; Thm 5.1 rate is standard plug-in; "two constructions + inherited" obscures real synthesis |
| Minor | 2 | Simmons not cited despite thesis claim; §5.2 length inflates compositional contribution |
| Suggestion | 1 | Add cheap min-entropy remark |

The refined thesis is sharp, honest, and reviewer-defensible in
conception. The execution lands partially: the QIF concession is
explicit and clean; the inherited-vs-proven audit is explicit in the
Introduction and contributions list; but the Simmons citation is missing
and the Pinsker bridge is presented as a theorem when it is more
accurately a framing contribution (whose proof is, in addition,
incorrect per logic-checker).

Net: the paper as written is *honestly positioned* but *thinly
contributing* once the concessions are granted. Unless the Pinsker
bridge is replaced with something substantively novel, or the
compositional bound is extended (tightness, lower bound, composition
beyond two maps), the paper may not clear the novelty bar for a top
theory venue.
