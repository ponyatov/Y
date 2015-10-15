#include "sym.hpp"

map<string,string> env;

void env_init() {
	env["MODULE"]="sym";
}

void W(char   c)	{ cout << c; }
void W(string s)	{ cout << s; }

void yyerror(string msg) {
	cerr << "\n" << msg << " @ " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() {
	env_init();
	return yyparse();
}

