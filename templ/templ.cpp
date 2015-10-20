#include "templ.hpp"

object::object(string T, string V)	{ tag=T; value=V; }
string object::tagval()	{ return "<"+tag+":"+value+">"; }
string object::pad(int n) { string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string object::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	for (vector<object*>::iterator it = nest.begin();
			it != nest.end(); it++)
		S+= (*it)->dump(depth+1);
	return S;
}
void object::join(object*o)	{ nest.push_back(o); }
object* object::eval()	{
	if (env[value]) return env[value]; else return this;
}

map<string,object*> env;
void env_init() {
	env["AUTHOR"] = new object("str",AUTHOR);
	env["LICENSE"] = new object("str",LICENSE);
	env["AUTOGEN"] = new object("str",AUTOGEN);
}

directive::directive(string V):object("",V) {
	while (value.size() && ( value[0] != ' ' && value[0] != '\t' ) ) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && ( value[0] == ' ' || value[0] == '\t' ) ) {
		value.erase(0,1);
	}
	// direective dependent
	if (tag == ".module") {
		if (curr_module) delete curr_module; curr_module = new module(value);
	}
	if (tag == ".file") {
		if (curr_file) delete curr_file; curr_file = new file(value);
	}
	if (tag == ".title") env["TITLE"] = this;
}

module::module(string V):object("module",V) { 
#ifdef __MINGW32__
	mkdir(V.c_str());
#else
	#error mkdir
#endif
	env["MODULE"] = this;
}
module *curr_module = new module("tmp");

file::file(string V): object("file",V) {
	if (curr_file) delete curr_file;
	assert( fh = fopen((curr_module->value+"/"+value).c_str(),"w") );
	curr_file = this;
}
file::~file() {
	if (fh) fclose(fh);
	if (curr_file) curr_file=NULL;
}
file *curr_file = NULL;

void W(char    c)	{ cout <<  c; }
void W(string  s)	{ cout <<  s; }
void W(string *s)	{ cout << *s; }

void yyerror(string msg) {
	cout << "\n" << msg << " " << yylineno << ":[" << yytext << "]\n\n";
	cerr << "\n" << msg << " " << yylineno << ":[" << yytext << "]\n\n";
	exit(-1);
}

int main()	{ env_init(); return yyparse(); }

