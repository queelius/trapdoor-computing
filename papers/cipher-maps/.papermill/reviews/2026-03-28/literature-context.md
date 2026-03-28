# Literature Context

**Date**: 2026-03-28
**Paper**: "Cipher Maps: Total Functions as Trapdoor Approximations"

## Field Survey

### Privacy-Preserving Computation (PETs Community)

The PoPETs community expects papers to engage with the dominant privacy paradigms and clearly position novel work. The current landscape includes:

1. **ORAM and oblivious computation**: Goldreich & Ostrovsky (1996) [cited]; Path ORAM (Stefanov et al., CCS 2013) [NOT cited]; recent Circuit ORAM variants. The paper correctly distinguishes itself from ORAM but does not cite Path ORAM, which is the most-cited practical ORAM construction.

2. **Trusted Execution Environments (TEEs)**: Intel SGX, ARM TrustZone. A growing body of PoPETs work uses TEEs for trusted computation. The paper's trusted/untrusted model has structural similarity to TEE-based architectures but does not mention TEEs.

3. **Differential Privacy**: The paper correctly notes it is not differential privacy (Section 9.5). No missing citations needed.

4. **Property-preserving encryption attacks**: Naveed, Kamara, and Wright (CCS 2015) "Inference Attacks on Property-Preserving Encrypted Databases" is a landmark paper showing that OPE/DET leakage is exploitable in practice. The paper cites OPE [Agrawal 2004, Boldyreva 2009] and DET [Bellare 2007] but does NOT cite the attack literature. A PoPETs reviewer familiar with the leakage-abuse literature would notice this gap.

5. **Frequency analysis attacks on encrypted databases**: Islam, Kuzu, and Kantarcioglu (CCS 2012) "Access Pattern Disclosure on Searchable Encryption" and Kellaris et al. (CCS 2016) on reconstruction attacks. The cipher map's representation uniformity (Property 2) is designed to resist frequency analysis, but the paper does not cite the attacks it is defending against.

### Missing Citations That PoPETs Reviewers Would Expect

**High priority (likely to be flagged):**
- Naveed, Kamara, Wright (CCS 2015) -- inference attacks on PPE databases
- Grubbs, Lacharite, Minaud, Paterson, Smart (S&P 2019) -- leakage abuse on structured encryption
- Kamara, Moataz (EUROCRYPT 2019) -- computationally volume-hiding structured encryption
- Bost (CCS 2016) or Demertzis et al. -- forward/backward privacy in dynamic SSE

**Medium priority:**
- Mitzenmacher and Upfal (2005, textbook) -- probability and computing, for the Bernoulli/hash analysis
- Carter and Wegman (JCSS 1979) -- universal hashing
- Pagh and Rodler (JCSS 2004) -- cuckoo hashing (related to cuckoo filters already cited)
- Dietzfelbinger et al. (FOCS 1988) -- polynomial hashing

**Lower priority but would strengthen the paper:**
- Dwork, Naor, Reingold (STOC 2004) or Dodis, Smith (EUROCRYPT 2005) -- entropic security (most similar theoretical framework to cipher maps' information-theoretic approach)
- Esposito et al. (ESA 2020) RecSplit / Genuzio et al. PTHash -- modern perfect hashing

### Direct Competitors / Overlapping Claims

No paper in the literature proposes the exact same abstraction (total function as privacy mechanism via acceptance predicate). The closest works are:

1. **Honey encryption** (Juels & Ristenpart, EUROCRYPT 2014): Maps any decryption key to a plausible-looking plaintext, ensuring indistinguishable outputs. Shares the "every input produces output" property. The paper does NOT cite honey encryption, and a PoPETs reviewer would likely draw this comparison.

2. **Deterministic encryption with input distributions** (Bellare et al., CRYPTO 2007) [cited]: Provides security when input has sufficient entropy. The cipher map's representation uniformity is analogous to the min-entropy requirement.

3. **Homophonic substitution** (Simmons 1979) [cited]: The paper correctly identifies this connection.

### Potential Conflicts or Subsumption

- The information-theoretic lower bound (-log2(eps) + H(Y) bits/element) is a standard result in the AMQ/Bloom filter literature. The paper presents it as if novel; it should more clearly attribute the membership component to Carter, Mitzenmacher, Goodrich et al.
- The composition formula eta_total = 1 - prod(1 - eta_i) is standard for independent error events. The paper frames this as a theorem about cipher maps specifically, but the result is more general.

### Benchmark Gaps

The paper is purely theoretical with no experiments. PoPETs papers typically include:
- Performance benchmarks (construction time, query time)
- Concrete parameter instantiations
- Comparison tables against deployed systems

The absence of any implementation or evaluation is a significant gap for PoPETs, which tends to favor practical contributions over pure theory.
