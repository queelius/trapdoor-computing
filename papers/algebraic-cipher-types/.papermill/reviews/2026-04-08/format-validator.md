# Format Validator Report

**Date**: 2026-04-08
**Paper**: Algebraic Cipher Types
**Validator**: format-validator

## Summary

The paper builds cleanly with no LaTeX errors or warnings. Label resolution is complete. The main formatting concern is that the paper uses a generic article class rather than the ACM format expected by PLAS.

---

## 1. Build Verification

**Status**: Clean build. No errors, no warnings.

The build log shows no unresolved references, no undefined citations, no multiply-defined labels. The pdflatex/bibtex/pdflatex/pdflatex pipeline completes successfully.

**Note**: 6 of 12 .bib entries are not cited and do not appear in the compiled bibliography. This is not a LaTeX error (BibTeX only includes cited entries) but indicates dead entries in the .bib file.

---

## 2. Label Resolution

All label/ref pairs resolve correctly:

| Label | Type | Referenced by |
|-------|------|---------------|
| sec:intro | section | -- |
| sec:prelim | section | -- |
| def:cipher-map | definition | -- |
| def:machines | definition | -- |
| sec:types | section | -- |
| sec:void-unit | subsection | -- |
| sec:products | subsection | Cref in sec:exponentials, discussion |
| sec:sums | subsection | Cref in discussion |
| prop:product-tradeoff | proposition | -- |
| thm:sum-impossibility | theorem | Cref in intro, discussion |
| rem:sum-vs-product | remark | -- |
| rem:trusted-matching | remark | -- |
| ex:optional | example | -- |
| sec:exponentials | subsection | -- |
| sec:orbit | section | Cref in intro |
| def:orbit | definition | Cref in monotonicity proof, confidentiality proof |
| thm:monotonicity | theorem | Cref in intro |
| cor:empty-ops | corollary | -- |
| def:candidate-set | definition | -- |
| thm:confidentiality-bound | theorem | Cref in intro, examples, discussion |
| sec:cipher-tm | section | Cref in intro |
| def:cipher-tm | definition | -- |
| prop:cipher-tm-space | proposition | -- |
| prop:head-determinism | proposition | -- |
| rem:oram | remark | -- |
| sec:discussion | section | -- |
| def:cipher-node | definition | -- |
| rem:shared-vars | remark | -- |
| sec:cipher-bool | subsection | -- |
| def:cipher-bool | definition | Cref in generalization remark |
| prop:noise-absorption | proposition | -- |
| rem:general-cipher-type | remark | -- |
| tab:boolean-search | table | -- |

No unused labels. No dangling references.

---

## 3. Venue Formatting

**Major: Wrong document class for PLAS.** PLAS (at CCS) uses the ACM sigconf format (acmart document class). The paper currently uses the standard LaTeX article class with 11pt font and 1-inch margins.

Required changes for PLAS submission:
- Switch to `\documentclass[sigconf]{acmart}`
- Add ACM CCS concepts
- Add ACM keywords
- Add proper author block with affiliation and ORCID
- Follow ACM reference format
- Check page limits (PLAS typically 6-12 pages in ACM format; 15 pages in article class may compress)

**Severity**: Major (must be fixed before submission).
**Confidence**: High.

If targeting IACR ePrint instead, the current format is acceptable (ePrint has no fixed format requirement, though the IACR iacrtrans class is commonly used).

---

## 4. Package Usage

| Package | Necessary | Order correct |
|---------|-----------|---------------|
| geometry | Yes | Yes |
| amsmath | Yes | Yes |
| amssymb | Yes | Yes |
| amsthm | Yes | Yes |
| mathtools | Yes (for \allowbreak) | Yes |
| natbib | Yes | Yes |
| booktabs | Yes (tables) | Yes |
| hyperref | Yes | Should be loaded last -- currently before cleveref, which is correct (cleveref must be after hyperref) |
| cleveref | Yes | Yes (loaded after hyperref) |

No package conflicts detected. `hypertexnames=false` is set to avoid hyperref naming collisions with shared theorem counters.

---

## 5. Table Formatting

**Table 1 (Boolean search)**:
- Uses booktabs correctly (toprule, midrule, bottomrule)
- Caption placed above table (correct per convention)
- Column alignment: left for query, centered for metrics -- appropriate
- Minor: "FP" column header is ambiguous (false positives count? rate?)
- Minor: "Time" column has no units in header (seconds shown in data)

**Encoding granularity table** (unnumbered, inline):
- Uses booktabs correctly
- Not a formal \table environment (embedded in center environment)
- Missing data ("---") in space column -- see methodology auditor
- Minor: Should be a numbered table if it carries results

---

## 6. Theorem Environment Consistency

| Environment | Counter | Shared with |
|-------------|---------|-------------|
| definition | per-section | standalone |
| theorem | per-section | proposition, corollary, lemma (shared counter) |
| remark | per-section | standalone |
| example | per-section | standalone |

The shared counter for theorem/proposition/corollary means they are numbered sequentially (e.g., Theorem 3.2 followed by Proposition 3.1 would not occur -- they share a counter). This is standard and correct.

---

## 7. Typography

| Issue | Location | Severity |
|-------|----------|----------|
| Em-dashes (---) used correctly throughout | Global | OK |
| Math mode for inline math correct | Global | OK |
| \mathrm used for function names (enc, dec, orbit, Cand, conf) | Global | OK |
| \mathsf used for cipher type constructor C | Global | OK |
| Quotation marks use `` and '' correctly | Global | OK |
| \B macro expands to \{0,1\} -- correct | Global | OK |
| Line 802-803: "enc_pair" uses subscript for pairing -- slightly inconsistent with enc_A, enc_B | Sec 5.1 | Suggestion |
