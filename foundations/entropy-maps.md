---
abstract: The basic theory behind an entropy map is to map values in the domain to
  values in the codomain by hashing to a prefix-free code in the codomain. We do not
  store anything related to the domain, since we are simply hashing them, and a prefix
  of that hash will be used as a code for a value in the codomain.
author: admin
categories:
- entropy map
- rate-distortion
- bernoulli map
- probabilistic-data-structure
comments: true
date: 2024-02-18
draft: false
featured: false
image:
  caption: ''
  focal_point: ''
  preview_only: true
tags: ["entropy-map", "rate-distortion", "bernoulli-map", "probabilistic-data-structures", "hashing", "information-theory"]
description: "Entropy maps use prefix-free hash codes to approximate functions without storing the domain, achieving information-theoretic space bounds with controllable error."
linked_project:
- bernoulli_data_type
series:
- oblivious-approximate-computing
slug: entropy-map
title: Entropy Maps
---

The PDF version of this post is available on [GitHub](https://github.com/queelius/bernoulli_data_type/tree/master/entropy-maps-paper/entropy-map.pdf).

An entropy map approximates a function $f : \mathcal{X} \to \mathcal{Y}$ by hashing domain values to prefix-free codes in the codomain. We store nothing about the domain itself. We just hash, and a prefix of that hash serves as a code for a codomain value.

We allow multiple codes per codomain value. For instance, the value `a` might be encoded by `00`, `01`, `10`, and `11`. If the hash is less than 4, we decode it as `a`.

Suppose $\Pr\lbrace f(X) = y\rbrace = p_y$ where $X \sim p_X$. The optimally space-efficient code, assuming a uniform hash function $h$, assigns prefix-free codes for $y$ whose probability of being selected by $h$ sums to $p_y$. The expected bit length is
$$
    \ell = -\sum_{y \in \mathcal{Y}} p_y \log_2 p_y,
$$
which is the entropy of the output distribution. That is why we call it an entropy map.

If $\mathcal{X}$ is finite, we can think of it as implicitly encoding the domain and storing the prefix-free code for each domain element. The average bit length per element is $\ell$, and the total is $|X| \ell$.

## Rate distortion: Bernoulli maps

We can allow errors. If one codomain value $y'$ is very common (say $p_{y'} > .99$), we can give it a prefix-free code that covers probability $p_{y'}$ and then skip coding for it in the entropy map. A random $x \in \mathcal{X}$ will map to $y'$ with probability $p_{y'}$ (which can be made as close to 1 as desired by trading space for accuracy). For the remaining domain values, we code them correctly, or allow errors on those too after attempting correct coding.

### Bernoulli set-indicator function

Consider a set-indicator function
$$
    1_{\mathcal{A}} : \mathcal{X} \to \lbrace0,1\rbrace,
$$
where $\mathcal{A} \subseteq \mathcal{X}$ and $\mathcal{X}$ is very large (possibly infinite). We assign prefix-free codes for codomain value $1$ such that a random hash maps an element of $\mathcal{X}$ to a code for $1$ with probability $\varepsilon$, where $\varepsilon$ is small (say $2^{-10}$).

There exists a (countably infinite) set of hash functions that hash all elements in $\mathcal{A}$ to codes for $1$ and elements in $\mathcal{A}' = \mathcal{X} \setminus \mathcal{A}$ to codes for either $0$ or $1$. Choosing a random hash function with this property, we expect $\varepsilon$ of the elements in $\mathcal{A}'$ to hash to $1$ (false positives) and the remaining $1 - \varepsilon$ to hash to $0$.

For any $x \in \mathcal{X}$, we test membership by checking whether a prefix of $h(x)$ is a code for $0$ or $1$. If it is a code for $0$, then $x$ is definitely not in $\mathcal{A}$. If it is a code for $1$, then $x$ is in $\mathcal{A}$ with a false positive rate of $\varepsilon$ and a true positive rate of $1$, since we explicitly chose a hash function that maps all elements of $\mathcal{A}$ to codes for $1$.

There is an interesting framing here. The entropy map starts as a compression problem, but it is also a rate-distortion problem. In the set-indicator approximation above, we are implicitly choosing to minimize a loss function where false negatives are much more costly than false positives. Either because negative elements are rarely queried, or because false positives are cheap compared to false negatives (falsely thinking a rustling in the bushes is a tiger is much less costly than failing to notice an actual tiger).

We call this a Bernoulli set-indicator function, `bernoulli<(set<X>, X) -> bool>{` $1_A$ `}`. This is what gets communicated, not the latent function $1_A$.

The confusion matrix for a hash function conditioned on mapping all of $\mathcal{A}$ to codes for $1$:

Table 1: Conditional distribution of Bernoulli set-indicator functions on $\mathcal{X} = \lbrace a,b\rbrace$

| latent/observed | $1_\emptyset$       | $1_{\lbrace a\rbrace}$                  | $1_{\lbrace b\rbrace}$                  | $1_{\lbrace a,b\rbrace}$   |
------------------|---------------------|------------------------------|------------------------------|-----------------|
| $1_\emptyset$   | $(1-\varepsilon)^2$ | $(1-\varepsilon)\varepsilon$ | $(1-\varepsilon)\varepsilon$ | $\varepsilon^2$ |
| $1_{\lbrace a\rbrace}$     | $0$                 | $1-\varepsilon$              | $0$                          | $\varepsilon$   |
| $1_{\lbrace b\rbrace}$     | $0$                 | $0$                          | $1-\varepsilon$              | $\varepsilon$   |
| $1_{\lbrace a,b\rbrace}$   | $0$                 | $0$                          | $0$                          | $1$             |

The no-false-negatives constraint produces a lot of zeros. If we observe `bernoulli<set<X>,X) -> bool>{`$1_{\lbrace a\rbrace}$`}`, the latent function is either $1_{\emptyset}$ or $1_{\lbrace a\rbrace}$. Since $\varepsilon$ is small, $1_{\lbrace a\rbrace}$ is much more likely.

The maximum degrees of freedom for this confusion matrix:

Table 2: Confusion matrix with maximum degrees of freedom

| latent/observed | $1_\emptyset$ | $1_{\lbrace a\rbrace}$ | $1_{\lbrace b\rbrace}$ | $1_{\lbrace a,b\rbrace}$               |
------------------|---------------|-------------|-------------|-----------------------------|
| $1_\emptyset$   | $p_{1 1}$     | $p_{1 2}$   | $p_{1 3}$   | $1-p_{1 1}-p_{1 2}-p_{1 3}$ |
| $1_{\lbrace a\rbrace}$     | $p_{2 1}$     | $p_{2 2}$   | $p_{2 3}$   | $1-p_{2 1}-p_{2 2}-p_{2 3}$ |
| $1_{\lbrace b\rbrace}$     | $p_{3 1}$     | $p_{3 2}$   | $p_{3 3}$   | $1-p_{3 1}-p_{3 2}-p_{3 3}$ |
| $1_{\lbrace a,b\rbrace}$   | $p_{4 1}$     | $p_{4 2}$   | $p_{4 3}$   | $1-p_{4 1}-p_{4 2}-p_{4 3}$ |

That is $4 \times (4 - 1) = 12$ degrees of freedom. Table 1 has just 1 degree of freedom ($\varepsilon$).

Degrees of freedom give a measure of model complexity. More parameters means more data needed for estimation, though frequently we already know the parameters because they were specified by the algorithm that generated the Bernoulli approximation.

### Boolean Bernoulli as constant function

How many functions of type `() -> bool`? Two: `true` and `false`. That is $|\lbrace true, false\rbrace|^{|\lbrace1\rbrace|} = 2^1 = 2$.

We can think of Boolean values as functions `() -> bool`. Applying the Bernoulli model `bernoulli<() -> bool>` gives the same result as before.

Table 3: Confusion matrix for Bernoulli model on Boolean values

| latent/observed | `true`      | `false`     |
|-----------------|-------------|-------------|
| `true`          | $p_{1 1}$   | $1-p_{1 1}$ |
| `false`         | $1-p_{2 2}$ | $p_{2 2}$   |

Maximum of two degrees of freedom. In the binary symmetric channel, $p_{1 1} = p_{2 2}$:

Table 4: Symmetric confusion matrix for Bernoulli Boolean

| latent/observed | `true` | `false` |
|-----------------|--------|---------|
| `true`          | $p$    | $1-p$   |
| `false`         | $1-p$  | $p$     |

### Conditional distribution of latent function given observed function

Once we have an observation `bernoulli<set<X>,X) -> bool>{x}`, what does the confusion matrix tell us? Let me abstract the problem.

Let $X$ and $Y$ be random variables. Suppose $P(X = x | Y = y)$ is hard to compute, but $P(Y = y | X = x)$ is easy. (This is exactly the situation with confusion matrices: we know the conditional distribution of the observed function given the latent one, but we want the reverse.)

Bayes' rule:
$$
P(X = x | Y = y) = \frac{P(Y = y | X = x) P(X = x)}{P(Y = y)}
$$

We need two things. First, $P(X = x)$, the prior. If we know the distribution of $X$, encode it. Otherwise use an uninformed prior (uniform).

Second, $P(Y = y)$, the normalizing constant:
$$
P(Y = y) = \sum_{x'} P(Y = y | X = x') P(X = x')
$$
With a uniform prior over finite $|X|$, $P(X = x) = 1/|X|$, and:
$$
P(X = x | Y = y) = \frac{P(Y = y | X = x)}{\sum_{x'} P(Y = y | X = x')}
$$

Applying this to the set-indicator case: replace $X$ with the latent indicator and $Y$ with the observed Bernoulli indicator. Read the confusion matrix, pick out the relevant column, normalize.

For example, observing $1_{\lbrace a\rbrace}$: the column is $(p_{1 2}, p_{2 2}, p_{3 2}, p_{4 2})'$. The conditional probability is
$$
p_{k|2} = \frac{p_{k 2}}{\sum_{j=1}^4 p_{j 2}},
$$
where $k$ indexes the latent function and we condition on column 2.

More generally:
$$
p_{k|i} = \frac{p_{k i}}{\sum_{j=1}^4 p_{j i}}.
$$

Doing this for all four observed indicators using the one-parameter confusion matrix from Table 1:

Table 5: Conditional probability of latent indicator given observed indicator

| observed/latent | $1_\emptyset$                     | $1_{\lbrace a\rbrace}$                     | $1_{\lbrace b\rbrace}$                     | $1_{\lbrace a,b\rbrace}$         |
|-----------------|-----------------------------------|---------------------------------|---------------------------------|-----------------------|
| $1_\emptyset$   | $1$                               | $0$                             | $0$                             | $0$                   |
| $1_{\lbrace a\rbrace}$     | $\varepsilon/(1+\varepsilon)$     | $1/(1+\varepsilon)$             | $0$                             | $0$                   |
| $1_{\lbrace b\rbrace}$     | $\varepsilon/(1+\varepsilon)$     | $0$                             | $1/(1+\varepsilon)$             | $0$                   |
| $1_{\lbrace a,b\rbrace}$   | $\varepsilon^2/(1+\varepsilon)^2$ | $\varepsilon/(1+\varepsilon)^2$ | $\varepsilon/(1+\varepsilon)^2$ | $1/(1+\varepsilon)^2$ |

When we observe the empty set in a model where false negatives are impossible, we know the latent function is $1_\emptyset$ with certainty. Observing $1_{\lbrace a\rbrace}$, we know the latent is either $1_{\emptyset}$ or $1_{\lbrace a\rbrace}$, with the latter much more likely since $\varepsilon$ is small.

## Algorithms

The simplest algorithm: hash domain values concatenated with a bit string $b$ and decode the result. Find $b$ such that $h(x + b)$ decodes to the correct $f(x)$ for all $x \in \mathcal{X}$.

### Two-level hash function evaluation

The practical version uses a two-level scheme. First, hash each $x \in \mathcal{X}$ concatenated with a bit string $b$ (same as before), but use the result to index into a hash table $H$ at position $j$. Then choose a bit string for $H[j]$ for each $x$ mapping to $j$ such that $f(x) = \text{decode}(h(x + H[j]))$.

This keeps the success probability $p_j = \prod_x \Pr\lbrace f(x) = \text{decode}(h(x + H[j]))\rbrace$ roughly constant for each bucket, independent of the total domain size, by choosing an appropriately sized hash table.

Each decoding is an independent Bernoulli trial. The probability that a particular $x$ hashing to bucket $j$ is decoded correctly is the fraction of hash values that are valid prefix-free codes for $f(x)$.

### Oblivious entropy maps

An *oblivious* entropy map applies the hash function to trapdoors of $\mathcal{X}$ rather than elements directly, and the prefix-free codes for $\mathcal{Y}$ have no discernible structure (a random assignment of hash values to codomain values). This is relevant to my work on encrypted search.
