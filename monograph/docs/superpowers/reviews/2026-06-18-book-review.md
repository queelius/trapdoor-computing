# Full-Book Review + Revision Record

**Date:** 2026-06-18
**Scope:** the complete monograph (14 chapters + 3 appendices, 70pp), the first end-to-end read after part-by-part drafting.
**Method:** three specialist auditors dispatched in parallel (cross-reference integrity, cold-read for seams, independent numeric recheck), synthesized and acted on here.

## Auditor verdicts

| Auditor | Verdict | Summary |
|---|---|---|
| cross-ref | **PASS** | 0 broken refs, 0 label collisions; all 75 referenced labels resolve; 10/10 load-bearing semantic spot-checks match; the only notes are orphaned section anchors (harmless) and the benign hyperref `page.i` duplicate. |
| math | **PASS** | every numeric claim (Ch 3-10) independently recomputed in Python; zero errors. All landmines intact: Fannes-not-Pinsker, K propto D, orbit denominator `|X|`, Assouad-not-Le-Cam, image-relative `H*`. One minor: Ch 6 bit-ordering convention was unstated. |
| quality (cold-read) | **BLOCKING** (now resolved) | the book reads as one coherent treatment, the watchlist threads cleanly and the six-movement arc holds; but the part-by-part drafting left one blocking seam and three substantive ones, listed below. |

## Findings and revisions

All findings from the cold-read are addressed; the book rebuilds clean (70pp, 0 undefined refs).

| # | Severity | Finding | Fix |
|---|---|---|---|
| 1 | **BLOCKING** | The flagship watchlist example (`ex:watchlist-numbers`) conflated the **input support** `im(enc)` (10 tokens, governs `delta`, `H*`) with the **output acceptance set** `union A(y)` (~4 codewords, governs `epsilon`); a careful reader could not reconcile "10 or 4 valid tokens?" | Ch 3: rewrote the example's close to name the two sets explicitly as the two ends of the pipeline `dec(f-hat(enc(x,k)))`, ten input tokens governing `delta` and `H*=log2 10`, four output codewords governing `epsilon`; numbers unchanged. |
| 2 | SUBSTANTIVE | Ch 6 promised the equality channel is "taken up at the active-adversary scale later in this part" (Ch 8), but Ch 8 never paid it off. | Ch 6: redirected the forward-reference to the real payoffs, the multiple-representation machinery (`def:uniformity`) that buys it back, and the multi-instance coincidence leakage that `part:confidentiality` measures. |
| 3 | SUBSTANTIVE | The region-shape tension was framed inconsistently across Ch 5/10/12 ("space-optimal != confidentiality-optimal" vs Ch 10's "Huffman-style" coincidence defense, which is also the space-optimal Huffman). | Ch 5: reframed as three allocations pulling in different directions (space-optimal `propto Pr`, frequency-flat, coincidence-concentrated), a frontier rather than an optimum, forward to Ch 12. Ch 10: dropped "Huffman-style" for the coincidence defense (now "concentrated, mass on a few regions"), removing the collision with space-optimal Huffman. |
| 4 | SUBSTANTIVE | `alpha` overloaded: acceptance probability `alpha(y)=|A(y)|/2^n` (Ch 5/10) vs Bernoulli false-positive rate `alpha` (App A). | App A: added a disambiguating clause distinguishing the two and noting their relationship (`FPR ~ epsilon = sum_y alpha(y)` for a HashSet). |
| 5 | MINOR | Ch 6 `ex:boolean-watchlist` silently switched to `n=8` (bit-image width) while citing the `n=12` token example, and never stated the bit-ordering convention. | Ch 6: noted `n=8` is the bit-image width (distinct from the 12-bit token space) and stated bit positions numbered from the right (0 = LSB). |
| 6 | MINOR | Ch 8 typed-chains read as a contradiction ("compounds through the chain" then "bounded by the sum"). | Ch 8: reworded as super-linear growth with the sum as an explicit *loose upper bound*. |
| 7 | MINOR (declined) | Ch 14's frank self-critique has no antecedent earlier in the book. | Left as deliberate closing candor (the auditor marked it optional); appropriate in a roadmap chapter. |

## Net

Cross-reference and numeric integrity were already clean; the value of the full pass was the cold-read, which found exactly the kind of seams part-by-part drafting produces, one of them in the most-reused example. All blocking and substantive findings are fixed; the book now reads as one coherent treatment with its flagship example unambiguous. No landmine reverted; build clean at 70pp.
