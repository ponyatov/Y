/***** DO NOT EDIT: this file was autogened by bI *****/
#include "hpp.hpp"

// main .cpp part

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

// generic symbolic object

sym::sym(string T,string V)	{ tag=T; value=V; }			// symbol constructor
void sym::join(sym*o)		{ nest.push_back(o); }		// add nested object

string sym::pad(int n)	{string S; for (int i=0;i<n;i++) S+="\t"; return S;}
string sym::tagval()	{ return "<"+tag+":"+value+">"; }
string sym::dump(int depth) {							// dump symbol object
	string S = "\n"+pad(depth)+tagval();				// header
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		S += (*it)->dump(depth+1);						// recurse with pad++
	return S;
}

string sym::hpp(int depth)	{
	string S = pad(depth)+"//"+tagval()+"\n";
	if (tag=="class") S="struct "+value+" {\n";
	for (auto it=nest.begin();it!=nest.end();it++)
		S+=(*it)->hpp(depth+1);
	if (tag=="class") return S+"};\n";
	return S;
}
string sym::cpp(int depth)	{ return pad(depth)+"//C++: "+tagval(); }

sym* sym::eval()	{									// object evaluator
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	sym *ET = env[tag];									// look up tag in env[]
	sym *EV = env[value];								// look up val in env[]
//	sym *RR;											// resulting object
	if (ET) {											// eval RR class tag
		if (ET->tag=="fn") return ET->fn(this);				// process class tag
	} //else RR->tag=tag;									// copy this tag
	if (EV) {
		if (nest.size())
			for (auto it=nest.begin(); it!=nest.end(); it++)	// copy nested
				EV->join(*it);
		return EV;
	} //else RR->value=value;								// copy this value
	if (tag=="["&&value=="]"								// function apply
	&& nest.size() && nest[0]->tag=="fn")	
		return (Fn*)nest[0]->fn(this);
//	else return this;
	return this;											// default return
}

map<string,sym*> env;									// global env[]ironment
void env_init() {
	// meta constants
	env["LOGO"]=new sym("logo",LOGO);
	env["LISP"]=new sym("lisp",LISP);
	env["AUTHOR"]=new sym("author",AUTHOR);
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
	env["env"]=new Fn("env",setenv);				// env[] update functions
	env["class"]=new Fn("class",defclass);			// class definition
//	env["+"]=new Fn("add",add);
//	env["print"]=new Fn("print",print);
	env["exit"]=new Fn("exit",exit);
	// C++ generator functions
	env["hpp"]=new Fn("hpp",hpp);
//	env["ctype"]=new sym("fn","ctype");
	env["str"]=new Fn("str",str);
//	env["sym"]=new sym("alias","Symbol");
}

// dynamic symbolic object subsystem

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\t'&&value[0]!=' ')) {	// shift val->tag
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\t'||value[0]==' ')) {	// shift spaces
		                 value.erase(0,1); }
	// file-specific operations
	if (tag==".inc") incFile(this);							// .include files
	if (tag==".file") {										// create new .file
		env["FILES"]->value+=value+" ";						// FILES+= filename
		value = curr_module->value+"/"+value;			// full name with module
		if (curr_file) delete curr_file; curr_file=new File(value,"w"); }
	if (tag==".eof") {										// end .file
		if (curr_file) delete curr_file; curr_file=NULL; }
												// .module metainfo directives
	if (tag==".title")	env["TITLE"]	=new sym("title",value);
	if (tag==".about")	env["ABOUT"]	=new sym("about",value);
	if (tag==".author")	env["AUTHOR"]	=new sym("author",value);
	if (tag==".license")env["LICENSE"]	=new sym("license",value);
	if (tag==".github")	env["GITHUB"]	=new sym("github",value);
	if (tag==".color")	env["COLOR"]	=new Str(value);
}

Module::Module(string V):sym("module",V) {					// define .module
	#ifdef __MINGW32__
		mkdir(V.c_str());									// create win32 dir
	#else
		mkdir(V.c_str(),0700);								// create POSIX dir
	#endif
}
Module *curr_module = new Module("next");	// default module on system start

File::File(string V,string M):sym("file",V) {		// create file [Mode="r/w"]
	assert(fh=fopen(V.c_str(),M.c_str()));}
File::~File() { fclose(fh); }						// close file
File *curr_file = NULL;								// current out file for W()

Int::Int(string V):sym("int",V)	{}					// integer number
sym* Int::eval() {
	ostringstream os; os << atoll(value.c_str()); value=os.str();
	return this; }

Num::Num(string V):sym("num",V) {}					// float point number
sym* Num::eval() {
	ostringstream os; os << strtold(value.c_str(),NULL); value=os.str();
	return this; }

Str::Str(string V):sym("str",V)	{}					// string
string Str::hpp()	{ return "std::string\t"+value+"\n"; }

													// aggregate data types
List::List():sym("[","]") {}						// [list]
Vector::Vector():sym("","") {}						// <vector>
Pair::Pair(sym*A,sym*B):sym(A->value,B->value) {}	// pa:ir

Dot::Dot():sym("dot",".") {}
Op::Op(string V):sym("op",V) {}

Fn::Fn(string V, FN F):sym("fn",V)	{ fn=F; }


/*
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
*/

sym* print(sym*o) { sym* T = new Str(o->nest[1]->value); W(T->value); return T; }
sym* exit(sym*o)  { return new sym("exit","0"); }

sym* setenv(sym*o) {
	return env["%%"];
}
sym* defclass(sym*o) { env[o->value]=o; return o; }
sym* hpp(sym*o)		{
	sym *S=new Str("");
	for (auto it=o->nest.begin()+1;it!=o->nest.end();it++)
		S->value += (*it)->hpp();
	return S;
}
sym* cpp(sym*o)		{ return new Str(o->cpp()); }
sym* str(sym*o)		{ return new Str(o->value); }
