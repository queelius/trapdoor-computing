"""ITEM 2: is skewed randomized-encoding invariance true? Ground-truth check."""
from fractions import Fraction
from itertools import product
from gf2 import CODE, ORDER, law, class_hits_and_W

def class_members(v):
    from gf2 import mask_top, M
    l, cw = CODE[v]
    m = mask_top(l)
    return [x for x in range(1 << M) if (x & m) == (cw & m)]

print("=" * 70)
print("ITEM 2: skewed randomized-encoding invariance")
print("=" * 70)

# --- The candidate counterexample: store {A,A,B} (A twice, no C,D) ---
store = ['A', 'A', 'B']
canon = [CODE[v][1] for v in store]   # [0,0,8]
q_canon = law(canon)
print(f"\nStore {store}  (A length-1 stored TWICE, B once, C/D unstored)")
print(f"canonical patterns {canon} -> q = {tuple(str(x) for x in q_canon)}")

# enumerate ALL within-class re-encodings (A in class(A), A in class(A), B in class(B))
A_opts = class_members('A')   # {0..7}
B_opts = class_members('B')   # {8..11}
laws = {}
for a1, a2, b in product(A_opts, A_opts, B_opts):
    q = law([a1, a2, b])
    laws.setdefault(q, 0)
    laws[q] += 1

distinct = sorted(laws, key=lambda q: tuple(float(x) for x in q))
print(f"\ndistinct realized laws over ALL {len(A_opts)**2 * len(B_opts)} within-class draws: {len(distinct)}")
for q in distinct:
    flag = "  <- canonical" if q == q_canon else ""
    print(f"   q = {tuple(str(x) for x in q)}   count={laws[q]}{flag}")

broke = [q for q in distinct if q != q_canon]
print(f"\nINVARIANCE HOLDS for all draws? {len(broke) == 0}")
if broke:
    # exhibit one explicit breaking draw
    for a1, a2, b in product(A_opts, A_opts, B_opts):
        if law([a1, a2, b]) != q_canon:
            h, W = class_hits_and_W([a1, a2, b])
            print(f"COUNTEREXAMPLE draw A1={a1:04b} A2={a2:04b} B={b:04b}: "
                  f"q = {tuple(str(x) for x in law([a1,a2,b]))}  (|W|={W}, hits={h})")
            break
    print("=> the deferred skewed-invariance lemma is FALSE in general.")

# --- The saturation regime the TESTS exercise: full support {A,B,C,D,...} ---
print("\n" + "-" * 70)
print("Full-support store (the regime the existing tests use): every value present")
store2 = ['A', 'B', 'C', 'D', 'A', 'A', 'B']     # the test's base_seq
canon2 = [CODE[v][1] for v in store2]
q2 = law(canon2)
print(f"store {store2} -> canonical q = {tuple(str(x) for x in q2)}")
opts = {v: class_members(v) for v in ORDER}
import random
rng = random.Random(2026)
sat_laws = set()
for _ in range(20000):
    pats = [rng.choice(opts[v]) for v in store2]
    sat_laws.add(law(pats))
print(f"distinct laws over 20000 random within-class draws: {len(sat_laws)}")
print(f"INVARIANT under full support? {sat_laws == {q2}}")

# confirm WHY: every code length's projection is already full
from gf2 import gf2_basis, M
def proj_rank(W_basis, l):
    from gf2 import mask_top, gf2_rank
    m = mask_top(l)
    return gf2_rank([w & m for w in W_basis])
Wb = gf2_basis(canon2)
print("per-length projection ranks (full = saturated):",
      {l: f"{proj_rank(Wb,l)}/{l}" for l in sorted({CODE[v][0] for v in ORDER})})
