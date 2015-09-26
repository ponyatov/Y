#ifndef _bI_H
#define _bI_H


// \\\ header files in std namespace
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <list>
#include <map>
#ifdef __MINGW32__
#include <direct.h>
#else
#include <sys/stat.h>
#endif
using namespace std;
// ///

/*

#include <sstream>

struct biObject {				// master class
	string *cls;					// class name
	string *val;					// generic string value
	list<biObject*> L;
	biObject(const char*);
	biObject(const char*,char*);
	biObject(const char*,string*);
	biObject(string*,string*);
	biObject(const char*,const char*);
	virtual string* dump(int depth=0);	// dump object in reloadable form
	virtual string* eval();				// evaluate (compute) object contents
};

extern map<string,biObject*> env;

struct biList: public biObject {
	biList();
	biList(biObject*);
};

struct biString: public biObject {
	biString(char*);
};

struct biPair: public biObject {
	biPair(biObject*,biObject*);
};

struct biDirective: public biObject {
	biDirective(char*);
};

struct biFile: public biObject {
	FILE *fh;
	char mode;
	biFile(string*,char);
	~biFile();
	string *dump(int depth=0);
	void W(string);
	void W(char);
};
struct biTest: public biFile {
	biTest(string*);
};
extern biFile *bi_file;

struct biModule: public biObject {
	FILE *make;	FILE *cpp; FILE *hpp;
	biModule(const char*);
	~biModule();
	string head; string body; string hbody;
	bool lex_used;
	void files(string);
	void depends(string,string,string);
	void headmake(string,string,string);
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
	string* dump(int depth=0);
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

string autogen(string pfx, string obj="");
void W(string*, bool tofile=true);
void W(char, bool tofile=true);

void terminator();

*/

// \\\ lexer/parser header block
extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "parser.tab.hpp"
// ///

// \\ textout writers
void W(string   ,bool to_file=true);
void W(string  *,bool to_file=true);
// //

#endif // _bI_H

