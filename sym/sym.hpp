#ifndef _H_SYM
#define _H_SYM

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <list>
#include <map>

using namespace std;

struct sym {
	string cls;				// class
	string val;				// value
	list<sym*> nest;		// nested syms list
	sym(string,char*);		// token constructor
	virtual string dump();	// dump sym internals for debugging
	virtual string eval();	// evaluate (compute) object
};

extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "sym.tab.hpp"

#endif // _H_SYM

