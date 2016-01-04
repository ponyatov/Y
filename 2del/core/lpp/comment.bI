<*>^\#[^\\n]*\\n+		{W(yytext,false);}	/* full line comment with EOLs */
<*>\#[^\\n]*			{W(yytext,false);}	/* comment at rest line */
