#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <list>

#ifdef __MINGW32__
#else
#error no Linux
#endif

#include <map>
#include <list>

#ifdef __linux__
#include <sys/stat.h>
#endif // __linux__
#ifdef __MINGW32__
#include <direct.h>
#endif // __MINGW32__

using namespace std;

struct biObject {				// master class
	string *cls;					// class name
	string *val;					// generic string value
	biObject(const char*,char*);
//	biObject(string*,string*);
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

#endif // _bI_H

