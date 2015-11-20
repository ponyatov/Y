#include "hpp.hpp"

#define YYERR "\n\n"<<msg<<" #"<<yylineno<<" ["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }	// error()
int main() { env_init(); return yyparse(); }						// main()

// writers
void W(char    c,bool to_file)	{ cout << c ;					// single char
	if (to_file&&curr_file) fprintf(curr_file->fh,"%c",c); }
void W(string  s,bool to_file)	{ cout <<  s;					// string
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s.c_str()); }
void W(string *s,bool to_file)	{ cout << *s;					// string ptr
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s->c_str()); }
void W(sym    *o,bool to_file)	{ cout << o->dump();			// symb.object
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",o->dump().c_str()); }

// symbolic object realization

sym::sym(string T,string V)	{ tag=T; value=V; }			// symbol constructor
void sym::join(sym*o)	{ nest.push_back(o); }			// add nested object

string sym::pad(int n) {string S; for (int i=0;i<n;i++) S+="\t"; return S;}
string sym::tagval()	{ return "<"+tag+":"+value+">"; }
string sym::dump(int depth) {							// dump symbol object
	string S = "\n"+pad(depth)+tagval();				// header
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		S += (*it)->dump(depth+1);						// recurse with pad++
	return S;
}

sym* sym::eval()	{									// object evaluator
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	sym *E = env[value];								// look up in env[]
	if (E) {
		if (nest.size())
			for (auto it=nest.begin(); it!=nest.end(); it++)	// copy nested
				E->join(*it);
		return E;
	}
//	if (tag=="list" && nest.size() && nest[0]->tag=="fn")	// function apply
//		return (Fn*)nest[0]->fn(this);
//	else return this;
	return this;										// default return
}

map<string,sym*> env;									// global env[]ironment
void env_init() {
	// meta constants
	env["AUTHOR"]=new sym("author",AUTHOR);
	env["LOGO"]=new sym("logo",LOGO);
	env["LISP"]=new sym("lisp",LISP);
	env["LICENSE"]=new sym("license",LICENSE);
	env["GITHUB"]=new sym("github",GITHUB);
	env["AUTOGEN"]=new sym("autogen",AUTOGEN);
	env["bICONFIG"]=new sym("bIconfig",bICONFIG);
	env["MODULE"]=curr_module;
	env["FILES"]=new Str("");
	env["CFILES"]=new Str("cpp.cpp");
	env["HFILES"]=new Str("hpp.hpp");
	env["COLOR"]=new Str("peachpuff");
	env["ABOUT"]=new Str("");
	// special symbols
	env["%T"]=new sym("true","%T");
	env["%F"]=new sym("false","%F");
	env["%N"]=new sym("nil","%N");
	env["%E"]=new sym("error","%E");
	env["%%"]=new sym("default","%%");
	// low-level fu()nctions
	env["+"]=new Fn("add",add);
//	env["print"]=new Fn("print",print);
	env["exit"]=new Fn("exit",exit);
}

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\t'&&value[0]!=' ')) {
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\t'||value[0]==' '))
		                 value.erase(0,1);
	// inline eval
	if (tag==".file") { 
		env["FILES"]->value+=value+" ";
		value = curr_module->value+"/"+value;
		if (curr_file) delete curr_file; curr_file=new File(value); }
	if (tag==".eof") {
		if (curr_file) delete curr_file; curr_file=NULL; }
	if (tag==".inc") incFile(this);
	if (tag==".title")	env["TITLE"]	=new sym("title",value);
	if (tag==".about")	env["ABOUT"]	=new sym("about",value);
	if (tag==".author")	env["AUTHOR"]	=new sym("author",value);
	if (tag==".license")env["LICENSE"]	=new sym("license",value);
	if (tag==".github")	env["GUTHUB"]	=new sym("github",value);
	if (tag==".color")	env["COLOR"]	=new Str(value);
}

Module::Module(string V):sym("module",V)	{
	#ifdef __MINGW32__
	mkdir(V.c_str());
	#else
	mkdir(V.c_str(),0700);
	#endif
}

File::File(string V):sym("file",V) { assert(fh=fopen(V.c_str(),"w"));}
File::~File() { fclose(fh); }

Module *curr_module = new Module("next");
File *curr_file = NULL;

Int::Int(string V):sym("int",V)	{}
sym* Int::eval() {
	ostringstream os; os << atoll(value.c_str()); value=os.str();
	return this; }

Num::Num(string V):sym("num",V) {}
sym* Num::eval() {
	ostringstream os; os << strtold(value.c_str(),NULL); value=os.str();
	return this; }

Str::Str(string V):sym("str",V)	{}

List::List():sym("[","]") {}
Vector::Vector():sym("","") {}
Pair::Pair(sym*A,sym*B):sym(A->value,B->value) {}
Dot::Dot():sym("dot",".") {}
Op::Op(string V):sym("op",V) {}

Fn::Fn(string V, FN F):sym("fn",V)	{ fn=F; }

sym* add(sym*o)	{
	if (o->nest.size()>=3) {
		sym* S=o->nest[1];
		for (auto it=o->nest.begin()+2; it!=o->nest.end(); it++)
			S = S->add(*it);
		return S;
	} else return env["%E"];
}

sym* sym::add(sym*o) { sym* L = new List(); L->join(this); L->join(o); return L; }
sym* List::add(sym*o)	{ join(o); return this; }
sym* Int::add(sym*o)	{ assert(o->tag=="int");
	ostringstream os; os << atoi(value.c_str()) + atoi(o->value.c_str());
	value=os.str(); return this; }

sym* print(sym*o) { sym* T = new Str(o->nest[1]->value); W(T->value); return T; }
sym* exit(sym*o)  { return new sym("exit","0"); }
