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
	cp sym/vimedit.bat ./
	cp sym/vimedit.rc ./
	cp sym/sym.rcwin32 ./
	cp sym/sym.ypp ./
	cp sym/sym.lpp ./
	cp sym/sym.hpp ./
	cp sym/sym.cpp ./

C = sym.cpp sym.tab.cpp sym.lex.cpp
H = sym.hpp sym.tab.hpp
RES ?= sym.res
./sym$(EXE): $(C) $(H) $(RES)
	$(CXX) $(CXXFILES) -o $@ $(C) $(RES)
sym.tab.cpp: sym.ypp
	bison $<
sym.lex.cpp: sym.lpp
	flex -o $@ $<
sym.res: sym.rcwin32
	windres sym.rcwin32 -O coff -o $@
##### makefile.sym #####
