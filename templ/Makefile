.PHONY: exec
exec: ./templ$(EXE)
	./templ$(EXE) < templ.sym > templ.log
C = templ.cpp templ.tab.cpp templ.lex.cpp
H = templ.hpp templ.tab.hpp
./templ$(EXE): $(C) $(H)
	$(CXX) $(CXXFILES) -o $@ $(C)
templ.tab.cpp: templ.ypp
	bison $<
templ.lex.cpp: templ.lpp
	flex -o $@ $<

