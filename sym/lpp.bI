.file lpp.lpp
$AUTOGEN$
%{
\#include "hpp.hpp"
#string StrBuf;
#void incFile(sym* inc) {
#	yyin = fopen(inc->value.c_str(),"r");
#	if (!yyin) yyerror(inc->tagval());
#	yypush_buffer_state(yy_create_buffer(yyin,YY_BUF_SIZE));
#}
%}
%option noyywrap
%option yylineno
S [\\-\\+]\?
D [0-9]+
X [ \\t]*[^\\n]*
					/* expression parsing state */
%x xx
%%
\\\\.						T1(CHAR)
<*>^\#[^\\n]*\\n+			{W(yytext,false);}	/* full line comment with EOLs */
<*>\#[^\\n]*				{W(yytext,false);}	/* comment at rest line */

\\\$						{BEGIN(xx);TC(SX);}	/* expression mode on: inline str*/
\\\?						{BEGIN(xx);TC(QX);}	/* expression mode on: debug dump */
<xx>[\\\$\\\?]				{BEGIN(INITIAL);}	/* expression mode off (inline) */
<xx>[ \\t\\r\\n]+			{}					/* drop spaces in expression mode */

												/* numbers */
<xx>{S}{D}\\.{D}[eE]{S}{D}	TO("num",NUM)		/* exponential */
<xx>{S}{D}[eE]{S}{D}		TO("num",NUM)		/* exponential */
<xx>{S}{D}\\.{D}				TO("num",NUM)		/* float */
<xx>{S}{D}					TO("int",NUM)		/* integer */
<xx>0x[0-9A-F]+				TO("hex",NUM)		/* hexadecimal int */
<xx>0b[01]+					TO("bin",NUM)		/* binary int */

<xx>'[^']*'				TO("str",STR)		/* string */
<xx>[a-zA-Z0-9_]+		TO("sym",SYM)		/* symbol */
<xx>\\%[TFNE\\%]			TO("sym",SYM)		/* specials */

<xx>\\=					TC(EQ)			/* operators */
<xx>\\[					TC(LQ)			/* [list begin */
<xx>\\]					TC(RQ)			/* list end] */
<xx>\\(					TC(LP)
<xx>\\)					TC(RP)

\\n			TC(CHAR)
.			TC(CHAR)
#<<EOF>>		{ yypop_buffer_state(); if ( !YY_CURRENT_BUFFER ) yyterminate();}
%%
.eof
