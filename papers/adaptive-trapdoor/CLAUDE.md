# CLAUDE.md (adaptive-trapdoor)

## What this paper is

A follow-on to "The Entropy Ratio" (`papers/maximizing-confidentiality/`).
That paper develops a static confidentiality theory: $\delta$ is a
fixed property of an allocation $K(x)$ over a fixed distribution $D$.

This paper makes confidentiality dynamic: $D$ drifts, $K$ must adapt,
and the question is how fast and at what cost.

## Status

Stage: idea. Preliminary experiments live in
`~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py`
with results in `notes/preliminary-results.md`.

## What this paper is NOT

- It is not about secret rotation. That is `papers/cipher-rekeying/`.
- It is not about confidentiality measurement (covered by the
  Entropy Ratio paper, including the finite-sample subsection).
- It is not about general adversarial adaptation. The threat model
  is honest-but-curious untrusted machine plus naturally drifting D,
  not active drift induced by an adversary.

## Sibling papers and load order

- `papers/cipher-maps/`: framework definition.
- `papers/algebraic-cipher-types/`: type constructors and orbit closure.
- `papers/maximizing-confidentiality/`: static confidentiality theory.
- `papers/cipher-rekeying/`: secret rotation.
- This paper: distributional adaptation.

A reader needs the Entropy Ratio paper as background; the others are
not strict prerequisites.

## Build

```bash
cd paper && make
```

Standard pdflatex+bibtex+pdflatex+pdflatex chain.
