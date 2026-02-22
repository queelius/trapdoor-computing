# CLAUDE.md

## Repository Overview

**Trapdoor computing**: a paradigm for computing with values whose meaning is hidden behind a one-way trapdoor (cryptographic hash). The trusted machine holds the decoder; the untrusted machine sees only opaque bit strings flowing through opaque lookup tables.

This repo collects the authentic formalism and develops it into papers. The Bernoulli model (separate repo) provides the error/approximation framework; this repo focuses on the trapdoor construction and composition.

## Key Concepts

- **Cipher map**: a total function on bit strings (bits in, bits out) implementing a trapdoor approximation of a latent function
- **Four properties**: Totality, Representation Uniformity, Correctness (eta-bounded), Composability
- **Trusted/Untrusted model**: trusted machine encodes+decodes, untrusted machine evaluates cipher maps blindly
- **Parameters**: eta (correctness), epsilon (noise decode probability / space), mu = H(Y) (value encoding cost)

## Structure

```
trapdoor-computing/
  foundations/          # Authentic 2023-2024 blog posts (source of truth)
  formalism/            # Design docs and formal development
  papers/               # Papers developed from the formalism
```

## Relationship to Other Repos

- `bernoulli/` (bernoulli_data_type) — C++ library and papers for the Bernoulli model framework. Semi-separate; provides the error model that cipher maps use.
- `oblivious-computing/` — Legacy monorepo. Foundational papers (F1-F4) and extensions (E1-E2) are authentic. Application papers are mixed (authentic content, Claude-era edits). cipher_maps_unified is being reframed here.
- `boolean-algebra-over-trapdoor-sets/` — Pre-July-2024 commits (up to 549091a) are authentic. Later commits are Claude-drifted.

## Build

Papers use standard LaTeX: `cd papers/<name> && make`

## Author

Alexander Towell <lex@metafunctor.com>
