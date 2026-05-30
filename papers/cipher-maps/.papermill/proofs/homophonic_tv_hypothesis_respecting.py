import math, random

def cell(D, c):
    X = list(D)
    K = {x: math.ceil(c*D[x]) for x in X}   # note: under hypothesis c>=1/minD, ceil(cD)>=1 automatically
    N = sum(K.values())
    tv = 0.5*sum(abs(D[x]-K[x]/N) for x in X)
    return tv, len(X)/(2*N), len(X)/N, N, K

random.seed(7)
viol_half = 0
viol_full = 0
worst_half = 0.0; wcase=None
trials=300000
checked=0
for _ in range(trials):
    n=random.randint(2,40)
    w=[random.expovariate(1.0) for _ in range(n)]
    s=sum(w); D={i:w[i]/s for i in range(n)}
    minD=min(D.values())
    c_min=1.0/minD
    # enforce hypothesis: c >= 1/min D. pick c as a multiple at/above c_min
    c=c_min*random.choice([1.0,1.0,1.5,2.0,5.0,20.0])
    checked+=1
    tv,bh,bf,N,K=cell(D,c)
    if tv>bh+1e-12:
        viol_half+=1
        r=tv/bh
        if r>worst_half: worst_half=r; wcase=(n,round(c,2),round(c_min,2),tv,bh,N)
    if tv>bf+1e-12:
        viol_full+=1

print(f"trials with hypothesis c>=1/minD enforced: {checked}")
print(f"violations of |X|/(2N): {viol_half}")
print(f"violations of |X|/N:    {viol_full}")
print(f"worst ratio TV/(|X|/(2N)): {worst_half:.6f}")
print(f"worst case (n,c,c_min,tv,bound_half,N): {wcase}")
