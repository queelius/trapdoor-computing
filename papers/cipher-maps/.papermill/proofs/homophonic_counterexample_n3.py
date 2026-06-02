import math
def tv(D, c):
    X=list(range(len(D)))
    K=[math.ceil(c*D[x]) for x in X]; N=sum(K)
    t=0.5*sum(abs(D[x]-K[x]/N) for x in X)
    return t, N, K
# Hand counterexample: n=3, c=100, near point-mass D
D=[0.0101,0.0101,0.9798]; c=100
t,N,K=tv(D,c)
print(f"n=3 c=100 D={D}")
print(f"  min D={min(D)}, 1/minD={1/min(D):.4f}, hypothesis c>=1/minD: {c>=1/min(D)}")
print(f"  K={K} N={N}")
print(f"  TV={t:.6f}")
print(f"  |X|/(2N) [maxconf claim] = {3/(2*N):.6f}   -> TV/claim = {t/(3/(2*N)):.4f}")
print(f"  (|X|-1)/N [corrected]    = {2/N:.6f}   -> TV<=this? {t<=2/N+1e-12}")
print(f"  |X|/N [hyp-free old]     = {3/N:.6f}")
# sweep n=2..8, push c large, k=n-1 light elements just above floor, 1 heavy
print("\nsup construction (k=n-1 light at (1+e)/c, 1 heavy), c=10000:")
for n in range(2,9):
    c=10000.0; e=1e-3
    light=(1+e)/c
    Dn=[light]*(n-1)+[1-(n-1)*light]
    t,N,K=tv(Dn,c)
    claim=n/(2*N); corr=(n-1)/N
    print(f"  n={n}: TV/[|X|/(2N)]={t/claim:.4f} (>1 = maxconf violated)  TV/[(n-1)/N]={t/corr:.4f} (<=1 = corrected holds)  2(n-1)/n={2*(n-1)/n:.4f}")
