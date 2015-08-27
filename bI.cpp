#include "bI.hpp"

void yyerror(const char *msg) {
	std::cerr << "\n\nerror @ "<<yylineno<<" ["<<yytext<<"] : "<<msg<<"\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	return yyparse();
}
