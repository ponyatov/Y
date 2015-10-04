#ifndef _H_DURA
#define _H_DURA

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
#include <direct.h>
#endif
#include <map>
#include <vector>
using namespace std;

struct biObject {
	string tag, value;
	biObject(string,string);
	virtual string dump(int depth=0);
	virtual biObject* eval();
	string tagval(),pad(int);
};

extern map<string,biObject*> env;
extern void env_init();

struct biModule: biObject {
	biModule(string);
};
extern biModule *bi_module;

struct biFile: biObject {
	FILE *fh;
	biFile(string);
	~biFile();
	void W(char);
	void W(string*);
	void W(string);
	void W(biObject*);
};
extern biFile *bi_file;

struct biDirective: biObject {
	biDirective(string);
};

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
#include "dura.tab.hpp"

void W(char,bool to_file=true);
void W(string*,bool to_file=true);
void W(string,bool to_file=true);
void W(biObject*,bool to_file=true);

#endif // _H_DURA

