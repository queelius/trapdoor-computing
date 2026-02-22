# Design Doc: Reframing Cipher Maps as Trapdoor Computing

**Date**: 2026-02-22
**Status**: Approved for implementation
**Scope**: cipher_maps_unified paper

## Motivation

The papermill review (Review 2) identified "obliviousness is not formally defined" as the most consequential gap blocking submission. Rather than importing a standard definition (ORAM-style access-pattern indistinguishability), we reexamined what the cipher maps framework actually provides and concluded it's a distinct notion that deserves its own name and formalization.

The word "oblivious" carries baggage from ORAM, oblivious transfer, and data-oblivious algorithms — all of which describe different guarantees than what cipher maps provide. We're renaming the paradigm to **trapdoor computing**.

## Key Insight: Cipher Maps Are Total Functions

The fundamental reframing: a cipher map is a **total function on bit strings**. It has no concept of "in-domain" vs "out-of-domain." Every input produces output.

```
bits in  -->  [cipher map]  -->  bits out
```

The concepts of "domain," "false positive," and "false negative" only exist on the **trusted machine** that holds the decoder (the trapdoor). The **untrusted machine** sees only opaque bit strings flowing through opaque lookup tables. It cannot distinguish:
- A meaningful query from a noise/filler query
- A correct result from a noise result
- A real cipher value from a random bit string

## The Trusted / Untrusted Machine Model

```
Trusted Machine (T)              Untrusted Machine (U)
holds: decoder d, hash key       holds: cipher maps {f_i}, cipher values
can: encode, decode, inject      can: evaluate cipher maps, return results
      noise, verify results      cannot: decode values, distinguish signal
                                          from noise, enumerate domains
```

- T encodes plaintext values into cipher values (with representation multiplicity)
- T sends cipher values to U (mixed with noise/filler — U can't tell)
- U applies cipher maps: bits in -> bits out (total function, always produces output)
- U returns cipher results to T
- T decodes results it cares about, ignores the rest

## Four Properties of a Trapdoor Cipher Map

A cipher map f-hat: {0,1}^m -> {0,1}^m implementing a latent function f: X -> Y satisfies:

### 1. Totality
f-hat is defined on ALL inputs. It is simply a hash-based function: bits in, bits out. For inputs not encoding any x in X, the output is computationally indistinguishable from uniform random bits under the random oracle model.

Note: noise does NOT necessarily stay noise through composition. Random output from one cipher map has probability epsilon of being a valid codeword for the next map. We do not try to control noise output — the cipher map is just a cryptographic hash. This is a feature: valid-looking outputs don't prove valid inputs, which is exactly what makes signal indistinguishable from noise to the untrusted machine.

**Why it matters**: If out-of-domain queries returned "error" or null, the untrusted machine could distinguish real from filler queries. Totality ensures the untrusted machine learns nothing from the mere act of evaluation.

### 2. Representation Uniformity
For each x in X, there exist multiple encodings encode(x, k) for k = 0, ..., K-1. The distribution of encode(x, k) over random k is delta-close to uniform over the codomain.

**Why it matters**: This is homophonic substitution — frequent values get more representations to prevent frequency analysis. The untrusted machine observing cipher values in transit cannot perform frequency attacks because all values appear with roughly equal probability.

### 3. Correctness (eta-bounded)
For x in X with encoding c = encode(x, k), decode(f-hat(c)) = f(x) with probability at least 1 - eta.

**Why it matters**: eta is the only parameter that affects the trusted machine's correctness guarantee. eta > 0 is a construction trade-off: tolerating some incorrectly-encoded elements makes the seed search faster and the structure smaller.

### 4. Composability
For cipher maps f-hat, g-hat with correctness parameters eta_f, eta_g, the composition g-hat . f-hat has correctness parameter:

    eta_total = eta_f + eta_g - eta_f * eta_g = 1 - (1 - eta_f)(1 - eta_g)

Noise closure means each map is total: noise input produces random output. With probability epsilon, that random output happens to be a valid codeword (noise "becomes" signal). We do not control noise output — the cipher map is just a hash.

**Why it matters**: This enables building complex trapdoor computations (AND/OR/NOT, arithmetic, branching, whole programs) by composing simple cipher maps. The error accumulates predictably. Noise stays noise through any number of compositions.

## Parameter Decomposition

The old framing used "false positive rate epsilon" and "false negative rate eta" — terminology from Bloom filters that doesn't fit. The new decomposition:

| Parameter | Controls | Affects |
|-----------|----------|---------|
| **eta** | Correctness — fraction of in-domain elements with wrong answers | Trusted machine |
| **mu** | Value encoding cost — bits per element for function values (= H(Y)) | Space |
| **epsilon** | Noise decode probability — probability random bits form a valid codeword | Space budget |
| **\|c_A S\|/\|S\|** | Representation multiplicity — frequency equalization | Adversary observing traffic |
| **delta** | Representation uniformity — closeness to uniform distribution | Adversary with partial knowledge |

### epsilon reframed

epsilon is NOT a "false positive rate" in the Bloom filter sense (the structure never says "yes" or "no"). epsilon is:
1. A **space parameter**: each stored element costs -log_2(epsilon) + mu bits
2. A **noise property**: the probability that random bits decode to a valid codeword
3. Only relevant if someone (adversary with partial decoder access, or diagnostic) tries to decode noise

The trusted machine never decodes noise (it knows which queries are real). The untrusted machine can't decode anything. So epsilon's primary role is determining space, not "false positive" behavior.

### eta reframed

eta IS about correctness, but it's a construction parameter (how many constraints the seed must satisfy), not a runtime error rate. Once the cipher map is built, the eta fraction of elements that fail are deterministic — the same elements always fail for a given seed.

## What This Replaces

The current paper (Def 4.1) defines obliviousness via three informal bullets:
- "Mappings only revealed through direct evaluation"
- "Domain cannot be efficiently enumerated"
- "Unmapped inputs behave as random oracles"

These are replaced by the four formal properties above. The informal bullets are approximately captured by:
- Bullet 1 -> Property 2 (representation uniformity) + the trapdoor model
- Bullet 2 -> Property 1 (noise closure) — you can't enumerate the domain because every query returns something
- Bullet 3 -> Property 1 (noise closure) — out-of-domain inputs produce noise indistinguishable from valid output

## Naming Decisions

- **The paradigm**: "trapdoor computing" (replaces "oblivious computing" in this paper)
- **The construction**: "cipher maps" (stays — it's the paper's central object)
- **The property**: defined formally by the four properties above (no single buzzword)
- **ORAM reference**: Keep as related work, acknowledge the distinction explicitly

## Relationship to Standard Crypto Notions

| Standard Notion | How Cipher Maps Relate |
|----------------|----------------------|
| **ORAM** | Both hide access patterns, but ORAM reshuffles storage; cipher maps use static total functions with noise injection |
| **FHE** | Both enable computation on encrypted data, but FHE preserves exact algebraic structure; cipher maps use approximation and hash-based tables |
| **Garbled circuits** | Most similar — both use encrypted lookup tables. But garbled circuits are one-time use and exact; cipher maps are reusable and approximate. Cipher maps have noise closure; garbled circuits don't. |
| **Semantic security** | Representation uniformity is similar to IND-CPA, but parameterized by delta rather than negligible |
| **Trapdoor functions** | The decoder IS a trapdoor — easy to evaluate cipher maps, hard to invert without the decoder |

## Scope of Changes

### Title
Old: "Cipher Maps: A Unified Framework for Oblivious Function Approximation Through Algebraic Structures and Bernoulli Models"
New: "Cipher Maps: A Framework for Trapdoor Computing Through Algebraic Structures and Bernoulli Models"

### Abstract
- Replace "oblivious function approximation" -> "trapdoor function approximation"
- Replace "obliviousness conditions" -> reference to four formal properties
- Add brief mention of trusted/untrusted model
- Keep the space bound (-log_2 epsilon + mu) — the math doesn't change

### Section 4 (major rewrite)
- Add subsection on trusted/untrusted machine model
- Replace Def 4.1 with formal four-property definition
- Reframe Thm 4.1 (Cipher-Bernoulli Correspondence) in trapdoor language
- Replace Prop 4.2 with formal statement using representation uniformity

### Section 7
- Rename "Bernoulli Obliviousness" theorem -> "Bernoulli Trapdoor Properties" or similar
- Restate against the four-property definition

### Sections 1, 5, 6, 8, 9, 10, Appendices
- Replace "oblivious" with "trapdoor" where referring to the paradigm
- Keep "oblivious" where citing ORAM or standard terms
- Reframe "false positive rate epsilon" narrative in Section 6

### What does NOT change
- The mathematical results (theorems, proofs, bounds)
- The Singular Hash Map construction (Algorithm 1)
- The composition theorem (Thm 7.5)
- The space complexity analysis (Section 6)
- The cipher functor definition (Section 2)
- The Bernoulli model (Section 3, except Thm 3.5 which is separately broken)

## The Broader Vision (from discussion)

Trapdoor computing enables:
- Composing cipher maps for AND/OR/NOT, math ops, if/else, branching, whole programs
- Space trade-off: a single cipher map for an entire program is ideal but impractical; compose smaller ones
- Noise injection + filler queries as active defense (other papers may develop this further)
- Fast evaluation (hash lookups), reasonable construction time, reseedable when leakage accumulates
- At any granularity: bools, pairs, tuples, higher-level objects

The encrypted search scenario:
1. Trusted machine encodes query as cipher bigrams + filler
2. Untrusted machine applies cipher search functions (can't distinguish real from filler)
3. Results flow back as cipher bools — some from real queries, some from noise (but noise may have randomly produced valid-looking cipher bools too)
4. Trusted machine decodes only the results it cares about

The untrusted machine sees: opaque bits through opaque tables producing opaque bits. It cannot distinguish signal from noise at any point in the pipeline.
