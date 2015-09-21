#include "bI.hpp"

// object

biObject::biObject(const char* C) { 
	cls = new string(C);
	val = new string();
}

biObject::biObject(const char* C,char* V) { 
	cls = new string(C);
	val = new string(V);
}

string* biObject::dump()	{ return new string("<"+*cls+":"+*val+">"); }
string* biObject::eval()	{ return val; }

// string

biString::biString(char *V):biObject("str",V) {}


// tex

TEX tex("bI.tex");

string TEX::fix(string s) {
	string T;
	for ( string::iterator c=s.begin(); c!=s.end(); c++) { switch (*c) {
		case '^':
		case '[':
		case ']':
		case '\\': break;
		case '#': T+="\\#"; break;
		case '$': T+="\\$"; break;
		case '%': T+="\\%"; break;
		default: T+=*c; break;
	}}
	return T;
}

void TEX::W(string x)		{ body+=fix(x); }
void TEX::sec(string x)		{ 
	switch (x[0]) {
		case '+': body+="\\section{"+fix(x)+"}\n"; break;
		case '-': body+="\\subsubsection{"+fix(x)+"}\n"; break;
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


biDirective::biDirective(const char* C,char *V):biObject(C,V) {}
biSec::biSec(char *V):biDirective(".sec",V) { 
	val->erase(val->find(".sec"),4);
	tex.sec(*val);
}

// writers

void W(string* s)	{ cout << *s; }
void W(string  s)	{ cout <<  s; }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { return yyparse(); }

