#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(Sym*o)		{ cout<<o->dump(); }
void W(string s)	{ cout<<s; }

Sym::Sym(string T,string V)		{ tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V)	{}
void Sym::push(Sym*o)			{ nest.push_back(o); }
void Sym::setpar(Sym*o)			{ par[o->val]=o; }

string Sym::pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string Sym::tagval()	{ return "<"+tag+":"+val+">"; }
string Sym::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	for (auto pr=par.begin();pr!=par.end();pr++)
		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin();it!=nest.end();it++)
		S += (*it)->dump(depth+1);
	return S;
}

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// lookup in glob.env[]
	for (auto it=nest.begin();it!=nest.end();it++)		// recurse eval()
		(*it) = (*it)->eval();
	return this;
}

Sym* Sym::eq(Sym*o)		{ env[o->val]=o; return o; }
Sym* Sym::at(Sym*o)		{ push(o); return this; }
Sym* Sym::dot(Sym*o)	{ setpar(o); return this; }

map<string,Sym*> env;
void env_init() { fn_init(); }

Str::Str(string V):Sym("str",V) {}
string Str::tagval()			{ return "<"+tag+":'"+val+"'>"; }

List::List():Sym("[","]") {}
Pair::Pair(Sym*A,Sym*B):Sym(A->val,B->val) {}

Op::Op(string V):Sym("op",V) {}
Lambda::Lambda():Sym("^","^") {}

void fn_init() {}

