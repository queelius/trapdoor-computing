# Submission tracker: Codec-Controlled Retrieval (towell2026codec)

Single place that says where this paper stands across venues. Update on every status
change (prepared / submitted / decision / camera-ready). Papermill working state is in
`.papermill/state.md`; this file is the submission ledger.

## Current state (as of 2026-06-10)

- **SUBMITTED to ACM TOPS, 2026-06-10. Manuscript ID TOPS-2026-06-0371.** Single-blind
  (the ScholarOne flow required no anonymized manuscript), so the de-anonymized 31pp acmsmall
  PDF (`venue/tops/main.pdf`) went in, with a cover letter drafted in-voice, 3 keywords
  (searchable encryption / frequency hiding / retrieval data structures), funding=none,
  prior-history=NONE, and all ACM policy attestations. Now under editorial processing; await
  reviewer assignment then first decision (no fixed ETA; first decisions typically run months).
  The exclusive-submission attestation binds the paper to TOPS while under review, so PoPETs and
  other venues are fallbacks only if TOPS rejects or the paper is withdrawn.
- **Paper**: content-complete and reviewed. Multi-agent editorial review 2026-06-09
  (report: `.papermill/reviews/2026-06-09/review.md`, verdict minor revision); the
  revision pass and a full restructure (spine + appendix Refinements) are done.
- **Canonical source**: `paper/codec_retrieval.tex` + `paper/refs.bib` (article class,
  de-anonymized, 33 pp). This is the content source of truth.
- **HOLD LIFTED (2026-06-10)**: the fresh-audit corrections #5-#10 were reconciled in another
  session and COMMITTED to this branch (cd7c709 FreqDist scoping; 0834c11 T1-T4c #5-#7 + re-pin
  maph 660110a; 5dca8ac second-half #8-#10 + re-pin maph 402c8ca): the manuscript, BOTH venue
  ports, source/construction-note.md, artifact/note + PROVENANCE, the three updated gates, and
  CLAIMS/FINDINGS. Verified in this working copy (full-support 18x, corruption-budget 16x,
  gap-language 11x); venue/tops rebuilt clean (31pp, 0 errors/undefined/overfull, corrections in
  the rendered PDF, acmsmall + AI disclosure intact).
- **#5 abstract residual: RESOLVED (commit befcb27)**: the abstract, intro, freqdist-real
  theorem-statement, and conclusion lines were aligned to the gap-independent form across
  canonical + both venue ports; the 3 legitimate "the M1 law is frequency-independent" (T3)
  spots were kept. The submitted PDF reflects this.
- Author venue history (metafunctor.com/publications) is conference-heavy (Complex Networks 2025,
  ICCCI/ICCCNT IEEE confs, ISCS 2026); conference option is on the table alongside TOPS.
- **Why ACM TOPS**: a rolling-deadline journal (no fixed deadline to miss), a 35-page limit
  with no per-page fees, and the cogirth / randomized-encoding / graded refinements stay
  first-class **in-body**. Submitted from `venue/tops/` (acmsmall, 31 pp, de-anon, single-blind).
  The PoPETs version is retained as a fallback if TOPS rejects.

## Venue status

| Venue | Status | Format | Body limit | Deadline model | Source | Notes |
|---|---|---|---|---|---|---|
| **ACM TOPS** | **SUBMITTED 2026-06-10 (TOPS-2026-06-0371)** | acmsmall (single-col) | 35 pp, no per-page fees | rolling | `venue/tops/` | 31 pp, single-blind, de-anon; under editorial processing |
| IEEE TIFS | considered, declined | IEEEtran 2-col | no cap but $220/pg overlength from p11 | rolling | not built | strong fit, but ~$900-1400 overlength fee at this length; declined in favor of TOPS (no fee) |
| Designs, Codes & Cryptography | candidate (coding identity) | Springer journal | generous | rolling | to build | best home for the GF(2)/cogirth/coset/wiretap math; privacy framing becomes secondary motivation |
| ESORICS 2027 | candidate (conference) | LNCS | 16 pp (+ appendix; 20 total) | ~Jan 2027 (fixed) | to build | roomier than PoPETs but still capped + fixed deadline; ESORICS 2026 deadline (Jan 9 2026) passed |
| IEEE Trans. Inf. Theory | fallback (prestige / identity shift) | IEEEtran | none | rolling | not built | top prestige, no page limit, but recast around information theory; ~12-18 mo review |
| PoPETs 2027 (Issue 3) | fallback only (TOPS holds the paper) | acmart sigconf + popets | 12 pp | paper 2026-11-30 | `venue/popets/` | ready; submit ONLY if TOPS rejects/withdrawn (exclusive-submission attestation) |

Status vocabulary: candidate -> preparing -> prepared -> submitted -> under review ->
{major revision | minor revision | accept | reject} -> camera-ready -> published | withdrawn.

## PoPETs 2027 (primary)

- **Source**: `venue/popets/main.tex` + `venue/popets/refs.bib` (anonymized). Build: `cd
  venue/popets && make`. Mechanics and the documentclass swap: `venue/popets/NOTES.md`.
- **Readiness**: body = 12 pages (fits the limit); builds clean (0 errors, 0 undefined);
  anonymized (verified 0 identity strings in the PDF); AI-disclosure section present;
  ~0 visible overflow boxes.
- **Remaining before upload**:
  - [ ] Drop official `popets.sty` into `venue/popets/` (author kit at
        submit.petsymposium.org), do the documentclass swap (NOTES.md), rebuild, re-check
        the body is <= 12 pp.
  - [ ] Human proofread of the anonymized PDF (esp. the body Refinements summary and the
        appendix seam, which are new).
  - [ ] Upload at submit.petsymposium.org (HotCRP); paste the AI-disclosure form text
        (NOTES.md) into the submission form.
  - [ ] On accept/shepherd: de-anonymize, mint the Zenodo artifact DOI, cite it, prepare
        camera-ready (13 pp allowed for major-revision/accept-with-shepherding).
- **2027 paper deadlines** (AoE): Issue 1 May 31 2026 (passed), Issue 2 Aug 31 2026
  (**registration window missed**, per author 2026-06-09), **Issue 3 Nov 30 2026 (next
  target)**, Issue 4 Feb 28 2027. PoPETs registers the title/abstract BEFORE the paper PDF
  deadline; confirm Issue 3's exact registration date on the submission server.
- **Format reqs** (verified petsymposium.org, 2026-06-09): acmart sigconf +
  `\usepackage{popets}`; body <= 12 pp excluding bib and clearly-marked appendices;
  double-blind; mandatory AI-use disclosure (paper + HotCRP form); AI cannot be an author.

## Decision log

- 2026-06-10: **SUBMITTED to ACM TOPS** as Manuscript ID **TOPS-2026-06-0371** (sole author,
  date 10-Jun-2026). Single-blind (the ScholarOne flow required no anonymized file). Driven via
  Playwright through ScholarOne: uploaded the corrected 31pp PDF, pasted the #5-aligned
  <=250-word abstract, added 3 keywords, drafted a cover letter in-voice, answered funding=none,
  supplementary=No, prior-history=NONE, and all ACM policy attestations. The #5 abstract residual
  was aligned first (commit befcb27). Next: editorial processing, reviewer assignment, first
  decision.
- 2026-06-09: Missed the PoPETs Issue 2 registration window. The prepared version waits (Issue
  3, paper 2026-11-30) as a fallback, but the author chose to reconsider a roomier venue so the
  refinements stay in-body. Ran a venue survey (papermill:venue): ESORICS 2026 deadline (Jan 9
  2026) already passed, confirming conferences carry the same missed-deadline risk; pivoted the
  recommendation to a rolling-deadline journal. Ranked shortlist: IEEE TIFS (lead) > ACM TOPS >
  DCC (coding identity) > ESORICS 2027 (conference) > IEEE TIT (prestige/identity shift). Venue
  pick pending; then build venue/<chosen>/ from the canonical 33pp article.
- 2026-06-09: Author chose IEEE TIFS. Then found TIFS (IEEE SPS journal) charges overlength
  fees from the 11th published page at $220/page; the full in-body paper (~15-17 IEEEtran pp)
  implies ~$900-1400 in fees. Surfaced the tradeoff: TIFS (top privacy journal, but per-page
  overlength fees) vs ACM TOPS / Springer DCC (no IEEE-style per-page overlength fees, also
  rolling, refinements in-body free). Awaiting author call: accept TIFS fees, trim toward 10pp,
  or switch to a no-fee journal.
- 2026-06-09: Author switched to **ACM TOPS** (no per-page fees). Built `venue/tops/` from the
  canonical article in acmsmall (single-column, so the PoPETs 2-column overflow issues did not
  recur): 30 pp, 0 errors, 0 undefined, 0 overfull, refinements in-body (sec:refinements p15;
  appendix only the two proofs from p28), AI disclosure added, de-anonymized. Comfortably under
  the 35-page TOPS cap. Remaining: confirm TOPS blinding and (if double-anonymous) apply the
  anonymization deltas; proofread; ACM upload. PoPETs build retained as the fallback.

## Companion coordination

- `cipher-maps` (`towell2026ciphermaps`): the companion framework, also PoPETs-targeted,
  still in article class. This paper cites it (anonymized for review). Once this paper has
  a stable citation/DOI, cross-update cipher-maps, and vice versa.

## Artifact / DOI

- Self-contained pinned artifact at `artifact/` (8 Catch2 gates + Python cross-checks).
  Zenodo deposit and DOI are a camera-ready step (use the anonymized artifact for review);
  see `SUBMISSION-CHECKLIST.md`.
