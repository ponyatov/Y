/* DO NOT EDIT: this file was autogened by bI language system */
/* <module:sym> */
#include "sym.hpp"
void W(char    c) { cout <<  c; }
void W(string  s) { cout <<  s; }
void W(string *s) { cout << *s; }
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
