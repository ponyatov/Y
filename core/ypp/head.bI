$AUTOGEN$
/* tiny Lisp-like language grammar */
%{
\#include "hpp.hpp"
%}
%defines %union {				/* syntax tree types: char string AST-item */
char c; string *s; sym *o; }	
