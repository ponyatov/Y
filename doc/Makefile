TEX = bI.tex
TEX += ../../texheader/ebook.tex
TEX += ../../texheader/colors.tex
TEX += ../../texheader/relsec.tex
TEX += ../../texheader/comp.tex
TEX += ../../texheader/misc.tex
TEX += intro.tex files.tex compiler.tex

FIG = tmp/compiler.png

LATEX = pdflatex -halt-on-error
bI.pdf: $(TEX) $(FIG)
#	ln -s ~/tmp tmp
	$(LATEX) $< && $(LATEX) $<
	
tmp/%.png: fig/%.dot
	dot -Tpng -o $@ $<