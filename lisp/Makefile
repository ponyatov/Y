MODULE ?= $(notdir $(CURDIR))
.PHONY: exec
exec: ./$(MODULE)$(EXE) $(MODULE).bI
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C += cpp.cpp ypp.tab.cpp lex.yy.c
H += hpp.hpp ypp.tab.hpp
CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"$(MODULE)\"
./$(MODULE)$(EXE): $(C) $(H) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) && strip --strip-all $@
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
