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
Sym::Sym(string T,string V) { tag=T; val=V; next=NULL; };	// <T:V>
Sym::Sym(string V):Sym("sym",V)	{}							// token

// ------------------------------------------------------- dumping
string Sym::dump(int depth) {
	string S = "\n"+pad(depth)+"<"+val+">";
	if (next) S += next->dump(depth+1);
	return S; }
string Sym::pad(int n) { string S; for(int i=0;i<n;i++) S+="\t"; return S; }
	
// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");							// nil/false

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- specials
	env["nil"]		= nil;
}
