#include "bI.hpp"

// writers

void W(string* s)	{ cout << *s; }
void W(string  s)	{ cout <<  s; }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { return yyparse(); }

