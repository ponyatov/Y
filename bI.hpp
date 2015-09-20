#ifndef _bI_H
#define _bI_H

#include <iostream>
<<<<<<< HEAD
#include <cstdio>
=======
>>>>>>> master
#include <cstdlib>
#include <cstdio>

#include <list>

#ifdef __MINGW32__
#else
#error no Linux
#endif

#include <map>
#include <list>

#ifdef __linux__
#include <sys/stat.h>
#endif // __linux__
#ifdef __MINGW32__
#include <direct.h>
#endif // __MINGW32__

using namespace std;

<<<<<<< HEAD
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
	void fix();					// fixes for different AST node classes
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

=======
struct biObject {				// master class
	virtual string* dump();		// dump object in reloadable form
	virtual string* eval();		// evaluate (compute) object contents
};

extern int yylex();
extern char *yytext;
extern int yylineno;
extern int yyparse();
extern void yyerror(string);
#include "parser.tab.hpp"

void W(string*);
void W(string);

#endif // _H_bI

>>>>>>> master
