.PHONY: default
default: sym

.PHONY: sym
sym: sym$(EXE)
	sym/sym$(EXE) < sym/test.bI > bI.bIog
	sym/sym$(EXE) < lex.yy.c >> bI.bIog
sym$(EXE): bI.bIog
	cd sym &&\
	flex lexer.lpp &&\
	bison parser.ypp &&\
	$(CXX) $(CXXFLAGS) -o sym$(EXE) sym.cpp lex.yy.c parser.tab.cpp

.PHONY: exec
exec: bI.bIog

.PHONY: clean
clean:
	rm -rf *~ .*~ ./bI$(EXE) lex.yy.c parser.tab.?pp bI.tex tmp
	echo -n > bI.bIog

.PHONY: pdf
pdf: tmp/bI.pdf
bI.tex: bI.bIog
tmp/bI.pdf: bI.tex
	mkdir -p tmp
	pdflatex -output-directory tmp $<
	pdflatex -output-directory tmp $<

bI.bIog: bI.bI ./bI$(EXE)
	./bI$(EXE) < $< > $@

C = core.cpp lex.yy.c parser.tab.cpp
H = bI.hpp

./bI$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: lexer.lpp
	flex $<
parser.tab.cpp: parser.ypp
	bison $<

