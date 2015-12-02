%%
bI:
	| bI CHAR		{ W(\$2); }					/* bypass any undetected char */
.inc core/ypp/directive.bI
	| bI SX ex 		{ W(\$3->eval()->value); }		/* insert computed string */
	| bI QX ex 		{ W(\$3);						/* dump AST and eval result */
					  W("\\n----------------");
					  W(\$3->eval());
					  W("\\n============================\\n"); }
;
