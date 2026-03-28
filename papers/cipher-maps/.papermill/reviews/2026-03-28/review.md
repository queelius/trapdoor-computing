# Multi-Agent Review Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"
**Author**: Alexander Towell
**Pages**: 19 (in article class; will change in PoPETs template)
**Target Venue**: PoPETs 2027
**Review Round**: 3 (prior rounds: 2026-03-19 major-revision, 2026-03-26 minor-revision)
**Recommendation**: major-revision

## Summary

**Overall Assessment**: The paper presents a clean conceptual framework (cipher maps) with two genuinely novel insights: the acceptance predicate unification and the Shannon-frequency duality. The writing is clear, the proofs are correct under stated assumptions, and the honest limitations sections are commendably candid. However, the paper is not ready for PoPETs 2027 in its current form. Three structural gaps -- the absence of a formal security definition, the lack of any experimental evaluation, and missing engagement with the leakage-abuse attack literature -- are each independently likely to result in rejection at PoPETs. These are not minor fixes; they represent the gap between a good formalism paper and a publishable PETs paper.

**Strengths**:
1. The acceptance predicate framework (Section 6.2) is a genuine unification: showing that all batch cipher maps reduce to a choice of acceptance predicate is elegant and provides a single knob for the entire construction (novelty-assessor)
2. The Shannon-frequency duality (Section 6.2, "Shannon-optimal allocation and frequency hiding" paragraph) -- the insight that space-optimal coding IS frequency hiding -- is the paper's central contribution and is both non-obvious and well-argued (novelty-assessor, logic-checker)
3. The four-property framework provides useful conceptual vocabulary: totality, representation uniformity, correctness, composability decompose the design space cleanly and independently (novelty-assessor)
4. All proofs are correct under stated assumptions; the composition theorem proof is clean and the inclusion-exclusion argument with the re-randomization condition is well-handled (logic-checker)
5. The honest limitations sections are unusually candid: "marginal uniformity only" (Remark 4.1), the encoding granularity honest limitations list (Section 8), and "What This Framework Is Not" (Section 9.5) set clear expectations (prose-auditor)
6. The construction layers (Section 3.3) provide intuitive motivation for why each property exists, and the careful disclaimer about monad structure shows intellectual honesty (prose-auditor)
7. The bibliography is clean: all 18 entries cited, no orphans, no undefined references, clean build with zero warnings (citation-verifier, format-validator)

**Weaknesses**:
1. No formal security definition: the paper makes security claims (Definition 5.2: "$U$ cannot...") but backs them only with informal appeals to Properties 1 and 2, never defining a security game or experiment (novelty-assessor, methodology-auditor)
2. No experimental evaluation: purely theoretical, with no implementation, no benchmarks, no concrete parameter instantiations for realistic workloads (novelty-assessor)
3. Missing engagement with the leakage-abuse attack literature: the paper claims advantages over PPE and SSE but does not cite the attacks (Naveed et al. 2015, Islam et al. 2012) that motivate these comparisons (citation-verifier, literature-context)
4. Missing comparison to honey encryption (Juels & Ristenpart 2014), which shares the core "every input produces output" property (citation-verifier, literature-context)
5. Composition formula inconsistency: Theorem 4.1 uses equality, Theorem 7.1 uses inequality -- same result, different claims (logic-checker)
6. Space optimality theorem (Thm 6.2) conflates information-theoretic capacity with achievable physical storage when $\eta > 0$ (logic-checker)
7. ROM dependency is pervasive but implications for practical instantiation are not discussed (methodology-auditor)

**Finding Counts**: Critical: 0 | Major: 6 | Minor: 11 | Suggestions: 4

## Major Issues

### M1. No formal security definition (source: novelty-assessor, methodology-auditor)
- **Location**: Section 5 (Trust Model), Definition 5.2 (lines 463-485)
- **Quoted text**: "$U$ cannot: (1) Decode cipher values (does not hold $s$ or $\dec$). (2) Distinguish real encodings from filler (by Property 1). (3) Determine the domain $X$ or function $f$ (by Property 2, cipher values are $\delta$-close to uniform). (4) Enumerate which inputs are 'in-domain' (by totality, every input produces output)."
- **Problem**: These are security claims without a security definition. PoPETs papers that propose new primitives are expected to formalize what the adversary learns. The paper explicitly rejects simulation-based, game-based, and differential privacy definitions (Section 9.5), but offers no alternative formalization. The four properties parameterize leakage ($\delta$, $\varepsilon$, $\eta$) but there is no theorem saying "any adversary with access to $\hat{f}$ can learn at most X about $f$." Without this, a PoPETs reviewer cannot evaluate the security claims.
- **Suggestion**: Define an indistinguishability-based security experiment: given oracle access to $\hat{f}$, the adversary outputs a predicate of $f$ (e.g., a value $f(x)$ for some $x$, or a membership decision $x \in X$). Show that the advantage is bounded by $\delta + \varepsilon$ or similar. This does not require simulation-based security; it requires making the informal claims in Definition 5.2 precise.
- **Cross-verified**: Yes, by methodology-auditor. The adversary model is not defined (honest-but-curious is implied but never stated). The security claims depend on ROM assumptions that are never discussed in the standard model.

### M2. No experimental evaluation (source: novelty-assessor)
- **Location**: The entire paper
- **Problem**: PoPETs favors papers with practical contributions. The paper has no implementation, no benchmarks, no concrete parameter trade-off analysis for realistic scenarios. The construction time table (Section 6.4) uses toy parameters ($m=100$). A PoPETs reviewer will ask: "For encrypted keyword search over $10^6$ documents with $10^4$ keywords, what are the concrete space, construction time, and query time? How does this compare to a Bloom filter index or an SSE scheme?" The paper cannot answer these questions.
- **Suggestion**: At minimum, add a "Concrete Instantiation" subsection to Section 6: pick a realistic scenario, compute concrete parameters, and provide a comparison table against Bloom filter and SSE baselines. Ideally, implement a prototype and report measurements. An implementation need not be production-quality; even a Python proof-of-concept with timing measurements would substantially strengthen the paper.
- **Cross-verified**: Not applicable (factual observation).

### M3. Missing leakage-abuse attack citations and honey encryption comparison (source: citation-verifier, literature-context)
- **Location**: Section 2 (Related Work)
- **Problem**: The paper positions cipher maps against PPE (OPE, DET) and SSE, claiming cipher maps avoid their leakage. But the paper does not cite the attack papers that demonstrate this leakage is exploitable:
  - Naveed, Kamara, Wright (CCS 2015): inference attacks on PPE databases
  - Islam, Kuzu, Kantarcioglu (CCS 2012): access pattern disclosure on SSE
  - Cash, Grubbs, Perry, Ristenpart (CCS 2015): leakage-abuse attacks on SSE

  Additionally, honey encryption (Juels & Ristenpart, EUROCRYPT 2014) shares the core property that every input/key produces plausible output. This is the most closely related prior work not cited.
- **Suggestion**: Add a "Leakage-abuse attacks" paragraph to Related Work: cite the attack papers, explain how cipher maps' four properties address (or do not address) these specific attack vectors. Add a "Honey encryption" paragraph noting the shared "every input produces output" property and distinguishing cipher maps (reusable, approximate, function evaluation) from honey encryption (decryption-specific, exact).
- **Cross-verified**: Not applicable (literature knowledge).

### M4. Composition formula: equality/inequality inconsistency persists (source: logic-checker)
- **Location**: Theorem 4.1 (line 391), Theorem 7.1 (line 1002), Corollary 7.1 (line 1052), Discussion (line 1189)
- **Quoted text (Thm 4.1)**: "$\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g) = \eta_f + \eta_g - \eta_f \eta_g$"
- **Quoted text (Thm 7.1)**: "$\eta_{g \circ f} \leq \eta_f + \eta_g - \eta_f \eta_g = 1 - (1 - \eta_f)(1 - \eta_g)$"
- **Problem**: Theorem 7.1 correctly states the result as an inequality with equality under re-randomization. But Theorem 4.1 (the forward reference in Section 4.4) still uses equality without qualification. Corollary 7.1 and the Discussion (line 1189) also use equality. This inconsistency was flagged as M1 in the prior review (2026-03-26). The fix was applied only to Theorem 7.1; the forward reference and corollary were not updated.
- **Suggestion**: Change Theorem 4.1 (line 391) to use $\leq$. Change Corollary 7.1 (line 1052) to use $\leq$ with a note that equality holds under re-randomization. Update Discussion line 1189 to use $\leq$ or add the re-randomization qualifier.
- **Cross-verified**: Yes, verified directly against manuscript. Lines 391 and 1002 confirmed.

### M5. Space optimality theorem framing (source: logic-checker)
- **Location**: Theorem 6.2 (lines 704-739)
- **Quoted text**: "The batch construction achieves space complexity $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits per element"
- **Problem**: The $(1-\eta)$ factor is an information-theoretic statement about useful capacity, not an achievable physical space reduction. In the two-level hash construction, the seed table has the same number of entries regardless of $\eta$; failing elements' seeds are "don't cares" but still occupy physical storage unless the table is entropy-coded. The proof's Step 4 says "$(1-\eta)n$ elements are stored" but all $n$ elements are in the hash table; $\eta n$ simply map to wrong outputs. The claim is correct if interpreted as compressed information content but misleading as achievable space without further explanation.
- **Suggestion**: Clarify the theorem statement: "The batch construction achieves information-theoretic space complexity of $(1-\eta)(-\log_2 \varepsilon + \mu)$ bits per element, representing the information content of the $(1-\eta)n$ correctly-encoded elements. Physical storage matches this bound when the seed table is entropy-coded; uncompressed storage is $(-\log_2 \varepsilon + \mu)$ bits per element regardless of $\eta$."
- **Cross-verified**: Yes, by methodology-auditor. The physical storage of the two-level hash construction does not shrink with $\eta > 0$; only the constraint difficulty decreases.

### M6. ROM implications not discussed (source: methodology-auditor)
- **Location**: Section 3.1 (Preliminaries, lines 195-200) and throughout
- **Quoted text**: "Throughout, $h : \{0,1\}^* \to \{0,1\}^n$ denotes a cryptographic hash function modeled as a random oracle"
- **Problem**: All four properties and all theorems depend on the ROM. The paper correctly defines the ROM (fixed from the 2026-03-26 review) but never discusses what happens with real hash functions. For PoPETs, which expects practical security analysis, the gap between ROM and standard model needs at least a discussion paragraph. Key ROM dependencies: (a) totality requires uniform hash output for non-stored elements; (b) correctness analysis requires independent Bernoulli trials; (c) composition requires independence across maps; (d) representation uniformity requires hash values to be independent of the seed.
- **Suggestion**: Add a paragraph at the end of Section 3.1 or in the Discussion: "All results in this paper hold in the random oracle model. Practical instantiation requires hash functions with pseudorandom properties (e.g., SHA-256). The critical ROM assumptions are uniformity of hash output on non-stored elements (for totality), independence of hash values across elements (for correctness analysis and construction time), and independence across maps with different seeds (for composition). Standard-model instantiation via universal hash families is an open question."
- **Cross-verified**: Not applicable (factual observation about the paper's scope).

## Minor Issues

### m1. Abstract overclaims "demonstrate" for set membership and encrypted search (source: prose-auditor)
- **Location**: Abstract, lines 60-62
- **Quoted text**: "demonstrate the construction on arbitrary maps, set membership, and encrypted search"
- **Problem**: Set membership is a 15-line remark (Remark 6.1); encrypted search is a discussion subsection with no new technical content. "Demonstrate" implies comparable treatment.
- **Suggestion**: Change to "illustrate the construction on arbitrary maps, with set membership and encrypted search as applications."

### m2. Discussion section overloaded with 6 disparate subsections (source: prose-auditor)
- **Location**: Section 9 (lines 1176-1349)
- **Suggestion**: Promote "Online Construction" (Section 9.3) to a brief top-level section. Move "What This Framework Is Not" to the Introduction.

### m3. Notation $K(x)$ conflicts with Kolmogorov complexity (source: prose-auditor)
- **Location**: Definition 3.1 (line 212)
- **Suggestion**: Use $\kappa(x)$ or $\mathrm{mult}(x)$ instead.

### m4. Zero figures in 19 pages (source: prose-auditor, format-validator)
- **Location**: The entire paper
- **Problem**: TikZ source files exist in `paper/img/` but are not included. At minimum, a figure showing the acceptance predicate partition of hash space would make the Shannon-frequency duality visually intuitive.
- **Suggestion**: Add at least one figure (acceptance predicate visualization).

### m5. "4th-order Bernoulli Boolean" used without definition (source: prose-auditor)
- **Location**: Section 7.1, line 987
- **Suggestion**: Rephrase as: "The output has four distinct case-dependent correctness probabilities despite the Boolean type having only two values."

### m6. Lower bound proof: $\varepsilon = n/|U|$ identification is informal (source: logic-checker)
- **Location**: Theorem 6.1 proof, line 569
- **Suggestion**: Add one sentence justifying the identification.

### m7. Adversary model not stated (source: methodology-auditor)
- **Location**: Section 5 (Trust Model)
- **Problem**: Honest-but-curious is implied but never stated.
- **Suggestion**: Add: "We model $U$ as honest-but-curious: $U$ evaluates $\hat{f}$ correctly and returns all results, but attempts to learn information about $f$, $X$, or $Y$ from its observations."

### m8. Bucketed construction assumes uniform bucket sizes (source: methodology-auditor)
- **Location**: Proposition 6.2, lines 800-817
- **Suggestion**: Add a note that construction time is dominated by the largest bucket, which is $\Theta(m/k + \log k)$ w.h.p.

### m9. Algorithm 1 uses $h(\ell) \oplus h(x)$ but entropy cipher map uses $h(x \| s)$ (source: methodology-auditor)
- **Location**: Algorithm 1 (line 665) vs. Section 6.5 (line 860)
- **Suggestion**: Unify the hash construction notation.

### m10. Self-citation [bernoulli-types] is unpublished and cited 3 times for foundational claims (source: citation-verifier)
- **Location**: Lines 96, 1201, 1233
- **Suggestion**: Post as arXiv preprint before submission, or include essential Bernoulli definitions as an appendix.

### m11. No DOIs in bibliography entries (source: citation-verifier)
- **Location**: references.bib
- **Suggestion**: Add DOIs for the 17 published entries.

## Suggestions

### S1. Add a concrete parameter instantiation (source: novelty-assessor)
Even without a full implementation, compute concrete bits/element, construction time, and query time for a realistic scenario (e.g., 10^5 documents, 10^4 keywords) and compare against Bloom filter and SSE baselines.

### S2. Consider the AND gate table in inclusion-exclusion form (source: logic-checker)
Write the (0,0) case as $1-(1-p_1)(1-p_2)$ rather than $p_1+p_2-p_1 p_2$ to make the connection to the composition formula transparent.

### S3. Cut the monad disclaimer (source: prose-auditor)
Section 3.3, lines 285-287: "Whether the layers satisfy formal monad laws..." is a distraction. Either develop it or remove it.

### S4. Reformat for PoPETs template early (source: format-validator)
The paper is 19 pages in article class. PoPETs format will change the page count. Test early to avoid last-minute cuts.

## Detailed Notes by Domain

### Logic and Proofs
All proofs are structurally correct. The composition theorem is sound under stated assumptions. The main issue is the equality/inequality inconsistency between Theorem 4.1 and Theorem 7.1, which is a residual from incomplete prior-round fixes. The space optimality theorem is correct as an information-theoretic statement but needs clearer framing to avoid being read as a physical storage claim. The lower bound proof has one informal step ($\varepsilon = n/|U|$) that is correct but should be justified.

### Novelty and Contribution
The paper has two strong novel contributions (acceptance predicate unification, Shannon-frequency duality) and several modest ones. The conceptual framework is valuable. However, for PoPETs specifically, the paper falls short on two axes: formal security definitions (which the paper explicitly refuses to provide) and experimental validation (which is entirely absent). The paper would be stronger at a theory venue (TCC, STACS) with a formal security definition, or at PoPETs with an implementation and attack-literature engagement.

### Methodology
The formal framework is sound. The ROM is correctly stated. The parameter decomposition ($\eta, \varepsilon, \mu, \delta$) is clean and well-motivated. Gaps are: ROM implications not discussed, adversary model not formalized, bucketed construction analysis simplified. These are all addressable without restructuring.

### Writing and Presentation
The writing is clear and well-organized. The honest limitations are a genuine strength. The Discussion is overloaded and could be restructured. The abstract slightly overclaims. Zero figures is a missed opportunity. The paper reads well for a theory audience but needs more concrete detail for a PoPETs audience.

### Citations and References
Bibliography integrity is excellent. The critical gap is engagement with the leakage-abuse attack literature and honey encryption -- both essential for PoPETs positioning. The unpublished self-citation (bernoulli-types) is a risk for peer review.

### Formatting and Production
Clean build, no warnings, all references resolve. Wrong document class for PoPETs (article instead of PoPETs template). No anonymization. These are mechanical fixes but must be done before submission.

## Literature Context Summary

The paper draws on approximate data structures, property-preserving encryption, and secure computation, but does not fully belong to any of these communities. Its closest intellectual relatives are:

1. **Honey encryption** (Juels & Ristenpart, EUROCRYPT 2014): Shares the "every input produces plausible output" property. Not cited.
2. **Entropic security** (Dodis & Smith, EUROCRYPT 2005): Information-theoretic security based on entropy rather than computational assumptions. Most similar formal framework to cipher maps' parameterized guarantees. Not cited.
3. **Homophonic substitution** (Simmons 1979): Correctly identified and cited as the historical ancestor of representation uniformity.
4. **Bloom filters and AMQ structures**: The paper correctly positions cipher maps as generalizing Bloom filters. The space lower bound is standard in this literature.
5. **Leakage-abuse attacks** (Naveed et al. 2015, Islam et al. 2012): Demonstrate the practical consequences of PPE/SSE leakage. The paper claims to avoid this leakage but does not cite or engage with the attack literature. This is the most critical citation gap for PoPETs.

For PoPETs, the paper's main positioning challenge is that it proposes a new primitive without the security formalization or experimental validation that the venue expects. The theoretical contributions (acceptance predicate, Shannon-frequency duality) are strong enough for a theory venue; the practical narrative (encrypted search, set membership) needs concrete backing for a systems-oriented venue.

## Review Metadata
- Review method: Single-reviewer multi-domain analysis covering logic, novelty, methodology, prose, citations, formatting, and literature context
- Cross-verifications performed: 3 (composition inconsistency verified against manuscript; space optimality cross-checked between logic and methodology perspectives; security claim cross-checked between novelty and methodology perspectives)
- Disagreements noted: 1 (logic-checker rated space optimality as MAJOR; after cross-verification with methodology perspective, downgraded to MAJOR with the understanding that it is a framing issue rather than a proof error -- the mathematical claim is correct but the presentation is misleading)
- Prior review issues checked: M1 (composition =/<= ) partially fixed in Thm 7.1 but not in Thm 4.1/Cor 7.1; M2 (ROM) fully fixed; M3 (section ordering) fully fixed; m2 (symmetric error in deniability) fully fixed; m6 (Shannon citation) fully fixed; m7 (Bellare-Rogaway citation) fully fixed; m8 (fixed date) fully fixed; m9 (hypertexnames) fully fixed
