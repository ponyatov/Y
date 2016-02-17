#include <hpp.hpp>
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
Sym::Sym(string T,string V) { tag=T; val=V; }			// <T:V>
Sym::Sym(string V):Sym("",V)	{}						// token

// ------------------------------------------------------- nest[]ed elements
void Sym::push(Sym*o) { nest.push_back(o); }

// ------------------------------------------------------- par{}ameters
void Sym::par(Sym*o) { pars[o->str()->val]=o; }

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
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) {							// dump as text
	string S = "\n"+pad(depth)+tagval();				// <T:V>
	for (auto pr=pars.begin(),e=pars.end();pr!=e;pr++)	// par{}ameters
		S+="\n"+pad(depth+1)+"__ "+pr->first+pr->second->dump(depth+2);
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		S+=(*it)->dump(depth+1);
	return S; }

// ------------------------------------------------------- evaluation

Sym* Sym::eval() {
	auto E = glob.find(val);							// \ lookup in env{}
	if (E!=glob.end()) return E->second;				// /
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// recursive eval()
		(*it)=(*it)->eval();							// with objects replace
	return this; }

// ------------------------------------------------------- operators

Sym* Sym::str()			{ return new Str(val); }		// str(A)	as string

Sym* Sym::eq(Sym*o)		{ glob[val]=o; return o; }		// A = B	assignment

Sym* Sym::at(Sym*o)		{ push(o); return this; }		// A @ B	apply

Sym* Sym::add(Sym*o) { Sym* R = new Op("+");			// A + B	add
	R->push(this); R->push(o); return R; }
Sym* Sym::div(Sym*o) { Sym* R = new Op("/");			// A / B	div
	R->push(this); R->push(o); return R; }

Sym* Sym::ins(Sym*o)	{ push(o); return this; }		// A += B	insert

// ================================================================= DIRECTIVE
Directive::Directive(string V):Sym("",V) {
	while (val.size() && (val[0]!=' ' && val[0]!='\t')) {
		tag += val[0]; val.erase(0,1); }
	while (val.size() && (val[0]==' ' || val[0]=='\t')) {
		               val.erase(0,1); }				}
string Directive::tagval() { return tagstr(); }
Sym* Directive::eval() { return this; }
//	if (tag==".end") { W(this); W("\n"); exit(0); }

// =================================================================== SCALARS

Scalar::Scalar(string T,string V):Sym(T,V) {};
Sym* Scalar::eval() { return this; }					// block env{} lookup

// ======================================================= string
Str::Str(string V):Scalar("str",V) {}
string Str::tagval() { return tagstr(); }
Sym* Str::eq(Sym*o) { yyerror("immutable"); }
Sym* Str::add(Sym*o) { return new Str(val+o->str()->val); }
Sym* Str::upcase(Sym*o) {								// to UPCASE
	string S = o->str()->val;
	transform(S.begin(),S.end(),S.begin(),::toupper);
	return new Str(S); }

// ================================================================ COMPOSITES

// ======================================================= co,ns (Lisp-like)
Cons::Cons(Sym*A,Sym*B):Sym("","") { push(A); push(B); }

// ======================================================= [list]

List::List():Sym("[","]") {}

Sym* List::str() { string S;							// concatenate elements
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

// =============================================================== FUNCTIONALS

// ======================================================= operator
Op::Op(string V):Sym("op",V) {}
Sym* Op::copy() { Sym* R = new Op(val);
	for (auto it=nest.begin(),e=nest.end();it!=e;it++) R->push(*it);
	return R; }
Sym* Op::eval() {
	if (val=="~") return nest[0];						// ~A	quote
	if (val=="%") return (nest[0]->eval())->member(nest[1]);// A % B	member
	Sym::eval();										// nest[]ed evaluate
	if (val==":") return nest[0]->inher(nest[1]);		// A : B	inheritance
	if (val=="=") return nest[0]->eq(nest[1]);			// A = B	assign
	if (val=="@") return nest[0]->at(nest[1]);			// A @ B	apply
	if (val=="+") return nest[0]->add(nest[1]);			// A + B	add
	if (val=="/") return nest[0]->div(nest[1]);			// A / B	divide
	if (val=="+=") return nest[0]->ins(nest[1]);		// A += B	insert
	return this; }

// ======================================================= internal function
Fn::Fn(string V,FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }					// apply function

// ======================================================= {la:mbda}
Lambda::Lambda():Sym("^","^") {}
Sym* Lambda::eval() { return this; }

// ------------------------------------------------------ lambda via rewriting
// f**ken magic: apply by rewrite, not apply by eval in environment
// WARNING: RECURSION NOT APPLICABLE (???)

Sym* Sym::copy() { Sym*C = new Sym(tag,val);			// copy
	for (auto pr=pars.begin(),e=pars.end();pr!=e;pr++)	// par{}ameters
		C->pars[pr->first]=pr->second;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)	// nest[]ed
		C->push((*it)->copy());
	return C; }

bool Sym::match(Sym*o) { return o->str()->val==val; }	// match

Sym* Sym::replace(Sym*A,Sym*B) {						// replace
	if (match(A)) return B;
	for (auto pr=pars.begin(),e=pars.end();pr!=e;pr++)
		pars[pr->first]= pr->second->replace(A,B);
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it) = (*it)->replace(A,B);
	return this; }

Sym* Lambda::at(Sym*o) {								// lambda apply
	Sym* R = copy()->replace(pars.begin()->second,o);	// via rewrite
	if (R->nest.size()!=1) yyerror("multibody lambda:"+R->dump());
	else return (R->nest[0])->eval(); } // with eval
//	else return (R->nest[0])        ; } // as symbolic expression

// =================================================================== OBJECTS

Sym* Sym::inher(Sym*o) {
	Sym*O=new Sym(val,o->val); O->pars["super"]=this; return O; }
Sym* Sym::member(Sym*o) {
	pars[o->nest[0]->str()->val]= o->nest[1]; return this; }

// ==================================================================== FILEIO

// ======================================================= file
File::File(Sym*o):Sym("file",o->val) {}
Sym* File::file(Sym*o) { return new File(o); }
File::~File() { if (fh) fclose(fh); }
Sym* File::eq(Sym*o) { yyerror(tagval()+"="+o->tagval()); }

// ====================================================== GLOBAL ENV{}IRONMENT
map<string,Sym*> glob;
void env_init() {									// init env{} on startup
	// ----------------------------------------------- metainfo constants
	glob["MODULE"]		= new Str(MODULE);			// module name
	glob["OS"]			= new Str(OS);				// target os
	glob["EXE"]			= new Str(EXE);				// executable file suffix
	#ifdef HAVE_META
	#endif
	// ----------------------------------------------- string
	glob["upcase"]		= new Fn("upcase",Str::upcase);
	// ----------------------------------------------- fileio
	glob["file"]		= new Fn("fn",File::file);
}
