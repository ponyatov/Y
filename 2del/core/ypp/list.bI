list:				{ \$\$ = new List(); }		/* create new [list] */
	| list ex		{ \$\$ = \$1; \$\$->join(\$2); }	/* add next element */
;
