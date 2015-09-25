#ifndef _H_SYM
#define _H_SYM

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <list>
#include <map>

#ifdef __MINGW32__
#include <direct.h>
#else
#include <sys/stat.h>
#endif

using namespace std;

struct sym {
	string cls;							// class
	string val;							// value
	list<sym*> nest;					// nested syms list
	sym(string,string);					// token constructor
	sym(sym*,sym*);						// pairing constructor
	virtual string dump(int depth=0);	// dump sym internals for debugging
	virtual string eval();				// evaluate (compute) object
};
extern map<string,sym*> env;

struct module: sym {
	void init();
	module(string);
	module(sym*,sym*);
};
extern module *curr_module;

struct ffile: sym {
	FILE *fh;
	ffile(sym*,sym*);
	~ffile();
};
extern ffile *curr_file;

extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "sym.tab.hpp"

extern void W(char  ,bool tofile=true);
extern void W(string,bool tofile=true);
extern void W(sym*  ,bool tofile=true);

#endif // _H_SYM

