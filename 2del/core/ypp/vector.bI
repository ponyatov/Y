vector:				{ \$\$ = new Vector(); }		/* create new <vector> */
	| vector ex		{ \$\$ = \$1; \$\$->join(\$2); }	/* add next element */
;
