# Literature Context (Merged Scout Output)

**Note**: As in the 2026-05-23 round, parallel scout subagents were unavailable in this session; the area chair conducted the literature assessment directly. This round is verification-heavy (cross-paper consistency with the foundation), so the field survey is condensed and the prior round's full survey (`../2026-05-23/literature-context.md`) is incorporated by reference. New material here is the **cross-paper / intra-ecosystem** positioning that this round's mandate added.

## Field positioning (condensed; unchanged from prior rounds)
ACT triangulates: SSE + leakage-abuse line (Song, Curtmola, Islam, Cash, Grubbs -- all cited), QIF (Smith 2009 -- cited), IFC (Sabelfeld-Myers 2003 -- cited), functional encryption (Boneh-Sahai-Waters 2011 -- cited). The cipher-type-algebra-over-trapdoor-computing framing has no direct prior occurrence. Novelty of the four contributions is not threatened by external prior art.

Missing-but-relevant for a PLAS audience (suggestion-level, carry-over): cryptographic type systems (Vaughan-Zdancewic 2007, Fournet-Rezk 2008), mixed-mode secure-computation compilers (ABY, Obliv-C, MOTION -- neighbors to the @cipher_node expression-tree realization), Bloom-cascade-FPR (Bose et al. 2008 -- neighbor to the Table 2 AND-chain divergence), indexed monads (Atkey 2009 -- neighbor to the typed-chain depth index). None threaten novelty.

## Intra-ecosystem positioning (the cross-paper mandate of this round)

The relevant "prior art" this round is ACT's own ecosystem -- the foundation `cipher_maps.tex` and the sibling maxconf paper -- because the foundation now exists and is detailed, and the review is informed by it. The key question is whether ACT's confidentiality contribution is distinct from the foundation's.

**Three confidentiality measures across the ecosystem, verified distinct:**

| Paper | Measure | What it captures | Threat posture |
|---|---|---|---|
| Foundation (`towell2026cipher`) Prop 5.1 | entropy ratio `e = H(Q)/n >= 1 - delta - h_2(delta)/n` (Fannes-Audenaert) | marginal uniformity of the cipher-value stream (a delta quantity) | passive observation |
| Foundation §8.2-8.3, Thm 8.2 | coincidence-oracle accuracy | collision/coincidence counting across instances | passive, multi-instance |
| maxconf (`towell2026maxconf`) | entropy-ratio framework (full proof of foundation's Prop 5.1, per foundation's cite [maxconf §4]) | same family as the foundation's `e`; the entropy-ratio "owner" | -- |
| **ACT (this paper)** Thm 5.3 | `H(X \| view) >= H(X) - log2 \|orbit\|` | reachability of cipher values under composition of the operations the untrusted machine holds | **active probing** |

These measure different things. ACT's orbit-closure bound is **genuinely distinct** (reachability under active composition) and is neither a re-derivation of nor derivable from the foundation's entropy-ratio (Prop 5.1) or coincidence-oracle (Thm 8.2). So there is **no novelty-threatening overlap and no duplication of the maxconf entropy-ratio framework.**

**However**: ACT cites the foundation only for the granularity principle (§8.1), never for the foundation's confidentiality machinery (§5, §8.2-8.3). It introduces "a confidentiality bound" as if the foundation had none. This is a positioning silence, not a conflict. The recommended fix (one or two sentences dividing the labor: foundation = marginal/delta + coincidence; maxconf = entropy ratio; ACT = orbit reachability) converts the silence into a crisp three-way story and forecloses the obvious reviewer objection. Flagged Minor by novelty-assessor and citation-verifier.

## Confidence
High on the distinctness of the three measures (each verified against foundation `.tex` body text). Medium on the maxconf details (not read in full; inferred from the foundation's citations into maxconf §4).
