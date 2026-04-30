# Citation Verifier Report

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12
**Confidence**: MEDIUM-HIGH

---

## Overall Assessment

Of the 30 entries in `references.bib`, only 10 are cited in main.tex.
All 10 compiled `\bibitem` entries appear with natbib-rendered
authorship, no "undefined reference" warnings, and correct label
resolution (verified via `main.log`).

The refined thesis (2026-04-12) specifically claimed these additions:
- Smith 2009, Alvim et al. 2020 (QIF): **cited correctly** in §2.
- Bost and Fouque 2017 (SSE dummy queries): **cited correctly** in §2.
- Demertzis et al. 2020 (SEAL): **cited correctly** in §2.
- Naveed et al. 2015 (PPE attacks): **cited correctly** in §2.
- Islam et al. 2012 (access pattern): **cited correctly** in §2.
- Simmons 1979 (homophonic): **NOT cited** despite being in the bib
  and despite the refined thesis claiming it would be.
- Shannon 1948 (source coding): **cited correctly** in §6.

Key metadata checks for the new citations:

| Entry | Claimed venue | Verification | Status |
|---|---|---|---|
| smith2009foundations | FoSSaCS 2009 | Correct: Geoffrey Smith, "On the Foundations of Quantitative Information Flow," FoSSaCS 2009, pp. 288 to 302, Springer LNCS | OK |
| alvim2020science | Springer 2020 book | Correct: Alvim, Chatzikokolakis, McIver, Morgan, Palamidessi, Smith, "The Science of Quantitative Information Flow," Information Security and Cryptography, Springer 2020 | OK |
| demertzis2020seal | USENIX Security 2020 | Correct: Demertzis, Papadopoulos, Papamanthou, Shintre, "SEAL: Attack Mitigation for Encrypted Databases via Adjustable Leakage," 29th USENIX Security, 2020 | OK |
| naveed2015inference | CCS 2015 | Correct: Naveed, Kamara, Wright, "Inference Attacks on Property-Preserving Encrypted Databases," ACM CCS 2015 | OK |
| islam2012access | NDSS 2012 | Correct: Islam, Kuzu, Kantarcioglu, "Access Pattern Disclosure on Searchable Encryption: Ramification, Attack and Mitigation," NDSS 2012 | OK |
| bost2017thwarting | ACM CCS 2017 | **Needs verification**: Bost and Fouque's "Thwarting leakage abuse attacks against searchable encryption" is best known as IACR ePrint 2017/617. Several sources cite it as a CCS paper but a primary record should be checked. Either ePrint or Asiacrypt if any.  | Flag |
| jaynes1957information | Phys Rev 106(4), 620 to 630 | Correct: E. T. Jaynes, "Information Theory and Statistical Mechanics," Physical Review 106(4), 620 to 630, 1957 | OK |
| shannon1948mathematical | Bell Sys Tech J 27(3), 379 to 423 | Correct; the paper was published in two parts in BSTJ vol 27 issues 3 and 4. The commonly-cited pp 379 to 423 for the first part is correct. | OK |

---

## MAJOR: Simmons 1979 is claimed in the refined thesis but not cited

**Location**: `simmons1979symmetric` is in references.bib but does not
appear in any `\cite{}` in main.tex. The refined thesis (2026-04-12)
states: "noise injection cites Bost and Fouque, homophonic cites
Simmons, compression cites Shannon."

**Problem**: §4.2 (Multiple Representations) and Example 5 (Homophonic
encryption for Zipf) are the natural points to cite Simmons 1979,
which introduces homophonic substitution. The prior review
(2026-04-09) noted that the homophonic construction is classical and
should credit Simmons. The refined thesis claims this was addressed;
execution did not land the cite.

**Suggestion**: Add `\cite{simmons1979symmetric}` at line 519 or 524
(§4.2 opening) and at line 562 (Example 5 header). Sample text for
line 524:
> "Each element $x$ can be given $K(x) \geq 1$ distinct encodings
> (classical homophonic substitution, Simmons
> 1979~\cite{simmons1979symmetric})."

---

## MAJOR: Bost and Fouque 2017 venue may be incorrect

**Location**: references.bib entry `bost2017thwarting` at lines 290 to 296.

**Quoted text (.bib)**:
```
@inproceedings{bost2017thwarting,
  title={Thwarting leakage abuse attacks against searchable encryption},
  author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
  booktitle={Proceedings of the 2017 ACM Conference on Computer and Communications Security},
  pages={1901--1915},
  year={2017}
}
```

**Problem**: The CCS 2017 proceedings can be searched for Bost/Fouque
at page 1901 to 1915; this page range approximately matches Bost,
Minaud, Ohrimenko "Forward and Backward Private Searchable Encryption
from Constrained Cryptographic Primitives" (CCS 2017), *not* "Thwarting
leakage abuse attacks against searchable encryption." The latter paper
is an IACR ePrint (2017/617) by Bost and Fouque, not a CCS paper.

This should be verified against the primary record. If the paper is
only available as an ePrint, the bib entry should be:

```
@misc{bost2017thwarting,
  title={Thwarting leakage abuse attacks against searchable encryption},
  author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
  year={2017},
  note={IACR ePrint 2017/617}
}
```

**Suggestion**: Verify the venue. If ePrint, update the bib entry. The
cited content (dummy queries with game-based security analysis) does
appear in the Bost and Fouque ePrint; the content claim is correct,
only the venue metadata is suspect.

---

## MINOR: 21 of 30 bibliography entries are uncited

**Location**: references.bib; main.tex citations.

**Problem**: The bibliography includes 21 entries that have no
`\cite{}` in main.tex:

```
belazzougui2009hash, bellare1993random, bernoulli-types,
bloom1970space, boldyreva2009order, cash2013highly, cash2015leakage,
chaum1981untraceable, cover2006elements, curtmola2006searchable,
gentry2009fully, goldreich1996software, grubbs2018pump,
juels2014honey, mackay2003information, sabelfeld2003language,
sayood2017introduction, shannon1949communication,
simmons1979symmetric, song2000practical, yao1982protocols
```

Since the paper uses natbib with `plainnat`, uncited entries are
automatically omitted from the compiled bibliography (verified: the
compiled `.bbl` has exactly 10 `\bibitem` entries). So this is only a
`.bib` hygiene issue, not a reader-facing problem.

However, several of these entries would **strengthen** the paper if
brought into the text:
- `cover2006elements`: should be cited at §3 preliminaries for the
  IT notation sentence (and elsewhere).
- `bellare1993random`: should be cited wherever "random oracle model"
  is invoked (at least §3 preliminaries, line 241).
- `simmons1979symmetric`: required per the refined thesis (see MAJOR
  above).
- `goldreich1996software`, `gentry2009fully`, `yao1982protocols`:
  could be cited in §1 "What this paper does not do" when naming
  ORAM, FHE, and MPC as alternatives.
- `cash2015leakage`, `grubbs2018pump`: could be added to §2 Leakage
  paragraph as the canonical reference class for SSE attacks.
- `curtmola2006searchable`: could be cited in §2 to establish the
  SSE simulation-based security standard being contrasted with.

**Suggestion**: Add these as a revision cleanup pass, OR delete
unused entries from the `.bib` to reduce visual noise for the
maintainer.

---

## MINOR: Shannon 1949 is in bib but the paper cites Shannon 1948 for source coding

**Location**: Section 6.1, line 875.

**Observation**: `shannon1949communication` ("Communication theory of
secrecy systems") is the classical secrecy reference, famously
introducing the notion of unicity distance, product ciphers, and
perfect secrecy. The paper cites `shannon1948mathematical` for source
coding, which is correct. But Shannon 1949 would naturally appear in
§1 (framing the information-theoretic approach to confidentiality) or
§7 (discussing the relationship of the entropy ratio to classical
perfect secrecy).

**Suggestion**: Cite shannon1949communication in §1 or §7 discussion
(e.g., "The entropy ratio generalizes Shannon's classical
communication-theoretic view of secrecy~\cite{shannon1949communication}
to the approximate trapdoor setting").

---

## MINOR: `grubbs2018pump` entry is incomplete (carry-over from 2026-04-09)

**Location**: references.bib lines 142 to 148.

**Quoted text**:
```
@article{grubbs2018pump,
  title={Why your encrypted database is not secure},
  author={Grubbs, Paul and Lacharit{\'e}, Marie-Sarah and Minaud, Brice and Paterson, Kenneth G},
  journal={Proceedings of the ACM on Management of Data},
  year={2018}
}
```

**Problem**: Missing volume, pages, DOI. Also "Proceedings of the
ACM on Management of Data" is the PACMMOD journal (SIGMOD) which
started in 2023; in 2018 the paper would have been at SIGMOD
Conference or HotOS. The original "Why your encrypted database is not
secure" by Grubbs, Lacharite, Minaud, Paterson was published at HotOS
2017 (16th Workshop on Hot Topics in Operating Systems). The venue
and year are both wrong.

Correction:
```
@inproceedings{grubbs2017hotos,
  title={Why your encrypted database is not secure},
  author={Grubbs, Paul and Lacharit{\'e}, Marie-Sarah and Minaud, Brice and Paterson, Kenneth G},
  booktitle={Proceedings of the 16th Workshop on Hot Topics in Operating Systems (HotOS)},
  pages={162--168},
  year={2017}
}
```

(The entry is uncited, so this does not affect the compiled PDF, but
it's a "time-bomb" waiting for future use.)

---

## MINOR: All towell2026 references are unpublished

**Location**: references.bib entries for `towell2026cipher`,
`towell2026algebraic`, `bernoulli-types`.

**Observation**: Three references are marked `@unpublished` or `@misc`
with "Manuscript" notes. The cipher-maps paper is referenced eight
times, carrying much of the preliminaries. A reviewer will note that
the paper depends heavily on an unpublished companion manuscript.

This is unavoidable for a coordinated monograph series, but the paper
should make the dependency legible. Options:
1. Add a paragraph in §1 explaining the relationship: "This paper is
   the quantitative companion to the cipher maps
   framework~\cite{towell2026cipher}, which defines the four
   properties and acceptance-predicate construction we build on."
2. Where inherited results are cited (Prop 4.3, Thm 5.2), quote the
   exact statement from the companion paper in a footnote. This
   removes the need for a reviewer to locate the companion.
3. If the companion is on arXiv or another permanent repository, cite
   it via arXiv ID, not just GitHub URL.

**Suggestion**: Option (1) is cheapest and adequate; option (2) is
more reviewer-friendly. At minimum, the cipher-maps URL should point
to a stable snapshot, not a moving branch.

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 2 | Simmons not cited despite thesis claim; Bost/Fouque venue may be wrong |
| Minor | 4 | 21 uncited bib entries; Shannon 1949 unused; grubbs entry broken; unpublished companion deps |
| Suggestion | 0 | |

The citation situation has improved substantially from the prior
round: QIF (Smith, Alvim), SSE leakage (Bost/Fouque, Demertzis), and
PPE attacks (Naveed, Islam) are now all cited in §2. The residual
concerns are the missing Simmons cite (contradicts the thesis
refinement's own stated plan), potentially incorrect venue metadata
for Bost/Fouque, and .bib hygiene.
