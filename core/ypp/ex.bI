ex: SYM | NUM | STR								/* atoms (primary types)*/
	| LP ex RP		{ \$\$ = \$2; }				/* (parenthes)			*/
  	| LQ list RQ	{ \$\$ = \$2; }				/* [list]				*/
  	| LL vector GG	{ \$\$ = \$2; }				/* <vector>				*/
	| BL block BR	{ \$\$ = \$2; }				/* {block}				*/
	| ex COLON ex	{ \$\$ = new Pair(\$1,\$3); }	/* pa:ir				*/
	| ex EQ ex		{ \$\$ = \$1; \$\$->join(\$3); }	/* some = nested		*/
;
