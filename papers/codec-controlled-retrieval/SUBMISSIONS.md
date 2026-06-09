# Submission tracker: Codec-Controlled Retrieval (towell2026codec)

Single place that says where this paper stands across venues. Update on every status
change (prepared / submitted / decision / camera-ready). Papermill working state is in
`.papermill/state.md`; this file is the submission ledger.

## Current state (as of 2026-06-09)

- **Paper**: content-complete and reviewed. Multi-agent editorial review 2026-06-09
  (report: `.papermill/reviews/2026-06-09/review.md`, verdict minor revision); the
  revision pass and a full restructure (spine + appendix Refinements) are done.
- **Canonical source**: `paper/codec_retrieval.tex` + `paper/refs.bib` (article class,
  de-anonymized, 33 pp). This is the content source of truth.
- **Active target (2026-06-09)**: **ACM TOPS** (Transactions on Privacy and Security). A
  rolling-deadline journal: no fixed deadline to miss, a 35-page limit with no per-page fees,
  and the cogirth / randomized-encoding / graded refinements stay first-class **in-body**. The
  submission version is BUILT at `venue/tops/` (acmsmall, 30 pp, 0 errors, de-anonymized).
  Remaining before submit: confirm the TOPS review model (single-blind vs double-anonymous;
  see `venue/tops/NOTES.md`) and, if double-anonymous, apply the anonymization deltas; then a
  proofread and the ACM submission upload. The PoPETs version is held as the conference/
  companion fallback.

## Venue status

| Venue | Status | Format | Body limit | Deadline model | Source | Notes |
|---|---|---|---|---|---|---|
| **ACM TOPS** | **active target; BUILT** | acmsmall (single-col) | 35 pp, no per-page fees | rolling | `venue/tops/` | 30 pp, 0 errors, refinements in-body, de-anon; confirm blinding before submit |
| IEEE TIFS | considered, declined | IEEEtran 2-col | no cap but $220/pg overlength from p11 | rolling | not built | strong fit, but ~$900-1400 overlength fee at this length; declined in favor of TOPS (no fee) |
| Designs, Codes & Cryptography | candidate (coding identity) | Springer journal | generous | rolling | to build | best home for the GF(2)/cogirth/coset/wiretap math; privacy framing becomes secondary motivation |
| ESORICS 2027 | candidate (conference) | LNCS | 16 pp (+ appendix; 20 total) | ~Jan 2027 (fixed) | to build | roomier than PoPETs but still capped + fixed deadline; ESORICS 2026 deadline (Jan 9 2026) passed |
| IEEE Trans. Inf. Theory | fallback (prestige / identity shift) | IEEEtran | none | rolling | not built | top prestige, no page limit, but recast around information theory; ~12-18 mo review |
| PoPETs 2027 (Issue 3) | prepared, on hold | acmart sigconf + popets | 12 pp | paper 2026-11-30 | `venue/popets/` | ready; kept as the conference/companion fallback if we stay with PoPETs |

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
