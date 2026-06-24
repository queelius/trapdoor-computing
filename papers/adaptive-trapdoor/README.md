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
