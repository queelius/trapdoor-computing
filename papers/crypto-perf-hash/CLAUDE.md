# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LaTeX academic paper: "Cryptographic perfect hash functions: A theoretical analysis on space efficiency and algebraic composition" by Alexander Towell.

Analyzes cryptographic perfect hash functions with: (1) cryptographic hash function properties, (2) theoretical lower-bound space complexity, (3) maximum entropy in-place encoding.

## Repository Structure

```
paper/              # Main paper sources
  paper.tex         # LaTeX source
  references.bib    # BibTeX bibliography
  paper.pdf         # Compiled output
  html/             # HTML export
img/                # Generated figures (PDF, EPS, TEX)
research/           # Mathematica notebooks (.nb) for derivations and plots
archive/            # Previous versions
```

## Building the Paper

```bash
cd paper
latexmk -pdf paper.tex
```

Or manually:
```bash
cd paper
pdflatex paper.tex && bibtex paper && pdflatex paper.tex && pdflatex paper.tex
```

## Custom LaTeX Macros

Key commands defined in `paper/paper.tex`:
- `\Fun{name}` - Function notation
- `\PH`, `\ph` - Perfect hash data type and constructor
- `\Expect{X}` - Expectation operator
- `\BL` - Bit length function
- `\cat` - Concatenation operator (#)
- Theorem environments: `theorem`, `corollary`, `definition`, `postulate`, `conjecture`, `example`, `remark`

## Paper Structure

1. **Section 1**: Prior Art
2. **Section 2**: Perfect hash function fundamentals
3. **Section 3**: Cryptographic perfect hash functions using random oracles (Algorithm 1)
4. **Section 4**: Two-level practical perfect hash functions (Algorithm 2)
5. **Section 5**: Algebra of function composition
6. **Appendix**: Probability mass of random bit length (Algorithm 3)

Key result: Expected space complexity is log₂(e) - (1/r - 1)log₂(1/(1-r)) bits/element, achieving 1.44 bits/element for minimal perfect hash (r=1).

## Research Materials

The `research/` directory contains Mathematica notebooks for mathematical derivations and plot generation. Plots are exported to `img/` for paper inclusion.
