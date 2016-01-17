#ifndef _H_WIN32TEST
#define _H_WIN32TEST

#include <iostream>
#include <cassert>
#include <windows.h>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag;
	string val;
	Sym(string,string);
	string dump();
};
struct Cons:Sym { Cons(Sym*,Sym*); };

extern void W(Sym*);
extern void W(string);

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
#include "ypp.tab.hpp"

extern HINSTANCE hApp;

#endif // _H_WIN32TEST
