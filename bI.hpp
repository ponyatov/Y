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

struct biObject {				// master class
	virtual string* dump();		// dump object in reloadable form
	virtual string* eval();		// evaluate (compute) object contents
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

