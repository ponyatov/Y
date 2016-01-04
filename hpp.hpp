#ifndef _H_bI
#define _H_bI

														// == lexer interface ==
extern int yylex();										// parse next token
extern int yylineno;									// current source line
extern char* yytext;									// found token text
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
														// == parser interface ==
extern int yyparse();									// run parser
extern void yyerror(std::string);						// error callback
#include "ypp.tab.hpp"									// token defines for lexer

#endif // _H_bI
