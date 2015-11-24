block:				{ \$\$ = new Block(); }		/* create new {block} */
	| block ex		{ \$\$ = \$1; \$\$->join(\$2); }	/* add next element */
;
