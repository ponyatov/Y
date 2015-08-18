#include "bI.hpp"

void yyerror(const char *msg) {
	std::cerr << "\n\nerror @ "<<yylineno<<" ["<<yytext<<"] : "<<msg<<"\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	return yyparse();
}


//biID::biID(char *val) {
//	value = new std::string(val);
//}

//biID::~biID() { delete value; }
//
//std::string* biID::str() { return value; }
