## DO NOT EDIT: this file was autogened by bI language system ##

.PHONY: exec
exec: ./bI$(EXE)
	./bI$(EXE) < bI.sym > bI.log
	mkdir -p bI ; cp *.sym bI/bI.sym

.PHONY: clean
clean:
	rm -rf bI tmp ./bI$(EXE) bI.log 
	rm -rf bI.lex.?pp bI.tab.?pp *~ .*~

.PHONY: upgrade
upgrade:
	cp bI/README.md ./
	cp bI/.gitignore ./
	cp bI/Makefile ./
	cp bI/filetype.vim ./
	cp bI/syntax.vim ./
	cp bI/bI.ypp ./
	cp bI/bI.lpp ./
	cp bI/bI.hpp ./
	cp bI/bI.cpp ./

C = bI.cpp bI.tab.cpp bI.lex.cpp
H = bI.hpp bI.tab.hpp
./bI$(EXE): $(C) $(H)
	$(CXX) $(CXXFILES) -o $@ $(C)
bI.tab.cpp: bI.ypp
	bison $<
bI.lex.cpp: bI.lpp
	flex -o $@ $<
