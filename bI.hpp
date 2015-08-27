#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>

using namespace std;

extern int yylex(void);
extern int yyparse(void);
extern char *yytext;
extern int yylineno;
extern void yyerror(const char *msg);
#include "bI.tab.hpp"

#endif //  _H_bI
