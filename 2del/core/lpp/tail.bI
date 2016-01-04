\\n					TC(CHAR)			/* line end */
.					TC(CHAR)			/* any undetected char */

<<EOF>>		{ yypop_buffer_state();		/* end of .inluded file */
			if ( !YY_CURRENT_BUFFER )
				yyterminate();}
%%
