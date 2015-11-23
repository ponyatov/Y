							/* char \$ \? */
%token <c> CHAR SX QX
							/* = [ ] ( ) < > : */
%token <c> EQ LQ RQ LP RP LL GG COLON
							/* symbol 12.34 'string' (classic Lisp atoms) */
%token <o> SYM NUM STR
							/* directives with special processing */
%token <o> DIRECTIVE
%token <o> MODULE FFILE FEOF INC
							/* nonterminal types: expression list vector */
%type <o> ex list vector
