
#include "sym.hpp"

sym::sym(string C,string V)	{ cls=C; val=V; }
sym::sym(sym* A, sym* B)	{ cls=A->val; val=B->val; }

string sym::dump()	{ return "<"+cls+":"+val+">"; }
string sym::eval()	{ return val; }

module::module(sym* A, sym* B):sym(A,B)		{ mkdir(val.c_str()); }
module::module(string A):sym(".module",A)	{ mkdir(val.c_str()); }

module curr_module("tmp");

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

void W(string s)	{ cout << s; }

int main(int argc, char *argv[]) {
	cout << "# " << argv[0] << "\n";
	return yyparse();
}

