#include "bI.hpp"

// object

biObject::biObject(const char* C,char* V) { 
	cls = new string(C);
	val = new string(V);
}

string* biObject::dump()	{ return new string("<"+*cls+":"+*val+">"); }
string* biObject::eval()	{ return val; }

// writers

void W(string* s)	{ cout << *s; }
void W(string  s)	{ cout <<  s; }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { return yyparse(); }

