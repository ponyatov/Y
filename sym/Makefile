## DO NOT EDIT: this file was autogened by bI/sym language system ##
##### makefile.sym #####

.PHONY: exec
exec: ./sym$(EXE)
	./sym$(EXE) < sym.sym > sym.log
	cp *.sym sym/

.PHONY: clean
clean:
	rm -rf sym tmp ./sym$(EXE) sym.log 
	rm -rf sym.lex.?pp sym.tab.?pp *~ .*~

.PHONY: upgrade
upgrade:
	cp sym/README.md ./
	cp sym/.gitignore ./
	cp sym/Makefile ./
	cp sym/filetype.vim ./
	cp sym/syntax.vim ./
	cp sym/sym.ypp ./
	cp sym/sym.lpp ./
	cp sym/sym.hpp ./
	cp sym/sym.cpp ./

C = sym.cpp sym.tab.cpp sym.lex.cpp
H = sym.hpp sym.tab.hpp
./sym$(EXE): $(C) $(H)
	$(CXX) $(CXXFILES) -o $@ $(C)
sym.tab.cpp: sym.ypp
	bison $<
sym.lex.cpp: sym.lpp
	flex -o $@ $<

##### makefile.sym #####
