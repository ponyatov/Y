#include "nuf.hpp"

map<string,string> var;

void var_init() {
	var["MODULE"]="nuf";
}

void W(char   c)	{ cout << c; }
void W(string s)	{ cout << s; }
void W(int    n)	{ cout << n; }

void yyerror(string msg) {
	cerr << "\n" << msg << " @ " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() {
	var_init();
	return yyparse();
}

