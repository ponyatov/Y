#ifndef _H_PIL
#define _H_PIL

#include "PIL/hpp.hpp"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern void incFile(sym*);
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"
#define TC(X)	{ yylval.c = yytext[0]; return X; }
#define T1(X)	{ yylval.c = yytext[1]; return X; }
#define TS(X)	{ yylval.s = new string(yytext); return X; }
#define TO(C,X)	{ yylval.o = new sym(C,yytext); return X; }
#define TX(C,X)	{ yylval.o = new C(yytext); return X; }

void W(char   ,bool to_file=true);
void W(string ,bool to_file=true);
void W(string*,bool to_file=true);
void W(sym*   ,bool to_file=true);

#endif // _H_PIL
