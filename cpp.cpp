#include "h.h"

void yyerror(const char *msg) {
	std::cerr << "\n\nerror @ "<<yylineno<<" : "<<yytext<<"\n"<<msg<<"\n\n";
}

int main(int argc, char *argv[]) {
	std::cerr << "# " << argv[0] << "\n";
	yyparse();
	std::cerr << "\n###\n";
	return 0;
}
