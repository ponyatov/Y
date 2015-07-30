EXE ?= .exe
FLEX ?= flex
BISON ?= bison

#def: clean

all: bI$(EXE)
	./$< < bI.bI

clean:
	rm -f parser.tab.* lex.yy.c bI$(EXE) *~

bI$(EXE):  cpp.cpp parser.tab.cpp lex.yy.c h.h
	$(CXX) $(CXXFLAGS) -o $@ cpp.cpp parser.tab.cpp lex.yy.c

parser.tab.cpp: parser.tab.hpp
parser.tab.hpp: parser.ypp
	$(BISON) -d parser.ypp

lex.yy.c: lexer.lpp parser.tab.hpp
	$(FLEX) lexer.lpp
