/* DO NOT EDIT: this file was autogened by bI language system */
/* <module:sym> */
#ifndef _H_sym
#define _H_sym

#define MODULE "sym"
#define TITLE "pure symbolic script engine"
#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev/sym"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI language system"

#include <map>							// \ required std includes
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>						// /
#ifdef __MINGW32__						// \ win32 specific
#include <direct.h>						// /
#else									// \ Linux & others POSIX-compatibles
#include <sys/stat.h>					// /
#endif
using namespace std;

struct biObject {
	string tag;							// object class name or data type
	string value;						// object value
	biObject(string,string);
	virtual string dump(int depth=0);	// dump	object in string form
	virtual biObject* eval();			// compute object symbolically
};

extern map<string,biObject*> env;		// \ environment (global var registry)
extern void env_init();					// /

struct biDirective: biObject {
	biDirective(string);
};

struct biModule: biObject {
	biModule(string);
};
extern biModule *bi_module;

struct biFile: biObject {
	biFile(string);
	~biFile();
	FILE *fh;
	void W(char);
	void W(string);
};
extern biFile *bi_file;

										// syntax core interface
extern int yylex();						// \ lexer
extern char *yytext;					// 		regexp-parsed text
extern int yylineno;					// /	current line number 
extern int yyparse();					// \ parser
extern void yyerror(string);			// syntax error callback
#include "sym.tab.hpp"					// / parser defines

void W(char     ,bool to_file=true);	// \ writers
void W(string   ,bool to_file=true);
void W(string*  ,bool to_file=true);
void W(biObject*,bool to_file=true);	// //

#endif // _H_sym
