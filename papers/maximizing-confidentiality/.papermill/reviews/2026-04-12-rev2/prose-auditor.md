# Prose Auditor Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Confidence**: HIGH

---

## Overall Assessment

The Pinsker -> Fannes rename is **propagated cleanly to all major
locations** the user listed, except for two stragglers in the §5
section structure that are highly visible. Specifically, §5's title
("Three Levers for Improving Confidentiality") and §7.4's opening
sentence ("We demonstrate the three levers") are both unchanged from
the morning round. These are the most reader-visible landmarks in the
paper and contradict the abstract / §1 / §1-contributions / §8
"two-plus-inherited" framing.

Theorem 5.1 is now well-stated: the sampling model is explicit, MI
preservation is the Part-2 claim, and Part-4 is a quantitative bound.
The new "Sampling Regimes" remark is well-placed. The new
"Numerical Scale" remark after Thm 3.1 makes the Fannes bound
operationally interpretable.

The new exposition (Numerical Scale remark, Sampling Regimes remark,
case-study comparison paragraph) is uniformly competent. No new prose
problems introduced. Minor carryover issues (Q-notation overload,
Preliminaries IT re-derivation) are unchanged.

---

## Resolution audit

### Morning M8. "Three levers" wording. PARTIALLY RESOLVED

**User's claim in prompt**: "Abstract and Conclusion no longer say
'three levers'; both rewritten to match Intro's 'two-plus-inherited'
framing."

**Verification**:

- **Abstract** (line 47 to 69): "We analyze two constructions that
  reduce $\delta$ with explicit costs (noise injection and multiple
  representations), and inherit a third, encoding granularity, from
  the cipher maps framework." ✓ Resolved.
- **§1 framing** (line 110 to 132): "We analyze two constructions
  that reduce $\delta$ with explicit costs: 1. Noise injection ...
  2. Multiple representations ... A third construction, encoding
  granularity, ... is inherited from the cipher maps framework." ✓
  Resolved.
- **§1 contributions #2** (line 158 to 164): "**Two constructions
  that reduce $\delta$.** ... A third construction, encoding
  granularity, is inherited from the cipher maps framework and used
  without re-proof." ✓ Resolved.
- **§2 Related Work QIF** (line 196 to 215): No "three levers"
  language; uses "the *Fannes bridge*" and "compositional leakage
  bound." ✓ Resolved.
- **§8 Conclusion** (line 1231 to 1265):
  "Two constructions reduce $\delta$ with explicit costs---noise
  injection (bandwidth) and multiple representations with $K(x) \propto
  D(x)$ (space). A third dimension, encoding granularity, is inherited
  from the cipher maps framework. The three together are expressible
  in terms of the cipher map parameters." ✓ Resolved (the residual
  "three together" is acceptable framing -- it counts the levers
  accurately, contrasts with "two constructions we analyze").

**But two stragglers remain**:

#### Straggler 1: §5 section title (line 484)

```latex
\section{Three Levers for Improving Confidentiality}
\label{sec:levers}
```

This is the title of the section that contains noise injection,
multiplicity, and granularity. A reviewer skimming the table of
contents will see "Three Levers" prominently. The intro and
contributions list now disclaim that the third (granularity) is
inherited; the section title still presents the three as
co-equal "levers" the paper analyzes.

**Suggested fix**:
```latex
\section{Constructions for Reducing $\delta$}
\label{sec:levers}
```
or
```latex
\section{Two Constructions and an Inherited Lever}
\label{sec:levers}
```

#### Straggler 2: §7.4 opening sentence (line 1122)

> "We demonstrate the three levers on a system with vocabulary $m =
> 10{,}000$ and Zipf-distributed queries."

This is the first sentence of the case-study subsection, immediately
preceding Table 4. A reviewer reading just the experimental section
will see "the three levers" in the case-study framing.

**Suggested fix**:
> "We demonstrate the two constructions of \S\ref{sec:levers} on a
> system with vocabulary $m = 10{,}000$ and Zipf-distributed queries."

(The case study only varies homophonic and noise; granularity is not
part of Table 4 since the case study doesn't compose multiple cipher
maps.)

**Severity downgrade**: M8 was Major in the morning round; with five
of seven locations corrected and two highly-visible stragglers
remaining, I'd hold this at **Minor (residual)**. The fix is a 30-
second edit and lands cleanly.

### Morning M5 (prose). Pinsker rename propagation. RESOLVED

**Verification of all listed locations**:

- Abstract (line 56 to 58): "via the Fannes-Audenaert continuity
  inequality" ✓
- §1 framing (line 102 to 105): "via the Fannes-Audenaert continuity
  inequality~\cite{fannes1973continuity, audenaert2007sharp}" ✓
- §1 contribution #1 (line 151 to 156): "**Fannes bridge.** ... via
  the Fannes-Audenaert continuity inequality" ✓
- §2 Related Work QIF (line 204 to 207): "the *Fannes bridge*
  connecting the representation-uniformity parameter $\delta$ ... to
  the entropy ratio" ✓
- §8 Conclusion (line 1235 to 1236): "the Fannes bridge: the
  representation-uniformity parameter $\delta$ lower-bounds $e$
  through the Fannes-Audenaert continuity inequality" ✓

The only "Pinsker" mention is the deliberate aside in the proof (line
453 to 455), used to remind the reader why Fannes-Audenaert is the
right tool. This is good defensive exposition.

**Verdict**: Morning M5 (prose-side concern about Pinsker unit issues
and the broader Pinsker-vs-Fannes distinction) is fully addressed.

### Morning M3 / M4 / M5 (logic-checker). Theorem 5.1 rewrite. PROSE-LEVEL CHECK

**Verification of Theorem 5.1 prose** (line 736 to 780):

- **Statement clarity**: The theorem now states all four parts as
  well-defined mathematical claims. Part 1 is a hypothesis re-statement;
  parts 2, 3, 4 are quantitative.
- **Sampling model in statement**: "each $c_i$ is an independent
  in-domain cipher value drawn according to the pushforward of $D$
  under $\enc$ (so the latent pair $(f_1(x), f_2(x))$ is drawn i.i.d.
  from the true joint under $D$)" -- explicit and sufficient.
- **Part 2**: "Mutual information is preserved: $I(\fhat_1(C);
  \fhat_2(C)) = I(f_1(X); f_2(X))$" -- precise, not "preserves all
  correlations."
- **Part 3**: "$N = O(|Y_1|\cdot|Y_2|/\xi^2)$ samples, the standard
  plug-in estimator rate" -- attributed to its rate type.
- **Part 4**: "$\delta_3 \approx 0$ requires reconstructing $\fhat_3$
  with respect to the joint distribution" -- with proof showing
  $\delta_3$ bounded below by $\TV(\text{joint}, \text{prod-of-marginals})$.
  Quantitative.

**Sampling Regimes remark** (line 782 to 790): "A different regime,
in which the same cipher value $c$ is reused across evaluations, does
not yield additional samples of the joint and so has no corresponding
rate." This is the cleanest possible disambiguation; the remark is
well-placed (right after the proof) and succinct.

**Why this matters paragraph** (line 792 to 799): unchanged from
morning; still appears after the proof. The morning prose-auditor
suggested moving this earlier (M-ordering issue). That suggestion was
not adopted; the paragraph stays in its post-proof position. Mild
prose suboptimality but not blocking.

**Verdict**: The Thm 5.1 rewrite is competent prose. The M-ordering
suggestion (operational takeaway -> theorem -> proof -> mitigations)
remains unaddressed but is a stylistic preference not a defect.

### Morning Numerical Scale remark. NEW, GOOD

**Location**: §3.3, immediately after Thm 3.1 proof, line 458 to 463.

> "For $\delta = 0.05$ and $n = 64$, the bound gives $e \geq 0.945$.
> For $\delta = 0.01$, $e \geq 0.989$. The linear scaling in $\delta$
> means tightening $\delta$ by an order of magnitude tightens the
> leakage bound by roughly the same order."

**Assessment**: Good prose. Two concrete data points + a one-sentence
takeaway about scaling. Exactly what a "Numerical Scale" remark
should do. Both numbers verified by independent calculation
(Logic-Checker).

**Mild note**: $n = 64$ is used without context. A casual reader
might wonder whether 64 is bits or bytes or something else.
One-clause clarification would help: "For $\delta = 0.05$ and a
64-bit cipher value ($n = 64$)..." But this is a polish item.

---

## Carry-over open items (severity unchanged)

| Morning finding | Severity (then) | Severity (now) | Note |
|---|---|---|---|
| M2 (Pinsker unit issue) | Major | Resolved | Fannes proof is in bits throughout |
| M3 (QIF paragraph thin on min-entropy) | Major | Open | Still says "discuss Shannon-vs-min-entropy in §7.discussion" but §7 doesn't have such a discussion |
| M4 ($Q$ notation overloaded) | Major | Open | Unchanged |
| M5 (§5 opening / §5.1 ordering) | Major | Open | Unchanged |
| m1 (§5.2 active-probing informal) | Minor | Open | Unchanged |
| m2 (Prelim re-derives IT defs) | Minor | Open | Unchanged |
| m3 (5th limitation on tightness) | Minor | Open | Unchanged |

**Min-entropy promise**: §2 Related Work line 214 to 215 says "We
discuss the Shannon-vs-min-entropy choice in \S\ref{sec:discussion}."
Checking §9 Discussion (renamed from §7 in current numbering, line
1156 onward): no such discussion is present. This is an unfulfilled
forward reference. Either add a paragraph to §9 or remove the forward
reference.

**Severity**: Minor (broken forward reference). Prior morning M12
flagged the missing min-entropy engagement. This is now slightly
worse: the paper *promises* the discussion in §2 but does not
deliver it in §9.

---

## New issue: broken forward reference

### Minor: Promised Shannon-vs-min-entropy discussion missing

**Location**: §2 line 214 to 215; §9 (Discussion) line 1156 onward.

**§2 says**: "We discuss the Shannon-vs-min-entropy choice in
\S\ref{sec:discussion}."

**§9 (Discussion and Open Questions, line 1158 to 1223)** has six
labeled paragraphs:
1. The entropy ratio as a design tool
2. Relationship to the orbit closure
3. Adaptive $K(x)$
4. Tight bounds for composition
5. Beyond Boolean search
6. Limitations (4-bullet list)

None of these address the Shannon-vs-min-entropy question. The
forward reference is unfulfilled.

**Suggestion**: Add a paragraph like the one suggested in the
morning's novelty-assessor:

> **Shannon vs min-entropy.** We adopt Shannon entropy because the
> adversary in our setting estimates a distribution $D$ from many
> observations -- a distribution-estimation rather than single-query
> guessing model. Min-entropy leakage~\cite{smith2009foundations} is
> appropriate when one high-probability query dominates; the analogue
> in our framework would replace TV-closeness ($\delta$) with
> $\ell_\infty$-closeness ($\delta_\infty = \max_c |Q(c) - U(c)|$),
> and the corresponding Fannes-type bound becomes much tighter on
> min-entropy. We focus on Shannon for the present paper.

This closes the forward-reference loop and addresses the morning M12.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 0 | (M-stragglers in §5 title and §7.4 opening downgraded to Minor) |
| Minor | 3 | §5 title still "Three Levers"; §7.4 opening still "the three levers"; broken forward reference (Shannon vs min-entropy in §9) |
| Carry-over open | 5 | $Q$ notation; §5 opening order; §5.1 ordering; §5.2 informal; Prelim IT redefinition |

The afternoon revision lands the major prose changes promised:
- Pinsker -> Fannes rename propagated to all five named locations.
- Three levers -> two-plus-inherited propagated to abstract, intro,
  contributions, conclusion (with two visible stragglers in §5 title
  and §7.4 opening).
- Theorem 5.1 prose tightened (sampling, MI preservation,
  quantitative part 4).
- Numerical Scale remark adds operational meaning.

The paper's prose is in markedly better shape than the morning round.
The remaining issues are: two cosmetic stragglers (§5 title; §7.4
first sentence), one broken forward reference (Shannon-vs-min-entropy),
and the carry-over polish items from the morning. None are blocking.
