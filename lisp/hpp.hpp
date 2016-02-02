#ifndef _H_LEXX
#define _H_LEXX
										// == std.includes ==
#include <iostream>
#include <cstdlib>
//#include <vector>
#include <map>
using namespace std;

struct Sym {							// == Abstract Symbolic Type (AST) ==
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// -------------------------------------------------------------- constructors
	Sym(string,string);					// <T:V>
	Sym(string);						// token
// ------------------------------------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object as text
	virtual string tagval();			// <T:V> header string
	string pad(int);					// padding with tree decorators
// -------------------------------------------------------- compute (evaluate)
	virtual Sym* eval();
// ----------------------------------------------------------------- operators	
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* add(Sym*);				// A + B	add
	virtual string str();
};

extern void W(Sym*);								// \ ==== writers ====
extern void W(string);								// /

// ================================================================== SPECIALS
extern Sym* nil;									// nil/false

// =================================================================== SCALARS
struct Str:Sym { Str(string); Sym*add(Sym*); };		// string

// ================================================================ COMPOSITES
struct Cons:Sym { Cons(Sym*,Sym*); Sym*A; Sym*D; 	// classic Lisp cons
	string dump(int); Sym*eval(); string str(); };

// =============================================================== FUNCTIONALS
// =================================================== function
typedef Sym*(*FN)(Sym*);							// function ptr
struct Fn:Sym { Fn(string,FN); FN fn; 				// internal function
	Sym* at(Sym*); };

// ==================================================================== FILEIO
// =================================================== file
struct File:Sym { File(Sym*); };
extern Sym* file(Sym*);

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

#endif /// _H_LEXX
