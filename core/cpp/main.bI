// main .cpp part

\#define YYERR "\\n\\n"<<msg<<" \#"<<yylineno<<" ["<<yytext<<"]\\n\\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }	// error()
int main() { env_init(); return yyparse(); }						// main()
