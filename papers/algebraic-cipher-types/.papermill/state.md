---
title: "Algebraic Cipher Types: Confidentiality Trade-offs in Type Constructors over Trapdoor Computing"
stage: revising
format: latex
authors:
  - name: "Alexander Towell"
    email: "lex@metafunctor.com"
    orcid: "0000-0001-6443-9897"
    affiliation: "Southern Illinois University Edwardsville"

metrics:
  pages: 20
  tex_lines: ~1640
  sections: 8
  figures: 0
  citations: 22
  last_built: 2026-06-03

thesis:
  claim: "Cipher types form an algebra: the standard type constructors (void, unit, product, sum, exponential) build complex cipher types from simpler ones, and each constructor induces a specific confidentiality cost absent in plaintext programming. Products leak correlations under component-wise encoding; sums force an impossibility (tag hiding and untrusted pattern matching cannot coexist); the cipher exponential is the cipher map abstraction itself, closing the algebra back on the trapdoor framework. A uniform information-theoretic bound holds across the algebra (the conditional entropy H(X | view) is at least H(X) - log_2 |orbit|), and a typed-composition discipline turns this bound into a design-time budget. The algebra is instantiated in a cipher Boolean type, evaluated on 20 Newsgroups Boolean search, and shown to support partial filtering (return a superset of relevant documents, hiding which are relevant)."
  novelty: "(1) An algebra of cipher types with a coherent confidentiality calculus: products, sums, and exponentials each carry a quantifiable confidentiality cost, surveyed uniformly through the encoding-granularity knob (joint vs. component-wise). The cipher exponential is the cipher map abstraction itself, closing the algebra back on the trapdoor framework. (2) Three constructor-specific results: product correlation trade-off (Prop 4.1), sum-type impossibility (Thm 4.2), exponential computation-pattern trade-off (Prop 4.5). (3) A construction-independent entropy-form confidentiality bound H(X | V) >= H(X) - log_2 |orbit| (Thm 5.3) that applies uniformly across the algebra, plus a typed-composition recurrence (Prop 5.5) that controls orbit growth at construction time. (4) Instantiation and evaluation: a cipher Boolean type with AND/OR/NOT, 20 Newsgroups Boolean search (with the AND-chain FPR-divergence finding), and partial filtering as a tunable precision-for-confidentiality trade. NOTE: the automatic expression-tree -> cipher-program rewriting (propagation, cut points, branching/control-flow obliviousness, @cipher_node compiler) was REMOVED 2026-06-03 and relocated to a companion paper (towell2026cipherprog); construction of single cipher maps belongs to the foundation paper (towell2026cipher Sec 6), which this paper cites rather than re-derives."
  refined: 2026-05-04
  previous_claim: "Every algebraic operation the untrusted machine can perform on cipher values enlarges their orbit closure and, by information-theoretic bound, reduces confidentiality. Each algebraic type constructor (product, sum, exponential) therefore induces a quantifiable confidentiality cost, culminating in a sum-type impossibility (tag hiding and untrusted pattern matching cannot coexist), and a typed cipher-program discipline, realized concretely via expression-tree cut points, turns those costs into a design-time budget."
  refinement_notes: "Restored the algebraic framing promised by the title. Across review rounds 2026-04-08 through 2026-04-30 the sum-type impossibility had been elevated to the headline ('culminating in a sum-type impossibility'), which underplayed the §4 algebra (void/unit/product/sum/exponential). The 2026-05-04 refinement makes the algebra primary, lifts the product trade-off (already a Proposition) to consistent prominence with sum, lifts the cipher-exponential observation from a paragraph to two Propositions (Prop 4.4 'cipher exponential is the cipher map abstraction', Prop 4.5 'exponential confidentiality trade-off'), and adds §4.5 'Summary: The Cipher-Type Algebra' with Table 1 consolidating the per-constructor costs. Sum-type impossibility remains a structurally distinguished result (categorical not quantitative), but is now one of three constructor-specific results within a uniform algebraic frame. Earlier history (2019-2022 notebook construction-from-simple-types thread) is now visible in the paper structure rather than buried."

  earliest_claim: "Each algebraic type constructor (sum, product, exponential) imposes a specific, unavoidable trade-off between confidentiality and composability when applied to cipher values. Orbit closure under the available operations bounds adversarial knowledge."

prior_art:
  last_survey: null
  key_references:
    - "towell2026cipher: Cipher maps (batch construction, four properties)"
    - "towell2026bernoulli: Bernoulli data types (accuracy-side algebraic analysis)"
  gaps: "Review flagged thin bibliography (6 cites in 15pp). Need information flow type systems (Sabelfeld & Myers 2003), functional encryption (BSW 2011), SSE (Curtmola 2006). Target 20-30 refs for PLAS."

experiments:
  - name: "Cipher Boolean search over 20 Newsgroups"
    status: re-run-with-baselines
    note: "Table 1 now reports mean +/- SD across 5 seeds (single term: 0.408 +/- 0.014 precision; 1.000 recall for AND chains; 0.91-0.96 for OR/NOT). Plaintext baseline (1.00/1.00 by construction) included as a column. Hardware spec line added."
  - name: "FPR compounding through AND/OR chains"
    status: tabulated
    note: "Table 2 reports empirical vs theoretical FPR for k=1..5 across 5 seeds, 1000 trials each. AND chain ratios: 1.01, 2.96, 35.2, 256, 12160 (the 'order of magnitude' was a major undercount). OR chain ratios: 0.90 to 1.02 (matches theory tightly). Cited in the conclusion."
  - name: "Encoding granularity comparison"
    status: complete-with-space
    note: "Table 3 now reports build time, space, bits/elem, intermediates exposed for all 3 levels with mean +/- SD. Counter-intuitive finding: leaf/intermediate annotations use *less* total space (~140B) than root (694B) because per-component domains are smaller; the trade-off is build-time and intermediate exposure, not raw space."

venue:
  target: null
  candidates:
    - "PLAS (Programming Languages and Analysis for Security, at CCS)"
    - "IACR ePrint (technical report)"
    - "TCC (Theory of Cryptography Conference)"

review_history:
  - date: 2026-04-08
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 2 | Major: 11 | Minor: 12 | Suggestions: 6"
    location: ".papermill/reviews/2026-04-08/"
    status: partially-addressed
    notes: "C1 (noise absorption), C2 (orbit confidentiality bound), and 3 major issues fixed in commits c052809 + a6b5c60. Remaining: experimental baselines/error bars, bibliography expansion, Discussion-section rebalance."
  - date: 2026-04-12
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 1 | Major: 12 | Minor: 18 | Suggestions: 14"
    location: ".papermill/reviews/2026-04-12/"
    status: partially-addressed
    notes: "Post-restructure review. C1 (candidate-set tautology, new critical finding) fixed by rewriting Section 5.3 in entropy form: conditional-entropy bound H(X|view) >= H(X) - log2 |orbit| as primary theorem, set-form bound conf >= 1 - |orbit|/|X| as corollary. Dropped the disconnected candidate-set definition. M1 (typed-chain arity mismatch) fixed by generalizing Def/Prop 5.4 to arbitrary arities with the correct bound sum N_i, N_{i+1} = N_i^{a_i}. Example 5.4 corrected. M11 (denominator switch) resolved by the entropy-form rewrite. LC-MIN-1/LC-MIN-2 (TM head direction framing, pairing cipher map) fixed by storing (state, symbol) as one cipher value per cell and making the head direction explicitly cleartext on output. M6 (bibliography) partially addressed: 21 cites now (up from 10), including all 7 previously dead entries plus 4 new refs (Smith 2009 QIF, Cash 2015 leakage attacks, Grubbs 2017, Lang 1995 20 Newsgroups). M8 (thin Section 6.3 synthesis) addressed by adding formal cut-point definition, explicit mapping to both realizations, and a regex-matching worked example. Remaining: M2/M3/M4/M5 (experimental baselines and error bars, FPR table, granularity space data), M7 (document class for PLAS), M9 (self-citations unpublished)."
  - date: 2026-04-13
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 0 | Major: 6 | Minor: 14 | Suggestions: 8"
    location: ".papermill/reviews/2026-04-13/"
    status: partially-addressed
    notes: "Third review verifies the second-round fixes. C1, M1, M6, M8 (structurally), LC-MIN-1, M11 confirmed fully resolved. Three new majors flagged in second-round content: MAJ-1 (regex example fabricated exponential cost via strawman expression-tree decomposition), MAJ-2 (cipher TM shift cipher map invoked but space not analyzed), MAJ-3 (typed-chain bound misapplied to cipher TM, which is a self-loop not a chain). Critical count is 0 for the first time. Carry-forward: M2/M3/M4/M5 (experimental issues), M7 (doc class), M9 (self-citations)."
  - date: 2026-04-29
    type: in-session-fix
    addresses: "MAJ-1, MAJ-2, MAJ-3 from 2026-04-13 review"
    notes: "MAJ-3 fixed by rewriting the 'What the typed-chain bound says in each case' paragraph in Section 6.3 as 'What bounds the orbit in each case', explicitly distinguishing the typed-chain bound (expression tree, distinct cipher spaces) from the deterministic-trajectory bound (cipher TM, self-loop on a single cipher space). MAJ-1 fixed by rewriting the regex example as 'Regex matching: same total cost, different leakage', acknowledging |Q_R| can be 2^{O(r)}, presenting the natural typed-chain decomposition with l cut points each O(|Q_R|*|Sigma|) for total O(l*|Q_R|*|Sigma|), reframing the comparison as a leakage-profile choice rather than a space-cost choice. MAJ-2 fixed by factoring the shift into two unary cipher maps (clear, set_q parameterized by new state), Prop 6.1 updated to account for all three families (delta_T, clear, |Q|*|{L,R,S}| instances of set_q) giving total space O(|Q|^2*|Gamma|). PDF builds clean at 19 pages with no warnings."
  - date: 2026-04-29
    type: multi-agent
    recommendation: major-revision
    findings: "Critical: 0 | Major: 2 | Minor: 5 | Suggestions: 3"
    location: ".papermill/reviews/2026-04-29/"
    status: addressed-in-session
    notes: "Fourth-round verification review. Confirmed MAJ-2 (cipher TM shift), MAJ-3 (typed-chain split), LC-MIN-4 (Def 3.3), LC-MIN-6 (zero-errors framing) fully resolved. Flagged four new defects from third-round fixes: MAJ-1 (cipher TM space mismatch: abstract/intro/conclusion still claimed O(|Q|*|Gamma|) but Prop 6.1 now O(|Q|^2*|Gamma|)), MAJ-2 (conclusion still claimed typed-chain bound 'constrains identically' both realizations, contradicting MAJ-3 fix in §6.3), MIN-1 (regex example claimed equal total cost while showing different costs), MIN-2 (LC-MIN-3 partial: plaintext renamed delta_T->tau_T but cipher hat-delta_T still used delta), MIN-3 (set_q selection mechanism under-specified: untrusted machine cannot extract q from cipher c' without trapdoor)."
  - date: 2026-04-29
    type: in-session-fix
    addresses: "MAJ-1, MAJ-2, MIN-1, MIN-2, MIN-3 from 2026-04-29 verification"
    notes: "Abstract, intro contributions, and conclusion updated to O(|Q|^2*|Gamma|) consistent with Prop 6.1. Conclusion's 'constrains identically' claim replaced with 'orbits bounded by complementary arguments (typed-chain for expression tree, deterministic-trajectory for cipher TM)'. Regex example reframed: same orbit bound but different construction-cost asymptotics, with crossover near l ~ |Q_R|; cost comparison decoupled from leakage comparison. Cipher rename completed: hat-delta_T -> hat-tau_T throughout, eliminating the delta collision in §6. set_q selection made explicit: tau_T output is now a triple (c', d, q_sel) where q_sel in Q is a plaintext selector; trajectory leakage proposition (Prop 6.2) generalized to (d_i, q_{sel,i}) pairs; §6.3 leakage profile updated to match. Build clean at 19 pages."
  - date: 2026-04-30
    type: experimental-rerun
    addresses: "M2/M3/M4/M5 from 2026-04-13 review (carry-forward across all four rounds)"
    notes: "Wrote examples/experiment_paper_tables.py in cipher-maps Python lib (at /home/spinoza/github/trapdoor-computing/src/cipher-maps/) producing all three §7.3 tables with multi-seed averaging. Output saved to docs/paper-numbers.md per PAPER-INTEGRATION.md convention. Paper §7.3 rewritten: Table 1 (Boolean search) now reports mean +/- SD across 5 seeds with plaintext baseline column; Table 2 (FPR compounding) is new and replaces the prior prose paragraph, showing AND ratios 1.01/2.96/35.2/256/12160 vs OR ratios 0.90-1.02; Table 3 (granularity) now has space measurements for all 3 levels with the counter-intuitive finding that leaf annotations use less raw space (smaller per-component domains). Hardware spec added. Conclusion updated to surface the AND-chain divergence as a quotable empirical finding (the previous prose claim 'order of magnitude at k=3' was a major undercount of the actual 35x at k=3 / 12000x at k=5). Build clean at 20 pages."
  - date: 2026-04-30
    type: multi-agent
    recommendation: minor-revision
    findings: "Critical: 0 | Major: 0 | Minor: 1 | Suggestions: 1"
    location: ".papermill/reviews/2026-04-30/"
    status: addressed-in-session
    notes: "Fifth-round verification of the experimental rerun. All Table 1/2/3 numerics check out internally (predicted FP 242 vs measured 233 +/- 13; theoretical FPRs match p_T^k and 1-(1-p_T)^k; bits/elem cross-check correct). Counter-intuitive Table 3 finding (leaf < root space) is physically correct. Single minor flagged: regex example title 'same total cost, different leakage' contradicted the body which now correctly says 'same orbit bound but different cost asymptotics'. Title corrected to 'Regex matching: same orbit bound, different cost asymptotics and leakage profiles'. M2/M3/M4/M5 confirmed fully closed. Carry-forward unchanged: M7 (article doc class, gated on venue), M9 (3 unpublished self-cites, gated on arXiv/IACR ePrint posting). Paper is content-complete pending external blockers."
  - date: 2026-04-30
    type: in-session-fix
    addresses: "Single minor from 2026-04-30 verification"
    notes: "Regex example title corrected from 'same total cost, different leakage' to 'same orbit bound, different cost asymptotics and leakage profiles', matching the body's prose. Build clean at 20 pages."
  - date: 2026-05-02
    type: structural-revision
    addresses: "Author-driven simplification: cipher TM is redundant once you have @cipher_node + plain Python over opaque bit strings"
    notes: "Removed §6.1 (Cipher Turing Machines) entirely along with Definition 6.1, Proposition 6.1 (cipher TM space), Proposition 6.2 (trajectory leakage), and the ORAM comparison remark. Collapsed §6 'Realizing Cipher Programs' to one realization (expression-tree decomposition). §6.3 demoted from 'Cut-Point Structure Common to Both Realizations' to 'Cut-Point Structure'. The §6.3 'mapping the two realizations' / 'what bounds the orbit in each case' paragraphs collapsed to a single 'what bounds the orbit' paragraph that mentions the iterated/self-loop case as a contrast without giving it its own propositions. Regex example reframed as a typed-chain example with the self-loop case as a contrast in the body (no separate analysis). Abstract, intro contributions, conclusion, acknowledgments updated. §8 open-question item 3 (cipher TM with oblivious head) replaced with item on plain operations on cipher bytes. PDF now 19 pages (was 20). Thesis essentially unchanged: still 'one principle with three instances' but with one realization rather than two."
  - date: 2026-05-04
    type: thesis-refinement
    addresses: "Restoring the algebraic framing promised by the title (author-driven, not review-driven)"
    notes: "Across review rounds 2026-04-08 through 2026-04-30 the sum-type impossibility had been elevated to the headline result, with state.md describing the paper as 'culminating in a sum-type impossibility'. The §4 structure remained algebraic (void/unit/product/sum/exponential), but products and exponentials had less elevation than sums. The 2026-05-04 refinement makes the algebra primary across abstract / intro contributions / conclusion. Concrete changes: (a) §4 lead-in replaced with a paragraph framing cipher types as an algebra with a universal granularity knob (joint vs component-wise) and three constructor-specific costs. (b) §4.4 Exponentials lifted from one paragraph to two Propositions: Prop 4.4 'Cipher exponential is the cipher map abstraction' (closing the algebra back on the trapdoor framework) and Prop 4.5 'Exponential confidentiality trade-off' (the granularity knob applied to function composition). (c) New §4.5 'Summary: The Cipher-Type Algebra' with Table 1 consolidating the three trade-offs and prose calling out (i) the universal granularity knob, (ii) sums as categorically different (impossibility, not asymptotic recovery), (iii) closure of per-constructor costs under the orbit-closure framework of §5. (d) Abstract, intro contributions list, and conclusion rewritten to lead with the algebra. (e) Bound presented as entropy form `H(X | V) >= H(X) - log_2 |orbit|` in the abstract (was the set-form fraction; the entropy form is the actual primary theorem since 2026-04-12). PDF now 21 pages (was 19). Thesis is now consistent with the title."
  - date: 2026-05-04
    type: multi-agent
    informed_by: "../cipher-maps foundation paper (cross-paper consistency check)"
    recommendation: minor-revision
    findings: "Critical: 0 | Major: 3 content (composability =vs<=, Thm 5.3 proof gap, six citation-number defects) + 2 external (M7, M9) | Minor: 5"
    location: ".papermill/reviews/2026-05-04/"
    status: addressed-in-session
    notes: "Sixth review, first one informed by the foundation paper cipher_maps.tex (which now exists in-tree, builds 39pp). Reviewer cross-checked all towell2026cipher citation sites against the foundation's resolved label numbers (cipher_maps.aux) and gave the unreviewed 2026-05-04 algebraic restructure (Prop 4.4/4.5, Table 1) a cold read. New props sound; algebraic frame coherent. Also confirmed a Thm 5.3 proof gap independently flagged by an isolated 2026-05-23 review. A second isolated 2026-05-23 review dir exists from a parallel session (ACT-only, not cross-paper)."
  - date: 2026-05-04
    type: in-session-fix
    addresses: "MAJ-1, MAJ-2, MAJ-3, MIN-1, MIN-2, MIN-4, MIN-5 from 2026-05-04 cross-paper review, plus an author-confirmed Corollary 5.4 deletion"
    notes: "Cross-paper-informed fixes. MAJ-1: §3 composability restated from strict `=` to `<= 1-(1-eta_f)(1-eta_g)` with 'equality under the re-randomization condition of [Thm 4.2]', matching the foundation's revised Theorem 4.2 (the M4 fix the foundation made; ACT had not propagated it). MAJ-3: six citation-number fixes against foundation ground truth: [Def 1.1]->[Def 3.1]; three [Sec 9]->[Sec 8.1]; [Prop 9.1]->[Prop 8.1]; [Sec 9.3]->[Sec 8.1]. Foundation bib entry annotated that cross-references follow the 2026-05 revision and may shift (root cause of MAJ-3 was number drift in the unposted foundation). MAJ-2 (Thm 5.3 proof gap): the proof bounded H(view) <= log2|orbit| while the setup defined view := orbit-as-SET (whose entropy is bounded by #distinct-orbits, not single-orbit-cardinality). Repaired by redefining the view as the adversary's orbit-ELEMENT observation (range <= |orbit|), so H(view) <= log2|orbit| is honest; theorem STATEMENT and abstract unchanged. Verified the fix gives correct extremes (orbit=1 => H(X|V)>=H(X), full privacy). DURING the fix I discovered Corollary 5.4 (set form) was inverted: it claimed |S_F(c)| <= |orbit| with conf = 1-|S|/|X|, which makes 'no operations' (orbit=1) read as conf maximal while the formula gives the opposite; the inequality direction and the conf definition were both backwards relative to the now-correct entropy theorem. Author chose option Y: deleted Corollary 5.4 and its proof, stripped the conf line from the Extremes remark, redirected the one downstream reference (Prop 5.5) to substitute the orbit bound into Thm 5.3 directly. Entropy theorem (correct, abstract-cited) now stands alone. MIN-1 10^4->over 10^4; MIN-2 added three-way confidentiality-labor division (foundation delta-marginal Prop 5.1 + §8.2 collision; maxconf entropy ratio; ACT orbit reachability); MIN-4 overfull hbox eliminated; MIN-5 'tape configuration' vestige -> 'cipher value'. Build clean: 21 pages, 0 overfull, 0 undefined. Remaining open: M7 (doc class, venue-gated), M9 (post the three @misc self-cites)."
  - date: 2026-05-04
    type: proof-hardening
    addresses: "papermill:proof on Thm 5.3 (orbit-closure confidentiality bound = formalism Measure C1)"
    notes: "Hardened the Thm 5.3 proof against the gap repaired earlier the same day, aligned with the now-canonical formalism §4A.2 (cipher-map-formalism.md) which owns the two-scale framing and delegates this proof to ACT. Strategy: information-theoretic counting bound. Settled correctness with two concrete tests: (a) small-orbit bites -- X uniform on m, op=isZero gives |orbit|=2, residual = log2 m - h2(1/m) >= log2 m - 1, matches; (b) large-orbit vacuous -- successor mod m gives the full m-cycle, same set for every x, so reveals m but not which x, bound gives >= 0, true/uninformative. Both confirm the bound holds iff the view is the adversary's RESOLVED observation (one cipher value, support <= |orbit|), NOT the orbit-as-a-set-valued RV (entropy bounded by #distinct-orbits). Presentation changes to §5.3: (1) setup paragraph now states the modeling explicitly -- 𝒱_F(c) is a random variable supported on orbit_F(c); the orbit set is trapdoor-independent (labeled rem:orbit-indep) and is the SUPPORT, not a set-valued signal; what carries info is which element it resolves to. (2) proof spells out the support<=M => H<=log2 M => I<=H => residual = H(X)-I chain with the standard facts named. (3) new Remark 'Which scale this bounds' (rem:two-scales): this is the active scale (Measure C1), controlling quantity is orbit size not delta; complementary to the marginal entropy-ratio scale (M1) per the formalism's two-scale separation; cites towell2026cipher + towell2026maxconf. Statement and abstract unchanged. Build clean: 21pp, 0 overfull, 0 undefined, rem:orbit-indep and rem:two-scales resolve. CROSS-REPO FLAG (not yet acted on): formalism/cipher-map-formalism.md §4A.2 still lists the inverted set form `conf_F(c) >= 1 - |orbit|/|X|` that ACT deleted; the formalism is the authoritative shared spine, so this is a real discrepancy to reconcile (recommend matching ACT: keep entropy form, drop or correct the set form to candidate-set >= |X|/|orbit|). Surfaced to user."
  - date: 2026-05-04
    type: proof-hardening
    addresses: "Author question on Thm 4.2 (sum-type impossibility): what if the pattern-match selector tau were a cipher map returning a cipher value of the right type?"
    notes: "Author found a genuine soft spot: the proof asserted 'pattern matching requires a function tau : B^n -> {A,B}' (plaintext tag out), but the FUSED ELIMINATOR h-hat : C(A+B) -> C(Z) for h(inl a)=f(a), h(inr b)=g(b) computes the match result as a cipher value WITHOUT materializing the tag -- so the assertion was false as a universal claim, and under a loose eval-time reading of property 2 the fused eliminator is a literal COUNTEREXAMPLE to the headline theorem (no eval-time trusted help, tag hidden, correct handler's result). The theorem is true only under the DISPATCH reading: the untrusted machine selecting which of two separately-held handlers to apply, decided untrusted-side. Three edits. (1) Tightened property 2 to the dispatch reading: 'holding the A-handler f-hat and B-handler g-hat separately, apply exactly one of them, choosing which as a function of the cipher value, with no per-query trusted assistance.' (2) Reframed both proof paragraphs (first horn + 'no intermediate encoding') to derive a SELECTOR s : B^n -> {A,B} from dispatch (s = tag on valid encodings => distinguisher => leak), replacing the tau-from-pattern-matching assertion; added an inline note that computing the result without forming s is possible but is not dispatch. (3) New remark rem:oblivious-elim 'Oblivious elimination without dispatch': the fused eliminator h-hat (trusted-built over joint encoding, evaluated blindly, tag hidden, no branch) is the efficient form of trusted pattern matching -- compiled once at construction, no per-query round trip, strictly better than rem:trusted-matching -- and the evaluate-both-branches + cipher-mux route (Ex 5.3 branching) is the other tag-hiding non-dispatch option. Both internalize the case analysis so the untrusted machine never forms s. Net effect: converts an apparent loophole into the constructive story for cipher-sum elimination and upgrades the round-trip remark. Theorem name and all \\Cref prose ('pattern matching') preserved; statement made precise. Build clean: 21pp, 0 overfull, 0 undefined, rem:oblivious-elim + ex:branching-orbit resolve."
  - date: 2026-06-03
    type: content-expansion
    addresses: "Author observation: ciphering a subtree forces all semantic ancestors (and their siblings) to cipher; control flow is the sharp case; depth can force the if to leak."
    notes: "Expanded §6 with the upward-propagation story, a figure, and a new subsection on branching. (1) New remark rem:cipher-propagation in §6.1 (Expression-Tree Decomposition): replacing a subtree with a cipher map makes its output a cipher value, so every ancestor that semantically consumes it must be a cipher map, and (since a cipher map takes cipher inputs) sibling inputs must be cipher too; the ciphered region is upward-closed along data-flow edges (the combiner IS this region); only pure plumbing stays plaintext; in a single-rooted tree a single cut whose result reaches the output ciphers the whole tree. Control-flow case: branching on a cipher Boolean is untrusted dispatch on 1+1 (Thm 4.2), so if must become a cipher mux forcing both branches to be cipher values and evaluated -- which is why tracing computes all branches. (2) First figure in the paper (fig:cipher-tree, added \\usepackage{tikz}+fit): two-panel expression tree for if(x+1<y) then p else q -- panel (a) plaintext with a dashed cut box around the x+1 subtree, panel (b) the cut rolled into cipher map M1 with every node above double-circled (ciphered), showing the sibling y and both branches p,q pulled in. (3) New subsection §6.2 'Branching and the Limits of Oblivious Control' (sec:branching): cipher-if as ite : C(2)xC(R)xC(R)->C(R); Prop 'No oblivious short-circuit' (prop:no-short-circuit) -- short-circuit = dispatch = leak t (Thm 4.2); hiding t forbids skipping the untaken branch, paid at eval time (mux) or construction time (fuse); three regimes (bounded fixed-shape -> oblivious, 2^k leaves for k nested ifs; total-but-partial -> totality+noise makes wrong-branch eval safe, e.g. y/x at x=0; unbounded data-dependent -> public-bound O(N) masking or trajectory leak); the unification 'oblivious iff fixed data-independent computation graph', with unbounded control = the cipher TM (retroactively justifying why the expression tree, not the TM, is the realization); remark rem:mux-cost (ite costs O(|R|^2), the product trade-off inside control flow; fusing costs O(|X|); variant-typed branches defer dispatch to the next consumer). Cut-Point Structure (now §6.3) self-loop paragraph cross-links to sec:branching. Prop proof corrected before commit to admit the fuse route (earlier draft overstated 'must evaluate both at runtime'). Build clean: 24pp (was 21; +figure +subsection), 0 overfull, 0 undefined, all new labels resolve."
  - date: 2026-06-03
    type: scope-restructure
    addresses: "Author decision: the expression-tree -> cipher-program rewriting is a distraction for this paper; this paper only CONSTRUCTS cipher maps of specific functions to analyze leakage/trade-offs, it does not evaluate whole-program realization. Construction machinery already belongs to the foundation paper."
    notes: "Removed §6 'Realizing Cipher Programs' ENTIRELY (365 lines): the lead-in, Expression-Tree Decomposition (Def cipher-node, granularity bullets, rem:cipher-propagation, the tikz figure fig:cipher-tree, rem:shared-vars, the automatic-tracing paragraph), Branching and the Limits of Oblivious Control (prop:no-short-circuit, the three regimes, rem:mux-cost), and Cut-Point Structure (def:cut-point, the regex example). All saved to /tmp/sec6_migration.tex for the companion paper. Decision rationale: (a) single-cipher-map CONSTRUCTION is the foundation paper's contribution (towell2026cipher Sec 6 batch/PHF); this paper now cites it in §3 rather than re-deriving. (b) whole-program REALIZATION (propagation, cut points, branching/control-flow) is a separate problem -> companion paper towell2026cipherprog. (c) this paper's actual scope is cipher TYPES + their leakage/composition (algebra, sum-impossibility, orbit, typed chains) + a concrete instantiation (cipher Booleans, search) -- none of which needs the realization story. Edits: abstract last sentence reframed (drop expression-tree/@cipher_node; mention instantiation + partial filtering); intro contribution #3 changed from 'Expression-tree realization' to 'Instantiation and evaluation' (cipher Booleans, search, FPR divergence, partial filtering); §3 gained a construction-cite paragraph (build via foundation Sec 6, not re-derived; whole-program assembly -> companion); §8 open-questions dropped the two §6-dependent items (plain-ops-on-cipher-bytes, cut-point-optimization) and added a 'Realizing whole programs -> companion' item; conclusion's realization paragraph reframed to construction+companion-pointer; granularity experiment (Table 3/now in §6 Cipher Boolean Eval) reworded to drop annotation/tracing language, tied to product trade-off Prop 4.1. ADDED §6.4 'Partial Filtering' (sec:partial-filter): the bag-gated cipher-OR multiplexer (gate: C(Bool)^m -> fire/idle on OR), returning a superset of relevant docs while hiding which (1-in-m anonymity), orbit bound in operational form (1 bit/bag), precision ~1/m as a tunable confidentiality lever tied to Table 1; analytical, no fabricated numbers. rem:oblivious-elim (the type-level fused-eliminator remark) stays in §4 (referenced only from the §4 proof). Section count 9->8, pages 24->20, figure removed, citations 21->22 (added towell2026cipherprog). Build clean: 0 overfull, 0 undefined, no orphan refs to deleted §6 labels."

related_papers:
  - path: ~/github/trapdoor-computing/papers/cipher-maps
    rel: foundation
    label: "Cipher map abstraction, four properties, batch construction (Sec 6). This paper CITES its construction rather than re-deriving it."
  - path: ~/github/trapdoor-computing/papers/cipher-program-construction
    rel: companion-spinoff
    label: "Realizing whole programs as cipher-map compositions: cut points, propagation, control-flow obliviousness, @cipher_node automatic rewriting. SPUN OUT of this paper 2026-06-03 (was §6). Seeded from /tmp/sec6_migration.tex."
  - path: ~/github/bernoulli/papers/bernoulli_data_type
    rel: companion
    label: "Accuracy-side algebraic types (Kronecker factorization, error propagation)"
  - path: ~/github/trapdoor-computing/.archive/algebraic_cipher_types-legacy
    rel: origin
    label: "2019-2022 C++ notebook with original ideas (archived 2026-04-29; see ARCHIVED.md inside)"
  - path: ~/github/trapdoor-computing/papers/maximizing-confidentiality
    rel: sibling
    label: "Entropy-ratio confidentiality framework (same ecosystem)"
---

## Notes

Paper started 2026-03-28 from the algebraic_cipher_types notebook (2019-2022).
Restructured 2026-04-12 (algebra framing), then 2026-06-03 (removed the
whole-program-realization §6 to a companion paper; this paper is now cipher
types + their leakage/composition + a cipher-Boolean instantiation).
Current structure (8 sections):

1. Introduction
2. Related Work
3. Preliminaries (cipher maps recap; construction cited from foundation Sec 6)
4. Cipher Type Constructors (static: void/unit, product, sum, exponential)
5. Orbit Closure and Information Leakage (dynamic: definition, monotonicity,
   confidentiality bound, examples, typed composition chains)
6. Cipher Boolean Algebra and Evaluation
   6.1 Cipher Boolean type
   6.2 Noise unreliability (proposition + remarks + practical allocation)
   6.3 Experimental validation (Boolean search, FPR compounding, granularity)
   6.4 Partial filtering (bag-gated multiplexer; precision-for-confidentiality)
7. Discussion (relationships, open questions incl. companion pointer)
8. Conclusion

(Former §6 "Realizing Cipher Programs" -- cipher TM, expression-tree
decomposition, cut points, branching/control-flow obliviousness, @cipher_node
automatic rewriting -- was spun out to papers/cipher-program-construction on
2026-06-03; seed at /tmp/sec6_migration.tex.)

Theoretical results (by label): Prop:product-tradeoff, Thm:sum-impossibility,
Thm:monotonicity, Thm:confidentiality-bound, Prop:typed-orbit,
Prop:cipher-tm-space, Prop:head-determinism, Prop:noise-unreliability.

Implementation (commit cc8ff90) integrates empirical results from the
`cipher-maps` Python library: Boolean search over 20 Newsgroups, AND-chain
FPR compounding (notable because empirical FPR exceeds the Bernoulli
independence prediction by ~1 order of magnitude at k=3).

## Review Summary (2026-04-08)

Multi-agent editorial review recommended major-revision. Strengths:
introduction positioning against ORAM/FHE/garbled circuits, the elegance
of the sum-type impossibility, and honesty about limitations (component-wise
encoding leaks correlations, no simulation-based security).

Critical issues fixed in post-review commits:
- **C1** Proposition 6.1 (noise absorption): reformulated
- **C2** Theorem 4.3 (confidentiality bound): orbit correctly integrated
  into candidate-set definition, single formula as the theorem
- **M1** Sum-type impossibility: balanced-prior assumption made explicit
- **M3** Discussion overload: Related Work + Conclusion split out

Still outstanding from the review:
- **M2** Bibliography thin (6 cites); need IFC, FE, SSE refs; unused .bib
  entries to be cited or removed
- **M4** Table 1 lacks baselines and error bars (5+ seeds, mean ± SD)
- **M5** FPR compounding reported in prose only; needs table/figure
- **M6** Encoding granularity table missing space for 2/3 levels

## Next Actions

The paper is **content-complete** as of 2026-04-30 (5 review rounds,
trajectory Critical 2->1->0->0->0; final round flagged 1 minor since
closed). The remaining items are external blockers, not content
rewrites.

1. **Venue commitment (M7)**: choose between
   - PLAS (Programming Languages and Analysis for Security, at CCS):
     swap to `\documentclass[sigconf,nonacm=true]{acmart}`, add CCS
     concepts, verify page count under the acmart template. Best
     fit for the type-theoretic framing and sum-type impossibility.
   - IACR ePrint or arXiv: keep article class, submit as a technical
     report. Best fit if PLAS deadline is unfavorable or if a
     longer treatment is preferred.
   - TCC: requires hardening of the orbit-closure framework into
     simulation-style or game-style definitions, which contradicts
     the paper's deliberate framing. Not recommended.
2. **Self-citations (M9)**: post `towell2026cipher` and
   `towell2026bernoulli` to IACR ePrint or arXiv before final
   submission so the load-bearing preliminaries are publicly
   verifiable. Three @misc entries currently cite "Manuscript in
   preparation"; updating to arXiv or ePrint links would close the
   reviewer concern about unverifiable load-bearing references.
3. **Optional strengtheners** for whichever venue is chosen:
   - Submit-time bibliography sweep (cite phobic, add a software
     citation for the cipher-maps library, etc.).
   - One pre-submission proofreading pass for prose nits.

Status by review round:
- Critical: 2 (2026-04-08) -> 1 (2026-04-12) -> 0 (2026-04-13) -> 0 (2026-04-29) -> 0 (2026-04-30)
- Major: 11 -> 12 -> 6 -> 2 -> 0
- Closed in-session: candidate-set tautology, typed-chain arity,
  cipher TM space accounting, cut-point synthesis, regex example,
  notation collision, plaintext baseline, error bars, FPR table,
  granularity space data.

## Restructure Log (2026-04-12)

Reorganized the paper around a clearer thesis. Changes to structure,
not to the underlying results:

- Added new §6 "Realizing Cipher Programs" as the unifying home for
  two realizations. §6.1 compresses the old §6 Cipher Turing Machine
  from ~180 lines to ~60. §6.2 promotes the expression-tree /
  @cipher_node material from the old Discussion to a proper
  subsection. §6.3 is new prose making the cut-point pattern explicit.
- Promoted old §7.2 "Cipher Boolean Algebra" from subsection to full
  section §7, with three subsections (type / noise unreliability /
  experimental validation) so evaluation has its own heading.
- Created new §8 "Discussion" holding the three Relationship
  paragraphs (previously inlined in old §7.1) and the Open Questions
  block. Added a fifth open question about cut-point placement as
  constrained optimization.
- Updated abstract, intro contributions list, and conclusion to match.
  Cipher TM drops from the headline; typed-chain discipline and
  expression-tree realization are elevated.
- All theorem/proposition/definition labels preserved; the four
  dropped labels (sec:cipher-tm-def, sec:cipher-tm-space,
  sec:head-leakage, and the subsection-label form of sec:cipher-bool)
  were not referenced from elsewhere in the paper.
- PDF builds clean at 17 pages with no undefined references.

## Second-Round Fixes (2026-04-12, post-review)

After the second multi-agent review:

- **§5.3 confidentiality bound rewritten in entropy form.** Dropped
  the candidate-set detour (whose orbit-containing clause was a
  tautology, per C1 in the second review) in favour of a conditional
  entropy bound $H(X \mid \mathcal{V}_F(c)) \geq H(X) - \log_2
  |\mathrm{orbit}_F(c)|$ as the primary theorem, with the set-form
  bound $\mathrm{conf}_F(c) \geq 1 - |\mathrm{orbit}_F(c)|/|X|$ as a
  corollary. This also resolves the M11 denominator switch.
- **§5.5 typed-chain proposition generalized** (M1). The chain
  signature now carries explicit arity $a_i$, and the orbit bound is
  $\sum_i N_i$ with $N_0 = m$, $N_{i+1} = N_i^{a_i}$. Unary ($a_i=1$)
  and single-value-start ($m=1$) cases recover the previous $m(k+1)$
  and $1+k$ bounds respectively. Example 5.4 updated to reflect the
  binary-AND arity explicitly.
- **§6.1 cipher TM definition cleaned** (LC-MIN-1, LC-MIN-2). Each
  tape cell is now a single cipher value in $\cipher{Q \times \Gamma}$
  with a distinguished state marking the head, eliminating the implicit
  pairing cipher map. Head direction is explicitly cleartext on the
  output pair $(c', d)$.
- **§6.3 cut-point synthesis strengthened** (M8). Added a formal
  Definition 6.3 of cut point and cut-point set, explicit mapping of
  each realization onto this structure, explicit statement of what the
  typed-chain bound says in each case, and a worked regex-matching
  example that plays the same computation out as both a cipher TM and
  an expression tree.
- **Bibliography expanded** (M6). 21 cites (up from 10). All 7
  previously dead entries now cited: Bloom 1970 (cipher Boolean as
  Bloom-like), Fredman et al. 1984 (PHF backing), Shannon 1948
  (source coding for the allocation), Song et al. 2000 (original SSE),
  Islam et al. 2012 (access-pattern attacks), Turing 1936 (cipher TM
  preliminaries), towell2026maxconf (sibling work). Four new:
  Smith 2009 (quantitative information flow, grounding the
  entropy-form bound), Cash et al. 2015 and Grubbs et al. 2017
  (SSE leakage-abuse attacks), Lang 1995 (20 Newsgroups dataset).
- **PDF now 19 pages, builds clean, no undefined references.**
