MODULE = llx
.PHONY: exec
exec: ./llx.exe llx.bI
	./llx.exe < llx.bI > llx.blog
C = cpp ypp.tab.cpp lex.yy.c
H = hpp ypp.tab.hpp meta.hpp
CXXFLAGS += -I. -std=gnu++11 -DMODULE="\"llx\"" -DOS="win32"
./llx.exe: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<

.PHONY: upgrade
upgrade:
	cp next/Makefile ./
	cp next/README.md ./
	cp next/meta.hpp ./
