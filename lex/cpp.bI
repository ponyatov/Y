cpp	= next + file @ 'cpp.cpp'
cpp += '#include "hpp.hpp"\n'
#cpp += '#define YYERR "\\n\\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\\n\\n"\n'
#cpp += 'void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }\n'
#cpp += 'int main() { return yyparse(); }\n'
#cpp += '
#void W(string s) { cout << s; }
#void W(Sym*o) { W(o->dump()); }
#'
cpp += '
int main(int argc, char *argv[]) {
	cerr << "\\n" << MODULE << " : " << TITLE << "\\n" << AUTHOR << "\\n\\n";
	return 0;
}
'
