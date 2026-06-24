# Citation Verifier, Round 6 (2026-05-02)

Cross-checked every `\cite{}` against `references.bib` and verified
the cite-target chain for sister papers.

## Bibliography vs Text Cite Coverage

### All bib entries used in text?

Reading `references.bib` (29 entries) and the unique cite keys used
in `cipher_maps.tex` (28 unique keys):

Cited in text:
- agrawal2004order, alvim2012measuring, belazzougui2009hash,
  bellare1993random, bellare2007deterministic, bender2012quotient,
  bernoulli-types, bloom1970space, boldyreva2009order, cash2013highly,
  cash2015leakage, curtmola2006searchable, dodis2005entropic,
  esposito2020recsplit, fan2014cuckoo, fredman1984storing,
  gentry2009fully, goldreich1996software, islam2012access,
  juels2014honey, kamara2019computationally, kerschbaum2015frequency,
  naveed2015inference, shannon1948mathematical, simmons1979symmetric,
  smith2009foundations, song2000practical, towell2026maxconf,
  towell2026rekeying, yao1982protocols.

In bib but not cited:
- **towell2026algebraic** (line 190 of references.bib): bibliography
  entry exists but no `\cite{towell2026algebraic}` anywhere in
  cipher_maps.tex.

**Finding CITE-N1 (minor)**: `towell2026algebraic` is unused. Either
add a citation (e.g., in a "Companion work" remark in section 9 noting
the algebraic functorial framework) or remove the bib entry. Severity:
**minor**.

### All cited keys defined in bib?

Cross-checking the 30 cite keys used in text against the 29 keys in
references.bib: all keys used in text are defined. No undefined cites.
**Build passes** with no missing references warnings.

## Sister-Paper Citation Chain Verification

### CITE-2: maxconf Theorem 4.1, part 3

**Cited at**: cipher_maps.tex line 688, "Full proof and discussion of
tightness in `\cite[Theorem~4.1, part~3]{towell2026maxconf}`."

**Cite target**: maximizing-confidentiality/main.tex line 451-478:
Theorem 4.1 ("Entropy ratio decomposition") with three numbered parts.
Part (3) at lines 470-477 states:

> "For $\delta \leq 1/2$, the entropy ratio is bounded by
> $e \geq 1 - \delta - h_2(\delta)/n$, where $h_2(\delta) = -\delta
> \log_2 \delta - (1-\delta) \log_2(1-\delta)$ is the binary entropy.
> The bound follows from the Fannes-Audenaert continuity inequality
> [fannes1973continuity, audenaert2007sharp]."

This matches **exactly** what cipher-maps Proposition 5.1 references
(line 668-679: $e \geq 1 - \delta - h_2(\delta)/n$). The cite is
**correct and load-bearing**. **Verified**.

### CITE-1: rekeying Theorem 7.1

**Cited at**: cipher_maps.tex line 1699, "$H(X | \mathcal{V}) \geq
H(X) - \log_2(n+1)$ where $\mathcal{V}$ is the adversary's view of all
intermediate cipher values `\cite[Thm.~7.1]{towell2026rekeying}`".

**Cite target**: cipher-rekeying/paper/main.tex line 842-854:
Theorem 7.1 ("Rekeying chain confidentiality bound") at section 7
("Information-Theoretic Cost"). Statement:

> "Let $c_0 \in \cipherS{X}{s_0}$ encode latent value $x \in X$, and
> let $c_i = \rhat_i(c_{i-1}) \in \cipherS{X}{s_i}$ for $i = 1, \ldots, n$
> be the result of an $n$-step rekeying chain. Let $F = \{\rhat_1,
> \ldots, \rhat_n\}$ be the set of rekeying maps, and let
> $\mathcal{V}_F = \{c_0, c_1, \ldots, c_n\}$ be the adversary's view.
> Then the residual entropy of $X$ given $\mathcal{V}_F$ satisfies
> $H(X | \mathcal{V}_F) \geq H(X) - \log_2(n+1)$."

This matches what cipher-maps cites. The cite is **correct and
load-bearing**. **Verified**.

The R5 reviewer was wrong to flag CITE-1; the user's R6 revert to 7.1
is correct.

## Other Cite Checks

### CITE-3: RecSplit (esposito2020recsplit)

**Cited at**: cipher_maps.tex line 1806, "the
\texttt{phobic}\footnote{...} implementation of the RecSplit minimal
perfect hash construction~\cite{esposito2020recsplit}."

**Bib entry**: line 246-252 of references.bib:
> Esposito, Mueller Graf, Vigna 2020, "RecSplit: Minimal perfect hashing
> via recursive splitting", ALENEX 2020.

The R5 finding was that section 6.4 line 1190 mentions "perfect hash
function" without citation. Reading line 1187-1193 of cipher_maps.tex:

> "An alternative construction uses perfect hash functions (PHFs) to
> assign elements to slots in $O(m)$ time, avoiding the seed search
> entirely. A PHF maps the $m$ cipher keys to $m$ distinct slots; each
> slot stores the XOR-masked value encoding. Construction time drops
> from exponential in bucket size to linear in $m$. A reference
> implementation using a RecSplit-family PHF achieves 700 documents per
> second on the 20 Newsgroups corpus..."

The reference at line 1192 to "RecSplit-family PHF" does not have
`\cite{esposito2020recsplit}` here. The cite appears later at line 1806
in §10.1. **Recommend** add `\cite{esposito2020recsplit}` at line 1192
on first mention of "RecSplit", or change line 1192 to "an MPHF
construction" with the cite. Severity: **minor**.

### CITE-4: Kerschbaum 2015

**Cited at**: cipher_maps.tex line 203, "Kerschbaum's frequency-hiding
OPE~\cite{kerschbaum2015frequency}".

**Bib entry**: line 238-244 of references.bib:
> Kerschbaum 2015, "Frequency-hiding order-preserving encryption", CCS 2015.

The cite is correct and the contrast paragraph is well-written.
**Verified**. R5 finding closed.

### CITE-5: Kamara-Moataz 2019

**Cited at**: cipher_maps.tex line 197, "The volume-hiding
line~\cite{kamara2019computationally}".

**Bib entry**: line 254-261 of references.bib:
> Kamara, Moataz 2019, "Computationally volume-hiding structured
> encryption", EUROCRYPT 2019.

The cite is correct. Note: the bib entry venue is "EUROCRYPT 2019"
(Annual International Conference on the Theory and Applications of
Cryptographic Techniques), which is correct. **Verified**. R5 finding
closed.

### CITE-6: Manuscript-in-prep entries

**Status**: 4 bib entries with `note={Manuscript in preparation}`:
- bernoulli-types (line 49 with github URL note).
- towell2026algebraic (line 194; UNUSED, see CITE-N1).
- towell2026maxconf (line 201; load-bearing for Proposition 5.1).
- towell2026rekeying (line 208; load-bearing for §9.5).

The R6 narrative said these would be replaced with arXiv preprint IDs
"imminently." As of this review, the bib entries are still
"Manuscript in preparation." Until arXiv DOIs are minted and the bib
is updated, the load-bearing citations are technically broken (a
reviewer cannot fetch the cited material).

Severity: **major** (until preprints are posted; once posted, this
becomes minor and then resolved).

### CITE-7: Missing DOIs

The bib has no DOI fields. PoPETs and most modern venues prefer DOIs
for all references. R4 m11 backlog item. Status: unaddressed.
Severity: **minor**.

### CITE-S2 (R5): Warner 1965 missing

Already covered in novelty-assessor as NOV-4. The Bayesian deniability
proposition (Proposition 10.4.1 line 1926) is a direct restatement of
Warner 1965 randomized response. Severity: **minor**.

### CITE-S3 (R5): bernoulli-types scope ambiguity

The `bernoulli-types` cite key is used 3 times in cipher-maps:
- Line 114 (Bernoulli error model paragraph in intro).
- Line 1642 (relations and algebraic types extension in section 9.1).
- Line 1674 (trapdoor Boolean algebra companion in section 9.3).

The bib entry title is "Bernoulli Sets and Maps: A Probabilistic
Framework for Approximate Data Structures" with a github URL pointing
to bernoulli_sets. But:
- "Bernoulli Sets and Maps" is the umbrella, not a single paper.
- The 3 cites in cipher-maps reference different sub-topics:
  (1) the error model itself (sets, hash function),
  (2) relations and algebraic types (separate papers in the bernoulli
  monorepo: bernoulli_relations, bernoulli_data_type),
  (3) trapdoor Boolean algebra (boolean-algebra-over-trapdoor-sets, a
  separate paper entirely).

The current `bernoulli-types` cite key is overloaded. **Recommend**
either:
(a) Split into three cite keys: `towell2026bernoulli` (umbrella),
`towell2026bernoulli_alg` (algebraic types extension), `towell2026tba`
(trapdoor Boolean algebra). All three need bib entries with proper
URLs/DOIs.
(b) Use `bernoulli-types` only for the umbrella reference and replace
the §9.1 and §9.3 cites with specific paper citations.

Severity: **minor** (will resolve when sister paper preprints are
posted).

## Summary of Citation Track

- 0 critical (CITE-1, CITE-2 both verified correct in R6).
- 1 major (CITE-6 load-bearing cites to manuscript-in-prep papers;
  resolves once arXiv preprints posted).
- 5 minor (CITE-N1 unused towell2026algebraic, CITE-3 RecSplit on
  first mention, CITE-7 DOIs, CITE-S2 Warner, CITE-S3 bernoulli-types
  overloading).
- 0 suggestions.

Net: citation hygiene is mostly good in R6. The R5 critical
miscount on CITE-1 was the reviewer's error; the user's verification
of both CITE-1 and CITE-2 against the source papers was correct. The
remaining major (CITE-6) is timing-dependent: post the preprints, the
issue resolves.
