# Prose Auditor Report (Round 5, 2026-04-30)

**Specialist**: prose-auditor
**Manuscript**: cipher_maps.tex (1841 lines, 26 pages)

## Summary

The R5 restructure is substantial: §5 was reorganized around the
entropy ratio (new §5.1 Confidentiality Measure, new Proposition 5.1,
new §5.2 Operational Consequences enumeration), the abstract was
rewritten to lead with QIF positioning, §1 added a "Positioning"
paragraph in the same vein, and §9.5 ("Bounded Composition as a
Security Feature") was added. The new TikZ figure
(Figure 1, acceptance partition) is well integrated.

The principal narrative concern is **stylistic discontinuity**: the
intro and §5 are written in the new QIF-aware register, but §6 onward
retains the original tuple-form prose with the older voice. The seams
are visible.

**Findings**: 0 critical, 2 major, 6 minor, 5 suggestions.

## Critical findings

None.

## Major findings

### PROSE-1 (Major): The intro QIF positioning collides with §6-9 tuple-form prose

**Location**: §1 lines 122-142 (QIF positioning) vs §6 lines 1158-1264 (instantiations) and §9 (Discussion)
**Quoted text** (§1, new R5 voice):
> "Cipher maps belong to the *quantitative information flow* tradition... and the broader parameterized-leakage program initiated by entropic security. The defining commitment is that security is *measurable rather than negligible*..."

**Quoted text** (§6.5, original tuple-form voice):
> "$\fhat(c) = h(c \| H[\mathrm{bucket}(c)])$, total function. $\enc(x, 0) = x$ (simplest version; $K(x)=1$). $\dec(r) = y$ if $r \in C_y$ for some $y$, else $\bot$."

**Problem**: The §1 voice positions cipher maps as a security primitive
in the QIF tradition, with parameterized leakage. The §6.5 voice
mechanically describes a tuple. This is fine in principle, but the
transition between the two voices is abrupt and the §6+ sections
never re-engage with the QIF framing introduced in §1.

The §6.5 "Property status" enumeration ("Totality: yes. Representation
uniformity: achievable...") feels disconnected from the §5.1 entropy
ratio that was supposed to be the security measure. The reader has
to mentally re-translate "Property 2 ($\delta$-bounded)" into "the
$\delta$ that gates the entropy ratio in Proposition 5.1."

The seams are most visible at:
- §6.4 "Construction Time and Bucketing" (line 1055): no mention of
  $\delta$ or entropy ratio; reads as if §5 didn't happen.
- §7 "Composition" (line 1267): the AND gate warm-up is in the original
  voice; doesn't connect to "what does composition do to $e$?"
- §9.4 "Application: Encrypted Search" (line 1642): the four properties
  are re-stated for encrypted search but not connected to the entropy-
  ratio framing.

**Suggestion**: Add 1-2 sentence "QIF-bridge" connectives at:
- End of §6.5 (entropy cipher map): "By Proposition 5.1, the entropy
  cipher map's confidentiality is bounded below by $1 - \delta -
  h_2(\delta)/n$, where $\delta$ is the achievable representation
  uniformity from Property 2."
- Start of §7 (Composition): "The composition theorem gives an
  $\eta$-accumulation bound; the analogous question for the entropy
  ratio (how $e$ degrades under composition) is treated in companion
  work~[towell2026maxconf, towell2026rekeying]."
- End of §9.4 (Application): "The four properties yield concrete
  operational guarantees (Table 2): in the encrypted search setting,
  these specialize to bounded query-frequency leakage and bounded
  domain-identification advantage."

These are minor edits but they restore the narrative arc the §1 sets
up.

### PROSE-2 (Major): §5.2 Operational Consequences enumeration mixes registers and overstates

**Location**: §5.2 lines 685-704 (the enumerated list)
**Quoted text** (item 1):
> "*Decoding requires the trapdoor.* Recovering $\dec$ from $\fhat$
> requires inverting the cryptographic hash $h$ used in the
> construction (\S\ref{sec:batch}). Under the random oracle model
> (Preliminaries, \S\ref{sec:abstraction}), this is computationally
> infeasible."

**Quoted text** (item 2):
> "*Real and filler queries are statistically equivocal (Property~1,
> totality).* Both produce $n$-bit output through the same total
> function; the joint distribution of the trace under any $T$-chosen
> real-vs-filler partition is identical."

**Problem**: The four items use different registers:
- Item 1 is a **computational** claim (hash inversion is hard).
- Item 2 is a **statistical** claim (joint distribution identical).
- Item 3 is a **probabilistic** claim (posterior bounded by $\delta$).
- Item 4 is a **decision-theoretic** claim (advantage bounded by $1-e$).

The mix is jarring; an §5.2 enumeration that's supposed to
"restate the entropy ratio bound under specific adversary goals"
(line 681) jumps between three different formal frameworks.

Worse, item 2's "the joint distribution... is identical" is too strong
(see logic-checker LOG-1). The actual bound is $\delta$-close, not
identical. Property 1 alone gives totality (uniform output for
non-image inputs), but real queries hit the image of $\enc$ which is a
$\delta$-fraction of the cipher value space; they are not statistically
identical to filler queries. The error is in the prose framing, not
the underlying math.

Item 3's "Pinsker-style arguments" is also wrong (see LOG-2): Pinsker
goes the other direction. The correct argument is data-processing on
$\delta$-uniform marginals.

**Suggestion**: Rewrite §5.2 as a **single coherent register**: each item
should be phrased as "The entropy ratio bound (Proposition 5.1) implies
that, for adversary goal $G$, advantage is bounded by $X$." Specifically:

- **Item 1**: Currently a separate claim about computational hardness
  of hash inversion. Demote to a Remark (it's true but it's a
  prerequisite assumption, not a consequence of the entropy ratio).
- **Item 2**: Replace "joint distribution... identical" with "the
  cipher value distribution is $\delta$-close to uniform (Property 2),
  so any statistical test for real-vs-filler has advantage $\leq \delta$."
- **Item 3**: Replace "Pinsker-style arguments" with "by data-processing
  applied to Property 2."
- **Item 4**: Keep as-is; it's the cleanest item.

Result: a coherent enumeration in one register (decision-theoretic),
each item clearly a consequence of Proposition 5.1.

## Minor findings

### PROSE-3 (Minor): Abstract sentence flow has a clause-pile-up

**Location**: lines 55-81 (abstract)
**Quoted text**:
> "Cipher maps fit the quantitative information flow tradition
> [smith2009foundations,alvim2012measuring]: rather than achieving
> negligible leakage in a security parameter, they bound observable
> leakage by measurable parameters $\delta$ (representation uniformity),
> $\varepsilon$ (noise-decode probability), and $\eta$ (correctness),
> with the entropy ratio serving as the security measure (formal
> framework in companion work [towell2026maxconf])."

**Problem**: This is a 50-word sentence with three parenthetical clauses
and a citation chain. The reader's working memory is exceeded by the
end. The point ("cipher maps measure leakage rather than negligible-it")
is buried.

**Suggestion**: Break into two sentences:
> "Cipher maps fit the quantitative information flow tradition: rather
> than achieving negligible leakage in a security parameter, they bound
> observable leakage by three measurable parameters: $\delta$
> (representation uniformity), $\varepsilon$ (noise-decode probability),
> and $\eta$ (correctness). The entropy ratio
> $e = H(X|\mathrm{view})/H^*(X)$ unifies these into a single
> confidentiality measure, with formal development in companion work."

Cleaner two-step argument and the entropy ratio gets a definition
(currently the reader is expected to know what an entropy ratio is).

### PROSE-4 (Minor): "Manuscript in preparation" appears 4 times in the bib

**Location**: references.bib (4 entries: bernoulli-types, towell2026maxconf, towell2026rekeying, towell2026algebraic)

**Problem**: Citation-verifier flagged this as a citation issue (CITE-6).
For prose: each in-text citation to one of these reads "developed in
companion work [towell2026XXX]," "treated in companion work
[towell2026XXX]," "details in companion paper [towell2026XXX]."

The repetition is striking. A reader counts at least 12 in-text
references to "companion work" or equivalent across §3, §5, §6, §7, §9.
The cumulative effect is a paper that constantly defers.

**Suggestion**: Cluster the deferrals. Add an early "Roadmap of
companion work" footnote in §1 or §3 that lists the three sister
papers (maxconf, rekeying, algebraic) with one-line descriptions of
what each owns. Then in-text references can be terse: "the entropy
ratio (treated in maxconf)" rather than "the entropy ratio is
formally developed in companion work~[towell2026maxconf]."

This both reduces the repetition and gives the reader a single map of
where to look for what.

### PROSE-5 (Minor): The "Notational convention" paragraph is dense

**Location**: §3.1 lines 297-315
**Quoted text**:
> "We write $\cipherS{X}{s}$ for the cipher value space induced by
> encoding the latent type $X$ under secret $s$, that is, the image of
> $\enc(\cdot, \cdot)$ in $\B^n$. When the secret is clear from
> context, we drop the subscript and write $\cipher{X}$. The same
> notation applies to latent functions: for $f : X \to Y$, the cipher
> map of $f$ under secret $s$ is written $\cipherS{f}{s} : \cipherS{X}{s}
> \to \cipherS{Y}{s}$. Under the random oracle model and the four
> properties..."

**Problem**: This paragraph introduces a categorical-style notation
that is then used 4 times elsewhere in the paper (Definition 4.4
composability, §9.5 bounded composition, §9.5 rekeying chain,
§5.1 confidentiality measure). The notation works, but the
introduction here is paragraph-length and front-loaded with category-
theoretic detail (functor, $\mathbf{Cipher}_s$ category).

A reader who doesn't care about the categorical apparatus has to
read the entire paragraph to find the simple substitution rule
($\cipherS{X}{s} = $ image of $\enc$ in $\B^n$).

**Suggestion**: Lead with the substitution rule:
> "We write $\cipherS{X}{s}$ for the cipher value space (image of
> $\enc(\cdot, \cdot)$ in $\B^n$) and $\cipherS{f}{s}$ for the cipher
> map (a total function on $\cipherS{X}{s}$). When the secret is
> clear, we drop the subscript: $\cipher{X}, \cipher{f}$.
>
> [Optional categorical paragraph]
> Under the four properties, $\cipherS{\cdot}{s}$ behaves as a functor..."

The reader who needs only the notation gets it in one sentence.

### PROSE-6 (Minor): "Honest limitations" paragraphs appear in two places (§5.2 and §8.2)

**Location**: §5.2 line 736-741 (last row of Table 2 and surrounding text)
and §8.2 lines 1566-1574 ("Honest limitations" enumeration).

**Problem**: The paper twice signals "we are being honest about the
limits." First in Table 2 ("Detect cross-query correlations: **Not
bounded**") with its surrounding paragraph. Second in §8.2 as an
explicit "Honest limitations" enumeration.

The two are consistent in content but redundant in voice. Two
"honest disclosures" of the same limitation read as defensive.

**Suggestion**: Merge. The §5.2 mention should be a brief "see §8.2
for the formal limitation" pointer. The §8.2 enumeration should be
the canonical statement. Or vice versa: the §5.2 statement is the
canonical, and §8.2 just refers back.

### PROSE-7 (Minor): The §9.4 experimental paragraph is duplicated

**Location**: §9.4 lines 1677-1704 (two paragraphs)
**Quoted text**: Both the first paragraph (lines 1677-1692) and the
second paragraph (lines 1694-1704) describe:
- The cipher Boolean partition (5%/90%/5%)
- The 248 to 12 FP drop for 3-term AND
- "Perfect recall for AND queries"

**Problem**: The duplication is from the R4 review (the methodology-
auditor flagged this in METH-1 of the R4 report and again in METH-1
of the R5 report). It persists into R5.

The second paragraph adds the descriptive material on cipher Boolean
types (partitioning, AND/OR/NOT mechanics) that the first paragraph
glosses; but the second paragraph also re-asserts the experimental
numbers, creating the duplication.

**Suggestion**: Reorder. Lead with the descriptive paragraph
(cipher Boolean partition mechanics, what AND/OR/NOT do); follow with
the experimental paragraph (which can then be terse, focusing on
numbers). Or merge into one paragraph that flows: "we use cipher
Boolean types with partition X; on the 20 Newsgroups corpus, this
yields measurements Y."

### PROSE-8 (Minor): "We" appears with inconsistent referents

**Location**: throughout
**Examples**:
- Line 130: "we restrict attention to single-secret composition" ("we" = authors of cipher-maps paper)
- Line 274: "we expect the four-property framework to survive such a translation" ("we" = author)
- Line 666: "Three mechanisms reduce $\delta$..." (no "we")
- Line 1582: "We note this connection..." ("we" = author)
- Line 1635: "is developed in a companion paper" (passive)

**Problem**: Single-author paper, but "we" is used inconsistently with
"the author" or passive voice. PoPETs convention permits authorial
"we," but it should be consistent.

**Suggestion**: Pick one register: either consistent "we" (most common
in single-author math/CS papers) or consistent passive voice. The
mix is mildly jarring but easily fixed.

## Suggestions

- **PROSE-S1**: Consider adding a "Reading guide" early in §1: "This
  paper is structured as: framework (§3-§5), construction (§6),
  composition (§7), granularity (§8), discussion (§9). Readers
  familiar with QIF can skim §5.1; readers familiar with PHF can
  skim §6.1." This helps reviewers navigate and signals confidence.

- **PROSE-S2**: The "Property status" tables in §6.5 (lines 1215-1221)
  use **bold** for "yes"/"achievable"/"yes"/"yes". This is a hold-over
  from the original tuple-form prose. Consider replacing with a
  paragraph: "All four properties are achieved: totality structurally
  (§4.1), representation uniformity by Shannon-optimal allocation
  (§4.2), correctness by seed search (§4.3), composability by output
  totality (§4.4)." Reads less defensive.

- **PROSE-S3**: The "Open Questions" enumeration in §9.6 (lines 1776-1813)
  has 6 items of varying granularity. Items 1-4 are technical
  open questions; items 5-6 are bigger structural questions. Consider
  splitting into two subsections or numbering them by category.

- **PROSE-S4**: The phrase "trapdoor Boolean algebra" appears in §3.3,
  §6.4, and §9.3, each time with slightly different framing
  ("an alternative", "a companion paper", "the trapdoor Boolean
  algebra is developed in a companion paper"). One canonical
  introduction would help. Currently the reader builds up an
  understanding of "trapdoor Boolean algebra" piecemeal across the
  paper.

- **PROSE-S5**: The introduction's last paragraph (lines 122-142)
  is very long (one full paragraph, ~250 words). Consider splitting
  the last sentence ("This puts cipher maps in a different design
  space from oblivious RAM, fully homomorphic encryption, and
  simulation-based searchable encryption...") into a separate
  positioning paragraph. Currently it fights with the QIF
  positioning for attention.

## Stylistic notes (low priority)

- "We frame this as a feature rather than a limitation." (line 1762)
  is a strong rhetorical move. Justified, but consider the more
  measured: "We argue this is a feature, not a limitation." The
  current version reads slightly defensive.

- The Algorithm 6.3 caption ("Batch Cipher Map Construction") could
  be expanded: the algorithm has two early-stopping rules and a
  shuffle step that the caption doesn't mention. A reader skimming
  the algorithm box doesn't see what the algorithm does at a glance.

- The Table 2 entry "Test membership $x \in X$" uses "$\in X$" but
  the latent function is $f : X \to Y$, so $X$ is the domain not
  the membership set. The semantic gloss should be "Test membership
  in the indicator domain of $f$" or similar. Minor.

## Recommendation

The R5 prose is largely fine, but the QIF-positioning seams are
visible. PROSE-1 (intro/§5 vs §6+ register mismatch) is the load-
bearing issue: the paper now sells QIF positioning in the abstract/
intro but doesn't sustain that voice through the technical content.
A QIF-aware reader who reads §1 expects more of §6-9 to engage with
the entropy ratio framing.

PROSE-2 (the §5.2 enumeration) is the second concern: the four items
mix registers and contain two prose-level errors (LOG-1, LOG-2 in
the logic-checker report) that the prose framing has propagated.
Rewriting §5.2 in a single coherent register fixes both the prose
and the underlying logic issues simultaneously.

The minor findings are mostly fix-by-edit. Two editorial passes
(PROSE-1 connectives + PROSE-2 register fix) close the principal
prose gaps.
