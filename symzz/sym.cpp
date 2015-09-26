
#include "sym.hpp"

// symbol

sym::sym(string C,string V)	{ cls=C; val=V; }
sym::sym(sym* A, sym* B)	{ cls=A->val; val=B->val; }

string mult(int n) { string s; for (int i=0;i<n;i++) s+="\t"; return s; }

string sym::dump(int depth)	{ return "\n"+mult(depth)+"<"+cls+":"+val+">"; }

string sym::eval()	{ return val; }

map<string,sym*> env;

// module

void module::init() {
	#ifdef __MINGW32__
	mkdir(val.c_str()); 
	#else
	mkdir(val.c_str(),0744); 
	#endif
	curr_module=this;
}

module::module(sym* A, sym* B):sym(A,B)		{ init(); }
module::module(string A):sym(".module",A)	{ init(); }

module *curr_module = new module("tmp");

// file

ffile::ffile(sym*A,sym*B):sym(A,B) {
	if (curr_file!=NULL) delete curr_file;
	assert(fh=fopen((curr_module->val+"/"+val).c_str(),"w"));
	curr_file=this;
};
ffile::~ffile() 			{ fclose(fh); curr_file=NULL; };

ffile *curr_file=NULL;

// error

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

void W(char c, bool tofile)		{ cout << c; 
	if (tofile && curr_file) fprintf(curr_file->fh,"%c",c); }
void W(string s, bool tofile)	{ cout << s;
	if (tofile && curr_file) fprintf(curr_file->fh,"%s",s.c_str()); }
void W(sym* s, bool tofile)		{ cout << s->dump();
	if (tofile && curr_file) fprintf(curr_file->fh,"%s",s->eval().c_str()); }

int main(int argc, char *argv[]) {
	cout << "# " << argv[0] << "\n";
	return yyparse();
}

