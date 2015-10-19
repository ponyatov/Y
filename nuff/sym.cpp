#include "sym.hpp"

// \\ object

object::object(string T, string V)	{ tag=T; value=V; }
string object::tagval()				{ return tag+":"+value; }
string object::dump(int depth)		{ return "\n"+pad(depth)+tagval(); }
object* object::eval()				{ value = env[value]; return this; }

string object::pad(int n) {
	string S;
	for (int i=0 ; i<n ; i++) S+="\t";
	return S;
}

// // object

map<string,string> env;

void env_init() {
	env["MODULE"]="sym";
	env["HPP"]="#include \"sym.hpp\"";
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

