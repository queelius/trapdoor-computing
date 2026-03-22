# Proof Verification: Cipher Maps Unified
Date: 2026-03-19
Paper: `paper/cipher_maps.tex`
Formalism reference: `/home/spinoza/github/trapdoor-computing/formalism/cipher-map-formalism.md`

## Methodology

Every formal claim (theorem, lemma, proposition, corollary) and every definition with claimed properties is verified step-by-step. Claims are cross-referenced against the formalism document. Verdict scale:

- **VERIFIED**: Proof is logically sound as written.
- **LIKELY-CORRECT**: Minor gaps but the result is almost certainly true; gaps are fillable.
- **UNCERTAIN**: Significant gaps or unclear reasoning; result may be true but proof does not establish it.
- **ERROR**: Proof contains a logical error or the claim is false.
- **NO-PROOF-GIVEN**: Claim is stated without proof.

---

## Section 2: Algebraic Foundations

### Definition 2.1: Monoid (lines 162-170)

**Statement**: Standard definition of monoid (S, *, e) with closure, associativity, identity.

**Assessment**: Standard and correct. No issues.

**Verdict**: N/A (definition)

---

### Definition 2.2: Group (lines 172-174)

**Statement**: Group is a monoid with inverses.

**Assessment**: Standard and correct.

**Verdict**: N/A (definition)

---

### Definition 2.3: Cipher Functor (lines 182-198)

**Statement**: Given a monoid (S, *, e) and encoding set A subset of S, the cipher functor c_A produces a cipher system (c_A S, encode, decode) with:
1. Carrier set c_A S
2. Encoding: encode: S x N -> c_A S
3. Decoding: decode: c_A S -> S with decode(encode(s,k)) = s and encode(decode(c), k) in c_A S
4. Representation multiplicity: distinct encodings for each s

**Assumptions (explicit)**: S is a monoid, A is a subset of S.

**Assumptions (implicit)**:
- encode is injective in k for fixed s (claimed in item 4 but not formally stated as an axiom)
- The encoding set A plays no explicit role in the definition as stated -- it is mentioned as a parameter but does not appear in any axiom. This is a design issue noted in Review 2 as part of M5.

**Issues**:
1. The encoding set A appears in the definition name but not in the axioms. The definition says "subset A called the encoding set" but never uses A. Looking at the subsequent construction (Definition 2.4, Example 2.1), A determines which elements can be "directly encoded" -- but this constraint is not captured in Definition 2.3's axioms.
2. "cipher functor c_A" is named but not yet shown to be a functor. That comes later in Theorem 7.4. Calling it a functor at the definition stage is premature.
3. The axiom decode(encode(s,k)) = s is a left-inverse condition. The axiom encode(decode(c), k) in c_A S just says re-encoding a decoded value stays in the carrier set -- this is trivially true if c_A S is defined as the image of encode, and vacuously adds nothing.

**Cross-reference**: The formalism document (Definition 1.1) defines a cipher map differently -- as a tuple (f-hat, enc, dec, s) where f-hat is a total function on bit strings. This is a fundamentally different (and better) definition. The formalism does not use the cipher functor / encoding set abstraction at all. The cipher functor is an artifact of the earlier algebraic cipher types paper and does not appear in the formalism's four-property framework.

**Verdict**: N/A (definition, but has structural issues)

---

### Definition 2.4: Lifted Operation (lines 204-208)

**Statement**: Given cipher system and representation selector rho, define x (c_A *) y = encode(decode(x) * decode(y), rho(decode(x)*decode(y), x, y)).

**Assessment**: Well-defined given the axioms: decode maps to S, * is closed in S, encode maps back to c_A S. The representation selector rho is a function producing a natural number index.

**Verdict**: N/A (definition, well-formed)

---

### Theorem 2.1: Cipher Monoid Properties (lines 212-236)

**Statement**: For any representation selector rho, (c_A S, c_A *, encode(e,0)) is a monoid.

**Assumptions (explicit)**: (S, *, e) is a monoid; cipher system from Definition 2.3; lifted operation from Definition 2.4; arbitrary rho.

**Assumptions (implicit)**: The claim is that this is a monoid on c_A S itself, not on the quotient c_A S / ~.

**Proof walkthrough**:

- Step 1 (Closure): decode(x), decode(y) in S; S closed under *; encode produces element of c_A S. -- **VALID**.

- Step 2 (Associativity): The proof shows decode((x c_A* y) c_A* z) = decode(x c_A* (y c_A* z)) by using decode(encode(s,k)) = s and associativity in S. This establishes that both sides decode to the same element of S. -- **VALID for the decode image**.

  However, the proof then acknowledges the problem: "To obtain equality in c_A S (not merely equivalence under decode), we note that a consistent selector satisfying [condition] ensures associativity holds in c_A S. In general, associativity holds up to the equivalence x ~ y iff decode(x) = decode(y)."

  This is a **concession that the theorem as stated is false for general rho**. The proof establishes associativity on the quotient c_A S / ~, not on c_A S itself. For (c_A S, c_A *, encode(e,0)) to be a monoid, associativity must hold as equality in c_A S, which requires a "consistent selector" -- a condition not assumed in the theorem statement.

- Step 3 (Identity): decode(encode(e,0) c_A* x) = e * decode(x) = decode(x). Again, this shows decode-level identity, not equality in c_A S. The proof does not show encode(e,0) c_A* x = x, only that decode(encode(e,0) c_A* x) = decode(x). For identity to hold in c_A S, we need encode(e,0) c_A* x = x, which means encode(decode(x), rho(decode(x), encode(e,0), x)) = x. This holds only if rho returns the original encoding index of x, which is not guaranteed.

**Cross-reference**: The formalism document does not have this theorem. The formalism works with cipher maps as total functions on bit strings and does not lift monoid structure. The Remark after the proof (lines 238-240) correctly identifies the quotient monoid as the natural setting.

**Verdict**: **ERROR**. The theorem claims (c_A S, c_A *, encode(e,0)) is a monoid for *any* representation selector rho. The proof shows this only for the quotient monoid c_A S / ~. The theorem should be restated for the quotient monoid. This was identified as M6 in Review 2.

**Notes**: The fix is straightforward: either (a) restate the theorem for c_A S / ~ (where it is correct and trivially follows from S being a monoid via the isomorphism decode), or (b) restrict to representation selectors satisfying an explicit consistency condition. Option (a) is preferable because it is honest about what the construction achieves.

---

### Theorem 2.2: Homomorphism (lines 246-266)

**Statement**: decode: c_A S -> S is a monoid homomorphism: decode(encode(e,0)) = e, and decode(x c_A* y) = decode(x) * decode(y).

**Assumptions**: Cipher system from Definition 2.3, lifted operation from Definition 2.4.

**Proof walkthrough**:

- Step 1 (Identity): decode(encode(e,0)) = e by the decoding axiom. -- **VALID**.

- Step 2 (Operation): decode(x c_A* y) = decode(encode(decode(x) * decode(y), rho(...))) = decode(x) * decode(y) by the decoding axiom decode(encode(s,k)) = s. -- **VALID**.

**Cross-reference**: This is a trivial consequence of the construction. The lifted operation is *defined* to decode, compute, and re-encode. So decode being a homomorphism is immediate from the definition -- it is not a deep result. The formalism document does not state this separately.

**Verdict**: **VERIFIED**. Correct but trivial by construction.

---

### Definition 2.5: Encoding Set Properties (lines 273-281)

**Statement**: An encoding set A is complete (A = S), generating (submonoid generated by A equals S), or minimal (no proper subset is generating).

**Assessment**: Standard algebraic definitions applied to this setting. Well-formed.

**Verdict**: N/A (definition)

---

### Proposition 2.1: Security-Efficiency Tradeoff (lines 283-293)

**Statement**: For a finite monoid S, if A is generating but not complete, then: (1) some elements require composite representations, (2) security increases with |S|/|A|, (3) computational overhead increases with average composition length.

**Assumptions (explicit)**: Finite monoid S, A generating but not complete.

**Assumptions (implicit)**: "Security" is not defined anywhere in the paper. What does "security increases with |S|/|A|" mean formally?

**Proof walkthrough**: No proof given. The three items are informal observations:
1. Elements in S \ A require representation as products of elements of A. -- This follows from A being generating: every element is a finite product of elements from A. For elements not in A, this product has length >= 2. **VALID as an observation**.
2. "Security increases with |S|/|A|" -- This is not a formal claim. What security model? What advantage measure? Without defining security, this is hand-waving. **UNJUSTIFIED**.
3. "Computational overhead increases with average composition length" -- True informally: representing an element as a product of k generators requires k-1 multiplications. **VALID as an observation**.

**Cross-reference**: The formalism document does not have this proposition. The formalism's Section 1.4 gives a parameter table but does not discuss encoding sets in this algebraic sense.

**Verdict**: **UNCERTAIN**. Items 1 and 3 are valid informal observations. Item 2 is meaningless without a security definition. Should be downgraded to a remark or given formal content.

---

### Example 2.1: Cipher Boolean (lines 320-329)

**Statement**: For the Boolean monoid ({0,1}, AND, 1) with encoding set A = {1}, the cipher functor produces cipher Booleans with lifted AND and security (observer cannot distinguish c_0^(k) from c_1^(k) without encoding secret).

**Assessment**:
- The monoid ({0,1}, AND, 1) is correct: AND is associative, 1 is the identity for AND. (Note: 0 AND x = 0 for all x, so 0 is the absorbing element, not the identity.)
- A = {1} is generating? We need {1} to generate all of {0,1} under AND. But the submonoid generated by {1} is just {1} (1 AND 1 = 1). So A = {1} is NOT generating for ({0,1}, AND, 1). This means 0 has no representation as a product of elements from A. The example is internally inconsistent with the encoding set theory from Section 2.3.
- However, Definition 2.3 does not actually require A to be generating -- it is just a subset. The encoding function encode is defined on all of S, not just A. So the example may still work if we interpret the cipher functor more broadly.
- "Security: An observer cannot distinguish c_0^(k) from c_1^(k) without the encoding secret" -- This is an informal claim with no formal backing. What encoding secret? The cipher functor definition has no secret.

**Cross-reference**: The formalism document discusses cipher Booleans indirectly through the HashSet construction (Section 2.1), which is much more concrete and does not use the cipher functor abstraction.

**Verdict**: **UNCERTAIN**. The example is superficially coherent but has internal inconsistencies (A = {1} does not generate {0,1} under AND) and makes unsupported security claims.

---

### Example 2.2: Multiplicative Group Cipher (lines 331-341)

**Statement**: For (Z_p*, *, 1) with A = {g} (primitive root), encode(a, j) = g^{k + j(p-1)} under modular exponentiation, with homomorphic multiplication and DLP-based security.

**Assessment**:
- (Z_p*, *, 1) is a group (and hence monoid). Correct.
- A = {g} where g is a primitive root. This IS generating for Z_p* since g generates the entire group. Correct.
- encode(a, j) = g^{k + j(p-1)} where a = g^k. But by Fermat's little theorem, g^{p-1} = 1 mod p. So g^{k + j(p-1)} = g^k * (g^{p-1})^j = g^k * 1^j = g^k = a. This means ALL representations encode(a, j) for different j are IDENTICAL: they all equal a. There is no representation multiplicity.

  This was identified as M7 in Review 2. The representation multiplicity property (item 4 of Definition 2.3) requires distinct encodings. But g^{k + j(p-1)} mod p = g^k mod p for all j. So the example violates the cipher functor's own definition.

- The homomorphic multiplication claim is correct but trivial: multiplying g^{k_a} * g^{k_b} = g^{k_a + k_b} in Z_p*. But this is just normal multiplication in the group -- no cipher structure is involved.

**Cross-reference**: The formalism document does not have a group cipher example. It uses HashSet, entropy map, and trapdoor boolean algebra as its three constructions, all of which are concrete hash-based constructions.

**Verdict**: **ERROR**. The representation multiplicity claim is false due to Fermat's little theorem. All "different" representations are identical in Z_p*. The example needs fundamental restructuring (e.g., ElGamal-style randomized encryption where encode(a, j) = (g^j, a * h^j) for a public key h).

---

## Section 3: Bernoulli Model Framework

### Definition 3.1: Bernoulli Approximation (lines 351-356)

**Statement**: Given a latent function p: X -> Y, a Bernoulli approximation p*: X -> Y satisfies Pr[p*(x) != p(x)] = e(x) where {e(x)} are a priori statistically independent random variables.

**Assessment**:
- The notation is confusing: e(x) is described as both a probability (Pr[...] = e(x)) and as a "random variable" ("statistically independent random variables"). If e(x) is a fixed probability, the {e(x)} are parameters, not random variables. If e(x) is itself random, this is a hierarchical Bayesian model, which is not what the rest of the paper assumes.
- This was identified as minor issue m16 in Review 2.
- The independence claim ("a priori statistically independent") is about the error events {p*(x) != p(x)} for different x, which is a reasonable assumption under the random oracle model.

**Cross-reference**: The formalism document (implicit in Section 1.3, Property 3) defines correctness as Pr[dec(f-hat(enc(x,k))) != f(x)] <= eta, which is cleaner: eta is a bound on the average error probability over random x and k.

**Verdict**: N/A (definition, but has a notational issue with e(x) being called a "random variable" when it appears to be a fixed probability)

---

### Definition 3.2: Bernoulli Confusion Matrix (lines 364-365)

**Statement**: For functions {p_1, ..., p_n} of type X -> Y, the confusion matrix Q = [q_{ij}] where q_{ij} = Pr[observe p_j | latent p_i].

**Assessment**: Standard definition of a confusion/channel matrix. The interpretation of "observe p_j | latent p_i" requires clarification -- are we observing the function identity or a single function evaluation? The definition is ambiguous but standard enough.

**Verdict**: N/A (definition)

---

### Definition 3.3: Induced Bernoulli Type (lines 382-399)

**Statement**: Given cipher type c_A S with probabilistic encoding, the induced Bernoulli type has Pr[B_S(s) = s'] = 1 - epsilon(s) if s' = s, and epsilon(s)/(|S|-1) if s' != s.

**Assessment**:
- This assumes a specific error model: when the cipher type errs, it produces a uniformly random wrong answer. This is a strong assumption not justified by the cipher functor construction.
- The definition mixes two different things: the cipher type (algebraic, exact decode by construction) and a Bernoulli approximation (probabilistic). Where do the errors come from? The cipher functor as defined has exact decoding: decode(encode(s,k)) = s. There are no errors in the algebraic construction.
- The connection text (lines 395-399) claims cipher types "with randomized encoding naturally exhibit Bernoulli behavior" but does not explain the mechanism.

**Cross-reference**: The formalism document explains the error mechanism clearly: errors come from (a) the seed search missing some elements (eta), (b) random non-domain inputs happening to decode to valid values (epsilon), and (c) hash collisions in the trapdoor boolean algebra. None of these are captured by the algebraic cipher functor.

**Verdict**: N/A (definition, but the connection between cipher types and Bernoulli errors is unjustified)

---

### Theorem 3.1: Bernoulli Entropy (lines 425-429)

**Statement**: The entropy of a Bernoulli model with confusion matrix Q is H(Bernoulli) = -sum_{i,j} q_{ij} log q_{ij}.

**Assessment**:
- The formula -sum_{i,j} q_{ij} log q_{ij} is NOT the entropy of the Bernoulli model. This formula doesn't even produce a well-defined entropy:
  - Each row of Q is a probability distribution (sums to 1), so -sum_j q_{ij} log q_{ij} is the conditional entropy H(observed | latent = i).
  - The joint entropy involves the prior distribution on latent values: H(observed, latent) = H(latent) + H(observed | latent).
  - The formula as stated sums over all i,j without weighting by the prior, producing sum_i H(observed | latent = i), which is not a standard entropy measure.
- No proof is given (labeled "theorem" but the "proof" is just the statement itself).
- This was identified as M2 in Review 2.

**Cross-reference**: The formalism document does not have an entropy theorem. It correctly uses H(Y) = -sum_y p_y log_2 p_y for the output distribution entropy (Definition 1.4, parameter mu).

**Verdict**: **ERROR**. The formula is wrong. It should either (a) be the conditional entropy H(observed | latent) = sum_i pi_i H(Q_i) where pi is the prior, or (b) be relabeled as "the sum of row entropies" with no claim that this is "the entropy of the Bernoulli model." The claim should be downgraded from a theorem (it has no proof) to a definition or remark.

---

## Section 4: Cipher Maps

### Definition 4.1: Cipher Map (lines 440-454)

**Statement**: A cipher map is an oblivious Bernoulli approximation f* = (f, C, Q) where f is the latent function, C is the computational basis, Q is the confusion matrix, and the implementation satisfies obliviousness conditions: (a) mappings only revealed through direct evaluation, (b) domain cannot be efficiently enumerated, (c) unmapped inputs behave as random oracles.

**Assessment**:
- "Oblivious Bernoulli approximation" is not previously defined.
- "Computational basis provided" (C) is not defined.
- The "obliviousness conditions" are informal English bullets, not formal mathematical conditions.
- "Mappings only revealed through direct evaluation" -- what does "direct evaluation" mean formally?
- "Domain cannot be efficiently enumerated" -- this is a computational complexity claim; what complexity model? What does "efficiently" mean?
- "Unmapped inputs behave as random oracles" -- this conflates the implementation (uses a random oracle) with a property (outputs are indistinguishable from random).
- This was identified as M1 in Review 2: obliviousness is never formally defined.

**Cross-reference**: The formalism document (Definition 1.1 + Section 1.3) provides the correct replacement: a cipher map is a tuple (f-hat, enc, dec, s) satisfying four measurable properties (totality, representation uniformity, correctness, composability). The formalism's definition is precise, parameterized, and testable. The paper's definition is vague.

**Verdict**: N/A (definition, but fatally imprecise -- this is the paper's central definition and it is not rigorous)

---

### Theorem 4.1: Cipher-Bernoulli Correspondence (lines 462-475)

**Statement**: Every cipher functor c_A induces a Bernoulli model where the confusion matrix entries are determined by the probability of selecting different cipher representations.

**Proof walkthrough**:
- The "proof" identifies three factors (encoding distribution, algebraic operations, decoding) that "combine to create a confusion matrix structure Q."
- No actual computation or derivation is given. The proof does not derive Q from the cipher functor definition. It just says these factors "combine" without saying how.
- The statement itself is vague: "determined by the probability of selecting different cipher representations" is not a formula.

**Cross-reference**: The formalism document does not have this theorem. The connection between cipher maps and Bernoulli models is through the error parameters (eta, epsilon), not through a confusion matrix derived from the cipher functor.

**Verdict**: **NO-PROOF-GIVEN**. The "proof" is a sketch at best. The theorem is too vague to be true or false -- it needs a precise statement before it can be verified.

---

### Proposition 4.1: Representation Indistinguishability (lines 481-483)

**Statement**: For any a in S, the representations {encode(a,k) : k in N} are computationally indistinguishable without knowledge of the encoding secret.

**Assessment**:
- "Computationally indistinguishable" is a formal cryptographic notion requiring specification of a distinguisher, security parameter, and negligible advantage bound. None are provided.
- "Encoding secret" is not defined in Definition 2.3 (the cipher functor). The cipher functor has no secret -- it is a purely algebraic construction.
- No proof is given.
- This claim is exactly the kind of hand-waving identified in M1: security/privacy claims without formal definitions.

**Cross-reference**: The formalism document (Property 2, Section 1.3) provides the correct replacement: representation uniformity is defined as d_TV(Q, Uniform) <= delta, where Q is the induced distribution on cipher values. This is a concrete, measurable property, not a computational indistinguishability claim.

**Verdict**: **NO-PROOF-GIVEN**. The claim is also ill-defined (no security model, no secret, no formal notion of indistinguishability).

---

## Section 5: Singular Hash Map Construction

### Definition 5.1: Hash-Based Cipher Construction (lines 498-508)

**Statement**: Construction using hash function h and serialization, finding seed sigma such that h(encode_S(s) || sigma) is in encode_{c_A S}(s) for all s in A.

**Assessment**: This is an algorithmic description rather than a mathematical definition. The structure is reasonable: find a seed that makes the hash decode correctly for all stored elements. This corresponds to the formalism's "batch construction" (Definition 1.1).

**Issue**: The definition references "the encoding set A" but Algorithm 1 (lines 530-552) does not use encoding sets -- it works with a generic map M of key-value pairs. There is an inconsistency between the algebraic framing (encoding sets) and the algorithmic construction (key-value maps). This was identified as m9 in Review 2.

**Verdict**: N/A (definition/algorithm, has consistency issues)

---

### Definition 5.2: Entropy Map (lines 514-522)

**Statement**: An entropy map encodes f: X -> Y by assigning prefix-free codes to Y, using hash h: X -> {0,1}*, and decoding y = Decode(h(x)) when the hash prefix matches.

**Assessment**: Correct high-level description matching the formalism's Section 2.2. The key idea is sound: prefix-free codes partition hash space, and the decode operation extracts the function value from the hash output.

**Cross-reference**: Matches formalism Section 2.2 (Entropy Map construction).

**Verdict**: N/A (definition, well-formed)

---

## Section 6: Theoretical Analysis

### Definition 6.1: Mean Encoding Length (lines 573-578)

**Statement**: mu = H(Y) = -sum_y p_y log_2 p_y where p_y = |{x in X : f(x) = y}| / |X|.

**Assessment**: Correct. This is the Shannon entropy of the output distribution. The notation mu = H(Y) is standard. The connection to prefix-free coding (Shannon's source coding theorem) is correctly invoked.

**Cross-reference**: Matches formalism Section 1.4 (parameter mu = H(Y)).

**Verdict**: N/A (definition, correct)

---

### Theorem 6.1: Information-Theoretic Lower Bound (lines 580-601)

**Statement**: Any data structure representing an approximate map f-hat: X -> Y union {bot} with false positive rate epsilon and false negative rate eta = 0 over n stored elements requires at least n(-log_2 epsilon + mu) bits.

**Assumptions (explicit)**: False positive rate epsilon, false negative rate eta = 0, n stored elements, mu = H(Y).

**Assumptions (implicit)**:
- The universe U satisfies |U| >> n.
- The output distribution (p_y) is known and fixed.
- Function values for different elements are independent draws from (p_y). This is a strong assumption -- in general, function values may be correlated.

**Proof walkthrough**:

- Step 1 (Membership component): "A counting argument shows that the number of distinguishable set-error configurations grows as binom(|U|, n) / epsilon^{|U|-n}; taking logarithms and applying Stirling's approximation yields a lower bound of n log_2(1/epsilon) bits."
  - This is a sketch, not a proof. The counting argument is not given. The formula binom(|U|,n) / epsilon^{|U|-n} is stated without derivation.
  - However, the n log_2(1/epsilon) lower bound for approximate membership (Bloom filter lower bound) is well-known. See Carter et al. (1978), Broder and Mitzenmacher (2004). The cite to Bloom (1970) is appropriate for context but Bloom did not prove the lower bound.
  - **VALID** as a known result, but the proof sketch is inadequate.

- Step 2 (Value component): "By Shannon's source coding theorem, encoding n independent draws from (p_y) requires at least n H(Y) = n mu bits."
  - This is correct IF the function values are independent draws from (p_y). The independence assumption is implicit and may not hold for arbitrary functions f.
  - For the case where f is a fixed but unknown function, and we consider the worst case over functions with the given output distribution, the bound still holds by an entropy argument. But the proof should state this clearly.
  - **VALID** modulo the implicit independence assumption.

- Step 3 (Combining): "Since both components are jointly necessary, the total requirement is n(-log_2 epsilon + mu) bits."
  - The additivity claim (membership and value encoding are jointly necessary) requires that the two components are information-theoretically independent. This is plausible (membership is about which elements are stored; value is about what they map to) but the proof does not formally establish independence.
  - **GAP**: need a formal argument that the membership and value components are independent information requirements.

**Cross-reference**: The formalism document (Section 1.4) states the space formula -log_2 epsilon + mu as "information-theoretic" but does not prove the lower bound. The paper's proof attempt is more detailed than the formalism.

**Verdict**: **LIKELY-CORRECT**. The result is well-known in the probabilistic data structure literature and is almost certainly true. The proof sketch has gaps (counting argument not given, independence of components not formally established, function value independence assumed) but the result follows from standard information-theoretic arguments.

---

### Theorem 6.2: Space Complexity (lines 605-631)

**Statement**: The Singular Hash Map achieves -(1-eta)log_2 epsilon + (1-eta)mu bits per element.

**Assumptions (explicit)**: False positive rate epsilon, false negative rate eta, mu = H(Y).

**Assumptions (implicit)**: Random oracle model for h; Algorithm 1's construction succeeds.

**Proof walkthrough**:

- Step 1 (False negative reduction): "When false negatives are permitted at rate eta, only (1-eta)n elements must decode correctly."
  - **VALID**. If we tolerate eta fraction of errors, we only need to satisfy (1-eta)n constraints.

- Step 2 (Per-element bit cost): "Under the random oracle model, the probability that a random bit string's prefix matches the code for value y is 2^{-|c_y|}, where |c_y| is the code length. By Shannon-optimal coding, |c_y| approx -log_2 p_y, so expected code length per element is sum_y p_y |c_y| = mu."
  - This is about the value encoding cost, not the total cost. The argument that the expected code length equals mu (Shannon entropy) under optimal coding is correct by Shannon's source coding theorem.
  - **VALID**.

- Step 3 (False positive control): "For non-members x not in {x_1, ..., x_n}, the hash h(l) XOR h(x) is (under the random oracle model) uniformly distributed."
  - This is the key step and it has an issue (identified as M8 in Review 2): h(l) XOR h(x) is uniformly distributed ONLY IF h(l) is independent of h(x). Under the random oracle model, h(l) and h(x) are indeed independent for l != x (since a random oracle produces independent outputs for distinct inputs). But l is NOT independent of the stored elements {x_1, ..., x_n} -- l was chosen to satisfy constraints on all stored elements. So h(l) is conditioned on the stored elements.
  - For a NON-member x (not in the stored set), h(x) is independent of h(l) and of all h(x_i) under the random oracle model (since x is a new query). So h(l) XOR h(x) is uniformly distributed for non-members. This is correct but the argument needs the explicit statement that x is distinct from l and from all stored elements.
  - "Achieving target rate epsilon thus requires -log_2 epsilon additional bits of hash beyond the value encoding" -- this is the crux. The false positive rate equals the probability that a random bit string's prefix is a valid codeword. If the total hash output is m bits and the codes use m - b bits for value encoding, then the probability of a random prefix matching any codeword is 2^{-b}. Setting epsilon = 2^{-b} gives b = -log_2 epsilon. Total bits per element: b + mu = -log_2 epsilon + mu.
  - **LIKELY-VALID** but needs the explicit independence argument for non-members.

- Step 4 (Combining): Multiplying per-element cost by effective element count gives the claimed formula.
  - **VALID** given Steps 1-3.

**Cross-reference**: The formalism document (Section 2.2, parameter table) states the space formula -log_2 epsilon + H(Y) bits/element for the entropy map. The paper's proof is more detailed.

**Verdict**: **LIKELY-CORRECT**. The result is correct. The proof has one gap (M8: explicit independence argument for non-members under RO model) that is straightforward to fill.

---

### Corollary 6.1: Asymptotic Optimality (lines 633-636)

**Statement**: When eta = 0, the Singular Hash Map achieves -log_2 epsilon + mu bits per element, matching the lower bound of Theorem 6.1.

**Assessment**: Immediate from Theorem 6.2 with eta = 0: -(1-0)log_2 epsilon + (1-0)mu = -log_2 epsilon + mu. This matches Theorem 6.1.

**Verdict**: **VERIFIED** (trivial given Theorems 6.1 and 6.2).

---

### Theorem 6.3: Collision-Bernoulli Connection (lines 642-656)

**Statement**: For a given seed l, the probability of successful construction is p = prod_{i=1}^m (1 - e_i) where e_i is the Bernoulli error rate for element i and m = (1-eta)n.

**Assumptions (explicit)**: Random oracle model; m = (1-eta)n stored elements.

**Assumptions (implicit)**: Hash outputs for distinct elements are independent (follows from random oracle model).

**Proof walkthrough**:

- Step 1: "Under the random oracle model, the hash values h(l) XOR h(x_i) for distinct elements x_i are independent uniformly distributed bit strings."
  - For a fixed l, h(l) is a fixed value. h(x_i) for distinct x_i are independent uniform bit strings under RO. So h(l) XOR h(x_i) are independent uniform bit strings (XOR with a fixed value is a bijection on uniform distributions).
  - **VALID**.

- Step 2: "For element x_i with target value f(x_i) = y_i, the probability of incorrect decoding is e_i = 1 - 2^{-|c_{y_i}|}."
  - Wait: the probability of CORRECT decoding is the probability that the hash prefix matches the code for y_i, which is 2^{-|c_{y_i}|} (under uniform hash). So the probability of incorrect decoding is 1 - 2^{-|c_{y_i}|}. But this seems very high (close to 1 for all reasonable code lengths).
  - Actually, this is correct: for a random seed l, the probability that h(l) XOR h(x_i) happens to have the right prefix for y_i is indeed 2^{-|c_{y_i}|}, which is small. The error rate per element per random trial is high. This is why the seed search requires many trials.
  - **VALID**.

- Step 3: "Since the random oracle makes the hash outputs independent across elements, the joint success probability factors."
  - By Step 1, the hash values are independent, so success/failure events are independent. The product formula follows.
  - **VALID**.

- Step 4: "The expected number of seed trials until success is 1/p."
  - This is the expected value of a geometric random variable. Correct.
  - **VALID**.

- Step 5: "By the inequality of arithmetic and geometric means, p >= (1 - e-bar)^m where e-bar = (1/m) sum_i e_i, confirming that the construction terminates in expected O((1-e-bar)^{-m}) trials."
  - AM-GM gives prod(1-e_i) >= ... actually, the correct inequality here is from the concavity of log: prod(1-e_i) = exp(sum log(1-e_i)) <= exp(m * log(1 - e-bar)) = (1 - e-bar)^m. Wait, that goes the wrong way. By Jensen's inequality on the concave function log(1-x): (1/m) sum log(1-e_i) <= log(1 - e-bar), so prod(1-e_i) <= (1-e-bar)^m. This means p <= (1-e-bar)^m, not p >= (1-e-bar)^m.
  - So the claimed inequality is in the **WRONG DIRECTION**. The proof claims p >= (1-e-bar)^m (a lower bound on success probability), but Jensen gives p <= (1-e-bar)^m (an upper bound).
  - This does not affect the main result (the product formula in the theorem statement is correct). The AM-GM remark is just providing a bound on the expected number of trials, and the bound goes the wrong way -- it gives a lower bound on expected trials, not an upper bound. The construction still terminates (p > 0 since each e_i < 1), but the stated bound is incorrect.

**Cross-reference**: The formalism document (Section 2.2) discusses construction time: "expected value epsilon^{-l}" trials per bucket in the two-level hash, which is a different (and more precise) analysis.

**Verdict**: **LIKELY-CORRECT**. The main product formula (the theorem statement) is correct. The proof is valid for Steps 1-4. Step 5 has an inequality in the wrong direction (should be <= not >=). This is a minor error in a supplementary remark, not in the core result.

**Notes**: Fix the inequality direction or remove the AM-GM remark. The construction terminates because p > 0 (each factor 1 - e_i > 0 since e_i < 1); the expected number of trials is 1/p = 1/prod(1-e_i), which is finite.

---

### Theorem 6.4: Collision Resistance (lines 660-668)

**Statement**: If h is a random oracle and |encode_{c_A S}(s)| = 2^m / |S| for all s, then: (1) finding collisions requires Omega(2^{m/2}) operations, (2) inverting the encoding requires Omega(2^m / |S|) operations, (3) the observable distribution is computationally indistinguishable from uniform.

**Proof walkthrough**: **No proof given in the main text**. The appendix (A.2, lines 899-909) provides a security reduction sketch.

**Assessment of appendix proof**:
- The reduction: given an adversary A that distinguishes cipher representations with advantage epsilon, construct algorithm B that finds hash collisions with probability epsilon/2.
- B's strategy: sample random bit b, compute c = encode(x_b, k), forward to A. When A outputs b', if b' = b, "B uses A's internal state to extract a hash collision."
- This is a standard IND-CPA-style game but the reduction is hand-waving: "uses A's internal state to extract a hash collision" is not a valid proof step. How does B extract a collision from the fact that A correctly guessed b? This step is not justified.
- Claim 1 (collision resistance: Omega(2^{m/2})): This is the birthday bound for hash functions, which is a well-known result. It does not need the reduction -- it follows directly from h being a random oracle with m-bit output. **VALID as a known fact, but the proof does not establish it.**
- Claim 2 (inverting encoding: Omega(2^m / |S|)): Under the RO model, inverting h requires 2^m / |S| queries because each preimage maps to one of |S| elements, so the search space is 2^m / |S|. This is a standard argument. **VALID as a known fact.**
- Claim 3 (indistinguishable from uniform): Under the RO model, h maps to uniformly random outputs, so the observable distribution IS uniform (in the ROM). This is not "computationally indistinguishable from uniform" -- it IS uniform. **VALID but overstated (stronger than claimed).**

**Cross-reference**: The formalism document does not have a collision resistance theorem. The formalism's security argument is information-theoretic (Properties 1-2 + trapdoor), not based on collision resistance.

**Verdict**: **NO-PROOF-GIVEN**. The three claims are individually correct (they follow from standard random oracle model arguments) but the proof in Appendix A.2 does not validly establish them. The reduction is incomplete. This was identified as M5 in Review 2. The fix is to cite the standard results rather than attempt a novel reduction.

---

## Section 7: Connections Between Frameworks

### Proposition 7.1: Induced Bernoulli Structure (lines 678-681)

**Statement**: Every cipher type cipher<T,N,M> induces a Bernoulli model bernoulli<T,K> where the order K depends on the representation distribution.

**Assessment**: No proof given. The claim is vague: "the order K depends on the representation distribution" does not specify the relationship. What is K as a function of N, M, and the representation distribution?

**Cross-reference**: The formalism document does not have this proposition. The connection between cipher types and Bernoulli models is through specific constructions (Section 2), not through a general abstract correspondence.

**Verdict**: **NO-PROOF-GIVEN**. The claim is too vague to verify.

---

### Theorem 7.1: Bernoulli Obliviousness (lines 689-691)

**Statement**: A Bernoulli approximation with symmetric confusion matrix and random oracle behavior for undefined inputs satisfies obliviousness conditions.

**Assessment**:
- "Obliviousness conditions" are not formally defined (the cipher map definition's conditions are informal English bullets).
- "Random oracle behavior for undefined inputs" is a property of the implementation, not of the Bernoulli model.
- No proof given.
- The claim is essentially tautological: if you define obliviousness as "symmetric errors + random oracle on undefined inputs" and then assert that a system with "symmetric confusion matrix + random oracle behavior" satisfies obliviousness, you have said nothing.

**Cross-reference**: The formalism document replaces "obliviousness" with four concrete properties and proves each for specific constructions. This theorem has no analogue in the formalism.

**Verdict**: **NO-PROOF-GIVEN**. The claim is also essentially vacuous given that "obliviousness conditions" are undefined.

---

### Theorem 7.2: Functoriality (lines 709-734)

**Statement**: The cipher construction c_A is a functor from the category of monoids to itself: (1) object mapping, (2) morphism mapping, (3) identity preservation, (4) composition preservation.

**Assumptions (explicit)**: c_A maps monoids to cipher monoids (Theorem 2.1); monoid homomorphisms lift to cipher homomorphisms.

**Assumptions (implicit)**: The morphism mapping is well-defined (independent of representation choice).

**Proof walkthrough**:

- Step 1 (Object mapping): "Theorem 2.1 shows c_A maps monoids to monoids."
  - But Theorem 2.1 is **incorrect as stated** (ERROR verdict above) -- it only works for the quotient monoid. So this step inherits that error.
  - **GAP** (depends on fixing Theorem 2.1).

- Step 2 (Morphism mapping): Define c_A(phi)(c) = encode_2(phi(decode_1(c)), k) for "some canonical choice of representation index k."
  - The phrase "some canonical choice" is problematic (identified as M3 in Review 2). Different choices of k give different functions. For c_A(phi) to be well-defined, it must produce the same result regardless of which representative c of the equivalence class is used as input. Specifically, if decode_1(c) = decode_1(c'), then c_A(phi)(c) and c_A(phi)(c') must be in the same equivalence class. Since decode_2(c_A(phi)(c)) = phi(decode_1(c)) = phi(decode_1(c')) = decode_2(c_A(phi)(c')), they ARE in the same equivalence class. So the morphism mapping is well-defined on the quotient.
  - On c_A S itself (not the quotient), c_A(phi) depends on the choice of k, so it is not canonically defined. This is the M3 issue.
  - **VALID on the quotient, INVALID on c_A S without fixing k**.

- Step 3 (Identity): "c_A(id_S) maps c -> encode(id_S(decode(c)), k) = encode(decode(c), k), which acts as the identity on c_A S up to representation choice."
  - "Up to representation choice" means it is NOT the identity on c_A S. It IS the identity on the quotient. The proof acknowledges this with "up to representation choice" but the theorem statement claims identity preservation on c_A S.
  - **VALID on the quotient, INVALID on c_A S**.

- Step 4 (Composition): The calculation is:
  c_A(psi o phi)(c) = encode_3((psi o phi)(decode_1(c)), k)
                    = encode_3(psi(phi(decode_1(c))), k)
                    = (c_A(psi) o c_A(phi))(c)
  - The last equality assumes that c_A(psi)(c_A(phi)(c)) = encode_3(psi(decode_2(encode_2(phi(decode_1(c)), k))), k) = encode_3(psi(phi(decode_1(c))), k). This uses decode_2(encode_2(s, k)) = s. **VALID**.
  - But again, this is equality of decoded values (both sides decode to psi(phi(decode_1(c)))). On c_A S, the result depends on k choices.
  - **VALID on the quotient**.

**Cross-reference**: The formalism document does not claim functoriality. The formalism works directly with cipher maps as functions on bit strings without categorical structure.

**Verdict**: **UNCERTAIN**. The proof works cleanly for the category of quotient monoids (c_A S / ~). It does not work for c_A S itself due to the non-canonical representation choice. The theorem should be restated: "c_A is a functor from Mon to Mon, where the target objects are quotient monoids c_A S / ~ with the induced operation." Alternatively, work in a category where morphisms are equivalence classes of functions modulo ~. This was identified as M3 in Review 2.

---

### Theorem 7.3: Cipher Composition (lines 742-768)

**Statement**: For nested cipher types c_B(c_A S): (1) double encoding provides enhanced security, (2) error rates compose as epsilon_total = epsilon_A + epsilon_B - epsilon_A * epsilon_B, (3) homomorphic properties preserved through both layers.

**Proof walkthrough**:

- Claim 2 (error composition): The proof uses inclusion-exclusion:
  epsilon_total = Pr[E_A union E_B] = Pr[E_A] + Pr[E_B] - Pr[E_A intersect E_B] = epsilon_A + epsilon_B - epsilon_A * epsilon_B.
  - The last step uses independence: Pr[E_A intersect E_B] = epsilon_A * epsilon_B. The proof justifies this by "independence follows from the layers using independent encoding secrets."
  - This is the same as the composition theorem in the formalism (Theorem 3.1). The formalism correctly notes that independence requires the "re-randomization" assumption (formalism Section 3.2, Remark on independence).
  - **VALID under the independence assumption**, which should be stated explicitly.

- Claim 3 (homomorphic preservation): "decode_A(decode_B(x c_B(c_A*) y)) = decode_A(decode_B(x)) * decode_A(decode_B(y))".
  - This follows from applying Theorem 2.2 (homomorphism) twice: decode_B is a homomorphism c_B(c_A S) -> c_A S, and decode_A is a homomorphism c_A S -> S.
  - **VALID** (given Theorem 2.2, which is verified).

- Claim 1 (enhanced security): "An adversary must break both layers."
  - This is an informal security claim with no formal backing. "Break" is not defined. The paper has no adversary model.
  - **UNJUSTIFIED**.

**Cross-reference**: The formalism's Theorem 3.1 (composition correctness) proves the same error formula with an honest discussion of the independence assumption (Section 3.2). The formalism's treatment is superior because it explicitly states the assumption and discusses when it holds.

**Verdict**: **LIKELY-CORRECT** for claim 2 (error composition), **VERIFIED** for claim 3 (homomorphism), **NO-PROOF-GIVEN** for claim 1 (security).

---

## Appendix A.1: Detailed Proof of Homomorphism (lines 885-897)

**Statement**: Detailed proof of Theorem 2.2.

**Assessment**: This is a more verbose version of the proof already given for Theorem 2.2. It adds no new content. The proof is correct (as verified above for Theorem 2.2) but duplicative.

**Verdict**: **VERIFIED** (same as Theorem 2.2, redundant).

---

## Appendix A.2: Security Reduction for Hash-Based Construction (lines 899-909)

**Assessment**: Already analyzed under Theorem 6.4 above. The reduction is incomplete.

**Verdict**: **NO-PROOF-GIVEN** (already assessed above).

---

## Summary Table

| Claim | Location | Verdict | Key Issue |
|-------|----------|---------|-----------|
| Theorem 2.1 (Cipher Monoid) | lines 212-236 | **ERROR** | Only true for quotient monoid, not c_A S (M6) |
| Theorem 2.2 (Homomorphism) | lines 246-266 | **VERIFIED** | Trivial by construction |
| Proposition 2.1 (Security-Efficiency) | lines 283-293 | **UNCERTAIN** | "Security" undefined; items 1,3 valid informally |
| Example 2.2 (Cyclic Cipher) | lines 331-341 | **ERROR** | No representation multiplicity (Fermat's little theorem) (M7) |
| Theorem 3.1 (Bernoulli Entropy) | lines 425-429 | **ERROR** | Formula wrong; not an entropy of the model (M2) |
| Theorem 4.1 (Cipher-Bernoulli Correspondence) | lines 462-475 | **NO-PROOF-GIVEN** | "Proof" is a sketch with no derivation |
| Proposition 4.1 (Rep. Indistinguishability) | lines 481-483 | **NO-PROOF-GIVEN** | No security model, no secret defined |
| Theorem 6.1 (Lower Bound) | lines 580-601 | **LIKELY-CORRECT** | Known result; proof sketch has gaps |
| Theorem 6.2 (Space Complexity) | lines 605-631 | **LIKELY-CORRECT** | Correct modulo M8 (independence for non-members) |
| Corollary 6.1 (Asymptotic Optimality) | lines 633-636 | **VERIFIED** | Trivial from Thm 6.1 + 6.2 |
| Theorem 6.3 (Collision-Bernoulli) | lines 642-656 | **LIKELY-CORRECT** | Main formula correct; AM-GM inequality direction wrong |
| Theorem 6.4 (Collision Resistance) | lines 660-668 | **NO-PROOF-GIVEN** | Claims correct (standard results) but proof invalid (M5) |
| Proposition 7.1 (Induced Bernoulli) | lines 678-681 | **NO-PROOF-GIVEN** | Vague claim |
| Theorem 7.1 (Bernoulli Obliviousness) | lines 689-691 | **NO-PROOF-GIVEN** | "Obliviousness" undefined; claim vacuous |
| Theorem 7.2 (Functoriality) | lines 709-734 | **UNCERTAIN** | Valid for quotient monoid; invalid on c_A S (M3) |
| Theorem 7.3 (Cipher Composition) | lines 742-768 | **LIKELY-CORRECT** | Error formula correct under independence; security claim unjustified |
| Appendix A.1 (Homomorphism detail) | lines 885-897 | **VERIFIED** | Redundant with Theorem 2.2 |
| Appendix A.2 (Security reduction) | lines 899-909 | **NO-PROOF-GIVEN** | Reduction incomplete |

### Tally

| Verdict | Count |
|---------|-------|
| VERIFIED | 3 (Thm 2.2, Cor 6.1, Appendix A.1) |
| LIKELY-CORRECT | 4 (Thm 6.1, 6.2, 6.3, 7.3) |
| UNCERTAIN | 3 (Prop 2.1, Ex 2.1, Thm 7.2) |
| ERROR | 3 (Thm 2.1, Ex 2.2, Thm 3.1) |
| NO-PROOF-GIVEN | 5 (Thm 4.1, Prop 4.1, Thm 6.4, Prop 7.1, Thm 7.1) |

### Critical Findings

1. **Three formal errors**: Theorem 2.1 (monoid claim fails for non-quotient), Example 2.2 (Fermat kills multiplicity), Theorem 3.1 (entropy formula wrong).

2. **Five claims with no proof**: Theorems 4.1, 6.4, 7.1; Propositions 4.1, 7.1. These are stated as theorems/propositions but have no proof or only a hand-waving sketch.

3. **Pervasive quotient issue**: Theorems 2.1, 2.2, and 7.2 all work on the quotient monoid c_A S / ~ but are stated for c_A S. The fix is systematic: either restate everything for the quotient (preferred) or restrict to representation selectors that ensure equality in c_A S.

4. **Missing formalism**: The paper's central definition (Definition 4.1, cipher map) is imprecise. The formalism document's Definition 1.1 + four properties provide the correct replacement.

5. **Strongest results are the practical ones**: Theorems 6.1, 6.2, and 7.3 (space bounds and composition) are the paper's genuine contributions and are LIKELY-CORRECT with minor fixable gaps. The algebraic/categorical material (Theorems 2.1, 7.2) has more serious issues.

### Recommendations

1. **Drop or demote the cipher functor / category theory**: Theorems 2.1, 2.2, and 7.2 are either trivial (on the quotient) or wrong (on c_A S). They add bulk without insight. Demote to an appendix remark.

2. **Replace Definition 4.1 with the formalism's Definition 1.1 + four properties**: This is the paper's real contribution and it is currently missing.

3. **Fix the three errors**: Restate Theorem 2.1 for quotient monoid; fix Example 2.2 (use ElGamal or remove); relabel Theorem 3.1 as a definition with the correct formula.

4. **Prove or remove the five unproven claims**: Either provide real proofs for Theorems 4.1, 6.4, 7.1 and Propositions 4.1, 7.1, or remove them. Citing standard results (birthday bound, RO uniformity) is preferable to attempting novel reductions.

5. **Strengthen the composition theorem**: The error composition formula (Theorem 7.3 / formalism Theorem 3.1) is the paper's strongest result. Give it a prominent position, state the independence assumption explicitly, and derive it from the noisy gates analysis (formalism Section 3.1).
