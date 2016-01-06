TEX = bI.tex bib.tex
TEX += ../../texheader/ebook.tex
TEX += ../../texheader/colors.tex
TEX += ../../texheader/relsec.tex
TEX += ../../texheader/comp.tex
TEX += ../../texheader/misc.tex
TEX += intro.tex install.tex warning.tex compiler.tex 
TEX += files.tex core.tex lexer.tex parser.tex
TEX += headers.tex cppcore.tex ast.tex makes.tex comment.tex scalars.tex

FIG = tmp/compiler.png tmp/meta.png

LST = tmp/lpp tmp/ypp tmp/hpp tmp/cpp tmp/mk
LPP = tmp/lpp.head tmp/lpp.opt tmp/lpp.rules tmp/lpp.spaces tmp/lpp.comment
YPP = tmp/ypp.head
HPP = tmp/hpp.once tmp/hpp.lex tmp/hpp.pars tmp/hpp.inc tmp/hpp.wrt tmp/hpp.env
CPP = tmp/cpp.hdr tmp/cpp.wrt tmp/cpp.err tmp/cpp.main tmp/cpp.env
MPP = tmp/mk.mod tmp/mk.clean tmp/mk.ch tmp/mk.cc

LATEX = pdflatex -halt-on-error
bI.pdf: $(TEX) $(FIG) $(LST) $(LPP) $(YPP) $(HPP) $(CPP) $(MPP)
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
$(CPP): tmp/cpp ../cpp.cpp
	$< < ../cpp.cpp
$(MPP): tmp/mk  ../Makefile
	$< < ../Makefile