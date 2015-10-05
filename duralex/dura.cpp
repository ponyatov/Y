#include "dura.hpp"

biObject::biObject(string T, string V)	{ tag=T; value=V; }

string biObject::pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }
string biObject::tagval()	{ return "<"+tag+":"+value+">"; }

string biObject::dump(int depth) {
	string S="\n"+pad(depth)+tagval();
	for (vector<biObject*>::iterator it = nest.begin(); it != nest.end(); it++)
		S += (*it)->dump(depth+1);
	return S;
}

int biObject::size()		{ return nest.size(); }

biObject* biObject::eval() {
//	if (tag=="list" && nest.size()==1) return nest[0];
	if (tag=="fn" && value=="class") {
		return new biObject("class",nest[0]->value);
	}
	if (tag=="=" && nest.size()==2) {
		env[nest[0]->value] = nest[1]; return nest[1];
	}
	if (tag=="/") {
		if (
			nest[0]->tag=="list" && 
//			nest[0]->size()>1 && 
			nest[1]->tag=="str") {
			// punctuate list by string (insert str between list items)
			string S; string B = nest[1]->value;
			for (
				vector<biObject*>::iterator it = nest[0]->nest.begin();
				it != nest[0]->nest.end();
				it++ )
				S += (*it)->eval()->value + B;
			// drop last 
			S.erase(S.size()-B.size(),B.size());
			return new biObject("str",S);
		}
	}
	if (tag=="list") {
		value="";
		for (
			vector<biObject*>::iterator it = nest.begin();
			it != nest.end();
			it++ )
			value += (*it)->eval()->value;
		return this;
	}
	return this; 
}

void biObject::join(biObject* o)	{ nest.push_back(o); }

map<string,biObject*> env;

void env_init() {
	#ifdef __MINGW32__
		env["EXE"] = new biObject("const",".exe");
	#else
		env["EXE"] = new biObject("const",".elf");
	#endif
	env["AUTHOR"] = new biObject(".author",AUTHOR);
	env["LICENSE"] = new biObject(".license",LICENSE);
	env["GITHUB"] = new biObject(".github",GITHUB);
	// internal functions
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
	if (tag==".title")  env["TITLE"] = this;
	if (tag==".github") env["GITHUB"]= this;
	if (tag==".author") env["AUTHOR"]= this;
	if (tag==".file") {
		if (bi_file) delete bi_file; bi_file = new biFile(value); }
	if (tag==".eof") {
		if (bi_file) delete bi_file; bi_file=NULL; }
	if (tag==".module") {
		if (bi_module) delete bi_module; 
		bi_module = new biModule(value); }
}

biString::biString(string V): biObject("str",V) {
	value.erase(0,1);
	value.erase(value.size()-1,1);
};
int biString::size() { return value.size(); }

void W(char      c,bool to_file)	{ cout << c ; 
	if (to_file&&bi_file) bi_file->W(c); }
void W(string*   s,bool to_file)	{ cout << *s ; 
	if (to_file&&bi_file) bi_file->W(s); }
void W(string    s,bool to_file)	{ cout << s ; 
	if (to_file&&bi_file) bi_file->W(s); }
void W(biObject* s,bool to_file) 	{ cout << s->dump();
	if (to_file&&bi_file) bi_file->W(s); }

void yyerror(string err) {
	cerr << "\n\n" << err << " # " << yylineno << " : " << yytext << "\n";
	exit(-1);
}

int main() { env_init(); return yyparse(); }

