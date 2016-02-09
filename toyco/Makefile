MODULE ?= $(notdir $(CURDIR))
.PHONY: exec
exec: ./$(MODULE)$(EXE) $(MODULE).bI
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C += cpp.cpp ypp.tab.cpp lex.yy.c
H += hpp.hpp ypp.tab.hpp meta.hpp
L += 
CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"$(MODULE)\" -DOS=\"$(OS)\"
./$(MODULE)$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(L)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<

