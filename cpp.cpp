#include "../hpp.hpp"
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
Sym::Sym(Sym*o):Sym(o->tag,o->val) {				// copy
	for (auto it=o->nest.begin(),e=o->nest.end();it!=e;it++)
		push(new Sym(*it));
}
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
	if (n>0) {
		for (int i=0;i<n-1;i++) S+="|   ";
		S += "\\___"; }
	return S; }
// --------------------------------------------------- evaluation (computing)
Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;				// lookup in glob.env[]
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)// recursive eval()
		(*it) = (*it)->eval();						// with objects replace
	return this;
}
// --------------------------------------------------- operators
Sym* Sym::dummy(Sym*o) { push(o); return this; }	// cons -> nest[] folding
Sym* Sym::doc(Sym*o){								// A "B"	docstring
	Sym*E = new Sym(this); E->par["doc"]=o; return E; }	
Sym* Sym::eq(Sym*o)	{ env[val]=o; return o; }		// A = B	assignment
Sym* Sym::at(Sym*o)	{ return dummy(o); }			// A @ B	apply
Sym* Sym::dot(Sym*o){ return new Cons(this,o); }	// A . B	cons
Sym* Sym::add(Sym*o){ return dummy(o); }			// A + B	add
Sym* Sym::add()		{ return this; }				// +A		sum
Sym* Sym::ins(Sym*o){ return dummy(o); }			// A += B	insert
// ============================================================================

// ================================================================= DIRECTIVE
string Directive::tagval() { return tagstr(); }
Directive::Directive(string V):Sym("",V) {
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }
}
Sym* Directive::eval() { Sym::eval();
	val=nest[0]->val; 
	if (tag==".module") env["MODULE"]=nest[0];
	if (tag==".title") env["TITLE"]=nest[0];
	if (tag==".author") env["AUTHOR"]=nest[0];
	if (tag==".github") env["GITHUB"]=nest[0];
	nest.erase(nest.begin());
	return this; }

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");						// nil
// ============================================================================

// =================================================================== SCALARS

// =================================================== string
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
// ===================================================

// =================================================== machine numbers
Hex::Hex(string V):Sym("hex",V) {}					// hexadecimal
Bin::Bin(string V):Sym("bin",V)	{}					// binary

// =================================================== integer
Int::Int(string V):Sym("int","") { val = atoi(V.c_str()); }
Int::Int(long   V):Sym("int","") { val = V; }
string Int::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }
Sym* Int::add(Sym*o) {
	cerr << "\n\n\n";
	cerr << tagval() << "\n";
	cerr << o->tagval() << "\n";
//	cerr << "car:" << o->car->tagval() << "\n";
//	cerr << "cdr:" << o->cdr->tagval() << "\n";
	cerr << "\n\n\n";
	if (o->tag=="int") return new Int(val+dynamic_cast<Int*>(o)->val);
	return Sym::add(o);
}

// =================================================== floating number
Num::Num(string V):Sym("num","") { val = atof(V.c_str()); }
string Num::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

// ============================================================================

// ================================================================ COMPOSITES
// ====================================================================== CONS
Cons::Cons(Sym*X,Sym*Y):Sym("","") { car=X, cdr=Y; }
Sym* Cons::eval() {									// eval as car@cdr
	return (car->eval())->at(cdr); }
string Cons::dump(int depth) {
	string S = Sym::dump(depth);
	S += car->dump(depth+1); S += cdr->dump(depth+1);
	return S; }
Sym* Cons::add() { return car->add(cdr); }
/* droppped due to bI lispification following SICP bible
List::List():Sym("[","]") {}						// [list]
Pair::Pair(Sym*A,Sym*B):Sym(A->val,B->val) {}		// pa:ir
Tuple::Tuple(Sym*A,Sym*B):Sym(",",",") {			// tu,ple
	push(A); push(B); }
Vector::Vector():Sym("","") {}						// <vector>
*/

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
		if (val=="+=") return nest[0]->ins(nest[1]);
	}
	return this;
}
Sym* Op::at(Sym*o) {
	if (val=="+") return o->add();
	return this;
}
Op* doc = new Op("doc");							// "doc"string operator
// ===================================================

// =================================================== function
Fn::Fn(string V,FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }				// apply function
// ===================================================

Lambda::Lambda():Sym("^","^") {}					// {la:mbda}

// ============================================================================

// ==================================================================== FILEIO
// =================================================== dir
Sym* dir(Sym*o) { return new Dir(o); }
string Dir::tagval() { return tagstr(); }
/*
Sym* Dir::add(Sym*o) {
	if (o->tag!="file") return Sym::add(o);
	else return new File(val+'/'+o->val);
}
*/
// ===================================================

// =================================================== file
File::File(Sym*o):Sym("file",o->val) {}
File::~File() { if (fh) fclose(fh); }
Sym* file(Sym*o) { return new File(o); }
string File::tagval() { return tagstr(); }
/*
Sym* File::addeq(Sym*o) {
	if (!fh) assert(fh=fopen(val.c_str(),"w"));		// auto open on write
	return new Int(fprintf(fh,"%s",o->val.c_str()));
}
*/
// ===================================================
// ============================================================================

// ======================================================================= GUI
Sym* message(Sym*o) 	{ return new Message(o); }
string Message::tagval(){ return tagstr(); }
Window::Window(Sym*o):Sym("window",o->val)	{ }
string Window::tagval()	{ return tagstr(); }
// ============================================================================

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	env["nil"]		= nil;
	// ----------------------------------------------- metainfo constants
	env["OS"]		= new Str(OS);					// host OS
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	env["TITLE"]	= new Str(TITLE);				// module title
	env["AUTHOR"]	= new Str(AUTHOR);				// author (c)
	env["LICENSE"]	= new Str(LICENSE);				// license
	env["GITHUB"]	= new Str(GITHUB);				// github home
	env["AUTOGEN"]	= new Str(AUTOGEN);				// autogenerated code signature
	env["LOGO"]		= new Str(LOGO);				// bI logo (w/o file extension)
	env["LISPLOGO"]	= new Str(LISPLOGO);			// Lisp Warning logo
	// ----------------------------------------------- internal functions
	// ----------------------------------------------- fileio
	env["dir"]		= new Fn("dir",dir);
	env["file"]		= new Fn("file",file);
	// ----------------------------------------------- GUI
	env["message"]	= new Fn("message",message);
	env["window"]	= new Fn("window",window);
}

