# Proof Verification: Cipher Maps Unified

**Date**: 2026-03-19
**Paper**: `papers/cipher-maps-unified/paper/cipher_maps.tex`
**Reviewer**: papermill (Claude Opus 4.6)

---

## Verification Protocol

For each theorem/lemma/proposition/corollary, I state the claim, check each proof step, flag gaps or errors, and rate confidence on the scale: **verified** / **likely-correct** / **uncertain** / **error-found**.

---

## Theorem 2.1: Cipher Monoid Properties (lines 212--236)

**Claim.** For any representation selector rho, the triple (c_A S, c_A *, encode(e,0)) is a monoid.

**Proof check.**

1. **Closure** (lines 220--221): Correct. If decode(x) and decode(y) are in S, and S is closed under *, then decode(x)*decode(y) is in S, so encode(decode(x)*decode(y), rho(...)) is in c_A S by the encoding axiom.

2. **Associativity** (lines 222--230): The proof shows decode((x c_A* y) c_A* z) = decode(x c_A* (y c_A* z)). This establishes that both sides represent the same element of S under decode. However, the proof then admits (line 230) that actual equality in c_A S requires a "consistent selector" condition. The proof **does not show** that this condition is satisfiable for general selectors rho. The statement "For any representation selector rho" is therefore false as stated.

   **Gap**: The theorem claims the monoid property for ALL rho, but the proof only establishes it for rho satisfying the consistency condition. For arbitrary rho, c_A S is a monoid only on the quotient c_A S / ~.

3. **Identity** (lines 232--234): The proof shows decode(encode(e,0) c_A* x) = decode(x). Same issue as associativity --- this establishes decode-equivalence, not equality in c_A S. For the constant selector rho = 0: encode(e,0) c_A* x = encode(decode(x), rho(decode(x), encode(e,0), x)). This equals x only if rho(decode(x), encode(e,0), x) = k_x where x = encode(decode(x), k_x). The constant selector rho = 0 gives encode(decode(x), 0), which equals x only if x was encoded with index 0. So even the constant selector fails the identity law for elements with non-zero encoding index.

**Verdict: error-found**

The cipher monoid is a monoid on the quotient c_A S / ~ where x ~ y iff decode(x) = decode(y). It is NOT a monoid on c_A S itself for general (or even constant) selectors. The remark after the proof (lines 238--240) acknowledges this, but the theorem statement does not.

**Fix**: State the theorem for c_A S / ~ explicitly, or restrict to selectors satisfying a specific condition and prove that condition is satisfiable.

---

## Theorem 2.2: Homomorphism (lines 246--266)

**Claim.** decode: c_A S -> S is a monoid homomorphism, i.e., decode(encode(e,0)) = e and decode(x c_A* y) = decode(x) * decode(y).

**Proof check.**

1. **Identity**: decode(encode(e,0)) = e by the decoding axiom (Def 2.2, line 192). Correct.

2. **Operation**: By Def 2.3, x c_A* y = encode(decode(x)*decode(y), rho(...)). Then decode(x c_A* y) = decode(encode(decode(x)*decode(y), rho(...))) = decode(x)*decode(y) by the decoding axiom. Correct.

**Verdict: verified**

Note: This theorem is well-posed because decode maps to S (not to c_A S), so the quotient issues from Theorem 2.1 do not arise. decode is a surjective homomorphism from (c_A S, c_A*) to (S, *), and it factors through the quotient.

---

## Proposition 2.3: Security--Efficiency Tradeoff (lines 283--293)

**Claim.** For a finite monoid S, if A is generating but not complete, then (1) some elements require composite representations, (2) security increases with |S|/|A|, (3) computational overhead increases with average composition length.

**Proof check.** No proof given. These are informal observations.

1. Statement (1) is true by definition: if A is generating but not complete, elements in S\A must be written as products of elements of A.
2. Statement (2) is undefined: "security" has no formal definition in the paper.
3. Statement (3) is reasonable but also informal.

**Verdict: uncertain**

This is not really a proposition --- it is a collection of informal observations. It should be labeled as a remark.

---

## Theorem 3.4: Bernoulli Entropy (lines 425--429)

**Claim.** The entropy of a Bernoulli model with confusion matrix Q is H = -sum_{i,j} q_{ij} log q_{ij}.

**Proof check.** No proof given. This is the definition of the joint entropy of the bivariate random variable (latent, observed), which is a standard information-theoretic quantity. It is not a theorem; it is a definition.

**Verdict: likely-correct (but misclassified as theorem)**

The statement is correct as a definition but should not be labeled a theorem. The formula H = -sum q_{ij} log q_{ij} is the joint entropy of the (latent, observed) pair, which is well-defined whenever Q is a valid joint distribution. But Q as defined is a conditional distribution (row-stochastic), not a joint distribution. To get the joint entropy, one needs the prior on latent values: P(latent=i, observed=j) = pi_i * q_{ij} where pi is the prior. The formula as stated is incorrect unless Q is already a joint distribution.

**Revised verdict: error-found**

The formula applies to the joint distribution, but Q is defined as a conditional distribution (each row sums to 1). The correct formula for the joint entropy would be H = -sum_{i,j} pi_i * q_{ij} * log(pi_i * q_{ij}).

---

## Theorem 4.2: Cipher--Bernoulli Correspondence (lines 462--475)

**Claim.** Every cipher functor c_A induces a Bernoulli model where the confusion matrix entries are determined by the probability of selecting different cipher representations.

**Proof check.** The "proof" (lines 467--475) does not compute anything. It lists three factors (encoding distribution, algebraic operations, decoding function) and asserts they "combine to create a confusion matrix structure Q where q_{ab} = Pr[observe b | latent a]." No formula for q_{ab} is given.

To verify this claim, one would need to:
1. Fix a distribution on encoding indices k
2. Fix an algebraic operation or evaluation procedure
3. Compute Pr[decode(evaluate(encode(a, k))) = b | latent = a]
4. Show this defines a valid stochastic matrix

None of these steps are carried out.

**Verdict: uncertain (proof absent)**

The claim is plausible for specific cipher functor instances but is not proved in generality. The formalism document (Section 2) instantiates this correctly for specific constructions, which is the right approach. The paper should follow suit.

---

## Proposition 4.3: Representation Indistinguishability (lines 481--486)

**Claim.** For any a in S, the representations {encode(a,k) : k in N} are computationally indistinguishable without knowledge of the encoding secret.

**Proof check.** No proof given. No formal definition of computational indistinguishability is provided. The claim depends entirely on the construction: for hash-based constructions under the random oracle model, representations may be indistinguishable. For the abstract cipher functor, there is no basis for the claim.

**Verdict: uncertain (proof absent, claim depends on construction)**

---

## Theorem 5.1: Information-Theoretic Lower Bound (lines 580--601)

**Claim.** Any data structure representing an approximate map f-hat: X -> Y u {bot} with false positive rate epsilon and false negative rate eta = 0 over n stored elements requires at least n(-log_2(epsilon) + mu) bits, where mu = H(Y).

**Proof check.**

1. **Membership component** (lines 591--594): The counting argument is: the structure must reject at least (1-epsilon)(|U|-n) non-members. The number of distinguishable configurations is at least C(|U|, n) / epsilon^{|U|-n}. Taking log and applying Stirling gives n * log_2(1/epsilon). This is the standard Bloom filter lower bound argument (Carter, Floyd, Gill, Markowsky, Wegman, 1978; Bloom 1970 cited). The argument is correct under the assumption that the universe U is much larger than n.

   **Minor issue**: The citation to Bloom 1970 is not quite right --- Bloom's paper gives the construction, not the lower bound. The information-theoretic lower bound is from later work (e.g., Carter et al. 1978, or more precisely Broder and Mitzenmacher 2004).

2. **Value component** (lines 597--599): By Shannon's source coding theorem, encoding n independent draws from distribution (p_y) requires at least n*H(Y) bits. Correct, under the assumption that the values are drawn independently. In a map, the values f(x_1),...,f(x_n) are deterministic given f, so the "n independent draws" assumption is about the distribution of f, not about randomness. This is a subtlety that the proof glosses over.

3. **Combining** (lines 600--601): "Since both components are jointly necessary, the total requirement is n(-log_2(epsilon) + mu) bits." The additivity requires that the membership information and value information are independent, which is true when the membership predicate is independent of the function values. This is the case for the approximate map model where membership and value encoding are separate. Correct.

**Verdict: likely-correct**

The argument is standard and the conclusion is correct, though the proof could be more precise about the independence assumption and the correct citation.

---

## Theorem 5.2: Space Complexity (lines 605--631)

**Claim.** The Singular Hash Map achieves space complexity -(1-eta)*log_2(epsilon) + (1-eta)*mu bits per element.

**Proof check.**

1. **Step 1: False negative reduction** (lines 615--617): When eta > 0, only (1-eta)*n elements need correct decoding. This is correct as a reduction in constraints, but the paper does not describe how Algorithm 1 is modified to permit false negatives. Algorithm 1 as written requires ALL elements to decode correctly. The eta > 0 case presumably modifies the algorithm to accept solutions where up to eta*n elements fail, but this is not stated.

2. **Step 2: Per-element bit cost** (lines 619--622): Under the random oracle model, h(ell) XOR h(x_i) is uniformly distributed. The probability that a random bit string's prefix matches the code for value y is 2^{-|c_y|}. With Shannon-optimal coding, |c_y| = -log_2(p_y), so the expected code length is sum_y p_y |c_y| = mu. This is correct.

3. **Step 3: False positive control** (lines 624--627): For non-members, the hash output is uniform, so the probability of decoding to any valid output is epsilon (the total measure of all codewords in the prefix-free code). This determines the false positive rate. The claim that this requires "-log_2(epsilon) additional bits of hash beyond the value encoding" conflates two things: the total hash length determines epsilon, and the value encoding length is mu. The per-element cost is the hash length, which must satisfy: probability of random match = epsilon * 2^{-mu}, so hash length = -log_2(epsilon) + mu. Wait --- actually the hash output length determines both: if the total prefix-free code covers fraction epsilon of the hash space, and within that, individual codewords have measure proportional to p_y, then the total hash length is -log_2(epsilon) + mu. This is correct but the reasoning in the proof is somewhat circular.

4. **Step 4: Combining** (lines 629--630): Multiplying per-element cost by effective element count. Correct.

**Verdict: likely-correct**

The result is correct. The proof has a gap in Step 1 (not describing the modified algorithm for eta > 0) and Step 3 could be clearer, but the conclusion follows from standard arguments.

---

## Corollary 5.3: Asymptotic Optimality (lines 633--636)

**Claim.** When eta = 0, the Singular Hash Map achieves -log_2(epsilon) + mu bits per element, matching the lower bound.

**Proof check.** Direct substitution of eta = 0 into Theorem 5.2. Correct.

**Verdict: verified**

---

## Theorem 5.5: Collision--Bernoulli Connection (lines 642--656)

**Claim.** For a given seed ell, the success probability is p = prod_{i=1}^{m} (1 - e_i) where e_i is the Bernoulli error rate for element i.

**Proof check.**

1. Under the random oracle model, hash values h(ell) XOR h(x_i) for distinct x_i are independent uniform bit strings. Correct: if h is a random oracle, h(x_i) are independent uniform, and XOR with the common h(ell) preserves uniformity and independence (since XOR with a fixed string is a bijection).

   **Wait**: h(ell) is NOT independent of h(x_i) --- they are all outputs of the same random oracle h, but on distinct inputs (ell vs x_i). So h(ell) XOR h(x_i) is XOR of two independent uniform values, which is uniform. And h(ell) XOR h(x_i) is independent of h(ell) XOR h(x_j) for i != j? No --- they share the common h(ell). Let Z = h(ell). Then Z XOR h(x_1) and Z XOR h(x_2) are NOT independent --- they are both functions of the same Z. However, given Z, they are independent (since h(x_1) and h(x_2) are independent). So the joint distribution of {Z XOR h(x_i)} is NOT the product distribution, but is the distribution of {Z XOR U_i} where U_i are iid uniform and Z is uniform. This is exchangeable but not independent.

   **However**, the success condition is: Z XOR h(x_i) has the correct prefix for each i. Given Z (which is fixed once ell is chosen), the events are independent (since h(x_i) are independent). So p = E_Z[prod_i Pr[Z XOR h(x_i) decodes to f(x_i) | Z]]. Since each h(x_i) is uniform and independent of Z, Pr[Z XOR h(x_i) decodes to f(x_i) | Z] = 2^{-|c_{f(x_i)}|} = 1 - e_i regardless of Z. So the product is correct.

2. The expected number of trials is 1/p. Correct: geometric distribution.

3. The AM-GM bound p >= (1 - e_bar)^m. Correct: by AM-GM, the geometric mean is <= the arithmetic mean, so prod(1-e_i) >= (1 - (1/m)*sum(e_i))^m.

   **Wait**: AM-GM says the geometric mean is at most the arithmetic mean, which gives prod(1-e_i)^{1/m} <= (1/m)*sum(1-e_i) = 1 - e_bar, hence prod(1-e_i) <= (1-e_bar)^m. This is an UPPER bound, not a lower bound. The paper claims p >= (1-e_bar)^m, which would be wrong.

   **Actually**: For concave functions, Jensen's inequality gives E[f(X)] <= f(E[X]). Since log is concave, (1/m)*sum(log(1-e_i)) <= log(1-e_bar), so prod(1-e_i) <= (1-e_bar)^m. This is an UPPER bound on p, meaning the expected number of trials 1/p >= 1/(1-e_bar)^m. The paper says "p >= (1-e_bar)^m" which is backwards.

**Verdict: error-found**

The main formula p = prod(1-e_i) is correct. However, the AM-GM bound claim is reversed: the correct inequality is p <= (1-e_bar)^m, not p >= (1-e_bar)^m. This means the expected number of trials 1/p >= (1-e_bar)^{-m}, which is a LOWER bound on construction time, not an upper bound. The paper uses it as if it were confirming termination, but the termination guarantee comes from p > 0 (which holds whenever each e_i < 1), not from the AM-GM bound.

---

## Theorem 5.4: Collision Resistance (lines 660--668)

**Claim.** Under random oracle model with |encode_{c_A S}(s)| = 2^m/|S| for all s: (1) finding collisions requires Omega(2^{m/2}) operations, (2) inverting requires Omega(2^m/|S|) operations, (3) observable distribution is computationally indistinguishable from uniform.

**Proof check.** No proof in the main text. The appendix (lines 900--909) sketches a reduction but does not complete it (see MAJOR issue 7 in the review).

For the claims themselves:
1. Collision resistance of 2^{m/2} is the birthday bound for random oracles. Correct as a standard result, but not proved in the paper.
2. Inverting requires 2^m/|S| operations: under the random oracle model, each hash output is uniform in {0,1}^m, and each element has 2^m/|S| valid hashes. To find a preimage mapping to a specific s, you need to find a hash in a set of size 2^m/|S| among 2^m possibilities, requiring 2^m/(2^m/|S|) = |S| queries in expectation. This is O(|S|), not Omega(2^m/|S|). The claim appears to be wrong.

   **Wait**: Re-reading: "Inverting the encoding requires Omega(2^m/|S|) operations." If |encode(s)| = 2^m/|S| for each s, then the fraction of the hash space that maps to any particular s is (2^m/|S|)/2^m = 1/|S|. So a random hash output maps to a specific s with probability 1/|S|, meaning you need |S| random queries to find one that maps to s. But the claim says Omega(2^m/|S|), which is the SIZE of the encoding set per element, not |S|. These are different unless 2^m/|S| = |S|, i.e., |S| = 2^{m/2}.

   The claim is confusingly stated. The standard result is: inverting a random oracle with range size R requires Omega(R) queries. Here R = 2^m, and we want to find any preimage that decodes to a specific s. The probability of success per query is 2^m/(|S| * 2^m) = 1/|S|, so expected queries = |S|. The Omega(2^m/|S|) claim does not match.

**Verdict: error-found (claim 2 is likely wrong; claims 1 and 3 are standard but unproved)**

---

## Theorem 7.1: Functoriality (lines 709--734)

**Claim.** The cipher construction c_A is a functor from the category of monoids to itself.

**Proof check.**

1. **Object mapping** (line 720): Theorem 2.1 shows c_A maps monoids to monoids. But per the error found in Theorem 2.1, c_A S is only a monoid on the quotient. So the object mapping goes from Mon to a quotient structure, not to Mon itself.

2. **Morphism mapping** (lines 722--724): Given phi: S_1 -> S_2, define c_A phi(c) = encode_2(phi(decode_1(c)), k). This depends on a choice of k (representation index). The choice "for some canonical choice of k" is not specified. Different choices of k give different maps. For the functor to be well-defined, the morphism mapping must be deterministic.

   **Moreover**: The map c_A phi depends on both encode_2 and decode_1, which are part of different cipher systems. The encoding set A is fixed in the notation c_A, but encode_2 depends on the encoding set for S_2, which is a priori different from A for S_1. The paper does not address how A relates to S_2.

3. **Identity preservation** (lines 726--727): "c_A(id_S) maps c -> encode(id_S(decode(c)), k) = encode(decode(c), k), which acts as the identity on c_A S up to representation choice." The phrase "up to representation choice" means it is NOT the identity. A functor must preserve identity exactly: F(id_A) = id_{F(A)}. "Up to representation choice" means F(id_A)(c) = encode(decode(c), k), which equals c only if k is the original encoding index of c. This is not guaranteed.

4. **Composition preservation** (lines 728--733): The algebra is correct: c_A(psi o phi)(c) = encode_3((psi o phi)(decode_1(c)), k) = encode_3(psi(phi(decode_1(c))), k). And (c_A psi o c_A phi)(c) = c_A psi(encode_2(phi(decode_1(c)), k)) = encode_3(psi(decode_2(encode_2(phi(decode_1(c)), k))), k') = encode_3(psi(phi(decode_1(c))), k'). These are equal only if k = k', which requires the representation index to be preserved through composition. This is not guaranteed.

**Verdict: error-found**

The cipher construction is NOT a strict functor on Mon. It is a functor from Mon to Mon only when working with the quotient c_A S / ~, in which case it is trivially the identity functor (since c_A S / ~ is isomorphic to S via decode). The functoriality claim, as stated, is incorrect.

---

## Theorem 7.3: Bernoulli Obliviousness (lines 689--691)

**Claim.** A Bernoulli approximation with symmetric confusion matrix and random oracle behavior for undefined inputs satisfies obliviousness conditions.

**Proof check.** No proof given. The "obliviousness conditions" refer to Definition 4.1, which is itself informal. So this is an informal claim about informal conditions, making it unfalsifiable.

**Verdict: uncertain (claim and conditions both informal)**

---

## Theorem 7.5: Cipher Composition (lines 742--768)

**Claim.** For nested cipher types c_B(c_A S): (1) double encoding provides enhanced security, (2) error rates compose as epsilon_total = epsilon_A + epsilon_B - epsilon_A * epsilon_B, (3) homomorphic properties are preserved.

**Proof check.**

1. **Claim (1)**: "An adversary must break both layers." No formalization. What does "break" mean? Not proved.

2. **Claim (2)** (lines 754--759): The derivation uses inclusion-exclusion: Pr[E_A or E_B] = Pr[E_A] + Pr[E_B] - Pr[E_A and E_B] = epsilon_A + epsilon_B - epsilon_A * epsilon_B. This requires independence of E_A and E_B, which is stated as following from "the layers using independent encoding secrets" (line 758). Under independent seeds, the events "layer A errs on element x" and "layer B errs on element x" are indeed independent (since they depend on different random oracles). Correct under this assumption.

   **Subtlety**: The claim "total error occurs when at least one layer errs" (line 757) is correct for composition g o f: the composition is wrong when f produces wrong output OR g produces wrong output. But when f produces wrong output, g receives a random input (not the intended cipher value), so g's behavior on that input is not characterized by its correctness parameter epsilon_B. The correct analysis: Pr[composition correct] = Pr[f correct] * Pr[g correct | f correct]. The second factor equals 1 - epsilon_B only if g's correctness on f's output is independent of whether f was correct. This is the re-randomization assumption from the formalism document (Section 3.2, Remark), which is acknowledged there but not here.

3. **Claim (3)** (lines 762--764): "Homomorphic preservation follows by applying Theorem 2.2 twice." The equation decode_A(decode_B(x c_B(c_A*) y)) = decode_A(decode_B(x)) * decode_A(decode_B(y)). This is correct if the nested operation c_B(c_A*) is defined as: decode at both levels, operate in S, re-encode at both levels. But the paper does not define the nested operation precisely.

**Verdict: likely-correct (claim 2, under independence assumption), uncertain (claims 1 and 3)**

The error composition formula is the paper's most useful result and is correctly derived under the stated assumptions. However, the re-randomization subtlety should be acknowledged.

---

## Appendix A.1: Detailed Proof of Homomorphism (lines 883--897)

This is a re-proof of Theorem 2.2. The proof repeats the same argument with slightly different notation. No new content.

**Verdict: verified (redundant)**

---

## Appendix A.2: Security Reduction (lines 900--909)

**Claim.** Breaking the cipher type is at least as hard as finding hash collisions.

**Proof check.** The reduction: given (x_0, x_1), sample b, compute c = encode(x_b, k), send to adversary A, receive guess b'. "If b' = b, B uses A's internal state to extract a hash collision."

This is a standard-looking IND-CPA reduction skeleton, but the critical step --- extracting a hash collision from A's internal state --- is completely unjustified. In the random oracle model, one extracts collisions by monitoring A's oracle queries and finding two distinct queries with the same output. But this requires A to make queries that actually collide, which is not guaranteed by A's ability to distinguish representations.

**Verdict: error-found (reduction incomplete)**

---

## Summary Table

| Claim | Lines | Verdict | Severity |
|-------|-------|---------|----------|
| Thm 2.1: Cipher Monoid | 212--236 | **error-found** | Major: monoid only on quotient, not on c_A S |
| Thm 2.2: Homomorphism | 246--266 | **verified** | --- |
| Prop 2.3: Security-Efficiency | 283--293 | **uncertain** | Minor: informal, should be remark |
| Thm 3.4: Bernoulli Entropy | 425--429 | **error-found** | Minor: formula applies to joint, Q is conditional |
| Thm 4.2: Cipher-Bernoulli | 462--475 | **uncertain** | Major: proof absent |
| Prop 4.3: Indistinguishability | 481--486 | **uncertain** | Major: no proof, depends on construction |
| Thm 5.1: Lower Bound | 580--601 | **likely-correct** | Minor citation issue |
| Thm 5.2: Space Complexity | 605--631 | **likely-correct** | Minor: gap in eta>0 case |
| Cor 5.3: Optimality | 633--636 | **verified** | --- |
| Thm 5.5: Collision-Bernoulli | 642--656 | **error-found** | Minor: AM-GM bound direction reversed |
| Thm 5.4: Collision Resistance | 660--668 | **error-found** | Major: claim 2 likely wrong, no proof |
| Thm 7.1: Functoriality | 709--734 | **error-found** | Major: not a strict functor |
| Thm 7.3: Bernoulli Obliviousness | 689--691 | **uncertain** | Major: informal conditions |
| Thm 7.5: Composition | 742--768 | **likely-correct** | Minor: re-randomization subtlety |
| App A.2: Security Reduction | 900--909 | **error-found** | Major: reduction incomplete |

**Summary**: 2 verified, 3 likely-correct, 4 uncertain (proof absent or informal), 6 error-found. The errors range from reversed inequalities (Thm 5.5) to fundamental mathematical incorrectness (Thm 2.1, Thm 7.1). The space bound results (Thm 5.1, 5.2, Cor 5.3) are the most solid; the algebraic and security results are the weakest.
