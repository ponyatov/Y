#include "hpp.hpp"

#define YYERR "\n\n"<<msg<<" #"<<yylineno<<" ["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(char    c,bool to_file)	{ cout << c ;
	if (to_file&&curr_file) fprintf(curr_file->fh,"%c",c); }
void W(string  s,bool to_file)	{ cout <<  s;
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s.c_str()); }
void W(string *s,bool to_file)	{ cout << *s;
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",s->c_str()); }
void W(sym    *o,bool to_file)	{ cout << o->dump();
	if (to_file&&curr_file) fprintf(curr_file->fh,"%s",o->dump().c_str()); }

sym::sym(string T,string V)	{ tag=T; value=V; }
void sym::join(sym*o)	{ nest.push_back(o); }
string sym::pad(int n) {string S; for (int i=0;i<n;i++) S+="\t"; return S;}
string sym::tagval()	{ return "<"+tag+":"+value+">"; }

string sym::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	for (auto it=nest.begin(); it!=nest.end(); it++)
		S += (*it)->dump(depth+1);
	return S;
}

sym* sym::eval()	{
	for (auto it=nest.begin(); it!=nest.end(); it++)
		(*it) = (*it)->eval();
	if (env[value]) return env[value];
	if (tag=="list" && nest.size() && nest[0]->tag=="fn")	// apply
		return (Fn*)nest[0]->fn(this);
	else return this;
}

map<string,sym*> env;
void env_init() {
	// meta constants
	env["AUTHOR"]=new sym("author",AUTHOR);
	env["LOGO"]=new sym("logo",LOGO);
	env["LISP"]=new sym("lisp",LISP);
	env["LICENSE"]=new sym("license",LICENSE);
	env["GITHUB"]=new sym("github",GITHUB);
	env["AUTOGEN"]=new sym("autogen",AUTOGEN);
	env["MODULE"]=curr_module;
	// special symbols
	env["%T"]=new sym("true","%T");
	env["%F"]=new sym("false","%F");
	env["%N"]=new sym("nil","%N");
	env["%E"]=new sym("error","%E");
	// low-level fu()nctions
	env["+"]=new Fn("add",add);
	env["print"]=new Fn("print",print);
	env["exit"]=new Fn("exit",exit);
}

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\t'&&value[0]!=' ')) {
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\t'||value[0]==' '))
		                 value.erase(0,1);
	// inline eval
	if (tag==".file") { value = curr_module->value+"/"+value;
		if (curr_file) delete curr_file; curr_file=new File(value); }
	if (tag==".eof") {
		if (curr_file) delete curr_file; curr_file=NULL; }
	if (tag==".inc") incFile(this);
	if (tag==".title")	env["TITLE"]	=new sym("title",value);
	if (tag==".about")	env["ABOUT"]	=new sym("about",value);
	if (tag==".author")	env["AUTHOR"]	=new sym("author",value);
	if (tag==".license")env["LICENSE"]	=new sym("license",value);
	if (tag==".github")	env["GUTHUB"]	=new sym("github",value);
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
	char S[0x100]; sprintf(S,"%i",atol(value.c_str())); value=S;
	return this; }

Num::Num(string V):sym("num",V) {}
sym* Num::eval() {
	char S[0x100]; sprintf(S,"%e",atof(value.c_str())); value=S;
	return this; }

Str::Str(string V):sym("str",V)	{}

List::List():sym("list","[]") {}
Op::Op(string V):sym("op",V) {}

Fn::Fn(string V, FN F):sym("fn",V)	{ fn=F; }

sym* add(sym*o)	{
	if (o->nest.size()>=3) {
	sym* S=o->nest[1];
	for (auto it=o->nest.begin()+2; it!=o->nest.end(); it++)
		S = S->add(*it);
	return S; } else return env["%E"]; }

sym* sym::add(sym*o) { sym* L = new List(); L->join(this); L->join(o); return L; }
sym* List::add(sym*o)	{ join(o); return this; }
sym* Int::add(sym*o)	{ assert(o->tag=="int");
	ostringstream os; os << atoi(value.c_str()) + atoi(o->value.c_str());
	value=os.str(); return this; }

sym* print(sym*o) { sym* T = new Str(o->nest[1]->value); W(T->value); return T; }
sym* exit(sym*o)  { return new sym("exit","0"); }
