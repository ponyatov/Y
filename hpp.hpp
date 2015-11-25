/***** DO NOT EDIT: this file was autogened by bI *****/
#ifndef _H_bI
#define _H_bI

// metainfo constants

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/bI"
#define AUTOGEN "/***** DO NOT EDIT: this file was autogened by bI *****/"
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
	vector<sym*> nest;			// nested objects tree
	void join(sym*);			// add nested object
	string pad(int);			// pad tagval with tabs
	string tagval();			// <tag:value> string
	string dump(int depth=0);	// dump object in string form
	virtual sym* eval();		// evaluate (compute) object
	// functions
	sym* (*fn)(sym*);			// optional ptr to internal sym* fn(sym*)
	// code generation
	virtual string hpp(int depth=0);	// dump in C++ .hpp
};
extern map<string,sym*> env;	// \\ global environment: objects registry
extern void env_init();			// //

// dynamic symbolic object subsystem

struct Directive:sym { Directive(string); };				// .directive
struct Module:sym {											// .module
	Module(string); ~Module();
	static void CurrSet(Module*); };			
extern Module *curr_module;									// current module
struct File:sym {											// .file
	File(string,string M="r"); ~File(); FILE *fh;
	static void CurrSet(File*); };							// set curr_file
extern File *curr_file;									// current output file

struct Int:sym { Int(string); sym* eval(); };				// integer
struct Hex:sym { Hex(string); sym* eval(); };				// hex
struct Bin:sym { Bin(string); sym* eval(); };				// binary
struct Num:sym { Num(string); sym* eval(); };				// float number
struct Str:sym { Str(string); };							// string

struct List:sym { List(); };								// [list]
struct Vector:sym { Vector(); };							// <vector>
struct Pair:sym { Pair(sym*,sym*); };						// pa:ir
struct Block:sym { Block(); };								// {block}

// class processing

struct Class:sym { Class(string); };						// class:def
extern sym* classdef(sym*);									// class fn

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

// functions

typedef sym* (*FN)(sym*);									// ptr to fn()
struct Fn:sym { Fn(string,FN); };							// function

extern sym* hpp(sym*);			// hpp

#endif // _H_bI
