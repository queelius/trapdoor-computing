# Fourth-round verification review (2026-04-29)

**Scope**: verify six fixes from the 2026-04-13 review post-session.

## Fixes verified clean

- **MAJ-3 (§6.3 typed-chain misapplication)**: The "What bounds the orbit in each case" paragraph (lines 1181-1201) now cleanly distinguishes the two arguments. Expression-tree realization invokes `\Cref{def:typed-chain}` and `\Cref{prop:typed-orbit}` with the bound `\sum_i N_i`; cipher TM is explicitly called out as *not* satisfying the typed-chain hypothesis (single cipher space, self-loop), with a separate deterministic-trajectory bound of `T+1` (or `m(T+1)`). The closing sentence frames cut-point structure as a syntactic abstraction over which decompositions exist, not a single confidentiality theorem. No residual conflation.

- **MAJ-1 (§6.3 regex example)**: Example 6.7 (lines 1203-1233) now (a) acknowledges `|Q_R| = 2^{O(r)}` worst case via subset construction (line 1207), (b) uses the natural typed-chain decomposition with ℓ separate `\hat{\delta}_i : \cipher{Q_R}_i \times \cipher{\Sigma} \to \cipher{Q_R}_{i+1}` cipher maps each of size `O(|Q_R|·|Σ|)`, total `O(ℓ·|Q_R|·|Σ|)`, and (c) closes with "Cut-point placement therefore selects *which structure leaks*, not *whether the program fits in space*." Strawman framing eliminated.

- **MAJ-2 (§6.1 cipher TM shift cipher map)**: Definition 6.1 (lines 976-1010) factors the head shift into two unary cipher maps `\hat{\mathrm{clear}} : \cipher{Q×Γ} \to \cipher{Q×Γ}` and `\hat{\mathrm{set}}_q : \cipher{Q×Γ} \to \cipher{Q×Γ}` parameterized by `(q, d)`. Each has domain size `|Q×Γ|`. Proposition 6.1 (lines 1012-1030) reports `|Q|·|{L,R,S}|` instances of `\hat{\mathrm{set}}_q` plus the single `\hat{\mathrm{clear}}` and the single `\hat{\tau}_T`, totalling `O(|Q|² · |Γ|)`. The bookkeeping is internally consistent: domain size per map is `|Q×Γ| = |Q|·|Γ|`, multiplied by `|Q|·3` instances = `O(|Q|²·|Γ|)`.

- **LC-MIN-3 (notation collision δ_T → τ_T)**: All TM-transition occurrences (lines 971-1029, 1164-1165, 1210) use `\tau_T` or `\hat{\tau}_T`; an explanatory sentence at lines 971-974 motivates the rename. No residual `\delta_T` remains anywhere in main.tex (grep confirms zero matches). All `\Cref{def:cipher-tm}` style references resolve (no "undefined reference" warnings in main.log).

- **LC-MIN-4 (formal `\cipher{X}` definition)**: New `\begin{definition}[Cipher type]` with `\label{def:cipher-type}` is in place at lines 261-271, correctly defined as the set of valid cipher values `{enc(x,k) : x∈X, 0≤k<K(x)}`. Sits between the cipher-value note (line 257) and the trusted/untrusted machines definition (line 273), matching the requested location. The §4 inline introduction at line 295 has been replaced with "We use the cipher-type notation `\cipher{X}` from `\Cref{def:cipher-type}` throughout." Clean.

- **LC-MIN-6 ("zero errors" framing)**: §7.3 lines 1427-1430 now read "As expected from the PHF construction (perfect-hash backing gives exact lookup on the construction domain), all three produce zero errors on the full domain (150 inputs); we report this as a sanity check, not a measured outcome." Honest qualification.

## Fixes with residual issues

None.

## New defects introduced (if any)

None observed. The build is clean (no undefined references, no multiply-defined labels in main.log).

## Status of overall trajectory

The paper is converging. The fourth round closed the three new majors from the 2026-04-13 round and the three associated minors with no residual breakage. Section 6 (cipher TM, expression-tree decomposition, cut-point common structure) now reads as a coherent unit with consistent notation, well-bounded space accounting, and a sharp distinction between the two orbit-bound arguments. Remaining open items (M2/M3/M4/M5 experimental, M7 doc class, M9 self-citations) are out-of-scope per instructions and unaffected by this pass.
