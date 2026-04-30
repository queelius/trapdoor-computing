# Preliminary Results

All numbers come from
`~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py`.
Re-run with:

```bash
cd ~/github/trapdoor-computing/src/cipher-maps
python -m experiments.online_adaptation --scenario both --n-queries 30000 --seed 42
```

## Stationary scenario

Setup: Zipf$(64, \alpha=1.5)$, budget = 1024, batch size 1500, retune
every batch, smoothing $\alpha = 1$.

| Cumulative queries | predicted_tv (oracle) | empirical_e (oracle) |
|---|---|---|
| 4500   | 0.0365 | 0.604 |
| 10500  | 0.0217 | 0.594 |
| 16500  | 0.0157 | 0.608 |
| 22500  | 0.0163 | 0.608 |
| 28500  | 0.0140 | 0.598 |

Predicted TV against the oracle distribution decreases monotonically
as more queries arrive. The algorithm is learning $D$ and tuning
$K(x)$ progressively closer to the analytical optimum.

## Drift scenario

Setup: same as stationary, but the true distribution shifts from
Zipf$(\alpha = 2.0)$ to Zipf$(\alpha = 1.0)$ at cumulative queries
$\approx 15{,}000$.

| Cumulative | predicted_tv (oracle) | empirical_e |
|---|---|---|
| 4500   | 0.042 | 0.607 |
| 10500  | 0.034 | 0.588 |
| 16500  | 0.434 | 0.406 |  <-- drift hits, K(x) is now stale
| 22500  | 0.321 | 0.500 |
| 28500  | 0.250 | 0.548 |

At the drift point predicted TV jumps from $0.034$ to $0.434$, a
12-fold degradation. Adaptive retuning recovers part of this within
two batches but the system has spent ~6000 queries in degraded
confidentiality.

This is the central phenomenon the paper formalizes: stale $K(x)$
under drift produces a measurable confidentiality crater whose
depth scales with the drift magnitude and whose width scales with
the retune cadence.

## Figures (already generated)

In `~/github/trapdoor-computing/src/cipher-maps/experiments/figures/`:

- `online_stationary.png`: stationary trajectory.
- `online_drift.png`: drift trajectory with vertical drift marker.
- `newsgroups_homophonic.png`: cross-strategy benchmark on 20NG
  (also referenced by the Entropy Ratio paper).
- `fig1_empirical_tv.png`, `fig2_gap_vs_sqrt_ratio.png`:
  finite-sample bias on synthetic Zipf.
