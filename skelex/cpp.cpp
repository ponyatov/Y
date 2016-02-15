#include "hpp.hpp"
// ======================================================= error callback
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
// ======================================================= main()
int main() { glob_init(); return yyparse(); }

// ======================================================= writers
void W(Sym* o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }

// ============================================== Abstract Symbolic Type (AST)

// ------------------------------------------------------- constructors
Sym::Sym(string T,string V) { tag=T; val=V; 			// <T:V>
	env = new Env(&glob_env); }
Sym::Sym(string V):Sym("",V)	{}						// token

// ------------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }

// ------------------------------------------------------- env[]irnoment
void Sym::par(Sym*o) { env->par(o); }

// ------------------------------------------------------- dumping
string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::tagstr() { return "<"+tag+":'"+val+"'>"; }	// <T:'V'> header
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval() + env->dump();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }

// ------------------------------------------------------- evaluation

Sym* Sym::eval() {
	Sym* E = env->lookup(this); if (E) return E;		// lookup in env[]
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// recursive eval()
		(*it) = (*it)->eval();							// with objects replace
	return this; }

// ------------------------------------------------------- operators

Sym* Sym::str()			{ return new Str(val); }		// str(A)	as string

Sym* Sym::eq(Sym*o)		{ env->next->set(val,o);		// A = B	assignment
	return o; }
Sym* Sym::at(Sym*o)		{ push(o); return this; }		// A @ B	apply

Sym* Sym::add(Sym*o) { Sym* R = new Op("+");			// A + B	add
	R->push(this); R->push(o); return R; }
Sym* Sym::div(Sym*o) { Sym* R = new Op("/");			// A / B	div
	R->push(this); R->push(o); return R; }

Sym* Sym::ins(Sym*o)	{ push(o); return this; }		// A += B	insert

// =================================================================== SCALARS

Scalar::Scalar(string T,string V):Sym(T,V) {};
Sym* Scalar::eval() { return this; }					// block env[] lookup

// ======================================================= string
Str::Str(string V):Scalar("str",V) {}
string Str::tagval() { return tagstr(); }
Sym* Str::eq(Sym*o) { yyerror("immutable"); }
Sym* Str::add(Sym*o) { return new Str(val+o->str()->val); }
Sym* Str::upcase(Sym*o) {								// to UPCASE
	string S = o->str()->val;
	transform(S.begin(),S.end(),S.begin(),::toupper);
	return new Str(S); }

List::List():Sym("[","]") {}
Sym* List::div(Sym*o) {
	List*L = new List();
	if (nest.size()) {
		for (auto it=nest.begin(),e=nest.end();it!=e;it++) {
			L->push(*it); L->push(o); }
		L->nest.pop_back();
	}
	return L;
}
Sym* List::str() { string S;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++) S += (*it)->str()->val;
	return new Str(S); }

Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	if (val=="~") return nest[0]; else Sym::eval();
	if (nest.size()==2) {
		if (val=="@") return nest[0]->at(nest[1]);
		if (val=="=") return nest[0]->eq(nest[1]);
		if (val=="+") return nest[0]->add(nest[1]);
		if (val=="/") return nest[0]->div(nest[1]);
		if (val=="+=") return nest[0]->ins(nest[1]);
	}
	return this;
}

Fn::Fn(string V,FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }

File::File(Sym*o):Sym("file",o->val) {}
Sym* File::file(Sym*o) { return new File(o); }
Sym* File::eq(Sym*o) { yyerror(tagval()+"="+o->tagval()); }

Env::Env(Env*X) { next=X; }
void Env::par(Sym*o) { iron[o->val]=o; }
void Env::set(string V,Sym*o) { iron[V]=o; }
string Env::dump() { string S;
	for (auto it=iron.begin(),e=iron.end();it!=e;it++)
		S += "," + it->first + ":" + it->second->tagval();
	return S; }

Env glob_env(NULL);
Sym* Env::lookup(Sym*o) {
	auto it = iron.find(o->val); if (it!=iron.end()) return it->second;
	if (next) return next->lookup(o);
	return NULL;
}
void glob_init() {
	// ----------------------------------------------- metainfo constants
	glob_env.iron["MODULE"]	= new Str(MODULE);		// module name
	// ----------------------------------------------- string
	glob_env.iron["upcase"]	= new Fn("upcase",Str::upcase);
	// ----------------------------------------------- fileio
	glob_env.iron["file"]	= new Fn("fn",File::file);
}

