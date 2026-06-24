# Methodology Auditor Report (Round 5, 2026-04-30)

**Specialist**: methodology-auditor
**Manuscript**: cipher_maps.tex (1841 lines)

## Summary

The cipher maps paper is primarily theoretical (theorems, propositions, lower bounds). Its experimental content is contained in two paragraphs of §9.4 (Application: Encrypted Search). The R5 review prompt claimed §10 was promoted to top-level with five subsections including a "20 Newsgroups Validation" section structured as Setup/Construction/Single-term/Multi-term/Reproducibility. **This is not in the manuscript.** The actual structure remains as in R4: a single "Experimental validation" paragraph (lines 1677-1704) inside §9.4.

This is the most consequential R5 finding: the user planned a Phase 5 §10 promotion as the structural fix for MAJ-2 (no experimental evaluation). The Phase 5 work did not land in the cipher_maps.tex file under review.

**Findings**: 0 critical, 4 major, 5 minor.

## Critical findings

None directly methodological, but see MAJ-1 below.

## Major findings

### METH-1 (Major): Phase 5 §10 promotion not reflected in manuscript

**Location**: cipher_maps.tex §9.4 (lines 1677-1704)
**Quoted text** (the entire experimental content, full passage):
> "Experimental validation. A reference implementation (cipher-maps, Python) validates the encrypted search application on the 20 Newsgroups corpus (18,266 documents, 58,903 unique words). Construction uses perfect hash functions (via phobic) with $n = 8$-bit cipher Booleans ($p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$). At 5,000 documents: construction takes 5.9 seconds (843 documents per second), single-term queries achieve perfect recall (1.0) with precision 0.39 (matching the theoretical false positive rate $p_T = 0.05$ per document). Multi-term AND queries improve precision (FP drops from 248 to 12 for 3-term AND) while maintaining perfect recall. OR and NOT queries lose recall (0.97 and 0.88 respectively) due to noise propagation through the cipher Boolean operations. The full 18,266-document index builds in 25.6 seconds.
>
> Boolean search queries composed from AND, OR, and NOT can be evaluated entirely on the untrusted machine using cipher Boolean types. A cipher Boolean type partitions the hash space into True, False, and noise regions (e.g., 5%, 90%, 5% respectively). AND, OR, and NOT are themselves cipher maps over the cipher Boolean space. Members of a cipher set are forced into the True region by construction; non-members land randomly in True (5%, the false positive rate), False (90%), or noise (5%). Experimental validation on 5,000 documents shows perfect recall for AND queries with false positives decreasing from 248 (single term) to 12 (3-term AND). Details are developed in the companion paper on algebraic cipher types."

**Problem**: This is essentially the same experimental content from R4. Specifically:
1. Still missing: hardware specification (CPU model, memory, OS, Python version, library versions).
2. Still missing: experimental protocol (how queries were sampled, how multi-term queries were generated, what counts as "single term"/"multi-term").
3. Still missing: trial count and statistical confidence (one number per metric, no error bars).
4. Still missing: comparison baselines (no Bloom filter or SSE measurements at the same precision/recall).
5. Still missing: query distribution (uniform over vocabulary? Zipfian? sampled from the corpus?).
6. The 5%/90%/5% partition is asserted but not justified relative to the data.
7. The two paragraphs partially duplicate each other: the second paragraph re-introduces "perfect recall for AND queries" and the FP-drop numbers (248 to 12) that appear in the first paragraph.

The R4 nm5/nm6/nm8 issues persist. The R5 prompt asserted these were addressed structurally; they were not.

**Suggestion**: This is the path-forward decision the user must make. Two options:
- **Option A (minimum)**: Treat the experimental paragraph as preliminary-only, remove duplicated material, add a brief reproducibility statement ("Code at https://github.com/queelius/cipher-maps; experiments run on commit X with seed Y on hardware Z"). Acknowledge that full evaluation is in companion work or future work.
- **Option B (preferred)**: Promote §9.4 to a real §10 evaluation section as the prompt described. This requires running additional experiments to fill in baselines, error bars, and query-distribution sweeps. The 2-4 week budget in the next-actions list of the state file applies.

Either way, the current state misrepresents what was done in R5 against what the prompt claims.

### METH-2 (Major): Construction-time numbers (843 docs/sec, 25.6 seconds) lack confidence intervals

**Location**: cipher_maps.tex lines 1683-1685 and 1692
**Quoted text**:
> "At 5,000 documents: construction takes 5.9 seconds (843 documents per second) [...] The full 18,266-document index builds in 25.6 seconds."

**Problem**: Single-trial timing measurements without variance. "843 docs/sec" is one trial; the underlying construction algorithm has stochastic seed search (Algorithm 6.3 with random shuffle), so trial-to-trial variance is real and unreported.

The §6.4 "Construction Time and Bucketing" section also reports a single number ("700 documents per second" at line 1154 for the seed-search comparison). Same issue.

**Suggestion**: Run construction 30 times, report mean and 95% CI. If the CI is tight (e.g., $\pm 5\%$), one number is fine but the "averaged over 30 trials" attribution is needed. Industry standard for construction-time benchmarks.

### METH-3 (Major): Precision metric calculation is opaque

**Location**: cipher_maps.tex lines 1684-1685
**Quoted text**:
> "single-term queries achieve perfect recall (1.0) with precision 0.39 (matching the theoretical false positive rate $p_T = 0.05$ per document)"

**Problem**: Precision = 0.39 with FPR = 0.05 per document and 5,000 documents implies false-positive count ≈ 5000 × 0.05 ≈ 250 (matching the "248" later in the paragraph). True positives must be such that 250 / (TP + 250) ≈ 0.61, giving TP ≈ 160-ish, depending on rounding.

But this calculation requires knowing **which queries**: the precision number depends entirely on the query. A vocabulary-uniform random query has expected TP that varies wildly with the rarity of the term. The paper does not say what query distribution generated the 0.39 precision.

The reader cannot reconstruct or sanity-check the number without the protocol.

**Suggestion**: State the query distribution explicitly. E.g., "queries sampled uniformly from the corpus vocabulary, restricted to terms appearing in $\geq 5$ documents, $N = 100$ queries per setting." Without this, the precision number is uninterpretable.

### METH-4 (Major): "Cipher-maps Python library" is cited as the implementation but not characterized

**Location**: cipher_maps.tex line 1678
**Quoted text**: "A reference implementation (cipher-maps, Python)"
**Footnote**: none.
**Bibliography**: no entry.

**Problem**: The library is referenced informally. There's no URL, no version, no commit hash, no DOI. The state file (`.papermill/state.md`) and parent CLAUDE.md identify the implementation as `~/github/cipher-maps/`, but the paper doesn't link it.

**Suggestion**: Add a footnote on first mention: "Available at \url{https://github.com/queelius/cipher-maps}, commit \texttt{XXXXXX} (April 2026)." Optionally cite a Zenodo-archived snapshot for permanence.

The same applies to the `phobic` library mention at line 1683 (unannotated, no link).

## Minor findings

### METH-5 (Minor): The 5%/90%/5% partition is asserted not justified

**Location**: cipher_maps.tex line 1683 (asserted) and 1697-1700 (re-asserted in next paragraph)
**Quoted text**: "$p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$"

**Problem**: This partition is non-symmetric and unjustified. Why not 10/80/10? Or 5/85/10? The paper does not discuss the design space of $(p_T, p_F, p_N)$ trade-offs.

A reader expects the choice to be motivated. The implicit assumption is "5% acceptance for True corresponds to a Bloom-filter-equivalent FPR of 5%, 90% for False is the dominant region, 5% for noise allows deniability." But this is reverse-engineered from the numbers; the paper doesn't say so.

**Suggestion**: Insert a sentence: "The partition $p_T = 0.05$, $p_F = 0.90$, $p_N = 0.05$ corresponds to a 5% false-positive rate (matching standard Bloom filter parameters at $\sim 7$ bits/element) with 5% acceptance allocated to the noise region for deniability (Proposition 9.4)."

### METH-6 (Minor): No comparison to standard Bloom filter at equivalent FPR

**Location**: §9.4 evaluation paragraph
**Problem**: The cipher Boolean construction is positioned as a privacy-enhanced Bloom filter (Remark 6.8). A natural sanity check: build a Bloom filter at FPR = 0.05 on the same corpus, measure construction time, query time, recall, and precision. Compare. This is the comparison the paper invites by Remark 6.8 but doesn't deliver.

**Suggestion**: A 3-row table comparing (Bloom filter, cipher map at $\eta=0$, cipher map at $\eta=0.01$) on (build time, query time, recall, precision) would close METH-6. Probably 1 day of work using the existing cipher-maps Python library.

### METH-7 (Minor): Construction time table at line 1086-1098 has unexplained rows

**Location**: cipher_maps.tex lines 1086-1098 (the $\alpha$ vs $\eta$ table)
**Quoted text**:
> "$\alpha = 0.5$, $\eta = 0$: $2^{100}$ ... $\alpha = 0.99$, $\eta = 0.05$: $1.0$"

**Problem**: This is a calculation, not data. The numbers are derived from Proposition 6.4 (Poisson binomial CDF). The table is fine as illustration but should be labeled as theoretical/calculated, not measured.

**Suggestion**: Caption the table "Theoretical seeds-tried estimates from the Poisson binomial bound (Proposition 6.4)" to distinguish it from the empirical timing results in §9.4.

### METH-8 (Minor): "phobic" library named but not described

**Location**: cipher_maps.tex line 1683
**Problem**: "phobic" is jargon for a specific PHF library. The state file (R4 nm16) flagged this as a known issue. The R5 prompt claims phobic was explained (Phase 6 quick win, nm16). I cannot find any explanation in the manuscript.

**Suggestion**: Add a footnote: "phobic (\url{https://github.com/jermp/phobic}) is a recent practical PHF implementation derived from the PTHash family." The current text reads as an inside joke to readers unfamiliar with the library.

### METH-9 (Minor): The "OR and NOT lose recall (0.97 and 0.88)" is unexplained

**Location**: cipher_maps.tex lines 1689-1691
**Quoted text**: "OR and NOT queries lose recall (0.97 and 0.88 respectively) due to noise propagation through the cipher Boolean operations."

**Problem**: "Noise propagation" is asserted as the mechanism, but the calculation is not shown. From Theorem 7.1 (composition correctness), $\eta_{\mathrm{NOT}}$ should be computable from the cipher Boolean partition (5/90/5). For NOT specifically, recall = 0.88 implies a 12% loss; this should match a calculation from the framework.

**Suggestion**: Add a one-sentence calculation: "For NOT queries, the recall loss matches the predicted $\eta_{\mathrm{NOT}}$ from Theorem 7.1 applied to the 5/90/5 partition: [show calculation, expect $\approx 0.10$ to $0.12$]." This connects the experimental result to the theoretical framework, which is the paper's main contribution.

## Methodology suggestions

- **METH-S1**: The §6.4 paragraph mentioning "RecSplit-family PHF achieves 700 documents per second on the 20 Newsgroups corpus, compared to approximately 10 documents per second with the seed search construction" claims a 70x speedup. This is a real, useful comparison and arguably the most informative experimental result in the paper. Worth promoting to a small table with construction-time measurements at multiple corpus sizes (1000, 5000, 10000, 18266).

- **METH-S2**: The cipher-maps Python library presumably has unit tests for the four properties (totality, representation uniformity, correctness, composability). A "validation experiment" measuring each property on the constructed maps (e.g., empirically estimating $\delta$ via Monte Carlo) would convert the paper from "framework + preliminary timing" to "framework + property validation." The maxconf paper already implements a "leakage analyzer" (line 1058 of maxconf), which could be applied here.

## Reproducibility checklist (PoPETs format)

| Item | Status |
|---|---|
| Code link | **Missing** (mentioned in prose, not as URL) |
| Hardware spec | Missing |
| Software versions (Python, library deps) | Missing |
| Random seed | Missing |
| Number of trials | Missing |
| Confidence intervals | Missing |
| Query distribution | Missing |
| Baseline comparisons | Missing |
| Data link (20 Newsgroups specific version) | Missing |
| Wall-clock methodology (CPU vs wall, single-thread?) | Missing |

This checklist is what PoPETs reviewers will populate. Currently only one item is satisfied (corpus identified). The rest are blockers for any methodology-conscious reviewer.

## Recommendation

The methodological gap is the single largest open issue for cipher-maps. The R5 round was supposed to address MAJ-2 by promoting the experiments to §10; this did not happen. Two paths:
1. **Defer evaluation to companion work** (algebraic-cipher-types or maxconf), and adjust cipher-maps to be honest about the deferral (a one-paragraph "implementation evidence" with reproducibility metadata, not a "validation").
2. **Do the §10 promotion** as the prompt described, requiring 2-4 weeks of additional experiments.

Without one of these, MAJ-2 persists into R6 and is the principal threat to PoPETs survivability after the citation fixes.
