/* DO NOT EDIT: this file was autogened by bI language system */
#include "sym.hpp"

object::object(string T, string V)	{ tag=T; value=V; }
string object::tagval()	{ return "<"+tag+":"+value+">"; }
string object::pad(int n) { string S; for (int i=0;i<n;i++) S+="t"; return S; }
string object::dump(int depth) {
	string S; if (depth) S+="n"+pad(depth); S+=tagval();
	for (vector<object*>::iterator it = nest.begin();
			it != nest.end(); it++)
		S+= (*it)->dump(depth+1);
	return S;
}
void object::join(object*o)	{ nest.push_back(o); }
object* object::eval()	{
	for (vector<object*>::iterator it = nest.begin();
			it != nest.end(); it++)
		(*it)=(*it)->eval();
	if (env[value]) return env[value]; 
	if (tag=="list") {
		value="";
		for (vector<object*>::iterator it = nest.begin();
			it != nest.end(); it++)
			value += (*it)->value;
	}
	return this;
}

map<string,object*> env;
void env_init() {
	env["AUTHOR"] = new object("str",AUTHOR);
	env["LICENSE"] = new object("str",LICENSE);
	env["GITHUB"] = new object("str",GITHUB);
	env["AUTOGEN"] = new object("str",AUTOGEN);
	env["FILES"] = new object("list","");
}

directive::directive(string V):object("",V) {
	while (value.size() && ( value[0] != ' ' && value[0] != 't' ) ) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && ( value[0] == ' ' || value[0] == 't' ) ) {
		value.erase(0,1);
	}
	// direective dependent
	if (tag == ".module") {
		if (curr_module) delete curr_module; curr_module = new module(value);
	}
	if (tag == ".file") {
		if (curr_file) delete curr_file; curr_file = new file(value);
		env["FILES"]->join(new object("str",value));
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

void W(char    c,bool tofile)	{ cout <<  c;
	if (tofile && curr_file) fprintf(curr_file->fh,"%c",c); }
void W(string  s,bool tofile)	{ cout <<  s;
	if (tofile && curr_file) fprintf(curr_file->fh,"%s",s.c_str()); }
void W(string *s,bool tofile)	{ cout << *s;
	if (tofile && curr_file) fprintf(curr_file->fh,"%s",s->c_str()); }
void W(object *o,bool tofile)	{ cout << o->dump();
	if (tofile && curr_file) fprintf(curr_file->fh,"%s",o->dump().c_str()); }

void yyerror(string msg) {
	cout << "n" << msg << " " << yylineno << ":[" << yytext << "]nn";
	cerr << "n" << msg << " " << yylineno << ":[" << yytext << "]nn";
	exit(-1);
}

int main()	{ env_init(); return yyparse(); }

