							/* char \$ \? */
%token <c> CHAR SX QX
							/* = [ ] ( ) < > { } : */
%token <c> EQ LQ RQ LP RP
%token <c> LL GG BL BR COLON
							/* symbol 12.34 'string' (classic Lisp atoms) */
%token <o> SYM NUM STR
							/* directives with special processing */
%token <o> DIRECTIVE
%token <o> MODULE FFILE FEOF INC
							/* nonterminal types: expression list vector block*/
%type <o> ex list vector block
