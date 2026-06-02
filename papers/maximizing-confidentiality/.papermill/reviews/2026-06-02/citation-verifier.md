# Citation-Verifier Report, Round 5 (2026-06-02, cross-paper)

**Paper**: "The Entropy Ratio" (`main.tex`, 25pp)
**Scope**: cross-paper citation accuracy is the primary deliverable. All
companion label numbers independently confirmed against the companion
`.aux` (resolved cross-references) and `.tex` (section titles).
**Method**: For each `\cite[...]{...}` into a companion, I resolved the
target label in the companion's `.aux` `\newlabel` table and confirmed
the section/theorem title in the companion's `.tex`.

---

## Cross-paper citation-drift table (MAIN DELIVERABLE)

Every row below is independently confirmed. "Companion evidence" gives the
`.aux` `\newlabel` entry that resolves the true number.

| Line(s) in `main.tex` | Current cite | Correct cite | Companion evidence | Severity |
|---|---|---|---|---|
| 193, 817, 999 | `[Sec.~8]{towell2026cipher}` (FPR compounding) | `[Sec.~7.4]` | `sec:composition=7` ("Composition"); "Error Accumulation by Gate Type" is subsec 7.4; `sec:uniformity=8` is the granularity section, not composition | HIGH |
| 168, 732 | `[Sec.~9]{towell2026cipher}` (encoding granularity) | `[Sec.~8]` | `sec:uniformity=8` ("Representation Uniformity and Encoding Granularity"); `sec:discussion=9` ("Discussion") | HIGH |
| 739 | `[Prop.~9.1]{towell2026cipher}` (granularity spectrum) | `[Prop.~8.1]` | `prop:granularity=8.1` ("Granularity and privacy") | HIGH |
| 828, 956 | `[Sec.~9.2]{towell2026cipher}` (compositional leakage) | `[Sec.~8.2]` | `subsec:comp-leakage=8.2` ("Compositional Leakage") | HIGH |
| 772 | `[Thm.~4.1]{towell2026algebraic}` (sum-type impossibility) | `[Thm.~4.2]` | `thm:sum-impossibility=4.2`; `prop:product-tradeoff=4.1` is the product proposition (theorem/prop share a counter) | HIGH |
| **1084** | `[Sec.~5.4]{towell2026algebraic}` (typed composition chains) | `[Sec.~5.5]` | `sec:typed-chains=5.5`; `sec:orbit-examples=5.4` (§5.4 is "Examples"). NEW, not in the user's pre-check list | HIGH |

All six are verifiably wrong: a reader who follows the pointer lands on a
different section/theorem than the one our prose describes. Five were
pre-resolved by the area chair; row 1084 is a new sixth, found by checking
every `towell2026algebraic` cite (not just the flagged ones).

### Correct citations, verified, DO NOT CHANGE

| Line | Cite | Resolves to | Status |
|---|---|---|---|
| 307 | `[Def.~3.1]{cipher}` | `def:cipher-map=3.1` | OK |
| 319 | `[Sec.~4]{cipher}` | `sec:properties=4` | OK |
| 360 | `[Thm.~6.1]{cipher}` | `thm:lower-bound=6.1` | OK |
| 367 | `[Sec.~5]{cipher}` | `sec:trust-model=5` | OK |
| 373 | `[Sec.~6.2]{cipher}` | `subsec:acceptance=6.2` | OK |
| 778, 1073 | `[Sec.~5]{algebraic}` | `sec:orbit=5` | OK |
| 787, 1687 | `[Thm.~5.3]{algebraic}` | `thm:confidentiality-bound=5.3` | OK number; but see logic-checker for the form/denominator mismatch. Thm 5.3 is the entropy form, our paper quotes a set form |

`references.bib` defines `towell2026cipher` (line 3) and `towell2026algebraic`
(line 10). Both keys resolve. No undefined-citation warnings in the build.

---

## Bidirectional check (companion to our paper)

I grepped both companions for `towell2026maxconf` and resolved each target
against our current theorem numbering.

**STALE (MEDIUM, fix in companion):** `cipher_maps.tex` line 843 cites
`[Theorem~4.1, part~3]{towell2026maxconf}` as "Full proof and discussion of
tightness" of the Fannes bridge. In our current paper the Fannes bridge is
**Theorem 3.1** (`thm:entropy-decomposition`, line 469), part (3). Our
**Theorem 4.1** (`thm:noise-dilution`, line 566) is now Noise Dilution, a
different result whose part (3) is the Fisher-information bound. So after
this paper's restructuring (Thm 5.1/5.2 added, the §4/§5 split), the
cipher-maps back-reference points to the wrong theorem. Fix (in
cipher-maps): `[Theorem~3.1, part~3]{towell2026maxconf}`.

**OK:** `cipher_maps.tex` line 906 cites `[\S 5--6]{towell2026maxconf}` for
"specific adversary games"; our §5 (Compositional Scale) and §6 (Practical
Measurement) cover this. Accurate. Lines 69/176/783/812/818/1728/2345/2598
cite the paper at section granularity (`\S 4` = our Constructions, or bare
key). All still accurate.

**OK:** `algebraic-cipher-types/main.tex` lines 222 and 1554 cite
`towell2026maxconf` at bare-key granularity ("treatment is developed further
in"). Not affected by restructuring.

---

## New-prose citation scan (since 2026-04-29)

- §6.5 "Empirical Anchor" (lines 1243-1369): cites `shannon1948mathematical`,
  `cover2006elements` (CTW), `devroye1996nonparametric`. All defined and
  appropriate. No new broken cites.
- §9 "Practical depth" (lines 1670-1700): cites `[Thm.~5.3]{algebraic}`
  (line 1687, OK number) and internal refs. No new broken cites.

No NEW intra-paper citation defects. The bibliography trim to 15 entries
(done 2026-05-23) holds; no uncited-entry carry-over remains.

---

## C-2 note (not this paper's bug, but adjacent)

The consistency report C-2 records that cipher-maps' `.bib` carries a stale
title for `towell2026algebraic` ("A Functorial Framework...") and that
cipher-rekeying uses a duplicate key `towell2026actypes`. Our paper is clean
on C-2: it uses the canonical `towell2026algebraic` with the correct title.
No action here; flagged only so the area chair can confirm the family fix
lands elsewhere.

---

## Summary

- 6 cross-paper section/theorem pointers are wrong (HIGH each); all have
  exact one-token fixes.
- 1 stale back-reference in the cipher-maps companion (MEDIUM; fix there).
- 0 new intra-paper citation defects.

The drift is entirely mechanical: section/theorem renumbering in the
companions that this paper never tracked. None is a fabricated citation; all
point to the right paper, just the wrong locator. After the six one-token
edits the cross-paper citation layer is correct.
