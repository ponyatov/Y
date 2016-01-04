#ifndef _H_bI
#define _H_bI
														// == std.includes ==
#include <iostream>
#include <sstream>
#include <cstdlib>
//#include <cstdio>
//#include <cassert>
#include <vector>
#include <map>
#ifdef __MINGW32__
	#include <direct.h>
#else
	#include <sys/stat.h>
#endif

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
