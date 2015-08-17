
EXE ?= bI.exe

TEX = manual.tex tex.py 

.PHONY: autobuild
autobuild: pdf bI.log

.PHONY: clean
clean:
	echo $@
	rm -f parser.tab.* 
	rm -f lex.yy.cc 
	rm -f $(EXE)
	rm -f *.o

.PHONY: all
all: manual.pdf bI.log

bI.log: bI.bI $(EXE) Makefile
	$(EXE) < bI.bI > bI.log
	@head bI.log
	@echo ...
	@tail bI.log

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
$(EXE): core.cpp lex.yy.c parser.tab.cpp parser.tab.hpp bI.hpp
	g++ -o $@ core.cpp lex.yy.c parser.tab.cpp
	$@ < test.bI > test.log

parser.tab.cpp: parser.ypp
parser.tab.hpp: parser.ypp
	bison -d parser.ypp
lex.yy.c: lexer.lpp parser.tab.hpp
	flex lexer.lpp
