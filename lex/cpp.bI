cpp	= next + file @ 'cpp.cpp'
cpp += '#include "hpp.hpp"\n'
cpp += '#define YYERR "\\n\\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\\n\\n"\n'
cpp += 'void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }\n'
#cpp += 'int main() { return yyparse(); }\n'
cpp += 'int main(int argc, char *argv[]) {
	cerr << "\\n" << MODULE << " : " << TITLE << "\\n" << ABOUT << "\\n";
	cerr << /* (c) */ AUTHOR << "\\n\\n";
	return yyparse(); }'
cpp += '
void W(string s) { cout << s; }
void W(Sym*o) { W(o->dump()); }
'
cpp += '
// ------------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }
// ------------------------------------------------------- par{}ameters
void Sym::partag(Sym*o) { par[o->tag]=o; }
void Sym::parval(Sym*o) { par[o->val]=o; }
// ------------------------------------------------------- dumping
string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::pad(int n) { string S;						// pad as tree
	for(int i=0;i<n;i++) S+="\t"; return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\\n" + pad(depth) + tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }
'
cpp += '
// ------------------------------------------------------- evaluation

Sym* Sym::eval() {
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// recursive eval()
		(*it) = (*it)->eval();							// with objects replace
	return this; }
'
