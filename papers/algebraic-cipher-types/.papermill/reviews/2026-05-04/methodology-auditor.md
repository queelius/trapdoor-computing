# Methodology Auditor Report

**Date**: 2026-05-04 (cross-paper-informed)
**Reviewer role**: Experimental design, statistical rigor, reproducibility.
**This round**: (1) re-confirm the 2026-04-30 experimental rerun still holds; (2) serve as the cross-verification lens for the Thm 5.3 proof gap (route: logic issue -> methodology-auditor, "is the probabilistic/random-variable structure set up correctly?").

## Experimental methodology (re-confirmation)

The 2026-04-30 rerun closed all prior methodology majors and nothing has regressed. Verified against §7.3 (ACT:1392-1541) and the displayed tables:

- **Five-seed averaging** with mean +/- SD on all three §7.3 tables (Tables 2,3,4 in the typeset numbering). Good hygiene.
- **Plaintext baseline** correctly framed as "1.00/1.00 by construction" (the cipher Boolean type is a sound over-approximation of set membership) -- this is the right framing; it is not an empirical baseline but a structural reference, and the paper says so (ACT:1408-1410).
- **Honest reporting of seed-search failure**: the intermediate granularity row reports n=2 of 5 successful seeds (ACT:1504-1506, 1520). Reporting the failure rather than hiding it is exactly right.
- **Hardware spec** stated (x86_64, single-threaded, Python 3.12; ACT:1399-1400).
- **Reproducibility**: the driver script lives in the sibling `cipher-maps` repo. Note: the integration handshake doc referenced as `src/cipher-maps/PAPER-INTEGRATION.md` was **not found at that path** in this checkout (I searched `src/` and `~/github/cipher-maps`); this does not affect the paper's claims but the reproducibility pointer in the paper's CLAUDE/state docs is stale. The paper text itself does not cite that path, so no paper edit is required; flag for the author's records. (Minor, documentation-only.)

### Statistical candor at k=5 (carry-over suggestion, still apt)
Table 2's AND ratio at k=5 is 12,160x, but at 1000 trials/seed the expected FP count under the Bernoulli model (p_T^5 = 3.13e-7) is ~3e-4, so the empirical floor (~0.0038) is driven by a handful of false positives. The qualitative claim (orders-of-magnitude divergence) is robust and well-explained structurally; the *specific multiplier* is trial-count-sensitive. One candor sentence near Table 2 would pre-empt a methodology reviewer. Suggestion-level (not a defect; the structural explanation at 1480-1496 is sound and is the actual contribution).

## Cross-verification of the Thm 5.3 proof gap (methodology lens)

I was routed the logic-checker's MAJ finding (Thm 5.3 proof, ACT:858-867) for a second opinion from the probabilistic-structure angle. **I agree the random-variable setup is wrong**, and from the methodology lens the diagnosis is clean:

A mutual-information bound `I(X;V) <= H(V) <= log2 N` is only valid when V is a random variable with at most N realizations. The proof needs V to be the adversary's *observation*. As written, `V_F(c) := orbit_F(c)` is a deterministic function of (c, F) -- and the paper itself states the orbit does **not** depend on the latent value X (ACT:775-782). A quantity that does not depend on X carries zero mutual information with X. So the *literal* object the proof conditions on gives the vacuous bound I(X;V)=0. The intended object -- "which cipher value in the orbit the adversary's probing lands on / distinguishes" -- is X-dependent and does have <= |orbit| realizations, which is what makes the bound meaningful. The proof silently uses the second while defining the first.

This is exactly the kind of estimator/measurement mis-specification that the methodology lens is meant to catch: the *measured quantity* (orbit-as-set) and the *quantity the inference needs* (orbit-landing observable) are not the same random variable. **The underlying claim is methodologically reasonable** -- bounding leakage by the log of the number of distinguishable observations is standard -- so the repair is to fix the random-variable definition, not to retract the theorem. I endorse the logic-checker's option (b) (set-form-first via injective decoder, then entropy form). The theorem statement, and therefore the abstract/intro/conclusion, need not change.

**Conclusion of cross-verification**: both lenses (logic, methodology) agree -- proof gap is real, bound is recoverable, statement stands. No disagreement.

## Other methodology checks
- Table 3 (Boolean search) precision approximation k/(k + p_T(N-k)) (ACT:1438-1440) checks out for the single-term case (~0.4). FP counts (233/43/15) consistent with decreasing match sets through AND chains.
- Table 4 (granularity) counter-intuitive finding (leaf/intermediate use *less* total space than root: ~140B vs 694B) is physically correct (smaller per-component domains; seed-search stores one n-bit seed/element). The 2026-04-30 round verified this; re-confirmed. The bits/elem cross-check (37.0 root vs 7.4-7.5 component) is consistent.

## Confidence
High. Experimental side is solid and unchanged. Thm 5.3 cross-verification: high confidence the random-variable structure is mis-specified and high confidence it is repairable.
