
.PHONY: sym
sym: ./sym$(EXE)
	mkdir -p tmp
	./sym$(EXE) < gitignore.sym > tmp/.gitignore
	./sym$(EXE) < Makefile.sym > tmp/Makefile
	./sym$(EXE) < sym.ypp.sym > tmp/sym.ypp
	./sym$(EXE) < sym.lpp.sym > tmp/sym.lpp
	./sym$(EXE) < sym.hpp.sym > tmp/sym.hpp
	./sym$(EXE) < sym.cpp.sym > tmp/sym.cpp
	cp *.sym tmp/

.PHONY: upgrade
upgrade: Makefile sym.ypp sym.hpp sym.hpp sym.cpp
	cp sym/.gitignore .gitignore
	cp sym/Makefile Makefile
	cp sym/sym.ypp sym.ypp
	cp sym/sym.lpp sym.lpp
	cp sym/sym.hpp sym.hpp
	cp sym/sym.cpp sym.cpp

.PHONY: clean
clean:
	rm -rf ./sym$(EXE) *~ lex.yy.c sym.tab.?pp

C = sym.cpp lex.yy.c sym.tab.cpp
H = sym.hpp sym.tab.hpp
./sym$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: sym.lpp
	flex $<
sym.tab.cpp: sym.ypp
	bison $<

