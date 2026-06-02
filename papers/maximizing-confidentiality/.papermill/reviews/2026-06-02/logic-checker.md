# Logic-Checker Report, Round 5 (2026-06-02, cross-paper)

**Paper**: "The Entropy Ratio" (`main.tex`, 25pp)
**Scope**: (A) cross-paper claim-level inheritance accuracy; (B) re-verify
the new Theorem 5.2 (Le Cam/Assouad) lower-bound sketch. Intra-paper proofs
and numerics were verified in rounds 1 to 4 and are not re-litigated.

---

## A. Claim-level inheritance findings

### A1. FPR formulas over-attributed to cipher-maps (HIGH)

**Claim in our paper.** Theorem `thm:fpr-compounding` (lines 999 to 1009)
states AND-chain FPR `= p_T^k` and OR-chain FPR `= 1 - (1-p_T)^k`,
attributed via `\cite[Sec.~8]{towell2026cipher}` (which after the
citation-verifier fix becomes `[Sec.~7.4]`).

**What cipher-maps actually proves.** cipher-maps §7.4 ("Error Accumulation
by Gate Type", `cipher_maps.tex` lines 1637 to 1646) does NOT state these
closed forms. It only says each gate "induces a different case table" and
that "interval arithmetic propagates bounds." There is no `p_T^k` and no
`1-(1-p_T)^k` in that subsection. The explicit closed-form FPR-compounding
formulas, with empirical validation, live in the **algebraic-cipher-types**
paper (its Table 3, `tab:fpr-compounding`), and the formulas themselves are
elementary (independence of k Bernoulli filters).

**Verdict.** Even after the section-number fix, the attribution
over-credits cipher-maps for a specific result it does not state. This is a
correctness-of-attribution issue, not a math error (the formulas are true).

**Fix (mechanical).** Either (a) state the formulas as elementary and cite
cipher-maps §7.4 only for the gate-type framing: "For k independent
Boolean-valued cipher maps, the FPR compounds elementarily as ... ; the
gate-type accounting is from [Sec.~7.4]{towell2026cipher}, and the empirical
validation is [Table 3]{towell2026algebraic}." Or (b) drop the inheritance
claim and present `thm:fpr-compounding` as the paper's own elementary
restatement (it is short enough). Recommend (a): it is honest about where
the empirical confirmation lives and keeps the gate-type credit.

### A2. Granularity spectrum table over-attributed to cipher-maps Prop 8.1 (MEDIUM)

**Claim in our paper.** Proposition `prop:granularity` (line 739) is cited
as `[Prop.~9.1]{towell2026cipher}` (after fix: `[Prop.~8.1]`), and the
spectrum **table** at lines 760 to 770 (Root `p=k` / `O(|Y|^k)` ...
Leaf `p=1` / `O(k|Y|)`) is presented immediately under it as if it were part
of that proposition's content.

**What cipher-maps Prop 8.1 actually states.** cipher-maps Prop 8.1
("Granularity and privacy", `cipher_maps.tex` lines ~1690 to 1715) defines
the entanglement parameter p, the component-wise (`p=1`) vs joint (`p=2`,
`p=k`) levels, and proves that independent component-wise maps leak the
correlation even at `delta=0`. It does NOT contain the `O(|Y|^k)` vs
`O(k|Y|)` space spectrum **table**. That table matches the **spine** §4.3
("The spectrum", `cipher-map-formalism.md` lines 547 to 558), which presents
it as the spine's synthesis, not as cipher-maps Prop 8.1.

**Verdict.** The proposition statement (lines 741 to 754) is faithful to
cipher-maps Prop 8.1. The space-spectrum table is broader than Prop 8.1 and
should not sit silently under the `[Prop.~8.1]` attribution.

**Fix.** Add one clause crediting the table to the granularity discussion as
a whole, e.g. caption or lead-in "The space costs across the spectrum
(below) follow from the entanglement parameter of [Sec.~8]{towell2026cipher}
and are summarized in the formalism." Low-effort; protects against a
reviewer who checks Prop 8.1 and finds no table.

### A3. Orbit-closure bound: wrong form AND wrong denominator (HIGH)

This is the most substantive cross-paper inconsistency.

**Claim in our paper.** Lines 789 and 1076 state
`conf_F(c) >= 1 - |orbit_F(c)| / 2^n`, attributed to algebraic
`[Thm.~5.3]{towell2026algebraic}`.

**Two problems, both confirmed against source:**

1. **Wrong form.** algebraic Thm 5.3 (`thm:confidentiality-bound`,
   `algebraic/main.tex`) states the **entropy form**
   `H(X | V_F(c)) >= H(X) - log_2 |orbit_F(c)|`. It does NOT state a set form
   with a denominator. Our paper attributes a set-form inequality to a
   theorem that proves the entropy form. (The algebraic paper's set form, if
   present, lives elsewhere; Thm 5.3 as labeled is the entropy form.)

2. **Wrong denominator.** The spine §4A.2 (`cipher-map-formalism.md`
   line 614) gives the canonical set form as
   `conf_F(c) >= 1 - |orbit_F(c)| / |X|` (denominator **|X|**). Our paper
   uses **2^n**. These differ whenever `|X| < 2^n` (the generic case, since
   the domain is diluted into the n-bit cipher space). With `|X| < 2^n`,
   `|orbit|/2^n` is smaller than `|orbit|/|X|`, so our paper's bound is
   numerically **looser** (claims more confidentiality) than the spine's.

**Adjudication.** The spine is authoritative on shared definitions
(`cipher-map-formalism.md` line 9, and §8 Paper Map assigns Measure C1 to
the algebraic paper with the `|X|` denominator). The `|X|` form is the
defensible one: orbit closure bounds the residual uncertainty of the
**latent** X, whose support is X, so the relevant normalizer is `|X|`, not
the ambient `2^n`. Using `2^n` silently inflates the confidentiality claim.

**Fix (recommended).** Replace `2^n` with `|X|` at lines 789 and 1076, and
either (i) cite the entropy form as stated, "Thm 5.3 gives
`H(X | V_F(c)) >= H(X) - log_2|orbit_F(c)|`; equivalently
`conf_F(c) >= 1 - |orbit_F(c)|/|X|`", or (ii) keep the set form but add "(set
form of [Thm.~5.3]{algebraic}; see spine §4A.2)". This aligns both the form
and the denominator with the authoritative source and removes an
optimistic-direction discrepancy.

### A4. C-4 Le Cam dual-role footnote absent (MEDIUM)

Confirmed: our paper has **no footnote** at the Thm 5.2 Le Cam site
distinguishing its role (compositional LOWER bound, Measure C3) from the
cipher-maps Le Cam role (marginal UPPER bound on a single-guess attacker,
Measure M2, cipher-maps §5.3). The spine §4A.3 recommends each paper add the
one-clause footnote. Without it, a reader who has seen "by Le Cam" in
cipher-maps will assume the same bound. **Fix:** add at the Thm 5.2 proof a
footnote: "Le Cam's two-point method appears at the marginal scale in the
companion (an upper bound on a single-guess distinguisher, accuracy
`<= 1/2 + delta/2`); here it is used at the compositional scale as a lower
bound on the joint-recovery minimax rate. Same tool, opposite role." (See
also the terminology note in B2 below: the construction is actually
Assouad's, so the footnote should say "two-point/Assouad" or just "the
two-point method generalized to a hypercube packing.")

---

## B. Theorem 5.2 (compositional lower bound) re-verification

### B1. Construction is valid; one constant-factor slip (LOW to MEDIUM)

The packing construction (lines 906 to 927): pair the `m = |Y_1||Y_2|` cells
into `m/2` pairs, set `P^(s)(v_i^pm) = (1/m)(1 +- s_i*eps)`. I verified
numerically:

- Each `P^(s)` sums to 1 (valid distribution). Confirmed.
- **Pairwise TV claim is off by a factor of 2.** The paper states
  `TV(P^(s), P^(s')) = (eps/m) * d_H(s, s')`. Direct computation gives
  `TV = (2 eps/m) * d_H(s, s')`: a coordinate where `s_i != s'_i`
  contributes `eps/m` on the `+` cell and `eps/m` on the `-` cell, summing
  to `2 eps/m` before the factor-`1/2` in TV cancels against the two cells,
  netting `2 eps/m` per unit Hamming distance. (Verified: at `d_H=1`,
  TV `= 0.025` for `eps=0.1, m=8`, versus the paper's `eps/m = 0.0125`.)

This constant does NOT change the final rate `Omega(sqrt(m/N))` (the factor
is absorbed into the absolute constant `c`), so the THEOREM is correct. But
the proof sketch states the factor explicitly and it is wrong by 2. **Fix:**
change `(eps/m)` to `(2eps/m)` in the pairwise-TV line, or hedge to
`Theta(eps/m) * d_H`. LOW for the result, MEDIUM for a careful reader of the
headline lower bound's derivation.

### B2. "Le Cam two-point" is really Assouad over a hypercube (MEDIUM, already noted 2026-05-23)

The sketch invokes a `2^(m/2)`-packing `s in {+-1}^(m/2)` and reasons over
all of it. That is **Assouad's lemma** (a hypercube of `2^d` hypotheses),
not Le Cam's **two-point** method (exactly two hypotheses, by definition).
The rate is correct and Devroye-Gyorfi-Lugosi is the right reference for the
construction, but calling it "Le Cam's two-point method" (lines 80, 213,
762, 906, abstract, intro, conclusion) is a terminology error repeated
~6 times. This was flagged in the 2026-05-23 round (their Weakness 2) and is
still open. **Fix:** replace "Le Cam's two-point method" with "Assouad's
lemma" (or "the two-point/Assouad method over a hypercube packing")
everywhere it describes Thm 5.2. This is a real attribution error in the
paper's named headline technique, so it should land before submission.

### B3. Sampling model consistency (OK)

Thm 5.2's model (independent `c_i`, line 888 "Under the sampling model of
Theorem~\ref{thm:comp-leakage}") matches Thm 5.1 exactly. The Remark
"Sampling regimes" (lines 929 to 938) correctly distinguishes the
independent-`c_i` regime (which yields the rate) from the reused-`c` regime
(no additional samples, no rate). Internally consistent.

---

## C. C-9 H* ambiguity, confirmed and slightly worse than reported (MEDIUM)

The consistency report's C-9 says Thm 3.1 uses `H*=n` in the Fannes part and
`log_2|X|` in the `K=1` clause. Confirmed, and the spread is actually
three-way within one theorem plus its definition:

- `def:max-entropy` (line 424): H* is "max entropy subject to constraints";
  "for a single cipher value drawn from a vocabulary of size m, the max
  entropy is `log_2 m`." (vocabulary-m framing)
- Thm 3.1 part (1) (line 482): `H(Q) = H* = n`. (ambient n)
- Thm 3.1 part (2) (line 485): `e <= H(D)/log_2|X|`. (alphabet `log_2|X|`)
- Thm 3.1 part (3) (line 487): `e >= 1 - delta - h_2(delta)/n`. (ambient n)

The spine §4A.1 pins the marginal entropy ratio at `e = H(Q)/n, H* = n`.
**Downstream consequence (the part that matters):** Example 4.1 (line 709)
computes the baseline `e ~ 0.72` using `H* = log_2 10000 = 13.29`, i.e. the
`log_2|X|` convention from part (2), NOT `n`. So the paper's headline numbers
(`e=0.72`, `e=0.87`, `e=0.98` in Table 4) are normalized by `log_2|X|`, while
the Fannes bound `e >= 0.945` (Remark, line 527) is normalized by `n=64`.
These are different normalizers, so the two families of e-values are not on
the same scale, and the paper never says so.

**Fix.** Add one sentence after Thm 3.1 (or in `def:entropy-ratio`)
distinguishing the two normalizers: the **ambient** ratio `H(Q)/n` (used by
the Fannes bound and the spine's M1) and the **effective-alphabet** ratio
`H(Q)/log_2|X|` (used by the `K=1` clause and the worked examples, which
treat the vocabulary as the alphabet). State which the reported e-values use
(it is the effective-alphabet one). This is internal-consistency hygiene; it
does not invalidate any number, but it removes a real "which H*?" stumble.

---

## D. C-10 U vs U_im, verified CORRECT (no action beyond a reminder)

Thm 4.2 (`thm:multiplicity`, line 661) states the bound against `U_im`
(uniform over `Im(enc)`), then explicitly lifts to `U` over `B^n` via the
birthday term (lines 666 to 669: "TV(Q,U) inherits the same bound up to a
birthday-bound term O(sum K / 2^n)"). The two-step IS explicit. Downstream,
the §6.4 newsgroups figure (line 1565) honestly reports `TV(Q, U_im)`, not
`TV(Q,U)`. So no silent conflation. The only residual: the canonical spine
`delta` is against `U` over `B^n`, so headline `delta`/`e` claims that feed
the Fannes bound should reference the lifted (U) bound. Recommend a
half-sentence reminder at the case-study invocation (Table 4) that the
reported `delta` is the U-lifted value. LOW.

---

## Findings summary (severity)

| ID | Finding | Severity |
|---|---|---|
| A1 | FPR formulas over-attributed to cipher-maps §7.4 | HIGH |
| A3 | Orbit bound: entropy-form theorem quoted as set form; denominator `2^n` vs spine `|X|` | HIGH |
| B2 | "Le Cam two-point" is Assouad (terminology, ~6 sites) | MEDIUM |
| A2 | Granularity spectrum table over-attributed to Prop 8.1 | MEDIUM |
| A4 | C-4 Le Cam dual-role footnote absent | MEDIUM |
| C | C-9 H* normalizer ambiguity (ambient n vs alphabet log2|X|) | MEDIUM |
| B1 | Thm 5.2 pairwise-TV constant off by 2 | LOW-MEDIUM |
| D | C-10 handled correctly; one reminder sentence | LOW |

The mathematics is sound throughout; A3 is the only finding that changes a
stated inequality (and in the conservative direction: the fix tightens the
claimed bound). Everything else is attribution/normalization hygiene that a
side-by-side reader of the family would catch.
