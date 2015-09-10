.PHONY: next
next: ./bI$(EXE) Makefile
	./bI$(EXE) < bI.bI > bI.log

.PHONY: clean
clean:
	rm -rf ./bI$(EXE) bI.log lex.yy.c bI.tab.?pp *~ .*~

CPP = bI.cpp lex.yy.c bI.tab.cpp
HPP = bI.hpp bI.tab.hpp

#CXXFLAGS += -Wno-write-strings

./bI$(EXE): $(CPP) $(HPP) Makefile 
	$(CXX) $(CXXFLAGS) -o $@ $(CPP)
lex.yy.c: bI.lpp
	flex $<
bI.tab.cpp bI.tab.hpp: bI.ypp
	bison $<

#TEX = doc/manual.tex doc/header.tex doc/bib.tex doc/regtex.py
#TEX += doc/files.tex doc/about.tex
#TEX += doc/syntax.tex doc/types.tex
#TEX += doc/eclipse.tex 
#TEX += META-INF/icon.png META-INF/new_project.png META-INF/MANIFEST.MF
#TEX += plugin.xml
#
#.PHONY: all
#all: pdf bI.html
#
#bI.html: bI$(EXE) bI.bI
#	@echo =============================
#	./bI$(EXE) < bI.bI > bI.html
#	@echo =============================
#	
#.PHONY: pdf
#pdf: doc/bI.pdf
#doc/bI.pdf: $(TEX)
#	cd doc &&\
#	mkdir -p ../tmp &&\
#	python regtex.py &&\
#	pdflatex -halt-on-error -output-directory ../tmp manual.tex &&\
#	pdflatex -halt-on-error -output-directory ../tmp manual.tex &&\
#	cp ../tmp/manual.pdf bI.pdf
