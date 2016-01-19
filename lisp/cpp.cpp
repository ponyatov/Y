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
Sym::Sym(Sym*o):Sym(o->tag,o->val) {				// copy
	for (auto it=o->nest.begin(),e=o->nest.end();it!=e;it++)
		push(new Sym(*it));
}
// --------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }		// add
// --------------------------------------------------- par{}ameters
// --------------------------------------------------- dumping
string Sym::tagval() {return "<"+tag+":"+val+">";}	// <T:V> header string
string Sym::tagstr() {return "<"+tag+":'"+val+"'>";}// <T:'V'> Str-like header
string Sym::dump(int depth) {						// dump symbol object
	string S = "\n" + pad(depth) + tagval();			// header
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)	// par{}emeters
		S += ","+pr->first+":"+pr->second->tagval();
	return S; }
string Sym::pad(int n) { string S;					// tab padding
	for (int i=0;i<n;i++) S+="\t"; return S; }
// --------------------------------------------------- evaluation (computing)
Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;				// lookup in glob.env[]
	E = new Sym(this);								// copy this
	for (auto it=E->nest.begin(),e=E->nest.end();it!=e;it++)// recursive eval()
		(*it) = (*it)->eval();						// with objects replace
	return E;//this;
}
// --------------------------------------------------- operators
Sym* Sym::doc(Sym*o){								// A "B"	docstring
	Sym*E = new Sym(this); E->par["doc"]=o; return E; }	
Sym* Sym::eq(Sym*o)	{ env[val]=o; return o; }		// A = B	assignment
Sym* Sym::at(Sym*o)	{ push(o); return this; }		// A @ B	apply
Sym* Sym::dot(Sym*o){ return new Cons(this,o); }	// A . B	cons
// ============================================================================

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");						// nil
// =================================================== classic Lisp cons element
Cons::Cons(Sym*X,Sym*Y):Sym("","") { car=X, cdr=Y; }
Sym* Cons::eval() { (car->eval())->at(cdr->eval()); }// eval as car@cdr
string Cons::dump(int depth) {
	string S = Sym::dump(depth);
	S += car->dump(depth+1);
	S += cdr->dump(depth+1);
	return S;
}
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
	if (nest.size()==2) {							// A op B bin.operator
		if (val=="@") return nest[0]->at(nest[1]);
		if (val=="doc") return nest[0]->doc(nest[1]);
	}
	return this;
}
Op* doc = new Op("doc");							// "doc"string operator
// ===================================================

// =================================================== function
Fn::Fn(string V,FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }				// apply function
// ===================================================

// ============================================================================

// ==================================================================== FILEIO
// =================================================== dir
Dir::Dir(Sym*o):Sym("dir",o->val) {}
Sym* dir(Sym*o) { return new Dir(o); }
string Dir::tagval() { return tagstr(); }
// ===================================================
// =================================================== file
File::File(Sym*o):Sym("file",o->val) {}
Sym* file(Sym*o) { return new File(o); }
string File::tagval() { return tagstr(); }
// ===================================================
// ============================================================================

// ======================================================================= GUI
// ============================================================================

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	env["nil"]		= nil;
	// ----------------------------------------------- metainfo constants
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	// ----------------------------------------------- internal functions
	env["dir"]		= new Fn("dir",dir);
	env["file"]		= new Fn("file",file);
}
// ============================================================================
