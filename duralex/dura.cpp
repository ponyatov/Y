#include "dura.hpp"

biObject::biObject(string T, string V)	{ tag=T; value=V; }

string pad(int n)	{ string S; for (int i=0;i<n;i++) S+="\t"; return S; }

string biObject::dump(int depth) {
	string S = "\n"+pad(depth)+"<"+tag+":"+value+">";
	return S;
}

biModule::biModule(string V):biObject("module",V) {
	mkdir(value.c_str());
}

biModule *bi_module = new biModule("tmp");

biFile::biFile(string V):biObject("file",V) {
	assert( fh = fopen((bi_module->value+"/"+V).c_str(),"w") );
}

biFile::~biFile()	{ fclose(fh); }

void biFile::W(string*   s)	{ fprintf(fh,"%s",s->c_str()); }
void biFile::W(string    s)	{ fprintf(fh,"%s",s.c_str()); }
void biFile::W(biObject* s) { fprintf(fh,"%s",s->dump().c_str()); }

biFile *bi_file = NULL;

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

int main() { return yyparse(); }

