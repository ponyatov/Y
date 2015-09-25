
#include "sym.hpp"

sym::sym(string C,char* V) { cls=C; val=string(V); }

string sym::dump()	{ return "<"+cls+":"+val+">"; }
string sym::eval()	{ return val; }

void yyerror(string s) {
	cerr << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	cout << "# " << argv[0] << "\n";
	return yyparse();
}

