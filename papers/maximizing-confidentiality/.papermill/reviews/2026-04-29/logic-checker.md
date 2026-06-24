# Logic Checker Report (round 3, 2026-04-29)

## Scope

Verify that today's two structural changes (contribution-list reorder
and two-scale framing in §1/§5) preserved mathematical content;
confirm rev2 fixes remain intact; assess the new "compositional channel
intrinsic to composability" claim.

## Verification: theorems unchanged in mathematical content

Direct comparison against rev2 source (using prior-round reports as
oracle):

| Theorem | Status | Notes |
|---|---|---|
| Thm 3.1 (entropy decomposition / Fannes bridge) | **Unchanged** | Linear bound `e >= 1 - delta - h_2(delta)/n` preserved at lines 442-449; proof at 462-480; Pinsker clarifying remark at 477-479. |
| Numerical Scale remark | **Unchanged** | n=64 with context "typical width for the hash output of a cipher map" (line 483); values e >= 0.945 / 0.989 verified by direct calculation. |
| Thm 4.1 (noise dilution) | **Unchanged** | Mixture entropy formula at line 532; Fisher-info `rho^2` claim at line 567 still missing distribution-dependent constant (M2 carry-over from rev2). |
| Thm 4.2 (multiplicity) | **Unchanged** | `K(x) propto D(x)` with `K(x) = ceil(c*D(x))` preserved (line 597); TV bound derivation that was added in rev2 (n4) preserved at 626-629. |
| Thm 5.1 (compositional leakage) | **Unchanged** | All four parts intact; sampling-regime remark intact (line 816); MI fragility sentence "marginally independent of the latent pair" intact at line 801. |
| Prop 5.2 (FPR compounding) | **Unchanged** | At lines 878-888. |
| Prop 6.1 (compression estimator) | **Unchanged** | Carry-over m6 still open. |

The two structural changes (paragraph-reorganization in §1 and §5
opener / title rewrite) did not alter any equation, theorem statement,
or proof. Equation numbering and theorem reference numbers (`thm:comp-leakage`,
`thm:entropy-decomposition`, `thm:noise-dilution`, `thm:multiplicity`,
`thm:fpr-compounding`, `prop:granularity`, `prop:compression`) are
identical.

## Numerical verification (independent recomputation)

| Claim | Paper value | Verified value | Status |
|---|---|---|---|
| Fannes bound, delta=0.05, n=64 | e >= 0.945 | 0.9455 | OK |
| Fannes bound, delta=0.01, n=64 | e >= 0.989 | 0.9887 | OK |
| Zipf s=1, m=10000, H_m | 9.788 | 9.7876 | OK |
| Zipf s=1, m=10000, H(D) | 9.55 | 9.5323 | OK |
| Baseline e | 0.72 | 0.7174 | OK |
| Example 4.1 H(Q) after homophonic | 11.5 | 11.5779 | OK (paper hedges with ~) |
| Example 4.1 e after homophonic | 0.87 | 0.8713 | OK |
| Sum K_top (top-100 cells) | ~519 | 576 with ceiling, 518.7 with exact | OK (paper text uses "approximately") |

Sub-bullet on the sum-K discrepancy: with the literal `ceil(c*D(x))`
prescription, `sum_K = 576`. The paper's "~519" is the integral
approximation (`100 * H_100`), which would be exact without the ceiling.
The discrepancy is ~11% but the paper's verbal "approximately" hedge
covers it. Carry-over minor, not new.

## Assessment of "compositional channel intrinsic to composability" claim

Quoted text (line 155-158):
> "The compositional channel is intrinsic to the framework's
> composability, not a bug: the same property that lets the untrusted
> machine chain evaluations blindly is the property that creates the
> channel."

This is a structural argument. To assess it:

1. **Is it logically sound?** Composability (Property 4 of cipher
   maps) means `g_hat o f_hat` is again a cipher map for `g o f`. For
   composition to function correctly, `f_hat(c)` must be a *valid
   cipher value* of the right type for `g_hat`. That means the
   downstream untrusted operation can take an upstream output as input
   with no decoding step. This is exactly what enables the
   untrusted-side observation `(f_hat_1(c), f_hat_2(c))` for the same
   `c`: the same `c` is reusable as input.

2. **Is it tight?** A reader could push back: "But Thm 5.1 doesn't
   require composability; it just requires two cipher maps applied to
   the same input." That's a fair semantic clarification. The channel
   is created by *value reuse*, not by *function composition*. If a
   cipher map system forbade reusing cipher values across evaluations
   (e.g., by re-encoding after every operation), the channel would
   close.

3. **However**, in cipher-map systems the *whole point* of cipher
   values being a stable encoded representation is that they survive
   operations. Re-encoding after every operation breaks composability
   in the practical sense (the untrusted machine cannot chain
   operations without trusted-machine intervention). So the structural
   argument is: cipher value persistence (which is what enables
   composability) IS what enables shared-c observation. The argument
   holds at this granularity.

**Verdict**: The claim is defensible but slightly loose. A more
precise statement would distinguish:

- Composability (chaining) requires cipher values to survive operations.
- Shared-c observation requires cipher values to be reused across
  observations.
- These are the same structural property: *value persistence under
  the cipher map framework*.

I do not flag this as a finding; the current paragraph reads as
informal motivation, not a theorem statement. A logic-checker who
reads the paper as a competing reviewer might write a comment "the
'intrinsic' claim could be sharpened" but would not block on it.

## Findings (this round)

### New issues introduced today: NONE

The two structural changes are pure expository re-routing. No
equations or theorem statements were altered. No new mathematical
content was introduced beyond the framing prose.

### Carry-over open items

- **M2 (carry-over)**: Thm 4.1 Fisher info `rho^2` missing
  distribution-dependent constant. Unchanged. Severity: Major.
- **m1 (carry-over)**: `Q` notation overloaded with KL convention.
- **m6 (carry-over)**: Compression estimator proof terse.
- **Minor 5 (rev2)**: Resolved (the "marginally independent" sentence
  is in place at line 801).

### Self-check

I read the §1 framing twice in sequence to test whether the inserted
"two scales" paragraph (lines 95-105) breaks the prior flow:

- Line 78-93: Sets up the question (cipher map + parameters,
  qualitative vs. quantitative).
- Line 95-105 (NEW): Names the marginal/compositional decomposition
  as the spine.
- Line 107 (`\paragraph{Marginal scale.}`): Walks into the entropy
  ratio measure.
- Line 147 (`\paragraph{Compositional scale.}`): Walks into Thm 5.1.
- Line 172 (`\paragraph{Contributions.}`): Lists numbered
  contributions, with Thm 5.1 first.

The flow is internally coherent. The reader is set up for a
two-pronged structure and the contributions list confirms it. From a
logic-checking standpoint, the framing edits do not introduce
mathematical inconsistency.

## Summary

The paper's mathematical content is unchanged from rev2. All theorems,
proofs, numerical examples, and remarks are preserved. The two
structural changes (paragraph re-routing in §1, §5 retitling and
opener rewrite) are purely expositional and do not affect mathematical
correctness. The "intrinsic to composability" claim is defensible.

The carry-over open items (M2 Fisher info constant; m1 Q-notation; m6
compression proof terseness) remain at their rev2 severities.

**Recommendation from logic-checker**: ready (mathematics is sound;
no blocking logic issues).
