#include "bI.hpp"

void yyerror(const char *msg) {
	std::cerr << "\n\nerror @ "<<yylineno<<" ["<<yytext<<"] : "<<msg<<"\n\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	cout << "<html>\n";
	cout << "<meta http-equiv=\"Content-Type\" ";
	cout << "content=\"text/html; charset=utf-8\" />\n";
	cout << "<body>\n<pre>\n";
	return yyparse();
}
