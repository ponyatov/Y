#ifndef _H_bI
#define _H_bI
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

// ============================================== ABSTRACT SYMBOLIC TYPE (AST)
struct Sym {
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// -------------------------------------------------------------- constructors
	Sym(string,string);					// <T:V>
	Sym(string);						// token
// --------------------------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*); void pop();
// -------------------------------------------------------------- par{}ameters
	map<string,Sym*> pars;
	void par(Sym*);						// add parameter 
// ------------------------------------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object as text
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// padding with tree decorators
// ------------------------------------------------------ lambda via rewriting
	virtual Sym* copy();				// copy
	virtual bool match(Sym*);			// pattern matching
	Sym* replace(Sym*,Sym*);			// nested symbols overwrite
// -------------------------------------------------------- compute (evaluate)
	virtual Sym* eval();
// ----------------------------------------------------------------- operators	
	virtual Sym* str();					// str(A)	string representation
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* add(Sym*);				// A + B	add
	virtual Sym* div(Sym*);				// A / B	div
	virtual Sym* ins(Sym*);				// A += B	insert
};
// ====================================================== GLOBAL ENV{}IRONMENT
extern map<string,Sym*> glob;						// global env{}
extern void env_init();

extern void W(Sym*);								// \ ==== writers ====
extern void W(string);								// /

// ================================================================= DIRECTIVE
struct Directive:Sym { Directive(string); Sym*eval(); string tagval(); };

// =================================================================== SCALARS
struct Scalar:Sym { Scalar(string,string);			// scalars common class
	Sym*eval(); };									// block env[] lookup

struct Str:Scalar { Str(string); string tagval();	// string
	Sym*eq(Sym*); Sym* add(Sym*);
	static Sym* upcase(Sym*); };					// to UPCASE

// ================================================================ COMPOSITES
// =================================================== [list]
struct List:Sym { List(); Sym*str(); Sym*div(Sym*); };

// =============================================================== FUNCTIONALS
// =================================================== operator
struct Op:Sym { Op(string); Sym*eval(); Sym*copy(); };
// =================================================== {la:mbda}
struct Lambda:Sym { Lambda(); Sym*eval(); Sym*at(Sym*); };
// =================================================== internal function
typedef Sym*(*FN)(Sym*);							// function ptr
struct Fn:Sym { Fn(string,FN); FN fn; Sym*at(Sym*); };

// ==================================================================== FILEIO
// =================================================== file
struct File:Sym { File(Sym*); static Sym*file(Sym*);
	Sym*eq(Sym*); FILE *fh; ~File(); };

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

#endif // _H_bI
