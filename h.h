#ifndef _H_H
#define _H_H

#include <iostream>
#include <string>
#include <cstdlib>

// lexer/parser
extern int yylex(void);
extern int yyparse(void);
extern char *yytext;
extern int yylineno;
extern void yyerror(const char *msg);

#define YYERROR_VERBOSE 1

#include "parser.tab.hpp"

#endif // _H_H
