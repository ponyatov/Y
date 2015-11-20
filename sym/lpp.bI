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
%%
%%
\\n			TC(CHAR)
.			TC(CHAR)
#<<EOF>>		{ yypop_buffer_state(); if ( !YY_CURRENT_BUFFER ) yyterminate();}
.eof
