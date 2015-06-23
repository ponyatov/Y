%option main
%option yylineno

%{
//#include <stdio.h>
//#include <stdlib.h>
#include <iostream>
#include <string>
%}

%%

.		{
			std::cerr << "\n\nY lexer: unknown token @ line "<<yylineno<<": "; 
			std::cerr << yytext << "\n\n";
			yyterminate();
		}

%%


/*
{
                    String msg("some error with number: "); msg.append(yytext);
                    yyerror(msg.c_str());
                   }
*/
