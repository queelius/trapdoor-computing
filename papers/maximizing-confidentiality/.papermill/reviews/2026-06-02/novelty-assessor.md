# Novelty-Assessor Report, Round 5 (2026-06-02)

**Paper**: "The Entropy Ratio" (`main.tex`, 25pp)
**Scope (per area chair):** has the optimal-rate / impossibility framing
changed the novelty calculus, and is it defensible against the two companion
papers' claims? Prior rounds settled the contribution-list ordering and the
two-scale framing.

---

## The optimal-rate reframing strengthens novelty, and is defensible

The headline is now the compositional-leakage **pair**: Thm 5.1 (upper
bound, plug-in rate `O(|Y_1||Y_2|/xi^2)`, MI preservation) plus Thm 5.2
(matching minimax lower bound, "Theta optimal"). In prior rounds the open
weakness M11 was "Thm 5.1's plug-in rate is standard, no matching lower
bound." Thm 5.2 closes M11: the rate is now provably optimal, which lifts the
result from "standard estimation fact applied to cipher maps" to "tight
characterization of the compositional channel." That is a genuine novelty
upgrade, and it is reviewer-defensible: matching upper and lower bounds is
the standard bar for "optimal," and the paper meets it (modulo the Assouad
vs Le Cam naming, which is a labeling fix, not a substance gap; see
logic-checker B2).

**Caveat on how much credit to claim.** The minimax rate
`Theta(m/xi^2)` for distribution estimation in TV is itself classical
(Devroye-Gyorfi-Lugosi). The paper's novelty is not the rate in the abstract
but the *identification* that the cipher-map compositional channel achieves
exactly this rate and that no per-map `delta` moves it. The paper frames this
correctly (intro lines 204 to 220 call it "compositional leakage at the
optimal rate" and credit plug-in/Le Cam for the bounds themselves). It does
not overclaim the minimax machinery as new. Good. Keep that honesty; do not
let a future polish pass inflate "we prove the minimax rate" into "we
discover the minimax rate."

---

## Defensibility against the companion papers (the cross-paper novelty question)

This is the new angle for this round. The spine §8 Paper Map and §4A measures
table assign ownership explicitly. I checked our paper against that boundary.

### N-1 (verify, OK): ownership boundaries are respected

- **Measure C3 (shared-variable joint recovery, Thms 5.1/5.2)** is assigned
  to THIS paper by the spine (§4A.4 table, line 642). Our paper owns it.
  Correct, no encroachment.
- **Measure M1 (entropy ratio / Fannes bridge)** is shared: spine assigns it
  to both this paper (Thm 3.1) and cipher-maps (Prop 5.1). Our paper frames
  the Fannes bridge as contribution #2 and is explicit it is "a normalized
  form of Shannon leakage borrowed from the QIF literature" (abstract,
  intro). It does NOT claim the entropy ratio as novel. Correct.
- **Measure C1 (orbit closure)** belongs to algebraic. Our paper cites it
  (§5.3 active probing, §9 practical depth) and explicitly frames orbit
  closure as the algebraic paper's, measuring "active" confidentiality
  versus our "passive" (§9 lines 1660 to 1668). Correct attribution. (The
  denominator bug is a correctness issue, logic-checker A3, not a novelty
  overreach.)

So the paper does not claim anything the spine assigns elsewhere. The
ownership story is clean.

### N-2 (COMPLETENESS GAP, MEDIUM): §9 practical-depth omits Measure C2 (coincidence oracle)

This is the one place the cross-paper map exposes a gap. The §9
"Practical depth in cipher programs" paragraph (lines 1670 to 1700) builds a
multi-level composition depth budget from three ingredients: FPR compounding
(correctness ceiling), Thm 5.1/5.2 (shared-variable leakage, C3), and orbit
closure (C1). But multi-level composition with **repeated instances of the
same latent f** is governed by **Measure C2 (multi-instance coincidence,
cipher-maps Thm 8.2)**, which the spine §4A.2 (line 617) describes precisely:
`t` cipher maps for the same `f` under independent seeds let a
coincidence-oracle attacker reach accuracy `1 - (1/2) sum_y alpha(y)^t`. A
deep cipher program that re-invokes the same primitive (e.g. the same
membership test at multiple chain levels) is exactly the C2 regime, and the
paragraph does not mention it.

This is a **completeness gap, not an error**: nothing the paragraph says is
wrong, but the depth-budget story is incomplete without C2. A reader who
knows the family will notice that the one compositional measure NOT cited in
the paper's own multi-level-composition discussion is the one that fires when
primitives repeat.

**Fix (recommended).** Add one sentence to the §9 paragraph cross-referencing
C2: e.g. "When a cipher program re-invokes the same primitive across levels,
a third channel opens: the multi-instance coincidence oracle
([Thm.~8.2]{towell2026cipher}) reaches accuracy `1 - (1/2) sum_y alpha(y)^t`
in the instance count `t`, defended by concentrated (Huffman) acceptance
partitions or randomized encoding." This closes the loop, demonstrates
command of the full family, and costs nothing in novelty (it credits
cipher-maps for C2). It also strengthens the paper's "complete framework for
designing, measuring, and improving confidentiality" closing claim
(conclusion line 1801), which currently overpromises slightly by omitting C2.

### N-3 (LOW): the "complete framework" closing claim

The conclusion (line 1798 to 1802) says the theory provides "a complete
framework for designing, measuring, and improving confidentiality." Given the
spine names five measures (M1, M2, C1, C2, C3) and this paper directly treats
M1 and C3 (citing C1, omitting C2), "complete" is a slight overreach for a
single paper. **Fix:** soften to "a framework spanning the marginal and
compositional scales" or add the C2 cross-reference (N-2) so the claim is
backed. Minor.

---

## Is the framing still honest about what is new vs inherited?

Yes. The contribution list (lines 203 to 242) correctly partitions: Thm
5.1/5.2 (ours), Fannes bridge (ours, but the measure is borrowed),
constructions (ours, with granularity inherited), measurement (ours).
Inherited results (FPR compounding, granularity) are flagged "inherited from
the cipher maps framework" each time. The over-attribution issues the
logic-checker found (A1, A2) are the *opposite* failure mode: the paper is if
anything too generous in crediting cipher-maps for results cipher-maps does
not fully state. That is a safer error than claiming inherited work as one's
own, and the fixes (cite the right locus) resolve it.

---

## Summary

| ID | Finding | Severity |
|---|---|---|
| N-2 | §9 depth budget omits Measure C2 (coincidence oracle) cross-reference | MEDIUM (completeness) |
| N-3 | "complete framework" closing claim slightly overreaches | LOW |
| N-1 | ownership boundaries respected | none (positive) |

Novelty is in good shape and improved by the Thm 5.2 addition. The cross-
paper lens surfaces one real completeness gap (N-2): the multi-level-depth
discussion should cite C2, the one compositional measure that fires when
primitives repeat. That single added sentence both closes the gap and
substantiates the "complete framework" claim.
