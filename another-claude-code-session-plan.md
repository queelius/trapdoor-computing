# Parallel-Session Work Plan

This file specifies remaining work that the **other Claude Code session**
(or the user manually) should apply. Written by the session that built
the cipher-maps experimental harness on 2026-04-29 and 2026-04-30.

The goal is two surgical additions to the entropy ratio paper plus a
scaffold for a new paper. Both sessions were touching the same files
in parallel and conflicting; this spec lets one session do the rest
without conflicts.

## What is already done (do not redo)

### `src/cipher-maps/`
- `LICENSE` (MIT) added.
- `experiments/` subpackage: `observer.py`, `tuning.py`, `adaptive_k.py`,
  `finite_sample.py`, `newsgroups_homophonic.py`,
  `online_adaptation.py`, with tests under `experiments/tests/`.
- `experiments/figures/` contains generated PNGs and CSVs:
  `fig1_empirical_tv.png`, `fig2_gap_vs_sqrt_ratio.png`,
  `newsgroups_homophonic.png`, `online_stationary.png`,
  `online_drift.png`, plus matching CSVs.
- Committed and pushed to `queelius/cipher-maps@8dd15e7`.

### `papers/maximizing-confidentiality/`
- `img/finite_sample_gap.png` copied in.
- `img/newsgroups_homophonic.png` copied in.
- `main.tex` has §5.4 "Finite-Sample Resolution of $\delta$" inserted
  after §5.3 "The Leakage Analyzer" (around line 1074). The subsection
  is complete: text, two equations, one figure include, paragraph on
  practical implication.

## What is NOT done (apply these)

### Step 1: ensure `graphicx` is loaded

**File**: `papers/maximizing-confidentiality/main.tex`.

The preamble currently does not include `\usepackage{graphicx}`, but
the inserted §5.4 (and the §6.4 to be inserted next) reference
`\includegraphics{...}` figures from `img/`. The build will fail
without graphicx.

**Find this block in the preamble (around line 7-9)**:

```latex
\usepackage{booktabs}
\usepackage{hyperref}
```

**Replace with**:

```latex
\usepackage{booktabs}
\usepackage{graphicx}
\graphicspath{{img/}}
\usepackage{hyperref}
```

If `\usepackage{graphicx}` is already present, skip this step.

### Step 2: insert §6.4 (homophonic on 20NG)

**File**: `papers/maximizing-confidentiality/main.tex`.

**Anchor**: find the end of `\subsection{Encoding Granularity}` inside
`\section{Experimental Results}`. The last line of that subsection is:

```latex
the trade-off: 3 exposed values, 64.2 bits per element.
```

This sits immediately before `\subsection{Case Study: Confidentiality
Improvement}`.

**Insert after that line, before the Case Study subsection**, the
following text exactly:

```latex

\subsection{Homophonic Encoding on the 20 Newsgroups Corpus}
\label{subsec:newsgroups-homophonic}

We apply the proportional homophonic prescription
(Theorem~\ref{thm:multiplicity}) to the empirical word-frequency
distribution of the 20 Newsgroups training split.  Tokenising the
2.31\,M word corpus and retaining the top 500 most frequent words
gives a vocabulary in which the head word \emph{the} carries 7.1\%
of probability mass, the top ten words 33\%, and the top hundred
74\%.  The effective vocabulary $1/\sum_x D(x)^2$ is 64, so the
distribution is highly skewed even after tail truncation.

We compare three allocators across budgets $\sum K \in
\{|X|, 2|X|, 5|X|, 20|X|, 100|X|\}$: the uniform baseline
($K(x) = b/|X|$), the proportional homophonic
($K(x) \propto D(x)$), and a sub-optimal square-root variant
($K(x) \propto \sqrt{D(x)}$).  For each cell we build a fresh
\texttt{PHFCipherMap}, stream $N = 30{,}000$ queries sampled from
$D$, and record predicted and empirical TV
(Fig.~\ref{fig:newsgroups-homophonic}).

\begin{figure}[ht]
\centering
\includegraphics[width=\linewidth]{newsgroups_homophonic}
\caption{Homophonic encoding on the 20 Newsgroups distribution.
Left: representation uniformity $\TV(Q, U_{\mathrm{im}})$ versus
budget for the three allocators (solid: predicted; dashed:
empirical at $N=30{,}000$).  Right: lower bound on the entropy
ratio $e$ from the Fannes-Audenaert inequality.  Proportional
allocation dominates uniform and square-root at every budget.}
\label{fig:newsgroups-homophonic}
\end{figure}

The proportional allocator drops predicted $\TV$ from $0.545$ at
$\sum K = |X|$ (no flexibility) to $0.165$ at $2|X|$ and $0.021$
at $5|X|$, with empirical $e$ rising from $0.40$ to $0.85$.  The
square-root allocator plateaus near $\TV \approx 0.30$ regardless
of budget; it spreads representations too evenly across rare and
common elements.  The uniform allocator does not improve at all,
since its $K$ does not depend on $D$.  At budgets above $20|X|$,
the empirical $\TV$ measurement enters the finite-sample regime
of \S\ref{subsec:finite-sample}: the analytical floor continues
to drop, but $N = 30{,}000$ is no longer enough queries to
resolve it.

```

### Step 3: build the paper

```bash
cd /home/spinoza/github/trapdoor-computing/papers/maximizing-confidentiality
make
# or: pdflatex main && bibtex main && pdflatex main && pdflatex main
```

Confirm:
- `main.pdf` builds cleanly.
- §5.4 appears with `finite_sample_gap.png`.
- §6.4 appears with `newsgroups_homophonic.png`.
- Page count grew from ~17pp to ~19pp.

If references to `\ref{thm:multiplicity}` or `\ref{subsec:finite-sample}`
break, check that the existing labels match those names. The theorem
label should already exist; the §5.4 label was inserted along with the
subsection.

### Step 4: scaffold the new paper

Create directory `papers/adaptive-trapdoor-computing/` with the
following structure and contents.

```
papers/adaptive-trapdoor-computing/
  README.md
  CLAUDE.md
  notes/
    motivation.md
    preliminary-results.md
    open-questions.md
    plan.md
    related-work.md
  paper/
    main.tex
    references.bib
    Makefile
  .papermill/
    state.md
```

#### `README.md`

```markdown
# Adaptive Trapdoor Computing

Paper draft on maintaining confidentiality in trapdoor systems
under distributional drift.

The cipher map framework treats $K(x)$, the per-element
representation count, as a design-time parameter chosen for a
fixed query distribution $D$. Real systems see $D$ drift over
time: vocabulary, popularity, seasonal patterns. A static $K(x)$
fitted to old $D$ becomes badly mismatched, and confidentiality
($\delta$, equivalently $e$) degrades.

This paper develops:

1. A streaming observer for empirical $\hat D$.
2. Online retuning of $K(x)$ from $\hat D$.
3. Cadence theory: when to retune (regret bounds).
4. Secret-preserving retune algorithm (library extension).
5. Empirical evaluation on real drift datasets.

See `notes/` for motivation, preliminary results, and the open
questions blocking publication.

Status: idea / preliminary. Drafting blocked on the items in
`notes/open-questions.md`.

## Author

Alexander Towell, lex@metafunctor.com
```

#### `CLAUDE.md`

```markdown
# CLAUDE.md (adaptive-trapdoor-computing)

## What this paper is

A follow-on to "The Entropy Ratio" (`papers/maximizing-confidentiality/`).
That paper develops a static confidentiality theory: $\delta$ is a
fixed property of an allocation $K(x)$ over a fixed distribution $D$.

This paper makes confidentiality dynamic: $D$ drifts, $K$ must adapt,
and the question is how fast and at what cost.

## Status

Stage: idea. Preliminary experiments live in
`~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py`
with results in `notes/preliminary-results.md`.

## What this paper is NOT

- It is not about secret rotation. That is `papers/cipher-rekeying/`.
- It is not about confidentiality measurement (covered by the
  Entropy Ratio paper, including the finite-sample subsection).
- It is not about general adversarial adaptation. The threat model
  is honest-but-curious untrusted machine plus naturally drifting D,
  not active drift induced by an adversary.

## Sibling papers and load order

- `papers/cipher-maps/`: framework definition.
- `papers/algebraic-cipher-types/`: type constructors and orbit closure.
- `papers/maximizing-confidentiality/`: static confidentiality theory.
- `papers/cipher-rekeying/`: secret rotation.
- This paper: distributional adaptation.

A reader needs the Entropy Ratio paper as background; the others are
not strict prerequisites.

## Build

```bash
cd paper && make
```

(stub Makefile is the standard pdflatex+bibtex+pdflatex+pdflatex chain).
```

#### `notes/motivation.md`

```markdown
# Motivation

## The static-confidentiality hole

The Entropy Ratio paper assumes a fixed query distribution $D$. The
homophonic prescription $K(x) = \lceil c \cdot D(x) \rceil$ is
optimal at design time. But:

- Vocabulary changes over time. New terms appear; old terms fall out
  of use.
- Per-user distributions differ from population distributions and
  are unknown at design time.
- Concept drift: even at fixed vocabulary, the popularity ordering
  shifts (news topics, seasonal patterns, query trends).
- Threat surface shifts: an adversary may probe more frequently
  along an axis the system was not tuned for.

A $K(x)$ tuned for $D_0$ is mismatched against $D_t$. Confidentiality
$e$ drops. The system was secure when deployed but is no longer
secure now.

## What this paper says

Operational confidentiality is a maintained property, not a delivered
one. The trusted machine must:

1. Observe the query stream and estimate $\hat{D}$.
2. Detect when $\hat{D}$ has drifted enough to warrant retuning.
3. Retune $K(x)$ from the current estimate.
4. Apply the retuning without invalidating already-emitted ciphertext.

Each step has a cost (observation budget, decision threshold, retune
overhead, cryptographic care).

## Why now

The cipher-maps Python library and its experiments harness
(2026-04-29) make the empirical work tractable: the observer,
allocator strategies, and online loop already exist as
`experiments/online_adaptation.py`. Preliminary results show that
the phenomenon is real and quantifiable, and they identify the
specific blocker (no secret-preserving retune in the library).

## Sibling/contrast

- Cipher rekeying (`papers/cipher-rekeying/`) addresses secret
  rotation: the secret changes, latent values stay, $K(x)$ stays.
- Adaptive trapdoor (this paper) addresses allocation retuning: the
  secret stays, latent values stay, $K(x)$ changes.

Both can compose. A deployed system may rotate keys quarterly and
retune $K(x)$ daily.
```

#### `notes/preliminary-results.md`

```markdown
# Preliminary Results

All numbers come from
`~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py`.
Re-run with:

```bash
cd ~/github/trapdoor-computing/src/cipher-maps
python -m experiments.online_adaptation --scenario both --n-queries 30000 --seed 42
```

## Stationary scenario

Setup: Zipf$(64, \alpha=1.5)$, budget = 1024, batch size 1500, retune
every batch, smoothing $\alpha = 1$.

| Cumulative queries | predicted_tv (oracle) | empirical_e (oracle) |
|---|---|---|
| 4500   | 0.0365 | 0.604 |
| 10500  | 0.0217 | 0.594 |
| 16500  | 0.0157 | 0.608 |
| 22500  | 0.0163 | 0.608 |
| 28500  | 0.0140 | 0.598 |

Predicted TV against the oracle distribution decreases monotonically
as more queries arrive. The algorithm is learning $D$ and tuning
$K(x)$ progressively closer to the analytical optimum.

## Drift scenario

Setup: same as stationary, but the true distribution shifts from
Zipf$(\alpha = 2.0)$ to Zipf$(\alpha = 1.0)$ at cumulative queries
$\approx 15{,}000$.

| Cumulative | predicted_tv (oracle) | empirical_e |
|---|---|---|
| 4500   | 0.042 | 0.607 |
| 10500  | 0.034 | 0.588 |
| 16500  | 0.434 | 0.406 |  <-- drift hits, K(x) is now stale
| 22500  | 0.321 | 0.500 |
| 28500  | 0.250 | 0.548 |

At the drift point predicted TV jumps from $0.034$ to $0.434$, a
12-fold degradation. Adaptive retuning recovers part of this within
two batches but the system has spent ~6000 queries in degraded
confidentiality.

This is the central phenomenon the paper formalizes: stale $K(x)$
under drift produces a measurable confidentiality crater whose
depth scales with the drift magnitude and whose width scales with
the retune cadence.

## Figures (already generated)

In `~/github/trapdoor-computing/src/cipher-maps/experiments/figures/`:

- `online_stationary.png`: stationary trajectory.
- `online_drift.png`: drift trajectory with vertical drift marker.
- `newsgroups_homophonic.png`: cross-strategy benchmark on 20NG
  (also referenced by the Entropy Ratio paper).
- `fig1_empirical_tv.png`, `fig2_gap_vs_sqrt_ratio.png`:
  finite-sample bias on synthetic Zipf.
```

#### `notes/open-questions.md`

```markdown
# Open Questions Blocking Publication

These are the items that must be resolved before the paper can be
written up.

## 1. Secret-preserving retune (library)

Currently the experiments rebuild the cipher map from scratch on
every retune step. A real deployed system cannot do that without
invalidating already-emitted cipher values. The fix:

- Add `PHFCipherMap.retune_k(new_k_input_fn)` to cipher-maps.
- The method preserves `enc_key`, `decode_secret`, `scramble_key`.
- It rebuilds the PHF and slot table for the new (x, rep) keys.
- Old cipher values, encoded with the old $K(x)$, must still
  decode under the new map (their (x, rep) keys are still valid).

Theoretical question: does retuning preserve confidentiality
guarantees on old cipher values? (The new cipher map can decode
them, but does the orbit-closure bound apply to the union of old
and new cipher spaces?)

Estimated work: 1-2 days for the library feature, plus 1 week to
work out the information-theoretic accounting.

## 2. Real distribution drift datasets

Synthetic Zipf-shift is an existence proof. Reviewers will ask for
real corpus drift. Candidates:

- 20 Newsgroups split by topic (induced drift across categories).
- Reddit comments split by month or year.
- Query logs with explicit timestamps (AOL? MSN? a more recent log?).
- News article frequencies by day (Wikipedia pageviews? Common
  Crawl?).

For each, characterize: drift rate (KL divergence over time),
stationarity assumption, vocabulary stability.

## 3. Retune cadence theory

When should retuning fire?

Options:
- Every batch (naive, expensive).
- Threshold on $\TV(\hat D_t, \hat D_{t-k})$.
- Adaptive doubling-period schedules.
- Sequential change-point detection (CUSUM, online Bayes).

Need: regret bound. If we retune at times $t_1, t_2, \ldots$, what
is the average $\delta$ over time? How does it depend on the cadence
strategy and the drift process?

## 4. Adversarial drift

The paper threat model assumes natural drift. But an adversary may
deliberately shift its query pattern to widen the staleness window.
- Is this a meaningful attack? Quantify the leakage.
- Is the defence the same (faster retuning) or different (drift-
  detection that distinguishes natural vs adversarial)?

This may be a separate follow-on paper.

## 5. Composition with secret rotation

If both rekeying (`papers/cipher-rekeying/`) and retuning happen,
do they compose? When?
- A retune that does not change the secret is straightforward.
- A rekey that does not change $K(x)$ is straightforward.
- Doing both at once: order matters?
```

#### `notes/plan.md`

```markdown
# Plan

## Section sketch (12-15pp target)

1. Introduction (1.5pp)
   - Static confidentiality is the wrong abstraction for deployed
     systems. Drift exists. Tuning becomes stale. Operational
     confidentiality must be maintained.

2. Background (1pp)
   - Cipher map basics; refer to cipher-maps paper.
   - Entropy ratio and homophonic prescription; refer to The Entropy
     Ratio.

3. Formal model: drift and staleness (2pp)
   - $D_t$ is a process. $K_t$ is the active allocation.
   - Define $\delta_t$ and $e_t$ as functions of time.
   - Define drift magnitude and staleness window.

4. Online observation and tuning (3pp)
   - Streaming observer (empirical $\hat D$ with smoothing).
   - Allocators (refer to experiments/tuning.py).
   - Retune cadence: naive, threshold, change-point.

5. Secret-preserving retune (3pp)
   - The retune algorithm (library extension).
   - Theorem: confidentiality of old cipher values under the new
     map. Bound via orbit closure of the joint cipher space.

6. Experiments (3pp)
   - Synthetic drift (Zipf alpha shift).
   - Real-corpus drift (TBD which dataset).
   - Cadence comparison.
   - Cost (retune budget vs $\delta$ trajectory).

7. Discussion (1pp)
   - Composition with rekeying.
   - Adversarial drift (open question).

8. Related work (1pp)
9. Conclusion (0.5pp)

## Order of work

1. Library feature (retune_k method) and tests.
2. Real-drift dataset selection and preprocessing.
3. Cadence experiments.
4. Theory: regret bounds, orbit-closure extension.
5. Drafting.

Estimated total: 1-2 months focused.
```

#### `notes/related-work.md`

```markdown
# Related Work to Survey

## Internal (cite directly)

- `cipher-maps`: framework and four properties.
- `algebraic-cipher-types`: orbit closure bound (extends here).
- `maximizing-confidentiality` ("The Entropy Ratio"): static $\delta$,
  homophonic prescription.
- `cipher-rekeying`: sibling paper on secret rotation.

## External

### Concept drift
- Gama et al. (2014). "A survey on concept drift adaptation." ACM CS.
- Lu et al. (2018). "Learning under Concept Drift." IEEE TKDE.

### Online learning under non-stationarity
- Cesa-Bianchi & Lugosi (2006). Prediction, Learning, and Games.
- Adaptive regret bounds (Hazan, Seshadhri 2009).

### Searchable encryption with dynamic data
- Bost et al. (2017). "Forward and backward private searchable
  encryption." CCS.
- Compare: dynamic SSE updates the index when documents change;
  this paper updates the encoding when the query distribution
  changes.

### Differential privacy under drift
- Composition theorems with renewable budgets.
- Less directly relevant but worth a paragraph for contrast.

### Information-theoretic security under non-stationarity
- Sparse literature here. May be a contribution opportunity.
```

#### `paper/main.tex` (skeleton)

```latex
\documentclass[11pt]{article}

% Essential packages
\usepackage[margin=1in]{geometry}
\usepackage{amsmath,amssymb,amsthm}
\usepackage{mathtools}
\usepackage[numbers,square]{natbib}
\usepackage{booktabs}
\usepackage{graphicx}
\graphicspath{{img/}}
\usepackage{hyperref}
\hypersetup{hypertexnames=false}
\usepackage{cleveref}

% Theorem environments (matching sibling papers)
\theoremstyle{definition}
\newtheorem{definition}{Definition}[section]
\theoremstyle{plain}
\newtheorem{theorem}{Theorem}[section]
\newtheorem{lemma}[theorem]{Lemma}
\newtheorem{corollary}[theorem]{Corollary}
\newtheorem{proposition}[theorem]{Proposition}
\theoremstyle{remark}
\newtheorem{remark}{Remark}[section]
\newtheorem{example}{Example}[section]

% Notation (matching cipher-maps paper)
\newcommand{\fhat}{\hat{f}}
\newcommand{\enc}{\mathrm{enc}}
\newcommand{\dec}{\mathrm{dec}}
\newcommand{\im}{\mathrm{Im}}
\newcommand{\TV}{d_{\mathrm{TV}}}
\newcommand{\B}{\{0,1\}}

\title{Adaptive Trapdoor Computing:\\
Maintaining Confidentiality Under Distributional Drift}
\author{Alexander Towell\\\texttt{lex@metafunctor.com}}
\date{\today}

\begin{document}
\maketitle

\begin{abstract}
TODO. Static confidentiality assumes a fixed query distribution.
Real systems see drift. We develop online observation and retuning
of the homophonic allocation $K(x)$, prove a regret bound on average
confidentiality, and present a secret-preserving retune algorithm
that maintains validity of already-emitted cipher values. We
evaluate on TBD real drift dataset.
\end{abstract}

\section{Introduction}
TODO. See notes/plan.md.

\section{Background}
TODO. Cite cipher-maps and The Entropy Ratio.

\section{Drift and Staleness: Formal Model}
TODO.

\section{Online Tuning}
TODO. Describe observer, allocators, cadence.

\section{Secret-Preserving Retune}
TODO. Algorithm + correctness theorem.

\section{Experiments}
TODO. Synthetic + real drift.

\section{Discussion}
TODO.

\section{Related Work}
TODO. See notes/related-work.md.

\section{Conclusion}
TODO.

\bibliographystyle{plainnat}
\bibliography{references}

\end{document}
```

#### `paper/Makefile`

```makefile
TARGET = main
PDF = $(TARGET).pdf

.PHONY: all clean quick

all: $(PDF)

$(PDF): $(TARGET).tex references.bib
	pdflatex -interaction=nonstopmode $(TARGET)
	bibtex $(TARGET) || true
	pdflatex -interaction=nonstopmode $(TARGET)
	pdflatex -interaction=nonstopmode $(TARGET)

quick: $(TARGET).tex
	pdflatex -interaction=nonstopmode $(TARGET)

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.toc *.fls *.fdb_latexmk
```

#### `paper/references.bib` (stub)

```bibtex
@misc{towell2026ciphermaps,
  author       = {Alexander Towell},
  title        = {Cipher Maps: A Unified Framework for Oblivious Function
                  Approximation},
  year         = {2026},
  howpublished = {Manuscript},
  note         = {Sibling paper}
}

@misc{towell2026entropyratio,
  author       = {Alexander Towell},
  title        = {The Entropy Ratio: Quantitative Confidentiality for
                  Trapdoor Computing},
  year         = {2026},
  howpublished = {Manuscript}
}

@misc{towell2026rekeying,
  author       = {Alexander Towell},
  title        = {Cipher Rekeying},
  year         = {2026},
  howpublished = {Manuscript}
}

@article{gama2014concept,
  author = {Gama, Joao and Zliobaite, Indre and Bifet, Albert and
            Pechenizkiy, Mykola and Bouchachia, Abdelhamid},
  title  = {A Survey on Concept Drift Adaptation},
  journal = {ACM Computing Surveys},
  volume = {46},
  number = {4},
  year   = {2014}
}
```

#### `.papermill/state.md`

```yaml
---
title: "Adaptive Trapdoor Computing"
stage: idea
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Operational confidentiality of a trapdoor system is a maintained
    property under distributional drift, not a delivered one. Online
    observation and retuning of K(x) keep delta near its analytical
    optimum at a query-budget cost, with secret-preserving retune
    keeping already-emitted ciphertext valid."
  novelty: "Drift-aware confidentiality theory. None of the existing
    cipher-maps / algebraic-types / entropy-ratio / rekeying papers
    address temporal dynamics."
  refined: ""

prior_art:
  last_survey: null
  key_references:
    - cipher-maps (sibling)
    - The Entropy Ratio (sibling, prerequisite)
    - cipher-rekeying (sibling)
    - Gama et al. 2014 (concept drift)

experiments:
  preliminary:
    location: ~/github/trapdoor-computing/src/cipher-maps/experiments/online_adaptation.py
    figures: experiments/figures/online_stationary.png, online_drift.png
    finding: "Drift jumps predicted TV from 0.034 to 0.434 instantly;
      adaptive retuning recovers it to 0.25 within two batches."
  needed:
    - real drift dataset
    - cadence comparison
    - secret-preserving retune validation

venue:
  target: null
  candidates:
    - PoPETs
    - CCS (workshop)
    - ESORICS

review_history: []

next_action: "Implement PHFCipherMap.retune_k() in the cipher-maps
  library; pick a real drift dataset; draft the formal model section."
---
```

## Step 5: commit

After applying steps 1-4, commit at the **trapdoor-computing** repo
root:

```bash
cd /home/spinoza/github/trapdoor-computing
git add papers/maximizing-confidentiality/main.tex
git add papers/maximizing-confidentiality/img/finite_sample_gap.png
git add papers/maximizing-confidentiality/img/newsgroups_homophonic.png
git add papers/adaptive-trapdoor-computing/
git add another-claude-code-session-plan.md
git commit -m "$(cat <<'MSGEOF'
Entropy Ratio: add finite-sample and 20NG subsections; scaffold adaptive paper

Two surgical additions to maximizing-confidentiality:
- Section 5.4: Finite-Sample Resolution of delta (Glivenko-Cantelli
  bound on empirical TV measurement; gap fits 0.4 sqrt(|im|/N))
- Section 6.4: Homophonic Encoding on 20 Newsgroups (real corpus
  validation of the multiplicity theorem)

Scaffold for a future paper on adaptive trapdoor computing under
distributional drift. Notes, paper skeleton, and papermill state
populated; no draft text yet. The drift result motivating this paper
came from cipher-maps experiments/online_adaptation.py.

Co-Authored-By: Claude Opus 4.7 (1M context) <noreply@anthropic.com>
MSGEOF
)"
```

## Notes for the executing session

- Step 1 (graphicx) is critical. Step 2 will fail silently or with
  ugly errors if the package is not loaded.
- Step 2 anchor text is unique in the file; a simple find-and-replace
  on the anchor block is safe.
- Step 4 contents should be created verbatim from this spec. The
  intent is for the future-self researcher to be able to resume
  cold from these notes.
- Steps are independent; partial application is fine. If only steps
  1-3 are applied, the entropy ratio paper is still publication-ready;
  the new-paper scaffold can come later.
