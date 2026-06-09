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

## Core Principles

1. **Bernoulli Axiom**: Element-wise independence + conditional independence of block error rates collapse exponential error models to 2 parameters per element. This is why composition is tractable.
2. **Space-Accuracy Duality**: bits/element = -log2(epsilon) + mu. Three independent derivations (bernoulli_entropy, bernoulli-hash-function, crypto-perf-hash) converge on this. -log2(epsilon) is the cost of hiding; mu = H(Y) is the cost of encoding values.
3. **Composition Predictability**: eta_total = 1 - prod(1 - eta_i). Errors multiply independently; for small eta, approximately sum(eta_i). Appears in noisy-gates, bernoulli_composition, bernoulli_maps, and cipher-map-formalism.
4. **Totality as Privacy**: The untrusted machine sees a total function on bit strings. It cannot distinguish real queries from filler, one encoding from another, or correct results from noise. This is NOT ORAM, FHE, or simulation-based security.
5. **Encoding Granularity Trade-off**: Joint encoding hides correlations; component-wise encoding leaks them. The entanglement parameter p controls the spectrum from marginal uniformity (p=1) to full correlation hiding (p=k, space O(|Y|^k)).
6. **Boolean Asymmetry**: AND/OR are exact at the bit level; NOT is approximate (complement non-preservation via pigeonhole). This structural constraint applies to all systems built on this framework.
7. **Confidentiality lives at two scales (do not conflate them)**. The MARGINAL scale measures a single cipher map's leakage by the entropy ratio `e = H(Q)/n` (entropy of the observed cipher-value distribution `Q` over `n` bits, a normalized Shannon-leakage form from QIF), bounded below by Fannes-Audenaert: `e >= 1 - delta - h_2(delta)/n`, linear in `delta`. Small `delta` (Property 2) buys marginal confidentiality; the three levers that lower `delta` are noise injection, multiple representations `K(x) > 1` (homophonic: `K(x) ∝ D(x)`), and joint encoding granularity. The COMPOSITIONAL/ACTIVE scale is governed by DIFFERENT measures that `delta` does NOT control: orbit-closure residual entropy `H(X | view) >= H(X) - log2|orbit_F(c)|` (active adversary with operations), the multi-instance coincidence-oracle accuracy, and shared-variable joint recovery at rate `Θ(|Y1||Y2|/ξ²)`. The canonical definitions, the two-scale framing, and the per-measure ownership table are in `formalism/cipher-map-formalism.md` §4A; see `formalism/cross-paper-consistency.md` for why the old `e = H(X|view)/H*(X)` form was a conflation of the two scales. Papers: marginal `e` in `papers/maximizing-confidentiality/` ("The Entropy Ratio"); orbit closure in `papers/algebraic-cipher-types/`.

## Provenance and Authenticity

**This is critical.** Prior Claude sessions drifted the formalism toward ORAM-style access-pattern indistinguishability, which is NOT this framework's privacy model. Privacy here comes from one-way hash + uniform representation, not access-pattern hiding.

- **Authentic source**: `foundations/` (authentic 2023-2024 blog posts). The historical record. It carries occasional errata, flagged inline (e.g. the inverted homophonic prescription `K(x) ∝ 1/D(x)` in `trapdoor-boolean-algebra.md`, corrected to `K(x) ∝ D(x)`).
- **Canonical spine**: `formalism/cipher-map-formalism.md` is the reconciled source of truth for shared definitions: the cipher-map tuple, the four properties, the composition theorem, the two-scale confidentiality measures (§4A), and the Paper Map plus canonical-notation table (§8). When a paper and the spine disagree on a shared definition, the spine wins. `formalism/DESIGN-trapdoor-reframing.md` holds the four-properties / parameter-decomposition design rationale; `formalism/notation.md` is the conventions guide that defers to the spine's §8 table.
- **Reconciliation report**: `formalism/cross-paper-consistency.md` logs cross-paper drift (notation, bibkeys, measure conflations) with fix status (items C-1 through C-10). Read it before "fixing" an apparent inconsistency: it may already be tracked or deliberately resolved.
- **Full classification**: `ECOSYSTEM-TRIAGE.md` maps every paper/repo as AUTHENTIC, CLAUDE-EXPANDED, MIXED, or DRIFTED
- **Do NOT** import ORAM, differential privacy, simulation-based, or game-based crypto definitions. If you find yourself writing `\Adv`, `\Simulator`, `\Trace`, or `\PPT`, stop. That's the wrong formalism.

## Build Commands

Build systems vary per paper. The legacy 2019-2022 C++ notebook (formerly `papers/algebraic_cipher_types/`, underscore) was archived 2026-04-29 and now lives at `.archive/algebraic_cipher_types-legacy/`; the **paper** at `papers/algebraic-cipher-types/` (hyphen) remains the active artifact. The naming-collision warning is no longer an active concern.

```bash
# cipher-maps paper (top-level Makefile or paper/Makefile)
cd papers/cipher-maps && make
cd papers/cipher-maps/paper && make   # equivalent

# algebraic-cipher-types paper (rewritten 2026; Makefile in paper/)
cd papers/algebraic-cipher-types/paper && make

# maximizing-confidentiality (now titled "The Entropy Ratio";
# Makefile at paper root, main.tex at root)
cd papers/maximizing-confidentiality && make
# also: make quick (single pass), make stats (page/section counts)

# adaptive-trapdoor paper (idea/preliminary; depends on the
# cipher-maps experimental harness for empirical results)
cd papers/adaptive-trapdoor/paper && make

# The remaining papers all follow the paper/Makefile convention.
# cd papers/<name>/paper && make  where <name> is one of:
#   codec-controlled-retrieval  (towell2026codec; construction + experiments companion to cipher-maps)
#   cipher-rekeying             (rekeying via cipher closures)
#   cipher-closures             (cipher data structures + code-data duality; spun out of cipher-rekeying 2026-06)
#   cipher-program-construction (realizing programs as cipher-map compositions; spun out of algebraic-cipher-types 2026-06)

# algebraic_cipher_types-legacy: original 2019-2022 C++ library, ARCHIVED 2026-04-29
# (kept for provenance; do not build, do not edit; see ARCHIVED.md inside)
# cd .archive/algebraic_cipher_types-legacy/src && make   # historical build path

# General fallback (no Makefile)
cd <paper_dir> && pdflatex main.tex && bibtex main && pdflatex main.tex && pdflatex main.tex
```

## Structure

```
trapdoor-computing/
  foundations/          # Authentic 2023-2024 blog posts (source of truth)
  formalism/            # Design docs and formal development
    cipher-map-formalism.md       # RECONCILED CANONICAL SPINE: defs, composition, two-scale measures (§4A), paper map + notation table (§8)
    cross-paper-consistency.md    # Reconciliation report: notation/bibkey drift, measure conflations, fix status (C-1..C-10)
    notation.md                   # Notation conventions guide (defers to spine §8 table)
    DESIGN-trapdoor-reframing.md  # Four properties, parameter decomposition
  papers/               # Git subtrees, each with its own GitHub remote
    cipher-maps/                       # Core cipher-maps paper, QIF-restructured (the hub; towell2026cipher)
    codec-controlled-retrieval/        # towell2026codec: GF(2)-linear ribbon/XOR construction + experiments companion to cipher-maps
    algebraic-cipher-types/            # Algebraic cipher types: type algebra, sum impossibility, orbit closure, cipher Boolean eval
    cipher-program-construction/       # Realizing programs as cipher-map compositions (spun out of algebraic-cipher-types 2026-06-03; scaffold)
    cipher-rekeying/                   # Cipher rekeying via closures (2026-04 draft; closure/data-structure material spun out 2026-06-03)
    cipher-closures/                   # Cipher data structures + the code-data duality (spun out of cipher-rekeying 2026-06-03; scaffold)
    maximizing-confidentiality/        # "The Entropy Ratio", QIF-grounded
    adaptive-trapdoor/                 # Distributional drift / online K(x) retuning (idea/preliminary)
    (boolean-algebra-over-trapdoor-sets retired 2026-06-09: kernels folded into
     cipher-maps §9.4 online construction + algebraic-cipher-types; standalone
     archived to ~/github/archived/, canonical GitHub repo retained)
  src/                  # Shared source artifacts (cipher-maps Python library, nested git repo)
  .archive/             # Snapshots of older drafts and superseded variants
    oblivious-computing-deprecated/    # Pre-July-2024 monorepo with DRIFTED formalism
    algebraic_cipher_types-legacy/     # Original 2019-2022 C++ notebook (archived 2026-04-29)
  SISTER-PAPER-DOIS.md  # Zenodo DOI checklist; closes cipher-maps R8 MAJ-1 (sister-paper "in preparation" citations)
  FUTURE-RESEARCH.md    # Five salient ideas mined from the archived C++ notebook
  ECOSYSTEM-TRIAGE.md   # Classification of all related papers/code
  .papermill/state.md   # Papermill project state (stage, thesis, next actions)
```

**Subtree workflow**: Each paper under `papers/` is a git subtree with its own remote. Remote names are short (`cipher-maps`, `maximizing-confidentiality`, `algebraic-cipher-types`); the directory name uses the long form. (The `boolean-algebra` remote was retired 2026-06-09 when that paper was archived; its GitHub repo remains canonical.) Edit in place and commit normally. Push back: `git subtree push --prefix=papers/<dir> <remote> main`. Pull upstream: `git subtree pull --prefix=papers/<dir> <remote> main --squash`.

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

**Key conceptual link**: A cipher map's correctness parameter eta IS the Bernoulli model's false negative rate (beta) for the hash-based construction. The Bernoulli composition theorem eta_total = 1 - (1-eta_f)(1-eta_g) from `bernoulli_composition/` is Property 4.

The Bernoulli side provides quantitative error theory. The trapdoor side adds cryptographic hiding (one-way hash, trusted/untrusted model, representation uniformity). Bernoulli without trapdoor is approximate computing; trapdoor without Bernoulli has no error model.

### Other Related Repos

- `~/github/cipher-maps/`: Python implementation backing the experimental claims in the papers. Provides PHF-backed cipher maps, the cipher Boolean type (AND/OR/NOT as cipher maps over a partitioned hash space), typed composition chains via `CipherSpace` tags, and end-to-end Boolean search. The 20 Newsgroups benchmarks, FPR-compounding validation, and granularity experiments cited in `cipher-maps` and `maximizing-confidentiality` come from this library.
- `oblivious-computing/`: Legacy monorepo. Foundational papers (F1-F4) and extensions (E1-E2). F2 is DRIFTED (wrong ORAM formalism). Application papers are MIXED.
- `~/github/archived/boolean-algebra-over-trapdoor-sets/`: ARCHIVED 2026-06-09. The trapdoor-set construction (deterministic K=1 Bloom-image set algebra, the equality-channel/plaintext-Boolean leakage regime). Its two load-bearing kernels were folded into the active papers: the generalized-Boolean-algebra characterization into `algebraic-cipher-types` (Remark `rem:trapdoor-set-algebra`), and the K=1 deterministic baseline into `cipher-maps` §9.4 (online construction). Pre-July-2024 commits (up to 549091a) are authentic; the standalone was retired as insufficiently novel on its own (the construction is a single-hash Bloom filter; the contribution was the algebra, now folded).

## Publication Surface

Papers in this repo surface on **metafunctor.com** through the `mf` CLI:

- Series page: `metafunctor.com/series/trapdoor-computing/` lists all papers tagged into the `trapdoor-computing` series, in `series_weight` order (paper_db field).
- Individual paper pages: `metafunctor.com/papers/<slug>/` (e.g., `cipher-maps`, `algebraic-cipher-types`, `max-conf-in-encrypted-search`).
- Lifecycle index: `metafunctor.com/publications/` tracks status (draft, preprint, submitted, etc.).

Workflow: build PDFs locally, then `mf papers ingest <slug>` to refresh Hugo content from the source repo. Note: ingestion strips `series_weight` and `status` from frontmatter (those fields are not in `paper_db.json` schema), so re-add them by hand after ingest. Use `mf series add trapdoor-computing content/papers/<slug>/index.md` to retag.

## Writing Style

Prefer plain English over notation when it's equally precise. Don't define standard concepts (entropy, conditional entropy, TV distance) from scratch. Don't give full type signatures for functions the reader already knows. Lead with the result, not the formalism.

## Author

Alexander Towell <lex@metafunctor.com>
