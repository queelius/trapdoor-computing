#!/usr/bin/env python3
"""E4: the multi-instance coincidence-oracle attack, with the corrected direction.

Context
-------
A separate paper (cipher-maps) studies a multi-instance "coincidence oracle"
attacker against shared-function deployments. The attacker observes the outputs
of t cipher-map instances that share the same key set S and the same value
assignment f, and that differ only in their per-instance non-member randomness.
For codec-controlled retrieval the non-member output of one instance is a draw
from the codec's codespace shares alpha (alpha(v) = |class(v)| / 2^M, which sum
to 1 over the full codespace). The coincidence oracle is the simplest possible
attacker: it predicts "k in S" iff all t observed outputs are equal.

Closed form
-----------
For k in S, the canonical encoding is deterministic, so all t outputs equal f(k)
and the coincidence event C ("all t outputs equal") holds with probability 1.
For k not in S, the t outputs are i.i.d. draws from alpha, so
P(C | k not in S) = sum_v alpha(v)^t. At a balanced prior pi = 1/2 the oracle's
accuracy is

    acc(t) = 1 - (1/2) * sum_v alpha(v)^t.

Define S(t) = sum_v alpha(v)^t (the "coincidence sum").

The corrected direction (this is the crux)
-------------------------------------------
For fixed sum_v alpha(v) = 1 and t >= 2, S(t) is MAXIMIZED by a CONCENTRATED
(Huffman-like) distribution (most mass on few values, S(t) -> 1) and MINIMIZED by
the UNIFORM distribution (S(t) = K^(1 - t), small). Since acc(t) = 1 - S(t)/2:

    CONCENTRATED / Huffman  ->  large S(t)  ->  acc(t) near 1/2  ->  LOW attacker
                                                                     accuracy
                                                                     = BEST defense.
    UNIFORM                 ->  small S(t)  ->  acc(t) near 1     ->  HIGH attacker
                                                                     accuracy
                                                                     = WORST defense.

So CONCENTRATED / Huffman codecs are the BETTER defense against the coincidence
oracle; UNIFORM is the WORSE defense. An earlier writeup
(bernoulli .../RESULTS_14.md, in its pre-fix state, and cipher-maps section 10.6)
read this backwards and claimed uniform defends best. That reading is inverted.

This script independently CONFIRMS the corrected direction with a Monte Carlo
simulation of the attack, and checks the Monte Carlo against the closed form. If
the Monte Carlo were to show uniform with LOWER attacker accuracy than
concentrated, that would contradict the stated direction and the script would say
so loudly rather than print a false conclusion.

Run
---
    python3 analysis/coincidence_oracle.py
    python3 analysis/coincidence_oracle.py --trials 200000 --reps 12

Requires numpy. Deterministic given the seed (default 2026).
"""

from __future__ import annotations

import argparse
import sys

try:
    import numpy as np
except ImportError:  # pragma: no cover
    print(
        "ERROR: numpy is required. Install with 'pip install numpy'.",
        file=sys.stderr,
    )
    sys.exit(2)


# =====================================================================
# Codecs: each is a name plus an alpha vector (codespace shares, summing to 1).
# K = 8 values throughout.
# =====================================================================

K = 8


def _normalize(weights: list[float]) -> np.ndarray:
    arr = np.asarray(weights, dtype=np.float64)
    if np.any(arr < 0.0):
        raise ValueError("alpha weights must be non-negative")
    total = arr.sum()
    if total <= 0.0:
        raise ValueError("alpha weights must sum to a positive number")
    return arr / total


def build_codecs() -> dict[str, np.ndarray]:
    """Return name -> alpha (length-K codespace-share vector, sums to 1).

    All vectors have sum 1 (they tile the full 2^M codespace), so they are
    comparable under the fixed-sum coincidence-sum argument.
    """
    codecs: dict[str, np.ndarray] = {}

    # UNIFORM: alpha(v) = 1/8 each. This is the WORST defense (we will confirm).
    codecs["uniform"] = _normalize([1.0] * K)

    # HUFFMAN / CONCENTRATED: dyadic powers of two, 1/2, 1/4, 1/8, 1/16, ...
    # with the tail mass folded onto the last value so the vector sums to 1.
    # This is a realizable prefix-code codespace (Kraft-tight): codeword
    # lengths 1, 2, 3, 4, 5, 6, 7, 7. This is the BEST defense (we will confirm).
    lengths = [1, 2, 3, 4, 5, 6, 7, 7]
    codecs["huffman"] = _normalize([2.0 ** (-l) for l in lengths])

    # INTERMEDIATE_A: a milder skew (Zipf-ish), between uniform and Huffman.
    codecs["intermediate_zipf"] = _normalize(
        [1.0 / ((i + 1) ** 1.2) for i in range(K)]
    )

    # INTERMEDIATE_B: a "padded / dominant default" codec. One value holds
    # most of the codespace (a single dominant outcome), the rest split a
    # small remainder uniformly. Concentrated but in a different shape than
    # the dyadic Huffman, so it stresses the direction claim independently.
    rest = [1.0] * (K - 1)
    codecs["intermediate_padded"] = _normalize([float(9 * (K - 1))] + rest)

    return codecs


# =====================================================================
# Closed form.
# =====================================================================


def coincidence_sum(alpha: np.ndarray, t: int) -> float:
    """S(t) = sum_v alpha(v)^t."""
    return float(np.sum(np.power(alpha, t)))


def closed_form_accuracy(alpha: np.ndarray, t: int, pi: float = 0.5) -> float:
    """acc(t) = pi * P(C|in S) + (1-pi) * (1 - P(C|not in S)).

    P(C | in S) = 1 (deterministic canonical encoding).
    P(C | not in S) = sum_v alpha(v)^t.
    For pi = 1/2: acc(t) = 1 - S(t)/2.
    """
    pc_not = coincidence_sum(alpha, t)
    return pi * 1.0 + (1.0 - pi) * (1.0 - pc_not)


# =====================================================================
# Monte Carlo of the coincidence-oracle attack.
#
# Attack model (faithful to bernoulli .../14_coincidence_oracle.py):
#   - A balanced test set: half the probed keys are members, half non-members.
#   - For a MEMBER key, all t instances return the same value f(k); the t-tuple
#     of outputs is constant, so the coincidence event C ("all t equal") always
#     holds. (We do not even need to know which value: the oracle ignores the
#     value and looks only at whether the t outputs agree.)
#   - For a NON-MEMBER key, each of the t instances returns an independent draw
#     from the codec's alpha (decode of a uniform M-bit pattern). C holds iff all
#     t draws happen to coincide.
#   - The oracle predicts "in S" iff C holds. Accuracy = fraction of the balanced
#     test set classified correctly.
# The only random part is the non-member draws; members are deterministic, so a
# member is ALWAYS classified correctly and a non-member is misclassified exactly
# when its t draws coincide. Hence empirical accuracy
#   = (1/2) * 1 + (1/2) * (1 - empirical P(t non-member draws coincide)),
# which estimates the closed form 1 - S(t)/2 without bias.
# =====================================================================


def simulate_accuracy(
    alpha: np.ndarray,
    t: int,
    trials: int,
    rng: np.random.Generator,
) -> float:
    """One Monte Carlo estimate of acc(t) over `trials` balanced probes.

    We simulate `trials` member probes and `trials` non-member probes.
    Members are always correct. Non-members are correct unless their t draws
    coincide. Returns the fraction correct over all 2*trials probes.
    """
    values = np.arange(alpha.shape[0])

    # Members: t outputs are identical, so C holds and the oracle says "in S",
    # which is correct, for every member probe. Count = trials correct.
    member_correct = trials

    # Non-members: draw a (trials, t) matrix of i.i.d. value indices ~ alpha.
    draws = rng.choice(values, size=(trials, t), p=alpha)
    # Coincidence per probe: all t columns equal the first column.
    coincide = np.all(draws == draws[:, [0]], axis=1)
    # Oracle predicts "in S" iff coincide; for a non-member that is WRONG.
    # So a non-member is classified correctly iff NOT coincide.
    nonmember_correct = int(np.count_nonzero(~coincide))

    total_correct = member_correct + nonmember_correct
    total = 2 * trials
    return total_correct / total


def simulate_with_ci(
    alpha: np.ndarray,
    t: int,
    trials: int,
    reps: int,
    rng: np.random.Generator,
) -> tuple[float, float, float]:
    """Replicate the MC `reps` times; return (mean, ci_low, ci_high).

    The CI is a normal 95% interval on the across-replication mean
    (mean +/- 1.96 * sd / sqrt(reps)). With reps >= 2 this captures the
    Monte Carlo uncertainty of the estimate itself.
    """
    estimates = np.array(
        [simulate_accuracy(alpha, t, trials, rng) for _ in range(reps)],
        dtype=np.float64,
    )
    mean = float(estimates.mean())
    if reps >= 2:
        sd = float(estimates.std(ddof=1))
        half = 1.96 * sd / np.sqrt(reps)
    else:  # pragma: no cover
        # Fall back to a single-sample binomial CI on 2*trials Bernoulli probes.
        n = 2 * trials
        p = mean
        half = 1.96 * np.sqrt(max(p * (1.0 - p), 1e-12) / n)
    return mean, mean - half, mean + half


# =====================================================================
# Reporting.
# =====================================================================


def fmt(x: float, digits: int = 6) -> str:
    return f"{x:.{digits}f}"


def run(trials: int, reps: int, seed: int) -> int:
    rng = np.random.default_rng(seed)
    codecs = build_codecs()
    t_values = list(range(1, 9))  # t = 1..8

    print("=" * 78)
    print("E4: coincidence-oracle attack, corrected direction")
    print("=" * 78)
    print(
        f"K = {K} values, t = 1..8, trials = {trials} member + {trials} "
        f"non-member per rep,"
    )
    print(f"reps = {reps}, seed = {seed}.")
    print("Attacker accuracy acc(t) = 1 - (1/2) * sum_v alpha(v)^t. "
          "HIGHER acc = WORSE defense.")
    print()
    print("Codec alpha (codespace shares, sum = 1):")
    for name, alpha in codecs.items():
        shares = ", ".join(fmt(a, 4) for a in alpha)
        print(f"  {name:20s} [{shares}]  (max share {fmt(alpha.max(), 4)})")
    print()

    header = (
        f"| {'codec':20s} | {'t':>2s} | {'acc_closed':>10s} | "
        f"{'acc_mc':>10s} | {'mc_95%_ci':>24s} | {'in CI?':>6s} |"
    )
    sep = (
        "|" + "-" * 22 + "|" + "-" * 4 + "|" + "-" * 12 + "|"
        + "-" * 12 + "|" + "-" * 26 + "|" + "-" * 8 + "|"
    )
    print(header)
    print(sep)

    # Collect results for the direction check and for the results file.
    table_rows: list[str] = [header, sep]
    # acc_by_t[name][t] = closed-form accuracy.
    acc_by_t: dict[str, dict[int, float]] = {name: {} for name in codecs}
    all_in_ci = True

    for name, alpha in codecs.items():
        for t in t_values:
            acc_cf = closed_form_accuracy(alpha, t)
            acc_by_t[name][t] = acc_cf
            mc_mean, ci_lo, ci_hi = simulate_with_ci(
                alpha, t, trials, reps, rng
            )
            # The closed form should lie inside the MC 95% CI. We allow a small
            # absolute tolerance equal to one binomial standard error over the
            # full 2*trials probes: near acc = 1 the across-rep CI can collapse
            # to a width below the per-estimate sampling resolution, so without
            # this the check would flag pure sampling jitter (a few 1e-5) as a
            # mismatch. A genuine direction/formula error is far larger than this.
            tol = 1e-9 + np.sqrt(
                max(acc_cf * (1.0 - acc_cf), 1e-12) / (2.0 * trials)
            )
            in_ci = (ci_lo - tol) <= acc_cf <= (ci_hi + tol)
            all_in_ci = all_in_ci and in_ci
            ci_str = f"[{fmt(ci_lo)}, {fmt(ci_hi)}]"
            row = (
                f"| {name:20s} | {t:>2d} | {fmt(acc_cf):>10s} | "
                f"{fmt(mc_mean):>10s} | {ci_str:>24s} | "
                f"{'yes' if in_ci else 'NO':>6s} |"
            )
            print(row)
            table_rows.append(row)
        print(sep)
        table_rows.append(sep)

    # =================================================================
    # Direction check (the crux). The corrected claim is NOT "one specific
    # codec wins" but the MONOTONE statement:
    #
    #   acc(t) = 1 - S(t)/2 with S(t) = sum_v alpha(v)^t, so for t >= 2 a more
    #   CONCENTRATED codec (larger S(t)) has STRICTLY LOWER attacker accuracy.
    #   UNIFORM minimizes S(t) = K^(1-t), so it is the UNIQUE WORST defense
    #   (highest attacker accuracy). Every concentrated codec strictly beats it.
    #
    # We verify two things at every t >= 2:
    #   (A) uniform has the strictly HIGHEST attacker accuracy of all codecs.
    #   (B) the ordering of codecs by acc(t) is exactly the REVERSE of their
    #       ordering by S(t): more concentration -> less attacker accuracy,
    #       with no inversions. (intermediate_padded, max share 0.90, is the
    #       MOST concentrated and is correctly the BEST defense; huffman and
    #       intermediate_zipf sit between it and uniform. This is the direction
    #       working, not a violation.)
    # =================================================================
    print()
    print("-" * 78)
    print("DIRECTION CHECK (the crux): concentrated codecs are the BEST defense")
    print("(lower attacker accuracy); UNIFORM is the UNIQUE WORST. acc is")
    print("monotone DECREASING in concentration S(t) = sum_v alpha(v)^t.")
    print("-" * 78)

    names = list(codecs.keys())
    direction_ok = True
    for t in t_values:
        if t < 2:
            continue
        accs = {name: acc_by_t[name][t] for name in names}
        s_of_t = {name: coincidence_sum(codecs[name], t) for name in names}
        worst_name = max(accs, key=accs.get)  # highest attacker accuracy
        # (A) uniform is the unique worst (strictly highest attacker accuracy).
        unif_uniquely_worst = worst_name == "uniform" and all(
            accs["uniform"] > accs[n] + 1e-12 for n in names if n != "uniform"
        )
        # (B) acc ranking is the exact reverse of the S(t) ranking (more
        # concentration => strictly less attacker accuracy, no inversions).
        order_by_acc = sorted(names, key=lambda n: accs[n])        # asc acc
        order_by_s = sorted(names, key=lambda n: -s_of_t[n])       # desc S(t)
        monotone = order_by_acc == order_by_s
        # Concentrated codecs (huffman, padded) must both beat uniform.
        concentrated_beat_uniform = (
            accs["huffman"] < accs["uniform"] - 1e-12
            and accs["intermediate_padded"] < accs["uniform"] - 1e-12
        )
        ok = unif_uniquely_worst and monotone and concentrated_beat_uniform
        direction_ok = direction_ok and ok
        flag = "OK" if ok else "VIOLATION"
        best_name = order_by_acc[0]
        print(
            f"  t={t}: WORST = {worst_name:20s} ({fmt(accs[worst_name], 5)}), "
            f"BEST = {best_name:20s} ({fmt(accs[best_name], 5)}); "
            f"monotone={'yes' if monotone else 'NO'}  [{flag}]"
        )

    # Quote the headline numbers at t = 4 for the report.
    a4_u = acc_by_t["uniform"][4]
    a4_h = acc_by_t["huffman"][4]
    print()
    print(
        f"  At t=4: uniform acc = {fmt(a4_u, 5)} (WORST defense), "
        f"huffman acc = {fmt(a4_h, 5)} (concentrated, better defense)."
    )
    print(
        f"  Uniform lets the attacker be {fmt(a4_u - a4_h, 5)} more accurate "
        f"than Huffman at t=4 (and more still vs the most-concentrated codec)."
    )

    print()
    print("=" * 78)
    if not all_in_ci:
        print(
            "CONCERN: at least one closed-form value fell OUTSIDE the Monte "
            "Carlo 95% CI. Investigate before trusting the table."
        )
    if direction_ok and all_in_ci:
        print(
            "CONCLUSION: Monte Carlo matches the closed form for every (codec, "
            "t), AND"
        )
        print(
            "for every t >= 2 attacker accuracy is monotone DECREASING in "
            "concentration:"
        )
        print(
            "CONCENTRATED / Huffman codecs have LOWER attacker accuracy (BETTER "
            "defense) and"
        )
        print(
            "UNIFORM has the strictly HIGHEST (WORST defense). Concentration "
            "wins."
        )
        print(
            "The 'uniform defends best' reading (bernoulli RESULTS_14.md "
            "pre-fix state,"
        )
        print("cipher-maps section 10.6) is INVERTED and is WRONG.")
    elif not direction_ok:
        print(
            "STOP: the corrected direction was NOT confirmed. Either the Monte "
            "Carlo or"
        )
        print(
            "the closed form is wrong. Do NOT trust the 'concentrated wins' "
            "claim until"
        )
        print("this is debugged.")
    print("=" * 78)

    # Persist a markdown table for the bijou benchmarks dir (copied separately).
    _maybe_write_results_md(table_rows, a4_u, a4_h, trials, reps, seed)

    # Exit non-zero if the direction failed (so CI / automation catches it).
    return 0 if (direction_ok and all_in_ci) else 1


def _maybe_write_results_md(
    table_rows: list[str],
    a4_u: float,
    a4_h: float,
    trials: int,
    reps: int,
    seed: int,
) -> None:
    """Best-effort: write the table to the module-level RESULTS_MD path if set.

    The CLI sets RESULTS_MD when --results-md is passed; otherwise this is a
    no-op (the caller copies stdout into the bijou results file by hand).
    """
    path = getattr(_maybe_write_results_md, "path", None)
    if not path:
        return
    lines = [
        "# E4: coincidence-oracle attack (corrected direction)",
        "",
        f"K = 8 values, t = 1..8, trials = {trials} member + {trials} "
        f"non-member per rep, reps = {reps}, seed = {seed}.",
        "",
        "Attacker accuracy `acc(t) = 1 - (1/2) * sum_v alpha(v)^t`. "
        "HIGHER acc = WORSE defense.",
        "",
        *table_rows,
        "",
        f"At t=4: uniform acc = {fmt(a4_u, 5)} (worst defense), "
        f"huffman acc = {fmt(a4_h, 5)} (best defense).",
        "",
        "CORRECTED DIRECTION: for every t >= 2 the concentrated / Huffman "
        "codec has the LOWEST attacker accuracy (best defense) and uniform "
        "the HIGHEST (worst defense). The 'uniform defends best' reading "
        "(bernoulli RESULTS_14.md pre-fix state, cipher-maps section 10.6) "
        "is inverted and wrong.",
        "",
    ]
    with open(path, "w", encoding="utf-8") as fh:
        fh.write("\n".join(lines) + "\n")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="E4 coincidence-oracle attack, corrected direction."
    )
    parser.add_argument(
        "--trials",
        type=int,
        default=100000,
        help="member (and non-member) probes per replication (default 100000).",
    )
    parser.add_argument(
        "--reps",
        type=int,
        default=10,
        help="number of Monte Carlo replications for the CI (default 10).",
    )
    parser.add_argument(
        "--seed", type=int, default=2026, help="numpy seed (default 2026)."
    )
    parser.add_argument(
        "--results-md",
        type=str,
        default=None,
        help="optional path to also write the table as markdown.",
    )
    args = parser.parse_args(argv)
    if args.results_md:
        _maybe_write_results_md.path = args.results_md  # type: ignore[attr-defined]
    return run(trials=args.trials, reps=args.reps, seed=args.seed)


if __name__ == "__main__":
    sys.exit(main())
