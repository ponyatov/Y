							/* char markers: \$ \? */
%token <c> CHAR SX QX
							/* = ( ) */
%token <c> EQ LP RP
							/* list: [ ] vector: < > */
%token <c> LQ RQ LL GG 
							/* lambda: { } : \@ */
%token <c> BL BR COLON DOG
							/* symbol 12.34 'string' (classic Lisp atoms) */
%token <o> SYM NUM STR
							/* directives with special processing */
%token <o> DIRECTIVE
%token <o> MODULE FFILE FEOF INC
							/* nonterminal types: expression list vector block*/
%type <o> ex list vector lambda
