#ifndef _H_TOYCO
#define _H_TOYCO
#include "meta.hpp"
										// == std.includes ==
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

extern ofstream llfile;

struct Sym {							// == Abstract Symbolic Type (AST) ==
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// -------------------------------------------------------------- constructors
	Sym(string,string);					// <T:V>
	Sym(string);						// token
// --------------------------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// ------------------------------------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object as text
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// padding with tree decorators
// -------------------------------------------------------- compute (evaluate)
	virtual Sym* eval();
// ----------------------------------------------------------------- operators	
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* add(Sym*);				// A + B	add
// ------------------------------------------------------ compile to LLVM code
	virtual Sym* llvm();
};

extern void W(Sym*);					// \ ==== writers ====
extern void W(string);					// /

// =================================================================== SCALARS
struct Scalar:Sym { Scalar(string,string);			// scalars common class
	Sym*eval(); };									// block env[] lookup

struct Str:Scalar { Str(string); string tagval();
	Sym*add(Sym*); Sym* llvm(); };

struct LL:Sym { LL(string); string tagval(); };

struct Int:Scalar { Int(string); };
struct Num:Scalar { Num(string); };

// =============================================================== FUNCTIONALS
// =================================================== operator
struct Op:Sym { Op(string); Sym* eval(); Sym*llvm(); };

// ====================================================== GLOBAL ENV{}IRONMENT
extern map<string,Sym*> env;
extern void env_init();								// init env{} on startup

// ========================================================== PARSER INTERFACE
													// == lexer interface ==
extern int yylex();									// parse next token
extern int yylineno;								// current source line
extern char* yytext;								// found token text
extern void incLude(Sym*inc);						// .include file
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
													// == parser interface ==
extern int yyparse();								// run parser
extern void yyerror(string);						// error callback
#include "ypp.tab.hpp"								// token defines for lexer

#endif // _H_TOYCO

