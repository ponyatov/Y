%{
#include "LLVMsh.hpp"
%}
%defines %union { long i; double f; char c; string *s; Sym*o; }
%token <o> SYM NUM STR
%token <o> EQ AT
%token <c> CHAR
%type <o> ex scalar
%%
grammar :
		| grammar ex		{ W($2->eval()); }
		| grammar CHAR	{ W($2); }
;
scalar : SYM | NUM | STR ;
ex : scalar
	| ex AT ex	{ $$=$2; $$->push($1); $$->push($3); }
	| ex EQ ex	{ $$=$2; $$->push($1); $$->push($3); }
;
%%