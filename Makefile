
.PHONY: all
all: bI$(EXE)
	./bI$(EXE) < bI.bI
	
.PHONY: clean
clean:
	rm -f bI$(EXE) *.o lex.yy.cc parser.tab.* *.log

bI$(EXE): lex.yy.c parser.tab.cpp core.cpp bI.hpp
	$(CXX) $(CXXFLAGS) -o $@ lex.yy.c parser.tab.cpp core.cpp

lex.yy.c: lexer.lpp
	flex lexer.lpp
	
parser.tab.cpp: parser.ypp
	bison -d parser.ypp
