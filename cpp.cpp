#include "hpp.hpp"

#define YYERR "\n\n"<<msg<<"#"<<yylineno<<":["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { return yyparse(); }

void W(char    c,bool to_file)	{ cout << c ; }
void W(string  s,bool to_file)	{ cout <<  s; }
void W(string *s,bool to_file)	{ cout << *s; }
void W(sym    *o,bool to_file)	{ cout << o->dump(); }

sym::sym(string T,string V)	{ tag=T; value=V; }
string sym::pad(int n) {string S; for (int i=0;i<n;i++) S+="\t"; return S;}
string sym::tagval()	{ return "<"+tag+":"+value+">"; }
string sym::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	return S;
}

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\t'&&value[0]!=' ')) {
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\t'||value[0]==' '))
		                 value.erase(0,1);
}

Module::Module(string V):sym("module",V)	{
	#ifdef __MINGW32__
	mkdir(V.c_str());
	#else
	mkdir(V.c_str(),0700);
	#endif
}

Module *curr_module = new Module("next");
File *curr_file = NULL;
