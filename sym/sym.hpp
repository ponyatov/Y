#ifndef _H_SYM
#define _H_SYM

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <list>
#include <map>

#ifdef __MINGW32__
#include <direct.h>
#endif

using namespace std;

struct sym {
	string cls;				// class
	string val;				// value
	list<sym*> nest;		// nested syms list
	sym(string,string);		// token constructor
	sym(sym*,sym*);			// pairing constructor
	virtual string dump();	// dump sym internals for debugging
	virtual string eval();	// evaluate (compute) object
};

struct module: sym {
	module(string);
	module(sym*,sym*);
};
extern module curr_module;

extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "sym.tab.hpp"

extern void W(string);

#endif // _H_SYM

