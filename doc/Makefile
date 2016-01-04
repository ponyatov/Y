TEX = bI.tex
TEX += ../../texheader/ebook.tex
TEX += ../../texheader/colors.tex
TEX += ../../texheader/relsec.tex
TEX += ../../texheader/comp.tex
TEX += ../../texheader/misc.tex
TEX += intro.tex

LATEX = pdflatex -halt-on-error
bI.pdf: $(TEX)
	$(LATEX) $< && $(LATEX) $<