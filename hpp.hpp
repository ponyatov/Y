#ifndef _H_bI
#define _H_bI
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
	vector<AST*> nest;									// nest[]ed elements
	void push(AST*);									// push nested as stack
// -------------------------------------------------------------------------------
	map<std::string,AST*> par;							// par{}ameters
	void setpar(AST*);									// add/set parameter
// -------------------------------------------------------------------------------
	std::string dump(int depth=0);						// recursive dump(+1)
	std::string tagval();								// <tag:val> header
	std::string pad(int);								//
};

extern map<string,sym*> env;							// == glob.environment ==
extern void env_init();

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

#endif // _H_bI
