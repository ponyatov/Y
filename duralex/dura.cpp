#include "dura.hpp"

biObject::biObject(string T, string V)	{ tag=T; value=V; }

string pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }

string biObject::dump(int depth) {
	string S = "\n"+pad(depth)+"<"+tag+":"+value+">";
	return S;
}

biModule::biModule(string V):biObject("module",V) {
	mkdir(value.c_str());
}

biModule *bi_module = new biModule("tmp");

void W(string* s)		{ cout << *s ; }
void W(string  s)		{ cout <<  s ; }
void W(biObject* s) 	{ cout << s->dump(); }

void yyerror(string err) {
	cerr << "\n\n" << err << " # " << yylineno << " : " << yytext << "\n";
	exit(-1);
}

int main() { return yyparse(); }

