.PHONY: exec
exec: ./dura$(EXE)
	./dura$(EXE) < dura.bI > dura.bIog

.PHONY: upgrade
upgrade:
	cp dura/.gitignore ./
	cp dura/README.md ./
	cp dura/Makefile ./

C = dura.cpp lex.yy.c dura.tab.cpp
H = dura.hpp dura.tab.hpp

./dura$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $