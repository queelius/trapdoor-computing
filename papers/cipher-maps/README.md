# Cipher Maps

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

A unified theoretical framework bridging **algebraic cipher types**, **Bernoulli approximation models**, and **oblivious data structures** for privacy-preserving computation.

> This paper unifies two earlier works: *Algebraic Cipher Types* (functorial foundations) and *Cipher Maps* (space-optimal constructions). The originals are archived in `archive/`.

## Abstract

We present cipher maps, a comprehensive theoretical framework unifying oblivious function approximation, algebraic cipher types, and Bernoulli data models. Building on the mathematical foundations of cipher functors that lift monoids into cipher monoids, we develop oblivious Bernoulli maps that provide privacy-preserving function approximation with controllable error rates. These maps satisfy strong obliviousness conditions while maintaining space-optimal implementations.

We introduce the **Singular Hash Map**, achieving `-log₂ε + μ` bits per element asymptotically---matching information-theoretic lower bounds.

## Key Contributions

1. **Cipher Functor as Proper Functor**: Formalizes the cipher construction as a functor on the category of monoids, ensuring compositional reasoning
2. **Encoding Set Theory**: Characterizes the security--efficiency design space through complete, generating, and minimal encoding sets
3. **Space-Optimal Construction**: The Singular Hash Map matches information-theoretic lower bounds
4. **Composition Theorem**: Nested cipher types compose with error rate `ε_A + ε_B - ε_A·ε_B`
5. **Three-Way Bridge**: Shows algebraic cipher types induce Bernoulli models, which enable oblivious structures

## Building

```bash
# Compile PDF
make

# Clean build artifacts
make clean

# Remove all generated files including PDFs
make cleanall

# Watch for changes and rebuild (requires inotifywait)
make watch
```

## Project Structure

```
cipher_maps_unified/
├── paper/
│   ├── cipher_maps.tex       # Main LaTeX source
│   ├── references.bib        # Bibliography
│   └── img/                  # TikZ figures
├── archive/                  # Archived original papers
│   ├── original_algebraic_cipher_types.zip
│   └── original_cipher_maps.zip
├── Makefile                  # Build automation
├── README.md                 # This file
├── CITATION.cff              # GitHub citation metadata
├── .zenodo.json              # Zenodo archival metadata
├── LICENSE                   # CC-BY-4.0 license
└── cipher_maps.pdf           # Compiled PDF
```

## Reference Implementation

A Python implementation of the algebraic cipher type system is included in the archived `original_algebraic_cipher_types.zip`. It provides:

- `CipherBool`, `CipherInteger`, `CipherPair`, `CipherOptional` types
- Homomorphic operations preserving algebraic laws
- Two-stage cipher function construction algorithm
- Property-based tests verifying functor/monad laws

## Citation

```bibtex
@article{towell2025ciphermaps,
  title={Cipher Maps: A Unified Framework for Oblivious Function Approximation
         Through Algebraic Structures and Bernoulli Models},
  author={Towell, Alexander},
  year={2025}
}
```

## Related Work

- [Bernoulli Types](https://github.com/queelius/bernoulli-types-python) - Python implementation of Bernoulli type theory
- [Oblivious Computing](https://github.com/queelius/oblivious-computing) - Parent research monorepo

## License

This work is licensed under [CC-BY-4.0](LICENSE).
