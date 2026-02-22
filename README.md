# Trapdoor Computing

A paradigm for computing with values whose meaning is hidden behind a one-way trapdoor.

## The Idea

A **cipher map** is a total function on bit strings. Every input produces output. The concepts of "domain," "correct," and "incorrect" only exist on the **trusted machine** that holds the decoder. The **untrusted machine** sees only opaque bits flowing through opaque lookup tables — it cannot distinguish signal from noise.

## Foundations

The `foundations/` directory contains the authentic source documents (2023-2024) that define the framework:

- **bernoulli-model.md** — The Bernoulli Model: latent/observed duality, confusion matrices, HashSet construction achieving `-log_2(epsilon)` bits per element
- **noisy-gates.md** — Noisy Turing Machines: composing Bernoulli logic gates, interval arithmetic for error propagation through circuits
- **trapdoor-boolean-algebra.md** — Boolean Algebra Over Trapdoors: approximate homomorphism from powerset to bit strings via cryptographic hash, marginal uniformity
- **entropy-maps.md** — Entropy Maps: prefix-free hash codes for function approximation, mu = H(Y) space bound, two-level hash construction

## Four Properties of a Cipher Map

A cipher map f-hat implementing a latent function f satisfies:

1. **Totality** — f-hat is defined on all inputs (bits in, bits out). Out-of-domain inputs produce random output. With probability epsilon, random output happens to be a valid codeword.
2. **Representation Uniformity** — Each domain value has multiple encodings. The distribution over encodings is delta-close to uniform, preventing frequency analysis.
3. **Correctness** — For in-domain inputs, decode(f-hat(encode(x))) = f(x) with probability at least 1 - eta.
4. **Composability** — Composing cipher maps compounds error predictably: eta_total = 1 - (1 - eta_f)(1 - eta_g).

## Author

Alexander Towell — [metafunctor.com](https://metafunctor.com)
