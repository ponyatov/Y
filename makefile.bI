# universal Makefile template, lexical programs uses special sym/Makefile.bI
.file Makefile
\# $AUTOGEN$
.PHONY: exec
exec: ./$MODULE$\$(EXE)
	./$MODULE$\$(EXE)
.PHONY: clean
clean:
	rm -rf *~ .*~ ./$MODULE$\$(EXE) *.*log
C = $CFILES$
H = $HFILES$
./$MODULE$\$(EXE): \$(C) \$(H) \$(RES)
	\$(CXX) -I. -std=gnu++11 \$(CXXFILES) -o \$\@ \$(C) \$(RES)
res.res: rc.rc
	windres \$< -O coff -o \$\@
.eof
