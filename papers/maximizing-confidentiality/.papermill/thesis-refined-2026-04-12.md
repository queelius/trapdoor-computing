# Thesis Refinement: The Entropy Ratio, Quantitative Confidentiality for Trapdoor Computing

Date: 2026-04-12 (revised same day after multi-agent review)
Paper state: draft-complete (17pp after critical-error fixes)

## 2026-04-12 revision log (review-triggered fixes)

The multi-agent review (`.papermill/reviews/2026-04-12/review.md`) found
two critical mathematical errors in headline contributions. Both have
been fixed:

### Fix 1: Pinsker -> Fannes-Audenaert (C1)

The Thm 3.1 pt 3 proof invoked Pinsker in the wrong direction:
Pinsker gives `D_KL >= 2*d_TV^2`, a lower bound on KL from TV; the
paper used it as an upper bound on KL from TV, which does not follow.
Counterexample: `Q = (1-delta)U + delta*1_{c_0}` has `d_TV ~ delta` but
`D_KL ~ delta*n`.

Replaced with the Fannes-Audenaert continuity inequality, yielding
the correct linear bound `e >= 1 - delta - h_2(delta)/n`. For
`delta=0.05, n=64`, the correct bound gives `e >= 0.945`; the original
bogus bound gave `e >= 0.99992`. Gap is material for a paper whose
thesis is quantitative measurement.

Renamed "Pinsker bridge" -> "Fannes bridge" throughout (abstract,
intro, Related Work, contributions list, conclusion).

### Fix 2: K(x) direction inverted (C2)

The paper had `K(x) ~ 1/D(x)` ("more representations for rare
elements"), which under the paper's own sampling model `Q(v) =
D(x)/K(x)` concentrates mass rather than flattening it. Classical
homophonic substitution (Simmons 1979) is `K(x) ~ D(x)`: frequent
elements get more code symbols so per-symbol frequency equalizes.

Corrected Thm 4.2 statement, proof, Example 5, Table 4, Intro bullet,
Contributions list, and Conclusion. Also corrected the algebra error
in the proof: `D(x) / (c/D(x)) = D(x)^2/c`, not `c`.

### Numerical updates (M1)

Zipf s=1, m=10000: H(D) = 9.55 bits (was incorrectly 7.83), baseline
e = 0.72 (was 0.59).

With correct `K(x) ~ D(x)` homophonic on top 100: total cells
Sum K(x) ~ c = 100*H_m ~ 979. Space overhead 1.04x (was 1.52x based on
broken construction). Combined confidentiality 0.72 -> 0.98 (was 0.59
-> 0.85).

The corrected construction is strictly better than the broken one:
less space overhead, more confidentiality. The paper's story
strengthens with the fix.

### Minor fixes landed

- Simmons 1979 now `\cite{}`d at Section 4.2 opening (M6).
- Thm 5.1 pt (2) rewritten as mutual-information preservation
  `I(fhat_1(C); fhat_2(C)) = I(f_1(X); f_2(X))` (M4).
- Thm 5.1 pt (3) now specifies i.i.d. in-domain sampling regime (M3).
- Thm 5.1 pt (4) now gives a quantitative bound on achievable
  delta_3 rather than a tautology (M5 partial).
- Abstract and Conclusion no longer say "three levers"; they reflect
  the two-plus-inherited framing consistent with Section 1 (M8).
- Added a numerical-scale remark after Thm 3.1 for the Fannes bound.

### Bib additions

- `fannes1973continuity`: Fannes' original 1973 continuity result.
- `audenaert2007sharp`: Audenaert's 2007 sharp version.

## Baseline refinement (2026-04-12 morning)

## Refined Thesis (accepted 2026-04-12)

**Claim.** In the cipher map framework, representation uniformity (δ)
controls Shannon leakage via Pinsker, giving `e ≥ 1 − 2δ²/n`. Two
constructions reduce δ with explicit costs. Noise injection costs
bandwidth `1 + R/N` and dilutes Fisher information by `ρ²`. Multiple
representations cost space `Σ K(x)` with `K(x) ∝ 1/D(x)`. We prove a
compositional bound showing that marginal δ-uniformity is insufficient
when shared variables recur across evaluations.

**Novelty.** (1) The Pinsker bridge making δ the operational handle
for information-theoretic confidentiality in cipher maps. (2) The
compositional leakage proposition: `O(1/ξ²)` observations suffice to
recover shared-variable joint distributions to TV-accuracy ξ even when
marginals are δ-uniform. The entropy ratio is standard QIF; the
constructions (noise, homophonic) are classical; the novelty is the
*bridge* and the *compositional bound*.

## What changed from the 2026-04-01 thesis

The previous thesis claimed:

> Confidentiality can be measured as `e = H/H*` and systematically
> improved via **three levers** (noise injection, multiple
> representations, encoding granularity) expressible in terms of the
> four cipher map parameters.

That framing had three problems identified in this session:

1. **`e = H/H*` is not novel.** It is normalized Shannon leakage from
   the QIF literature (Smith 2009; Alvim et al. 2020). Leading with
   the measure lets a reviewer dismiss the paper as a rediscovery.
2. **"Three levers" over-credits this paper.** Granularity is *cited*
   from the cipher-maps companion paper (`[towell2026cipher, Prop.
   9.1]`), not proven here. Calling it a lever of this paper inflates
   the contribution.
3. **FPR compounding is also cited**, not proven. The paper's
   compositional novelty is not FPR compounding but the correlation
   leakage from shared variables (Prop. 5.2).

The refined thesis fixes all three:
- Acknowledges `e` as QIF-standard.
- Claims only two constructions (noise, multiplicity) as this paper's.
- Elevates the compositional bound from a late proposition to a
  headline contribution.

## Contribution audit (proven here vs. cited)

| Result | Statement | Status | Severity |
|---|---|---|---|
| Thm 3.1 part 3 | `e ≥ 1 − 2δ²/n` via Pinsker | **Proven here** | Headline |
| Thm 3.1 parts 1, 2 | `δ=0 ⟹ e=1`; `K=1 ⟹ e ≤ H(D)/log|X|` | Proven here | Framing |
| Thm 4.1 | Noise dilution, Fisher info `ρ²` | **Proven here** | Headline |
| Thm 4.2 | `K(x) ∝ 1/D(x)` construction for δ → 0 | **Proven here** | Headline |
| Prop 4.3 (Granularity spectrum) | Joint vs component-wise encoding | **Cited** from `[towell2026cipher, Prop. 9.1]` | Inherited |
| Thm 5.1 (FPR compounding) | `p_T^k` for AND, `1−(1−p_T)^k` for OR | **Cited** from `[towell2026cipher, Sec. 8]` | Inherited |
| Prop 5.2 (Correlation leakage) | Shared variables leak joint under δ-uniform marginals | **Proven here** | Headline (under-promoted) |
| Prop 6.1 (Compression estimator) | `H(Q) = lim (1/m) E[|C(sequence)|]` | Textbook (Shannon) | Methodological |

## Implications for the paper (pending user approval)

### Accepted this session

1. **Promote Prop 5.2 to Theorem** and move it earlier in Section 5, ahead of the cited FPR compounding result. The paper's compositional story is "δ-uniformity is necessary but insufficient", and that tension should open Section 5, not close it.

2. **Make inheritance explicit in the Introduction.** The three-lever paragraph should read something like:

    > We analyze two constructions that reduce δ, noise injection
    > and multiple representations, and inherit a third (encoding
    > granularity) from the cipher maps framework
    > [towell2026cipher, Sec. 9], which we use but do not re-prove.

3. **Tighten the Related Work QIF paragraph.** State explicitly: the
   entropy ratio itself is Shannon leakage normalized; the
   contribution is the Pinsker bridge δ → e and the compositional
   bound, not the measure.

### Not yet decided (needs follow-up)

- Should the paper include a min-entropy companion bound? The
  novelty-assessor flagged that Shannon entropy misses worst-case
  leakage. A one-paragraph min-entropy remark is cheap; a full bound
  would require work.
- Venue: "theory venue (15-20 pages)" in state.md is still a
  placeholder. With the sharpened thesis, candidates are
  TCC, CSF (Computer Security Foundations), or the QIF workshop.
  Decision deferred to a `/papermill:venue` run.

## Socratic record

### Q1: Is `e = H/H*` your novelty?
**A:** No. It's QIF-standard (Smith 2009; Alvim et al. 2020). The
paper should say so.

### Q2: Is the granularity spectrum your contribution?
**A:** No. It's from `[towell2026cipher, Prop. 9.1]` and cited as
such. Removing it from the "three levers" framing is more honest.

### Q3: What's left that's genuinely novel here?
**A:** The Pinsker bridge (δ → e) and the compositional leakage
bound. That's the thesis.

### Q4: Is Prop 5.2 strong enough to carry headline weight?
**A:** Yes. It articulates the tension that δ-uniform marginals
don't prevent joint recovery from shared variables, which is the
reason practitioners can't stop at multiplicity. It deserves theorem
status and earlier placement.

### Q5: What does this do to the paper's length?
**A:** No change to length. Reframing Intro, elevating a proposition,
and adding one sentence about inheritance. The 13-page body is
preserved.

## Next actions

1. Update `state.md` thesis block (this session).
2. Update Introduction to reflect two-lever plus inherited-third framing
   (separate commit).
3. Promote Prop 5.2 to Thm 5.0, reorder Section 5 (separate commit).
4. Tighten Related Work QIF paragraph (separate commit).
5. Consider min-entropy remark for Discussion section (open).
6. Run `/papermill:venue` with the refined thesis (open).
