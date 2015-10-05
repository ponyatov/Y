#ifndef _H_pure
#define _H_pure

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#ifdef __MINGW32__
#include <direct.h>
#endif
#include <map>
#include <vector>
using namespace std;

extern int yylex();
extern void yyerror(string);
extern int yylineno;
extern char *yytext;
extern int yyparse();
#include "pure.tab.hpp"
void W(char,bool to_file=true);
#endif // _H_MODULE
