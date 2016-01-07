#ifndef _H_bI
#define _H_bI
														// == metainfo constants

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
#ifdef __MINGW32__
#include <direct.h>		// win32
#else
#include <sys/stat.h>	// linux
#endif

struct AST {											// == AST symbolic type ==
// -------------------------------------------------------------------------------
	std::string tag;									// class/type tag
	std::string val;									// value
// -------------------------------------------------------------------------------
	AST(std::string,std::string);						// <T:V> constructor
	AST(AST*);											// copy constructor
// -------------------------------------------------------------------------------
	std::vector<AST*> nest;								// nest[]ed elements
	void push(AST*);									// push nested as stack
// -------------------------------------------------------------------------------
	std::map<std::string,AST*> par;						// par{}ameters
	void setpar(AST*);									// add/set parameter
// -------------------------------------------------------------------------------
	std::string dump(int depth=0);						// recursive dump(+1)
	virtual std::string tagval();						// <tag:val> header
	std::string pad(int);								// padding string
// -------------------------------------------------------------------------------
	virtual AST* eval();								// compute/evaluate
// ------------------------------------------------------- operators
	virtual AST* eq(AST*);								// A = B  assignment
	virtual AST* at(AST*);								// A @ B  apply
	virtual AST* dot(AST*);								// A . B  index
	virtual AST* neg();									// -A     negate
	virtual AST* add(AST*);								// A + B  \ arithmetic
	virtual AST* sub(AST*);								// A - B
	virtual AST* mul(AST*);								// A * B
	virtual AST* div(AST*);								// A / B
	virtual AST* pow(AST*);								// A ^ B  /
};

extern std::map<std::string,AST*> env;				// == global environment ==
extern void env_init();									// init env[] on startup
extern void fn_init();									// internal functions 

extern void W(AST*);									// == writers ==
extern void W(std::string);
														// == lexer interface ==
extern int yylex();										// parse next token
extern int yylineno;									// current source line
extern char* yytext;									// found token text
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
														// == parser interface ==
extern int yyparse();									// run parser
extern void yyerror(std::string);						// error callback
#include "ypp.tab.hpp"									// token defines for lexer

														// == scalars ==
struct Sym:AST { Sym(std::string); };					// generic symbol
struct Str:AST { Str(std::string); };					// string
struct Int:AST { Int(std::string); long   val;			// integer
	std::string tagval(); AST*neg(); };
struct Hex:AST { Hex(std::string); };					// hex machine number
struct Bin:AST { Bin(std::string); };					// binary machine number
struct Num:AST { Num(std::string); double val;			// floating point number
	std::string tagval(); AST*neg(); };
														// == composites ==
struct List:AST { List(); };							// [list]
struct Vector:AST { Vector(); };						// <vector>
struct Pair:AST { Pair(AST*,AST*); };					// pa:ir

														// == functionals ==
struct Op:AST { Op(std::string); };						// operator
struct Lambda:AST { Lambda(); };						// {lambda}
typedef AST*(*FN)(AST*);								// function ptr
struct Fn:AST { Fn(std::string,FN); FN fn; };			// internal function

#endif // _H_bI
