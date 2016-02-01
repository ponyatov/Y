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
	for(int i=0;i<n-1;i++) S+="|   ";
	if (n) S+="\\___";
	return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
	return S; }

// ------------------------------------------------------- evaluation
Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// lookup in glob.env[]
	return this; }

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");							// nil/false

// =================================================================== SCALARS

// ======================================================= integer
Int::Int(string V):Sym("int","") { val = atoi(V.c_str()); }
Int::Int(long N):Sym("int","") { val = N; }
string Int::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

// ================================================================ COMPOSITES
// ====================================================================== CONS
Cons::Cons(Sym*X,Sym*Y):Sym("","") { A=X; D=Y; }		// classic Lisp cons
string Cons::dump(int depth) {
	return A->dump(depth)+D->dump(depth+1); }
Sym* Cons::eval() { return A->eval()->at(D); }

// =============================================================== FUNCTIONALS

// ======================================================= function
Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }					// apply

// ==================================================================== FILEIO

// ======================================================= directory
Sym* dir(Sym*o) { 
	return new Cons(new Dir(o),dynamic_cast<Cons*>(o)->D); }
Dir::Dir(Sym*o):Sym("dir",dynamic_cast<Cons*>(o)->A->val) {}

// ======================================================= file
Sym* file(Sym*o) {
	return new Cons(new File(o),dynamic_cast<Cons*>(o)->D); }
File::File(Sym*o):Sym("file",dynamic_cast<Cons*>(o)->A->val) {}

// ====================================================================== LISP
Sym* Sym::at(Sym*o)	{ return new Cons(this,o); }

Sym* sum(Sym*o) { 
	Sym* A = dynamic_cast<Cons*>(o)->A; 
	Sym* D = dynamic_cast<Cons*>(o)->D;
	return A->sum(D);
}
Sym* Sym::sum(Sym*o) { return new Cons(this,o); }
Sym* Int::sum(Sym*o) { 
	if (o->tag=="int")	return new Int(val+dynamic_cast<Int*>(o)->val);
	else 				Sym::sum(o);
}

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- specials
	env["nil"]		= nil;
	// ----------------------------------------------- lisp functions
	env["+"]		= new Fn("+",sum);
	// ----------------------------------------------- fileio
	env["dir"]		= new Fn("dir",dir);
	env["file"]		= new Fn("file",file);
}
