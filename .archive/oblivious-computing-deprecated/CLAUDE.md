# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

Research monorepo on **oblivious computing** and **privacy-preserving computation**. LaTeX research papers are the primary contributions; code implementations are secondary.

**Core Thesis**: Approximation + Uniform Encoding = Privacy

## Structure

```
oblivious-computing/
├── papers/                          # All research papers
│   ├── foundational/                # Core 4-paper series (read in order)
│   │   ├── 01-bernoulli-theory/     # 26 pages - type-theoretic foundations
│   │   ├── 02-oblivious-computing/  # 18 pages - privacy through uniformity
│   │   ├── 03-pir-systems/          # 14 pages - PIR applications
│   │   └── 04-statistical-validation/ # 12 pages - empirical validation
│   ├── extensions/                  # Side papers (read after Paper 1)
│   │   ├── threshold-structures/    # 11 pages - novel 2-level data structure
│   │   └── regular-bernoulli-types/ # 9 pages - type equality under noise
│   └── [application papers]         # Various applied research
├── bernoulli-types-python/          # Python implementation library
├── archive/                         # Archived older C++ code and PDFs
├── blog/                            # Blog posts
└── docs/                            # Documentation
```

## Building Papers

Each paper directory is self-contained with `paper.tex`, `Makefile`, `notation.tex`, `macros.tex`, `references.bib`.

```bash
# Build single paper
cd papers/foundational/01-bernoulli-theory && make

# Build all foundational papers
for dir in papers/foundational/*/; do (cd "$dir" && make); done

# Build all papers
for dir in papers/foundational/*/ papers/extensions/*/; do (cd "$dir" && make); done

# Clean auxiliary files
make clean      # Remove .aux, .log, etc.
make cleanall   # Also remove PDF
```

## Python Library

```bash
cd bernoulli-types-python

# Install for development
pip install -e ".[dev]"

# Run tests
pytest

# Run with coverage
pytest --cov=bernoulli_types --cov-report=html

# Type checking
mypy src/bernoulli_types

# Linting
ruff check src/
```

## Key Concepts

| Concept | Paper | Description |
|---------|-------|-------------|
| Latent/Observed duality | 1 §1 | True values vs noisy observations |
| Confusion matrix | 1 §2 | FPR/FNR error rate representation |
| Bernoulli types B(T) | 1 §2-4 | Probabilistic type constructors |
| Hash construction | 1 §5 | ValidEncodings sized by 1/p(x) |
| Uniformity = Privacy | 2 §2 | Uniform distributions hide patterns |
| Random oracle paradox | 2 §3 | Consistency vs uniformity tension |
| Tuple encoding | 3 §4 | Hide Boolean AND correlations |
| Entropy maps | 4 §2 | Space-optimal encoding |

## Reading Order

```
Paper 1 (foundation) → Paper 2 (privacy) → Paper 3 (applications) → Paper 4 (validation)
                    ↘ threshold-structures (extension)
                    ↘ regular-bernoulli-types (extension)
```

## Application Papers in `papers/`

- ~~`Maximizing-Confidentiality-*`~~ - Moved to `~/github/trapdoor-computing/papers/maximizing-confidentiality/`
- `encrypted-search-ob-types/` - Encrypted search integration
- `algebraic_cipher_types/` - Functorial homomorphic encryption framework
- ~~`cipher_maps_unified/`~~ - Moved to `~/github/trapdoor-computing/papers/cipher-maps-unified/`
- ~~`boolean-algebra-over-trapdoor-sets/`~~ - Moved to `~/github/trapdoor-computing/papers/boolean-algebra-over-trapdoor-sets/`
- ~~`crypto-perf-hash/`~~ - Moved to `~/github/trapdoor-computing/papers/crypto-perf-hash/`
- ~~`encrypted_search_thesis/`~~ - Moved to `~/github/papers/encrypted-search-thesis/`
- ~~`estimating_es_conf_moving_avg_bootstrap/`~~ - Moved to `~/github/papers/estimating-es-conf-mab/`
- ~~`known_plaintext_attack_time_series_analysis/`~~ - Moved to `~/github/papers/known-plaintext-attack-time-series-analysis/`
