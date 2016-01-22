#ifndef _H_bI
#define _H_bI
										// == metainfo constants ==

#define TITLE "bI dynamic language system"
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
#include <cstdio>
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
// --------------------------------------- par{}ameters / class members table
	map<string,Sym*> par;
	void setpar(Sym*);
// --------------------------------------- dumping
	virtual string dump(int depth=0);	// dump symbol object
	virtual string tagval();			// <T:V> header string
	string tagstr();					// <T:'V'> Str-like header string
	string pad(int);					// tab padding
// --------------------------------------- evaluation (computing)
	virtual Sym* eval();
// --------------------------------------- operators
	Sym* dummy(Sym*);					// A dummy B	cons -> nest[] folding
	virtual Sym* doc(Sym*);				// A "B"	docstring
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* dot(Sym*);				// A . B	index
	virtual Sym* ins(Sym*);				// A += B	insert (vs C increment)
	virtual Sym* add(Sym*);				// A + B	add
	virtual Sym* add();					// +A		sum
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
// ================================================================= DIRECTIVE
struct Directive:Sym { Directive(string);
	string tagval(); Sym*eval(); };

// =================================================================== SCALARS
struct Str:Sym { Str(string); string tagval(); };	// string
struct Hex:Sym { Hex(string); };					// hexadecimal machine number
struct Bin:Sym { Bin(string); };					// binary machine number (bit string)
struct Int:Sym { Int(string); Int(long);			// integer
	long val; string tagval();
	Sym*add(Sym*); };
struct Num:Sym { Num(string); Num(double);			// floating number
	double val; string tagval(); };

// ================================================================ COMPOSITES
// ====================================================================== CONS
struct Cons:Sym { Cons(Sym*,Sym*);					// classic Lisp cons element
	Sym* car; Sym* cdr; string dump(int);
	Sym* eval(); Sym*add(); };
/* droppped due to bI lispification following SICP bible
struct List:Sym { List(); };						// [list]
struct Pair:Sym { Pair(Sym*,Sym*); };				// pa:ir
struct Vector:Sym { Vector(); };					// <vector>
struct Tuple:Sym { Tuple(); 						// tu,ple
	Tuple(Sym*,Sym*); };
*/

// =============================================================== FUNCTIONALS
// =================================================== operator
struct Op:Sym { Op(string); Sym* eval();
	Sym* at(Sym*); };
extern Op* doc;										// "doc"string operator
// =================================================== 

struct Lambda:Sym { Lambda(); };					// {la:mbda}
// =================================================== function
typedef Sym*(*FN)(Sym*);							// function ptr
struct Fn:Sym { Fn(string,FN); 						// internal/dyncompiled function
	FN fn; Sym*at(Sym*); };

// ==================================================================== FILEIO
struct Dir:Sym { Dir(Sym*); string tagval();		// directory
	Sym*ins(Sym); };
extern Sym* dir(Sym*);
struct File:Sym { File(Sym*); string tagval();		// file
	FILE *fh; ~File(); };
extern Sym* file(Sym*);

// ======================================================================= GUI
struct Message:Sym { Message(Sym*);	string tagval(); };	// message box/bar
extern Sym* message(Sym*);
struct Window:Sym { Window(Sym*); string tagval(); };	// window
extern Sym* window(Sym*);

// =============================================================== OS SPECIFIC
#ifdef __MINGW32__
#include "win32.hpp"								// win32/MinGW
#endif

// ====================================================== GLOBAL ENV{}IRONMENT
extern map<string,Sym*> env;
extern void env_init();								// init env{} on startup

#endif // _H_bI
