# Multi-Agent Review Report, Round 6

**Date**: 2026-05-02
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Author**: Alexander Towell
**Manuscript**: `/home/spinoza/github/trapdoor-computing/papers/cipher-maps/paper/cipher_maps.tex`
**Page count**: 28
**Recommendation**: **major-revision** (with caveat: 1 critical, 4 major, otherwise close to minor-revision)

## Summary

**Overall Assessment**: The Round 6 fixes substantially improved the
paper. All 3 critical R5 findings (CITE-1 wrong theorem #, CITE-2 wrong
theorem #, METH-1 §10 promotion absent) are resolved or confirmed
non-issues. The §5.1/§5.2 refactor cleaned up the QIF positioning.
However, the §10 promotion exposed empirical numbers to closer scrutiny
that revealed an arithmetic inconsistency in the multi-term FP claim
(critical). The §5.1 entropy ratio definition and the abstract/intro
abstract definition still mismatch (major). The Definition environment
for the entropy ratio was not added (major). The Theorem 6.2 Step 2
attribution remains loose (major). Net: the paper is closer to PoPETs-
submittable than it was at R5, but is not yet at minor-revision because
of one new arithmetic inconsistency in the empirical section, plus the
LOG residuals around the central definition.

The recommendation is **major-revision**, but the gap to **minor-revision**
is small (estimated 4-8 hours of focused editorial work plus optional
sister-paper preprint posting).

**Strengths**:
1. Round 5 critical findings cleanly addressed (citation-verifier).
2. §5.1/§5.2 refactor produced a coherent QIF presentation
   (prose-auditor, logic-checker).
3. §10 structurally promoted with required subsections (methodology-auditor).
4. Kerschbaum 2015 and Kamara-Moataz 2019 added with precise mechanism
   contrasts (novelty-assessor).
5. Bibliography clean: all cites resolved, only one unused entry
   (citation-verifier).
6. §9.5 "Bounded Composition as a Security Feature" is some of the
   sharpest writing in the paper (prose-auditor).
7. Build is clean, no errors, all references resolve (format-validator).

**Weaknesses**:
1. **CRIT-1 (METH-N2)**: Multi-term AND FP arithmetic doesn't check
   out under the stated p_T^k model (12 observed FPs vs 0.625 predicted).
2. **MAJ-1 (LOG-3a)**: Entropy ratio defined two different ways
   (intro: H(X|view)/H*(X); §5.1: H(Q)/n).
3. **MAJ-2 (LOG-N1)**: Entropy ratio not in a Definition environment.
4. **MAJ-3 (LOG-N5)**: Theorem 6.2 Step 2 still conflates per-element
   acceptance probability with bit cost.
5. **MAJ-4 (METH-N1)**: Construction throughput numbers inconsistent
   across §6.4 (700) and §10.3 (843 at 5K, 713 at 18K).
6. (CITE-6) Three load-bearing sister papers still cited as
   "Manuscript in preparation"; arXiv preprints not yet posted.

**Finding Counts**: Critical: 1 | Major: 7 | Minor: ~22 | Suggestions: ~10

## Critical Issues

### CRIT-1: Multi-term AND FP claim arithmetic doesn't add up (source: methodology-auditor)

- **Location**: §10.3, line 1897-1907 ("Multi-term Boolean queries" paragraph).
- **Quoted text**:
  > "Multi-term AND queries reduce false positives sharply (from 248
  > single-term to 12 for 3-term AND) while maintaining perfect recall.
  > The reduction follows the AND composition bound: cipher Boolean AND
  > multiplies false-positive probabilities, so $k$-term AND has
  > per-document FP rate approximately $p_T^k$."
- **Problem**: With $p_T = 0.05$ and 5,000 documents (the implied corpus size
  from line 1891: "$5000 \cdot p_T = 250$ over $\approx 4{,}840$ true
  non-matches"), the 3-term AND FP count under the model is
  $5000 \cdot p_T^3 = 5000 \cdot 1.25 \times 10^{-4} = 0.625$
  expected FPs, not 12. Even with 18,266 documents,
  $18266 \cdot p_T^3 = 2.3$ FPs. Observed 12 is 5x to 20x the
  prediction. This breaks the headline empirical claim.
- **Suggestion**: Three options:
  (a) The 3 query terms are correlated within the corpus (likely cause).
  Reword to "Multi-term AND queries achieve FP rate approximately
  $p_T^k$ for independent terms; for correlated terms within the corpus
  the rate is higher (12 observed vs 0.6 predicted under independence
  for 3-term, indicating term correlations boost effective FP rate by
  about 20x)."
  (b) The cipher Boolean implementation has a noise floor that violates
  $p_T^k$. Document the floor explicitly: "cipher Boolean AND has a
  noise floor of approximately X due to (mechanism); the empirical FP
  rate plateaus at the floor."
  (c) Re-run the experiment with explicitly independent random query
  triples and report the result; if 12 holds, find the cause.
  Pick whichever matches the actual experimental setup, then update.
- **Cross-verified**: Yes, by orchestrator re-reading §10.3 and the
  state file. The arithmetic is unambiguous; the resolution depends on
  what the experimental setup actually does.

## Major Issues

### MAJ-1: Entropy ratio definition mismatch between intro and §5.1 (source: logic-checker)

- **Location**: Intro line 129-130 vs §5.1 line 649.
- **Quoted text (intro)**:
  > "an untrusted evaluator's residual uncertainty about the latent
  > function is reported as a continuous quantity (the entropy ratio
  > $e = H(X \mid \mathrm{view}) / H^*(X)$)"
- **Quoted text (§5.1)**:
  > "The entropy ratio is $e(\fhat, \tau) = H(Q)/n$ where $H(Q)$ is the
  > Shannon entropy of $Q$ and $n$ is the cipher value space dimension"
- **Problem**: These are different definitions. The intro normalizes
  the residual entropy of the latent X by the max latent entropy
  $H^*(X) = \log_2 |X|$. The §5.1 normalizes the cipher value
  distribution entropy $H(Q)$ by the cipher value space dimension $n$.
  The two are related via data-processing but they are not equal.
  A reviewer reading the intro and then §5.1 will see a definitional
  inconsistency. The §5.2 item 4 (line 737-741) compounds the issue
  by referencing both $1 - e(\fhat, \tau)$ and $H^*(X)$ in the same
  sentence.
- **Suggestion**: Pick one definition for the cipher-maps paper.
  Option A (recommended): use $e = H(Q)/n$ throughout (matching §5.1
  and matching maxconf §4.2). Update intro line 129-130 to
  "$e = H(Q)/n$ where $Q$ is the distribution of cipher values
  observed by U" and update the §5.2 item 4 to use the same
  normalization. Then the data-processing-to-latent argument is one
  forward-pointer to maxconf.
  Option B: use $e = H(X|view)/H^*(X)$ throughout, matching the intro,
  and rewrite §5.1 to define this latent-side entropy ratio with a
  data-processing argument from $H(Q)$.
  Option A is less work and matches the actual proof in Proposition 5.1.
- **Cross-verified**: Yes, by re-reading both passages. The mismatch
  is real, not an artifact of my reading.

### MAJ-2: Entropy ratio not in a Definition environment (source: logic-checker, prose-auditor)

- **Location**: §5.1 line 644-660.
- **Quoted text**:
  > "We adopt the *entropy ratio* of the companion entropy ratio
  > paper [maxconf §4]. Let Q denote the distribution of cipher values
  > that U observes (the marginal of the trace's input column). The
  > entropy ratio is $e(\fhat, \tau) = H(Q)/n$..."
- **Problem**: The entropy ratio is the central confidentiality measure
  of the paper but is not defined in a `\begin{definition}` environment.
  The user's R6 narrative described "Definition 5.1" but the manuscript
  has only inline math in flowing prose. As a result:
  (a) Proposition 5.1 cannot reference a definition number.
  (b) §5.2 items 2-4 cannot reference a definition number.
  (c) Table 5.1 (Quantitative confidentiality bounds) caption uses
  "$e$" without a definition pointer.
  (d) Reviewers asking "where is the central object formally defined?"
  see prose, not a Definition environment.
- **Suggestion**: Wrap the relevant lines in a Definition environment:
  ```latex
  \begin{definition}[Entropy ratio]
  \label{def:entropy-ratio}
  Let $Q$ denote the distribution of cipher values observed by $U$.
  The \emph{entropy ratio} of $U$'s view is $e(\fhat, \tau) = H(Q)/n$,
  where $H(Q)$ is the Shannon entropy of $Q$ and $n$ is the
  cipher-value-space bit width.
  \end{definition}
  ```
  Then update Proposition 5.1 and §5.2 items 2-4 to reference
  `Definition~\ref{def:entropy-ratio}`.
- **Cross-verified**: Yes, by checking the list of `\begin{definition}`
  environments and confirming none corresponds to the entropy ratio.

### MAJ-3: Theorem 6.2 Step 2 still loose attribution (source: logic-checker)

- **Location**: §6.5 Theorem 6.2 proof, Step 2 (line 1047-1066).
- **Quoted text**:
  > "Each correctly stored element $x_i$ must satisfy $h(\ell) \oplus
  > h(x_i) \in A(y_i)$ ... under the random oracle model this occurs
  > with probability $\alpha(y_i)$, so the information cost of pinning
  > down a single element's acceptance is $-\log_2 \alpha(y_i)$ bits."
- **Problem**: The "information cost of pinning down a single element's
  acceptance" is two different things conflated:
  (a) Time cost: $1/\alpha(y_i)$ trials per element to find a passing seed.
  (b) Storage cost: $\log_2(1/\alpha(y_i))$ bits per element to record
  which seed was chosen.
  The proof needs (b), not (a). The current text says
  "$-\log_2 \alpha$ bits" which equals (b) but is *justified* via
  (a). This is a presentation issue, not a logic error, but it is
  the same MAJ-1 from R4 / pre-R5 reviews that has been rephrased
  multiple times without being structurally fixed.
- **Suggestion**: Replace Step 2's loose phrasing with: "The seed
  table must record which of the $1/\alpha(y_i)$ candidate seeds
  achieves the acceptance constraint $h(\ell) \oplus h(x_i) \in
  A(y_i)$. Under the random oracle model with Shannon-optimal
  $\alpha(y) = \varepsilon \cdot p_y$, this storage cost is
  $-\log_2 \alpha(y_i) = -\log_2 \varepsilon - \log_2 p_y$ bits per
  element. Averaging over the value distribution gives the per-element
  cost $-\log_2 \varepsilon + H(Y)$." This separates the search work
  (which determines construction time, not storage) from the seed-table
  storage (which is the actual space cost).
- **Cross-verified**: Yes, by re-reading §6.5 proof.

### MAJ-4: Construction throughput numbers inconsistent (source: methodology-auditor)

- **Location**: §6.4 line 1190 vs §10.3 line 1883-1884.
- **Quoted text (§6.4)**:
  > "A reference implementation using a RecSplit-family PHF achieves
  > 700 documents per second on the 20 Newsgroups corpus..."
- **Quoted text (§10.3)**:
  > "At 5,000 documents, construction completes in 5.9 seconds (843
  > documents per second). The full 18,266-document index builds in
  > 25.6 seconds."
- **Problem**: 25.6 s for 18,266 docs = 713 docs/sec. The §6.4 number
  (700) is presumably the rounded full-corpus figure; the §10.3
  numbers (843 at 5K and 713 at 18K, the latter implicit) reveal a
  scaling pattern. The discrepancy is small (700 vs 713) but a
  reviewer cross-checking will notice. Worse, the §10.3 paragraph
  reports two numbers (5.9s/5K and 25.6s/18K) without explaining the
  scaling: throughput drops from 843 to 713 as corpus size grows from
  5K to 18K (-15%), but the cause (PHF construction is super-linear?
  Cache pressure?) is not stated.
- **Suggestion**: Either (a) report a single consistent throughput
  (the 18K-corpus number, 713 docs/sec, rounded to 700 in §6.4),
  with a note: "throughput drops modestly with corpus size due to
  growing PHF construction cost", or (b) report the scaling
  explicitly: "Construction throughput is 843 docs/sec at 5K
  documents and 713 docs/sec at 18K documents; the per-document
  PHF construction cost grows mildly with corpus vocabulary size."
- **Cross-verified**: Yes, by recomputing 18266/25.6.

### MAJ-5: NOV-N2, framework contribution needs explicit positioning (source: novelty-assessor)

- **Location**: §1 Introduction.
- **Problem**: The paper's contribution is a unifying framework
  (definition + 4 properties + acceptance predicate framework +
  composition theorem) that subsumes existing constructions (Bloom
  filter, perfect hash, frequency-hiding). PoPETs reviewers may
  expect "new attack" or "new construction with better parameters"
  rather than "new framework." Without explicit framing, reviewers
  may judge the contribution as insufficient.
- **Suggestion**: Add a paragraph to §1 explicitly framing the
  contribution: "This paper does not propose a new construction;
  rather, it identifies a framework (the cipher map abstraction)
  that unifies existing approximate-membership and frequency-hiding
  constructions under a single formalism with measurable parameters
  $(\eta, \varepsilon, \delta)$. Bloom filters become cipher maps
  with $K(x)=1$, prefix-free coding gives the entropy cipher map,
  Shannon-optimal partition shaping unifies space optimality with
  frequency hiding. The contribution is the framework plus its
  formal consequences (Theorems 6.1, 6.2, 7.1)." Severity: major
  (positioning matters for venue acceptance).
- **Cross-verified**: Yes, this matches the actual claims of the paper.

### MAJ-6: CITE-6, load-bearing cites to manuscript-in-prep (source: citation-verifier)

- **Location**: bib entries for towell2026maxconf (Proposition 5.1
  proof sketch), towell2026rekeying (§9.5 chain bound), bernoulli-types
  (§9.1, §9.3 Bernoulli model and trapdoor Boolean algebra forwards),
  towell2026algebraic (currently UNUSED).
- **Problem**: Three of the four sister-paper citations are load-bearing
  for non-trivial claims in cipher-maps. Until arXiv preprints are
  posted with permanent DOIs, a reviewer cannot fetch the cited
  material. The user's R6 narrative says preprints will be posted
  "imminently"; the bib still says "Manuscript in preparation."
- **Suggestion**: Post arXiv preprints for towell2026maxconf and
  towell2026rekeying before submission. Update bib with arXiv IDs
  and DOIs. For bernoulli-types, either post the umbrella paper or
  split the cite into specific paper references (CITE-S3). The
  unused towell2026algebraic entry should either be cited (e.g.,
  in a "Companion work" remark) or removed (CITE-N1).
- **Cross-verified**: Yes, by reading the bib and confirming the
  cite contexts.

### MAJ-7: LOG-S1, same-secret composition vs re-randomization (source: logic-checker, carry-over)

- **Location**: §4.4 line 510 (Definition 4.4) vs §7.2 line 1352
  (Definition 7.2 Re-randomization condition).
- **Quoted text (§4.4)**:
  > "let $\cipherS{f}{s}$ ... and $\cipherS{g}{s}$ ... a cipher map
  > for $g : Y \to Z$ (both under the same secret $s$, sharing
  > encoding and decoding for type $Y$)"
- **Quoted text (§7.2)**:
  > "(i) $\fhat$ and $\ghat$ use independent seeds, and (ii) ..."
- **Problem**: Definition 4.4 specifies same-secret composition;
  Definition 7.2 condition (i) requires independent seeds. Same-secret
  composition cannot satisfy condition (i). Therefore the equality
  case of Theorem 7.1 (which requires re-randomization) never applies
  in single-secret composition (the framework §4.4 sets up). The
  text at line 528 ("agreeing exactly under the re-randomization
  condition") is misleading.
- **Suggestion**: Clarify that "same secret" in §4.4 means "same
  master secret with domain-separated subkeys"; relax §7.2 (i) to
  "$\fhat$ and $\ghat$ use independently keyed sub-derivations of the
  master secret (e.g., HMAC-SHA256 with distinct keys derived from
  s)". Under random oracle separation, this gives the independence
  needed for the equality case while preserving the §4.4 single-secret
  framing. Severity: major (carry-over from R5).
- **Cross-verified**: Yes.

## Minor Issues (selected highlights)

The full minor list is in the individual specialist reports.
Highlighted here:

### MIN-1 (LOG-1a): Le Cam normalization
§5.2 item 2 says advantage at most $\delta$; standard Le Cam gives
$\delta/2$. Either tighten the bound or note the normalization.

### MIN-2 (LOG-N6): Stirling drop
§6.1 Theorem 6.1 proof drops $n \log_2 e \approx 1.44n$ as
"leading order." Add parenthetical noting the magnitude.

### MIN-3 (LOG-N7): $\delta \leq 1/2$ condition
Proposition 5.1 inherits Fannes-Audenaert applicability $\delta \leq
1/2$ from maxconf but doesn't state it. Add condition.

### MIN-4 (LOG-N8): Theorem 6.2 Step 2 independence
Add "(by independence under the random oracle)" to the additivity claim.

### MIN-5 (METH-N3): Uniform query distribution is the strawman
Reviewers will ask about non-uniform (Zipf, empirical-log) distributions.
Acknowledge or report at least one alternative.

### MIN-6 (METH-N4): No baseline comparison
Bloom filter at matched FPR would close the "comparison anchor" gap.
A single cell would suffice.

### MIN-7 (METH-N7): Hardware spec is too thin
"Commodity x86_64 desktop" insufficient for PoPETs reproducibility
checklist. Add CPU model, RAM, OS, library versions.

### MIN-8 (NOV-1 residual): Scope paragraph not consolidated
Add a "Scope" paragraph at end of §1 explicitly listing what
cipher-maps contributes and what is deferred to companions.

### MIN-9 (NOV-4): Warner 1965 missing
Bayesian deniability proposition (Proposition 10.4.1) is a direct
restatement of Warner 1965 randomized response. Cite.

### MIN-10 (NOV-5): Shannon vs min-entropy
§5.1 should say *why* Shannon entropy and not min-entropy.

### MIN-11 (PROSE-N1): §10 narrative seams
Add 1-sentence transitions between §10.2/10.3, §10.3/10.4, §10.4/10.5.

### MIN-12 (PROSE-N3): §5.2 item 4 is the weakest item
Item 4 invokes undefined H*(X). Either expand to self-contained
statement or shorten to forward-pointer.

### MIN-13 (PROSE-N5/FMT-5): Author identification
Anonymize author block and library URL before submission.

### MIN-14 (CITE-N1): Unused towell2026algebraic entry
Either cite (e.g., "Companion work" remark) or remove from bib.

### MIN-15 (CITE-3 sub): RecSplit cite on first mention
§6.4 line 1192 mentions "RecSplit-family PHF" without `\cite{esposito2020recsplit}`.

### MIN-16 (CITE-7): DOIs missing throughout bib
Add DOI fields for all citations.

### MIN-17 (CITE-S3): bernoulli-types overloaded
The cite key is used for three different sub-topics. Split or specify.

### MIN-18 (FMT-N1): 104pt overfull at line 1875-1880
Fix the long URL line in §10.3 Setup itemize.

### MIN-19 (FMT-1, carry-over): Venue port to PoPETs class
Required before submission. Mechanical work.

### MIN-20 (R4 m3): K(x) → κ(x) rename
Backlog item, unaddressed. Either do or remove from backlog.

### MIN-21 (R4 m9): Hash notation unification
Backlog item, unaddressed.

### MIN-22 (METH-N5): "Work in progress" framing in §10.5
Either trim §10.5 to a one-paragraph forward-pointer, or do the
experiments before submission.

## Suggestions

S-1 (NOV-N1): Sharpen abstract novelty claim with one sentence.
S-2 (NOV-N4): Connect §10.3 OR/NOT recall numbers to §7.4 gate-by-gate
analysis with a one-sentence prediction.
S-3 (PROSE-N4): Promote §9.5 framing to a sentence in the introduction.
S-4 (PROSE-N6): Soften "achieving the information-theoretic lower bound"
abstract phrasing to credit Bloom-filter prior art for the
$-\log_2 \varepsilon$ term.
S-5 (PROSE-N7): Mention multiple-derivation cross-check from CLAUDE.md.
S-6 (PROSE-N8): Anchor "sub-Turing" with a one-line operational gloss.
S-7 (FMT-N2): Standardize on `\Cref` throughout.
S-8 (FMT-N4, FMT-N5): Wrap embedded tables in §6.4, §6.6.1 in
`\begin{table}` environments for caption/numbering.
S-9 (METH-N6): "Reproduces the table above": there is no LaTeX table;
either add one or reword.
S-10 (METH-N8): Lead §10.3 Construction paragraph with query latency,
not throughput.

## Detailed Notes by Domain

### Logic and Proofs

The §5.1/§5.2 refactor (R6) is substantively better than R5. CITE-1
and CITE-2 are both verified correct against the source papers
(maxconf Theorem 4.1 part 3 is the Fannes-Audenaert bound; rekeying
Theorem 7.1 is the chain bound). LOG-1, LOG-2 prose fixes (Le Cam,
data-processing) are correct citations.

Outstanding logic issues: (a) MAJ-1 entropy ratio definition mismatch
between intro and §5.1; (b) MAJ-2 missing Definition environment;
(c) MAJ-3 Theorem 6.2 Step 2 still loose; (d) MAJ-7 same-secret
composition vs re-randomization mismatch. Plus 4-5 minors.

### Novelty and Contribution

The 4-property framework + acceptance predicate framework + composition
theorem is a genuine contribution. The R6 fixes (Kerschbaum and
Kamara-Moataz cites with mechanism contrasts) closed the most pressing
NOV gaps. NOV-N2 (framing as "framework contribution" rather than
"new construction") is the remaining major issue: a 1-2 paragraph
introduction adjustment can close it. NOV-1 Scope paragraph not
consolidated is a minor.

### Methodology

R6 §10 promotion is a structural success but exposed two arithmetic
issues: CRIT-1 (3-term FP discrepancy) and MAJ-4 (throughput
inconsistency). R5 minors METH-3, METH-4, METH-5 are all addressed.
Remaining work-in-progress disclosures (Bloom baseline, replicate
variance) are honest but expose the §10.5 paragraph to "evaluation
incomplete" criticism.

### Writing and Presentation

Prose quality is publication-grade. R5 PROSE-1, PROSE-2, PROSE-7
are all resolved. R6 introduced minor seams in §10 transitions and
a few notation inconsistencies but no structural problems. The §9.5
"Bounded Composition as a Security Feature" is some of the best
prose in the paper.

### Citations and References

R5 critical CITE-1 and CITE-2 are verified correct in R6. The user
correctly identified that R5 reviewer's CITE-1 finding was a false
positive (rekeying Theorem 7.1 is the right cite). The remaining
major is CITE-6 (load-bearing cites to manuscript-in-prep papers);
this resolves once arXiv preprints are posted.

### Formatting and Production

Build is clean. 4 overfull hboxes, one significant (104pt at line
1875-1880). All references resolve. Standard `article` class needs
porting to PoPETs template (FMT-1). Author identification requires
anonymization (FMT-5). Page count 28 vs PoPETs target 18-20.

## Literature Context Summary

Cipher-maps' QIF positioning is venue-appropriate for PoPETs. PoPETs
accepts both cryptographic-security and quantitative-leakage papers.
The contribution is type (c) "framework that unifies existing
constructions" rather than (a) new construction or (b) new attack;
this is acceptable but riskier and benefits from explicit positioning
(MAJ-5 / NOV-N2).

Key prior work that could be cited but is not:
- Patel-Persiano-Yeo-Yung 2019 (CCS) volume-hiding multi-maps (strong
  recommend; cleanest comparison to cipher-maps' totality+Property 2).
- Alvim et al. 2020 textbook "Science of QIF" (recommend).
- Köpf-Smith 2010 min-entropy leakage (recommend; foundational measure
  choice question).
- Pouliot-Wright 2016 Kraken (recommend; co-occurrence attack the
  paper acknowledges in §8.2 but does not cite).
- Format-preserving encryption (Bellare-Ristenpart-Rogaway-Stegers
  2009) (consider; structural overlap with totality).

PoPETs survivability: with arXiv-preprint posting of sister papers +
Bloom filter strawman + anonymization + template port + page trim,
the paper is plausibly PoPETs-submittable. Without these, high-risk.
Technical content is solid.

## Cross-Verification Summary

For findings that warranted cross-checking against the manuscript
directly:
- CRIT-1 (FP arithmetic): orchestrator computed $5000 \cdot 0.05^3 =
  0.625$; observed 12 is 20x off. Cross-verified.
- MAJ-1 (entropy ratio mismatch): orchestrator read both intro line
  129-130 and §5.1 line 649; the two definitions are different.
  Cross-verified.
- MAJ-2 (no Definition env): orchestrator listed all 7 `\begin{definition}`
  environments; none corresponds to entropy ratio. Cross-verified.
- MAJ-3 (Theorem 6.2 Step 2): orchestrator re-read proof; the loose
  attribution remains. Cross-verified.
- MAJ-4 (throughput inconsistency): orchestrator computed 18266/25.6
  = 713; §6.4 says 700. Cross-verified.
- CITE-1, CITE-2: orchestrator read both sister papers' Theorem 7.1
  and Theorem 4.1 directly to confirm the cite chain. Cross-verified.

## What's Left for a Final Polish Pass

In priority order:

### Critical (1-2 hours):

1. **Fix CRIT-1**: resolve the 3-term AND FP arithmetic. Either
   document term correlation explicitly or recompute and report
   correctly. This is the hard one because it requires understanding
   what the experiment actually measured.

### Major (4-8 hours):

2. **Fix MAJ-1 and MAJ-2 together**: pick one entropy ratio definition
   ($H(Q)/n$ recommended), wrap in Definition environment, update intro
   to match. Update §5.2 items 2-4 to reference the Definition.

3. **Fix MAJ-3**: rewrite Theorem 6.2 Step 2 to separate seed-table
   storage cost from search-time cost.

4. **Fix MAJ-4**: report consistent throughput numbers across §6.4
   and §10.3, with explicit corpus-size-dependence note.

5. **Fix MAJ-5**: add a 1-paragraph "framework contribution" framing
   to §1.

6. **Fix MAJ-7**: clarify same-secret composition uses domain-
   separated subkeys; relax Definition 7.2 (i) to subkey independence.

### Minor backlog (2-3 days, can be parallelized):

7. R5 minor backlog (LOG-1a, LOG-N6, LOG-N7, LOG-N8, METH-N3, METH-N4,
   METH-N7).

8. NOV residuals (NOV-1 Scope paragraph, NOV-4 Warner cite, NOV-5
   Shannon vs min-entropy).

9. PROSE residuals (PROSE-N1 §10 transitions, PROSE-N3 §5.2 item 4
   shortening, PROSE-N5 anonymization).

10. CITE residuals (CITE-N1 unused entry, CITE-3 RecSplit on first
    mention, CITE-7 DOIs, CITE-S2 Warner, CITE-S3 bernoulli-types).

11. FMT residuals (FMT-N1 104pt overfull, FMT-1 venue port, FMT-5
    anonymization).

### Sister-paper preprint posting (1-2 days):

12. Post towell2026maxconf, towell2026rekeying as arXiv with DOIs.
    Update bib. Closes CITE-6 and downgrades NOV-1 to fully resolved.

### Pre-submission cleanup (1 day):

13. Venue port (PoPETs class), anonymization, page trim.

## Path to Minor-Revision Recommendation

If items 1-6 are fixed (4-8 hours of focused editorial work), the
recommendation drops from major-revision to minor-revision. The
sister-paper preprints (item 12) and venue cleanup (item 13) are
necessary for submission but do not affect the round-by-round
recommendation.

## Path to Ready Recommendation

Items 1-13 above, plus a Bloom filter strawman comparison (METH-N4)
and at least 3-replicate variance characterization (METH-2 carry-over).

## Honest PoPETs Survivability Assessment

If items 1-6 land plus sister-paper preprints get posted plus
anonymization plus template port plus page trim, the paper is a
credible PoPETs submission. The main reviewer-side risks:

1. Type (c) framework contribution may face "show me numbers, not a
   framework" pushback. MAJ-5 fix mitigates.
2. Single-run experimental section without baselines may face
   "evaluation incomplete" pushback. METH-N4 fix mitigates.
3. Three load-bearing sister papers as preprints may face "what if
   the companion work doesn't pan out" pushback. Posting preprints
   with DOIs mitigates; can't fully eliminate.

The technical content (4-property framework, acceptance predicate
framework, lower bound + matching achievability, composition theorem,
Fannes-Audenaert bridge) is solid and original. Once the production
gaps and the four major editorial items are addressed, the paper has
a credible shot at PoPETs.

Bottom line: **the paper is close to PoPETs-submittable but not there
yet**. Estimated focused work to submission-ready: 1-2 weeks if the
sister-paper preprints can be posted in parallel, 3-4 weeks if they
need substantial polish.

## Review Metadata

- Agents used (acting as orchestrator, no subagent dispatch available):
  literature-context, logic-checker, methodology-auditor,
  novelty-assessor, prose-auditor, citation-verifier, format-validator.
- Cross-verifications performed: 6 (CRIT-1, MAJ-1, MAJ-2, MAJ-3,
  MAJ-4, CITE-1+CITE-2).
- Disagreements noted: 0.
- Manuscript reads: 3 (initial, mid-specialist verification, final
  self-verification).
- Sister-paper reads: 2 (maxconf §4 for Theorem 4.1, rekeying §7
  for Theorem 7.1).
