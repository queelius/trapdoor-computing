# Literature / Cross-Paper Context Packet, Round 5 (2026-06-02)

External literature scouts (broad/targeted) were not launchable in this
environment (Task tool unavailable, as in the 2026-04-29 round). For this
CROSS-PAPER round the relevant "literature" is the trapdoor-computing paper
family itself plus the canonical spine. This packet consolidates the
authoritative ownership map that the specialist findings reference.

## Authoritative sources used

1. **Spine** `formalism/cipher-map-formalism.md` (dated 2026-06-02,
   "Canonical source of truth"). Authoritative on shared definitions
   (line 9). Key sections: §4A (two-scale confidentiality measures), §8
   (Paper Map + Canonical Notation table).
2. **Consistency report** `formalism/cross-paper-consistency.md`
   (2026-06-02). Verbatim-extraction audit, findings C-1..C-10.
3. **cipher-maps** (hub) `papers/cipher-maps/paper/cipher_maps.{tex,aux}`.
4. **algebraic-cipher-types** `papers/algebraic-cipher-types/paper/main.{tex,aux}`.

## The five confidentiality measures (spine §4A) and their owners

| Measure | Scale | Quantity | δ-controlled? | Owner |
|---|---|---|---|---|
| M1 entropy ratio | marginal | `e = H(Q)/n >= 1 - δ - h_2(δ)/n` | yes | **This paper** (Thm 3.1), cipher-maps (Prop 5.1) |
| M2 single-guess | marginal | accuracy `<= 1/2 + δ/2` | yes | cipher-maps (§5.3) |
| C1 orbit closure | active | `H(X|V_F) >= H(X) - log_2|orbit_F(c)|` | no | algebraic |
| C2 coincidence | compositional | `acc(t) = 1 - (1/2) sum_y α(y)^t` | no | cipher-maps (Thm 8.2) |
| C3 joint recovery | compositional | minimax `Θ(|Y_1||Y_2|/ξ^2)` | no | **This paper** (Thms 5.1, 5.2) |

This paper OWNS M1 (shared) and C3. It correctly cites C1 and does not claim
M2. The one omission surfaced this round: the §9 depth discussion does not
cross-reference C2 (novelty-assessor N-2).

## Companion label resolution (from the `.aux` files)

These are the resolved numbers every citation-drift finding rests on:

cipher-maps (`cipher_maps.aux`):
- `def:cipher-map = 3.1`, `sec:properties = 4`, `thm:lower-bound = 6.1`,
  `sec:trust-model = 5`, `subsec:acceptance = 6.2`
- `sec:composition = 7`, gate-error subsec = 7.4
- `sec:uniformity = 8`, `prop:granularity = 8.1`,
  `subsec:comp-leakage = 8.2`, `thm:coincidence-oracle = 8.2` (theorem),
  `sec:discussion = 9`

algebraic-cipher-types (`main.aux`):
- `prop:product-tradeoff = 4.1`, `thm:sum-impossibility = 4.2`
- `sec:orbit = 5`, `thm:confidentiality-bound = 5.3` (entropy form),
  `sec:orbit-examples = 5.4`, `sec:typed-chains = 5.5`

## Consistency-report findings touching this paper (status this round)

- **C-4 (Le Cam dual-role):** still OPEN. No footnote at our Thm 5.2 site.
  (logic-checker A4). Compounded by the fact that our use is actually
  Assouad, not Le Cam two-point (logic-checker B2).
- **C-6 (parameter tuple order):** OPEN. Spine canonical is `(η, ε, μ, δ)`.
  Our paper uses `(η, ε, δ, μ)` at lines 109, 277, 471, 1779 and `(η, ε, δ)`
  at 429; only line 319 (the hub-import line) uses the canonical
  `(η, ε, μ, δ)`. Internally inconsistent. (logic-checker / area chair.)
- **C-9 (H\* ambiguity):** OPEN, three-way within Thm 3.1, and the worked
  e-values use `log_2|X|` while the Fannes bound uses `n`. (logic-checker C.)
- **C-10 (U vs U_im):** effectively CLOSED. The two-step lift is explicit in
  Thm 4.2 and downstream uses U_im honestly. (logic-checker D.)

## Prior-round carry-over relevant to framing

The 2026-05-23 round (the first 25-page round) already caught the §6.5 panel
mismatch and the Assouad-vs-Le-Cam naming, but was NOT cross-paper-citation
informed: it did not catch the six citation-drift errors, the orbit
denominator discrepancy, the FPR/granularity over-attributions, the C-6
order, the C-9 normalizer split, or the stale bidirectional cite. Those are
this round's contribution.

## Positioning (carry-over, unchanged)

The paper's external positioning against QIF (Smith; Alvim et al.), SSE
leakage mitigation (Bost-Fouque; Demertzis et al.), and PPE inference attacks
(Naveed et al.; Islam et al.) is intact from prior rounds. No external
novelty threat identified; the cipher-map framing remains structurally
distinctive (information-theoretic, no ORAM/FHE/simulation machinery).
