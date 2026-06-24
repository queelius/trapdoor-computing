# Logic Checker Report, Round 9 (2026-06-02)

**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations
**Focus this round**: (1) new Proposition prop:homophonic correctness and
self-containment; (2) K(x) proportional to D(x) direction consistency;
(3) regressions from the d_TV-inline / removed-deferral / codec-inventory
edits; (4) aggressive direction/inequality/constant sweep.

All findings below were verified against the manuscript text and, where
arithmetic is involved, against independent numerical computation.

---

## Summary

The recent homophonic-allocation arc is **mathematically sound and
self-contained**. Proposition prop:homophonic states a correct exact
identity and a correct hypothesis-free bound, with a clean proof that
depends on nothing external (no maxconf, no unproven general-n result).
The K(x) proportional to D(x) direction is correct at all sites and D, K
are defined before first use. No regressions from the d_TV / deferral /
codec-inventory edits.

The aggressive direction sweep surfaced **one new major finding**: the
Zipf skew parameter is mislabeled as s = 1 at two sites (section 8.3
numerical illustration and section 10.6 Setup), but the paper's own
numbers (max alpha = 0.5, attacker accuracy 0.984, 132x ratio) require
s = 1.2, which is what the source experiment actually uses. A literal
Huffman code on Zipf(s=1) over |Y|=8 gives max alpha = 0.25 and does not
reproduce the headline illustration. This is a parameter/constant
mislabel of the same family as the three direction errors the user has
caught in prior rounds. The fix is a one-character edit at two sites.

Two minor notation findings (undefined kappa(y); n-vs-M bit-width).

**Counts**: Critical 0 | Major 1 | Minor 3 | Suggestions 1.

---

## Proposition prop:homophonic (the round's centerpiece): PASS

**Location**: lines 535-575.

**Statement**: For injective enc with image of size N = sum_x K(x) and
normalized allocation A(x) = K(x)/N,
  TV(Q, Uniform(im enc)) = (1/2) sum_x |D(x) - K(x)/N| = TV(D, A),
and for the Simmons allocation K(x) = ceil(c D(x)),
  TV(Q, Uniform(im enc)) <= |X|/N, vanishing as the budget c (hence N) grows.

### Exact identity: CORRECT

Verified by independent computation across 6 random (X, D, c) configs:
in every case (1/2) sum over cipher values |Q(c) - 1/N| equals
(1/2) sum_x |D(x) - K(x)/N| equals TV(D, A) to machine precision. The
proof's group-by-group collapse is right: for c = enc(x,k), Q(c) =
D(x)/K(x), there are K(x) such cipher values per x, and
K(x) |D(x)/K(x) - 1/N| = |D(x) - K(x)/N|. Halving gives the TV. The
second equality is the definition of TV(D, A), valid because
sum_x A(x) = N/N = 1 (the proof correctly notes this normalization).

### Simmons bound TV < |X|/N: CORRECT

Verified numerically (same 6 configs): TV(Q, Uniform(im)) <= |X|/N holds
in every case. The proof writes K(x) = c D(x) + r(x) with rounding excess
r(x) in [0,1), N = c + R where R = sum_x r(x) < |X|, and
K(x)/N - D(x) = (r(x) - R D(x))/N. The triangle inequality then gives
  TV = (1/(2N)) sum_x |r(x) - R D(x)|
     <= (1/(2N)) (sum_x r(x) + R sum_x D(x))
      = R/N < |X|/N.
The arithmetic is right. The factor-of-2 handling is correct (the 1/(2N)
prefactor cancels into the final R/N because sum r(x) + R = R + R = 2R).

### Self-containment: CONFIRMED

The proof uses only: injectivity of enc, the definition of Q, the
definition of TV, and the triangle inequality. It does **not** invoke
maxconf, does **not** invoke any unproven general-n |X|/(2N) result, and
does **not** depend on the c >= 1/min D hypothesis that the maxconf
tighter bound needs. It stands entirely on the exact identity plus a
triangle bound. This is exactly the bulletproof, hypothesis-free posture
the user asked for. The removed deferral sentence (commit c9e830b) was
the right call: the paper now claims only what it proves.

### Target-distribution correctness (within-image vs full-space): CORRECT

The proposition targets Uniform(im enc) (within the image), while
Definition 4.2's delta targets Uniform({0,1}^n) (full ambient space).
The prose immediately after the proof (lines 577-581) makes this
distinction cleanly: "The proposition bounds the gap to uniformity within
the image im(enc); the residual gap to Uniform({0,1}^n) in Definition 4.2
is the noise region outside the image, populated by totality (Property 1)
and noise injection." This is correct and is the right way to bridge the
two notions. No overclaim.

### One nuance worth a footnote (not a defect)

The proof's substitution K(x) = c D(x) + r(x) with r(x) in [0,1) is exact
for K(x) = ceil(c D(x)) **as long as c D(x) is not an integer**; when
c D(x) is a positive integer, ceil gives r(x) = 0, still in [0,1), so the
bound holds. The only edge case is rare values with c D(x) < 1: ceil
gives K(x) = 1 and r(x) = 1 - c D(x) in (0,1), again fine. The bound is
robust to the floor-at-1 that any practical allocation imposes. No change
needed; mentioning the integer edge case would be a courtesy but is not
required for correctness.

---

## K(x) proportional to D(x) direction: PASS (all sites correct)

Verified every occurrence of the K-D relationship:

| Line | Context | Direction |
|---|---|---|
| 323 | Related Work, Homophonic substitution | K(x) propto D(x): "assigns more representations to frequent values" CORRECT |
| 457 | Layer 3, Multiple representations | K(x) propto D(x): "equalizes frequencies" CORRECT |
| 526 | After Definition 4.2 | K(x) propto D(x): "frequent values get more representations" CORRECT |
| 700 | Table tab:params, K(x) row | "Set to propto D(x)" CORRECT |
| 547 | Proposition Simmons allocation | K(x) = ceil(c D(x)) CORRECT |

The operational justification is right in every case: with K(x) propto
D(x), the per-representation query frequency D(x)/K(x) is constant across
x, so Q is flat. This is the correct direction (heavy values need MORE
representations to spread their mass). The R7-era inversion (K propto
1/D) is fully gone.

**D and K defined before first use**: D(x) ("prior probability that the
trusted machine encodes latent value x") and K(x) ("number of cipher
representations assigned to x") are both introduced at lines 318-320 in
the Related Work homophonic-substitution paragraph, which is the first
substantive use. They are formally (re)defined in Definition 4.2
(lines 502-504: "D : X -> [0,1] the prior probability distribution ...
the query distribution"). Definition precedes formal dependence. PASS.

---

## Regression check on recent edits: PASS

### d_TV inline definition (commit e52e7a8): clean

Definition 4.2 (lines 515-520) now defines TV with both forms:
(1/2) sum_c |P(c) - Q(c)| and sup_A |P(A) - Q(A)|. Both are standard and
correct. The \TV macro (d_{TV}) is used consistently throughout
(lines 513, 543, 825, 918, 919, 1639, ...). No dangling or
double-definition. The Proposition reuses \TV with the same meaning.

### Removed deferral sentence (commit c9e830b): clean

Confirmed no residual "Tighter constants" / "additional budget
hypotheses" / "developed in the companion entropy-ratio work" text
anywhere in the manuscript. The prose flows directly from the proof to
the within-image/full-space clarification remark. No dangling reference
to a now-absent claim.

### Section 10.6 codec-inventory fix (commit 9b60c2b): clean

The Setup paragraph (lines 2606-2628) now enumerates each sweep's codec
set separately and explicitly flags that "specific codec sets differ per
analysis paragraph below." Le Cam study: 5 codecs at n in {4,5}. E3:
a different 5-codec set. E4: Huffman n in {4..8} plus Dense(n=3). This
resolves R8 MAJ-2 cleanly; no reader-reconciliation gap remains.

### E4 H1 wording fix (commit 9b60c2b): clean

Line 2754-2757 now reads "within 0.02 across all 15 Huffman cells (13 of
15 within 0.01; two Huffman(M=5) cells at t in {2,3} have gaps 0.010 and
0.016 respectively; mean absolute gap 0.004)." Matches the E4 CSV.
Resolves R8 MAJ-3.

---

## Other proof-bearing results re-verified (all PASS)

| Result | Location | Check | Verdict |
|---|---|---|---|
| Composition correctness (Thm 4.1 / Thm 7.1) | 660-672, 1535-1576 | eta <= 1-(1-eta_f)(1-eta_g), equality under re-randomization | PASS. The `<=` ... `=` form is the bound followed by its algebraic equivalent; "equality under re-randomization" clause disambiguates. Consistent across abstract (79), both theorems, Corollary 7.1 (1596), Discussion (2127). The R6-era `=`/`<=` inconsistency is fully resolved. |
| AND-gate correctness table | 1481-1506 | Four cases by exact enumeration | PASS. All four match (p1 p2; 1-p1(1-p2); 1-p2(1-p1); p1+p2-p1 p2). |
| Chain composition | 1592-1616 | Induction on Thm 7.1 | PASS. |
| Lower bound | 949-998 | -log2(eps)+H(Y); membership + value additive via chain rule | PASS. Stirling drop of 1.44n term correctly flagged as matched asymptotically by achievability. |
| Space optimality (Thm 6.2) | 1186-1236 | (1-eta)(-log2 eps + mu); storage vs search-time separated | PASS. R6 MAJ-3 separation (storage cost vs seed-trial cost) is present and correct (Remark rem:physical-storage reinforces). |
| Per-seed success / bucketing | 1259-1327 | Poisson-binomial, geometric-mean alpha | PASS. |
| Confidentiality bound (Prop 5.1) | 808-836 | e >= 1 - delta - h2(delta)/n via Fannes-Audenaert | PASS direction. Verified H(Q) >= n(1-delta) - h2(delta) is a valid lower bound across random Q. Proof sketch defers full derivation to maxconf Theorem 4.1 part 3 (the load-bearing forward reference; see MAJ-1 below). |
| Coincidence-oracle accuracy (Thm 8.1) | 1814-1883 | 1 - half sum_y prod_i alpha_i(y); members/filler/combine | PASS. Member case Pr=1, filler case sum prod alpha, balanced-prior combine all correct. |
| cor:t-geometry direction | 1921-1931 | uniform maximizes attacker accuracy (worst), concentrated minimizes (best) | PASS. Verified numerically: at |Y|=8, t in {2,3,5}, uniform_acc > huffman_acc > concentrated_acc. R7 CRIT-1 inversion fully closed. |
| Randomized-encoding defense (Prop 8.2) | 1994-2060 | pattern-coincidence prod 1/|A_i(y)|; decode-coincidence invariant | PASS direction. Larger |A(y)| -> lower member-coincidence -> better defense (line 2017). Saturation hypothesis still stated informally (see LOG-MIN-2). |
| Bayesian deniability (Prop 10.x) | 2542-2560 | pi(1-eta)/(pi(1-eta)+(1-pi)eta) | PASS. posterior=1 at eta=0, posterior=pi at eta=1/2. Matches Warner. |

---

## MAJOR FINDING

### LOG-MAJ-1 (NEW): Zipf skew mislabeled s = 1; should be s = 1.2

**Severity**: Major.
**Source**: logic-checker (direction/constant sweep).
**Locations**:
- Line 1934-1937 (section 8.3, "Numerical illustration"):
  "For |Y| = 8 with a Zipf p_y (skew parameter s = 1), the
  Shannon-optimal Huffman partition gives max_y alpha(y) approx 0.5
  (the dominant value claims half the codespace), while uniform gives
  max_y alpha(y) = 1/8 = 0.125."
- Line 2609 (section 10.6, Setup): "latent value distribution p_y Zipf
  with skew s = 1."

**Problem**: The stated parameter s = 1 is inconsistent with the paper's
own numbers and with the source experiment. Verified by independent
Huffman construction:

- Literal Huffman on Zipf(s=1) over |Y|=8: p[0] = 0.368, codeword
  lengths [2,2,3,3,4,4,4,4], so **max alpha = 2^-2 = 0.25**, not 0.5.
  At t = 5 this gives attacker accuracy approx 0.999 (error 1.2e-3), not
  0.984. The "132x better defense" illustration does NOT reproduce from
  s = 1.
- The source experiment (bernoulli .../14_coincidence_oracle.py, line 77)
  uses raw[i] = 1/(i+1)^1.2, i.e. **Zipf s = 1.2**. This gives
  p[0] = 0.4286, Huffman lengths [1,3,3,4,4,4,5,5], **max alpha = 0.5**,
  sum alpha^5 = 0.0313, attacker accuracy = **0.9843**. These are exactly
  the paper's numbers, and the E3 CSV confirms max_q = 0.5 for the
  Huffman(M=4,p_f) codec.

So the numbers (0.5, 0.984, 132x) are correct and validated against the
CSV; only the **stated skew parameter is wrong** (s=1 written where the
experiment and the numbers require s=1.2). A PoPETs reviewer who
recomputes Huffman(Zipf(8, s=1)) gets max alpha = 0.25 and concludes the
headline illustration is wrong, when in fact only the label is wrong.

This is precisely the class of constant/parameter mislabel the user has
caught three times before (the K(x) direction, the CRIT-1 inversion, the
K(x) prescription). It was NOT caught in R8: R8's logic-checker verified
the *ratio* (132) against the formula but did not reconstruct the Huffman
code from the stated s=1, so the mislabel slipped through.

**Suggestion**: Change "skew parameter s = 1" to "skew parameter s = 1.2"
at both line 1934 and line 2609. All numbers stay correct. Optionally add
a parenthetical at line 1936 noting the dominant value receives a
length-1 codeword under this skew. (Zero risk: the numbers are already
validated against the CSV; only the parameter label changes.)

**Cross-verification**: Confirmed against (a) independent Huffman
construction on both s=1 and s=1.2, (b) the source experiment file
f_distribution() at line 77 using exponent 1.2, (c) the E3 results.csv
max_q column showing 0.5 for Huffman(M=4,p_f) and 0.9843568 predicted
accuracy at t=5. All three agree: the distribution is s=1.2.

---

## MINOR FINDINGS

### LOG-MIN-1 (NEW): kappa(y) undefined in section 8.3 honest-limitations list

**Location**: lines 2098-2101.
"The defense incurs space cost only when kappa(y) > 1 ... The Dense
partition ... has kappa(y) = 1 for all y."

**Problem**: kappa(y) is used nowhere else; the paper's multiplicity
symbol is K(x) (and K(y) appears once at line 2767). kappa(y) is
undefined. The reader must guess it means the per-value multiplicity or
the codespace-class size. This is a notation slip, not a logic error.

**Suggestion**: Replace kappa(y) with K(y) (or define it as the
per-value codespace-class size if that is the intended meaning). One-line
fix.

### LOG-MIN-2: Proposition 8.2 saturation hypothesis still informal (carry-over R7 MAJ-2, R8 LOG-MAJ-4)

**Location**: lines 1999-2006.
The "saturates" assumption ("every bit string in A_i(y) is reachable as
fhat_i(c) for some member cipher value c encoding a value-y plaintext")
is the bijectivity/surjectivity condition the proof needs, but it is
stated inline rather than as a named definition. The proof is correct
GIVEN saturation; the issue is precision of statement, not soundness.

**Suggestion**: Promote to a one-line Definition (Encoder saturation) and
reference it from the proposition hypothesis. Carry-over; non-blocking.

### LOG-MIN-3 (NEW): n vs M bit-width notation unreconciled in section 10.6

**Location**: Le Cam study uses n (lines 2612-2614, "n in {4,5}");
E3/E4 use M (lines 2618-2620, 2748-2781, "Dense(M=3)", "2^{M - l_y}").
Line 2005 writes the codespace class size as 2^{n - l_{f(x)}} (using n),
while line 2748 writes the same quantity as 2^{M - l_y} (using M).

**Problem**: M is never defined; the reader must infer M = n = cipher
value space bit-width. Same physical quantity, two symbols.

**Suggestion**: Standardize on n throughout, or add a one-line note in
the section 10.6 Setup that M denotes the codec bit-width (= n). Minor.

---

## SUGGESTION

### LOG-SUG-1: Direction/parameter-summary table (carry-over R8 LOG-SUG-1, now reinforced)

The user has now caught (or this review has caught) FOUR
direction/parameter errors over the revision cycle (K direction, CRIT-1
inversion, K prescription, and now the s=1/s=1.2 mislabel). A small table
codifying, for each prescription, "which direction means better defense"
and "which distribution parameter produces which max alpha" would make
this class of error visible at edit time. The s=1.2 mislabel in
particular would have been caught immediately by a table row pairing the
distribution with its resulting max alpha. Recommend placing it near the
section 8.3 numerical illustration or section 5.2.

---

## Cross-checks performed

1. Homophonic identity + Simmons bound: 6 independent numerical configs.
2. K(x)-D(x) direction: all 5 sites read against operational justification.
3. cor:t-geometry direction: numerical (uniform vs Huffman vs concentrated
   at t in {2,3,5}).
4. AND-gate table: exact enumeration of all 4 cases.
5. Bayesian deniability: boundary cases eta=0 and eta=1/2.
6. Fannes-Audenaert direction: random Q, confirmed lower bound holds.
7. Zipf s=1 vs s=1.2: independent Huffman construction + source file
   inspection + E3 CSV max_q column. Triple-confirmed.
8. Composition formula `<=`/`=` across all 5 sites.
9. d_TV / deferral / codec-inventory regression scan.
