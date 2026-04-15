# Oblivious Computing Research

A collection of research papers exploring privacy-preserving computation through probabilistic approximation.

## Core Insight

> **Approximation + Uniform Encoding = Privacy**

These papers develop a unified framework where:
1. **Controlled imprecision** (Bernoulli types) enables space-efficient data structures
2. **Uniform distributions** hide access patterns and values
3. **Hash-based construction** bridges both paradigms

## Paper Series

All papers are organized in the [papers/](./papers) directory.

### Foundational Papers

| # | Paper | Description | Pages |
|---|-------|-------------|-------|
| 1 | [01-bernoulli-theory](./papers/foundational/01-bernoulli-theory) | Type-theoretic framework for probabilistic data structures | 26 |
| 2 | [02-oblivious-computing](./papers/foundational/02-oblivious-computing) | Privacy through uniform encoding | 18 |
| 3 | [03-pir-systems](./papers/foundational/03-pir-systems) | Private information retrieval applications | 14 |
| 4 | [04-statistical-validation](./papers/foundational/04-statistical-validation) | Empirical validation and bounds | 12 |

**Total**: 70 pages

### Extension Papers

| Paper | Description | Pages |
|-------|-------------|-------|
| [threshold-structures](./papers/extensions/threshold-structures) | Novel 2-level probabilistic data structure with O(2) query time | 11 |
| [regular-bernoulli-types](./papers/extensions/regular-bernoulli-types) | Type-theoretic equality under noisy observation | 9 |

**Total**: 20 pages

### Application Papers

| Paper | Description | Status |
|-------|-------------|--------|
| [cipher_maps](./papers/cipher_maps) | Oblivious function approximators | Complete |
| [encrypted-search-ob-types](./papers/encrypted-search-ob-types) | Encrypted search integration | Complete |
| [Maximizing-Confidentiality-*](./papers/Maximizing-Confidentiality-in-Encrypted-Search-Through-Entropy-Optimization) | Entropy-based confidentiality | Complete |

## Reading Order

```
                    ┌─────────────────────────┐
                    │ 01-bernoulli-theory     │
                    │ (foundation)            │
                    └───────────┬─────────────┘
                                │
              ┌─────────────────┼─────────────────┐
              ▼                 ▼                 ▼
    ┌─────────────────┐ ┌───────────────┐ ┌───────────────┐
    │ 02-oblivious-   │ │ threshold-    │ │ regular-      │
    │ computing       │ │ structures    │ │ bernoulli-    │
    │ (privacy)       │ │ (extension)   │ │ types         │
    └────────┬────────┘ └───────────────┘ │ (extension)   │
             │                            └───────────────┘
             ▼
    ┌─────────────────┐
    │ 03-pir-systems  │
    │ (applications)  │
    └────────┬────────┘
             │
             ▼
    ┌─────────────────┐      ┌─────────────────────┐
    │ 04-statistical- │      │ Application papers: │
    │ validation      │      │ - cipher_maps       │
    └─────────────────┘      │ - encrypted-search  │
                             │ - Maximizing-Conf.  │
                             └─────────────────────┘
```

## Key Concepts

| Concept | Introduced In | Description |
|---------|---------------|-------------|
| Latent/Observed duality | Paper 1 §1 | True vs. noisy values |
| Confusion matrix | Paper 1 §2 | Error rate representation |
| Bernoulli types B(T) | Paper 1 §2-4 | Probabilistic type constructors |
| Hash construction | Paper 1 §5 | Unifying implementation |
| Uniformity = Privacy | Paper 2 §2 | Core privacy insight |
| Random oracle paradox | Paper 2 §3 | Why perfect obliviousness is impossible |
| Tuple encoding | Paper 3 §4 | Hide query correlations |
| Entropy maps | Paper 4 §2 | Space-optimal encoding |

## Building All Papers

```bash
# Build all papers
for dir in papers/foundational/*/ papers/extensions/*/; do
    (cd "$dir" && make)
done

# Build just foundational series
for dir in papers/foundational/*/; do (cd "$dir" && make); done

# Build individual paper
cd papers/foundational/01-bernoulli-theory && make
```

## Page Count Summary

| Category | Papers | Total Pages |
|----------|--------|-------------|
| Foundational | 4 | 70 |
| Extensions | 2 | 20 |
| **Grand Total** | **6** | **90** |

## Related Code

- [bernoulli-types](./bernoulli-types) - C++ header-only library implementing Bernoulli types
- [bernoulli-types-python](./bernoulli-types-python) - Python implementation

## Author

Alexander Towell <atowell@siue.edu>

## License

MIT License - See individual paper directories for specific licensing.
