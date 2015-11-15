# DO NOT EDIT: this file was autogened by PIL
.PHONY: exec
exec: ./PIL$(EXE)
	./PIL$(EXE) < pil.pil > log.pilog
.PHONY: clean
clean:
	rm -rf *~ .*~ *.log ./PIL$(EXE) *.pilog ypp.tab.?pp lex.yy.c
.PHONY: upgrade
upgrade:
	cp PIL/Makefile ./
	cp PIL/.gitignore ./
	cp PIL/README.md ./
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
./PIL$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
