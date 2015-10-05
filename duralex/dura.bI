# comment

?C=list,.gitignore,README.md,Makefile
@C=list,.gitignore,README.md,Makefile
$C=list,.gitignore,README.md,Makefile

.title		symbolic program template generator
.github		https://github.com/ponyatov/Y/tree/dev/duralex

.module dura

.sec File templates

.file .gitignore
*~
*.swp
$MODULE
$(MODULE)$EXE
$(MODULE).bIog
/tmp/
lex.yy.c
$(MODULE).tab.cpp
$(MODULE).tab.hpp
.eof

.file README.md
\# $TITLE

$AUTHOR

license:    $LICENSE

github:     $GITHUB
.eof

.file Makefile
.PHONY: exec
exec: ./$(MODULE)\$(EXE)
	./$(MODULE)\$(EXE) < $(MODULE).bI > $(MODULE).bIog

.PHONY: upgrade
upgrade:
	cp dura/.gitignore ./
	cp dura/README.md ./
	cp dura/Makefile ./

C = $(MODULE).cpp lex.yy.c $(MODULE).tab.cpp
H = $(MODULE).hpp $(MODULE).tab.hpp

./$(MODULE)\$(EXE): \$(C) \$(H)
	\$(CXX) \$(CXXFLAGS) -o \$\@ \$(C)
lex.yy.c: $(MODULE).lpp
	flex \$<
$(MODULE).tab.cpp: $(MODULE).ypp
	bison \$<
.eof

