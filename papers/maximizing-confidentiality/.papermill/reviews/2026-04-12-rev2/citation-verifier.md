# Citation Verifier Report (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Confidence**: HIGH

---

## Overall Assessment

Three new citations land in this round:
- `simmons1979symmetric` is now `\cite`d in §4.2 (resolves morning M6)
- `fannes1973continuity` is `\cite`d in §1 framing and Thm 3.1 proof (new)
- `audenaert2007sharp` is `\cite`d alongside Fannes (new)
- `cover2006elements` is now `\cite`d in Thm 5.1 part 3 proof (new)

The morning M7 (Bost-Fouque venue) is **unchanged**: the bib entry
still claims CCS 2017 with pages 1901-1915, which appears to be
incorrect attribution to a different CCS 2017 paper. This was flagged
as deferred in the prompt; my view is unchanged.

The morning m13 (`grubbs2018pump` venue) is **unchanged**: the bib
entry still says "Proceedings of the ACM on Management of Data 2018"
where the actual venue is HotOS 2017. Cosmetic since the entry is
uncited.

No new citation accuracy issues introduced.

---

## Resolution audit

### Morning M6. Simmons not cited. RESOLVED

**Verification**: Line 565 of main.tex now has:
```latex
homophonic substitution prescription~\cite{simmons1979symmetric}:
$K(x) \propto D(x)$.
```

This is in §4.2 (Multiple Representations) opening paragraph,
exactly where the morning round suggested. ✓

**Caveat on attribution accuracy**: The Simmons 1979 paper is
"Symmetric and asymmetric encryption" in *ACM Computing Surveys*
11(4), 1979. This paper is primarily a survey of public-key
encryption and the early development of asymmetric crypto, not
specifically a treatise on homophonic substitution. The classical
homophonic substitution technique (assigning multiple ciphertext
symbols to high-frequency plaintext symbols) predates 1979 by
centuries (used in 16th-century Italian nomenclators, formalized in
Friedman 1922 and Kahn's *The Codebreakers* 1967). Simmons 1979 does
discuss homophonic substitution as one classical technique, but it
is not the primary or definitive reference.

A more accurate citation would be either Kahn 1967 (textbook
reference for classical ciphers) or Massey-Lai 1990s ("Some
applications of source coding in cryptography") for the
information-theoretic treatment, or both. Simmons 1979 is
defensible as a citation but not optimally attributed.

**Severity for citation accuracy**: Minor. The cite exists, the
spirit is right, the attribution is loose. A theory reviewer
familiar with the historical homophonic literature might raise an
eyebrow; most reviewers will accept the cite.

### New citations: Fannes 1973 and Audenaert 2007. ADDED CORRECTLY

**Bib entry verification**:

```bibtex
@article{fannes1973continuity,
  title={A continuity property of the entropy density for spin lattice systems},
  author={Fannes, Mark},
  journal={Communications in Mathematical Physics},
  volume={31},
  number={4},
  pages={291--294},
  year={1973}
}
```

**Verification against primary record**: Mark Fannes, "A continuity
property of the entropy density for spin lattice systems," *Comm.
Math. Phys.* 31, 291-294 (1973). This is the canonical Fannes 1973
inequality. Title and metadata are correct.

```bibtex
@article{audenaert2007sharp,
  title={A sharp continuity estimate for the von {N}eumann entropy},
  author={Audenaert, Koenraad M R},
  journal={Journal of Physics A: Mathematical and Theoretical},
  volume={40},
  number={28},
  pages={8127--8136},
  year={2007}
}
```

**Verification against primary record**: K. M. R. Audenaert, "A sharp
continuity estimate for the von Neumann entropy," *J. Phys. A: Math.
Theor.* 40 (2007) 8127-8136. Correct. The Audenaert paper provides
the sharp constant ($t \log_2(d-1) + h_2(t)$ in the bit-formulation)
that the proof actually uses. Citing both Fannes and Audenaert is
appropriate (Fannes for the original, Audenaert for the sharp form).

**Locations cited**:
- §1 framing line 102 to 103: `\cite{fannes1973continuity, audenaert2007sharp}` ✓
- §3.3 Thm 3.1 part 3 line 423 to 424: `\cite{fannes1973continuity, audenaert2007sharp}` ✓

The cite locations are appropriate -- where the inequality is named
and where it is applied.

**Verdict on new citations**: Correctly attributed and well-placed.

### New citation: Cover-Thomas 2006. ADDED CORRECTLY

**Location**: §5.1 Thm 5.1 part (3) proof, line 773.

The proof now says: "$O(\sqrt{|Y_1|\cdot|Y_2|/N})$~\cite{cover2006elements}"
attributing the empirical-distribution TV convergence rate to
Cover-Thomas 2006. The cite is appropriate; Cover-Thomas covers the
Pinsker-Csiszár-Kullback inequality, but the standard rate
$\sqrt{K/N}$ for empirical distribution estimation in TV is more
commonly attributed to specific empirical-process results (e.g.,
Devroye-Gyorfi-Lugosi 1996; Han-Jiao-Weissman 2015) rather than
Cover-Thomas. The cite is defensible at the textbook-reference level
but a more specific reference would be more rigorous.

**Severity**: Minor. The result is correct; the citation is
permissive.

### Morning M7. Bost-Fouque venue. STILL OPEN

**Status**: The bib entry at lines 310 to 316 is unchanged:
```bibtex
@inproceedings{bost2017thwarting,
  title={Thwarting leakage abuse attacks against searchable encryption},
  author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
  booktitle={Proceedings of the 2017 ACM Conference on Computer and Communications Security},
  pages={1901--1915},
  year={2017}
}
```

**Re-verification of the morning concern**:

Searching public records: Bost and Fouque, "Thwarting leakage abuse
attacks against searchable encryption", appears as IACR Cryptology
ePrint Archive, Report 2017/617 (2017). It does NOT appear in the
ACM CCS 2017 proceedings.

The CCS 2017 proceedings entry at pages 1901-1915 is:
- Bost, Minaud, Ohrimenko, "Forward and Backward Private Searchable
  Encryption from Constrained Cryptographic Primitives" (CCS 2017)

The bib entry conflates the two -- the title and authors are from
the ePrint, but the venue and page range are from a different paper
(by Bost-Minaud-Ohrimenko, both at CCS 2017).

**Severity unchanged**: Major (citation accuracy).

**Fix**:
```bibtex
@misc{bost2017thwarting,
  title={Thwarting leakage abuse attacks against searchable encryption},
  author={Bost, Rapha{\"e}l and Fouque, Pierre-Alain},
  year={2017},
  howpublished={IACR Cryptology ePrint Archive, Report 2017/617},
  url={https://eprint.iacr.org/2017/617}
}
```

The cited content (dummy queries with game-based security analysis)
is correctly attributed to Bost-Fouque; only the venue metadata
needs correction.

### Morning m13. `grubbs2018pump` venue. STILL OPEN (cosmetic)

**Status**: Bib entry at lines 162 to 168 unchanged. Still says
journal "Proceedings of the ACM on Management of Data" (which is the
PACMMOD journal that started in 2023, not 2018). The actual venue is
HotOS 2017.

**Note**: The entry is uncited in main.tex, so this is a "time bomb"
for future use, not a current correctness issue.

**Severity unchanged**: Minor.

### Morning m12. 21 uncited bibliography entries. PARTIALLY RESOLVED

The afternoon round added 4 citations (Simmons, Fannes, Audenaert,
Cover-Thomas) bringing the cited count from 10 to 14. Of the morning's
21 uncited entries, 3 are now cited (Simmons, Cover-Thomas were
uncited; Fannes and Audenaert are new entries that are cited).

Remaining uncited entries (19):
```
belazzougui2009hash, bellare1993random, bernoulli-types,
bloom1970space, boldyreva2009order, cash2013highly, cash2015leakage,
chaum1981untraceable, curtmola2006searchable, gentry2009fully,
goldreich1996software, grubbs2018pump, juels2014honey,
mackay2003information, sabelfeld2003language, sayood2017introduction,
shannon1949communication, song2000practical, yao1982protocols
```

Cosmetic. Not visible in compiled PDF.

---

## New observation: Cover-Thomas citation could be tighter

**Location**: §5.1, Thm 5.1 part 3 proof.

**Observation**: The plug-in TV convergence rate cited as Cover-Thomas
2006 is technically correct (Cover-Thomas covers basic empirical
distribution convergence), but more specific references exist:
- Devroye, Gyorfi, Lugosi 1996, *A Probabilistic Theory of Pattern
  Recognition*, Ch. 1: TV convergence of empirical distributions.
- Han, Jiao, Weissman 2015, "Minimax estimation of functionals of
  discrete distributions": minimax-optimal $\sqrt{K/N}$ rate.
- Weissman et al. 2003: tighter exponential-tail bounds.

**Severity**: Minor. Cover-Thomas is the safest textbook reference; a
specialist reviewer might prefer one of the above. Not a defect.

---

## Status summary

| Morning finding | Severity (then) | Status (now) |
|---|---|---|
| M6. Simmons not cited | Major | Resolved |
| M7. Bost-Fouque venue | Major | Open (deferred) |
| m12. 21 uncited bib entries | Minor | Partially resolved (now 19 uncited) |
| m13. `grubbs2018pump` venue | Minor | Open (deferred) |

| New citation | Status |
|---|---|
| `fannes1973continuity` (cited at §1, §3.3) | Correctly attributed |
| `audenaert2007sharp` (cited alongside Fannes) | Correctly attributed |
| `cover2006elements` (cited at Thm 5.1 proof) | Cite is permissive; tighter references exist |

| New observation | Severity |
|---|---|
| Simmons 1979 attribution loose for homophonic | Minor |
| Cover-Thomas cite could be tighter | Minor |

---

## Summary

| Severity | Count | Description |
|----------|-------|-------------|
| Critical | 0 | |
| Major | 1 | Bost-Fouque venue still wrong (carry-over) |
| Minor | 3 | grubbs2018pump venue (carry-over); Simmons attribution loose; Cover-Thomas cite permissive |
| Suggestion | 0 | |

The afternoon revision lands the promised Simmons cite and the new
Fannes / Audenaert cites, all correctly attributed. The Bost-Fouque
venue concern from the morning round is still open. The Cover-Thomas
cite is acceptable at the textbook level. Citation hygiene is in
better shape than the morning round; only one major (Bost-Fouque
venue) and three minors remain.
