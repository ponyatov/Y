%{
\#include "hpp.hpp"
string StrBuf;										/* string parsing buffer */
void incFile(sym* inc) {							/* .inc processing */
	yyin = fopen(inc->value.c_str(),"r");
	if (!yyin) yyerror(inc->tagval());
	yypush_buffer_state(yy_create_buffer(yyin,YY_BUF_SIZE));
}
%}
%option noyywrap
%option yylineno
					/* number sign */
S [\\-\\+]\?
					/* decimal number */
N [0-9]+
					/* directive tail part (after .directive till line end ) */
D [ \\t]*[^\\n]*
					/* expression parsing state */
%x xx
					/* string parsing state */
%x ss
%%
