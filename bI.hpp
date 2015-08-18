#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>

struct biObject {
	enum {INT,FLOAT,STRING,ID,OP} t;
	union {
		int i;
		float f;
		std::string *s;
		std::string *id;
		char op;
	} v;
};

extern int yylex(void);
extern int yyparse(void);
extern char *yytext;
extern int yylineno;
extern void yyerror(const char *msg);
#include "parser.tab.hpp"

#endif //  _H_bI
