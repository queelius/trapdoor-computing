# Literature Context, Round 6 (2026-05-02)

This packet merges what the orchestrator could verify against the cited
literature plus current bibliographic knowledge for venue positioning.
(Subagent dispatch was unavailable; this is the orchestrator's
direct-read survey.)

## State of the Art (relevant venues)

### PoPETs / PETS positioning

PoPETs accepts both:

- **Cryptographic security** (simulation-based, indistinguishability,
  game-based), dominant in SSE / structured encryption tracks.
- **Quantitative leakage analysis** (information-theoretic bounds,
  empirical leakage measurement, anonymity sets), dominant in
  anonymous communication, statistical privacy, and leakage-abuse
  attack/defense tracks.

Cipher-maps lands in the latter camp. Recent precedents at PoPETs that
have been accepted with QIF-style or measurable-leakage arguments
include the leakage-abuse defense literature (Cash, Grubbs, Perry,
Ristenpart-style attacker assumptions), the mosaic/PRR-based
"information leakage of differentially private mechanisms" line
(Ding, Kifer, Wang and follow-ons), and several anonymity-set quantification
papers. The paper's QIF positioning is therefore venue-appropriate.
However, PoPETs reviewers will look for at least one of:
(a) a tight information-theoretic bound proven in the paper,
(b) a concrete attack or measurement against the bound, or
(c) a concrete real-world deployment plus reproducibility evidence.

The current cipher-maps draft has (a) (Theorem 6.1 lower bound,
Theorem 6.2 achievability, Theorem 7.1 composition, Proposition 5.1
Fannes-Audenaert bridge) and a partial (c) (preliminary
20 Newsgroups validation in section 10.3). It does not have (b). Reviewers
familiar with leakage-abuse will likely ask "what attack achieves the
delta bound, or what's the gap between bound and observed leakage?"

### Frequency-hiding / volume-hiding cited adequately?

Now-cited (R6):
- Kerschbaum 2015 frequency-hiding OPE, cited with mechanism contrast.
- Kamara and Moataz 2019 computationally volume-hiding STE, cited as SSE-side analogue.

Potentially missed (recommend adding if room):

- **Patel, Persiano, Yeo, Yung 2019 (CCS)**, "Mitigating leakage in
  secure cloud-hosted data structures: Volume-hiding for multi-maps via
  hashing." This is the mainline volume-hiding multi-map construction,
  more directly comparable to cipher-maps' "every cipher-map evaluation
  hides volume by construction" claim than Kamara and Moataz alone. If the
  cipher-maps paper claims to subsume volume-hiding via Property 1 plus
  Property 2, this paper is the cleanest comparison point. **Strong
  recommend** add as one-sentence cite in section 2.

- **Lacharite, Minaud, Paterson 2018 (S&P)**, "Improved reconstruction
  attacks on encrypted data using range query leakage." Foundational for
  the "what can an adversary recover from leakage profile" argument that
  cipher-maps' Property 2 supposedly defeats. Worth a one-line cite in
  section 2 leakage-abuse paragraph.

- **Grubbs, Lacharite, Minaud, Paterson 2019 (CCS)**, "Learning to
  reconstruct: Statistical learning theory and encrypted database attacks."
  Same family. Optional.

- **Pouliot and Wright 2016 (CCS)**, Kraken attack on secure indexes. The
  paper says "frequency-based attacks face uniform output" and "totality
  eliminates access-pattern attacks", but does not engage with
  frequency-via-co-occurrence attacks (Kraken) which exploit query
  co-occurrence patterns. Property 2 is marginal; co-occurrence is
  joint. The section 5.2 "compositional leakage" subsection acknowledges this
  but does not cite Kraken. **Recommend** add to section 5.2 or section 6.5 (compositional
  leakage subsection).

### QIF positioning, Smith / Alvim / Kopf cited adequately?

Now-cited:
- Smith 2009 foundations of QIF (twice).
- Alvim et al. 2012 generalized gain functions.
- Dodis and Smith 2005 entropic security.

Potentially missed:

- **Alvim, Chatzikokolakis, McIver, Morgan, Palamidessi, Smith 2020 (Springer book), "The Science of Quantitative Information Flow"**.
  This is the textbook now standard for any QIF-positioned paper. A
  one-cite reference in section 5.1 would establish the positioning more firmly.
  Currently reviewers may find that the paper is QIF-positioned via two
  papers from 2009 and 2012. **Recommend** add.

- **Kopf and Smith 2010**, "Vulnerability bounds and leakage resilience of
  blinded cryptography under timing attacks." Specifically establishes
  min-entropy leakage as the operationally meaningful measure when the
  adversary's goal is single-guess recovery. The cipher-maps paper uses
  Shannon entropy (entropy ratio = H(Q)/n), which is appropriate for
  averaged leakage but weaker than min-entropy for the worst-case-secret
  scenario typical in encrypted search. Pretty significant gap, at
  least one reviewer will ask why Shannon and not min-entropy. The paper
  punts to companion maxconf, but the issue is the *foundational
  measure choice*, which a reviewer should be able to evaluate without
  needing to read the companion. **Strong recommend** add a one-line
  acknowledgment in section 5.1 alongside the existing $g$-leakage parenthetical.

### Approximate / noisy primitives in the past 3 years

The "noise as confidentiality" framing has analogues in:

- **Differential privacy** in encrypted databases (e.g., Roy et al.
  Crypt-DB+DP, Bater et al. SMCQL). The paper's section 9.5 "what this
  framework is not" disclaims DP but does not engage with the
  *combination* of DP-style noise plus cryptographic primitive that has
  been studied recently. A reviewer comparing cipher-maps' eta to DP's
  epsilon may want a one-line distinction. The Round 4 backlog already
  flags this as nm17.

- **Approximate cryptographic accumulators** (Camacho and Hevia 2010 line),
  not sure this is a fair comparison; the paper doesn't claim
  accumulation. Optional.

- **Honey objects** (juels2014honey), already cited.

### Recent perfect hash function constructions

Cited:
- Belazzougui, Botelho, Dietzfelbinger 2009 (CHD).
- Esposito, Mueller, Vigna 2020 RecSplit (now cited via the phobic library).
- Fredman, Komlos, Szemeredi 1984 (FKS).

Worth knowing about (not necessarily citing):
- **Pibiri 2022 (ALENEX) PTHash**, successor to RecSplit, more
  space-efficient. Optional cite.
- **ConSplit 2023** (if extant). Skip.

The PHF citations are sufficient for the paper's empirical claim. The
704 documents/sec claim references "phobic" which is the author's own
RecSplit Python implementation (https://pypi.org/project/phobic/). The
footnote at line 1804 makes this clear.

## Direct competitors search

### "Every input is a valid encoding"

Closest published prior:
- Honey encryption (juels2014honey, cited).
- Format-preserving encryption (FPE; Bellare, Ristenpart, Rogaway, Stegers 2009).
  FPE produces ciphertexts in the same format as plaintexts (e.g., CC#
  to CC#-shaped ciphertext); every input is a valid output. The paper
  does not cite FPE. The conceptual overlap is real (both achieve
  "totality" on the encoded space) but the threat models diverge:
  FPE is exact and deterministic per key, no error parameter, no
  representation multiplicity. **Consider** a one-sentence cite in
  related work.

### "Shannon-optimal acceptance partition"

I am not aware of any prior published work matching $\alpha(y) \propto
p_y$ for *frequency hiding under acceptance predicates*. The
information-theoretic equivalence to Huffman/arithmetic coding is
classical; the application to encrypted lookup as both space-optimal
*and* frequency-hiding appears genuinely original. Bloom filter
literature optimizes false-positive rates but does not connect this
to frequency hiding. The paper's claim of unification is novel.

### $-\log_2 \varepsilon + H(Y)$ as a unified bound

The $-\log_2 \varepsilon$ term is classical Bloom-filter lower bound
(Carter and Wegman 1979 universal hashing line, formalized in the Bloom
filter optimality literature). The $+ H(Y)$ extension to a value-bearing
codomain is straightforward but I don't recall it stated as a single
sentence in the literature. The decomposition argument in Theorem 6.1
(Step 1 plus Step 2 with the chain rule) is standard and the result is
correct as stated, but the framing "this is novel as a unified bound"
should be soft-pedaled. The proper credit chain is:

- Bloom 1970, Carter and Wegman 1979 for $-\log_2 \varepsilon$.
- Shannon 1948 for $H(Y)$ (cited).
- The combination via independence: minor extension, not a major
  claim.

The paper's Theorem 6.1 attribution is fine because the decomposition
proof is given inline. But Section 4 ("achieving $-\log_2 \varepsilon
+ H(Y)$ bits per element") in the abstract should not read as a novel
information-theoretic discovery; the contribution is the unification
with frequency hiding via Shannon-optimal acceptance allocation. The
abstract phrasing is currently OK but borderline.

### 20 Newsgroups encrypted search baselines

20 Newsgroups is a standard NLP benchmark; encrypted-search benchmarks
on 20 Newsgroups are uncommon (most encrypted-search papers benchmark
on Enron Email or TREC). I cannot find a published Bloom-filter-based
encrypted-search benchmark on 20 Newsgroups that the paper could
directly compare against. The paper acknowledges this in
section 10.5 ("Bloom-filter baseline at matched FPR ... is work in progress"),
which is honest but exposes the experimental section to "no baseline
comparison" criticism. PoPETs reviewers typically expect at least one
strawman comparison.

## PoPETs survivability assessment

**With current state (Round 6)**:

Strengths for PoPETs:
- QIF positioning is venue-appropriate.
- Information-theoretic lower bound plus matching achievability is the
  kind of result PoPETs likes.
- Reproducibility footprint exists (open-source library, examples).
- Honest about limitations (compositional leakage, noise injection costs,
  marginal-only uniformity).

Risks for PoPETs:
- Three load-bearing sister papers (maxconf, rekeying, bernoulli-types)
  are unpublished. PoPETs has accepted papers depending on
  in-preparation companions before, but reviewers prefer arXiv or DOI
  links. **Strong recommend** post all three on arXiv with DOIs before
  submission. The bernoulli-types citation is to a github repo with no
  paper attached; this is the weakest link.
- Single-run experimental section with no replicate variance and no
  baseline comparison. PoPETs reviewers may ask for at least Bloom
  filter at matched FPR. The section 10.5 "work in progress" framing is honest
  but may not satisfy reviewers expecting a fuller evaluation.
- Author identification is not anonymized (FMT-5). The author/email line
  and the library URL must be removed/anonymized before submission.
- Paper class is article, not the PoPETs LaTeX class (FMT-1). Low effort
  but must be done.
- Page count 28 vs PoPETs typical 18-20 main body. Trimming required.

Bottom line: with arXiv-preprint posting of sister papers plus a Bloom
filter strawman plus anonymization plus template port plus page trim, the paper
is plausibly PoPETs-submittable. Without these, it's a high-risk
submission. The technical content is solid; the production gaps are
addressable.
