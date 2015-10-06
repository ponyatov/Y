.PHONY: exec
exec: ./dura$(EXE)
	./dura$(EXE) < dura.bI > dura.bIog

.PHONY: all
all: ./dura$(EXE)

C = dura.cpp lex.yy.c dura.tab.cpp
H = dura.hpp dura.tab.hpp
./dura$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: dura.lpp
	flex $<
dura.tab.cpp: dura.ypp
	bison $<

.PHONY: upgrade
upgrade:
	cp dura/README.md ./
	cp dura/vimedit.bat ./
	cp dura/.gitignore ./
	cp dura/Makefile ./

