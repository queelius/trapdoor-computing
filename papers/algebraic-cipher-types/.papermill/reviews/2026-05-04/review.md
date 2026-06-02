# Multi-Agent Review Report (cross-paper-informed)

**Date**: 2026-05-04
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Author**: Alexander Towell
**Version reviewed**: post 2026-05-04 thesis refinement, 21pp, ~1693 LaTeX lines, `\documentclass[11pt]{article}`. Builds clean (one overfull hbox).
**Recommendation**: **minor-revision**

**What makes this round distinct from the existing 2026-05-23 round**: (1) it gives the unreviewed 2026-05-04 algebraic restructure (Prop 4.4, Prop 4.5, Table 1, the reframed abstract/intro/conclusion) a genuine cold read; (2) it is *informed by the foundation paper* `cipher_maps.tex`, which now exists in-tree and builds clean (39pp). Every `towell2026cipher` citation was cross-checked against the foundation's resolved numbers (`cipher_maps.aux`, confirmed against the PDF). The 2026-05-23 round reviewed ACT in isolation and did not perform this cross-check; this round confirms and extends the user's candidate cross-paper findings.

---

## Summary

**Overall Assessment**: The paper remains in good shape after six substantive rounds. The 2026-05-04 algebraic restructure is sound: the two new propositions (4.4, 4.5) hold, Table 1 matches the per-constructor results and prose, and the restored "one algebra / universal granularity knob / three constructor-specific costs / sum is categorically different" frame is coherent end-to-end with no contradictory seams from the old sum-centric framing. The cross-paper check surfaces concrete, mechanical citation-number defects (six wrong-number sites) and one substantive fidelity-to-source error (composability stated as strict equality where the foundation states an inequality). The previously-flagged Thm 5.3 proof gap (2026-05-23 MAJ-1) is independently confirmed and sharpened. None of these change any theorem *statement*; all are local fixes.

**Strengths**:
1. The new Prop 4.5 (exponential confidentiality trade-off) is a genuine, if modest, contribution that makes the "universal granularity knob" claim land on exponentials, and connects cleanly back to the product trade-off (logic-checker, novelty-assessor).
2. The restored algebraic frame is coherent: abstract, §4 lead-in, per-constructor subsections, Table 1, and conclusion all tell the same story; sum-impossibility is correctly repositioned as the *categorically different* one of three, not a leftover headline (prose-auditor, novelty-assessor).
3. ACT's orbit-closure bound is genuinely distinct from the foundation's confidentiality machinery (entropy ratio, coincidence-oracle) and from the maxconf entropy-ratio framework -- reachability-under-active-composition versus marginal/collision leakage -- so there is no duplication (novelty-assessor, citation-verifier, literature-context, all cross-verified against foundation text).
4. Experimental side (five-seed averaging, plaintext baseline, honest seed-search-failure reporting, Table 2 AND-chain divergence with a sound structural explanation) is unchanged and solid (methodology-auditor).
5. Both papers build clean; ACT's label graph is intact after the restructure (format-validator).

**Weaknesses**:
1. (Major, cross-paper) ACT §3 misstates the foundation's Composability theorem as a strict equality; the foundation (Thm 4.2) states an inequality with an equality-under-re-randomization qualifier (logic-checker; user candidate B, confirmed).
2. (Major, carry-forward from 2026-05-23, independently confirmed) The Thm 5.3 proof conflates the orbit-as-set with the adversary's observation random variable; taken literally it proves the vacuous bound (logic-checker, cross-verified by methodology-auditor).
3. (Major, carry-forward) Six wrong-number `towell2026cipher` citation sites (citation-verifier; user candidate A, all confirmed).
4. (Major, carry-forward external) Three unpublished `@misc` self-citations (M9) and document class still `article` (M7) (citation-verifier, format-validator).
5. (Minor) ACT does not position its orbit bound against the foundation's own confidentiality machinery -- a silence, not a conflict (novelty-assessor, citation-verifier; user candidate C1).

**Finding Counts**: Critical: 0 | Major: 3 content (composability restatement, Thm 5.3 proof, citation-number defects) + 2 external carry-forwards (M7, M9) | Minor: 5 | Suggestions: 3

**Trajectory**: 2/11 (04-08) -> 1/12 (04-12) -> 0/6 (04-13) -> 0/2 (04-29) -> 0/0+2cf (04-30) -> 0/1+2cf (05-23) -> **0 Critical / 3 content-Major + 2 cf (05-04)**. The Major count rises this round only because the cross-paper check was performed for the first time and surfaced defects invisible to an isolated read; all three content-Majors are local, non-propagating fixes.

---

## Critical Issues

None.

---

## Major Issues

### MAJ-1 (NEW this round, cross-paper). Composability misstated as strict equality; the foundation states an inequality.
- **Source**: logic-checker (confirms user candidate B).
- **Location**: ACT §3 Preliminaries, Property 4, lines 262-263.
- **Quoted text (ACT)**:
  > For cipher maps $\fhat$ (correctness $\eta_f$) and $\hat{g}$ (correctness $\eta_g$), the composition $\hat{g} \circ \fhat$ has correctness $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$.
- **Foundation ground truth (Thm 4.2 `thm:composition-correctness`, cipher_maps.tex:660-672)**:
  > $\eta_{g \circ f} \leq \eta_f + \eta_g - \eta_f \eta_g = 1 - (1 - \eta_f)(1 - \eta_g)$, with equality under the re-randomization condition.
- **Problem**: ACT's preliminaries misstate the cited paper's own theorem -- strict `=` where the source has `<=` plus an equality qualifier. The foundation deliberately switched to the inequality (re-randomization, Foundation Def 7.1, is what makes equality typical-but-not-universal).
- **Load-bearing assessment**: traced all downstream uses in ACT §4-§7. **Nothing in ACT relies on exact multiplicativity.** Orbit closure (§5) is correctness-agnostic; the typed-chain bound counts reachable values, not error; §7 measures FPR empirically. So this is a fidelity-to-source defect, not a propagating logical error.
- **Suggestion**: ACT:262-263 -> "the composition $\hat g\circ\fhat$ has correctness $\eta_{g\circ f}\le 1-(1-\eta_f)(1-\eta_g)$, with equality under the foundation's re-randomization condition." One line.
- **Cross-verified**: quoted both papers verbatim; foundation `.aux` confirms `thm:composition-correctness` = Thm 4.2. Severity Major (misquotes a cited theorem; the foundation author as reviewer will catch it), cheap fix.

### MAJ-2 (carry-forward from 2026-05-23, independently confirmed and sharpened). Thm 5.3 proof conflates the orbit set with the adversary's observation variable.
- **Source**: logic-checker; cross-verified by methodology-auditor.
- **Location**: ACT §5.3, lines 841-867.
- **Quoted text (proof of Thm 5.3, ACT:858-867)**:
  > The view $\mathcal{V}_F(c)$ takes at most $|\orbitF(c)|$ distinct values as $X$ ranges over its distribution, since the orbit is a finite set of bit strings computable from $c$. Therefore $I(X; \mathcal{V}_F(c)) \leq H(\mathcal{V}_F(c)) \leq \log_2 |\orbitF(c)|$, and $H(X \mid \mathcal{V}_F(c)) = H(X) - I(X; \mathcal{V}_F(c))$.
- **Problem (sharpened from 2026-05-23)**: the setup (ACT:841-844) defines $\mathcal{V}_F(c) := \orbitF(c)$, and the paper's own Remark (ACT:775-782) stresses the orbit depends only on $(c,F)$, **not on the latent value $X$**. So, taken literally, $\mathcal{V}_F(c)$ is a *constant* random variable (same set for every $X$), giving $I(X;\mathcal{V})=0$ and the **vacuous** bound $H(X\mid\mathcal{V})\ge H(X)$ -- not the claimed $H(X)-\log_2|\orbit|$. The displayed inequality $H(\mathcal{V})\le\log_2|\orbit|$ tacitly treats $\mathcal{V}$ as ranging *over* the orbit, but the setup says $\mathcal{V}$ *is* the orbit. The 2026-05-23 round framed this as "set vs single value"; the sharper statement is that the literal object carries zero information, so the proof either proves a vacuum or silently swaps the variable.
- **Suggestion**: prove the set-form (Corollary 5.4) first via an injective-decoder argument -- the adversary's distinguishing observable $W$ (which orbit element its probing lands on) takes $\le|\orbit|$ values; any deduction $W\to$ latent is a function, so $|S_F(c)|\le|\orbit|$; then $H(X\mid W)\ge H(X)-\log_2|S_F(c)|\ge H(X)-\log_2|\orbit|$. State Thm 5.3 conditioning on $W$, not on the orbit-as-set. The **theorem statement is unchanged**, so the abstract/intro/conclusion (which quote it identically) need no edit. ~30 min.
- **Cross-verified**: logic-checker re-derived it; methodology-auditor confirmed from the random-variable-specification lens (measured quantity != quantity the inference needs). Both agree: gap real, bound recoverable, statement stands. **No disagreement.** Strengthened by the cross-paper finding that ACT's orbit measure is distinct from the foundation's entropy-ratio, so the repair stands on its own ground.
- **Severity**: Major (load-bearing theorem; proof as written does not establish the claim). Recoverable.

### MAJ-3 (NEW this round, cross-paper). Six wrong-number `towell2026cipher` citation sites.
- **Source**: citation-verifier (confirms all four user candidate-A defects; six occurrences).
- **Location / ground truth** (full table in the dedicated cross-paper section below). Summary:
  - ACT:232 `[Def.~1.1]` -> cipher map is Foundation **Def 3.1**.
  - ACT:399, 706, 1572 `[Sec.~9]` (3 sites) -> granularity is Foundation **§8.1**; Foundation §9 is **Discussion**.
  - ACT:1575 `[Sec.~9.3]` -> entanglement parameter is an unlabeled **Definition in §8.1**; Foundation §9.3 exists but is **"Online Construction"** (so the cite points at unrelated content, not merely a missing subsection).
  - ACT:1168 `[Prop.~9.1]` -> "Granularity and privacy" is Foundation **Prop 8.1**; the shared-input scenario is precisely Foundation **§8.2 Compositional Leakage**.
- **Problem**: these resolve to wrong content in the current foundation. The `[Sec.~9]` sites are worst: a reader chasing the granularity principle lands on the Discussion. All cited *claims* are true and supported at the corrected locations (wrong-number, not wrong-claim).
- **Suggestion**: apply the six mechanical fixes (table below). Pin the foundation version (commit/arXiv vN) in the bib note, because the foundation is itself under active revision (its source shows a recently inserted §8.3) and these numbers can drift.
- **Cross-verified**: every numbered cite checked against `cipher_maps.aux` and the corresponding `.tex` body. Severity Major (multiple incorrect references to the single most load-bearing citation; mechanical to fix).

### MAJ-4 (carry-forward, external). M9 self-citations and M7 document class.
- **Source**: citation-verifier (M9), format-validator (M7).
- **M9**: `towell2026cipher` (most load-bearing), `towell2026bernoulli`, `towell2026maxconf` are `@misc ... Manuscript in preparation` (references.bib:1-20). Fix: post to arXiv/IACR ePrint, update the note. Note this round: the foundation demonstrably exists, so posting is unblocked; **posting does NOT fix MAJ-3's number defects** -- those are separate.
- **M7**: `\documentclass[11pt]{article}` (line 1). Gated on venue (PLAS -> acmart + CCS concepts; ePrint/arXiv -> article is fine).
- **Severity**: Major (submission blockers), but external decisions, not content rewrites. Unchanged across all rounds.

---

## Minor Issues

### MIN-1 (carry-over, twice-flagged). Conclusion "10^4" understates Table 2's 12,160.
- **Source**: prose-auditor, logic-checker.
- **Location**: conclusion, line 1666: "by $10^4 \times$ at $k = 5$". Table 2 (line 1469) shows 12,160 (1.2x underestimate). Flagged 2026-04-30 and 2026-05-23; not yet applied. Fix: "over $10^4\times$" or "$\sim\!1.2\times10^4$". 5 seconds.

### MIN-2 (NEW, cross-paper). ACT does not position its orbit bound against the foundation's confidentiality machinery.
- **Source**: novelty-assessor, citation-verifier (user candidate C1, confirmed; severity Minor).
- **Problem**: ACT cites the foundation only for granularity (§8.1), never for Foundation Prop 5.1 (entropy ratio) or §8.2-8.3 (compositional / coincidence-oracle leakage). It introduces "a confidentiality bound" as if the foundation had none. The measures are genuinely distinct (verified -- no overlap, no duplication of maxconf's entropy ratio), so this is a silence, not a conflict; but the foundation author as reviewer will ask whether ACT is aware of §5/§8.
- **Suggestion**: add 1-2 sentences (in §5.3 or the Discussion "Relationship to cipher maps", ACT:1549) dividing the labor: foundation Prop 5.1 = marginal/delta leakage; foundation §8.3 coincidence-oracle = cross-instance collision; maxconf = entropy ratio; ACT = orbit reachability under active probing.

### MIN-3 (NEW). Sum-type vs implicit-flow differentiation could be sharper.
- **Source**: novelty-assessor (also 2026-05-23 MIN-2).
- **Location**: §2 (158-166), §4.3 lead-in. Add the explicit contrast: IFC = compile-time yes/no rejection; cipher-types = encoding-level quantification with a continuous joint/component-wise knob. Forecloses "Thm 4.2 is implicit-flow rebranded."

### MIN-4 (carry-over). Overfull hbox at line 703.
- **Source**: format-validator, prose-auditor. The only build warning (§4.5 "Universal granularity knob", 19.7pt). Rephrase or insert a break.

### MIN-5 (carry-over). "Starting tape configuration" vestige in §6.3.
- **Source**: prose-auditor (also 2026-05-23 MIN-5).
- **Location**: §6.3 "What bounds the orbit", line 1237. "tape configuration" is leftover jargon from the removed cipher-TM section. Rephrase to "starting cipher value/state."

(Presentation, shared across reviewers: Prop 4.4's Proof block unpacks definitions; consider trimming to one line or relabeling as Remark/Definition-by-correspondence. Logged under prose/novelty; not separately numbered.)

---

## Suggestions

1. **Software citation** for the `cipher-maps` Python library (§7.3, line 1393): add a `@software`/`@misc` with repo URL + tag for reproducibility. (Note: the integration handshake doc cited in the project's own CLAUDE/state as `src/cipher-maps/PAPER-INTEGRATION.md` was not found at that path in this checkout; stale pointer, documentation-only, no paper edit.)
2. **Statistical candor note for Table 2 at k=5**: at 1000 trials/seed the Bernoulli-expected FP count is ~3e-4, so the 12,160x ratio is dominated by a few-FP floor; the qualitative orders-of-magnitude claim is robust, the specific multiplier is trial-count-sensitive. One sentence pre-empts a methodology reviewer.
3. **For PLAS only**: engage cryptographic type systems (Vaughan-Zdancewic 2007, Fournet-Rezk 2008) in §2 and Bloom-cascade-FPR (Bose et al. 2008) in the Table 2 discussion. One paragraph each.

---

## Cross-paper consistency (cipher-maps-informed)

Every `towell2026cipher` citation site in ACT, the cited number/claim, the foundation ground truth (from `cipher_maps.aux`, confirmed against `cipher_maps.tex` body and the typeset PDF), and a verdict. Foundation builds clean (39pp); printed reference numbers are authoritative.

| ACT line | ACT cites | Cited claim | Foundation ground truth | Verdict |
|---|---|---|---|---|
| 85 | (bare) | 4 properties + 3 constructions | §3-§6 | OK |
| 229 | (bare) | recall cipher map abstraction | §3 (`sec:abstraction`) | OK |
| **232** | `[Def.~1.1]` | cipher map definition | **Def 3.1** (`def:cipher-map`, p.5) | **wrong-number** |
| 245 | `[Sec.~4]` | four properties, (eta,eps,mu,delta) | **§4** Four Properties (`sec:properties`) | OK |
| 277 | `[Sec.~5]` | trusted/untrusted machines | **§5** Trust model (`sec:trust-model`) | OK |
| **399** | `[Sec.~9]` | encoding-granularity principle | **§8.1** (`subsec:granularity`); §9 = Discussion | **wrong-number** |
| 612 | (bare) | cipher map = total fn correct on enc(A) | Def 3.1 + §4 | OK (no over-attribution of exponential framing) |
| 664 | `[Sec.~6]` | lookup-table cost O(\|A\|.\|C\|) | **§6** Batch (`sec:batch`); space = bits/elem (Thm 6.2); table = domain x bits | OK (claim-supported; tighten to [Thm 6.2] optional) |
| **706** | `[Sec.~9]` | entanglement parameter spectrum | **§8.1** | **wrong-number** |
| **1168** | `[Prop.~9.1]` | correlation preserved, component-wise enc | **Prop 8.1** (`prop:granularity`, p.22); shared-input = **§8.2** Compositional Leakage | **wrong-number** |
| 1550 | (bare) | extends the cipher map framework | whole paper | OK |
| **1572** | `[Sec.~9]` | encoding-granularity principle | **§8.1** | **wrong-number** |
| **1575** | `[Sec.~9.3]` | entanglement parameter $p$ | unlabeled **Def in §8.1**; foundation §9.3 = **"Online Construction"** (unrelated) | **wrong-number** |
| 1596 | (bare) | trapdoor boolean algebra | §3 / instantiations | OK |
| 1687 | (bare) | building on cipher map framework | whole paper | OK |

**Tally**: 6 wrong-number sites (4 distinct wrong references). 0 wrong-claim. 0 over-attribution (Prop 4.4's `(per \cite{towell2026cipher})` at 612 correctly supports the cipher-map facts via Def 3.1 + §4 without attributing the exponential-type framing to the foundation -- the foundation has no exponential-type framing). All user candidate-A defects confirmed; no additional defects found; no false positives.

**Substantive inconsistency (user candidate B): CONFIRMED** -- composability `=` vs foundation's `<=` (MAJ-1 above). Non-propagating.

**Positioning (user candidate C): CONFIRMED, Minor** -- C1 (orbit bound not positioned against foundation's confidentiality machinery; the measures are distinct -- entropy-ratio/coincidence vs orbit-reachability -- so no duplication, only a silence; MIN-2 above). C2 (Prop 4.4 attribution): no over-attribution (table row 612). C3 (three-paper coherence): ACT's §5.3 does not overlap or conflict with the maxconf entropy-ratio framework; ACT's orbit bound is the reachability-side complement (literature-context table). All three sub-points verified against foundation text.

---

## Detailed Notes by Domain

### Logic and Proofs
New props sound (4.4 definitional-but-correct; 4.5 correct and substantive). Table 1 matches the per-constructor results row by row. Composability misquote (MAJ-1) confirmed verbatim and shown non-propagating. Thm 5.3 proof gap (MAJ-2) independently re-derived and sharpened: the literal orbit-as-set is X-independent, hence carries zero information, hence the proof as written yields a vacuous bound; the intended (and correct) reading conditions on the orbit-landing observable. Fix leaves the statement intact. Prop 5.5, Thm 4.2, Thm 5.2, Prop 4.1, noise unreliability, and Table 2 numerics all re-verified sound. Full report: `logic-checker.md`.

### Novelty and Contribution
Algebraic restructure is a real clarity gain, not vapor; Prop 4.5 adds modest genuine content; Prop 4.4 is honest but oversold as a Proposition. ACT's orbit-closure bound is distinct from the foundation's entropy-ratio (Prop 5.1), the foundation's coincidence-oracle (§8.3), and the maxconf entropy-ratio framework -- verified, no duplication. The one gap is that ACT does not *say* the foundation has its own (different) measure (MIN-2). Full report: `novelty-assessor.md`.

### Methodology
2026-04-30 experimental rerun holds; nothing regressed. Five-seed averaging, plaintext baseline framing, honest seed-search-failure reporting, hardware spec all present. Served as the cross-verification lens for MAJ-2 and concurs the random-variable structure is mis-specified but the bound is recoverable. k=5 candor suggestion stands. Full report: `methodology-auditor.md`.

### Writing and Presentation
Restored algebraic frame reads coherently; no contradictory seam from the old sum-centric framing. Entropy-form bound stated identically in abstract/intro/Thm 5.3/conclusion. Residuals: "10^4" understatement (MIN-1), overfull hbox (MIN-4), "tape configuration" vestige (MIN-5), Prop 4.4 over-framed. §7.3 FPR explanation paragraph is excellent. Full report: `prose-auditor.md`.

### Citations and References
21 entries, all cited, no dead keys. Six wrong-number foundation cites (MAJ-3, full table above). M9 (3 unpublished self-cites) and the positioning gap (MIN-2) and software-citation suggestion. Recommend pinning the foundation version to prevent number drift. Full report: `citation-verifier.md`.

### Formatting and Production
Both papers build clean. ACT 21pp, one overfull hbox, no undefined refs, label graph intact after the restructure (new labels prop:exponential-identity, prop:exponential-tradeoff, sec:type-summary, tab:algebra-summary all resolve). §4.5's Table 1 renumbers the §7.3 tables to 2/3/4 (PDF internally correct via \Cref; only docs are stale). M7 doc class gated on venue. Full report: `format-validator.md`.

---

## Literature Context Summary
ACT's external positioning (SSE + leakage attacks, QIF, IFC, FE) is unchanged and adequate; the cipher-type-algebra-over-trapdoor framing has no direct prior occurrence. The round's relevant "prior art" is intra-ecosystem: a verified three-way division of confidentiality labor -- foundation (marginal/delta entropy-ratio + coincidence-oracle), maxconf (entropy-ratio framework), ACT (orbit reachability under active probing). Distinct, non-duplicative; ACT should state the division (MIN-2). PLAS-audience neighbors (cryptographic type systems, Bloom-cascade-FPR, mixed-mode MPC compilers, indexed monads) remain optional strengtheners. Full notes: `literature-context.md`.

---

## Recommendation Rationale

**minor-revision.** Per the brief's calibration: the new propositions are sound (no soundness problem in Prop 4.4/4.5), and the positioning gap against the foundation's confidentiality machinery is *not* severe (the measures are genuinely distinct; it is a one-sentence silence, not a duplication). That rules out the major-revision escalation conditions. What remains is exactly the predicted profile: mechanical citation-number fixes (MAJ-3, six edits), the composability restatement (MAJ-1, one line), the recoverable Thm 5.3 proof repair (MAJ-2, statement unchanged), and the external carry-forwards (M7/M9). All are local; none propagate; none change a theorem statement.

**Why not minor-revision-lighter / accept**: MAJ-1 misquotes a cited theorem, MAJ-2 is a load-bearing proof that as written proves a vacuum, and MAJ-3 has six incorrect references to the single most load-bearing citation. An external reviewer -- especially the foundation's author -- will catch all three. They must be fixed.

**Why not major-revision**: no critical issue; the algebraic restructure is sound; the new propositions hold; the orbit-closure contribution is distinct and non-overlapping; every fix is mechanical or a localized proof edit with no downstream propagation.

**Smallest path to acceptance** (internal effort ~1 hour):
1. Restate composability as `<=` with the re-randomization qualifier (MAJ-1, ACT:262-263).
2. Repair the Thm 5.3 proof via the set-form-first / injective-decoder route; statement unchanged (MAJ-2, ACT:858-867 and Cor 5.4 at 881-887).
3. Apply the six citation-number fixes (MAJ-3): 232 `[Def.~3.1]`; 399/706/1572 `[\S 8.1]`; 1575 `[Def. in \S 8.1]`; 1168 `[Prop.~8.1]` (+ "§8.2"). Pin the foundation version in the bib.
4. Add the 1-2 sentence confidentiality-measure division of labor (MIN-2).
5. Fix MIN-1 (10^4 -> over 10^4), MIN-4 (hbox), MIN-5 (tape vestige).
Then the external decisions: venue (M7) and post `towell2026cipher` (M9).

---

## Review Metadata
- Specialists: logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator, plus a condensed literature assessment. Parallel subagent (Task) execution was unavailable in this session; the area chair conducted each specialist analysis directly and verified every finding against both papers' source.
- Cross-paper ground truth: foundation `cipher_maps.tex` (137 KB) + `cipher_maps.aux` (resolved labels) + clean 39pp build; every numbered `towell2026cipher` cite checked.
- Cross-verifications performed: 2.
  - MAJ-2 (Thm 5.3 proof): logic-checker finding cross-verified by methodology-auditor (random-variable-specification lens). Both agree: gap real, statement stands, bound recoverable. No disagreement.
  - MAJ-1 (composability) and MAJ-3 (citation numbers): cross-checked directly against foundation `.tex`/`.aux` verbatim.
- Disagreements noted: 0.
- Hallucination check: every quoted ACT line (262-263, 858-867, citation sites) and every foundation quote (Thm 4.2 at cipher_maps.tex:660-672; Def 3.1 label; §8.1/§9 numbers) verified against source. Bibliography verified against references.bib.
- Relationship to the 2026-05-23 review: that round reviewed ACT in isolation and recommended minor-revision with one new Major (the Thm 5.3 gap). This round confirms that finding, adds the cross-paper layer the brief required (composability inconsistency + six citation-number defects + the positioning division of labor), and reaches the same minor-revision verdict for consistent reasons.
