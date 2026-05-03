# Citation Verifier Report (Round 5, 2026-04-30)

**Specialist**: citation-verifier
**Manuscript**: cipher_maps.tex (1841 lines, 26 pages)
**Bibliography**: references.bib (31 entries, prompt claimed 32)

## Summary

- 31 entries in references.bib (prompt overstated count by 1)
- 28 entries cited at least once
- **3 uncited entries**: esposito2020recsplit, kamara2019computationally, kerschbaum2015frequency
- **1 unresolved cross-reference**: cipher-maps cites `[Thm.~7.1]{towell2026rekeying}` but the chain bound is at Theorem 6.1 in the rekeying paper
- **1 likely cross-reference error**: cipher-maps cites `[Theorem~4.3]{towell2026maxconf}` but the entropy decomposition theorem with the Fannes bound is Theorem 4.1 in maxconf

## Critical findings

### CITE-1 (Critical): Cross-paper theorem number mismatch (rekeying)

**Location**: cipher_maps.tex line 1749
**Text**: `\cite[Thm.~7.1]{towell2026rekeying}`
**Context**: The chain confidentiality bound `H(X|V) >= H(X) - log_2(n+1)`.
**Verification**: In `/home/spinoza/github/trapdoor-computing/papers/cipher-rekeying/paper/main.tex`, theorems are numbered by section (`\newtheorem{theorem}{Theorem}[section]`). The chain bound is in §6 "Information-Theoretic Cost" at line 843, label `thm:chain-bound`. With section-relative numbering, this is **Theorem 6.1**, not 7.1.

There is a §7 in the rekeying paper but it is "Applications," not the chain bound location.

**Suggestion**: Change `[Thm.~7.1]` to `[Thm.~6.1]` in cipher_maps.tex line 1749. Verify by building both PDFs and reading the actual numbering.

### CITE-2 (Critical): Cross-paper theorem number mismatch (maxconf)

**Location**: cipher_maps.tex line 661
**Text**: `Full proof and discussion of tightness in \cite[Theorem~4.3]{towell2026maxconf}.`
**Context**: The Fannes-Audenaert bound proof is deferred.
**Verification**: In `/home/spinoza/github/trapdoor-computing/papers/maximizing-confidentiality/main.tex`, theorems are numbered by section. §4 is "The Confidentiality Measure" and contains exactly one theorem (Theorem 4.1, "Entropy ratio decomposition" at line 434). The Fannes-Audenaert bound is **part 3 of Theorem 4.1**.

§4 has no Theorem 4.2 or 4.3. The next theorem (Noise dilution) is at line 531 in §5, making it Theorem 5.1.

**Suggestion**: Change `[Theorem~4.3]` to `[Theorem~4.1, part 3]` or simply `[Theorem~4.1]` in cipher_maps.tex line 661. This is the load-bearing citation for Proposition 5.1, so the wrong number undermines the M1 collapse strategy.

## Major findings

### CITE-3 (Major): RecSplit cited by name but no `\cite{...}` invocation

**Location**: cipher_maps.tex line 1154
**Text**: `A reference implementation using a RecSplit-family PHF achieves 700 documents per second on the 20~Newsgroups corpus`
**Bibliography**: `esposito2020recsplit` is in references.bib (lines 246-252) but never invoked with `\cite{}`.
**Verification**: `grep -n "esposito" cipher_maps.tex` returns no matches.

**Suggestion**: Insert `\cite{esposito2020recsplit}` after "RecSplit-family PHF" at line 1154. The prompt's claim ("RecSplit cited (esposito2020recsplit)") is not reflected in the actual file.

### CITE-4 (Major): Kerschbaum 2015 in bib, never cited

**Location**: bib entry `kerschbaum2015frequency` (lines 238-244 of references.bib).
**Verification**: `grep -n "kerschbaum" cipher_maps.tex` returns no matches.

**Why it matters**: Kerschbaum 2015 is the closest published predecessor for "frequency-hiding via output distribution shaping." The cipher maps paper now centers on this exact mechanism (Shannon-optimal acceptance allocation as both space-optimal and frequency-hiding). A PoPETs reviewer will spot this gap. The state file already flagged it as a "gap" two rounds ago.

**Suggestion**: Add a one-sentence comparison in §2 (Related Work) under a paragraph titled something like "Frequency-hiding constructions." Suggested wording: "Kerschbaum's frequency-hiding OPE~\cite{kerschbaum2015frequency} hides plaintext frequency by injecting random ranks on duplicate inserts; cipher maps hide it by shaping the acceptance partition so that the cipher value distribution matches the output distribution. Both attack the same threat (frequency analysis on encrypted records) by different mechanisms."

### CITE-5 (Major): Kamara-Moataz 2019 in bib, never cited

**Location**: bib entry `kamara2019computationally` (lines 254-261 of references.bib).
**Verification**: `grep -n "kamara" cipher_maps.tex` returns one match, at line 203, but it's "Naveed, Kamara, and Wright" referring to `naveed2015inference`. Kamara-Moataz is never cited.

**Why it matters**: Volume-hiding STE (Kamara-Moataz 2019) achieves the same operational guarantee as cipher maps' totality property by different means. The current Related Work has a paragraph on Cash et al. SSE but no acknowledgement of the volume-hiding sub-line. PoPETs reviewers in the SSE community will notice.

**Suggestion**: Add to §2 the paragraph on SSE: "The volume-hiding line~\cite{kamara2019computationally} is closer to cipher maps' approach: rather than analyzing leakage, it engineers indistinguishability between document-set sizes. Cipher maps achieve a related guarantee structurally (totality + Property 2) at lower per-query cost."

## Minor findings

### CITE-6 (Minor): "Manuscript in preparation" risk for three sister papers

**Locations**:
- bernoulli-types (cited 5 times, including in §2 Related Work and §9.1 Discussion)
- towell2026maxconf (cited 4 times, load-bearing for Proposition 5.1)
- towell2026rekeying (cited 4 times, including for the §9.5 chain bound)
- towell2026algebraic (cited once, for the cipher Boolean type details in §9.4)

**Verification**: All four bib entries are `@misc{...}` with `note={Manuscript in preparation}`. None has a DOI, an arXiv ID, or a permanent URL.

**Why it matters**: A reader who needs to verify Proposition 5.1 (the load-bearing M1-collapse claim) cannot. PoPETs has no formal rule against citing unpublished work, but a Theorem-citation that resolves to nothing is a bad look.

**Suggestion** (deferred to user, already noted in the prompt): Mint Zenodo DOIs at minimum, and ideally arXiv preprints. Update the bib entries with the resulting permanent identifiers. For maximum survivability, post both maxconf and rekeying as arXiv preprints **before** submitting cipher-maps to PoPETs.

### CITE-7 (Minor): No DOIs anywhere in the bibliography

**Verification**: `grep -nE "doi|DOI" references.bib` returns no matches.

**Why it matters**: Modern crypto and PETS venues increasingly request DOI-resolvable bibliography entries. Currently the bib has only journal/conference proceedings without persistent identifiers.

**Suggestion**: Add DOI fields to all entries. This is mechanical (look up via crossref.org) and an hour of work. Already in the next-actions list (m11) but worth restating.

### CITE-8 (Minor): Shannon 1948 citation is to a 1948 BSTJ article, modern reprint preferred

**Location**: lines 149-157 of references.bib (`shannon1948mathematical`).
**Bibtex**: cites volume 27, number 3, pages 379-423.
**Note**: The Bell System Technical Journal article was a two-part publication (vols 27.3 and 27.4). The standard form in the QIF and information-theory literatures cites both parts or uses the reprint. Not strictly an error, but stylistic.

**Suggestion**: Either cite both parts (`pages={379--423, 623--656}`) or switch to the standard reprint citation. Low priority.

## Suggestions (non-blocking)

- **CITE-S1**: Consider adding Köpf-Smith 2010 ("Vulnerability bounds and leakage resilience of blinded cryptography against timing attacks") to broaden the QIF citation base. The paper currently cites three QIF references; one more would help substantiate the "QIF tradition" claim against expert reviewers.

- **CITE-S2**: Consider citing Warner 1965 (randomized response) as a historical anchor for the deniability proposition (§9.4, prop:deniability). The Bayesian deniability formula is mathematically the standard randomized-response posterior; acknowledging the antecedent is good scholarship.

- **CITE-S3**: The cipher-maps paper repeatedly mentions the "trapdoor Boolean algebra" (§4.4 paragraph, §6.4 introduction, §9.3) and cites it as `bernoulli-types`. But the bibtex entry `bernoulli-types` is titled "Bernoulli Sets and Maps", which is a different paper from the trapdoor Boolean algebra one. The state file lists `boolean-algebra-over-trapdoor-sets` as a companion paper but that bib entry doesn't exist.

  **Action**: either add a bib entry `towell2024boolean` for the trapdoor Boolean algebra paper, or clarify that `bernoulli-types` covers it. Currently the citation is misleading: a reader following `bernoulli-types` won't find the trapdoor Boolean algebra material there.

## Verification matrix

| Claim in cipher-maps | Verified against | Result |
|---|---|---|
| Theorem 4.3 of maxconf gives Fannes bound | maxconf §4 | **Wrong number**: actual is Theorem 4.1 |
| Theorem 7.1 of rekeying gives chain bound | rekeying §7 | **Wrong number**: actual is Theorem 6.1 |
| RecSplit cited at line 1154 | bib | **Missing**: name appears, no `\cite` |
| Kerschbaum 2015 in bib | bib + tex | **Uncited**: in bib, never invoked |
| Kamara-Moataz 2019 in bib | bib + tex | **Uncited**: in bib, never invoked |
| Smith 2009 cited | bib + tex | OK (lines 64, 124, 577, 635) |
| Alvim 2012 cited | bib + tex | OK (lines 64, 124, 635) |
| Dodis-Smith 2005 cited | bib + tex | OK (line 124) |
| Cash 2015 leakage-abuse cited | bib + tex | OK (line 207) |
| Juels-Ristenpart honey cited | bib + tex | OK (line 224) |

## Bibliography integrity

- Build is clean: `pdflatex` produces no `Citation undefined` warnings.
- BibTeX log is clean: `cipher_maps.blg` shows no errors.
- All `\cite` invocations resolve.
- Three bib entries are dead weight (uncited).

## Recommendation

**Two critical corrections required**:
1. Fix Theorem number citations to maxconf and rekeying. These are load-bearing for the M1 collapse strategy.
2. Drop the missing citations (esposito, kerschbaum, kamara) into place; one editorial pass will resolve them.

After those fixes, citation hygiene is acceptable for PoPETs. The unpublished-sister-paper risk remains and should be addressed by minting Zenodo DOIs or arXiv preprints **before** submission.
