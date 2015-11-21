.file ypp.ypp
$AUTOGEN$
%{
\#include "hpp.hpp"
%}
%defines %union { char c; sym *o; }
%token <c> CHAR SX QX
%token <c> EQ LQ RQ LP RP #%token <o> LL GG COLON
%token <o> SYM NUM STR
%type <o> ex list #vector
														/* operators priority */
%left EQ
%%
$MODULE$:
	| $MODULE$ CHAR  { W(\$2); };						/* any undetected char */
	| $MODULE$ SX ex { W(\$3->eval()->value); }		/* insert computed string */
	| $MODULE$ QX ex { W(\$3);						/* dump AST and eval result*/
					  W("\\n----------------");
					  W(\$3->eval());
					  W("\\n============================\\n"); }
;
ex: SYM | NUM | STR
  	| LQ list RQ	{ \$\$ = \$2; }				/* [list] */
	| ex EQ ex		{ \$\$ = \$1; \$\$->join(\$3); }	/* some = other */
;
list:				{ \$\$ = new List(); }		/* create new list */
	| list ex		{ \$\$ = \$1; \$\$->join(\$2); }	/* add next element */
;
%%
.eof
