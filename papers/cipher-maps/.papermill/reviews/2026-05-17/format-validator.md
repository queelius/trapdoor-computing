# Format Validator Report (Round 7)

**Date**: 2026-05-17
**Paper**: Cipher Maps: Total Functions as Trapdoor Approximations

## Build status

- Build: clean (`make` completes with bibtex + 3 pdflatex passes)
- Output: 36 pages, 510925 bytes
- LaTeX warnings: none (no undefined references, no multiply-defined
  labels)
- Overfull hbox count: 5 (down from R6 reading of "4 overfull, one
  104pt"; actually still 5 overfull, with one at 118pt)

## Document class

`\documentclass[11pt]{article}` (still not PoPETs template). Carry-over
from R6 (FMT-1).

## OVERFULL HBOX INVENTORY

| Location | Severity | Notes |
|---|---|---|
| lines 1676-1683 | 4.4pt | §8.2 (compositional leakage) prose |
| lines 1829-1836 | 18.3pt | §8.3 (multi-instance) empirical verification |
| lines 1905-1910 | 118.9pt | §8.3 def of pattern/decode attackers |
| lines 2241-2250 | 7.8pt | §10 (Implementation and Evaluation) intro |
| lines 2386-2392 | 14.3pt | §10.3 Reproducibility paragraph |

The 118.9pt overfull at line 1905-1910 is the worst. Let me look at
context: this is in the description-list item bodies of Definition
8.x (`\item[Pattern-coincidence attacker (private-codec threat).]`).
A long itemize label combined with math content overflows the
margin. Specific text: the second bullet item has math content
`\mathbf{D} = (\dec_1(\fhat_1(c_1)), \ldots, \dec_t(\fhat_t(c_t)))`
which is too wide.

The 104pt overfull from R6 (line 1875-1880) is no longer present;
that was the 20NG URL line which is now within margin.

## MAJOR FINDINGS

### FMT-1: 118.9pt overfull hbox in Definition 8.x

**Location**: Lines 1905-1910.

**Quoted text**:
> "\item[Decode-coincidence attacker (public-codec threat).] Observes
> the decoded values $\mathbf{D} = (\dec_1(\fhat_1(c_1)), \ldots,
> \dec_t(\fhat_t(c_t)))$..."

**Problem**: 118.9pt is approximately 1.6 inches of overflow, very
visible in the PDF (text extends well past the right margin). The
combination of long `\item[...]` label and long math expression
overflows.

**Suggestion**: Either:
(a) Move the math expression to display style:
```
\item[Decode-coincidence attacker (public-codec threat).]
    Observes the decoded values
    \[ \mathbf{D} = (\dec_1(\fhat_1(c_1)), \ldots, \dec_t(\fhat_t(c_t))) \]
    and predicts...
```
(b) Shorten the math by introducing a notation $\dec_i \circ \fhat_i$:
```
$\mathbf{D} = ((\dec_i \circ \fhat_i)(c_i))_{i=1}^{t}$
```

### FMT-2: Article class still in use, not PoPETs template (carry-over)

**Status**: Same as logic-checker MAJ-6 and R6 FMT-1.

**Suggestion**: Port to the PoPETs LaTeX class as part of submission
prep. Mechanical work, brings page count down.

### FMT-3: 36 pages exceeds PoPETs target by 8-10 pages

**Status**: Carry-over and growing. R6 reported 28 pages. R7's new
content (§8.3 multi-instance, §10.6 codec-security empirical) added
8 pages. The §8.3 + §10.6 additions are technically motivated, but
PoPETs has a tight page budget.

**Suggestion**: After porting to PoPETs template, identify trimming
candidates:
- §9.1 (Relationship to Bernoulli Model) is one page, references a
  manuscript-in-prep. Could shrink.
- §9.4 (Bounded Composition as a Security Feature) is 1.5 pages,
  could fold into §9.5 (Open Questions).
- §4.5 (Parameter Decomposition) has both a table and a paragraph
  saying the same thing. Could collapse.
- §10.4 (Deniability via Correctness Parameter) has the Bayesian
  deniability proposition. Could move to appendix.

Estimated trim: 4-5 pages from these moves alone, bringing the paper
to roughly 28 pages in the article-class build, or roughly 18-20 in
the PoPETs template.

## MINOR FINDINGS

### FMT-MIN-1: Underfull boxes not checked

The log has no `Underfull` warnings, so this is clean.

### FMT-MIN-2: Theorem environment numbering scheme

The paper uses `\newtheorem{theorem}{Theorem}[section]` and
`\newtheorem{lemma}[theorem]{Lemma}` etc., giving section-prefixed
numbering (e.g., Theorem 6.1, Theorem 6.2). Consistent.

### FMT-MIN-3: `\Cref` vs `\ref` usage is mixed

The paper uses both `\Cref{...}` (capitalized cleveref) and
`\ref{...}` interchangeably. R6 FMT-N2 flagged this. Still
inconsistent.

Counts:
- `\ref{...}` total: ~150 occurrences
- `\Cref{...}` total: ~8 occurrences

Standardize on `\Cref` throughout, or accept the mix and document.

### FMT-MIN-4: §5.2 numbered enumerate items still have inline labels

The §5.2 enumerate items use `\emph{...}` for the descriptor (e.g.,
"\emph{Decoding requires the trapdoor.}"). This is a style choice;
matches the rest of the paper.

### FMT-MIN-5: Table 8 (`tab:scope-keys`) is in `\begin{table}` env

Now wrapped properly. Earlier rounds flagged untabularized tables.
Verified that §6.4 and §6.6.1 tables remain in `\begin{center}`
blocks (not `\begin{table}`). R6 FMT-N4, FMT-N5 are carry-over.

### FMT-MIN-6: Bibliography style `plainnat` is fine for the build

bibtex run produced `cipher_maps.bbl` cleanly. No bib errors.

### FMT-MIN-7: Author block (single author) not yet anonymized

For double-blind PoPETs submission, the `\author{Alexander Towell\\
\texttt{lex@metafunctor.com}}` needs to be replaced with a placeholder.
The footnote URLs in §10.1 (cipher-maps library) and §10.6
(`towell2026codec`) also need anonymization. Standard pre-submission
step.

### FMT-MIN-8: Hyperref `\hypersetup{hypertexnames=false}` is fine

Standard option to prevent label-naming issues. No problem.

### FMT-MIN-9: Section ordering jump from §9.6 to §10 is fine

§9 (Discussion) has subsections 9.1 through 9.6 (with §9.6 being the
new Threat Model Scope subsection added in R7). §10 (Implementation
and Evaluation) follows naturally. Numbering correct.

### FMT-MIN-10: Title page date is "March 2026"

`\date{March 2026}` (line 49). Should be "May 2026" given Round 7
date.

## SUGGESTIONS

### FMT-SUG-1: Add a glossary or notation table near §3

The paper introduces a lot of notation: $\fhat$, $\enc$, $\dec$, $s$,
$\cipher{X}$, $\cipherS{X}{s}$, $\eta$, $\varepsilon$, $\delta$,
$\mu$, $K(x)$, $\alpha(y)$, $\bar\alpha$, $H(Q)$, $\TV$, $A(y)$,
$A_i(y)$, $p_y$, $p_T$, $p_F$, $p_N$, $\ell_y$, $L$, $\kappa$, $t$,
$\pi$, $\mathcal{V}$, etc. A glossary table at §3 or end-of-paper
would help. ~1/2 page.

### FMT-SUG-2: Move algorithm pseudo-code to an appendix

Algorithm 1 (BuildCipherMap) at §6.3 is a half-page algorithm
pseudo-code. Moving to appendix could free space for §10 trim
recovery.

### FMT-SUG-3: Combine §8.3 subsubsections under `\paragraph` headers

PROSE-2 noted that §8.3's three `\subsubsection*{...}` headings break
the paper's style. Combining them under `\paragraph{...}` would also
slightly reduce vertical whitespace.

## Summary

- Critical: 0
- Major: 3 (FMT-1 118pt overfull, FMT-2 PoPETs template, FMT-3 page
  count)
- Minor: 10
- Suggestions: 3
- Build: clean (0 warnings, 5 overfull hboxes)
- Page count: 36 (need ~8 page trim, or template port to recover ~10
  pages)
