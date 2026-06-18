# Cipher Map Formalism

**Date**: 2026-06-02 (reconciled with the paper family; supersedes the 2026-03-08 draft)
**Status**: Canonical source of truth for shared definitions
**Prerequisite**: `DESIGN-trapdoor-reframing.md` (four properties, parameter decomposition)
**Authentic source**: Four blog posts in `foundations/` (2023--2024)
**Reconciliation report**: `cross-paper-consistency.md` (notation drift, bibkey fixes, measure conflations)

This document is the shared spine for the trapdoor-computing paper family. It gives precise definitions for the four properties of a cipher map, instantiates them against the three concrete constructions from the blog posts, derives the composition theorem, formalizes the trusted/untrusted machine model, and (Section 4A) fixes the canonical confidentiality measures the papers build on. Where a result is owned by one paper (acceptance predicates, the coincidence oracle, sum-type impossibility, rekeying), the spine names it and points to the owner; see the Paper Map in Section 8. When a paper and this document disagree on a shared definition, this document is authoritative, and the disagreement is logged in the reconciliation report.

---

## 1. The Cipher Map Abstraction

### 1.1 Setting

Let $f : X \to Y$ be a **latent function** — a function whose domain, codomain, and mapping are known only to a trusted party. A **cipher map** is a concrete object that allows an untrusted party to *evaluate* an approximation of $f$ without learning $f$, $X$, or $Y$.

**Definition 1.1** (Cipher map).
A cipher map for a latent function $f : X \to Y$ is a tuple $(\hat{f}, \mathrm{enc}, \mathrm{dec}, s)$ where:

- $\hat{f} : \{0,1\}^n \to \{0,1\}^n$ is a **total function** on $n$-bit strings,
- $\mathrm{enc} : X \times \{0, \ldots, K-1\} \to \{0,1\}^n$ is an encoding function,
- $\mathrm{dec} : \{0,1\}^n \to Y \cup \{\bot\}$ is a decoding function,
- $s$ is a secret (the trapdoor), from which $\hat{f}$, $\mathrm{enc}$, and $\mathrm{dec}$ are derived.

The untrusted machine holds $\hat{f}$. The trusted machine holds $\mathrm{enc}$, $\mathrm{dec}$, and $s$.

**Two construction strategies.** Cipher maps can be built in fundamentally different ways:

- **Batch construction.** The trusted machine invests computation upfront to find $s$ such that $\hat{f}$ satisfies correctness constraints for all $x \in X$ simultaneously (seed search). This gives tunable $\eta$ and optimal space, but requires knowing $X$ and $f$ at construction time. Examples: HashSet, entropy map.

- **Online construction.** The cipher map $\hat{f}$ is defined directly by the hash structure — no seed search is needed. $s$ is a hash key, not a searched seed. Operations are limited to those the hash structure supports algebraically (e.g., set union, intersection). Space and accuracy trade-offs are fixed by the hash width $n$. Example: trapdoor boolean algebra.

Both strategies produce objects satisfying Definition 1.1. They differ in construction cost, supported operations, and parameter trade-offs (see §2.4).

**Remark (values as constant functions).** A cipher value $\mathrm{enc}(v, k)$ can be viewed as a cipher map for the constant function $f_v(x) = v$ for all $x$. Under this view, the type of cipher values and the type of cipher maps are the same — a cipher map from a trivial domain. This simplifies the trusted/untrusted model (§5): the untrusted machine deals with a single kind of object (total functions on bit strings), some of which happen to be constant.

**Notation.** Throughout, $h : \{0,1\}^* \to \{0,1\}^n$ denotes a cryptographic hash modeled as a random oracle.


### 1.2 Construction Layers

The four properties arise from three orthogonal type transformations. These were identified in earlier design work (algebraic cipher types, 2019) and provide the conceptual scaffolding for why each property exists.

**Layer 1: Undefined injection** (`undef`).
Extend the domain $X$ to $X \cup \{\bot_1, \ldots, \bot_N\}$ by adding $N$ undefined elements. A function $f : X \to Y$ lifts to a partial function $\tilde{f} : X \cup \{\bot_i\} \rightharpoonup Y$ that is undefined on the $\bot_i$. This dilutes the domain: real elements are a fraction $|X| / (|X| + N)$ of the extended type.

- **What it buys**: Filler queries become structurally identical to real queries — both are elements of the extended type. The parameter $\varepsilon \approx |X| / (|X| + N)$ controls the dilution ratio.
- **Maps to**: The space parameter $\varepsilon$ (noise decode probability).

**Layer 2: Noise closure** (`noise`).
Lift a partial function $\tilde{f} : X' \rightharpoonup Y'$ to a total function $\hat{f} : X' \to Y'$ by mapping undefined inputs to random outputs (via cryptographic hash).

- **What it buys**: The untrusted machine cannot distinguish real from undefined inputs — both produce output. No "not found" or error signals.
- **Maps to**: **Property 1 (Totality)**.

**Layer 3: Multiple representations** (`cipher`).
Replace each value $x$ with $K(x) \geq 1$ distinct representations, keyed by a secret $S$. Representational equality implies value equality, but value equality does not imply representational equality.

- **What it buys**: Frequency equalization — frequent values get more representations so all cipher values appear with roughly equal probability. Without the secret, an adversary cannot determine which representations encode the same value.
- **Maps to**: **Property 2 (Representation Uniformity)**.

**The combined type.** Applying all three layers gives $\mathrm{cipher}(\mathrm{noise}(\mathrm{undef}(X)))$ — an element with multiple representations, total evaluation, and diluted domain. This is a cipher map.

**Important caveat.** We present these as *conceptual layers*, not algebraic monads. Whether the layers satisfy formal monad laws (associativity of bind, unit laws) in the approximate setting is an open question that we do not need to resolve. The decomposition is valuable for understanding *why* each property exists, regardless of whether the layers compose with strict algebraic regularity.

**Property 3 (Correctness, $\eta$-bounded)** and **Property 4 (Composability)** are not associated with a single layer — they are emergent properties of how a cipher map is *constructed* and *composed*. Correctness depends on the seed search (batch) or hash structure (online). Composability depends on the totality guarantee enabling chained evaluation.


### 1.3 Four Properties

A cipher map $(\hat{f}, \mathrm{enc}, \mathrm{dec}, s)$ for $f : X \to Y$ is characterized by four properties parameterized by $(\eta, \varepsilon, \mu, \delta)$.


#### Property 1: Totality

$\hat{f}$ is defined on all $2^n$ inputs. For inputs $c \notin \mathrm{Im}(\mathrm{enc})$ (i.e., bit strings not encoding any $x \in X$), the output $\hat{f}(c)$ is computationally indistinguishable from a uniform random $n$-bit string under the random oracle model.

**Formally.** For all $c \in \{0,1\}^n$:
$$\hat{f}(c) \in \{0,1\}^n$$
and for $c$ chosen uniformly at random from $\{0,1\}^n \setminus \mathrm{Im}(\mathrm{enc})$, the distribution of $\hat{f}(c)$ is uniform over $\{0,1\}^n$ under the random oracle model. (In the ROM, the hash output is truly uniform, not merely computationally indistinguishable from uniform.)

**Consequence.** The untrusted machine cannot distinguish a real query $\mathrm{enc}(x, k)$ from a random filler string $c \gets \{0,1\}^n$, because both produce $n$-bit outputs.


#### Property 2: Representation Uniformity ($\delta$-bounded)

For each $x \in X$, there are $K(x) \geq 1$ valid encodings. The marginal distribution of a random encoding, taken over a random $x \sim D$ and random representation index $k$, is $\delta$-close to uniform on the populated support $\mathrm{Im}(\mathrm{enc})$.

**Formally.** Let $D$ be a distribution on $X$. Define the induced distribution on cipher values:
$$Q(c) = \sum_{x \in X} D(x) \cdot \frac{|\{k : \mathrm{enc}(x,k) = c\}|}{K(x)}$$

Representation uniformity requires:
$$d_{\mathrm{TV}}(Q, \mathrm{Uniform}(\mathrm{Im}(\mathrm{enc}))) \leq \delta,
\qquad H^* = \log_2 \lvert \mathrm{Im}(\mathrm{enc}) \rvert$$

where $d_{\mathrm{TV}}$ denotes total variation distance, and the reference is the uniform distribution on the **populated support** $\mathrm{Im}(\mathrm{enc})$, with maximum entropy $H^* = \log_2\lvert\mathrm{Im}(\mathrm{enc})\rvert$, *not* the ambient $\{0,1\}^n$. (See `cross-paper-consistency.md`, item C-11: an ambient reference is unsatisfiable for sparse images, since any realizable $Q$ then sits at total variation $\approx 1$ from uniform over all of $\{0,1\}^n$. The construction principle below, the confidentiality paper, and the monograph use the image-relative form; this document now matches.)

**Construction principle.** To achieve small $\delta$, assign $K(x) \propto D(x)$ encodings per value, so that frequent values get *more* representations (classical homophonic substitution; Simmons 1979). Setting $K(x) = \lceil c \cdot D(x) \rceil$ for a normalizing constant $c$ flattens the per-cipher-value probability $D(x)/K(x)$ toward a constant. The homophonic-allocation identity (Cipher Maps Prop. 4.1) gives the exact $d_{\mathrm{TV}}(Q, \mathrm{Uniform}(\mathrm{Im}(\mathrm{enc}))) = d_{\mathrm{TV}}(D, K/N)$ with $N = \sum_x K(x)$, bounded by the tight $(|X|-1)/N$. The total budget is $\sum_x K(x) \approx c$, so concentrating multiplicity on the heavy part of $D$ is far cheaper than spreading it over the tail. (See `cross-paper-consistency.md`, item C-1: an earlier version of this document, and the trapdoor-boolean-algebra appendix it quoted, stated the prescription as $K(x) \propto 1/D(x)$, which is inverted and self-contradictory. The papers carry the corrected $K(x) \propto D(x)$; this document now matches.)

**Honest limitation.** $\delta$ bounds the *marginal* distribution of cipher values. It says nothing about *joint* distributions — see Section 4 for encoding granularity.


#### Property 3: Correctness ($\eta$-bounded)

For in-domain elements, the cipher map computes $f$ correctly with probability at least $1 - \eta$.

**Formally.** For $x$ chosen uniformly from $X$ and $k$ chosen uniformly from $\{0, \ldots, K(x)-1\}$:
$$\Pr_{x, k}\bigl[\mathrm{dec}(\hat{f}(\mathrm{enc}(x, k))) \neq f(x)\bigr] \leq \eta$$

**Notes.**
- $\eta$ is a **construction parameter**: it reflects how many constraints the seed $s$ must satisfy. Tolerating $\eta > 0$ makes the seed search faster and the structure smaller.
- Once built, the failing elements are deterministic for a given seed — the same elements always fail.
- $\eta$ only affects the trusted machine's guarantee. The untrusted machine never decodes.

**Remark (Approximation as privacy).** Nonzero $\eta$ is not purely a construction cost — it also provides privacy. A false positive creates *plausible deniability*: the untrusted machine cannot distinguish "element is in the set" from "cipher map erred." With $\eta = 0$, the answer is deterministic and the adversary learns the exact truth. With $\eta > 0$, each answer carries ambiguity. This is the dual of representation uniformity: Property 2 hides *which* value was queried; nonzero $\eta$ hides *what the answer means*.


#### Property 4: Composability

For cipher maps $\hat{f}$ and $\hat{g}$ with correctness parameters $\eta_f$ and $\eta_g$ respectively, the composition $\hat{g} \circ \hat{f}$ has correctness parameter:
$$\eta_{g \circ f} \leq 1 - (1 - \eta_f)(1 - \eta_g) = \eta_f + \eta_g - \eta_f \cdot \eta_g$$

**Formally.** Let $\hat{f}$ be a cipher map for $f : X \to Y$ with parameter $\eta_f$, and $\hat{g}$ a cipher map for $g : Y \to Z$ with parameter $\eta_g$. Define $\hat{g} \circ \hat{f} : \{0,1\}^n \to \{0,1\}^n$ by $(\hat{g} \circ \hat{f})(c) = \hat{g}(\hat{f}(c))$. Then $\hat{g} \circ \hat{f}$ is a cipher map for $g \circ f$ with:
$$\Pr_{x,k}\bigl[\mathrm{dec}_{g \circ f}((\hat{g} \circ \hat{f})(\mathrm{enc}(x,k))) \neq g(f(x))\bigr] \leq \eta_f + \eta_g - \eta_f \eta_g$$

**Derivation.** See Section 3.

**Noise behavior under composition.** Noise input to $\hat{f}$ produces random output (by totality). With probability $\varepsilon$, that random output happens to be a valid codeword for $\hat{g}$. We do not try to control noise output — the cipher map is just a hash. This is a feature: valid-looking outputs do not prove valid inputs.


### 1.4 Parameter Decomposition

| Parameter | Type | Range | Controls | Determined by |
|-----------|------|-------|----------|---------------|
| $\eta$ | Correctness | $[0, 1)$ | Fraction of in-domain elements with wrong answers | Construction (seed search constraints) |
| $\varepsilon$ | Noise decode | $(0, 1)$ | Probability random bits form a valid codeword | Encoding scheme (prefix-free code allocation) |
| $\mu$ | Value cost | $(0, \infty)$ | Bits per element for function values | $\mu = H(Y)$ where $Y$ is output distribution |
| $\delta$ | Uniformity | $[0, 1]$ | TV distance from uniform over cipher values | Representation multiplicity $K(x)$ |
| $K(x)$ | Multiplicity | $\{1, 2, \ldots\}$ | Number of encodings per domain element | Set to $\propto D(x)$ for small $\delta$ (homophonic) |
| $p$ | Entanglement | $\{1, \ldots, k\}$ | Number of values encoded as a single unit | Application privacy requirements (§4.3) |

**Space per element:**
$$\text{bits/element} = -\log_2 \varepsilon + \mu = -\log_2 \varepsilon + H(Y)$$

This is information-theoretic: $-\log_2 \varepsilon$ bits to distinguish signal from noise, plus $H(Y)$ bits to encode the function value.


---

## 1A. Bernoulli Foundation

The cipher map abstraction rests on the Bernoulli model developed in a separate paper family (`bernoulli_sets`, `bernoulli_composition`, `bernoulli_maps`). This section makes the dependency explicit.

### 1A.1 The Two Axioms and Kronecker Factorization

The Bernoulli model is built on two axioms:

1. **Element-wise independence (Axiom 1).** For distinct elements $x_i, x_j \in X$, the errors $\mathbf{1}[\hat{f}(\mathrm{enc}(x_i)) \text{ incorrect}]$ and $\mathbf{1}[\hat{f}(\mathrm{enc}(x_j)) \text{ incorrect}]$ are independent Bernoulli random variables.

2. **Conditional independence of block error rates (Axiom 2).** Conditioned on the error rate parameter $\eta$, the per-element error indicators are i.i.d. Bernoulli($\eta$).

These axioms are what make cipher map composition *tractable*. Without them, a joint confusion matrix for $m$ elements in an $n$-th order model has $n(2^m - 1)$ free parameters, exponential in the number of elements.

**Theorem (Kronecker factorization, from `bernoulli_sets`).** Under Axioms 1 and 2, the joint confusion matrix for $m$ independent Bernoulli tests factors as the tensor product of per-element channels:
$$C_{\text{joint}} = C_1 \otimes C_2 \otimes \cdots \otimes C_m$$
where each $C_i$ is a $2 \times 2$ confusion matrix with at most 2 free parameters ($\eta_i, \varepsilon_i$). The total parameter count reduces from $n(2^m - 1)$ to at most $2m$.

**Consequence for cipher maps.** This factorization is the reason that correctness composes multiplicatively: the probability that a chain of $m$ cipher maps is correct equals $\prod_{i=1}^m (1 - \eta_i)$, because each map's error is independent. Without element-wise independence, the composition theorem (§3) would require tracking exponentially many joint failure modes.

### 1A.2 Parameter Correspondence

The cipher map parameters are not independent inventions; they are the Bernoulli model parameters under different names.

| Cipher map parameter | Bernoulli model source | Paper |
|---|---|---|
| $\eta$ (correctness) | $\beta$ (FNR) for batch constructions; the false negative rate of the Bernoulli set/map | `bernoulli_sets` |
| $\varepsilon$ (noise decode) | $\alpha$ (FPR); the false positive rate governing space via $-\log_2 \alpha$ bits/element | `bernoulli_sets`, `bernoulli_entropy` |
| $\mu = H(Y)$ (value cost) | Shannon entropy of the output distribution; the information-theoretic cost per element beyond the noise budget | `bernoulli_entropy`, `bernoulli_maps` |
| $\eta_{\text{total}} = 1 - \prod(1-\eta_i)$ | Composition closure theorem for Bernoulli set operations | `bernoulli_composition` |

For batch constructions (HashSet, entropy map), $\eta$ IS the Bernoulli FNR ($\beta$): the fraction of in-domain elements whose hash does not land in the correct codeword region. The space formula $-\log_2 \varepsilon + H(Y)$ is derived in `bernoulli_entropy` as the information-theoretic lower bound and achieved by the Bernoulli hash function construction.

### 1A.3 The Two Ecosystems

The Bernoulli model and trapdoor computing are complementary halves of a single framework:

- **Bernoulli provides the error theory.** How errors arise (hash collisions), how they propagate (composition theorem), how they trade against space ($-\log_2 \varepsilon + \mu$), and how they decompose (Kronecker factorization). This is the *accuracy* axis.

- **Trapdoor adds the hiding theory.** Why the untrusted machine cannot decode (one-way hash), why all queries look alike (totality + representation uniformity), and why composition preserves hiding (noise closure). This is the *confidentiality* axis.

Neither is complete without the other. A Bernoulli set without trapdoor hiding is a Bloom filter: space-efficient but not private. A trapdoor construction without Bernoulli error analysis has no quantitative correctness guarantees.

The layered type hierarchy from `bernoulli_maps` ($\mathrm{Bool} \to \mathrm{Set} \to \mathrm{Map} \to \mathrm{Relation} \to \mathrm{Type}$) maps directly to increasingly complex cipher map constructions:

| Bernoulli layer | Cipher map construction | Example |
|---|---|---|
| $B_{\mathrm{bool}}$ (Bernoulli Boolean) | Cipher membership predicate | HashSet: $\hat{f}(c) \in \{0^n, \text{other}\}$ |
| $B_{X \to \mathrm{bool}}$ (Bernoulli set) | Cipher set (multiple predicates) | Trapdoor boolean algebra: $F(A) = h(x_1) \mathbin{|} \cdots \mathbin{|} h(x_k)$ |
| $B_{X \to Y}$ (Bernoulli map) | Cipher map (general function) | Entropy map: prefix-free hash codes |
| $B_{X \times Y \to \mathrm{bool}}$ (Bernoulli relation) | Cipher relation | Cipher join/project (future work) |


---

## 2. Concrete Constructions

We instantiate the cipher map abstraction against three constructions from the blog posts. For each, we identify which properties are satisfied and with what parameter values.


### 2.1 HashSet (from `bernoulli-model.md` §HashSet)

**Latent function.** Set membership indicator: $f = \mathbf{1}_A : X \to \{0,1\}$ where $A \subseteq X$.

**Construction.** Choose a seed $s$ such that:
$$h(x \| s) = 0^n \quad \text{for all } x \in A$$

Membership test: declare $x \in A$ if and only if $h(x \| s) = 0^n$.

**Mapping to cipher map abstraction.**
- $\hat{f}(c) = h(c \| s)$, a total function on all bit strings (hash always produces output).
- $\mathrm{enc}(x, 0) = x$ (single encoding per element; $K(x) = 1$ for all $x$).
- $\mathrm{dec}(r) = \begin{cases} 1 & \text{if } r = 0^n \\ 0 & \text{otherwise} \end{cases}$

**Parameter instantiation.**

| Parameter | Value | Justification |
|-----------|-------|---------------|
| $\eta$ | $0$ | All members satisfy $h(x \| s) = 0^n$ by construction (zero false negatives) |
| $\varepsilon$ | $2^{-n}$ | Random $c$ satisfies $h(c \| s) = 0^n$ with probability $2^{-n}$ under ROM |
| $\mu$ | $\leq 1$ | Binary output; $H(Y) = -p\log_2 p - (1-p)\log_2(1-p)$ where $p = |A|/|X|$ |
| $\delta$ | N/A | Single encoding per element ($K(x) = 1$); no representation uniformity |
| Space | $n = -\log_2 \varepsilon$ bits/element | Information-theoretic lower bound for membership |

**Property checklist.**

| Property | Status | Notes |
|----------|--------|-------|
| Totality | **Yes** | $h(c \| s)$ is defined for all $c \in \{0,1\}^*$ |
| Representation Uniformity | **No** | $K(x) = 1$; cipher values are just domain elements, frequency attacks possible |
| Correctness | **Yes** ($\eta = 0$) | Zero false negatives; construction guarantees all members hash to $0^n$ |
| Composability | **Yes** | Intersection of HashSets: $x \in A \cap B$ iff $h(x\|s_A) = 0^n$ AND $h(x\|s_B) = 0^n$ |

**Note.** The HashSet is a cipher map with perfect correctness but no representation uniformity. It demonstrates that the four properties are independent — a construction can satisfy some without others. To achieve representation uniformity, the HashSet would need to be extended with multiple encodings per element (see §2.3).


### 2.2 Entropy Map (from `entropy-maps.md`)

**Latent function.** Arbitrary $f : X \to Y$ where $Y$ is finite.

**Construction.** Assign a **prefix-free code** $C_y \subseteq \{0,1\}^*$ for each $y \in Y$, where the fraction of hash space covered by $C_y$ is proportional to (or at least close to) $\Pr_D[f(X) = y]$. Find a seed $s$ (via two-level hashing) such that:
$$h(x \| s) \in C_{f(x)} \quad \text{for all } x \in X$$

Evaluation: compute $h(c \| s)$ and decode via prefix-free code.

**Two-level hash (practical algorithm).**
1. Primary hash maps $x$ to a bucket index $j \in \{0, \ldots, b - 1\}$.
2. For each bucket, find a local seed $s_j$ such that $h(x \| s_j)$ decodes to $f(x)$ for all $x$ in bucket $j$.
3. Store $s_j$ in a seed table $H[j]$.
4. Query: compute bucket $j$ (1 hash), evaluate $h(x \| H[j])$ and decode (1 hash). Total: $O(2)$ hash operations regardless of $\varepsilon$.

**Construction time.** Let $\ell$ be the number of items in a bucket. Each candidate seed succeeds independently with probability $\varepsilon^\ell$ (all $\ell$ items must land in valid codewords). The number of trials per bucket is geometric with expected value $\varepsilon^{-\ell}$. Total expected construction time: $O(b \cdot \varepsilon^{-\ell})$. To keep this feasible, choose $b \geq n / \ell_{\max}$ where $\ell_{\max} = \lfloor \log T / \log(1/\varepsilon) \rfloor$ for a trial budget $T$ per bucket.

**Remark (connection to perfect hashing).** With $b = n$ (one item per bucket), the two-level hash reduces to a perfect hash function with implicit $\log_2(1/\varepsilon)$-bit fingerprints: the seed $s_j$ encodes the fingerprint. With $b < n$, multiple items share a seed, amortizing storage at the cost of harder seed search ($\varepsilon^{-\ell}$ grows exponentially in items per bucket). The two-level structure is the practical sweet spot — one level has $O(n)$ storage, three or more levels add hash operations without saving space.

**Mapping to cipher map abstraction.**
- $\hat{f}(c) = h(c \| H[\text{bucket}(c)])$, total function (hash always outputs).
- $\mathrm{enc}(x, 0) = x$ (in the simplest version; $K(x) = 1$).
- $\mathrm{dec}(r) = y$ if $r \in C_y$ for some $y$, else $\bot$.

**Parameter instantiation.**

| Parameter | Value | Justification |
|-----------|-------|---------------|
| $\eta$ | Construction-dependent | Fraction of elements whose bucket seed fails; reducible to near-zero with retry |
| $\varepsilon$ | Code-dependent | Probability random bits fall in $\bigcup_y C_y$; for membership ($Y = \{0,1\}$), $\varepsilon = 2^{-n}$ |
| $\mu$ | $H(Y)$ | Shannon entropy of output distribution — this is the defining result |
| $\delta$ | From code assignment | If codes are assigned with $|C_y| \propto \Pr[f(X) = y]$, marginal can approach uniform |
| Space | $-\log_2 \varepsilon + H(Y)$ bits/element | Information-theoretic bound |

**Property checklist.**

| Property | Status | Notes |
|----------|--------|-------|
| Totality | **Yes** | Hash always produces output; prefix-free decode may return $\bot$ but the hash evaluation is total |
| Representation Uniformity | **Achievable** | By assigning multiple codes per output value proportional to $\Pr_D[f(X) = y]$ |
| Correctness | **Yes** ($\eta \approx 0$) | Construction ensures correct decode for in-domain elements; $\eta$ controlled by bucket retry |
| Composability | **Yes** | Output of one entropy map is an $n$-bit string; can serve as input to another |

**Key result (entropy maps blog).** The space per element equals $H(Y) = -\sum_y p_y \log_2 p_y$ bits, where $p_y = \Pr[f(X) = y]$. This means: the *function value* component of storage cost equals the Shannon entropy of the output distribution.

**Connection to Bloom filters.** The entropy map for the set-indicator function $\mathbf{1}_A : X \to \{0,1\}$ is analogous to a Bloom filter: two codewords ("member" / "non-member") allocated hash space in ratio $\varepsilon : (1 - \varepsilon)$. The $\mu$ component (value encoding cost) is the binary entropy: $H(\varepsilon) = -\varepsilon \log_2 \varepsilon - (1 - \varepsilon)\log_2(1 - \varepsilon)$ bits. Total space per element is $-\log_2 \varepsilon + H(\varepsilon)$. Note: this is a different construction from a standard Bloom filter (hash-based lookup vs. bit array with $k$ hash functions); the space bounds differ.


### 2.3 Trapdoor Boolean Algebra (from `trapdoor-boolean-algebra.md`)

**Latent function.** Set operations over subsets of a string universe: $f : \mathcal{P}(X^*) \to \{0,1\}^n$ where $X^*$ is the free semigroup over alphabet $X$.

**Construction.** Define a map $F : \mathcal{P}(X^*) \to \{0,1\}^n$ by:

$$F(\{x_1, \ldots, x_k\}) = h(x_1) \mathbin{|} h(x_2) \mathbin{|} \cdots \mathbin{|} h(x_k)$$

Since sets are encoded by OR-ing hash values, adding elements sets more bits. This determines the operation correspondence:

| Lattice operation | Bit operation | Exact? |
|-------------------|---------------|--------|
| $A \cup B$ | $F(A) \mathbin{|} F(B)$ | **Exact** — union OR-s together all bit positions from both sets |
| $A \cap B$ | $F(A) \mathbin{\&} F(B)$ | **Approximate** — spurious bits from cross-element collisions (see below) |
| $A^\complement$ | ${\sim}F(A)$ | **Approximate** — ${\sim}F(A) \neq F(A^\complement)$ in general |
| $\emptyset$ | $0^n$ | **Exact** |
| $X^*$ | $1^n$ | **Exact** (limiting) |

$F$ is an approximate Boolean algebra homomorphism: exact for $\cup$; approximate for $\cap$ and $\complement$.

**Why intersection is approximate.** $F(A) \mathbin{\&} F(B)$ retains all bit positions set in *both* $F(A)$ and $F(B)$. But $F(A)$ has bits set by *all* elements of $A$ (not just those in $A \cap B$), and likewise for $F(B)$. When elements of $A \setminus B$ happen to set the same bit positions as elements of $B \setminus A$ (cross-element hash collisions), those bits survive the AND and appear as spurious bits in the result. Formally: $F(A \cap B) \subseteq F(A) \mathbin{\&} F(B)$, with equality only when there are no cross-element collisions. The spurious bits are false positives for membership in $A \cap B$.

**Why NOT is approximate (and degrades with set size).** ${\sim}F(A)$ flips all bits, giving the positions *not* set by any element of $A$. But $F(A^\complement)$ is the OR of hashes of *all elements not in $A$* — for large complements, this converges to $1^n$. The discrepancy: ${\sim}F(A)$ has many 1-bits when $|A|$ is small (a useful approximation) but few 1-bits when $|A|$ is large (most bits are set by $A$'s elements). Meanwhile $F(A^\complement)$ has many 1-bits when $A^\complement$ is large. So NOT is a *better* approximation for small sets and *worse* for large sets — the opposite of the (erroneous) claim in the blog post.

> **Errata note.** The blog post states that NOT "gets better for large sets" — this is backwards. For large $|A|$, $F(A)$ approaches $1^n$, so ${\sim}F(A)$ approaches $0^n$, which is a poor approximation of $F(A^\complement)$ (which should be $1^n$ when $A^\complement$ is large). NOT is most accurate when $|A|$ is small relative to $n$.

> **Errata note.** The blog post's definition block (lines 139--141) states `F(∩) = |` and `F(∪) = &`, but the proofs immediately below (First Property, Second Property) demonstrate the opposite: intersection uses bitwise AND and union uses bitwise OR. The proofs are correct; the definition block has the correspondence reversed. This formalism follows the proofs.

**Relational predicates.**
- Membership: $x \in_B W$ iff $h(x) \mathbin{\&} F(W) = h(x)$ (every bit of $h(x)$ is set in $F(W)$).
- Subset: $A \subseteq_B B$ iff $F(A) \mathbin{\&} F(B) = F(A)$ (every bit of $F(A)$ is set in $F(B)$).

> **Errata note.** The blog post defines `a ⊆_B b := a | b = a`, which tests whether $b$'s bits are a subset of $a$'s — the reverse of the intended set-theoretic direction. The correct bitwise test for $A \subseteq B$ (meaning $B$ has at least all of $A$'s elements, hence at least all of $A$'s bits) is $F(A) \mathbin{\&} F(B) = F(A)$, consistent with the membership predicate.

**False positive analysis (membership).** For random $x \notin W$ where $|W| = k$:
$$\varepsilon_\in = (1 - 2^{-(k+1)})^n$$

Derivation (under ROM, hash outputs are independent uniform bits): each bit position $j$ has $\Pr[h(x)_j = 1] = 1/2$ and $\Pr[F(W)_j = 0] = (1/2)^k = 2^{-k}$ (probability none of $k$ elements set bit $j$). Bit $j$ causes a rejection when $h(x)_j = 1$ and $F(W)_j = 0$, which happens with probability $2^{-(k+1)}$. All $n$ bits must independently pass: $(1 - 2^{-(k+1)})^n$.

**Space complexity.**
- Single-level: $n = \log \varepsilon / \log(1 - 2^{-(k+1)}) = \mathcal{O}(2^k)$ bits. Exponential in set size.
- Two-level (practical): hash to $2^w$ bins of $(q - w)$ bits each. Total space $2^w(q - w)$ bits. FP rate: $\varepsilon(k, w, q) = (1 - 2^{-(k/2^w + 1)})^{q-w}$.

**Mapping to cipher map abstraction.** The trapdoor boolean algebra is not a single cipher map but a **family of cipher maps** — one for each relational predicate ($\in_B$, $\subseteq_B$, $=_B$). For the membership predicate:
- $\hat{f}(c) = c \mathbin{\&} F(W)$ (total function on all $n$-bit strings).
- $\mathrm{enc}(x, 0) = h(x)$ (single encoding per element in the basic construction).
- $\mathrm{dec}(r) = \begin{cases} 1 & \text{if } r = h(x) \\ 0 & \text{otherwise} \end{cases}$ (where $x$ is the queried element).

**Parameter instantiation (membership predicate, set size $k$).**

| Parameter | Value | Justification |
|-----------|-------|---------------|
| $\eta$ | Operation-dependent | Union exact; intersection has spurious bits from collisions; NOT degrades with $|A|/n$ |
| $\varepsilon$ | $(1 - 2^{-(k+1)})^n$ | False positive rate for membership (derived above) |
| $\mu$ | $n$ bits (bit vector width) | Entire set represented as single $n$-bit vector |
| $\delta$ | From marginal uniformity | See below |
| Space | $n$ bits total (not per element) | Constant-size representation regardless of set size (but FP rate degrades) |

**Property checklist.**

| Property | Status | Notes |
|----------|--------|-------|
| Totality | **Yes** | Bitwise operations defined on all $n$-bit strings |
| Representation Uniformity | **Marginal only** | See §2.3.1 |
| Correctness | **Partial** | Union exact; intersection approximate (cross-element collisions); NOT approximate (degrades with set size) |
| Composability | **Yes** | Boolean operations compose; error from NOT propagates via interval arithmetic |


#### 2.3.1 Marginal Uniformity (from blog post appendix)

**Problem.** Unigram frequencies in cipher values reflect the latent distribution $D$: frequent elements appear more often, enabling frequency analysis.

**Solution.** Map each element $x$ to $K(x) \propto \Pr_D(x)$ distinct hash values (more codes for frequent values; see the corrected construction principle under Property 2). Then:
$$\Pr[\text{observe cipher value } c] \approx \Pr[\text{observe cipher value } c'] \quad \forall c, c'$$

**Limitation (stated honestly in the blog post).** This achieves **marginal** uniformity only. Joint distributions (bigrams, trigrams, etc.) are not equalized. An adversary observing sequences of cipher values can still detect correlations.

**Why this matters.** Marginal uniformity suffices when queries are independent (e.g., individual membership tests). It does NOT suffice when queries are correlated (e.g., searching for phrases, where bigram frequencies leak information). See Section 4 for the encoding granularity principle.


### 2.4 Construction Comparison

| | HashSet | Entropy Map | Trapdoor Boolean Algebra |
|---|---------|-------------|--------------------------|
| **Construction** | Batch (seed search) | Batch (seed search) | Online (hash key only) |
| **Latent function** | $\mathbf{1}_A$ (membership) | Arbitrary $f : X \to Y$ | Set operations on $\mathcal{P}(X^*)$ |
| **Totality** | Yes | Yes | Yes |
| **Rep. Uniformity** | No ($K = 1$) | Achievable | Marginal only |
| **Correctness $\eta$** | $0$ | $\approx 0$ (tunable) | Union exact; intersection/NOT approximate |
| **$\varepsilon$** | $2^{-n}$ | Code-dependent | $(1 - 2^{-(k+1)})^n$ |
| **$\mu$** | $\leq 1$ bit | $H(Y)$ | $n$ bits (fixed width) |
| **Space/element** | $-\log_2 \varepsilon$ | $-\log_2 \varepsilon + H(Y)$ | $n / k$ (amortized, degrades with $k$) |
| **Blog post** | `bernoulli-model.md` | `entropy-maps.md` | `trapdoor-boolean-algebra.md` |


---

## 3. Composition Theorem

This section derives the composition formula $\eta_{g \circ f} = 1 - (1-\eta_f)(1-\eta_g)$ from the noisy gates analysis in `noisy-gates.md`.


### 3.1 Warm-Up: The AND Gate (from `noisy-gates.md`)

Consider two independent Bernoulli Boolean values $B_1, B_2$ with correctness probabilities $p_1, p_2$ (i.e., $\Pr[B_i = x_i] = p_i$ where $x_i$ is the latent value). The AND gate computes $\mathrm{AND}(B_1, B_2)$ as an approximation of $\mathrm{AND}(x_1, x_2)$.

**Case analysis.** The correctness of the output depends on the latent inputs:

| $x_1$ | $x_2$ | $\mathrm{AND}(x_1, x_2)$ | $\Pr[\text{output correct}]$ |
|--------|--------|---------------------------|-------------------------------|
| 1 | 1 | 1 | $p_1 p_2$ |
| 1 | 0 | 0 | $1 - p_1(1 - p_2) = 1 - p_1 + p_1 p_2$ |
| 0 | 1 | 0 | $1 - p_2(1 - p_1) = 1 - p_2 + p_1 p_2$ |
| 0 | 0 | 0 | $1 - (1-p_1)(1-p_2) = p_1 + p_2 - p_1 p_2$ |

**Derivation of the (1,0) case.** When $x_1 = 1, x_2 = 0$: the correct output is 0. Output is wrong (1) only if $B_1 = 1$ (correct, prob $p_1$) AND $B_2 = 1$ (incorrect, prob $1 - p_2$). So $\Pr[\text{wrong}] = p_1(1 - p_2)$, giving $\Pr[\text{correct}] = 1 - p_1 + p_1 p_2$.

The output is a **4th-order Bernoulli Boolean** — four distinct correctness probabilities despite bool having only two values. The order arises because four distinct input combinations each produce different correctness.

**Interval arithmetic.** Rather than tracking all four probabilities, bound them by a minimum-length interval:
$$[\min_{\text{cases}} p_{\text{correct}},\ \max_{\text{cases}} p_{\text{correct}}]$$

For AND with $p_1, p_2 \in (0.5, 1)$:
- Minimum: $p_1 p_2$ (case 1,1)
- Maximum: $p_1 + p_2 - p_1 p_2$ (case 0,0)


### 3.2 From AND Gate to General Composition

The AND gate analysis treats $p_1, p_2$ as correctness of the *inputs*. For composition of cipher maps, the analogous setup is:

- $\hat{f}$ maps cipher value $c$ to cipher value $\hat{f}(c)$, correct with probability $1 - \eta_f$.
- $\hat{g}$ maps cipher value $\hat{f}(c)$ to cipher value $\hat{g}(\hat{f}(c))$, correct with probability $1 - \eta_g$ *given correct input*.

**Theorem 3.1** (Composition correctness).
Let $\hat{f}$ be a cipher map for $f : X \to Y$ with correctness $\eta_f$, and $\hat{g}$ be a cipher map for $g : Y \to Z$ with correctness $\eta_g$. Then $\hat{g} \circ \hat{f}$ is a cipher map for $g \circ f$ with correctness:
$$\eta_{g \circ f} = 1 - (1 - \eta_f)(1 - \eta_g)$$

*Proof (upper bound).* The composition fails when either $\hat{f}$ or $\hat{g}$ (or both) produces an incorrect result. By a union bound:
$$\Pr[\text{composition incorrect}] \leq \Pr[\hat{f} \text{ incorrect}] + \Pr[\hat{g} \text{ incorrect}] = \eta_f + \eta_g$$

For a tighter bound, observe that the composition is correct when **both** maps are correct. If we assume:
1. $\hat{f}$ and $\hat{g}$ use independent seeds, and
2. $\hat{g}$'s correctness on $\hat{f}(c)$ is independent of whether $\hat{f}$ was correct (i.e., re-randomization: the encoding fed to $\hat{g}$ is a fresh random valid encoding of $f(x)$),

then $\Pr[\text{both correct}] = (1 - \eta_f)(1 - \eta_g)$ and:
$$\eta_{g \circ f} = 1 - (1 - \eta_f)(1 - \eta_g) = \eta_f + \eta_g - \eta_f \eta_g$$
$\square$

**Remark on the independence assumption.** Condition 2 (re-randomization) deserves care. In practice, $\hat{f}$ produces a *specific* encoding of $f(x)$, not a uniformly random one. If $\hat{g}$'s correctness depends on *which* encoding it receives, the errors may be correlated. The formula $\eta_f + \eta_g - \eta_f \eta_g$ is therefore best understood as an upper bound under the weaker assumption that errors are positively correlated (i.e., failure of $\hat{f}$ does not decrease $\hat{g}$'s failure probability). For the exact error rate of a specific composition, the case-by-case analysis from §3.1 (interval arithmetic) gives tighter bounds.

**Connection to AND gate.** The AND gate in the noisy-gates analysis is a specific composition: $g = \mathrm{AND}$ applied to two Bernoulli inputs. The four cases in §3.1 decompose the error more finely than Theorem 3.1 because they condition on the latent input values. For specific circuits, use interval arithmetic to track $[\eta_{\min}, \eta_{\max}]$ through each gate rather than the worst-case formula.


### 3.3 Composition Chains

For a chain of $m$ cipher maps $\hat{f}_1, \ldots, \hat{f}_m$:
$$\eta_{\text{total}} \leq 1 - \prod_{i=1}^{m} (1 - \eta_i)$$

The relation is an **upper bound**, not an equality: "every stage correct" is sufficient but not necessary for the chain to be correct, since a stage error can be masked by a later stage mapping the corrupted token back to a correct value (cf. the cancellation noted in §3.2 and the noise behavior under Property 4). Equality holds only under the assumption that any stage error propagates to the output. (See `cross-paper-consistency.md`, item C-12.)

If all $\eta_i = \eta$:
$$\eta_{\text{total}} \leq 1 - (1 - \eta)^m \approx m\eta \quad \text{for small } \eta$$

**Example.** A circuit of 100 cipher maps each with $\eta = 10^{-6}$:
$$\eta_{\text{total}} \leq 1 - (1 - 10^{-6})^{100} \approx 10^{-4}$$

**Interval refinement.** For tighter bounds on specific circuits, use the case-by-case analysis from §3.1 with interval arithmetic, tracking $[\eta_{\min}, \eta_{\max}]$ through each gate. This gives input-dependent bounds rather than worst-case.


### 3.4 The Boolean Thread

The AND gate analysis in §3.1 is not merely an illustrative example. It reveals the structural constraints on composition at the bit level, constraints that apply to all cipher map systems built on bitwise operations.

**AND and OR are exact.** For Boolean cipher values encoded as bit positions in an $n$-bit string (the trapdoor boolean algebra construction), $F(A \cup B) = F(A) \mathbin{|} F(B)$ and $F(A) \mathbin{\&} F(B) \supseteq F(A \cap B)$. Union is exact because OR-ing bit vectors preserves all set bits from both operands. Intersection is approximate but only in one direction (spurious bits from cross-element collisions; never missing bits).

**NOT is approximate, and this is structural.** The complement ${\sim}F(A)$ flips the bits of $F(A)$, but $F(A^\complement)$ is the OR of hashes of all elements *not* in $A$. By the pigeonhole principle, for any universe larger than $2^n$, every bit position has some element hashing to it, so $F(A^\complement) = 1^n$ while ${\sim}F(A) \neq 1^n$ in general. This is not an implementation deficiency; it is a consequence of compressing an infinite (or large) universe into $n$ bits. No finite-width bitwise construction can make NOT exact.

**Consequence.** Any system that composes cipher maps through Boolean operations inherits the asymmetry: AND/OR chains accumulate error only through the composition theorem ($\eta_{\text{total}} \le 1 - \prod(1-\eta_i)$), while NOT introduces additional structural error that depends on the ratio $|A|/2^n$. Circuits with many NOT operations degrade faster than circuits with only AND/OR.


### 3.5 Convergence of the Composition Formula

The composition bound $\eta_{\text{total}} \le 1 - \prod_{i=1}^{m}(1 - \eta_i)$, with its multiplicative survival core $\prod_i (1-\eta_i)$, appears independently in four places across the two ecosystems:

1. **`noisy-gates.md` (foundations).** Derived from the AND gate case analysis: $\Pr[\text{both correct}] = p_1 \cdot p_2$, giving $\eta = 1 - (1-\eta_1)(1-\eta_2)$ (§3.1 above).

2. **`bernoulli_composition`.** Derived as the composition closure theorem for Bernoulli set operations: the probability that a chain of $m$ independent approximate tests all succeed is $\prod(1-\eta_i)$.

3. **`bernoulli_maps`.** Derived for the function space $B_{X \to Y}$: composing Bernoulli maps $\hat{g} \circ \hat{f}$ with independent seeds yields the same multiplicative survival formula.

4. **This document (§3.2, Theorem 3.1).** Derived from the union bound refined by independence.

The four derivations use different starting points (case analysis, set-theoretic composition, function-space composition, probabilistic union bound) but arrive at the identical formula. This convergence is evidence that the result is not an artifact of any particular proof technique but a structural property of independent approximate computations. The underlying fact is elementary: for independent events $A_1, \ldots, A_m$, $\Pr[\bigcap A_i] = \prod \Pr[A_i]$.


---

## 4. Representation Uniformity and Encoding Granularity

Property 2 (representation uniformity) is the subtlest of the four properties. This section defines it precisely, identifies what it does and does not guarantee, and introduces the *encoding granularity principle*.


### 4.1 The Metric: Total Variation Distance

**Definition 4.1.** Let $P$ and $Q$ be distributions on a finite set $\Omega$. The total variation distance is:
$$d_{\mathrm{TV}}(P, Q) = \frac{1}{2} \sum_{\omega \in \Omega} |P(\omega) - Q(\omega)| = \max_{A \subseteq \Omega} |P(A) - Q(A)|$$

**Why TV distance.** TV distance has the operational interpretation: no test can distinguish $P$ from $Q$ with advantage greater than $d_{\mathrm{TV}}(P, Q)$. This directly bounds what an adversary observing cipher values can learn.

**Remark.** Max-divergence ($D_\infty$) would give a stronger guarantee (bounds the *ratio* of probabilities rather than the difference) but is harder to achieve. We use TV distance because the blog post constructions are designed around frequency equalization, which naturally yields TV bounds. Upgrading to $D_\infty$ is future work.


### 4.2 The Encoding Granularity Principle

Representation uniformity ($\delta$-closeness to uniform) is defined *per cipher map*. What correlations it hides depends on **what is encoded as a unit**.

**Definition 4.2** (Encoding granularity).
The *encoding granularity* of a cipher map $\hat{f}$ for $f : X \to Y$ is the type $X$. Representation uniformity applies to the distribution over encodings of individual elements of $X$.

**The three granularity levels (by example).**

Consider encrypting a pair of Boolean values $(a, b)$ where $a$ and $b$ are correlated.

**Level 1: Component-wise encoding.** Encode $a$ and $b$ as separate cipher values: $(\mathrm{enc}_1(a, k_1), \mathrm{enc}_2(b, k_2))$.

- Each component's marginal distribution is $\delta$-close to uniform.
- **Joint correlations leak.** If $a$ and $b$ are correlated (e.g., $a = b$ always), the pair $(\mathrm{enc}_1(a, k_1), \mathrm{enc}_2(b, k_2))$ may reveal this correlation, because representation uniformity only bounds the marginal.
- This is the limitation identified in the trapdoor boolean algebra appendix.

**Level 2: Pair-wise encoding.** Encode $(a, b)$ as a single cipher value: $\mathrm{enc}((a,b), k)$.

- The distribution over encodings of pairs is $\delta$-close to uniform over $\{0,1\}^n$.
- **Joint correlations hidden.** An adversary sees a single opaque cipher value; it cannot determine whether the underlying pair is $(0,0)$, $(0,1)$, $(1,0)$, or $(1,1)$.
- Cost: the domain is $X = \{0,1\}^2$ (4 elements) rather than $X = \{0,1\}$ (2 elements). Space per encoding grows.

**Level 3: Whole-program encoding (ideal but impractical).** Encode the entire program state as a single cipher value.

- All correlations hidden: the adversary sees one opaque bit string per computation step.
- Cost: domain is the entire state space, which is typically exponential. Space and construction time are prohibitive.

**The trade-off.** Coarser encoding granularity yields better privacy (more correlations hidden) but requires more space and construction time. The *ideal* cipher map encodes the entire program as a single value, but composition exists precisely because that is impractical — you compose smaller cipher maps and accept that intermediate correlations may leak.

### 4.3 The Entanglement Parameter $p$

The three granularity levels above are discrete. In practice, encoding granularity is a continuous parameter.

**Definition 4.3** (Entanglement parameter).
For a system encoding $k$ correlated Boolean values, the *entanglement parameter* $p$ is the number of values encoded as a single unit. The system has type:

$$\mathrm{cipher}(\{0,1\}^p)^{k/p}$$

where each block of $p$ bits is encoded jointly as one cipher value. (For non-Boolean types, replace $\{0,1\}^p$ with the appropriate product type.)

**The spectrum.**

| $p$ | Encoding | Privacy | Space per block |
|-----|----------|---------|-----------------|
| $1$ | Each bit independently | Marginal uniformity only; all correlations leak | $O(1)$ |
| $2$ | Pairs (bigrams) | Pairwise correlations hidden; higher-order may leak | $O(|Y|^2)$ |
| $p$ | $p$-tuples ($p$-grams) | $p$-wise correlations hidden | $O(|Y|^p)$ |
| $k$ | Entire state as one value | All correlations hidden (ideal) | $O(|Y|^k)$ (prohibitive) |

**Connection to bigram encoding.** The algebraic cipher types design notes identify this trade-off: "to hide correlations, $\mathrm{ob}(\{a,b\})$ should be sent as a bigram, rather than constructing $\mathrm{ob}(a) \cup \mathrm{ob}(b)$ from $\mathrm{ob}(a)$ and $\mathrm{ob}(b)$ on the untrusted machine." This is precisely $p = 2$ vs. $p = 1$.

**Relationship to $\delta$.** The representation uniformity parameter $\delta$ should be understood as *relative to the encoding unit*. A system with $p = 1$ and $\delta = 0$ has perfect marginal uniformity but leaks all correlations. A system with $p = k$ and $\delta = 0$ has perfect joint uniformity. Formally, $\delta$ is a function of $p$: $\delta(p)$ bounds the TV distance from uniform for $p$-tuples. The privacy guarantee strengthens as $p$ increases, at exponential space cost.

**Formal statement.**

**Proposition 4.1** (Granularity and privacy).
Let $\hat{f}$ be a cipher map for $f : X_1 \times X_2 \to Y$ with representation uniformity $\delta$. Then:
1. The marginal distribution of $\mathrm{enc}((x_1, x_2), k)$ over random $(x_1, x_2) \sim D$ and random $k$ is $\delta$-close to uniform.
2. This implies that the joint distribution of $(x_1, x_2)$ is hidden up to $\delta$.

Now let $\hat{f}_1, \hat{f}_2$ be independent cipher maps for $f_1 : X_1 \to Y_1$ and $f_2 : X_2 \to Y_2$, each with representation uniformity $\delta$. Then:
1. Each marginal cipher value is $\delta$-close to uniform.
2. **But correlations between $x_1$ and $x_2$ are not hidden**, even when $\delta = 0$. An adversary observing multiple pairs $(\mathrm{enc}_1(x_1, k_1), \mathrm{enc}_2(x_2, k_2))$ can build joint frequency tables and detect correlations in $(x_1, x_2)$, because each $\mathrm{enc}_i$ is a deterministic function of $(x_i, k_i)$ — the correlation structure of $(x_1, x_2)$ under $D$ is preserved in the joint distribution of cipher value pairs.

*Proof sketch.* Part 1 of each case follows from Property 2 applied to the respective cipher map. Part 2 of the component-wise case: representation uniformity bounds the *marginal* distribution of each cipher value, not the *joint*. Even with $\delta = 0$ (perfect marginal uniformity), an adversary observing $N$ independent draws of $(\mathrm{enc}_1(x_1), \mathrm{enc}_2(x_2))$ can estimate the joint distribution $\Pr[\mathrm{enc}_1 = c_1, \mathrm{enc}_2 = c_2]$ and recover the correlation structure of $(x_1, x_2)$. This is because: (a) $\mathrm{enc}_i$ is a deterministic function of $(x_i, k_i)$, so correlated inputs produce correlated cipher values; and (b) marginal uniformity is a single-observation property, not a multi-observation one. $\square$


### 4.4 Honest Limitations

1. **Marginal uniformity says nothing about joint distributions.** An adversary observing a sequence of $m$ cipher values from component-wise encoding can detect correlations even if each individual value looks uniform.

2. **The blog post acknowledges this.** From the trapdoor boolean algebra appendix: "only marginal distribution uniform, not joint" and "sequence-based approach: space grows exponentially with sequence length."

3. **Encoding granularity is a design choice, not a property of the formalism.** The cipher map abstraction supports any granularity; the user must choose based on the privacy/efficiency trade-off for their application.

4. **Equality pattern leakage is fundamental.** Any deterministic encoding leaks the equality pattern of its inputs: observing $\mathrm{enc}(x_1, k_1) = \mathrm{enc}(x_2, k_2)$ reveals $x_1 = x_2$. Multiple representations ($K(x) > 1$) reduce but do not eliminate this — repeated queries with the same $(x, k)$ still match. Mitigation requires either re-randomizing $k$ on each use or accepting bounded equality leakage.


---

## 4A. Confidentiality Measures (Two Scales)

The four properties (Section 1.3) characterize a cipher map structurally. This section fixes the quantitative confidentiality measures the papers build on. The central reconciliation point, due to the Entropy Ratio paper, is that **confidentiality lives at two scales that do not reduce to each other**, and each scale has its own measure. Conflating them (as the project `CLAUDE.md` Core Principle 7 did, by writing the entropy ratio as $H(X \mid \text{view})/H^*(X)$, a form that is neither measure below) produces statements that are individually plausible and jointly wrong. Engineering at one scale does not engineer at the other.

### 4A.1 The Marginal Scale

A single cipher map, observed on a stream of cipher values, leaks only through the non-uniformity of that stream. Two equivalent measures quantify this, both controlled by the representation-uniformity parameter $\delta$ (Property 2).

**Measure M1: the entropy ratio.** Let $Q$ be the induced cipher-value distribution (Property 2) and let $U = \mathrm{Uniform}(\{0,1\}^n)$. The per-query **entropy ratio** is
$$e \;=\; \frac{H(Q)}{H^*}, \qquad H^* = n,$$
the observed entropy of one cipher value normalized by its maximum $H^* = \log_2|\mathrm{Im}(\mathrm{enc})|$ bits (image-relative, matching Property 2; cf. C-11/BP-5). Equivalently $e = 1 - D_{\mathrm{KL}}(Q \,\|\, U_{\mathrm{im}})/H^*$, with $U_{\mathrm{im}}$ uniform on $\mathrm{Im}(\mathrm{enc})$. It satisfies $e \in [0,1]$, with $e = 1$ iff $Q = U_{\mathrm{im}}$ (perfect uniformity, $\delta = 0$).

**Bridge to $\delta$ (Fannes--Audenaert).** For $\delta \leq 1/2$,
$$e \;\geq\; 1 - \delta - \frac{h_2(\delta)}{H^*}, \qquad h_2(\delta) = -\delta\log_2\delta - (1-\delta)\log_2(1-\delta), \quad H^* = \log_2|\mathrm{Im}(\mathrm{enc})|.$$
This is *linear* in $\delta$. (Pinsker runs the wrong way here: it lower-bounds KL given TV, not the reverse. Fannes--Audenaert is the correct continuity direction.) This bound is proven as Theorem 3.1 in the Entropy Ratio paper and restated as Proposition 5.1 in the Cipher Maps paper; the two agree.

**Measure M2: single-guess distinguishing accuracy (Le Cam, marginal).** A membership-inference attacker who observes a decoded output $\mathrm{dec}(\hat{f}(c))$ and guesses real-vs-filler is limited, at balanced prior, to accuracy
$$\tfrac{1}{2} + \tfrac{\delta}{2},$$
i.e. distinguishing advantage at most $\delta/2$. This is Le Cam's two-point lemma applied to the cipher-value marginals (Cipher Maps paper, Section 5.3, stated in prose, not a numbered theorem). **Scope caveat:** this bound is value-side only. An attacker exploiting *structure in the key universe* (e.g. $S = \{x : x \equiv 0 \bmod 7\} \subseteq \mathbb{Z}_N$) can exceed it; when the membership set is drawn at random the bound is tight.

Both M1 and M2 are marginal: they see one cipher value at a time, and small $\delta$ controls them.

### 4A.2 The Compositional / Active Scale

When the untrusted machine can either (a) apply operations to a cipher value, or (b) observe several cipher maps on the same cipher value, it learns things that **no value of $\delta$ prevents**. This is not a flaw; it is the same composability (Property 4) that makes blind chained evaluation possible.

**Measure C1: orbit-closure residual entropy (active adversary).** Let $F = \{\hat{f}_1, \ldots, \hat{f}_k\}$ be the cipher maps available to the untrusted machine and let $\mathrm{orbit}_F(c) \subseteq \{0,1\}^n$ be the smallest set containing $c$ and closed under every $\hat{f}_i$. With the view defined as $\mathcal{V}_F(c) = \mathrm{orbit}_F(c)$,
$$H(X \mid \mathcal{V}_F(c)) \;\geq\; H(X) - \log_2 |\mathrm{orbit}_F(c)|, \qquad \mathrm{conf}_F(c) \;\geq\; 1 - \frac{|\mathrm{orbit}_F(c)|}{|X|}.$$
This is the confidentiality bound of the Algebraic Cipher Types paper (entropy form and set form). It is **active**: the leakage is governed by orbit size, which a typed-composition discipline bounds at design time (a depth-$k$ typed chain from $m$ inputs gives $|\mathrm{orbit}| \leq \sum_i N_i$, independent of the cipher-space sizes). Note this is conditional residual entropy of the *latent* $X$, an unnormalized quantity; it is **not** the entropy ratio $e$ of M1, and the two should never be equated.

**Measure C2: multi-instance coincidence (same $f$, independent seeds).** If the untrusted machine holds $t$ cipher maps $\hat{f}_1, \ldots, \hat{f}_t$ for the *same* latent $f$ under independent seeds, with public acceptance partitions $\{\alpha_i(y)\}$, the coincidence-oracle attacker reaches accuracy
$$\mathrm{accuracy}(t) \;=\; 1 - \tfrac{1}{2}\sum_{y} \prod_{i=1}^{t} \alpha_i(y) \quad\xrightarrow{\text{homogeneous}}\quad 1 - \tfrac{1}{2}\sum_{y} \alpha(y)^t.$$
This is Theorem 8.2 of the Cipher Maps paper. Concentrated (Huffman-style) acceptance partitions minimize the sum and so defend best at every $t$; the deployment defense when shared-$f$ composition is unavoidable is randomized encoding ($K(x) > 1$), not codec retuning.

**Measure C3: shared-variable joint recovery (different $f$, shared cipher value).** If the untrusted machine observes pairs $(\hat{f}_1(c_i), \hat{f}_2(c_i))$ for $f_1 : X \to Y_1$, $f_2 : X \to Y_2$ on shared in-domain cipher values, mutual information is preserved exactly,
$$I(\hat{f}_1(C); \hat{f}_2(C)) = I(f_1(X); f_2(X)),$$
and the joint distribution on $Y_1 \times Y_2$ is recoverable at the minimax-optimal rate $\Theta(|Y_1|\,|Y_2|/\xi^2)$ in TV accuracy $\xi$ (upper bound by plug-in estimation, matching lower bound by **Assouad's lemma** over a $2^{m/2}$ hypercube packing). This is the main result of the Entropy Ratio paper (its Theorems 5.1 and 5.2; the lower bound is Assouad, not Le Cam's two-point method, which cannot give a dimension-dependent rate, see §4A.3 and C-4/BP-6). **No per-cipher-map $\delta$ changes this rate.** The defenses are system-level: reduce observations, encode jointly (raise the entanglement $p$, Section 4.3), or inject noise.

### 4A.3 Marginal Le Cam vs Compositional Assouad (Do Not Conflate)

Two different minimax tools appear at the two scales, and an earlier framing wrongly filed both under the bare phrase "Le Cam". The marginal single-guess bound is Le Cam's two-point method (two hypotheses). The compositional minimax lower bound is **Assouad's lemma** (a $2^{m/2}$ hypercube packing summed over coordinates), which a two-hypothesis argument cannot reproduce, since the rate is dimension-dependent. Do not conflate:

| Use | Scale | Method | Role | Bound | Owner |
|---|---|---|---|---|---|
| M2 | marginal | Le Cam two-point | upper bound on a single-guess attacker | accuracy $\leq \tfrac12 + \tfrac\delta2$ | Cipher Maps Section 5.3 |
| C3 | compositional | **Assouad's lemma** | lower bound on the joint-estimation minimax rate | $\mathbb{E}[\mathrm{TV}] \geq c\sqrt{|Y_1||Y_2|/N}$ | Entropy Ratio Theorem 5.2 |

### 4A.4 Summary of Measures

| Measure | Scale | Quantity | Controlled by $\delta$? | Owner paper |
|---|---|---|---|---|
| M1 entropy ratio | marginal | $e = H(Q)/n \geq 1 - \delta - h_2(\delta)/n$ | yes | Entropy Ratio (Thm 3.1), Cipher Maps (Prop 5.1) |
| M2 single-guess | marginal | accuracy $\leq \tfrac12 + \tfrac\delta2$ | yes | Cipher Maps (Section 5.3) |
| C1 orbit closure | active | $H(X\mid\mathcal{V}_F) \geq H(X) - \log_2|\mathrm{orbit}_F(c)|$ | no | Algebraic Cipher Types |
| C2 coincidence | compositional | $\mathrm{acc}(t) = 1 - \tfrac12\sum_y \alpha(y)^t$ | no | Cipher Maps (Thm 8.2) |
| C3 joint recovery | compositional | minimax rate $\Theta(|Y_1||Y_2|/\xi^2)$ | no | Entropy Ratio (Thms 5.1, 5.2) |

The single sentence to remember: **$\delta$ buys marginal confidentiality (M1, M2) and nothing at the compositional or active scale (C1, C2, C3).** That separation is the spine of the Entropy Ratio paper and the design rationale for typed composition (Algebraic Cipher Types) and rekeying (Cipher Rekeying).

---

## 5. The Trusted / Untrusted Machine Model

This section formalizes the trust model that is implicit in the blog posts and made explicit in `DESIGN-trapdoor-reframing.md`. This is a new formalization extending the blog post ideas.

> **Provenance note.** The trusted/untrusted distinction is not in the blog posts. It is a formalization of the *implicit* model: the blog posts describe constructions where a "seed" (trapdoor) enables decoding, and without it, the hash output is opaque. This section makes that implicit model explicit.


### 5.1 Definitions

**Definition 5.1** (Trusted machine $T$).
The trusted machine $T$ is a computational agent that holds:
- The seed $s$ (trapdoor),
- The encoding function $\mathrm{enc}$,
- The decoding function $\mathrm{dec}$,
- Knowledge of which queries are real vs. filler.

$T$ can:
- Encode plaintext values: $x \mapsto \mathrm{enc}(x, k)$ for chosen $k$.
- Decode cipher results: $r \mapsto \mathrm{dec}(r)$.
- Inject noise: generate random $c \gets \{0,1\}^n$ as filler queries.
- Verify results: check $\mathrm{dec}(\hat{f}(\mathrm{enc}(x, k))) = f(x)$.

**Definition 5.2** (Untrusted machine $U$).
The untrusted machine $U$ is a computational agent that holds:
- The cipher map $\hat{f}$ (a total function on bit strings),
- A collection of cipher values (encodings + filler, indistinguishable to $U$).

$U$ can:
- Evaluate cipher maps: $c \mapsto \hat{f}(c)$ for any $c \in \{0,1\}^n$.
- Return results to $T$.

$U$ cannot:
- Decode cipher values (does not hold $s$ or $\mathrm{dec}$).
- Distinguish real encodings from filler (by Property 1, both produce $n$-bit outputs).
- Determine the domain $X$ or function $f$ (by Property 2, cipher values are $\delta$-close to uniform).
- Enumerate which inputs are "in-domain" (by totality, every input produces output).


### 5.2 Information Flow

```
    T                                U
    |                                |
    |-- enc(x, k) + filler c_i ---->|     (cipher values, indistinguishable)
    |                                |
    |                         f-hat(c) for each c
    |                                |
    |<-- f-hat(enc(x,k)), f-hat(c_i)|     (cipher results, indistinguishable)
    |                                |
    dec(f-hat(enc(x,k))) = f(x)     |     (T decodes real results)
    ignore f-hat(c_i)               |     (T discards filler results)
```

**What $U$ observes.** A sequence of $n$-bit strings as input, and a sequence of $n$-bit strings as output. Under the four properties:

1. **Totality**: every input produces output; no "error" signals leak domain information.
2. **Representation uniformity**: cipher values are $\delta$-close to uniform; frequency analysis is bounded by $\delta$.
3. **Correctness**: irrelevant to $U$ (only $T$ decodes).
4. **Composability**: $U$ can chain cipher maps without needing to decode intermediate results.


### 5.3 What the Properties Guarantee Against $U$

| Adversary capability | Prevented by | Mechanism |
|----------------------|--------------|-----------|
| Distinguish real from filler queries | Property 1 (totality) | All queries produce output; no "not found" signal |
| Frequency analysis on cipher values | Property 2 (rep. uniformity) | Cipher values $\delta$-close to uniform |
| Learn function values | Trapdoor (one-way hash) | Cannot invert $h$ without seed $s$ |
| Enumerate domain $X$ | Property 1 + trapdoor | Cannot test membership (every input works); cannot invert hash |
| Detect correlations between queries | **Not fully prevented** | Only marginal uniformity; joint correlations may leak (see §4.2) |

The last row is the honest limitation: the four properties do not provide full correlation hiding unless the encoding granularity encompasses the correlated values.


### 5.4 What $T$ Can Do (Consequence of Holding the Trapdoor)

$T$ holds the seed $s$ and therefore can:
1. **Encode any $x \in X$**: choose representation index $k$, compute $\mathrm{enc}(x, k)$.
2. **Decode any cipher result**: compute $\mathrm{dec}(r)$, obtaining $f(x)$ or $\bot$.
3. **Verify correctness**: check $\mathrm{dec}(\hat{f}(\mathrm{enc}(x, k))) = f(x)$.
4. **Detect noise-to-signal events**: if $\mathrm{dec}(\hat{f}(c_{\text{filler}})) \neq \bot$, a random input happened to produce a decodable output (probability $\varepsilon$). $T$ knows which queries were filler and ignores these.
5. **Reseed**: when leakage accumulates (e.g., $U$ observes enough queries to mount statistical attacks), $T$ can construct a new cipher map with a fresh seed $s'$.


---

## 6. Summary and Verification

### 6.1 Gap Resolution

| Gap | Resolution |
|-----|-----------|
| **G1: Totality definition** | Definition 1.1 and Property 1 (§1.3): $\hat{f} : \{0,1\}^n \to \{0,1\}^n$ total, out-of-domain outputs uniform under ROM. Instantiated for all three constructions (§2). Construction layers (§1.2) show totality arises from the noise layer. |
| **G2: $\delta$ undefined** | Definition: $d_{\mathrm{TV}}(Q, \mathrm{Uniform})$ (§4.1). Parameterized by entanglement $p$ (§4.3). Honest limitation: marginal only at $p=1$ (§4.4). |
| **G3: Parameter instantiation** | Table in §2.4 gives $\eta, \varepsilon, \mu, \delta$ for HashSet, entropy map, trapdoor boolean algebra. Entanglement parameter $p$ added (§1.4, §4.3). |
| **G4: Composition not derived** | Derived in §3: from AND gate case analysis (§3.1) to general theorem (§3.2) to chains (§3.3). Boolean thread (§3.4) and cross-ecosystem convergence (§3.5) strengthen the result. |
| **G5: Trusted/untrusted model** | Formalized in §5: definitions of $T$ and $U$, information flow, what each can/cannot do. Flagged as extending blog post ideas. |
| **G6: Construction unification** | §2 shows each construction as instance of Definition 1.1. Batch vs. online strategies distinguished (Definition 1.1, §2.4). Construction layers (§1.2) provide conceptual decomposition. |
| **G7: Bernoulli connection** | §1A makes the dependency explicit: Kronecker factorization (§1A.1), parameter correspondence (§1A.2), two-ecosystem relationship (§1A.3). |
| **G8: Unformalized frontier** | §7 catalogs six open problems identified across the ecosystem, with sources and precise problem statements. |


### 6.2 Verification Checklist

- [x] Each property has a precise mathematical statement (§1.3).
- [x] Each construction is shown to satisfy (or not) each property with specific parameter values (§2.1--2.3).
- [x] Composition theorem has a derivation, not just a statement (§3).
- [x] $\delta$ has a concrete metric (TV distance) and honest limitations (§4).
- [x] No concepts imported from outside the blog posts without explicit flagging (§1.2 caveat, §5 provenance note).
- [x] Encoding granularity principle stated with trade-off analysis (§4.2).
- [x] Construction layers (undef/noise/cipher) explain why each property exists (§1.2).
- [x] Batch vs. online construction strategies distinguished (Definition 1.1, §2.4).
- [x] Entanglement parameter $p$ formalizes continuous encoding granularity (§4.3).
- [x] Intersection corrected from "exact" to "approximate" with derivation (§2.3).
- [x] NOT corrected: degrades with set size, not improves (§2.3).
- [x] Values-as-constant-functions unification noted (Remark after Definition 1.1).
- [x] Bernoulli foundation section connects cipher map parameters to Bernoulli model (§1A).
- [x] Kronecker factorization theorem stated with consequence for composition (§1A.1).
- [x] Boolean thread: AND/OR exact, NOT approximate and structural (§3.4).
- [x] Composition formula convergence across four independent derivations documented (§3.5).
- [x] Unformalized frontier catalogs open problems with sources (§7).


### 6.3 Open Questions

Items 1--5 below are retained from the original draft. Section 7 expands on items 2, 3, and 4 with additional context from the cross-ecosystem analysis and adds new open problems (sum-type trade-off, orbit closure, cipher TM).

1. **Max-divergence vs. TV distance for $\delta$.** TV distance gives an operational bound on distinguishing advantage. Max-divergence ($D_\infty$) would give per-element bounds. Which is the right metric depends on the threat model.

2. **Noise-to-signal probability under composition.** See §7.5 for expanded treatment.

3. **Tight bounds for intersection and NOT.** See §7.6 for expanded treatment.

4. **Adaptive encoding granularity.** See §7.4 for expanded treatment.

5. **Layered construction laws.** Do the three construction layers (undef, noise, cipher) satisfy formal algebraic laws (e.g., monad laws, naturality) in the approximate setting? If so, this would enable equational reasoning about cipher map constructions. If not, identify which laws fail and whether weaker algebraic structures apply.


---

## 7. Frontier (Status Updated 2026-06-02)

This section listed ideas identified across the ecosystem but not yet formalized. Several have since been formalized in the paper family; each such item is now marked **FORMALIZED** with a pointer to its owning paper. The remaining items are genuinely open. See the Paper Map (Section 8) for the full ownership table.

### 7.1 Sum-Type Confidentiality Trade-Off (FORMALIZED)

**Status: formalized** as the sum-type impossibility theorem in the Algebraic Cipher Types paper (tag hiding and untrusted pattern matching are mutually exclusive, with advantage bounded by $\delta$). The conjecture below was correct; the paper supplies the proof.

Source: `.archive/algebraic_cipher_types-legacy/` (2019-2022 C++ notebook, archived 2026-04-29; formerly `papers/algebraic_cipher_types/`).

For a sum type $X + Y$, there are two cipher constructions with incompatible guarantees:

- $\mathrm{OT}(X + Y)$: encode the tagged union as a single cipher value. This hides the tag (adversary cannot determine whether the value is from $X$ or $Y$) but breaks composability with functions typed over $\mathrm{OT}(X)$ or $\mathrm{OT}(Y)$ individually, because pattern matching on the tag requires the trapdoor.

- $\mathrm{OT}(X) + \mathrm{OT}(Y)$: encode each branch separately and expose the tag. This preserves composability (functions on $\mathrm{OT}(X)$ apply directly to the left branch) but leaks the tag bit.

This trade-off is structural: no construction can simultaneously hide the tag and support pattern matching without the trapdoor. A formal proof would show that any cipher type satisfying both properties implies a trapdoor inversion, contradicting the one-way assumption.

### 7.2 Orbit/Closure Information Leak Bounds (FORMALIZED)

**Status: formalized** as the confidentiality bound (Measure C1, Section 4A.2) in the Algebraic Cipher Types paper: $\mathrm{conf}_F(c) \geq 1 - |\mathrm{orbit}_F(c)|/|X|$, with proven monotonicity (more operations enlarge the orbit and lower confidentiality) and the typed-composition refinement that bounds orbit size at design time. The Cipher Rekeying paper extends it to cross-secret rekeying chains. The open problem below is closed.

Source: `.archive/algebraic_cipher_types-legacy/` (archived 2026-04-29; formerly `papers/algebraic_cipher_types/`).

Given a computational basis $F$ (a set of operations on cipher type $\mathrm{OT}(T)$), the *orbit closure* of a known cipher value $c$ under $F$ is the set of all cipher values reachable from $c$ by applying operations in $F$. Examples: $\mathrm{and}(x, \mathrm{not}(x)) = \mathrm{false}$ reveals $\mathrm{OT}(\mathrm{false})$; successor cascades from $\mathrm{OT}(0)$ reveal the entire integer type.

### 7.3 Cipher Turing Machine (EXPLORED, THEN CUT)

**Status: explored and removed.** A cipher TM construction (space $O(|\text{program}|)$, leaking head movement) was drafted in the Algebraic Cipher Types paper and then cut (2026-04) to collapse the paper to a single realization, the expression-tree decomposition with `@cipher_node` cut points. The idea is recorded in `FUTURE-RESEARCH.md`; it is not currently a target. Retained here for provenance.

Source: `.archive/algebraic_cipher_types-legacy/` (archived 2026-04-29; formerly `papers/algebraic_cipher_types/`).

Cipher maps as defined here are lookup tables with space $O(|X|)$. A cipher Turing machine replaces states, alphabet symbols, and transition functions with their cipher counterparts, divorcing space complexity from domain cardinality. Space becomes $O(|\text{program}|)$ rather than $O(|X|)$, at the cost of revealing execution patterns (head movements, step count).

### 7.4 Adaptive Encoding Granularity (PAPER IN PROGRESS)

**Status: active draft.** This is the subject of the `papers/adaptive-trapdoor/` paper (idea/preliminary stage): maintaining confidentiality under a drifting query distribution $D$, where a static $K(x)$ (and, by extension, a static entanglement choice $p$) goes stale. The streaming observer, online $K(x)$ retuning, and drift-sensitivity experiments live in the `cipher-maps` library `experiments/` subpackage. The granularity-adaptation half stated below remains open within that paper.

The entanglement parameter $p$ (§4.3) is currently uniform: all $p$-tuples of values are encoded jointly. In practice, some values are correlated and others are independent.

**Open sub-problem.** Define an adaptive scheme where $p$ varies per value pair based on measured or known correlation. The scheme should encode correlated values jointly ($p = 2$ or higher) and independent values separately ($p = 1$), achieving a finer privacy/efficiency trade-off. The challenge is that the choice of $p$ for each pair is itself a signal that may leak correlation structure to the adversary.

### 7.5 Noise-to-Signal Under Composition

Through a chain of $m$ cipher maps, garbage input has probability $\varepsilon$ of landing in a valid codeword at each stage. The naive bound $1 - (1-\varepsilon)^m$ assumes independence across stages.

**Open problem.** Determine the exact noise-to-signal probability when maps share structure (e.g., common hash family, overlapping codeword spaces). Characterize conditions under which garbage propagating through a chain accidentally produces a valid, decodable output at the end. This matters for the trusted machine's ability to distinguish real results from noise artifacts.

### 7.6 Tight Closed-Form Bounds

Two error rates in the trapdoor boolean algebra lack closed-form expressions:

1. **Intersection FPR.** The probability that $F(A) \mathbin{\&} F(B)$ has spurious bits (cross-element collisions from $A \setminus B$ and $B \setminus A$) as a function of $|A|$, $|B|$, $|A \cap B|$, and $n$.

2. **NOT error rate.** $\eta_{\mathrm{NOT}}(|A|, n)$: the fraction of bit positions where ${\sim}F(A)$ disagrees with $F(A^\complement)$, as a function of set size and bit width.

Both are computable in principle from the bit-occupation probability $(1 - 2^{-k})$ per position, but the existing analysis stops at asymptotic bounds. Closed-form expressions would complete the parameter instantiation for the trapdoor boolean algebra (§2.3).


---

## 8. Paper Map

How the paper family sits on this spine. Every paper imports the cipher-map tuple (Definition 1.1) and the four properties (Section 1.3) by citation; none redefines them. Each paper then owns a distinct layer of the theory.

| Paper | Bibkey | Builds on the spine via | Owns (canonical home) |
|---|---|---|---|
| **Cipher Maps** | `towell2026cipher` | Definition 1.1, four properties, composition theorem (Section 3), space bound (§1.4) | The hub. Acceptance predicates and the (TV, $L$) Pareto frontier; Measure M1 (entropy ratio, Prop 5.1) and M2 (single-guess Le Cam, §5.3); Measure C2 (coincidence oracle, Thm 8.2). |
| **The Entropy Ratio** | `towell2026maxconf` | Definition 1.1 (cited), Property 2 ($\delta$), Measure M1 | The two-scale framing (Section 4A here). Measure C3 (shared-variable joint recovery, Thms 5.1/5.2). The three levers (noise injection, multiplicity, granularity) as $\delta$-reduction with costs. |
| **Algebraic Cipher Types** | `towell2026algebraic` | Definition 1.1 (cited), four properties, Property 2 ($\delta$ as the advantage bound) | Cipher types as an algebra (void/unit/product/sum/exponential). The sum-type impossibility theorem. Measure C1 (orbit closure) and the typed-composition design-time budget. |
| **Cipher Rekeying** | `towell2026rekeying` | Definition 1.1 (cited), Measure C1 (orbit closure, from Algebraic Cipher Types) | The rekeying functor as a cipher map; naturality; $n$-step chain leakage; randomized rekeying. The secret-as-data move (one corner of the code-data duality owned by Cipher Closures). |
| **Cipher Closures** | `towell2026closures` | Definition 1.1 (cited), Measure C1 (orbit closure), the cipher exponential (Algebraic Cipher Types Prop 4.3) | Cipher closures (SICP-style procedures over a secret). The code-data duality: cipher data structures as cipher maps (dispatch pattern, designed orbits via XOR hash chains), and cipher maps as cipher data (the exponential); leakage of orbit-encoded data structures. Spun out of Cipher Rekeying 2026-06-03. |
| **Adaptive Trapdoor** | (draft) | Property 2 ($\delta$), Measure M1, the homophonic $K(x) \propto D(x)$ construction | Confidentiality maintenance under drift in $D$: streaming observer, online $K(x)$ retuning, drift sensitivity. Idea/preliminary stage. |
| **Boolean Algebra over Trapdoor Sets** | (retired 2026-06-09) | The trapdoor boolean algebra construction (§2.3) | ARCHIVED to `~/github/archived/`. Was the pre-2024 authentic systems treatment (deterministic K=1 trapdoor sets; equality-channel/plaintext-Boolean leakage). Retired as insufficiently novel standalone (single-hash Bloom filter); its two kernels folded into the active papers: the generalized-Boolean-algebra characterization into Algebraic Cipher Types (`rem:trapdoor-set-algebra`), and the K=1 deterministic baseline into Cipher Maps §9.4 (online construction). |

**Canonical citation keys.** Use `towell2026algebraic` for the Algebraic Cipher Types paper everywhere. The key `towell2026actypes` (used only inside Cipher Rekeying) is a duplicate of the same paper and should be renamed; see `cross-paper-consistency.md` item C-2. The Cipher Maps `.bib` entry for that paper also carries a stale title ("A Functorial Framework...") that must be updated to the real title ("Confidentiality Trade-offs in Type Constructors over Trapdoor Computing").

**Shared macro vocabulary.** All papers share the same LaTeX macros for the core objects: `\fhat` ($\hat{f}$), `\enc`, `\dec`, `\B` ($\{0,1\}$), `\cipher{X}` ($\mathsf{C}(X)$), `\cipherS{X}{s}` ($\mathsf{C}_s(X)$), `\orbitF` ($\mathrm{orbit}_F$). A future shared `trapdoor.bib` plus a common macro preamble would remove the remaining per-paper drift; see the reconciliation report.

### Canonical Notation (the shared spine)

| Concept | Canonical symbol | Notes |
|---|---|---|
| Latent function | $f : X \to Y$ | known only to the trusted machine |
| Cipher map (function part) | $\hat{f} : \{0,1\}^n \to \{0,1\}^n$ | total; held by the untrusted machine |
| Encode / decode | $\mathrm{enc}$, $\mathrm{dec}$ | trusted only; $\mathrm{enc}: X \times \{0,\dots,K(x){-}1\} \to \{0,1\}^n$, $\mathrm{dec}: \{0,1\}^n \to Y \cup \{\bot\}$ |
| Secret / trapdoor | $s$ | derives $\hat{f}, \mathrm{enc}, \mathrm{dec}$ |
| Cipher type / space | $\mathsf{C}(X)$, $\mathsf{C}_s(X)$ | the image of $\mathrm{enc}$; sans-serif C |
| Query distribution on $X$ | $D$ | prior the trusted machine encodes from |
| Induced cipher-value distribution | $Q$ | what the untrusted machine observes |
| Representation uniformity | $\delta = d_{\mathrm{TV}}(Q, \mathrm{Uniform}(\{0,1\}^n))$ | marginal only |
| Correctness | $\eta$ | $\Pr[\mathrm{dec}(\hat f(\mathrm{enc}(x,k))) \neq f(x)] \leq \eta$ |
| Noise-decode / space | $\varepsilon$ | $\Pr[\text{random bits decode}]$; space $-\log_2\varepsilon + H(Y)$ |
| Value cost | $\mu = H(Y)$ | |
| Multiplicity | $K(x) \geq 1$ | homophonic: $K(x) \propto D(x)$ |
| Entanglement / granularity | $p$ | values encoded jointly per unit |
| Entropy ratio (M1) | $e = H(Q)/n \in [0,1]$ | **not** $H(X\mid\text{view})/H^*(X)$ |
| Orbit closure (C1) | $\mathrm{orbit}_F(c)$, view $\mathcal{V}_F(c)$ | active-adversary reachable set |
| Acceptance probability | $\alpha(y) = |A(y)|/2^n$ | $\varepsilon = \sum_y \alpha(y)$ |

This table is the reference any new paper or revision should match. Deviations are drift and belong in the reconciliation report, not in a paper.

For the *conventions* behind these symbols (the value / function / type notational levels, the cipher functor that unifies them, the rule for when to write `\hat f` versus `\mathsf{C}_s(f)`, the secret-versus-function subscript rule, and worked resolutions of recurring notation questions), see `notation.md`. That document is subordinate to this table: where they disagree on a symbol, this table wins.

---

## 9. Canonical Forms Consolidated by the Monograph (2026-06-18)

Drafting the monograph (`monograph/`, 14 chapters) forced the whole program into one frame, and several statements that were scattered or implicit across the papers acquired a clean canonical form. They are promoted here so a paper can cite a single source. (This is the synthesis-engine payoff logged in `monograph/HARVEST.md`.)

### 9.1 The Four Cannots (capability summary)

Against the untrusted machine $U$, a cipher map guarantees four things $U$ cannot do, each blocked by a named property:

1. **Cannot decode** a token to its latent value (one-way hash; only $T$ holds the trapdoor).
2. **Cannot distinguish a real query from filler** (Totality, Property 1: every string answers).
3. **Cannot determine the domain** or read which value a token carries (Representation Uniformity, Property 2: $Q$ is $\delta$-close to $U_{\mathrm{im}}$).
4. **Cannot be sure a result is correct** (nonzero $\eta$, Property 3: an answer may be a true result or a cipher-map error, the deniability dual).

Monograph Ch 1.2 (`sec:untrusted-sees`) is the canonical prose; cite this list rather than re-deriving it.

### 9.2 The Cipher Closure (unifying abstraction)

A **cipher closure** is a procedure that captures a trapdoor secret and exposes an operation interface over bit strings, with the secret reachable only through that interface. Cipher values, cipher maps, and cipher data structures are all cipher closures, differing only in the interface exposed; rekeying is a closure that transforms another closure's captured secret. This subsumes the value / map / data-structure / secret distinctions under one object (monograph Ch 13, `def:cipher-closure`; cipher-closures paper). It is the cleanest statement of the code-data duality the program rests on.

### 9.3 The Two-Scale Irreducibility (canonical statement)

Confidentiality lives at two scales that do not reduce to each other. The **marginal** scale (a single token) is governed by $\delta$ through the entropy ratio $e = H(Q)/H^*$ and its Fannes-Audenaert lower bound. The **compositional** scale (several evaluations on shared tokens) is governed by the joint-recovery rate $\Theta(|Y_1||Y_2|/\xi^2)$, **which no per-cipher-map parameter, $\delta$ included, can move**. Reducing $\delta$ is necessary but not sufficient; the compositional channel is intrinsic to composability (totality plus Property 4 create it). Monograph Ch 10 (`rem:irreducibility`) is the canonical statement; the Entropy Ratio paper owns the theorems.

### 9.4 Two Ways to Hide Frequency

Frequency-hiding has two mechanisms, and they differ in cost structure:

| Mechanism | How | Cost |
|---|---|---|
| Homophonic multiplicity | $K(x) \propto D(x)$ spreads frequent values over tokens | space; per-query for online defenses |
| GF(2) codec | non-member output law fixed on the stored span | one-time build, a rank condition; **zero per-query** |

The structural (codec) mechanism is the program's distinctive contribution against the 2024 tunable-leakage field, where every neighbor pays per query. Monograph Ch 12 (`tab:hiding`); codec and Entropy Ratio papers.

### 9.5 Promoted Tables (available to reuse)

Two monograph tables are canonical positioning artifacts the papers may reuse: the "what trapdoor computing is not" comparison (Ch 2, `tab:not`: ORAM / FHE / garbled circuits / SSE-PPE rows, by threat-model difference) and the type-constructor algebra (Ch 7, `tab:constructors`: which constructors lift through the trapdoor, product passing and sum hitting the impossibility).
