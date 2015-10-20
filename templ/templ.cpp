#include "templ.hpp"

object::object(string T, string V)	{ tag=T; value=V; }
string object::tagval()	{ return "<"+tag+":"+value+">"; }
string object::dump()	{ return tagval(); }

directive::directive(string V):object("",V) {
	while (value.size() && ( value[0] != ' ' && value[0] != '\t' ) ) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && ( value[0] == ' ' || value[0] == '\t' ) ) {
		value.erase(0,1);
	}
}

module::module(string V):object("module",V) { 
#ifdef __MINGW32__
	mkdir(V.c_str());
#else
	#error mkdir
#endif
}
module *curr_module = new module("tmp");

void W(char    c)	{ cout <<  c; }
void W(string  s)	{ cout <<  s; }
void W(string *s)	{ cout << *s; }

void yyerror(string msg) {
	cout << "\n" << msg << "@" << yylineno << ":[" << yytext << "]\n\n";
	cerr << "\n" << msg << "@" << yylineno << ":[" << yytext << "]\n\n";
	exit(-1);
}

int main()	{ return yyparse(); }

