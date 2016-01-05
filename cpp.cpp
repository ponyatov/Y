#include "hpp.hpp"

#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(std::string msg) { std::cout<<YYERR; std::cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

std::map<std::string,AST*> env;
void env_init() {}

void W(AST*o)			{ std::cout << o->dump(); }
void W(std::string s)	{ std::cout << s; }

AST::AST(std::string T,std::string V) { tag=T; val=V; }
std::string AST::pad(int n) { std::string S; for(int i=0;i<n;i++) S+="\t"; return S; }
std::string AST::tagval()	{ return "<"+tag+":"+val+">"; }
std::string AST::dump(int depth) {
	std::string S = "\n"+pad(depth)+tagval();
	for (auto pr=par.begin() ; pr!=par.end() ; pr++)
		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin() ; it!=nest.end() ; it++)
		S += (*it)->dump(depth+1);
	return S;
}

AST* AST::eval() {
	AST*E = env[val]; if (E) return E;
	for (auto it=nest.begin() ; it!=nest.end() ; it++)
		(*it) = (*it)->eval();
	return this;
}

Sym::Sym(std::string V):AST("sym",V)	{}
Str::Str(std::string V):AST("str",V)	{}

Int::Int(std::string V):AST("int","")	{ val = atoi(V.c_str()); }
std::string Int::tagval() {
	std::ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

Hex::Hex(std::string V):AST("hex",V)	{}
Bin::Bin(std::string V):AST("bin",V)	{}

Num::Num(std::string V):AST("num","")	{ val = atof(V.c_str()); }
std::string Num::tagval() {
	std::ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }
