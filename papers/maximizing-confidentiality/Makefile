# Makefile for Encrypted Search Paper
# Author: Alexander Towell

.PHONY: all pdf clean cleanall view help clean-repo git-clean git-release

# Default target
all: pdf

# Main document name
MAIN = main

# Build the PDF
pdf:
	@echo "Building $(MAIN).pdf..."
	pdflatex -shell-escape $(MAIN).tex
	bibtex $(MAIN)
	pdflatex -shell-escape $(MAIN).tex
	pdflatex -shell-escape $(MAIN).tex
	@echo "✓ PDF built successfully: $(MAIN).pdf"

# Quick build (single pass, for testing)
quick:
	@echo "Quick building $(MAIN).pdf..."
	pdflatex -interaction=nonstopmode $(MAIN).tex
	@echo "✓ Quick build complete"

# Clean auxiliary files
clean:
	@echo "Cleaning auxiliary files..."
	rm -f *.aux *.log *.out *.toc *.lof *.lot *.loa
	rm -f *.bbl *.blg *.bcf *.run.xml
	rm -f *.glo *.gls *.glg *.ist *.acn *.acr *.alg
	rm -f *.fls *.fdb_latexmk *.synctex.gz
	rm -f *.xdy *.slo
	rm -f *~
	rm -rf _minted-$(MAIN)
	@echo "✓ Auxiliary files cleaned"

# Clean everything including PDF
cleanall: clean
	@echo "Removing PDF..."
	rm -f $(MAIN).pdf
	@echo "✓ All generated files removed"

# Clean obsolete section files
clean-sections:
	@echo "Cleaning obsolete section files..."
	@if [ -d sections ]; then \
		echo "  Found sections/ directory"; \
		ls sections/*.tex 2>/dev/null | wc -l | xargs -I {} echo "  Contains {} .tex files"; \
		echo "  These are no longer used (content is in main.tex)"; \
		read -p "  Remove sections/ directory? [y/N] " -n 1 -r; \
		echo; \
		if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
			rm -rf sections/; \
			echo "  ✓ Removed sections/ directory"; \
		fi; \
	else \
		echo "  No sections/ directory found"; \
	fi

# Clean research files
clean-research:
	@echo "Cleaning research directory..."
	@if [ -d research ]; then \
		echo "  Found research/ directory"; \
		ls research/ 2>/dev/null | wc -l | xargs -I {} echo "  Contains {} files"; \
		read -p "  Remove research/ directory? [y/N] " -n 1 -r; \
		echo; \
		if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
			rm -rf research/; \
			echo "  ✓ Removed research/ directory"; \
		fi; \
	else \
		echo "  No research/ directory found"; \
	fi

# Clean obsolete log files
clean-logs:
	@echo "Cleaning obsolete log files..."
	rm -f paper.log
	@echo "✓ Obsolete logs removed"

# Full repository cleanup
clean-repo: clean-sections clean-research clean-logs clean
	@echo "Cleaning other obsolete files..."
	@if [ -f gls-custom.tex ]; then \
		echo "  Found gls-custom.tex (may be obsolete)"; \
		read -p "  Remove gls-custom.tex? [y/N] " -n 1 -r; \
		echo; \
		if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
			rm -f gls-custom.tex; \
			echo "  ✓ Removed gls-custom.tex"; \
		fi; \
	fi
	@if [ -f main_backup.tex ]; then \
		echo "  Found main_backup.tex"; \
		rm -f main_backup.tex; \
		echo "  ✓ Removed main_backup.tex"; \
	fi
	@echo "✓ Repository cleanup complete"

# View the PDF
view: pdf
	@echo "Opening $(MAIN).pdf..."
	@if command -v xdg-open > /dev/null; then \
		xdg-open $(MAIN).pdf; \
	elif command -v open > /dev/null; then \
		open $(MAIN).pdf; \
	elif command -v evince > /dev/null; then \
		evince $(MAIN).pdf &; \
	else \
		echo "No PDF viewer found. Please open $(MAIN).pdf manually."; \
	fi

# Count statistics
stats:
	@echo "=== Paper Statistics ==="
	@echo "Main file: $(MAIN).tex"
	@wc -l $(MAIN).tex | awk '{print "  Lines: " $$1}'
	@grep -c "^\\\\section{" $(MAIN).tex | awk '{print "  Sections: " $$1}'
	@grep -c "^\\\\subsection{" $(MAIN).tex | awk '{print "  Subsections: " $$1}'
	@grep -c "\\\\begin{theorem}" $(MAIN).tex | awk '{print "  Theorems: " $$1}'
	@grep -c "\\\\begin{definition}" $(MAIN).tex | awk '{print "  Definitions: " $$1}'
	@grep -c "\\\\begin{algorithm}" $(MAIN).tex | awk '{print "  Algorithms: " $$1}'
	@grep -c "\\\\cite{" $(MAIN).tex | awk '{print "  Citations: " $$1}'
	@if [ -f $(MAIN).pdf ]; then \
		pdfinfo $(MAIN).pdf | grep "Pages:" | awk '{print "  PDF Pages: " $$2}'; \
		ls -lh $(MAIN).pdf | awk '{print "  PDF Size: " $$5}'; \
	fi
	@echo "  References: $$(grep -c "^@" references.bib)"

# Clean git repository (remove untracked LaTeX auxiliary files)
git-clean:
	@echo "Cleaning untracked LaTeX auxiliary files from git..."
	@git status --short | grep "^??" | grep -E "\.(aux|log|out|toc|lof|lot|loa|bbl|blg|bcf|run\.xml|glo|gls|glg|ist|acn|acr|alg|fls|fdb_latexmk|synctex\.gz|xdy|slo)$$" || true
	@read -p "Remove these untracked files? [y/N] " -n 1 -r; \
	echo; \
	if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
		git status --short | grep "^??" | grep -E "\.(aux|log|out|toc|lof|lot|loa|bbl|blg|bcf|run\.xml|glo|gls|glg|ist|acn|acr|alg|fls|fdb_latexmk|synctex\.gz|xdy|slo)$$" | awk '{print $$2}' | xargs -r rm -f; \
		echo "✓ Untracked auxiliary files removed"; \
	fi

# Git release workflow
git-release: clean pdf
	@echo "=== Git Release Workflow ==="
	@echo ""
	@echo "Step 1: Checking git status..."
	@git status --short
	@echo ""
	@echo "Step 2: Stage changes?"
	@read -p "Add modified and deleted files to staging? [y/N] " -n 1 -r; \
	echo; \
	if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
		git add -u; \
		echo "✓ Modified and deleted files staged"; \
	fi
	@echo ""
	@echo "Step 3: Stage new files?"
	@git status --short | grep "^??" && { \
		read -p "Add new/untracked files? [y/N] " -n 1 -r; \
		echo; \
		if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
			git add .; \
			echo "✓ New files staged"; \
		fi \
	} || echo "No untracked files to add"
	@echo ""
	@echo "Step 4: Current staging status:"
	@git status --short
	@echo ""
	@echo "Step 5: Create commit?"
	@read -p "Create commit? [y/N] " -n 1 -r; \
	echo; \
	if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
		read -p "Enter commit message: " commit_msg; \
		git commit -m "$$commit_msg" -m "🤖 Generated with Claude Code" -m "Co-Authored-By: Claude <noreply@anthropic.com>"; \
		echo "✓ Commit created"; \
	fi
	@echo ""
	@echo "Step 6: Create git tag?"
	@read -p "Create a version tag (e.g., v1.0)? [y/N] " -n 1 -r; \
	echo; \
	if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
		read -p "Enter tag name: " tag_name; \
		read -p "Enter tag message: " tag_msg; \
		git tag -a $$tag_name -m "$$tag_msg"; \
		echo "✓ Tag $$tag_name created"; \
	fi
	@echo ""
	@echo "✓ Release workflow complete!"
	@echo ""
	@echo "To push changes, run:"
	@echo "  git push origin master"
	@echo "  git push origin --tags"

# Help target
help:
	@echo "=== Encrypted Search Paper - Makefile ==="
	@echo ""
	@echo "Available targets:"
	@echo "  make           - Build the PDF (same as 'make pdf')"
	@echo "  make pdf       - Build the PDF with full bibliography processing"
	@echo "  make quick     - Quick build (single pass, for testing)"
	@echo "  make clean     - Remove auxiliary files (keep PDF)"
	@echo "  make cleanall  - Remove all generated files including PDF"
	@echo "  make view      - Build and open the PDF"
	@echo "  make stats     - Show paper statistics"
	@echo ""
	@echo "Repository cleanup:"
	@echo "  make clean-sections  - Remove obsolete sections/ directory"
	@echo "  make clean-research  - Remove research/ directory"
	@echo "  make clean-logs      - Remove obsolete log files"
	@echo "  make clean-repo      - Full repository cleanup (interactive)"
	@echo "  make git-clean       - Remove untracked LaTeX auxiliary files"
	@echo ""
	@echo "Git workflow:"
	@echo "  make git-release     - Interactive git release workflow (clean, build, commit, tag)"
	@echo ""
	@echo "  make help            - Show this help message"
