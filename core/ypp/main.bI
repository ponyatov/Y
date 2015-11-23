%%
$MODULE$:
	| $MODULE$ CHAR		{ W(\$2); };					/* any undetected char */
.inc core/ypp/directive.bI
	| $MODULE$ SX ex { W(\$3->eval()->value); }		/* insert computed string */
	| $MODULE$ QX ex { W(\$3);							/* dump AST and eval result */
				  W("\\n----------------");
				  W(\$3->eval());
				  W("\\n============================\\n"); }
;
