/* DO NOT EDIT: this file was autogened by bI/sym language system */
/***** hpp.sym *****/

#ifndef _H_bI
#define _H_bI

// metainfo constants

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev/"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI/sym language system"

#include <vector>				// \\ standart includes
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#ifdef __MINGW32__
#include <direct.h>
#else
#include <sys/stat.h>
#endif
using namespace std;				// //

struct object {						// \\ generic AST-like dynamic object
	string tag;						// object class or data type
	string value;					// object value in string form
	object(string,string);			// constructor from string form tag:value
	string tagval();				// <tag:value> string
	string pad(int);				// pad tagval with tabs
	string dump(int depth=0);		// dump object in string form
	object* eval();					// evaluate (compute) object
	vector<object*> nest;			// nested objects tree
	void join(object*);				// add nested object
};									// //

extern map<string,object*> env;		// \\ global environment: objects registry
void env_init();					// //

typedef object* (*fn)(object*);		// \\ system functions
extern map<string,fn> sysfn;		
extern void fn_init();
extern object* fn_date(object*);	// //

struct directive: object {			// \\ .directive
	directive(string);
};									// //

struct module: object {				// \\ .module
	module(string);
};
extern module *curr_module;			// //

struct file: object {				// \\ output .file
	file(string);
	~file();
	FILE *fh;
};
extern file *curr_file;				// //

extern int yylex();					// \\ lexer/parser specific (flex/bison)
extern int yylineno;				// current line number (for error reports)
extern char *yytext;				// current detected text in lexer
extern void incFileName(object*);	// .include nested file
extern void yyerror(string);		// syntax error processing function
extern int yyparse();				// syntax parser
#include "bI.tab.hpp"				// //

void W(char   ,bool tofile=true);	// \\ writers
void W(string ,bool tofile=true);
void W(string*,bool tofile=true);
void W(object*,bool tofile=true);	// //

#endif // _H_bI

/***** hpp.sym *****/
