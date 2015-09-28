#ifndef _bI_H
#define _bI_H

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"

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
struct biFile: public biObject {
	FILE *fh;
	char mode;
	biFile(string*,char);
	~biFile();
	string *dump(int depth=0);
	void W(string);
	void W(char);
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
*/

// \\\ generic symbol type
struct biObject {					// class implements all symbol functionality
	// data fields
    string tag;						// symbol tag a.k.a. class/type name
    string value;					// symbol value
    map<string,biObject*>attr;		// symbol attributes
    list<biObject*>nest;			// nested symbols for composite symbols/types
	// constructors
	biObject(string,string);		// leaf symbol from strings
	biObject(biObject*,biObject*);	// pair constructor
	// serializatin and computing
    virtual string dump(int depth=0);// (idented) debug dump
	virtual string eval();			// evaluate (compute) recursive with nested	
};
// ///

// \\\ environment
extern map<string,biObject*> env;
void init_env();
// ///

// \\\ directive
struct biDirective: biObject {
	biDirective(string);
};
// ///

// \\\ file
struct biFile: biObject {
	biFile(string);
	~biFile();
	void W(char);
	void W(string);
	FILE *fh;
};
extern biFile* bi_file;
// ///

// \\\ module
struct biModule: biObject {
	FILE *make; FILE* readme;
	string title,author,about;
	biModule(string);
	~biModule();
};
extern biModule* bi_module;
// ///

// \\\ lexer/parser header block
extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "parser.tab.hpp"
// ///

// \\ textout writers

// autogenerated marker creator
string autogen(string pfx, string obj);

void W(char     ,bool to_file=true);
void W(string   ,bool to_file=true);
void W(string  *,bool to_file=true);
void W(biObject*,bool to_file=true);
// //

// system cleanup
void terminator();

#endif // _bI_H

