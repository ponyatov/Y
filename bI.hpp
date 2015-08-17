#ifndef _H_bI
#define _H_bI

#include <iostream>
#include <cstdlib>

class biObject {
public:
	virtual std::string *str();
};

class biID: public biObject {
	std::string *value;
public:
	biID(char *);
	~biID();
	std::string *str(); 
};

extern int yylex(void);
extern int yyparse(void);
extern char *yytext;
extern int yylineno;
extern void yyerror(const char *msg);
#include "parser.tab.hpp"


#endif //  _H_bI
