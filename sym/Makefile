sym.log: sym.sym ./sym$(EXE) 
	./sym$(EXE) < $< > $@

.PHONY: clean
clean:
	rm -rf *~ .*~ ./sym$(EXE) *.log lex.yy.c sym.tab.?pp tmp

C = sym.cpp sym.tab.cpp lex.yy.c
H = sym.hpp sym.tab.hpp

./sym$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
sym.tab.cpp: sym.ypp
	bison $<
lex.yy.c: sym.lpp
	flex $<

