.PHONY: all pdf clean cleanall watch

PAPER_DIR = paper
PAPER = cipher_maps
PDF = $(PAPER).pdf

all: pdf

pdf:
	cd $(PAPER_DIR) && pdflatex $(PAPER).tex
	cd $(PAPER_DIR) && bibtex $(PAPER) || true
	cd $(PAPER_DIR) && pdflatex $(PAPER).tex
	cd $(PAPER_DIR) && pdflatex $(PAPER).tex
	cp $(PAPER_DIR)/$(PDF) .

clean:
	cd $(PAPER_DIR) && rm -f *.aux *.bbl *.blg *.log *.out *.toc *.lof *.lot *.fls *.fdb_latexmk *.synctex.gz

cleanall: clean
	cd $(PAPER_DIR) && rm -f $(PDF)
	rm -f $(PDF)

watch:
	@echo "Watching for changes in $(PAPER_DIR)/$(PAPER).tex..."
	@while true; do \
		inotifywait -q -e modify $(PAPER_DIR)/$(PAPER).tex && \
		$(MAKE) pdf; \
	done
