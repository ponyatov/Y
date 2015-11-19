# universal script engine (bI abridged dialect)
.file ypp.ypp
$AUTOGEN$
$bICONFIG$
%{
\#include "hpp.hpp"
%}
%defines %union { char c; sym*o; }		/* union for syntax tree elements */
%token <c> CHAR
%token <o> SYM NUM STR EQ LQ RQ LP RP	/* symbol number string = [ ] ( ) */
%type <o> ex list
%left EQ
%%
$MODULE$ :
	| $MODULE$ CHAR 			{ W(\$2); }			/* any undetected char */
	| $MODULE$ ex				{ W(\$2); 			/* bI language expression */
						  W("\\n-------------------");
						  W(\$2->eval());
						  W("\\n========================================");
						}
;
ex : SYM | NUM | STR							/* atomic language elements */
	| LQ list RQ		{ \$\$=\$2; }				/* [list] */
	| LP ex RP			{ \$\$=\$2; }				/* (parens) */
	| ex EQ ex			{ \$\$=\$1; \$\$->join(\$3); }/* SOME = OTHER */
;
list :			{ \$\$=new sym("[","]"); }	/* create new list */
	| list ex	{ \$\$=\$1; \$\$->join(\$2); }	/* add next element */
;
%%
.eof
.file lpp.lpp
$AUTOGEN$
$bICONFIG$
%{
\#include "hpp.hpp"
string StrBuf;
void incFile(sym* inc) {
	yyin = fopen(inc->value.c_str(),"r");
	if (!yyin) yyerror(inc->tagval());
	yypush_buffer_state(yy_create_buffer(yyin,YY_BUF_SIZE));
}
%}
%option noyywrap
%option yylineno
S [\-\+]\?
D [0-9]+
			/* string state */
%x ss
%%
<*>^\#[^\\n]*\\n+		{W(yytext);}	/* full comment line: skip with EOLs */
<*>\#[^\\n]*			{W(yytext);}	/* end line comment */
[ \\t\\r\\n]+			{W(yytext);}	/* drop all spaces */

									/* numbers */
{S}{D}[eE]{S}{D}	TO("num",NUM)	/* float */
{S}{D}\\.{D}			TO("num",NUM)	/* exponential */
{S}{D}				TO("int",NUM)	/* integer */
0x[0-9A-F]+			TO("hex",NUM)	/* hexadecimal int */
0b[01]+				TO("bin",NUM)	/* binary int */

'\\n				{BEGIN(ss);StrBuf="'";}
'					{BEGIN(ss);StrBuf="'";}
<ss>'				{BEGIN(INITIAL);yylval.o=new sym("str",StrBuf+"'");return STR;}
<ss>\\n				{StrBuf+="\\\\n";}
<ss>\\t				{StrBuf+="\\\\t";}
<ss>.				{StrBuf+=yytext;}

#\\'[^\\']*\\'			TO("str",STR)	/* string */
[a-zA-Z0-9_]+		TO("sym",SYM)	/* symbol */
\\%[TFNE\\%]			TO("sym",SYM)	/* special symbol */

\\\=					TO("op",EQ)		/* operators */
\\\[					TO("op",LQ)
\\\]					TO("op",RQ)
\\\(					TO("op",LP)
\\\)					TO("op",RP)

.					TC(CHAR)		/* any other char */
%%
.eof
.inc sym/hpp.bI
