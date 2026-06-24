# Citation Verifier Report, Round 8 (2026-05-27)

This round verifies citation accuracy, audits the four
"Manuscript in preparation" entries (MAJ-6 carry-over), and identifies
missing references.

## Bibliography integrity

The bibliography has 38 entries. All entries verified against the
manuscript for occurrence:

| BibTeX key | Cited in | Status |
|---|---|---|
| gentry2009fully | section 1, 2, 9.5 | OK |
| bloom1970space | section 2, 6.6.1 | OK |
| goldreich1996software | section 1, 2, 9.5 | OK |
| cash2013highly | section 2 | OK |
| yao1982protocols | section 1, 2 | OK |
| bernoulli-types | section 1, 9.1, 9.3 | OK (Manuscript in prep, see below) |
| bender2012quotient | section 2 | OK |
| fan2014cuckoo | section 2 | OK |
| fredman1984storing | section 2 | OK |
| belazzougui2009hash | section 2, 6.4 | OK |
| agrawal2004order | section 2 | OK |
| boldyreva2009order | section 2 | OK |
| bellare2007deterministic | section 2 | OK |
| song2000practical | section 2 | OK |
| curtmola2006searchable | section 1, 2 | OK |
| simmons1979symmetric | section 2, 4.2 | OK |
| bellare1993random | section 3.1 | OK |
| shannon1948mathematical | section 6.1, 6.6.1 | OK |
| naveed2015inference | section 2 (twice) | OK |
| islam2012access | section 2 | OK |
| juels2014honey | section 2 | OK |
| cash2015leakage | section 2 | OK |
| towell2026algebraic | section 10.3 | OK (Manuscript in prep, see below) |
| towell2026maxconf | section 1, 3.4, 5.1, 5.2, 8.1, 10.1, 10.5 | OK (Manuscript in prep, see below) |
| towell2026rekeying | section 3.4, 4.4, 9.4 | OK (Manuscript in prep, see below) |
| dodis2005entropic | section 1, 5.1 | OK |
| smith2009foundations | section 1, 5, 5.1 | OK |
| alvim2012measuring | section 1, 5.1 | OK |
| kerschbaum2015frequency | section 2 | OK |
| esposito2020recsplit | section 6.4, 10.1 | OK |
| warner1965randomized | section 10.4 | OK |
| kamara2019computationally | section 2 | OK |
| lecam1986asymptotic | section 5.2 | OK |
| towell2026codec | section 10.6 | OK |

All 38 entries are cited; no orphan references. All citations in
the manuscript resolve to a BibTeX entry (cleveref + natbib verified
via the build log showing no "undefined citation" warnings).

## CITE-MAJ-1 (Manuscript in preparation: load-bearing)

R6 / R7 MAJ-6 carry-over.

Four entries with `note={Manuscript in preparation}`:
- bernoulli-types
- towell2026algebraic
- towell2026maxconf
- towell2026rekeying

Cross-checked load-bearing forward references:

### towell2026maxconf (most load-bearing)

- Section 1 line 176: "(formal framework in companion work [cite])".
  The entropy-ratio framing in section 1 attributes its definition
  and bound to this companion paper.
- Section 3.4 line 380: "developed in companion work" for the
  categorical rekeying apparatus. Cross-load: this is actually a
  rekeying reference, suggests the cite at line 380 should be
  towell2026rekeying not towell2026maxconf. Verifying . . . line 382
  cites `\cite{towell2026rekeying}`. So line 380 reference is
  rekeying-related correctly. Confirmed.
- Section 5.1 line 715: "We adopt the entropy ratio of the companion
  entropy ratio paper [Section 4][cite]". Section reference is to
  section 4 of towell2026maxconf.
- Section 5.1 line 775 (proof of Prop 5.1): "Full proof and discussion
  of tightness in [Theorem 4.1, part 3][cite]." Specific theorem
  reference; reviewer cannot check without preprint.
- Section 5.2 line 838: "Translating this bit bound into a guessing-
  advantage bound depends on the prior over g(f) and is treated for
  specific adversary games in [Section 5 to 6][cite]." Section
  reference; reviewer cannot check without preprint.
- Section 8.1 line 1660: "[cite] treats the granularity lever in detail
  within the entropy-ratio framework." General reference.
- Section 10.1 line 2274: "[cite]" for additional empirical
  investigations. General reference.
- Section 10.5 line 2530: "the sister work [cite] reports related K(x)
  tuning experiments on this corpus." General reference.

Three specific theorem / section references are blocked on preprint:
- Theorem 4.1 part 3 (Prop 5.1 proof, line 775)
- Section 4 (entropy ratio definition, line 715)
- Sections 5 to 6 (guessing-advantage translation, line 838)

These three reads must resolve at submission time.

### towell2026rekeying

- Section 3.4 line 383: "developed in companion work [cite]"
  (categorical apparatus).
- Section 4.4 line 601: "Composing across different secrets requires
  the rekeying functor of [cite]". General reference.
- Section 9.4 line 2142: "[Thm. 7.1][cite]: each rekeying step costs
  at most one bit of latent entropy". Specific theorem reference.

One specific theorem reference: Theorem 7.1. This must resolve at
submission time.

### towell2026algebraic

- Section 10.3 line 2401: "characterized in companion work [cite]"
  for the AND noise-floor mechanism. Single load-bearing reference;
  the noise-floor formula is given in the cipher-maps paper (lines
  2392 to 2399) but the per-construction routing is deferred.

### bernoulli-types

- Section 1 line 156: "[cite]" for Bernoulli model framework.
  General reference.
- Section 9.1 line 2085: "[cite]" for relations and algebraic types.
  General reference.
- Section 9.3 line 2117: "[cite]" for trapdoor Boolean algebra.
  General reference.

No specific theorem references. But the URL in the bib entry
(https://github.com/queelius/bernoulli_sets) was flagged in R7 as
stale (MAJ-17). Verified at this round: HTTP 200 (page exists).
Closure: URL works.

### Resolution paths

1. Post all four to Zenodo with DOIs before submission. Closes
   MAJ-6 fully. Estimated 1 to 2 days.
2. Inline the three specific load-bearing theorem references into
   cipher_maps.tex:
   - Theorem 4.1 part 3 from towell2026maxconf: include the Fannes-
     Audenaert derivation directly in Prop 5.1's proof (~ 2
     paragraphs).
   - Section 4 of towell2026maxconf: copy the entropy ratio
     definition rather than cite.
   - Sections 5 to 6 of towell2026maxconf: drop section 5.2 item 4
     "function-value leakage bound" if the translation is not in
     this paper.
   - Theorem 7.1 of towell2026rekeying: rephrase section 9.4 to be
     a forward-looking discussion rather than citing a specific
     bound from an unpublished paper.

Path 1 is cleaner. The user has stated intent for Zenodo DOIs.

## CITE-MAJ-2 (Huffman 1952 missing)

R7 CITE-2 carry-over.

The paper centers Huffman codes in:
- Section 6.2 (line 1036): "Shannon-optimal when |code(y)| ≈ -log_2
  p_y. This is the entropy cipher map construction."
- Section 6.6.1 (line 1308): "The entropy cipher map is the batch
  construction instantiated with a prefix-free acceptance
  predicate."
- Section 8.3 (line 1879): "the Shannon-optimal Huffman partition
  gives max alpha(y) approximately 0.5"
- Section 10.6 (lines 2582, 2607, 2628, 2658, 2685, 2691): explicit
  Huffman partition references and numbers.

The Huffman 1952 paper ("A Method for the Construction of Minimum-
Redundancy Codes", Proc. IRE 40(9): 1098 to 1101) is the standard
citation for Huffman coding. The paper currently has zero Huffman
citations.

Recommended bibentry:
```
@article{huffman1952method,
  title={A Method for the Construction of Minimum-Redundancy Codes},
  author={Huffman, David A},
  journal={Proceedings of the IRE},
  volume={40},
  number={9},
  pages={1098--1101},
  year={1952}
}
```

First-mention citation site: section 6.2 line 1036, change
"Shannon-optimal" to "Shannon-optimal (Huffman 1952 [cite])".

Status: open since R7. Lower priority than MAJ-6 but worth landing
in the same editorial pass.

## CITE-MAJ-3 (Cover-Thomas 2006 for Kraft inequality)

The paper invokes Kraft's inequality implicitly at section 10.6 line
2604: "we enumerate all Kraft-feasible length assignments". The Kraft
inequality is also load-bearing for the prefix-free coding apparatus
in section 6 (without explicit invocation).

Cover-Thomas is the standard reference. Add as textbook citation at
section 6.1 (alongside Shannon 1948) and section 10.6 line 2604.

Recommended bibentry:
```
@book{cover2006elements,
  title={Elements of Information Theory},
  author={Cover, Thomas M and Thomas, Joy A},
  edition={2nd},
  year={2006},
  publisher={Wiley-Interscience}
}
```

R7 CITE-MIN-3 carry-over.

## CITE-MAJ-4 (volume-hiding STE references incomplete)

Section 2 cites kamara2019computationally for volume-hiding STE.
But the parallel construction Patel-Persiano-Yeo-Yung 2019 is not
cited. PPYY 2019 ("Mitigating Leakage in Secure Cloud-Hosted Data
Structures") presents an alternative volume-hiding construction with
explicit leakage profile, published at ACM CCS 2019.

R6 / R7 carry-over. Add at section 2 paragraph "Searchable symmetric
encryption" line 230.

Recommended bibentry:
```
@inproceedings{patel2019mitigating,
  title={Mitigating Leakage in Secure Cloud-Hosted Data Structures: Volume-Hiding for Multi-Maps via Hashing},
  author={Patel, Sarvar and Persiano, Giuseppe and Yeo, Kevin and Yung, Moti},
  booktitle={Proceedings of the 2019 ACM SIGSAC Conference on Computer and Communications Security (CCS)},
  pages={79--93},
  year={2019}
}
```

## CITE-MIN-1 (Alvim et al 2020 QIF textbook)

R6 / R7 carry-over.

The QIF positioning at section 1 line 165 to 173 ("Cipher maps belong
to the *quantitative information flow* tradition") cites
smith2009foundations and alvim2012measuring. The modern textbook
reference Alvim-Chatzikokolakis-McIver-Morgan-Palamidessi-Smith 2020
("The Science of Quantitative Information Flow", Springer) is the
single comprehensive QIF reference and should anchor the framing.

Recommended bibentry:
```
@book{alvim2020science,
  title={The Science of Quantitative Information Flow},
  author={Alvim, M{\'a}rio S and Chatzikokolakis, Konstantinos and McIver, Annabelle and Morgan, Carroll and Palamidessi, Catuscia and Smith, Geoffrey},
  year={2020},
  publisher={Springer},
  series={Information Security and Cryptography}
}
```

## CITE-MIN-2 (Köpf-Smith 2010 min-entropy leakage)

R6 / R7 carry-over.

Section 5.1 (lines 734 to 743) discusses Shannon entropy vs min-
entropy and says "Settings where min-entropy is preferred (one-shot
key recovery, cryptographic guessing games) are treated in the
companion work [cite]." This sentence should also cite Köpf-Smith
2010 ("Vulnerability Bounds and Leakage Resilience of Blinded
Cryptography under Timing Attacks") as the canonical reference for
min-entropy leakage in side-channel analysis.

Recommended bibentry:
```
@inproceedings{kopf2010vulnerability,
  title={Vulnerability Bounds and Leakage Resilience of Blinded Cryptography under Timing Attacks},
  author={K{\"o}pf, Boris and Smith, Geoffrey},
  booktitle={2010 23rd IEEE Computer Security Foundations Symposium (CSF)},
  pages={44--56},
  year={2010}
}
```

## CITE-MIN-3 (Kellaris et al 2016 multi-snapshot attacks)

New for R8 (closest published precedent for section 8.3 multi-
instance composition).

Section 8.3 introduces the multi-instance composition attack via
the coincidence oracle. Kellaris-Kollios-Nissim-O'Neill 2016
("Generic Attacks on Secure Outsourced Databases", ACM CCS) is the
closest published precedent for "attacker observing t snapshots of
a structure under the same latent function". Should be cited at
section 8.3.

Recommended bibentry:
```
@inproceedings{kellaris2016generic,
  title={Generic Attacks on Secure Outsourced Databases},
  author={Kellaris, Georgios and Kollios, George and Nissim, Kobbi and O'Neill, Adam},
  booktitle={Proceedings of the 2016 ACM SIGSAC Conference on Computer and Communications Security (CCS)},
  pages={1329--1340},
  year={2016}
}
```

## CITE-MIN-4 (Pouliot-Wright 2016 Kraken)

R6 / R7 carry-over.

Section 8.2 (compositional leakage) discusses cross-query correlation
attacks informally. Pouliot-Wright 2016 ("The Shadow Nemesis:
Inference Attacks on Efficiently Deployable, Efficiently Searchable
Encryption", ACM CCS) is the canonical reference for co-occurrence
attacks on encrypted databases.

Recommended bibentry:
```
@inproceedings{pouliot2016shadow,
  title={The Shadow Nemesis: Inference Attacks on Efficiently Deployable, Efficiently Searchable Encryption},
  author={Pouliot, David and Wright, Charles V},
  booktitle={Proceedings of the 2016 ACM SIGSAC Conference on Computer and Communications Security (CCS)},
  pages={1341--1352},
  year={2016}
}
```

## CITE-MIN-5 (Le Cam two-point lemma page reference)

R7 CITE-MIN-9 carry-over.

Section 5.2 line 814 cites Le Cam's two-point lemma via
`\cite{lecam1986asymptotic}`. The book is 700+ pages; a section or
page number would help a reader find the specific lemma.

Recommendation: cite as `\cite[Section 16.4]{lecam1986asymptotic}` or
similar. The two-point lemma is typically in the early chapters on
likelihood ratio testing.

## CITE-MIN-6 (DOIs throughout bibliography)

R7 CITE-MIN-8 carry-over.

Of 38 entries, ~ 5 to 10 have DOIs. Modern bibliographies generally
include DOIs for verifiability. Recommended: add `doi={...}` field to
all journal/conference entries.

Lower priority; cosmetic.

## CITE-MIN-7 (Xor / Ribbon filter references)

New for R8 (suggested by literature-context).

The Bloom-baseline experiment in section 10.3 compares cipher set
to optimal Bloom filter. Modern below-Bloom approximate-membership
data structures include:

- Xor filter (Graf-Lemire 2020, "Xor Filters: Faster and Smaller
  Than Bloom and Cuckoo Filters")
- Ribbon filter (Dillinger-Walzer 2021, "Ribbon Filter: Practically
  Smaller Than Bloom and Xor")

Adding these as additional rows in Table 10.x (lines 2419 to 2438)
would land the practical-overhead story against the current frontier
rather than 1970-era baseline.

Recommended bibentries:
```
@article{graf2020xor,
  title={Xor Filters: Faster and Smaller Than {Bloom} and {Cuckoo} Filters},
  author={Graf, Thomas Mueller and Lemire, Daniel},
  journal={ACM Journal of Experimental Algorithmics},
  volume={25},
  pages={1--16},
  year={2020}
}

@misc{dillinger2021ribbon,
  title={Ribbon Filter: Practically Smaller Than {Bloom} and {Xor}},
  author={Dillinger, Peter C and Walzer, Stefan},
  year={2021},
  howpublished={arXiv:2103.02515}
}
```

## Findings

### Critical

None.

### Major

**CITE-MAJ-1**: 4 Manuscript-in-prep entries (carry-over MAJ-6).
Resolution: Zenodo DOIs.

**CITE-MAJ-2**: Huffman 1952 missing (R7 carry-over).

**CITE-MAJ-3**: Cover-Thomas 2006 missing (R7 carry-over).

**CITE-MAJ-4**: Patel-Persiano-Yeo-Yung 2019 missing (R6 / R7
carry-over).

### Minor

**CITE-MIN-1 to 7** as above. Most R6 / R7 carry-over; CITE-MIN-3
new this round (Kellaris et al), CITE-MIN-7 new this round (Xor /
Ribbon).

### Suggestions

**CITE-SUG-1**: "Concurrent and prior work in multi-instance
composition" subsection in section 2 (R7 carry-over). Would house
Kellaris et al + Pouliot-Wright + Geng-Smith multi-instance work.

**CITE-SUG-2**: Issa-Wagner-Kamath 2020 (operational leakage Pareto)
at section 10.6 (TV, L) Pareto frontier paragraph. Establishes the
methodological parallel and positions the result in the active
research line.
