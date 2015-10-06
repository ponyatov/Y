
.title		pure symbolic script engine
.github		https://github.com/ponyatov/Y/tree/dev/sym

.module sym

.file README.md
$'# ',TITLE,'\n\n',$AUTHOR,'\n\nlicense:\t',LICENSE,'\n\ngithub:\t\t',GITHUB
.eof

.file .gitignore
*~
*.swp
$MODULE,EXE
$MODULE,.bIog
$'/',MODULE,'/'
lex.yy.c
$MODULE,.tab.cpp
$MODULE,.tab.hpp
.eof

.file Makefile
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

