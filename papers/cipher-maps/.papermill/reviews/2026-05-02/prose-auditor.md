# Prose Auditor, Round 6 (2026-05-02)

Read the manuscript end to end checking writing quality, narrative arc,
notation consistency, and section-to-section flow.

## Round 5 Findings, Round 6 Status

### PROSE-1 (was major, addressed)

**R5 issue**: Register seam between intro/section 6+ and the new QIF
introduction prose; abrupt transitions.

**R6 verification**: The QIF positioning paragraph (line 122-142) and
the section 5.1 confidentiality measure paragraph now share a common
register: "parameterized leakage in the QIF tradition", "entropy ratio",
"measurable rather than negligible." The previously identified seams
have been smoothed by the consistent vocabulary. **Resolved**.

### PROSE-2 (was major, addressed)

**R5 issue**: Section 5.2 mixed registers (some items security-claim
style, some QIF-style).

**R6 verification**: Section 5.2 (Operational Consequences) at line
707-741 is now a single coherent enumeration:
- Item 1 (Decoding requires the trapdoor): cryptographic register.
- Item 2 (Real and filler queries are $\delta$-equivocal): QIF
  register with Le Cam invocation.
- Item 3 (Domain identification bounded by $\delta$): QIF register
  with data-processing inequality.
- Item 4 (Function-value leakage bounded by entropy ratio): QIF
  register.

The four items now use a common QIF vocabulary. The opening sentence
("These are not separate security guarantees; they are concrete
restatements of the entropy ratio bound under specific adversary
goals") is a clean register-bridge. **Resolved**.

### PROSE-7 (was minor, partially addressed)

**R5 issue**: Section 9.4 paragraphs partially duplicated each other.

**R6 status**: The old section 9.4 ("Application: Encrypted Search")
has been removed from the Discussion. The new section 10.2 uses the
"Search agent = trusted machine T" mapping which is a direct
reformulation of the §9.4 text. The duplication is gone. **Resolved**.

## New Findings (Round 6)

### PROSE-N1 (new, minor): Section 10 has narrative seams

The §10 promotion was a major restructure. The five subsections read
as somewhat independent paragraphs:
- 10.1 Reference Implementation (the library exists, here's what it does).
- 10.2 Application: Encrypted Search (mapping table from cipher map
  framework to encrypted search vocabulary).
- 10.3 20 Newsgroups: Boolean Search Validation (concrete numbers).
- 10.4 Deniability via the Correctness Parameter (Bayesian analysis).
- 10.5 Further Empirical Investigations (work-in-progress list).

The transitions between subsections are abrupt. For example:
- After 10.2's mapping table, 10.3 jumps to "We instantiate the
  encrypted search application on..." with no transition sentence.
- After 10.3's Reproducibility paragraph, 10.4 jumps to "The correctness
  parameter $\eta$ has a precise Bayesian deniability interpretation
  for Boolean-valued cipher maps" with no connection to the empirical
  results just presented.

**Recommendation**: Add 1-sentence transitions:
- End of 10.2: "The next subsection instantiates this mapping
  on the 20 Newsgroups corpus."
- Start of 10.4: "The empirical results above establish that cipher
  maps are practical for Boolean queries; the following theoretical
  result complements the empirical findings by quantifying the
  deniability provided by the correctness parameter $\eta$."
- Start of 10.5: "Several empirical questions remain open."

Severity: **minor**.

### PROSE-N2 (new, minor): "Definition" not used for entropy ratio

(Already covered as logic finding LOG-N1.) The entropy ratio is
introduced in flowing prose with inline math, not as a numbered
Definition environment. From a prose standpoint, this is a missed
opportunity: a Definition environment makes the object easier to
reference and signals to readers "this is the central object of the
paper's confidentiality analysis." Severity: **minor** (mostly a
logic-checker concern, but also a writing-style concern).

### PROSE-N3 (new, minor): Item 4 of section 5.2 is the weakest item

Reading section 5.2 line 716-741 as a unified enumeration:
- Item 1: 5 lines, clean cryptographic claim with explicit ROM
  pointer.
- Item 2: 7 lines, clean QIF claim with explicit Le Cam pointer.
- Item 3: 8 lines, clean QIF claim with explicit DPI pointer plus
  aggregation note.
- Item 4: 5 lines, weaker claim invoking $H^*(X)$ which is undefined
  in cipher-maps.

Item 4 should either be expanded to give a self-contained statement
(define $H^*(X) = \log_2 |X|$ or $H^*(X) = $ max entropy on the latent
space) or shortened to a one-line forward-pointer:
"Function-value leakage on the latent space $X$ is bounded via the
data-processing inequality applied to Property 2; see [maxconf
Theorem 4.1] for the precise bound including the latent-vs-cipher
normalization."

The current item 4 tries to make a strong claim ("$1 - e$ advantage")
without the formal apparatus to support it. **Recommend** the
shortening option. Severity: **minor**.

### PROSE-N4 (new, minor): Section 9.5 is excellent prose, deserves to lead

Section 9.5 ("Bounded Composition as a Security Feature") at line
1679-1724 is one of the best-written passages in the paper. It frames
the rekeying constraint as a security feature (sub-Turing computation)
and makes a clean parallel to capability machines, total functional
languages, and structurally recursive type theories. The "expressivity
envelope" framing is sharp.

But it's buried at the end of section 9 (Discussion). A reader
skimming the paper will likely miss it. Two options:
(a) Promote the §9.5 framing to a paragraph in the introduction (one
sentence: "We frame the bounded composition envelope as a security
feature analogous to capability machines and total functional
languages: chain length is the explicit expressivity dial, and
$\log_2(n+1)$ is the explicit confidentiality cost."). 
(b) Move §9.5 earlier in the Discussion, before "Open Questions" and
"What This Framework Is Not."

**Recommendation**: option (a), 1-sentence intro mention, no
restructure. Severity: **minor**.

### PROSE-N5 (new, minor): "metafunctor" identification

Line 48: `\author{Alexander Towell\\\texttt{lex@metafunctor.com}}`
Line 1789: `\url{https://github.com/queelius/cipher-maps}`

These are author-identifying. PoPETs is double-blind, so:
- Author line will need to be `\author{Anonymous}` or removed
  during submission.
- The library URL will need to be replaced with a placeholder
  ("[anonymized library URL]") or removed.

These are not prose issues per se, but they are presentation
issues that need handling before submission. Severity: **minor**
(carry-over from FMT track).

### PROSE-N6 (new, minor): Abstract claim "achieving the
information-theoretic lower bound"

Abstract line 73-76: "Shannon-optimal allocation of this partition
simultaneously minimizes space (achieving $-\log_2 \varepsilon + H(Y)$
bits per element, the information-theoretic lower bound)..."

This is technically correct (under Shannon-optimal allocation, the
batch construction matches the lower bound at $\eta = 0$). But "the
information-theoretic lower bound" phrasing implies novelty in
*establishing* the bound, when most of the bound (the $-\log_2
\varepsilon$ term) is classical Bloom-filter literature. The
contribution is the *unification* with frequency hiding via the same
Shannon-optimal allocation, not the bound itself.

**Recommendation**: Reword to "achieving $-\log_2 \varepsilon + H(Y)$
bits per element (matching the information-theoretic lower bound and
extending classical Bloom-filter optimality to value-bearing
codomains)..." or similar. Severity: **suggestion** (the current
phrasing is OK but borderline overclaim).

### PROSE-N7 (new, suggestion): "Three independent derivations converge"
phrasing in CLAUDE.md not in paper

The project-level CLAUDE.md mentions "Three independent derivations
(bernoulli_entropy, bernoulli-hash-function, crypto-perf-hash) converge
on this." This kind of "multiple-derivation cross-check" is exactly
what would strengthen the paper's claim of fundamentality. Currently
the paper at Theorem 6.1 gives one proof. Adding a sentence "This
bound has been derived independently in three contexts: [bernoulli
entropy], [bernoulli hash function], [perf hash benchmarks]" would
strengthen the claim and show the paper's place in a research program.

Severity: **suggestion** (out of scope for current submission target,
but worth noting for a journal version).

### PROSE-N8 (new, suggestion): "Sub-Turing as a security feature"
neologism

Section 9.5 introduces "Sub-Turing computation as a security feature"
(also section title in cipher-rekeying section 7.3). This phrasing is
distinctive and I think correct, but it's also potentially jarring
for a security audience that doesn't think in computation-theoretic
terms.

A reviewer skeptical of the framing may push back. **Recommend** add
one parenthetical anchor: "Sub-Turing (i.e., not Turing-complete; the
expressivity envelope is bounded by the trusted machine's pre-
provisioned rekeying budget)." This anchors the term to a concrete
operational meaning. Severity: **suggestion**.

## Notation Consistency Check

I scanned for notation inconsistencies. Findings:

### N-CONSIST-1: $K(x)$ vs $\kappa(x)$

The R4 backlog included m3: rename $K(x)$ to $\kappa(x)$ to free $K$
for other uses (e.g., chain length in rekeying or partition count
in granularity). This rename did not happen. The notation $K(x)$ is
used 14 times, $K > 1$ multiple times, $K(x) = 1$, etc.

**Recommend** rename $K(x)$ to $\kappa(x)$ if the R4 m3 backlog item
is to be closed. Otherwise, leave as is and remove m3 from backlog.
Severity: **minor**.

### N-CONSIST-2: Hash notation $h(\cdot)$ vs $h(\ell) \oplus h(x)$

Section 3.1 line 286 defines $h: \B^* \to \B^n$.
Algorithm 1 line 990 uses $h(\ell) \oplus h(x)$.
Section 6.4 line 1190 uses "PHF" without explicit hash function.
Section 9.1 line 1644 references "BHF (Bernoulli Hash Function)".

The mix of bare $h$ and seeded $h(\ell) \oplus h(x)$ is OK because the
context disambiguates, but a single notation pass would help. The R4
backlog m9 (hash notation unification) is unaddressed. Severity:
**minor**.

### N-CONSIST-3: $\B^n$ vs $\{0,1\}^n$

Both notations appear:
- Section 3.1 line 38 defines `\newcommand{\B}{\{0,1\}}` so `\B^n` =
  `\{0,1\}^n`.
- Section 3.1 line 286 uses `\B^*` and `\B^n`.
- Most of the rest of the paper uses `\{0,1\}^n` in displayed math.
- Definition 4.1 (Cipher map) line 343 uses `\{0,1\}^n`.
- Definition 4.2 (Totality) line 437 uses `\{0,1\}^n` then `\B^n`.

Mixed but disambiguated by `\B = \{0,1\}` definition. Could be cleaner
by picking one. **Recommend** use `\B^n` throughout, since the macro
is defined. Severity: **suggestion**.

### N-CONSIST-4: "cipher value" vs "cipher value space"

Used interchangeably. Both clear in context. No action needed.

## Section Flow

Overall narrative arc:
- Intro (section 1): contrast with ORAM/FHE/SSE, four-property abstraction,
  QIF positioning. Strong opening.
- Related work (section 2): comprehensive coverage. Strong.
- Cipher map abstraction (section 3): clean definitions and construction
  layers. Strong.
- Four properties (section 4): clean definitions. Strong.
- Trust model (section 5): definitions plus QIF measure plus operational
  consequences. The new structure is good.
- Batch construction (section 6): lower bound, acceptance predicates,
  algorithm. Strong.
- Composition (section 7): warm-up plus general theorem plus chain
  corollary. Strong.
- Granularity (section 8): definitions, proposition, comp leakage.
  Strong.
- Discussion (section 9): Bernoulli model, algebraic structure, online
  construction, bounded composition (section 9.5), open questions, "what
  this is not." Section 9.5 is excellent (see PROSE-N4).
- Implementation (section 10): structurally promoted but has internal
  arithmetic inconsistencies (see methodology-auditor METH-N1, METH-N2).

The arc holds together. The R6 §10 promotion improved the empirical
exposition. The R6 §5 restructure (entropy ratio plus operational
consequences) clarified the QIF positioning. Overall prose quality
is publication-grade.

## Summary of Prose Track

- 0 critical.
- 0 new major (all R6 PROSE findings are minor or suggestion).
- 6 minor (PROSE-N1 §10 narrative seams, PROSE-N2 entropy ratio not a
  Definition env, PROSE-N3 §5.2 item 4 weakest, PROSE-N5 author
  identification, N-CONSIST-1 K(x) rename, N-CONSIST-2 hash notation).
- 5 suggestions (PROSE-N4 §9.5 promotion, PROSE-N6 abstract overclaim,
  PROSE-N7 multiple derivations, PROSE-N8 sub-Turing parenthetical,
  N-CONSIST-3 $\B^n$ standardization).

Net assessment: prose quality is solid. R5 PROSE-1, PROSE-2, PROSE-7
all resolved. R6 introduced minor seams in §10 and a few notation
inconsistencies but no structural prose problems.

The paper is publication-quality from a writing standpoint. The
remaining issues are editorial polish, not structural.
