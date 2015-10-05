#include "pure.hpp"
void yyerror(string err) {
	cerr << "\n\n" << err << " # " << yylineno << " : " << yytext << "\n";
	exit(-1);
}
void W(char      c,bool to_file)	{ cout << c; }
int main() { return yyparse(); }
