
#include "sym.hpp"

void yyerror(string s) {
	cerr << s << " # " << yylineno << " : " << yytext << "\n\n";
	cout << s << " # " << yylineno << " : " << yytext << "\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	cout << "# " << argv[0] << "\n";
	return yyparse();
}

