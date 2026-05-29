import math

def homophonic_tv(D, c):
    X = list(D)
    K = {x: max(1, math.ceil(c * D[x])) for x in X}
    total_slots = sum(K.values())
    tv = 0.0
    for x in X:
        per_value_Q = D[x] / K[x]
        per_value_U = 1.0 / total_slots
        tv += K[x] * abs(per_value_Q - per_value_U)
    tv *= 0.5
    bound = len(X) / (2.0 * total_slots)
    return tv, bound, total_slots

results = []
results.append(f"{'dist':<14}{'c':>8}{'sumK':>8}{'TV':>12}{'bound':>12}{'ok':>6}")
dists = {}
dists["uniform-8"] = {i: 1/8 for i in range(8)}
for n in (8, 32):
    raw = [1/((i+1)**1.0) for i in range(n)]
    s = sum(raw); dists[f"zipf-{n}"] = {i: r/s for i,r in enumerate(raw)}
dists["heavy-tail"] = {0: 0.9, **{i: 0.1/9 for i in range(1,10)}}

for name, D in dists.items():
    for c in (10, 100, 1000, 10000):
        tv, bound, sk = homophonic_tv(D, c)
        ok = "yes" if tv <= bound + 1e-12 else "NO!"
        results.append(f"{name:<14}{c:>8}{sk:>8}{tv:>12.6f}{bound:>12.6f}{ok:>6}")

open("tv_out.txt","w").write("\n".join(results))
print("\n".join(results))
