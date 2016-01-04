.file Makefile
\# $AUTOGEN$
\# make parameters: EXE=.(exe|elf) RES=(res.res|) TAIL=("tail..."|)
.PHONY: exec
exec: ./$MODULE$\$(EXE)
	./$MODULE$\$(EXE) < test.bI > test.blog \$(TAIL)
#	./$MODULE$\$(EXE) < $MODULE$.bI > $MODULE$.blog $(TAIL)
.PHONY: clean
clean:
	rm -rf *~ .*~ ./$MODULE$\$(EXE) *.*log *.tab.\?pp lex.yy.c \$(RES)
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
