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

// ------------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }

// ------------------------------------------------------- par{}ameters
void Sym::partag(Sym*o) { par[o->tag]=o; }

// ------------------------------------------------------- dumping
string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::tagstr() { return "<"+tag+":'"+val+"'>"; }	// <T:'V'> header
string Sym::pad(int n) { string S;						// pad as tree
	//for(int i=0;i<n;i++) S+="\t"; return S; }
	for(int i=0;i<n-1;i++) S+="|   ";
	if (n) S+="\\___";
	return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)	// par{}ameters
		S += ","+pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S += (*it)->dump(depth+1);
	return S; }

// ------------------------------------------------------- evaluation

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;					// lookup in glob.env[]
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// recursive eval()
		(*it) = (*it)->eval();							// with objects replace
	return this; }

// ------------------------------------------------------- operators
	
Sym* Sym::eq(Sym*o)		{ env[val]=o; return o; }		// A = B	assignment
Sym* Sym::at(Sym*o)		{ push(o); return this; }		// A @ B	apply

Sym* Sym::str()			{ return new Str(val); }		// str(A)	as string

Sym* Sym::add(Sym*o)	{ push(o); return this; }		// A + B	add
Sym* Sym::div(Sym*o)	{ push(o); return this; }		// A / B	div

Sym* Sym::ins(Sym*o)	{ push(o); return this; }		// A += B	insert

// ================================================================== SPECIALS
Sym* Rd = new Sym("mode","R");							// read mode
Sym* Wr = new Sym("mode","W");							// write mode

// =================================================================== SCALARS

// ======================================================= string
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
Sym* Str::eq(Sym*o) { yyerror("immutable"); }
Sym* Str::add(Sym*o) { return new Str(val+o->str()->val); }

// ================================================================ COMPOSITES

// ====================================================================== LIST
List::List():Sym("[","]") {}							// [list]
Sym* List::str() {										// concatenate elements
	string S;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->str()->val;
	return new Str(S);
}
Sym* List::div(Sym*o) {									// split elements
	Sym* L = new List();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++) {
		L->push((*it)); L->push(o); }
	L->nest.pop_back();
	return L;
}

// =============================================================== FUNCTIONALS

// ======================================================= operator
Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	Sym::eval();										// nest[]ed evaluate
	Sym* Result=this;
	if (nest.size()==2) {								// A op B bin.operator
		if (val=="=")	Result=nest[0]->eq(nest[1]);	// A = B
		if (val=="@")	Result=nest[0]->at(nest[1]);	// A @ B
		if (val=="+")	Result=nest[0]->add(nest[1]);	// A + B
		if (val=="/")	Result=nest[0]->div(nest[1]);	// A / B
		if (val=="+=")	Result=nest[0]->ins(nest[1]);	// A += B
	}
	if (par.count("doc")) Result->par["doc"]=par["doc"];
	return Result; }

// ======================================================= function
Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }					// apply function

// ==================================================================== FILEIO

// ======================================================= directory
Sym* dir(Sym*o) { return new Dir(o); }
Sym* Dir::add(Sym*o) {
	o->partag(Wr); o->partag(this); push(o);
	assert(o->tag=="file");
	assert(dynamic_cast<File*>(o)->fh=fopen((val+'/'+o->val).c_str(),"w"));
	return o; }
	
// ======================================================= file
Sym* file(Sym*o) { return new File(o); }
File::File(Sym*o):Sym("file",o->val) {}
File::~File() { if (fh) fclose(fh); }

Sym* File::ins(Sym*o) {
	push(o->str());
	if (fh) fprintf(fh,"%s",o->str()->val.c_str());
	return this; }

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- metainfo constants
	env["OS"]		= new Str(OS);					// host OS
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
//	env["TITLE"]	= new Str(TITLE);				// module title
//	env["ABOUT"]	= new Str(ABOUT);				// short module description
	env["AUTHOR"]	= new Str(AUTHOR);				// author (c)
	env["LICENSE"]	= new Str(LICENSE);				// license
	env["GITHUB"]	= new Str(GITHUB);				// github home
	env["AUTOGEN"]	= new Str(AUTOGEN);				// autogenerated code signature
	env["LOGO"]		= new Str(LOGO);				// bI logo (w/o file extension)
	// ----------------------------------------------- specials
	env["R"]		= Rd;
	env["W"]		= Wr;
	// ----------------------------------------------- fileio
	env["dir"]		= new Fn("dir",dir);
	env["file"]		= new Fn("file",file);
}

