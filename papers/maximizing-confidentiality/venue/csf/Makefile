# CSF submission version (IEEEtran conference, 2-column). See NOTES.md.
# Canonical source of truth is ../../main.tex + ../../references.bib.
STEM = main

.PHONY: all clean
all: $(STEM).pdf

$(STEM).pdf: $(STEM).tex refs.bib
	pdflatex -interaction=nonstopmode $(STEM)
	bibtex $(STEM) || true
	pdflatex -interaction=nonstopmode $(STEM)
	pdflatex -interaction=nonstopmode $(STEM)

clean:
	rm -f *.aux *.log *.out *.toc *.bbl *.blg *.fls *.fdb_latexmk *.synctex.gz *.pdf
