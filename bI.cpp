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

AST::AST(string *cls, string *val) {
	tag["class"]=*cls;
	tag["value"]=*val;
}

AST::AST(AST* FN, AST* A) {
	tag["class"]=FN->tag["class"];
	tag["value"]=FN->tag["value"];
	child.push_back(A);
}

AST::AST(AST* A, AST* OP, AST* B) {
	tag["class"]=OP->tag["class"];
	tag["value"]=OP->tag["value"];
	child.push_back(A);
	child.push_back(B);
}

string AST::str(int depth) {
	if (tag.size()>2||child.size()||depth>0) {
	string S = string("");
	if (depth==0) S+="\n------------------------------------------------\n";
	for (int i=0;i<depth;i++) S+="\t";
	S+="< ";
	for ( map<string,string>::iterator t=tag.begin(); t!=tag.end(); t++ )
		S+= t->first +":"+ t->second +" ";
	S+=">\n";
	for ( list<AST*>::iterator c=child.begin(); c!=child.end(); c++)
		S+= (*c)->str(depth+1);
	if (depth==0) S+="------------------------------------------------\n";
	return S;		
	} else return "<"+tag["class"]+":"+tag["value"]+">";
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

