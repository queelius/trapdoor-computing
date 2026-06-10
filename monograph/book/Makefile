# Trapdoor Computing monograph build.
BOOK = book

.PHONY: all clean cleanall

all:
	pdflatex -interaction=nonstopmode -halt-on-error $(BOOK).tex
	-biber $(BOOK)
	pdflatex -interaction=nonstopmode -halt-on-error $(BOOK).tex
	pdflatex -interaction=nonstopmode -halt-on-error $(BOOK).tex

clean:
	rm -f *.aux *.log *.bbl *.bcf *.blg *.out *.toc *.lof *.lot *.run.xml *.idx
	rm -f parts/*.aux chapters/*.aux frontmatter/*.aux appendices/*.aux

cleanall: clean
	rm -f $(BOOK).pdf
