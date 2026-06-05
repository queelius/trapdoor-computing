# E4: coincidence-oracle attack (corrected direction)

K = 8 values, t = 1..8, trials = 100000 member + 100000 non-member per rep, reps = 10, seed = 2026.

Attacker accuracy `acc(t) = 1 - (1/2) * sum_v alpha(v)^t`. HIGHER acc = WORSE defense.

| codec                |  t | acc_closed |     acc_mc |                mc_95%_ci | in CI? |
|----------------------|----|------------|------------|--------------------------|--------|
| uniform              |  1 |   0.500000 |   0.500000 |     [0.500000, 0.500000] |    yes |
| uniform              |  2 |   0.937500 |   0.937528 |     [0.937114, 0.937942] |    yes |
| uniform              |  3 |   0.992188 |   0.992267 |     [0.992169, 0.992365] |    yes |
| uniform              |  4 |   0.999023 |   0.999029 |     [0.998988, 0.999070] |    yes |
| uniform              |  5 |   0.999878 |   0.999875 |     [0.999863, 0.999886] |    yes |
| uniform              |  6 |   0.999985 |   0.999987 |     [0.999983, 0.999992] |    yes |
| uniform              |  7 |   0.999998 |   0.999999 |     [0.999997, 1.000000] |    yes |
| uniform              |  8 |   1.000000 |   1.000000 |     [0.999999, 1.000000] |    yes |
|----------------------|----|------------|------------|--------------------------|--------|
| huffman              |  1 |   0.500000 |   0.500000 |     [0.500000, 0.500000] |    yes |
| huffman              |  2 |   0.833313 |   0.833141 |     [0.832617, 0.833665] |    yes |
| huffman              |  3 |   0.928571 |   0.928628 |     [0.928344, 0.928912] |    yes |
| huffman              |  4 |   0.966667 |   0.966713 |     [0.966545, 0.966881] |    yes |
| huffman              |  5 |   0.983871 |   0.983961 |     [0.983855, 0.984067] |    yes |
| huffman              |  6 |   0.992063 |   0.992133 |     [0.991993, 0.992274] |    yes |
| huffman              |  7 |   0.996063 |   0.996071 |     [0.996009, 0.996134] |    yes |
| huffman              |  8 |   0.998039 |   0.998007 |     [0.997941, 0.998074] |    yes |
|----------------------|----|------------|------------|--------------------------|--------|
| intermediate_zipf    |  1 |   0.500000 |   0.500000 |     [0.500000, 0.500000] |    yes |
| intermediate_zipf    |  2 |   0.876197 |   0.876663 |     [0.876302, 0.877023] |    yes |
| intermediate_zipf    |  3 |   0.956116 |   0.956046 |     [0.955840, 0.956252] |    yes |
| intermediate_zipf    |  4 |   0.982396 |   0.982546 |     [0.982441, 0.982652] |    yes |
| intermediate_zipf    |  5 |   0.992641 |   0.992692 |     [0.992531, 0.992854] |    yes |
| intermediate_zipf    |  6 |   0.996877 |   0.996897 |     [0.996810, 0.996984] |    yes |
| intermediate_zipf    |  7 |   0.998667 |   0.998666 |     [0.998619, 0.998713] |    yes |
| intermediate_zipf    |  8 |   0.999430 |   0.999426 |     [0.999401, 0.999452] |    yes |
|----------------------|----|------------|------------|--------------------------|--------|
| intermediate_padded  |  1 |   0.500000 |   0.500000 |     [0.500000, 0.500000] |    yes |
| intermediate_padded  |  2 |   0.594286 |   0.594546 |     [0.594297, 0.594796] |    yes |
| intermediate_padded  |  3 |   0.635490 |   0.635221 |     [0.634740, 0.635702] |    yes |
| intermediate_padded  |  4 |   0.671950 |   0.671853 |     [0.671296, 0.672411] |    yes |
| intermediate_padded  |  5 |   0.704755 |   0.704623 |     [0.704098, 0.705148] |    yes |
| intermediate_padded  |  6 |   0.734279 |   0.734053 |     [0.733490, 0.734616] |    yes |
| intermediate_padded  |  7 |   0.760852 |   0.760878 |     [0.760583, 0.761172] |    yes |
| intermediate_padded  |  8 |   0.784766 |   0.785012 |     [0.784518, 0.785506] |    yes |
|----------------------|----|------------|------------|--------------------------|--------|

At t=4: uniform acc = 0.99902 (worst defense), huffman acc = 0.96667 (best defense).

CORRECTED DIRECTION: for every t >= 2 the concentrated / Huffman codec has the LOWEST attacker accuracy (best defense) and uniform the HIGHEST (worst defense). The 'uniform defends best' reading (bernoulli RESULTS_14.md pre-fix state, cipher-maps section 10.6) is inverted and wrong.

