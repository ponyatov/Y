#include "bI.hpp"

void yyerror(char *msg) { 
	cerr << "\n\nerror #"<<yylineno<<" : "<<msg<<" ["<<yytext<<"]\n\n"; 
	exit(-1);
}

// object

biObject::biObject(string *_name) { name = _name; }

// file

biFile *bi_file = NULL;

biFile::biFile(string *name):biObject(name) {
	fh=fopen((*bi_module->name+"/"+*name).c_str(),"w");
}

biFile::~biFile() {
	fclose(fh);
}

void biFile::W(char c)		{ if (fh) fputc(c,fh); }
void biFile::W(string *s)	{ if (fh) fprintf(fh,"%s",s->c_str()); }
void biFile::W(string s)	{ if (fh) fprintf(fh,"%s",s.c_str()); }

// module

biModule *bi_module = new biModule(new string("next"));

biModule::biModule(string *name):biObject(name) {
	#ifdef __linux__
	mkdir(name->c_str(),0744);
	#endif // __linux__
	#ifdef __MINGW32__
	mkdir(name->c_str());
	#endif // __MINGW32__
}

// AST

AST::AST() {}

AST::AST(char *cls, char *val) {
	tag["class"]=cls;
	tag["value"]=val;
}

string AST::str(int depth) {
	string S = string("");
	for (int i=0;i<depth;i++) S+="\t";
	S+="< ";
	for ( map<string,string>::iterator t=tag.begin(); t!=tag.end(); t++ )
		S+= t->first +":"+ t->second +" ";
	S+=">\n";
	return S;		
}

void W(char c,bool log_only) { 
	cout<<c; 
	if (!log_only) if (bi_file) bi_file->W(c); 
}

void W(string *s, bool log_only) {
	cout<<s;
	if (!log_only) if (bi_file) bi_file->W(s);
}

void W(string s, bool log_only) {
	cout<<s;
	if (!log_only) if (bi_file) bi_file->W(s);
}

int main(int argc, char *argv[]) {
	return yyparse();
}

