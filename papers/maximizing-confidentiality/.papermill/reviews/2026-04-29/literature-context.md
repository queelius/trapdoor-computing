# Literature Context (carried forward from 2026-04-12 + rev2 + today's verification)

## Status

Literature scouts not launched in this environment (Task tool unavailable). Carry-over from prior rounds:

- The paper's QIF positioning (Smith 2009; Alvim et al. 2020) is already
  cited and substantively engaged in §2.
- SSE leakage references engaged: Bost-Fouque 2017 (now correctly
  attributed to IACR ePrint 2017/617 in this round, M7 from rev2
  resolved), Demertzis et al. 2020 (SEAL), Naveed et al. 2015, Islam et
  al. 2012.
- Foundational references: Fannes 1973 / Audenaert 2007 (continuity
  inequality), Cover-Thomas 2006, Shannon 1948, Jaynes 1957, Simmons
  1979.

## Gaps still present

These remain mostly the same as prior rounds. They are not flagged as
new this round; they are carry-overs:

- **Oya & Kerschbaum 2021** (search-pattern leakage attack on encrypted
  search; directly relevant to Thm 5.1's motivation), still not cited.
- **Kellaris et al. 2016** (joint-distribution leakage from query
  patterns), still not cited.
- **Fuller et al. 2017** (SoK on searchable encryption), still not
  cited.
- **Grubbs et al. 2017 HotOS** (`grubbs2018pump` bib entry has wrong
  venue but is uncited; cosmetic).

## What's new this round (2026-04-29)

The contribution-list reorder (Thm 5.1 ahead of Fannes bridge) and the
explicit two-scale framing slightly *strengthens* the SSE-related
positioning. The paper now leads with a result that connects directly
to the SSE joint-leakage thread (Cash, Kellaris, Oya-Kerschbaum). The
positioning would benefit from one sentence in §2 acknowledging that
shared-variable joint recovery is conceptually adjacent to the SSE
joint-leakage attacks, while distinguishing that:

- those attacks exploit query-pattern correlations across distinct
  encrypted queries to known plaintexts;
- Thm 5.1 exploits cipher-map composability, which is structural rather
  than statistical.

This is a Suggestion-level item, not blocking.
