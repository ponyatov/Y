#ifndef _H_SYM
#define _H_SYM

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "sym.tab.hpp"

#endif // _H_SYM

