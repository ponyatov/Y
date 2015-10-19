#ifndef _H_sym
#define _H_sym

#include <iostream>					// \\ std C++ includes
#include <cstdlib>
#include <map>
#include <vector>
//@use(iostream)
using namespace std;				// //

struct object {						// \\ symbolic object
	object(string,string);			// constructor
	string tag;						// class tag
	string value;					// object value in string form
	vector<object*> nest;			// nested objects
	string dump(int depth=0);		// dump object in AST text form
	object* eval();					// compute (evaluate) object with nested
	string pad(int);				// pad element using tabs
	string tagval();				// return object header in string repr
};									// //

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

