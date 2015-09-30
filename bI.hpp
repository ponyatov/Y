#ifndef _bI_H
#define _bI_H

#define AUTHOR "(c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved"

// \\\ header files in std namespace
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
//#include <list>
#include <vector>
#include <map>
#ifdef __MINGW32__
#include <direct.h>
#else
#include <sys/stat.h>
#endif
using namespace std;
// ///

// \\\ generic symbol type
struct biObject {					// class implements all symbol functionality
	// data fields
    string tag;						// symbol tag a.k.a. class/type name
    string value;					// symbol value
    map<string,biObject*>attr;		// symbol attributes
    vector<biObject*>nest;			// nested symbols for composite symbols/types
	// constructors
	biObject(string,string);		// leaf symbol from strings
	biObject(biObject*,biObject*);	// pair constructor
	biObject(biObject*);			// copy contructor
	// serializatin and computing
    virtual string dump(int depth=0);// (idented) debug dump
	virtual biObject* eval();		// evaluate (compute) recursive with nested	
	// misc
	void join(biObject*);			// add item to nest
	string pad(int depth);			// dump padding
	// operators
	virtual biObject* pfxminus();		// -obj
	virtual biObject* pfxplus();		// +obj
	virtual biObject* div(biObject*);	// obj/obj
};
// ///

// \\\ environment
extern map<string,biObject*> env;
void init_env();
// ///

// \\\ class
struct biClass: biObject {
	biClass(string);
	biClass(biObject*);
	biClass(biObject*,biObject*);
};
extern map<string,biClass*> bi_class_registry;	/* global class registry */
// ///

// \\\ operator
struct biOP: biObject {
	biOP(string);
	biObject* eval();
};
// ///

// \\\ numeric types
struct biInt: biObject {
	biInt(string);
//	biInt(biObject*);
	int val;
	string dump(int depth=0);
	// operators
	biObject* pfxminus();
	biObject* pfxplus();
	biObject* div(biObject*);
};
// ///

// \\\ table of contents
struct TOC {
	FILE *fh;
	int l1,l2,l3,cls;
	void W(int,string);
	static const int SECP=1,SEC=2,SECM=3,CLASS=5;
	TOC(string);
	~TOC();
};
extern TOC toc;
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

