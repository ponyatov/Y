\\.						T1(C)						/* escaped char */
<*>#[^\n]*\n			{}							/* line comment */

^\.[a-z]+[ \t]*/\{		TX(biDirective,DIRECTIVE)	/* {} blocked directive */
^\.file+[ \t]+[^\n]*	TX(biDirective,FFILE)		/* .file */
^\.eof					TX(biDirective,FEOF)		/* .eof */
^\.[a-z]+[ \t]*[^\n]*	TX(biDirective,DIRECTIVE)	/* directive */

<*>\'[^\']*\'			TO("str",STR)				/* 'string' */
<*>\"[^\"]*\"			TO("str",STR)				/* "string" */
													
{D}						TO("int",NUM)				/* numeric literals */
0x[0-9A-F]+				TO("hex",NUM)
0b[01]+					TO("bin",NUM)
{D}\.{D}				TO("float",NUM)
{D}[eE]{S}{D}			TO("float",NUM)
													/* operators */
\+						TO("+",ADD)
\-						TO("-",SUB)
\*						TO("*",MUL)
\/						TO("/",DIV)
\^						TO("^",POW)

^class[ \t]+				{BEGIN(ss); TS(CLASS);}			/* class keyword */
<ss>\n\n					{BEGIN(INITIAL); TS(ENDCLASS);}
<ss>[ \t]+					{W(yytext);}					/* drop spaces */
<ss>[a-zA-Z][a-zA-Z0-9]*	TO("sym",SYM)					/* symbol */

<ss>:						TX(biOP,COLON)					/* : */
<ss>=						TX(biOP,EQ)						/* = */

\n						TC(EOL)						/* end line syntax marker */
.						TC(C)						/* any undetected char */

