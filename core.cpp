#include "bI.hpp"

// object

biObject::biObject(const char* C) { 
	cls = new string(C);
	val = new string();
}

biObject::biObject(const char* C,const char* V) { 
	cls = new string(C);
	val = new string(V);
}

biObject::biObject(const char* C,char* V) { 
	cls = new string(C);
	val = new string(V);
}

biObject::biObject(const char* C,string* V) { 
	cls = new string(C);
	val = V;
}

string* biObject::dump()	{ return new string("<"+*cls+":"+*val+">"); }
string* biObject::eval()	{ return val; }

// string

biString::biString(char *V):biObject("str",V) {}

// pair

biPair::biPair(biObject* X,biObject* Y):biObject("pair","") {
	A=X; B=Y; 
}

string* biPair::dump()	{ return new string(*A->dump()+":"+*B->dump()); }
string* biPair::eval()	{ return new string(*A->eval()+":"+*B->eval()); }

// module

biModule::biModule(const char*m):biObject("module",m) {
	mkdir(val->c_str());
};
biModule *bi_module = new biModule("tmp");

// file

biFile::biFile(string *name,char m): biObject("file",name) {
	mode=m;
	switch (mode) {
		case 'r': assert(fh=fopen(val->c_str(),"r")); break;
		case 'w': assert(fh=fopen(val->c_str(),"w")); break;
		default: yyerror(string("file mode ")+*dump());
	}
}
biFile::~biFile() { fclose(fh); }

string* biFile::dump()	{
	ostringstream os; 
	os << "<" << *cls << ":" << *val ;
	os << ",mode:" << mode << ",open:" << (fh==NULL ? "F" : "T") << ">";
	return new string(os.str());
}

void biFile::W(string s)	{ fprintf(fh,"%s",s.c_str());	}
void biFile::W(char c)		{ fprintf(fh,"%c",c);			}

biFile *bi_file = NULL;

// tex

TEX tex("bI.tex");

string TEX::fix(string s) {
	string T;
	for ( string::iterator c=s.begin(); c!=s.end(); c++) { switch (*c) {
		case '^':
		case '[':
		case ']':
		case '<': T+="\\textless "; break;
		case '>': T+="\\textgreater "; break;
		case '\\': T+=""; break;
		case '#': T+="\\#"; break;
		case '$': T+="\\$"; break;
		case '%': T+="\\%"; break;
		default: T+=*c; break;
	}}
	return T;
}

void TEX::W(string x)		{ body+=fix(x); }
void TEX::sec(int l,string x)		{ 
	switch (l) {
		case +1: body+="\\section{"+fix(x)+"}\n"; break;
		case -1: body+="\\subsubsection{"+fix(x)+"}\n"; break;
		default: body+="\\subsection{"+fix(x)+"}\n"; break;
	}}

TEX::TEX(const char *fn)	{ assert(fh=fopen(fn,"w")); }
TEX::~TEX()					{ 
	head+="\\documentclass[10pt]{article}\n";
	head+="\\usepackage[a5paper,landscape,margin=5mm]{geometry}\n";
	head+="\\title{"+title+"}\n";
	head+="\\author{"+author+"}\n";
	head+="\\begin{document}\n\\maketitle\n\\tableofcontents\n\n";
	foot+="\\end{document}\n";
	fprintf(fh,"%s",head.c_str());
	fprintf(fh,"%s",body.c_str());
	fprintf(fh,"%s",foot.c_str());
	fclose(fh); 
}

// directive

biDirective::biDirective(char *V):biObject("",V) {
	while (val->at(0)!=' '&&val->at(0)!='\t') {
		*cls += val->at(0);
		val->erase(0,1);
		if (val->size()==0) break;
	}
	if (val->size())
		while (val->at(0)==' '||val->at(0)=='\t') val->erase(0,1);

	if (*cls==".title") 	tex.title=tex.fix(*val);
	if (*cls==".author") 	tex.author=tex.fix(*val);
	if (*cls==".sec")		tex.sec(0,*val);
	if (*cls==".sec+")		tex.sec(+1,*val);
	if (*cls==".sec-")		tex.sec(-1,*val);
	if (*cls==".file")		{ 
		if (bi_file) delete bi_file; 
		bi_file=new biFile(new string(*bi_module->val+"/"+*val),'w');
	}
	if (*cls==".eof")		{
		if (bi_file) delete bi_file;
		bi_file=NULL;
	}
}

// writers

void W(string* s, bool tofile)	{ 
	cout << *s; 
	if (tofile&&bi_file) bi_file->W(*s); }
void W(string  s, bool tofile)	{ 
	cout <<  s; 
	if (tofile&&bi_file) bi_file->W( s); }
void W(char c, bool tofile)	{ 
	cout << c; 
	if (tofile&&bi_file) bi_file->W( c); }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { return yyparse(); }

