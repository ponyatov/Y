// lexer/parser interface (flex/bison)

extern int yylex();
extern int yylineno;
extern char* yytext;
extern void incFile(sym*);
extern int yyparse();
extern void yyerror(string);
\#include "ypp.tab.hpp"
\#define TC(X)	{ yylval.c = yytext[0]; return X; }			/* char token */
\#define T1(X)	{ yylval.c = yytext[1]; return X; }			/* escaped char */
\#define TS(X)	{ yylval.s = new string(yytext); return X; }/* string tok */
\#define TO(C,X)	{ yylval.o = new sym(C,yytext); return X; }	/* generic sym */
\#define TX(C,X)	{ yylval.o = new C(yytext); return X; }		/* inherited sym */
