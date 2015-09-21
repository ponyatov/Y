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

void TEX::W(string x)		{ assert(fh); fprintf(fh,"%s",x.c_str()); }
TEX::TEX(const char *fn)	{ fh=fopen(fn,"w"); 
}
TEX::~TEX()					{ 
	W("\\documentclass[10pt]{article}\n");
	W("\\usepackage[a5paper,landscape,margin=5mm]{geometry}\n");
	W("\\title{"+title+"}\n");
	W("\\author{"+author+"}\n");
	W("\\begin{document}\n\\maketitle\n\\tableofcontents\n\n");
	W("\\end{document}\n");
	fclose(fh); 
}

// directive


biDirective::biDirective(const char* C,char *V):biObject(C,V) {}
biSec::biSec(char *V):biDirective(".sec",V) { val->erase(val->find(".sec"),4); }

// writers

void W(string* s)	{ cout << *s; }
void W(string  s)	{ cout <<  s; }

// main

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main() { return yyparse(); }

