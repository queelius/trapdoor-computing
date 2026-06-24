# Prose Auditor Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Headline finding

R7 PROSE-1 (abstract "inverts" framing embodying CRIT-1) is CLOSED:
the abstract was rewritten and no longer contains the inversion claim.
The R7 prose carry-overs (subsubsection* style, paragraph density,
abstract length) remain unaddressed.

## R7 prose issues, R8 status

### CLOSED (R7 PROSE-1 / MAJ-12): Abstract "inverts" framing
- **Status**: Verified. Abstract at lines 51 to 92 reads "Both single-
  instance and multi-instance optima favor concentrated (Huffman-style)
  partitions" with no "inversion" language. R7 fix landed cleanly.

### NOT FIXED (R7 MAJ-13): §8.3 subsubsection* style break
- **Location**: Lines 1732, 1840, 1887
- **Status**: Unchanged. §8.3 uses three `\subsubsection*{...}`
  ("The coincidence oracle", "Geometric corollary: t-dependent
  allocation", "Randomized encoding as a defense") while rest of paper
  uses numbered subsections or paragraph headings.
- **Suggestion**: Replace with paragraph headings (`\paragraph{...}`)
  or numbered subsubsections. Paragraph headings would be the
  lighter-touch fix.
- Severity MAJOR (style consistency).

### NOT FIXED (R7 MAJ-14): §10.6 paragraph-per-claim density
- **Location**: Lines 2495, 2528, 2565, 2590, 2605, 2640
- **Status**: Unchanged. §10.6 reads as one-paragraph-per-claim recap
  (Le Cam tightness, (TV, L) Pareto, Multi-instance, Randomized
  encoding, Threat model scope, Summary). The narrative arc is weak.
- **Suggestion**: Add a structure-setting sentence at the start of
  §10.6 outlining the five claim sequence. Could be a single sentence:
  "This section reports five findings from the empirical study, each
  in turn: Le Cam tightness, (TV, L) Pareto frontier, multi-instance
  coincidence-oracle accuracy, randomized-encoding defense, and
  threat-model scope."
- Severity MAJOR.

### NOT FIXED (R7 MAJ-15): Abstract (TV, L) sentence is 49 words
- **Location**: Abstract lines 72 to 77
- **Status**: Unchanged. The sentence "Acceptance predicates expose a
  Pareto frontier between expected codeword length L and TV-leakage;
  the Shannon-optimal corner (L = -log_2 epsilon + H(Y), matching the
  information-theoretic lower bound) and the TV-optimal corner are
  distinct under integer codeword constraints, with the gap reaching
  42x in TV at 17% length overhead on heavy-tailed value distributions."
  is approximately 56 words and has three semicolon-joined clauses.
- **Suggestion**: Split into three sentences. Could read: "Acceptance
  predicates expose a Pareto frontier between expected codeword length
  L and TV-leakage. The Shannon-optimal corner
  (L = -log_2 epsilon + H(Y), matching the information-theoretic lower
  bound) and the TV-optimal corner are distinct under integer codeword
  constraints. The gap reaches 42x in TV at 17% length overhead on
  heavy-tailed value distributions."
- Severity MAJOR.

## R8 new prose findings

### PROSE-N1 (NEW, MINOR): "Huffman dominates at every t" wording
- **Location**: §10.6 line 2583, Corollary 8.x (line 1860)
- **Issue**: "Huffman dominates at every t" reads as a defender-side
  recommendation, but the formal statement is about attacker accuracy
  being maximized (which is the defender's worst case). The phrase
  "Huffman defends best" or "Huffman provides the lowest attacker
  accuracy" would be more precise. The current phrasing inverts the
  technical claim (the attacker accuracy under Huffman is LOWER, so
  Huffman wins as a defense).
- **Status**: This is a remnant of the R7 CRIT-1 fix sequence;
  "dominates" was the original wording and meant to indicate Huffman
  is the recommended choice. The reader has to parse this against the
  formula 1 - (1/2) sum alpha^t.
- **Suggestion**: Reword "Huffman dominates at every t" to "Huffman is
  the recommended codec at every t" or "Huffman provides the lowest
  attacker accuracy at every t."
- Severity MINOR.

### PROSE-N2 (NEW, MINOR): "Coincidence oracle" used 20+ times
- **Location**: §8.3, §10.6 throughout
- **Issue**: The term "coincidence oracle" appears 20+ times in the
  paper. By the third use, the reader has internalized the concept;
  by the tenth use, the repetition becomes visible.
- **Suggestion**: Once introduced (§8.3), abbreviate as "the oracle"
  in subsequent paragraphs of §10.6 where context is clear.
- Severity MINOR.

### PROSE-N3 (NEW, MINOR): "$\sim$" vs "approximately" inconsistent
- **Location**: Various lines (§8.3 line 1860, §10.6 line 1869, line
  1874, line 2575)
- **Issue**: The paper uses both "$\sim$" (e.g., "~ 132x") and
  "approximately" (e.g., "approx 0.984") and "$\approx$" (e.g.,
  "$\approx 0.984$") for the same concept. Pick one and standardize.
- **Suggestion**: Standardize on "$\approx$" throughout for numerical
  approximations.
- Severity MINOR.

### PROSE-N4 (NEW, MINOR): §10.6 "sampling noise" phrasing is informal
- **Location**: §10.6 lines 2501, 2571
- **Issue**: "Within sampling noise" appears multiple times. PoPETs
  reviewers expect more specific language: "within the Wilson 95% CI
  half-width" or "to within 0.014 (95% CI half-width at n = 5000)."
- **Suggestion**: Replace "sampling noise" with explicit CI references.
- Severity MINOR.

### PROSE-N5 (NEW, MINOR): "Honest limitations" headings get repetitive
- **Location**: Lines 1703 ("Honest limitations" §8.2), 2020 ("Honest
  limitations" §8.3 randomized encoding)
- **Issue**: Two "Honest limitations" paragraph headings appear within
  10 pages. The word "honest" is a stylistic flag rather than a
  technical term; conventional academic prose would use "Limitations"
  or "Caveats."
- **Suggestion**: Rename to "Limitations" or "Scope and caveats" at
  both locations.
- Severity MINOR.

### PROSE-N6 (NEW, MINOR): "How to read this paper" guide would help
- **Location**: §1 lines 100 to 113
- **Issue**: The introduction's section-by-section roadmap at lines
  108 to 113 lists §3 through §9 but does not mention §10 (the
  empirical evaluation). The reader has to discover §10 from the TOC.
  Also, the framework-vs-construction distinction (lines 120 to 149)
  is critical for setting reader expectations and could be promoted
  earlier.
- **Suggestion**: Add §10 to the roadmap at line 108 to 113, and
  consider promoting the framework-vs-construction paragraph
  immediately after the abstract (or to the first paragraph of §1).
- Severity MINOR.

### PROSE-N7 (NEW, MINOR): §8.3 prose-to-theorem transition abrupt
- **Location**: §8.3 lines 1730 to 1745
- **Issue**: The opening paragraph ends "This deployment pattern arises
  whenever..." and then jumps directly to "Consider t cipher maps..."
  followed by Theorem 8.1. A bridge sentence ("We now state the
  closed-form result for the coincidence-oracle attacker.") would
  improve readability.
- Severity MINOR.

### PROSE-N8 (NEW, MINOR): Abstract opening sentence is dense
- **Location**: Abstract lines 53 to 56
- **Issue**: "Outsourcing function evaluation to an untrusted machine
  typically requires oblivious RAM (hiding access patterns), fully
  homomorphic encryption (exact computation on ciphertexts), or
  garbled circuits (encrypted lookup tables, single-use)." This is
  ~32 words with three parenthetical clauses. The reader has to track
  three competing techniques before the cipher map is introduced.
- **Suggestion**: Either reduce to two clauses ("oblivious RAM and
  fully homomorphic encryption") or move the contrasts to a second
  sentence.
- Severity MINOR.

### PROSE-N9 (NEW, MINOR): "Bernoulli paragraph" placement in §1
- **Location**: §1 lines 152 to 163
- **Issue**: The "Bernoulli error model" paragraph stands alone in §1
  without a clear connection to the framework framing that precedes
  it. The link is made later via §9.1, but a forward reference at
  §1 would help orient the reader.
- **Suggestion**: Add a forward reference: "(See §9.1 for the formal
  relationship.)"
- Severity MINOR.

### PROSE-N10 (NEW, MINOR): "Verified" vs "confirmed" in §10.6 summary
- **Location**: §10.6 Summary lines 2640 to 2663
- **Issue**: "The empirical study confirms five claims" followed by
  "(i)... realized in practice... (ii)... refines under integer-
  codeword constraints... (iii)... matching empirical accuracy to
  within sampling noise; (iv) the coincidence-oracle accuracy is
  maximized... (v) the value-side analysis applies only to..." The
  list mixes "confirmed", "verified", and bare assertions.
- **Suggestion**: Standardize on "the empirical study confirms" or
  "we observe" throughout.
- Severity MINOR.

## Summary of prose findings

- 0 critical
- 3 major carry-over from R7 (MAJ-13 subsubsection*, MAJ-14 §10.6
  density, MAJ-15 abstract sentence length)
- 10 minor new (PROSE-N1 dominates wording, PROSE-N2 coincidence
  oracle repetition, PROSE-N3 ~/approximately, PROSE-N4 sampling
  noise, PROSE-N5 Honest limitations heading, PROSE-N6 §10 roadmap,
  PROSE-N7 §8.3 transition, PROSE-N8 abstract opening, PROSE-N9
  Bernoulli paragraph, PROSE-N10 verified/confirmed)

**Prose-side recommendation**: The R7 PROSE-1 fix landed cleanly. The
remaining items are editorial polish. A 2 to 3 hour pass on §8.3
subsubsection* style (MAJ-13), §10.6 structure sentence (MAJ-14), and
abstract sentence-length (MAJ-15) addresses the majors. Minor items
can be deferred to a final editorial sweep.
