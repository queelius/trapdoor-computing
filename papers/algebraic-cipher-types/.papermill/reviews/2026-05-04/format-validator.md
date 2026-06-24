# Format Validator Report

**Date**: 2026-05-04
**Reviewer role**: Build verification, label resolution, venue formatting.

## Build status (ACT)
- `main.log`: `Output written on main.pdf (21 pages, 375641 bytes).`
- Warnings: exactly one -- `Overfull \hbox (19.70331pt too wide) in paragraph at lines 703--713` (§4.5 universal-granularity-knob paragraph). No undefined references, no multiply-defined labels. Clean modulo the one hbox.
- This is consistent with the 2026-05-23 round; no regression from the algebraic restructure.

## Label resolution
All `\Cref`/`\ref` targets resolve. New labels introduced by the 2026-05-04 restructure -- `prop:exponential-identity` (4.4), `prop:exponential-tradeoff` (4.5), `sec:type-summary` (§4.5), `tab:algebra-summary` (Table 1) -- all defined and referenced. The intro contributions list (101-140) references all of them correctly. No dangling labels from the cipher-TM removal (those were swept 2026-05-02).

## Table numbering note (documentation-only)
§4.5 adds **Table 1** (`tab:algebra-summary`). The §7.3 experimental tables are therefore **Tables 2/3/4** in the PDF (`tab:boolean-search`, `tab:fpr-compounding`, `tab:granularity`). All in-text references use `\Cref`, so the PDF is internally correct. Only the prose of state.md and older review files (which say "Table 1/2/3" for the experimental tables) is stale. No paper edit required.

## Foundation build (cross-paper, for verification confidence)
The cited foundation paper builds clean: `cipher_maps.log` -> `Output written on cipher_maps.pdf (39 pages, 525937 bytes)`, no undefined refs. All `\newlabel` numbers in `cipher_maps.aux` used as cross-paper ground truth this round are therefore from a valid build. (This is what makes the citation-number verdicts authoritative.)

## Venue formatting (carry-forward M7)
- Line 1: `\documentclass[11pt]{article}`. Unchanged. If the venue is PLAS, swap to `\documentclass[sigconf,nonacm=true]{acmart}` and add CCS concepts; 21pp article compresses to ~14-16pp under acmart sigconf, within typical limits. If IACR ePrint or arXiv, article class is fine.
- Venue-decision blocker, not a content defect.

## Findings
- MIN (carry-over): overfull hbox at line 703 -- the only build warning; fixable with a rephrase or `\-` hint. Shared with prose-auditor.
- M7 (carry-forward): document class gated on venue.

## Confidence
High. Both papers build clean; label graph intact.
