
.PHONY: exec
exec: bI.blog

bI.blog: bI.bI ./bI$(EXE)
	./bI$(EXE) < $< > $@

C = core.cpp lex.yy.c parser.tab.cpp
H = bI.hpp

./bI$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: lexer.lpp
	flex $<
parser.tab.cpp: parser.ypp
	bison $<

