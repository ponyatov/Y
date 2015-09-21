#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

//#include <map>
#include <list>

using namespace std;

struct biObject {				// master class
	string *cls;					// class name
	string *val;					// generic string value
	biObject(const char*);
	biObject(const char*,char*);
	biObject(const char*,const char*);
	virtual string* dump();		// dump object in reloadable form
	virtual string* eval();		// evaluate (compute) object contents
};

struct biString: public biObject {
	biString(char*);
};

struct biPair: public biObject {
	biObject *A; biObject *B; 
	biPair(biObject*,biObject*);
	string* dump();
	string* eval();
};

struct biDirective: public biObject {
	biDirective(const char*,char*);
};

struct biSec: public biDirective {
	biSec(char*);
};

struct TEX {
	FILE* fh;
	string title,author,head,body,foot;
	TEX(const char*);
	~TEX();
	void W(string);
	void sec(string);
	string fix(string);
};
extern TEX tex;

extern int yylex();
extern char *yytext;
extern int yylineno;
extern int yyparse();
extern void yyerror(string);
#include "parser.tab.hpp"

void W(string*);
void W(string);

#endif // _bI_H

