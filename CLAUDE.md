# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

**Trapdoor computing**: a paradigm for computing with values whose meaning is hidden behind a one-way trapdoor (cryptographic hash). The trusted machine holds the decoder; the untrusted machine sees only opaque bit strings flowing through opaque lookup tables.

This repo collects the authentic formalism and develops it into papers. The Bernoulli model (separate repo at `~/github/bernoulli/`) provides the error/approximation framework; this repo focuses on the trapdoor construction and composition.

## Key Concepts

- **Cipher map**: a total function on bit strings (bits in, bits out) implementing a trapdoor approximation of a latent function. Defined formally in `formalism/cipher-map-formalism.md` as a tuple $(\hat{f}, \mathrm{enc}, \mathrm{dec}, s)$.
- **Four properties**: Totality, Representation Uniformity, Correctness (η-bounded), Composability
- **Trusted/Untrusted model**: trusted machine encodes+decodes, untrusted machine evaluates cipher maps blindly
- **Parameters**: η (correctness), ε (noise decode probability / space), μ = H(Y) (value encoding cost), δ (representation uniformity)
- **Two construction strategies**: batch (seed search, e.g. HashSet/entropy map) vs online (algebraic, e.g. trapdoor boolean algebra)

## Provenance and Authenticity

**This is critical.** Prior Claude sessions drifted the formalism toward ORAM-style access-pattern indistinguishability, which is NOT this framework's privacy model. Privacy here comes from one-way hash + uniform representation, not access-pattern hiding.

- **Source of truth**: `foundations/` (authentic 2023–2024 blog posts)
- **Formalism**: `formalism/DESIGN-trapdoor-reframing.md` (four properties, parameter decomposition) and `formalism/cipher-map-formalism.md` (precise definitions, constructions, composition theorem)
- **Full classification**: `ECOSYSTEM-TRIAGE.md` maps every paper/repo as AUTHENTIC, CLAUDE-EXPANDED, MIXED, or DRIFTED
- **Do NOT** import ORAM, differential privacy, simulation-based, or game-based crypto definitions. If you find yourself writing `\Adv`, `\Simulator`, `\Trace`, or `\PPT`, stop. That's the wrong formalism.

## Build Commands

Build systems vary per paper:

```bash
# cipher-maps-unified (Makefile at paper root, builds from paper/ subdir)
cd papers/cipher-maps-unified && make

# maximizing-confidentiality (Makefile at paper root, main.tex at root)
cd papers/maximizing-confidentiality && make
# also: make quick (single pass), make stats (page/section counts)

# boolean-algebra-over-trapdoor-sets (Makefile inside paper/ subdir)
cd papers/boolean-algebra-over-trapdoor-sets/paper && make

# crypto-perf-hash (Makefile inside paper/ subdir)
cd papers/crypto-perf-hash/paper && make

# encrypted-search (Makefile inside paper/ subdir)
cd papers/encrypted-search/paper && make

# algebraic_cipher_types (Makefile inside src/ subdir, not paper/)
cd papers/algebraic_cipher_types/src && make

# General fallback (no Makefile)
cd <paper_dir> && pdflatex main.tex && bibtex main && pdflatex main.tex && pdflatex main.tex
```

## Structure

```
trapdoor-computing/
  foundations/          # Authentic 2023-2024 blog posts (source of truth)
  formalism/            # Design docs and formal development
    cipher-map-formalism.md   # Precise definitions and composition theorem
    DESIGN-trapdoor-reframing.md  # Four properties, parameter decomposition
  papers/               # Papers developed from the formalism
    cipher-maps-unified/      # Most developed paper (on hold pending formalism)
    maximizing-confidentiality/  # USENIX target, 51pp entropy optimization
    boolean-algebra-over-trapdoor-sets/  # Pre-July-2024 authentic only
    crypto-perf-hash/         # Hash construction space analysis
    encrypted-search/         # Encrypted search with Bernoulli types
    algebraic_cipher_types/   # Original 2022 algebraic types paper
  ECOSYSTEM-TRIAGE.md   # Classification of all related papers/code
  .papermill/state.md   # Papermill project state (stage, thesis, next actions)
```

## Relationship to Bernoulli Ecosystem

The Bernoulli model at `~/github/bernoulli/` provides the mathematical foundation cipher maps build on. Individual papers there are separate git repos under `~/github/bernoulli/papers/`:

| Bernoulli paper | Relevance to trapdoor computing |
|---|---|
| `bernoulli_sets/` | Core model: FPR/FNR, confusion matrices, error count distributions. The "approximate" in cipher maps. |
| `bernoulli_composition/` | Error propagation through set operations. Directly used by cipher map composability (Property 4). |
| `bernoulli_maps/` | Approximate functions $X \to Y$ with error rates. Cipher maps ARE approximate maps with a trapdoor. |
| `bernoulli-hash-function/` | Space-optimal Bernoulli set/map construction. The hash construction cipher maps use. |
| `bernoulli_data_type/` | Type-theoretic generalization: Bool, sum, product types. Algebraic cipher types build on this. |
| `bernoulli_classification_measures/` | PPV, accuracy, Youden's J. Measures for evaluating cipher map correctness. |

**Key conceptual link**: A cipher map's correctness parameter η IS the Bernoulli model's false negative rate (β) for the hash-based construction. The Bernoulli composition theorem η_total = 1 - (1-η_f)(1-η_g) from `bernoulli_composition/` is Property 4.

### Other Related Repos

- `oblivious-computing/`: Legacy monorepo. Foundational papers (F1-F4) and extensions (E1-E2). F2 is DRIFTED (wrong ORAM formalism). Application papers are MIXED.
- `boolean-algebra-over-trapdoor-sets/`: Pre-July-2024 commits (up to 549091a) are authentic. Later commits are Claude-drifted.

## Author

Alexander Towell <lex@metafunctor.com>
