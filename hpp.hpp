#ifndef _H_bI
#define _H_bI
										// == metainfo constants ==

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev"
#define AUTOGEN "/***** DO NOT EDIT: this file was autogened by bI *****/"
#define LOGO "logo64x64"
#define LISPLOGO "warning64x64"
										// == std.includes ==
#include <iostream>
#include <sstream>
#include <cstdlib>
//#include <cstdio>
#include <cassert>
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
	Sym(Sym*);							// copy
// --------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// --------------------------------------- par{}ameters
	map<string,Sym*> par;
	void setpar(Sym*);
// --------------------------------------- dumping
	string dump(int depth=0);			// dump symbol object
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// tab padding
// --------------------------------------- evaluation (computing)
	virtual Sym* eval();
// --------------------------------------- operators
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* dot(Sym*);				// A . B	index
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
	string tagval(); Sym* car; Sym* cdr; };

// ================================================================= DIRECTIVE
struct Directive:Sym { Directive(string);
	string tagval(); };

// =================================================================== SCALARS
struct Str:Sym { Str(string); string tagval(); };	// string
struct Hex:Sym { Hex(string); };					// hexadecimal machine number
struct Bin:Sym { Bin(string); };					// binary machine number (bit string)
struct Int:Sym { Int(string);						// integer
	long val; string tagval(); };
struct Num:Sym { Num(string);						// floating number
	double val; string tagval(); };

// ================================================================ COMPOSITES
struct List:Sym { List(); };						// [list]
struct Pair:Sym { Pair(Sym*,Sym*); };				// pa:ir
struct Vector:Sym { Vector(); };					// <vector>
struct Tuple:Sym { Tuple(); 						// tu,ple
	Tuple(Sym*,Sym*); };

// =============================================================== FUNCTIONALS
struct Op:Sym { Op(string); Sym* eval(); };			// operator
struct Lambda:Sym { Lambda(); };					// {la:mbda}
typedef Sym*(*FN)(Sym*);							// function ptr
struct Fn:Sym { Fn(string,FN); 						// internal/dyncompiled function
	FN fn; Sym*at(Sym*); };

													// == GUI ==
//struct Window:Sym

													// == OS specific ==
#ifdef __MINGW32__
#include "mingw32.hpp"								// win32/MinGW
#endif

extern map<string,Sym*> env;						// == global env{}ironment ==
extern void env_init();								// init env{} on startup

#endif // _H_bI
