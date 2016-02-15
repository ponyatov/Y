.PHONY: log.log
log.log: src.src ./exe.exe
	./exe.exe < $< > $@ && tail $(TAIL) $@
C = ../cpp.cpp ypp.tab.cpp lex.yy.c
H = ../hpp.hpp ypp.tab.hpp
F = -I.. -I. -std=gnu++11 -DMODULE=\"$(notdir $(CURDIR))\"
./exe.exe: $(C) $(H) Makefile
	$(CXX) $(F) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
