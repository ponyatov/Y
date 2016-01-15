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
//#include <cassert>
#include <vector>
#include <map>
using namespace std;

struct Sym {							// == abstract symbolic type (AST) ==
// ---------------------------------------------------------------------------
	string tag;							// data type / class
	string val;							// symbol value
// ---------------------------------------------------------------------------
	Sym(string,string);					// <T:V> constructor
	Sym(string);						// token constructor
	Sym(Sym*);							// copy constructor
// ---------------------------------------------------------------------------
	vector<Sym*> nest;					// nest[]ed
	void push(Sym*);					// add nested element
// ---------------------------------------------------------------------------
	map<string,Sym*> par;				// par{}ameters
	void setpar(Sym*);					// add parameter
// ---------------------------------------------------------------------------
	string dump(int depth=0);			// dump symbol object
	string pad(int);					// tab padding
	virtual string tagval();			// <T:V> header string
// ---------------------------------------------------------------------------
	virtual Sym* eval();				// compute/evaluate object
// ----------------------------------------------------------------- operators
	virtual Sym* eq(Sym*);				// A = B	assignment
	virtual Sym* at(Sym*);				// A @ B	apply
	virtual Sym* dot(Sym*);				// A . B	index
};

extern void W(Sym*);								// == writers ==
extern void W(string);

extern map<string,Sym*> env;						// == global environment ==
extern void env_init();								// init env[] on startup
extern void fn_init();								// register internal functions

// == lexer interface ==
extern int yylex();						// parse next token
extern int yylineno;					// current source line
extern char* yytext;					// found token text
#define TOC(C,X) { yylval.o = new C(yytext); return X; }// token macro used in lexer

// == parser interface ==
extern int yyparse();					// run parser
extern void yyerror(std::string);		// error callback
#include "ypp.tab.hpp"					// token defines for lexer

struct Directive:Sym { Directive(string);// == .directive ==
	string tagval(); };
										// == specials ==
extern Sym* nil;						// nil

										// == scalars ==
struct Str:Sym { Str(string);			// string
	string tagval(); };
struct Hex:Sym { Hex(string); };		// hexadecimal machine number
struct Bin:Sym { Bin(string); };		// binary machine number (bit string)
struct Int:Sym { Int(string);			// integer
	long val; string tagval(); };
struct Num:Sym { Num(string);			// floating number
	double val; string tagval(); };

										// == composites ==
struct List:Sym { List(); };			// [list]
struct Pair:Sym { Pair(Sym*,Sym*); };	// pa:ir
struct Vector:Sym { Vector(); };		// <vector>
struct Tuple:Sym { Tuple(); 			// tu,ple
	Tuple(Sym*,Sym*); };

										// == functionals ==
struct Op:Sym { Op(string); 			// operator
	Sym* eval(); };
struct Lambda:Sym { Lambda(); };		// {la:mbda}
typedef Sym*(*FN)(Sym*);				// function ptr
struct Fn:Sym { Fn(string,FN); 			// internal/dyncompiled function
	FN fn; Sym*at(Sym*); };

										// == GUI ==
//struct Window:Sym

										// == OS specific ==
#ifdef __MINGW32__
#include "mingw32.hpp"					// win32/MinGW
#endif

#endif // _H_bI
