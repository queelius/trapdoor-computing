# Ecosystem Triage

**Date**: 2026-02-22
**Purpose**: Classify all papers, blog posts, and code in the oblivious-computing ecosystem as authentic vs Claude-drifted.

## Context

Claude misinterpreted "oblivious" as ORAM-style access-pattern indistinguishability and progressively replaced the author's original trapdoor computing formalism with standard crypto formalism that didn't match intent. This triage identifies what's safe to build on vs what needs recovery.

## Classification Key

- **AUTHENTIC**: Original author content, no Claude drift. Safe to cite and build on.
- **MIXED**: Authentic mathematical content with Claude-era editorial/structural changes. Core math is sound; framing/terminology may have shifted.
- **DRIFTED**: Substantially rewritten by Claude with wrong formalism. Use pre-drift commits only.

---

## Authentic Source Material (Source of Truth)

### Blog Posts (metafunctor.com, 2023-2024)

All in the `oblivious-approximate-computing` series. Content verified unchanged from first commit; only Hugo frontmatter formatting changed over time.

| Document | Date | Content |
|----------|------|---------|
| Bernoulli Model | 2023-06-17 | B_T(x), confusion matrices, HashSet construction, -log2(epsilon) bits/element |
| Noisy Turing Machines | 2023-06-17 | Composing Bernoulli logic gates, interval arithmetic, error propagation through circuits |
| Trapdoor Boolean Algebra | 2023-06-17 | Approximate homomorphism F: P(X*) -> {0,1}^n, AND/OR exact, NOT approximate, marginal uniformity |
| Entropy Maps | 2024-02-18 | Prefix-free hash codes, mu=H(Y), two-level hash, "oblivious entropy maps" = hash applied to trapdoors |

**Location**: Copied into this repo at `foundations/`.
**Originals**: `metafunctor/content/post/{bernoulli_bool,trapdoor_bool_algebra,entropy_map}/`

### C++ Library and Papers (bernoulli/)

| Item | Location | Content |
|------|----------|---------|
| bernoulli_data_type | `bernoulli/bernoulli_data_type/` | Original C++ library: bernoulli<bool> with rate_span interval arithmetic, hash_set, hash_map, entropy_bloom_filter |
| Entropy maps paper | `bernoulli/papers/entropy-maps-paper/` | LaTeX + PDF of the entropy map construction |
| Bernoulli sets/maps/relations papers | `bernoulli/papers/` | Original paper drafts for the data structure family |

**Status**: AUTHENTIC. Not a git repo (flat directory), but content predates Claude era.

---

## Papers in oblivious-computing/papers/

### Foundational Series (AUTHENTIC)

No git history (flat files in non-git monorepo), but consistent authorial voice, no signs of Claude formalism drift. Core theoretical foundations.

| ID | Directory | Pages | Notes |
|----|-----------|-------|-------|
| F1 | `foundational/01-bernoulli-theory` | 26 | Type-theoretic foundations of Bernoulli model |
| F2 | `foundational/02-oblivious-computing` | 18 | Privacy through approximation and uniformity |
| F3 | `foundational/03-pir-systems` | 14 | PIR applications |
| F4 | `foundational/04-statistical-validation` | 12 | Empirical validation |

### Extensions (AUTHENTIC)

| ID | Directory | Pages | Notes |
|----|-----------|-------|-------|
| E1 | `extensions/regular-bernoulli-types` | 9 | Type equality under noise |
| E2 | `extensions/threshold-structures` | 11 | Two-level data structure (relates to crypto-perf-hash) |

### Application Papers (MIXED)

Core mathematical content is authentic. Jan-Feb 2026 commits show Claude-assisted editorial work: repository restructuring, citation management, related work updates, review cycles. The math is sound; the framing around "oblivious" may need correction to "trapdoor."

| ID | Directory | Pages | Claude-Era Changes |
|----|-----------|-------|--------------------|
| A1 | `Maximizing-Confidentiality-*` | 51 | Jan 2026: "Improve paper clarity and repository structure" |
| A3+A4 | `cipher_maps_unified` | 17 | Feb 2026: Merged from two papers, two review cycles, DESIGN doc for trapdoor reframing. Most actively Claude-edited. |
| A5 | `crypto-perf-hash` | 16 | Jan 2026: citation metadata added |
| A6 | `encrypted-search-ob-types` | 20 | Jan 2026: repo restructuring |
| A7 | `encrypted_search_confidentiality` | 17 | Jan 2026: repo restructuring |
| A9 | `known_plaintext_attack_time_series_analysis` | 24 | Jan 2026: "Add theoretical depth, pedagogical content" |
| A10 | `estimating_es_conf_moving_avg_bootstrap` | 8 | Published (IEEE CloudCom 2016). Minimal Claude-era changes. |

### Thesis (MIXED)

| ID | Directory | Pages | Notes |
|----|-----------|-------|-------|
| A8 | `encrypted_search_thesis` | 106 | Published MS thesis (2014). Jan 2026: reorganized as archive. Content authentic. |

---

## Separate Repositories

### boolean-algebra-over-trapdoor-sets (DRIFTED)

**Repo**: github.com/queelius/boolean-algebra-over-trapdoor-sets
**Pre-Claude boundary**: commit 549091a (2024-07-07)

| Period | Status | What Happened |
|--------|--------|---------------|
| Pre-July 2024 | AUTHENTIC | Original paper development, incremental updates |
| Oct 2025 | DRIFTED | "Major release: Complete library refactor" |
| Jan 2026 | DRIFTED | "v0.5.0: Complete rewrite as minimal Python library"; paper revision "Fix technical errors, add theoretical framework" |

**Recovery**: Use commits up to 549091a only. Post-drift work imported ORAM-style formalism and departed from the trapdoor map approach.

### bernoulli/ (AUTHENTIC)

Not a git repo. Contains the original C++ bernoulli_data_type library and associated papers. Pre-Claude content throughout.

### oblivious-computing-backup/ (MIXED)

Backup copy of oblivious-computing monorepo. Contains deprecated/ and deprecated-saved/ directories suggesting awareness of drift.

---

## Summary

| Classification | Count | Items |
|----------------|-------|-------|
| AUTHENTIC | ~15 | F1-F4, E1-E2, 4 blog posts, C++ library, bernoulli papers, A10 |
| MIXED | ~8 | A1, A3+A4, A5-A9, A8 thesis |
| DRIFTED | ~1 | boolean-algebra-over-trapdoor-sets (post-July 2024) |

The core formalism is intact. The authentic blog posts and foundational papers provide a solid base. The main recovery work is:

1. Reframe cipher_maps_unified using the trapdoor computing formalism (design doc written, implementation pending)
2. Decide what to do with drifted boolean-algebra repo (revert to 549091a or archive)
3. Correct "oblivious" -> "trapdoor" terminology in mixed papers where it refers to the paradigm (keep "oblivious" where citing ORAM or standard terms)
