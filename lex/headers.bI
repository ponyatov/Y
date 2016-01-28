
hpp_Sym = '
struct Sym {									// Abstact Symbolic Type (AST)
	string tag;									// class/tag
	string val;									// value
	Sym(string,string);							// <T:V> constructor
	Sym(string);								// token constructor
	virtual string dump();						// string representation
	virtual Sym* eval();						// evaluate computable object
};
'

hpp_writers = '
extern void W(Sym*);							// \ writers
extern void W(string);							// /
'

hpp_includes = '
												// std.includes
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

'

hpp_lex = '
												// parser interface
extern int yylex();								// lexer
extern int yylineno;							// current line
extern char* yytext;							// lexed text
extern int yyparse();							// syntax parser
extern void yyerror(string);					// error callback
#include "ypp.tab.hpp"
#define TOC(C,X) { yylval.o = new C(yytext); return X; }	/* token */

'

hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"\n'
hpp += hpp_includes
hpp += hpp_Sym
hpp += hpp_lex
hpp += hpp_writers
hpp += '#endif // _H_'+upcase@MODULE+'\n'

