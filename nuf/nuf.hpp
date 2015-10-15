#ifndef _H_nuf
#define _H_nuf

#include <iostream>					// \\ std C++ includes
#include <cstdlib>
#include <map>
using namespace std;				// //

extern map<string,string> var;		// vars registry

extern int yylex();					// \\ lexer & parser
extern int yylineno;
extern char *yytext;
extern int yyparse();
extern void yyerror(string);
#include "nuf.tab.hpp"			// //

extern void W(char);				// \\ writers
extern void W(string);
extern void W(int);					// //

#endif // _H_nuf

