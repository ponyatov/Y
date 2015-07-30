EXE ?= .exe

all: bI$(EXE)

clean:
	rm -f parser.tab.* lex.yy.c bI$(EXE)

bI$(EXE):  cpp.cpp parser.tab.cpp lex.yy.c
	g++ -o $@ cpp.cpp parser.tab.cpp lex.yy.c

parser.tab.cpp: parser.tab.hpp
parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lex.yy.c: lexer.lpp parser.tab.hpp
	flex lexer.lpp

