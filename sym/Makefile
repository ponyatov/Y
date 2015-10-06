
.PHONY: gen
gen: ../duralex/dura.exe
	$< < sym.bI > sym.bIog

.PHONY: all
all: ./sym$(EXE)

C = sym.cpp lex.yy.c sym.tab.cpp
H = sym.hpp sym.tab.hpp
./sym$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: sym.lpp
	flex $<
sym.tab.cpp: sym.ypp
	bison $<

.PHONY: upgrade
upgrade:
	cp sym/README.md ./
	cp sym/vimedit.bat ./
	cp sym/.gitignore ./
	cp sym/Makefile ./

