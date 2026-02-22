---
categories:
- Research
- Mathematics
date: 2023-06-17
description: The Bernoulli Model is a framework for reasoning about probabilistic
  data structures by treating noisy outputs as Bernoulli-distributed approximations
  of latent values, from Booleans to set-indicator functions.
draft: false
math: true
series:
- oblivious-approximate-computing
slug: bernoulli-boolean-model
tags:
- probabilistic-data-structures
- bloom-filter
- probability
- type-theory
title: 'The Bernoulli Model: A Probabilistic Framework for Data Structures and Types'
toc: true
---

## Motivation

The **Bernoulli Model** is a framework for thinking about probabilistic data structures and types of a particular sort. I developed this formalism primarily to build toward Oblivious Data Types (a separate document), but the core idea stands on its own: Bernoulli approximations have useful properties for reasoning about space/accuracy tradeoffs, and the formalism lets us track correctness through computations.

The Bernoulli Model also provides a way to think about existing probabilistic data structures. The Bloom filter, Count-Min sketch, and my own Bernoulli data type family all fit this framework. The family covers everything from sets (like Bloom filters) to maps, in a near-space-optimal way, with controlled accuracy/space tradeoffs.

## Introduction: Bernoulli Boolean

The Boolean type $\mathrm{bool}$ models $\lbrace \mathrm{true},\mathrm{false}\rbrace$, or more compactly $\lbrace 0,1\rbrace$. This document replaces $\mathrm{bool}$ with a type $B_{\mathrm{bool}}$, a *noisy* Boolean. More generally, we can have a Bernoulli type for any type $T$, denoted $B_T$.

> As a special case, Bloom filters can be thought of as a Bernoulli type for the set indicator function, $1_A : X \mapsto \lbrace 0,1\rbrace$. More on that later.

There are two types with fewer values than $\mathrm{bool}$: the absurd type $\mathrm{void}$ (no values, cannot be constructed) and the unit type $()$ (one value, also denoted $()$). Since $()$ has only one value, there is no uncertainty to model.

As degenerate cases: $B_{\mathrm{void}} \equiv \mathrm{void}$ and $B_{()} \equiv ()$.

The Boolean type has two values, so it is the first type where uncertainty can be introduced.

Every Bernoulli Model has an *order*, an integer greater than 1, describing the number of independent ways the generating process can produce errors. We write $B_T^{(k)}$ for a Bernoulli Model of type $T$ with order $k$. For $\mathrm{void}$ and $()$, the maximum order is 0. In general $T \equiv B_T^{(0)}$: if there are no ways to introduce errors, you just have the type itself.

Unless it matters, I drop the order and write $B_T$. The notation $B_T(x)$ denotes the Bernoulli approximation of latent value $x$. When $x$ is unobservable, $B_T(x)$ is a noisy measurement of it.

In the Bernoulli Boolean Model, $B_{\mathrm{bool}}(x)$ is a Bernoulli random variable with
$$
\Pr\lbrace  B_{\mathrm{bool}}(x) \neq x\rbrace = \varepsilon(x)
$$
for each $x \in \lbrace 0,1\rbrace$, where $0 < \varepsilon(x) < 1$ is the error probability. In practice, $\varepsilon(x)$ is known or its expectation is known, and it can be set to balance space complexity against accuracy.

## Binary Channels

The Bernoulli Boolean model maps onto two channel models:

1. **Binary Symmetric Channel (First-order, $B_{\mathrm{bool}}^{(1)}$)**: The error probability is the same for $1$ and $0$.

2. **Binary Asymmetric Channel (Second-order, $B_{\mathrm{bool}}^{(2)}$)**: The error probability differs for $1$ and $0$.

## False Positives and Negatives

Errors decompose into:

1. $B_{\mathrm{bool}}(0) = 1$ is a *false negative*.
2. $B_{\mathrm{bool}}(1) = 0$ is a *false positive*.

In the first-order model, these probabilities are equal. In the second-order model, they differ. A common special case of the second-order model: false negatives occur with probability 0 and false positives with probability $0 < \varepsilon < 1$. This is exactly the Bloom filter error model.

## Prediction

$B_T(x)$ is correlated with the latent value $x$ and so provides information about it. Given $B_T(x)$, you can predict $x$ better than guessing, assuming the error rate is better than chance (for $B_{\mathrm{bool}}$, that means $\varepsilon(x) < 0.5$). With no prior information, the maximum likelihood estimate of $x$ is just the observation $B_T(x)$.

Since $\varepsilon(x)$ is normally known, we can use Bayes' rule:
$$
\Pr\lbrace X = x \mid B_T(x) = x \rbrace \propto \Pr\lbrace B_T(x) = x \mid X = x\rbrace \Pr\lbrace X = x\rbrace,
$$
where $\Pr\lbrace X = x\rbrace$ is the prior and $\Pr\lbrace B_T(x) = x \mid X = x\rbrace$ is the probability the observation is correct. For $X = 1$ this is the true positive rate $\tau$, for $X = 0$ the true negative rate $\nu$.

In the first-order model with accuracy $\tau$:
$$
\Pr\lbrace x \mid B_{\mathrm{bool}}^{(1)}(x)\rbrace = \frac{\tau \Pr\lbrace X = x\rbrace}
    {\tau \Pr\lbrace X = x\rbrace + (1-\tau) (1-\Pr\lbrace X = x\rbrace)}.
$$

Dividing numerator and denominator by $\Pr\lbrace X = x\rbrace$:
$$
\Pr\lbrace x \mid B_{\mathrm{bool}}^{(1)}(x)\rbrace = \frac{\tau}{\tau + (1-\tau) (1/\Pr\lbrace X = x\rbrace - 1)}.
$$

Under maximum entropy ($\Pr\lbrace X = 1\rbrace = 0.5$), this simplifies to $\Pr\lbrace x \mid B_{\mathrm{bool}}^{(1)}(x)\rbrace = \tau$.

Given $n$ i.i.d. noisy measurements,
$$
\Bigl\lbrace  B_{1,\mathrm{bool}}^{(1)}(x), \ldots, B_{n,\mathrm{bool}}^{(1)}(x) \Bigr\rbrace,
$$
the maximum likelihood estimate is the majority vote. As $n \to \infty$, the majority vote converges in probability to $x$.

This is not typically how Bernoulli Booleans arise in practice. Usually they show up as analytical results of probabilistic data structures framed in the Bernoulli Model.

## Inducing Bernoulli Types

Now we generalize.

### Unit Functions

The Bernoulli Model for value types like $\mathrm{bool}$ can be thought of as Bernoulli approximations of unit functions $() \mapsto X$. A unit function takes no input and maps to a constant. There are $|X|$ such functions.

Replacing $() \mapsto X$ with $B_X$ (equivalently $B_{() \mapsto X}$) allows for errors. The confusion matrix for $B_{() \mapsto \mathrm{bool}}^{(2)}$ is:

Table 1: Second-order Bernoulli Boolean Model for $() \mapsto \mathrm{bool}$

| $x / B_{\mathrm{bool}}^{(2)}$ | observe $1$     | observe $0$           |
|-------------------------------|-----------------|-----------------------|
| **latent** $1$                | $\tau = 1-\eta$ | $\eta$                |
| **latent** $0$                | $\varepsilon$   | $\nu = 1-\varepsilon$ |

Observing $B_{() \mapsto \mathrm{bool}}(x) = 1$: the latent value is $1$ with probability $\tau$ (true positive) and $0$ with probability $\varepsilon$ (false positive). Observing $0$: latent is $1$ with probability $\eta$ (false negative) and $0$ with probability $\nu$ (true negative).

The maximum order is 2, since $\eta$ and $\varepsilon$ are independent and fully describe the model. Each row sums to 1 (total probability), so no additional free parameters are possible.

This is just the asymmetric binary channel, with different error rates for $1$ and $0$.

The first-order model sets $\epsilon = \varepsilon = \eta$:

Table 2: First-Order Bernoulli Boolean Model for $() \mapsto \mathrm{bool}$

| $x / B_{\mathrm{bool}}^{(1)}$ | observe $1$              | observe $0$        |
|-------------------------------|--------------------------|--------------------|
| **latent** $1$                | $\tau =1-\epsilon$       | $\eta = \epsilon$  |
| **latent** $0$                | $\varepsilon = \epsilon$ | $\nu = 1-\epsilon$ |

One free parameter: the symmetric binary channel.

The zeroth-order model is deterministic:

Table 3: Zeroth-Order Bernoulli Boolean Model for $() \mapsto \mathrm{bool}$

| $x / B_{\mathrm{bool}}^{(1)}$ | observe $1$ | observe $0$ |
|-------------------------------|-------------|-------------|
| **latent** $1$                | 1           | 0           |
| **latent** $0$                | 0           | 1           |

Zero free parameters. No uncertainty.

#### Prediction: Boolean Values

Applying Bayes' rule to the first-order model $B_{\mathrm{bool}}^{(1)}$, we compute $\Pr\lbrace X = 1 | B_{\rm{bool}}^{(1)} = 1\rbrace$:
$$
\Pr\lbrace X = 1 | B_{\rm{bool}}^{(1)} = 1\rbrace =
    \frac{
        \Pr\lbrace B_{\rm{bool}}^{(1)} =1 | X=1\rbrace \Pr\lbrace X = 1\rbrace
    }
    {
        \Pr\lbrace B_{\rm{bool}}^{(1)} = 1\rbrace
    }
$$
From the confusion matrix, $\Pr\lbrace B_{\rm{bool}}^{(1)}=1 | X = 1\rbrace = \tau = 1 - \epsilon$:
$$
\Pr\lbrace X=1 | B_{\rm{bool}}^{(1)}=1\rbrace = \frac
    {(1-\epsilon) \Pr\lbrace X = 1\rbrace}
    {\Pr\lbrace B_{\rm{bool}}^{(1)}=1\rbrace}
$$
By the total probability theorem:
$$
\begin{split}
\Pr\lbrace B_{\rm{bool}}^{(1)} = 1\rbrace = \Pr\lbrace
    B_{\rm{bool}}^{(1)}=1 | X=1\rbrace \Pr\lbrace X = 1\rbrace + \\
    \Pr\lbrace B_{\rm{bool}}^{(1)}=1 | X=0\rbrace \Pr\lbrace X = 0\rbrace.
\end{split}
$$
Substituting confusion matrix values:
$$
\Pr\lbrace B_{\rm{bool}}^{(1)} = 1\rbrace = (1-\epsilon) \Pr\lbrace X = 1\rbrace + \epsilon \Pr\lbrace X = 0\rbrace.
$$

Substituting back and simplifying (dividing numerator and denominator by $\Pr\lbrace X = 1\rbrace$):
$$
\Pr\lbrace X=1 | B_{\rm{bool}}^{(1)}=1\rbrace = \frac
    {1-\epsilon}
    {1-\epsilon (1 - q/(1-q))}
$$
where $q = \Pr\lbrace X = 0\rbrace$.

Evaluating at interesting points:

1. At $q = 0$: result is $1$. We know the latent value is $1$ with certainty (prior says so), so the observation does not matter.
2. As $q \to 1$: result goes to $0$. We know the latent value is $0$ with certainty, so again the observation does not matter.
3. At $q = 0.5$: result is $1-\epsilon$. Maximum entropy case, maximum ignorance about the latent value.

## Unary Bernoulli Functions

Now we expand to unary functions.

### Lifting Unary Functions

The space of all functions $f : \rm{bool} \mapsto \rm{bool}$ is:

Table 4: All possible functions of type $\rm{bool} \mapsto \rm{bool}$

| $f$          | $f(\rm{true})$ | $f(\rm{false})$ |
|--------------|----------------|-----------------|
| $\rm{id}$    | $\rm{true}$    | $\rm{false}$    |
| $\rm{not}$   | $\rm{false}$   | $\rm{true}$     |
| $\rm{true}$  | $\rm{true}$    | $\rm{true}$     |
| $\rm{false}$ | $\rm{false}$   | $\rm{false}$    |

What happens when we replace Boolean inputs with Bernoulli Boolean values? That is: what is $\Pr\lbrace f\bigl(B_{\rm{bool}}^{(1)}(x)\bigr) = f(x)\rbrace$?

The constant functions ($\mathrm{true}$ and $\mathrm{false}$) are trivial. They always produce the same output regardless of input, so Bernoulli noise in the input does not matter: $\mathrm{true} : B_{\rm{bool}}^{(k)} \mapsto B_{\rm{bool}}^{(0)}$.

The interesting cases are $\mathrm{id}$ and $\mathrm{not}$. If $\Pr\lbrace B_{\rm{bool}}^{(1)}(x) = x\rbrace = p$, then feeding $B_{\rm{bool}}^{(1)}(\mathrm{true})$ into $\mathrm{id}$ gives the correct output with probability $p$ and the wrong output with probability $1-p$. Same for $\mathrm{false}$ inputs.

Since the output is correct with probability $p$, it is itself a Bernoulli Boolean. We have monadically lifted $\mathrm{id} : \mathrm{bool} \mapsto \mathrm{bool}$ to $B_{\mathrm{bool}}^{(1)} \mapsto B_{\mathrm{bool}}^{(1)}$.

Note that this is not a Bernoulli Model of the function $B_{\mathrm{bool} \mapsto \mathrm{bool}}$. It is a function of type $B_{\mathrm{bool}} \mapsto B_{\mathrm{bool}}$. The distinction matters.

Consider $\mathrm{true} : \mathrm{bool} \mapsto \mathrm{bool}$. Feeding it a Bernoulli Boolean gives a known-correct output (no latent values). But a Bernoulli *approximation* of the function $\mathrm{true}$ is a different concept entirely. The type is $B_{\mathrm{bool} \mapsto \mathrm{bool}}$, and the latent function is unobservable. The approximation $B_{\mathrm{bool} \mapsto \mathrm{bool}}(\mathrm{true})$ is observable and provides information about the latent function.

There are 4 functions of type $\mathrm{bool} \mapsto \mathrm{bool}$. The full confusion matrix for the highest-order model, $B_{\mathrm{bool} \mapsto \mathrm{bool}}^{(12)}$:

Table 5: Bernoulli Model for $\mathrm{bool} \mapsto \mathrm{bool}$

|                       | observe $\mathrm{id}$ | observe $\mathrm{not}$ | observe $\mathrm{true}$ | observe $\mathrm{false}$ |
|-------------------------|--------------|---------------|----------------|-----------------|
| latent $\mathrm{id}$    | $p_{1 1}$    | $p_{1 2}$     | $p_{1 3}$      | $p_{1 4}$       |
| latent $\mathrm{not}$   | $p_{2 1}$    | $p_{2 2}$     | $p_{2 3}$      | $p_{2 4}$       |
| latent $\mathrm{true}$  | $p_{3 1}$    | $p_{3 2}$     | $p_{3 3}$      | $p_{3 4}$       |
| latent $\mathrm{false}$ | $p_{4 1}$    | $p_{4 2}$     | $p_{4 3}$      | $p_{4 4}$       |

Each row sums to 1, so we have at most $4(4-1) = 12$ degrees of freedom. That is the maximum order. In practice I drop the order and write $B_{\mathrm{bool} \mapsto \mathrm{bool}}$ (propagating error rates with interval arithmetic).

The first-order model, with maximum entropy given error rate $\epsilon$:

Table 6: First-order Bernoulli Model for $\mathrm{bool} \mapsto \mathrm{bool}$

| | observe $\mathrm{id}$ | observe $\mathrm{not}$ | observe $\mathrm{true}$ | observe $\mathrm{false}$ |
|-----------------------------|--------------|--------------|--------------|--------------|
| **latent** $\mathrm{id}$    | $1-\epsilon$ | $\epsilon/3$ | $\epsilon/3$ | $\epsilon/3$ |
| **latent** $\mathrm{not}$   | $\epsilon/3$ | $1-\epsilon$ | $\epsilon/3$ | $\epsilon/3$ |
| **latent** $\mathrm{true}$  | $\epsilon/3$ | $\epsilon/3$ | $1-\epsilon$ | $\epsilon/3$ |
| **latent** $\mathrm{false}$ | $\epsilon/3$ | $\epsilon/3$ | $\epsilon/3$ | $1-\epsilon$ |

When we have a Bernoulli approximation of some latent function, we want to store error information in the output so it propagates through computation. The output becomes a Bernoulli Boolean: the Bernoulli Model generates a function of type $\mathrm{bool} \mapsto B_{\mathrm{bool}}$. In our implementation, we built a type system using interval arithmetic to propagate error rates.

The Bernoulli Model on $\mathrm{bool} \mapsto \mathrm{bool}$ does not change the input type. You can also feed Bernoulli Booleans as input, which usually produces even higher-order Bernoulli Booleans as output.

Since functions are values, we can ask: what is the probability the observed function equals the latent function?
$$
\Pr\lbrace  B_{\mathrm{bool} \mapsto \mathrm{bool}}(f) = f\rbrace.
$$

Function equality means each input maps to the same output:
$$
\begin{split}
\Pr\lbrace B_{\mathrm{bool}\mapsto \mathrm{bool}}^{(1)}(\mathrm{id})(\mathrm{true}) = \mathrm{id}(\mathrm{true}) \rbrace \times \\ \Pr\lbrace B_{\mathrm{bool}\mapsto \mathrm{bool}}^{(1)}(\mathrm{id})(\mathrm{false}) = \mathrm{id}(\mathrm{false}) \rbrace
\end{split}
$$

From the confusion matrix, this product is $1-\epsilon$. Normally, the process generating the Bernoulli Model is defined in terms of these per-input probabilities.

### Higher-Order Bernoulli Models

Higher order means more parameters to estimate, but also more capacity to approximate the latent function. In the confusion matrix, we want the diagonal close to 1. For off-diagonal elements, functions more similar to the latent should have larger probabilities than dissimilar ones. This is just loss minimization.

## Set-Indicator Functions

A set-indicator function maps elements to Booleans: $X \mapsto \mathrm{bool}$, returning true if the input is in the set.

The Bloom filter is a second-order Bernoulli model of the set-indicator function. False negatives are impossible (probability 0), false positives occur with probability $\varepsilon$. Technically $\varepsilon$ is the *expected* false positive rate; the true rate is a random variable that usually cannot be computed exactly unless $X$ is finite.

### HashSet: Approximate Set-Indicator Functions

Suppose we have a cryptographic hash function $h : X \mapsto \lbrace 0,1\rbrace^n$. We define a $\mathrm{HashSet}$:

- Given a set $A$ to approximately represent.
- Find a seed $s$ such that $h(x s) = 0^n$ for all $x \in A$.
- For $x \notin A$, by the properties of $h$, $h(x s) = 0^n$ with probability $2^{-n}$ (false positive).
- Define membership as $x \in A \equiv h(x s) = 0^n$.

Finding the seed requires that all $x \in A$ hash to $0^n$. Each trial succeeds with probability $\prod_{j=1}^{|A|} 2^{-n} = 2^{-n|A|}$, so we need an expected $2^{n|A|}$ trials. We store just the seed: $n|A|$ bits total, or $n$ bits per element. Since $\varepsilon = 2^{-n}$, the space is $-\log_2 \varepsilon$ bits per element.

This achieves the information-theoretic lower bound, but at exponential time complexity. Better algorithms exist at a cost to space.

### Bernoulli Model for Set-Indicator Functions

The number of functions $X \mapsto \mathrm{bool}$ is $2^{|X|}$. These are all possible set-indicator functions, and we can approximate them with $B_{X \mapsto \mathrm{bool}}$.

The $\mathrm{HashSet}$ construction induces this Bernoulli Model. False positives at rate $\epsilon$, false negatives at rate $0$. The Bernoulli Model on the function also specifies a Bernoulli Model on the Boolean output:
$$
    \in : X \times \mathcal{P}(X) \mapsto B_{\mathrm{bool}}.
$$

Consider $X = \lbrace 1,2\rbrace$ and $A = \lbrace 2\rbrace$. The confusion matrix:

Table 7: Bernoulli Model for $X \mapsto \mathrm{bool}$

|               | $1_\emptyset$ | $1_{\lbrace 1\rbrace}$ | $1_{\lbrace 2\rbrace}$ | $1_{\lbrace 1,2\rbrace}$ |
|---------------|---------------|-------------|-------------|---------------|
| $1_\emptyset$ | $(1-\epsilon)^2$ | $\epsilon(1-\epsilon)$ | $\epsilon(1-\epsilon)$ | $\epsilon^2$ |
| $1_{\lbrace 1\rbrace}$   | $0$           | $1-\epsilon$ | $0$ | $\epsilon$ |
| $1_{\lbrace 2\rbrace}$   | $0$           | $0$         | $1-\epsilon$ | $\epsilon$ |
| $1_{\lbrace 1,2\rbrace}$ | $0$           | $0$         | $0$         | $1$           |

We do not know the latent set $A = \lbrace 2\rbrace$. We only have the approximation $B_{X \mapsto \mathrm{bool}}(A)$, and we use it as a stand-in for $A$.

In row 3 (latent $\lbrace 2\rbrace$), the first two columns are zero. This makes sense: no false negatives, only false positives.

With probability $1-\epsilon$ the output is correct, with probability $\epsilon$ it is wrong. This is a Bernoulli Set, and we can use it to provide information about the latent set.

On equality: $\Pr\lbrace B_{X \mapsto \mathrm{bool}}(A) = A\rbrace = 1-\epsilon$. But typically people care about point queries: what is the probability that a positive test result is correct?
$$
\Pr\lbrace x \in B_{X \mapsto \mathrm{bool}}(A)\rbrace.
$$

The true positive rate is 1 (by construction), the false positive rate is $\epsilon$. Membership tests yield Bernoulli Boolean values:
$$
    x \in B_{X \mapsto \mathrm{bool}}(A) : X \mapsto \mathrm{bool}^{(2)}.
$$

## Conclusion

The Bernoulli Model is a way to think about uncertainty in function outputs and how that uncertainty propagates through computation. The uncertainty typically arises from trading space for accuracy. More space means a closer approximation to the latent function.
