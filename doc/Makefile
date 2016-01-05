TEX = bI.tex
TEX += ../../texheader/ebook.tex
TEX += ../../texheader/colors.tex
TEX += ../../texheader/relsec.tex
TEX += ../../texheader/comp.tex
TEX += ../../texheader/misc.tex
TEX += intro.tex install.tex compiler.tex 
TEX += files.tex core.tex lexer.tex parser.tex
TEX += headers.tex cppcore.tex ast.tex comment.tex scalars.tex

FIG = tmp/compiler.png

LST = tmp/lpp tmp/ypp
LPP = tmp/lpp.head tmp/lpp.opt tmp/lpp.rules tmp/lpp.spaces tmp/lpp.comment
YPP = tmp/ypp.head
HPP = tmp/hpp.once tmp/hpp.lex tmp/hpp.pars tmp/hpp.inc

LATEX = pdflatex -halt-on-error
bI.pdf: $(TEX) $(FIG) $(LST) $(LPP) $(YPP) $(HPP)
#	ln -s ~/tmp tmp
	$(LATEX) $< && $(LATEX) $<
	
tmp/%.png: fig/%.dot
	dot -Tpng -o $@ $<
	
tmp/%: lst/%.lpp
	flex -o $@.c $< && $(CXX) -o $@ $@.c
	
$(LPP): tmp/lpp ../lpp.lpp
	$< < ../lpp.lpp
$(YPP): tmp/ypp ../ypp.ypp
	$< < ../ypp.ypp
$(HPP): tmp/hpp ../hpp.hpp
	$< < ../hpp.hpp