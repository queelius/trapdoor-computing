# Multi-Agent Review Report (Round 5, 2026-06-02, CROSS-PAPER)

**Date**: 2026-06-02
**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor
Computing" by Alexander Towell (25 pages, 6 theorems, 4 tables, 3 figures)
**Recommendation**: **minor-revision**

This is the first **cross-paper-consistency** round. Four prior intra-paper
rounds (2026-04-12, -rev2, 2026-04-29, 2026-05-23) all landed at
minor-revision and verified the internal proofs, numerics, and prose. The
paper is internally polished. This round's purpose, and its entire value-add,
is **consistency with the two companion papers (`towell2026cipher`,
`towell2026algebraic`) and the canonical spine** (`cipher-map-formalism.md`).
Settled intra-paper findings are not re-litigated.

**Bottom line:** the paper's mathematics is sound, but its cross-paper
citation layer is broken in six places (the companions were renumbered and
this paper never tracked them), one inherited inequality uses the wrong form
and denominator, and two inherited results are over-attributed. Every finding
has an exact mechanical fix. None blocks the paper's scientific claims; all
are the kind of defect a referee who reads the family side-by-side will
catch. No critical errors.

---

## Summary

**Overall Assessment**: A strong, internally-consistent theory paper whose
**cross-paper interface** has drifted. The companions' section and theorem
numbers moved (cipher-maps composition is now §7, granularity §8; algebraic
sum-impossibility is Thm 4.2, typed chains §5.5), and all six of this paper's
pointers into those locations are stale. Independently, the orbit-closure
bound this paper inherits is quoted in a form (set form, denominator `2^n`)
that disagrees with both the source theorem (entropy form) and the spine
(set form, denominator `|X|`). After the mechanical fixes the paper is
submission-ready.

**Strengths**:
1. The compositional-leakage pair (Thm 5.1 + Thm 5.2) is a genuine novelty
   upgrade: Thm 5.2's matching minimax lower bound closes the long-standing
   M11 gap and earns the "information-theoretically optimal" framing
   (novelty-assessor).
2. Ownership boundaries against the family are respected: the paper owns M1
   (shared) and C3, correctly cites C1, and never claims M2; it does not
   encroach on any measure the spine assigns elsewhere (novelty-assessor N-1).
3. The C-10 `U` vs `U_im` two-step is explicit in Thm 4.2 and used honestly
   downstream; the one consistency-report worry that could have been an error
   is in fact correctly handled (logic-checker D).
4. The new §6.5 compression-validation transforms Prop 6.1 from asserted to
   empirically anchored against four stream archetypes, with honest scoping
   (methodology-auditor).
5. The build compiles cleanly in three passes to 25 pages with all
   cross-references resolving (format-validator).
6. The paper's over-attribution failures (crediting cipher-maps for results
   it does not fully state) are the *safe* direction of error: they
   under-claim the paper's own work rather than over-claim (novelty-assessor).

**Weaknesses**:
1. Six cross-paper citations point to the wrong section/theorem after the
   companions were renumbered (citation-verifier; HIGH).
2. The inherited orbit-closure bound (lines 789, 1076) uses the set form with
   denominator `2^n`, but algebraic Thm 5.3 states the *entropy* form, and
   the spine's set form uses `|X|`; the `2^n` version is numerically looser
   (claims more confidentiality) (logic-checker A3; HIGH).
3. The FPR-compounding formulas are attributed to cipher-maps §7.4, which
   does not state them (it gives only interval arithmetic); the explicit
   formulas live in algebraic Table 3 (logic-checker A1; HIGH after the
   section-number fix).
4. The headline lower bound's named technique is wrong: a `2^{m/2}`-packing
   is Assouad's lemma, not "Le Cam's two-point method" (repeated ~6 times
   incl. the abstract) (logic-checker B2, prose-auditor P-2; MEDIUM).
5. `H*` carries two normalizers inside Thm 3.1 (`n` in parts 1 and 3,
   `log_2|X|` in part 2), and the worked e-values use `log_2|X|` while the
   Fannes bound uses `n` (logic-checker C; MEDIUM).
6. The §9 multi-level-depth budget omits Measure C2 (the coincidence oracle),
   the one compositional channel that fires when a program repeats a
   primitive (novelty-assessor N-2; MEDIUM completeness gap).

**Finding Counts**: Critical: 0 | Major (HIGH): 3 | Minor (MEDIUM): 6 |
Suggestions (LOW): 6

---

## SECTION 1: CROSS-PAPER CONSISTENCY (primary deliverable)

### (a) Verified citation-drift table

All companion label numbers independently confirmed against the companion
`.aux` (resolved cross-references) and `.tex` (section titles). Each row is a
verifiable one-token fix.

| Line(s) | Current cite | Correct cite | Companion `.aux` evidence | Severity |
|---|---|---|---|---|
| 193, 817, 999 | `[Sec.~8]{cipher}` (FPR compounding) | `[Sec.~7.4]` | `sec:composition=7`; gate-error subsec 7.4; `sec:uniformity=8` is granularity | HIGH |
| 168, 732 | `[Sec.~9]{cipher}` (granularity) | `[Sec.~8]` | `sec:uniformity=8`; `sec:discussion=9` | HIGH |
| 739 | `[Prop.~9.1]{cipher}` (granularity spectrum) | `[Prop.~8.1]` | `prop:granularity=8.1` | HIGH |
| 828, 956 | `[Sec.~9.2]{cipher}` (compositional leakage) | `[Sec.~8.2]` | `subsec:comp-leakage=8.2` | HIGH |
| 772 | `[Thm.~4.1]{algebraic}` (sum impossibility) | `[Thm.~4.2]` | `thm:sum-impossibility=4.2`; 4.1 is product prop | HIGH |
| **1084** | `[Sec.~5.4]{algebraic}` (typed chains) | `[Sec.~5.5]` | `sec:typed-chains=5.5`; 5.4 is "Examples" (NEW find) | HIGH |

**Correct, verified, do NOT change:** `[Def.~3.1]` (307), `[Sec.~4]` (319),
`[Thm.~6.1]` (360), `[Sec.~5]` (367), `[Sec.~6.2]` (373) into cipher-maps;
`[Sec.~5]` (778, 1073), `[Thm.~5.3]` (787, 1687) into algebraic. All resolve
as the user listed. (The `[Thm.~5.3]` *number* is right; its *form* is wrong,
see 1(c)/A3 below.)

**Bidirectional (companion -> us), STALE, fix in companion:** cipher-maps
`cipher_maps.tex` line 843 cites `[Theorem~4.1, part~3]{towell2026maxconf}`
for the Fannes-bridge full proof. After this paper's restructuring the Fannes
bridge is **Theorem 3.1** part (3); our Theorem 4.1 is now Noise Dilution.
Fix in cipher-maps: `[Theorem~3.1, part~3]`. (cipher-maps line 906's
`[\S 5--6]` reference is still accurate.)

### (b) Consistency-report findings C-4 / C-6 / C-9 / C-10 status

| ID | Issue | Status in current `main.tex` | Action |
|---|---|---|---|
| **C-4** | "Le Cam" dual-role footnote | OPEN. No footnote at the Thm 5.2 site distinguishing the compositional LOWER-bound role (C3) from cipher-maps' marginal UPPER-bound role (M2). Compounded: our use is actually Assouad. | Add the one-clause footnote (and fix the technique name, see 1(d)). |
| **C-6** | Parameter tuple order | OPEN, internally inconsistent. `(η,ε,δ,μ)` at lines 109, 277, 471, 1779 and `(η,ε,δ)` at 429; only line 319 (hub import) uses the spine-canonical `(η,ε,μ,δ)`. | Align all to `(η, ε, μ, δ)`. Five edits. |
| **C-9** | `H*` ambiguity | OPEN, three-way. Thm 3.1: `H*=n` (parts 1, 3), `log_2|X|` (part 2); `def:max-entropy` uses "vocabulary m". Worked e-values use `log_2|X|`; Fannes bound uses `n`. | Add one sentence distinguishing the ambient ratio `H(Q)/n` (Fannes, spine M1) from the effective-alphabet ratio `H(Q)/log_2|X|` (examples); state which the reported numbers use. |
| **C-10** | `U` vs `U_im` | CLOSED. Two-step lift explicit in Thm 4.2 (lines 666-669); §6.4 reports `TV(Q,U_im)` honestly; no downstream conflation. | Optional half-sentence reminder at Table 4 that the reported δ is the U-lifted value. |

### (c) Claim-level inheritance findings

1. **FPR formulas over-attributed (HIGH).** `thm:fpr-compounding` (line 999)
   states `FPR=p_T^k` (AND) and `1-(1-p_T)^k` (OR) crediting cipher-maps.
   cipher-maps §7.4 ("Error Accumulation by Gate Type", lines 1637-1646) does
   NOT state these closed forms; it gives only interval arithmetic. The
   explicit formulas + empirical validation are in **algebraic Table 3**
   (`tab:fpr-compounding`). Fix: state the formulas as elementary, cite
   cipher-maps §7.4 for the gate-type framing and algebraic Table 3 for the
   validation.

2. **Granularity spectrum table over-attributed (MEDIUM).** Our spectrum
   table (lines 760-770, `O(|Y|^k)` vs `O(k|Y|)`) sits under the `[Prop.~8.1]`
   attribution, but cipher-maps Prop 8.1 defines `p` and the
   component-wise/joint distinction without that space-spectrum table; the
   table matches the **spine §4.3**. Fix: credit the table to the granularity
   discussion / spine, not to Prop 8.1's statement.

3. **Orbit-closure form AND denominator wrong (HIGH).** Lines 789 and 1076
   state `conf_F(c) >= 1 - |orbit_F(c)|/2^n` crediting algebraic Thm 5.3. But
   (i) algebraic Thm 5.3 states the **entropy form**
   `H(X|V_F(c)) >= H(X) - log_2|orbit_F(c)|`, not a set form; and (ii) the
   spine §4A.2 set form uses denominator **`|X|`**, not `2^n`. With
   `|X| < 2^n` (generic) the `2^n` form is looser (over-claims
   confidentiality). The spine is authoritative; `|X|` is the defensible
   normalizer (orbit bounds residual uncertainty of the latent X). Fix:
   change `2^n` to `|X|` at both sites and either cite the entropy form as
   stated or label the set form "(set form of Thm 5.3; spine §4A.2)".

### (d) NEW cross-paper inconsistencies (not in the pre-check)

- **Sixth citation drift (line 1084):** typed composition chains cite
  `[Sec.~5.4]` but resolve to `[Sec.~5.5]`. (Table above; HIGH.)
- **Stale bidirectional cite into cipher-maps** (line 843 there points at our
  old Thm 4.1). (1(a) above; MEDIUM, fix in companion.)
- **"Le Cam two-point" is Assouad (MEDIUM).** The Thm 5.2 sketch (line 907)
  applies the lemma to a `2^{m/2}`-packing, which is Assouad's lemma; Le
  Cam's two-point method uses exactly two hypotheses. The wrong name appears
  ~6 times including the abstract. This is also a within-family hazard
  (cross-paper-consistency C-4): cipher-maps genuinely uses Le Cam two-point
  (for M2), so naming our Assouad bound "Le Cam two-point" actively invites
  the conflation C-4 warns about. Fix: rename to "Assouad's lemma" everywhere
  it describes Thm 5.2.
- **§9 omits Measure C2 (MEDIUM completeness).** The multi-level-depth budget
  cites FPR compounding, C3 (Thm 5.1/5.2), and C1 (orbit), but not C2
  (coincidence oracle, cipher-maps Thm 8.2), which governs repeated-primitive
  composition. Add one cross-reference sentence.

---

## SECTION 2: INTRA-PAPER FINDINGS (lighter)

### Major (HIGH)
Covered in Section 1(c): A1 (FPR attribution) and A3 (orbit form/denominator)
are both cross-paper but manifest as intra-paper statements. No purely
intra-paper HIGH findings; the three prior rounds cleared those.

### Minor (MEDIUM)

**M-MED-1: §6.5 noise-mixture panel mislabeled (methodology, prose).**
Caption (line 1262) places the noise mixture in the **Centre** panel; body
(line 1292) says "Noise mixture (right panel)" and line 1305 also says
"right panel". Fix: line 1292 -> "(centre panel)" and check the body text.
Additionally the `rho=1` point carries a 2.2-bit byte-alignment confound
(`hat H=11.72` vs predicted `9.53`); state that the panel validates the
dilution trend and the `rho<1` regime, not the absolute value at `rho=1`.
(Flagged 2026-05-23 for the label; the confound-scoping is new.)

**M-MED-2: Thm 5.2 pairwise-TV constant off by 2 (logic).** The sketch states
`TV(P^(s),P^(s')) = (eps/m) d_H`; the correct value is `(2 eps/m) d_H`
(verified numerically). Does not change the `Omega(sqrt(m/N))` rate. Fix:
`(eps/m)` -> `(2eps/m)` at line 907, or hedge to `Theta(eps/m) d_H`.

### Suggestions (LOW)
1. ξ undefined at first abstract use (line 79); add "(in TV accuracy ξ)" or
   accept as standard (prose P-5).
2. §9 practical-depth paragraph is dense; optional sentence break before "In
   practice, useful cipher programs span depth 2 to 5" (prose P-4).
3. "5 seeds" in §6.5 applies to synthetic streams only; clarify the 20NG
   stream is single-corpus (methodology M-2).
4. Soften the conclusion's "complete framework" (line 1801), or back it by
   adding the C2 cross-reference (novelty N-3).
5. Four overfull hboxes (lines 588-596, 686-693, 915-927, 1384-1403); clear
   the 45pt one at 1384 (long `\texttt` paths) or update the "zero warnings"
   claim in `CLAUDE.md` to "clean compile, four cosmetic overfull boxes"
   (format F-1).
6. Add the C-10 half-sentence reminder at Table 4 (δ reported is U-lifted).

---

## SECTION 3: Detailed Notes by Domain

### Logic and Proofs
Three cross-paper claim-level findings (A1 FPR over-attribution, A2
granularity-spectrum over-attribution, A3 orbit form/denominator), the last
being the only one that changes a stated inequality (in the conservative
direction). Thm 5.2 re-verified: construction valid, distributions sum to 1,
final rate correct; two issues, a constant-factor-2 TV slip and the
Assouad-vs-Le-Cam misnomer. C-9 H* ambiguity confirmed three-way. C-10
confirmed correctly handled. Full detail in `logic-checker.md`.

### Novelty and Contribution
Thm 5.2 upgrades the headline from "standard rate" to "minimax-optimal" and
closes M11; framing is honest (credits plug-in/Assouad for the bounds, claims
only the identification that the cipher-map channel achieves them). Ownership
vs the family is clean (owns M1/C3, cites C1, omits M2 correctly). One
completeness gap: §9 should cross-reference C2. The "complete framework"
closing slightly overreaches. Detail in `novelty-assessor.md`.

### Methodology
§6.5 is a real strengthening; the one substantive item is the noise-mixture
panel (mislabel + `rho=1` confound scoping). Tables 2 and 4 unchanged and
consistent; the AND noise-floor reframing is intact and should not be
"fixed." Thm 5.1/5.2 remain empirically unvalidated, acceptable for a theory
venue with the existing acknowledgment. Detail in `methodology-auditor.md`.

### Writing and Presentation
Two MEDIUM items in reader-visible locations: the §6.5 panel mismatch (new
figure) and the "Le Cam two-point" misnomer (abstract + headline). The
optimal-rate reframing prose is crisp and not overclaimed. `H*` overload is
the one genuine notation drift vs the spine. Detail in `prose-auditor.md`.

### Citations and References
Six wrong cross-paper pointers (HIGH each), all one-token fixes; one stale
back-reference in cipher-maps (fix there); zero new intra-paper citation
defects; bibliography trim to 15 holds. Detail in `citation-verifier.md`.

### Formatting and Production
Clean compile, 25 pages, all references resolve. Four cosmetic overfull
hboxes; the "zero warnings" invariant is inaccurate and should be corrected
in documentation or by clearing the boxes. Detail in `format-validator.md`.

---

## Literature Context Summary
External scouts unavailable (Task tool); for a cross-paper round the relevant
context is the family + spine, consolidated in `literature-context.md`. The
spine §4A five-measure table (M1, M2, C1, C2, C3) is the ownership backbone:
this paper owns M1 (shared with cipher-maps) and C3. The companion label
resolutions from the `.aux` files are the evidentiary basis for the
citation-drift table. External positioning (QIF, SSE, PPE) is intact from
prior rounds; no external novelty threat.

---

## Recommendation and Prioritized Fix Order

**Recommendation: minor-revision.** No critical issues. The mathematics is
sound; every finding is mechanical. The cross-paper layer, which three prior
rounds did not examine, needs one focused editing pass.

**Fix order (highest impact first):**

1. **(HIGH, ~10 min) Six citation fixes.** Lines 193/817/999 -> `[Sec.~7.4]`;
   168/732 -> `[Sec.~8]`; 739 -> `[Prop.~8.1]`; 828/956 -> `[Sec.~8.2]`;
   772 -> `[Thm.~4.2]`; 1084 -> `[Sec.~5.5]`. Rebuild.
2. **(HIGH, ~10 min) Orbit bound (A3).** Lines 789, 1076: `2^n` -> `|X|`;
   reconcile with the entropy form of Thm 5.3 (cite as stated, or label the
   set form per spine §4A.2).
3. **(HIGH, ~10 min) FPR attribution (A1).** Reframe `thm:fpr-compounding` as
   elementary; cite cipher-maps §7.4 for gate-type framing, algebraic Table 3
   for validation.
4. **(MEDIUM, ~10 min) Assouad rename (B2/P-2).** Global "Le Cam's two-point
   method" -> "Assouad's lemma" where it describes Thm 5.2 (abstract, intro,
   Related Work, §5.1, proof sketch, conclusion). Add the C-4 dual-role
   footnote at the Thm 5.2 site.
5. **(MEDIUM, ~5 min) §6.5 panel label + confound (M-MED-1).** Line 1292 ->
   "(centre panel)"; add the `rho=1` scoping sentence.
6. **(MEDIUM, ~5 min) C-6 order.** Lines 109, 277, 429, 471, 1779 ->
   `(η, ε, μ, δ)`.
7. **(MEDIUM, ~5 min) C-9 H* disambiguation sentence** after Thm 3.1.
8. **(MEDIUM, ~3 min) §9 add C2 cross-reference (N-2).**
9. **(MEDIUM, ~3 min) Granularity-table attribution (A2).**
10. **(LOW) Suggestions 1-6** as a final sweep; and tell the author the
    `[Theorem~4.1, part~3]` fix belongs in the cipher-maps companion.

Total estimated effort: under 90 minutes. With items 1 to 9 landed, the paper
is consistent with the family and ready for venue submission. The headline
science (Thm 5.1 + 5.2 compositional leakage at the optimal rate) is correct
and well-positioned; this round only tightens its interface to the rest of
the program.

---

## Review Metadata
- Specialist roles executed by the area chair directly (Task tool
  unavailable in this environment, as in the 2026-04-29 round). Per-role
  reports: `logic-checker.md`, `novelty-assessor.md`,
  `methodology-auditor.md`, `prose-auditor.md`, `citation-verifier.md`,
  `format-validator.md`, plus `literature-context.md`.
- Cross-verifications performed:
  - All 6 citation-drift fixes confirmed against companion `.aux`
    `\newlabel` entries (cipher_maps.aux, algebraic main.aux): verified.
  - Orbit denominator: confirmed `2^n` in our paper (lines 789, 1076),
    entropy form in algebraic Thm 5.3, `|X|` set form in spine §4A.2:
    verified, three-way discrepancy real.
  - FPR formulas: confirmed absent from cipher-maps §7.4 (interval
    arithmetic only), present in algebraic Table 3: verified.
  - Thm 5.2 pairwise TV: recomputed numerically, `(eps/m)` should be
    `(2eps/m)`: verified.
  - Assouad vs Le Cam: confirmed `2^{m/2}`-packing in the sketch (line 907),
    inconsistent with "two-point": verified.
  - Bidirectional cipher-maps line 843 -> our old Thm 4.1: verified stale.
  - Build: fresh `make`, exit 0, 25 pages, 4 overfull hboxes, all refs
    resolve: verified.
- Hallucination check: every quoted manuscript line (789, 999, 907, 1076,
  1801, the C-6 tuple lines, the §6.5 caption/body lines) re-read against
  source. No discrepancies.
- Disagreements among roles: none. Findings are mutually consistent.
- Relationship to 2026-05-23: that round caught the §6.5 panel label and the
  Assouad naming but was not cross-paper-citation informed; the six citation
  fixes, the orbit denominator, the over-attributions, C-6, C-9, the stale
  back-reference, and the Thm 5.2 constant are new this round.
