	| bI MODULE		{ W(\$2,false); }
	| bI FFILE CHAR	{ W(\$2,false); W(\$3,false); }	/* drop <.file:..>*/
	| bI FEOF  CHAR	{ W(\$2,false); W(\$3,false); }	/* drop <.eof:..> */
	| bI INC   		{ W(\$2,false); W("\\n",false); }	/* drop <.inc:..> */
	| bI DIRECTIVE 	{ W(\$2); }
