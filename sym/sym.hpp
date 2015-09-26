#ifndef _H_SYM
#define _H_SYM

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

// \\\ generic symbol type
struct biSymbol {					// class implements all symbol functionality
	// data fields
    string tag;						// symbol tag a.k.a. class/type name
    string value;					// symbol value
    map<string,biSymbol*>attr;		// symbol attributes
    list<biSymbol*>nest;			// nested symbols for composite symbols/types
	// constructors
	biSymbol(string,string);		// leaf symbol from strings
	biSymbol(biSymbol*,biSymbol*);	// pair constructor
	// serializatin and computing
    virtual string dump(int depth=0);// (idented) debug dump
	virtual string eval();			// evaluate (compute) recursive with nested
};
// ///

// \\\ file
struct biFile:biSymbol {
	biFile(biSymbol*,biSymbol*);
	biFile(const char*);
	~biFile();
	void W(string);						// \\ file writers
	void W(string*);
	void W(biSymbol*);					// //
private:
	FILE *fh;
	void init();	
};
extern biFile *bi_file;					// current file opened for writing
// ///

// \\\ module
struct biModule:biSymbol {
	biModule(biSymbol*,biSymbol*);
	biModule(const char*);
	~biModule();
private:
	biFile* Makefile;
	biFile* README;
	void init();
};
extern biModule *bi_module;				// current active module
// ///

// \\\ lexer/parser header block
extern int yyparse();
extern void yyerror(string);
extern int yylex();
extern int yylineno;
extern char* yytext;
#include "sym.tab.hpp"
// ///

// textout writers
void W(string   ,bool to_file=true);
void W(string  *,bool to_file=true);
void W(biSymbol*,bool to_file=true);

#endif // _H_SYM

