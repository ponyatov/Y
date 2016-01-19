#include "hpp.hpp"
// =================================================== error callback
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
// =================================================== main()
#ifndef __MINGW32__
int main() { env_init(); return yyparse(); }
#endif
// =================================================== writers
void W(Sym* o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }

// =================================================== Abstract Symbolic Type (AST)
// --------------------------------------------------- constructors
Sym::Sym(string T,string V)		{ tag=T; val=V; };	// <T:V>
Sym::Sym(string V):Sym("sym",V)	{}					// token
// --------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }		// add
// --------------------------------------------------- par{}ameters
void Sym::setpar(Sym*o) { par[o->val]=o; }			// add
// --------------------------------------------------- dumping
string Sym::tagval() {return "<"+tag+":"+val+">";}	// <T:V> header string
string Sym::tagstr() {return "<"+tag+":'"+val+"'>";}// <T:'V'> Str-like header
string Sym::dump(int depth) {						// dump symbol object
	string S = "\n" + pad(depth) + tagval();			// header
	for (auto pr=par.begin() ; pr!=par.end() ; pr++)	// par{}ameters
		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin() ; it!=nest.end() ; it++)	// nest[]ed
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
Sym* Sym::doc(Sym*o){ par["doc"]=o; return this; }	// A "B"	docstring
Sym* Sym::eq(Sym*o)	{ env[val]=o; return o; }		// A = B	assignment
Sym* Sym::at(Sym*o)	{ push(o); return this; }		// A @ B	apply
Sym* Sym::dot(Sym*o){ return new Cons(this,o); }	// A . B	cons
// ============================================================================

string Directive::tagval() { return tagstr(); }
Directive::Directive(string V):Sym("",V) {				// == .directive ==
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }
}

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

													// == machine numbers ==
Hex::Hex(string V):Sym("hex",V) {}					// hexadecimal
Bin::Bin(string V):Sym("bin",V)	{}					// binary

														// == integer ==
Int::Int(string V):Sym("int","") { val = atoi(V.c_str()); }
string Int::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }
														// == floating number ==
Num::Num(string V):Sym("num","") { val = atof(V.c_str()); }
string Num::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

// ============================================================================


														// == composites ==
List::List():Sym("[","]") {}							// [list]
Pair::Pair(Sym*A,Sym*B):Sym(A->val,B->val) {}			// pa:ir
Tuple::Tuple(Sym*A,Sym*B):Sym(",",",") {				// tu,ple
push(A); push(B); }
Vector::Vector():Sym("","") {}							// <vector>

// =============================================================== FUNCTIONALS

// =================================================== operator
Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	Sym::eval();									// nest[]ed evaluate
	if (nest.size()==2) {							// A op B bin.operator
		if (val=="=") return nest[0]->eq(nest[1]);
		if (val=="@") return nest[0]->at(nest[1]);
		if (val==".") return nest[0]->dot(nest[1]);
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

Lambda::Lambda():Sym("^","^") {}						// {la:mbda}

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
Sym* window(Sym*o)			{ return new Window(o); }
string Window::tagval()		{ return tagstr(); }

Sym* message(Sym*o) 		{ return new Message(o); }
string Message::tagval()	{ return tagstr(); }
// ============================================================================

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	env["nil"]		= nil;
	// ----------------------------------------------- metainfo constants
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	env["AUTHOR"]	= new Str(AUTHOR);				// author (c)
	env["LICENSE"]	= new Str(LICENSE);				// license
	env["GITHUB"]	= new Str(GITHUB);				// github home
	env["AUTOGEN"]	= new Str(AUTOGEN);				// autogenerated code signature
	env["LOGO"]		= new Str(LOGO);				// bI logo (w/o file extension)
	env["LISPLOGO"]	= new Str(LISPLOGO);			// Lisp Warning logo
	// ----------------------------------------------- internal functions
	env["window"] = new Fn("window",window);
	env["message"] = new Fn("message",message);
}

