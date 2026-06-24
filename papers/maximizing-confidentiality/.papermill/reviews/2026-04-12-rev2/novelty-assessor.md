# Novelty Assessor Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Confidence**: MEDIUM-HIGH

---

## Overall Assessment

The afternoon revision changes the *correctness* of the headline
contributions but not their *substance*: the framing of the paper's
novelty is largely unchanged. The Pinsker -> Fannes rename and the
$K(x) \propto D(x)$ correction make the math right; they do not lift
the contributions from "framing-level" to "substantive new
mathematics."

That said, my morning view of "Pinsker bridge" as a textbook
invocation is somewhat softened: the Fannes-Audenaert continuity
inequality is also textbook (well-known in quantum information theory
since Fannes 1973 and tightened by Audenaert 2007), but its
*application* in a cryptographic / trapdoor-computing setting --
specifically as a translation device from the cipher-map parameter
$\delta$ to the Shannon leakage measure $e$ -- is not standard. The
*framing novelty* (taking the QIF measure $e$ and showing it has a
concrete operational handle in the cipher-map parameter $\delta$) is
genuine; the *mathematical novelty* (one-line application of a
textbook continuity inequality) is small.

The compositional leakage theorem (Thm 5.1) carries more of the
headline weight after this revision. With parts (2), (3), (4) all
made precise (per logic-checker), Thm 5.1 now has four distinct
claims, three quantitative. Of these, parts (2) and (4) are genuinely
informative: MI preservation under shared cipher values is a clean
statement, and the $\delta_3 \geq \TV(\text{joint}, \text{prod})$
lower bound (part 4) is non-trivial.

---

## Resolution audit

### Morning M10. "Fannes bridge" framed as textbook invocation. PARTIALLY RESOLVED

**Status**: The rename and Numerical-Scale remark help but do not
change the underlying issue. The Fannes bridge is still a one-line
application of a known continuity inequality. The numerical remark
($\delta=0.05, n=64 \to e \geq 0.945$) does helpfully convey the
operational meaning of the bound, which strengthens the *framing*
contribution.

**My current view**: With the linear bound (correct), the value
proposition is: "$\delta$ is a small concrete number measurable from
construction parameters, and a 1-percentage-point change in $\delta$
produces a 1-percentage-point change in $e$, in the regime
$\delta \ll 1$." This is the operational handle the QIF literature
does not provide because QIF works with the leakage measure
abstractly, not with a parameter of the construction.

The defensibility-as-headline-contribution argument:
- *In favor*: the bridge connects a structural construction parameter
  ($\delta$) to a standard leakage measure ($e$); this is what makes
  $\delta$ useful as a design knob.
- *Against*: the bridge is one inequality. A theory reviewer will see
  it as plumbing, not a result.

**Severity downgraded slightly**: from clearly Major to "borderline
Major-Suggestion." The numerical-scale remark and explicit citation
of Fannes-Audenaert give the bridge enough texture to be defensible.

**Suggestion (unchanged from morning)**: Either add a tightness
result (Fannes-Audenaert is sharp; the constant $\log_2(d-1)$ is
asymptotically optimal in the relevant scaling) or de-emphasize the
bridge as a *theorem-level* contribution while retaining it as a
*framing* contribution. The paper currently does the latter implicitly
by listing it as "Contribution 1" without major proof depth; a single
sentence acknowledging Fannes-Audenaert is sharp would help.

### Morning M11. Thm 5.1 sample complexity is standard plug-in. STILL OPEN

**Status**: The proof now correctly cites Cover-Thomas 2006 for the
plug-in rate. The rate itself is not a novel probability result. As I
noted in the morning, the *insight* (shared-$c$ does not hide the
joint, even with marginal $\delta$-uniformity) is the genuine
contribution; the *quantitative bound* is standard learning theory.

The afternoon revision did not add a matching lower bound. Without
the lower bound, the result is "the obvious plug-in estimator works,"
not "no estimator can do better."

**Severity unchanged**: Major-as-novelty-concern. Note: this is not a
correctness issue per logic-checker; the rate is correct. It is a
novelty-bar concern.

**Suggestion (unchanged)**: Add a Le-Cam or Fano lower bound showing
$N = \Omega(|Y_1||Y_2|/\xi^2)$ is necessary. This would lift Thm 5.1
from "an upper bound" to "an information-theoretic impossibility."

### Morning concern: Honest framing. RESOLVED

The two-plus-inherited framing (introduced morning) is now consistent
in:
- Abstract (line 60 to 62): "two constructions ... and inherit a third"
- §1 framing (line 110 to 132): "two constructions ... A third
  construction ... is inherited"
- §1 contributions #2 (line 158 to 164): "Two constructions that
  reduce $\delta$ ... A third construction, encoding granularity, is
  inherited"
- §8 Conclusion (line 1237 to 1240): "Two constructions reduce $\delta$
  ... A third dimension, encoding granularity, is inherited"

But (per prose-auditor) **§5 title and §7.4 opening still say "three
levers"**. This is a prose-level inconsistency, not a novelty-claim
issue, but it does undermine the framing if a reviewer skims those
landmarks.

### New consideration: Fannes-Audenaert citation is correct attribution

**Verification of the new bib entries**:
- `fannes1973continuity`: M. Fannes, *A continuity property of the
  entropy density for spin lattice systems*, Comm. Math. Phys. 31(4),
  291-294, 1973. This paper proves the continuity property for von
  Neumann entropy in the quantum setting; it specializes to the
  classical Shannon entropy continuity statement used in the proof.
  Attribution is correct, though the "spin lattice" phrasing of the
  title might surprise a reader expecting a classical-IT reference.
- `audenaert2007sharp`: K. Audenaert, *A sharp continuity estimate for
  the von Neumann entropy*, J. Phys. A 40(28), 8127-8136, 2007.
  Audenaert's paper gives the sharp constant in the Fannes-type bound
  ($t \log_2(d-1) + h_2(t)$ instead of the looser Fannes 1973 form).
  Citing both Fannes and Audenaert is appropriate.

These attributions are correct and conventional in the QIF / quantum
IT literature. A reader familiar with classical IT might expect
Csiszar-Korner (1981) or Petz (2008) instead, but the Fannes-Audenaert
pair is standard.

---

## Compositional leakage as genuine contribution

With the morning M3 to M5 fixes (sampling model specified, MI
preservation explicit, part-4 quantitative), Thm 5.1 reads as four
claims:

| Part | Claim | Novelty |
|---|---|---|
| 1 | Marginals are $\delta$-uniform (hypothesis) | None (definition) |
| 2 | $I(\fhat_1(C); \fhat_2(C)) = I(f_1(X); f_2(X))$ | Modest -- determinism + sampling |
| 3 | $N = O(|Y_1||Y_2|/\xi^2)$ samples for $\xi$-TV joint estimation | Standard plug-in rate |
| 4 | Optimal $\delta_3 \geq \TV(\text{joint}, \text{prod})$ | Modest -- direct from Shannon-optimal predicate analysis |

Of these, part (4) is the most surprising and useful. It says:
"Shannon-optimal acceptance predicates for $\fhat_3$ designed against
the marginal-product distribution cannot achieve $\delta_3 = 0$ under
correlated input." This is a specific, non-obvious lower bound that
practitioners would find informative.

**Net upgrade in my view**: Thm 5.1 part (4) is a contribution worth
defending at a theory venue. It is non-trivial and prescriptive (it
tells the engineer what they cannot do, not just what they could do).

---

## Headline-weight re-assessment

Compared to the morning round, my view is:

- **Fannes bridge**: still a framing contribution; the mathematical
  content is one Fannes-Audenaert application. Numerical-scale remark
  helps. Defensible but not heavyweight.
- **Two constructions analyzed (noise + multiplicity)**: now
  internally correct (per logic-checker). The cost-attached toolkit
  framing is the right framing. Modest engineering contribution.
- **Compositional leakage**: this is now the strongest piece. Parts
  (2), (3), (4) together form a coherent compositional analysis with
  one genuinely informative quantitative claim (part 4).
- **Practical measurement**: compression estimator + Monte-Carlo +
  case study; standard tools, useful packaging.

**Recommendation re ordering**: If headline weight is the question,
the *order* of contributions (Fannes bridge first, compositional
leakage third) under-weights the strongest contribution. The paper
might consider promoting compositional leakage to first contribution
in a future revision. But this is a presentation choice, not a
correctness or novelty defect.

---

## Resolution table (morning -> rev2)

| Morning finding | Severity | Status |
|---|---|---|
| Pinsker bridge as textbook | Major | Partially resolved (rename + numerical scale remark) |
| Thm 5.1 standard plug-in rate | Major | Open (no lower bound) |
| Two-plus-inherited under-claims synthesis | Major | Partially resolved (intro framing better; section heading lags) |
| Simmons not cited | Minor | Resolved (cited at §4.2 line 565) |
| §5.2 length inflates contribution | Minor | Open (unchanged) |
| Min-entropy remark | Suggestion | Open |

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 2 | Fannes bridge depth (defensible but borderline); Thm 5.1 lacks lower bound |
| Minor | 1 | §5.2 length still inflates compositional weight |
| Suggestion | 1 | Add cheap min-entropy remark; consider promoting compositional leakage to first contribution |

The novelty story is now: the paper provides (i) a textbook-application
bridge ($\delta \to e$ via Fannes-Audenaert), supported by a numerical-
scale remark; (ii) a cost-attached design toolkit (noise + multiplicity)
with corrected math; (iii) a four-part compositional leakage theorem,
of which parts (2) and (4) are genuinely informative even if part (3)
is standard. This is a defensible contribution package for a theory
venue, though the headline framing could better foreground (iii) over
(i).

The afternoon fixes did not introduce new novelty issues. They
corrected mathematical errors without affecting the contribution
package. The paper's novelty bar is unchanged from the morning, with
the caveat that the Fannes bridge is now mathematically sound (which
matters for whether the contribution is *real*, even if it does not
change whether it is *substantial*).
