
.title		pure symbolic calculated source files
.github		https://github.com/ponyatov/Y/tree/dev/duralex/pure

.module pure

.title

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

.file pure.lpp
$'%{\n#include "',MODULE,'.hpp"'
\#define TC(X)		{ yylval.c = yytext[0]; return X; }
%}
%option noyywrap
%option yylineno
%%
\\n		TC(EOL)
.		TC(CHAR)
%%
.eof

.file pure.ypp
$'%{\n#include "',MODULE,'.hpp"\n%}'
%defines
%union {
	char c;
}
%token <c> CHAR EOL
%%
$MODULE :
	| $MODULE EOL		{ W(\$2); }
	| $MODULE CHAR		{ W(\$2); }
;
%%
.eof

.file pure.hpp
\#ifndef _H_$MODULE
\#define _H_$MODULE

\#include <iostream>
\#include <sstream>
\#include <cstdlib>
\#include <cstdio>
\#include <cassert>
\#ifdef __MINGW32__
\#include <direct.h>
\#endif
\#include <map>
\#include <vector>
using namespace std;

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
$'#include "',$MODULE,'.tab.hpp"'
void W(char,bool to_file=true);
#void W(string,bool to_file=true);
\#endif // _H_MODULE
.eof

.file pure.cpp
$'#include "',MODULE,'.hpp"'
$'void yyerror(string err) {'
$'\tcerr << "\\n\\n" << err << " # " << yylineno << " : " << yytext << "\\n";'
$'\texit(-1);\n}'
void W(char      c,bool to_file)	{ cout << c; }
$'int main() { return yyparse(); }'
.eof

.file Makefile
$'C = ',$MODULE,'.cpp lex.yy.c ',MODULE,'.tab.cpp'
$'H = ',$MODULE,'.hpp ',MODULE,'.tab.hpp'
$'./',MODULE,EXE,': $(C) $(H)\n\t$(CXX) $(CXXFLAGS) -o $@ $(C)'
$'lex.yy.c: ',$MODULE,'.lpp\n\tflex $<'
$MODULE,'.tab.cpp: ',MODULE,'.ypp\n\tbison $<'
.eof

.file vimedit.bat
gvim -p $FILES/' '
.eof


.module dura
.title		symbolic program template generator
.github		https://github.com/ponyatov/Y/tree/dev/duralex

.sec File templates

.file .gitignore
*~
*.swp
$MODULE,.elf
$MODULE,EXE
$MODULE,.bIog
$'/',MODULE,'/'
/tmp/
lex.yy.c
$MODULE,.tab.cpp
$MODULE,.tab.hpp
.eof

.file README.md
\# $TITLE

$AUTHOR

license:    $LICENSE

github:     $GITHUB
.eof

$C=dura.cpp,lex.yy.c,dura.tab.cpp
$H=dura.hpp,dura.tab.hpp

.file Makefile
.PHONY: exec
exec: $'./',MODULE,'$(EXE)'
	$'./',MODULE,'$(EXE)',' < ',MODULE,'.bI > ',MODULE,'.bIog'

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

.file dura.lpp
%{
$'#include "',$MODULE,'.hpp"'
\#define TC(X)		{ yylval.c = yytext[0]; return X; }
\#define T1(X)		{ yylval.c = yytext[1]; return X; }
\#define TS(X)		{ yylval.s = new string(yytext); return X; }
%}
%option noyywrap
%option yylineno
%%
\\\\.			T1(CHAR)
\#[^\\n]*\\n	{}
\\n				TC(EOL)
.				TC(CHAR)
%%
.eof

@CHAR=class(char)
@STRING=class(string)

@Symbol=class(Symbol)

.file dura.ypp
%{
$'#include "',$MODULE,'.hpp"'
%}

%defines

%union {
	$CHAR c;
	$STRING *s;
#	$Symbol *o;
}

%token <c> CHAR EOL

%%
x :
	| x EOL		{ W(\$2); }
	| x CHAR	{ W(\$2); }
;
%%
.eof

.file dura.hpp
\#ifndef _H_$MODULE
\#define _H_$MODULE

\#include <iostream>
\#include <sstream>
\#include <cstdlib>
\#include <cstdio>
\#include <cassert>
\#ifdef __MINGW32__
\#include <direct.h>
\#endif
\#include <map>
\#include <vector>
using namespace std;

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
$'#include "',MODULE,'.tab.hpp"'

void W(char,bool to_file=true);
void W(string*,bool to_file=true);
void W(string,bool to_file=true);
#void W(biObject*,bool to_file=true);

\#endif // _H_$MODULE
.eof

.file dura.cpp
$'#include "',$MODULE,'.hpp"'

void W(char      c,bool to_file)	{ cout << c ; }
#	if (to_file&&bi_file) bi_file->W(c); }

void yyerror(string err) {
	cerr << "\\n\\n" << err << " \# " << yylineno << " : " << yytext << "\\n";
	exit(-1);
}

int main() { return yyparse(); }
.eof

.file vimedit.bat
gvim -p $FILES/' '
.eof

