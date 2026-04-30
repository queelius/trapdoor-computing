# Citation Verifier Report (round 3, 2026-04-29)

## Scope

No new citations expected this round (the structural changes were
prose-only). Verify the rev2 citation cleanup is intact.

## Verification of rev2 fixes

| Item | Status |
|---|---|
| Bost-Fouque 2017 venue (M7 morning, M2 rev2) | Resolved this round. references.bib lines 310-316 now uses `@misc` with `howpublished={IACR Cryptology ePrint Archive, Report 2017/617}` and the IACR ePrint URL. |
| Simmons 1979 cited (M6 morning) | Cited at §4.2 line 590 (`\cite{simmons1979symmetric}`). Bib entry at line 89. |
| Fannes 1973 cited | Cited at lines 116, 188, 448 (Thm 3.1 proof). Bib entry at line 57. |
| Audenaert 2007 cited | Cited at lines 116, 188, 448. Bib entry at line 67. |
| Cover-Thomas 2006 cited | Cited at line 807 (Thm 5.1 part 3 proof). Bib entry at line 49. |

All five rev2 citation additions/fixes are intact.

## Bibliography cited/uncited audit

Total entries in `references.bib`: 33.

Cited in `main.tex` (14):
- alvim2020science
- audenaert2007sharp
- bost2017thwarting
- cover2006elements
- demertzis2020seal
- fannes1973continuity
- islam2012access
- jaynes1957information
- naveed2015inference
- shannon1948mathematical
- simmons1979symmetric
- smith2009foundations
- towell2026algebraic
- towell2026cipher

Uncited (19): belazzougui2009hash, bellare1993random, bernoulli-types,
bloom1970space, boldyreva2009order, cash2013highly, cash2015leakage,
chaum1981untraceable, curtmola2006searchable, gentry2009fully,
goldreich1996software, grubbs2018pump, juels2014honey, mackay2003information,
sabelfeld2003language, sayood2017introduction, shannon1949communication,
song2000practical, yao1982protocols.

Uncited count is unchanged from rev2 (was 19). No regression.

## Carry-over flagged in prior rounds

- **Minor 3 (rev2)**: "Simmons attribution loose for homophonic"
  (Simmons 1979 is more about asymmetric crypto; canonical
  homophonic reference is Kahn 1967). Status: still open. Severity
  unchanged from rev2 (Minor).
- **m13 (morning)**: `grubbs2018pump` venue is wrong (should be
  HotOS 2017, listed as different). Status: open but cosmetic
  since the entry is uncited.

## Findings (this round)

### New this round: NONE

No new citations were introduced; no citation regressions detected.
All five rev2 citation additions are intact.

### Carry-over

- Minor 3: Simmons attribution loose. Open.
- m13: `grubbs2018pump` venue wrong. Open (cosmetic).

## Summary

Citation hygiene this round is unchanged from rev2. Bost-Fouque
correction (rev2 M7) is in place and verified. No new citation
issues introduced by today's structural changes.

**Recommendation from citation-verifier**: minor-revision (carry-over
items only).
