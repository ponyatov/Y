
TEX = doc/manual.tex doc/header.tex doc/bib.tex doc/regtex.py
TEX += doc/files.tex doc/about.tex
TEX += doc/syntax.tex doc/types.tex
TEX += doc/eclipse.tex 
TEX += META-INF/icon.png META-INF/new_project.png META-INF/MANIFEST.MF
TEX += plugin.xml

.PHONY: all
all: pdf bI.html

bI.html: bI$(EXE) bI.bI
	@echo =============================
	./bI$(EXE) < bI.bI > bI.html
	head -n11 bI.html|tail -n6
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
	rm -f bI bI$(EXE) *.o lex.yy.c bI.tab.* *.log

bI$(EXE): lex.yy.c bI.tab.cpp bI.cpp bI.hpp
	$(CXX) $(CXXFLAGS) -o $@ lex.yy.c bI.tab.cpp bI.cpp

lex.yy.c: bI.lpp
	flex -8 bI.lpp
	
bI.tab.cpp: bI.ypp
	bison -d bI.ypp
