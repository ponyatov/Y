#ifndef _H_sym
#define _H_sym

#include <iostream>					// \\ std C++ includes
#include <cstdlib>
#include <map>
using namespace std;				// //

extern map<string,string> env;		// \\ vars registry
extern void env_init();				// //

extern int yylex();					// \\ lexer & parser
extern int yylineno;
extern char *yytext;
extern int yyparse();
extern void yyerror(string);
#include "sym.tab.hpp"				// //

extern void W(char);				// \\ writers
extern void W(string);				// //

#endif // _H_sym

