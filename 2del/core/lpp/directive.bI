^\\.end				{W(new Directive(yytext),false);yyterminate();}
^\\.module{D}		TX(Directive,MODULE)
^\\.file{D}			TX(Directive,FFILE)
^\\.eof				TX(Directive,FEOF)
^\\.inc{D}			TX(Directive,INC)
^\\.[a-z]+{D}		TX(Directive,DIRECTIVE)
