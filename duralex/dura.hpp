#ifndef _H_DURA
#define _H_DURA

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
#include <direct.h>
#endif
using namespace std;

struct biObject {
	string tag, value;
	biObject(string,string);
	virtual string dump(int depth=0);
};

struct biModule: biObject {
	biModule(string);
};
extern biModule *bi_module;

struct biFile: biObject {
	FILE *fh;
	biFile(string);
	~biFile();
};
extern biFile *bi_file;

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
#include "dura.tab.hpp"

void W(string*);
void W(string);
void W(biObject*);

#endif // _H_DURA

