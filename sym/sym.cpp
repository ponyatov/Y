/* DO NOT EDIT: this file was autogened by bI language system */
/* <module:sym> */
#include "sym.hpp"
// \ Object
biObject::biObject(string T,string V)	{ tag = T; value = V; }
string biObject::dump(int depth)		{ return "<"+tag+":"+value+">"; }
// /
// \ Directive
biDirective::biDirective(string V):biObject("",V) {
	// autogenerate tag & value
	while (value.size() && ( value[0] != ' ' && value[0] != '\t'))
		{ tag += value[0]; value.erase(0,1); }
	while (value.size() && ( value[0] == ' ' || value[0] == '\t'))
		{                  value.erase(0,1); }
	// process specific directive tag
	if (tag == ".module") bi_module = new biModule(value);
}
// /
// \ Module
biModule::biModule(string V):biObject("module",V) {
	mkdir(value.c_str());
}
biModule *bi_module = new biModule("tmp");
// /
// \ writers
void W(char      c) { cout <<  c; }
void W(string    s) { cout <<  s; }
void W(string   *s) { cout << *s; }
void W(biObject *o) { cout << o->dump(); }
// /
void yyerror(string msg) {
	cout << "\n\n" << msg << "#" << yylineno << ":" << yytext << "\n\n";
	cerr << "\n\n" << msg << "#" << yylineno << ":" << yytext << "\n\n";
	exit(-1); }
int main(int argc, char *argv[]) {
	cout << "# " << AUTOGEN << "\n";
	cout << "# <module:" << MODULE << ">\n";
	cout << "# argv[0]:\t" << argv[0] << "\n\n";
	return yyparse();
}
