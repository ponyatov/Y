
.PHONY: exec
exec: ./interp$(EXE)
	./interp$(EXE) < test.in > test.out

C = interp.cpp lex.yy.c parser.tab.cpp
H = interp.hpp parser.tab.hpp

./interp$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: lexer.lpp
	flex $<
parser.tab.cpp: parser.ypp
	bison $<

