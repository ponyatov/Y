
.title		pure symbolic script engine
.github		https://github.com/ponyatov/Y/tree/dev/sym

.module sym

.sec+	Source files

.file README.md
$'# ',TITLE,'\n\n',$AUTHOR,'\n\nlicense:\t',LICENSE,'\n\ngithub:\t\t',GITHUB
.eof

.file .gitignore
*~
*.swp
$MODULE,'.exe'
$MODULE,'.elf'
$MODULE,.bIog
$MODULE,.toc
$'/',MODULE,'/','\n/tmp/'
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
$'\tcp ',MODULE,'/',MODULE,'.ypp ./'
$'\tcp ',MODULE,'/',MODULE,'.lpp ./'
$'\tcp ',MODULE,'/',MODULE,'.hpp ./'
$'\tcp ',MODULE,'/',MODULE,'.cpp ./'

.eof

.file sym.ypp
$'%{\n#include "',MODULE,'.hpp"\n%}'
.eof

.file sym.lpp
$'%{\n#include "',MODULE,'.hpp"'
\#define TC(X)	{ yylval.c = yytext[0]; 			return X; }
\#define T1(X)	{ yylval.c = yytext[1]; 			return X; }
\#define TS(X)	{ yylval.s = new string(yytext);	return X; }
%}
%option noyywrap
%option yylineno
%%
\\r				{}				/* drop DOS 0x0D char */
\#[^\\n]*\\n		{}				/* drop line comment */
\\\\.				T1(CHAR)		/* escape char prefixed */
\\n				TC(EOL)			/* end of line (CR) */
.				TC(CHAR)		/* any other char in undetected text */
%%
.eof

.file sym.hpp
\#ifndef _H_$MODULE
\#define _H_$MODULE
\#endif // _H_$MODULE
.eof

.file sym.cpp
$'#include "',MODULE,'.hpp"'
.eof

.file vimedit.bat
gvim -p $MODULE,'.bI ',FILES/' '
.eof

