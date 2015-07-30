#ifndef _H_H
#define _H_H

#include <iostream>
#include <string>
#include <cstdlib>

// lexer/parser
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char *msg);

#include "parser.tab.hpp"

#endif // _H_H
