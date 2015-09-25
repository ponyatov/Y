#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

#include <map>
#include <list>

#ifdef __MINGW32__
#include <direct.h>
#else
#include <sys/stat.h>
#endif // __MINGW32__

using namespace std;

struct biObject {				// master class
	string *cls;					// class name
	string *val;					// generic string value
	list<biObject*> L;
	biObject(const char*);
	biObject(const char*,char*);
	biObject(const char*,string*);
	biObject(string*,string*);
	biObject(const char*,const char*);
	virtual string* dump();		// dump object in reloadable form
	virtual string* eval();		// evaluate (compute) object contents
	virtual void join(biObject*);
};

struct biList: public biObject {
	biList();
	biList(biObject*);
	void join(biObject*);
	string* dump();
};

struct biString: public biObject {
	biString(char*);
};

struct biPair: public biObject {
	biObject *A; biObject *B; 
	biPair(biObject*,biObject*);
	string* dump();
	string* eval();
};

struct biDirective: public biObject {
	biDirective(char*);
};

struct biFile: public biObject {
	FILE *fh;
	char mode;
	biFile(string*,char);
	~biFile();
	string *dump();
	void W(string);
	void W(char);
};
extern biFile *bi_file;

struct biModule: public biObject {
	FILE *make;	FILE *cpp; FILE *hpp;
	biModule(const char*);
	~biModule();
	void files(string);
	void depends(string,string,string);
};
extern biModule *bi_module;

struct biClass: public biObject {
	biFile *cpp;
	string hpps;
	string super;
	list<string> fld;
	biFile *hpp;
	void init(biObject*);
	biClass(biObject*);
	biClass(biObject*,biObject*);
	~biClass();
	string* dump();
};

extern biClass* bi_class;
extern map<string,string*> bi_class_reg;

struct biLexer: public biObject {
	biFile *lpp; biFile *hpp;
	biLexer(biObject*);
	~biLexer();
};
extern biLexer *bi_lexer;

struct TEX {
	FILE* fh;
	string title,author,head,body,foot;
	TEX(const char*);
	~TEX();
	void W(string);
	void sec(int,string);
	string fix(string);
};
extern TEX tex;

extern int yylex();
extern char *yytext;
extern int yylineno;
extern int yyparse();
extern void yyerror(string);
#include "parser.tab.hpp"

string autogen(string pfx, string obj="");
void W(string*, bool tofile=true);
void W(string, bool tofile=true);
void W(char, bool tofile=true);

#endif // _bI_H

