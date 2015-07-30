#ifndef _H_H
#define _H_H

#include <iostream>

// lexer/parser
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char *msg);

#endif // _H_H
