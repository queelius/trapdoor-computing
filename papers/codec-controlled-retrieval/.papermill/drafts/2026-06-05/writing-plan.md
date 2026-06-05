# Writing plan and construction record (2026-06-05)

This paper was drafted by reshaping a complete, proven, reviewed source note
(`source/construction-note.md`, the snapshot of the maph codec-controlled-retrieval
note at commit a79d9c0) into PoPETs venue prose. Because the technical substance
(theorems T1 through T5, the FreqDist security model, the two-attacks reconciliation,
experiments E1 through E4, and the related-work ledger) was already established and
adversarially reviewed, this was a single-orchestrator reshaping pass, not a
multi-agent generation. No claims were generated or re-derived; every theorem
statement, bound, and number was transcribed faithfully and only the prose and
structure were adapted.

## Section assignment (all reshaped by the lead author from the source note)

| Paper section | Source-note origin | Role |
|---|---|---|
| 1 Introduction | thesis-refined + ledger opener | Motivate the gap; tiered contributions (A baseline, B novel, C headline); one-breath threat model; cipher-maps positioning |
| 2 Background and the linear-retrieval view | T1/T2 "Setup and facts" + outline sec 2 | Codecs, codespace shares alpha(v); lookup(y)=a_y^T z as a dense ~64-bit GF(2) band (NOT a 3-wise XOR); the span W; idealized model M1 |
| 3 Non-member output uniform on the stored span | T1, T2 | thm:support (R(z)=W, proven), thm:idealized (P(out=v)=|class(v) cap W|/|W| under M1) |
| 4 Frequency independence | T3 | thm:freqindep (W depends only on support, not multiplicities) |
| 5 Sharp codec-control threshold [HEADLINE] | T4 | lem:subspace-coset, thm:threshold (rank pi|_W = log2 K, transversality, sharp step; gf2_rank bridge; ex:m4 worked instance; rem:skewed deferral) |
| 6 Idealized to real | T5 | delta small, scale-independent to 1e7, sampling floor 0.00334, redundancy-governed; labeled characterization not closed-form bound |
| 7 Security: frequency-analysis resistance | Security/FreqDist section | def:freqdist, thm:freqdist-ideal (Adv=0 under M1), thm:freqdist-real (Adv <= 2(delta0+delta1)); independence-not-comparative; scope |
| 8 Two attacks pull opposite ways | Reconciliation section | flat defeats freq analysis; concentrated/Huffman defeats coincidence oracle acc(t)=1-(1/2)sum alpha^t; sign-error correction; Pareto frontier |
| 9 Evaluation | Experiments E1-E4 | Tables with the REAL numbers from source/results/; implementation note |
| 10 Related work and novelty | Related-work ledger | Three-tier ledger; four must-differentiate items; the three gap cites |
| 11 Discussion/limitations/conclusion | Scope + closing | Open problems, takeaway |
| Appendix A | T1/T2 Step 3 | Full induction that R(z)=W (sketched in body, full in appendix) |

## Editorial judgments (places venue prose risked softening a precise claim)

1. **Lead with B/C, cite A as baseline (self-collision guard).** The abstract
   codec-output law P(out=v) ~ |class(v)|/2^M is the author's own prior work
   (bernoulli_maps singular-hash-map) and the Honey-Encryption DTE idea. Per the hard
   rules, the abstract does NOT headline it; the contributions list explicitly marks it
   tier A ("cited not claimed"), and the related-work section credits it before claiming
   anything. The abstract leads with "junk is a designable object" (the B move) and the
   sharp threshold (the C headline).

2. **T1 framed as an idealization throughout, not slipped in as a theorem.** The source
   note is emphatic that T1 (uniform-on-W) is the model M1, not derived from the band
   geometry; thm:idealized is stated as conditional on def:M1, and the body repeatedly
   signposts that the gap to the real construction is T5. I preserved this division
   exactly; softening it (e.g. stating uniformity as unconditional) would overclaim.

3. **thm:support claims only what is true about the reachable set.** R(z)=W is exact
   (full row space over all coefficient vectors), but the reachable single-band outputs
   are stated as "contained in W and span W", NOT "equal W as a raw set". This precise
   distinction from the note is kept verbatim, including the genericity remark
   (rem:genericity) that it is a property of THIS builder (free slots zero, no random
   fill), not of ribbon retrieval in the abstract.

4. **T5 labeled a characterization, not a bound.** rem:t5-bound states the empirical
   observation plus a labeled big-O and an explicitly-non-proven conjecture; I did not
   upgrade it to a theorem. The sampling-floor value 0.00334 uses the correct MAD-based
   computation (note flags the cruder standard-error proxy 0.00418 as a 1.25x overstate);
   I kept the MAD value and the parenthetical correction.

5. **Coincidence-oracle direction stated correctly (the corrected direction).** acc(t) =
   1 - (1/2) sum alpha(v)^t, defender wants acc small hence S(t) large, so CONCENTRATED
   (Huffman) defends best and UNIFORM worst. rem:sign records the inverted "uniform
   defends best" reading as wrong. In E4 (tab:e4) I followed the note's accurate framing:
   accuracy is MONOTONE in concentration and intermediate_padded (0.90) at acc 0.672 is
   the best defense; I did not repeat the results.md line-46 shorthand that only compared
   uniform vs huffman.

6. **Security framed as INDEPENDENCE, not comparative.** Per the note and hard rules,
   the FreqDist result is an indistinguishability statement (Adv=0 idealized; symmetric
   residual real), explicitly NOT "codec X leaks c times less than Y". This is what makes
   it immune to the direction error that inverted the coincidence-oracle reading; I kept
   the "independence not comparative" subsection intact.

## Numbers transcribed (verified against source/results/ CSVs)

- E1 span cliff: balanced_M4_K4 0.500 (rank 1) -> 0.00277 (rank 2);
  balanced_M8_K8 0.500 (rank 2) -> 0.00505 (rank 3); skewed_M4 0.251 (rank 1) ->
  0.00238 (rank 2). Sub-threshold CIs degenerate (zero-width).
- E2: baselines uniform 0.00292, mid 0.00360, skew_b 0.00381, skew_a 0.01897; cross
  pairs all skew_a-inclusive ~0.014, rich-rich ~0.0036.
- E3: 0.00352 (1e4), 0.00311 (1e5), 0.00352 (1e6), 0.00284 (1e7); sampling floor 0.00334.
- E4: at t=4, uniform 0.99902, intermediate_zipf 0.98240, huffman 0.96667,
  intermediate_padded 0.67195; MC matches closed form in every cell.
- Security bound: Adv <= 2(delta0+delta1); ~0.012 rich/rich, ~0.04 one-side-thin.

All checked equal to the CSVs (codec_span/results.csv, freq_independence/results.csv,
scale/results.csv, coincidence_oracle/results.md).

## Build

`cd paper && make` compiles cleanly via pdflatex + bibtex (Makefile runs four pdflatex
passes after the bibtex step for full cross-reference stability). Output: 22 pages,
zero undefined references/citations, zero overfull/underfull boxes, no hard errors.
Three benign bibtex metadata warnings remain (empty booktitle for the ribbon arXiv
entry; empty year for the two unpublished in-house works towell2026ciphermaps and
towell_bernoulli_maps); these are properties of refs.bib as provided and do not affect
compilation or citation resolution.

## Repairs made inside the paper directory (only)

- refs.bib: escaped an unescaped underscore in the note field of towell_bernoulli_maps
  (bernoulli/papers/bernoulli\_maps) that broke bibtex's generated .bbl in text mode.
- Makefile: added refs.bib as a prerequisite of the PDF target and a fourth pdflatex
  pass so a plain `make` reaches fully stable cross-references.
- preamble: added a \TVsamp macro for the sampling-noise total-variation floor, since
  \TV already carries a subscript (d_{TV}) and subscripting it again is a double
  subscript error.

## Cite keys

Used (all present in refs.bib): chazelle2004bloomier, cheng2019pmte,
dillinger2021ribbon, dillinger2022burr, filic2022adversarial, graf2020xor,
graf2022binaryfuse, grubbs2020pancake, hu2025retrieval, juels2014honey,
lacharite2018fse, naveed2015inference, patel2019volumehiding, towell2026ciphermaps,
towell_bernoulli_maps.

Referenced but NOT in refs.bib: none. (dietzfelbinger2008succinct and
dietzfelbinger2019gauss are in refs.bib but not cited in the body; they are available
if a reviewer wants the retrieval space lower bound or the GF(2) Gaussian-elimination
foundation cited explicitly.)
