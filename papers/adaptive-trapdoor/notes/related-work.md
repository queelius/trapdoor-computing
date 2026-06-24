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
