# Citation Verifier (2026-04-13)

## Scope

Bibliography integrity, citation accuracy, dead bib entries, missing citations.

## Summary

Bibliography has expanded from 10 to 21 entries between 2026-04-12 and 2026-04-13. All 21 entries are now cited at least once. No dead bib entries remain. The four new references (Smith 2009 QIF, Cash 2015, Grubbs 2017, Lang 1995) are appropriately placed. The bibliography is no longer thin in absolute terms; it is on the lower end of expectations for PLAS but not disqualifying.

Three carry-forward concerns remain from 2026-04-12: self-citations to unpublished manuscripts (M9), a couple of positioning gaps for cipher TM and @cipher_node decorator, and the phobic library still uncited.

## Verification details

### Bibliography integrity

- Total bib entries: 21
- Total citation calls in body: 29 (some entries cited multiple times)
- Distinct keys cited: 21
- Bib entries never cited: 0
- Cites without bib entry: 0
- All cleveref `\Cref` and `\cite` calls resolve in the build (no warnings).

### New references added between 2026-04-12 and 2026-04-13

| Key | Used at | Appropriate? |
|---|---|---|
| `smith2009foundations` | §2 Related Work, QIF paragraph (line 188) and §5 Thm 5.3 context | YES, grounds the entropy-form bound |
| `cash2015leakage` | §2 SSE paragraph (line 176) | YES, leakage-abuse attacks on SSE |
| `grubbs2017leakage` | §2 SSE paragraph (line 177) | YES, leakage-abuse on encrypted DBs |
| `lang1995newsweeder` | §2 related concepts (line 203) | YES, dataset citation |
| `bloom1970space` | §2 (line 200), connecting cipher Boolean to Bloom filter | YES |
| `fredman1984storing` | §6.2 Def 6.2 (line 1050), PHF backing | YES |
| `shannon1948mathematical` | §7.1 Remark 7.1 (line 1221), source coding | YES |
| `song2000practical` | §2 SSE paragraph (line 167) | YES |
| `islam2012access` | §2 SSE paragraph (line 175) | YES |
| `turing1936computable` | §2 (line 197), TM origin | YES |
| `towell2026maxconf` | §2 (line 206), sibling work | YES |

The 7 previously dead bib entries are now all in use.

### Carry-forward findings

#### CV-CF-1. Unpublished self-citations are load-bearing (carry-forward of M9)

- `towell2026cipher`: cited 16 times. Core definitions (cipher map, four properties, composition), preliminaries, and several specific propositions (`[towell2026cipher, Sec. 6]` for noise budget, `[towell2026cipher, Sec. 9]` for encoding granularity, `[towell2026cipher, Prop. 9.1]` for joint distribution preservation) depend on this manuscript.
- `towell2026bernoulli`: cited 4 times. Bernoulli error model, accuracy-side analysis, FPR composition prediction.
- `towell2026maxconf`: cited 1 time, sibling work in §2.

A reviewer cannot fully evaluate Theorem 5.3 or Section 7 without access to the cipher-maps manuscript.

**Suggestion**: post `towell2026cipher` and `towell2026bernoulli` to IACR ePrint or arXiv before submission. Alternative: expand §3 Preliminaries with verbatim composition theorem and representation-uniformity statement. The current Preliminaries (lines 209-269) is about 60 lines and could be doubled to be self-contained.

#### CV-CF-2. phobic PHF library uncited

- Location: §7.3, line 1313, "PHF backend via phobic".
- Status: uncited.
- Suggestion: add a footnote with the URL or a citation to the library's paper if any.

#### CV-CF-3. SoK-style references not present

The 2026-04-12 review suggested adding modern surveys: Viand-Jattke-Hithnawi 2021 (FHE compilers SoK), Naveed-Wright 2015 update, recent FHE compiler tools. None added in 2026-04-13. This is not strictly necessary but PLAS papers commonly include 1-2 SoK-style references.

### New citation observations (2026-04-13)

#### CV-NEW-1. No citations for obfuscation literature

The cipher Turing machine in §6.1 is structurally close to obfuscated FSMs/TMs. The paper does not cite:
- Lynn, Prabhakaran, Sahai 2004 "Positive results and techniques for obfuscation" (TCC).
- Wichs, Zirdelis 2017 "Obfuscating compute-and-compare programs" (FOCS).
- Garbled TM literature: Goldwasser-Kalai-Popa-Vaikuntanathan-Zeldovich 2013, Lu-Ostrovsky 2013.

A reviewer asking "how does the cipher TM differ from an obfuscated TM?" will not have a textual answer. The current text only preempts ORAM (line 1019-1030).

#### CV-NEW-2. No citations for FHE compilers

The @cipher_node decorator pattern is structurally similar to FHE compiler annotations. The paper does not cite:
- Concrete (Zama).
- HEIR (Google MLIR project).
- Viand, Jattke, Hithnawi 2021 "SoK: fully homomorphic encryption compilers".

Suggestion: a single `\cite{viand2021sok}` in §6.2 establishing that cipher-node annotations belong to a known design pattern.

### Positive observations

- The IFC, FE, SSE, QIF coverage is clean.
- The dataset citation (Lang 1995) closes a 2026-04-12 finding.
- The QIF citation (Smith 2009) is genuinely supportive of the new entropy-form theorem.
- Random oracles (Bellare-Rogaway 1993) used appropriately in the totality property.
- All bib entries are correctly formatted and consistent in style.

## Citation accuracy spot checks

I verified five citations by cross-referencing the cited claims against the cited papers:

1. `goldreich1996software` for ORAM access-pattern hiding (line 1021): correct.
2. `boneh2011functional` for FE definitions (line 153): correct.
3. `curtmola2006searchable` for rigorous SSE foundations (line 168): correct.
4. `smith2009foundations` for QIF entropy-form leakage (line 188): correct (Smith's QIF measures use min-entropy; the paper's bound uses Shannon entropy, but the QIF tradition encompasses both).
5. `bellare1993random` for random oracle model (line 234, line 723): correct.

No citation accuracy issues found.

## Verdict

Bibliography is now in acceptable shape. The 2026-04-13 expansion closes the largest 2026-04-12 gap. Two recommendations for the next revision:
1. Add 1-3 obfuscation-literature citations to §6.1 (cipher TM positioning).
2. Add 1 FHE-compiler citation to §6.2 (@cipher_node positioning).

The unpublished self-citation issue (CV-CF-1) is more consequential than any new citation gap. Posting `towell2026cipher` to a public preprint server is a higher priority than adding more references.
