
.title		pure symbolic script engine
.github		https://github.com/ponyatov/Y/tree/dev/sym

.module sym

.sec	Kernel source file templates

.sec-	Project files

.file README.md
$'# ',TITLE
\#\# (self-computed source files)
$'\n',$AUTHOR,'\n\nlicense:\t',LICENSE,'\n\ngithub:\t\t',GITHUB
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
\# $AUTOGEN
\# <module:$MODULE,'>'

.PHONY: gen
gen: ../duralex/dura.exe
$'\t$< < ',MODULE,'.bI > ',MODULE,'.bIog'

.PHONY: all
all: $'./',MODULE,'$(EXE)'
$'\t','./',MODULE,'$(EXE)',' < ',MODULE,'.bI > ',MODULE,'.bIog'

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
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'%{\n#include "',MODULE,'.hpp"\n%}'
%defines
%union {
	char c;
	string *s;
}
%token <c> CHAR EOL
%token <s> STR
%%
$MODULE,' :'
$'\t| ',MODULE,' STR\t{ W($2); }'
$'\t| ',MODULE,' EOL\t{ W($2); }'
$'\t| ',MODULE,' CHAR\t{ W($2); }'
%%
.eof

.file sym.lpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'%{\n#include "',MODULE,'.hpp"'
\#define TC(X)		{ yylval.c = yytext[0]; 			return X; }
\#define T1(X)		{ yylval.c = yytext[1]; 			return X; }
\#define TS(X)		{ yylval.s = new string(yytext);	return X; }
string StringBuffer;
%}
%option noyywrap
%option yylineno

%x ss

%%
\\r				{}				/* drop DOS 0x0D char */
\#[^\\n]*\\n		{}				/* drop line comment */
\\\\.				T1(CHAR)		/* escape char prefixed */

'				{BEGIN(ss); StringBuffer="\'";}
<ss>'			{BEGIN(INITIAL);
				yylval.s = new string(StringBuffer+"\'"); return STR;}
<ss>.			{StringBuffer += yytext;}

\\n				TC(EOL)			/* end of line (CR) */
.				TC(CHAR)		/* any other char in undetected text */
%%
.eof

.file sym.hpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
\#ifndef _H_$MODULE
\#define _H_$MODULE

\#define MODULE "$MODULE,'"'
\#define TITLE "$TITLE,'"'
\#define AUTHOR "$AUTHOR,'"'
\#define LICENSE "$LICENSE,'"'
\#define GITHUB "$GITHUB,'"'
\#define AUTOGEN "DO NOT EDIT: this file was autogened by bI language system"

\#include <map>					// \\ required std includes
\#include <vector>
\#include <iostream>
\#include <cstdlib>				// /
\#ifdef __MINGW32__				// \\ win32 specific
\#include <direct.h>				// /
\#else							// \\ Linux & others POSIX-compatibles
\#include <sys/stat.h>			// /
\#endif
using namespace std;
								// syntax core interface
extern int yylex();				// \\ lexer
extern char *yytext;			// 		regexp-parsed text
extern int yylineno;			// /	current line number 
extern int yyparse();			// \\ parser
extern void yyerror(string);	// syntax error callback
$'#include "',MODULE,'.tab.hpp"'			// / parser defines
								
void W(char);					// \\ writers
void W(string);					// //
void W(string*);				// //
\#endif // _H_$MODULE
.eof

.sec-	Low-Level symbolic engine code in C++

.file sym.cpp
$'/* ',AUTOGEN,' */'
$'/* <module:',MODULE,'> */'
$'#include "',MODULE,'.hpp"'
void W(char    c) { cout <<  c; }
void W(string  s) { cout <<  s; }
void W(string *s) { cout << *s; }
void yyerror(string msg) {
	cout << "\\n\\n" << msg << "\#" << yylineno << ":" << yytext << "\\n\\n";
	cerr << "\\n\\n" << msg << "\#" << yylineno << ":" << yytext << "\\n\\n";
	exit(-1); }
int main(int argc, char *argv[]) {
	cout << "\# " << AUTOGEN << "\\n";
	cout << "\# <module:" << MODULE << ">\\n";
	cout << "\# argv[0]:\\t" << argv[0] << "\\n\\n";
	return yyparse();
}
.eof

.sec-	.bat for module edit in (g)vim tabs

.file vimedit.bat
gvim -p $MODULE,'.bI ',MODULE,'.bIog ',MODULE,'.toc ',FILES/' '
.eof

