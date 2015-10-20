## DO NOT EDIT: this file was autogened by bI language system ##

.PHONY: exec
exec: ./templ$(EXE)
	./templ$(EXE) < templ.sym > templ.log
	./templ$(EXE) < Makefile.sym > Makefile.log
	./templ$(EXE) < gitignore.sym > gitignore.log
	./templ$(EXE) < vim.sym > vim.log
	./templ$(EXE) < ypp.sym  > core.log
	./templ$(EXE) < lpp.sym >> core.log
	./templ$(EXE) < hpp.sym >> core.log
	./templ$(EXE) < cpp.sym >> core.log
	mkdir -p templ
	cp *.sym templ/

.PHONY: clean
clean:
	rm -rf templ tmp ./templ$(EXE) *.log 
	rm -rf templ.lex.?pp templ.tab.?pp *~ .*~

.PHONY: upgrade
upgrade:
	cp templ/README.md ./
	cp templ/.gitignore ./
	cp templ/Makefile ./
	cp templ/filetype.vim ../sym/
	cp templ/filetype.vim ./
	cp templ/syntax.vim ../sym/
	cp templ/syntax.vim ./

C = templ.cpp templ.tab.cpp templ.lex.cpp
H = templ.hpp templ.tab.hpp
./templ$(EXE): $(C) $(H)
	$(CXX) $(CXXFILES) -o $@ $(C)
templ.tab.cpp: templ.ypp
	bison $<
templ.lex.cpp: templ.lpp
	flex -o $@ $<

