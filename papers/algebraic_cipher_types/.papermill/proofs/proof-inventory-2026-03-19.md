# Proof Inventory: Composable Oblivious Algebraic Data Types

**Date**: 2026-03-19
**Paper**: `papers/algebraic_cipher_types/`
**Purpose**: Catalog every mathematical claim, assess status, flag what is worth formalizing

---

## Notation

- **Status**: Proven / Sketched / Asserted / Conjectured / Empty
- **Correct?**: Yes / Likely / Unclear / No / N/A
- **Worth formalizing?**: Yes (which paper) / No / Already done (where)

---

## Section: ob_type.tex (Cipher value type model)

### Claim 1: Approximate obfuscated AND probabilities
**Location**: ob_type.tex, lines 184-198
**Statement**: For an obfuscated Boolean type with proportion epsilon of cipher values mapped to OT(True):
- P(AND(OT(True), OT(True)) = OT(True)) = 1
- P(AND(OT(True), OT(False)) = OT(True)) = epsilon
- P(AND(OT(False), OT(True)) = OT(True)) = epsilon
- P(AND(OT(False), OT(False)) = OT(True)) = epsilon

**Status**: Asserted. No proof; justified by the construction where epsilon proportion of cipher values are OT(True) and only true-true pairs are perfectly mapped.
**Correct?**: Likely, given the specific construction described (map only true-true pairs, let everything else hit the noise floor). The epsilon rate comes from the random-hash behavior on unmapped inputs.
**Worth formalizing?**: No. This is a special case of the general Bernoulli error model already formalized in bernoulli_data_type.

---

### Claim 2: Space complexity for approximate Boolean operations
**Location**: ob_type.tex, line 202
**Statement**: Expected space complexity for AND on obfuscated Booleans is O(|OT(True)|^2).
**Status**: Asserted.
**Correct?**: Likely. Only true-true pairs are stored; the rest rely on random hash behavior. Number of true-true pairs is |OT(True)|^2.
**Worth formalizing?**: No. Subsumed by general cipher map space complexity analysis.

---

### Claim 3: Empty theorem on optimal space complexity for black box Boolean functions
**Location**: ob_type.tex, lines 218-220
**Statement**: "Theorem: Here."
**Status**: Empty. The theorem body is a placeholder.
**Correct?**: N/A
**Worth formalizing?**: The intended claim (optimal space complexity for a black box cipher Boolean function parametrized by valid inputs, OT(True) proportion, OT(False) proportion, and OT(Null) proportion) is worth developing in a future algebraic cipher types paper.

---

### Claim 4: Corollary -- space O(p) when q=r=0.5
**Location**: ob_type.tex, lines 223-225
**Statement**: If q = r = 0.5 (equal proportion true and false), then space complexity is O(p) where p is the number of valid input combinations.
**Status**: Asserted (corollary of the empty theorem).
**Correct?**: Plausible. If half the cipher values are true and half false, a cipher map only needs to store the p valid pairs.
**Worth formalizing?**: Only as part of the full theorem above.

---

### Claim 5: Obfuscated type as functor / natural transformation
**Location**: ob_type.tex, lines 230-236
**Statement**: An obfuscated type is a functor T -> OT(T) preserving structure over a restricted set of functions. It is actually a set of functors (one per random obfuscation). Natural transformations allow mapping between functors.
**Status**: Sketched (6 lines, no development).
**Correct?**: The intuition is sound but imprecise. Whether this satisfies formal functor/natural-transformation laws depends on how "preserving structure over a restricted set of functions" is defined. In the approximate setting, functoriality (preserving composition) holds only up to error.
**Worth formalizing?**: Not in this form. The cipher-map-formalism already notes the monad caveat. A categorical treatment would need to handle the approximate composition carefully (lax functor or similar). Low priority.

---

### Claim 6: Orbit/closure analysis of information leaks
**Location**: ob_type.tex, lines 238-246
**Statement** (informal): Operations generate orbits of known cipher values. The ratio of known cipher values to total cipher values measures confidentiality loss. Operations like AND(X, NOT(X)) = false reveal specific cipher values, and ideally these map to the same representation to avoid wasting space.
**Status**: Asserted (informal TODO paragraph).
**Correct?**: Yes, the intuition is correct. Operations that produce algebraically determined values (identities, zeros, tautologies) reveal cipher representations. The closure grows monotonically with additional operations.
**Worth formalizing?**: **Yes -- high priority for the new algebraic cipher types paper.** This needs: (a) a formal definition of orbit closure under a set of operations on cipher types; (b) a monotonicity theorem; (c) quantitative confidentiality bound.

---

### Claim 7: Composition of trusted/untrusted computation
**Location**: ob_type.tex, lines 580-596
**Statement**: Given h = f_1 o ... o f_n, we can partition it as: first k functions on trusted machine, next l functions (in cipher form) on untrusted machine, final m functions on trusted machine, mediated by encoder g and decoder g^{-1}.
**Status**: Asserted. The composition formula is stated but relies on the cipher maps being composable (chaining OT(f_{k+1}) o ... o OT(f_{k+l})).
**Correct?**: Yes, given composability (Property 4 of cipher maps). The formula as written has a minor notational issue (missing "o" between OT(f_{k+l}) and g^{-1} on line 595), but the structure is correct.
**Worth formalizing?**: **Already done** -- this is essentially the composition theorem in cipher-map-formalism.md Section 1.3 Property 4 and Section 5 (trusted/untrusted model). No need to re-derive.

---

### Claim 8: Cipher types are non-regular
**Location**: ob_type.tex, lines 630-634
**Statement**: An oblivious type is a non-regular type since it does not necessarily support comparison (= : OT(T) x OT(T) -> OT(Bool)) or default construction.
**Status**: Asserted.
**Correct?**: Yes. Equality on cipher types either requires the trapdoor (so it cannot be exposed to the untrusted machine) or reveals information (each equality test reveals one bit). Default construction is problematic because a default value is a known value.
**Worth formalizing?**: Worth stating as a **remark** in the new algebraic cipher types paper. Not a theorem; it is a design consequence.

---

### Claim 9: Equality operator on cipher types has false negative behavior
**Location**: ob_type.tex, lines 655-658
**Statement**: Equality on cipher types: if it returns true, they are equal; if false, they may be unequal (with true negative rate tnr) or equal (with false negative rate 1 - tnr).
**Status**: Asserted.
**Correct?**: Yes, because multiple representations of the same value will have different bit patterns. Representational equality implies value equality, but representational inequality does not imply value inequality.
**Worth formalizing?**: Useful as a lemma in the algebraic cipher types paper, specifically under the section on representation uniformity and its consequences. The false-negative rate for equality is 1 - 1/K(x) for a value with K(x) representations.

---

### Claim 10: Information cascade from default construction + successor
**Location**: ob_type.tex, lines 661-679
**Statement**: If an integer cipher type OT(Z) supports default construction of OT(0) and a successor operation, then repeated application reveals cipher representations for all non-negative integers. Division provides another path: OT(x)/OT(x) = OT(1), then successor reveals all values.
**Status**: Asserted (informal argument).
**Correct?**: Yes. This is a concrete instance of the orbit closure principle (Claim 6). The orbit of OT(0) under successor is the entire non-negative cipher type. The orbit of any OT(x) under {division, successor} includes OT(1) and hence the entire type.
**Worth formalizing?**: **Yes, as examples in the orbit/closure section** of the new paper. These are the motivating examples for the general theory.

---

## Section: ob_primitive_types.tex (Primitive obfuscated algebraic data types)

### Claim 11: OT(Void) = Void
**Location**: ob_primitive_types.tex, lines 108-113
**Statement**: Since Void has no values, OT(Void) is equivalent to Void. There is only one function Void -> X (the absurd function).
**Status**: Asserted.
**Correct?**: Yes. There is nothing to obfuscate.
**Worth formalizing?**: Only as a base case in the algebraic type theory. Trivial; state without proof.

---

### Claim 12: Cardinality of function spaces involving Unit
**Location**: ob_primitive_types.tex, lines 115-119
**Statement**: |Unit -> X| = |X|, |X -> Unit| = 1, |Unit -> Unit| = 1 (identity function). For partial functions, |X ->? Unit| = 2^|X|.
**Status**: Asserted.
**Correct?**: Yes. Standard type theory.
**Worth formalizing?**: No. Standard; cite or state without proof.

---

### Claim 13: Sum-type confidentiality/composability trade-off
**Location**: ob_primitive_types.tex, lines 125-137
**Statement**: OT(X) + OT(Y) reveals which branch was taken but preserves composability with functions expecting OT(X) or OT(Y). OT(X+Y) hides which branch but impairs composability: functions on OT(X) or OT(Y) cannot be applied without pattern matching, which requires the trapdoor. This is a fundamental trade-off.
**Status**: Asserted (informal).
**Correct?**: Yes. This follows from the semantics of sum types: pattern matching on a tagged union requires knowing the tag. In OT(X+Y), the tag is encrypted, so only the trusted machine can pattern-match. In OT(X)+OT(Y), the tag is visible (it is the structural position), so any machine can pattern-match, but the tag is leaked.
**Worth formalizing?**: **Yes -- this is the CORE contribution for the new paper.** Needs a theorem: (a) any cipher type for X+Y that hides the tag must prevent pattern matching by the untrusted machine; (b) any cipher type that permits pattern matching by the untrusted machine reveals the tag. Proof via information-theoretic argument.

---

### Claim 14: Three-monad pipeline (restrict -> partial -> embed -> noise -> cipher)
**Location**: ob_primitive_types.tex, lines 146-158
**Statement**: Given f : X -> Y, the cipher construction proceeds in five steps:
1. Restrict f to A subset X
2. Extend to partial function on A + {epsilon_1,...,epsilon_k}
3. Embed codomain into Y + {epsilon_1,...,epsilon_r}
4. Apply noise: make total by mapping undefined inputs to random outputs
5. Apply cipher: replace values with opaque cipher representations

**Status**: Sketched. Each step is described but the formal properties of the composition are not proven.
**Correct?**: Yes. This is the direct precursor to the construction layers in cipher-map-formalism.md Section 1.2.
**Worth formalizing?**: **Already done** in cipher-map-formalism.md. The formalism presents this as three layers (undef, noise, cipher) and explicitly credits this paper. No need to re-derive.

---

### Claim 15: Cipher monad C_{M,N,S} type constructor
**Location**: ob_primitive_types.tex, lines 174-192
**Statement**: The cipher type constructor C_{M,N,S}(a) has: (a) cipher: a -> C(a), (b) decipher: C(a) -> Maybe(a), (c) bind: 2^a x (a -> b) -> (C(a) -> C(b)), where bind generates a cipher function that is correct on A and a random hash outside A.
**Status**: Sketched. The types are stated, the bind semantics are described, but no laws are verified and no formal construction is given.
**Correct?**: The types are plausible. Whether this satisfies monad laws (bind associativity, unit laws) is unverified, and the cipher-map formalism explicitly notes this is an open question.
**Worth formalizing?**: **Partially.** The bind operation is essentially the cipher map construction itself. The monad-law question is interesting but not essential. What matters is that the construction produces objects satisfying the four properties. Already addressed by cipher-map-formalism.md.

---

### Claim 16: Type erasure hierarchy
**Location**: ob_primitive_types.tex, lines 194-199
**Statement**: C_{M,N,S}(a) can be progressively type-erased: C_{M,N}(a) (drop secret), C_N(a) (drop multiplicity), C_{M,N} (drop value type), C_N (maximally erased, only know byte length).
**Status**: Asserted.
**Correct?**: Yes. Each erasure loses information and reduces the untrusted machine's ability to type-check.
**Worth formalizing?**: Worth mentioning in the obfuscation hierarchy section. Not a theorem; it is a design taxonomy.

---

### Claim 17: False mapping rate decomposition
**Location**: ob_primitive_types.tex, lines 202-216
**Statement**: For a partial function, the false mapping rate for element y is P(f(x) = y | x not in Dom(f)) = epsilon_y, and the total false mapping rate is sum over y of epsilon_y = epsilon. Equivalently, sum of true negative rates = 1 - epsilon.
**Status**: Asserted with equation.
**Correct?**: Yes. This is the definition of per-element and total false mapping rates for partial functions, with mutual exclusivity of outcomes.
**Worth formalizing?**: **Already done** in bernoulli_data_type. The Bernoulli model for per-element error rates is the same concept.

---

### Claim 18: Approximate map achieves information-theoretic lower bound
**Location**: ob_primitive_types.tex, lines 222-228
**Statement**: An optimal approximate map obtains the information-theoretic lower bound of -1.44 log_2(epsilon) bits per positive element, same as an approximate set.
**Status**: Asserted (within an example, marked "WORK THIS OUT EXACTLY").
**Correct?**: The lower bound for approximate sets is well-established (Carter et al., Broder & Mitzenmacher). Whether an "approximate map" (partial function with false-mapping behavior) achieves the same bound depends on the construction. The claim is plausible for the unary predicate case (isomorphic to approximate set) but unproven for general functions.
**Worth formalizing?**: **Worth investigating** for the cipher-maps paper. The space complexity of general cipher maps (not just predicates) as a function of error rate is an important open question.

---

## Section: ob_type.tex (duplicated in ob_primitive_types.tex) -- k-ary predicate model

### Claim 19: FPR is Bernoulli distributed (maximum entropy)
**Location**: kary_pred.tex lines 165-173 (also ob_primitive_types.tex lines 227-235)
**Statement**: The false positive rate maximizing uncertainty given expectation epsilon and support {True, False} is Bernoulli distributed: FPR ~ Ber(epsilon).
**Status**: Proven. The proof appeals to the maximum entropy property of the Bernoulli distribution on binary support with a given mean.
**Correct?**: Yes. This is a standard result in information theory.
**Worth formalizing?**: **Already done** in bernoulli_data_type. This is the foundational theorem of the Bernoulli model.

---

### Claim 20: Number of false positives is binomially distributed
**Location**: kary_pred.tex lines 187-196 (also ob_primitive_types.tex)
**Statement (Theorem, labeled thm:fpbinom_binary)**: Given FPR ~ Ber(epsilon) and n negatives, the number of false positives FP_n ~ Bin(n, epsilon).
**Status**: Proven. Proof: sum of n iid Bernoulli RVs is binomial.
**Correct?**: Yes.
**Worth formalizing?**: **Already done** in bernoulli_data_type.

---

### Claim 21: Realized false positive rate distribution
**Location**: kary_pred.tex lines 200-221 (also ob_primitive_types.tex)
**Statement (Theorem, labeled thm:truefpr)**: FPR_n = FP_n / n has expectation epsilon and variance epsilon(1-epsilon)/n. By large-sample approximation, FPR_n ~ N(epsilon, epsilon(1-epsilon)/n).
**Status**: Proven. Proof derives expectation and variance from binomial properties.
**Correct?**: Yes. Standard result.
**Worth formalizing?**: **Already done** in bernoulli_data_type.

---

### Claim 22: True negatives are binomially distributed
**Location**: kary_pred.tex lines 225-231 (also ob_primitive_types.tex)
**Statement (Corollary, labeled cor:tnbinom_binary)**: TN_n ~ Bin(n, 1 - epsilon).
**Status**: Stated as corollary of binomial properties. No separate proof needed.
**Correct?**: Yes. TN = n - FP; if FP ~ Bin(n, epsilon), then TN ~ Bin(n, 1-epsilon).
**Worth formalizing?**: **Already done** in bernoulli_data_type.

---

### Claim 23: False negatives are binomially distributed
**Location**: kary_pred.tex lines 234-240 (also ob_primitive_types.tex)
**Statement (Theorem, labeled thm:fnbinom_binary)**: FN_p ~ Bin(p, eta) where p is the number of positives and eta is the false negative rate.
**Status**: Stated without proof (but proof is symmetric to Claim 20).
**Correct?**: Yes. Same argument as FP, applied to positives with false negative rate.
**Worth formalizing?**: **Already done** in bernoulli_data_type.

---

### Claim 24: Expected number of pairs testing True
**Location**: kary_pred.tex lines 243-249 (also ob_primitive_types.tex)
**Statement (Theorem)**: Expected number of True results = epsilon * |T|^2 + (1 - epsilon - eta) * p.
**Status**: Stated without proof.
**Correct?**: Yes. True positives: (1-eta)*p. False positives: epsilon*n = epsilon*(|T|^2 - p). Total testing True: (1-eta)*p + epsilon*(|T|^2 - p) = epsilon*|T|^2 + (1 - epsilon - eta)*p.
**Worth formalizing?**: **Already done** in bernoulli_data_type.

---

### Claim 25: Optimal space complexity conjecture
**Location**: kary_pred.tex lines 251-266, ob_primitive_types.tex lines 151-165 (appears THREE times in the paper)
**Statement (Conjecture)**: Optimal space for an oblivious abstract data type is -(1-eta)*p*log_2(epsilon) bits when positives are fewer; -(1-eta)*n*log_2(1-epsilon) bits when negatives are fewer; worst case -(1-eta)*prod(u_i)*log_2(epsilon) when p = n.
**Status**: Conjectured. No proof attempted.
**Correct?**: The first formula -(1-eta)*p*log_2(epsilon) generalizes the well-known approximate set lower bound (-p*log_2(epsilon) for eta=0). The generalization to k-ary predicates and non-zero false negative rate is plausible but unproven. The "worst case" formula seems correct dimensionally.
**Worth formalizing?**: **Worth investigating** as a theorem in the cipher-maps paper or a separate information-theoretic note. The unary predicate case (k=1) is well-established; the general k-ary case would be a contribution.

---

## Section: boolean_algebra.tex

### Claim 26: Obfuscated Boolean algebra on n-bit vectors
**Location**: boolean_algebra.tex, lines 9-18
**Statement**: The obfuscated Boolean algebra (OT(Bit^n), OT(AND), OT(OR), OT(NOT), OT(1^n), OT(0^n)) with bitwise operators is isomorphic to any value type of cardinality 2^n and can implement obfuscated sets over n elements with full set-theoretic operations. However, the space for cipher operations like OT(AND) makes it impractical except for very small n.
**Status**: Asserted.
**Correct?**: Yes. A Boolean algebra on n-bit vectors represents the powerset of an n-element universe. The cipher map for AND : Bit^n x Bit^n -> Bit^n has 2^n * 2^n entries, each mapping to Bit^n -- so the space is O(2^{2n} * n), which is indeed impractical for large n.
**Worth formalizing?**: The space complexity calculation is worth stating precisely in the new paper as an example of the exponential type's space cost. The isomorphism claim is standard.

---

## Section: ob_tm.tex (Cipher Turing machine)

### Claim 27: Cipher Turing machine definition
**Location**: ob_tm.tex, lines 33-44
**Statement**: A cipher TM replaces states Q with OT(Q), input alphabet Sigma with OT(Sigma), tape alphabet Gamma with OT(Gamma), and transition function delta with a cipher map delta : OT(Q) x OT(Gamma) -> OT(Q) x OT(Gamma) x {L,R}.
**Status**: Defined (no claim to prove).
**Correct?**: The definition is well-formed. Note that {L,R} (head direction) is NOT ciphered -- this is an intentional design choice that the paper acknowledges leaks information.
**Worth formalizing?**: **Yes, as a definition in the new paper's Section 5.** The definition itself is clean and worth preserving.

---

### Claim 28: Multiple representations give different execution patterns
**Location**: ob_tm.tex, lines 56-58
**Statement**: Given different representations of the same input x, some patterns may still occur in the sequence of symbols read and written. Moreover, the head movement pattern is identical for the same input regardless of representation.
**Status**: Asserted.
**Correct?**: Partially. For a deterministic TM, the head movement is determined by the state sequence, which IS affected by cipher representations (different representations may lead to different transition paths if the transition function's cipher map produces different outputs). However, if the cipher map is correct (eta=0), then the state sequence will be correct and thus the head movement WILL be the same. With eta > 0, errors can propagate and change the execution pattern.
**Worth formalizing?**: Yes. A proposition: "For a correct (eta=0) cipher TM, all representations of the same input produce the same head movement pattern." This is a confidentiality limitation worth stating precisely.

---

### Claim 29: Space complexity divorced from domain cardinality
**Location**: ob_tm.tex, lines 68-69
**Statement**: For cipher maps, space complexity is a function of domain cardinality. For cipher TMs, space complexity can be divorced from the domain of definition.
**Status**: Asserted.
**Correct?**: Yes. A cipher map (lookup table) stores one entry per domain element, so space is O(|domain|). A cipher TM stores the transition function (size O(|Q| * |Gamma|)) and the tape, independent of the input domain (which can be Sigma^*, arbitrarily large).
**Worth formalizing?**: **Yes, as a proposition** in the new paper: cipher TM space is O(|Q| * |Gamma|) while cipher map space for the same function is O(|domain|). For large domains, the cipher TM is asymptotically cheaper in space.

---

### Claim 30: Multiple transition function versions add confidentiality at space cost
**Location**: ob_tm.tex, lines 62-63
**Statement**: An alternative strategy to obfuscating head movement: make the transition function contain multiple versions indexed by cipher tags. This costs space rather than time. Can be combined with oblivious TM for added confidentiality.
**Status**: Asserted (sketch only).
**Correct?**: Plausible. If the transition function has K versions, each a correct implementation with different cipher representations, then different executions can use different versions, making head movement patterns more diverse. Space cost: K times the single-version cost.
**Worth formalizing?**: Worth developing further but needs more detail on how "multiple versions indexed by cipher tags" actually works. Medium priority.

---

### Claim 31: Branching reveals cipher value mappings
**Location**: ob_tm.tex, lines 76-93
**Statement**: The if-then-else construct reveals which cipher values map to True or False, because the branch taken is observable. This is worse than AND(X, NOT(X)) = false (which reveals one value) because branching reveals ALL mappings. Omitting branching is the most reliable mitigation. Alternatively, implement specific if-expressions as cipher maps (losing composability) or use cipher TMs.
**Status**: Asserted (informal argument).
**Correct?**: Yes. This is another instance of the orbit/closure principle: branching is an operation that expands the orbit maximally.
**Worth formalizing?**: **Yes, as an example** in the orbit/closure section. The observation that branching is uniquely bad for confidentiality (it effectively gives the adversary an oracle for the predicate) should be stated precisely.

---

## Section: entropy.tex

### Claim 32: Algebraic type isomorphisms
**Location**: entropy.tex, lines 43-67
**Statement**: Standard algebraic type isomorphisms: Void + Void ~ Void, Void + Unit ~ Unit, Unit + Unit ~ Bool, Void x X ~ Void, Unit x X ~ X, (Unit + Unit) x (Unit + Unit) ~ Bool x Bool (4 values), X^0 = Unit, X^1 = X.
**Status**: Asserted.
**Correct?**: Yes. Standard type theory / algebra of types.
**Worth formalizing?**: No. Standard; state without proof.

---

### Claim 33: Optimal model -- every construction has unseen representation
**Location**: entropy.tex, lines 83-84
**Statement**: The optimal model is where every time an obfuscated value OT(x) of x is constructed, it has a state (representation) that has never been seen before.
**Status**: Asserted (informal).
**Correct?**: This is an idealization. It requires K(x) >= (number of times x is encoded), which may be infeasible for frequently-used values. The cipher-map formalism addresses this more carefully with the representation uniformity property and the delta parameter.
**Worth formalizing?**: No. Already subsumed by Property 2 (representation uniformity) in cipher-map-formalism.md.

---

## Section: algebraic_oblivious_operations.tex

### Claim 34: Composition reveals intermediate correlations
**Location**: algebraic_oblivious_operations.tex, lines 61-67
**Statement**: Given OT(f) : OT(Y) -> OT(Z) and OT(g) : OT(X) -> OT(Y), the composition OT(f) o OT(g) reveals the intermediate cipher value OT(y), creating correlations between OT(x), OT(y), and OT(z) that would not be visible if the composition were a single cipher map.
**Status**: Asserted.
**Correct?**: Yes. This is a fundamental limitation of sequential evaluation on the untrusted machine. A composed cipher map (single lookup table for f o g) hides intermediates; sequential evaluation exposes them.
**Worth formalizing?**: **Yes.** This should be a proposition in the new paper or in cipher-maps: "Sequential evaluation of composed cipher maps reveals intermediate cipher values. Hiding intermediates requires constructing a single cipher map for the composition, at the cost of space proportional to the domain of the first function."

---

### Claim 35: Orbit definition for unary functions
**Location**: algebraic_oblivious_operations.tex, lines 31-33
**Statement**: The orbit of a unary function f : X -> X for some x in X is the set of values reachable from x through function composition starting with f(x).
**Status**: Defined.
**Correct?**: Yes. Standard definition of orbit under iterated function application.
**Worth formalizing?**: Yes, as the starting definition for the orbit/closure analysis in Section 4 of the proposed new paper.

---

## Section: totally_ordered.tex

### Claim 36: Oblivious ordered set via pair membership
**Location**: totally_ordered.tex, lines 47-54
**Statement**: Given a strict total order on S, construct the set of concatenated cipher pairs {OT(x) ++ OT(y) : x < y} and make an oblivious set of it. Then OT(x) < OT(y) iff (OT(x) ++ OT(y)) is in the oblivious set.
**Status**: Sketched (construction described but properties not fully derived).
**Correct?**: Yes, this is a valid construction. The false positive and false negative rates of the comparison inherit from the oblivious set's rates. Space is O(p^2) where p = |S|, since the number of pairs with x < y is p(p-1)/2.
**Worth formalizing?**: This belongs in the encrypted-search or applications paper, not the algebraic types paper. Low priority for this ecosystem.

---

### Claim 37: Space comparison -- pair approach vs. rank approach
**Location**: totally_ordered.tex, lines 15 (also ob_primitive_types.tex)
**Statement**: The pair-based approach (maximum confidentiality) requires O((1-eta)^2 * p^2 * log_2(epsilon)) space. The rank-based approach (oblivious map of rank) requires O(p * (1-eta) * log_2(p/epsilon)) space.
**Status**: Asserted.
**Correct?**: The pair approach: number of ordered pairs is O(p^2), each stored in an approximate set at -log_2(epsilon) bits per element, so O(p^2 * log_2(1/epsilon)). The (1-eta)^2 factor accounts for false negatives on both elements. The rank approach: one cipher map entry per element, each entry is log_2(p) bits for the rank, and the map has space -log_2(epsilon) per entry. Roughly O(p * log_2(p/epsilon)). The orders of magnitude are correct.
**Worth formalizing?**: Only if pursuing the totally-ordered cipher set as a standalone result. Low priority.

---

## Section: apps.tex

### Claim 38: Encrypted Boolean Search type signatures
**Location**: apps.tex, lines 12-64
**Statement**: A hierarchy of type signatures for the encrypted Boolean search "relevant" function, from fully obfuscated to partially obfuscated, trading off confidentiality for practicality.
**Status**: Asserted (type signatures, no proofs).
**Correct?**: The type signatures are well-formed and the trade-offs described are accurate.
**Worth formalizing?**: Belongs in the encrypted-search paper. Not relevant to algebraic cipher types.

---

## Summary

### Claims worth formalizing for the new algebraic cipher types paper

| # | Claim | Priority | Type |
|---|-------|----------|------|
| 13 | Sum-type confidentiality/composability trade-off | **Critical** | Theorem |
| 6 | Orbit/closure analysis of information leaks | **High** | Definition + Theorem |
| 10 | Information cascade examples (default + successor, division) | **High** | Examples/corollaries |
| 27 | Cipher Turing machine definition | **High** | Definition |
| 29 | Cipher TM space divorced from domain cardinality | **High** | Proposition |
| 28 | Correct cipher TM preserves head movement pattern | **Medium** | Proposition |
| 31 | Branching maximally expands orbit | **Medium** | Example |
| 34 | Sequential composition reveals intermediates | **Medium** | Proposition |
| 8 | Cipher types are non-regular | **Low** | Remark |
| 9 | Equality on cipher types has false negatives | **Low** | Lemma |
| 3 | Optimal space for black box cipher Boolean function | **Low** | Open problem |

### Claims already formalized elsewhere

| # | Claim | Where |
|---|-------|-------|
| 14 | Three-monad pipeline | cipher-map-formalism.md Section 1.2 |
| 7 | Trusted/untrusted composition | cipher-map-formalism.md Section 5 |
| 19-24 | Bernoulli/binomial error model | bernoulli_data_type papers |
| 15 | Cipher monad construction | cipher-map-formalism.md (as construction layers) |

### Claims not worth formalizing

| # | Claim | Reason |
|---|-------|--------|
| 1-2 | Approximate Boolean operations | Special case of general Bernoulli model |
| 4 | Space O(p) when q=r=0.5 | Corollary of unproven theorem |
| 5 | Functor/natural transformation | Too vague; monad caveat already noted |
| 11-12 | Void/Unit types | Standard; state without proof |
| 16 | Type erasure hierarchy | Taxonomy, not a theorem |
| 17 | False mapping rate decomposition | Already in bernoulli_data_type |
| 32 | Algebraic type isomorphisms | Standard type theory |
| 33 | Optimal model (unseen representations) | Subsumed by representation uniformity |

### Open conjectures worth investigating

| # | Claim | Notes |
|---|-------|-------|
| 25 | Optimal space complexity for k-ary predicates | Unary case is known; general case would be a contribution |
| 18 | Approximate map achieves information-theoretic lower bound | Important for cipher-maps |
