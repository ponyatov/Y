#ifndef _H_SKELEX
#define _H_SKELEX

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Env;
struct Sym {
	string tag;
	string val;
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	Env* env; void par(Sym*);
	string dump(int depth=0); string pad(int);
	virtual string tagval(); string tagstr();
	virtual Sym* str();
	virtual Sym* eval();
	virtual Sym* eq(Sym*);
	virtual Sym* at(Sym*);
	virtual Sym* add(Sym*);
	virtual Sym* div(Sym*);
	virtual Sym* ins(Sym*);
};
struct Env {
	Env(Env*); Env* next;
	map<string,Sym*> iron; Sym* lookup(Sym*);
	void par(Sym*); void set(string,Sym*);
	string dump();
};
extern Env glob_env;
extern void glob_init();

extern void W(Sym*);
extern void W(string);

struct Str:Sym { Str(string); string tagval(); Sym*eval(); Sym*add(Sym*); };

struct List:Sym { List(); Sym*div(Sym*); Sym*str(); };

struct Op:Sym { Op(string); Sym*eval(); };

typedef Sym*(*FN)(Sym*);
struct Fn:Sym { Fn(string,FN F); FN fn; Sym*at(Sym*); };

struct File:Sym { File(Sym*); static Sym*file(Sym*);
	Sym*eq(Sym*); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_SKELEX
