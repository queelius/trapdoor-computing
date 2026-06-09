# Multi-Agent Editorial Review Report

**Date**: 2026-06-09
**Paper**: Codec-Controlled Retrieval: Structural Frequency-Hiding from the Non-Member Channel of XOR Retrieval (`towell2026codec`)
**Manuscript**: `paper/codec_retrieval.tex` (32 pp, builds clean via `cd paper && make`)
**Target venue**: PoPETs 2027 (construction/systems companion to cipher-maps)
**Recommendation**: **Minor revision** (no incorrect core result; one critical front-matter wording bug, fixed in this pass; remainder are citation hygiene, structural resequencing, methodology robustness, and venue formatting)

> Process note: eight specialists were dispatched in parallel from the main loop
> (not as nested subagents), so the orchestration limitation that forced the
> 2026-06-05 review to run every lens serially did not recur. Lenses: logic-checker,
> methodology-auditor, novelty-assessor, prose-auditor, citation-verifier,
> format-validator, literature-scout-targeted, literature-scout-broad. This review
> focused on the 2026-06-08 discovery integration (T4b/T4c/T5b/T5c/randenc), which the
> prior review (22 pp) never saw. Critical findings were cross-verified across lenses.

---

## Summary

This remains a strong, unusually honest paper. The headline (the sharp GF(2)-span
control threshold, T4) is, after exhaustive external search, **genuinely novel and
SAFE**: no prior work characterizes the non-member output value distribution of any
retrieval structure, and the 2025 SOTA (Hu-Kuszmaul FOCS 2025; Learned Static Function
DS 2025) explicitly leaves it "arbitrary." The five newly-integrated theorems are
**mathematically sound**: the logic-checker independently recomputed the `thm:randenc`
skewed counterexample, the `thm:realizable` `{2,2,3,3,3,3}` hit-geometry obstruction,
the uniform-unreachability diagnosis, and the full `thm:cogirth-graded` 3/6/9 cascade,
and all four FINDINGS.md subtleties are correctly scoped in the manuscript. Every
E1-E4 number matches the committed CSVs exactly.

There is **one critical defect**, and it is a front-matter wording bug, not a wrong
result: the abstract and introduction state that an adversary with *unboundedly many
adaptive queries* has FreqDist advantage at most `delta(p0)+delta(p1)` in the *real*
construction. That is false for `delta > 0`; the bound is a *single-observation* cap,
which is exactly how the body theorem is (correctly) scoped. This is the prior review's
M1, fixed in `thm:freqdist-real` but never propagated to the abstract/intro. It is
fixed in this pass (see Immediate Fixes). The remaining work is presentation
(resequencing the buried headline, one self-collision differentiation paragraph),
methodology robustness (large-N replication counts), citation hygiene (one fabricated
author list, one wrong venue), and the expected venue formatting (pets.cls,
anonymization, keywords).

**Finding counts**: Critical 2 · Major 9 · Minor ~14. Two Criticals and two Majors are
fixed immediately below; the rest are itemized for an author/polish pass.

---

## Cross-verified critical findings

### C1 (CRITICAL, cross-verified x3): Abstract and intro overclaim multi-query security in the real construction

- **Lenses**: logic-checker (C1, primary), prose-auditor (m6, conclusion echo), methodology-auditor (the delta is the *measured* per-build quantity).
- **Locations**: abstract (the FreqDist sentence); intro lines 188-194; echoed in conclusion ~1778.
- **The error**: "an adversary ... even with unboundedly many adaptive queries ... has advantage ... at most `delta(p0)+delta(p1)` in the real construction." For two *fixed, distinct* laws at TV distance `d = delta(p0)+delta(p1) > 0`, an adversary drawing `n` i.i.d. non-member outputs has optimal advantage `TV(law0^n, law1^n) -> 1` as `n -> infinity`. So the multi-query advantage is NOT bounded by `d`; only the **single-observation** advantage is (Le Cam two-point bound), which is precisely how `thm:freqdist-real` (lines ~1315-1331) is scoped, with its explicit "(No factor of 2 appears...)" note. The idealized `Adv = 0` for any query count is correct because there the two laws are *identical*.
- **Verification**: independently confirmed by recomputation. The body theorem is correct; only the abstract/intro/conclusion compressions drop the per-observation scope.
- **Fix (applied)**: abstract and intro reworded so "any number of adaptive queries -> advantage zero" attaches only to the idealized model, and the real-construction claim is the per-observation bound `<= delta(p0)+delta(p1)`. The deeper many-query argument (more queries let the adversary identify the per-build law, but that law is frequency-*independent* by `thm:freqindep`, so no frequency signal is recovered) should be the body's framing; see M-LOGIC-1 for the proof-prose tightening that makes this rigorous.

### C2 (CRITICAL, web-verified): `cheng2019pmte` has a fabricated author list

- **Lens**: citation-verifier (web-verified against USENIX/Semantic Scholar).
- **Current bib**: `Cheng, Haibo and Li, Zhixiong and Wang, Ping and Zhao, Chao`.
- **Actual authors**: Haibo Cheng, Zhixiong Zheng, Wenting Li, Ping Wang, Chao-Hsien Chu (five). The bib collapses "Zhixiong Zheng" + "Wenting Li" into a phantom "Li, Zhixiong", drops the fifth author, and invents "Zhao, Chao". Cited x4, including the Tier-A baseline paragraph.
- **Fix (applied)**: author field corrected to the verified five-author list.

---

## Major findings (itemized)

### M-CITE-1 (Major, applied): `dietzfelbinger2019gauss` wrong venue
STACS -> **ESA 2019** (LIPIcs 144, pp. 39:1-39:18). Dietzfelbinger-Walzer had a *different* paper at STACS 2019, which makes the slip plausible but wrong. Fixed in this pass.

### M-NOV-1 (Major): Self-collision: `thm:randenc` invariance overlaps the cipher-maps sibling, unflagged
- **Lens**: novelty-assessor (verified against `papers/cipher-maps/paper/cipher_maps.tex` `prop:rand-encoding` lines 2046-2083, `def:rand-encoding` 2015-2021).
- The decoded-law invariance under within-class randomization, *and its saturation precondition*, already appear in the cipher-maps companion. The codec paper's related-work point (2) differentiates cipher-maps only on backends and the query-marginal-vs-non-member axis; it is silent that the sibling already has a randomized-encoding invariance proposition. Both papers target PoPETs the same cycle, so a referee reading both will see it.
- The codec paper's genuine delta IS real: (a) the white-box solution-matrix divergence `z' != z` (no analogue in the random-oracle backend), and (b) the exact skewed-codec failure boundary (the `{A,A,B}` counterexample) that the sibling leaves as an unexamined precondition.
- **Fix (deferred, author judgment)**: add one differentiation sentence in related-work (2) and the `sec:randenc` preamble isolating (a)+(b) as the new content. This *strengthens* the contribution; it does not weaken it.

### M-METH-1 (Major): "Straddles the floor" is honest, but the abstract over-compresses it
- **Lens**: methodology-auditor (MAJ-1). Two of four E3 means (1e4: 0.00352; 1e6: 0.00352) sit *above* the analytic floor 0.00334; only 1e5 and 1e7 sit below. "Straddle" is accurate; the abstract's "at or below the query-sampling floor" reads as if every point were under it.
- **Fix (applied to abstract as part of C1 rewrite)**: "straddle the query-sampling floor." No change to sec:t5, which is already honest. (Does not affect the security theorem, whose bound holds for any delta.)

### M-METH-2 (Major): Understated uncertainty at large N
- **Lens**: methodology-auditor (MAJ-2). E3's "flat in N" rests on reps = 5 (1e6) and 3 (1e7) with *z*-intervals; at n=3 a t-interval is ~2.2x wider (t_{2,.975}=4.30). "Overlapping intervals" is then near-automatic and weak evidence for flatness.
- **Fix (deferred)**: raise reps to >=10 at every N (cost ~5 min at 1e7) OR report t-intervals with stated d.o.f. and soften "overlapping intervals." This touches the artifact/data, so it is an author/experiment action.

### M-PROSE-1 (Major): The headline is buried before its security payoff
- **Lens**: prose-auditor (M1). The threshold lands at `thm:threshold` (~601), then ~120 lines of graded regime + realizable set + randomized encoding + two cogirth theorems intervene before the security section (~1218) cashes it out. The pre-splice spine (gap -> characterization -> threshold -> idealized-to-real -> security) is interrupted by robustness/refinement material.
- **Fix (deferred, structural)**: resequence so threshold -> idealized-to-real -> security runs uninterrupted, moving the robustness/refinement clusters into a post-security "Refinements and robustness" section, OR add a roadmap sentence at the headline pointing to the security destination. No content cut.

### M-PROSE-2 (Major): `sec:randenc` misfiled inside the threshold section
- **Lens**: prose-auditor (M2). Randomized encoding is a confidentiality result, not a threshold result; it interrupts the mass-profile-to-real-gap line and opens with a backward reference. Move it adjacent to security or into the refinements section, opening with its own motivating question.

### M-PROSE-3 (Major): Contributions list items C/D overloaded
- **Lens**: prose-auditor (M3). Five theorems across two bullets, with the undefined compound "mass-over-codespace-share" (only named at ~770). Split so each named theorem gets at most one clause; gloss or defer the deep qualifications.

### M-FORMAT-1 (Major): Wrong document class
- **Lens**: format-validator. `\documentclass[11pt]{article}` must become `pets.cls`. PoPETs full papers are 25+2 pages; at 32 pp in article class the page budget must be re-checked after the class is applied (rendered length will differ). Tracked in SUBMISSION-CHECKLIST.

### M-FORMAT-2 (Major): No `\keywords{}`
- **Lens**: format-validator. PoPETs requires a keyword list after the abstract. Suggested: retrieval data structures, frequency hiding, XOR retrieval, GF(2) linear algebra, leakage suppression.

---

## Minor findings (consolidated)

**Logic** (logic-checker): M-LOGIC-1 (Major-ish, deferred) the `thm:freqdist-real` proof prose (1334-1342) itself conflates "decide which of two fixed laws" with the per-observation bound; recast to separate (i) single-observation advantage `<= TV`, (ii) many-query *can* identify the build but the difference is frequency-*independent* noise, so frequency recovery stays delta-bounded. M-LOGIC-2 (Major-ish, deferred) saturation-sufficiency in `thm:randenc(2)` (lines 850-855) is asserted at the decisive step (why a full projection cannot be lost when short generators contribute); supply the short lemma or label it "verified exhaustively, closed form deferred." m1 the `q(A)=1/2` "forces TV >= 1/4" justification is loose (the single TV coordinate is 1/8; the bound is correct via total-excess). m2 `ex:cogirth-graded` "9 of 12 columns carry its single top bit" mis-attributes the set top bit to A (A's codeword is 0). m3 the source-of-record note + FINDINGS.md still carry the superseded `2(...)` bound (sync hazard; update upstream).

**Methodology** (methodology-auditor): MIN-1 `intermediate_zipf` max share is ~0.43, not the stated ~0.34 (Table 4 descriptor; the acc value is correct). MIN-2 the "floor" is n_q-dependent; E1/E2 ran at n_q=5e4 (floor ~0.0047), E3 at 1e5 (floor 0.00334); the single-floor language should be qualified. MIN-3 state the replication policy. MIN-4 the E4 near-saturation CI uses a one-SE tolerance; caption accordingly or use Clopper-Pearson. MIN-5 surface the realizable-band-vs-raw-set caveat (currently only in the appendix's last sentence) once in the body at `thm:idealized`.

**Prose** (prose-auditor): M4 (Major-ish) several spliced sentences are overlong/over-hedged vs the author's voice (esp. intro randenc preview 196-199, cogirth scope nuance 1108-1116); break into one-claim-per-sentence. m1 "saturated" used in intro (~198) ~600 lines before its definition (~831). m2 informal float labels ("punchline", "witness"). m3 the "rank governs control, cogirth governs robustness" couplet appears 4x at equal depth; keep abstract + the body display, reference elsewhere. m4 "junk is a designable object" motif still 4x (prior review's m6 partially unaddressed). m5 `rem:genericity`/M1-on-image remark still interrupts the frequency-independence payoff (prior review suggestion 5). m6 conclusion's "capping the advantage at that distance" needs the "fixed separation no number of queries can widen" guard (same root as C1).

**Format** (format-validator): overfull 38.3pt at line 1747 (related-work paragraph; one-line reflow given), 0.82pt at 1377 (negligible). Anonymization inventory complete (author block line 58; first-person self-citations at 146, 219, 1656, 1714-1718; `maph` at 1483; self-cite bib entries) for the double-blind pass. Artifact paragraph must swap the moving-branch reference for the Zenodo DOI at camera-ready.

**Citations** (citation-verifier): `reviriego2024ixor` keyed on 2nd author (cosmetic); `gluesingluerssen2014fourier` key-year 2014 vs field-year 2015 (both defensible). `kuszmaulputterman2025incremental` author list flagged-approximate in state.md is in fact **verified correct** (5 authors, pages match SODA 2025). All other 20+ cites verified accurate, including all "must-differentiate" claims (Honey/DTE assumes uniform seed; PANCAKE/FSE online; Filic-Paterson is membership-PDS; NKW is the threat).

---

## Novelty verdict (both scouts: SAFE)

- **Headline (T4 span threshold) SAFE.** No prior characterization of the non-member value distribution of any retrieval/AMQ structure exists; the true novelty-killer (a Honey/DTE-backed retrieval structure shaping its off-support output) was searched for directly and does not exist. Tier A (codec-shapes-output) genuinely pre-exists in the author's bernoulli_maps (verified) and Honey Encryption, and is correctly demoted, not headlined.
- **Structural frequency-hiding (Claim 2) SAFE**, cleanly separated from online (PANCAKE/FSE/volume-hiding) and cipher-layer lineages.
- **Cogirth / randomized-encoding (Claim 3) SAFE as applications** of classical primitives (dual distance, wiretap coset coding), correctly cite-and-differentiated; the only risk is the M-NOV-1 self-collision wording.

**Suggested new citations** (from the scouts; none threatens novelty, all strengthen):
- Major: *Learned Static Function Data Structures* (Hermann, Lehmann, Vinciguerra, Walzer 2025, arXiv 2510.27588) - nearest mechanical cousin (per-key codes over value distributions), a DS referee will know it; *IHOP* (Oya-Kerschbaum, USENIX 2022) - breaks PANCAKE under correlated queries, the boundary a referee will probe; *SWAT* (VLDB 2024) - the modern PANCAKE-successor to compare against.
- Minor: *Modern Minimal Perfect Hashing: A Survey* (Lehmann et al., ACM CSUR 2025) as the single authoritative "treats non-member output as junk" anchor; *Non-Malleable Codes from the Wire-Tap Channel* (the crypto home of the coset primitive behind randenc); Kellaris et al. CCS 2016 (reconstruction-attack pillar); the 2024 FSE revisit; Filic et al. ASIACRYPT 2024 (freshness on the cited AMQ-PDS line).
- Verify before submission: that `hu2025retrieval` and `patel2019volumehiding` bibkeys resolve to the intended papers (both were flagged "not yet in refs.bib" historically; format-validator confirms 0 undefined cites now, so they resolve, but confirm they point to the right entries).

---

## What is strong (do not soften)

1. The T4 span threshold: clean, correct, genuinely new, honestly framed (classical coset-counting lemma -> new application + new consequence).
2. The A/B/C/D novelty tiering, verified honest end-to-end against the actual prior sources.
3. The five new theorems are mathematically sound and faithfully transcribed; all four FINDINGS.md subtleties correctly scoped.
4. PROVEN-vs-MEASURED discipline is exemplary (the T5 magnitude is in a remark, never a theorem; "every theorem has a passing empirical check" is accurate precisely because the open part is not a theorem).
5. Every E1-E4 number matches the committed CSVs exactly; E2's noise-floor baseline and E4's MC-vs-closed-form check are textbook-correct controls.
6. The security framing as INDEPENDENCE (not comparative leakage) and the honest opposite-pull reconciliation (no single optimal codec) pre-empt the two strongest referee objections.

---

## Recommended action plan (priority order)

1. **[done this pass]** C1 abstract+intro multi-query rewrite; C2 cheng author list; M-CITE-1 dietzfelbinger venue; M-METH-1 "straddle" wording.
2. **[author judgment, one paragraph each]** M-NOV-1 self-collision differentiation; M-LOGIC-1 proof-prose tightening; M-LOGIC-2 saturation-sufficiency lemma-or-label.
3. **[structural, a focused pass]** M-PROSE-1/2/3 resequence the buried headline, relocate `sec:randenc`, split the contributions bullets.
4. **[experiment]** M-METH-2 raise large-N reps or report t-intervals.
5. **[citations]** add the 3 Major scout cites; the minors as desired; m3 sync the upstream note's bound.
6. **[pre-submission, tracked]** M-FORMAT-1/2 pets.cls + keywords; anonymization; Zenodo DOI; the two minor overfull reflows.

---

## Immediate fixes applied in this pass

- Abstract: reworded the FreqDist sentence so "any number of queries -> advantage zero" attaches to the idealized model only; the real construction now states the per-observation bound; "at or below the floor" -> "straddle the floor" (C1 + M-METH-1).
- Intro (lines 188-194): same per-observation correction (C1).
- `refs.bib`: `cheng2019pmte` author list corrected to the five verified authors (C2); `dietzfelbinger2019gauss` venue STACS -> ESA with LIPiCS series/volume/pages (M-CITE-1).
- Rebuilt: 32 pp, 0 undefined refs/cites, 0 hard errors.

Not applied (need author judgment or larger restructuring): the conclusion echo (prose m6) and proof-prose (M-LOGIC-1) of the same C1 root, M-NOV-1, M-PROSE-1/2/3, M-METH-2, the new citations, and the pre-submission venue/anonymization items.
