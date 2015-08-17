TEX = manual.tex tex.py 

.PHONY: autobuild
autobuild: exe

.PHONY: all
all: manual.pdf exe

.PHONY: pdf
pdf: manual.pdf
manual.pdf: $(TEX)
	mkdir -p tmp
	python tex.py
	pdflatex -halt-on-error -output-directory tmp manual.tex
	pdflatex -halt-on-error -output-directory tmp manual.tex
#	mv tmp/$@ $@

.PHONY: exe
exe: bI.exe 
bI.exe: lexer.lpp parser.ypp core.cpp bI.hpp test.bI
	bison -d parser.ypp
	flex lexer.lpp
	g++ -o $@ core.cpp lex.yy.c parser.tab.cpp
	$@ < test.bI > test.log
	tail test.log
