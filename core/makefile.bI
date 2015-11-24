.file Makefile
\# $AUTOGEN$
\# make parameters: EXE=.(exe|elf) RES=(res.res|)
.PHONY: exec
exec: ./$MODULE$\$(EXE)
	./$MODULE$\$(EXE) < test.bI > test.blog
	./$MODULE$\$(EXE) < $MODULE$.bI > $MODULE$.blog
.PHONY: clean
clean:
	rm -rf *~ .*~ *.*log ./$MODULE$\$(EXE) *.tab.\?pp lex.yy.c \$(RES)
C = $CFILES$ ypp.tab.cpp lex.yy.c
H = $HFILES$ ypp.tab.hpp
\#RES = res.res
./$MODULE$\$(EXE): \$(C) \$(H) \$(RES)
	\$(CXX) -I. -std=gnu++11 \$(CXXFILES) -o \$\@ \$(C) \$(RES)
ypp.tab.cpp: ypp.ypp
	bison \$<
lex.yy.c: lpp.lpp
	flex \$<
\$(RES): rc.rc
	windres \$< -O coff -o \$\@
.eof
