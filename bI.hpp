#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <cstdlib>
#include <cstdio>

//#include <map>
#include <list>

#ifndef __MINGW32__
#error linux
#endif // __MINGW32__

using namespace std;

struct biObject {				// master class
	string *cls;					// class name
	string *val;					// generic string value
	biObject(const char*);
	biObject(const char*,char*);
	virtual string* dump();		// dump object in reloadable form
	virtual string* eval();		// evaluate (compute) object contents
};

struct biString: public biObject {
	biString(char*);
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

