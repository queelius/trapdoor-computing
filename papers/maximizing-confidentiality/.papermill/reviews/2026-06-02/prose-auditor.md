# Prose-Auditor Report, Round 5 (2026-06-02)

**Paper**: "The Entropy Ratio" (`main.tex`, 25pp)
**Scope (per area chair):** only NEW prose since 2026-04-29: §6.5
compression-validation, §9 practical-depth, and the optimal-rate reframing
in the abstract/intro/conclusion. Prior rounds covered the rest.

---

## P-1 (MEDIUM): §6.5 panel caption/body mismatch

Already flagged 2026-05-23 (their Weakness 1); still open. The figure caption
(line 1262) labels panels **Left** (Markov), **Centre** (noise mixture),
**Right** (20NG). The body paragraph headings (lines 1280, 1292, 1305) read
"Markov auto-correlation (left panel)", "Noise mixture (**right panel**)",
"Real corpus (right panel)". The noise-mixture heading says "right" but the
caption assigns it Centre; two paragraphs now claim "right panel." **Fix:**
line 1292 heading should be "(centre panel)"; verify the body text inside it
(line 1293 also says "right panel") is corrected too. Pure mechanical, but
it is in a brand-new figure and a reader hits it immediately.

## P-2 (MEDIUM): "Le Cam's two-point method" is the wrong name (prose surface of logic-checker B2)

The phrase "Le Cam's two-point method" appears in the abstract (line 80),
intro (line 213), Related Work (line 762... actually line 270), the §5.1
narrative, the Thm 5.2 sketch (line 906), and the conclusion (line 1762).
The construction is a `2^(m/2)` hypercube packing, which is Assouad's lemma,
not the two-point method. As prose, the repeated confident naming of the
wrong technique is a credibility risk: a minimax-literate reviewer will
flag it on sight. **Fix:** global replace with "Assouad's lemma" (or "the
two-point method generalized to a hypercube," if the author wants to keep
the Le Cam lineage). This is the single most visible prose issue because it
is in the abstract and the headline claim.

## P-3 (LOW): optimal-rate reframing reads cleanly

The "information-theoretically optimal rate" language (5 occurrences:
abstract 78, intro 177/209, Related Work 269, conclusion 1760) is
well-integrated and consistent. The abstract sentence "matching upper bound
from plug-in estimation, matching lower bound via Le Cam's two-point method"
(lines 79 to 81) is crisp. The only fix needed is the technique name (P-2);
the rhetoric itself is good and not overclaimed (the matching bounds justify
"optimal"). No softening required.

## P-4 (LOW): §9 "Practical depth" paragraph is dense but sound

The new §9 paragraph (lines 1670 to 1700) stitches FPR compounding, Thm 5.1,
and orbit closure into a depth-2-to-5 heuristic. It is a long single
paragraph (30 lines) doing a lot of work; it reads well but would benefit
from a sentence break before "In practice, useful cipher programs span
depth 2 to 5" (line 1692) to separate the mechanism (why depth is bounded)
from the catalog (what real programs do). Optional. The cross-references to
`thm:comp-leakage`, `thm:comp-leakage-lb`, and `[Thm.~5.3]{algebraic}` all
resolve.

## P-5 (LOW): ξ used in the abstract before any gloss

`xi` (TV accuracy) appears in the abstract (line 79) as
`Theta(|Y_1||Y_2|/xi^2)` with no gloss; it is first explained as "TV
accuracy xi" at line 751 (Prop 8.1 inheritance) and line 851 (Thm 5.1). A
reader of the abstract alone meets an undefined symbol. **Fix:** add "(in
total-variation accuracy xi)" at the first abstract occurrence, or accept it
as standard for the venue. Cosmetic.

---

## Notation drift cross-check (per area chair item 3)

I compared glyph meanings against the spine's Canonical Notation table
(`cipher-map-formalism.md` lines 868 to 886) for the symbols the area chair
flagged: delta, Q, U, H*, xi, p, K(x), orbit.

- **delta, Q, K(x), p, orbit:** consistent with the spine. No drift.
- **U vs U_im:** the paper uses both, correctly and explicitly (logic-checker
  D). The spine canonical comparator is `U` over `B^n`; the paper's headline
  `delta` is the U-lifted value. Fine, modulo the half-sentence reminder.
- **H\*:** this is the one genuine drift. The spine pins `H* = n` (M1). The
  paper uses `H* = n` in two clauses of Thm 3.1 and `H* = log_2|X|` in a
  third, and the worked numbers use `log_2|X|`. See logic-checker C. From a
  prose standpoint, the symbol `H*` carries two meanings in one section
  without a signpost; that is the kind of overload a careful reader trips on.
  Recommend the disambiguation sentence the logic-checker proposes.
- **xi:** used before gloss (P-5), but meaning is consistent throughout.

No glyph means two different things across papers in a way that misleads;
the only intra-paper overload is `H*`.

---

## Summary

| ID | Finding | Severity |
|---|---|---|
| P-1 | §6.5 panel caption/body mismatch (centre vs right) | MEDIUM |
| P-2 | "Le Cam two-point" misnomer in abstract + headline (should be Assouad) | MEDIUM |
| P-4 | §9 practical-depth paragraph dense (optional break) | LOW |
| P-5 | xi undefined at first abstract use | LOW |
| P-3 | optimal-rate reframing reads cleanly (no action beyond P-2) | none |

The new prose is in good shape. The two MEDIUM items (P-1 panel label, P-2
technique name) are both mechanical and both in reader-visible locations
(new figure; abstract). Fix those two and the new prose is submission-clean.
