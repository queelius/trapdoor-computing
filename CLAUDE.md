# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a LaTeX research paper targeting **USENIX Security Symposium**. It presents an information-theoretic framework for analyzing and improving confidentiality in encrypted search systems through entropy optimization.

**Core thesis**: Confidentiality can be measured as the ratio of observed entropy to maximum possible entropy (bounded 0-1), and systematically improved through techniques like homophonic encryption, query injection, and query aggregation.

## Build Commands

```bash
make          # Full build with bibliography (pdflatex × 3 + bibtex)
make quick    # Single-pass build for testing
make view     # Build and open PDF
make clean    # Remove auxiliary files (keep PDF)
make cleanall # Remove all generated files including PDF
make stats    # Show paper statistics (pages, sections, theorems, etc.)
```

## Repository Structure

- `main.tex` - Complete paper source (~2,800 lines, all content inline)
- `references.bib` - Bibliography (40 entries)
- `data/` - Plot data files for pgfplots figures
- `img/` - TikZ figures (.tex source and .pdf outputs)

## Paper Structure (15 sections)

1. Introduction → Related Work → Encrypted Search Model
2. **Core Theory**: Probabilistic Model → Entropy and Information → Maximum Entropy System → Maximum Entropy Under Constraints
3. **Applications**: Increasing Entropy → Case Study (59% → 85% efficiency)
4. **Appendices**: Entropy Derivations, Compression-Based Estimation, Maximum Entropy Optimization, Hypothesis Testing, Notation Reference

## LaTeX Conventions

The paper uses extensive custom macros for random variable notation. Key patterns:
- `\rv{X}` - Random variable styling
- `\qb`, `\rvqb` - Query batch notation (observed/random)
- `\hqb`, `\rvhqb` - Hidden query batch (hat-check notation)
- `\rs`, `\rvrs` - Result set notation
- Similar pattern for `\ts` (timestamps), `\sa` (search activities), `\tup` (tuples)

Uses `algorithm2e` for pseudocode, `pgfplots` for data visualization, and `tikz` for diagrams.

## Part of Larger Research

This paper is part of the oblivious-computing monorepo. Related work in sibling directories covers Bernoulli types, algebraic cipher types, and other encrypted search approaches. See parent `CLAUDE.md` for monorepo context.
