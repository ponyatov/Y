MODULE = $(notdir $(CURDIR))
OS = $(shell gcc -dumpmachine)
.PHONY: exec
exec: ./$(MODULE).exe
	./$(MODULE).exe
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"$(MODULE)\"
./$(MODULE).exe: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@
