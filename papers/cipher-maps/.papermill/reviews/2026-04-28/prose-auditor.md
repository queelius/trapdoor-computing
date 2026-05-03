# Prose Auditor Report, cipher-maps Round 4

**Date**: 2026-04-28
**Specialist**: Prose Auditor
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations" (1536 lines)
**Focus**: Writing quality, narrative arc, notation consistency, clarity

## Summary

The prose is generally clean, careful, and intellectually honest. The Round 3 M3 (citations reorganization) reads well: the new Leakage-abuse attacks paragraph and Honey encryption paragraph are crisp and well-calibrated. Three structural prose issues remain (one new, two carried over from Round 3 minors). The abstract has a framing weakness (cross-flagged with novelty-assessor N1). The Discussion section continues to be overloaded.

**Findings**: 0 critical, 1 major, 7 minor.

---

## Verification of Round-3 fixes

### M3 Related Work reorganization, VERIFIED FIXED with prose quality

The new SSE paragraph (lines 157-167), Leakage-abuse attacks paragraph (lines 169-192), and Honey encryption paragraph (lines 194-209) read smoothly. Each paragraph has a clear topic sentence, builds the comparison, and ends with a concrete claim about what cipher maps do (or do not) accomplish relative to the cited work. This is a meaningful prose improvement on the prior single-paragraph treatment.

The Honey encryption paragraph in particular is well-structured: it identifies the shared structural property ("every input produces output"), distinguishes the targets (encryption of one message vs. function evaluation), and ends with a sharp distinguishing observation about how the noise-decode probability $\varepsilon$ "converts every cipher output ... into a value that is either the latent answer or a uniformly drawn alternative." This is good honest writing.

---

## Major Finding

### P1. The Discussion section (§9) remains overloaded with seven subsections (MAJOR, m2 from Round 3 not addressed)

**Location**: §9, lines 1321 to 1524

**Subsections in §9**: 9.1 Relationship to Bernoulli Model; 9.2 Algebraic Structure; 9.3 Online Construction; 9.4 Application: Encrypted Search; 9.5 Open Questions; 9.6 What This Framework Is Not. (Note: lines 1471 "Open Questions" is the 5th subsection, lines 1510 "What This Framework Is Not" is the 6th.)

**Problem**: Six subsections in a Discussion section is too many for a 22pp paper. Each subsection covers material that is either (a) standalone enough to be a separate section, or (b) detail that should be folded into earlier sections. As it stands, the Discussion reads like a "leftover ideas" section rather than a synthesis.

The most consequential structural problem: §9.4 "Application: Encrypted Search" is the only place the experimental numbers appear. A reviewer reading the paper top-to-bottom does not encounter experimental evidence until the Discussion. Combined with the Round 3 M2 (no experimental evaluation) finding, this misordering compounds the problem.

§9.5 "Open Questions" mixes truly open theoretical questions (max-divergence vs. TV; sum-type confidentiality) with practical engineering items (closed-form NOT bound). This makes the Open Questions feel less like a research agenda and more like a TODO list.

§9.6 "What This Framework Is Not" is a defensive disclaimer. Cross-flagged with novelty-assessor N2 (the disclaimer leaves no positive label).

**Suggestion**: Restructure §9 with three goals:
1. Promote the experimental content (currently in §9.4) to a top-level §10 "Implementation and Validation."
2. Move §9.6 "What This Framework Is Not" to the Introduction (it sets expectations and is currently at the end where it cannot do that work).
3. Combine §9.1, §9.2, §9.3 into a single "Connections to Related Frameworks" subsection of one to two pages, citing the Bernoulli paper for full development.
4. Keep §9.5 "Open Questions" as a closing subsection, but trim from six items to three or four big-picture questions.

This restructuring also gives the experiments room to breathe, addressing the Round 3 M2 partially without new experiments.

---

## Minor Findings

### P2. Abstract framing: "Shannon-optimal" sentence underclaims the duality (MINOR, cross-flagged with novelty-assessor N1)

**Location**: Abstract, lines 53-58

**Quoted text**:
> "Shannon-optimal allocation of this partition simultaneously minimizes space ... maximizes output indistinguishability ... and enables predictable error composition"

**Problem**: The abstract reads as "X, Y, Z all happen at once." The paper's actual claim is "X = Y in this setting." The framing matters for readers who scan only the abstract.

**Suggestion**: See novelty-assessor N1 for the rewrite proposal. From a prose perspective: replace "simultaneously minimizes ... maximizes ... and enables" with two distinct sentences. One says space minimization and frequency hiding are the same optimization. The other says composition is a separate but predictable property.

### P3. ROM paragraph enumerates three assumptions but says "the four properties" depend on ROM (MINOR)

**Location**: §3.1 ROM paragraph, lines 245-262

**Quoted text** (line 249-250):
> "All four properties and every theorem in this paper depend on the random oracle model. ... The critical ROM assumptions are: (a) ... (b) ... (c) ..."

**Problem**: The lead sentence references four properties, then the paragraph enumerates three lettered assumptions (a, b, c). A reader looks for a fourth and finds none. The fourth property (representation uniformity) is implicitly covered by (a) (uniform hash output) and (c) (independence across maps), but a careful reader will notice the count mismatch.

**Suggestion**: Either:
- (a) Add a fourth assumption: "(d) hash-seed independence (Property 2, representation uniformity, requires that the encoding $\enc(x, k)$ for different $k$ values appears uniform under the random oracle)"
- or (b) Reword the lead sentence: "All theorems in this paper depend on the random oracle model. The critical ROM assumptions decompose into three categories: ..."

### P4. Notation inconsistency: $K(x)$ for multiplicity conflicts with Kolmogorov complexity (MINOR, m3 from Round 3 not addressed)

**Location**: Definition 3.1 (line 273-274)

**Problem**: Round 3 minor m3 noted that $K(x)$ is the standard notation for Kolmogorov complexity. In a paper that talks about information theory ($H(Y)$, Shannon entropy), reusing $K(x)$ for "number of representations" is confusing.

**Suggestion**: Replace $K(x)$ with $\kappa(x)$ or $r(x)$ throughout. Or use $\mathrm{mult}(x)$ for clarity.

### P5. Zero figures in 22 pages (MINOR, m4 from Round 3 not addressed)

**Location**: Throughout

**Problem**: The TikZ source files exist in `paper/img/` (fig_shmap.tex, fig_shs.tex) but are not included. The paper would benefit from at least one figure showing the acceptance predicate partition of hash space, which would make the Shannon-frequency duality visually intuitive.

**Suggestion**: Include the existing TikZ figures and reference them in §3 (singular hash map figure) and §6 (acceptance predicate visualization). For the central duality argument in §6.2, a figure showing acceptance regions sized by $p_y$ with random hash values landing in proportion to $\alpha(y)$ would carry significant conceptual weight.

### P6. "4th-order Bernoulli Boolean" used without sufficient explanation (MINOR, m5 from Round 3 not addressed)

**Location**: §7.1, line 1085

**Quoted text**:
> "The output is a *4th-order Bernoulli Boolean*: four distinct correctness probabilities despite the Boolean type having only two values."

**Problem**: This is the only place in the paper where "4th-order Bernoulli Boolean" appears. A reader who hasn't read the bernoulli-types companion paper will not know what "order" means here. The sentence does explain "four distinct correctness probabilities," but the term "4th-order" is left undefined.

**Suggestion**: Either drop the term and just say "four-case correctness profile" (as suggested in the prior review), or add a parenthetical: "(here 'order' refers to the number of input-dependent error rates, not the Bernoulli distribution's parameter)."

### P7. Section 5 (Trust Model) does not state honest-but-curious explicitly (MINOR, m7 from Round 3 not addressed)

**Location**: §5, Definition 5.2 (line 524)

**Problem**: The adversary $U$ is implicitly honest-but-curious. The paper never says this explicitly. A reader who comes from the cryptography literature will notice the absence and assume the worst (malicious adversary), then find the four properties insufficient for that case.

**Suggestion**: Add one sentence as suggested by methodology-auditor M-A3.

### P8. The paper title says "Total Functions as Trapdoor Approximations"; abstract uses "trapdoor" only once (MINOR)

**Location**: Title vs. abstract

**Problem**: The title's framing leans on "trapdoor approximation," but the abstract describes the contribution in terms of "acceptance predicate" and "Shannon-optimal allocation." The trapdoor framing (one-way hash, encoding/decoding asymmetry) is the conceptual frame; the acceptance predicate is the technical contribution. A reader who picks up the title expects the abstract to develop "trapdoor" as the central construct.

This is a minor narrative-arc consideration. It is fine for the title to be evocative and the abstract to be technical, but consider whether the abstract would benefit from one sentence locating the construction in the trapdoor framing: "A cipher map is a static lookup structure whose evaluation requires no secret, but whose encoding and decoding require a one-way trapdoor; the asymmetry is what enables outsourcing computation to an untrusted evaluator."

**Suggestion**: Optional. Add a sentence after "We show that a cipher map ... provides a distinct, quantifiable privacy model" that briefly names the trapdoor mechanism. Helps readers who scan the abstract and would prefer the title's terminology.

---

## Items Verified Strong

- The Introduction's "What this is not" paragraph (lines 104-114) is a model of how to frame a contribution by contrast. This paragraph is doing the work that §9.6 should be doing.
- The honest limitations sections (Remark 4.1; §8 "Honest limitations" list at line 1310; §9.6 "What This Framework Is Not") are an unusual strength for a theory paper.
- The proof prose is consistently clear: each proof has clear case structure, named steps, and identifies which assumption is in use.
- The abstract's "Privacy in encrypted computation need not come from access-pattern hiding (ORAM), exact algebraic homomorphism (FHE), or simulation-based security (garbled circuits)" is a strong opening.

## Notes for the orchestrator

The prose quality is consistently high. The major issue (P1, Discussion overload) is structural rather than sentence-level. P2 through P8 are mostly carryovers from Round 3 minors that were not addressed in this round; addressing them collectively would take perhaps a half-day of editing.

The Round 3 minors that *were* addressed (M3, M4, M5, M6) all show prose-level care: the new paragraphs are cleaner than the originals, not just longer.
