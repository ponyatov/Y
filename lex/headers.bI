
hpp_includes = '
															// std.includes
#include <iostream>
using namespace std;

'

hpp_lex = '
															// parser interface
extern int yylex();											// lexer
extern int yylineno;										// current line
extern char* yytext;										// lexed text
#define TOC(C,X) { yylval.o = new C(yytext); return X; }	/* token */
extern int yyparse();										// syntax parser
extern void error(string);									// error callback
#include "ypp.tab.hpp"

'

hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"\n'
hpp += hpp_includes
hpp += hpp_lex
hpp += '#endif // _H_'+upcase@MODULE+'\n'

