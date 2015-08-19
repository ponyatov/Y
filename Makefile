
TEX = doc/manual.tex doc/header.tex doc/regtex.py doc/bib.tex
TEX += doc/files.tex doc/about.tex

.PHONY: all
all: pdf bI.log

bI.log: bI$(EXE)
	@echo =============================
	./bI$(EXE) < bI.bI > bI.log
	head -n5 bI.log
	@echo =============================
	
.PHONY: pdf
pdf: doc/bI.pdf
doc/bI.pdf: $(TEX)
	cd doc &&\
	mkdir -p ../tmp &&\
	python regtex.py &&\
	pdflatex -halt-on-error -output-directory ../tmp manual.tex &&\
	pdflatex -halt-on-error -output-directory ../tmp manual.tex &&\
	cp ../tmp/manual.pdf bI.pdf

.PHONY: clean
clean:
	rm -f bI$(EXE) *.o lex.yy.cc parser.tab.* *.log

bI$(EXE): lex.yy.c parser.tab.cpp core.cpp bI.hpp
	$(CXX) $(CXXFLAGS) -o $@ lex.yy.c parser.tab.cpp core.cpp

lex.yy.c: lexer.lpp
	flex -8 lexer.lpp
	
parser.tab.cpp: parser.ypp
	bison -d parser.ypp
