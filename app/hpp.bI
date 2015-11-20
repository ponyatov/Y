.file hpp.hpp
$AUTOGEN$
\#ifndef _H_$MODULE$
\#define _H_$MODULE$
.inc sym/meta.pil
.inc sym/stdinc.pil

?ctype:string='std::string'?

?class:Symbol
	= string:tag
	= string:value
	= (init =<tag,value>)
?

.inc sym/sym.pil
\#endif // _H_$MODULE$
.eof
