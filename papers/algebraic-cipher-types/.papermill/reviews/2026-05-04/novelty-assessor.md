# Novelty Assessor Report

**Date**: 2026-05-04 (cross-paper-informed)
**Reviewer role**: Contribution clarity, differentiation, significance.
**This round**: judge (1) whether the restored algebraic frame is a genuine contribution or a re-packaging; (2) whether Prop 4.4/4.5 add novelty; (3) the positioning of ACT's orbit-closure bound against the foundation's existing confidentiality machinery (the cross-paper overlap question).

## Is the algebraic frame a real contribution?

Yes, with one honest qualification. The 2026-05-04 refinement (algebra primary; sum-impossibility demoted from headline to one-of-three) is a *framing* change, not new theorems -- except for Prop 4.4 and Prop 4.5, which are new. The framing change is nonetheless a real improvement in contribution clarity: the title has always been "Algebraic Cipher Types," and the prior rounds had let the paper under-deliver the algebra. The "one algebra, universal granularity knob (joint vs component-wise), three constructor-specific costs, sum categorically different" structure is now coherent and is the right organizing claim for this paper. The cipher-type algebra over the trapdoor-computing paradigm has **no direct prior occurrence** -- the paradigm itself is distinctive enough that this is new territory (confirmed against SSE, QIF, FE, and IFC literature; see literature-context).

### Prop 4.4 (cipher exponential = cipher map abstraction)
Honest identity claim. Novel *framing* within trapdoor computing ("the algebra closes back on itself"), but unsurprising under a categorical lens, and the proof is definitional. Its contribution is conceptual closure of the algebra, not a hard result. **Concur with the 2026-05-23 suggestion**: either downgrade to a Remark/Definition-by-correspondence, or keep as a Proposition but trim the Proof block to a one-line "immediate from Def 3.1 + the four properties." As-is it is not *wrong*, just slightly oversold. Minor (presentation).

Cross-paper: the foundation does NOT frame cipher maps as exponential types (verified -- no exponential-type framing anywhere in `cipher_maps.tex`; the functorial shorthand it does have is deferred to rekeying work). So Prop 4.4 is legitimately ACT's framing, and its generic citation to the foundation does not over-claim. Good.

### Prop 4.5 (exponential confidentiality trade-off)
This is the more substantive of the two new propositions and earns its place: it shows the universal granularity knob is not vacuous on exponentials (joint product cipher map hides the computation pattern at O(|A|.|C|) cost; component-wise reveals which functions run). It connects cleanly to Prop 4.1 (the part-(2) asymmetry "is itself an instance of joint product encoding"). This makes the "universal knob" claim of §4.5 land. Genuine, if modest, contribution.

## The cross-paper positioning question (the important one)

**Does ACT adequately position its orbit-closure bound (Thm 5.3) against the foundation's own confidentiality machinery?**

The foundation has substantial confidentiality machinery that ACT does not engage:
- Foundation **Prop 5.1** (`prop:confidentiality`): entropy ratio `e = H(Q)/n >= 1 - delta - h_2(delta)/n` via Fannes-Audenaert (cipher_maps.tex:808).
- Foundation **§8.2 Compositional Leakage** + **§8.3 Multi-Instance**: includes the "Coincidence-oracle accuracy" theorem (Thm 8.2, `thm:coincidence-oracle`, cipher_maps.tex:1789ff), which bounds an adversary that counts collisions/coincidences across instances.

ACT cites the foundation only for the *granularity principle* (§8.1), never for Prop 5.1 or the §8.2-8.3 leakage analysis.

**My assessment: the orbit-closure bound is genuinely distinct, but the paper does not say so, and that silence is a (minor) positioning gap.** The distinctness, verified:
- Foundation's entropy ratio is about the **marginal cipher-value distribution** (a delta / representation-uniformity quantity): how uniform the stream of opaque bit strings looks. It is a *passive-observation* measure.
- Foundation's coincidence-oracle is about **collision-counting across instances**: how often two encodings coincide.
- ACT's orbit closure is about **reachability under composition**: how many distinct cipher values an adversary can *produce* by feeding cipher-map outputs back as inputs. It is an *active-probing* measure (the paper's Remark 5.x on active probing makes this explicit).

These three measure different things. ACT's bound is not a re-derivation of, and is not derivable from, Foundation Prop 5.1 or Thm 8.2. So there is **no novelty-threatening overlap** -- ACT's orbit-closure is its own contribution. BUT: a reader who knows the foundation (and the foundation's author is the likely reviewer) will wonder whether ACT is aware of foundation §5/§8.2-8.3, because ACT introduces "a confidentiality bound" as if the foundation had none. Recommend ACT add one or two sentences (in §5.3 or the Discussion "Relationship to cipher maps" paragraph, ACT:1549) explicitly stating: the foundation's Prop 5.1 bounds marginal leakage via delta; the sibling maxconf paper owns the entropy-ratio framework; the coincidence-oracle (foundation §8.3) bounds cross-instance collision leakage; and ACT's orbit bound is the complementary *reachability-under-composition* measure for an actively-probing untrusted machine. This converts a silence into a crisp three-way division of labor and forecloses the "are they aware of their own §8?" objection.

**Three-paper coherence (cipher-maps delta-bound / maxconf entropy-ratio / ACT orbit-closure):** I checked whether ACT's §5.3 conflicts with the entropy-ratio framework that ACT's own state.md says maxconf owns. It does not. ACT's §5.3 is orbit-size reachability, expressed as H(X|view) >= H(X) - log2|orbit|; the entropy ratio H(Q)/n never appears in ACT. There is no duplication. The only risk is the *appearance* of a competing "confidentiality bound" without a pointer; the one-sentence positioning fix above resolves it. (I did not read maxconf in full; based on the foundation's citations to maxconf [§4] for the entropy-ratio proof, the division of labor is clear enough.)

## Sum-type vs implicit-flow differentiation (carry-over from 2026-05-23 MIN)
Still worth sharpening. §2 (158-166) and the §4.3 lead-in acknowledge the implicit-flow connection (Sabelfeld-Myers 2003) but a careless reviewer could read Thm 4.2 as implicit-flow rebranded. Add: IFC rejects at compile time (yes/no), cipher-types quantifies at the encoding level with a continuous joint/component-wise knob. The paper already says the first half; make the "continuous knob vs binary decision" contrast explicit. Minor.

## Contribution-list alignment
The four-contribution structure (§1, 100-140) aligns with abstract, body, and conclusion. Contribution 1 (algebra) now matches the restored framing. Contribution 2 (uniform bound) correctly states the entropy form H(X|V_F(c)) >= H(X) - log2|orbit_F(c)| identical to Thm 5.3 and the abstract -- consistent (the proof gap is a logic finding, not a consistency finding; the *statement* is uniform across abstract/intro/Thm 5.3/conclusion). Contributions 3 (typed-composition recurrence) and 4 (expression-tree realization) unchanged and sound.

## Verdict
The algebraic restructure is a genuine clarity improvement, not vapor; Prop 4.5 adds real (modest) content; Prop 4.4 is honest but oversold as a Proposition. The orbit-closure bound is novel and non-overlapping with the foundation's confidentiality machinery -- but ACT should *say* that the foundation has its own (different) measure, to forestall the obvious reviewer question. No major novelty defect. Positioning gap is Minor.

## Confidence
High on distinctness of the three confidentiality measures (each verified against foundation text). Medium on the maxconf division of labor (did not read maxconf directly).
