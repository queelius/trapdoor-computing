# Prose Auditor Report

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Summary

The writing is clean, well-organized, and unusually honest about limitations. The restructuring from the prior review (trust model before constructions) has been implemented. The narrative arc from abstraction through properties to constructions to composition is clear. Remaining issues are minor.

## Findings

### MINOR: The abstract claims "demonstrate the construction on arbitrary maps, set membership, and encrypted search" but two of these are only in discussion

- **Location**: Abstract, lines 60-62
- **Quoted text**: "demonstrate the construction on arbitrary maps, set membership, and encrypted search"
- **Problem**: "Arbitrary maps" is the entropy cipher map (Section 6.5) -- a full construction with algorithm and space analysis. "Set membership" is a remark (Remark 6.1) -- a short paragraph, not a full development. "Encrypted search" is a discussion subsection (Section 9.4) -- a domain vocabulary mapping with no new technical content. The abstract's "demonstrate" suggests all three receive comparable treatment, but they do not.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Weaken to: "prove the composition and space optimality theorems, and illustrate the construction on arbitrary maps, with set membership and encrypted search as applications."

### MINOR: Section 9 (Discussion) is overloaded -- 6 subsections spanning diverse topics

- **Location**: Section 9 (lines 1176-1349)
- **Quoted text**: Subsections: Relationship to Bernoulli Model, Algebraic Structure, Online Construction, Application: Encrypted Search, Open Questions, What This Framework Is Not
- **Problem**: The Discussion section contains material that ranges from foundational context (Bernoulli model), to an entirely separate construction (online/Boolean algebra), to an application (encrypted search), to scope delimitation (what this is not). Some of these deserve their own sections; others could be cut. The online construction (Section 9.3) and the encrypted search application (Section 9.4) each get 1 paragraph of substantive content, which dilutes the paper's focus.
- **Severity**: MINOR
- **Confidence**: MEDIUM
- **Suggestion**: Consider promoting "Online Construction" to a brief top-level section (after Composition) to give it structural weight matching its importance to the paper's narrative. Move "What This Framework Is Not" to the Introduction (where it would serve as a scope delimiter). The Discussion then becomes: Bernoulli Model, Algebraic Structure, Encrypted Search Application, Open Questions.

### MINOR: Notation $K(x)$ is overloaded with unrelated standard notation

- **Location**: Definition 3.1 (line 212), Table 4.1 (line 424)
- **Quoted text**: "$K(x) \geq 1$ is the number of encodings for element $x$"
- **Problem**: $K(x)$ is a standard notation for Kolmogorov complexity in information theory. Using it for the multiplicity function risks confusion for readers in the information theory community (a plausible audience for this paper).
- **Severity**: MINOR
- **Confidence**: MEDIUM
- **Suggestion**: Consider $M(x)$, $\kappa(x)$, or $\mathrm{mult}(x)$ instead.

### MINOR: Zero figures in a 19-page paper

- **Location**: The entire paper
- **Problem**: The paper has no figures. The TikZ source files `fig_shmap.tex` and `fig_shs.tex` exist in `paper/img/` but are not included. Figures would help with: (a) the construction layers (Section 3.3) -- a diagram showing undef -> noise -> cipher; (b) the trust model protocol (Section 5) -- a diagram showing $T$ and $U$ with information flows; (c) the acceptance predicate (Section 6.2) -- a visualization of hash space partitioned among acceptance sets.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Add at least one figure. The acceptance predicate partition of hash space is the most impactful candidate: it would make the Shannon-frequency duality visually intuitive.

### MINOR: The term "4th-order Bernoulli Boolean" is introduced without definition

- **Location**: Section 7.1 (line 987)
- **Quoted text**: "The output is a 4th-order Bernoulli Boolean: four distinct correctness probabilities despite the Boolean type having only two values."
- **Problem**: "4th-order Bernoulli Boolean" is not defined anywhere in the paper, nor is it standard terminology. The meaning is inferrable from context (a Boolean with four case-dependent correctness probabilities), but it reads as jargon from the Bernoulli framework that leaked into this paper without a definition.
- **Severity**: MINOR
- **Confidence**: HIGH
- **Suggestion**: Either define it formally or rephrase: "The output has four distinct case-dependent correctness probabilities despite the Boolean type having only two values."

### SUGGESTION: The construction layers (Section 3.3) disclaim monad structure -- consider removing the disclaimer or making it shorter

- **Location**: Section 3.3 (lines 285-287)
- **Quoted text**: "Whether the layers satisfy formal monad laws in the approximate setting is an open question"
- **Problem**: The monad reference is a distraction for most readers and an understatement for category theory readers (who would want either a proof or no mention). The disclaimer is appropriately cautious but adds noise.
- **Suggestion**: Cut the monad sentence entirely, or move it to the Discussion (Open Questions).

### Writing Quality Assessment

| Aspect | Rating | Notes |
|---|---|---|
| Clarity | Good | Most sections are clear on first reading |
| Organization | Good | Logical flow from abstraction to properties to constructions |
| Notation consistency | Good | $\eta, \varepsilon, \mu, \delta$ used consistently throughout |
| Honesty about limitations | Excellent | Unusually candid (marginal uniformity only, equality pattern leakage, what this is not) |
| Conciseness | Adequate | Some sections (Discussion) could be tighter |
| Abstract quality | Good | Clear thesis statement; minor overclaim on demonstrations |
