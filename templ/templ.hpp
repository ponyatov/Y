#ifndef _H_templ
#define _H_templ

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"
#define LICENSE "http://www.gnu.org/copyleft/lesser.html"
#define AUTOGEN "DO NOT EDIT: this file was autogened by bI language system"

#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#ifdef __MINGW32__
#include <direct.h>
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
extern void yyerror(string);
extern int yyparse();
#include "templ.tab.hpp"

void W(char);
void W(string);
void W(string*);

#endif // _H_templ

