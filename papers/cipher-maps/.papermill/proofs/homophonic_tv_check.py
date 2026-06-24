import math, random

def tv_and_bounds(D, c):
    X = list(D)
    K = {x: max(1, math.ceil(c * D[x])) for x in X}
    N = sum(K.values())
    # TV(Q,U) = TV(D, A) where A(x)=K(x)/N
    tv = 0.5 * sum(abs(D[x] - K[x]/N) for x in X)
    return tv, len(X)/(2*N), len(X)/N, N

random.seed(1)
worst_ratio_half = 0.0  # max of TV / (|X|/(2N)); >1 means |X|/(2N) violated
worst_case = None
viol = 0
trials = 200000
for _ in range(trials):
    n = random.randint(2, 40)
    # random distribution (Dirichlet-ish via exponentials)
    w = [random.expovariate(1.0) for _ in range(n)]
    s = sum(w); D = {i: w[i]/s for i in range(n)}
    c = random.choice([1,2,3,5,10,30,100,300,1000])
    tv, b_half, b_full, N = tv_and_bounds(D, c)
    if b_half > 0:
        r = tv / b_half
        if r > worst_ratio_half:
            worst_ratio_half = r
            worst_case = (n, c, tv, b_half, b_full, N)
    if tv > b_half + 1e-12:
        viol += 1

print(f"trials: {trials}")
print(f"violations of |X|/(2N): {viol}")
print(f"max ratio TV / (|X|/(2N)): {worst_ratio_half:.6f}")
print(f"worst case (n,c,tv,bound_half,bound_full,N): {worst_case}")
