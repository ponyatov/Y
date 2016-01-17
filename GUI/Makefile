MODULE = $(notdir $(CURDIR))
OS = $(shell $(CXX) -dumpmachine)
.PHONY: exec
exec: ./$(MODULE)$(EXE) $(MODULE).bI
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C = ../cpp.cpp ../$(OS).cpp ypp.tab.cpp lex.yy.c
H = ../hpp.hpp ../$(OS).hpp ypp.tab.hpp
CXXFLAGS += -I.. -I. -std=gnu++11 -DMODULE=\"$(MODULE)\"
LIBS += -lgdi32
./$(MODULE)$(EXE): $(C) $(H) $(RES) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(LIBS) $(RES)
ypp.tab.cpp: ../ypp.ypp
	bison $<
lex.yy.c: ../lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@
