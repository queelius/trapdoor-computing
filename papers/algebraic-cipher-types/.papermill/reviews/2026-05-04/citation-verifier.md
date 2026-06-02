# Citation Verifier Report

**Date**: 2026-05-04 (cross-paper-informed)
**Reviewer role**: Citation accuracy, missing references, bibliography integrity.
**This round's distinguishing task**: the foundation paper `towell2026cipher` now demonstrably EXISTS (`cipher_maps.tex`, 39pp, builds clean). Every `\cite[...]{towell2026cipher}` numbered qualifier is cross-checked against the foundation's resolved numbers (`cipher_maps.aux`, all confirmed against the typeset PDF page/number fields).

## Bibliography integrity (ACT references.bib)

21 entries, all cited, no dead keys (consistent with the 2026-05-23 finding; re-confirmed). `\bibliographystyle{plainnat}`, numbered/square natbib. No formatting errors. Build emits no undefined citations.

Three `@misc` self-citations remain "Manuscript in preparation" (`towell2026cipher`, `towell2026bernoulli`, `towell2026maxconf`) -- the carry-forward **M9**. Distinguishing point this round: `towell2026cipher` is no longer unverifiable to *us* (the file is in-tree and detailed). M9's fix (post to arXiv/ePrint, update the note) is unchanged; but note that **posting does not fix the citation-NUMBER defects below** -- those are a separate, newly surfaced problem.

## Cross-paper citation tabulation (every towell2026cipher site)

15 mentions / 14 cite commands. Nine carry a numbered qualifier; all nine verified against the foundation. Ground-truth numbers from `cipher_maps.aux` (printed reference number is the first field of each `\newlabel`):

| ACT line | ACT cites | Cited claim | Foundation ground truth | Verdict |
|---|---|---|---|---|
| 85 | (bare) | four properties + 3 constructions developed in foundation | §3-§6 | OK |
| 229 | (bare) | "recall the cipher map abstraction" | §3 | OK |
| **232** | `[Def.~1.1]` | cipher map definition | cipher map is **Def 3.1** (`def:cipher-map`, p.5) | **WRONG-NUMBER** |
| 245 | `[Sec.~4]` | four properties, params (eta,eps,mu,delta) | §**4** "Four Properties" (`sec:properties`) | OK |
| 277 | `[Sec.~5]` | trusted/untrusted machines | §**5** "Trusted/Untrusted Machine Model" (`sec:trust-model`) | OK |
| **399** | `[Sec.~9]` | encoding-granularity principle | granularity is §**8.1** (`subsec:granularity`); foundation §9 is **Discussion** (`sec:discussion`) | **WRONG-NUMBER** |
| 612 | (bare) | cipher map = total fn correct on encodings of A | Def 3.1 + §4 | OK (supports facts; does not over-attribute the exponential framing) |
| 664 | `[Sec.~6]` | lookup-table cost O(\|A\|.\|C\|) | §**6** "Batch Construction" (`sec:batch`); space stated as **bits/element** (Thm 6.2), table = domain x bits | OK (claim-supported; see note) |
| **706** | `[Sec.~9]` | entanglement parameter p spectrum | §**8.1** (granularity); §9 = Discussion | **WRONG-NUMBER** |
| **1168** | `[Prop.~9.1]` | correlation preserved under component-wise enc | "Granularity and privacy" is **Prop 8.1** (`prop:granularity`, p.22); shared-input case is §**8.2** Compositional Leakage | **WRONG-NUMBER** |
| 1550 | (bare) | "extends the cipher map framework" | whole paper | OK |
| **1572** | `[Sec.~9]` | encoding-granularity principle | §**8.1** | **WRONG-NUMBER** |
| **1575** | `[Sec.~9.3]` | entanglement parameter p | entanglement parameter is an (unlabeled) **Definition in §8.1** (`subsec:granularity`, cipher_maps.tex:1671); **there is no §9.3** (foundation §9.3 = "Online Construction") | **WRONG-NUMBER** |
| 1596 | (bare) | trapdoor boolean algebra of foundation | §3.3 / instantiations | OK |
| 1687 | (bare) | building on cipher map framework | whole paper | OK |

**Six wrong-number citation sites** (4 distinct wrong references): `[Def.~1.1]` x1 (->3.1), `[Sec.~9]` x3 (->8.1), `[Sec.~9.3]` x1 (->8.1), `[Prop.~9.1]` x1 (->8.1). Every one of the user-supplied candidate defects is **confirmed**; I found no additional defects and no false positives among the candidates.

### Why these matter
The `[Sec.~9]` defects are the worst because foundation §9 is literally a *Discussion* section, so a reader following the cite for the granularity principle lands on the wrong content (not just a wrong number with adjacent content). `[Sec.~9.3]` points at a subsection that does not exist as cited (foundation §9.3 is "Online Construction", unrelated). `[Def.~1.1]` is off by a chapter (foundation has no Definition 1.1; §1 is the Introduction with no numbered definitions).

### Recommended fixes (mechanical)
- 232: `[Def.~1.1]` -> `[Def.~3.1]`
- 399, 706, 1572: `[Sec.~9]` -> `[Sec.~8.1]` (or `[\S 8]`)
- 1575: `[Sec.~9.3]` -> `[Def. in \S 8.1]` (the entanglement-parameter definition is unlabeled in the foundation; cite the subsection)
- 1168: `[Prop.~9.1]` -> `[Prop.~8.1]`; consider adding "and §8.2 (Compositional Leakage)" since that subsection is the exact match for the shared-input scenario in rem:shared-vars.
- 664: keep `[Sec.~6]` but optionally tighten to `[Thm 6.2]` (the space-complexity theorem), since §6 states cost per element, not literally an "O(|A|.|C|) lookup-table cost."

These are stable once the foundation numbering is stable. **Risk note**: the foundation is itself under active revision (its .aux shows recently inserted subsections, e.g. §8.3 "Multi-Instance Composition Leakage" tagged [INTEGRATION 2026-05-07] in the source). ACT should pin to the foundation commit/version it cites, or these numbers can drift again. A `@misc` note like "version of <date> / arXiv vN" closes both M9 and the drift risk.

## Positioning gap (cross-paper, shared with novelty-assessor)

ACT cites the foundation **only** for the granularity principle (§8) and the four-properties recap. It never cites the foundation's **own confidentiality machinery**: Foundation **Prop 5.1** (`prop:confidentiality`, entropy ratio + Fannes-Audenaert, p.11) and Foundation **§8.2-§8.3** (compositional leakage; "Coincidence-oracle accuracy" Thm 8.2 `thm:coincidence-oracle`, p.23). ACT introduces its orbit-closure bound (Thm 5.3) without positioning it against the foundation's existing measure. This is a citation-completeness gap, not a citation error: the two measures are genuinely distinct (entropy ratio = marginal-uniformity/delta; orbit bound = reachability), so there is no duplication -- but a reader (especially the foundation author as reviewer) will expect ACT to say so explicitly. Recommend one sentence in §5.3 or §8 noting that the foundation's confidentiality bound (Prop 5.1) measures marginal leakage via delta, the sibling maxconf paper owns the entropy-ratio framework, and ACT's orbit bound is the complementary reachability-side measure. Minor.

## Missing-reference notes (carry-over from 2026-05-23, unchanged)
- No software citation for the `cipher-maps` Python library (§7.3, line 1393). Recommend a `@software`/`@misc` with the repo URL + tag. Minor.
- For PLAS: cryptographic-type-systems neighbors (Vaughan-Zdancewic 2007, Fournet-Rezk 2008) and Bloom-cascade-FPR (Bose et al. 2008) would strengthen §2 and the Table 2 discussion respectively. Suggestion-level.

## Confidence
High. Every numbered foundation citation was checked against `cipher_maps.aux` and the corresponding `.tex` body text.
