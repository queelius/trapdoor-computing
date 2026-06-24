# Novelty Assessor, Round 6 (2026-05-02)

Assessed the contribution clarity, differentiation from prior work, and
significance of cipher-maps Round 6.

## Round 5 Findings, Round 6 Status

### NOV-1 (was major, partially addressed)

**R5 issue**: Novelty fragmented across three unpublished sister papers
(maxconf, rekeying, algebraic), making it hard for a reader to assess
the core contribution of cipher-maps without reading three companions.

**R6 status**: The R6 fix narrative said the choice was "Option A
(commit to outsourcing with explicit Scope paragraph)." Let me verify.

Reading the manuscript, the QIF positioning paragraph at line 122-142
("Positioning: parameterized leakage in the QIF tradition") and the
abstract paragraph at line 64-69 both reference maxconf for the "formal
framework." Section 5.1 (line 644-666) explicitly defers to maxconf
section 4 for "formal definitions, decomposition into multiple components,
and discussion of when this measure suffices versus when other QIF
measures (min-entropy leakage, $g$-leakage) apply."

The section 9.5 ("Bounded Composition as a Security Feature") at line 1679-1724
similarly defers the chain bound to rekeying section 7. Theorem 7.1 of rekeying
is the load-bearing citation.

**Assessment**: The outsourcing is now explicit and well-signposted.
The cipher-maps paper claims:
1. The cipher map abstraction (4 properties, definitions).
2. The acceptance predicate framework (Shannon-optimal allocation).
3. The information-theoretic lower bound (Theorem 6.1).
4. The achievability theorem (Theorem 6.2).
5. The composition theorem (Theorem 7.1).
6. The encoding granularity principle (Proposition 8.1).
7. Bounded composition as security feature (qualitative section 9.5).
8. Reference implementation plus 20 Newsgroups validation (section 10).

Of these, items 1 through 6 are self-contained in cipher-maps. Item 7 explicitly
forwards to rekeying for the formal chain bound. Item 8 is empirical,
self-contained.

**The Scope paragraph that R5 recommended (NOV-1 Option A) is not
explicitly present.** The intro mentions outsourcing briefly but does
not have a dedicated "Scope" paragraph saying:
"This paper develops the cipher map abstraction and the batch
construction. The formal entropy ratio framework, the rekeying functor,
and the algebraic functorial structure are developed in companion
work [maxconf, rekeying, algebraic]."

**Recommendation**: Add a one-paragraph "Scope" subsection at the end
of section 1 (Introduction), explicitly listing what cipher-maps
contributes and what is deferred. This would close NOV-1 cleanly.
Severity: **minor** (the outsourcing is signposted but not
consolidated into one easy-to-find spot).

### NOV-2 / CITE-4 (was major, addressed)

**R5 issue**: Kerschbaum 2015 frequency-hiding OPE not cited.

**R6 verification**: Line 202-215 has a "Frequency-hiding constructions"
paragraph in section 2:

> "Kerschbaum's frequency-hiding OPE~\cite{kerschbaum2015frequency}
> hides plaintext frequency by injecting random ranks on duplicate
> inserts; cipher maps hide it by shaping the acceptance partition so
> that the cipher value distribution matches the output distribution
> (\S\ref{subsec:acceptance}, \Cref{fig:acceptance-partition}). Both
> attack the same threat (frequency analysis on encrypted records) by
> different mechanisms..."

The mechanism contrast is precise and helpful. The closing sentence
("The two constructions are complementary: Kerschbaum's mechanism
applies within each cipher map evaluation, the cipher map mechanism
applies across many evaluations") is interesting framing but slightly
overstated; Kerschbaum's mechanism actually applies *across multiple
inserts of the same plaintext*, not within a single cipher map evaluation.
**Sub-recommendation**: Reword "applies within each cipher map evaluation"
to "applies during database construction (random rank for each insert)";
keep the contrast that cipher maps apply during query evaluation.
Severity: **minor**.

Otherwise, **resolved**.

### NOV-3 / CITE-5 (was major, addressed)

**R5 issue**: Kamara and Moataz 2019 volume-hiding STE not cited.

**R6 verification**: Line 196-200 in the SSE paragraph:

> "The volume-hiding line~\cite{kamara2019computationally} is closer to
> cipher maps' approach: rather than analyzing leakage, it engineers
> indistinguishability between document-set sizes. Cipher maps achieve
> a related guarantee structurally (totality plus Property~2) at lower
> per-query cost."

The contrast is reasonable but the "lower per-query cost" claim is
unverified by the experimental section. Volume-hiding STE has known
overheads (e.g., padding to maximum response size); cipher maps
have totality (no failure mode), which is a different mechanism. The
paper claims structural equivalence but doesn't quantify the cost
comparison.

**Sub-recommendation**: Either qualify "lower per-query cost" with
"(no padding overhead, since totality is structural rather than
per-query)" or drop the cost comparison and replace with "via a
different mechanism (totality plus marginal uniformity rather than
explicit padding)." Severity: **minor**.

Otherwise, **resolved**.

### NOV-4 (was minor, unaddressed)

**R5 issue**: Warner 1965 randomized response should be cited for
deniability proposition (Proposition 9.4 / now 10.4.1).

**R6 status**: Proposition 10.4.1 (Bayesian deniability, line 1926)
does not cite Warner. The Bayes computation is identical to the
original randomized response analysis in Warner 1965 (JASA).
**Recommendation**: Add `\cite{warner1965randomized}` after "Bayesian
deniability interpretation" at line 1921 or in the proof. Severity:
**minor**.

### NOV-5 (was minor, unaddressed)

**R5 issue**: Shannon vs min-entropy QIF acknowledgment.

**R6 status**: section 5.1 line 664-666 mentions "min-entropy leakage,
$g$-leakage" in a parenthetical but doesn't say *why* the paper uses
Shannon entropy rather than min-entropy. **Recommend** add: "We use
Shannon entropy because it admits the Fannes-Audenaert bound to TV;
min-entropy leakage gives tighter worst-case adversary bounds and is
treated in [maxconf]." Severity: **minor**.

## New Findings (Round 6)

### NOV-N1 (new, minor): The "every input is a valid encoding" claim is novel as framed

The paper's central novelty claim, "totality plus frequency-equalized
output via Shannon-optimal acceptance allocation", is genuine. I am
not aware of any prior work that combines these two properties. The
closest precedents:
- Honey encryption: totality on key space, but exact (no error
  parameter), single-message.
- Format-preserving encryption: totality on plaintext format, but
  exact and not frequency-hiding.
- Bloom filters: not total (failure mode = no output for non-members).
- SSE / volume-hiding STE: not total in the same sense; padding is
  per-query, not structural.

**The cipher map combination of (a) total function with (b) tunable
correctness parameter $\eta$ and (c) Shannon-optimal frequency hiding
appears genuinely new**. The paper's positioning is honest about this.

**Sub-suggestion**: A one-sentence "to our knowledge, no prior work
combines these three properties" is appropriate in the introduction.
Currently the abstract says "We propose the *cipher map*: a total
function on bit strings whose privacy properties emerge from a one-way
trapdoor combined with a frequency-equalized output distribution." This
is fine as is, but could be sharpened to make the novelty claim
explicit. Severity: **suggestion**.

### NOV-N2 (new, major): The contribution is "framework plus theorems",
not "novel attack" or "novel construction"

PoPETs reviewers ranking by novelty often distinguish:
(a) New construction with better parameters than existing constructions.
(b) New attack on existing constructions.
(c) New formal framework that unifies/clarifies existing constructions.

Cipher-maps is type (c). This is venue-appropriate but riskier:
type (c) papers are evaluated more on the *clarity and utility* of the
framework than on quantitative improvements. The paper needs to
convince reviewers that:
- The 4-property characterization captures all the relevant cases.
- The acceptance predicate framework genuinely unifies the prior
  constructions (Bloom filter, perfect hash, etc.).
- The space-frequency duality is a genuine insight, not a restatement.

The paper does make these arguments. But a reviewer who is skeptical
of frameworks ("show me a new construction or attack") may find the
contribution insufficient.

**Recommendation**: Add a paragraph to the introduction explicitly
positioning the contribution as a unifying framework, with a list of
existing constructions that the framework subsumes (Bloom filter via
HashSet, perfect hash via batch construction, frequency-hiding by
acceptance partition shaping). Currently the introduction emphasizes
the abstraction and four properties but does not list "what becomes a
cipher map under this lens" as a contribution. Severity: **major**
(framing issue, fixable in 1-2 paragraphs).

### NOV-N3 (new, minor): The cipher-rekeying section 9.5 forwarding

Section 9.5 ("Bounded Composition as a Security Feature") is now a
qualitative motivation for *why* cipher rekeying matters, with the
formal chain bound at Theorem 7.1 of rekeying as the load-bearing
result. Without rekeying being published, this section reads as
"trust me, the formal version exists in another paper." A single
reviewer who reads only cipher-maps will see no proof.

**Sub-recommendation**: Either inline the chain bound proof (1-2
paragraphs of formal statement plus sketch) or add a footnote pointing
to the arXiv preprint of rekeying when posted. Severity: **minor**
(structural; the qualitative argument in section 9.5 is fine on its
own merits as a "framework as feature" paragraph, but the load-bearing
citation is to an unpublished paper).

### NOV-N4 (new, suggestion): The "compose AND/OR/NOT" claim deserves
quantitative validation

Section 10.3 reports OR recall 0.97 and NOT recall 0.88 ("noise
propagation through the cipher Boolean operations"). The paper at
section 7.4 ("Error Accumulation by Gate Type") motivates that AND/OR/NOT
have different error compounding profiles. But the section 10.3 numbers
(recall = 0.97 / 0.88) are not connected to any specific bound from
section 7.4. **Recommend** add a one-sentence prediction: "Under the
gate-by-gate analysis (section 7.4), OR recall is bounded by $1 - 2\eta$ and
NOT recall by $1 - \eta - p_T$; observed values 0.97 and 0.88 are
consistent with these bounds for the operational $\eta = 0.05$ and
$p_T = 0.05$." This connects the empirical to the theoretical.
Severity: **suggestion**.

## Summary of Novelty Track

- 0 critical findings.
- 1 new major (NOV-N2: type (c) framework contribution needs explicit
  framing in introduction).
- 0 carry-over major (NOV-1 substantially addressed via outsourcing
  mechanism, residual is minor; NOV-2 and NOV-3 resolved).
- 4 minor (NOV-1 Scope paragraph not consolidated, NOV-2 sub-rewording,
  NOV-3 sub-clarification, NOV-N3 forward-cite to rekeying preprint
  when posted, NOV-4 Warner cite, NOV-5 Shannon vs min-entropy).
- 2 suggestions (NOV-N1 sharpen abstract novelty claim, NOV-N4
  empirical-to-theoretical connection).

The novelty content is genuine and the R6 fixes substantially improved
the framing. The remaining gap is positioning: the paper is a framework
contribution and PoPETs reviewers may need the contribution sharpened
in the introduction so they don't expect a new attack/construction.
