#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <list>

#ifdef __MINGW32__
#else
#error no Linux
#endif

using namespace std;

struct biObject {
};

extern int yylex();
extern char *yytext;
extern int yylineno;
extern int yyparse();
extern void yyerror(string);
#include "parser.tab.hpp"

void W(string*);
void W(string);

#endif // _H_bI

