TARGET = main
PDF = $(TARGET).pdf

.PHONY: all clean quick

all: $(PDF)

$(PDF): $(TARGET).tex references.bib
	pdflatex -interaction=nonstopmode $(TARGET)
	bibtex $(TARGET) || true
	pdflatex -interaction=nonstopmode $(TARGET)
	pdflatex -interaction=nonstopmode $(TARGET)

quick: $(TARGET).tex
	pdflatex -interaction=nonstopmode $(TARGET)

clean:
	rm -f *.aux *.bbl *.blg *.log *.out *.toc *.fls *.fdb_latexmk
