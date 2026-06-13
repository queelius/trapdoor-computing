---
title: "The Entropy Ratio: Quantitative Confidentiality for Trapdoor Computing"
stage: round-2 fixes APPLIED (2026-06-13). Canonical 018583b: Thm 4.1(1) restated as exact mixture entropy (case study now 72->94, not 72->98, verified by Python recompute); Thm 4.1(3) proof repaired (pointwise bound) + regime condition + image-filler; Thm 5.1(2) canonical-output hypothesis + general >=; Property-2/Thm 3.1 delta image-relative, H*=log2|im|; conclusion stale numbers fixed; new remarks (irreducibility, classical-rate); CLAUDE.md Landmines 5-6; cross-paper C-9/C-10 resolved, C-11 added. Build 32pp, 0 undefined, 4 prior landmines intact. CSF port re-derived at venue/csf/ (commit follows): 12pp body, 5 appendices A-E, anonymized incl. the in-body artifact URL (anonymous.4open.science; line-joined grep = 0 leaks -- the round-1 false-negative lesson), 5 tables resizeboxed, 2 displays broken, 3 seam fixes; 0 undefined, 0 overfull >20pt. Remaining pre-submission: AI-use disclosure + ethics statement per CSF 2027 CFP; minor seam-audit polish (m1-m5). Thm 5.2 Assouad verified correct twice. Review report: .papermill/reviews/2026-06-11/review.md.
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"

thesis:
  claim: "Cipher map confidentiality decomposes into two scales that do not reduce to each other. At the COMPOSITIONAL SCALE (the paper's main contribution), the joint distribution over latent outputs of multiple cipher maps observed on a shared cipher value is recoverable at the INFORMATION-THEORETICALLY OPTIMAL rate Theta(|Y1||Y2|/xi^2) -- matching upper bound from plug-in estimation (Thm 5.1), matching lower bound via Assouad's lemma (Thm 5.2), and mutual-information preservation I(fhat_1(C); fhat_2(C)) = I(f_1(X); f_2(X)). No per-cipher-map parameter (including arbitrarily small delta) changes the rate. The compositional channel is intrinsic to the framework's composability, not a bug: the same property that lets the untrusted machine chain evaluations blindly is the property that creates the channel. Defending at the compositional scale therefore requires SYSTEM-LEVEL interventions (reducing observations, joint encoding, noise injection); marginal-scale parameter tuning alone does not. At the MARGINAL SCALE, the representation-uniformity parameter delta lower-bounds the entropy ratio via the Fannes-Audenaert continuity inequality (e >= 1 - delta - h_2(delta)/n, linear in delta), and two constructions reduce delta with explicit costs: noise injection (bandwidth 1+R/N, Fisher info dilution rho^2 with explicit C(D) constant) and multiple representations (space sum K(x), K(x) proportional to D(x), classical homophonic). Engineering at one scale does not engineer at the other; the cipher map design problem must be solved at both scales independently."
  novelty: "(1) Compositional leakage at the optimal rate (main result): Theorems 5.1 and 5.2 together establish the SHARP rate Theta(|Y1||Y2|/xi^2) for joint recovery -- matching upper bound from empirical-distribution plug-in (Thm 5.1) and matching minimax lower bound via Assouad's lemma (Thm 5.2). Marginal delta is necessary but not sufficient: no per-cipher-map parameter reduces the rate, only system-level interventions do. The framing is impossibility-flavored, not just capability. (2) The Fannes bridge making delta the operational handle for the marginal scale, with two cost-attached constructions: noise injection (Thm 4.1, Fisher dilution rho^2 with explicit C(D)) and classical homophonic K(x) propto D(x) (Thm 4.2). The entropy ratio itself is standard QIF (Smith 2009, Alvim et al. 2020); the constructions are classical (Simmons 1979, Bost-Fouque 2017, Demertzis et al. 2020); the novelty is the IMPOSSIBILITY (with sharp Assouad constants) and the BRIDGE (with operational construction theorems). Granularity (Prop 4.3) and FPR compounding (a Proposition citing algebraic Table 3) are inherited from towell2026cipher, not proven here."
  refined: "2026-06-03/04: Cross-paper consistency + empirical completion. Thm 5.2 lower bound corrected from 'Le Cam two-point' to ASSOUAD'S LEMMA (a 2^(m/2) hypercube packing; two-point cannot give a dimension-dependent rate) with a fixed factor-2 TV slip; six stale companion-section citations fixed; orbit denominator 2^n->|X|; FPR downgraded Thm->Prop and re-attributed to algebraic Table 3; multiplicity Thm 4.2 corrected to the tight (|X|-1)/N citing cipher-maps Prop 4.1; delta-reduction constructions reframed as the framework's (cost analysis is ours). Added experiments 6.5 (compression), 6.6 (Monte Carlo S1/S2/S3 incl. lower-bound bake-off), 6.7 (realized attack on the real construction). The earlier 2026-05-04 note below predates the Le-Cam->Assouad correction; treat ASSOUAD as canonical."
  refined_2026_05_04: "2026-05-04: Sharpened the compositional contribution from 'rate result' to 'information-theoretically optimal rate' framing throughout, leaning on Theorem 5.2 (Le Cam minimax lower bound, added 2026-04-30 in commit 08b38e3). Specifically: abstract now closes on 'unavoidable for any choice of per-cipher-map parameters'; §1 framing paragraph and contributions list both promote impossibility-flavored language ('information-theoretically optimal rate Theta(|Y1||Y2|/xi^2)'); §2 Related Work novelty paragraph cites both Thms 5.1 and 5.2 with matching upper and lower bounds; §8 Conclusion now frames as 'compositional leakage pair' (not single theorem). Important precision preserved: 'no per-cipher-map parameter changes the rate' rather than 'no construction can stop it', because system-level interventions (observation budgets, joint encoding, noise injection) DO reduce effective adversary advantage. The impossibility is with respect to per-cipher-map parameters only. See .papermill/thesis-refined-2026-05-04.md."
  refined_prior_4: "2026-04-29 (later): Adopted explicit two-scale framing in §1 introduction. Inserted a 'Our central observation' paragraph after the cipher-maps setup that names the marginal/compositional decomposition as the paper's spine. The existing Fannes-bridge paragraph is now framed as the marginal-scale elaboration; the existing compositional leakage paragraph is framed as the compositional-scale elaboration (with a 'compositional channel is intrinsic to composability, not a bug' framing). Renamed §5 to 'The Compositional Scale'. §5 opening rewritten to pivot off scales rather than 'two effects.' Abstract and Conclusion remain in current narrative form (two-scale frame implicit, not named) per user choice."
  refined_prior_3: "2026-04-29: Promoted compositional leakage theorem (Thm 5.1) above the Fannes bridge in the contribution-list ordering, abstract, intro framing, Related Work paragraph, and Conclusion, per rev2 review Suggestion 2. Theorem 5.1 is now framed as the paper's headline contribution; the Fannes bridge is supporting (it makes the marginal target operational, but marginal target is necessary-not-sufficient per Thm 5.1)."
  refined_prior_2: "2026-04-12 (rev2): Fixed two critical errors caught by review. (a) Thm 3.1 pt 3 originally used Pinsker in wrong direction; replaced with Fannes-Audenaert: linear bound e >= 1 - delta - h_2(delta)/n, not quadratic e >= 1 - 2*delta^2/n. (b) Thm 4.2 originally had K(x) ~ 1/D(x) which concentrates rather than flattens; corrected to classical homophonic K(x) ~ D(x) (Simmons 1979). Numerics updated for Zipf s=1 baseline e=0.72 (was 0.59); case study now 0.72 -> 0.98 with 1.04x space (was 0.59 -> 0.85 with 1.52x space, which was based on broken construction)."
  refined_prior: "2026-04-12: Sharpened thesis. Demoted entropy ratio from headline to prerequisite (QIF-standard), promoted Prop 5.2 (correlation leakage) to headline, made citation of granularity/FPR-compounding explicit."
  refined_original: "2026-04-01: Complete rewrite from cipher map formalism. Old 43-page paper replaced by 13-page theory paper."

prior_art:
  last_survey: "2026-06-09 (ecosystem-wide adversarial survey; report at trapdoor-computing/.papermill/prior-art/2026-06-09-ecosystem-survey.md)"
  key_references:
    - "towell2026cipher - Cipher maps framework (four properties, composition, acceptance predicates)"
    - "towell2026algebraic - Algebraic cipher types (sum/product trade-offs, orbit closure)"
    - "Shannon 1949 - Communication Theory of Secrecy Systems"
    - "Jaynes 1957 - Maximum entropy principle"
    - "Islam et al. 2012 - Access pattern leakage attacks"
    - "Cash et al. 2015 - Leakage-abuse attacks"
    - "Simmons 1979 - Homophonic substitution (survey mention only; see gaps for the rigorous citations)"
  gaps:
    - "CRITICAL (headline positioning): Bindschaedler-Grubbs-Cash-Ristenpart-Shmatikov 'The Tao of Inference in Privacy-Protected Databases' PVLDB 2018 anticipates the QUALITATIVE two-scale separation (analytically optimal multinomial attack, extended across correlated columns, 96.9% multi-column recovery). NOT cited. Must cite + differentiate: they prove attack optimality; we prove the matching-minimax-rate theorem. Reposition headline as 'the sharp information-theoretic counterpart of a known phenomenon'."
    - "Kawamoto-Chatzikokolakis-Palamidessi LMCS 2017 (QIF compositionality): bounds under independence, notes correlation breaks component-determines-total. The closest QIF-native precedent; cite. Our Assouad rate is the delta over KCP."
    - "Farokhi-Sandberg (Automatica 2019 + IEEE TSG 2018): Fisher-information-as-privacy line. Thm 4.1 must credit it and reframe as instantiating that measure for the cipher-map noise construction (closed-form rho^2 with C(D) remains new)."
    - "Homophonic rigor: add Gunther EUROCRYPT 1988 and/or Jendal-Kuhn-Massey EUROCRYPT 1989 alongside Simmons 1979 for Thm 4.2."
    - "D.Smith-G.Smith CSF 2017 (tight leakage from repeated independent runs) = the canonical C2/coincidence citation for the Sec 9 discussion; Espinoza-Smith 2012 cascade for the MI-equality argument."
    - "Duchi-Jordan-Wainwright FOCS 2013 (local privacy minimax rates): methodological cousin (Assouad/Fano, sqrt(domain/N) rates) with INVERTED intent (their rate is the guarantee, ours is the leakage). Cite with the contrast."
    - "LEAKER (Kamara et al EuroS&P 2022): cite as the empirical counterpart; one sentence also justifies the 20NG corpus choice."
    - "CRITICAL (FSE steelman, 2026-06-09 follow-up scout): this paper is the program's MOST EXPOSED to the 'FSE rebranded' objection. Verified by file inspection: it cites ONLY Simmons 1979 for homophonic substitution; no Lacharite-Paterson FSE (ToSC 2018), no PANCAKE (USENIX 2020), no FH-OPE (Kerschbaum CCS 2015), no Revisiting-FSE (Chen-Yang-Lv, Cybersecurity 2024), despite being built around the homophonic delta-reduction lever and listing 'homophonic substitution' in keywords. ALSO: Cao et al. VLDB 2023 frequency-revealing attacks on FH-OPE already contain the QUALITATIVE 'marginal flattening does not hide joint structure' insight; frame the two-scale theorem as 'we prove the bound the attack literature observed'. The required related-work sentence and 5 BibTeX entries are in the survey report Part VII."
    - "VERDICT: sharp two-sided rate + MI-preservation survives as genuinely unclaimed (medium-high confidence), INCLUDING against the FSE line (steelman differentiator 5: formal half new, qualitative half is Cao 2023 / KCP / Tao-of-Inference territory). Qualitative separation does NOT survive. Seven BibTeX entries in the survey report Parts II + five more in Part VII."

experiments:
  - name: "Boolean search on 20 Newsgroups"
    description: "Precision/recall vs confidentiality trade-off. 5000 docs, 8-bit cipher Booleans."
  - name: "FPR compounding"
    description: "AND/OR chains k=1..5, empirical vs theoretical FPR."
  - name: "Encoding granularity"
    description: "Root/intermediate/leaf encoding of 7-function pipeline."
  - name: "Case study"
    description: "Confidentiality improvement from 72% to 98% via combined homophonic + noise (1.04x space, 1.5x bandwidth)."
  - name: "Compression estimator validation (6.5)"
    description: "gzip H_hat vs analytic entropy: uniform, Markov, mixture, 20NG token stream."
  - name: "Monte Carlo rate validation (6.6)"
    description: "S1 compositional rate TV=0.31 sqrt(m/N) R2=0.997; S2 Fisher dilution rho^2; S3 lower-bound bake-off (4 estimators incl oracle, none beats slope -1/2)."
  - name: "Realized attack on the construction (6.7)"
    description: "Real trapdoor maps built by the library; joint recovery reproduces the rate c=0.32; eta sets a recovery floor."

venue:
  target: "CSF (IEEE Computer Security Foundations Symposium) -- settled 2026-06-10 after a 5-specialist review. Novelty and methodology auditors both call it the clean fit for a matching-bounds theorem; needs no new experiments. PoPETs was runner-up (more reach, but gates on an m-sweep of the realized attack + a standard SSE corpus)."
  candidates: ["CSF (Computer Security Foundations)", "PoPETs", "TCC", "QIF workshop"]
  plan_2026_06_11: "User-confirmed path: CSF 2027 cycle 1 primary (projected ~Jul 24 2026 from the CSF 2026 cycle pattern Jul 24 / Oct 9 / Jan 29; CFP not yet posted as of 2026-06-11; watch ieee-security.org), with PoPETs 2027 Issue 2 as dated fallback (submission Aug 31 2026 FIRM, notification Nov 1 2026, petsymposium.org/cfp27.php) if the CSF CFP has not appeared by mid-July. PoPETs path additionally requires the methodology-gating experiments (m-sweep on realized attack + one standard SSE corpus, ~1 day) and the acmart port swap (codec venue/popets is the template)."
  requirements: "CSF format (stable across years; CSF 2027 CFP not yet posted as of 2026-06): two-column IEEE Proceedings style, body <= 12 pages EXCLUDING bibliography and well-marked appendices, DOUBLE-BLIND review."
  format_todo: "DONE 2026-06-10: CSF venue port at venue/csf/ (IEEEtran conference 2-col, 12pp body, Assouad proof kept in body, measurement + Boolean-chains + finite-sample + empirical-anchor moved to appendices A-D, anonymized for double-blind, 0 undefined refs, 0 wide overfull, 0 PDF identity leaks). Canonical single-column main.tex untouched. Remaining before submission: (1) add AI-use disclosure once CSF 2027 policy is posted; (2) final proofread of the 2-col render; (3) submit when CSF 2027 CFP opens."

review_history: []

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher maps formalism (four properties, composition, acceptance predicates)"
  - path: ~/github/trapdoor-computing/papers/algebraic-cipher-types
    rel: companion
    label: "Algebraic cipher types (sum/product trade-offs, orbit closure, confidentiality bound)"
  - path: ~/github/bernoulli/papers/bernoulli_sets
    rel: foundation
    label: "Bernoulli model provides the error framework"
---

## Notes

Initialized by papermill on 2026-03-19.

### 2026-04-01: Complete rewrite

Rewrote the paper from scratch, grounding it in the cipher map formalism.

- **Old paper**: main.tex (43 pages, USENIX target, pre-cipher-map formalism)
- **New paper**: main_new.tex (13 pages, theory venue, grounded in cipher map framework)
- **Bibliography**: references_new.bib (25 entries, matching cipher-maps paper conventions)

Key changes:
1. Replaced all custom notation with cipher-maps paper notation (fhat, enc, dec, eta, epsilon, delta, mu)
2. Replaced the 15-section structure with 8 focused sections
3. Grounded the entropy ratio in the four cipher map properties
4. Added encoding granularity (from cipher-maps and algebraic-cipher-types papers)
5. Added compositional confidentiality (FPR compounding, correlation leakage)
6. Added orbit closure as a confidentiality bound
7. Added experimental results from cipher-maps library (three experiments)
8. Dropped ORAM, queueing theory, mix networks, and all appendices

The paper compiles cleanly (13 pages, no errors, no warnings).

Writing plan saved to .papermill/drafts/2026-04-01/writing-plan.md.

## Overview

13-page paper developing quantitative confidentiality theory for cipher map systems. Defines confidentiality as the entropy ratio e = H/H* in [0,1]. Connects e to the four cipher map parameters (eta, epsilon, delta, mu). Identifies three levers for improving confidentiality: noise injection (trades bandwidth), multiple representations (trades space), encoding granularity (trades functionality). Analyzes confidentiality under composition (FPR compounding, correlation leakage). Provides practical measurement via compression-based entropy estimation. Validates on 20 Newsgroups corpus with three experiments.
