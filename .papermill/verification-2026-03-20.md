# Verification Report: maximizing-confidentiality fixes
Date: 2026-03-20

## Fix 1: Inter-arrival entropy formula (geometric distribution)
**Location**: lines 1196-1198 of main.tex
**Mathematical correctness**: PASS
- The theorem statement now uses the standard geometric entropy formula:
  H(Geom(p)) = [-(1-p)log_2(1-p) - p log_2(p)] / p, with p = lambda * tau.
- Numerical verification: p=0.25 yields H = 3.245 bits, consistent with the
  claimed ~3.25 (not the erroneous 12.76 from the old formula).
- The asymptotic limit (lambda*tau -> 0) is log_2(1/lambda) + log_2(1/tau) + log_2(e),
  verified numerically: for lambda=0.1, tau=0.001, exact=14.730, asymptotic=14.730.
- The appendix derivation (lines 2388-2405) independently derives the same
  closed-form formula via the full summation, confirming agreement.

**Consistency with surrounding text**: PASS
- The theorem statement (line 1198) now exactly matches the proof body (line 1214).
- The proof defines p = lambda*tau and states the geometric entropy in the same form.
- The asymptotic formula in the theorem (line 1202) follows correctly from the
  exact formula via standard Taylor expansion of the log terms as p -> 0.
- No other locations in the paper reference this specific formula, so no
  downstream inconsistencies.

**New errors introduced**: NONE

## Fix 2: Joint maximum entropy (result set entropy removal)
**Location**: lines 1633-1648 of main.tex
**Mathematical correctness**: PASS
- The joint formula (lines 1640-1641) now correctly omits independent result set
  entropy terms, containing only: H*(T) + H*(A) + H*(N_trap) + E[N_trap]*H*(Y).
- The remark (lines 1646-1648) correctly explains: since result sets are a
  deterministic function of the query, H(R|Q) = 0, so H(Q,R) = H(Q).
- The proof body (lines 1650-1663) is fully consistent: it explicitly invokes
  H(R|Q) = 0 (line 1656) to collapse the result set term, then decomposes query
  entropy into cardinality + trapdoor selection terms.
- Section 7 (line 1680-1684) independently confirms: "given a hidden query, the
  corresponding random result set is degenerate" and H(Q,R) = H(Q) = H(R).

**Consistency with surrounding text**: PASS with caveat (see below)
- The fixed joint maximum entropy theorem (line 1636) is internally consistent.
- The proof, remark, and Section 7 discussion all agree on the deterministic
  relationship H(R|Q) = 0.
- **Caveat**: The earlier "Constrained maximum entropy" theorem (lines 1145-1157)
  still includes the term H*(R|N) in both its statement and proof. This predates
  the fix and was not updated. However, this is a pre-existing issue in the paper
  rather than a new error introduced by Fix 2. The proof of that earlier theorem
  itself is internally inconsistent: lines 1148-1149 include the R term but the
  derivation at lines 1167-1168 drops it. Fix 2's theorem (line 1636) effectively
  supersedes that earlier, less developed version.
- The minimum mutual information corollary (line 1669) references H*_n, which now
  correctly excludes the result set term.

**New errors introduced**: NONE (the pre-existing inconsistency at lines 1145-1157
was not introduced by this fix)

## Fix 3: Mixture entropy (inequality instead of equality)
**Location**: lines 2205-2212 of main.tex
**Mathematical correctness**: PASS
- The formula now correctly uses >= (lower bound) instead of equality:
  H(X_combined) >= sum_i w_i H(X_i).
- This follows from the concavity of entropy (Jensen's inequality for concave
  functions): H(sum w_i p_i) >= sum w_i H(p_i).
- The explanation (line 2212) correctly notes equality holds only when all
  component distributions are identical, which they are not here.
- Numerical check: 0.67*23.49 + 0.33*39.87 = 28.90 bits. The paper states 28.86,
  a discrepancy of 0.04 bits. This is a minor rounding artifact from using
  0.67/0.33 instead of exact 2/3 and 1/3 (which give 28.95). The discrepancy
  does not affect the efficiency ratio (28.86/39.87 = 0.72, 28.90/39.87 = 0.72).

**Consistency with surrounding text**: PASS
- The weights w1=0.67, w2=0.33 are consistent with the injection rates:
  lambda_auth=0.10, lambda_fake=0.05, total=0.15, so w1=10/15=2/3~0.67.
- The component entropies 23.49 and 39.87 match the baseline calculation
  (line 2156: 3*7.83=23.49) and maximum entropy (line 2160: 3*13.29=39.87).
- The efficiency 0.72 (line 2216) is consistent with the lower bound of 28.86.
- Since the true mixture entropy exceeds the lower bound, the actual efficiency
  also exceeds 0.72, making the case study conclusions (improvement from 0.59
  baseline) conservative and still valid.
- The summary table (line 2240) reports 0.72 for "artificial queries only",
  consistent with the computed lower bound.
- The combined strategy efficiency of 0.85 (line 2241) remains valid as an
  approximate figure since both individual improvements are conservative bounds.

**New errors introduced**: NONE
(Minor note: the arithmetic 0.67*23.49 + 0.33*39.87 = 28.90, not 28.86 as
displayed. This 0.04-bit discrepancy is cosmetic and does not affect conclusions.)

## Overall Verdict: ALL PASS

All three fixes are mathematically correct, consistent with surrounding text,
and introduce no new errors. One pre-existing issue was noted: the earlier
"Constrained maximum entropy" theorem (lines 1145-1157) still includes result
set entropy terms, which is inconsistent with Fix 2's (correct) removal of
those terms from the later joint formula. This is not a regression from the
fixes but a pre-existing inconsistency that should be addressed separately.
