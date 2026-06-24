# Methodology-Auditor Report, Round 5 (2026-06-02)

**Paper**: "The Entropy Ratio" (`main.tex`, 25pp)
**Scope (light, per area chair):** the NEW §6.5 compression-validation
experiment, and whether the new headline framing has left any
methodological gap. Tables 1 to 4 and §6.1 to 6.4 were audited in rounds 1
to 4; only deltas here.

---

## §6.5 "Empirical Anchor for the Compression Estimator" (new since 2026-04-29)

This subsection (lines 1243 to 1369) upgrades Prop 6.1 from "asserted" to
"empirically anchored." It tests `hat H` (gzip per-symbol estimate) on four
streams: i.i.d. uniform sanity check, first-order Markov, the Thm 4.1 noise
mixture, and a real 20NG token stream. Reproducibility points to
`experiments/compression_validation.py` (line 1396). 5 seeds, error bars
`+- 1 sigma`. This is solid methodology for a measurement-tool validation.

**Strength.** The design is honest about what it is testing: archetypes of
stream structure, not specific cipher programs. The "Scope" paragraph
(lines 1353 to 1369) pre-empts the obvious objection (these are not the
output of a real multi-primitive cipher program) and correctly defers
program-shape mapping to deployment-time analysis. The bias direction
(`hat H >= H_rate`) matches Prop 6.1 on every stream, which is the claim the
proposition makes. Good.

### M-1 (MEDIUM): noise-mixture panel is methodologically mislabeled, and the bias story is confounded

Two coupled issues in the noise-mixture panel:

1. **Panel-label mismatch (also a prose finding).** The caption (line 1262)
   places the noise mixture in the **Centre** panel; the body paragraph
   (line 1292) titles it "Noise mixture (**right panel**)." Right is the
   20NG corpus per the caption. A reader cross-referencing figure and text
   is misdirected. **Fix:** body should read "(centre panel)."

2. **The pure-Zipf bias is a known confound, stated but not quantified
   cleanly.** At `rho=1.0` the estimator reads `hat H = 11.72` against a
   predicted `9.53` (line 1298): a 2.2-bit gap. The text attributes this to
   gzip degenerating to byte-level Huffman on 16-bit symbols whose byte-pair
   entropy exceeds the 14-bit symbol entropy (lines 1299 to 1303). That
   explanation is plausible and honest, but it means the noise-mixture panel
   does NOT cleanly validate Thm 4.1's formula at the `rho=1` endpoint: the
   2.2-bit gap is an encoding artifact, not the theorem's prediction. The
   panel validates the SLOPE (dilution direction) well; it does not validate
   the absolute `H_mix` at the no-noise end. **Fix:** state explicitly that
   the panel validates the dilution trend and the `rho < 1` regime, and that
   the `rho=1` point is dominated by the byte-alignment confound (so it is
   not evidence for or against the formula there). One sentence.

### M-2 (LOW): "5 seeds" vs single-corpus claims

The 20NG corpus panels (real-corpus, right) are single-corpus measurements;
the text correctly notes the `~0.03`-bit margin is "near the noise floor of
single-corpus measurement" (line 1322). Good hedging. No CIs are possible on
a single corpus, which is fine, but the 5-seed claim in the §6.5 opener
(line 1254) applies only to the synthetic streams. **Fix:** clarify "5 seeds
(synthetic streams); the 20NG stream is a single corpus." Cosmetic.

### M-3 (LOW, carry-over from prior rounds): Thm 5.1/5.2 still not empirically validated

The headline compositional-leakage pair (Thm 5.1 + 5.2) has no direct
experiment: §6 validates FPR compounding (Table 2), granularity (Table 3),
homophonic (§6.4), the case study (Table 4), and now the compression
estimator (§6.5), but not the joint-recovery attack itself. This was noted
2026-04-29 (their methodology weakness 5) and 2026-05-23. For a theory venue
this is acceptable (the rate is classical and the lower bound is analytic),
but the paper should keep the one-sentence acknowledgment. Confirmed present
in spirit via the §6.5 "Scope" paragraph, which references Thm 5.1's
compositional leakage as shaping real program streams. Adequate; no new
action.

---

## Tables 1 to 4 (delta check only)

- Table 2 (FPR compounding): the AND noise-floor at `~4e-3` for `k>=3` is
  intact and correctly reframed as a defender's confidentiality budget
  (lines 1481 to 1494). Do not "fix" to zero (per CLAUDE.md). The empirical
  ratios (35x at k=3, 256x at k=4, 1.2e4 at k=5) correctly illustrate the
  floor dominating `p_T^k`. Consistent with the §9 practical-depth claim of
  a `k~3` correctness ceiling.
- Table 4 (case study): analytical, labeled as such (caption line 1596).
  Uses the homophonic `K(x) propto D(x)` construction. The `0.72 -> 0.98`
  trajectory is unchanged and was numerically re-verified in prior rounds.
  Note the normalizer caveat from the logic-checker C-9 finding: these
  e-values use `log_2|X|`, not `n`; that is a presentation issue, not a
  computation error.

No new methodological defects in the tables.

---

## Summary

| ID | Finding | Severity |
|---|---|---|
| M-1 | Noise-mixture panel mislabeled (centre vs right) + rho=1 confound not bounded off | MEDIUM |
| M-2 | "5 seeds" scope (synthetic only) | LOW |
| M-3 | Thm 5.1/5.2 unvalidated empirically (carry-over, acceptable) | LOW |

§6.5 is a genuine methodological strengthening. The one substantive item is
M-1: fix the panel label and explicitly scope the `rho=1` confound out of
the formula-validation claim. Everything else is cosmetic or accepted
carry-over.
