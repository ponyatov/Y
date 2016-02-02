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

// ------------------------------------------------------- evaluation

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// lookup in glob.env[]
	else return this; }

// ------------------------------------------------------- operators

Sym* Sym::at(Sym*o)		{ return new Cons(this,o); }	// A @ B	apply
string Sym::str()		{ return val; }
Sym* Sym::add(Sym*o)	{								// A + B	add
	return new Cons(env["+"],new Cons(this,o)); }

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");							// nil/false

// =================================================================== SCALARS

// ======================================================= string
Str::Str(string V):Sym("str",V) {}
Sym* Str::add(Sym*o) { return new Str(val+o->eval()->val); }

// ================================================================ COMPOSITES
// ====================================================================== CONS
Cons::Cons(Sym*X,Sym*Y):Sym("","") { A=X; D=Y; }		// classic Lisp cons
string Cons::dump(int depth) {
	return A->dump(depth+1)+D->dump(depth+1); }
Sym* Cons::eval() { return A->eval()->at(D->eval()); }
string Cons::str()	{ return A->str()+D->str(); }

// =============================================================== FUNCTIONALS
// ======================================================= function
Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }					// apply function

// ================================================================= OPERATORS
Sym* sum(Sym*o) {										// + operator
	Sym* A = dynamic_cast<Cons*>(o)->A;
	Sym* D = dynamic_cast<Cons*>(o)->D;
	return A->add(D); }

Sym* def(Sym*o) {										// = operator
	Sym* A = dynamic_cast<Cons*>(o)->A;
	Sym* D = dynamic_cast<Cons*>(o)->D;
	env[A->val] = D; return D; }	

// ==================================================================== FILEIO

// ======================================================= file
File::File(Sym*o):Sym("file",o->val) {}
Sym* file(Sym*o) { return new File(o); }

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- metainfo constants
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	// ----------------------------------------------- specials
	env["nil"]		= nil;
	// ----------------------------------------------- operators
	env["="]		= new Fn("=",def);				// =
	env["+"]		= new Fn("+",sum);				// +
	// ----------------------------------------------- fileio
	env["file"]		= new Fn("file",file);
}
