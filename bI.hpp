/* DO NOT EDIT: this file was autogened by bI/sym language system */
/***** hpp.sym *****/

#ifndef _H_bI
#define _H_bI

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define GITHUB "https://github.com/ponyatov/Y/tree/dev/"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI/sym language system"

#include <vector>
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
using namespace std;

struct object {
	string tag,value;
	object(string,string);
	string tagval();
	string pad(int);
	string dump(int depth=0);
	object* eval();
	vector<object*> nest;
	void join(object*);
};

extern map<string,object*> env;
void env_init();

struct directive: object {
	directive(string);
};

struct module: object {
	module(string);
};
extern module *curr_module;

struct file: object {
	file(string);
	~file();
	FILE *fh;
};
extern file *curr_file;

extern int yylex();
extern int yylineno;
extern char *yytext;
extern void incFileName(object*);
extern void yyerror(string);
extern int yyparse();
#include "bI.tab.hpp"

void W(char   ,bool tofile=true);
void W(string ,bool tofile=true);
void W(string*,bool tofile=true);
void W(object*,bool tofile=true);

#endif // _H_bI

/***** hpp.sym *****/
