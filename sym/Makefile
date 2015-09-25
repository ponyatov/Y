
log.log: sym.sym ./sym$(EXE) 
	./sym$(EXE) < $< > $@

C = sym.cpp sym.tab.cpp lex.yy.c
H = sym.hpp sym.tab.hpp

./sym$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
sym.tab.cpp: sym.ypp
	bison $<
lex.yy.c: sym.lpp
	flex $<

