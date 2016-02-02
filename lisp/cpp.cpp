#include "hpp.hpp"
// ======================================================= error callback
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
// ======================================================= main()
int main() { env_init(); return yyparse(); }
// ======================================================= writers
void W(Sym* o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }

// ============================================== Abstract Symbolic Type (AST)

// ------------------------------------------------------- constructors
Sym::Sym(string T,string V) { tag=T; val=V; };			// <T:V>
Sym::Sym(string V):Sym("sym",V)	{}						// token

// ------------------------------------------------------- dumping
string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::pad(int n) { string S;						// pad as tree
	for(int i=0;i<n;i++) S+="\t"; return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
	return S; }
	
// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");							// nil/false

// ================================================================ COMPOSITES
// ====================================================================== CONS
Cons::Cons(Sym*X,Sym*Y):Sym("","") { A=X; D=Y; }		// classic Lisp cons
string Cons::dump(int depth) {
	return A->dump(depth+1)+D->dump(depth+1); }

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- specials
	env["nil"]		= nil;
}
