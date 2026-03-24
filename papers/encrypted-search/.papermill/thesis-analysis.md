# Thesis Analysis: Encrypted Search as Trapdoor Computing

**Date**: 2026-03-19
**Paper length**: ~150 lines, 3 pages (draft)

## Main Claim

Encrypted search is a special case of trapdoor computing. The standard encrypted search vocabulary (search agents, encrypted search providers, information needs, hidden queries, secure indexes) maps directly to the four-property cipher map framework (trusted/untrusted machines, latent functions, cipher values, cipher maps with totality, representation uniformity, correctness, composability). Traditional constructions like Bloom filters and searchable encryption are subsumed as specific cipher map instantiations.

## What's Novel

The novelty is **reframing**, not construction. The paper claims:

1. **Vocabulary unification**: Encrypted search terminology (SA, ESP, information need, hidden query, secure index) is shown to be domain-specific naming for the general cipher map concepts (trusted machine, untrusted machine, latent function, cipher value, cipher map).

2. **Generalization via subsumption**: Bloom filters are cast as cipher maps with eta=0, K(x)=1, and observable output -- a special case with no representation uniformity and no output privacy. Searchable encryption schemes that leak access patterns are similarly subsumed. The cipher map abstraction generalizes both by making output opaque and supporting arbitrary latent functions (not just set membership).

3. **Positioning encrypted search as one application among many**: The paper argues the same formalism covers encrypted databases, private set intersection, confidential analytics, etc. -- only the choice of latent function f and parameter trade-offs change.

## What's Missing to Make This Complete

### Critical gaps

1. **No bibliography**: Zero citations. The TODO notes acknowledge this. The paper needs references to Song et al. (2000), Goh (2003), Curtmola et al. (2006), Cash et al. (2013), and the formalism paper itself. Without citations, the "vocabulary mapping" claim is not grounded in the literature it claims to reframe.

2. **No concrete constructions**: The paper maps vocabulary but does not instantiate it. A keyword search cipher map, a ranked retrieval cipher map, or a Boolean query composition cipher map would demonstrate the framework's utility beyond definitions.

3. **No parameter analysis**: The four properties are specialized to encrypted search in Section 2, but no concrete parameter values (eta, epsilon, mu, delta) are derived for any encrypted search scenario. The formalism's strength is quantitative; without numbers, the mapping is purely qualitative.

4. **No comparison to existing constructions**: The remark about Bloom filters and searchable encryption (lines 116-125) asserts subsumption but does not prove it or trace the parameter correspondence in detail.

### Structural gaps

5. **No related work section**: Standard for any paper reframing an existing domain.

6. **No conclusion/discussion**: The paper ends with a Scope section and TODOs.

7. **No proofs or derivations**: The error accumulation formula (line 112) is stated but not derived in this paper (it comes from the formalism).

### Desirable additions

8. **Concrete example walkthrough**: Take a specific encrypted search system (e.g., Goh's secure index construction), show it as a cipher map tuple (f-hat, enc, dec, s), derive its four-property parameters.

9. **Comparison table**: Existing encrypted search constructions vs. cipher map parameters -- what does each construction achieve and fail at, in cipher map terms?

10. **Relationship to ORAM**: The paper should address why this is NOT ORAM and what the difference is. The Scope section hints at this but does not make the distinction explicit.
