#include "hpp.hpp"
// =================================================== error callback
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
// =================================================== main()
int main() { env_init(); return yyparse(); }
// =================================================== writers
void W(Sym* o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }

// =================================================== Abstract Symbolic Type (AST)
// --------------------------------------------------- constructors
Sym::Sym(string T,string V)		{ tag=T; val=V; };	// <T:V>
Sym::Sym(string V):Sym("sym",V)	{}					// token
// --------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }		// add
// --------------------------------------------------- dumping
string Sym::tagval() {return "<"+tag+":"+val+">";}	// <T:V> header string
string Sym::tagstr() {return "<"+tag+":'"+val+"'>";}// <T:'V'> Str-like header
string Sym::dump(int depth) {						// dump symbol object
	string S = "\n" + pad(depth) + tagval();			// header
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }
string Sym::pad(int n) { string S;					// tab padding
	for (int i=0;i<n;i++) S+="\t"; return S; }
// --------------------------------------------------- evaluation (computing)
Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;				// lookup in glob.env[]
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)// recursive eval()
		(*it) = (*it)->eval();						// with objects replace
	return this;
}
// --------------------------------------------------- operators
// ============================================================================

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");						// nil
// =================================================== classic Lisp cons element
Cons::Cons(Sym*X,Sym*Y):Sym("","") { car=X, cdr=Y; }
// ============================================================================

// =================================================================== SCALARS

// =================================================== string
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
// ===================================================

// ============================================================================

// ================================================================ COMPOSITES
// ============================================================================

// =============================================================== FUNCTIONALS

// =================================================== operator
Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	Sym::eval();									// nest[]ed evaluate
	return this;
}
// ===================================================

// ============================================================================

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	env["nil"]		= nil;
	// ----------------------------------------------- metainfo constants
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	// ----------------------------------------------- internal functions
}
// ============================================================================
