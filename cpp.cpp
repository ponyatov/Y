#include "../hpp.hpp"
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
void Sym::parval(Sym*o) { par[o->val]=o; }

// ------------------------------------------------------- dumping
string Sym::tagval() { return "<"+tag+":"+val+">"; }	// <T:V> header string
string Sym::tagstr() {									// <T:'V'> header
	string S = "<"+tag+":'";
	for (int i=0;i<val.size();i++)
		switch (val[i]) {
			case '\n': S+="\\n"; break;
			case '\t': S+="\\t"; break;
			default: S+=val[i];
		}
	return S+"'>"; }
string Sym::pad(int n) { string S;						// pad as tree
	//for(int i=0;i<n;i++) S+="\t"; return S; }
	for(int i=0;i<n-1;i++) S+="|   ";
	if (n) S+="\\___";
	return S; }

string Sym::dump(int depth) {							// dump as text
	string S = "\n" + pad(depth) + tagval();
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)	// par{}ameters
		S += ","+pr->first+":"+pr->second->tagval();
//	for (auto mt=meth.begin(),e=meth.end();mt!=e;mt++)	// math{}ods
//		S += "\n"+pad(depth+1)+mt->first+mt->second->dump(depth+2);
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
Sym* Sym::inher(Sym*o)	{								// A : B	inheritance
	return new Sym(this->val,o->val); }
Sym* Sym::dot(Sym*o)	{ return new Pair(this,o); }	// A . B	pair

Sym* Sym::member(Sym*o)	{								// A % B	class member
	meth[o->str()->val]=o->nest[0]; return this; }

Sym* Sym::str()			{ return new Str(val); }		// str(A)	as string

Sym* Sym::add(Sym*o)	{ push(o); return this; }		// A + B	add
Sym* Sym::div(Sym*o)	{ push(o); return this; }		// A / B	div

Sym* Sym::ins(Sym*o)	{ push(o); return this; }		// A += B	insert

// ------------------------------------------------------- translate
Sym* Sym::h()			{ return new Str("extern "+tag+"("+val+");\n"); }

// ================================================================= DIRECTIVE
Directive::Directive(string V):Sym("",V) {
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }
}
Sym* Directive::eval() {
	if (tag==".end") { W(this); W("\n"); exit(0); }
	return this; }

// ================================================================== SPECIALS
Sym* nil = new Sym("nil","");							// nil/false
Sym* Rd = new Sym("mode","R");							// read mode
Sym* Wr = new Sym("mode","W");							// write mode

// =================================================================== SCALARS

// ======================================================= string
Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
Sym* Str::eq(Sym*o) { yyerror("immutable"); }
Sym* Str::add(Sym*o) { return new Str(val+o->str()->val); }
Sym* upcase(Sym*o) { 
	string S = o->str()->val;
	transform(S.begin(),S.end(),S.begin(),::toupper);
	return new Str(S);
}

// ======================================================= machine numbers
Hex::Hex(string V):Sym("hex",V) {}						// hexadecimal
Bin::Bin(string V):Sym("bin",V)	{}						// binary string

// ======================================================= integer
Int::Int(string V):Sym("int","") { val = atoi(V.c_str()); }
string Int::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

// ======================================================= floating number
Num::Num(string V):Sym("num","") { val = atof(V.c_str()); }
string Num::tagval() {
	ostringstream os; os<<"<"<<tag<<":"<<val<<">"; return os.str(); }

// ================================================================ COMPOSITES

// ====================================================================== LIST
// ======================================================= [list]

List::List():Sym("[","]") {}

Sym* List::str() {										// concatenate elements
	string S;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->str()->val;
	return new Str(S); }

Sym* List::div(Sym*o) {									// split elements
	Sym* L = new List();
	if (nest.size()) {
		for (auto it=nest.begin(),e=nest.end();it!=e;it++) {
			L->push((*it)); L->push(o); }
		L->nest.pop_back(); }
	return L; }

// ======================================================= pa:ir

Pair::Pair(Sym*A,Sym*B):Sym("","") { push(A); push(B); }

Sym* Pair::eq(Sym*o) {
	return this;
/*	
	assert(nest.size()==2);
	cout << "\n\nnest0 " << nest[0]->dump() << endl;
	cout << "\n\nnest1 " << nest[1]->dump() << endl;
	return nest[0];
	*/
}

// =============================================================== FUNCTIONALS

// ======================================================= operator
Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	if (val=="=") return nest[0]->eq(nest[1]->eval());	// A = B
	Sym::eval();										// nest[]ed evaluate
	Sym* Result=this;
	if (nest.size()==2) {								// A op B bin.operator
//		if (val=="=")	Result=nest[0]->eq(nest[1]);	// A = B
		if (val=="@")	Result=nest[0]->at(nest[1]);	// A @ B
		if (val==".")	Result=nest[0]->dot(nest[1]);	// A . B
		if (val=="%")	Result=nest[0]->member(nest[1]);// A % B -> A
		if (val==":")	return nest[0]->inher(nest[1]);	// A : B
		if (val=="+")	Result=nest[0]->add(nest[1]);	// A + B
		if (val=="/")	return nest[0]->div(nest[1]);
		if (val=="+=")	return nest[0]->ins(nest[1]);
	}
	if (par.count("doc")) Result->par["doc"]=par["doc"];// copy par[doc]
	return Result; }

Sym* Op::eq(Sym*o) { return this->eval()->eq(o); }		// compute lvalue
// ===================================================

// ======================================================= function
Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }					// apply function
// ===================================================

// ======================================================= {lambda}
Lambda::Lambda():Sym("^","^") {}						// {la:mbda}
// ===================================================

// =================================================================== OBJECTS
Class::Class(string V,Class*S):Sym("class",V) {			// class
	if (S) { par["super"]=S;							// set superclass ptr
	env[val] = this; }									// register constructor 
}
Class* cls = new Class("class");
Sym* Class::inher(Sym*o) { return new Class(o->str()->val,this); }
Object::Object(Class*C,Sym*V):Sym(C->str()->val,V->str()->val) { 
	par["class"]=C; val=V; }
Sym* Class::at(Sym*o) { return new Object(this,o); }

// ==================================================================== FILEIO

// ======================================================= directory
Sym* dir(Sym*o) { return new Dir(o); }
Sym* Dir::add(Sym*o) {
	o->partag(Wr); o->partag(this); push(o);
	assert(o->tag=="file");
	assert(dynamic_cast<File*>(o)->fh=fopen((val+'/'+o->val).c_str(),"w"));
	return o; }
// ===================================================

// ======================================================= file
File::File(Sym*o):Sym("file",o->val) {}
File::~File() { if (fh) fclose(fh); }
Sym* file(Sym*o) { return new File(o); }

Sym* File::ins(Sym*o) {
	push(o->str());
	if (fh) fprintf(fh,"%s",o->str()->val.c_str());
	return this; }

// ======================================================================= GUI
Sym* message(Sym*o)	{ return new Message(o); }
Window::Window(Sym*o):Sym("window",o->val) {}
Sym* window(Sym*o)	{ return new Window(o); }

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> env;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- metainfo constants
	env["OS"]		= new Str(OS);					// host OS
	env["MODULE"]	= new Str(MODULE);				// module name (CFLAGS -DMODULE)
	env["TITLE"]	= new Str(TITLE);				// module title
	env["ABOUT"]	= new Str(ABOUT);				// short module description
	env["AUTHOR"]	= new Str(AUTHOR);				// author (c)
	env["LICENSE"]	= new Str(LICENSE);				// license
	env["GITHUB"]	= new Str(GITHUB);				// github home
	env["AUTOGEN"]	= new Str(AUTOGEN);				// autogenerated code signature
	env["LOGO"]		= new Str(LOGO);				// bI logo (w/o file extension)
	env["COLOR"]	= new Str(COLOR);				// editor color theme
	// ----------------------------------------------- specials
	env["nil"]		= nil;
	env["R"]		= Rd;
	env["W"]		= Wr;
	// ----------------------------------------------- string
	env["upcase"]	= new Fn("upcase",upcase);
	// ----------------------------------------------- objects
	env["class"]	= cls;
	// ----------------------------------------------- fileio
	env["dir"]		= new Fn("dir",dir);
	env["file"]		= new Fn("file",file);
	// ----------------------------------------------- GUI
	env["message"]	= new Fn("message",message);
	env["window"]	= new Fn("window",window);
}

