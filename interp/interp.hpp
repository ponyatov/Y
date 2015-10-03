#ifndef _H_INTERP
#define _H_INTERP

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

struct sym {
	string tag,value;
	sym(string,string);
	sym(sym*);
	vector<sym*> nest;
	string dump(int depth=0);
	sym* eval();
	void app(sym*);
	sym* pfxplus();
	sym* pfxminus();
	sym* add(sym*);
	sym* sub(sym*);
	sym* mul(sym*);
	sym* div(sym*);
};

// \\\ lexer/parser header block
extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "parser.tab.hpp"

#endif // _H_INTERP

