# Claim to gate map

Every theorem in the manuscript maps to a computational gate (a Catch2 test in the
self-contained `artifact/`, run via `artifact/CMakeLists.txt`) and to a section of
the source-of-record note (`source/construction-note.md`, a verbatim copy of
`maph/docs/codec_controlled_retrieval.md` at the pinned commit). The security
theorems are backed by the experiment data in `source/results/` rather than a unit
test. Independent pure-Python reimplementations in `artifact/python/verification/`
cross-check the linear-algebra gates with exact rational arithmetic.

## Theorems

| Manuscript | Result | Note section | Gate (tag) | What it checks |
|---|---|---|---|---|
| `thm:support` (T1) | non-member output support is exactly the stored span `W` | T1/T2 | `test_prefix_codec` (`[span][nonmember]`) | reachable outputs span `W`, `R(z) = W` |
| `thm:idealized` (T2) | idealized law is uniform on `W`, decoded by the codec | T1/T2 | `test_prefix_codec` (`[span][nonmember]`) | decode of `Uniform(W)` is the codec-controlled law |
| `thm:freqindep` (T3) | the non-member law is independent of storage frequency | T3 | `test_prefix_codec` (`[contrastive]`) | same `W`, different store counts, identical law |
| `thm:threshold` (T4) | sharp control threshold: control iff `rank pi|_W = log2 K` (balanced) | T4 | `test_prefix_codec` (`[threshold]`) | step in the integer rank; over/under regimes |
| `thm:graded` (T4b) | skewed codec is graded; mass is a non-increasing ladder | T4b | `test_skewed_realizability` (`[skewed][realizability]`) | flag formula, ladder, designed-Kraft punchline, witness `(1/2,1/4,1/8,1/8)` |
| `thm:realizable` (T4c) | the realizable set, completely characterized | T4c | `test_realizable_set` (`[realizable]`) | constructive form; mass>=share; `{1,2,3,3}` sufficiency (8 laws); `{2,2,3,3,3,3}` insufficiency witness |
| `thm:cogirth` (T5b) | cogirth `d*` is the exact erasure budget (balanced); `d* >= (K/2) m_min` | T5b | `test_cogirth_robustness` (`[cogirth]`) | `d*` via the closed form; broken step TV = 0.5; the bound |
| `thm:cogirth-graded` (T5c) | per-rung cogirth FAMILY (graded); T5b is the single-rung collapse | T5c | `test_cogirth_graded` (`[cogirth][graded]`) | bridge identity; per-rung cogirth vs exhaustive first-change; cascade 3/6/9; collapse |
| `thm:randenc` | balanced invariance unconditional; skewed FALSE in general, holds under saturation | randomized section | `test_randomized_encoding` (`[randomized]`) + `test_randomized_boundary` (`[randomized][boundary]`) | saturated invariance (exact + empirical + white-box divergence); the `{A,A,B}` counterexample; saturation sufficiency |
| `thm:freqdist-ideal` | idealized FreqDist advantage is exactly zero | Security | (T3 gate) + `source/results/freq_independence/` | the two oracles are the identical law under M1 |
| `thm:freqdist-real` | real advantage `<= 2(delta(p0)+delta(p1))` | Security | `source/results/scale/`, `freq_independence/` | delta measured at/below the sampling floor up to 1e7 keys |
| `lem:subspace-coset` | a subspace meets a coset in empty-or-a-coset | T4 | `test_skewed_realizability` (uses it per length) | the counting lemma the flag formula rests on |

## Experiments (E1 to E4)

| Experiment | Data | Note |
|---|---|---|
| E1 codec span / control threshold | `source/results/codec_span/` | the sharp rank threshold, replicated with CIs |
| E2 frequency independence | `source/results/freq_independence/` | non-member law vs storage frequency; the FreqDist constant |
| E3 scale independence of delta | `source/results/scale/` | delta flat in `N` from 1e4 to 1e7, at/below the sampling floor |
| E4 coincidence oracle (perimeter) | `source/results/coincidence_oracle/` | the opposite-pulling multi-instance attack; concentrated codecs defend |

## Independent Python cross-checks (`artifact/python/verification/`)

| Script | Cross-checks |
|---|---|
| `gf2.py` | shared GF(2) + `{1,2,3,3}` codec helpers |
| `item1.py`, `item1_general.py` | T4c realizable set: enumerates subspaces, the necessary conditions, sufficiency for `{1,2,3,3}`, insufficiency for `{2,2,3,3,3,3}` |
| `item2.py` | the `thm:randenc` skewed counterexample (4 distinct laws over 256 draws) and the saturated regime |
| `saturation.py` | saturation sufficiency over 12000 redraws; necessity is false; rank non-monotonicity |

These reimplement the C++ gates in pure Python with `fractions.Fraction`, so the
agreement is exact, not floating-point, and the counterexamples are independent of
the C++ codec implementation.
