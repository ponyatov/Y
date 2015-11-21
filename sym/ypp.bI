.file ypp.ypp
$AUTOGEN$
%{
\#include "hpp.hpp"
%}
%defines %union { char c; sym *o; }
%token <c> CHAR #SX QX
#%type <o> ex list vector
%%
$MODULE$:
	| $MODULE$ CHAR { W(\$2); }
;
%%
.eof
