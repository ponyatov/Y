
EXE ?= bI.exe

TEX = manual.tex tex.py 

.PHONY: autobuild
autobuild: exe

.PHONY: clean
clean:
	echo $@
	rm -f parser.tab.* 
	rm -f lex.yy.cc 
	rm -f $(EXE)
	rm -f *.o

.PHONY: all
all: manual.pdf exe

.PHONY: pdf
pdf: manual.pdf
manual.pdf: $(TEX)
	mkdir -p tmp
	python tex.py
	pdflatex -halt-on-error -output-directory tmp manual.tex
	pdflatex -halt-on-error -output-directory tmp manual.tex
	cp tmp/$@ $@

.PHONY: exe
exe: $(EXE)
$(EXE): lexer.lpp parser.ypp core.cpp bI.hpp test.bI
	bison -d parser.ypp
	flex lexer.lpp
	g++ -o $@ core.cpp lex.yy.c parser.tab.cpp
	$@ < test.bI > test.log
	@head test.log
	@echo ...
	@tail test.log
