# Multi-Agent Review Report

**Date**: 2026-04-12
**Paper**: Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing
**Author**: Alexander Towell
**Version**: Post-restructure (2026-04-12), 17pp, 1398 lines, LaTeX article class
**Prior review**: 2026-04-08 (major-revision; Critical: 2, Major: 11, Minor: 12, Suggestions: 6)
**Recommendation**: **major-revision**

## Summary

**Overall Assessment**: The 2026-04-12 restructure materially improves the paper's narrative coherence. The "one principle, three instances, two realizations" framing is now clearly articulated, the Discussion section is no longer overloaded, and Related Work and Conclusion now exist. Two of the three critical issues from the prior review are fixed. The paper's core contribution (the sum-type impossibility) remains the strongest element, the orbit-closure framework is a reasonable secondary contribution, and the typed-chain discipline earns its place as the design-time payoff. However, the restructure did not address five of the six outstanding major issues (experimental baselines, error bars, FPR table, space data, bibliography expansion, document class), and two new issues surfaced in the restructure: a proof-structure defect in the candidate-set definition that is the same issue C2 from the prior review reappearing as a tautology, and a typed-chain orbit bound that does not apply to the binary operations used in the accompanying example.

**Strengths**:
1. The restructure's unifying thesis ("one principle with three instances plus two realizations") is substantively visible in the paper, not just asserted. The cipher-type section (Section 4) builds to the sum-type impossibility; the orbit-closure section (Section 5) provides the quantitative framework; the realizations (Section 6) instantiate the cut-point pattern. (novelty-assessor, prose-auditor)
2. The sum-type impossibility theorem (Theorem 4.2) is the strongest contribution: clean, information-theoretic, with direct implications for encrypted schema design. The balanced-prior case and the unbalanced case are both treated. (logic-checker, novelty-assessor)
3. The Introduction, Related Work, and Conclusion are well-written: clear, direct, and focused. The positioning against ORAM, FHE, FE, and SSE is explicit and correct. (prose-auditor)
4. The LaTeX build is clean: no warnings, all cross-references resolve through the restructure, structure is intact. (format-validator)
5. The cipher Boolean experimental section, although below conference-grade standard on its own (see weaknesses), contains one genuinely novel empirical finding: the Bernoulli independence assumption breaks for cipher-map AND composition at depth > 2. This is worth expanding. (methodology-auditor, novelty-assessor)
6. Honesty about limitations remains: component-wise encoding leaks correlations, cipher TMs leak head movement, the framework does not provide simulation-based security. (novelty-assessor)

**Weaknesses**:
1. The candidate-set definition (Definition 5.2) was revised in response to prior C2 but the added clause is tautological. The orbit plays no formal role in constraining the candidate set, and the proof of Theorem 5.3 uses a different informal notion. (logic-checker, cross-verified)
2. The typed-chain orbit bound (Proposition 5.4) is stated for a unary chain signature but illustrated with a binary operation (AND), under which the claimed bound 1+k does not hold. (logic-checker)
3. Experimental baselines, error bars, hardware specification, and run counts are absent. The most interesting empirical finding (FPR compounding anomaly) is reported in prose without data. (methodology-auditor)
4. Bibliography is 10 cited references (up from 6 in prior review, still short of the 20 to 30 expected for PLAS). Seven bib entries remain dead. No post-2020 references. (citation-verifier)
5. Document class is article rather than ACM sigconf if PLAS is the target. (format-validator)
6. Cut-point synthesis (Section 6.3) is thin (about 15 lines) and earns the unification in part, not fully. (prose-auditor)

**Finding Counts**: Critical: 1 | Major: 12 | Minor: 18 | Suggestions: 14

---

## Critical Issues

### C1. Candidate-set definition still does not use the orbit (source: logic-checker; cross-verified against lines 637-648 and 550-563)

- **Location**: Section 5.3, Definition 5.2 (lines 637 to 648).
- **Quoted text**:
  > Cand_F(c) = { x in X | exists k s.t. enc(x, k) = c and orbit_F(enc(x,k)) = orbit_F(c) }.
- **Problem**: The orbit function depends only on its cipher-string argument. Whenever enc(x, k) = c, the clause orbit_F(enc(x,k)) = orbit_F(c) is automatic (both evaluate to orbit_F(c)). The second clause is a tautology. The definition reduces to { x in X | exists k s.t. enc(x, k) = c }, which does not depend on F. The subscript F on Cand_F remains misleading. The proof of Theorem 5.3 uses a *different*, informal notion ("every orbit element is a valid encoding of a distinct latent value"), which treats orbit elements as distinguishable equivalence-class representatives, not candidates encoding c. The formal definition and the proof are incompatible.
- **Suggestion**: Redefine Cand_F(c) to require consistency across the orbit, not just at c. One option:
  > Cand_F(c) = { x in X | there exists an assignment x_{c'} in X cup {noise} for each c' in orbit_F(c), satisfying x_c = x and for every (c', c'') in orbit_F(c)^2 with f(c') = c'' (some f in F), f_latent(x_{c'}) = x_{c''} is satisfiable }.
  Alternatively, present the theorem in information-theoretic form: if the adversary sees k distinct cipher values in the orbit, they learn at most log_2 k bits about the latent value, so H(X | orbit view) >= H(X) - log_2 |orbit_F(c)|. Drop the candidate-set detour.
- **Cross-verified**: Yes, by area chair. Re-read lines 550 to 563 (Def 5.1 of orbit) and lines 637 to 648 (Def 5.2 of candidate set). orbitF is a function of cipher strings alone; the added clause is provably a tautology. This is the same defect as prior-review C2, now recurring as a tautological fix rather than an inconsistent-formula fix.

---

## Major Issues

### M1. Typed-chain orbit bound wrong for binary operations (source: logic-checker)

- **Location**: Section 5.5, Definition 5.4 (lines 810 to 817), Proposition 5.4 (lines 824 to 847), Example 5.4 (lines 849 to 866).
- **Quoted text**:
  > [Def 5.4:] A typed composition chain of depth k is a sequence of cipher maps f_0, ..., f_{k-1} where f_i : C(A)_i -> C(A)_{i+1} ...
  >
  > [Prop 5.4:] |orbit_F(c)| <= 1 + k ...
  >
  > [Ex 5.4:] AND_0 : C(Bool)_0 x C(Bool)_0 -> C(Bool)_1.
- **Problem**: Def 5.4 uses a unary signature; Prop 5.4 proves `1+k` by walking `c -> f_0(c) -> f_1(f_0(c)) -> ...` producing exactly one new value per step. But Example 5.4 uses binary AND. With binary operations and full orbit closure starting from multiple cipher Booleans (which is what Boolean search provides: one per word), the orbit can be up to `sum_{i=0}^{k} m^{2^i}` where m is the number of starting values. Even restricting to a single starting value c, the bound `1+k` holds only for unary operations; for binary operations, self-combinations can produce multiple reachable values at each level depending on how AND interacts with already-reached values.
- **Suggestion**: Either (a) restrict Prop 5.4 to unary chains and give a separate bound for arity > 1; (b) restate for single-starting-value, arity-agnostic with a carefully bounded per-level growth; or (c) rewrite Example 5.4 with a unary chain (e.g., NOT or successor) so the proposition and the example match. Option (b) is most faithful; the correct bound for binary chains starting from m initial values is `sum_{i=0}^{k} m^{2^i}`, still finite, still type-bounded, but not `1+k`.
- **Cross-verified**: Yes. Binary arity confirmed at line 855. Example's concluding claim "The orbit from any cipher Boolean value has size at most 3" (line 862) is true only for single-starting-value chains and only if self-combinations collapse to one element per level, which for AND(c, c) happens to hold (the output of a binary operation with identical inputs is deterministic), but the example's framing invites multiple starting values.

### M2. No experimental baselines in Table 1 (source: methodology-auditor; carry-forward of prior M4)

- **Location**: Section 7.3, Table 1 (lines 1204 to 1219).
- **Problem**: Table 1 reports precision, recall, FP count, and time for cipher Boolean search. No baseline is provided. A reader cannot tell whether 0.39 precision / 1.00 recall is good, typical, or poor for Boolean encrypted search. Natural baselines: (1) plaintext search (expected P=R=1.0), to show recall degradation; (2) Bloom filter at the same p_T=0.05 rate, to isolate the noise-region contribution; (3) an SSE benchmark on the same corpus (e.g., Cash et al. 2013 on 20 Newsgroups).
- **Suggestion**: Add plaintext and Bloom filter columns. A three-way comparison isolates what the cipher-map construction contributes beyond a Bloom-like filter.

### M3. No error bars or run counts (source: methodology-auditor; carry-forward of prior M4)

- **Location**: Section 7.3, Table 1 and unnumbered granularity table (lines 1204 to 1256).
- **Problem**: The paper does not state whether numbers are from single or averaged runs. No variance, no standard deviations. Wall-clock times have no hardware specification. Reproducibility is undermined.
- **Suggestion**: 5+ seeds, mean +/- SD for precision/recall/time. Hardware line: "All measurements on [CPU model], single-threaded, Python 3.x, cipher-maps commit [hash]."

### M4. FPR compounding finding in prose only (source: methodology-auditor, novelty-assessor; carry-forward of prior M5)

- **Location**: Section 7.3, "FPR compounding vs. Bernoulli model" paragraph (lines 1228 to 1242).
- **Problem**: The single most surprising experimental finding (Bernoulli independence breaks for cipher-map AND at depth > 2) is a paragraph of prose. "An order of magnitude at k=3" is not quantified. No OR-chain data. No chain-length progression.
- **Suggestion**: Add Table 2: predicted FPR (p_T^k), empirical OR FPR, empirical AND FPR, ratio, for k = 1 to 5. Alternatively, a log-scale figure.

### M5. Space column missing for 2 of 3 granularity levels (source: methodology-auditor; carry-forward of prior M6)

- **Location**: Section 7.3, unnumbered granularity table (lines 1247 to 1256).
- **Problem**: The granularity table shows "---" for intermediate and leaf annotations in the space column. Space is the central axis of the encoding granularity trade-off; without it, the table shows only that root annotation is small.
- **Suggestion**: Measure on-disk size via a safe serialization format (JSON or equivalent) and fill the column; or provide analytic estimates: "Intermediate annotation produces 3 cipher maps of approximately |domain_i| * log_2 |codomain_i| bytes."

### M6. Bibliography thin; 7 dead bib entries remain (source: citation-verifier; carry-forward of prior M2)

- **Location**: `references.bib` and Section 2 Related Work.
- **Problem**: 10 references cited (up from 6), 7 bib entries unused (bloom1970space, fredman1984storing, islam2012access, shannon1948mathematical, song2000practical, towell2026maxconf, turing1936computable), no post-2020 references. PLAS typically expects 20 to 30 references.
- **Suggestion**:
  - Cite the 7 dead entries where relevant: Bloom at Section 7.1 (cipher Boolean as Bloom-like), Fredman at Section 7.1 (PHF implementation), Shannon at Remark 7.1 ("Shannon-optimal allocation"), Turing at Section 6.1 (cipher TM introduction), Song/Islam in Section 2, towell2026maxconf in Section 5 or Section 8 as a sibling work.
  - Add recent SSE leakage attacks (Cash et al. 2015, Kellaris et al. 2016, Grubbs et al. 2017), modern FHE compiler references (Viand et al. 2021 SoK, HEIR, Concrete), and obfuscation-of-FSM references (Lynn-Prabhakaran-Sahai 2004, Ananth-Jain 2015).
  - Target bibliography size: 22 to 28 entries.

### M7. Wrong document class for PLAS target (source: format-validator; carry-forward of prior M8)

- **Location**: Line 1 of main.tex: `\documentclass[11pt]{article}`.
- **Problem**: PLAS (at CCS) uses ACM sigconf via `acmart`. Article class is not accepted in submission.
- **Suggestion**: Create a PLAS submission branch with `\documentclass[sigconf,nonacm=true]{acmart}`, add CCS concepts and keywords, verify page count. If IACR ePrint is the target instead, article class is fine.

### M8. Cipher TM as a "second realization" needs more integration (source: novelty-assessor, prose-auditor)

- **Location**: Section 6.1 and Section 6.3 (lines 895 to 1064).
- **Problem**: Cipher TM occupies one subsection with three formal statements, one remark, but no experimental validation. Section 6.3 (the unification with expression-tree decomposition) is thin (about 15 lines). A reviewer may ask "why is this here?" The "practical realization is expression tree; cipher TM is second realization" framing works only if Section 6.3 earns it.
- **Suggestion**: Strengthen Section 6.3 with (a) a formal definition of "cut point", (b) a figure showing the two realizations side-by-side, and (c) a worked example (e.g., regular-expression matching) realized both ways. Alternatively, compress Section 6.1 further and move full treatment to an appendix.

### M9. Unpublished self-citations are load-bearing (source: citation-verifier; carry-forward of prior M9)

- **Location**: Throughout; `towell2026cipher` cited 16 times, `towell2026bernoulli` 4 times.
- **Problem**: Core definitions (representation uniformity, four properties, composition theorem) and specific referenced propositions ([9, Prop. 4.2], [9, Sec. 9], [9, Prop. 9.1], [9, Sec. 6]) depend on an unpublished manuscript. A reviewer cannot fully evaluate Theorem 5.3 or Proposition 6.1 without access.
- **Suggestion**: Either (a) post towell2026cipher to IACR ePrint or arXiv before submission; and/or (b) expand Section 3 Preliminaries to be self-contained for the results in this paper (include composition theorem and representation-uniformity statement verbatim). Target: +1 page of Preliminaries material.

### M10. Precision of 0.39 is unexplained to PLAS audience (source: methodology-auditor; carry-forward of prior m4)

- **Location**: Section 7.3, Table 1, first row.
- **Problem**: A PLAS reader without Bloom-filter background sees 0.39 precision on a single-term query and may conclude the scheme is broken. The expected precision is approximately `TP / (TP + p_T * (N - TP))`, which for TP small relative to N and p_T=0.05 produces ~0.3 to 0.4.
- **Suggestion**: Add one sentence: "The precision reflects the p_T=0.05 false-positive rate; for a true set of size k in a corpus of size N, expected precision is approximately k / (k + 0.05(N-k))."

### M11. Denominator switch in Theorem 5.3 proof not rigorously justified (source: logic-checker)

- **Location**: Section 5.3, Theorem 5.3 and proof (lines 661 to 689).
- **Problem**: The definition of `conf_F(c)` uses `|X|` as denominator; the theorem states a bound with `2^n` as denominator. The proof transitions from one to the other via "|X| <= 2^n," but the resulting inequality has `|orbit|/|X| >= |orbit|/2^n`, giving `1 - |orbit|/|X| <= 1 - |orbit|/2^n`. To conclude `conf >= 1 - |orbit|/2^n` from `conf >= 1 - |orbit|/|X|` does not follow; the substitution yields a looser but unjustified bound.
- **Suggestion**: State the theorem with `|X|` in the denominator: `conf_F(c) >= 1 - |orbit_F(c)|/|X|`. Alternatively, use an entropy-form bound: `H(X | orbit view) >= H(X) - log_2 |orbit_F(c)|`, which avoids the denominator issue entirely.

### M12. 20 Newsgroups dataset uncited (source: citation-verifier; carry-forward of prior m10)

- **Location**: Section 7.3, abstract mention.
- **Problem**: The corpus is used but never formally cited.
- **Suggestion**: Add Lang 1995 (NewsWeeder) or the scikit-learn dataset reference.

### M13. 5,000-document subset is unmotivated (source: methodology-auditor)

- **Location**: Section 7.3, lines 1192 to 1202.
- **Problem**: Corpus has 18,266; experiments use 5,000. Selection criterion and reason for subsetting unstated.
- **Suggestion**: One sentence: "We evaluate on a random 5,000-document sample (fixed across queries) for tractability; results extrapolate to the full 18,266 corpus as [note/appendix]."

### M14. "Order of magnitude" not quantified (source: logic-checker, methodology-auditor)

- **Location**: Section 7.3, line 1234.
- **Problem**: "The empirical FPR exceeds p_T^k by an order of magnitude at k=3" is vague. The actual value should be stated.
- **Suggestion**: "The empirical FPR at k=3 is approximately X, versus the predicted 1.25e-4, a factor-of-Y excess."

---

## Minor Issues

### m1. Notation overload: delta (TV distance) vs. delta_T (transition function) (source: prose-auditor; carry-forward of prior m2)
- **Location**: Section 3 (delta) vs. Section 6.1 (delta_T).
- **Suggestion**: Rename TM transition to tau_T or sigma_T.

### m2. C(X) notation not formally defined (source: prose-auditor; carry-forward of prior M7)
- **Location**: Line 252, first use in prose.
- **Suggestion**: Add Definition 3.3 in Preliminaries: `C(X) = { enc(x, k) : x in X, 0 <= k < K(x) } subset B^n`.

### m3. Cipher TM head direction framing inconsistent (source: logic-checker)
- **Location**: Section 6.1, Def 6.1 (lines 906 to 923).
- **Problem**: "cipher encoding of (next state, symbol to write, head direction)" vs. "The head direction is not cipher-encoded."
- **Suggestion**: Output is a pair: (cipher(next state, symbol), direction in clear).

### m4. Cipher TM pairing operation not constructed (source: logic-checker; carry-forward of prior m3)
- **Location**: Section 6.1, Def 6.1.
- **Suggestion**: Either require (state, symbol) stored jointly per tape cell, or acknowledge the pairing cipher map as a required sub-construction.

### m5. "All three produce zero errors" is definitional, not empirical (source: logic-checker; carry-forward of prior m6)
- **Location**: Section 7.3, line 1257.
- **Suggestion**: "As expected from the PHF construction, all three produce zero errors on the full domain."

### m6. "Up to correctness eta" in Example 5.1 is loose (source: logic-checker)
- **Location**: Section 5.4, Example 5.1, line 717.
- **Suggestion**: Add one-sentence clarification of how the orbit degrades under eta > 0.

### m7. Granularity table unnumbered (source: format-validator; carry-forward of prior m5)
- **Location**: Section 7.3, lines 1246 to 1256.
- **Suggestion**: Promote to `\begin{table}` with caption and label.

### m8. Queries in Table 1 are not specified (source: methodology-auditor)
- **Location**: Section 7.3, Table 1.
- **Suggestion**: List or describe the query selection protocol.

### m9. 150-input loan pipeline is a toy (source: methodology-auditor; carry-forward of prior m7)
- **Location**: Section 7.3, granularity table.
- **Suggestion**: Scale up or add asymptotic-scaling note.

### m10. Construction rate lacks hardware specification (source: methodology-auditor)
- **Location**: Section 7.3, line 1202.
- **Suggestion**: Add hardware details.

### m11. No reproducibility statement (source: methodology-auditor)
- **Location**: Section 7.3.
- **Suggestion**: URL, commit hash, dataset reference.

### m12. Abstract's closing sentence is a run-on (source: prose-auditor)
- **Location**: Lines 57 to 62.
- **Suggestion**: Split into two sentences.

### m13. "Most fundamental algebraic structure" is a value judgement (source: prose-auditor)
- **Location**: Section 7, line 1072.
- **Suggestion**: "A minimal non-trivial sum-type instance."

### m14. "Shannon-optimal allocation" uncited (source: prose-auditor, citation-verifier)
- **Location**: Remark 7.1, line 1101.
- **Suggestion**: Cite shannon1948mathematical (already in bib).

### m15. "Compile-time decision with no runtime cost" misleading (source: prose-auditor)
- **Location**: Section 5.5, lines 872 to 874.
- **Suggestion**: Clarify that the k cipher maps must still be stored.

### m16. Remark 5.3 duplicates Example 5.1 (source: prose-auditor)
- **Location**: Section 5.4.
- **Suggestion**: Fold one into the other.

### m17. Conclusion's "apply to any cipher map construction" overstated (source: prose-auditor)
- **Location**: Section 9, line 1358.
- **Suggestion**: Constrain to constructions satisfying representation uniformity and composability.

### m18. "phobic" PHF library uncited (source: citation-verifier)
- **Location**: Section 7.3, line 1193.
- **Suggestion**: Footnote or citation with URL.

---

## Suggestions

1. **Add at least one figure**: either an orbit-closure diagram in Section 5, or a cut-point diagram showing both realizations side by side in Section 6.3. The paper is 17 pages of theory with zero figures. (prose-auditor, format-validator)

2. **Present confidentiality bound in entropy form**: `H(X | view) >= H(X) - log_2 |orbit|` avoids the |X| vs 2^n denominator issue (M11) and better fits the PLAS audience's familiarity with min-entropy measures. (logic-checker)

3. **Strengthen Section 6.3 cut-point synthesis**: formal definition of "cut point," worked example realized both ways (e.g., regular-expression matching as TM and as expression tree), figure. (novelty-assessor, prose-auditor)

4. **Promote the FPR compounding finding**: dedicated subsection with Table 2, an intuitive explanation (deterministic cipher-map output is not a fresh random draw), and implications for the composition theorem. (novelty-assessor, methodology-auditor)

5. **Acknowledge the reachability/orbit origin**: a one-paragraph note that "orbit closure" is a reachability construct used in dynamical systems, model checking, and epistemic logic; the novelty is the application to cipher-value transition systems. (novelty-assessor)

6. **Explicitly position cipher TM against iO/VBB/FSM obfuscation**: a paragraph distinguishing cipher TMs from cryptographic obfuscators (not game-based, not PPT-secure; representation-uniform and approximate-correct). Preempts "how does this relate to obfuscation?" reviewer questions. (novelty-assessor)

7. **Add an orbit-bound validation experiment**: measure orbit size under AND/NOT for varying n, plot against 2^n, test whether the predicted bound holds. Connects theory to empirical work in one place. (methodology-auditor)

8. **Connect @cipher_node to multi-stage programming terminology**: frame as a staging annotation to better engage the PL-reviewer vocabulary. (novelty-assessor)

9. **Consider splitting the paper if PLAS page limits force a cut**: sum-type impossibility + orbit closure + typed chains is one coherent paper; cipher TM + expression-tree + experiments is another. Current 17 article pages translates to approximately 10 to 12 sigconf pages, likely within limits. (novelty-assessor, carry-forward of prior suggestion 4)

10. **Contribution-vs-prior-art comparison table**: a compact matrix comparing cipher maps, FHE, FE, SSE on hiding mechanism, operations, type-system support. (novelty-assessor)

11. **Cite `towell2026maxconf`**: the sister paper on entropy-ratio confidentiality is thematically adjacent and currently unused. (citation-verifier)

12. **Use `natbib`'s `\citet`**: author-name citations read more naturally than bracketed numbers in Related Work. (citation-verifier)

13. **Remove "functorial" from submission metadata** (if present): the paper has no category theory. (novelty-assessor, carry-forward of prior m11)

14. **Add reproducibility paragraph**: artifact URL, dataset citation, hardware, seeds. (methodology-auditor)

---

## Detailed Notes by Domain

### Logic and Proofs (logic-checker)
Nine formal results. Seven are sound (Prop 4.1, Thm 4.2, Thm 5.1, Cor 5.2, Prop 6.1, Prop 6.2, Prop 7.1). Two have issues: Def 5.2 + Thm 5.3 (candidate set tautology + denominator switch, C1 + M11) and Prop 5.4 (typed-chain bound wrong for binary operations, M1). The prior-review C1 (noise absorption) and major M1 (balanced prior) are fixed. The prior-review C2 is *partially* fixed: the formulas are cleaned up but the underlying candidate-set definition still does not use the orbit in a non-trivial way.

### Novelty and Contribution (novelty-assessor)
The restructure materially improves contribution cohesion. The sum-type impossibility remains the strongest result; the orbit-closure framework is a reasonable framing-novel contribution; typed chains and expression-tree decomposition are legitimate design-discipline contributions. Cipher TM sits uneasily as a "second realization"; Section 6.3 earns the unification only partially. Three positioning gaps: vs. obfuscation-of-FSM literature (cipher TM), vs. FE lower bounds (sum-type impossibility), vs. reachability (orbit closure). Each gap is a paragraph's worth of acknowledgement.

### Methodology (methodology-auditor)
The experimental section is the weakest part of the paper and was not materially improved by the restructure. The prior review's M4, M5, M6 all persist. Baselines, error bars, hardware spec, run counts, sampling motivation, and the FPR-compounding table are all outstanding. Strengthening Section 7.3 is the most impactful improvement for the paper's overall credibility.

### Writing and Presentation (prose-auditor)
The restructure fixed three major prose issues from the prior review: Discussion overload (M3), no Related Work (M10), no Conclusion (M12). The writing quality is high. Remaining issues are granular: notation overload, one missing formal definition, one thin synthesis subsection, a handful of sentence-level over-claims.

### Citations and References (citation-verifier)
10 cited, 17 bib entries (7 dead), no post-2020 references, 3 self-citations to unpublished manuscripts. The prior review M2 is partially addressed. The self-citation dependency is serious for a submission; posting towell2026cipher to IACR ePrint or arXiv before submission would help.

### Formatting and Production (format-validator)
Build is clean. Cross-references all resolve. Structure is intact. Document class needs conversion for PLAS (M7). Unnumbered table needs promotion (m7). Zero figures (FV-MIN-2) is an outlier for a 17-page theoretical paper.

---

## Literature Context Summary

The paper's positioning against direct comparators (FHE, FE, ORAM, SSE, PPE) is explicit and correct. The positioning against adjacent literatures (obfuscation of FSMs, reachability/model-checking, recent SSE leakage attacks, FHE compilers) is absent. The bibliography needs approximately 12 additional references to meet PLAS expectations.

The sum-type impossibility theorem belongs to a recognized family (deterministic encryption leakage, FE lower bounds) but is distinct in its framework (representation uniformity, not IND-CPA) and setting (algebraic sum types, not equality). Orbit closure is a reachability construct with precedents but the application to cipher-value transition systems is new. The FPR compounding anomaly is genuinely novel and underclaimed.

Venue fit: PLAS is the natural primary target given the type-theoretic framing, the sum-type impossibility, and the typed-chain discipline. IACR ePrint is a reasonable fallback. TCC is a weaker fit (game-based proofs expected).

---

## Comparison with 2026-04-08 Review

The restructure's effect on the prior review's findings:

**Critical (prior, 2)**:
- C1 (noise absorption falsity): **fixed**. Prop 7.1 now states "noise unreliability," which the proof supports.
- C2 (confidentiality bound formulas): **partially fixed**. Formulas cleaned up; single formula stated as the theorem. But the underlying candidate-set defect recurs (current C1 in this review, LC-CRIT-1).

**Major (prior, 11)**:
- M1 (balanced prior assumption): **fixed** by explicit acknowledgement in proof.
- M2 (bibliography thin): **partially fixed**. 10 cited (up from 6), still short of 20.
- M3 (Discussion overload): **fixed** by restructure.
- M4 (no baselines/error bars): **not addressed** (current M2, M3).
- M5 (FPR compounding in prose only): **not addressed** (current M4).
- M6 (space data missing): **not addressed** (current M5).
- M7 (C(X) notation not formalized): **not addressed** (current m2).
- M8 (wrong document class): **not addressed** (current M7).
- M9 (unpublished self-citations): **not addressed** (current M9).
- M10 (no Related Work): **fixed** by restructure.
- M11 (scope too broad): **partially addressed** by unifying restructure.

**Minor (prior, 12)**:
- m1 (K(x) undefined): **not addressed** (carry-forward).
- m2 (delta vs delta_T overload): **not addressed** (current m1).
- m3 (pairing operation hand-waved): **not addressed** (current m4).
- m4 (0.39 precision unexplained): **not addressed** (current M10).
- m5 (unnumbered table): **not addressed** (current m7).
- m6 (zero errors "is expected"): **not addressed** (current m5).
- m7 (150-input toy): **not addressed** (current m9).
- m8 (conf_F not defined before theorem): **fixed** by Def 5.3.
- m9 (cipher value/map conflation): **acceptable as-is** (remark exists).
- m10 (20 Newsgroups uncited): **not addressed** (current M12).
- m11 (functorial metadata): **to verify** at submission time.
- m12 (no Conclusion): **fixed** by restructure.

Summary: 6 of 25 issues fixed. 5 partially addressed or subsumed by restructure. 14 remaining open. The restructure was targeted at prose/structure problems; the logic and experimental issues remain largely untouched.

---

## Recommendation Rationale

**major-revision** because:
- One critical issue (C1, candidate-set tautology) blocks publication as-is. The proof of Theorem 5.3 does not follow from the formal definition; this is a correctness concern for the paper's central quantitative result.
- Multiple major issues (typed-chain bound arity, experimental baselines, FPR compounding table, bibliography expansion, document class) are all individually addressable but collectively significant.
- The paper's contribution is real and the restructure is a net improvement. With C1, M1, M2-M14 addressed, the paper would be in strong shape for PLAS.

The path to acceptance is clear: fix the candidate-set definition (or replace with entropy-form bound), correct the typed-chain bound for arity > 1, flesh out the experiments with baselines and a FPR-compounding table, expand the bibliography to 22 to 28 references, and reformat for ACM sigconf. Estimated effort: one focused revision pass of two to three weeks.

---

## Review Metadata

- Specialists consulted: logic-checker, novelty-assessor, methodology-auditor, prose-auditor, citation-verifier, format-validator, literature-context (merged scout).
- Cross-verifications performed:
  - C1 (candidate-set tautology): verified by area chair against Def 5.1 (lines 550 to 563) and Def 5.2 (lines 637 to 648).
  - M1 (typed-chain binary bound): verified by area chair against Def 5.4 (lines 810 to 817) and Example 5.4 (lines 849 to 866).
  - M11 (denominator switch): verified by area chair against Def 5.3 (lines 651 to 659) and Thm 5.3 (lines 661 to 670).
- Disagreements noted: 0 (no specialist disagreements on critical or major findings).
- Specialists not disagreed with on C1: logic-checker flagged; methodology-auditor (via cross-check at the definitional level) concurs that the formalism does not support the theorem as stated.
