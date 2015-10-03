#ifndef _H_INTERP
#define _H_INTERP

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

// \\\ lexer/parser header block
extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "parser.tab.hpp"

#endif // _H_INTERP

