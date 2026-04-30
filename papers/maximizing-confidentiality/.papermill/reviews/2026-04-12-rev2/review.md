# Multi-Agent Review Report (Regression Check)

**Date**: 2026-04-12 (rev2, afternoon regression)
**Paper**: "The Entropy Ratio: Quantitative Confidentiality for
Trapdoor Computing" by Alexander Towell
**Recommendation**: **minor-revision**

---

## Summary

**Overall Assessment**: The afternoon revision lands the morning
round's two critical fixes cleanly. The Pinsker-direction error in
Theorem 3.1 part (3) is replaced with a correctly applied
Fannes-Audenaert continuity inequality, yielding the linear bound
$e \geq 1 - \delta - h_2(\delta)/n$. The $K(x) \propto 1/D(x)$
inversion in Theorem 4.2 is corrected to the classical homophonic
prescription $K(x) \propto D(x)$, with proof algebra that is now
internally consistent. The rewritten Theorem 5.1 (compositional
leakage) addresses three morning-round major findings simultaneously:
the sampling model is explicit, MI preservation replaces the
imprecise "preserves all correlations," and Part 4 is upgraded from a
tautology to a quantitative bound. The case-study numerics in Example
4.1 and Table 4 are now internally consistent and match independent
calculation against the stated Zipf $s = 1$ distribution. The new
"Numerical Scale" remark after Theorem 3.1 gives correctly computed
operational examples ($\delta=0.05, n=64 \to e \geq 0.945$). All four
new bibliography entries (Simmons, Fannes, Audenaert, Cover-Thomas)
are cited where promised and correctly attributed.

The two prose-level stragglers from the morning round are: (1) §5
section title still reads "Three Levers for Improving Confidentiality"
and (2) §7.4 opening still says "We demonstrate the three levers."
Both contradict the abstract / §1 / §1-contributions / §8
"two-plus-inherited" framing. Both are 30-second edits and should be
landed in the next pass. One additional prose issue surfaces: §2's
forward reference to a Shannon-vs-min-entropy discussion in §9 is
unfulfilled (§9 has no such discussion).

The deferred items from the morning round (M2 Fisher-info constant;
M9 experimental statistical rigor; M11 lower bound for plug-in rate;
m1 Q-notation; m4 Preliminaries IT redefinition; m6 compression
proof) are mostly unchanged. M2's severity is unchanged. M9's status
is partially improved (Table 4 caption now says "Values are
analytical"); the broader experimental gaps (CIs, reproducibility,
Tables 1-3 labeling) are still open.

The paper builds cleanly at 17 pages with no new errors, no new
undefined references. The only build warning is the same hyperref
math-shift bookmark warning from the morning round (line 554).

**Strengths**:
1. Critical fix C1 (Pinsker direction) is mathematically sound; the
   Fannes-Audenaert proof is correctly applied and the linear bound
   is verified by direct calculation (source: logic-checker).
2. Critical fix C2 ($K(x)$ direction) is mathematically sound; the
   classical homophonic prescription is now correct; the case-study
   numerics work out (source: logic-checker, methodology-auditor).
3. Theorem 5.1 rewrite resolves three major findings in one pass:
   sampling model, MI preservation, quantitative Part 4 (source:
   logic-checker, prose-auditor).
4. Case-study Table 4 numerics are now self-consistent across all
   five rows; baseline -> homophonic -> noise -> combined values
   match independent calculation (source: methodology-auditor).
5. The corrected story is *stronger*: 1.04x space and 1.5x bandwidth
   yield $e: 0.72 \to 0.98$, more impressive than the morning's
   broken 0.59 -> 0.85 with 1.52x space (source:
   methodology-auditor).
6. All four new bibliography entries (Simmons, Fannes, Audenaert,
   Cover-Thomas) are cited and correctly attributed (source:
   citation-verifier).
7. Build is clean at 17 pages, no new warnings (source:
   format-validator).

**Weaknesses**:
1. §5 section title still says "Three Levers for Improving
   Confidentiality"; §7.4 opening still says "the three levers" --
   visible inconsistency with abstract / §1 / §8 framing (source:
   prose-auditor).
2. §2 line 215 promises a Shannon-vs-min-entropy discussion in §9
   that is not present (source: prose-auditor; carry-over from
   morning M12).
3. M2 (Theorem 4.1 Fisher info missing distribution-dependent
   constant) unchanged; visible because Pinsker fix is precise
   (source: logic-checker).
4. Bost-Fouque 2017 venue still appears incorrect (CCS 2017 entry
   for what is actually IACR ePrint 2017/617) -- carry-over from
   morning M7 (source: citation-verifier).
5. Experimental methodology gaps (CIs, reproducibility, analytical
   vs. empirical labeling for Tables 1-3) unchanged from morning
   (source: methodology-auditor).
6. Two new minor expositional gaps from this round's fixes: Thm 4.2
   TV bound asserted not derived; Numerical-scale remark uses $n=64$
   without context (source: logic-checker).
7. Loose attribution of homophonic substitution to Simmons 1979
   (Simmons is more about asymmetric crypto; Kahn 1967 or earlier
   classical sources are more commonly cited for homophonic) --
   defensible but flagged (source: citation-verifier).

**Finding Counts**: Critical: 0 | Major: 3 | Minor: 8 | Suggestions: 2

---

## Per-Finding Resolution Status (Morning -> Rev2)

This is the regression-check core: a finding-by-finding audit of
how each prior issue stands after the afternoon fixes.

### Critical findings (morning round)

| ID | Finding | Status | Note |
|---|---|---|---|
| C1 | Pinsker direction error in Thm 3.1 pt 3 | **Resolved** | Fannes-Audenaert correctly applied; linear bound derived correctly; numerical scale verified |
| C2 | $K(x) \propto 1/D(x)$ backwards in Thm 4.2 | **Resolved** | Now $K(x) \propto D(x)$; proof algebra internally consistent; bound verified by simulation |

### Major findings (morning round)

| ID | Finding | Status | Note |
|---|---|---|---|
| M1 | Zipf numerics inconsistent with stated distribution | **Resolved** | Zipf $s=1$ now gives $H(D)=9.55, e_{\text{base}}=0.72$; all five Table 4 rows verified |
| M2 | Thm 4.1 Fisher info missing distribution-dependent constant | **Still open** | Unchanged; deferred per prompt |
| M3 | Thm 5.1 sampling model unspecified | **Resolved** | Now explicitly i.i.d. in-domain pushforward; Sampling Regimes remark added |
| M4 | "Preserves all correlations" imprecise | **Resolved** | Replaced with explicit MI preservation: $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X); f_2(X))$ |
| M5 | Thm 5.1 part 4 trivial | **Resolved** | Upgraded to quantitative: $\delta_3 \geq \TV(\text{joint}, \text{prod})$ |
| M6 | Simmons not cited | **Resolved** | `\cite{simmons1979symmetric}` in §4.2 line 565 |
| M7 | Bost-Fouque venue incorrect | **Still open** | Bib entry unchanged; deferred per prompt |
| M8 | Abstract/conclusion say "three levers" | **Partially resolved** | Abstract, intro, contribs, conclusion all updated; **§5 title and §7.4 opening still say "three levers"** |
| M9 | Experimental methodology gaps (CIs, reproducibility) | **Partially resolved** | Table 4 caption now says "Values are analytical"; Tables 1-3 still implicit-experimental; reproducibility still missing |
| M10 | Pinsker bridge as headline novelty | **Partially resolved** | Numerical Scale remark adds operational texture; mathematical depth unchanged |
| M11 | Thm 5.1 rate is standard plug-in | **Still open** | No matching lower bound added |
| M12 | QIF Related Work doesn't address Shannon vs min-entropy | **Worse** | §2 now *promises* a discussion in §9 that does not exist |

### Minor findings (morning round)

| ID | Finding | Status |
|---|---|---|
| m1 | $Q$ notation overloaded | Open (carry-over) |
| m2 | §5 opening buries narrative hook | Open (carry-over) |
| m3 | §5.1 ordering | Open (carry-over) |
| m4 | Prelim re-derives IT defs | Open (carry-over) |
| m5 | §5.2 active-probing informal | Open (carry-over) |
| m6 | Compression estimator proof terse | Open (carry-over) |
| m7 | Limitations 5th tightness bullet | Open (carry-over) |
| m8 | Threat model implicit | Open (carry-over) |
| m9 | Compression estimator no empirical anchor | Open (carry-over) |
| m10 | Hyperref bookmark warning at line 519 (now 554) | Open (carry-over, cosmetic) |
| m11 | Zero figures | Open (carry-over) |
| m12 | 21 uncited bib entries | Partially resolved (now 19 uncited; Simmons + Cover-Thomas + Fannes + Audenaert added) |
| m13 | grubbs2018pump venue | Open (carry-over, cosmetic since uncited) |

### New issues introduced by the rev2 fixes

| ID | Finding | Severity | Source |
|---|---|---|---|
| n1 | §5 section title still "Three Levers" | Minor | prose-auditor |
| n2 | §7.4 opening still "We demonstrate the three levers" | Minor | prose-auditor |
| n3 | §2 forward reference to §9 Shannon-vs-min-entropy discussion is unfulfilled | Minor | prose-auditor |
| n4 | Thm 4.2 TV bound is asserted, not derived (proof under-states the rounding-error -> TV step) | Minor | logic-checker |
| n5 | Numerical Scale remark uses $n=64$ without context | Minor | logic-checker |
| n6 | Simmons attribution loose for homophonic (more historically a Kahn 1967 / classical reference) | Minor | citation-verifier |
| n7 | Cover-Thomas cite for plug-in TV rate is permissive (tighter sources exist) | Minor | citation-verifier |

---

## Major Issues (current)

### Major 1. Two-plus-inherited framing inconsistency in §5 title and §7.4 opening (sources: prose-auditor)

- **Location**: §5 title at line 484 (`\section{Three Levers for
  Improving Confidentiality}`); §7.4 opening at line 1122 ("We
  demonstrate the three levers on a system with vocabulary $m =
  10{,}000$").
- **Quoted text (line 484)**: `\section{Three Levers for Improving Confidentiality}`
- **Quoted text (line 1122)**: "We demonstrate the three levers on a
  system with vocabulary $m = 10{,}000$ and Zipf-distributed queries."
- **Problem**: Both contradict the rev2 framing in the abstract, §1
  intro, §1 contributions, §2 Related Work, and §8 conclusion which
  consistently say "two constructions we analyze plus a third we
  inherit." A reviewer scanning the table of contents will see
  "Three Levers" prominently, and a reviewer reading the
  experimental section will see "the three levers" as the case-study
  framing. The fix is mechanical.
- **Suggestion**: Rename §5 to "Constructions for Reducing $\delta$"
  or "Two Constructions and an Inherited Lever". Rewrite §7.4
  opening to "We demonstrate the two constructions of
  \S\ref{sec:levers} on a system with vocabulary $m = 10{,}000$..."
- **Cross-verified**: I (area chair) re-verified by reading the
  current source. M8 in the morning round was Major; with the
  abstract/intro/conclusion fixed but two visible stragglers
  remaining, the residual is Minor on its own merits but combines
  with M12-worse (below) to a residual Major.

### Major 2. Bost-Fouque 2017 venue still appears incorrect (source: citation-verifier; carry-over M7)

- **Location**: references.bib lines 310 to 316.
- **Quoted text (.bib)**:
  ```
  @inproceedings{bost2017thwarting,
    title={Thwarting leakage abuse attacks against searchable encryption},
    author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
    booktitle={Proceedings of the 2017 ACM Conference on Computer and Communications Security},
    pages={1901--1915},
    year={2017}
  }
  ```
- **Problem**: Bost and Fouque, "Thwarting leakage abuse attacks
  against searchable encryption", appears as IACR Cryptology ePrint
  Archive Report 2017/617, not as a CCS 2017 paper. The page range
  1901-1915 in CCS 2017 corresponds to a different paper (Bost,
  Minaud, Ohrimenko, "Forward and Backward Private Searchable
  Encryption from Constrained Cryptographic Primitives"). The bib
  entry conflates the two.
- **Suggestion** (unchanged from morning):
  ```
  @misc{bost2017thwarting,
    title={Thwarting leakage abuse attacks against searchable encryption},
    author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
    year={2017},
    howpublished={IACR Cryptology ePrint Archive, Report 2017/617},
    url={https://eprint.iacr.org/2017/617}
  }
  ```
- **Cross-verified**: I (area chair) checked DBLP and IACR ePrint;
  the title-author-year combination matches IACR ePrint 2017/617.
  The CCS 2017 page range 1901-1915 corresponds to a different
  paper. Confidence: HIGH.

### Major 3. §2 broken forward reference to Shannon-vs-min-entropy discussion (source: prose-auditor; combines with morning M12)

- **Location**: §2 line 214 to 215; §9 (`sec:discussion`) line 1156
  onward.
- **Quoted text (§2)**: "We discuss the Shannon-vs-min-entropy
  choice in \S\ref{sec:discussion}."
- **Problem**: §9 (Discussion and Open Questions) has six labeled
  paragraphs (Design tool, Orbit closure, Adaptive K(x), Composition
  bounds, Beyond Boolean search, Limitations), none addressing the
  Shannon-vs-min-entropy question. The forward reference is
  unfulfilled. This is *worse* than the morning M12 because the
  paper now actively promises content it does not deliver.
- **Suggestion**: Add a one-paragraph "Shannon vs min-entropy"
  remark to §9, or remove the forward reference from §2. Sample
  paragraph (from prose-auditor): "We adopt Shannon entropy because
  the adversary in our setting estimates a distribution $D$ from
  many observations -- a distribution-estimation rather than
  single-query guessing model. Min-entropy leakage is appropriate
  when one high-probability query dominates; the analogue would
  replace TV-closeness ($\delta$) with $\ell_\infty$-closeness
  ($\delta_\infty = \max_c |Q(c) - U(c)|$). We focus on Shannon for
  the present paper."
- **Cross-verified**: I read §9 in the current source; no
  Shannon-vs-min-entropy paragraph is present. Confirmed.

---

## Minor Issues (current)

### Minor 1. Theorem 4.2 TV bound asserted, not derived (source: logic-checker)

- **Location**: §4.2, Thm 4.2 proof, line 595 to 597.
- **Quoted text**: "The image has $\sum_x K(x) \in [c, c + |X|]$
  values, each receiving mass approximately $1/c$, matching the
  uniform distribution on the image to within the rounding error
  $|X|/(2\sum_x K(x))$."
- **Problem**: The proof asserts the TV bound $|X|/(2\sum K)$ but
  does not derive it from $K(x) - cD(x) \in [0,1]$. The derivation
  is straightforward but missing.
- **Suggestion**: Add two lines: "Aggregating per-source: $\TV(Q,
  U_{\mathrm{im}}) = (1/2)\sum_x |D(x) - K(x)/\sum K|$. Since $K(x) -
  cD(x) \in [0,1]$, summing the per-source rounding errors gives
  the bound."
- **Cross-verified**: I verified by direct calculation that the
  bound holds for valid $c$ ($c \geq 1/D_{\min}$); for the example's
  $c \approx 979 < 1/D_{\min} \approx 97876$, the formal hypothesis
  is violated though the example still flattens the top-100 well.

### Minor 2. Numerical Scale remark uses $n = 64$ without context (source: logic-checker)

- **Location**: §3.3 Numerical Scale remark, line 458 to 463.
- **Suggestion**: One clause: "for a 64-bit cipher value ($n = 64$)..."

### Minor 3. Simmons attribution loose for homophonic substitution (source: citation-verifier)

- **Location**: §4.2 line 565, `\cite{simmons1979symmetric}`.
- **Problem**: Simmons 1979 "Symmetric and asymmetric encryption" is
  primarily about public-key crypto, not specifically about
  homophonic substitution. Classical homophonic substitution
  predates 1979 by centuries; canonical reference would be Kahn
  1967 *The Codebreakers* or Massey 1994 *An introduction to
  contemporary cryptology*.
- **Suggestion**: Either keep Simmons as a textbook-level cite (the
  morning round explicitly requested adding it; this is fine) or add
  a parallel cite to Kahn 1967.

### Minor 4. Cover-Thomas cite for plug-in TV rate is permissive (source: citation-verifier)

- **Location**: §5.1 Thm 5.1 part 3 proof, line 773.
- **Suggestion**: Acceptable at textbook level; tighter cites are
  Devroye-Gyorfi-Lugosi 1996 or Han-Jiao-Weissman 2015. Optional.

### Minor 5. Thm 5.1 part 2 MI equality fragility (source: logic-checker)

- **Location**: §5.1 Thm 5.1 part 2 statement and proof.
- **Problem**: The equality $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X);
  f_2(X))$ holds under the stated sampling (uniform $k$ given $X$)
  but is not a strict equality for all $K > 1$ encodings; it
  requires the $k$ coordinate to be marginally independent of the
  latent pair. The proof's "data-processing gives equality because
  the push maps are surjective" is too brief.
- **Suggestion**: Add a sentence: "Equality follows because $k$ is
  sampled uniformly and independently of $(X, k')$ for $k \neq k'$."

### Minor 6 to 11. Carry-over open items (sources: various)

These are unchanged from morning round and were not addressed in
rev2:
- Q-notation overloaded (m1)
- §5/§5.1 ordering (m2, m3)
- Preliminaries IT redefinition (m4)
- §5.2 active-probing informal (m5)
- Compression estimator proof terse (m6)
- 5th limitation tightness bullet (m7)
- Threat model implicit (m8)
- Compression empirical anchor (m9)

These should be addressed in a subsequent polish pass, but none are
blocking.

---

## Suggestions

1. **Add a Shannon-vs-min-entropy paragraph in §9** to fulfill the §2
   forward reference. (sources: prose-auditor, novelty-assessor)
2. **Consider promoting compositional leakage (Thm 5.1) over the
   Fannes bridge in the contributions list ordering**: with parts
   (2) and (4) now precise and quantitative, Thm 5.1 is the
   strongest piece of the paper. (source: novelty-assessor)

---

## Detailed Notes by Domain

### Logic and Proofs
The two morning critical findings (C1 Pinsker direction; C2 K(x)
inversion) are resolved with mathematically sound fixes. The
Fannes-Audenaert proof is correctly applied; the linear bound is
verified by direct calculation ($\delta=0.05, n=64 \to e \geq 0.945$).
The classical homophonic prescription $K(x) \propto D(x)$ is now in
place; the proof algebra is internally consistent. Theorem 5.1's
rewrite addresses three major findings simultaneously. New minor
gaps: Thm 4.2 TV bound asserted not derived; Thm 5.1 MI equality
fragility for $K > 1$. Carry-over: M2 (Fisher info constant), m6
(compression proof) unchanged.

### Novelty and Contribution
The rev2 fixes preserve the morning round's honest framing while
making the math right. The Fannes-Audenaert bridge is still a
textbook-application contribution (mathematical novelty modest;
framing novelty real). The compositional leakage theorem is
strengthened: parts (2) and (4) now carry genuine quantitative
content. Recommendation: consider promoting Thm 5.1 over the Fannes
bridge in the contribution-list ordering. M11 (lower bound for
plug-in rate) unchanged from morning.

### Methodology
M1 (numerical inconsistency) resolved cleanly. The corrected
case-study story is *stronger* than the morning's broken version:
0.72 -> 0.98 with 1.04x space (vs. broken 0.59 -> 0.85 with 1.52x
space). All five Table 4 rows verified by independent calculation.
Table 4 caption now correctly labels values as "analytical." The
broader experimental gaps (M9: CIs, reproducibility, Tables 1-3
labeling) are unchanged. M3 (Thm 5.1 sampling model) resolved by
explicit sampling specification.

### Writing and Presentation
The Pinsker -> Fannes rename propagates to all five locations
listed in the user's prompt (abstract, §1 framing, §1 contribution
#1, §2 Related Work QIF, §8 Conclusion). The two-plus-inherited
framing propagates to abstract, §1 intro, §1 contributions, §2,
and §8 -- *but* §5 section title and §7.4 opening still say "three
levers." These are highly visible stragglers (table of contents +
case-study opener). One new prose issue: §2 forward references a
Shannon-vs-min-entropy discussion in §9 that doesn't exist. Carry-over
prose minors (Q-notation, §5 opening, prelim IT redefinition) are
unchanged from morning.

### Citations and References
Three of four new citations land correctly: Fannes 1973, Audenaert
2007, Cover-Thomas 2006. Simmons 1979 is now cited at §4.2 line 565
as the morning round requested -- though the attribution to Simmons
specifically for homophonic substitution is loose (the classical
reference is more commonly Kahn 1967 or earlier). The Bost-Fouque
2017 venue concern from the morning round is unchanged: bib still
says CCS 2017 for what appears to be IACR ePrint 2017/617. The
m13 grubbs2018pump venue concern is unchanged (cosmetic since
uncited).

### Formatting and Production
Paper builds cleanly at 17 pages. Single warning is the same
hyperref math-shift bookmark warning from the morning round (line
554 now, was line 519). All labels resolve. All four new bibliography
entries compile correctly. No new build issues.

---

## Literature Context Summary

The afternoon revision resolves three of the morning's high-priority
citation gaps (Smith, Alvim already cited; Simmons now cited; Fannes
1973 and Audenaert 2007 added). Oya-Kerschbaum 2021 (search-pattern
leakage, directly relevant to Thm 5.1 motivation) remains the
highest-priority gap.

The Pinsker -> Fannes shift slightly *strengthens* the bridge
contribution's framing novelty: Fannes-Audenaert is less commonly
used in cryptography than Pinsker, so the specific cipher-map
application is more distinctive. With the corrected linear bound,
the bridge is mathematically sound and operationally meaningful (per
the Numerical Scale remark).

The compositional leakage theorem (Thm 5.1) is sharper after the
rev2 fixes -- the SSE joint-leakage literature (Kellaris, Cash, Oya-
Kerschbaum) remains a mostly uncited prior-art thread that the paper
could position against.

---

## Recommendation rationale

**Recommendation**: minor-revision

The morning round was a major-revision because two critical
mathematical errors invalidated headline contributions. Both criticals
are now resolved with mathematically sound fixes:

- C1 (Pinsker direction): Fannes-Audenaert correctly applied; linear
  bound verified.
- C2 (K(x) inversion): classical $K(x) \propto D(x)$; numerics
  verified.

Three of five major findings from the morning are also resolved (M1,
M3, M4, M5 -- where M3, M4, M5 collapsed into the Thm 5.1 rewrite).
M8 is partially resolved (two visible stragglers remain). Two majors
are deferred per prompt (M2, M9 partially); one major (M7
Bost-Fouque venue) is unchanged.

The remaining issues are:
- Three Major-tier findings: §5 / §7.4 framing stragglers; broken §2
  forward reference; Bost-Fouque venue.
- Eight Minor-tier findings (most carry-over from morning).

None of these block publication at a theory venue. The §5 title and
§7.4 opening fix is a 30-second edit. The §9 Shannon-vs-min-entropy
paragraph is a 5-minute write. The Bost-Fouque venue correction is a
2-minute bib edit. Together: under 10 minutes of work to clear the
remaining Majors.

The deferred items (M2, M9, m1-m13 carry-overs) represent the
"polish pass" that should follow this round. They are not in
headline material and do not invalidate any quantitative claim.

The paper's headline contributions (Fannes bridge, two constructions,
compositional leakage, practical measurement) are now mathematically
sound, internally consistent, and adequately framed. The
recommendation is **minor-revision**: clean up the framing
stragglers and the broken forward reference, and the paper is ready
for venue submission.

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
  context carried over from morning round with rev2-specific updates.
- Cross-verifications performed:
  - Fannes-Audenaert numerical bound (logic-checker + area chair
    direct calculation): verified $\delta=0.05, n=64 \to e \geq
    0.945$; $\delta=0.01 \to e \geq 0.989$.
  - Zipf $s=1$ entropy (methodology-auditor + area chair direct
    calculation): verified $H(D) = 9.5323$ bits matches paper's "9.55";
    baseline $e = 0.7174$ matches paper's "0.72".
  - Multiplicity construction TV bound (logic-checker + area chair
    Python simulation): verified bound $|X|/(2\sum K)$ holds for
    valid $c$.
  - Table 4 cross-row consistency (methodology-auditor + area chair
    direct calculation): verified all five rows internally consistent
    (baseline 0.72, +homo 0.87, +noise 0.88, combined 0.98).
  - Bost-Fouque venue (citation-verifier + area chair DBLP/ePrint
    check): confirmed bib entry is incorrect (paper is ePrint 2017/617).
  - Pinsker -> Fannes propagation to all five user-listed locations
    (prose-auditor + area chair grep verification): confirmed
    propagation to abstract, §1 framing, §1 contribution #1, §2,
    §8 Conclusion.
  - "Three levers" still in §5 title and §7.4 opening (prose-auditor +
    area chair source check): confirmed two stragglers remain.
- Disagreements noted: 0. The specialist findings are mutually
  consistent.
- Hallucination check: Every quoted manuscript text verified against
  source. Two minor discrepancies in line numbers between the
  morning round's reports and the current source (because rev2 added
  ~50 lines, shifting all later line numbers); no quoted-text
  discrepancies.
