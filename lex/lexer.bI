lex	= next + file @ 'lpp.lpp'
lex += '%{\n#include "hpp.hpp"\n%}\n'
lex += '%option noyywrap\n%option yylineno\n'
lex += 'S [\+\-]?\nN [0-9]+\n' 
lex += '%%\n'
#lex += lex_comment = '#[^\\n]*\t{}\t/* line comment */\n'
lex += '
[a-zA-Z0-9_]+		TOC(Sym,SYM)							/* symbol */
'

lex += '
[ \\t\\r\\n]+		{}									/* drop spaces */
.				{}									/* drop undetected chars */
%%
'
lex_hpp = '
													// == lexer interface ==
extern int yylex();									// parse next token
extern int yylineno;								// current source line
extern char* yytext;								// found token text
extern void incLude(Sym*inc);						// .include file
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
' 
