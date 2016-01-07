
// generic symbolic object

void env_init() {
	// meta constants
	env["FILES"]=new Str("");
	env["CFILES"]=new Str("cpp.cpp");
	env["HFILES"]=new Str("hpp.hpp");
	env["COLOR"]=new Str("darkblue");
	env["ABOUT"]=new Str("");
	// special symbols
	env["%T"]=new sym("true","%T");
	env["%F"]=new sym("false","%F");
	env["%N"]=new sym("nil","%N");
	env["%E"]=new sym("error","%E");
	env["%%"]=new sym("default","%%");
	// functions
	env["hpp"]=new Fn("hpp",hpp);
	env["class"]=new Fn("class",classdef);
}

sym* sym::eval()	{									// object evaluator
	if (env[value]) return env[value];					// lookup in env[]
	for (auto it=nest.begin(); it!=nest.end(); it++)	// walk over nest[]ed
		(*it) = (*it)->eval();							// recurse compute
	if (env[tag]) return env[tag]->fn(this);
	if (nest.size() && nest[0]->tag=="fn")				// apply()
		return nest[0]->fn(this);
	return this;										// default as is
}

// dynamic symbolic object subsystem

Directive::Directive(string V):sym("",V) {
	while (value.size()&&(value[0]!='\t'&&value[0]!=' ')) {	// shift val->tag
		tag += value[0]; value.erase(0,1); }
	while (value.size()&&(value[0]=='\t'||value[0]==' ')) {	// shift spaces
		                 value.erase(0,1); }
	// file-specific operations
	if (tag==".inc") incFile(this);							// .include files
	if (tag==".module") Module::CurrSet(new Module(value));
	if (tag==".file") {										// create new .file
		env["FILES"]->value+=value+" ";						// FILES+= filename
		value = curr_module->value+"/"+value;			// full name with module
		if (curr_file) delete curr_file; curr_file=new File(value,"w"); }
	if (tag==".eof") File::CurrSet(NULL);					// end .file
												// .module metainfo directives
	if (tag==".title")	env["TITLE"]	=new sym("title",value);
	if (tag==".about")	env["ABOUT"]	=new sym("about",value);
	if (tag==".author")	env["AUTHOR"]	=new sym("author",value);
	if (tag==".license")env["LICENSE"]	=new sym("license",value);
	if (tag==".github")	env["GITHUB"]	=new sym("github",value);
	if (tag==".color")	env["COLOR"]	=new Str(value);
}

// file management

Module::Module(string V):sym("module",V) {					// define .module
	#ifdef __MINGW32__
		mkdir(V.c_str());									// create win32 dir
	#else
		mkdir(V.c_str(),0700);								// create POSIX dir
	#endif
	File::CurrSet(NULL);
}
void Module::CurrSet(Module*M) {
	if (curr_module) delete curr_module; curr_module=M; env["MODULE"]=M; }
Module::~Module() { File::CurrSet(NULL); }
Module *curr_module=new Module("next");			// default module on system start

File::File(string V,string M):sym("file",V) {		// create file [Mode="r/w"]
	assert(fh=fopen(V.c_str(),M.c_str()));}
void File::CurrSet(File*F) {						// reset current file
	if (curr_file) delete curr_file;				// close if opened
	curr_file=F; }									// set to selected File*
File::~File() { fclose(fh); }						// close file
File *curr_file = NULL;								// current out file for W()

// scalar data types

Int::Int(string V):sym("int",V)	{}					// integer number
sym* Int::eval() {
	ostringstream os; os << atol(value.c_str()); value=os.str();
	return this; }

Hex::Hex(string V):sym("hex",V) {}
sym* Hex::eval() { return this; }
Bin::Bin(string V):sym("bin",V) {}
sym* Bin::eval() { return this; }

Num::Num(string V):sym("num",V) {}					// float point number
sym* Num::eval() {
	ostringstream os; os << atof(value.c_str()); value=os.str();
	return this; }

Str::Str(string V):sym("str",V)	{}					// string

// aggregate data types

List::List():sym("[","]") {}						// [list]
Vector::Vector():sym("","") {}						// <vector>
Pair::Pair(sym*A,sym*B):sym(A->value,B->value) {}	// pa:ir
Block::Block():sym("{","}") {}						// {block}

// class processing

Class::Class(string V):sym("class",V) {}
sym* classdef(sym*o) {
	sym* C = new Class(o->value);							// create class
	C->fn = classdef;										// set def fn
	for (auto it=o->nest.begin();it!=o->nest.end();it++)	// copy nested
		C->join(*it);
	env[o->value]=C;										// save to env[]
	return C;}												// return as result

// functions

Fn::Fn(string V,FN F):sym("fn",V) { fn=F; }

sym* hpp(sym*o) {
	string S;
	for (auto it=o->nest.begin()+1 ; it!=o->nest.end() ; it++)
		S += (*it)->hpp();
	return new Str(S); }
