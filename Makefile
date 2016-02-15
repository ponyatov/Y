## make parameters : OS=win32|linux EXE=.exe| TAIL=-n17|-n7
MODULE = $(notdir $(CURDIR))
.PHONY: $(MODULE).blog
$(MODULE).blog: $(MODULE).bI ./$(MODULE)$(EXE)
	./$(MODULE)$(EXE) < $< > $@ && tail $(TAIL) $@
C = ../cpp.cpp ypp.tab.cpp lex.yy.c
H = ../hpp.hpp ypp.tab.hpp
L = 
CXXFLAGS += -I.. -I. -std=gnu++11 \
	-DMODULE=\"$(MODULE)\" -DOS=\"$(OS)\" -DEXE=\"$(EXE)\"
./$(MODULE)$(EXE): $(C) $(H) ../Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(L)
ypp.tab.cpp: ../ypp.ypp
	bison $<
lex.yy.c: ../lpp.lpp
	flex $<
