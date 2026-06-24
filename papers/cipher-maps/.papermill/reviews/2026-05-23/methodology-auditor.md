# Methodology Auditor Report (Round 8)

**Date**: 2026-05-23
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Headline finding

The Round 7 critical issue (CRIT-1) was an interpretation error, not a
methodology error; the empirical numbers (24/25 cells in CI, 42x TV
reduction, 132x Huffman defense ratio) remain unchanged. The
methodology audit at R8 reconfirms the R7 methodology assessment:
setup is careful, formulae and empirical numbers match within sampling
noise, but five major methodology gaps remain (variance, baselines,
enumeration, single-run, sample-size justification).

## R7 methodology issues, R8 status

### NOT FIXED (R7 MAJ-7): §10.6 single-run, no replicates
- **Location**: §10.6 line 2493 "All numbers below are single-run (no
  replicates)."
- **Status**: Unchanged. Five tables and three quantitative claims
  (24/25 in CI, mean Bayes gap -0.0004, 42x TV reduction) lack
  cross-replicate variance characterization.
- **Suggestion**: Run 3 replicates with different random seeds; report
  mean and std. PoPETs reviewers will flag this as a critical
  reproducibility weakness, especially because the headline empirical
  claim (42x) depends on a single Zipf instance.
- Severity MAJOR.

### NOT FIXED (R7 MAJ-8): No Bloom-filter baseline in codec sweep
- **Location**: §10.6 entire subsection
- **Status**: Unchanged. The novelty claim "Bloom filters become cipher
  maps with K(x) = 1, etc." would be supported by a direct comparison
  cell in Table tab:le-cam-tight at matched epsilon.
- **Suggestion**: Add a Bloom row to the table. Could be a single
  configuration (K(x) = 1, uniform partition, matched epsilon = 0.4
  to 0.6).
- Severity MAJOR.

### NOT FIXED (R7 MAJ-9): 14 Pareto-frontier configurations unenumerated
- **Location**: §10.6 lines 2528 to 2563
- **Status**: Unchanged. "Across 14 configurations covering |Y| in {4,
  6, 8}, n in {4, 6}, and four p_y shapes" enumerates the parameter
  space (3 x 2 x 4 = 24 candidates, of which presumably 14 are
  Kraft-feasible or distinct). The specific 14 configurations are not
  listed.
- **Suggestion**: Supplementary table listing the 14 configurations
  (|Y|, n, p_y shape) with per-cell TV gaps. Could appear in
  appendix.
- Severity MAJOR.

### NOT FIXED (R7 MAJ-10): §10.3 20 Newsgroups single-run
- **Location**: §10.3 lines 2343 to 2345
- **Status**: Unchanged. "Numbers below are wall-clock from the
  published library benchmarks in the examples/ subdirectory; a single
  run per cell, no cross-replicate aggregation."
- **Suggestion**: 3 replicates; report mean and std for the headline
  numbers (713 docs/sec, 0.39 precision, 12 3-term AND FPs).
- Severity MAJOR.

### NOT FIXED (R7 MAJ-11): Attacker-class tie sample-size justification
- **Location**: §10.6 line 2496 to 2502
- **Status**: Unchanged. "All three attackers achieve the same accuracy
  to within 0.014 sampling noise; mean Bayes gap to the Le Cam bound...
  is -0.0004 (statistically zero)." 0.014 is approximately the Wilson
  CI half-width at n = 5000; the "tie" may not generalize to larger n.
- **Suggestion**: Reword to "indistinguishable at n = 5000" with the
  Wilson CI footnote. If a single rerun at n = 50000 is feasible, that
  would strengthen the claim substantially.
- Severity MAJOR.

## R8 new methodology findings

### METH-N1 (NEW, MINOR): Reproducibility appendix would help
- **Location**: §10.6 generally
- **Issue**: The setup paragraph (lines 2479 to 2493) is dense. A
  reproducibility-focused appendix or block (random seeds, environment,
  exact code paths in towell2026codec) would make the §10.6 study fully
  reproducible.
- **Suggestion**: Add a §10.7 "Reproducibility" subsection or appendix
  with the random seeds, environment fingerprint, and a single command
  to reproduce each table.
- Severity MINOR.

### METH-N2 (NEW, MINOR): The 5-codec vs 6-codec count is ambiguous
- **Location**: §10.6 setup (lines 2482 to 2488)
- **Issue**: The setup paragraph mentions "Six acceptance predicates
  compared" (Dense, two Padded variants, Huffman n=4, Huffman n=5,
  AntiHuffman n=5) which is six, but Table tab:le-cam-tight shows five
  rows. The "Padded (default y_0)" variant from the setup is not in
  the table.
- **Suggestion**: Either add the Padded(y_0) row to Table
  tab:le-cam-tight or remove it from the setup paragraph.
- Severity MINOR.

### METH-N3 (NEW, MINOR): The "key-feature" attacker characterization is thin
- **Location**: §10.6 lines 2614 to 2624 (Table tab:scope-keys)
- **Issue**: The table shows three universe configurations
  (U_random, U_modular, U_partial) with TV (val), TV (joint), value-
  only accuracy, and key-feature accuracy. The "key-feature attacker"
  is not formally defined; the reader has to infer it from context.
- **Suggestion**: Add a one-sentence definition: "the key-feature
  attacker computes the modular residue x mod 7 from the encoded
  query, falling back on a uniform prior when no structure is detected."
- Severity MINOR.

### METH-N4 (NEW, MINOR): §10.3 query distribution remains uniform
- **Location**: §10.3 line 2340
- **Issue**: "Query distribution: uniform over the corpus vocabulary."
  This is a known carry-over from R6. Uniform query distribution
  underestimates leakage from adversaries with frequency knowledge.
- **Suggestion**: Add a Zipf query distribution row (or a note) to
  reflect realistic attack-side query distributions.
- Severity MINOR.

### METH-N5 (NEW, SUGGESTION): Move detailed setup tables to appendix
- **Location**: §10.6 generally
- **Issue**: §10.6 is dense with setup paragraphs and several tables.
  Moving the setup-only tables (Padded variant details, codec naming
  cross-reference) to an appendix would tighten the main-text §10.6
  presentation.
- Severity SUGGESTION.

## Summary of methodology findings

- 0 critical
- 5 major carry-over from R7 (MAJ-7 single-run, MAJ-8 no Bloom,
  MAJ-9 14 configs, MAJ-10 §10.3 single-run, MAJ-11 attacker-tie)
- 4 minor new (METH-N1 reproducibility appendix, METH-N2 6 vs 5
  codec count, METH-N3 key-feature attacker definition, METH-N4
  Zipf query distribution)
- 1 suggestion new (METH-N5 setup tables to appendix)

**Methodology-side recommendation**: All 5 R7 carry-over majors are
substantively addressable in a 1 to 2 day effort. The 3-replicate
runs for §10.6 (MAJ-7) and §10.3 (MAJ-10) are the most important;
the Bloom baseline (MAJ-8) is the most novelty-strengthening.
