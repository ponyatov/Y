
#include "sym.hpp"

// \\\ generic symbol type

biSymbol::biSymbol(string T,string V)		{ tag=T; value=V; }
biSymbol::biSymbol(biSymbol* T,biSymbol* V)	{ tag=T->value; value=V->value; }

string biSymbol::dump(int depth) {
	string S="\n"; for(int i=0;i<depth;i++) S+="\t";	// left padding
	S+="<"+tag+":"+value+">";							// symbol header
														// nested symbols
	return S;//+"\n";									// return final string
}

// ///

// \\\ module

biModule::biModule(biSymbol* T,biSymbol* V):biSymbol(T,V) {}
biModule::biModule(const char *V):biSymbol(".module",V) {}

biModule *bi_module = new biModule("tmp");

// ///

// \\\ file

biFile::biFile(biSymbol* T,biSymbol* V):biSymbol(T,V) {}

void biFile::W(string    C) { }
void biFile::W(string  * C) { }
void biFile::W(biSymbol* S) { }

biFile *bi_file=NULL;

// ///

// textout writers
void W(string    C,bool to_file) { cout << C;
	if (to_file && bi_file) bi_file->W(C);
}
void W(string  * C,bool to_file) { cout << *C;
	if (to_file && bi_file) bi_file->W(C);
}
void W(biSymbol* S,bool to_file) { cout << S->dump();
	if (to_file && bi_file) bi_file->W(S);
}

// parser error

void yyerror(string err) {
	cout << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	cerr << "\n" << err << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) { 
	W("#!" + string(argv[0]) + "\n");
	return yyparse();
}

