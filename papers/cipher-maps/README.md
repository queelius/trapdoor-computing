# Cipher Maps

[![License: CC BY 4.0](https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)

**Cipher Maps: Total Functions as Trapdoor Approximations.** A unifying
framework for parameterized-leakage outsourced function evaluation in
the quantitative information flow (QIF) tradition.

> This paper merges two earlier works (*Algebraic Cipher Types* and
> *Cipher Maps*); the originals are archived in `archive/`. The
> companion entropy-ratio and cipher-rekeying papers live in the
> sibling directories of the `trapdoor-computing` monorepo.

## Abstract

Outsourcing function evaluation to an untrusted machine typically
requires oblivious RAM, fully homomorphic encryption, or garbled
circuits, each at substantial cost. We propose the *cipher map*: a total
function on bit strings whose privacy properties emerge from a one-way
trapdoor (a cryptographic hash with a secret seed) combined with a
frequency-equalized output distribution. Cipher maps fit the
quantitative information flow tradition: rather than negligible leakage
in a security parameter, they bound observable leakage by measurable
parameters δ (representation uniformity), ε (noise-decode probability),
and η (correctness), with the entropy ratio as the security measure. The
construction reduces to one design choice, an *acceptance predicate*
partitioning hash space among output values.

## Key Contributions

1. **The cipher map abstraction** with four measurable properties
   (totality, representation uniformity, correctness, composability) as
   the unit of analysis for parameterized-leakage outsourced computation.
2. **The acceptance predicate as the universal knob**, with a
   (TV, length) Pareto frontier refining the Shannon-frequency duality:
   the Shannon-optimal (Huffman) and TV-optimal allocations are distinct
   under integer codeword constraints.
3. **A multi-instance composition theorem** (the coincidence oracle):
   a closed form for shared-function leakage across `t` instances, with
   randomized encoding as the deployment-side defense.
4. **Empirical Le Cam tightness** across a codec sweep and multiple
   attacker classes, plus a 20 Newsgroups encrypted-search evaluation
   and a Bloom-filter space comparison.
5. **A unification** of three previously disconnected literatures
   (approximate data structures, frequency-hiding encryption, encrypted
   search) under one formalism with measurable parameters.

## Building

```bash
make          # full build (pdflatex x3 + bibtex), copies PDF to repo root
make clean    # remove aux files
make cleanall # remove aux + PDFs
make watch    # rebuild on change (requires inotifywait)
```

Source is `paper/cipher_maps.tex` with `paper/references.bib`; TikZ
figures in `paper/img/`.

## Reference Implementation

The experimental claims (20 Newsgroups encrypted search, the
Bloom-filter comparison, the codec-security and randomized-encoding
studies) are backed by the open-source `cipher-maps` Python library
(PHF backend via `phobic`, cipher Boolean types, typed composition
chains). Benchmark scripts ship with the library.

## Citation

```bibtex
@misc{towell2026ciphermaps,
  title  = {Cipher Maps: Total Functions as Trapdoor Approximations},
  author = {Towell, Alexander},
  year   = {2026},
  note   = {Manuscript}
}
```

(DOI to be added on archival.)

## Related Work

- [Trapdoor Computing](https://github.com/queelius/trapdoor-computing): parent monorepo (formalism, companion papers, library)
- [Bernoulli Types](https://github.com/queelius/bernoulli): the error/approximation model cipher maps build on

## License

This work is licensed under [CC-BY-4.0](LICENSE).
