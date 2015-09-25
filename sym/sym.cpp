
#include "sym.hpp"

// symbol

sym::sym(string C,string V)	{ cls=C; val=V; }
sym::sym(sym* A, sym* B)	{ cls=A->val; val=B->val; }

string sym::dump()	{ return "<"+cls+":"+val+">"; }
string sym::eval()	{ return val; }

// module

module::module(sym* A, sym* B):sym(A,B)		{ mkdir(val.c_str()); curr_module=this; }
module::module(string A):sym(".module",A)	{ mkdir(val.c_str()); curr_module=this; }

module *curr_module = new module("tmp");

// file

ffile::ffile(sym*A,sym*B):sym(A,B)			{ 
	assert(fh=fopen((curr_module->val+"/"+val).c_str(),"w")); curr_file=this; }
ffile::~ffile() {
	if (curr_file) { fclose(fh); curr_file=NULL; }}
void ffile::W(string s)	{
	fprintf(fh,"%s",s.c_str()); }
void ffile::W(char c)	{
	fprintf(fh,"%c",c); }
ffile *curr_file=NULL;

// error

void yyerror(string s) {
	cerr << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << "\n\n" << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

void W(char c, bool tofile)	{ 
	cout << c; 
	if (tofile&&curr_file) curr_file->W(c); }
void W(string s, bool tofile)	{ 
	cout << s; 
	if (tofile&&curr_file) curr_file->W(s); }
void W(sym* s, bool tofile)	{ 
	cout << s->dump(); 
	if (tofile&&curr_file) curr_file->W(s->dump()); }

int main(int argc, char *argv[]) {
	cout << "# " << argv[0] << "\n";
	return yyparse();
}

