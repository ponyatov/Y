	| $MODULE$ MODULE		{ W(\$2);
					  if (curr_module) delete curr_module;
					  curr_module = new Module(\$2->value);
					  env["MODULE"] = curr_module; }
	| $MODULE$ FFILE		{ W(\$2); }
	| $MODULE$ FEOF		{ W(\$2); }
	| $MODULE$ DIRECTIVE 	{ W(\$2); }

