
.title		pure symbolic script engine
.github		https://github.com/ponyatov/Y/tree/dev/sym

.module sym

.file README.md
$'# ',TITLE,'\n\n',$AUTHOR,'\n\nlicense:\t',LICENSE,'\n\ngithub:\t\t',GITHUB
.eof

.file .gitignore
*~
*.swp
$MODULE,'.exe'
$MODULE,'.elf'
$MODULE,.bIog
$'/',MODULE,'/'
lex.yy.c
$MODULE,.tab.cpp
$MODULE,.tab.hpp
.eof

.file Makefile

.PHONY: gen
gen: ../duralex/dura.exe
	\$< < sym.bI > sym.bIog

.PHONY: all
all: $'./',MODULE,'$(EXE)'

$'C = ',MODULE,'.cpp lex.yy.c ',MODULE,'.tab.cpp'
$'H = ',MODULE,'.hpp ',MODULE,'.tab.hpp'
$'./',MODULE,'$(EXE)',': $(C) $(H)'
	\$(CXX) \$(CXXFLAGS) -o \$\@ \$(C)
lex.yy.c: $MODULE,.lpp
	flex \$<
$MODULE,'.tab.cpp: ',MODULE,.ypp
	bison \$<

.PHONY: upgrade
upgrade:
$'\tcp ',MODULE,'/README.md ./'
$'\tcp ',MODULE,'/vimedit.bat ./'
$'\tcp ',MODULE,'/.gitignore ./'
$'\tcp ',MODULE,'/Makefile ./'

.eof

.file sym.ypp
.eof

.file sym.lpp
.eof

.file sym.hpp
.eof

.file sym.cpp
.eof

.file vimedit.bat
gvim -p $FILES/' '
.eof

