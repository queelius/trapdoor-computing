# E4 Randomized-encoding defense validation (K sweep)

Run: 2026-05-27 12:50:55
Replicates per cell: 5
Total cells: 36

## Sub-hypothesis verification

### H1: under randomized encoding, pattern-coincidence TPR decreases with K

  t=2: Huffman pattern TPR vs M_bits = 4->0.5406, 5->0.2652, 6->0.1422, 7->0.0684, 8->0.0316 (monotone decreasing: True)
  t=3: Huffman pattern TPR vs M_bits = 4->0.4306, 5->0.1294, 6->0.0386, 7->0.0082, 8->0.0020 (monotone decreasing: True)
  t=4: Huffman pattern TPR vs M_bits = 4->0.4156, 5->0.1058, 6->0.0116, 7->0.0018, 8->0.0002 (monotone decreasing: True)

### H2: decode-coincidence accuracy is invariant under K

Max gap between canonical and random decode rates across all (codec, M, t) cells: 0.0114
H2 verdict (gap < 0.05 within sampling noise): PASS

### H3: Dense saturation (K=1 forced)

  Dense Dense(M=3) M=3 t=2: canonical pattern_tpr=1.0000, random pattern_tpr=1.0000, gap=0.0000
  Dense Dense(M=3) M=3 t=3: canonical pattern_tpr=1.0000, random pattern_tpr=1.0000, gap=0.0000
  Dense Dense(M=3) M=3 t=4: canonical pattern_tpr=1.0000, random pattern_tpr=1.0000, gap=0.0000

Max canonical-vs-random pattern TPR gap on Dense: 0.0000
H3 verdict (gap < 0.05): PASS

## Per-cell results (pattern-coincidence focus)

| codec | M | enc | t | pattern TPR mean (std) | pattern FPR mean (std) | pred TPR | pred FPR |
|---|--:|---|--:|---|---|--:|--:|
| Dense(M=3) | 3 | canonical | 2 | 1.0000 (0.0000) | 0.1241 (0.0071) | 1.0000 | 0.1250 |
| Dense(M=3) | 3 | canonical | 3 | 1.0000 (0.0000) | 0.0160 (0.0055) | 1.0000 | 0.0156 |
| Dense(M=3) | 3 | canonical | 4 | 1.0000 (0.0000) | 0.0019 (0.0013) | 1.0000 | 0.0020 |
| Dense(M=3) | 3 | random | 2 | 1.0000 (0.0000) | 0.1202 (0.0097) | 1.0000 | 0.1250 |
| Dense(M=3) | 3 | random | 3 | 1.0000 (0.0000) | 0.0142 (0.0023) | 1.0000 | 0.0156 |
| Dense(M=3) | 3 | random | 4 | 1.0000 (0.0000) | 0.0028 (0.0006) | 1.0000 | 0.0020 |
| Huffman(M=4) | 4 | canonical | 2 | 1.0000 (0.0000) | 0.0640 (0.0045) | 1.0000 | 0.0625 |
| Huffman(M=4) | 4 | canonical | 3 | 1.0000 (0.0000) | 0.0030 (0.0017) | 1.0000 | 0.0039 |
| Huffman(M=4) | 4 | canonical | 4 | 1.0000 (0.0000) | 0.0005 (0.0006) | 1.0000 | 0.0002 |
| Huffman(M=4) | 4 | random | 2 | 0.5406 (0.0056) | 0.0619 (0.0062) | 0.5317 | 0.0625 |
| Huffman(M=4) | 4 | random | 3 | 0.4306 (0.0206) | 0.0023 (0.0012) | 0.4381 | 0.0039 |
| Huffman(M=4) | 4 | random | 4 | 0.4156 (0.0069) | 0.0001 (0.0002) | 0.4090 | 0.0002 |
| Huffman(M=5) | 5 | canonical | 2 | 1.0000 (0.0000) | 0.0313 (0.0041) | 1.0000 | 0.0312 |
| Huffman(M=5) | 5 | canonical | 3 | 1.0000 (0.0000) | 0.0013 (0.0011) | 1.0000 | 0.0010 |
| Huffman(M=5) | 5 | canonical | 4 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0000 |
| Huffman(M=5) | 5 | random | 2 | 0.2652 (0.0178) | 0.0339 (0.0043) | 0.2756 | 0.0312 |
| Huffman(M=5) | 5 | random | 3 | 0.1294 (0.0149) | 0.0008 (0.0006) | 0.1457 | 0.0010 |
| Huffman(M=5) | 5 | random | 4 | 0.1058 (0.0117) | 0.0000 (0.0000) | 0.1058 | 0.0000 |
| Huffman(M=6) | 6 | canonical | 2 | 1.0000 (0.0000) | 0.0167 (0.0033) | 1.0000 | 0.0156 |
| Huffman(M=6) | 6 | canonical | 3 | 1.0000 (0.0000) | 0.0003 (0.0004) | 1.0000 | 0.0002 |
| Huffman(M=6) | 6 | canonical | 4 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0000 |
| Huffman(M=6) | 6 | random | 2 | 0.1422 (0.0091) | 0.0154 (0.0024) | 0.1378 | 0.0156 |
| Huffman(M=6) | 6 | random | 3 | 0.0386 (0.0081) | 0.0002 (0.0004) | 0.0364 | 0.0002 |
| Huffman(M=6) | 6 | random | 4 | 0.0116 (0.0031) | 0.0000 (0.0000) | 0.0132 | 0.0000 |
| Huffman(M=7) | 7 | canonical | 2 | 1.0000 (0.0000) | 0.0088 (0.0029) | 1.0000 | 0.0078 |
| Huffman(M=7) | 7 | canonical | 3 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0001 |
| Huffman(M=7) | 7 | canonical | 4 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0000 |
| Huffman(M=7) | 7 | random | 2 | 0.0684 (0.0111) | 0.0087 (0.0031) | 0.0689 | 0.0078 |
| Huffman(M=7) | 7 | random | 3 | 0.0082 (0.0036) | 0.0002 (0.0004) | 0.0091 | 0.0001 |
| Huffman(M=7) | 7 | random | 4 | 0.0018 (0.0011) | 0.0000 (0.0000) | 0.0017 | 0.0000 |
| Huffman(M=8) | 8 | canonical | 2 | 1.0000 (0.0000) | 0.0052 (0.0021) | 1.0000 | 0.0039 |
| Huffman(M=8) | 8 | canonical | 3 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0000 |
| Huffman(M=8) | 8 | canonical | 4 | 1.0000 (0.0000) | 0.0000 (0.0000) | 1.0000 | 0.0000 |
| Huffman(M=8) | 8 | random | 2 | 0.0316 (0.0053) | 0.0035 (0.0011) | 0.0344 | 0.0039 |
| Huffman(M=8) | 8 | random | 3 | 0.0020 (0.0019) | 0.0000 (0.0000) | 0.0023 | 0.0000 |
| Huffman(M=8) | 8 | random | 4 | 0.0002 (0.0004) | 0.0000 (0.0000) | 0.0002 | 0.0000 |

## Inclusion decision (per design.md)

- H1 monotone decrease in K: see per-t evidence above
- H2 PASS: True
- H3 PASS: True

Strong include if H1 + H2 + H3 all hold: new section 10.7 'Randomized-Encoding Defense at Scale' with two figures
Partial include if H1 holds but H2 or H3 fails: H1 part with caveat
Cut and re-investigate if H1 fails: revisit Proposition 8.2
