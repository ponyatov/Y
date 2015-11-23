	| $MODULE$ MODULE		{ W(\$2);
					  if (curr_module) delete curr_module;
					  curr_module = new Module(\$2->value);
					  env["MODULE"] = curr_module; }
	| bI FFILE CHAR	{ W(\$2,false); W(\$3,false); }		/* drop <.file:..>*/
	| bI FEOF  CHAR	{ W(\$2,false); W(\$3,false); }		/* drop <.eof:..> */
	| bI INC   		{ W(\$2,false); }					/* drop <.inc:..> */
	| $MODULE$ DIRECTIVE 	{ W(\$2); }

