"""Verify saturation SUFFICIENCY broadly: for many codecs and many SATURATED stores,
every within-class redraw preserves the law (and saturation). Also confirm NECESSITY
is false (a non-saturated store invariant for all draws)."""
import random
from fractions import Fraction
from itertools import product

def gf2_basis(vs):
    piv={}
    for b in vs:
        for p in sorted(piv,reverse=True):
            if (b>>p)&1: b^=piv[p]
        if b: piv[b.bit_length()-1]=b
    return [piv[p] for p in sorted(piv,reverse=True)]
def gf2_span(B):
    o=[0]
    for b in B: o+=[x^b for x in o]
    return o
def gf2_rank(vs): return len(gf2_basis(vs))

def analyze(M, codec):
    # codec: [(name,length,leftaligned_codeword)]
    L={n:l for (n,l,c) in codec}; C={n:c for (n,l,c) in codec}
    order=sorted(L, key=lambda n:(L[n],C[n]))
    def mask(l): return (1<<M)-1 if l>=M else ((((1<<M)-1)>>(M-l))<<(M-l))
    def decode(x):
        for n in order:
            if (x&mask(L[n]))==(C[n]&mask(L[n])): return n
        return None
    def law(stored):
        sp=gf2_span(gf2_basis(list(stored))); h={n:0 for n in L}
        for x in sp: h[decode(x)]+=1
        return tuple(Fraction(h[n],len(sp)) for n in order)
    def proj_rank(stored,l):
        B=gf2_basis(list(stored)); m=mask(l); return gf2_rank([b&m for b in B])
    def saturated(stored):
        return all(proj_rank(stored,l)==l for l in set(L.values()))
    def members(n):
        base=C[n]; cnt=1<<(M-L[n]); return [base|i for i in range(cnt)]
    return L,C,order,law,saturated,members

codecs=[
 ("skew1233",4,[('A',1,0b0000),('B',2,0b1000),('C',3,0b1100),('D',3,0b1110)]),
 ("flat1_3333",3,[('A',1,0b000),('B',3,0b100),('C',3,0b101),('D',3,0b110),('E',3,0b111)]),
 ("mix2233",4,[('A',2,0b0000),('B',2,0b0100),('C',3,0b1000),('D',3,0b1010),('E',3,0b1100),('F',3,0b1110)]),
 ("huff5",5,[('A',1,0),('B',2,0b10000),('C',3,0b11000),('D',4,0b11100),('E',5,0b11110),('F',5,0b11111)]),
 ("k122",2,[('A',1,0),('B',2,0b10),('C',2,0b11)]),
]
rng=random.Random(99)
fail=0; checked=0
for nm,M,cd in codecs:
    L,C,order,law,saturated,members=analyze(M,cd)
    names=list(L)
    # build SATURATED stores: full support + random extra repeats
    for trial in range(40):
        store=list(names)+[rng.choice(names) for _ in range(rng.randint(0,4))]
        canon=[C[n] for n in store]
        if not saturated(canon):     # full support should be saturated; assert
            print(f"  [{nm}] full-support store NOT saturated?! store={store}"); fail+=1; continue
        q0=law(canon)
        # many random redraws; assert law invariant AND saturation preserved
        for _ in range(60):
            rp=[rng.choice(members(n)) for n in store]
            if law(rp)!=q0: print(f"  [{nm}] SAT-store law CHANGED store={store}"); fail+=1; break
            if not saturated(rp): print(f"  [{nm}] redraw broke saturation store={store}"); fail+=1; break
            checked+=1
print(f"saturation sufficiency: {checked} redraws checked, {fail} failures")

# necessity false: {A} alone on skew1233 is non-saturated but invariant for all draws
L,C,order,law,saturated,members=analyze(4,[('A',1,0b0000),('B',2,0b1000),('C',3,0b1100),('D',3,0b1110)])
store=['A','A']; canon=[C['A'],C['A']]
laws=set(law([a1,a2]) for a1 in members('A') for a2 in members('A'))
print(f"NECESSITY check: store {{A,A}} saturated={saturated(canon)}  distinct laws over all draws={len(laws)} -> {[tuple(str(x) for x in q) for q in laws]}")

# MONOTONICITY hypothesis: does redraw ever DECREASE rank pi_l(W)? If never, then
# saturation (full) is preserved trivially (full cannot increase or decrease).
print("\nMONOTONICITY test: can a redraw decrease rank pi_l(W) for any code length l?")
rng2=random.Random(5)
dec=0; tot=0
for nm,M,cd in codecs:
    L,C,order,law,saturated,members=analyze(M,cd)
    names=list(L)
    lengths=sorted(set(L.values()))
    for _ in range(300):
        store=[rng2.choice(names) for _ in range(rng2.randint(1,8))]
        canon=[C[n] for n in store]
        def prk(stored,l):
            B=gf2_basis(list(stored)); m=((1<<M)-1) if l>=M else ((((1<<M)-1)>>(M-l))<<(M-l))
            return gf2_rank([b&m for b in B])
        r0={l:prk(canon,l) for l in lengths}
        for _ in range(20):
            rp=[rng2.choice(members(n)) for n in store]
            for l in lengths:
                tot+=1
                if prk(rp,l) < r0[l]: dec+=1
print(f"  rank pi_l decreased in {dec} of {tot} (redraw, length) cases")
print(f"  => rank pi_l is monotone NON-DECREASING under redraw? {dec==0}")
