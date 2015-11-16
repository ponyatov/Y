# DO NOT EDIT: this file was autogened by bI
.PHONY: exec
exec: ./bI$(EXE)
	./bI$(EXE) < pil.pil > pil.blog
.PHONY: clean
clean:
	rm -rf *~ .*~ *.*log ./bI$(EXE) *.tab.?pp lex.yy.c
.PHONY: upgrade
upgrade:
	cp bI/Makefile ./
	cp bI/.gitignore ./
	cp bI/README.md ./
	cp bI/hpp.hpp ./
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
#RES = res.res
./bI$(EXE): $(C) $(H) $(RES)
	$(CXX) -I. -std=gnu++11 $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@
