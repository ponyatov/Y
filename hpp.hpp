#ifndef _H_GUI
#define _H_GUI
										// == std.includes ==
#include <iostream>
#include <cstdlib>
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
	string dump(int depth=0);			// dump symbol
	string pad(int);					// tab padding
	virtual string tagval();			// <T:V> header string
// ---------------------------------------------------------------------------
	Sym* eval();						// compute/evaluate object
	virtual Sym* eq(Sym*);				// A = B
	virtual Sym* at(Sym*);				// A @ B
	virtual Sym* dot(Sym*);				// A . B
};
										// == writers ==
extern void W(Sym*);
extern void W(string);
										// == environment ==
extern map<string,Sym*> env;
extern void env_init();
extern void fn_init();
										// == scalars ==
struct Str:Sym { Str(string);			// string
	string tagval(); };
struct Int:Sym { Int(string);			// integer
	long val; };
struct Num:Sym { Num(string);			// floating number
	double val; };
										// == composites ==
struct List:Sym { List(); };			// [list]
struct Pair:Sym { Pair(Sym*,Sym*); };	// pa:ir

										// == functionals ==
struct Op:Sym { Op(string); };			// operator
struct Lambda:Sym { Lambda(); };		// {la:mbda}

										// == lexer/parser interface ==
extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
#include "ypp.tab.hpp"
										// == OS specific ==
#ifdef __MINGW32__
#include "mingw32.hpp"
#endif

#endif // _H_GUI
