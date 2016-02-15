.PHONY: log.log
log.log: src.src ./exe.exe
	./exe.exe < $< > $@ && tail $(TAIL) $@
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
./exe.exe: $(C) $(H) Makefile
	$(CXX) -std=gnu++11 -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
