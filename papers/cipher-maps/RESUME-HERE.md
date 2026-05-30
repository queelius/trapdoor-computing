# Resume here (cipher-maps)

Paused 2026-05-30 mid-session because the tooling channel became
intermittently unreliable (stale/out-of-order tool output; same file
read two ways gave two answers). NOTHING IS DAMAGED: all files are
intact and committed; the paper builds. The pause is only because
precise exact-match edits were unsafe through a flaky channel. Resume
in a fresh session anytime; there is no decay or deadline.

## Paper state

- HEAD: commit 07df47d. cipher_maps.tex builds clean, 39 pages.
- The theorem content is correct. In particular Proposition
  prop:homophonic (homophonic allocation) is right: it states the
  exact identity TV(Q, U_im) = (1/2) sum_x |D(x) - K(x)/N| = TV(D, K/N)
  and the rigorous bound TV < |X|/N. Both proven by hand, no numerics.

## Two open items

### 1. ONE known-false sentence to delete (small, do first)

In cipher_maps.tex, in the prose right AFTER the homophonic
Proposition's proof, there is a trailing paragraph ending with:

    "... populated by totality (Property~1) and noise injection
    (\S\ref{sec:trust-model}).  Tighter constants under additional
    budget hypotheses are developed in the companion entropy-ratio
    work~\cite{towell2026maxconf}."

DELETE the final sentence ("Tighter constants under additional budget
hypotheses are developed in the companion entropy-ratio
work~\cite{towell2026maxconf}."). It implies maxconf has a verified
tighter bound, which is the UNRESOLVED question in item 2. End the
paragraph at "noise injection (\S\ref{sec:trust-model})."

To locate it cleanly in a fresh session:
    grep -n "Tighter constants under additional" paper/cipher_maps.tex
(it sits just before "\begin{remark}[Marginal uniformity only]").

Then `make`, confirm clean build, commit.

### 2. Settle the maxconf multiplicity constant ANALYTICALLY

Open question: is maxconf Theorem 5.x's bound TV <= |X|/(2 sum K)
(under hypothesis c >= 1/min_x D(x)) correct, or should it be the
rigorous |X|/(sum K)?

DO NOT use numeric search to settle this. This session produced four
mutually inconsistent adversarial-search results for the same quantity
(the flaky channel garbled the outputs); none are trustworthy. The
exact identity makes this a clean finite optimization:

    find sup of  (1/2N) sum_x |r(x) - R D(x)|
    where r(x) = ceil(c D(x)) - c D(x) in [0,1), R = sum r,
    N = c + R, over distributions D on X (|X| = n), subject to
    c >= 1/min D.

Derive the exact sup by hand. Then either confirm |X|/(2N) (keep
maxconf's constant; still fix its proof, see below) or correct it.

Full framing + the maxconf proof gap (it bounds discrepancy to 1/c but
TV is to 1/M = 1/sum K; the final constant is asserted, not derived)
is in:
    papers/maximizing-confidentiality/.papermill/HANDOFF-multiplicity-theorem-fix.md
Diagnosis + retracted session numerics in:
    papers/cipher-maps/.papermill/proofs/homophonic-allocation-2026-05-28.md

## After both items: remaining pre-submission work (from R8 review)

- MAJ-1: mint Zenodo DOIs for sister papers; see SISTER-PAPER-DOIS.md
  (.zenodo.json files already prepared). Then update the 4
  "Manuscript in preparation" bib entries.
- MAJ-4/5/6 (submission-time, mechanical): PoPETs template port, page
  trim, anonymization.
- R8 unified report: .papermill/reviews/2026-05-27/review.md
  (recommendation was minor-revision conditional on MAJ-1).
