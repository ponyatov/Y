.PHONY: exec
exec: ./PIL$(EXE)
	./PIL$(EXE) < pil.pil > log.pilog
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
./PIL$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
