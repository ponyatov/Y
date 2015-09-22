#ifndef _bI_H
#define _bI_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>

//#include <map>
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

struct biModule: public biObject {
	FILE *make;
	biModule(const char*);
	~biModule();
	void depends(string,string,string);
	void o_dep(string);
};
extern biModule *bi_module;

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

struct biClass: public biObject {
	static const char chead[];
	biFile *cpp;
	biFile *hpp;
	biClass(biObject*);
	~biClass();
};

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

void W(string*, bool tofile=true);
void W(string, bool tofile=true);
void W(char, bool tofile=true);

#endif // _bI_H

