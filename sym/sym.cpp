
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

string biSymbol::eval() { return value; }

// ///

// \\\ file

void biFile::init() {
	if (bi_file) delete bi_file;
	assert(fh = fopen((bi_module->value+"/"+value).c_str(),"w"));
	bi_file = this;
}

biFile::biFile(biSymbol* T,biSymbol* V):biSymbol(T,V)	{ init(); }
biFile::biFile(const char *V):biSymbol("file",V)		{ init(); }

biFile::~biFile()	{ fclose(fh); }

void biFile::W(string    C) { }
void biFile::W(string  * C) { }
void biFile::W(biSymbol* S) { }

biFile *bi_file = NULL;

// ///

// \\\ module

void biModule::init() {
	if (bi_module) delete bi_module;		// close current module
	if (bi_file) delete bi_file;			// close current file
	#ifdef __MINGW32__
	mkdir(value.c_str());					// create module dir
	#else
	mkdir(value.c_str(),0744);
	#endif
	bi_module = this;						// set current module
	README = new biFile("README.md");		// \ open files AFTER bi_module set
	Makefile = new biFile("Makefile");		// /
}

biModule::biModule(biSymbol* T,biSymbol* V):biSymbol(T,V)	{ init(); }
biModule::biModule(const char *V):biSymbol(".module",V)		{ init(); }

biModule::~biModule()	{ delete README,Makefile; }

biModule *bi_module = new biModule("tmp");

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

