/* DO NOT EDIT: this file was autogened by bI language system */
/* <module:sym> */
#include "sym.hpp"

// \\ Object
biObject::biObject(string T,string V)	{ tag = T; value = V; }
string biObject::dump(int depth)		{ return "<"+tag+":"+value+">"; }

biObject* biObject::eval() {
	if ( tag == "str" ) return this;
	if ( tag == "sym" ) {
		if (!env[value]) return this;
		else return env[value];
	}
	return this;
}
// //

// \\ Environment
map<string,biObject*> env;
void env_init() {
	env["AUTHOR"]	= new biObject(".author",AUTHOR);
	env["LICENSE"]	= new biObject(".license",LICENSE);
	env["GITHUB"]	= new biObject(".github",GITHUB);
	env["FILES"]	= new biObject("list","");
	env["AUTOGEN"]	= new biObject(".autogen",AUTOGEN);
	#ifdef __MINGW32__
		env["EXE"]	= new biObject("str",".exe");
	#else
		env["EXE"]	= new biObject("str",".elf");
	#endif
}
// //

// \\ Directive
biDirective::biDirective(string V):biObject("",V) {
	// autogenerate tag & value
	while ( value.size() && (value[0] != ' ' && value[0] != '\t') )
		{ tag += value[0]; value.erase(0,1); }
	while ( value.size() && (value[0] == ' ' || value[0] == '\t') )
		{                  value.erase(0,1); }
	// process specific directive tag
	if (tag == ".module")	bi_module = new biModule(value);
	if (tag == ".file")		bi_file = new biFile(value);
	if (tag == ".eof")		if (bi_file) delete bi_file;
}
// //

// \\ Module
biModule::biModule(string V):biObject("module",V) {
	mkdir(value.c_str());
	if (bi_file) delete bi_file;
	env["MODULE"] = this;
}
biModule *bi_module = new biModule("tmp");
// //

// \\ File
biFile::biFile(string V):biObject("file",V) {
	if (bi_file) delete bi_file;
	assert ( fh = fopen((bi_module->value+"/"+value).c_str(),"w") );
	bi_file = this;
}
biFile::~biFile() 			{ fclose(fh); bi_file = NULL; }
void biFile::W(char c)		{ fprintf(fh,"%c",c); }
void biFile::W(string s)	{ fprintf(fh,"%s",s.c_str()); }
biFile *bi_file = NULL;
// //

// \\ writers
void W(char      c, bool to_file) { cout <<  c; 
	if (to_file && bi_file) bi_file->W(c); }
void W(string    s, bool to_file) { cout <<  s;
	if (to_file && bi_file) bi_file->W(s); }
void W(string   *s, bool to_file) { cout << *s;
	if (to_file && bi_file) bi_file->W(*s); }
void W(biObject *o, bool to_file) { cout << o->dump();
	if (to_file && bi_file) bi_file->W(o->dump()); }
// //

void yyerror(string msg) {
	cout << "\n\n" << msg << "#" << yylineno << ":" << yytext << "\n\n";
	cerr << "\n\n" << msg << "#" << yylineno << ":" << yytext << "\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	env_init();
	return yyparse();
}
