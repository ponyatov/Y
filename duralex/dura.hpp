#ifndef _H_DURA
#define _H_DURA

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
using namespace std;

struct sym {
	string tag, value;
	sym(string,string);
	virtual string dump(int depth=0);
};

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
#include "dura.tab.hpp"

void W(string*);
void W(sym*);

#endif // _H_DURA

