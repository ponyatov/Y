#include "dura.hpp"

biObject::biObject(string T, string V)	{ tag=T; value=V; }

string biObject::pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string biObject::tagval()	{ return "<"+tag+":"+value+">"; }

string biObject::dump(int depth) {
	if (depth)	return "\n"+pad(depth)+tagval();
	else		return tagval();
}

biObject* biObject::eval()		{ return this; }

map<string,biObject*> env;

void env_init() {
	#ifdef __MINGW32__
		env["EXE"] = new biObject("const",".exe");
	#else
		env["EXE"] = new biObject("const","");
	#endif
	env["AUTHOR"] = new biObject(".author",AUTHOR);
	env["LICENSE"] = new biObject(".license",LICENSE);
	env["GITHUB"] = new biObject(".github",GITHUB);
}

biModule::biModule(string V):biObject(".module",V) {
	mkdir(value.c_str());
	env["MODULE"]=this;
}

biModule *bi_module = new biModule("tmp");

biFile::biFile(string V):biObject(".file",V) {
	assert( fh = fopen((bi_module->value+"/"+V).c_str(),"w") );
}

biFile::~biFile()	{ fclose(fh); }

void biFile::W(char      c)	{ fprintf(fh,"%c",c); }
void biFile::W(string*   s)	{ fprintf(fh,"%s",s->c_str()); }
void biFile::W(string    s)	{ fprintf(fh,"%s",s.c_str()); }
void biFile::W(biObject* s) { fprintf(fh,"%s",s->dump().c_str()); }

biFile *bi_file = NULL;

biDirective::biDirective(string V):biObject("",V) {
	while (value.size() && ( value[0]!=' ' && value[0]!='\t'))
		{ tag+=value[0]; value.erase(0,1); }
	while (value.size() && ( value[0]==' ' || value[0]=='\t'))
		value.erase(0,1);
	if (tag==".title") env["TITLE"]= this;
	if (tag==".file") {
		if (bi_file) delete bi_file; bi_file = new biFile(value);
	}
}

void W(char      c,bool to_file)	{ cout << c ; 
	if (to_file&&bi_file) bi_file->W(c); }
void W(string*   s,bool to_file)	{ cout << *s ; 
	if (to_file&&bi_file) bi_file->W(s); }
void W(string    s,bool to_file)	{ cout <<  s ; 
	if (to_file&&bi_file) bi_file->W(s); }
void W(biObject* s,bool to_file) 	{ cout << s->dump();
	if (to_file&&bi_file) bi_file->W(s); }

void yyerror(string err) {
	cerr << "\n\n" << err << " # " << yylineno << " : " << yytext << "\n";
	exit(-1);
}

int main() { env_init(); return yyparse(); }

