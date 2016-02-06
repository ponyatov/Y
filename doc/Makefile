TEX = bI.tex bib.tex
TEX += ../../texheader/ebook.tex
TEX += ../../texheader/colors.tex
TEX += ../../texheader/relsec.tex
TEX += ../../texheader/comp.tex ../../texheader/bI.sty
TEX += ../../texheader/misc.tex
TEX += intro.tex install.tex warning.tex compiler.tex 
TEX += files.tex core.tex lexer.tex parser.tex
TEX += headers.tex cppcore.tex ast.tex makes.tex comment.tex scalars.tex
TEX += composites.tex
TEX += func.tex op.tex
TEX += gui.tex
TEX += storage.tex
TEX += network.tex
TEX += math.tex
TEX += cad.tex
TEX += syntax.tex
TEX += llvm.tex

FIG = tmp/compiler.png tmp/meta.png

LST = tmp/lpp$(EXE) tmp/ypp$(EXE) tmp/hpp$(EXE)
LST += tmp/cpp$(EXE) tmp/mk$(EXE) tmp/bi$(EXE)
LPP = tmp/lpp.head tmp/lpp.opt tmp/lpp.rules tmp/lpp.spaces
LPP += tmp/lpp.linecomment tmp/lpp.blockcomment
YPP = tmp/ypp.head
HPP = tmp/hpp.once tmp/hpp.lex tmp/hpp.pars tmp/hpp.inc tmp/hpp.wrt tmp/hpp.env
HPP += tmp/hpp.list tmp/hpp.pair tmp/hpp.vector tmp/hpp.tuple
CPP = tmp/cpp.hdr tmp/cpp.wrt tmp/cpp.err tmp/cpp.main tmp/cpp.env
CPP += tmp/cpp.list tmp/cpp.pair tmp/cpp.vector tmp/cpp.tuple
MPP = tmp/mk.mod tmp/mk.clean tmp/mk.ch tmp/mk.cc
BIP = tmp/bi.linecomment tmp/bi.blockcomment

LATEX = pdflatex -halt-on-error
bI.pdf: $(TEX) $(FIG) $(LST) $(LPP) $(YPP) $(HPP) $(CPP) $(MPP) $(BIP)
	$(LATEX) $< && $(LATEX) $<
	
tmp/%.png: fig/%.dot
	dot -Tpng -o $@ $<
	
tmp/%$(EXE): lst/%.lpp
	flex -o $@.c $< && $(CXX) -o $@ $@.c
	
$(LPP): tmp/lpp$(EXE) ../lpp.lpp
	$< < ../lpp.lpp
$(YPP): tmp/ypp$(EXE) ../ypp.ypp
	$< < ../ypp.ypp
$(HPP): tmp/hpp$(EXE) ../hpp.hpp ../mingw32.hpp
	$< < ../hpp.hpp
$(CPP): tmp/cpp$(EXE) ../cpp.cpp ../mingw32.cpp
	$< < ../cpp.cpp
$(MPP): tmp/mk$(EXE)  ../Makefile
	$< < ../Makefile
$(BIP): tmp/bi$(EXE)  ../bI.bI
	$< < ../bI.bI
