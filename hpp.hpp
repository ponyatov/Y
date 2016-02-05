#ifndef _H_bI
#define _H_bI

#include "meta.hpp"
										// == std.includes ==
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
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
//	Sym(Sym*);							// copy
// --------------------------------------------------------- nest[]ed elements
	vector<Sym*> nest;
	void push(Sym*);
// -------------------------------------------------------------- par{}ameters
	map<string,Sym*> par;				// can be used as class slots
	void partag(Sym*);					// par[tag]=obj
	void parval(Sym*);					// par[val]=obj
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
	virtual Sym* inher(Sym*);			// A : B	inheritance
	virtual Sym* str();					// str(A)	to string representation
	virtual Sym* add(Sym*);				// A + B	add
	virtual Sym* div(Sym*);				// A / B	div
	virtual Sym* ins(Sym*);				// A += B	insert
};

extern void W(Sym*);								// \ ==== writers ====
extern void W(string);								// /

// ================================================================= DIRECTIVE
struct Directive:Sym { Directive(string); Sym*eval(); };

// ================================================================== SPECIALS
extern Sym* nil;									// nil/false
//extern Sym* T;							// true
//extern Sym* F;							// false
//extern Sym* E;							// error
//extern Sym* D;							// default
extern Sym* Rd;										// read mode
extern Sym* Wr;										// write mode

// =================================================================== SCALARS
struct Str:Sym { Str(string); string tagval();		// string
	Sym*eq(Sym*); Sym* add(Sym*); };
extern Sym* upcase(Sym*);

struct Hex:Sym { Hex(string); };					// hexadecimal
struct Bin:Sym { Bin(string); };					// bit string
struct Int:Sym { Int(string); Int(long);			// integer
	string tagval(); long   val; };
struct Num:Sym { Num(string); Num(double);			// floating number
	string tagval(); double val; };

// ================================================================ COMPOSITES
struct Cons:Sym { Cons(Sym*,Sym*); Sym*A; Sym*D; 	// classic Lisp cons
	string dump(int); Sym*eval(); };
struct List:Sym { List();							// [list]
	Sym*str(); Sym*div(Sym*); };

// =============================================================== FUNCTIONALS
// =================================================== operator
struct Op:Sym { Op(string); Sym* eval(); };
// =================================================== 

struct Lambda:Sym { Lambda(); };					// {la:mbda}
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

// ======================================================================= GUI
struct Message:Sym { Message(Sym*);	};				// message box/bar
extern Sym* message(Sym*);
struct Window:Sym { Window(Sym*); };				// window
extern Sym* window(Sym*);

// =============================================================== OS SPECIFIC
#ifdef __MINGW32__
#include "win32.hpp"								// win32/MinGW
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

#endif // _H_bI
