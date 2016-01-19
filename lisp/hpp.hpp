#ifndef _H_LISP
#define _H_LISP

										// == std.includes ==
#include <iostream>
//#include <sstream>
#include <cstdlib>
//#include <cstdio>
//#include <cassert>
#include <vector>
#include <map>
using namespace std;

struct Sym {							// == Abstract Symbolic Type (AST) ==
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// --------------------------------------- constructors
	Sym(string,string);					// <T:V>
	Sym(string);						// token
// --------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// --------------------------------------- dumping
	string dump(int depth=0);			// dump symbol object
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// tab padding
// --------------------------------------- evaluation (computing)
	virtual Sym* eval();
};

extern void W(Sym*);								// == writers ==
extern void W(string);
													// == lexer interface ==
extern int yylex();									// parse next token
extern int yylineno;								// current source line
extern char* yytext;								// found token text
extern void incLude(Sym*inc);						// .include file
#define TOC(C,X) { yylval.o = new C(yytext); return X; }// token macro in .lpp
													// == parser interface ==
extern int yyparse();								// run parser
extern void yyerror(string);						// error callback
#include "ypp.tab.hpp"								// token defines for lexer

// ================================================================== SPECIALS
extern Sym* nil;									// nil
struct Cons:Sym { Cons(Sym*,Sym*);					// classic Lisp cons element
	Sym* car; Sym* cdr; };
// =================================================================== SCALARS
struct Str:Sym { Str(string); string tagval(); };	// string

// ================================================================ COMPOSITES

// =============================================================== FUNCTIONALS
struct Op:Sym { Op(string); Sym* eval(); };			// operator

extern map<string,Sym*> env;						// == global env{}ironment ==
extern void env_init();								// init env{} on startup

#endif // _H_LISP
