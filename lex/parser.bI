yacc = next + file @ 'ypp.ypp'
yacc += '%{\n#include "hpp.hpp"\n%}\n'
yacc += '%defines %union { Sym*o; }\n'
yacc += '%token <o> SYM NUM STR\t\t\t\t/* symbol number \'string\' */\n'
yacc += '%token <o> L R LQ RQ LB RB\t\t\t/* ( ) [ ] { } */\n'
yacc += '%token <o> EQ AT COLON DOT\t\t\t/* = @ : . */\n'
yacc += '%type <o> ex scalar list lambda\t\t/* expression scalar [list] {lambda} */\n'
yacc += '%%\n'
yacc += 'REPL\t: | REPL ex { W($2->eval()); } ;\n'
yacc += 'scalar\t: SYM | NUM | STR ;\n'
yacc += 'ex\t\t: scalar'
yacc += '
		| L ex R			{ $$=$2; }
		| LQ list RQ		{ $$=$2; }
		| LB lambda RB		{ $$=$2; }
;
list	:					{ $$=new List(); }
		| list ex			{ $$=$1; $$->push($2); }
;
lambda	:					{ $$=new Lambda(); }
		| lambda SYM COLON	{ $$=$1; $$->parval($2); }
		| lambda ex			{ $$=$1; $$->push($2); }
;
'
yacc += '%%\n'

yacc_hpp = '
													// == parser interface ==
extern int yyparse();								// run parser
extern void yyerror(string);						// error callback
#include "ypp.tab.hpp"								// token defines for lexer
'
