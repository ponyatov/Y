#ifndef _H_FSP
#define _H_FSP

#include "meta.hpp"
										// == std.includes ==
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

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
// -------------------------------------------------------------- par{}ameters
	map<string,Sym*> par;				// can be used as class slots
	void partag(Sym*);					// par[tag]=obj
// ------------------------------------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object as text
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// padding with tree decorators
// -------------------------------------------------------- compute (evaluate)
	virtual Sym* eval();
// ----------------------------------------------------------------- operators	
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* str();					// str(A)	to string representation
	virtual Sym* add(Sym*);				// A + B	add
	virtual Sym* div(Sym*);				// A / B	div
	virtual Sym* ins(Sym*);				// A += B	insert
};

extern void W(Sym*);								// \ ==== writers ====
extern void W(string);								// /

// ================================================================== SPECIALS
extern Sym* Rd;										// read mode
extern Sym* Wr;										// write mode

// =================================================================== SCALARS
struct Str:Sym { Str(string); string tagval();		// string
	Sym*eq(Sym*); Sym* add(Sym*); };

// ================================================================ COMPOSITES
struct List:Sym { List();							// [list]
	Sym*str(); Sym*div(Sym*); };

// =============================================================== FUNCTIONALS
// =================================================== operator
struct Op:Sym { Op(string); Sym* eval(); };
// =================================================== function
typedef Sym*(*FN)(Sym*);							// function ptr
struct Fn:Sym { Fn(string,FN); FN fn; Sym* at(Sym*); };// internal function

// ==================================================================== FILEIO
// =================================================== directory
struct Dir:Sym { Dir(Sym*); Sym* add(Sym*); };
extern Sym* dir(Sym*);
// =================================================== file
struct File:Sym { File(Sym*); FILE *fh; ~File();
	Sym* ins(Sym*); };
extern Sym* file(Sym*);

// =============================================================== OS SPECIFIC
#ifdef __MINGW32__
#include "../win32.hpp"								// win32/MinGW
#else
#include "linux.hpp"								// linux/posix
#endif

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

#endif // _H_FSP
