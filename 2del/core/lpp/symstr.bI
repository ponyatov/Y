<xx>'[^']*'			TX(Str,STR)			/* string */
<xx>[a-zA-Z0-9_]+	TO("sym",SYM)		/* symbol */
<xx>\\%[TFNE\\%]		TO("sym",SYM)		/* specials */
