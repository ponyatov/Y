#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <list>

#ifdef __linux__
#include <sys/stat.h>
#endif // __linux__
#ifdef __MINGW32__
#include <direct.h>
#endif // __MINGW32__

using namespace std;

struct biObject {
	string *name;
	biObject(string*);
};

struct biModule: public biObject {
	biModule(string*);
};

extern biModule *bi_module;

struct biFile: public biObject {
	biFile(string*);
	~biFile();
	FILE *fh;
	void W(char c);
	void W(string *s);
	void W(string s);
};

extern biFile *bi_file;

struct AST {
	map<string,string> tag;
	list<AST*> child;
	AST();
	AST(char*,char*);
	AST(string*,string*);
	AST(AST*,AST*);
	AST(AST*,AST*,AST*);
	string str(int depth=0);
};

struct biNative {
	enum  {INT,FLOAT,BIN,HEX,STR,PTR,FFILE} t;
	union {
		int i;
		float f;
		string *s;
		void *p;
		FILE *ff;
	} v;
};

extern int yylex();
extern int yyparse();
extern int yylineno;
extern void yyerror(char *);
extern char *yytext;
#include "bI.tab.hpp"

extern void W(char c,bool log_only=false);
extern void W(string *s, bool log_only=false);
extern void W(string s, bool log_only=false);

#endif // _bI_H

