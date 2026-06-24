#!/usr/bin/env python3
"""E3: replicated codec-security study.

Wraps bernoulli Experiment 14 (coincidence oracle) with a 10-iteration
replicate loop per (codec, t) cell. For each cell, computes mean
attacker accuracy, pooled Wilson 95% CI from 10*5000*2 = 100000 trials,
gap from theoretical prediction, and whether the prediction lies
inside the CI.

Run from cipher-maps paper root:

    python3 .papermill/experiments/2026-05-23/e3_codec_replicated.py \\
        --out .papermill/experiments/2026-05-23/e3 \\
        --n-replicates 10
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import math
import random
import sys
import time
from dataclasses import dataclass, asdict
from pathlib import Path

BERNOULLI_SRC = Path.home() / "github/bernoulli/src/bernoulli/src"
BERNOULLI_EXP = Path.home() / "github/bernoulli/src/bernoulli/experiments"
sys.path.insert(0, str(BERNOULLI_SRC))


def _load_exp14():
    """Load the numerically-prefixed Experiment 14 module via importlib."""
    spec = importlib.util.spec_from_file_location(
        "exp14", str(BERNOULLI_EXP / "14_coincidence_oracle.py")
    )
    if spec is None or spec.loader is None:
        raise RuntimeError("could not load Experiment 14")
    mod = importlib.util.module_from_spec(spec)
    sys.modules["exp14"] = mod  # required for @dataclass with `from __future__ import annotations`
    spec.loader.exec_module(mod)
    return mod


exp14 = _load_exp14()


CODEC_LABELS = [
    "Dense(M=3)",
    "Dense(M=4)",
    "Padded(M=4,v0)",
    "Huffman(M=4,p_f)",
    "AntiHuffman(M=4)",
]
T_VALUES = [1, 2, 3, 4, 5]


@dataclass
class ReplicatedCell:
    codec_label: str
    t: int
    n_replicates: int
    n_trials_per_replicate: int
    n_trials_total: int
    accuracy_predicted: float
    accuracy_empirical_mean: float
    accuracy_empirical_std: float
    accuracy_ci_low: float
    accuracy_ci_high: float
    gap_mean_vs_predicted: float
    prediction_in_ci: bool
    successes_pooled: int
    pc_nonmember_predicted: float
    max_q: float


def wilson_ci(successes: int, n: int, z: float = 1.96) -> tuple[float, float]:
    if n == 0:
        return (0.0, 1.0)
    p = successes / n
    denom = 1.0 + z * z / n
    centre = (p + z * z / (2.0 * n)) / denom
    half = (
        z * math.sqrt(p * (1.0 - p) / n + z * z / (4.0 * n * n))
    ) / denom
    return (max(0.0, centre - half), min(1.0, centre + half))


def run_cell_replicated(
    codec_label: str,
    t: int,
    p_f: dict,
    n_keys: int,
    n_universe_extra: int,
    n_test_per_class: int,
    n_replicates: int,
    base_seed: int,
) -> ReplicatedCell:
    per_rep_accuracy: list[float] = []
    successes_pooled = 0
    trials_per_rep = 2 * n_test_per_class  # member + non-member

    # Build codec once (deterministic given p_f).
    codec = exp14.make_codec(codec_label, p_f)

    for rep in range(n_replicates):
        cell_rng = random.Random(base_seed + rep)
        cell = exp14.run_one_cell(
            codec_label=codec_label,
            codec=codec,
            t=t,
            p_f=p_f,
            n_keys=n_keys,
            n_universe_extra=n_universe_extra,
            n_test_per_class=n_test_per_class,
            rng=cell_rng,
        )
        per_rep_accuracy.append(cell.accuracy_empirical)
        successes_pooled += round(cell.accuracy_empirical * trials_per_rep)

    n_trials_total = trials_per_rep * n_replicates
    mean = sum(per_rep_accuracy) / len(per_rep_accuracy)
    if len(per_rep_accuracy) > 1:
        var = sum((x - mean) ** 2 for x in per_rep_accuracy) / (len(per_rep_accuracy) - 1)
        std = math.sqrt(var)
    else:
        std = 0.0
    ci_low, ci_high = wilson_ci(successes_pooled, n_trials_total)
    # One canonical cell-level evaluation for theoretical prediction
    canonical = exp14.run_one_cell(
        codec_label=codec_label,
        codec=codec,
        t=t,
        p_f=p_f,
        n_keys=n_keys,
        n_universe_extra=n_universe_extra,
        n_test_per_class=10,  # tiny; we only want the prediction fields
        rng=random.Random(base_seed),
    )
    predicted = canonical.accuracy_predicted
    pc_nm = canonical.pc_nonmember_predicted
    max_q = canonical.max_q
    gap = mean - predicted
    in_ci = ci_low - 1e-6 <= predicted <= ci_high + 1e-6

    return ReplicatedCell(
        codec_label=codec_label,
        t=t,
        n_replicates=n_replicates,
        n_trials_per_replicate=trials_per_rep,
        n_trials_total=n_trials_total,
        accuracy_predicted=predicted,
        accuracy_empirical_mean=mean,
        accuracy_empirical_std=std,
        accuracy_ci_low=ci_low,
        accuracy_ci_high=ci_high,
        gap_mean_vs_predicted=gap,
        prediction_in_ci=in_ci,
        successes_pooled=successes_pooled,
        pc_nonmember_predicted=pc_nm,
        max_q=max_q,
    )


def write_csv(rows: list[ReplicatedCell], path: Path) -> None:
    if not rows:
        return
    fieldnames = list(asdict(rows[0]).keys())
    with path.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in rows:
            writer.writerow(asdict(r))


def write_summary(rows: list[ReplicatedCell], path: Path) -> None:
    in_ci = sum(1 for r in rows if r.prediction_in_ci)
    total = len(rows)
    max_gap = max(abs(r.gap_mean_vs_predicted) for r in rows) if rows else 0.0
    mean_gap = (
        sum(abs(r.gap_mean_vs_predicted) for r in rows) / total if rows else 0.0
    )

    lines = [
        "# E3 Replicated codec-security study",
        "",
        f"Run: {time.strftime('%Y-%m-%d %H:%M:%S')}",
        f"Replicates per cell: {rows[0].n_replicates if rows else 'N/A'}",
        f"Trials per cell: {rows[0].n_trials_total if rows else 'N/A'}",
        f"Cells with theoretical prediction inside Wilson 95% CI: {in_ci} / {total}",
        f"Mean absolute gap (empirical mean - predicted): {mean_gap:.4f}",
        f"Max absolute gap: {max_gap:.4f}",
        "",
        "## Per-cell results",
        "",
        "| codec | t | predicted | empirical mean | std | 95% CI | gap | in CI? |",
        "|---|--:|--:|--:|--:|---|--:|:-:|",
    ]
    for r in rows:
        ci = f"[{r.accuracy_ci_low:.4f}, {r.accuracy_ci_high:.4f}]"
        lines.append(
            f"| {r.codec_label} | {r.t} | {r.accuracy_predicted:.4f} | "
            f"{r.accuracy_empirical_mean:.4f} | {r.accuracy_empirical_std:.4f} | "
            f"{ci} | {r.gap_mean_vs_predicted:+.4f} | "
            f"{'yes' if r.prediction_in_ci else 'NO'} |"
        )
    lines += [
        "",
        "## Inclusion decision (per design.md)",
        "",
        "- Strong include (>= 28/30 in CI): section 10.6 Table 1 augmented with mean and CI columns; 'tight up to sampling noise' claim retained",
        "- Weak include (24-28/30 in CI): present results honestly; identify which cells deviate and why",
        "- Cut and re-investigate (< 24/30 in CI): theorem-vs-empirical gap is wider than the single-run paper claimed",
        "",
        f"This run: {in_ci}/{total} cells in CI.",
    ]
    path.write_text("\n".join(lines) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--n-replicates", type=int, default=10)
    parser.add_argument("--n-keys", type=int, default=2000)
    parser.add_argument("--n-universe-extra", type=int, default=8000)
    parser.add_argument("--n-test-per-class", type=int, default=5000)
    parser.add_argument("--seed", type=int, default=2026)
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=True)

    p_f = exp14.f_distribution()
    rows: list[ReplicatedCell] = []
    for label in CODEC_LABELS:
        for t in T_VALUES:
            t0 = time.time()
            print(f"cell {label}, t={t}...", file=sys.stderr, flush=True)
            cell = run_cell_replicated(
                codec_label=label,
                t=t,
                p_f=p_f,
                n_keys=args.n_keys,
                n_universe_extra=args.n_universe_extra,
                n_test_per_class=args.n_test_per_class,
                n_replicates=args.n_replicates,
                base_seed=args.seed + hash((label, t)) % (1 << 20),
            )
            dt = time.time() - t0
            print(
                f"  mean={cell.accuracy_empirical_mean:.4f} "
                f"pred={cell.accuracy_predicted:.4f} "
                f"gap={cell.gap_mean_vs_predicted:+.4f} "
                f"in_ci={cell.prediction_in_ci} ({dt:.1f}s)",
                file=sys.stderr,
            )
            rows.append(cell)
    write_csv(rows, args.out / "results.csv")
    write_summary(rows, args.out / "summary.md")
    in_ci = sum(1 for r in rows if r.prediction_in_ci)
    print(f"wrote {args.out}; {in_ci}/{len(rows)} cells in CI", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
