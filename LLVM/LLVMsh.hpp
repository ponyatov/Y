#ifndef _H_LLVMsh
#define _H_LLVMsh

// -------------------------------- LLVM includes
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/ADT/SmallVector.h>
//#include <llvm/IR/.h>

// -------------------------------- std includes
#include <iostream>
#include <sstream>
#include <cstdlib>
//#include <bitset>
#include <vector>
#include <map>
using namespace std;

struct Sym {					// === Abstract Symbolic Type (bI like) ===
	string tag;
	string val;
// ------------------------------- contructors
	Sym(string,string);
	Sym(string);
// ------------------------------- nested
	vector<Sym*> nest;
	void push(Sym*);
// ------------------------------- dumper
	string dump(int depth=0);
	string pad(int);
	virtual string tagval();
// ------------------------------- LLVM codegen
//	virtual llvm::Value* ll();
// ------------------------------- evaluate
	virtual Sym* eval();
};

extern map<string,Sym*> env;
extern void env_init();

// ------------------------------- writers
extern void W(char);
extern void W(Sym*);

// --------------------------------------------------------------- scalars
struct Str:Sym { Str(string); };								// string
struct Int:Sym { Int(string); long val; string tagval(); 		// integer

};
struct Hex:Int { Hex(string); string tagval(); };				// hex
struct Bin:Sym { Bin(string);									// binary
	vector<bool> val; string tagval(); };
struct Num:Sym { Num(string); double val; string tagval(); };	// float number

// --------------------------------------------------------------- functionals
struct Op:Sym { Op(string); };

// ---------------------------------------------------------- parser interface
extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse();
extern void yyerror(string);
#include "LLVMsh.parser.hpp"
#define TC(X)		{ yylval.c = yytext[0]; return X; }
#define TOC(C,X)	{ yylval.o = new C(yytext); return X; }

#endif // _H_LLVMsh
