/* DO NOT EDIT: this file was autogened by bI/sym language system */
/***** cpp.sym *****/
#include "sym.hpp"

// \\ generic AST-like dynamic object

object::object(string T, string V)	{ tag=T; value=V; }
string object::tagval()	{ return "<"+tag+":"+value+">"; }
string object::pad(int n) { string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string object::dump(int depth) {
	string S="\n"+pad(depth)+tagval();
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
	if (tag=="list" or tag=="block") {
		value="";
		for (vector<object*>::iterator it = nest.begin();
			it != nest.end(); it++)
			value += (*it)->value;
	}
	if (tag=="fn") {
		if (value=="class") {
			tag=value; value=nest[0]->value;
			file *cpp = new file(value+".cpp");
			file *hpp = new file(value+".hpp");
			for (vector<object*>::iterator it = nest.begin();
				it != nest.end(); it++)
				hpp->W((*it)->value);
			delete cpp,hpp;
			value=tagval();
		}
		if (sysfn[value]) {
			if (nest.size()==0) value = sysfn[value](new object("",""))->dump();
		}
	}
	return this;
}

// // generic AST-like dynamic object

// \\ global environment: objects registry

map<string,object*> env;
void env_init() {
	env["AUTHOR"] = new object("str",AUTHOR);
	env["LICENSE"] = new object("str",LICENSE);
	env["GITHUB"] = new object("str",GITHUB);
	env["AUTOGEN"] = new object("str",AUTOGEN);
	env["FILES"] = new object("list","");
}

// // global environment: objects registry

// \\ system functions

map<string,fn> sysfn;		

void fn_init() {
	sysfn["date"]=fn_date;
}

object* fn_date(object* o) {
	return new object("date","so:me:date");
}

// // system functions

// \\ .module

directive::directive(string V):object("",V) {
	while (value.size() && ( value[0] != ' ' && value[0] != '\t' ) ) {
		tag += value[0]; value.erase(0,1);
	}
	while (value.size() && ( value[0] == ' ' || value[0] == '\t' ) ) {
		value.erase(0,1);
	}
	// directive dependent
	if (tag == ".module") {
		if (curr_module) delete curr_module; curr_module = new module(value);
	}
	if (tag == ".file") {
		file::curr_close(); curr_file = new file(value);
		env["FILES"]->join(new object("str",value));
	}
	if (tag == ".eof")		if (curr_file) { delete curr_file; curr_file=NULL; }
	if (tag == ".title")   env["TITLE"] = this;
	if (tag == ".author")  env["AUTHOR"] = this;
	if (tag == ".license") env["LICENSE"] = this;
	if (tag == ".github")  env["GITHUB"] = this;
}

module::module(string V):object("module",V) { 
#ifdef __MINGW32__
	mkdir(V.c_str());
#else
	mkdir(V.c_str(),0700);
#endif
	env["MODULE"] = this;
}
module *curr_module = new module("tmp");

// // .module

// \\ output .file

file::file(string V): object("file",V) {
	if (curr_file) delete curr_file;
	assert( fh = fopen((curr_module->value+"/"+value).c_str(),"w") );
}
file::~file() {
	if (fh) fclose(fh);
}
void file::W(char    c)	{ fprintf(fh,"%c",c); }
void file::W(string  s)	{ fprintf(fh,"%s",s.c_str()); }
void file::W(string* s)	{ fprintf(fh,"%s",s->c_str()); }
void file::W(object* o)	{ fprintf(fh,"%s",o->dump().c_str()); }
void file::curr_close()	{ if (curr_file) { delete curr_file; curr_file=NULL; }}
file *curr_file = NULL;

// // output .file

// \\ writers

void W(char    c,bool tofile)	{ cout <<  c;
	if (tofile && curr_file) curr_file->W(c); }
void W(string  s,bool tofile)	{ cout <<  s;
	if (tofile && curr_file) curr_file->W(s); }
void W(string *s,bool tofile)	{ cout << *s;
	if (tofile && curr_file) curr_file->W(s); }
void W(object *o,bool tofile)	{ cout << o->dump();
	if (tofile && curr_file) curr_file->W(o); }

// // writers

// syntax error processing function
void yyerror(string msg) {
	cout << "\n" << msg << " " << yylineno << ":[" << yytext << "]\n\n";
	cerr << "\n" << msg << " " << yylineno << ":[" << yytext << "]\n\n";
	exit(-1);
}

// \\ _main() entry point

int main(int argc, char *argv[]) {
	env_init();
	fn_init();
	return yyparse();
}

// // _main() entry point
/***** cpp.sym *****/
