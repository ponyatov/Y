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
	cp PIL/hpp.hpp ./
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
#RES = res.res
./PIL$(EXE): $(C) $(H) $(RES)
	$(CXX) -I. -std=gnu++11 $(CXXFLAGS) -o $@ $(C) $(RES)
ypp.tab.cpp: ypp.ypp
	bison $<
lex.yy.c: lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@	
