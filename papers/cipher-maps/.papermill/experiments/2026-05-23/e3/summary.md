# E3 Replicated codec-security study

Run: 2026-05-27 12:52:45
Replicates per cell: 10
Trials per cell: 100000
Cells with theoretical prediction inside Wilson 95% CI: 23 / 25
Mean absolute gap (empirical mean - predicted): 0.0004
Max absolute gap: 0.0017

## Per-cell results

| codec | t | predicted | empirical mean | std | 95% CI | gap | in CI? |
|---|--:|--:|--:|--:|---|--:|:-:|
| Dense(M=3) | 1 | 0.5000 | 0.5000 | 0.0000 | [0.4969, 0.5031] | +0.0000 | yes |
| Dense(M=3) | 2 | 0.9375 | 0.9368 | 0.0014 | [0.9353, 0.9383] | -0.0007 | yes |
| Dense(M=3) | 3 | 0.9922 | 0.9925 | 0.0006 | [0.9920, 0.9930] | +0.0003 | yes |
| Dense(M=3) | 4 | 0.9990 | 0.9988 | 0.0002 | [0.9985, 0.9990] | -0.0002 | NO |
| Dense(M=3) | 5 | 0.9999 | 0.9999 | 0.0002 | [0.9998, 0.9999] | -0.0000 | yes |
| Dense(M=4) | 1 | 0.5000 | 0.5000 | 0.0000 | [0.4969, 0.5031] | +0.0000 | yes |
| Dense(M=4) | 2 | 0.8281 | 0.8265 | 0.0033 | [0.8241, 0.8288] | -0.0016 | yes |
| Dense(M=4) | 3 | 0.9102 | 0.9103 | 0.0023 | [0.9085, 0.9120] | +0.0001 | yes |
| Dense(M=4) | 4 | 0.9499 | 0.9497 | 0.0024 | [0.9483, 0.9510] | -0.0002 | yes |
| Dense(M=4) | 5 | 0.9718 | 0.9715 | 0.0017 | [0.9705, 0.9725] | -0.0003 | yes |
| Padded(M=4,v0) | 1 | 0.5000 | 0.5000 | 0.0000 | [0.4969, 0.5031] | +0.0000 | yes |
| Padded(M=4,v0) | 2 | 0.8281 | 0.8264 | 0.0035 | [0.8241, 0.8288] | -0.0017 | yes |
| Padded(M=4,v0) | 3 | 0.9102 | 0.9106 | 0.0025 | [0.9088, 0.9123] | +0.0004 | yes |
| Padded(M=4,v0) | 4 | 0.9499 | 0.9502 | 0.0031 | [0.9488, 0.9515] | +0.0003 | yes |
| Padded(M=4,v0) | 5 | 0.9718 | 0.9719 | 0.0019 | [0.9708, 0.9729] | +0.0000 | yes |
| Huffman(M=4,p_f) | 1 | 0.5000 | 0.5000 | 0.0000 | [0.4969, 0.5031] | +0.0000 | yes |
| Huffman(M=4,p_f) | 2 | 0.8555 | 0.8545 | 0.0023 | [0.8523, 0.8567] | -0.0010 | yes |
| Huffman(M=4,p_f) | 3 | 0.9358 | 0.9365 | 0.0030 | [0.9350, 0.9380] | +0.0007 | yes |
| Huffman(M=4,p_f) | 4 | 0.9686 | 0.9689 | 0.0016 | [0.9678, 0.9700] | +0.0003 | yes |
| Huffman(M=4,p_f) | 5 | 0.9844 | 0.9830 | 0.0015 | [0.9821, 0.9837] | -0.0014 | NO |
| AntiHuffman(M=4) | 1 | 0.5000 | 0.5000 | 0.0000 | [0.4969, 0.5031] | +0.0000 | yes |
| AntiHuffman(M=4) | 2 | 0.9141 | 0.9154 | 0.0021 | [0.9136, 0.9171] | +0.0013 | yes |
| AntiHuffman(M=4) | 3 | 0.9819 | 0.9816 | 0.0013 | [0.9807, 0.9824] | -0.0004 | yes |
| AntiHuffman(M=4) | 4 | 0.9958 | 0.9958 | 0.0007 | [0.9954, 0.9962] | -0.0000 | yes |
| AntiHuffman(M=4) | 5 | 0.9990 | 0.9991 | 0.0003 | [0.9988, 0.9992] | +0.0001 | yes |

## Inclusion decision (per design.md)

- Strong include (>= 28/30 in CI): section 10.6 Table 1 augmented with mean and CI columns; 'tight up to sampling noise' claim retained
- Weak include (24-28/30 in CI): present results honestly; identify which cells deviate and why
- Cut and re-investigate (< 24/30 in CI): theorem-vs-empirical gap is wider than the single-run paper claimed

This run: 23/25 cells in CI.
