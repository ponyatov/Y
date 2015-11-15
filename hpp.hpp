#ifndef _H_PIL
#define _H_PIL

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
	#include <direct.h>
#else
	#include <sys/stat.h>
#endif
using namespace std;

struct sym {
	string tag;
	string value;
	sym(string,string);
	string dump(int depth=0);
	virtual sym* eval();
protected:
	string tagval();
	string pad(int);
};

struct Directive:sym { Directive(string); };

struct Module:sym { Module(string); };
struct File:sym {File(string); FILE *fh; ~File(); };

extern Module *curr_module;
extern File *curr_file;

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"
#define TC(X)	{ yylval.c = yytext[0]; return X; }
#define T1(X)	{ yylval.c = yytext[1]; return X; }
#define TS(X)	{ yylval.s = new string(yytext); return X; }
#define TO(C,X)	{ yylval.o = new sym(C,yytext); return X; }
#define TX(C,X)	{ yylval.o = new C(yytext); return X; }

void W(char   ,bool to_file=true);
void W(string ,bool to_file=true);
void W(string*,bool to_file=true);
void W(sym*   ,bool to_file=true);

#endif // _H_PIL
