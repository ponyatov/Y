## make parameters: EXE=.exe| RES=res.res| TAIL=-n17|-n7 LLVM=|3.5
MODULE = $(notdir $(CURDIR))
MODULE = bI
OS = $(shell $(CXX) -dumpmachine)
.PHONY: exec
exec: ./$(MODULE)$(EXE) $(MODULE).bI
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
.PHONY: clean
clean:
	rm -rf ./$(MODULE)$(EXE) *.*log ypp.tab.?pp lex.yy.c $(RES)
C = cpp.cpp $(OS).cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp $(OS).hpp ypp.tab.hpp
CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"$(MODULE)\"
./$(MODULE)$(EXE): $(C) $(H) $(RES) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@

.PHONY: doc
doc:
	cd doc && $(MAKE)
