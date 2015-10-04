#include "dura.hpp"

string pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }

string sym::dump(int depth) {
	string S = "\n"+pad(depth)+"<"+tag+":"+value+">";
	return S;
}

void W(string* s)	{ cout << *s ; }
void W(sym* s) 		{ cout << s->dump(); }

void yyerror(string err) {
	cerr << err << "#" << yylineno << ":" << yytext << "\n";
	exit(-1);
}

int main() { return yyparse(); }

