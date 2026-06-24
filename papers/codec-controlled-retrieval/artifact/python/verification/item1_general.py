"""ITEM 1 (general): is the realizable set characterized by the CLEAN conditions,
across several skewed codecs?  Clean conditions:
  - q dyadic prob vector, q(v) in {0} U {2^-r : 0<=r<=l_v};
  - value with all-zero codeword is ALWAYS hit (q>0);
  - mass >= codespace share: q(v)>0 => q(v) >= 2^-l_v;
  - ladder over hits: l(u)<=l(v) & both hit => q(u)>=q(v)  (subsumes equal-among-same-length).
Compare clean-candidate set to the enumerated realizable set R = {q(W): W subspace}.
"""
from fractions import Fraction
from itertools import combinations, product

def gf2_basis(vecs):
    piv = {}
    for b in vecs:
        for p in sorted(piv, reverse=True):
            if (b >> p) & 1: b ^= piv[p]
        if b: piv[b.bit_length()-1] = b
    return [piv[p] for p in sorted(piv, reverse=True)]
def gf2_span(basis):
    out=[0]
    for b in basis: out += [x^b for x in out]
    return out
def all_subspaces(M):
    univ=list(range(1<<M)); seen=set(); subs=[]
    for k in range(0,M+1):
        for combo in combinations(univ,k):
            s=frozenset(gf2_span(gf2_basis(list(combo))))
            if s not in seen: seen.add(s); subs.append(s)
    return subs

def analyze(name, M, codec):
    # codec: list of (vname, length, leftaligned_codeword_int)
    def mask_top(l):
        return (1<<M)-1 if l>=M else ((((1<<M)-1)>>(M-l))<<(M-l))
    vals=[v for (v,l,c) in codec]
    L={v:l for (v,l,c) in codec}; C={v:c for (v,l,c) in codec}
    order=sorted(vals, key=lambda v:(L[v],C[v]))  # prefix-free decode: shortest prefix wins
    def decode(x):
        for v in order:
            if (x & mask_top(L[v]))==(C[v] & mask_top(L[v])): return v
        return None
    def q_of(S):
        S=list(S); n=len(S); out={}
        for v in vals:
            m=mask_top(L[v]); out[v]=Fraction(sum(1 for x in S if (x&m)==(C[v]&m)), n)
        return tuple(out[v] for v in vals)
    R=set(q_of(S) for S in all_subspaces(M))

    def share(v): return Fraction(1,1<<L[v])
    def allowed(v):
        base=[Fraction(1,1<<r) for r in range(0,L[v]+1)]
        zero_cw = (C[v] & mask_top(L[v]))==0
        return base if zero_cw else [Fraction(0)]+base
    def ladder(q):
        idx={v:i for i,v in enumerate(vals)}
        hit=[(L[v],q[idx[v]]) for v in vals if q[idx[v]]>0]
        return all(q1>=q2 for (l1,q1) in hit for (l2,q2) in hit if l1<=l2)
    def mass_share(q):
        return all(q[i]==0 or q[i]>=share(vals[i]) for i in range(len(vals)))
    clean=set()
    for q in product(*[allowed(v) for v in vals]):
        if sum(q)==1 and mass_share(q) and ladder(q):
            clean.add(q)
    print(f"[{name}] M={M} codec={[(v,L[v]) for v in vals]}")
    print(f"   |R|={len(R)}  |clean|={len(clean)}  clean==R? {clean==R}")
    if clean!=R:
        for q in sorted(clean-R, key=lambda q:tuple(float(x) for x in q)):
            print(f"     CLEAN-but-UNREALIZABLE: {tuple(str(x) for x in q)}")
        for q in sorted(R-clean, key=lambda q:tuple(float(x) for x in q)):
            print(f"     REALIZABLE-but-not-clean: {tuple(str(x) for x in q)}")
    return clean==R

# canonical left-aligned codewords as ints (top bits), bit M-1 = MSB
res=[]
res.append(analyze("skew1233", 4, [('A',1,0b0000),('B',2,0b1000),('C',3,0b1100),('D',3,0b1110)]))
res.append(analyze("flat1_3333",3,[('A',1,0b000),('B',3,0b100),('C',3,0b101),('D',3,0b110),('E',3,0b111)]))
res.append(analyze("k122",2,[('A',1,0b00),('B',2,0b10),('C',2,0b11)]))
res.append(analyze("bal2222",2,[('A',2,0b00),('B',2,0b01),('C',2,0b10),('D',2,0b11)]))
res.append(analyze("mix2233",4,[('A',2,0b0000),('B',2,0b0100),('C',3,0b1000),('D',3,0b1010),('E',3,0b1100),('F',3,0b1110)]))
res.append(analyze("skew1244",4,[('A',1,0b0000),('B',2,0b1000),('C',4,0b1100),('D',4,0b1101),('E',4,0b1110),('F',4,0b1111)]))
print(f"\nclean conditions sufficient for ALL tested codecs? {all(res)}")
