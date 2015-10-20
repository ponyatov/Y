#ifndef _H_templ
#define _H_templ

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#ifdef __MINGW32__
#include <direct.h>
#endif
using namespace std;

struct object {
	string tag,value;
	object(string,string);
};

struct module: object {
	module(string);
};
extern module *curr_module;

extern int yylex();
extern int yylineno;
extern char *yytext;
extern void yyerror(string);
extern int yyparse();
#include "templ.tab.hpp"

void W(char);
void W(string);
void W(string*);

#endif // _H_templ

