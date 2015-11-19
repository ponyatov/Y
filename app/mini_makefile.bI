# universal Makefile template, lexical programs uses special sym/Makefile.bI
.file Makefile
\# $AUTOGEN$
\# make parameters: EXE=.(exe|elf) RES=(res.res|)
.PHONY: exec
exec: ./$MODULE$\$(EXE)
	./$MODULE$\$(EXE)
# < $MODULE$.config > $MODULE$.blog
.PHONY: clean
clean:
	rm -rf *~ .*~ ./$MODULE$\$(EXE) \$(RES) *.*log
C = $CFILES$
H = $HFILES$
./$MODULE$\$(EXE): \$(C) \$(H) \$(RES)
	\$(CXX) -I. -std=gnu++11 \$(CXXFILES) -o \$\@ \$(C) \$(RES)
#ypp.tab.cpp: ypp.ypp
#	bison \$<
#lex.yy.c: lpp.lpp
#	flex \$<
\$(RES): rc.rc
	windres \$< -O coff -o \$\@
.eof
