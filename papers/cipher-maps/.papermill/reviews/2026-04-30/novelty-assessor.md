# Novelty Assessor Report (Round 5, 2026-04-30)

**Specialist**: novelty-assessor
**Manuscript**: cipher_maps.tex (1841 lines, 26 pages)

## Summary

Round 5 reframed the security argument around the entropy ratio in the
QIF tradition: §1 introduces the parameterized-leakage positioning, §5.1
adopts the entropy ratio as the confidentiality measure, Proposition
5.1 connects $\delta$ to $e$ via Fannes-Audenaert, and §5.2 enumerates
operational consequences. The technical content of the security
argument is mostly **outsourced** to a sister manuscript
(`towell2026maxconf`) that is not yet published.

This raises the central novelty question for R5: **does cipher-maps
make a defensible novelty claim once the security framework is hosted
elsewhere?** The answer is yes for the framework as a whole, but the
R5 changes have shifted what the novelty actually is, and the
manuscript has not adapted its claim structure to match.

**Findings**: 0 critical, 3 major, 4 minor.

## Critical findings

None.

## Major findings

### NOV-1 (Major): The novelty claim has fragmented across three unpublished manuscripts

**Location**: Abstract (lines 55-81), §1 (lines 122-142), §5.1 (lines 622-640)
**Quoted text** (abstract):
> "Cipher maps fit the quantitative information flow tradition, ... with the entropy ratio serving as the security measure (formal framework in companion work~[towell2026maxconf])."

**Quoted text** (§5.1):
> "Formal definition and detailed development appear in companion work~[\S 4]{towell2026maxconf}; we record only the bridge to the cipher map parameters here."

**Problem**: Three of the four "novel" load-bearing components of R5
are now described as "developed in companion work":

1. **The entropy ratio framework** -> deferred to towell2026maxconf
2. **The chain bound for bounded composition** -> deferred to towell2026rekeying
3. **The full algebraic cipher type system** (cipher Boolean type, AND/OR/NOT as cipher maps) -> deferred to towell2026algebraic

What remains uniquely in this paper is:
- Definition 3.1 (cipher map tuple)
- The four properties (totality, $\delta$-uniformity, $\eta$-correctness, composability)
- Theorem 6.1 (lower bound)
- Theorem 6.2 (space-optimal batch construction)
- Algorithm 6.3 (the seed-search algorithm)
- Theorem 7.1 (composition correctness)

This is a credible novel contribution by itself. The acceptance-predicate
unification (Shannon-optimal allocation $=$ frequency hiding) is a
genuinely new framing. But the **way the paper sells itself** in the
abstract and §1 emphasizes the QIF positioning and the entropy ratio as
the headline, then defers them.

A PoPETs reviewer who reads the abstract and §1 expects a security
argument to follow. The Operational Consequences enumeration in §5.2 is
a partial substitute, but Proposition 5.1's proof sketch is two lines
deferring to towell2026maxconf. This is the load-bearing claim of the
M1 collapse strategy, and it does not stand on its own.

**Suggestion**: Either:
- **Option A** (commit to outsourcing): Add an explicit "Scope" paragraph
  in §1 making clear that the security framework is established
  elsewhere and that this paper presents the framework + space
  optimality + composition. Recast the headline novelty as
  "acceptance-predicate framework + space-optimality + composition,
  with security developed in companion work."
- **Option B** (commit to in-paper proof): Inline the Proposition 5.1
  proof and the bridge to maxconf's Theorem 4.1 (with the corrected
  number per CITE-2), so a self-contained argument exists in
  cipher-maps. This is ~1 page of additional text.

Currently the paper sits between the two options: the abstract and §1
sell the QIF positioning, but the in-paper content does not deliver it.
Reviewers will notice.

### NOV-2 (Major): The "frequency-hiding via Shannon-optimal allocation" claim is novel but
underpositioned against Kerschbaum 2015

**Location**: §6.2 lines 915-935 (the "Shannon-optimal allocation and frequency hiding" paragraph)
**Quoted text**:
> "These are not two independent optimizations that happen to coincide. Shannon-optimal coding IS frequency hiding: matching the acceptance distribution to the output distribution simultaneously minimizes space and maximizes indistinguishability."

**Problem**: This is a real and arguably the cleanest novel contribution of the
R5 paper: the unification of Shannon-optimal coding and frequency hiding
in one optimization. But the related work (§2) does not contrast this
mechanism with Kerschbaum 2015's frequency-hiding OPE, which is the
closest published predecessor for "frequency-hiding mechanism in
encrypted data."

The bib has `kerschbaum2015frequency` (citation-verifier CITE-4 confirms
it's in the bib but uncited). A QIF/SSE reviewer will immediately ask:
"how is your mechanism different from Kerschbaum's?" The answer is good
(Kerschbaum injects random ranks on duplicates; cipher maps shape the
acceptance partition), but the paper does not make the contrast.

This is a novelty-positioning failure: a real novel contribution loses
half its impact because the comparison is not drawn.

**Suggestion**: Add to §2 a paragraph "Frequency-hiding constructions"
along the lines suggested by the citation-verifier (CITE-4):
"Kerschbaum's frequency-hiding OPE injects random ranks on duplicate
inserts to defeat frequency analysis on order-preserving ciphertexts;
cipher maps achieve the same goal structurally by shaping the acceptance
partition $A(y)$ so $\alpha(y) \propto p_y$, which simultaneously
minimizes per-element space and equalizes the cipher value frequency
profile (Theorem 6.2). The two mechanisms are complementary: Kerschbaum
preserves order, cipher maps trade order for frequency-hiding by
construction."

### NOV-3 (Major): The "totality eliminates access-pattern attacks" claim is novel but
unbenchmarked against volume-hiding STE

**Location**: §2 lines 198-222 (Leakage-abuse attacks paragraph)
**Quoted text**:
> "Totality and Shannon-optimal acceptance allocation together flatten the visible frequency profile (Property~2, $\delta$-bounded), so frequency-based attacks face uniform output; totality eliminates the 'in-domain vs.\ out-of-domain' distinction exploited by access-pattern attacks."

**Problem**: This claim positions cipher maps as a structural defense
against the Cash et al. 2015 leakage-abuse line and the Islam et al.
2012 access-pattern attacks. Good positioning. But the closest published
defender of these attacks is the volume-hiding SE line
(Patel-Persiano-Yeo-Yung 2019, Kamara-Moataz 2019), which uses
simulation-based machinery to achieve the same operational guarantee
(no in-domain vs out-of-domain signal).

`kamara2019computationally` is in the bib but uncited (CITE-5). The
paper currently lists "the comparison baselines" as ORAM, FHE, garbled
circuits, and SSE in §1. Volume-hiding STE is the natural fourth
comparator and it's missing.

A SSE-expert reviewer (likely on a PoPETs PC) will frame this as: "you
claim a structural defense against access-pattern attacks; the
volume-hiding line achieves this with proven security definitions; how
do you compare?"

**Suggestion**: Add a sentence to §2 "Searchable symmetric encryption"
paragraph or a new paragraph "Volume-hiding STE":
"The volume-hiding line~[kamara2019computationally] is closer to cipher
maps' approach: rather than analyzing leakage, it engineers
indistinguishability between document-set sizes via simulation-based
constructions. Cipher maps achieve a related guarantee structurally
(totality $+$ Property 2) at lower per-query cost, but with a
parameterized rather than negligible leakage profile."

This is a one-paragraph fix that converts a novelty risk into a
positioning advantage.

## Minor findings

### NOV-4 (Minor): The deniability proposition is presented as novel but is textbook
randomized response

**Location**: §9.4 lines 1709-1727 (Proposition 9.4)
**Problem**: The Bayesian deniability proposition is a direct
restatement of the randomized-response posterior (Warner 1965) and
appears in the differential privacy / encrypted-search literature in
many forms. The framing here as a Proposition is mathematically
correct but suggests novelty where none exists.

**Suggestion**: Either:
- Demote to a Remark with citation: "Remark (Bayesian deniability,
  randomized-response analogy)..."
- Cite Warner 1965 as the historical anchor (suggested by
  citation-verifier CITE-S2).

Either preserves the content while honestly representing the
historical position.

### NOV-5 (Minor): The Shannon-vs-min-entropy distinction is unaddressed

**Location**: §1 line 122-132 ("QIF tradition" positioning)
**Problem**: Smith 2009 (cited as foundational QIF) primarily
develops **min-entropy leakage** (one-try guessing advantage) as the
canonical operational measure. Cipher-maps adopts the **Shannon
entropy ratio**. This is a real fault line in the QIF community
between Smith-style (min-entropy) and Shannon-style measures.

The sister paper (maxconf, §4 lines 487-490 explicitly note the
Pinsker-vs-Fannes distinction) acknowledges this fault line.
Cipher-maps does not.

A QIF-expert reviewer will spot the absence and likely argue that
the cipher map regime should also justify Shannon over min-entropy.

**Suggestion**: Add a sentence in §5.1 (after the entropy-ratio
introduction): "The Shannon entropy ratio measures the adversary's
average residual uncertainty; the min-entropy ratio (one-try
guessing advantage, used in much of the QIF literature) is a
worst-case complement. Both bounds are obtainable from $\delta$ via
Fannes-Audenaert; the maxconf companion paper analyzes both."

Even acknowledging the distinction strengthens the QIF positioning.

### NOV-6 (Minor): "The construction reduces to a single design choice" is the M1
collapse pitch but is not delivered with a comparison

**Location**: Abstract lines 70-80, §6.2 lines 806-913
**Quoted text**: "The construction reduces to a single design choice:
an emph{acceptance predicate}..."

**Problem**: The acceptance-predicate unification is genuinely the
novel contribution. But the paper does not show what the unification
**replaces** in prior work. Compare to bernoulli-hash-function (BHF),
which has its own optimal allocation; or to MPHF + value table, which
can be parameterized similarly. The novel claim is that the cipher
map abstraction gives a single predicate that simultaneously achieves
multiple objectives, but this is not contrasted to alternative
abstractions.

**Suggestion**: Add a "What does this replace?" paragraph at the end
of §6.2 (Acceptance Predicates):
"Prior approaches treat space-optimality (Bloom filters, MPHF) and
frequency-hiding (Kerschbaum OPE, Kamara-Moataz volume-hiding SE) as
separate concerns requiring different mechanisms. The acceptance
predicate framework collapses both into one design choice: the
allocation $\alpha(y)$. Shannon-optimal allocation
$\alpha(y) \propto p_y$ achieves both simultaneously, eliminating the
trade-off."

### NOV-7 (Minor): The "bounded composition is a feature, not a limitation" framing is
strong but uncited against the secure-computation theory tradition

**Location**: §9.5 lines 1729-1774 ("Bounded Composition as a Security Feature")
**Problem**: The argument that bounded composition trades expressivity
for confidentiality (analogous to capability machines, total
functional languages, structurally recursive type theories) is well
written but lacks specific citations. A reviewer in the
secure-computation theory community will recognize the argument from
prior work on bounded sub-Turing models; citing one or two would
strengthen it.

**Suggestion**: Add two citations: e.g., Hofmann's work on linear
type systems for bounded resource use, or the Coq/Agda total
functional programming tradition. Even one citation legitimizes the
framing.

## Suggestions

- **NOV-S1**: The companion-paper outsourcing model is fragile.
  Consider committing to a "release plan" with explicit timestamps:
  arXiv preprint of maxconf and rekeying within X weeks of cipher-maps
  submission. Without this, the citation chain breaks under reviewer
  scrutiny.

- **NOV-S2**: The "What This Framework Is Not" section (§9.7) is
  defensive: it says cipher maps are not ORAM, not differential
  privacy, not simulation-based security. After R5's positive QIF
  positioning, this section could be reframed as "Where this framework
  sits" with positive comparisons rather than negations. The R4 review
  flagged this (MAJ-4); R5 addressed it via §1 positioning but left §9.7
  unchanged.

## Comparison against QIF primitives (Smith, Alvim)

The R5 prompt asked specifically about how cipher maps compare to
existing QIF primitives. Summary:

- **Smith 2009 g-leakage**: Operational measure (one-try guessing).
  Cipher maps use Shannon entropy ratio. Different but compatible
  measures of the same channel; cipher maps would benefit from being
  explicit about which measure and why.

- **Alvim 2012 generalized gain functions**: Allows arbitrary
  loss functions. Cipher maps' Operational Consequences enumeration
  (§5.2) implicitly assumes uniform loss. Could be strengthened by
  noting that the framework is gain-function-agnostic (as is the
  Fannes bound).

- **Dodis-Smith 2005 entropic security**: Cipher maps generalize the
  "negligible-leakage-on-high-entropy-messages" model to "bounded
  leakage at all entropy levels." This is a clean novelty claim that
  the paper makes implicitly but never explicitly.

The novelty against QIF: cipher maps are the first construction (to
my knowledge) that achieves the QIF measurable-leakage goal via a
trapdoor-based total function rather than through a randomization
procedure. This is genuinely new positioning. The paper should sell
it more directly.

## Recommendation

The R5 novelty story is real but currently fragmented. The acceptance-
predicate unification, the Shannon-frequency duality, the four-property
characterization, and the bounded-composition-as-feature framing are
genuinely novel contributions. The QIF/entropy-ratio bridge is novel
positioning but mostly outsourced to maxconf.

The principal novelty risk for PoPETs is that a reviewer reading the
abstract/§1 will expect a security argument the paper does not deliver
in-line. NOV-1 (commit to A or B) is the load-bearing fix. NOV-2 and
NOV-3 are fix-by-citation problems (Kerschbaum, Kamara-Moataz already in
the bib).

Net: the contribution is sound but the framing is unstable. Two
editorial passes (NOV-1 commitment + NOV-2, NOV-3 citations) close the
novelty gap.
