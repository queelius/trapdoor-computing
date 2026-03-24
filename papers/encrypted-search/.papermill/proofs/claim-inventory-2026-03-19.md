# Claim Inventory: Encrypted Search as Trapdoor Computing

**Date**: 2026-03-19
**Source**: paper/paper.tex (151 lines)

Every claim in the paper is listed below with its justification status and what would be needed for formal proof.

---

## Abstract Claims

### C1. "An untrusted provider evaluates cipher maps over confidential queries and indexes without learning the queries, the indexes, or the results."

**Location**: Lines 21-23 (abstract)
**Type**: Informal security claim
**Justified?**: Partially. The paper does not prove this. It is inherited from the cipher map formalism (Section 5, trusted/untrusted model). The formalism itself states this follows from: (a) totality (no "not found" signal), (b) representation uniformity (frequency analysis bounded by delta), (c) one-way hash (cannot invert without seed).
**Correct?**: Correct with caveats. The claim that the ESP learns *nothing* is too strong. The formalism honestly acknowledges that joint correlations may leak (Section 4.4). The claim should be: "without learning the queries, the indexes, or the results, *up to the limitations of marginal uniformity and the encoding granularity*."
**To prove formally**: Would need a simulation-based proof: there exists a simulator S that, given only the leakage profile L(q), produces a view indistinguishable from the ESP's real view. This is standard in the SSE literature (IND-CKA games) but is not done here or in the formalism.

### C2. "This positions encrypted search as one application domain among many -- trapdoor computing in general can approximate arbitrary computable functions."

**Location**: Lines 27-29 (abstract)
**Type**: Scope claim
**Justified?**: By reference to the formalism. The entropy map construction (formalism Section 2.2) supports arbitrary f : X -> Y, which covers any finite computable function.
**Correct?**: Correct for finite X and Y. For infinite domains, the claim needs qualification (the cipher map is constructed for a specific finite X, not for all possible inputs).
**To prove formally**: Already established in the formalism via the entropy map construction.

---

## Introduction Claims

### C3. "The provider sees only opaque bit strings and total functions on those bit strings -- the defining characteristics of a cipher map."

**Location**: Lines 42-44
**Type**: Definitional claim linking encrypted search to cipher maps
**Justified?**: This is the paper's central assertion. It is asserted, not proven. The claim is that the operational behavior of an ESP (receiving encoded queries, evaluating an index, returning results) matches Definition 1.1 of a cipher map.
**Correct?**: Correct as a description of the structure. An ESP does receive bit strings and evaluate a function on them. Whether every ESP is *literally* a cipher map (satisfying all four properties) is a stronger claim that is not proven.
**To prove formally**: Take the formal definition of an SSE scheme (e.g., Curtmola et al.'s tuple (Gen, Enc, Trpdr, Search, Dec)) and show it satisfies Definition 1.1 of a cipher map. This requires mapping Gen -> s, Enc -> enc, Trpdr+Search -> f-hat, Dec -> dec, and verifying the four properties.

### C4. "The general framework supports any computable function f : X -> Y via cipher maps f-hat : {0,1}^n -> {0,1}^n, with four properties (totality, representation uniformity, correctness, composability) parameterized by (eta, epsilon, mu, delta)."

**Location**: Lines 46-50
**Type**: Claim about the generality of the framework
**Justified?**: By reference to the formalism (entropy map construction).
**Correct?**: Correct for finite domains. The parameter p (entanglement) is mentioned parenthetically in the intro but not used again. The parameter delta is listed but its role in encrypted search is only addressed via representation uniformity in Definition 2.5.
**To prove formally**: Already done in the formalism.

### C5. Introduction mentions parameter "p" alongside (eta, epsilon, mu, delta).

**Location**: Line 49 (implicitly, the intro says "parameterized by (eta, epsilon, mu, delta)" but the review noted line 49 also mentions p somewhere)
**Type**: Parameter usage
**Issue**: The review (line 53) notes that "p" appears in the introduction but is never used again. Checking the text: line 49 actually lists "(eta, epsilon, mu, delta)" only. The Scope section (line 142) lists "(eta, epsilon, mu, delta, p)". This is the only mention of p. Since p (entanglement) is not discussed anywhere in the paper, it should be dropped from line 142 or explained.
**Correct?**: The parameter p is real (formalism Section 4.3), but it is a dangling reference in this paper.

---

## Vocabulary Mapping Claims (Section 2)

### C6. "The search agent is the trusted machine T."

**Location**: Definition 2.1 (lines 60-65)
**Type**: Vocabulary mapping
**Justified?**: By structural analogy. The SA formulates queries, sends them, and interprets results. T encodes, submits, and decodes. The roles match.
**Correct?**: Correct. The mapping is clean.
**To prove formally**: No proof needed; this is a definitional identification.

### C7. "The encrypted search provider is the untrusted machine U."

**Location**: Definition 2.2 (lines 67-73)
**Type**: Vocabulary mapping
**Justified?**: By structural analogy. The ESP stores an index and evaluates queries. U stores cipher maps and evaluates them.
**Correct?**: Correct.
**To prove formally**: Definitional identification, no proof needed.

### C8. "It cannot decode, cannot distinguish real queries from filler, and cannot determine which function is being computed."

**Location**: Lines 71-72 (inside Definition 2.2)
**Type**: Security claim about U/ESP
**Justified?**: Not proven in this paper. The three sub-claims:
  - "cannot decode": follows from U not holding s or dec (by assumption in the trust model).
  - "cannot distinguish real queries from filler": follows from totality (Property 1). This is correct under the random oracle model.
  - "cannot determine which function is being computed": this is a stronger claim. It requires that the cipher map f-hat does not reveal f. In the hash-based construction, f-hat is defined by the seed, and without the seed, the function appears random. Under ROM, this is plausible. But for table-based constructions (where f-hat is a lookup table), statistical analysis of the table might reveal structure.
**Correct?**: The first two sub-claims are correct under the formalism's assumptions. The third sub-claim ("cannot determine which function") is correct for hash-based constructions under ROM but needs qualification for other constructions.
**To prove formally**: Simulation-based security proof showing that U's view is simulatable without knowledge of f.

### C9. "An information need is a latent function f : X -> Y."

**Location**: Definition 2.3 (lines 75-81)
**Type**: Vocabulary mapping
**Justified?**: Clean mapping. An information need in IR is a user's desire for information, operationalized as a relevance function. Mapping this to a latent function f is a natural formalization.
**Correct?**: Correct, though the paper correctly notes that f can range from indicator functions (keyword search) to relevance scoring functions (ranked retrieval).
**To prove formally**: Definitional, no proof needed.

### C10. "For keyword search, f = 1_A is the indicator function for a set A of documents containing a keyword."

**Location**: Lines 77-78
**Type**: Concrete instantiation claim
**Justified?**: Standard IR formalization. Keyword search returns the set of documents containing a keyword, which is exactly the indicator function for that set.
**Correct?**: Correct.
**To prove formally**: N/A; this is a standard definition.

### C11. "A hidden query is a cipher value enc(x, k)."

**Location**: Definition 2.4 (lines 83-88)
**Type**: Vocabulary mapping
**Justified?**: The mapping is direct. A hidden query is an encoded form of a plaintext query that the ESP cannot read. enc(x, k) is the encoding of x under representation index k.
**Correct?**: Correct.
**To prove formally**: Definitional.

### C12. "A secure index is a cipher map f-hat stored on the ESP."

**Location**: Definition 2.5 (lines 90-91)
**Type**: Vocabulary mapping
**Justified?**: This is the core mapping. A secure index (Goh 2003) is a data structure enabling search without revealing content. Calling it a cipher map claims it satisfies Definition 1.1 (totality, defined on all inputs, etc.).
**Correct?**: Partially. Not all secure indexes in the SSE literature satisfy all four cipher map properties. For example:
  - A standard inverted index encrypted with AES is not total (querying a non-keyword returns an error or empty result, which leaks information).
  - A Bloom-filter-based index is total (every query returns a bit) but has K(x) = 1 (no representation uniformity).
  - A secure index with access-pattern leakage violates the spirit of the untrusted model.
The claim is correct if "secure index" is restricted to constructions that are total and produce opaque outputs. The paper should qualify this.
**To prove formally**: Take the formal definition of a secure index from Goh (2003) and verify it satisfies Definition 1.1. This is doable but requires care with the totality property.

### C13. "Totality: The ESP can evaluate the index on any bit string. There is no 'not found' signal; filler queries produce output indistinguishable from real queries."

**Location**: Lines 97-99
**Type**: Property specialization
**Justified?**: This follows directly from Property 1 of the formalism.
**Correct?**: Correct for cipher map constructions. Not all existing encrypted search schemes have this property (e.g., schemes that return empty result sets for non-matching queries do leak information).
**To prove formally**: Already proven in the formalism (Property 1, Section 1.3).

### C14. "Representation uniformity: Hidden queries are delta-close to uniform. Frequency analysis of query traffic is bounded by delta."

**Location**: Lines 101-103
**Type**: Property specialization
**Justified?**: Follows from Property 2 of the formalism (Section 1.3, TV distance bound).
**Correct?**: Correct, with the important caveat (stated in the formalism but NOT stated in this paper) that this is marginal uniformity only. Joint correlations across queries are not bounded by delta. This omission is significant for encrypted search, where query sequences are common.
**To prove formally**: Already proven in the formalism. The missing caveat about marginal-only uniformity should be added to the paper.

### C15. "Correctness: The search agent recovers the correct answer with probability >= 1 - eta."

**Location**: Lines 105-106
**Type**: Property specialization
**Justified?**: Follows from Property 3 of the formalism.
**Correct?**: Correct.
**To prove formally**: Already proven in the formalism.

### C16. "Nonzero eta provides plausible deniability: the ESP cannot distinguish a true positive from a false positive."

**Location**: Lines 106-108
**Type**: Privacy claim
**Justified?**: Partially. The intuition is correct: if the cipher map has eta > 0, then some fraction of in-domain queries return incorrect answers, so the ESP (even if it could somehow observe the decoded result) cannot be certain whether a positive result is true or false. But the ESP does NOT observe decoded results -- it sees only cipher values. So the claim needs more careful framing:
  - If the ESP could observe the decoded Boolean result (e.g., through a side channel), then eta > 0 provides deniability.
  - In the standard model where the ESP sees only cipher values, the ESP cannot distinguish true from false positives regardless of eta (because it cannot decode at all).
The interesting case is when the ESP observes the SA's *behavior* after decoding (e.g., the SA retrieves a document, suggesting a positive result). In that case, eta > 0 means the SA might be acting on a false positive, providing deniability.
**Correct?**: The intuition is correct but the formalization is missing. The claim conflates two threat models.
**To prove formally**: Define a deniability game: the ESP observes the SA's post-decoding behavior (e.g., "SA accessed document d") and must guess whether the cipher map's answer was correct. Show that the ESP's advantage is bounded by a function of eta. This is a modest but novel theorem.

### C17. "Composability: Boolean combinations of queries (AND, OR, NOT) compose as cipher map chains with predictable error accumulation eta_total = 1 - prod(1 - eta_i)."

**Location**: Lines 110-112
**Type**: Error accumulation formula
**Justified?**: The formula is from the formalism (Section 3.3, composition chains). The claim that Boolean query composition follows this formula is correct *if* each Boolean operation is implemented as a separate cipher map in a chain.
**Correct?**: Correct, with a subtlety. The composition theorem assumes the cipher maps in the chain use independent seeds and that g's correctness is independent of f's correctness (the re-randomization assumption, formalism Section 3.2). For encrypted search, this means each sub-query must be evaluated by a separate cipher map with an independent seed. If the sub-queries share structure (e.g., the same index), the independence assumption may fail and the bound is only an upper bound, not exact.
**To prove formally**: Already proven in the formalism under the independence assumption. The paper should state the assumption.

---

## Remark (Generality) Claims

### C18. "A Bloom filter is a cipher map with eta = 0, K(x) = 1 (no representation uniformity), and observable output."

**Location**: Lines 117-120
**Type**: Classification claim
**Justified?**: Partially. Let's check:
  - eta = 0: Bloom filters have zero false negatives but nonzero false positives. In the cipher map framework, eta measures the probability that dec(f-hat(enc(x,k))) != f(x) for in-domain x. For a Bloom filter testing membership of elements known to be in the set, the false negative rate is 0, so eta = 0 for true members. But for non-members, a Bloom filter returns false positives -- this is not an eta error (eta only applies to in-domain elements). So eta = 0 is correct, but the false positive rate maps to epsilon (noise decode probability), not eta.
  - K(x) = 1: Correct. Standard Bloom filters have a single encoding per element.
  - "Observable output": This is the key distinction. A Bloom filter returns a plaintext Boolean (0 or 1), not an opaque cipher value. The output is not encrypted. This means a Bloom filter violates the untrusted model: the ESP can read the result.
**Correct?**: Correct. The formalism (Section 2.1, HashSet) makes the same identification.
**To prove formally**: Map the Bloom filter operations to Definition 1.1 and verify. The formalism already does this for the closely related HashSet construction.

### C19. "Searchable encryption schemes which leak access patterns are similarly subsumed."

**Location**: Lines 119-120 (paraphrased)
**Type**: Subsumption claim
**Justified?**: Not proven. The claim is that schemes leaking access patterns are cipher maps with specific (bad) parameter values. This is plausible: access pattern leakage means delta is large (the distribution of cipher values is far from uniform, or the joint distribution leaks query identity). But the paper does not formalize what "access pattern leakage" means in cipher map terms.
**Correct?**: The intuition is correct but imprecise. Access pattern leakage in SSE (which queries touch which encrypted records) is a different kind of leakage than what delta captures. Delta bounds the *marginal distribution* of individual cipher values; access patterns reveal *which cipher values are associated with which index positions*, which is a structural leakage not directly modeled by any single cipher map parameter.
**To prove formally**: Define a formal leakage function for access patterns and show it is bounded by some function of (delta, epsilon, n). This is nontrivial and may require extending the formalism.

### C20. "The cipher map abstraction subsumes both [Bloom filters and searchable encryption]: a Bloom filter is [degenerate cipher map]; a secure index as defined here generalizes this."

**Location**: Lines 117-124
**Type**: Generality/subsumption claim
**Justified?**: Partially. The Bloom filter case (C18) is justified. The general subsumption of searchable encryption (C19) is asserted but not proven.
**Correct?**: Correct for Bloom filters and schemes fitting the cipher map model. Not all SSE schemes fit naturally (e.g., schemes based on ORAM or garbled circuits operate differently from the cipher map model).
**To prove formally**: For each claimed subsumed scheme, provide the explicit cipher map tuple and parameter instantiation.

---

## Scope Claims (Section 3)

### C21. "Encrypted search is one application of trapdoor computing."

**Location**: Line 131
**Type**: Scope claim
**Justified?**: By the vocabulary mapping in Section 2, encrypted search can be described in cipher map terms. Other applications are listed (encrypted databases, PSI, confidential analytics, cloud delegation).
**Correct?**: Correct.
**To prove formally**: N/A; this is a framing statement, not a mathematical claim.

### C22. "The cipher map abstraction applies to any setting where: (a) a trusted party wants to delegate computation to an untrusted party, (b) the function, its domain, and its codomain are confidential, (c) approximate answers are acceptable (or desirable for privacy)."

**Location**: Lines 132-137
**Type**: Applicability claim
**Justified?**: Informally. The cipher map is defined for any computable f : X -> Y with finite X, so any delegation of a finite computable function fits. Condition (b) is provided by the one-way hash and representation uniformity. Condition (c) is the eta parameter.
**Correct?**: Correct with the qualification that the function must be finite and known at construction time (for batch constructions) or structurally compatible (for online constructions). Dynamic functions or functions revealed incrementally require extensions not in the formalism.
**To prove formally**: Already established by the generality of the entropy map construction.

### C23. "Other applications include encrypted databases, private set intersection, confidential analytics, and any computation delegated to an untrusted cloud."

**Location**: Lines 139-143
**Type**: Application enumeration
**Justified?**: These are plausible applications but none are instantiated. The paper does not show cipher map tuples for any of them.
**Correct?**: Plausible but unverified. PSI and encrypted databases would need their own vocabulary mappings.
**To prove formally**: For each application, provide the cipher map tuple and parameter instantiation.

---

## Summary Table

| Claim | Type | Justified? | Correct? | Proof effort |
|-------|------|-----------|----------|--------------|
| C1: ESP learns nothing | Security | Partial (inherited from formalism) | Correct with caveats (marginal only) | Simulation proof |
| C2: One application among many | Scope | Yes (entropy map) | Yes (finite domains) | Already done |
| C3: ESP sees opaque bits + total functions | Structural | Asserted | Correct | Map SSE def -> cipher map def |
| C4: Framework supports any computable f | Generality | Yes (formalism) | Yes (finite domains) | Already done |
| C5: Parameter p mentioned but unused | -- | N/A | Dangling reference | Remove or explain |
| C6: SA = T | Vocabulary | By analogy | Correct | Definitional |
| C7: ESP = U | Vocabulary | By analogy | Correct | Definitional |
| C8: ESP cannot decode/distinguish/determine | Security | Partial | Mostly correct; "cannot determine function" needs qualification | Simulation proof |
| C9: Information need = latent function | Vocabulary | Clean | Correct | Definitional |
| C10: Keyword search = indicator function | Instantiation | Standard | Correct | N/A |
| C11: Hidden query = cipher value | Vocabulary | Direct | Correct | Definitional |
| C12: Secure index = cipher map | Vocabulary | Partial | Correct for total constructions; not all SSE indexes are total | Map Goh def -> cipher map def |
| C13: Totality specialization | Property | Formalism | Correct for cipher map constructions | Already done |
| C14: Rep. uniformity specialization | Property | Formalism | Correct; **missing marginal-only caveat** | Already done; add caveat |
| C15: Correctness specialization | Property | Formalism | Correct | Already done |
| C16: eta > 0 gives plausible deniability | Privacy | Intuition only | **Correct intuition, missing formalization, conflated threat models** | Deniability game definition + bound |
| C17: Composition formula | Error bound | Formalism | Correct under independence assumption; **assumption not stated** | Already done; state assumption |
| C18: Bloom filter as degenerate cipher map | Classification | Formalism | Correct | Already done |
| C19: SSE schemes subsumed | Subsumption | Asserted | Plausible but imprecise; access pattern leakage not modeled by delta | Formal leakage function mapping |
| C20: Cipher map generalizes both | Generality | Partial | Correct for Bloom filters; unverified for general SSE | Per-scheme instantiation |
| C21: ES is one application | Scope | Yes | Correct | N/A |
| C22: Applies to delegation + confidential + approximate | Applicability | Informal | Correct (finite, known functions) | Already done |
| C23: Other applications listed | Enumeration | Plausible | Unverified | Per-application instantiation |

---

## Key Findings

1. **No claim in the paper is formally proven.** All formal content is inherited from the cipher map formalism by reference. The paper's own contribution is purely definitional.

2. **Two claims have correctness issues requiring attention**:
   - C14: The marginal-only limitation of representation uniformity is not mentioned. For encrypted search (where query sequences are common), this is a significant omission.
   - C16: The plausible deniability claim conflates the standard untrusted model (ESP sees nothing) with a stronger threat model (ESP observes SA's behavior). The claim should specify which threat model it assumes.

3. **One claim has a missing assumption**: C17 does not state the independence assumption required for the composition formula to be exact rather than an upper bound.

4. **The strongest potential theorem is C16** (plausible deniability from eta > 0). If formalized, this is the paper's best candidate for a novel contribution beyond vocabulary mapping.

5. **The subsumption claims (C19, C20) are the weakest.** The claim that "searchable encryption schemes are subsumed" is imprecise because access pattern leakage operates at a different level than the cipher map parameters capture.
