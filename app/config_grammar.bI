.file ypp.ypp
/***** $AUTOGEN$ *****/
%{
\#include "hpp.hpp"
%}
%defines
%union { char c; sym*o; }
%token <c> CHAR
%token <o> SYM NUM STR EQ LL RR
%type <o> ex list
%%
$MODULE$:
	| $MODULE$ CHAR			{ W(\$2); } 
	| $MODULE$ ex				{ W(\$2); W('\\n'); }
;
ex:	SYM | NUM | STR
	| ex EQ ex			{ \$\$=\$1; \$\$->join(\$3); }
	| LL list RR		{ \$\$ = \$2; }
;
list :					{ \$\$ = new sym("[","]"); }
	| list ex			{ \$\$ = \$1; \$\$->join(\$2); }
;
%%
.eof

.file lpp.lpp
/***** $AUTOGEN$ *****/
%{
\#include "hpp.hpp"
%}
%option noyywrap
%option yylineno
S [\-\+]\?
D [0-9]+
%%
\#[^\\n]*\\n			{}				/* comment line */
{S}{D}[eE]{S}{D}	TO("num",NUM)
{S}{D}\\.{D}			TO("num",NUM)
{S}{D}				TO("int",NUM)
\\'[^\\']*\\'			TO("str",NUM)
[a-zA-Z0-9_]+		TO("sym",NUM)
\\=					TO("op",EQ)
\\\[					TO("op",LL)
\\\]					TO("op",RR)
[ \\t\\r\\n]+			{}				/* drop spaces */
\\n					TC(CHAR)		/* end of line */
.					TC(CHAR)		/* any other char */
%%
.eof
