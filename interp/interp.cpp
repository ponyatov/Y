#include "interp.hpp"

void yyerror(string err) {
	cout << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	cerr << "\n" << err << " # " << yylineno << " : [" << yytext << "]\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
   cout << "# " << argv[0] << "\n";
   return yyparse();
}

