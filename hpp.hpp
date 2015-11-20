// DO NOT EDIT: this file was autogened by PIL
#ifndef _H_PIL
#define _H_PIL

// metainfo constants

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y"
#define AUTOGEN  "/***** DO NOT EDIT: this file was autogened by bI *****/"
#define bICONFIG "/************ bI language abridged dialect ************/"
#define LOGO "logo64x64"
#define LISP "warning64x64"

// standart includes

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
	#include <direct.h>
#else
	#include <sys/stat.h>
#endif
#include <vector>
#include <map>
using namespace std;

// generic AST-like dynamic object

struct sym {
	string tag;					// object class or data type
	string value;				// object value in string form
	sym(string,string);			// constructor from string form tag:value
	string dump(int depth=0);	// dump object in string form
	virtual sym* eval();		// evaluate (compute) object
	string tagval();			// <tag:value> string
	string pad(int);			// pad tagval with tabs
	vector<sym*> nest;			// nested objects tree
	void join(sym*);			// add nested object
	sym*(*fn)(sym*);			// for functions: pointer to lowlevel C++ fn()
// predefined low-level functions defined on symbols and inherited objects
	virtual sym* add(sym*);		// + to current object
};
extern map<string,sym*> env;	// \\ global environment: objects registry
extern void env_init();			// //

// dynamic symbolic object subsystem

struct Directive:sym { Directive(string); };					// .directive
struct Module:sym { Module(string); };							// .module
extern Module *curr_module;				// current module
struct File:sym {File(string); FILE *fh; ~File(); };			// .file
extern File *curr_file;					// current output file

struct Int:sym { Int(string); sym* eval(); sym* add(sym*); };	// integer
struct Num:sym { Num(string); sym* eval(); };					// float number
struct Str:sym { Str(string); };								// string

struct List:sym { List(); sym* add(sym*); };					// [list]
struct Vector:sym { Vector(); };								// <vector>
struct Pair:sym { Pair(sym*,sym*); };							// pa:ir
struct Dot:sym { Dot(); };										// some.dot
struct Op:sym {Op(string);};									// operator

typedef sym* (*FN)(sym*);										// ptr to fn()
struct Fn:sym { Fn(string,FN); };								// function

										// low-level fu()nctions
extern sym* add(sym*o);
extern sym* print(sym*o);
extern sym* exit(sym*o);

// lexer/parser interface (flex/bison)

extern int yylex();
extern int yylineno;
extern char* yytext;
extern void incFile(sym*);
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"
#define TC(X)	{ yylval.c = yytext[0]; return X; }			/* char token */
#define T1(X)	{ yylval.c = yytext[1]; return X; }			/* escaped char */
#define TS(X)	{ yylval.s = new string(yytext); return X; }/* string tok */
#define TO(C,X)	{ yylval.o = new sym(C,yytext); return X; }	/* generic sym */
#define TX(C,X)	{ yylval.o = new C(yytext); return X; }		/* inherited sym */

// writers

void W(char   ,bool to_file=true);
void W(string ,bool to_file=true);
void W(string*,bool to_file=true);
void W(sym*   ,bool to_file=true);

#endif // _H_PIL
