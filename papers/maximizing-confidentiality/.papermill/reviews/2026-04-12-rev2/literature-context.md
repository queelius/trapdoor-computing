# Literature Context (Rev2 - Regression Check)

**Paper**: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
**Date**: 2026-04-12 (rev2)
**Sources**: Morning round 2026-04-12 literature-context.md (which itself
was synthesized from the 2026-04-09 scout output and area-chair direct
verification); area-chair re-verification against the rev2 manuscript.

---

## Context note

The Task-dispatched literature scouts (`papermill:literature-scout-broad`
and `papermill:literature-scout-targeted`) could not be launched in
this environment. The literature context is carried over from the
morning round with rev2-specific updates noted below.

---

## Update relative to morning round

### Resolution of priority gaps from morning's literature-context

| Prior priority | Reference | Status in rev2 |
|---|---|---|
| HIGH | Smith 2009 (QIF) | Cited in §2 (no change) |
| HIGH | Alvim et al. 2020 (QIF) | Cited in §2 (no change) |
| HIGH | Simmons 1979 (homophonic) | **Now cited** in §4.2 (was uncited) |
| HIGH | Fannes 1973 / Audenaert 2007 (continuity) | **Now cited** in §1, §3.3 (was uncited) |
| MEDIUM | Bost-Fouque 2017 | Cited in §2 (venue still wrong) |
| MEDIUM | Demertzis et al. 2020 | Cited in §2 (no change) |
| HIGH | Oya-Kerschbaum 2021 | Still not cited |
| MEDIUM | Bellare-Boldyreva-O'Neill 2007 | Not cited |
| MEDIUM | Dodis-Smith 2005 | Not cited |
| MEDIUM | Fuller et al. 2017 (SoK) | Not cited |

Net: of the morning's three highest-priority gaps (Smith, Alvim,
Simmons), all three are now resolved in the text. Two new high-
priority citations (Fannes 1973, Audenaert 2007) were added correctly
to support the rewritten Thm 3.1 proof.

The remaining HIGH-priority gap is Oya-Kerschbaum 2021 (search-pattern
leakage), directly relevant to Thm 5.1's compositional leakage motivation.

### New citations added in rev2

| Citation | Where used | Attribution check |
|---|---|---|
| `simmons1979symmetric` | §4.2 line 565 | Marginal -- Simmons 1979 is more about asymmetric crypto than homophonic substitution per se; the historical reference for homophonic substitution would be Kahn 1967 or earlier. Defensible at the textbook-citation level. |
| `fannes1973continuity` | §1 line 102, §3.3 line 423 | Correct: M. Fannes, *A continuity property of the entropy density for spin lattice systems*, Comm. Math. Phys. 31, 291-294, 1973 |
| `audenaert2007sharp` | §1 line 102, §3.3 line 423 | Correct: K. Audenaert, *A sharp continuity estimate for the von Neumann entropy*, J. Phys. A 40, 8127-8136, 2007. Provides the sharp $t \log_2(d-1) + h_2(t)$ form actually used in proof. |
| `cover2006elements` | §5.1 Thm 5.1 part 3 proof | Permissive textbook reference; tighter sources exist (Devroye-Gyorfi-Lugosi 1996 for empirical TV; Han-Jiao-Weissman 2015 for minimax) |

---

## Pinsker -> Fannes update

The morning literature-context noted that "Pinsker's inequality
bridging total-variation to KL-divergence is a workhorse in
cryptography" with examples in zero-knowledge (Sahai-Vadhan),
fuzzy extractors (Dodis-Ostrovsky-Reyzin-Smith), and Vadhan's
*Pseudorandomness* textbook.

**Updated assessment**: Now that the paper uses Fannes-Audenaert
instead of Pinsker, the relevant prior-art class shifts:

- **Fannes-Audenaert continuity in QIF**: Less commonly used than
  Pinsker in the cryptography literature. The Audenaert 2007 sharp
  form is more prevalent in quantum information theory. In classical
  QIF, the Shannon-entropy continuity question is more often
  approached via Pinsker (KL distance) or via differential-privacy
  composition theorems. The paper's specific use of Fannes-Audenaert
  to bound entropy from a TV bound is **uncommon in the
  cryptography/SSE literature**; this is a small flag in favor of
  the bridge as a non-textbook framing.

- **Concrete prior art for $\delta \to e$ in cipher-map / homophonic
  setting**: I am not aware of a directly comparable bridge. Massey
  1994 (*An introduction to contemporary cryptology*) discusses
  homophonic substitution and entropy bounds heuristically but
  doesn't give a Fannes-style derivation. So the paper's specific
  claim retains framing novelty even with the corrected proof.

**No known prior work** does the specific:
> "$\delta$-uniform cipher-value distribution implies entropy ratio
> $e \geq 1 - \delta - h_2(\delta)/n$"

translation in a cryptographic / cipher-map setting. The mathematical
input (Fannes-Audenaert) is textbook; the *bridge* in this context is
the paper's contribution. With the corrected linear bound, this is a
defensible (if modest) contribution.

---

## $K(x) \propto D(x)$ update

The morning round noted that the classical homophonic substitution
prescription is $K(x) \propto D(x)$ (Simmons 1979 and earlier
classical sources). The paper's morning version had the inverted
formula; rev2 corrects this.

**Updated literature note**: The classical homophonic substitution
literature (Massey 1994; Heys 2001; Stinson 2006 *Cryptography:
Theory and Practice* chapter on classical ciphers) consistently
states the rule "more frequent plaintext letters get more ciphertext
representations." This is the rule rev2 now uses. No prior-art
inconsistency.

---

## Compositional leakage update

The morning round positioned Thm 5.1 (compositional leakage) against
the SSE joint-leakage literature (Kellaris et al. 2016, Cash et al.
2015, Oya-Kerschbaum 2021, Grubbs et al. 2017). The afternoon round
sharpens Thm 5.1 (sampling model explicit, MI preservation, Part 4
quantitative) without adding citations to the SSE thread.

**Updated assessment**: With Thm 5.1 sharpened, the contribution
relative to the SSE literature is clearer:
- *Spirit*: established (Cash et al. 2015 is in the bib but uncited;
  Kellaris et al. 2016 not cited; Oya-Kerschbaum 2021 not cited).
- *Quantitative*: Thm 5.1 part 3 ($N = O(|Y_1||Y_2|/\xi^2)$) is the
  standard plug-in rate, novel only in the cipher-map framing.
- *Quantitative-with-novelty*: Thm 5.1 part 4 ($\delta_3 \geq
  \TV(\text{joint}, \text{prod})$) is non-trivially new -- I cannot
  identify a directly comparable claim in the SSE literature.

The paper's compositional contribution is solidified by the rev2 fixes
even without new citations.

---

## Benchmark context (carry-over, unchanged)

20 Newsgroups is still not a standard encrypted search benchmark.
The morning round suggested adding a one-sentence justification of
the corpus choice in §7 header; this has not been addressed in rev2.

---

## Summary of literature-context update

The rev2 fixes resolve three of the morning's high-priority citation
gaps (Simmons cited; Fannes 1973 and Audenaert 2007 added). One
high-priority gap remains (Oya-Kerschbaum 2021). The Pinsker -> Fannes
shift slightly *strengthens* the bridge contribution's framing
novelty: Fannes-Audenaert is less commonly used in cryptography than
Pinsker, so the specific cipher-map application is more distinctive.
The compositional leakage theorem (Thm 5.1) is sharper after the
rev2 fixes, with part 4 being a genuine quantitative contribution.

The paper's literature positioning is in better shape than the
morning round. Remaining gaps are: Oya-Kerschbaum 2021 cite, possibly
Kellaris et al. 2016, and the Bost-Fouque venue correction.
