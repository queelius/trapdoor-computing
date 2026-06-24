# Multi-Agent Review: "The Entropy Ratio" (post-repositioning)

**Date:** 2026-06-10
**Commit reviewed:** 65b0d0a (extra-care repositioning pass)
**Scope:** Verify the 2026-06-09 repositioning landed cleanly, two-scale
separation reframed as a *known phenomenon given a sharp matching-bounds
rate* (not a discovery); new Related Work paragraphs scope novelty
correctly and match cited papers; 15 added citations used accurately.
**Specialists run:** logic-checker, novelty-assessor, citation-verifier,
prose-auditor, methodology-auditor. Literature scouts deliberately
skipped, the literature was exhaustively surveyed the same day
(`.papermill/prior-art/2026-06-09-ecosystem-survey.md`).
**Target venue under consideration:** CSF vs PoPETs.

---

## Verdict: MINOR-REVISION (fixes applied 2026-06-10, commit follows)

The repositioning is **substantially successful and honest**. Across all
five specialists there are **zero critical issues, zero logical defects,
zero novelty overclaims, and zero citation misrepresentations**. The
genuinely novel result (the sharp, irreducible compositional rate) is now
the headline; the borrowed scaffolding (the qualitative two-scale
phenomenon, Fannes, Fisher-info privacy, homophonic substitution) is
explicitly labeled as borrowed at each point of use. The paper moved from
"most bibliographically exposed of the three top papers" (survey Part VII)
to honestly scoped.

---

## Convergent finding (the one thing all reviewers circled)

The only substantive note is **perceptual, not factual**: the core
compositional theorem reduces the cipher-map joint-recovery problem
*exactly* to textbook discrete-distribution estimation (plug-in upper
rate + standard Assouad lower rate), and the paper's own MI-preservation
identity advertises that the cipher layer is statistically invisible to
the estimator. A theory referee can therefore read the headline as "an
ordinary estimation rate with a security wrapper." The paper's real
contribution, the **irreducibility** of that rate to *any* per-cipher-map
parameter (δ included), is the non-obvious, genuinely new claim, and it
competes for prominence with the (textbook) rate formula in the abstract
and Contribution 1.

**Cheapest insurance (applied):** lead with the irreducibility *before*
the rate expression, so the headline a skimming reviewer anchors on is
the novel part, not the textbook part.

---

## Per-specialist summary

| Specialist | Verdict | Headline finding |
|---|---|---|
| **logic-checker** | SOUND | No logical defect introduced. Scoping consistent across abstract/intro/contributions/related-work/conclusion; no "we discovered the separation" anywhere. All 4 flagged theorems retain correct forms. Two MINOR: cosmetic `C(D)` notational seam in Thm 4.1 proof (pre-existing, not reframe-induced); the "literature does not contain" assertion is a negative-existence claim made safe by the "with a matching minimax rate" qualifier. |
| **novelty-assessor** | HONEST / defensible | Zero residual hype (grep-confirmed; only hit is the negative "we do not claim novelty there"). Sufficient for CSF; marginal-but-plausible for PoPETs. Biggest risk = theorem-depth *perception* (above). Soft items: "minimax-optimal for the adversary" → "rate-optimal"; "moves it" register dip. |
| **citation-verifier** | 14/15 clean | All 15 exist with correct venues/pages; all 15 used accurately. ONE metadata fix: `chen2024revisiting` middle author "Yang, Ji" → "Yang, Yue" (verified twice via Springer). `jendal1989information` year 1990-vs-1989 is acceptable (proceedings physically published 1990). |
| **prose-auditor** | Submission-quality | Three targeted line edits: split the 45-word "Second difference" FSE sentence (the single weakest passage, highest-stakes differentiation, "bounds/bounds" polarity collision); "moves it" → "lowers this rate"; optionally demote the third inline Fannes restatement to a back-reference. Fisher-info remark (731-740) and QIF-composition paragraph (293-304) rated exemplary. |
| **methodology-auditor** | Sound; venue-dependent | No critical/validity issues; three-way rate validation (Monte Carlo + estimator bake-off incl. oracle cheater + realized attack) called unusually strong. Two MAJOR-for-PoPETs / MINOR-for-CSF: single non-standard corpus (20NG, not a standard SSE benchmark); the §6.7 realized attack fixes m=64 and sweeps only N, so the dimension factor |Y₁||Y₂| is shown only in the abstract sampler. Minor: library naming (cipher-maps/trapdoor-maps/trapdoor_maps); seeds in code not enumerated in paper; n=2 granularity cell; FPR floor ratios. |

---

## Fixes applied (2026-06-10)

All high- and medium-confidence, venue-independent items:

1. **`chen2024revisiting` author**, "Yang, Ji" → "Yang, Yue" (`references.bib`). [citation-verifier]
2. **Lead with irreducibility**, Contribution 1 heading + opening reordered to state "no per-map parameter changes the rate" *before* the rate formula; heading now "Compositional leakage: a rate no per-map parameter can move (main result)". [novelty-assessor, the cheapest insurance]
3. **Intro register**, "no per-cipher-map parameter, δ included, lowers this rate" (was the colloquial "moves it" + em-dash pileup). [prose + novelty]
4. **"minimax-optimal for the adversary" → "rate-optimal"** (§5 "Why this matters", L1120), matches the theorem title; the rate-vs-constant nuance (oracle beats the constant 0.73×, not the rate) is now honest. [novelty-assessor]
5. **FSE "Second difference" sentence split** (§2), the 45-word sentence broken in two; "bounds the marginal / does not bound joint" polarity collision replaced with "flattens the marginal / leaves the joint unbounded". This is the highest-stakes differentiation sentence (FSE/encrypted-database referee). [prose-auditor, single weakest passage]
6. **Library naming unified**, paper now says `trapdoor-maps` (the actual package name, verified against `pyproject.toml` + the `from trapdoor_maps import` calls) everywhere, with the import module `trapdoor_maps` clarified once and the repo URL preserved. [methodology-auditor]

**Build after fixes:** clean, 31pp, 0 undefined citations, 0 LaTeX
warnings, no overfull box >18pt. All four mathematical landmines verified
intact (Fannes linear not Pinsker quadratic; K∝D with the single 1/D as
labeled contrast; Assouad not Le Cam; orbit denominator |X|).

---

## Deferred: venue-gated (do NOT do for CSF; required for PoPETs)

Per the methodology-auditor, these are the gating changes if PoPETs is
chosen; they are immaterial for CSF (where the corpus only supplies a
realistic D and the rate is validated corpus-independently):

- **Sweep m on the realized attack (§6.7)**, run the existing 12-seed
  harness at m ∈ {16, 64, 256} so the *deployed construction* (not just
  the abstract sampler) exhibits the full Θ(|Y₁||Y₂|/N) law. This is the
  single most important empirical improvement; low-cost (harness already
  parameterizes Y₁,Y₂). Upgrades the headline from "abstract rate +
  single-m construction spot-check" to "construction reproduces the rate".
- **Add one standard SSE corpus** (Enron / Wikipedia / TREC) or route the
  recovery attack through LEAKER (`kamara2022sok`), which the paper now
  cites as the framework of record. Answers the under-evaluation critique
  a leakage-abuse referee will raise.
- **Pin a library release tag/DOI** for bit-reproducible tables (artifact
  evaluation). Seeds are fully deterministic in code; this is a
  documentation gap, not a missing control.

## Deferred: optional polish (taste, low priority)

- Demote the third inline restatement of the Fannes formula in Related
  Work (≈L306) to a back-reference, if trimming. Medium confidence;
  deliberate "drumbeat" repetition is currently on the right side of the
  line. Left as-is.
- Mark FPR floor-dominated cells in Table 2 (dagger + "floor-limited")
  rather than printing a ratio the prose says to ignore. Minor.

---

## Venue read (synthesis)

Two of three relevant signals + the paper's own CLAUDE.md converge on
**CSF**:

- **CSF** routinely publishes papers whose contribution is converting an
  empirical/heuristic security observation into a tight information-
  theoretic bound, exactly this paper's shape. The Assouad lower bound is
  a complete, self-contained piece of minimax theory; the matching Θ with
  exact MI preservation + the oracle-cheater bake-off is a reviewer-proof
  package. **Requires no additional experiments.** Methodology-auditor:
  "sufficient as-is"; novelty-assessor: "adequate". The single-corpus
  concern is moot at CSF.
- **PoPETs** is more systems-leaning and runs artifact evaluation; a
  leakage-abuse referee will read one non-standard corpus + single-m
  realized attack as under-evaluation. Plausible-accept *only after* the
  three venue-gated empirical items above. More audience reach, real extra
  work.

**Recommendation: CSF**, best fit for a matching-bounds theorem, lowest
reviewer-variance, submittable after this polish with no new experiments.
PoPETs is viable but gates on ~1 day of experiments + a standard benchmark.
