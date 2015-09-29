\\.						T1(C)						/* escaped char */

^\.file+[ \t]+[^\n]*	TX(biDirective,FFILE)		/* .file */
^\.eof					TX(biDirective,FEOF)		/* .eof */

													

^class[ \t]+				{BEGIN(ss); TS(CLASS);}			/* class keyword */
<ss>\n\n					{BEGIN(INITIAL); TS(ENDCLASS);}

<ss>:						TX(biOP,COLON)					/* : */
<ss>=						TX(biOP,EQ)						/* = */

\n						TC(EOL)						/* end line syntax marker */
.						TC(C)						/* any undetected char */

