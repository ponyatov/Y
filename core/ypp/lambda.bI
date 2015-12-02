lambda:				{ \$\$ = new Lambda(); }		/* create new {lambda} */
	| lambda ex		{ \$\$ = \$1; \$\$->join(\$2); }	/* add next element */
;
