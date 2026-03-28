TEX = pdflatex
BIB = bibtex
MAIN = main

.PHONY: all clean cleanall

all: $(MAIN).pdf

$(MAIN).pdf: $(MAIN).tex references.bib
	$(TEX) $(MAIN)
	$(BIB) $(MAIN)
	$(TEX) $(MAIN)
	$(TEX) $(MAIN)

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.toc *.nav *.snm *.fls *.fdb_latexmk

cleanall: clean
	rm -f $(MAIN).pdf
