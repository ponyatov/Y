#ifndef _H_PIL
#define _H_PIL

#include "PIL/hpp.hpp"

/*
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/PIL"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI/PIL metasystem"
#define LOGO "![logo](logo64x64.png)"

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
#include <vector>
#include <map>
using namespace std;
*/

struct sym {
	string tag;
	string value;
	sym(string,string);
	string dump(int depth=0);
	virtual sym* eval();
	string tagval();
	string pad(int);
	vector<sym*> nest;
	void join(sym*);
};

extern map<string,sym*> env;
extern void env_init();

struct Directive:sym { Directive(string); };

struct Module:sym { Module(string); };
struct File:sym {File(string); FILE *fh; ~File(); };

extern Module *curr_module;
extern File *curr_file;

struct Int:sym { Int(string); sym* eval(); };
struct Num:sym { Num(string); sym* eval(); };

struct List:sym { List(); };
struct Op:sym {Op(string);};

extern int yylex();
extern int yylineno;
extern char* yytext;
extern void incFile(sym*);
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
