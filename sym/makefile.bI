.file Makefile
\# $AUTOGEN$
.PHONY: exec
exec: ./$MODULE$\$(EXE)
	./$MODULE$\$(EXE) < $MODULE$.bI > $MODULE$.blog
.PHONY: clean
clean:
	rm -rf *~ .*~ *.*log ./$MODULE$\$(EXE) *.tab.\?pp lex.yy.c
.PHONY: upgrade
upgrade:
	cp $MODULE$/Makefile ./
	cp $MODULE$/.gitignore ./
	cp $MODULE$/README.md ./
	cp $MODULE$/hpp.hpp ./
C = cpp.cpp ypp.tab.cpp lex.yy.c
H = hpp.hpp ypp.tab.hpp
\#RES = res.res
./$MODULE$\$(EXE): \$(C) \$(H) \$(RES)
	\$(CXX) -I. -std=gnu++11 \$(CXXFLAGS) -o \$\@ \$(C) \$(RES)
ypp.tab.cpp: ypp.ypp
	bison \$<
lex.yy.c: lpp.lpp
	flex \$<
res.res: rc.rc
	windres \$< -O coff -o \$\@	
.eof
