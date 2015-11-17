# generic program module template for bI autogen
# uses app/ template subtree

#.module PIL
#.title bI/PIL
#.about Program In Line
#.author (c) Jonh Doe <jd@mail.com>
#.github

.inc app/readme.bI
.inc app/gitignore.bI

.file ypp.ypp
/***** $AUTOGEN$ *****/
%{
\#include "hpp.hpp"
%}
%defines
%union { char c; sym*o; }
%token <c> CHAR
%token <o> SYM NUM STR
%type <o> ex
%%
$MODULE$:
	| $MODULE$ CHAR	{ W(\$2); } 
	| $MODULE$ ex		{ W(\$2); }
;
ex:	SYM | NUM | STR
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
{S}{D}[eE]{S}{D}	TO("num",NUM);
{S}{D}\\.{D}			TO("num",NUM);
{S}{D}				TO("int",NUM);
\\'[^\\']*\\'			TO("str",NUM);
[a-zA-Z0-9_]+		TO("sym",NUM);
\\n					TC(CHAR)		/* end of line */
.					TC(CHAR)		/* any other char */
%%
.eof

.inc sym/hpp.bI
.inc app/cpp.bI
.inc app/res.bI
.inc app/makefile.bI
.inc app/gvim.bI
